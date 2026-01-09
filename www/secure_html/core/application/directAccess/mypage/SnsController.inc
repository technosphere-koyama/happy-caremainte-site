<?php

/* * **********************************
 * NAME:SnsController
 * DESC:
 *  SNS用のコントローラ(クローズエリア)
 * 	SNS登録者と分離させるためにこのコントローラを別途作成
 * 
 *  コントローラの継承
 *  SnsController
 *  ↓
 *  MypageCloseCommonControllerFrame
 *  ↓
 *  MypageBaseCommonControllerFrame
 *  ↓
 *  ControllerCore
 *  となる
 * 
 * NOTICE:
 * CREATE: 2016.12.7 aoyama
 * *********************************** */

class SnsController extends MypageCloseCommonControllerFrame {

	private $sGroup;
	private $public_user_data;

	/* Constructor */
	public function __construct() {

		parent::__construct();

		//セッショングループを設定
		$this->sGroup = 'mypage';

		//セッションからユーザ情報を取得
		$this->public_user_data = SESSION::read(CONF::read('LOGIN_CATEGORY.PUBLIC'));

		//プロフィールリンク用に
		$this->set("user_link", "/profile/?uid=" . $this->public_user_data['system_id']);

		$this->set("page_group", "community");
	}

	/*	 * **********************************
	 * NAME  : index
	 * INPUT : NONE
	 * OUTPUT: NONE
	 * DESC  :
	 *  マイページのトップ画面アクセスした際にフロントより実行されるメソッド
	 * NOTICE:
	 * CREATE: 2016.10.21 aoyama
	 * UPDATE: 2017.09.20 aoyama
	 * *********************************** */
	public function index() {
		
		$image = new Image();
        $community = new CommunityModel();


		// 表示に必要な情報をセット
		$this->set("nickname", $this->public_user_data['nickname']);
		$this->set("system_id", $this->public_user_data['system_id']);
		$this->set("system_user_id", $this->public_user_data['system_user_id']);
		$this->set("avatar", $image->get_avatar_url($this->public_user_data['system_id']));

		/*
		 * タイムライン取得
		 */
		$timeline = new TimelineModel();

		//ページ指定文字のサニタイズ
		$pd = (InputVali::is_num(REQUEST::get_data('pd'))) ? REQUEST::get_data('pd') : 0;
		$pp = (InputVali::is_num(REQUEST::get_data('pp'))) ? REQUEST::get_data('pp') : CONF::read('PAGING.DEFAULT_NUM_PUBLIC');
		
		$this->set("pd",$pd);
		$this->set("pp",$pp);

		$tvViewArray = array();
		$timeline_ids = array();
        $thread_ids = array();
        $response_ids = array();

		foreach ($timeline->get_timeline_self($this->public_user_data['user_id'], $pd, $pp) AS $tlValue) {

			// 画像ファイルの表示用配列初期化(2017.2.13 aoyama)
			$file_url = array();

			switch ($tlValue['type']) {

				case "response":
					$file_url = $community->get_community_response_image($tlValue['thread_id'], $tlValue['code']);
                    $response_ids[] = $tlValue['code'];
                    $thread_ids[] = $tlValue['thread_id'];
					$mypost = false;
					break;
				case "timeline":
					//imageクラスではなくtimelineクラスで取得する方式に変更
					//$file_url = $image->get_timeline_url($tlValue['system_id'], $tlValue['code']);
					$file_url = $timeline->get_timeline_image($tlValue['system_id'], $tlValue['code']);
					$mypost = ($tlValue['user_id'] == $this->public_user_data['user_id']) ? true : false;
					$timeline_ids[] = $tlValue['code'];
					break;
			}

			$tvViewArray[] = array(
				"mypage_id" => $tlValue['code'],
				"prefix" => $tlValue['type'],
				"thread_id" => $tlValue['thread_id'],
				"thread_name" => $tlValue['thread_name'],
				"system_id" => $tlValue['system_id'],
				"nickname" => $tlValue['nickname'],
				"like_count" => $tlValue['like_count'],
				"text" => $tlValue['text'],
				"text_view" => StaticFunction::decode_view_text(nl2br($tlValue['text'])),
				"file_url" => $file_url,
				"publication" => $tlValue['publication'],
				"avatar" => $image->get_avatar_url($tlValue['system_id']),
				"update_time" => DbDateTime::get_date_type_dot($tlValue['update_time']),
				"is_my_post" => $mypost
			);
		}
		$this->set("timeline_array", $tvViewArray);

        /* 自身が参加しているコミュニティの配列をviewに渡す */
        $this->set("community_match", $community->get_community_match_user($thread_ids,$this->public_user_data['user_id']));

		/* timeline返信を取得しviewに渡す */
		$timeline_response_array = array();
		foreach ($timeline->get_timeline_response($timeline_ids) AS $value) {
			$edit_response_link = "";
			// 自分のレビューコメントの時はレビューの編集ボタンリンクを設定。これをviewの表示判定にも使用。
			if ($value['user_id'] == $this->public_user_data['user_id']) {
				$edit_response_link = "/mypage/response_delete.html?tr_id=" . $value['timeline_response_id'];
				$edit_response_link .= "&token=" . SESSION::read('EXPIRES.ORIGINAL_TOKEN');
				$edit_response_link .= "&pd=" . REQUEST::get_data('pd');
				$edit_response_link .= "&pp=" . REQUEST::get_data('pp');
			}

			$timeline_response_array[$value['timeline_id']][] = array(
				"timeline_response_id" => $value['timeline_response_id'],
				"user_id" => $value['user_id'],
				"nickname" => $value['nickname'],
				"avatar" => $image->get_avatar_url($value['system_id']),
				"user_link" => "/profile/?uid=" . $value['system_id'],
				"timeline_id" => $value['timeline_id'],
				"response_text" => StaticFunction::decode_view_text(nl2br($value['response_text'])),
				"update_time" => DbDateTime::get_date_type_dot($value['update_time']),
				"edit_link" => $edit_response_link
			);
		}
		$this->set("timeline_response_array", $timeline_response_array);

        // コミュニティのコメントを取得
        $comment_array = array();
        foreach ($community->get_comment_list($response_ids) AS $value) {
            $edit_response_link = "";
            // 自分のレビューコメントの時はレビューの編集ボタンリンクを設定。これをviewの表示判定にも使用。
            if ($value['user_id'] == $this->public_user_data['user_id']) {
                $edit_response_link = "/community/comment_delete.html?comment_id=" . $value['comment_id'];
                $edit_response_link .= "&token=" . SESSION::read('EXPIRES.ORIGINAL_TOKEN');
            }
            $comment_array[$value['response_id']][] = array(
                "nickname" => $value['nickname'],
                "avatar" => $image->get_avatar_url($value['system_id']),
                "user_link" => "/profile/?uid=" . $value['system_id'],
                "comment_id" => $value['comment_id'],
                "comment_text" => StaticFunction::decode_view_text(nl2br($value['comment_text'])),
                "update_time" => DbDateTime::get_date_type_dot($value['update_time']),
                "edit_link" => $edit_response_link
            );
        }
        $this->set("comment_array", $comment_array);


		/* ページング用 */
		$tl_count = $timeline->get_timeline_self_count($this->public_user_data['user_id']);

		$page = new PAGING();
		$this->set("pageng_html", $page->make_paging($tl_count));

		//いいねしているコメントの配列を取得
		$like = new LikeModel();
		$like_for_js = $like->get_mypage_like_own($this->public_user_data['user_id'], $tvViewArray);

		$in_array = array();
		foreach ($like_for_js AS $val) {
			$in_array[] = "'" . $val['prefix'] . ":" . $val['target_id'] . "'";
		}
		$mypage_like_array = implode(",", $in_array);

		$this->set("mypage_like_array", $mypage_like_array);

		//フレンドリストを表示
		$friend = new UserMatchModel();
		$friendList = $friend->get_friend_list($this->public_user_data['user_id'], 0, 5, 'commit');

		$friendArray = array();
		if (!StaticFunction::is_empty($friendList)) {
			foreach ($friendList AS $value) {

				$friendArray[] = array(
					"nickname" => $value['nickname'],
					"system_id" => $value['system_id'],
					"avatar" => $image->get_avatar_url($value['system_id'])
				);
			}
		}
		$this->set("friendArray", $friendArray);

		/*
		 * タイムライン投稿用
		 */

		// POSTデータがある場合、セッションに登録する。
		if (!StaticFunction::is_empty(REQUEST::post_data())) {

			SESSION::write($this->sGroup . '.comment', REQUEST::post_data('comment'));
			SESSION::write($this->sGroup . '.publication', REQUEST::post_data('publication'));
			SESSION::write($this->sGroup . '.file', true);
			if (!StaticFunction::is_empty(REQUEST::post_data('tl_id'))) {
				SESSION::write($this->sGroup . '.tl_id', REQUEST::post_data('tl_id'));
				$this->set("tl_id", REQUEST::post_data('tl_id'));
			}

			//ファイル添付がある場合
			/*
			 * 今のところ画像ファイルだけだが、
			 * 動画ファイルなどが対象になると大幅に工数UPになるかなと
			 * ファイル用のライブラリも必要になる
			 * UPDATE: 2017.2.12 aoyama
			 * 		複数画像の対応
			 */

			$file = new Image();

			//POSTされた画像のカウントをリセット
			$file_count = 0;

			// 一時ファイルのセッション用配列を初期化
			$tmp_file_name = array();
			$tmp_date_dir = array();
			$date_dir = array();

			foreach ($_FILES['timeline_file']['error'] AS $post_image_array) {
				if ($post_image_array === UPLOAD_ERR_OK) {

					//一時ファイル名を生成(連続対応のためカウンタ)
					$file_tmp_hash = Encrypt::member_regist_token($this->public_user_data['user_id'], time());
					$file_tmp_hash .= "_" . $file_count;

					//画像をロード
					$ret = $file->load($_FILES['timeline_file']['tmp_name'][$file_count]);

					//拡張子取得
					$thumb_ext = $file->get_image_type();

					//リサイズ
					//$thumb->resize_avatar(CONF::read("AVATAR.WIDTH"));
					//一時保存先システムディレクトリ[/public/images/tmp/[yyyymm]]
					$date_dir[$file_count] = DbDateTime::fairing_digit_8(DbDateTime::get_cur_datetime());
					$tmp_date_dir = DIR_SYSTEM_IMG_TMP . DS . $date_dir[$file_count] . DS;

					//一時ファイル名
					$tmp_file_name[$file_count] = $file_tmp_hash . '.' . $thumb_ext;

					//tmpディレクトリに保存
					//$ret = $file->save_jpeg($avatar_tmp_dir, $tmp_file_name);
					//tmpフォルダに移動
					$file->move_file("", $_FILES['timeline_file']['tmp_name'][$file_count], $tmp_date_dir, $tmp_file_name[$file_count]);
				}
				$file_count++;
			}

			//一時ファイルのファイル名と一時ディレクトリをセッションに保存
			SESSION::write($this->sGroup . '.tmp_file_name', $tmp_file_name);
			SESSION::write($this->sGroup . '.tmp_file_date', $date_dir);

//			return;
//			
//			if ($_FILES['timeline_file']['error'] == UPLOAD_ERR_OK) {
//
//				$file = new Image();
//
//				//一時ファイル名を生成
//				$file_tmp_hash = Encrypt::member_regist_token($this->public_user_data['user_id'], time());
//
//				//ロード
//				if (!$ret = $file->load($_FILES['timeline_file']['tmp_name'])) {
//					SESSION::write($this->sGroup . '.file',false);
//				}
//				else {
//
//					//拡張子取得
//					$thumb_ext = $file->get_image_type();
//
//					//リサイズ
//					//$thumb->resize_avatar(CONF::read("AVATAR.WIDTH"));
//					//tmp保存先システムディレクトリ[/public/images/tmp/[yyyymm]]
//					$date_dir = DbDateTime::fairing_digit_8(DbDateTime::get_cur_datetime());
//					$tmp_dir = DIR_SYSTEM_IMG_TMP . DS . $date_dir . DS;
//
//					//tmpファイル名
//					$tmp_file_name = $file_tmp_hash . '.' . $thumb_ext;
//
//					//tmpディレクトリに保存
//					//$ret = $file->save_jpeg($avatar_tmp_dir, $tmp_file_name);
//					//tmpフォルダに移動
//					$file->move_file("", $_FILES['timeline_file']['tmp_name'], $tmp_dir, $tmp_file_name);
//
//					SESSION::write($this->sGroup . '.tmp_file_name', $tmp_file_name);
//					SESSION::write($this->sGroup . '.tmp_file_date', $date_dir);
//				}
//			}

			$this->checkSessionParameter();
			$error_array = ALERT::get_session();

			if (!StaticFunction::is_empty($error_array)) {
                $this->set('error_array', $error_array);
				$this->formReturn();
				return;
			}

			//問題なければ確認画面へ
			$this->redirect("./complete.html");
		}
		$this->formReturn();
		//戻るボタンで帰ってviewに渡しきったのでセッション削除
		SESSION::delete($this->sGroup);
	}

