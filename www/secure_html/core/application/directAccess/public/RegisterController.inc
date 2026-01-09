<?php

/* * **********************************
 * NAME:RegisterController
 * DESC:
 *  
 * NOTICE:
 *  exec()は不要なため作成しない
 * CREATE: 2016.10.13 aoyama
 * UPDATE: 2016.11.18 aoyama
 *		ログインしているときはマイページにリダイレクト
 * *********************************** */
error_reporting(E_ALL);
ini_set('display_errors', 1);
class RegisterController extends PublicOpenControllerFrame {

	private $sGroup;
	private $fashionMasterArray;

	/* Constructor */
	public function __construct() {
		parent::__construct();
		$this->sGroup = 'regist';

		//ファッション系統の配列を取得してvuewに渡す
		$fashionMaster = new FashionTypeMasterModel();
		$this->fashionMasterArray = $fashionMaster->get_basic_data();
		$this->set("fashionTypeArray", $this->fashionMasterArray);

		//ログインしていればリダイレクト
		$login = new Login();
		if ($login->is_login()) {
			$this->redirect("/mypage/");
		}
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
	 * UPDATE: 2016.10.18 aoyama
	 * 		アバター設定
	 * *********************************** */
	public function index() {
		
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
	 * CREATE: 2016.10.13 aoyama
	 * *********************************** */
	public function confirm() {
		// POSTデータがあるのでセッションに登録しておく
		if (!StaticFunction::is_empty(REQUEST::post_data())) {

			SESSION::write($this->sGroup . '.name1', REQUEST::post_data('name1'));
			SESSION::write($this->sGroup . '.name2', REQUEST::post_data('name2'));
			SESSION::write($this->sGroup . '.kana1', REQUEST::post_data('kana1'));
			SESSION::write($this->sGroup . '.kana2', REQUEST::post_data('kana2'));
			SESSION::write($this->sGroup . '.telephone', StaticFunction::convert_zen_to_han_num(REQUEST::post_data('telephone')));
			SESSION::write($this->sGroup . '.telephone2', StaticFunction::convert_zen_to_han_num(REQUEST::post_data('telephone2')));
			SESSION::write($this->sGroup . '.telephone3', StaticFunction::convert_zen_to_han_num(REQUEST::post_data('telephone3')));
			SESSION::write($this->sGroup . '.email', REQUEST::post_data('email'));
			SESSION::write($this->sGroup . '.email2', REQUEST::post_data('email2'));
			SESSION::write($this->sGroup . '.zip', StaticFunction::convert_zen_to_han_num(REQUEST::post_data('zip')));
			SESSION::write($this->sGroup . '.state', REQUEST::post_data('state'));
			SESSION::write($this->sGroup . '.addr1', REQUEST::post_data('addr1'));
			SESSION::write($this->sGroup . '.addr2', REQUEST::post_data('addr2'));
			SESSION::write($this->sGroup . '.addr3', REQUEST::post_data('addr3'));
			SESSION::write($this->sGroup . '.sex', REQUEST::post_data('sex'));
			SESSION::write($this->sGroup . '.birth_y', REQUEST::post_data('birth_y'));
			SESSION::write($this->sGroup . '.birth_m', REQUEST::post_data('birth_m'));
			SESSION::write($this->sGroup . '.birth_d', REQUEST::post_data('birth_d'));
			SESSION::write($this->sGroup . '.wkbn', REQUEST::post_data('wkbn'));
			SESSION::write($this->sGroup . '.pass', REQUEST::post_data('pass'));

			// バリデーション
			$error_array = $this->checkSessionParameter();
			if (!StaticFunction::is_empty($error_array)) {
				SESSION::write($this->sGroup . '.error_array', $error_array);
				$this->redirect("/entry/");
			}
			
			$this->formReturn();
			return;
		}
		
		//POSTのないアクセスなのでindexへリダイレクト
		$this->redirect("/entry/");
	}

	/*	 * **********************************
	 * NAME  : send
	 * INPUT : 
	 * OUTPUT: 
	 * DESC  : 
	 *  入力完了画面用
	 *  処理フロー
	 * 	ーーーーーーーーーー
	 * 	1)会員登録API「addUser」にPOST
	 * 	2)新規IDをもって「input_verification」メソッド実行
	 * 		→ここでセッションに基幹システムデータを登録
	 * 	3)SNS登録用のDBリクエスト発行
	 * 	4)SNS情報をセッションにも追記
	 * 	5)すべて完了したのでメール送信
	 * 	ーーーーーーーーーー
	 * 
	 * NOTICE:
	 *  DB登録処理あり（セッションバリデーションあり）
	 *  この時点ではまだ仮登録状態
	 * CREATE: 2015.11.27 aoyama
	 * UPDATE: 2016.10.4 aoyama
	 * 		登録内容を調整（login_id）など
	 * *********************************** */
	public function complete() {

		if (StaticFunction::is_empty(SESSION::read($this->sGroup))) {
			$this->redirect("/entry/");
		}

		// バリデーション
		$error_array = $this->checkSessionParameter();
		if (!StaticFunction::is_empty($error_array)) {
			SESSION::write($this->sGroup . '.error_array', $error_array);
			$this->redirect("/entry/");
		}

		// 登録情報の配列格納
		$user_array = array(
			"name" => StaticFunction::marge_name(SESSION::read($this->sGroup . '.name1'), SESSION::read($this->sGroup . '.name2')),
			"kana" => StaticFunction::marge_name(SESSION::read($this->sGroup . '.kana1'), SESSION::read($this->sGroup . '.kana2')),
			"tel" => StaticFunction::marge_phone(SESSION::read($this->sGroup . '.telephone'), SESSION::read($this->sGroup . '.telephone2'), SESSION::read($this->sGroup . '.telephone3')),
			"email" => SESSION::read($this->sGroup . '.email'),
			"email2" => SESSION::read($this->sGroup . '.email2'),
			"zip" => SESSION::read($this->sGroup . '.zip'),
			"state" => SESSION::read($this->sGroup . '.state'),
			"addr1" => SESSION::read($this->sGroup . '.addr1'),
			"addr2" => SESSION::read($this->sGroup . '.addr2'),
			"addr3" => SESSION::read($this->sGroup . '.addr3'),
			"pass" => SESSION::read($this->sGroup . '.pass'),
			"birth" => StaticFunction::marge_birth(SESSION::read($this->sGroup . '.birth_y'),SESSION::read($this->sGroup . '.birth_m'),SESSION::read($this->sGroup . '.birth_d')),
			"sex" => SESSION::read($this->sGroup . '.sex'),
			"wkbn" => SESSION::read($this->sGroup . '.wkbn')
		);

		// 基幹システムへメール送信
		$mail = new Mail();
		if (!$mail->send_core_system_regist($user_array)) {
			LOGS_ERR('*** 会員登録でエラーが発生しました ***');
			$this->set('alert', 'エラーが発生しました。お手数ですが、再度お試し下さい。');
			return;
		}

		// メール内容をDBに保存
		$url = Conf::read('REST_API.BASE_URL') . "/preRegistVisitor";
		$this->curl_api_post($url, $user_array);

		// お客様控えメール送信
		/*
		if (!$mail->send_user_regist($user_array)) {
			LOGS_ERR('*** PASSWORD RESET ACCEPT MAIL SEND FAILED. ***');
			$this->set('alert', 'エラーが発生しました。お手数ですが、再度お試し下さい。');
			return;
		}
		 */

		//登録用セッションを削除
		SESSION::delete($this->sGroup);

		$this->set('result', "complete");
		return;
	}

	/*	 * **********************************
	 * NAME:checkSessionParameter
	 * DESC:
	 *  セッション情報バリデーション
	 * NOTICE:
	 * CREATE: 2016.10.3 aoyama
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

		//電話番号チェック
		if (!InputVali::is_phone(StaticFunction::marge_phone(SESSION::read($this->sGroup . '.telephone'), SESSION::read($this->sGroup . '.telephone2'), SESSION::read($this->sGroup . '.telephone3')))) {
			$error_array[] = array('target' => 'tel', 'message' => '電話番号はハイフン無しの半角文字で入力して下さい。');
		}

		if (!InputVali::is_mailaddress(SESSION::read($this->sGroup . '.email'))) {
			$error_array[] = array('target' => 'email', 'message' => 'メールアドレスを入力してください');
		}
		if (!StaticFunction::is_empty(SESSION::read($this->sGroup . '.email2'))) {
			if (!InputVali::is_mailaddress(SESSION::read($this->sGroup . '.email2'))) {
				$error_array[] = array('target' => 'email2', 'message' => 'サブメールアドレスを正しいメールアドレスで入力してください');
			}
		}
//
//		if (!InputVali::is_zip(SESSION::read($this->sGroup . '.zip'))) {
//			$error_array[] = array('target' => 'zip', 'message' => '郵便番号はハイフンを入れてください。');
//		}
//		if (!InputVali::is_prefecture(SESSION::read($this->sGroup . '.state'))) {
//			$error_array[] = array('target' => 'state', 'message' => '都道府県:' . InputVali::get_error_message());
//		}
//
//		if (!InputVali::is_municipality(SESSION::read($this->sGroup . '.addr1'))) {
//			$error_array[] = array('target' => 'addr1', 'message' => '市区郡を入力してください。');
//		}
//		if (!InputVali::is_municipality(SESSION::read($this->sGroup . '.addr2'))) {
//			$error_array[] = array('target' => 'addr2', 'message' => '町村・番地を入力してください。');
//		}

		if (!InputVali::is_sex_val(SESSION::read($this->sGroup . '.sex'))) {
			$error_array[] = array('target' => 'sex', 'message' => '性別を選択してください');
		}
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
//
//		if (!InputVali::is_job(SESSION::read($this->sGroup . '.wkbn'))) {
//			$error_array[] = array('target' => 'wkbn', 'message' => '職業を選択してください');
//		}

		if (!InputVali::is_password(SESSION::read($this->sGroup . '.pass'))) {//5～8文字
			$error_array[] = array('target' => 'pass', 'message' => 'パスワードを半角英数の5～8文字で入力してください');
		}
		
		return $error_array;
	}

	/*	 * **********************************
	 * NAME:formReturn
	 * DESC:
	 *  セッション情報をフォームに渡すためにセットする機能
	 * NOTICE:
	 * CREATE: 2015.11.27 aoyama
	 * *********************************** */
	private function formReturn() {

		// POSTデータがないので「戻るボタン」の可能性。setしそのまま表示

		$this->set("name1", SESSION::read($this->sGroup . '.name1'));
		$this->set("name2", SESSION::read($this->sGroup . '.name2'));
		$this->set("name_view", StaticFunction::marge_name(SESSION::read($this->sGroup . '.name1'),SESSION::read($this->sGroup . '.name2')));
		$this->set("kana1", SESSION::read($this->sGroup . '.kana1'));
		$this->set("kana2", SESSION::read($this->sGroup . '.kana2'));
		$this->set("kana_view", StaticFunction::marge_name(SESSION::read($this->sGroup . '.kana1'),SESSION::read($this->sGroup . '.kana2')));
		$this->set("telephone", SESSION::read($this->sGroup . '.telephone'));
		$this->set("telephone2", SESSION::read($this->sGroup . '.telephone2'));
		$this->set("telephone3", SESSION::read($this->sGroup . '.telephone3'));
		$this->set("telephone_view", StaticFunction::marge_phone(SESSION::read($this->sGroup . '.telephone'),SESSION::read($this->sGroup . '.telephone2'),SESSION::read($this->sGroup . '.telephone3')));
		$this->set("email", SESSION::read($this->sGroup . '.email'));
		$this->set("email2", SESSION::read($this->sGroup . '.email2'));
		$this->set("zip", SESSION::read($this->sGroup . '.zip'));
		$this->set("state", SESSION::read($this->sGroup . '.state'));
		$this->set("addr1", SESSION::read($this->sGroup . '.addr1'));
		$this->set("addr2", SESSION::read($this->sGroup . '.addr2'));
		$this->set("addr3", SESSION::read($this->sGroup . '.addr3'));
		$this->set("address_view", StaticFunction::marge_address_for_view(SESSION::read($this->sGroup . '.zip'), SESSION::read($this->sGroup . '.state'), SESSION::read($this->sGroup . '.addr1'), SESSION::read($this->sGroup . '.addr2'), SESSION::read($this->sGroup . '.addr3')));
		$this->set("sex", SESSION::read($this->sGroup . '.sex'));
		$this->set("birth_y", SESSION::read($this->sGroup . '.birth_y'));
		$this->set("birth_m", SESSION::read($this->sGroup . '.birth_m'));
		$this->set("birth_d", SESSION::read($this->sGroup . '.birth_d'));
		$this->set("birth_view", StaticFunction::marge_birth_for_view(SESSION::read($this->sGroup . '.birth_y'), SESSION::read($this->sGroup . '.birth_m'), SESSION::read($this->sGroup . '.birth_d')));
		$this->set("wkbn", SESSION::read($this->sGroup . '.wkbn'));
		$this->set("pass", SESSION::read($this->sGroup . '.pass'));
		$this->set("pass_mask", StaticFunction::changePasswordText(SESSION::read($this->sGroup . '.pass')));
		
		/*
		 * 会員登録方式の変更によりコメントアウト
		 */
//		$this->set("tmp_avatar", SESSION::read($this->sGroup . '.tmp_avatar'));
//		$this->set("tmp_avatar_date", SESSION::read($this->sGroup . '.tmp_avatar_date'));
//		$this->set("nickname", SESSION::read($this->sGroup . '.nickname'));
//		$this->set("fashion_id", SESSION::read($this->sGroup . '.fashion_id'));
//		if (!StaticFunction::is_empty(SESSION::read($this->sGroup . '.fashion_id'))) {
//			$this->set("fashion_id_view", $this->fashionMasterArray[SESSION::read($this->sGroup . '.fashion_id')]);
//		}
//		$this->set("like_brand", SESSION::read($this->sGroup . '.like_brand'));
//		$this->set("comment", SESSION::read($this->sGroup . '.comment'));
	}

	/**
	 * CURLでAPIと通信する（POST)
	 *
	 * @param string $url
	 * @param array $post_data
	 * @return void
	 */
	private function curl_api_post($url, $post_data) {
		// cURLセッションを初期化
		$ch = curl_init();

		// オプションを設定
		curl_setopt($ch, CURLOPT_URL, $url); // 取得するURLを指定
		curl_setopt($ch, CURLOPT_POST, TRUE);
        curl_setopt($ch, CURLOPT_POSTFIELDS, http_build_query($post_data));
        curl_setopt($ch, CURLOPT_SSL_VERIFYPEER, FALSE);  // オレオレ証明書対策
        curl_setopt($ch, CURLOPT_SSL_VERIFYHOST, FALSE);  // 
        curl_setopt($ch, CURLOPT_RETURNTRANSFER, TRUE);
        curl_setopt($ch, CURLOPT_COOKIEJAR, 'cookie');
        curl_setopt($ch, CURLOPT_COOKIEFILE, 'tmp');
        curl_setopt($ch, CURLOPT_FOLLOWLOCATION, TRUE); // Locationヘッダを追跡

		// URLの情報を取得
		$response =  curl_exec($ch);

		$res = json_decode($response, true);

		return $res;
	}


}

?>
