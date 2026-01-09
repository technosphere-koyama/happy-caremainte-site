<?php

/* * **********************************
 * NAME:LogIn
 * DESC:
 *  ログイン済みかどうか判定するクラス。
 *  セッションにログイン情報を保持しているか判定する。
 *  保持していない場合には、セッションをクリアして、ログイン画面を表示させる。
 * NOTICE:
 * CREATE: 2015.09.14 sonoda
 * UPDATE: 2015.09.19 hesaka 機能実装
 * *********************************** */
class Login {

	private $s_group;
	private $user_category;
	private $target_model;
	private $user_data;
	private $alert;
	private $is_locked = false;

	/*
	 * constructor
	 */
	public function __construct() {
		//デフォルトでPUBLICを設定しておく
		$this->set_target_model(CONF::read('LOGIN_CATEGORY.PUBLIC'));
	}

	/*	 * **********************************
	 * NAME  : set_user_category
	 * INPUT : user_category / string / ユーザの種類を示す文字列
	 * OUTPUT: none
	 * DESC  :
	 *  user_categoryにより、検索対象となるユーザテーブルを選択
	 * NOTICE:
	 *  モデルを読み替えて、後は同じ処理を行うので、モデルのメソッドの作りを
	 *  同じにしておかないとエラーとなる
	 * CREATE: 2015.09.18 hesaka
	 * UPDATE: 2015.11.24 hesaka セッションを、管理側とPUBLIC側で分けた(平行してログインできるようにするため)
	 * *********************************** */
	public function set_target_model($user_category) {
		$this->user_category = $user_category;
		$this->s_group = $user_category;
		switch ($this->user_category) {

			default:
				$this->target_model = new UserPublicModel();
				break;
		}
	}

	/*	 * **********************************
	 * NAME  : is_login
	 * INPUT : none
	 * OUTPUT: true / ログイン状態
	 *         false / ログアウト状態
	 * DESC  :
	 *  ユーザが現在ログイン状態かどうかを返す
	 * NOTICE:
	 * ------------------------------------
	 *  当該メソッドは、セッションを見て、ログインかどうかを判断するもので、
	 *  「ログイン認証」を行うものではない
	 * ------------------------------------
	 * CREATE: 2016.10.12 aoyama
	 * *********************************** */
	public function is_login() {

		/*
		 * セッションにユーザデータのuser_idがあるかどうかで判断する
		 */
		if (StaticFunction::is_empty(SESSION::read($this->s_group .".system_user_id"))) {
			//無ければログアウト状態
			return false;
		}
		
		//あればログイン状態
		return true;
	}

	/*	 * **********************************
	 * NAME  : is_sns_login
	 * INPUT : directory / string / viewのアクセス先ディレクトリ名
	 * OUTPUT: NONE
	 * DESC  :
	 * NOTICE:
	 * /core/application/directAccess/mypage/frame/MypageBaseCommonControllerFrame.inc
	 * から移植
	 * CREATE: 2016.11.5 aoyama
	 * *********************************** */
	public function is_sns_login() {
		if (StaticFunction::is_empty(SESSION::read(CONF::read('LOGIN_CATEGORY.PUBLIC') . ".user_id"))) {
			return false;
		} else {
			return true;
		}
	}
	
	/*	 * **********************************
	 * NAME  : session_verification
	 * INPUT : 
	 * OUTPUT: 
	 * DESC  :
	 *  is_loginのラッパー
	 * NOTICE:
	 * CREATE: 2016.10.12 aoyama
	 * *********************************** */
	public function session_verification() {

		return $this->is_login();
	}