	/*	 * **********************************
	 * NAME  : confirm
	 * INPUT : NONE
	 * OUTPUT: NONE
	 * DESC  :
	 *  マイページのトップ画面アクセスした際にフロントより実行されるメソッド
	 * NOTICE:
	 * CREATE: 2016.10.21 aoyama
	 * *********************************** */
	public function confirm() {

		$image = new Image();

		$this->set("tl_id", REQUEST::get_data('tl_id'));

		// 表示に必要な情報をセット
		$this->set("nickname", $this->public_user_data['nickname']);
		$this->set("system_id", $this->public_user_data['system_id']);
		$this->set("system_user_id", $this->public_user_data['system_user_id']);
		$this->set("date", DbDateTime::get_date_type_dot(DbDateTime::get_cur_datetime()));
		$this->set("avatar", $image->get_avatar_url($this->public_user_data['system_id']));

		//フレンドリストを表示
		$friend = new UserMatchModel();
		$friendList = $friend->get_friend_list($this->public_user_data['user_id'], 0, 5, 'commit');

		$friendArray = array();
		if (!StaticFunction::is_empty($friendList)) {
			foreach ($friendList AS $value) {

				$friendArray[] = array(
					"nickname" => $value['nickname'],
					"system_id" => $value['system_id'],
					"avatar" => $image->get_avatar_url($value['system_id'])
				);
			}
		}
		$this->set("friendArray", $friendArray);

		$this->formReturn();
	}

