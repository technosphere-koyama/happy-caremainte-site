<?php

/* * **********************************
 * NAME:MypageLoginControllerFrame
 * DESC:
 *  一般アクセス側のログイン画面に用いるクラスフレーム
 * NOTICE:
 *  ControllerCoreクラスを継承し、__construct()に子クラス名を
 *  渡し、Coreでログ出力などに使用してもらう
 * 
 *  コントローラの継承構造設計は、
 *  Controller
 *  ↓
 *  ControllerFrame
 *  ↓
 *  ControllerCore
 *  となる
 * CREATE: 2015.08.27 hesaka
 * UPDATE: 2016.09.09 hesaka 言語判定処理追加
 * UPDATE: 2016.09.12 sonoda
 *  多言語が有効な場合、ログイン認証に成功した後にリダイレクトするURLに、
 *  言語コードを含める必要がある。
 *  なので、言語判定の処理の後、PUBLIC_MYPAGE_URLを設定するように修正した。
 *
 *  [多言語が無効の場合]
 *  日本語のみのサイトだが、後々多言語にしたいという依頼があるかもしれないこと想定して、
 *  CURRENT_LANGUAGEを設定するようにする。
 *  こうしておくことで、DBに英語や中国語用のDBを追加するだけでよくなる。
 *  URLには、言語コードなしのパスを使用する。
 * *********************************** */
class MypageLoginControllerFrame extends ControllerCore {

	/* * **********************************
	 * NAME  : __construct
	 * INPUT : NONE
	 * OUTPUT: NONE
	 * DESC  :
	 *  一般アクセス側のログイン画面に用いる
	 *  クラスフレームのコンストラクタ
	 *  下記内容を処理する
	 *  
	 *  ・コアの起動
	 *  ・セッションスタート
	 *  ・各種認証(verification)など
	 * NOTICE:
	 * --------------------------------------
	 *  当該フレーム定義に必要な認証は
	 *  コントローラではなくここで行う
	 * --------------------------------------
	 * CREATE: 2015.xx.xx hesaka
	 * UPDATE: 2016.10.12 aoyama
	 *		言語判定解除
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
		 * 強制リダイレクトチェック
		 */
		if (CONF::read('FORCE_REDIRECT.IS_ACTIVE') === true) {
			$fr = new ForceRedirect();
			if (!$fr->verification()) {
				$this->redirect(CONF::read('FORCE_REDIRECT.DESTINATION'));
			}	
		}	

		/*
		 * メンテナンスチェック
		 * ※PUBLIC側のみの判断となる
		 */
		if (CONF::read('DB_SERVICE_MASTER.IS_MAINTENANCE') === true) {
			/*
			 * 許可されたIP以外はメンテナンス画面へ
			 */
			$irc = new IpAddressRestrict();
			if (!$irc->verification()) {
				$this->redirect(CONF::read('MAINTENANCE.URL'));
			}
		}
		
		/*
		 * ドメインリダイレクトチェック
		 */
		if (CONF::read('DOMAIN_REDIRECT.IS_ACTIVE') === true) {
			$fr = new DomainRedirect();
			$url = $fr->verification();
			if ($url !== true) {
				LOGS_ENV('DOMAIN REDIRECT!!! env=' . ENV_DIR_NAME);
				$this->redirect($url);
			}	
		}

		/*
		 * http,httpsリダイレクト
		 * ※どちらにリダイレクトするかはCONFIG設定による
		 */
		if (CONF::read('SSL_REDIRECT.IS_ACTIVE') === true) {
			$irc = new SslRedirect();
			$schema = $irc->verification();
			//指定外ポートの場合はリダイレクト
			if ($schema !== true) {
				$this->redirect($schema . '://' . URL_HOST . URL_REQUEST);
			}	
		}
		
		/*
		 * ベーシック認証
		 */
		if (CONF::read('BASIC_AUTH.IS_ACTIVE')) {
			$ba = new BasicAuth();
			/*
			 * 認証を行っていない、もしくは失敗した場合は認証ダイアログを表示する
			 * ※ダイアログを表示する場合はverification()の中でexit()をする
			 * 　成功した場合はtrueが返ってくるが、何も行わないためリターン値のチェックを行う必要が無い
			 */
			$ba->verification();
		}
		
		if (CONF::read('DEBUG_BAR.IS_ACTIVE')) DebugBarMaster::stop_measure('controller_constructor');
	}

	/* * **********************************
	 * NAME  : view
	 * INPUT : directory / string / viewのアクセス先ディレクトリ名
	 * OUTPUT: NONE
	 * DESC  :
	 *  VIEWファイルの読み込みを行う
	 * NOTICE:
	 *  PUBLICディレクトリにある直接アクセスされる
	 *  ファイルから呼び出されるもの
	 *  デバイスにより呼び出すVIEWファイルを
	 *  切り替える機能を有する
	 *  ※レスポンシブの場合は纏めることもできる
	 * CREATE: 2015.xx.xx hesaka
	 * UPDATE: 2016.10.07 hesaka 画面共通セットを追加
	 * *********************************** */
	public function view($directory = 'index') {

		/*
		 * 画面共通セット
		 */
		//フッタの言語切り替えリストセット
		$this->set('lang_list', CONF::read('MULTI_LANGUAGE'));

		if (CONF::read('DEBUG_BAR.IS_ACTIVE')) DebugBarMaster::start_measure('view', '【VIEW】');
		
		/*
		 * デバイスにより実行するViewを読み分ける
		 */
		switch (DEVICE_TYPE) {
			//PC ro タブレット or SP
			//今回はレスポンシブなのでデバイスによりディレクトリを分ける必要はない
			case DEVICE_TYPE_SP:
			case DEVICE_TYPE_PC:
			case DEVICE_TYPE_TABLET:
			default:
				LOGS_DBG_LV1('--- GO TO VIEW (PUBLIC' . ':' . $directory . ') ---');
//				include_once DIR_VIEW . DS . $directory . DS . FILENAME;
//				include_once DIR_VIEW . DS . DIR_NAME_MYPAGE . DS . $directory . DS . FILENAME;
				include_once DIR_VIEW . DS . PUBLIC_CURRENT_LANGUAGE . DS . DIR_NAME_MYPAGE . DS . $directory . DS . FILENAME;
				break;
		}

		//stop_measure()は、html周りを出力する際にレンダリングしているので、使用するとエラーとなるので実行しない
	}

}

?>