	/*	 * **********************************
	 * NAME  : input_verification
	 * INPUT : mail_address / string / メールアドレス
	 *         password / string / パスワード 
	 * OUTPUT: true / 認証に成功
	 *         false / 認証に失敗
	 * DESC  :
	 *  引数のlogin_id, password指定があれば、ユーザ照合を行う
	 * NOTICE:
	 * CREATE: 2016.10.12 aoyama
	 * UPDATE: 2016.10.15 aoyama
	 *		API認証と同時にDB検索も実施。
	 *		DBになくてもとりあえずログイン成功させておいて
	 *		初回ログインページへリダイレクトさせる
	 * *********************************** */
	public function input_verification($syste_user_id,$password) {

		/*
		 * APIに投げてログイン認証を行う
		 */
		$api = new Rest();
		
		/* APIのレスポンスを格納 */
		$user_array = $api->user_login($syste_user_id,$password);
		
		/* API通信エラー */
		if(!$user_array) {
			return false;
		}
		
		/* 正常レスポンスの時は情報をセッションに入れる */
		if($user_array["code"] != "200") {
			LOGS_LOGIN('[input_verification] API ERR RESPONSE code=' . $user_array["code"]);
			$this->alert = $user_array["message"];
			return false;
		}
			
		//ここでいう「user_id」はDBの「system_user_id」にあたる。
		$this->set_session_data($user_array);
		LOGS_LOGIN('[input_verification] !!! API LOGIN SUCCESS !!! $syste_user_id=' . $user_array['user']['user_id']);

		//user_publicを検索して既に初回ログインが完了しているかチェック。
		$userPublic = new UserPublicModel();
		$sns_user = $userPublic->verification($user_array['user']['user_id']);

		if(StaticFunction::is_empty($sns_user)) {
			//初回ログインが住んでいないので何もせず（セッションにuser_id、system_idを入れず）に正常終了
			return true;
		}

		//完了している場合はセッションに「user_id、system_id」を登録
		SESSION::write($this->s_group . '.user_id', $sns_user[0]['user_id']);
		SESSION::write($this->s_group . '.system_id', $sns_user[0]['system_id']);
		SESSION::write($this->s_group . '.nickname', $sns_user[0]['nickname']);
		SESSION::write($this->s_group . '.role', $sns_user[0]['role']);
		SESSION::write($this->s_group . '.fashion_id', (int)$sns_user[0]['fashion_id']);
		SESSION::write($this->s_group . '.like_brand', $sns_user[0]['like_brand']);
		SESSION::write($this->s_group . '.comment', $sns_user[0]['comment']);
		
		/*
		 * スマホアプリ連携用
		 * スマホ用のtokenが路銀画面のhiddenに渡されるのでその値をDBに登録
		 * このレコードから通知のあるユーザーに対してRESTリクエストをなげてアプリに通知する。
		 * CREATE: 2016.11.17 aoyama
		 */
		//アンドロイドトークンが取得できた場合
		if(!StaticFunction::is_empty(REQUEST::post_data('android_device_token'))) {
			$android = new UserAndroidModel();
			$android->set($sns_user[0]['user_id'],REQUEST::post_data('android_device_token'));
		}
		//iOSトークンが取得できた場合
		if(!StaticFunction::is_empty(REQUEST::post_data('ios_device_token'))) {
			$ios = new UserIosModel();
			$ios->set($sns_user[0]['user_id'],REQUEST::post_data('ios_device_token'));
		}
		return true;
	}
	

	
	/*	 * **********************************
	 * NAME  : logout
	 * INPUT : none
	 * OUTPUT: none
	 * DESC  :
	 *  ログアウト処理を行う
	 * NOTICE:
	 *  処理は、セッションのログインユーザ情報を保持している部分をクリアすれば良い
	 * CREATE: 2015.09.28 hesaka
	 * *********************************** */
	public function logout() {
		SESSION::delete($this->s_group);
		return true;
	}

	/*	 * **********************************
	 * NAME  : is_locked
	 * INPUT : none
	 * OUTPUT: true / ロックされている状態
	 *         false / ロックされていない状態
	 * DESC  :
	 *  ユーザがロックされているかどうかを返す
	 * NOTICE:
	 * CREATE: 2015.11.24 hesaka
	 * *********************************** */
	public function is_locked() {
		//ユーザがロックされていたら、念のためセッションのUSERをクリアしてtrueを返す
		//ロックされていなければfalseを返す
		SESSION::delete($this->s_group);
		return $this->is_locked;
	}



	/*	 * **********************************
	 * NAME  : get_login_user_id
	 * INPUT : none
	 * OUTPUT: float / ログインユーザID
	 *         NULL / 無い場合
	 * DESC  :
	 *  ログイン中のユーザIDを返す
	 * NOTICE:
	 * CREATE: 2015.11.24 hesaka
	 * *********************************** */
	public function get_login_user_id() {

	}
	