	/*	 * **********************************
	 * NAME  : complete
	 * INPUT : NONE
	 * OUTPUT: NONE
	 * DESC  :
	 * 		タイムライン投稿を登録、変更するメソッド
	 * NOTICE:
	 * CREATE: 2016.11.10 aoyama
	 * UPDATE: 2016.11.14 aoyama
	 * 		微調整
	 * UPDATE: 2016.12.12 aoyama	
	 * 		公開範囲設定対応
	 * *********************************** */
	public function complete() {

		if (StaticFunction::is_empty(SESSION::read($this->sGroup))) {
			$this->redirect("/mypage/sns.html");
		}

		/*
		 * バリデーション:エラーのときはindex.htmlに飛ばす
		 * indexのcheckSessionParameterとエラー情報の渡し方が異なる理由として
		 * ここでバリデーションに引っかかるということは予期しないアクセスなので
		 * そこまで親切にしなくてもいいかなと。(aoyama)
		 */
		$error_array = $this->checkSessionParameter();
		if (!StaticFunction::is_empty($error_array)) {
			$this->redirect("/mypage/sns.html");
		}

		$timeline = new TimelineModel();
		$datetime = DbDateTime::get_cur_datetime();

		//編集モード
		if (!StaticFunction::is_empty(SESSION::read($this->sGroup . '.tl_id'))) {

			//コミュニティの詳細を取得する
			$timeline_detail = $timeline->get_detail_by_id(SESSION::read($this->sGroup . '.tl_id'), $this->public_user_data['user_id']);
			if (StaticFunction::is_empty($timeline_detail)) {
				$this->redirect("/mypage/sns.html");
			}

			// タイムライン更新処理
			// 配列にPOSTデータを格納
			$param_list = array(
				'update_time' => DbCast::datetime($datetime),
				"comment" => DbCast::string(SESSION::read($this->sGroup . '.comment')),
				"publication" => DbCast::integer(SESSION::read($this->sGroup . '.publication'))
			);

			//画像がある場合はファイル名も更新
			if (!StaticFunction::is_empty(SESSION::read($this->sGroup . '.tmp_file_name'))) {
				$param_list += array(
					"image_file" => DbCast::string(SESSION::read($this->sGroup . '.tmp_file_name'))
				);
			}

			$condition = array(
				"WHERE" => array(
					"timeline_id" => DbCast::id(SESSION::read($this->sGroup . '.tl_id'))
				)
			);
			/* DB登録エラー */
			if (!$update = $timeline->update($param_list, $condition)) {
				LOGS_ERR("タイムライン編集に失敗しました。");
			}

			//画像保存用にタイムラインIDを保持(2017.2.13)
			$tl_id = SESSION::read($this->sGroup . '.tl_id');
		}

		//新規登録モード
		else {
			$datetime = DbDateTime::get_cur_datetime();
			// スレッド登録処理
			// 配列にPOSTデータを格納
			$param_array = array(
				'update_time' => DbCast::datetime($datetime),
				'create_time' => DbCast::datetime($datetime),
				"active" => DbCast::float(DB_ACTIVE_ON),
				'user_id' => DbCast::id($this->public_user_data['user_id']),
				"comment" => DbCast::string(SESSION::read($this->sGroup . '.comment')),
				"image_file" => DbCast::string(SESSION::read($this->sGroup . '.tmp_file_name')[0]),
				"publication" => DbCast::integer(SESSION::read($this->sGroup . '.publication'))
			);

			/* DB登録エラー */
			if (!$insert_id = $timeline->post_timeline($param_array)) {
				LOGS_ERR("タイムライン投稿に失敗しました。");
			}

			//画像保存用にタイムラインIDを保持(2017.2.13)
			$tl_id = $insert_id;
		}

		//添付画像がある場合は画像をユーザーディレクトリに移動
		/* ↓
		 * タイムラインは増加傾向にあるので/ユーザーID/タイムラインID/ディレクトリに保存する方式に変更。
		 * 過去の投稿については変換処理が必要。
		 * 画像の削除は追々削除ツール（AJAX）を作成予定。
		 * タイムラインの画像リストはディレクトリ内を参照する。（メソッドの作成が必要）
		 * 
		 */
		if (!StaticFunction::is_empty(SESSION::read($this->sGroup . '.tmp_file_name'))) {

			$img = new Image();

			//セッション配列を配列変数に代入
			$image_array = SESSION::read($this->sGroup . '.tmp_file_name');
			$tmp_date_array = SESSION::read($this->sGroup . '.tmp_file_date');
			
			//画像個数分、ループ処理
			$sort_num = 0;
			foreach ($image_array AS $img_key => $img_name_value) {

				$ret = $img->set_timeline_public(
					$tmp_date_array[$img_key]
					, $img_name_value
					, $this->public_user_data['system_id']
					, $tl_id /* タイムラインID */
					, $sort_num
				);

				//失敗時
				if (!$ret) {
					//失敗時はアラートメール送信
				}
				$sort_num++;
			}
		}

		//正常終了時はセッションを削除
		SESSION::delete($this->sGroup);

		//完了画面はないのでmypageへリダイレクト
		$this->redirect("/mypage/sns.html");
	}

