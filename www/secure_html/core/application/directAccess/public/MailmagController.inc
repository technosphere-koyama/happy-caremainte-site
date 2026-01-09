<?php

/* * **********************************
 * NAME:MailmagController
 * DESC:
 * 		メルマガ登録ページのコントローラー
 * NOTICE:
 *  exec()は不要なため作成しない
 * CREATE: 2016.10.13 aoyama
 * UPDATE: 2016.11.17 aoyama
 *		POST方式を変更
* *********************************** */
class MailmagController extends PublicOpenControllerFrame {

	private $sGroup;

	/* Constructor */
	public function __construct() {
		parent::__construct();
		$this->sGroup = 'mailmag';
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
	 * CREATE: 2016.10.13 aoyama
	 * UPDATE: 2016.11.14 aoyama
	 * *********************************** */
	public function index() {

		// ログイン中はログイン情報を配置
		$login = new Login();
		if ($login->is_login()) {

			/*
			 * もしもAPIからのTELが連結されていた場合は分割（aoyama）
			 */
			$telSplit = explode("-", SESSION::read(CONF::read('LOGIN_CATEGORY.PUBLIC') . '.tel'));

			$this->set("name1", SESSION::read(CONF::read('LOGIN_CATEGORY.PUBLIC') . '.name1'));
			$this->set("name2", SESSION::read(CONF::read('LOGIN_CATEGORY.PUBLIC') . '.name2'));
			$this->set("email", SESSION::read(CONF::read('LOGIN_CATEGORY.PUBLIC') . '.email'));
			$this->set("zip", SESSION::read(CONF::read('LOGIN_CATEGORY.PUBLIC') . '.zip'));
			$this->set("state", SESSION::read(CONF::read('LOGIN_CATEGORY.PUBLIC') . '.state'));
			$this->set("addr1", SESSION::read(CONF::read('LOGIN_CATEGORY.PUBLIC') . '.addr1'));
			$this->set("addr2", SESSION::read(CONF::read('LOGIN_CATEGORY.PUBLIC') . '.addr2'));
			$this->set("addr3", SESSION::read(CONF::read('LOGIN_CATEGORY.PUBLIC') . '.addr3'));
			$this->set("telephone", $telSplit[0]);
			$this->set("telephone2", $telSplit[1]);
			$this->set("telephone3", $telSplit[2]);
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
	 * CREATE: 2016.10.14 aoyama
	 * *********************************** */
	public function confirm() {
		// POSTデータがないので「戻るボタン」の可能性。setしそのまま表示
		
		// POSTデータがある場合、セッションに登録する。
		if (!StaticFunction::is_empty(REQUEST::post_data())) {

			SESSION::write($this->sGroup . '.name1', REQUEST::post_data('name1'));
			SESSION::write($this->sGroup . '.name2', REQUEST::post_data('name2'));
			SESSION::write($this->sGroup . '.email', REQUEST::post_data('email'));
			SESSION::write($this->sGroup . '.zip', StaticFunction::convert_zen_to_han_num(REQUEST::post_data('zip')));
			SESSION::write($this->sGroup . '.state', REQUEST::post_data('state'));
			SESSION::write($this->sGroup . '.addr1', REQUEST::post_data('addr1'));
			SESSION::write($this->sGroup . '.addr2', REQUEST::post_data('addr2'));
			SESSION::write($this->sGroup . '.addr3', REQUEST::post_data('addr3'));
			SESSION::write($this->sGroup . '.telephone', StaticFunction::convert_zen_to_han_num(REQUEST::post_data('telephone')));
			SESSION::write($this->sGroup . '.telephone2', StaticFunction::convert_zen_to_han_num(REQUEST::post_data('telephone2')));
			SESSION::write($this->sGroup . '.telephone3', StaticFunction::convert_zen_to_han_num(REQUEST::post_data('telephone3')));
			SESSION::write($this->sGroup . '.faxnum', StaticFunction::convert_zen_to_han_num(REQUEST::post_data('faxnum')));
			SESSION::write($this->sGroup . '.faxnum2', StaticFunction::convert_zen_to_han_num(REQUEST::post_data('faxnum2')));
			SESSION::write($this->sGroup . '.faxnum3', StaticFunction::convert_zen_to_han_num(REQUEST::post_data('faxnum3')));

			// バリデーション
			$error_array = $this->checkSessionParameter();
			if (!StaticFunction::is_empty($error_array)) {
				SESSION::write($this->sGroup . '.error_array', $error_array);
				$this->redirect("/mailmag/");
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
	 * CREATE: 2016.10.14 aoyama
	 * *********************************** */
	public function complete() {

		if (StaticFunction::is_empty(SESSION::read($this->sGroup))) {
			$this->redirect("/mailmag/");
		}

		// バリデーション
		$error_array = $this->checkSessionParameter();
		if (!StaticFunction::is_empty($error_array)) {
			SESSION::write($this->sGroup . '.error_array', $error_array);
			$this->redirect("/mailmag/");
		}

		//すべて完了したのでメール送信(管理者、お客様控えを送信している)
		$mail = new Mail();
		
		if (!$mail->send_mailmag_add_complete($this->sGroup)) {
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
	 * CREATE: 2016.10.14 aoyama
	 * *********************************** */
	private function checkSessionParameter() {

		$usermember = new UserPublicModel();
		$error_array = array();

		if (!InputVali::is_user_name(SESSION::read($this->sGroup . '.name1'))) {
			$error_array[] = array('target' => 'name1', 'message' => 'お名前(姓)を入力してください');
		}
		if (!InputVali::is_user_name(SESSION::read($this->sGroup . '.name2'))) {
			$error_array[] = array('target' => 'name2', 'message' => 'お名前(名)を入力してください');
		}

		if (!InputVali::is_mailaddress(SESSION::read($this->sGroup . '.email'))) {
			$error_array[] = array('target' => 'email', 'message' => 'メールアドレスを入力してください');
		}

		if (!StaticFunction::is_empty(SESSION::read($this->sGroup . '.zip'))) {
			if (!InputVali::is_zip(SESSION::read($this->sGroup . '.zip'))) {
				$error_array[] = array('target' => 'zip', 'message' => '郵便番号はハイフンを入れてください。');
			}
		}

		if (!StaticFunction::is_empty(SESSION::read($this->sGroup . '.state'))) {
			if (!InputVali::is_prefecture(SESSION::read($this->sGroup . '.state'))) {
				$error_array[] = array('target' => 'state', 'message' => '都道府県:' . InputVali::get_error_message());
			}
		}
		if (!StaticFunction::is_empty(SESSION::read($this->sGroup . '.addr1'))) {
			if (!InputVali::is_municipality(SESSION::read($this->sGroup . '.addr1'))) {
				$error_array[] = array('target' => 'addr1', 'message' => '市区郡を入力してください。');
			}
		}
		if (!StaticFunction::is_empty(SESSION::read($this->sGroup . '.addr2'))) {
			if (!InputVali::is_municipality(SESSION::read($this->sGroup . '.addr2'))) {
				$error_array[] = array('target' => 'addr2', 'message' => '町村・番地を入力してください。');
			}
		}
		if (
			!StaticFunction::is_empty(SESSION::read($this->sGroup . '.telephone')) ||
			!StaticFunction::is_empty(SESSION::read($this->sGroup . '.telephone2')) ||
			!StaticFunction::is_empty(SESSION::read($this->sGroup . '.telephone3'))
		) {
			if (!InputVali::is_phone(SESSION::read($this->sGroup . '.telephone') . "-" . SESSION::read($this->sGroup . '.telephone2') . "-" . SESSION::read($this->sGroup . '.telephone3'))) {
				$error_array[] = array('target' => 'tel', 'message' => '電話番号はハイフン無しの半角文字で入力して下さい。');
			}
		}

		if (
			!StaticFunction::is_empty(SESSION::read($this->sGroup . '.faxnum')) ||
			!StaticFunction::is_empty(SESSION::read($this->sGroup . '.faxnum2')) ||
			!StaticFunction::is_empty(SESSION::read($this->sGroup . '.faxnum3'))
		) {
			if (!InputVali::is_phone(SESSION::read($this->sGroup . '.faxnum') . "-" . SESSION::read($this->sGroup . '.faxnum2') . "-" . SESSION::read($this->sGroup . '.faxnum3'))) {
				$error_array[] = array('target' => 'tel', 'message' => 'FAX番号はハイフン無しの半角文字で入力して下さい。');
			}
		}
		return $error_array;
	}

	/*	 * **********************************
	 * NAME:formReturn
	 * DESC:
	 *  セッション情報をフォームに渡すためにセットする機能
	 * NOTICE:
	 * CREATE: 2015.11.27 aoyama
	 * UPDATE: 2016.10.13 aoyama
	 * *********************************** */
	private function formReturn() {

		// セッションの情報をセットしてviewに渡す
		if (!StaticFunction::is_empty(SESSION::read($this->sGroup))) {
			$this->set("name1", SESSION::read($this->sGroup . '.name1'));
			$this->set("name2", SESSION::read($this->sGroup . '.name2'));
			$this->set("name_view", StaticFunction::marge_name(SESSION::read($this->sGroup . '.name1'), SESSION::read($this->sGroup . '.name2')));
			$this->set("email", SESSION::read($this->sGroup . '.email'));
			$this->set("zip", SESSION::read($this->sGroup . '.zip'));
			$this->set("state", SESSION::read($this->sGroup . '.state'));
			$this->set("addr1", SESSION::read($this->sGroup . '.addr1'));
			$this->set("addr2", SESSION::read($this->sGroup . '.addr2'));
			$this->set("addr3", SESSION::read($this->sGroup . '.addr3'));
			if (!StaticFunction::is_empty(SESSION::read($this->sGroup . '.zip'))) {
				$this->set("address_view", StaticFunction::marge_address_for_view(SESSION::read($this->sGroup . '.zip'), SESSION::read($this->sGroup . '.state'), SESSION::read($this->sGroup . '.addr1'), SESSION::read($this->sGroup . '.addr2'), SESSION::read($this->sGroup . '.addr3')));
			} else {
				$this->set("address_view", "");
			}

			$this->set("telephone", SESSION::read($this->sGroup . '.telephone'));
			$this->set("telephone2", SESSION::read($this->sGroup . '.telephone2'));
			$this->set("telephone3", SESSION::read($this->sGroup . '.telephone3'));
			if (!StaticFunction::is_empty(SESSION::read($this->sGroup . '.telephone'))) {
				$this->set("telephone_view", StaticFunction::marge_phone(SESSION::read($this->sGroup . '.telephone'), SESSION::read($this->sGroup . '.telephone2'), SESSION::read($this->sGroup . '.telephone3')));
			} else {
				$this->set("telephone_view", "");
			}
			$this->set("faxnum", SESSION::read($this->sGroup . '.faxnum'));
			$this->set("faxnum2", SESSION::read($this->sGroup . '.faxnum2'));
			$this->set("faxnum3", SESSION::read($this->sGroup . '.faxnum3'));
			if (!StaticFunction::is_empty(SESSION::read($this->sGroup . '.faxnum'))) {
				$this->set("faxnum_view", StaticFunction::marge_phone(SESSION::read($this->sGroup . '.faxnum'), SESSION::read($this->sGroup . '.faxnum2'), SESSION::read($this->sGroup . '.faxnum3')));
			} else {
				$this->set("faxnum_view", "");
			}
		}
	}

}

?>
