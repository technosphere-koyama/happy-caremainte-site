<?php

/* * **********************************
 * NAME:PasswordReset
 * DESC:
 *  パスワード再設定画面コントローラ
 * NOTICE:
 * CREATE: 2015.10.07 hesaka
 * *********************************** */

class PasswordResetController extends PublicOpenControllerFrame {

	private $sGroup;

	/* Constructor */

	public function __construct() {
		parent::__construct();
		$this->sGroup = 'PasswordReset';
	}

	/*	 * **********************************
	 * NAME  : index
	 * INPUT : NONE
	 * OUTPUT: NONE
	 * DESC  :
	 *  パスワード再設定手続き画面
	 * NOTICE:
	 * CREATE: 2015.10.13 hesaka
	 * UPDATE: 2015.12.08 hesaka アカウントロック解除機能も実装
	 * *********************************** */

	public function index() {

		//GETにkeyが付いていなければaccept画面へリダイレクト
		if (empty(REQUEST::get_data('t'))) {
			$this->redirect('accept.html');
		}

		//ハッシュをキーにユーザ情報を取得
		$eum = new UserMemberModel();
		$user_data = $eum->select(
			array(
			'system_id', 'login_id', 'password', 'name',
			'mail_address', 'pw_reset_accept_time', 'create_time'
			), array('WHERE' =>
			array('pw_reset_token' => DbCast::string(REQUEST::get_data('t')))
			)
		);
		//エラーの場合
		if ($eum->db_select_check_error($user_data)) {
			LOGS_ERR('user member select error mail=' . REQUEST::post_data('mail'));
			$this->set('alert', 'エラーが発生しました。');
			return;
		}

		/*
		 * 存在しなければタイムアウト画面へリダイレクト
		 * 不正アクセスとする画面へ飛ばそうかとも思うが、期限切れの場合にハッシュをクリアするので、
		 * メールに貼ったURLアクセスを２回するだけで不正アクセスと表示されるので、タイムアウト画面へのリダイレクトにしておく
		 */
		if ($eum->db_select_check_empty($user_data)) {
			LOGS_NOTICE('*** NOT FOUND URER *** SEARCH BY TOKEN=' . REQUEST::get_data('t'));
			SESSION::write($this->sGroup . '.timeout', true);
			$this->redirect('timeout.html');
		}

		//存在するけど期限切れの場合は、ハッシュと期限をクリアしてタイムアウト画面へリダイレクト
		if (strtotime($user_data[0]['pw_reset_accept_time']) + CONF::read('PASSWORD_RESET_TOKEN.EXPIRE') < time()) {
			$eum->update(
				array(
				'pw_reset_token' => DbCast::string(NULL),
				'pw_reset_accept_time' => DbCast::datetime(NULL)
				), array('WHERE' =>
				array('system_id' => DbCast::string($user_data[0]['system_id']))
				)
			);
			LOGS_NOTICE('*** TOKEN EXPIRE *** OVER TIME=' .
				(time() - strtotime($user_data[0]['pw_reset_accept_time']) + CONF::read('PASSWORD_RESET_TOKEN.EXPIRE')) . '(sec)');
			SESSION::write($this->sGroup . '.timeout', true);
			$this->redirect('timeout.html');
		}

		//画面表示用にユーザIDをセット
		$this->set('login_id', $user_data[0]['login_id']);

		/*
		 * パスワードをポストされた場合でも上記チェックは行う
		 * でないと、
		 * 画面に飛んできてしばらく放置された後でも変更できてしまう
		 * いきなりポストされるクラッキングを受けると通してしまう
		 * ため
		 */

		//未入力の場合はここで終了
		if (!REQUEST::is_post()) {
			return;
		}

		//バリデーションチェック
		$error_array = $this->check_request_parameter('index');
		if (!StaticFunction::is_empty($error_array)) {
			$error_str = '';
			foreach ($error_array as $value) {
				$error_str .= $value['message'] . '<br>';
			}
//			$this->set('first_alert_no_fade', $error_str);
			$this->set('alert', $error_str);
			return;
		}

		//入力値チェック
		if (empty(REQUEST::post_data('password')) || empty(REQUEST::post_data('password_check'))) {
			$this->set('alert', '入力して下さい。');
			return;
		}
		if (REQUEST::post_data('password') != REQUEST::post_data('password_check')) {
			$this->set('alert', 'パスワードが確認用と違っています。');
			return;
		}

		//パスワードを暗号化
		$pwd_hash = Encrypt::password_encrypt(REQUEST::post_data('password'), $user_data[0]['system_id'], $user_data[0]['create_time']);

		//現在のパスワードと同じかチェック
		if ($user_data[0]['password'] == $pwd_hash) {
			$this->set('alert', '前回と同じパスワードはご使用いただけません。ご注意ください。');
			return;
		}

		/*
		 * パスワードを更新
		 * 同時にハッシュと期限をクリア
		 * ※ログイン失敗カウントもクリア
		 * 　アカウントロックされた場合、パスワード再設定で解除するので
		 */
		if (!$eum->update(
				array(
				'password' =>
				DbCast::string(
					Encrypt::password_encrypt(
						REQUEST::post_data('password'), $user_data[0]['system_id'], $user_data[0]['create_time']
					)
				),
			    'pw_reset_token' => DbCast::string(NULL), 
			    'login_failed_count' => DbCast::integer(0), 
			    'pw_reset_accept_time' => DbCast::datetime(NULL),
			    'last_pw_reset_time' => DbCast::datetime(DbDateTime::get_cur_datetime())
			), 
			array('WHERE' => array('system_id' => DbCast::string($user_data[0]['system_id'])))
		)) {
			LOGS_ERR('*** PASSWORD UPDATE FAILED. *** system_id=' . $user_data[0]['system_id']);
			$this->set('alert', 'エラーが発生しました。お手数ですが、再度お試し下さい。');
			return;
		}

		//パスワード変更完了メール
		$mail = new Mail();
		if (!$mail->send_password_reset_complete(
				$user_data[0]['name'], $user_data[0]['mail_address'])
		) {
			LOGS_ERR('*** PASSWORD RESET COMPLETE MAIL SEND FAILED. ***');

			//メール送信には失敗したが、変更処理は成功したため、エラーログを吐くのみにして、後は成功処理と同じ動作を行う
		}

		//変更処理を行ったという証明をセッションに入れておく
		SESSION::write($this->sGroup . '.index', true);

		//完了画面へ遷移
		$this->redirect('complete.html');
	}