	/*	 * **********************************
	 * NAME:checkSessionParameter
	 * DESC:
	 *  レスポンス専用ののセッション情報バリデーション
	 * NOTICE:
	 * CREATE: 2016.10.20 aoyama
	 * UPDATE: 2016.12.12 aoyama	
	 * 		公開範囲設定対応
	 * *********************************** */
	private function checkSessionParameter() {

		if (!SESSION::read($this->sGroup . '.file')) {
			ALERT::set_session('添付できるファイルは画像のみです。','file');
		}

		if (!InputVali::is_array_key(SESSION::read($this->sGroup . '.publication'), CONF::read('TL_PUBLICATION'))) {
            ALERT::set_session('公開範囲を選択してください。','publication');
		}

		if (!InputVali::is_comment_thread(SESSION::read($this->sGroup . '.comment'))) {
            ALERT::set_session('コメントは1000文字以内で入力してください。','comment');
		}
	}

	/*	 * **********************************
	 * NAME:formResponseReturn
	 * DESC:
	 *  セッション情報をレスポンス用フォームに渡すためにセットする機能
	 * NOTICE:
	 * CREATE: 2016.10.20 aoyama
	 * *********************************** */
	private function formReturn() {

		$file_url = "";

		// セッションの情報をセットしてviewに渡す
		if (!StaticFunction::is_empty(SESSION::read($this->sGroup))) {
			$this->set("comment", SESSION::read($this->sGroup . '.comment'));
			$this->set("comment_view", StaticFunction::decode_view_text(nl2br(SESSION::read($this->sGroup . '.comment'))));
			$this->set("publication", SESSION::read($this->sGroup . '.publication'));
			$this->set("publication_view", CONF::read('TL_PUBLICATION.' . SESSION::read($this->sGroup . '.publication')));
			$this->set("tmp_file_name", SESSION::read($this->sGroup . '.tmp_file_name'));
			$this->set("tmp_file_date", SESSION::read($this->sGroup . '.tmp_file_date'));

			$image = new Image();
			$timeline = new TimelineModel();

			/* 以下2017.2.13 の複数画像対応のためコメントアウト */
			
			//編集モードの場合は既存の情報を取得
//			if (!StaticFunction::is_empty(SESSION::read($this->sGroup . ".tl_id"))) {
//				$timeline_detail = $timeline->get_detail_by_id(SESSION::read($this->sGroup . ".tl_id"), $this->public_user_data['user_id']);
//				//詳細が取得できたので画像のパスを取得
//				if (!StaticFunction::is_empty($timeline_detail)) {
//					$file_url = $image->get_timeline_url($this->public_user_data['system_id'], $timeline_detail[0]['image_file']);
//				}
//			}


			/* プレビューでの画像ファイル */
			//まずはセッションにtmp画像が入っている場合は上書き
			//確認画面が無いので停止
//			if (!StaticFunction::is_empty(SESSION::read($this->sGroup . '.tmp_file_name'))) {
//				$file_url = $image->get_tmp_file_url(SESSION::read($this->sGroup . '.tmp_file_date'), SESSION::read($this->sGroup . '.tmp_file_name'));
//			}

//			$this->set("file_link", $file_url);
			/* 以下2017.2.13 の複数画像対応のためコメントアウト ここまで */
		}
	}

