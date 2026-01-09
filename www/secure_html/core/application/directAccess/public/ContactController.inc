<?php

/* * **********************************
 * NAME:ContactController
 * DESC:
 * 		お問合せページのコントローラー
 * NOTICE:
 * CREATE: 2016.10.16 aoyama
 * UPDATE: 2016.11.17 aoyama
 *		POST方式を変更
 * *********************************** */
class ContactController extends PublicOpenControllerFrame {

	private $sGroup;

	/* Constructor */
	public function __construct() {
		parent::__construct();
		$this->sGroup = 'contact';
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
	public function index() {

				
		// ログイン中でセッション情報が無い場合はログイン情報をviewiに渡す
		$login = new Login();
		if ($login->is_login()) {
			/*
			 * もしもAPIからのTELが連結されていた場合は分割（aoyama）
			 */
			$telArray = StaticFunction::phone_to_array(SESSION::read(CONF::read('LOGIN_CATEGORY.PUBLIC') . '.tel'));

			$this->set("name1", SESSION::read(CONF::read('LOGIN_CATEGORY.PUBLIC') . '.name1'));
			$this->set("name2", SESSION::read(CONF::read('LOGIN_CATEGORY.PUBLIC') . '.name2'));
			$this->set("kana1", SESSION::read(CONF::read('LOGIN_CATEGORY.PUBLIC') . '.kana1'));
			$this->set("kana2", SESSION::read(CONF::read('LOGIN_CATEGORY.PUBLIC') . '.kana2'));
			$this->set("email", SESSION::read(CONF::read('LOGIN_CATEGORY.PUBLIC') . '.email'));
			$this->set("state", SESSION::read(CONF::read('LOGIN_CATEGORY.PUBLIC') . '.state'));
			$this->set("telephone", StaticFunction::convert_zen_to_han_num($telArray[0]));
			$this->set("telephone2", StaticFunction::convert_zen_to_han_num($telArray[1]));
			$this->set("telephone3", StaticFunction::convert_zen_to_han_num($telArray[2]));
		}
		if(!StaticFunction::is_empty(SESSION::read($this->sGroup . '.error_array'))){
			$this->set("error_array", SESSION::read($this->sGroup . '.error_array'));
			SESSION::delete($this->sGroup . '.error_array');
		}
		$this->formReturn();
		//リターンしたのでセッションは消す。
		SESSION::delete($this->sGroup);
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
	 * CREATE: 2016.10.16 aoyama
	 * *********************************** */
	public function confirm() {
		// POSTデータがないので「戻るボタン」の可能性。setしそのまま表示
		// POSTデータがある場合、セッションに登録する。
		if (!StaticFunction::is_empty(REQUEST::post_data())) {
			
			SESSION::write($this->sGroup . '.name1', REQUEST::post_data('name1'));
			SESSION::write($this->sGroup . '.name2', REQUEST::post_data('name2'));
			SESSION::write($this->sGroup . '.kana1', REQUEST::post_data('kana1'));
			SESSION::write($this->sGroup . '.kana2', REQUEST::post_data('kana2'));
			SESSION::write($this->sGroup . '.email', REQUEST::post_data('email'));
			SESSION::write($this->sGroup . '.state', REQUEST::post_data('state'));
			SESSION::write($this->sGroup . '.telephone', StaticFunction::convert_zen_to_han_num(REQUEST::post_data('telephone')));
			SESSION::write($this->sGroup . '.telephone2', StaticFunction::convert_zen_to_han_num(REQUEST::post_data('telephone2')));
			SESSION::write($this->sGroup . '.telephone3', StaticFunction::convert_zen_to_han_num(REQUEST::post_data('telephone3')));
			SESSION::write($this->sGroup . '.comment', REQUEST::post_data('comment'));

			// バリデーション
			$error_array = $this->checkSessionParameter();
			if (!StaticFunction::is_empty($error_array)) {
				SESSION::write($this->sGroup . '.error_array', $error_array);
				$this->redirect("/contact/");
			}
			
			$this->formReturn();
			return;
		}
		
		//POSTのないアクセスなのでindexへリダイレクト
		$this->redirect("/contact/");
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
	 * CREATE: 2016.10.16 aoyama
	 * *********************************** */
	public function complete() {
		
		//セッションがないのでTOPへリダイレクト
		if (StaticFunction::is_empty(SESSION::read($this->sGroup))) {
			$this->redirect("/contact/");
		}
		
		// バリデーション
		$error_array = $this->checkSessionParameter();
		if (!StaticFunction::is_empty($error_array)) {
			SESSION::write($this->sGroup . '.error_array', $error_array);
			$this->redirect("/contact/");
		}

		//すべて完了したのでメール送信
		$mail = new Mail();

		//登録者へのメール送信
		if (!$mail->send_contact($this->sGroup)) {
			LOGS_ERR('*** MAIL SEND FAILED. Contact Order ***');
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
	 * CREATE: 2016.10.16 aoyama
	 * *********************************** */
	private function checkSessionParameter() {

		$error_array = array();

		if (!InputVali::is_user_name(SESSION::read($this->sGroup . '.name1'))) {
			$error_array[] = array('target' => 'name1', 'message' => 'お名前(姓)を入力してください');
		}
		if (!InputVali::is_user_name(SESSION::read($this->sGroup . '.name2'))) {
			$error_array[] = array('target' => 'name2', 'message' => 'お名前(名)を入力してください');
		}

		if (!InputVali::is_user_name(SESSION::read($this->sGroup . '.kana1'))) {
			$error_array[] = array('target' => 'kana1', 'message' => 'ふりがな(姓)を入力してください');
		}
		if (!InputVali::is_user_name(SESSION::read($this->sGroup . '.kana2'))) {
			$error_array[] = array('target' => 'kana2', 'message' => 'ふりがな(名)を入力してください');
		}
		
		if (!InputVali::is_mailaddress(SESSION::read($this->sGroup . '.email'))) {
			$error_array[] = array('target' => 'email', 'message' => 'メールアドレスを入力してください');
		}

		if (!InputVali::is_prefecture(SESSION::read($this->sGroup . '.state'))) {
			$error_array[] = array('target' => 'state', 'message' => '都道府県を選択してください');
		}

		//電話番号チェック
		if (!InputVali::is_phone(StaticFunction::marge_phone(SESSION::read($this->sGroup . '.telephone'), SESSION::read($this->sGroup . '.telephone2'), SESSION::read($this->sGroup . '.telephone3')))) {
			$error_array[] = array('target' => 'tel', 'message' => '電話番号はハイフン無しの半角文字で入力して下さい。');
		}

		if (!InputVali::is_comment_contact(SESSION::read($this->sGroup . '.comment'))) {
			$error_array[] = array('target' => 'comment', 'message' => '質問内容を200文字以内で入力してください');
		}
		return $error_array;
	}

	/*	 * **********************************
	 * NAME:formReturn
	 * DESC:
	 *  セッション情報をフォームに渡すためにセットする機能
	 * NOTICE:
	 * CREATE: 2016.10.13 aoyama
	 * *********************************** */
	private function formReturn() {
		
		// セッションの情報をセットしてviewに渡す
		if (!StaticFunction::is_empty(SESSION::read($this->sGroup))) {
			$this->set("name1", SESSION::read($this->sGroup . '.name1'));
			$this->set("name2", SESSION::read($this->sGroup . '.name2'));
			$this->set("name_view", StaticFunction::marge_name(SESSION::read($this->sGroup . '.name1'), SESSION::read($this->sGroup . '.name2')));

			$this->set("kana1", SESSION::read($this->sGroup . '.kana1'));
			$this->set("kana2", SESSION::read($this->sGroup . '.kana2'));
			$this->set("kana_view", StaticFunction::marge_name(SESSION::read($this->sGroup . '.kana1'), SESSION::read($this->sGroup . '.kana2')));

			$this->set("email", SESSION::read($this->sGroup . '.email'));
			$this->set("state", SESSION::read($this->sGroup . '.state'));
			$this->set("telephone", SESSION::read($this->sGroup . '.telephone'));
			$this->set("telephone2", SESSION::read($this->sGroup . '.telephone2'));
			$this->set("telephone3", SESSION::read($this->sGroup . '.telephone3'));
			$this->set("telephone_view", StaticFunction::marge_phone(SESSION::read($this->sGroup . '.telephone'), SESSION::read($this->sGroup . '.telephone2'), SESSION::read($this->sGroup . '.telephone3')));

			$this->set("comment", SESSION::read($this->sGroup . '.comment'));
		}
		
	}

}

?>
