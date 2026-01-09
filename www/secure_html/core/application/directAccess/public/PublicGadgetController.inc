<?php

/* * **********************************
 * NAME:CatalogController
 * DESC:
 * 		カタログお取り寄せページのコントローラー
 * NOTICE:
 * CREATE: 2016.10.17 aoyama
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
		// POSTデータがある場合、セッションに登録する。
		if (!StaticFunction::is_empty(REQUEST::post_data())) {

			SESSION::write($this->sGroup . '.name1', REQUEST::post_data('name1'));
			SESSION::write($this->sGroup . '.name2', REQUEST::post_data('name2'));
			SESSION::write($this->sGroup . '.kana1', REQUEST::post_data('kana1'));
			SESSION::write($this->sGroup . '.kana2', REQUEST::post_data('kana2'));
			SESSION::write($this->sGroup . '.birth_y', REQUEST::post_data('birth_y'));
			SESSION::write($this->sGroup . '.birth_m', REQUEST::post_data('birth_m'));
			SESSION::write($this->sGroup . '.birth_d', REQUEST::post_data('birth_d'));

			SESSION::write($this->sGroup . '.zip', REQUEST::post_data('zip'));
			SESSION::write($this->sGroup . '.state', REQUEST::post_data('state'));
			SESSION::write($this->sGroup . '.addr1', REQUEST::post_data('addr1'));
			SESSION::write($this->sGroup . '.addr2', REQUEST::post_data('addr2'));
			SESSION::write($this->sGroup . '.addr3', REQUEST::post_data('addr3'));

			SESSION::write($this->sGroup . '.telephone', REQUEST::post_data('telephone'));
			SESSION::write($this->sGroup . '.telephone2', REQUEST::post_data('telephone2'));
			SESSION::write($this->sGroup . '.telephone3', REQUEST::post_data('telephone3'));
			SESSION::write($this->sGroup . '.faxnum', REQUEST::post_data('faxnum'));
			SESSION::write($this->sGroup . '.faxnum2', REQUEST::post_data('faxnum2'));
			SESSION::write($this->sGroup . '.faxnum3', REQUEST::post_data('faxnum3'));
			SESSION::write($this->sGroup . '.email', REQUEST::post_data('email'));
			SESSION::write($this->sGroup . '.mag', REQUEST::post_data('mag'));

			// バリデーション(confirmセッション消す)
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
	 *  入力確認画面用
	 *  セッションがあればとりあえず表示する
	 *  ここではバリデーション無し
	 * NOTICE:
	 * CREATE: 2016.10.16 aoyama
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
	 * CREATE: 2016.10.16 aoyama
	 * *********************************** */
	public function complete() {

		if (!StaticFunction::is_empty(SESSION::read($this->sGroup))) {

			/*
			 * バリデーション:エラーのときはindex.htmlに飛ばす
			 * indexのcheckSessionParameterとエラー情報の渡し方が異なる理由として
			 * ここでバリデーションに引っかかるということは予期しないアクセスなので
			 * そこまで親切にしなくてもいいかなと。
			 */
			$error_array = $this->checkSessionParameter();
			if (!StaticFunction::is_empty($error_array)) {
				$this->redirect("./");
			} else {

				/*
				 * API接続
				 */
				$api = new Rest();

				// 配列にPOSTデータを格納
				$param_array = array(
					"name1" => SESSION::read($this->sGroup . '.name1')."　".SESSION::read($this->sGroup . '.name2'),
					"kana1" => SESSION::read($this->sGroup . '.kana1')."　".SESSION::read($this->sGroup . '.kana2'),
					'email' => SESSION::read($this->sGroup . '.email'),
					"state" => SESSION::read($this->sGroup . '.state'),
					"tel" => SESSION::read($this->sGroup . '.telephone') . "-" . SESSION::read($this->sGroup . '.telephone2') . "-" . SESSION::read($this->sGroup . '.telephone3'),
					"comment" => SESSION::read($this->sGroup . '.comment')
				);
				/* APIへのPOSTレスポンスを格納 */
				$result = $api->catalog_add($param_array);

				/* API通信エラー */
				if (!$result) {
					$error_array[] = array("message" => "カタログ請求の登録通信に失敗しました。お手数をおかけしますが時間をおいて再度登録してください。");
					$this->set('error_array', $error_array);
					return;
				}

				/* 正常レスポンスの時は情報をセッションに入れる */
				if ($result["code"] != "200") {
					$error_array[] = array("message" => $result["message"]);
					$this->set('error_array', $error_array);
					return;
				}
				
				//すべて完了したのでメール送信
				$mail = new Mail();
				
				$birth = SESSION::read(CONF::read('LOGIN_CATEGORY.PUBLIC') . '.birth_y')."/";
				$birth .= SESSION::read(CONF::read('LOGIN_CATEGORY.PUBLIC') . '.birth_m')."/";
				$birth .= SESSION::read(CONF::read('LOGIN_CATEGORY.PUBLIC') . '.birth_d');
				
				$addr = SESSION::read($this->sGroup . '.state');
				$addr .= SESSION::read($this->sGroup . '.addr1');
				$addr .= SESSION::read($this->sGroup . '.addr2');
				$addr .= SESSION::read($this->sGroup . '.addr3');
				
				$tel = SESSION::read($this->sGroup . '.telephone') . "-";
				$tel .= SESSION::read($this->sGroup . '.telephone2') . "-";
				$tel .= SESSION::read($this->sGroup . '.telephone3');
				
				$fax = SESSION::read($this->sGroup . '.faxnum') . "-";
				$fax .= SESSION::read($this->sGroup . '.faxnum2') . "-";
				$fax .= SESSION::read($this->sGroup . '.faxnum3');

				if (!$mail->send_catalog_add_complete(
						SESSION::read($this->sGroup . '.name1'), SESSION::read($this->sGroup . '.kana1'), $birth,SESSION::read($this->sGroup . '.zip'),$addr, $tel, $fax, SESSION::read($this->sGroup . '.email'),CONF::read('MAILMAG.'.SESSION::read($this->sGroup . '.mag'))
					)
				) {
					LOGS_ERR('*** PASSWORD RESET ACCEPT MAIL SEND FAILED. ***');
					$this->set('alert', 'エラーが発生しました。お手数ですが、再度お試し下さい。');
					return;
				}
				
				//正常終了時はセッションを削除
				SESSION::delete($this->sGroup);
			}
		} else {
			$this->redirect("./");
		}
	}

	/*	 * **********************************
	 * NAME:checkSessionParameter
	 * DESC:
	 *  メルマガ登録専用のセッション情報バリデーション
	 * NOTICE:
	 * CREATE: 2016.10.16 aoyama
	 * *********************************** */
	private function checkSessionParameter() {

		$usermember = new UserPublicModel();
		$error_array = array();

		if (!InputVali::is_user_name(SESSION::read($this->sGroup . '.name1'))) {
			$error_array[] = array('target' => 'name1', 'message' => 'お名前を入力してください');
		}

		if (!InputVali::is_user_name(SESSION::read($this->sGroup . '.kana1'))) {
			$error_array[] = array('target' => 'kana1', 'message' => 'ふりがなを入力してください');
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

		if (!InputVali::is_zip(SESSION::read($this->sGroup . '.zip'))) {
			$error_array[] = array('target' => 'zip', 'message' => '郵便番号はハイフンを入れてください。');
		}
		
		if (!InputVali::is_prefecture(SESSION::read($this->sGroup . '.state'))) {
			$error_array[] = array('target' => 'state', 'message' => '都道府県を選択してください');
		}

		if (!InputVali::is_phone(SESSION::read($this->sGroup . '.telephone') . "-" . SESSION::read($this->sGroup . '.telephone2') . "-" . SESSION::read($this->sGroup . '.telephone3'))) {
			$error_array[] = array('target' => 'tel', 'message' => '電話番号はハイフン無しの半角文字で入力して下さい。');
		}

		if (!StaticFunction::is_empty(SESSION::read($this->sGroup . '.faxnum')) || !StaticFunction::is_empty(SESSION::read($this->sGroup . '.faxnum2')) || !StaticFunction::is_empty(SESSION::read($this->sGroup . '.faxnum3'))) {
			if (!InputVali::is_num(SESSION::read($this->sGroup . '.faxnum'), true, 1, 5) ||
				!InputVali::is_num(SESSION::read($this->sGroup . '.faxnum2'), true, 1, 5) ||
				!InputVali::is_num(SESSION::read($this->sGroup . '.faxnum3'), true, 1, 5)) {
				$error_array[] = array('target' => 'tel', 'message' => 'FAX番号はハイフン無しの半角文字で入力して下さい。');
			}
		}

		if (!InputVali::is_mailaddress(SESSION::read($this->sGroup . '.email'))) {
			$error_array[] = array('target' => 'email', 'message' => 'メールアドレスを入力してください');
		}

		if (!InputVali::is_num(SESSION::read($this->sGroup . '.mag'), true, 1, 2)) {
			$error_array[] = array('target' => 'mag', 'message' => 'メルマガ購読を選択してください');
		}



//		SESSION::delete($this->sGroup . '.confirm');

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

		//メルマガのステータス配列を取得
//		$this->magArray = CONF::read('MAILMAG');
		

		// セッションの情報をセットしてviewに渡す
		if (!StaticFunction::is_empty(SESSION::read($this->sGroup))) {
			$this->set("name1", SESSION::read($this->sGroup . '.name1'));
			$this->set("name2", SESSION::read($this->sGroup . '.name2'));
			$this->set("kana1", SESSION::read($this->sGroup . '.kana1'));
			$this->set("kana2", SESSION::read($this->sGroup . '.kana2'));
			$this->set("birth_y", SESSION::read($this->sGroup . '.birth_y'));
			$this->set("birth_m", SESSION::read($this->sGroup . '.birth_m'));
			$this->set("birth_d", SESSION::read($this->sGroup . '.birth_d'));
			$this->set("zip", SESSION::read($this->sGroup . '.zip'));
			$this->set("state", SESSION::read($this->sGroup . '.state'));
			$this->set("addr1", SESSION::read($this->sGroup . '.addr1'));
			$this->set("addr2", SESSION::read($this->sGroup . '.addr2'));
			$this->set("addr3", SESSION::read($this->sGroup . '.addr3'));
			$this->set("telephone", SESSION::read($this->sGroup . '.telephone'));
			$this->set("telephone2", SESSION::read($this->sGroup . '.telephone2'));
			$this->set("telephone3", SESSION::read($this->sGroup . '.telephone3'));
			$this->set("faxnum", SESSION::read($this->sGroup . '.faxnum'));
			$this->set("faxnum2", SESSION::read($this->sGroup . '.faxnum2'));
			$this->set("faxnum3", SESSION::read($this->sGroup . '.faxnum3'));
			$this->set("email", SESSION::read($this->sGroup . '.email'));
			$this->set("mag", SESSION::read($this->sGroup . '.mag'));
			$this->set("mag_view", CONF::read('MAILMAG.'.SESSION::read($this->sGroup . '.mag')));
			$this->set("mag1_selected", (SESSION::read($this->sGroup . '.mag') == 1) ? 'checked':'');
			$this->set("mag2_selected", (SESSION::read($this->sGroup . '.mag') == 2) ? 'checked':'');
			
			
		} else {

			//* ログイン中でmailmagセッションにも情報がなかった場合はログイン情報を配置
			$login = new Login();
			if ($login->is_login()) {

				/*
				 * もしもAPIからのTELが連結されていた場合は分割（aoyama）
				 */
				$telSplit = explode("-", SESSION::read(CONF::read('LOGIN_CATEGORY.PUBLIC') . '.tel'));

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
				$this->set("telephone", $telSplit[0]);
				$this->set("telephone2", $telSplit[1]);
				$this->set("telephone3", $telSplit[2]);
				$this->set("email", SESSION::read(CONF::read('LOGIN_CATEGORY.PUBLIC') . '.email'));
				
				$this->set("mag1_selected", 'checked');
				$this->set("mag2_selected", '');
			}
		}
		// フォームに渡し終わったのでセッションを消す
		// SESSION::delete($this->sGroup);
	}

}

?>
