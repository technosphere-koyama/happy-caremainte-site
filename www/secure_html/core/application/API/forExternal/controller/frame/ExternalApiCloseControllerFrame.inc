<?php

/* * **********************************
 * NAME:ExternalApiCloseControllerFrame
 * DESC:
 *  外部への公開APIコントローラフレームとなる
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
 * *********************************** */
class ExternalApiCloseControllerFrame extends ApiControllerCore {

	private $is_error = false;
	
	/* * **********************************
	 * NAME  : __construct
	 * INPUT : NONE
	 * OUTPUT: NONE
	 * DESC  :
	 *  外部への公開APIコントローラフレーム
	 *  のコンストラクタ
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
			//指定ポートでなければ、エラーフラグをtrueへ
			if ($irc->verification() !== true) {
				$this->is_error = true;
			}	
		}	

		/*
		 * IP制限機能ONの場合、リストをチェックし
		 * 当てはまらない場合は指定URLへリダイレクト
		 */
		if (CONF::read('IP_RESTRICT.IS_ACTIVE') === true) {
			$irc = new IpAddressRestrict();
			//許可されなければ指定URLへリダイレクト
			if (!$irc->verification()) {
				$this->is_error = true;
			}
		}
		
		/*
		 * Auth認証を使用する必要があるかなー
		 */

		if (CONF::read('DEBUG_BAR.IS_ACTIVE')) DebugBarMaster::stop_measure('controller_constructor');

	}

	/* * **********************************
	 * NAME  : get_is_error
	 * INPUT : NONE
	 * OUTPUT: true / エラーが発生していた場合
	 *         false / エラーが発生していない場合
	 * DESC  :
	 *  コンストラクタにて、アクセス制限にあたるチェックを行い
	 *  弾かれる場合にエラーとなる
	 *  そのエラー状態を返すものである
	 * NOTICE:
	 *  コントローラで、処理を行い値を返して良いかを判断するために用いる
	 *  ここでエラーが返ってくる場合、正常なアクセスではないということになる
	 *  コントローラメソッドの最初に実行する想定
	 * CREATE: 2015.10.04 hesaka
	 * *********************************** */
	protected function get_is_error() {
		return $this->is_error;
	}
	
}

?>
