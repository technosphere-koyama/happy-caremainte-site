<?php

/* * **********************************
 * NAME:FriendController
 * DESC:
 * 		友達紹介登録ページのコントローラー
 * NOTICE:
 * CREATE: 2016.10.17 aoyama
 * UPDATE: 2016.11.17 aoyama
 *		POST方式を変更
 * *********************************** */
class FriendController extends PublicOpenControllerFrame {

	private $sGroup;

	/* Constructor */
	public function __construct() {
		parent::__construct();
		$this->sGroup = 'friend';
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
	 * CREATE: 2016.10.18 aoyama
	 * *********************************** */
	public function index() {

		//* ログイン中はログイン情報を配置
		$login = new Login();
		if ($login->is_login()) {

			$this->set("name1", SESSION::read(CONF::read('LOGIN_CATEGORY.PUBLIC') . '.name1'));
			$this->set("name2", SESSION::read(CONF::read('LOGIN_CATEGORY.PUBLIC') . '.name2'));
			$this->set("email", SESSION::read(CONF::read('LOGIN_CATEGORY.PUBLIC') . '.email'));
		}
		
		// POSTデータがある場合、セッションに登録する。
		if (!StaticFunction::is_empty(REQUEST::post_data())) {

			SESSION::write($this->sGroup . '.friend_name1', REQUEST::post_data('friend_name1'));
			SESSION::write($this->sGroup . '.friend_name2', REQUEST::post_data('friend_name2'));
			SESSION::write($this->sGroup . '.friend_email', REQUEST::post_data('friend_email'));
			SESSION::write($this->sGroup . '.name1', REQUEST::post_data('name1'));
			SESSION::write($this->sGroup . '.name2', REQUEST::post_data('name2'));
			SESSION::write($this->sGroup . '.email', REQUEST::post_data('email'));
			SESSION::write($this->sGroup . '.comment', REQUEST::post_data('comment'));

			// バリデーション(confirmセッション消す)
			$error_array = $this->checkSessionParameter();
			if (StaticFunction::is_empty($error_array)) {
				//問題なければ確認画面へ
				$this->redirect("./confirm.html");
			}
			
			$this->set('error_array', $error_array);
			$this->formReturn();
		}
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
	 * CREATE: 2016.10.14 aoyama
	 * *********************************** */
	public function confirm() {
		// POSTデータがないので「戻るボタン」の可能性。setしそのまま表示
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
	 *  API送信処理あり（セッションバリデーション含む）
	 * CREATE: 2016.10.18 aoyama
	 * *********************************** */
	public function complete() {

		if (StaticFunction::is_empty(SESSION::read($this->sGroup))) {
			$this->redirect("./");
		}

		$error_array = $this->checkSessionParameter();
		if (!StaticFunction::is_empty($error_array)) {
			$this->redirect("./");
		}

		//すべて完了したのでメール送信
		
		$mail_param = array(
			"friend_name" => StaticFunction::marge_name(SESSION::read($this->sGroup . '.friend_name1'), SESSION::read($this->sGroup . '.friend_name2')),
			"friend_email" => SESSION::read($this->sGroup . '.friend_email'),
			"name" => StaticFunction::marge_name(SESSION::read($this->sGroup . '.name1'),SESSION::read($this->sGroup . '.name2')),
			"email" => SESSION::read($this->sGroup . '.email'),
			"comment" =>  SESSION::read($this->sGroup . '.comment')
		);
		
		$mail = new Mail();
		if (!$mail->send_frend_complete($mail_param)) {
			LOGS_ERR('*** PASSWORD RESET ACCEPT MAIL SEND FAILED. ***');
			$this->set('alert', 'エラーが発生しました。お手数ですが、再度お試し下さい。');
			return;
		}

		//正常終了時はセッションを削除
		SESSION::delete($this->sGroup);
	}

	/*	 * **********************************
	 * NAME:checkSessionParameter
	 * DESC:
	 *  メルマガ登録専用のセッション情報バリデーション
	 * NOTICE:
	 * CREATE: 2016.10.18 aoyama
	 * *********************************** */
	private function checkSessionParameter() {

		$error_array = array();

		if (!InputVali::is_user_name(SESSION::read($this->sGroup . '.friend_name1'))) {
			$error_array[] = array('target' => 'friend_name1', 'message' => 'お友達のお名前（姓）を入力してください');
		}
		if (!InputVali::is_user_name(SESSION::read($this->sGroup . '.friend_name2'))) {
			$error_array[] = array('target' => 'friend_name2', 'message' => 'お友達のお名前（名）を入力してください');
		}

		if (!InputVali::is_mailaddress(SESSION::read($this->sGroup . '.friend_email'))) {
			$error_array[] = array('target' => 'friend_email', 'message' => 'お友達のメールアドレスを入力してください');
		}

		if (!InputVali::is_user_name(SESSION::read($this->sGroup . '.name1'))) {
			$error_array[] = array('target' => 'name1', 'message' => 'お名前（姓）を入力してください');
		}
		if (!InputVali::is_user_name(SESSION::read($this->sGroup . '.name2'))) {
			$error_array[] = array('target' => 'name2', 'message' => 'お名前（名）を入力してください');
		}

		if (!InputVali::is_mailaddress(SESSION::read($this->sGroup . '.email'))) {
			$error_array[] = array('target' => 'email', 'message' => 'メールアドレスを入力してください');
		}

		if (!StaticFunction::is_empty(SESSION::read($this->sGroup . '.comment'))) {
			if (!InputVali::is_comment_contact(SESSION::read($this->sGroup . '.comment'))) {
				$error_array[] = array('target' => 'comment', 'message' => 'メッセージは200文字以内で入力してください');
			}
		}

		return $error_array;
	}

	/*	 * **********************************
	 * NAME:formReturn
	 * DESC:
	 *  セッション情報をフォームに渡すためにセットする機能
	 * NOTICE:
	 * CREATE: 2016.10.18 aoyama
	 * *********************************** */
	private function formReturn() {

		// セッションの情報をセットしてviewに渡す
		if (!StaticFunction::is_empty(SESSION::read($this->sGroup))) {
			$this->set("friend_name1", SESSION::read($this->sGroup . '.friend_name1'));
			$this->set("friend_name2", SESSION::read($this->sGroup . '.friend_name2'));
			$this->set("friend_name_view", StaticFunction::marge_name(SESSION::read($this->sGroup . '.friend_name1'), SESSION::read($this->sGroup . '.friend_name2')));
			$this->set("friend_email", SESSION::read($this->sGroup . '.friend_email'));
			$this->set("name1", SESSION::read($this->sGroup . '.name1'));
			$this->set("name2", SESSION::read($this->sGroup . '.name2'));
			$this->set("name_view", StaticFunction::marge_name(SESSION::read($this->sGroup . '.name1'),SESSION::read($this->sGroup . '.name2')));
			$this->set("email", SESSION::read($this->sGroup . '.email'));
			$this->set("comment", SESSION::read($this->sGroup . '.comment'));
		}
	}
}

?>
