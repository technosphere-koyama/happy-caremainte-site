<?php

/* * **********************************
 * NAME:MypageMessageController
 * DESC:
 * 		messageテーブルはすべてのユーザが使用するため、
 * extend_idではなくuser_idで管理している。
 * なので、データ登録・更新の際にはuser_idを引数に渡している事が多い。
 * 他のコントローラと混同しないように注意すること！！！
 *
 * NOTICE:
 * CREATE: 2016.10.17 aoyama
 * *********************************** */
class MypageMessageController extends MypageCloseCommonControllerFrame {

	private $sGroup;
	private $public_user_data;

	/* Constructor */
	public function __construct() {
		parent::__construct();
		$this->sGroup = 'mypage_message';
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
	 * メッセージ一覧画面
	 * 
	 * CONF::read('LOGIN_CATEGORY.PUBLIC') == PUBLIC_USER
	 * 
	 * NOTICE:
	 * CREATE: 2016.10.17 aoyama
	 * UPDATE: 2016.12.15 aoyama
	 *		仕様変更により、ここでは一度でもメッセージをやり取りしたことがある
	 *		ユーザーの一覧を表示する。
	 * *********************************** */
	public function index() {

		//keyの値をcheck_request_parameterで使用しているので、、
		//ここの値を変更した場合は、check_request_parameterの値も
		//変更すること。	
		$this->set('status_list', array(
			'0' => 'すべて',
			'1' => '未読',
			'2' => '既読'
		));

		//フレンドリストを表示
		$image = new Image();
		$friend = new UserMatchModel();
		$friendList = $friend->get_friend_list($this->public_user_data['user_id'],0,5,'commit');

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
		
		//メッセージを取得する
		$message = new MypageMessageModel();

		//ページ指定文字のサニタイズ
		$pd = (InputVali::is_num(REQUEST::get_data('pd'))) ? REQUEST::get_data('pd') : 0;
		$pp = (InputVali::is_num(REQUEST::get_data('pp'))) ? REQUEST::get_data('pp') : CONF::read('PAGING.DEFAULT_NUM_PUBLIC');

		//メッセージを取得
		$messageList = $message->get_message_user_list($this->public_user_data['user_id'], $pd, $pp);

		if (!$messageList) {
			$this->set("messages", array());
			return;
		}
		
//		var_dump($messageList);
//		exit;

		$messageArray = array();
		foreach ($messageList AS $values) {
			$messageArray[] = array(
				'avatar' => $image->get_avatar_url($values['group_system_id']),
				"update_time" => DbDateTime::get_date_type_dot($values['create_time']),
				"user_link" => "/profile/?uid=" . $values['group_system_id'],
				"message_link" => "/mypage/message/detail.html?uid=" . $values['group_system_id'],
				"nickname" => $values['group_nickname']
			);
		}

		$this->set("messages", $messageArray);

		//メッセージ数を取得
		$messageCount = $message->get_message_user_list_num($this->public_user_data['user_id']);

		$page = new PAGING();
		$this->set("pageng_html", $page->make_paging($messageCount));

		return;
	}

	/*	 * **********************************
	 * NAME  : detail
	 * INPUT : NONE
	 * OUTPUT: NONE
	 * DESC  :
	 * メッセージ詳細画面
	 * NOTICE:
	 * CREATE: 2016.10.23 aoyama
	 * UPDATE: 2016.12.15 aoyama
	 *		メッセージの仕様変更
	 * UPDATE: 2016.12.22 aoyama
	 *		POST形式に変更
	 * *********************************** */
	public function detail() {

		//システムID形式をチェック
		if (!InputVali::is_system_id(REQUEST::get_data('uid'))) {
			$this->set("error", "ご指定のユーザーが見つかりません。");
			return;
		}
		$target_user = REQUEST::get_data('uid');

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
		
		//アバター、添付ファイルがあるときのためにimageインスタンス生成
		$image = new Image();
		
		$this->set("friend_nickname", $user_detail[0]['nickname']);
		$this->set("friend_avatar", $image->get_avatar_url($user_detail[0]['system_id']));
		$this->set("friend_link", "/profile/?uid=".$user_detail[0]['system_id']);
		
		//管理者権限を持っている場合はユーザーの個人情報を取得
		if(StaticFunction::is_admin($this->public_user_data['role'])) {
			
			//ターゲットの基幹システム情報を取得
			$api = new Rest();
			$target_detail = $api->get_user_detail($user_detail[0]['system_user_id']);
			if ($target_detail['code'] == "200") {
				$this->set("name", $target_detail['user']['name']);
			}
		}
		
		//ターゲットとしているメッセージユーザーのIDをそのままviewへ渡す
		$this->set("system_id", $target_user);
		
		//メッセージ用モデル読み込み
		$message = new MypageMessageModel();

		//ページ指定をセット
		$pd = (InputVali::is_num(REQUEST::get_data('pd'))) ? REQUEST::get_data('pd') : 0;
		$pp = (InputVali::is_num(REQUEST::get_data('pp'))) ? REQUEST::get_data('pp') : CONF::read('PAGING.DEFAULT_NUM_PUBLIC');

		//メッセージリストを取得
		$message_array = array();
		
		//未読メッセージの存在フラグ
		$unlead = false;
		
		foreach($message->get_message_list($this->public_user_data['user_id'],$user_id, $pd, $pp) AS $value) {
			
			//自分自身の投稿を判定
			$is_my_post = ($value['from_user_id'] === $this->public_user_data['user_id']) ? true : false;
			
			//未読メッセージが含まれていれば更新対象に。
			if ((int)$value['read_status'] === 1) {
				$unlead = true;
			}
			
			//配列化
			$message_array[] = array(
				'is_my_post' => $is_my_post,
				'message_id' => $value['message_id'],
				'from_avatar' => $image->get_avatar_url($value['from_system_id']),
				'from_nickname' => $value['from_nickname'],
				'from_system_id' => $value['from_system_id'],
				'to_nickname' => $value['to_nickname'],
				'to_system_id' => $value['to_system_id'],
				'message_comment' => StaticFunction::decode_view_text(nl2br($value['message_comment'])),
				'date' => DbDateTime::get_date_type_dot($value['create_time']),
				'user_link' => "/profile/?uid=".$value['to_system_id'],
				'file' => $image->get_message_url($value['from_system_id'],$value['image_file'] )
			);
		}
		$this->set('message_array',$message_array);
		
		//未読メッセージを受信していれば既読に変更
		if ($unlead) {
			$message->unread_update($user_id,$this->public_user_data['user_id']);
		}
		
		//メッセージ総数を取得
		$message_num = $message->get_message_list_num($this->public_user_data['user_id'],$user_id);

		//ページング出力
		$page = new PAGING();
		$this->set("pageng_html", $page->make_paging($message_num));
		
		//エラーメッセージがあれば出力
		if(!StaticFunction::is_empty(SESSION::read($this->sGroup . '.error_array'))){
			$this->set("error_array", SESSION::read($this->sGroup . '.error_array'));
			SESSION::delete($this->sGroup . '.error_array');
		}
		$this->formReturn();
		
		//リターンしたのでセッションは消す。
		SESSION::delete($this->sGroup);
		
		return;
	}

	/*	 * **********************************
	 * NAME  : complete
	 * INPUT : 
	 * OUTPUT: 
	 * DESC  : 
	 * 		メッセージ送信完了処理
	 * NOTICE:
	 * CREATE: 2016.11.2 aoyama
	 * UPDATE: 2016.12.22 aoyama
	 *		POST方式に変更
	 * *********************************** */
	public function complete() {

		/*
		 *  POSTデータがある場合、セッションに登録する。
		 * 	ユーザー宛のメッセージ送信をしようとしている。
		 * UPDATE: 2016.12.15 aoyama
		 * 		編集機能を追加
		 */
		if (!StaticFunction::is_empty(REQUEST::post_data())) {

			//GETパラメータからターゲットの
			$target_system_id = REQUEST::post_data('uid');

			//システムID形式をチェック
			if (!InputVali::is_system_id($target_system_id)) {
				$error_array[] = array("message" => "ユーザーの指定形式が無効です。");
				SESSION::write($this->sGroup . '.error_array', $error_array);
				$this->redirect("/mypage/message/detail.html?uid=".$target_system_id);
			}

			//対象ユーザーの検索
			$user = new UserPublicModel();
			if (!$user_id = $user->get_user_id_by_system_id($target_system_id)) {
				$error_array[] = array("message" => "ユーザーの検索に失敗しました。");
				SESSION::write($this->sGroup . '.error_array', $error_array);
				$this->redirect("/mypage/message/detail.html?uid=".$target_system_id);
			}

			//対象ユーザーの情報を取得
			$user_detail = $user->get_user_detail_by_user_id($user_id);
			if (StaticFunction::is_empty($user_detail[0])) {
				$error_array[] = array("message" => "ご指定のユーザーが見つかりません。");
				SESSION::write($this->sGroup . '.error_array', $error_array);
				$this->redirect("/mypage/message/detail.html?uid=".$target_system_id);
			}

			//フレンドチェック
			$friend = new UserMatchModel();
			$message = new MypageMessageModel();
			if (!$friend->is_match($this->public_user_data['user_id'], $user_detail[0]['user_id'])) {
				$error_array[] = array("message" => "メッセージはフレンドのみに送信できます。");
				SESSION::write($this->sGroup . '.error_array', $error_array);
				$this->redirect("/mypage/message/detail.html?uid=".$target_system_id);
			}
		
			//ユーザーチェックが通ったのでセッション登録
			SESSION::write($this->sGroup . '.message', REQUEST::post_data('message'));
			SESSION::write($this->sGroup . '.uid', REQUEST::post_data('uid'));
			SESSION::write($this->sGroup . '.file',true);

			//ファイル添付がある場合
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
		
			// バリデーション
			$error_array = $this->checkSessionParameter();
			if (!StaticFunction::is_empty($error_array)) {
				SESSION::write($this->sGroup . '.error_array', $error_array);
				$this->redirect("/mypage/message/detail.html?uid=".$target_system_id);
			}

			// メッセージ送信処理
			$message->send_message($this->public_user_data['user_id'], $user_detail[0]['user_id'], SESSION::read($this->sGroup . '.message'), SESSION::read($this->sGroup . '.tmp_file_name'));

			//アプリプッシュ用のクラス読み込み
			$andr = new UserAndroidModel();
			$ios = new UserIosModel();

			//プッシュ通知のタイトルと本文をセット（共通）
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
			$this->redirect("/mypage/message/detail.html?uid=" . $target_system_id);
		}
		
		//POSTのないアクセスなのでTOPへリダイレクト
		$this->redirect("/mypage/message/detail.html?uid=" . $target_system_id);
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
			$error_array[] = array('target' => 'message', 'message' => 'メッセージは400文字以内で入力してください。');
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