	/*	 * **********************************
	 * NAME  : delete
	 * INPUT : NONE
	 * OUTPUT: NONE
	 * DESC  :
	 * 		タイムラインを削除するメソッド
	 * 		確認画面はなくダイレクトに削除処理を実行
	 * NOTICE:
	 * CREATE: 2016.11.10 aoyama
	 * *********************************** */
	public function delete() {

		/* ハッシュチェック */
		if (!StaticFunction::check_token(REQUEST::get_data('token'))) {
			$this->redirect("/mypage/");
		}

		//tl_id（タイムラインID）の有無を確認
		if (StaticFunction::is_empty(REQUEST::get_data('tl_id'))) {
			$this->redirect("/mypage/");
		}

		//コミュニティの詳細を取得する
		$timeline = new TimelineModel();
		$timeline_detail = $timeline->get_detail_by_id(REQUEST::get_data('tl_id'), $this->public_user_data['user_id']);
		if (StaticFunction::is_empty($timeline_detail)) {
			$this->redirect("/mypage/");
		}

		$like = new LikeModel();
		//いいねを削除
		$like->delete_response_like(REQUEST::get_data('tl_id'));

		//画像があれば削除処理
		if (!StaticFunction::is_empty($timeline_detail[0]['image_file'])) {
			$img = new Image();
			if (!$img->delete(DIR_PUBLIC_IMG . DS . "user" . DS . $this->public_user_data['system_id'] . DS, $timeline_detail[0]['image_file'])) {
				LOGS_ERR("タイムラインの画像削除に失敗:" . $timeline_detail[0]['image_file']);
			}
		}

		//DBのactiveをOFFにする
		$param_list = array(
			"active" => DB_ACTIVE_OFF,
			"image_file" => DbCast::string("")
		);
		$condition = array(
			"WHERE" => array(
				"timeline_id" => DbCast::id(REQUEST::get_data('tl_id'))
			)
		);
		$timeline->delete($param_list, $condition);

		//問題なければ確認画面へ
		$this->redirect("/mypage/sns.html");
	}

