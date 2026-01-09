<?php

/* * **********************************
 * NAME:MypagePasswordController
 * DESC:
 *  マイページ(共通)_パスワード変更用のコントローラ
 *  完了画面に遷移せずに、アラートで完了した旨を表示する。
 * NOTICE:
 * CREATE: 2015.09.14 sonoda
 * UPDATE: 2016.09.14 hesaka 継承する親フレームをCloseCommonに変更
 * *********************************** */
class MypagePasswordController extends MypageCloseCommonControllerFrame {

	private $sGroup;
	private $public_user_data;

	/* Constructor */
	public function __construct() {
		parent::__construct();
		$this->sGroup = 'mypage';
		//セッションからユーザ情報を取得
		$this->public_user_data = SESSION::read(CONF::read('LOGIN_CATEGORY.PUBLIC'));
	}

	/*	 * **********************************
	 * NAME  : password
	 * INPUT : NONE
	 * OUTPUT: NONE
	 * DESC  :
	 * マイページの共通管理 パスワード入力画面に実行されるメソッド
	 * NOTICE:
	 * CREATE: 2016.07.20 sonoda　ワイヤ作成
	 * *********************************** */
	public function password() {

		/*
		 * POST要求がなければ、なにもしない。
		 */
		if (!REQUEST::is_post()) {
			if (!StaticFunction::is_empty(SESSION::read('alert_error'))) {
				$this->set('alert_error', SESSION::read('alert_error'));
				SESSION::delete('alert_error');
			}
			if (!StaticFunction::is_empty(SESSION::read('alert_comp'))) {
				$this->set('alert_comp', SESSION::read('alert_comp'));
				SESSION::delete('alert_comp');
			}
			return;
		}

		/*
		 * 変更するボタンが押下された時の処理
		 */
		SESSION::write($this->sGroup . '.password_old', REQUEST::post_data('password_old'));
		SESSION::write($this->sGroup . '.password', REQUEST::post_data('password'));
		SESSION::write($this->sGroup . '.password2', REQUEST::post_data('password2'));
		$error_array = $this->check_session_parameter();

		//エラーの場合、エラー文言をセットしてリダイレクト。
		if (!StaticFunction::is_empty($error_array)) {
			SESSION::write('alert_error', $error_array);
			SESSION::delete($this->sGroup);
			$this->redirect(URL_FULL);
		}

		//DBの保存値とチェック
		//暗号化をかけて、DBと同一かチェック
		//ハッシュをキーにユーザ情報を取得
		$eum = new UserPublicModel();
		$user_data = $eum->select(
			array(
			'system_id', 'password', 'create_time', 'mail_address'
			), array('WHERE' =>
			array('user_id' => DbCast::string($this->public_user_data['user_id']))
			)
		);

		$pwd_hash_old = Encrypt::password_encrypt(REQUEST::post_data('password_old'), $user_data[0]['system_id'], $user_data[0]['create_time']);
		if ($user_data[0]['password'] != $pwd_hash_old) {
			$this->set('alert_error', ALERT::set_text('現在のパスワードが正しくありません。'));
			return;
		}

		$pwd_hash = Encrypt::password_encrypt(REQUEST::post_data('password'), $user_data[0]['system_id'], $user_data[0]['create_time']);

		if ($user_data[0]['password'] == $pwd_hash) {
			$this->set('alert_error', ALERT::set_text('現在登録されているパスワードとは異なるパスワードを入力してください。'));
			return;
		}

		//ここまでこれば、成功パスなのでDBに保存
		$update_list = array('password' => DbCast::string($pwd_hash));
		$condition = array(
			'WHERE' => array(
				'user_id' => $this->public_user_data['user_id']
			)
		);
		$eum->update($update_list, $condition);

		//ログイン処理を行っておく
		$login = new Login();

		//対象となるターゲットユーザモデルを指定
		$login->set_target_model(CONF::read('LOGIN_CATEGORY.PUBLIC'));

		//認証を行う(入力値の空チェックも中で行う)
		if (!$login->input_verification(
				$user_data[0]['mail_address'], REQUEST::post_data('password')
			)) {
			//アカウントがロックされていた場合、パスワード再発行画面へリダイレクト
			if ($login->is_locked()) {
//				$this->redirect(CONF::read('URL_PUBLIC_ROOT') . 'accountlock' . DS);
				//ロックされていない場合はアラートセットして終了
			} else {
				$this->set('alert_list', ALERT::set_text($login->get_alert()));
			}
			return;
		}

		//ログイン認証に成功
		//受付での処理を行ったという証明をセッションに入れておく
		SESSION::write('alert_comp', ALERT::set_text('パスワードを更新しました。'));
		SESSION::delete($this->sGroup);

		//F5対策としてトップへリダイレクト
		$this->redirect('index.html');
	}

	/*	 * **********************************
	 * NAME:check_session_parameter
	 * INPUT: $page_type / string / ページのタイプ
	 * DESC:
	 *  マイページで使用するセッション情報バリデーション
	 *  マイページでは様々なフォームが存在するので、
	 *  適応させるフォームをページごとに分類する。
	 * NOTICE:
	 * CREATE: 2015.12.06 sonoda
	 * *********************************** */
	private function check_session_parameter() {

		$error_array = array();

		if (!InputVali::is_req(SESSION::read($this->sGroup . '.password_old'))) {
			$error_array[] = ALERT::set_array('現在のパスワードを入力してください。', 'password');
		}
		if (!InputVali::is_password(SESSION::read($this->sGroup . '.password'))) {
			$error_array[] = ALERT::set_array(InputVali::get_error_message(), 'password');
		}
		if (SESSION::read($this->sGroup . '.password') != SESSION::read($this->sGroup . '.password2')) {
			$error_array[] = ALERT::set_array('パスワードが一致しません', 'password');
		}
		if (SESSION::read($this->sGroup . '.password') == SESSION::read(CONF::read('LOGIN_CATEGORY.PUBLIC') . '.mail_address')) {
			$error_array[] = ALERT::set_array('メールアドレスと同様のパスワードは設定できません', 'password');
		}

		return $error_array;
	}

}

?>
