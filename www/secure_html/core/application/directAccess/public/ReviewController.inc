<?php

/* * **********************************
 * NAME:ReviewController
 * DESC:
 * 		レビューページのコントローラー
 * NOTICE:
 * CREATE: 2016.10.31 aoyama
 * *********************************** */
class ReviewController extends PublicOpenControllerFrame {

	private $sGroup;
	private $magArray;

	/* Constructor */
	public function __construct() {
		parent::__construct();
		$this->sGroup = 'review';

		//セッションからユーザ情報を取得
		$this->public_user_data = SESSION::read(CONF::read('LOGIN_CATEGORY.PUBLIC'));

        $login = new Login();
        //対象となるターゲットユーザモデルを指定
        $login->set_target_model(CONF::read('LOGIN_CATEGORY.PUBLIC'));

        //ログイン中かセッションにある値で認証
        if ($login->is_login() && !$this->is_sns_entry()) {
            //初回ログインページへリダイレクト
            $this->redirect(CONF::read('URL_PUBLIC_ROOT') . 'mypage/login_first');
		}
		
		$this->set("page_group", "review");
	}

	/*	 * **********************************
	 * NAME  : delete
	 * INPUT : NONE
	 * OUTPUT: NONE
	 * DESC  :
	 * 		レビューを削除するメソッド
	 * NOTICE:
	 * CREATE: 2016.11.14 aoyama
	 * *********************************** */
	public function delete() {

		/* ハッシュチェック */
		if (!StaticFunction::check_token(REQUEST::get_data('token'))) {
			//トークンチェックエラーなのでTOPへリダイレクト
			$this->redirect("/review/");
		}

		//rid（コメントID）の有無を確認
		if (StaticFunction::is_empty(REQUEST::get_data('review_id'))) {
			$this->redirect("/review/");
		}

		//コメントの情報を取得
		$review = new ReviewModel();
		$review_detail = $review->get_review(REQUEST::get_data('review_id'));

		//対象がなければ終了
		if (StaticFunction::is_empty($review_detail)) {
			$this->redirect("/review/");
		}

		$like = new LikeModel();
		//いいねを削除
		$like->delete_review_like(REQUEST::get_data('review_id'));

		//画像があれば削除処理
		if (!StaticFunction::is_empty($review_detail[0]['image_file'])) {
			$img = new Image();
			if (!$img->delete(DIR_PUBLIC_IMG . DS . "review" . DS . $review_detail[0]['review_id'] . DS, $review_detail[0]['image_file'])) {
				echo '$img->delete error';
				exit;
			}
		}

		//DBのactiveをOFFにする
		$param_list = array(
			"active" => DB_ACTIVE_OFF,
			"image_file" => DbCast::string("")
		);
		$condition = array(
			"WHERE" => array(
				"review_id" => DbCast::id(REQUEST::get_data('review_id'))
			)
		);

		$review->delete($param_list, $condition);

		//問題なければ確認画面へ
		$this->redirect("/review/");
	}

