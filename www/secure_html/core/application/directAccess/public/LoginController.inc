<?php

/* * **********************************
 * NAME:LoginController
 * DESC:
 *   ログイン画面用コントローラ
 * NOTICE:
 * CREATE: 2016.10.12 aoyama
 * *********************************** */
class LoginController extends PublicOpenControllerFrame {

	private $sGroup;

	/* Constructor */
	public function __construct() {
		parent::__construct();
		$this->sGroup = 'login';

		//セッションからユーザ情報を取得
		$this->public_user_data = SESSION::read(CONF::read('LOGIN_CATEGORY.PUBLIC'));
	}

	/*	 * **********************************
	 * NAME  : exec
	 * INPUT : NONE
	 * OUTPUT: NONE
	 * DESC  :
	 *  ユーザログイン画面用メソッド
	 * NOTICE:
	 * CREATE: 2016.10.12 aoyama
	 * UPDATE: 2016.11.18 aoyama
	 * 		ログイン失敗のテキストを変更
	 * UPDATE: 2016.12.19 aoyama
	 *		ログセット
	 * *********************************** */
	public function index() {

		/* ログインモジュール開始 */
		$login = new Login();

		//ログイン済みかチェック
		if ($login->is_login()) {
			//ログイン済みの場合はトップへリダイレクト
			$this->redirect(CONF::read('URL_PUBLIC_ROOT'));
		}

		//未入力の場合はここで終了
		if (!REQUEST::is_post()) {
			return;
		}

		/* 入力がなければ終了 */
		if (StaticFunction::is_empty(REQUEST::post_data('user_id')) || StaticFunction::is_empty(REQUEST::post_data('password'))) {
			//$this->set('alert', 'ユーザーIDとパスワードを入力して下さい。');
			$error_array[] = array('target' => 'comment', "message" => "ユーザーIDとパスワードを入力して下さい。");
			$this->set('error_array', $error_array);
			LOGS_LOGIN("FAILED_001_ID:".REQUEST::post_data('user_id')."_PASS:".REQUEST::post_data('password'));
			return;
		}
		/* TOKENチェック */
		if (REQUEST::post_data('token') != SESSION::read('EXPIRES.ORIGINAL_TOKEN')) {
			//$this->set('alert', 'ユーザーIDとパスワードを入力して下さい。');
			$error_array[] = array('target' => 'comment', "message" => "ユーザーIDとパスワードを入力して下さい。");
			$this->set('error_array', $error_array);
			LOGS_LOGIN("FAILED_002_ID:".REQUEST::post_data('user_id')."_PASS:".REQUEST::post_data('password')."_TOKEN:".REQUEST::post_data('token'));
			return;
		}

		if (!$login->input_verification(
				REQUEST::post_data('user_id'), REQUEST::post_data('password')
			)) {
			$error_array[] = array('target' => 'comment', "message" => "ユーザーIDとパスワードが一致しません。");
			$this->set('error_array', $error_array);
			LOGS_LOGIN("FAILED_003_ID:".REQUEST::post_data('user_id')."_PASS:".REQUEST::post_data('password')."_TOKEN:".REQUEST::post_data('token'));
			return;
		}
		
		//ログイン成功したので新着メッセージ数をセッションに登録
		LOGS_LOGIN("SUCCESS_ID:".REQUEST::post_data('user_id')."_PASS:".REQUEST::post_data('password')."_TOKEN:".REQUEST::post_data('token'));

		//ログイン認証に成功したらトップページヘリダイレクト
		if (!StaticFunction::is_empty(REQUEST::get_data('callback'))) {
			$this->redirect(REQUEST::get_data('callback'));
		} else {
			$this->redirect(CONF::read('URL_PUBLIC_ROOT') . 'mypage');
		}
	}

	/*	 * **********************************
	 * NAME  : happy
	 * INPUT : NONE
	 * OUTPUT: NONE
	 * DESC  :
	 *  未ログイン時のハッピーさんタイムラインの表示
	 * NOTICE:
	 * CREATE: 2016.12.16 aoyama
	 * *********************************** */
	public function happy() {
		
		$user_id = CONF::read('MASTER_USER.USER_ID');
		
		//ユーザー情報の取得
		$user = new UserPublicModel();
		$user_detail = $user->get_user_detail_by_user_id($user_id);
		if (StaticFunction::is_empty($user_detail[0])) {
			$this->set("error", "ご指定のユーザーが見つかりません。");
			return;
		}

		$friend = new UserMatchModel();
		$image = new Image();


		// 表示に必要な情報をセット
		$this->set("g_nickname", $user_detail[0]['nickname']);
		$this->set("g_comment", $user_detail[0]['comment']);
		$this->set("g_avatar", $image->get_avatar_url($user_detail[0]['system_id']));

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
		foreach ($timeline->get_timeline_happy($user_id, $pd, $pp) AS $tlValue) {

			// 画像ファイルの表示用配列初期化(2017.2.13 aoyama)
			$file_url = array();

			switch ($tlValue['type']) {

				case "response":
					// 2019.01.18 コミュニティ投稿の画像取得メソッドを追加
					$file_url = $community->get_community_response_image($tlValue['thread_id'],$tlValue['code']);
					break;
				case "timeline":
					//imageクラスではなくtimelineクラスで取得する方式に変更
					//$file_url = $image->get_timeline_url($tlValue['system_id'], $tlValue['file_name']);
					$file_url = $timeline->get_timeline_image($tlValue['system_id'], $tlValue['code']);
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
				"text_view" => StaticFunction::decode_view_text(nl2br($tlValue['text'])),
				"file_url" => $file_url,
				"avatar" => $image->get_avatar_url($tlValue['system_id']),
				"update_time" => DbDateTime::get_date_type_dot($tlValue['update_time'])
			);
		}
		$this->set("timeline_array", $tvViewArray);
		
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

		/* ページング用 */
		$tl_count = $timeline->get_timeline_happy_num($user_id);

		$page = new PAGING();
		$this->set("pageng_html", $page->make_paging($tl_count));


	}		
	
}

?>
