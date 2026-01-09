<?php

/* * **********************************
 * NAME:MypageRegistrationController
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
 * 		基幹システム情報の更新
 * 
 * NOTICE:
 * CREATE: 2016.11.15 aoyama
 * *********************************** */
class MypageRegistrationController extends MypageBaseCommonControllerFrame {

	private $sGroup;
	private $public_user_data;

	/* Constructor */
	public function __construct() {

		parent::__construct();
		$this->sGroup = "edit_user";

		//ファッション系統の配列を取得してvuewに渡す
		$fashionMaster = new FashionTypeMasterModel();
		$this->fashionMasterArray = $fashionMaster->get_basic_data();
		$this->set("fashionTypeArray", $this->fashionMasterArray);

		//セッションからユーザ情報を取得
		$this->public_user_data = SESSION::read(CONF::read('LOGIN_CATEGORY.PUBLIC'));
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
	 * *********************************** */
	public function index() {

		// 初期情報をセット
		/*
		 * もしもAPIからのTELが連結されていた場合は分割（aoyama）
		 */
		$telArray = StaticFunction::phone_to_array(SESSION::read(CONF::read('LOGIN_CATEGORY.PUBLIC') . '.tel'));

		$this->set("name1", SESSION::read(CONF::read('LOGIN_CATEGORY.PUBLIC') . '.name1'));
		$this->set("name2", SESSION::read(CONF::read('LOGIN_CATEGORY.PUBLIC') . '.name2'));
		//$this->set("kana1", SESSION::read(CONF::read('LOGIN_CATEGORY.PUBLIC') . '.kana1'));
		//$this->set("kana2", SESSION::read(CONF::read('LOGIN_CATEGORY.PUBLIC') . '.kana2'));
		$this->set("telephone", $telArray[0]);
		$this->set("telephone2", $telArray[1]);
		$this->set("telephone3", $telArray[2]);
		$this->set("email", SESSION::read(CONF::read('LOGIN_CATEGORY.PUBLIC') . '.email'));
		//$this->set("email2", SESSION::read(CONF::read('LOGIN_CATEGORY.PUBLIC') . '.email2'));
		$this->set("zip", SESSION::read(CONF::read('LOGIN_CATEGORY.PUBLIC') . '.zip'));
		$this->set("state", SESSION::read(CONF::read('LOGIN_CATEGORY.PUBLIC') . '.state'));
		$this->set("addr1", SESSION::read(CONF::read('LOGIN_CATEGORY.PUBLIC') . '.addr1'));
		$this->set("addr2", SESSION::read(CONF::read('LOGIN_CATEGORY.PUBLIC') . '.addr2'));
		$this->set("addr3", SESSION::read(CONF::read('LOGIN_CATEGORY.PUBLIC') . '.addr3'));

		if (!StaticFunction::is_empty(SESSION::read($this->sGroup . '.error_array'))) {
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
		if (!StaticFunction::is_empty(REQUEST::post_data())) {

			SESSION::write($this->sGroup . '.name1', REQUEST::post_data('name1'));
			SESSION::write($this->sGroup . '.name2', REQUEST::post_data('name2'));
			//SESSION::write($this->sGroup . '.kana1', REQUEST::post_data('kana1'));
			//SESSION::write($this->sGroup . '.kana2', REQUEST::post_data('kana2'));
			SESSION::write($this->sGroup . '.telephone', REQUEST::post_data('telephone'));
			SESSION::write($this->sGroup . '.telephone2', REQUEST::post_data('telephone2'));
			SESSION::write($this->sGroup . '.telephone3', REQUEST::post_data('telephone3'));
			SESSION::write($this->sGroup . '.email', REQUEST::post_data('email'));
			//SESSION::write($this->sGroup . '.email2', REQUEST::post_data('email2'));
			SESSION::write($this->sGroup . '.zip', REQUEST::post_data('zip'));
			SESSION::write($this->sGroup . '.state', REQUEST::post_data('state'));
			SESSION::write($this->sGroup . '.addr1', REQUEST::post_data('addr1'));
			SESSION::write($this->sGroup . '.addr2', REQUEST::post_data('addr2'));
			SESSION::write($this->sGroup . '.addr3', REQUEST::post_data('addr3'));

			// バリデーション
			$error_array = $this->checkSessionParameter();
			if (!StaticFunction::is_empty($error_array)) {
				SESSION::write($this->sGroup . '.error_array', $error_array);
				$this->redirect("/mypage/registration/");
			}

			$this->formReturn();
			return;
		}

		//POSTのないアクセスなのでindexへリダイレクト
		$this->redirect("/mypage/registration/");
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

		//セッションがないのでTOPへリダイレクト
		if (StaticFunction::is_empty(SESSION::read($this->sGroup))) {
			$this->redirect("/mypage/registration/");
		}
		
		// バリデーション
		$error_array = $this->checkSessionParameter();
		if (!StaticFunction::is_empty($error_array)) {
			SESSION::write($this->sGroup . '.error_array', $error_array);
			$this->redirect("/mypage/registration/");
		}
		
		//メール送信インスタンス
		$mail = new Mail();

		//古いユーザー情報をセット
		$old_array = array(
			"name" => StaticFunction::marge_name($this->public_user_data['name1'], $this->public_user_data['name2']),
			"zip" => $this->public_user_data['zip'],
			"state" => $this->public_user_data['state'],
			"addr1" => $this->public_user_data['addr1'],
			"addr2" => $this->public_user_data['addr2'],
			"addr3" => $this->public_user_data['addr3'],
			"tel" => $this->public_user_data['tel'],
			"email" => $this->public_user_data['email']
		);
		
		//新しいユーザー情報をセット
		$user_array = array(
			"name" => StaticFunction::marge_name(SESSION::read($this->sGroup . '.name1'), SESSION::read($this->sGroup . '.name2')),
			"zip" => SESSION::read($this->sGroup . '.zip'),
			"state" => SESSION::read($this->sGroup . '.state'),
			"addr1" => SESSION::read($this->sGroup . '.addr1'),
			"addr2" => SESSION::read($this->sGroup . '.addr2'),
			"addr3" => SESSION::read($this->sGroup . '.addr3'),
			"tel" => StaticFunction::marge_phone(SESSION::read($this->sGroup . '.telephone'), SESSION::read($this->sGroup . '.telephone2'), SESSION::read($this->sGroup . '.telephone3')),
			"email" => SESSION::read($this->sGroup . '.email')
		);
		
		//メール送信処理
		if (!$mail->send_core_user_edit($old_array, $user_array)) {
			LOGS_ERR('*** PASSWORD RESET ACCEPT MAIL SEND FAILED. ***');
			$this->set('alert', 'エラーが発生しました。お手数ですが、再度お試し下さい。');
			return;
		}

		// 更新したのでセッションに登録している情報を上書き
		SESSION::write(CONF::read('LOGIN_CATEGORY.PUBLIC') . '.name1', SESSION::read($this->sGroup . '.name1'));
		SESSION::write(CONF::read('LOGIN_CATEGORY.PUBLIC') . '.name2', SESSION::read($this->sGroup . '.name2'));
		//SESSION::write(CONF::read('LOGIN_CATEGORY.PUBLIC') . '.kana1', SESSION::read($this->sGroup . '.kana1'));
		//SESSION::write(CONF::read('LOGIN_CATEGORY.PUBLIC') . '.kana2', SESSION::read($this->sGroup . '.kana2'));
		SESSION::write(CONF::read('LOGIN_CATEGORY.PUBLIC') . '.tel', StaticFunction::marge_phone(SESSION::read($this->sGroup . '.telephone'), SESSION::read($this->sGroup . '.telephone2'), SESSION::read($this->sGroup . '.telephone3')));
		SESSION::write(CONF::read('LOGIN_CATEGORY.PUBLIC') . '.email', SESSION::read($this->sGroup . '.email'));
		//SESSION::write(CONF::read('LOGIN_CATEGORY.PUBLIC') . '.email2', SESSION::read($this->sGroup . '.email2'));
		SESSION::write(CONF::read('LOGIN_CATEGORY.PUBLIC') . '.zip', SESSION::read($this->sGroup . '.zip'));
		SESSION::write(CONF::read('LOGIN_CATEGORY.PUBLIC') . '.state', SESSION::read($this->sGroup . '.state'));
		SESSION::write(CONF::read('LOGIN_CATEGORY.PUBLIC') . '.addr1', SESSION::read($this->sGroup . '.addr1'));
		SESSION::write(CONF::read('LOGIN_CATEGORY.PUBLIC') . '.addr2', SESSION::read($this->sGroup . '.addr2'));
		SESSION::write(CONF::read('LOGIN_CATEGORY.PUBLIC') . '.addr3', SESSION::read($this->sGroup . '.addr3'));
		
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

		$error_array = array();

		if (!InputVali::is_user_name(SESSION::read($this->sGroup . '.name1'))) {
			$error_array[] = array('target' => 'name1', 'message' => '姓を入力してください');
		}
		if (!InputVali::is_user_name(SESSION::read($this->sGroup . '.name2'))) {
			$error_array[] = array('target' => 'name2', 'message' => '名を入力してください');
		}

//		if (!InputVali::is_user_name(SESSION::read($this->sGroup . '.kana1'))) {
//			$error_array[] = array('target' => 'kana1', 'message' => '姓（ふりがな）を入力してください');
//		}
//		if (!InputVali::is_user_name(SESSION::read($this->sGroup . '.kana2'))) {
//			$error_array[] = array('target' => 'kana2', 'message' => '名（ふりがな）を入力してください');
//		}


		if (!InputVali::is_num(SESSION::read($this->sGroup . '.telephone'), true, 1, 5) ||
			!InputVali::is_num(SESSION::read($this->sGroup . '.telephone2'), true, 1, 5) ||
			!InputVali::is_num(SESSION::read($this->sGroup . '.telephone3'), true, 1, 5)) {
			$error_array[] = array('target' => 'tel', 'message' => '電話番号はハイフン無しの半角文字で入力して下さい。');
		}

		if (!InputVali::is_mailaddress(SESSION::read($this->sGroup . '.email'))) {
			$error_array[] = array('target' => 'email', 'message' => 'メールアドレスを入力してください');
		}
//		if (!StaticFunction::is_empty(SESSION::read($this->sGroup . '.email2'))) {
//			if (!InputVali::is_mailaddress(SESSION::read($this->sGroup . '.email2'))) {
//				$error_array[] = array('target' => 'email2', 'message' => 'サブメールアドレスを正しいメールアドレスで入力してください');
//			}
//		}

		if (!InputVali::is_zip(SESSION::read($this->sGroup . '.zip'))) {
			$error_array[] = array('target' => 'zip', 'message' => '郵便番号は半角数字を入れてください。');
		}
		if (!InputVali::is_prefecture(SESSION::read($this->sGroup . '.state'))) {
			$error_array[] = array('target' => 'state', 'message' => '都道府県:' . InputVali::get_error_message());
		}

		if (!InputVali::is_municipality(SESSION::read($this->sGroup . '.addr1'))) {
			$error_array[] = array('target' => 'addr1', 'message' => '市区郡を入力してください。');
		}
		if (!InputVali::is_municipality(SESSION::read($this->sGroup . '.addr2'))) {
			$error_array[] = array('target' => 'addr2', 'message' => '町村・番地を入力してください。');
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
//			$this->set("kana1", SESSION::read($this->sGroup . '.kana1'));
//			$this->set("kana2", SESSION::read($this->sGroup . '.kana2'));
			$this->set("telephone", SESSION::read($this->sGroup . '.telephone'));
			$this->set("telephone2", SESSION::read($this->sGroup . '.telephone2'));
			$this->set("telephone3", SESSION::read($this->sGroup . '.telephone3'));
			$this->set("telephone_view", StaticFunction::marge_phone(SESSION::read($this->sGroup . '.telephone'), SESSION::read($this->sGroup . '.telephone2'), SESSION::read($this->sGroup . '.telephone3')));
			$this->set("email", SESSION::read($this->sGroup . '.email'));
//			$this->set("email2", SESSION::read($this->sGroup . '.email2'));
			$this->set("zip", SESSION::read($this->sGroup . '.zip'));
			$this->set("state", SESSION::read($this->sGroup . '.state'));
			$this->set("addr1", SESSION::read($this->sGroup . '.addr1'));
			$this->set("addr2", SESSION::read($this->sGroup . '.addr2'));
			$this->set("addr3", SESSION::read($this->sGroup . '.addr3'));
		}
	}

}

?>