	/*	 * **********************************
	 * NAME  : avatar_complete
	 * INPUT : NONE
	 * OUTPUT: NONE
	 * DESC  :
	 *  アバターを変更するメソッド
	 * NOTICE:
	 * CREATE: 2016.10.27 aoyama
	 * *********************************** */
	public function avatar_complete() {

		/* ハッシュチェック */
		if (REQUEST::post_data('token') != SESSION::read('EXPIRES.ORIGINAL_TOKEN')) {
			$this->set('alert_avatar', 'このページからは更新できません。');
			return;
		}

		//アバター登録がある場合
		if ($_FILES['avatar']['error'] == UPLOAD_ERR_OK) {

			$thumb = new Image();

			//一時画像ファイル名を生成
			$avatar_tmp_hash = Encrypt::member_regist_token($_SERVER['REMOTE_ADDR'], time());

			//ロード
			if (!$ret = $thumb->load($_FILES['avatar']['tmp_name'])) {
				SESSION::write($this->sGroup . '.file', false);
			} else {

				//拡張子取得
				$thumb_ext = $thumb->get_image_type();

				//リサイズ
				$thumb->resize_avatar(CONF::read("AVATAR.WIDTH"));

				//ファイル名
				$date_dir = DbDateTime::fairing_digit_8(DbDateTime::get_cur_datetime());
				$tmp_file_name = $avatar_tmp_hash . '.jpg';

				//tmp保存先システムディレクトリ[/public/images/tmp/日付]
				$avatar_tmp_dir = DIR_SYSTEM_IMG_TMP . DS . $date_dir . DS;

				//tmpディレクトリに保存
				$ret = $thumb->save_jpeg($avatar_tmp_dir, $tmp_file_name);

				SESSION::write($this->sGroup . '.tmp_avatar', $tmp_file_name);
				SESSION::write($this->sGroup . '.tmp_avatar_date', $date_dir);

				//5)アバター画像がある場合は画像をユーザーディレクトリに移動
				if (!StaticFunction::is_empty(SESSION::read($this->sGroup . '.tmp_avatar'))) {

					$img = new Image();
					$ret = $img->set_user_avatar_public(SESSION::read($this->sGroup . '.tmp_avatar_date'), SESSION::read($this->sGroup . '.tmp_avatar'), $this->public_user_data['system_id']);

					if (!$ret) {
						return;
					}
				}
			}

			//正常終了時はセッションを削除
			SESSION::delete($this->sGroup);
		}
		$this->redirect("/mypage/sns.html");
	}

