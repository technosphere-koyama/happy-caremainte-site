<?php

/* * **********************************
 * NAME:PasswordReminderController
 * DESC:
 *  パスワード再設定画面コントローラ
 * NOTICE:
 * CREATE: 2016.11.8 aoyama
 * *********************************** */
class PasswordReminderController extends PublicOpenControllerFrame {

	private $sGroup;

	/* Constructor */
	public function __construct() {
		parent::__construct();
		$this->sGroup = 'PasswordReminder';
	}

	/*	 * **********************************
	 * NAME  : index
	 * INPUT : NONE
	 * OUTPUT: NONE
	 * DESC  :
	 * 		パスワード再発行手続き入力画面
	 * NOTICE:
	 * CREATE: 2016.11.8 aoyama
	 * *********************************** */
	public function index() {

		//未入力の場合はここで終了
		if (!REQUEST::is_post()) {
			return;
		}

		/* 入力がなければ終了 */
		if (StaticFunction::is_empty(REQUEST::post_data('user_id')) || StaticFunction::is_empty(REQUEST::post_data('email'))) {
			$error_array[] = array('target' => 'login', "message" => "IDとメールアドレスを入力して下さい。");
			$this->set('error_array', $error_array);
			return;
		}
		/* ハッシュチェック */
		if (REQUEST::post_data('token') != SESSION::read('EXPIRES.ORIGINAL_TOKEN')) {
			$error_array[] = array('target' => 'login', "message" => "IDとメールアドレスを入力して下さい。");
			$this->set('error_array', $error_array);
			return;
		}

		$api = new Rest();

		if (!$result = $api->get_user_password_reset(REQUEST::post_data('user_id'), REQUEST::post_data('email'))) {
			$error_array[] = array('target' => 'login', "message" => "通信エラーが発生しました。時間をおいて再度ご入力ください");
			$this->set('error_array', $error_array);
			return;
		}

		if ($result['code'] == "200") {

			$mail = new Mail();

			if ($mail->send_password_reset(REQUEST::post_data('email'), $result['password'])) {
				$this->redirect('./complete.html');
			}
			LOGS_ERR(REQUEST::post_data('email'));
			$this->set('alert', 'メール送信に失敗しました。');
			return;
		}

		$error_array[] = array('target' => 'login', "message" => "入力いただきましたID、またはメールアドレスが正しくないようです。<br />再度お確かめの上、入力してください。");
		$this->set('error_array', $error_array);
		return;
	}

	/*	 * **********************************
	 * NAME  : complete
	 * INPUT : NONE
	 * OUTPUT: NONE
	 * DESC  :
	 * 		パスワード再発行手続き完了画面
	 * NOTICE:
	 * CREATE: 2016.11.8 aoyama
	 * *********************************** */
	public function complete() {

		return;
	}

}

?>