	/*	 * **********************************
	 * NAME  : index
	 * INPUT : 
	 * OUTPUT: 
	 * DESC  : 
	 * 		登録フォーム
	 * 		セッションにセットするのはここだけ。
	 * 		同時にバリデーションチェックも実施
	 * NOTICE:
	 * CREATE: 2016.10.16 aoyama
	 * *********************************** */
	public function index($page_group = "index") {

		if ($page_group != "index") {
			$this->set("page_group", $page_group);
		}

		//* ログイン
		$login = new Login();
		$review = new ReviewModel();
		$image = new Image();

		//自分のアバターをセット
		$this->set("own_avatar_url", $image->get_avatar_url(@$this->public_user_data['system_id']));
		$this->set("own_nickname", $image->get_avatar_url(@$this->public_user_data['nickname']));

		//ページ指定文字のサニタイズ
		$pd = (InputVali::is_num(REQUEST::get_data('pd'))) ? REQUEST::get_data('pd') : 0;
		$pp = (InputVali::is_num(REQUEST::get_data('pp')) AND REQUEST::get_data('pp') <= CONF::read('PAGING.DEFAULT_NUM_MAX')) ? REQUEST::get_data('pp') : CONF::read('PAGING.DEFAULT_NUM_PUBLIC');

		//レビューを取得
		$reviewViewArray = array();
//		foreach ($review->get_review($pd, $pp) AS $reviewValue) {
//
//			$reviewViewArray[] = array(
//				"review_id" => $reviewValue['review_id'],
//				"system_id" => $reviewValue['system_id'],
//				"nickname" => $reviewValue['nickname'],
//				"comment" => $reviewValue['comment'],
//				"file_url" => $image->get_review_url($reviewValue['review_id'], $reviewValue['image_file']),
//				"avatar" => $image->get_avatar_url($reviewValue['system_id']),
//				"update_time" => DbDateTime::get_date_type_dot($reviewValue['update_time'])
//			);
//		}
		$review_id = "";
		foreach ($review->get_review_package($pd, $pp) AS $reviewValue) {

			// 自分のレビューの時はレビューの編集ボタンリンクを設定。これをviewの表示判定にも使用。
			$edit_link = '';
			if (!empty($this->public_user_data['user_id']) && $reviewValue['review_user_id'] === $this->public_user_data['user_id']) {
    			$edit_link = "/review/edit.html?rid=" . $reviewValue['review_id'];
			}

			//レビューIDが切り替わったタイミングでコメントの対象を変更
			if ($review_id != $reviewValue['review_id']) {
				$review_id = $reviewValue['review_id'];
				$reviewViewArray[$review_id] = array(
					"review_id" => $reviewValue['review_id'],
					"nickname" => (!StaticFunction::is_empty($reviewValue['review_old_nickname'])) ? $reviewValue['review_old_nickname'] : $reviewValue['review_nickname'],
					"avatar" => $image->get_avatar_url($reviewValue['review_system_id']),
					"user_link" => (!StaticFunction::is_empty($reviewValue['review_old_nickname'])) ? "" : "/profile/?uid=" . $reviewValue['review_system_id'],
					"system_id" => $reviewValue['review_system_id'],
					"review_time" => DbDateTime::get_date_type_dot($reviewValue['review_time']),
					"file_url" => $image->get_review_url($reviewValue['review_id'], $reviewValue['review_image_file']),
					"comment" => $reviewValue['review_comment'],
					"comment_view" => StaticFunction::decode_view_text(nl2br($reviewValue['review_comment'])),
					"like_count" => $reviewValue['review_like_count'],
					"response" => array(),
					"edit_link" => $edit_link,
					"quarity" => $reviewValue['evaluation_1'],
					"quarity_view" => StaticFunction::create_star($reviewValue['evaluation_1']),
					"utility" => $reviewValue['evaluation_2'],
					"utility_view" => StaticFunction::create_star($reviewValue['evaluation_2']),
					"estimate_total" => ((INT) $reviewValue['evaluation_1'] + (INT) $reviewValue['evaluation_2']) / 2
				);
			}

			if (!StaticFunction::is_empty($reviewValue['review_response_id'])) {

				$edit_response_link = "";
				// 自分のレビューコメントの時はレビューの編集ボタンリンクを設定。これをviewの表示判定にも使用。
				$edit_response_link = '';
				if (!empty($this->public_user_data['user_id']) && $reviewValue['response_user_id'] === $this->public_user_data['user_id']) {
				    $edit_response_link = "/review/response_delete.html?rr_id=" . $reviewValue['review_response_id'];
				    $edit_response_link .= "&token=" . SESSION::read('EXPIRES.ORIGINAL_TOKEN');
				    $edit_response_link .= "&pd=" . REQUEST::get_data('pd');
				    $edit_response_link .= "&pp=" . REQUEST::get_data('pp');
				}

				$reviewViewArray[$review_id]['response'][] = array(
					"review_response_id" => $reviewValue['review_response_id'],
					"system_id" => $reviewValue['response_system_id'],
					"nickname" => (!StaticFunction::is_empty($reviewValue['response_old_nickname'])) ? $reviewValue['response_old_nickname'] : $reviewValue['response_nickname'],
					"user_link" => (!StaticFunction::is_empty($reviewValue['response_old_nickname'])) ? "" : "/profile/?uid=" . $reviewValue['response_system_id'],
					"response_text" => $reviewValue['response_text'],
					"response_text_view" => StaticFunction::decode_view_text(nl2br($reviewValue['response_text'])),
					"avatar" => $image->get_avatar_url($reviewValue['response_system_id']),
					"update_time" => DbDateTime::get_date_type_dot($reviewValue['response_time']),
					"edit_link" => $edit_response_link
				);
			}
		}
		$this->set("review_array", $reviewViewArray);

		//いいねしているコメントの配列を取得
		$like = new LikeModel();
		
		$like_for_js = array();
		if (!empty($this->public_user_data['user_id'])) {
		    $like_for_js = $like->get_review_like_own($this->public_user_data['user_id'], $reviewViewArray);
		}

		$in_array = array();
		foreach ($like_for_js AS $val) {
			$in_array[] = "'review:" . $val['target_id'] . "'";
		}
		$comment_like_array = implode(",", $in_array);

		$this->set("review_like_array", $comment_like_array);

		//ログイン常態をviewに渡す
		$this->set("is_login", $login->is_login());

		//ページング用レビューカウント
		$review_count = $review->get_review_count();
		$page = new PAGING();
		$this->set("pageng_html", $page->make_paging($review_count));


		// POSTデータがある場合、尚且つログインしている場合はセッションに登録する。
		if (!StaticFunction::is_empty(REQUEST::post_data()) && $login->is_login()) {

			SESSION::write($this->sGroup . '.comment', REQUEST::post_data('comment'));
			SESSION::write($this->sGroup . '.quarity', REQUEST::post_data('quarity'));
			SESSION::write($this->sGroup . '.utility', REQUEST::post_data('utility'));
			SESSION::write($this->sGroup . '.file',true);
			if (!StaticFunction::is_empty(REQUEST::post_data('review_id'))) {
				SESSION::write($this->sGroup . '.review_id', REQUEST::post_data('review_id'));
				$this->set("review_id", REQUEST::post_data('review_id'));
			}

			if ($_FILES['review_file']['error'] == UPLOAD_ERR_OK) {

				$file = new Image();

				//一時ファイル名を生成
				$file_tmp_hash = Encrypt::member_regist_token($this->public_user_data['user_id'], time());

				//ロード
				if (!$ret = $file->load($_FILES['review_file']['tmp_name'])) {
					SESSION::write($this->sGroup . '.file',false);
				}
				else {

					//拡張子取得
					$thumb_ext = $file->get_image_type();

					//リサイズ
					//$thumb->resize_avatar(CONF::read("AVATAR.WIDTH"));
					//tmp保存先システムディレクトリ[/public/images/tmp/[yyyymm]]
					$date_dir = DbDateTime::fairing_digit_8(DbDateTime::get_cur_datetime());
					$tmp_dir = DIR_SYSTEM_IMG_TMP . DS . $date_dir . DS;

					//tmpファイル名
					$tmp_file_name = $file_tmp_hash . '.' . $thumb_ext;

					//tmpディレクトリに保存
					//$ret = $file->save_jpeg($avatar_tmp_dir, $tmp_file_name);
					//tmpフォルダに移動
					$file->move_file("", $_FILES['review_file']['tmp_name'], $tmp_dir, $tmp_file_name);

					SESSION::write($this->sGroup . '.tmp_file_name', $tmp_file_name);
					SESSION::write($this->sGroup . '.tmp_file_date', $date_dir);
				}
			}

			// バリデーション
			$error_array = $this->checkSessionParameter();

			if (!StaticFunction::is_empty($error_array)) {
				$this->set('error_array', $error_array);
				$this->formReturn();
				return;
			}

			//問題なければ確認画面へ
			$this->redirect("./confirm.html");
		}

		$this->formReturn();
	}