	/*	 * **********************************
	 * NAME  : response
	 * INPUT : 
	 * OUTPUT: 
	 * DESC  : 
	 * 		タイムライン投稿に対するレスポンスを登録する。
	 * NOTICE:
	 * CREATE: 2016.12.13 aoyama
	 * UPDATE: 2017.2.8 aoyama
	 * 		タイムラインの表示順をレスポンスの登録時にするため、
	 * 		登録時刻を親タイムラインのupdate_timeを更新。
	 * *********************************** */
	public function response() {

		$timeline = new TimelineModel();

		//コメントが未入力の時もリダイレクト（JSチェック推奨）
		if (StaticFunction::is_empty(REQUEST::post_data('response_body'))) {
			$this->redirect("/mypage/sns.html");
		}

		/* ハッシュチェック */
		if (!StaticFunction::check_token(REQUEST::post_data('token'))) {
			$this->redirect("/mypage/sns.html");
		}

		$pageing = (!StaticFunction::is_empty(REQUEST::post_data('pd'))) ? "?pd=" . REQUEST::post_data('pd') . "&pp=" . REQUEST::post_data('pp') : "";

		//入力チェック（JSバリデーションを期待）
		$error_array = $this->checkResponseSessionParameter();
		if (!StaticFunction::is_empty($error_array)) {
			LOGS_ERR($error_array);
			$this->redirect("/mypage/sns.html" . $pageing);
		}

		$datetime = DbDateTime::get_cur_datetime();
		// スレッド登録処理
		// 配列にPOSTデータを格納
		$param_array = array(
			'update_time' => DbCast::datetime($datetime),
			'create_time' => DbCast::datetime($datetime),
			"active" => DB_ACTIVE_ON,
			'user_id' => DbCast::id($this->public_user_data['user_id']),
			"timeline_id" => DbCast::id(REQUEST::post_data('timeline_id')),
			"response_text" => DbCast::string(REQUEST::post_data('response_body'))
		);

		// レスポンス時に親タイムラインのupdate_timeを更新
		$param_list = array(
			'update_time' => DbCast::datetime($datetime)
		);
		$condition = array(
			"WHERE" => array(
				"timeline_id" => DbCast::id(REQUEST::post_data('timeline_id'))
			)
		);
		$timeline->update($param_list, $condition);

		if ($timeline->post_timeline_response($param_array)) {
			//ページングが発生している場合はページング情報をセット
			$this->redirect("/mypage/sns.html" . $pageing);
		}

		//何らかの原因で失敗するとここへ。
		$this->set('error_array', array(array("message" => "タイムラインへのコメントに失敗しました")));
	}

