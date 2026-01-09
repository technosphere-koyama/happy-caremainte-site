<?php

/* * **********************************
 * NAME:InternalApiCloseControllerFrame
 * DESC:
 *  管理画面などクローズドな環境に用いるAPI用コントローラのフレームとなる
 * NOTICE:
 *  ApiControllerCoreクラスを継承し、__construct()に子クラス名を
 *  渡し、Coreでログ出力などに使用してもらう
 * 
 *  コントローラの継承構造設計は、
 *  ApiController
 *  ↓
 *  ApiControllerFrame
 *  ↓
 *  ApiControllerCore
 *  となる
 * CREATE: 2015.10.04 hesaka
 * UPDATE: 2016.07.27 hesaka エラー判定をis_errorフラグ方式からApiErrorMessageMap方式へ
 * *********************************** */
class InternalApiCloseControllerFrame extends ApiControllerCore {

	/* * **********************************
	 * NAME  : __construct
	 * INPUT : NONE
	 * OUTPUT: NONE
	 * DESC  :
	 *  管理画面などクローズドな環境に用いる
	 *  API用コントローラフレームのコンストラクタ
	 *  下記内容を処理する
	 *  
	 *  ・コアの起動
	 *  ・セッションスタート
	 *  ・各種認証(verification)など
	 *  ・言語判定
	 * NOTICE:
	 * --------------------------------------
	 *  当該フレーム定義に必要な認証は
	 *  コントローラではなくここで行う
	 * --------------------------------------
	 * CREATE: 2015.xx.xx hesaka
	 * *********************************** */
	public function __construct() {

		if (CONF::read('DEBUG_BAR.IS_ACTIVE')) DebugBarMaster::start_measure('controller_constructor', '【FRAME_CONSTRUCTOR】');
		
		/*
		 * セッション スタート
		 */
		SESSION::start();
		
		//子クラス名をControllerCoreに渡す
		parent::__construct(get_class($this));

		/*
		 * エラーメッセージ スタンバイ
		 * ※CURRENT_LANGUAGE define後にロードする必要が出たためここで
		 */
		$this->stand_by_error_message();

		/*
		 * http,httpsアクセスチェック
		 * ※どちらで制限するかはCONFIG設定による
		 */
		if (CONF::read('SSL_REDIRECT.IS_ACTIVE') === true) {
			$irc = new SslRedirect();
			//指定ポートでなければ、エラー内容を出力し終了する
			if ($irc->verification() !== true) {
				print $this->get_error_message(API_ERR_RESTRICT_PROTOCOL);
				exit;
			}	
		}

		/*
		 * IP制限機能ONの場合、リストをチェックし
		 * 当てはまらない場合は指定URLへリダイレクト
		 */
		if (CONF::read('IP_RESTRICT.IS_ACTIVE') === true) {
			$irc = new IpAddressRestrict();
			//許可されなければ、エラー内容を出力し終了する
			if (!$irc->verification()) {
				print $this->get_error_message(API_ERR_RESTRICT_IP);
				exit;
			}
		}
		
		/*
		 * ログイン認証
		 */
		if (CONF::read('LOGIN.IS_ACTIVE') === true) {
			$login = new Login();
			//対象となるターゲットユーザモデルを指定
			$login->set_target_model(CONF::read('LOGIN_CATEGORY.SYSTEM'));
			//ログイン中かセッションにある値で認証
			//ログインできていなければ、エラー内容を出力し終了する
			if (!$login->session_verification()) {
				print $this->get_error_message(API_ERR_AUTH_FAILED);
				exit;
			}
		}

		if (CONF::read('DEBUG_BAR.IS_ACTIVE')) DebugBarMaster::stop_measure('controller_constructor');
	}

}

?>