	/*	 * **********************************
	 * NAME  : confirm
	 * INPUT : 
	 * OUTPUT: 
	 * DESC  : 
	 * 		入力確認画面用
	 * 		セッションがあればとりあえず表示する
	 * 		ここではバリデーション無し
	 * NOTICE:
	 * CREATE: 2016.10.16 aoyama
	 * *********************************** */
	public function confirm() {



		$this->formReturn();
	}

	/*	 * **********************************
	 * NAME  : complete
	 * INPUT : 
	 * OUTPUT: 
	 * DESC  : 
	 *  入力完了画面用
	 *  APIで情報を送信
	 * NOTICE:
	 * CREATE: 2016.10.31 aoyama
	 * *********************************** */
	public function complete() {

		if (StaticFunction::is_empty(SESSION::read($this->sGroup))) {
			$this->redirect("/review/");
		}

		/*
		 * バリデーション:エラーのときはindex.htmlに飛ばす
		 * indexのcheckSessionParameterとエラー情報の渡し方が異なる理由として
		 * ここでバリデーションに引っかかるということは予期しないアクセスなので
		 * そこまで親切にしなくてもいいかなと。(aoyama)
		 */
		$error_array = $this->checkSessionParameter();
		if (!StaticFunction::is_empty($error_array)) {
			$this->redirect("/review/");
		}

		$review = new ReviewModel();

		$datetime = DbDateTime::get_cur_datetime();

		//編集モード
		if (!StaticFunction::is_empty(SESSION::read($this->sGroup . '.review_id'))) {

			$target_review_id = SESSION::read($this->sGroup . '.review_id');

			// レスポンス更新処理
			// 配列にPOSTデータを格納
			$param_list = array(
				'update_time' => DbCast::datetime($datetime),
				"comment" => DbCast::string(SESSION::read($this->sGroup . '.comment')),
				"evaluation_1" => DbCast::integer(SESSION::read($this->sGroup . '.quarity')),
				"evaluation_2" => DbCast::integer(SESSION::read($this->sGroup . '.utility'))
			);

			//画像がある場合はファイル名も更新
			if (!StaticFunction::is_empty(SESSION::read($this->sGroup . '.tmp_file_name'))) {
				$param_list += array(
					"image_file" => DbCast::string(SESSION::read($this->sGroup . '.tmp_file_name'))
				);
			}

			$condition = array(
				"WHERE" => array(
					"review_id" => DbCast::id(SESSION::read($this->sGroup . '.review_id'))
				)
			);
			/* DB登録エラー */
			if (!$insert_id = $review->edit_review($param_list, $condition)) {
				LOGS_ERR("レビュー編集に失敗しました。");
				$error_array[] = array("message" => "コメント編集に失敗しました。");
				$this->set('error_array', $error_array);
				return;
			}
		}

		//新規登録モード
		else {
			$datetime = DbDateTime::get_cur_datetime();
			// スレッド登録処理
			// 配列にPOSTデータを格納
			$param_array = array(
				'update_time' => DbCast::datetime($datetime),
				'create_time' => DbCast::datetime($datetime),
				"active" => DB_ACTIVE_ON,
				'user_id' => DbCast::id($this->public_user_data['user_id']),
				"comment" => DbCast::string(SESSION::read($this->sGroup . '.comment')),
				"evaluation_1" => DbCast::integer(SESSION::read($this->sGroup . '.quarity')),
				"evaluation_2" => DbCast::integer(SESSION::read($this->sGroup . '.utility')),
				"image_file" => DbCast::string(SESSION::read($this->sGroup . '.tmp_file_name'))
			);

			/* DB登録エラー */
			if (!$target_review_id = $review->post_review($param_array)) {
				$error_array[] = array("message" => "レビュー投稿に失敗しました。");
				$this->set('error_array', $error_array);
				return;
			}
		}

		//添付画像がある場合は画像をレビューディレクトリに移動
		if (!StaticFunction::is_empty(SESSION::read($this->sGroup . '.tmp_file_name'))) {

			$img = new Image();
			$ret = $img->set_review_file(SESSION::read($this->sGroup . '.tmp_file_date'), SESSION::read($this->sGroup . '.tmp_file_name'), $target_review_id);

			//失敗時
			if (!$ret) {
				//失敗時はアラートメール送信
			}
		}

		//正常終了時はセッションを削除
		SESSION::delete($this->sGroup);

		//ページングが発生している場合はページング情報をセット
		$pageing = (!StaticFunction::is_empty(REQUEST::get_data('pd'))) ? "?pd=" . REQUEST::get_data('pd') . "&pp=" . REQUEST::get_data('pp') : "";

		$this->redirect("/review/" . $pageing);
	}