	/*	 * **********************************
	 * NAME  : complete
	 * INPUT : NONE
	 * OUTPUT: NONE
	 * DESC  :
	 *  パスワード再設定手続き画面
	 * NOTICE:
	 * CREATE: 2015.10.13 hesaka
	 * *********************************** */

	public function complete() {
		//indexから来たセッションが無ければindex画面へリダイレクト
		if (empty(SESSION::read($this->sGroup . '.index'))) {
			$this->redirect('index.html');
		}
		//セッションをクリアする
		SESSION::delete($this->sGroup . '.index');
	}

	/*	 * **********************************
	 * NAME  : timeout
	 * INPUT : NONE
	 * OUTPUT: NONE
	 * DESC  :
	 *  パスワード再設定ハッシュ期限切れ画面
	 * NOTICE:
	 *  再設定ハッシュを生成してから切られるタイムリミットを過ぎたら当該画面へ飛ばされる
	 * CREATE: 2015.10.13 hesaka
	 * *********************************** */

	public function timeout() {
		return;
		//再設定画面にてタイムアウトでリダイレクトされる際にセットされたセッションがなければリダイレクト
		if (empty(SESSION::read($this->sGroup . '.timeout'))) {
			$this->redirect('accept.html');
		}

		//トークンの有効期限を画面に表示するようにセット
		$this->set('expire', CONF::read('PASSWORD_RESET_TOKEN.EXPIRE') / 60);

		//セッションをクリアする
		SESSION::delete($this->sGroup . '.timeout');
	}

	/*	 * **********************************
	 * NAME  : accept
	 * INPUT : NONE
	 * OUTPUT: NONE
	 * DESC  :
	 *  パスワード再設定手続き受け付け画面
	 * NOTICE:
	 * CREATE: 2015.10.13 hesaka
	 * UPDATE: 2015.12.21 sonoda activeのメンバだけ受付可能にする。
	 * *********************************** */

