<?php

/* * **********************************
 * NAME:MypageController
 * DESC:
 *  マイページ用のコントローラ(クローズエリア)
 * 
 *  コントローラの継承
 *  MypageController
 *  ↓
 *  MypageCloseCommonControllerFrame
 *  ↓
 *  MypageBaseCommonControllerFrame
 *  ↓
 *  ControllerCore
 *  となる
 * 
 * NOTICE:
 * CREATE: 2016.10.19 aoyama
 * UPDATE: 2016.11.1  aoyama
 * 		フレンド一覧とコミュニティ一覧ページを作成
 * 		mypageを流用
 * *********************************** */
class ProfileController extends MypageCloseCommonControllerFrame {

	private $sGroup;
	private $public_user_data;

	/* Constructor */
	public function __construct() {

		parent::__construct();
		$this->sGroup = "profile";
		//セッションからユーザ情報を取得
		$this->public_user_data = SESSION::read(CONF::read('LOGIN_CATEGORY.PUBLIC'));

		//プロフィールリンク用に
		$this->set("user_link", "/profile/?uid=" . $this->public_user_data['system_id']);
		
		//ファッション系統の配列を取得してvuewに渡す
		$fashionMaster = new FashionTypeMasterModel();
		$this->fashionMasterArray = $fashionMaster->get_basic_data();
		$this->set("fashionTypeArray", $this->fashionMasterArray);

		$this->set("page_group", "community");
	}