	/*	 * **********************************
	 * NAME:checkSessionParameter
	 * DESC:
	 * 		レビュー専用のセッション情報バリデーション
	 * NOTICE:
	 * CREATE: 2016.10.31 aoyama
	 * *********************************** */
	private function checkSessionParameter() {

		$error_array = array();

		if (!SESSION::read($this->sGroup . '.file')) {
			$error_array[] = array('target' => 'file', 'message' => '添付できるファイルは画像のみです。');
		}
		
		
		if (!InputVali::is_review_message(SESSION::read($this->sGroup . '.comment'))) {
			$error_array[] = array('target' => 'comment', 'message' => 'レビューコメントは1000文字以内で入力してください。');
		}

		//品質の選択チェック
		if (!InputVali::is_array_key(SESSION::read($this->sGroup . '.quarity'), CONF::read('ESTIMATE_STAR'))) {
			$error_array[] = array('target' => 'quarity', 'message' => '品質を選択してください。');
		}

		//利便性の選択チェック
		if (!InputVali::is_array_key(SESSION::read($this->sGroup . '.utility'), CONF::read('ESTIMATE_STAR'))) {
			$error_array[] = array('target' => 'utility', 'message' => '利便性を選択してください。');
		}

		return $error_array;
	}

	/*	 * **********************************
	 * NAME:formReturn
	 * DESC:
	 * 		セッション情報をフォームに渡すためにセットする機能
	 * 		tmp_file系は画像をセットするため
	 * NOTICE:
	 * CREATE: 2016.10.31 aoyama
	 * *********************************** */
	private function formReturn() {

		$file_url = "";

		// セッションの情報をセットしてviewに渡す
		if (!StaticFunction::is_empty(SESSION::read($this->sGroup))) {
			$this->set("comment_view", StaticFunction::decode_view_text(nl2br(SESSION::read($this->sGroup . '.comment'))));
			$this->set("comment", SESSION::read($this->sGroup . '.comment'));
			$this->set("quarity", SESSION::read($this->sGroup . '.quarity'));
			$this->set("quarity_view", StaticFunction::create_star(SESSION::read($this->sGroup . '.quarity')));
			$this->set("utility", SESSION::read($this->sGroup . '.utility'));
			$this->set("utility_view", StaticFunction::create_star(SESSION::read($this->sGroup . '.utility')));
			$this->set("tmp_file_name", SESSION::read($this->sGroup . '.tmp_file_name'));
			$this->set("tmp_file_date", SESSION::read($this->sGroup . '.tmp_file_date'));

			$image = new Image();
			$review = new ReviewModel();

			//編集モードの場合は既存の情報を取得
			if (!StaticFunction::is_empty(SESSION::read($this->sGroup . ".review_id"))) {
				$review_detail = $review->get_review(SESSION::read($this->sGroup . ".review_id"));
				//詳細が取得できたので画像のパスを取得
				if (!StaticFunction::is_empty($review_detail)) {
					$file_url = $image->get_review_url(SESSION::read($this->sGroup . ".review_id"), $review_detail[0]['image_file']);
				}
			}


			/* プレビューでの画像ファイル */
			//まずはセッションにtmp画像が入っている場合は上書き
			if (!StaticFunction::is_empty(SESSION::read($this->sGroup . '.tmp_file_name'))) {
				$file_url = $image->get_tmp_file_url(SESSION::read($this->sGroup . '.tmp_file_date'), SESSION::read($this->sGroup . '.tmp_file_name'));
			}

			$this->set("file_link", $file_url);
		}
	}

