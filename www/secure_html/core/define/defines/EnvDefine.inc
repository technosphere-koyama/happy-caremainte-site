<?php

define("ENV_NAME_RELEASE", 'release');
define("ENV_NAME_STAGING", 'staging');
define("ENV_NAME_DEVELOP", 'local');

/*
 * 環境の判断を行う
 */

/*
 * SetEnvではなく、localかどうかで判断する場合は以下に切り替えること
 * ※これだと、条件以外が本番環境。という設定となるため、本当は良くない
 * 　だが、SetEnvが効かない場合はこれでいくしかないが
if ($_SERVER["HTTP_HOST"] == "localhost") {
	define("ENV_DIR_NAME", ENV_NAME_DEVELOP);
} else {
	define("ENV_DIR_NAME", ENV_NAME_RELEASE);
}
 */

/*
 * 既にENV_DIR_NAMEにセットされていた場合は何もしない
 */
//if (!defined('ENV_DIR_NAME')) {
//	switch (getenv('PHP_APP_ENV')) {
//		//本番環境
//		case 'release':
//			define("ENV_DIR_NAME", ENV_NAME_RELEASE);
//			break;
//		//ステージング(テスト)環境
//		case 'staging':
//			define("ENV_DIR_NAME", ENV_NAME_STAGING);
//			break;
//		//デベロップ環境
//		//本番・ステージング設定がない場合全てデベロップ環境と判断
//		default:
//			define("ENV_DIR_NAME", ENV_NAME_DEVELOP);
//	}
//}

if (preg_match("/www\.kyoto-happy\.co\.jp/", $_SERVER['HTTP_HOST'])) {
	define("ENV_DIR_NAME", ENV_NAME_RELEASE);
}elseif (preg_match("/happy-201901\.xaicom\.jp/", $_SERVER['HTTP_HOST'])) {
	define("ENV_DIR_NAME", ENV_NAME_STAGING);
} else {
	define("ENV_DIR_NAME", ENV_NAME_DEVELOP);	
}

//define("ENV_DIR_NAME", ENV_NAME_RELEASE);
?>
