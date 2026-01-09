<?php

/* * **********************************
 * NAME:AppVersionCheckController
 * DESC:
 * NOTICE:
 * CREATE: 2021.01.14 jc ooi
 * *********************************** */
//class AppVersionCheckController extends ExternalApiCloseControllerFrame {
class AppVersionCheckController {

	/* Constructor */
	public function __construct() {
//		parent::__construct();

//		header('Content-Type: application/json');
	}

	/*	 * **********************************
	 * NAME  : exec
	 * INPUT : 
	 * 		$device / string / Android or iOS
	 * 		$version / string / アプリバージョン(xx.yy.zz)
	 * OUTPUT: 
	 * 		true or false
	 * DESC  :
	 * 		説明
	 * NOTICE:
	 * CREATE: 2021.01.14 jc ooi
	 * *********************************** */
	public function exec() {

		$ret = array();

		// リクエストにアプリバージョンが存在しない場合
		if (StaticFunction::is_empty(REQUEST::post_data('version'))) {
			// アプリバージョンと本番環境URLを返す
			$ret = array(
				"code" => 200,
				"message" => "Ok.",
				"version" => CONF::read('APP_CONFIG.APP_VERSION'),
				"web_url" => CONF::read('APP_CONFIG.PRODUCTION_URL'),
			);
			$this->return_json($ret);
		}

		$req_version = REQUEST::post_data('version');
		$demand_version = CONF::read('APP_CONFIG.DEMAND');

		// バージョン文字列からピリオドを削除して数値に変換を行い比較する。
		if(intval(str_replace('.', '', $req_version)) >= intval(str_replace('.', '', $demand_version))){
			// アプリバージョンがデマンドバージョンより新しい場合
			// アプリバージョンと審議環境URLを返す
			$ret = array(
				"code" => 200,
				"message" => "Ok.",
				"version" => CONF::read('APP_CONFIG.APP_VERSION'),
				"web_url" => CONF::read('APP_CONFIG.DEMAND_URL'),
			);
			$this->return_json($ret);
		}

		$app_version = CONF::read('APP_CONFIG.APP_VERSION');
		$production_url= CONF::read('APP_CONFIG.PRODUCTION_URL');

//		// ※リクエストのdevice がiOS or Android の場合、アプリバージョンをスマホ用バージョンを返す
//		if (StaticFunction::is_empty(REQUEST::post_data('device'))) {
//			$device = REQUEST::post_data('device');
//			if($device == 'iOS' || $device == 'Android'){
//				$app_version = CONF::read('APP_CONFIG.APP_VERSION_MOBILE');
//			}
//		}

//		// リクエストのバージョンが１つ前のバージョンの場合に専用のAPI URLを返す
//		if(intval(str_replace('.', '', $req_version)) == intval(str_replace('.', '', CONF::read('APP_CONFIG.APP_PREVIOUS_VERSION')))){
//			$production_url = CONF::read('APP_CONFIG.PRODUCTION_PREVIOUS_URL');
//		}

		// アプリバージョンと本番環境URLを返す
		$ret = array(
			"code" => 200,
			"message" => "Ok.",
			"version" => $app_version,
			"web_url" => $production_url,
		);
		$this->return_json($ret);
	}

	private function return_json($array) {
		$array += array(
			"ios_store" => CONF::read('APP_CONFIG.IOS_STORE'),
			"android_store" => CONF::read('APP_CONFIG.ANDROID_STORE'),
		);
		echo json_encode($array);
		exit;
	}

}

?>