	public function accept() {

		/*
		 * 生年月日セレクト用のリストを作成
		 */
		/* 生年月日はデザインにないので一旦コメントアウト
		  //年
		  $cur_year = date('Y');
		  $year_list = array();
		  for ($y = ($cur_year - 80); $y <= $cur_year; $y++) {
		  $year_list[] = $y;
		  }
		  $this->set('cur_year', $cur_year);
		  $this->set('year_list', $year_list);

		  //月
		  $month_list = array();
		  for ($m = 1; $m <= 12; $m++) {
		  $month_list[] = $m;
		  }
		  $this->set('cur_month', date('m'));
		  $this->set('month_list', $month_list);

		  //日
		  $day_list = array();
		  for ($d = 1; $d <= 31; $d++) {
		  $day_list[] = $d;
		  }
		  $this->set('cur_day', date('j'));
		  $this->set('day_list', $day_list);
		 */

		//未入力の場合はここで終了
		if (!REQUEST::is_post()) {
			return;
		}

		//☆バリデーション追加。
		$error_array = $this->check_request_parameter('accept');
		if (!StaticFunction::is_empty($error_array)) {
			$error_str = '';
			foreach ($error_array as $value) {
				$error_str .= $value['message'] . '<br>';
			}
//			$this->set('first_alert_no_fade', $error_str);
			$this->set('alert', $error_str);
			return;
		}

		//入力値ユーザの確認
		$eum = new UserMemberModel();
		$user_data = $eum->select(
			array('system_id', 'login_id', 'name', 'mail_address'), array('WHERE' => array(
				'login_id' => DbCast::string(REQUEST::post_data('id')),
				'active' => DbCast::float(DB_ACTIVE_ON)/* ,
			  'birth_date' => DbCast::datetime(
			  DbDateTime::get_datetime_by_part(
			  REQUEST::post_data('year'),
			  REQUEST::post_data('month'),
			  REQUEST::post_data('date')
			  )
			  )
			 */
			))
		);
		//エラーの場合
		if ($eum->db_select_check_error($user_data)) {
			LOGS_ERR('user member select error login_id=' . REQUEST::post_data('id')/* . 
				  ', birth_year=' . REQUEST::post_data('year') .
				  ', birth_month=' . REQUEST::post_data('month') .
				  ', birth_day=' . REQUEST::post_data('date') */);
			$this->set('alert', 'エラーが発生しました。');
			return;
		}

		//存在しない場合は、その旨表示して終了
		if ($eum->db_select_check_empty($user_data)) {
			LOGS_NOTICE('not found user login_id=' . REQUEST::post_data('id')/* . 
				  ', birth_year=' . REQUEST::post_data('year') .
				  ', birth_month=' . REQUEST::post_data('month') .
				  ', birth_day=' . REQUEST::post_data('date') */);
			$this->set('alert', 'ユーザが見つかりません。');
			return;
		}

		//ハッシュ生成
		$datetime = DbDateTime::get_cur_datetime();
		$token = Encrypt::password_reset_token($user_data[0]['system_id'], $datetime);

		//存在した場合は、期限とハッシュをユーザレコードにセット
		if (!$eum->update(
				array(
				'pw_reset_token' => DbCast::string($token),
				'pw_reset_accept_time' => DbCast::datetime($datetime)
				), array('WHERE' =>
				array('system_id' => DbCast::string($user_data[0]['system_id']))
				)
			)) {
			LOGS_ERR('*** PASSWORD RESET TOKEN SET FAILED. ***');
			$this->set('alert', 'エラーが発生しました。お手数ですが、再度お試し下さい。');
			return;
		}

		//再設定画面URLにGETでハッシュをつけてメール
		$mail = new Mail();
		if (!$mail->send_password_reset_accept(
				$user_data[0]['name'], $user_data[0]['mail_address'], $token)
		) {
			LOGS_ERR('*** PASSWORD RESET ACCEPT MAIL SEND FAILED. ***');
			$this->set('alert', 'エラーが発生しました。お手数ですが、再度お試し下さい。');
			return;
		}

		LOGS_NOTICE('*** PASSWORD RESET ACCEPT MAIL SEND FAILED. ***');

		//受け付けでの処理を行ったという証明をセッションに入れておく
		SESSION::write($this->sGroup . '.accept', true);

		//受け付け完了画面へ遷移
		$this->redirect('accept_complete.html');
	}

	/*	 * **********************************
	 * NAME  : accept_complete
	 * INPUT : NONE
	 * OUTPUT: NONE
	 * DESC  :
	 *  パスワード再設定手続き受け付け完了画面
	 * NOTICE:
	 * CREATE: 2015.10.13 hesaka
	 * *********************************** */

	public function accept_complete() {
		//acceptから来たセッションが無ければaccept画面へリダイレクト
		if (empty(SESSION::read($this->sGroup . '.accept'))) {
			$this->redirect('accept.html');
		}

		//トークンの有効期限を画面に表示するようにセット
		$this->set('expire', CONF::read('PASSWORD_RESET_TOKEN.EXPIRE') / 60);

		//セッションをクリアする
		SESSION::delete($this->sGroup . '.accept');
	}

	/*	 * **********************************
	 * NAME:check_request_parameter
	 * INPUT: $page / string / チェック対象ページ
	 * OUTPUT: error_array / array / エラー内容を記載した配列
	 * DESC:
	 *  パスワードリセット画面で使用するPOSTリクエストに対するバリデーション
	 * NOTICE:
	 * CREATE: 2015.12.07 sonoda
	 * *********************************** */

	private function check_request_parameter($page) {

		$error_array = array();

		switch ($page) {
			case 'index':
				if (!InputVali::is_password(REQUEST::post_data('password'))) {
					$error_array[] = array('target' => 'password', 'message' => 'パスワード:' . InputVali::get_error_message());
				}
				if (REQUEST::post_data('password') != REQUEST::post_data('password_check')) {
					$error_array[] = array('target' => 'password_check', 'message' => 'パスワード（確認用）:パスワードが一致しません');
				}
				if (REQUEST::post_data('password') == REQUEST::post_data('id')) {
					$error_array[] = array('target' => 'password', 'message' => '会員IDと同様のパスワードは設定できません');
				}
				break;

			case 'accept':
				if (!InputVali::is_login_id(REQUEST::post_data('id'))) {
					$error_array[] = array('target' => 'id', 'message' => '会員ID:' . InputVali::get_error_message());
				}
				break;

			default :
				break;
		}

		return $error_array;
	}

}

?>
