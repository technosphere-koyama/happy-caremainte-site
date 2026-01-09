<?php

/* * **********************************
 * NAME:CatalogController
 * DESC:
 * 		カタログお取り寄せページのコントローラー
 * NOTICE:
 * CREATE: 2016.10.17 aoyama
 * UPDATE: 2016.11.17 aoyama
 *		POST方式を変更
 * *********************************** */
class CatalogController extends PublicOpenControllerFrame {

	private $sGroup;
	private $magArray;

	/* Constructor */
	public function __construct() {
		parent::__construct();
		$this->sGroup = 'catalog';
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
		
		// ログイン中はログイン情報をviewiに渡す
		$login = new Login();
		if ($login->is_login()) {

			/* もしもAPIからのTELが連結されていた場合は分割（aoyama）*/
			$telArray = StaticFunction::phone_to_array(SESSION::read(CONF::read('LOGIN_CATEGORY.PUBLIC') . '.tel'));

			$this->set("name1", SESSION::read(CONF::read('LOGIN_CATEGORY.PUBLIC') . '.name1'));
			$this->set("name2", SESSION::read(CONF::read('LOGIN_CATEGORY.PUBLIC') . '.name2'));
			$this->set("kana1", SESSION::read(CONF::read('LOGIN_CATEGORY.PUBLIC') . '.kana1'));
			$this->set("kana2", SESSION::read(CONF::read('LOGIN_CATEGORY.PUBLIC') . '.kana2'));
			$this->set("zip", SESSION::read(CONF::read('LOGIN_CATEGORY.PUBLIC') . '.zip'));
			$this->set("state", SESSION::read(CONF::read('LOGIN_CATEGORY.PUBLIC') . '.state'));
			$this->set("addr1", SESSION::read(CONF::read('LOGIN_CATEGORY.PUBLIC') . '.addr1'));
			$this->set("addr2", SESSION::read(CONF::read('LOGIN_CATEGORY.PUBLIC') . '.addr2'));
			$this->set("addr3", SESSION::read(CONF::read('LOGIN_CATEGORY.PUBLIC') . '.addr3'));
			$this->set("birth_y", SESSION::read(CONF::read('LOGIN_CATEGORY.PUBLIC') . '.birth_y'));
			$this->set("birth_m", SESSION::read(CONF::read('LOGIN_CATEGORY.PUBLIC') . '.birth_m'));
			$this->set("birth_d", SESSION::read(CONF::read('LOGIN_CATEGORY.PUBLIC') . '.birth_d'));
			$this->set("telephone", StaticFunction::convert_zen_to_han_num($telArray[0]));
			$this->set("telephone2", StaticFunction::convert_zen_to_han_num($telArray[1]));
			$this->set("telephone3", StaticFunction::convert_zen_to_han_num($telArray[2]));
			$this->set("email", SESSION::read(CONF::read('LOGIN_CATEGORY.PUBLIC') . '.email'));

			$this->set("mag1_selected", 'checked');
			$this->set("mag2_selected", '');
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
			SESSION::write($this->sGroup . '.birth_y', REQUEST::post_data('birth_y'));
			SESSION::write($this->sGroup . '.birth_m', REQUEST::post_data('birth_m'));
			SESSION::write($this->sGroup . '.birth_d', REQUEST::post_data('birth_d'));

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
			SESSION::write($this->sGroup . '.email', REQUEST::post_data('email'));
			SESSION::write($this->sGroup . '.mag', REQUEST::post_data('mag'));

			// バリデーション
			$error_array = $this->checkSessionParameter();
			if (!StaticFunction::is_empty($error_array)) {
				SESSION::write($this->sGroup . '.error_array', $error_array);
				$this->redirect("/catalog/");
			}
			
			$this->formReturn();
			return;
		}
		
		//POSTのないアクセスなのでindexへリダイレクト
		$this->redirect("/catalog/");
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

		if (StaticFunction::is_empty(SESSION::read($this->sGroup))) {
			$this->redirect("/catalog/");
		}

		// バリデーション
		$error_array = $this->checkSessionParameter();
		if (!StaticFunction::is_empty($error_array)) {
			SESSION::write($this->sGroup . '.error_array', $error_array);
			$this->redirect("/catalog/");
		}

		//すべて完了したのでメール送信
		$mail = new Mail();

		//基幹システム、お客さま控えへのメール送信
		if (!$mail->send_catalog_add_complete($this->sGroup)) {
			LOGS_ERR('*** MAIL SEND FAILED. Catalog Order ***');
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

		//生年月日チェック
		if (!InputVali::is_birth_y(SESSION::read($this->sGroup . '.birth_y'))) {
			$error_array[] = array('target' => 'birth_y', 'message' => '生年を選択してください。');
		}
		if (!InputVali::is_month(SESSION::read($this->sGroup . '.birth_m'))) {
			$error_array[] = array('target' => 'birth_m', 'message' => '生月を選択してください。');
		}
		if (!InputVali::is_date(SESSION::read($this->sGroup . '.birth_d'))) {
			$error_array[] = array('target' => 'birth_d', 'message' => '生日を選択してください。');
		}
		//日付としての正当性チェック
		if (!InputVali::is_date_degit_8_str(StaticFunction::marge_birth(SESSION::read($this->sGroup . '.birth_y'), SESSION::read($this->sGroup . '.birth_m'), SESSION::read($this->sGroup . '.birth_d')))) {
			$error_array[] = array('target' => 'birth_y', 'message' => '生年月日は正しい値で入力してください。');
		}

		//住所チェック
		if (!InputVali::is_zip(SESSION::read($this->sGroup . '.zip'))) {
			$error_array[] = array('target' => 'zip', 'message' => '郵便番号は半角数字を入れてください。');
		}
		if (!InputVali::is_prefecture(SESSION::read($this->sGroup . '.state'))) {
			$error_array[] = array('target' => 'state', 'message' => '都道府県を選択してください');
		}
		if (!InputVali::is_municipality(SESSION::read($this->sGroup . '.addr1'))) {
			$error_array[] = array('target' => 'addr1', 'message' => '市区郡を入力してください。');
		}
		if (!InputVali::is_municipality(SESSION::read($this->sGroup . '.addr2'))) {
			$error_array[] = array('target' => 'addr2', 'message' => '町村・番地を入力してください。');
		}
		if (!StaticFunction::is_empty(SESSION::read($this->sGroup . '.addr3'))) {
			if (!InputVali::is_municipality(SESSION::read($this->sGroup . '.addr3'))) {
				$error_array[] = array('target' => 'addr3', 'message' => 'ビル・マンション名を入力してください。');
			}
		}

		//電話番号チェック
		if (!InputVali::is_phone(StaticFunction::marge_phone(SESSION::read($this->sGroup . '.telephone'), SESSION::read($this->sGroup . '.telephone2'), SESSION::read($this->sGroup . '.telephone3')))) {
			$error_array[] = array('target' => 'tel', 'message' => '電話番号はハイフン無しの半角文字で入力して下さい。');
		}

		//FAX番号（入力されている場合のみ）チェック
		if (!StaticFunction::is_empty(SESSION::read($this->sGroup . '.faxnum')) || !StaticFunction::is_empty(SESSION::read($this->sGroup . '.faxnum2')) || !StaticFunction::is_empty(SESSION::read($this->sGroup . '.faxnum3'))) {
			if (!InputVali::is_phone(StaticFunction::marge_phone(SESSION::read($this->sGroup . '.faxnum'), SESSION::read($this->sGroup . '.faxnum2'), SESSION::read($this->sGroup . '.faxnum3')))) {
				$error_array[] = array('target' => 'tel', 'message' => 'FAX番号はハイフン無しの半角文字で入力して下さい。');
			}
		}

		if (!InputVali::is_mailaddress(SESSION::read($this->sGroup . '.email'))) {
			$error_array[] = array('target' => 'email', 'message' => 'メールアドレスを入力してください');
		}

		if (!InputVali::is_array_value(SESSION::read($this->sGroup . '.mag'), CONF::read('MAILMAG'))) {
			$error_array[] = array('target' => 'mag', 'message' => 'メルマガ購読を選択してください');
		}

		return $error_array;
	}

	/*	 * **********************************
	 * NAME:formReturn
	 * DESC:
	 *  セッション情報をフォームに渡すためにセットする機能
	 * NOTICE:
	 * CREATE: 2016.10.13 aoyama
	 * UPDATE: 2016.11.18 aoyama
	 *		ログイン情報はindexで
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
			$this->set("birth_y", SESSION::read($this->sGroup . '.birth_y'));
			$this->set("birth_m", SESSION::read($this->sGroup . '.birth_m'));
			$this->set("birth_d", SESSION::read($this->sGroup . '.birth_d'));
			$this->set("birth_view", StaticFunction::marge_birth_for_view(SESSION::read($this->sGroup . '.birth_y'), SESSION::read($this->sGroup . '.birth_m'), SESSION::read($this->sGroup . '.birth_d')));
			$this->set("zip", SESSION::read($this->sGroup . '.zip'));
			$this->set("state", SESSION::read($this->sGroup . '.state'));
			$this->set("addr1", SESSION::read($this->sGroup . '.addr1'));
			$this->set("addr2", SESSION::read($this->sGroup . '.addr2'));
			$this->set("addr3", SESSION::read($this->sGroup . '.addr3'));
			$this->set("address_view", StaticFunction::marge_address_for_view(SESSION::read($this->sGroup . '.zip'), SESSION::read($this->sGroup . '.state'), SESSION::read($this->sGroup . '.addr1'), SESSION::read($this->sGroup . '.addr2'), SESSION::read($this->sGroup . '.addr3')));
			$this->set("telephone", SESSION::read($this->sGroup . '.telephone'));
			$this->set("telephone2", SESSION::read($this->sGroup . '.telephone2'));
			$this->set("telephone3", SESSION::read($this->sGroup . '.telephone3'));
			$this->set("telephone_view", StaticFunction::marge_phone(SESSION::read($this->sGroup . '.telephone'), SESSION::read($this->sGroup . '.telephone2'), SESSION::read($this->sGroup . '.telephone3')));
			$this->set("faxnum", SESSION::read($this->sGroup . '.faxnum'));
			$this->set("faxnum2", SESSION::read($this->sGroup . '.faxnum2'));
			$this->set("faxnum3", SESSION::read($this->sGroup . '.faxnum3'));
			if (!StaticFunction::is_empty(SESSION::read($this->sGroup . '.faxnum'))) {
				$this->set("faxnum_view", StaticFunction::marge_phone(SESSION::read($this->sGroup . '.faxnum'), SESSION::read($this->sGroup . '.faxnum2'), SESSION::read($this->sGroup . '.faxnum3')));
			} else {
				$this->set("faxnum_view", "");
			}
			$this->set("email", SESSION::read($this->sGroup . '.email'));
			$this->set("mag", SESSION::read($this->sGroup . '.mag'));
			$this->set("mag1_selected", (SESSION::read($this->sGroup . '.mag') == CONF::read('MAILMAG.1')) ? 'checked' : '');
			$this->set("mag2_selected", (SESSION::read($this->sGroup . '.mag') == CONF::read('MAILMAG.2')) ? 'checked' : '');
		}
	}

}

?>