	/*	 * **********************************
	 * NAME:checkResponseSessionParameter
	 * DESC:
	 *  レスポンス専用ののセッション情報バリデーション
	 * NOTICE:
	 * CREATE: 2016.10.20 aoyama
	 * UPDATE: 2016.12.12 aoyama	
	 * 		公開範囲設定対応
	 * *********************************** */
	private function checkResponseSessionParameter() {

		$error_array = array();

		if (!InputVali::is_comment_thread(REQUEST::post_data('response_body'))) {
			$error_array[] = array('target' => 'comment', 'message' => '返信は1000文字以内で入力してください。');
		}

		return $error_array;
	}

	/*	 * **********************************
	 * NAME  : response_delete
	 * INPUT : NONE
	 * OUTPUT: NONE
	 * DESC  :
	 * 		コメントを削除するメソッド
	 * 		確認画面はなくダイレクトに削除処理を実行
	 * NOTICE:
	 * CREATE: 2016.12.13 aoyama
	 * *********************************** */
	public function response_delete() {

		$tr_id = REQUEST::get_data('tr_id');

		/* ハッシュチェック */
		if (!StaticFunction::check_token(REQUEST::get_data('token'))) {
			$this->redirect("/mypage/sns.html");
		}

		//rr_id（コメントのレスポンスID）の有無を確認
		if (StaticFunction::is_empty($tr_id)) {
			$this->redirect("/mypage/sns.html");
		}

		//レビューコメントの情報を取得（レスポンスユーザーの情報を取得するため）
		$timeline = new TimelineModel();
		$response = $timeline->is_timeline_response($tr_id);

		//対象がなければ終了
		if (StaticFunction::is_empty($response)) {
			$this->redirect("/mypage/sns.html");
		}

		//自分のコメントで無ければ終了
		if ($response[0]['user_id'] != $this->public_user_data['user_id']) {
			$this->redirect("/mypage/sns.html");
		}

		//DBのactiveをOFFにする
		$datetime = DbDateTime::get_cur_datetime();
		$param_list = array(
			"active" => DB_ACTIVE_OFF,
			'update_time' => DbCast::datetime($datetime)
		);
		$condition = array(
			"WHERE" => array(
				"timeline_response_id" => DbCast::id($tr_id)
			)
		);

		$timeline->delete_timeline_response($param_list, $condition);

		//ページングが発生している場合はページング情報をセット
		$pageing = (!StaticFunction::is_empty(REQUEST::get_data('pd'))) ? "?pd=" . REQUEST::get_data('pd') . "&pp=" . REQUEST::get_data('pp') : "";

		//問題なければ確認画面へ
		$this->redirect("/mypage/sns.html" . $pageing);
	}

}

?>