	/*	 * **********************************
	 * NAME  : response
	 * INPUT : 
	 * OUTPUT: 
	 * DESC  : 
	 * 		レビューに対するレスポンスを登録する。
	 * NOTICE:
	 * CREATE: 2016.10.31 aoyama
	 * *********************************** */
	public function response() {

		//* ログイン
		$login = new Login();
		$review = new ReviewModel();

		//ログインしていない場合はエラーメッセージ
		if (!$login->is_login()) {
			$this->redirect("/review/");
		}

		//コメントがみにゅ力の時もリダイレクト（JSチェック）
		if (StaticFunction::is_empty(REQUEST::post_data('response_body'))) {
			$this->redirect("/review/");
		}

		/* ハッシュチェック */
		if (!StaticFunction::check_token(REQUEST::post_data('token'))) {
			$this->redirect("/review/");
		}

		//入力チェック（JSバリデーションを期待）
		$error_array = $this->checkResponseSessionParameter();
		if (!StaticFunction::is_empty($error_array)) {
			LOGS_ERR($error_array);
			$this->redirect("/review/");
		}


		$datetime = DbDateTime::get_cur_datetime();
		// スレッド登録処理
		// 配列にPOSTデータを格納
		$param_array = array(
			'update_time' => DbCast::datetime($datetime),
			'create_time' => DbCast::datetime($datetime),
			"active" => DB_ACTIVE_ON,
			'user_id' => DbCast::id($this->public_user_data['user_id']),
			"review_id" => DbCast::id(REQUEST::post_data('review_id')),
			"response_text" => DbCast::string(REQUEST::post_data('response_body'))
		);
		if ($review->post_review_response($param_array)) {
			//ページングが発生している場合はページング情報をセット
			$pageing = (!StaticFunction::is_empty(REQUEST::post_data('pd'))) ? "?pd=" . REQUEST::post_data('pd') . "&pp=" . REQUEST::post_data('pp') : "";
			$this->redirect("/review/" . $pageing);
		}

		//何らかの原因で失敗するとここへ。
		$this->set('error_array', array(array("message" => "レビューへのコメントに失敗しました")));
	}

