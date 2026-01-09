<?php

/* * **********************************
 * NAME:PublicEscapeControllerFrame
 * DESC:
 *  制限の一切ない画面用フレーム
 *  ※403ページなど
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
 * CREATE: 2015.10.07 hesaka
 * UPDATE: 2016.09.09 hesaka 言語判定処理追加
 * *********************************** */
class PublicEscapeControllerFrame extends ControllerCore {

	/* * **********************************
	 * NAME  : __construct
	 * INPUT : NONE
	 * OUTPUT: NONE
	 * DESC  :
	 *  制限の一切ない画面用フレームのコンストラクタ
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
		 * 言語関係処理
		 */
		$cl = new ChangeLanguage();
		//言語判定
		//※ここでPUBLIC_CURRENT_LANGUAGEが定義される
		$redirect_url = $cl->verification('PUBLIC_CURRENT_LANGUAGE');
		if ($redirect_url !== true) {
			$this->redirect($redirect_url);
		}
		//ユーザからの切り替え指定
		$redirect_url = $cl->change_verification();
		if ($redirect_url !== true) {
			$this->redirect($redirect_url);
		}
		//動的各国語テキストロード(PUBLIC_CURRENT_LANGUAGE分だけ)
		include_once DIR_VIEW . DS . '_LANGUAGE' . DS . PUBLIC_CURRENT_LANGUAGE . '.php';

		/*
		 * ドメインリダイレクトチェック
		 */
		if (CONF::read('DOMAIN_REDIRECT.IS_ACTIVE') === true) {
			$fr = new DomainRedirect();
			$url = $fr->verification();
			if ($url !== true) {
				$this->redirect($url);
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
				include_once DIR_VIEW . DS . $directory . DS . FILENAME;
				break;
		}

		//stop_measure()は、html周りを出力する際にレンダリングしているので、使用するとエラーとなるので実行しない
	}

}

?>