	/*	 * **********************************
	 * NAME  : index
	 * INPUT : NONE
	 * OUTPUT: NONE
	 * DESC  :
	 *  プロフィールを閲覧するときに実行されるメソッド
	 * NOTICE:
	 * CREATE: 2016.10.19 aoyama
	 * UPDATE: 2017.2.13 aoyama
	 *		画像複数登録の対応（表示部分のみ）
	 * *********************************** */
	public function index() {
		
		//システムID形式をチェック
		if (InputVali::is_system_id(REQUEST::get_data('uid'))) {
			$target_user = REQUEST::get_data('uid');
		}
		else {
			$target_user = $this->public_user_data['system_id'];
		}

		//対象ユーザーの検索
		$user = new UserPublicModel();
		if (!$user_id = $user->get_user_id_by_system_id($target_user)) {
			$this->set("error", "ご指定のユーザーが見つかりません。");
			return;
		}

		//ユーザー情報の取得
		$user_detail = $user->get_user_detail_by_user_id($user_id);
		if (StaticFunction::is_empty($user_detail[0])) {
			$this->set("error", "ご指定のユーザーが見つかりません。");
			return;
		}

		$friend = new UserMatchModel();
		$image = new Image();

		//自分のアバターをセット
        $this->set("my_avatar", $image->get_avatar_url($this->public_user_data['system_id']));

		/*
		 *  POSTデータがある場合、セッションに登録する。
		 * 	ユーザー宛のメッセージ送信をしようとしている。
		 * UPDATE: 2016.10.28 aoyama
		 * 		編集機能を追加
		 */
		if (!StaticFunction::is_empty(REQUEST::post_data())) {

			SESSION::write($this->sGroup . '.message', REQUEST::post_data('message'));
			SESSION::write($this->sGroup . '.uid', REQUEST::post_data('uid'));
			SESSION::write($this->sGroup . '.file',true);

			//ファイル添付がある場合
			/*
			 * 今のところ画像ファイルだけだが、
			 * 動画ファイルなどが対象になると大幅に工数UPになるかなと
			 * ファイル用のライブラリも必要になる
			 */
			if ($_FILES['message_file']['error'] == UPLOAD_ERR_OK) {

				$file = new Image();

				//一時ファイル名を生成
				$file_tmp_hash = Encrypt::member_regist_token($_SERVER['REMOTE_ADDR'], time());

				//ロード
				if (!$ret = $file->load($_FILES['message_file']['tmp_name'])) {
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
					$file->move_file("", $_FILES['message_file']['tmp_name'], $tmp_dir, $tmp_file_name);

					SESSION::write($this->sGroup . '.tmp_file_name', $tmp_file_name);
					SESSION::write($this->sGroup . '.tmp_file_date', $date_dir);
				}
			}

			//セッションのフォームデータをチェック
			$error_array = $this->checkSessionParameter();

			if (StaticFunction::is_empty($error_array)) {



				//問題なければ確認画面へ
				$this->redirect("./confirm.html");
			}
			$this->set('error_array', $error_array);
			$this->formReturn();
		}

		/*
		 * 友達申請処理
		 */
		//フレンド申請
		if (
			REQUEST::get_data('mode') === "set" &&
			REQUEST::get_data('token') === SESSION::read('EXPIRES.ORIGINAL_TOKEN')
		) {
			if ($friend->set($this->public_user_data['user_id'], $user_detail[0]['user_id'])) {
				$message = new MypageMessageModel();
				$message_text = SANITIZE::exec('フレンド申請');
				$message->send_message($this->public_user_data['user_id'], $user_detail[0]['user_id'], $message_text);

				//受信者のアプリ登録を取得
				$andr = new UserAndroidModel();
				$ios = new UserIosModel();

				//プッシュ通知のタイトルと本文をセット
				$title = $this->public_user_data['nickname'] . 'さんからフレンド申請が届きました。';
				$body = $this->public_user_data['nickname'] . 'さんからフレンド申請が届きました。';

				//androidのトークンを取得し通知
				$andr_array = $andr->get_token($user_detail[0]['user_id']);
				if (!StaticFunction::is_empty($andr_array)) {
					$andr_push = new Fcm();
					foreach ($andr_array AS $andr_value) {
						$andr_push->post_push($andr_value['device_token'], $title, $body);
					}
				}

				//iOSのトークンを取得し通知
				$ios_array = $ios->get_token($user_detail[0]['user_id']);
				if (!StaticFunction::is_empty($ios_array)) {

					$ios_push = new Apns();
					foreach ($ios_array AS $ios_value) {
						$ios_push->post_push($ios_value['device_token'], $title, $body);
					}
				}
			}
		}

		/*
		 * フレンド登録解除
		 * UPDATE: 2016.10.26 aoyama
		 * このときは承認フローがないのでレコード削除しフレンドカウントを更新
		 */
		if (
			REQUEST::get_data('mode') === "remove" &&
			REQUEST::get_data('token') === SESSION::read('EXPIRES.ORIGINAL_TOKEN')
		) {
			//フレンド解消処理
			$friend->un_set($this->public_user_data['user_id'], $user_detail[0]['user_id']);

			// フレンドカウントセット
			$friend->set_friend_count($this->public_user_data['user_id']);
		}

		/*
		 * 友達状態をセット
		 */
		$this->set("is_match", $friend->is_match($this->public_user_data['user_id'], $user_detail[0]['user_id']));
		$this->set("is_self", ($this->public_user_data['user_id'] == $user_detail[0]['user_id']) ? true : false);
		$this->set("is_master", (CONF::read('MASTER_USER.USER_ID') == $user_detail[0]['user_id']) ? true : false);

		//ターゲットの基幹システム情報を取得
		$api = new Rest();
		$target_detail = $api->get_user_detail($user_detail[0]['system_user_id']);
		if ($target_detail['code'] == "200") {
			$target_name = $target_detail['user']['name'];
			$target_sex = $target_detail['user']['sex'] . "性";
			$target_birth = $target_detail['user']['birth_m'] . "月" . $target_detail['user']['birth_d'] . "日";
		}

		// 表示に必要な情報をセット
		$this->set("nickname", $user_detail[0]['nickname']);
		/*
		if(StaticFunction::is_admin($this->public_user_data['role'])) {
			$this->set("name", $target_name);
		}*/
		$this->set("sex", $target_sex);
		$this->set("birth", $target_birth);
		$this->set("fashion_view", (!StaticFunction::is_empty($user_detail[0]['fashion_id'])) ? $this->fashionMasterArray[$user_detail[0]['fashion_id']] : "　");
		$this->set("like_brand", $user_detail[0]['like_brand']);
		$this->set("comment", $user_detail[0]['comment']);
		$this->set("system_id", $user_detail[0]['system_id']);
		$this->set("system_user_id", $user_detail[0]['system_user_id']);
		$this->set("avatar", $image->get_avatar_url($user_detail[0]['system_id']));

		//フレンドリストを表示
		$friendList = $friend->get_friend_list($user_detail[0]['user_id'],0,5,'commit');

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
		 * 参加コミュニティリストを表示
		 */
		$community = new CommunityModel();
		$communityList = $community->get_thread_from_user($user_detail[0]['user_id'], 0, 10);

		$communityArray = array();
		if (!StaticFunction::is_empty($communityList)) {
			foreach ($communityList AS $value) {

				$communityArray[] = array(
					"thread_id" => $value['thread_id'],
					"thread_link" => "/community/detail.html?tid=" . $value['thread_id'],
					"community_name" => $value['community_name'],
					"community_detail" => $value['community_detail'],
					"category_name" => $value['category_name'],
					"avatar" => $image->get_avatar_thread_url($value['thread_id'], $value['image_file'])
				);
			}
		}
		$this->set("communityArray", $communityArray);

		/*
		 * タイムライン取得
		 */
		$timeline = new TimelineModel();

		//ページ指定文字のサニタイズ
		$pd = (InputVali::is_num(REQUEST::get_data('pd'))) ? REQUEST::get_data('pd') : 0;
		$pp = (InputVali::is_num(REQUEST::get_data('pp'))) ? REQUEST::get_data('pp') : CONF::read('PAGING.DEFAULT_NUM_PUBLIC');

		$tvViewArray = array();
		$timeline_ids = array();
		$response_ids = array();
		foreach ($timeline->get_timeline_profile($user_id, $pd, $pp,$this->public_user_data['user_id']) AS $tlValue) {

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
		if (isset($thread_ids)) {
			$this->set("community_match", $community->get_community_match_user($thread_ids,$this->public_user_data['user_id']));
		}        

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
		$tl_count = $timeline->get_timeline_profile_count($user_id,$this->public_user_data['user_id']);

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
	}

	/*	 * **********************************
	 * NAME  : friend_set
	 * INPUT : NONE
	 * OUTPUT: NONE
	 * DESC  :
	 *  友達申請が実行されるメソッド
	 * NOTICE:
	 * CREATE: 2016.10.21 aoyama
	 * *********************************** */
	public function friend_set() {

		//対象ユーザーの検索
		$user = new UserPublicModel();
		if (!$user_id = $user->get_user_id_by_system_id(REQUEST::get_data('uid'))) {
			$this->set("error", "ご指定のユーザーが見つかりません。");
			return;
		}

		$user_detail = $user->get_user_detail_by_user_id($user_id);

		if (!StaticFunction::is_empty($user_detail[0])) {

			$image = new Image();

			// 表示に必要な情報をセット
			$this->set("nickname", $user_detail[0]['nickname']);
			$this->set("fashion_view", $this->fashionMasterArray[$user_detail[0]['fashion_id']]);
			$this->set("like_brand", $user_detail[0]['like_brand']);
			$this->set("comment", $user_detail[0]['comment']);
			$this->set("system_id", $user_detail[0]['system_id']);
			$this->set("system_user_id", $user_detail[0]['system_user_id']);
			$this->set("avatar", $image->get_avatar_url($user_detail[0]['system_user_id']));

			//フレンドリストを表示
			$friend = new UserMatchModel();
			$friendList = $friend->get_friend_list($user_id,0,5,'commit');

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
		}
	}

	/*	 * **********************************
	 * NAME  : friend
	 * INPUT : NONE
	 * OUTPUT: NONE
	 * DESC  :
	 * 		プロフィールの友人一覧を表示するメソッド
	 * NOTICE:
	 * CREATE: 2016.11.1 aoyama
	 * *********************************** */
	public function friend() {

		//システムID形式をチェック
		if (!InputVali::is_system_id(REQUEST::get_data('uid'))) {
			$this->set("error", "ご指定のユーザーが見つかりません。");
			return;
		}

		//対象ユーザーの検索
		$user = new UserPublicModel();
		if (!$user_id = $user->get_user_id_by_system_id(REQUEST::get_data('uid'))) {
			$this->set("error", "ご指定のユーザーが見つかりません。");
			return;
		}

		$user_detail = $user->get_user_detail_by_user_id($user_id);
		if (!StaticFunction::is_empty($user_detail[0])) {

			$friend = new UserMatchModel();
			$image = new Image();

			/*
			 * 友達申請処理
			 */
			//フレンド登録
			if (
				REQUEST::get_data('mode') === "set" &&
				REQUEST::get_data('token') === SESSION::read('EXPIRES.ORIGINAL_TOKEN')
			) {
				$friend->set($this->public_user_data['user_id'], $user_detail[0]['user_id']);
			}

			/*
			 * フレンド登録解除
			 * UPDATE: 2016.10.26 aoyama
			 * このときは承認フローがないのでレコード削除しフレンドカウントを更新
			 */
			if (
				REQUEST::get_data('mode') === "remove" &&
				REQUEST::get_data('token') === SESSION::read('EXPIRES.ORIGINAL_TOKEN')
			) {
				//フレンド解消処理
				$friend->un_set($this->public_user_data['user_id'], $user_detail[0]['user_id']);

				// フレンドカウントセット
				$friend->set_friend_count($this->public_user_data['user_id']);
			}

			/*
			 * 友達状態をセット
			 */
			$this->set("is_match", $friend->is_match($this->public_user_data['user_id'], $user_detail[0]['user_id']));
			$this->set("is_self", ($this->public_user_data['user_id'] == $user_detail[0]['user_id']) ? true : false);

			// 表示に必要な情報をセット
			$this->set("nickname", $user_detail[0]['nickname']);
			$this->set("fashion_view", $this->fashionMasterArray[$user_detail[0]['fashion_id']]);
			$this->set("like_brand", $user_detail[0]['like_brand']);
			$this->set("comment", $user_detail[0]['comment']);
			$this->set("system_id", $user_detail[0]['system_id']);
			$this->set("system_user_id", $user_detail[0]['system_user_id']);
			$this->set("avatar", $image->get_avatar_url($user_detail[0]['system_id']));

			//フレンドリストを表示
			$friendList = $friend->get_friend_list($user_detail[0]['user_id'],0,5,'commit');

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
			 * 参加コミュニティリストを表示
			 */
			$community = new CommunityModel();
			$communityList = $community->get_thread_from_user($user_detail[0]['user_id'], 0, 10);

			$communityArray = array();
			if (!StaticFunction::is_empty($communityList)) {
				foreach ($communityList AS $value) {

					$communityArray[] = array(
						"thread_id" => $value['thread_id'],
						"thread_link" => "/community/detail.html?tid=" . $value['thread_id'],
						"community_name" => $value['community_name'],
						"community_detail" => $value['community_detail'],
						"category_name" => $value['category_name'],
						"avatar" => $image->get_avatar_thread_url($value['thread_id'], $value['image_file'])
					);
				}
			}
			$this->set("communityArray", $communityArray);
		}


		//フレンドリストを表示
		$friend = new UserMatchModel();
		$image = new Image();

		//一覧用
		//ページ指定文字のサニタイズ
		$pd = (InputVali::is_num(REQUEST::get_data('pd'))) ? REQUEST::get_data('pd') : 0;
		$pp = (InputVali::is_num(REQUEST::get_data('pp'))) ? REQUEST::get_data('pp') : CONF::read('PAGING.DEFAULT_NUM_PUBLIC');

		//フレンド一覧を取得
		$friendAllList = $friend->get_friend_list($user_id, $pd, $pp);
		if (!StaticFunction::is_empty($friendAllList)) {
			foreach ($friendAllList AS $value) {

				$friendAllArray[] = array(
					"match_id" => $value['match_id'],
					"nickname" => $value['nickname'],
					"system_id" => $value['system_id'],
					"friend_count" => $value['friend_count'],
					"friend_status" => $value['friend_status'],
					"avatar" => $image->get_avatar_url($value['system_id'])
				);
			}
		}
		$this->set("friendAllArray", $friendAllArray);

		//フレンド総数を取得
		$frined_num = $friend->get_friend_num($user_id);

		//ページング出力
		$page = new PAGING();
		$this->set("pageng_html", $page->make_paging($frined_num));
	}

	/*	 * **********************************
	 * NAME  : community
	 * INPUT : NONE
	 * OUTPUT: NONE
	 * DESC  :
	 * 		プロフィールの参加コミュニティ一覧を表示するメソッド
	 * NOTICE:
	 * CREATE: 2016.11.1 aoyama
	 * *********************************** */
	public function community() {

		//システムID形式をチェック
		if (!InputVali::is_system_id(REQUEST::get_data('uid'))) {
			$this->set("error", "ご指定のユーザーが見つかりません。");
			return;
		}

		//対象ユーザーの検索
		$user = new UserPublicModel();
		if (!$user_id = $user->get_user_id_by_system_id(REQUEST::get_data('uid'))) {
			$this->set("error", "ご指定のユーザーが見つかりません。");
			return;
		}

		$user_detail = $user->get_user_detail_by_user_id($user_id);
		if (!StaticFunction::is_empty($user_detail[0])) {

			$friend = new UserMatchModel();
			$image = new Image();

			/*
			 * 友達申請処理
			 */
			//フレンド登録
			if (
				REQUEST::get_data('mode') === "set" &&
				REQUEST::get_data('token') === SESSION::read('EXPIRES.ORIGINAL_TOKEN')
			) {
				$friend->set($this->public_user_data['user_id'], $user_detail[0]['user_id']);
			}

			/*
			 * フレンド登録解除
			 * UPDATE: 2016.10.26 aoyama
			 * このときは承認フローがないのでレコード削除しフレンドカウントを更新
			 */
			if (
				REQUEST::get_data('mode') === "remove" &&
				REQUEST::get_data('token') === SESSION::read('EXPIRES.ORIGINAL_TOKEN')
			) {
				//フレンド解消処理
				$friend->un_set($this->public_user_data['user_id'], $user_detail[0]['user_id']);

				// フレンドカウントセット
				$friend->set_friend_count($this->public_user_data['user_id']);
			}

			/*
			 * 友達状態をセット
			 */
			$this->set("is_match", $friend->is_match($this->public_user_data['user_id'], $user_detail[0]['user_id']));
			$this->set("is_self", ($this->public_user_data['user_id'] == $user_detail[0]['user_id']) ? true : false);

			// 表示に必要な情報をセット
			$this->set("nickname", $user_detail[0]['nickname']);
			$this->set("fashion_view", $this->fashionMasterArray[$user_detail[0]['fashion_id']]);
			$this->set("like_brand", $user_detail[0]['like_brand']);
			$this->set("comment", $user_detail[0]['comment']);
			$this->set("system_id", $user_detail[0]['system_id']);
			$this->set("system_user_id", $user_detail[0]['system_user_id']);
			$this->set("avatar", $image->get_avatar_url($user_detail[0]['system_id']));

			//フレンドリストを表示
			$friendList = $friend->get_friend_list($user_detail[0]['user_id'],0,5,'commit');

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
			 * 参加コミュニティリストを表示
			 */
			$community = new CommunityModel();
			$communityList = $community->get_thread_from_user($user_detail[0]['user_id'], 0, 10);

			$communityArray = array();
			if (!StaticFunction::is_empty($communityList)) {
				foreach ($communityList AS $value) {

					$communityArray[] = array(
						"thread_id" => $value['thread_id'],
						"thread_link" => "/community/detail.html?tid=" . $value['thread_id'],
						"community_name" => $value['community_name'],
						"community_detail" => $value['community_detail'],
						"category_name" => $value['category_name'],
						"avatar" => $image->get_avatar_thread_url($value['thread_id'], $value['image_file'])
					);
				}
			}
			$this->set("communityArray", $communityArray);
		}

		$community = new CommunityModel();
		$image = new Image();

		//一覧用
		//ページ指定文字のサニタイズ
		$pd = (InputVali::is_num(REQUEST::get_data('pd'))) ? REQUEST::get_data('pd') : 0;
		$pp = (InputVali::is_num(REQUEST::get_data('pp'))) ? REQUEST::get_data('pp') : CONF::read('PAGING.DEFAULT_NUM_PUBLIC');

		$communityAllList = $community->get_thread_from_user($user_id, $pd, $pp);
		$communityAllArray = array();
		if (!StaticFunction::is_empty($communityAllList)) {
			foreach ($communityAllList AS $value) {

				$communityAllArray[] = array(
					"community_link" => "/community/detail.html?tid=" . $value['thread_id'],
					"community_name" => $value['community_name'],
					"community_detail" => $value['community_detail'],
					"category_name" => $value['category_name'],
					"category_link" => $value['category_name'],
					"join_count" => $value['join_count'],
					"avatar" => $image->get_avatar_thread_url($value['thread_id'], $value['image_file'])
				);
			}
		}
		$this->set("communityAllArray", $communityAllArray);

		//参加コミュニティ総数を取得
		$thread_num = $community->get_thread_num_from_user($user_id);

		//ページング出力
		$page = new PAGING();
		$this->set("pageng_html", $page->make_paging($thread_num));
	}

	/*	 * **********************************
	 * NAME  : confirm
	 * INPUT : 
	 * OUTPUT: 
	 * DESC  : 
	 *  入力確認画面用
	 *  セッションがあればとりあえず表示する
	 *  ここではバリデーション無し
	 * NOTICE:
	 * CREATE: 2016.10.19 aoyama
	 * *********************************** */
	public function confirm() {
		$community = new CommunityModel();

		//システムID形式をチェック
		if (!InputVali::is_system_id(SESSION::read($this->sGroup . '.uid'))) {
			$this->set("error", "ご指定のユーザーが見つかりません。");
			return;
		}

		//対象ユーザーの検索
		$user = new UserPublicModel();
		if (!$user_id = $user->get_user_id_by_system_id(SESSION::read($this->sGroup . '.uid'))) {
			$this->set("error", "ご指定のユーザーが見つかりません。");
			return;
		}
		$user_detail = $user->get_user_detail_by_user_id($user_id);
		if (!StaticFunction::is_empty($user_detail[0])) {

			$friend = new UserMatchModel();
			$image = new Image();

			// 表示に必要な情報をセット
			$this->set("nickname", $user_detail[0]['nickname']);
			$this->set("fashion_view", $this->fashionMasterArray[$user_detail[0]['fashion_id']]);
			$this->set("like_brand", $user_detail[0]['like_brand']);
			$this->set("comment", $user_detail[0]['comment']);
			$this->set("system_id", $user_detail[0]['system_id']);
			$this->set("system_user_id", $user_detail[0]['system_user_id']);
			$this->set("avatar", $image->get_avatar_url($user_detail[0]['system_id']));

			//フレンドリストを表示
			$friendList = $friend->get_friend_list($user_detail[0]['user_id'],0,5,'commit');

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
			 * 参加コミュニティリストを表示
			 */
			$community = new CommunityModel();
			$communityList = $community->get_thread_from_user($user_detail[0]['user_id'], 0, 10);

			$communityArray = array();
			if (!StaticFunction::is_empty($communityList)) {
				foreach ($communityList AS $value) {

					$communityArray[] = array(
						"thread_id" => $value['thread_id'],
						"thread_link" => "/community/detail.html?tid=" . $value['thread_id'],
						"community_name" => $value['community_name'],
						"community_detail" => $value['community_detail'],
						"category_name" => $value['category_name'],
						"avatar" => $image->get_avatar_thread_url($value['thread_id'], $value['image_file'])
					);
				}
			}
			$this->set("communityArray", $communityArray);

			// viewにデータを渡す
			$this->formReturn();
		}
	}

	/*	 * **********************************
	 * NAME  : complete
	 * INPUT : 
	 * OUTPUT: 
	 * DESC  : 
	 * 		メッセージ送信完了処理
	 * NOTICE:
	 * CREATE: 2016.11.2 aoyama
	 * *********************************** */
	public function complete() {

		$target_system_id = SESSION::read($this->sGroup . '.uid');

		//システムID形式をチェック
		if (!InputVali::is_system_id($target_system_id)) {
			$this->set("error", "ご指定のユーザーが見つかりません。");
			return;
		}

		//対象ユーザーの検索
		$user = new UserPublicModel();
		if (!$user_id = $user->get_user_id_by_system_id($target_system_id)) {
			$this->set("error", "ご指定のユーザーが見つかりません。");
			return;
		}

		$user_detail = $user->get_user_detail_by_user_id($user_id);
		if (StaticFunction::is_empty(SESSION::read($this->sGroup)) && !StaticFunction::is_empty($user_detail[0])) {
			$this->set("error", "ご指定のユーザーが見つかりません。");
			return;
		}

		$friend = new UserMatchModel();
		$image = new Image();
		$message = new MypageMessageModel();

		if (!$friend->is_match($this->public_user_data['user_id'], $user_detail[0]['user_id'])) {
			$this->set("error", "メッセージはフレンドのみに送信できます");
			return;
		}

		/*
		 * バリデーション:エラーのときはindex.htmlに飛ばす
		 * indexのcheckSessionParameterとエラー情報の渡し方が異なる理由として
		 * ここでバリデーションに引っかかるということは予期しないアクセスなので
		 * そこまで親切にしなくてもいいかなと。(aoyama)
		 */
		$error_array = $this->checkSessionParameter();
		if (!StaticFunction::is_empty($error_array)) {
			$this->redirect("./profile/?uid=" . $target_system_id);
		}

		// メッセージ送信処理
		$message->send_message($this->public_user_data['user_id'], $user_detail[0]['user_id'], SESSION::read($this->sGroup . '.message'), SESSION::read($this->sGroup . '.tmp_file_name'));

		//受信者のアプリ登録を取得
		$andr = new UserAndroidModel();
		$ios = new UserIosModel();

		//プッシュ通知のタイトルと本文をセット
		$title = $this->public_user_data['nickname'] . 'さんからメッセージが届きました。';
		$body = $this->public_user_data['nickname'] . 'さんからメッセージが届きました。';

		//androidのトークンを取得し通知
		$andr_array = $andr->get_token($user_detail[0]['user_id']);
		if (!StaticFunction::is_empty($andr_array)) {
			$andr_push = new Fcm();
			foreach ($andr_array AS $andr_value) {
				$andr_push->post_push($andr_value['device_token'], $title, $body);
			}
		}

		//iOSのトークンを取得し通知
		$ios_array = $ios->get_token($user_detail[0]['user_id']);
		if (!StaticFunction::is_empty($ios_array)) {

			$ios_push = new Apns();
			foreach ($ios_array AS $ios_value) {
				$ios_push->post_push($ios_value['device_token'], $title, $body);
			}
		}

		//添付ファイルがある場合は画像を送信者ディレクトリに移動
		if (!StaticFunction::is_empty(SESSION::read($this->sGroup . '.tmp_file_name'))) {

			$img = new Image();
			$ret = $img->set_message_public(SESSION::read($this->sGroup . '.tmp_file_date'), SESSION::read($this->sGroup . '.tmp_file_name'), $this->public_user_data['system_id']);

			//失敗時
			if (!$ret) {
				LOGS_ERR("添付ファイルの送信に失敗しました。");
				//失敗時はアラートメール送信
			}
		}

		//正常終了時はセッションを削除
		SESSION::delete($this->sGroup);
		$this->redirect("/profile/?uid=" . $target_system_id);
	}

	/*	 * **********************************
	 * NAME:checkSessionParameter
	 * DESC:
	 *  メルマガ登録専用のセッション情報バリデーション
	 * NOTICE:
	 * CREATE: 2016.10.19 aoyama
	 * *********************************** */
	private function checkSessionParameter() {

		$error_array = array();
		
		if (!SESSION::read($this->sGroup . '.file')) {
			$error_array[] = array('target' => 'file', 'message' => '添付できるファイルは画像のみです。');
		}

		if (!InputVali::is_comment_thread(SESSION::read($this->sGroup . '.message'))) {
			$error_array[] = array('target' => 'message', 'message' => 'メッセージは1000文字以内で入力してください。');
		}

		return $error_array;
	}

	/*	 * **********************************
	 * NAME:formReturn
	 * DESC:
	 *  セッション情報をフォームに渡すためにセットする機能
	 * NOTICE:
	 * CREATE: 2016.11.2 aoyama
	 * *********************************** */
	private function formReturn() {

		// セッションの情報をセットしてviewに渡す
		if (!StaticFunction::is_empty(SESSION::read($this->sGroup))) {
			$this->set("message", SESSION::read($this->sGroup . '.message'));
			$this->set("tmp_file_name", SESSION::read($this->sGroup . '.tmp_file_name'));
			$this->set("tmp_file_date", SESSION::read($this->sGroup . '.tmp_file_date'));
		}
	}

}

?>