	/*	 * **********************************
	 * NAME:checkResponseSessionParameter
	 * DESC:
	 * 		レビュー専用のセッション情報バリデーション
	 * NOTICE:
	 * CREATE: 2016.10.31 aoyama
	 * *********************************** */
	private function checkResponseSessionParameter() {

		$error_array = array();

		if (!InputVali::is_review_message(REQUEST::post_data('response_body'))) {
			$error_array[] = array('target' => 'response_body', 'message' => 'レビュー返信は1000文字以内で入力してください。');
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
	 * CREATE: 2016.11.20 aoyama
	 * *********************************** */
	public function response_delete() {

		$rr_id = REQUEST::get_data('rr_id');

		/* ハッシュチェック */
		if (!StaticFunction::check_token(REQUEST::get_data('token'))) {
			$this->redirect("/review/");
		}

		//rr_id（コメントのレスポンスID）の有無を確認
		if (StaticFunction::is_empty($rr_id)) {
			$this->redirect("/review/");
		}

		//レビューコメントの情報を取得（レスポンスユーザーの情報を取得するため）
		$review = new ReviewModel();
		$response = $review->get_review_response($rr_id);

		//対象がなければ終了
		if (StaticFunction::is_empty($response)) {
			$this->redirect("/review/");
		}

		//自分のコメントで無ければ終了
		if ($response[0]['user_id'] != $this->public_user_data['user_id']) {
			$this->redirect("/review/");
		}

		//DBのactiveをOFFにする
		$datetime = DbDateTime::get_cur_datetime();
		$param_list = array(
			"active" => DB_ACTIVE_OFF,
			'update_time' => DbCast::datetime($datetime)
		);
		$condition = array(
			"WHERE" => array(
				"review_response_id" => DbCast::id($rr_id)
			)
		);

		$review->delete_review_response($param_list, $condition);

		//ページングが発生している場合はページング情報をセット
		$pageing = (!StaticFunction::is_empty(REQUEST::get_data('pd'))) ? "?pd=" . REQUEST::get_data('pd') . "&pp=" . REQUEST::get_data('pp') : "";

		//問題なければ確認画面へ
		$this->redirect("/review/" . $pageing);
	}

    /**
     * @return bool
     */
    private function is_sns_entry() {
        if (StaticFunction::is_empty(SESSION::read(CONF::read('LOGIN_CATEGORY.PUBLIC') . ".user_id"))) {
            return false;
        } else {
            return true;
        }
    }
}

?>