	/*	 * **********************************
	 * NAME  : get_alert
	 * INPUT : none
	 * OUTPUT: string / アラート文字列
	 * DESC  :
	 *  ログイン認証に失敗した際のアラート内容を返す
	 * NOTICE:
	 *  アラート内容はユーザに見せる目的に使用するもの
	 * CREATE: 2015.11.24 hesaka
	 * *********************************** */
	public function get_alert() {
		return $this->alert;
	}

	/*	 * **********************************
	 * NAME  : set_session_data
	 * INPUT : $user_array
	 * OUTPUT: none
	 * DESC  :
	 *  認証に成功して取得したユーザ情報をセッションにセットする
	 * NOTICE:
	 * CREATE: 2016.10.12 aoyama
	 * UPDATE: 2016.11.4 aoyama
	 *		pass、last_login_time、create_timeを削除。
	 *		APIからも返却されないので必要な時は相談
	 *		パスワードもここでは取得せず、
	 *		再発行の要請があった場合のみAPI「getUserDetail」で取得する
	 * *********************************** */
	private function set_session_data($user_array) {
		
		//まずはクリア
		SESSION::delete($this->s_group);
		
		
		if(!StaticFunction::is_empty( $user_array['user']['name']) && !StaticFunction::is_empty( $user_array['user']['kana'])) {
			list($name1,$name2) = StaticFunction::name_to_array($user_array['user']['name']);
			list($kana1,$kana2) = StaticFunction::name_to_array($user_array['user']['kana']);
		} else {
			$name1 = $user_array['user']['name1'];
			$name2 = $user_array['user']['name2'];
			$kana1 = $user_array['user']['kana1'];
			$kana2 = $user_array['user']['kana2'];
		}
		
		//基幹システムから取得した情報をセット
		SESSION::write($this->s_group . '.system_user_id', $user_array['user']['user_id']);
		SESSION::write($this->s_group . '.name1', $name1);
		SESSION::write($this->s_group . '.name2', $name2);
		SESSION::write($this->s_group . '.kana1', $kana1);
		SESSION::write($this->s_group . '.kana2', $kana2);
		SESSION::write($this->s_group . '.tel', $user_array['user']['tel']);
		SESSION::write($this->s_group . '.email', $user_array['user']['email']);
		SESSION::write($this->s_group . '.email2', $user_array['user']['email2']);
		SESSION::write($this->s_group . '.zip', StaticFunction::format_zip_hyphen($user_array['user']['zip']) );
		SESSION::write($this->s_group . '.state', $user_array['user']['state']);
		SESSION::write($this->s_group . '.addr1', $user_array['user']['addr1']);
		SESSION::write($this->s_group . '.addr2', $user_array['user']['addr2']);
		SESSION::write($this->s_group . '.addr3', $user_array['user']['addr3']);
		SESSION::write($this->s_group . '.sex', $user_array['user']['sex']);
		SESSION::write($this->s_group . '.birth_y', (int)$user_array['user']['birth_y']);
		SESSION::write($this->s_group . '.birth_m', (int)$user_array['user']['birth_m']);
		SESSION::write($this->s_group . '.birth_d', (int)$user_array['user']['birth_d']);
		SESSION::write($this->s_group . '.wkbn', $user_array['user']['wkbn']);
//		SESSION::write($this->s_group . '.pass', $user_array['user']['pass']);
//		SESSION::write($this->s_group . '.last_login_time', $user_array['user']['last_login_time']);
//		SESSION::write($this->s_group . '.create_time', $user_array['user']['create_time']);
		SESSION::write($this->s_group . '.point', $user_array['user']['point']);
		SESSION::write($this->s_group . '.depo', $user_array['user']['depo']);

		//追加情報をセット
		SESSION::write($this->s_group . '.user_agent', USER_AGENT);
		SESSION::write($this->s_group . '.addr', $_SERVER['REMOTE_ADDR']);
	}


	public function redirect_login($url)
	{
		//ログインページへリダイレクト
		header('location: ' . CONF::read('URL_PUBLIC_ROOT') . '/login?callback=' . urlencode($url));
		exit();
	}
}

?>
