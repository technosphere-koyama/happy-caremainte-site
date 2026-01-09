<?php

/* ---------------------------------------
  directory
  ---------------------------------------- */
/*
 * ライブラリ・モジュールのプリロードconfigディレクトリ名
 */
define("DIR_NAME_PRE_LOAD_CONF", 'preLoadConf');
define("DIR_NAME_THIRD_PARTY", 'thirdParty');

/*
 * ライブラリ・モジュールの有効/無効判断用ファイル名
 */
define("FILE_NAME_VALID_MODULE_ON", 'ON');
define("FILE_NAME_VALID_MODULE_OFF", 'OFF');

/*
 * セパレータ短くする
 */
define("DS", DIRECTORY_SEPARATOR);

/*
 * 各固定ディレクトリ名(単パス)
 */
define("DIR_NAME_ADMIN", 'mc_admin');
define("DIR_NAME_CART", 'shop_cart');
define("DIR_NAME_MYPAGE", 'mypage');

/*
 * 各固定ディレクトリ名(フルパス)
 */
define("DIR_APPLICATION", DIR_CORE . DS . 'application');
define("DIR_APPLICATION_API", DIR_APPLICATION . DS . 'API');
define("DIR_APPLICATION_DIRECT_ACCESS", DIR_APPLICATION . DS . 'directAccess');

define("DIR_CONF", DIR_CORE . DS . 'conf');

define("DIR_TMP", DIR_CORE . DS . 'tmp');
define("DIR_LOG", DIR_TMP . DS . 'log');
define("DIR_LOG_ARCHIVE", DIR_LOG . DS . 'archive');
define("DIR_SESSION", DIR_TMP . DS . 'session');
define("DIR_DIRECTORY_LIST", DIR_TMP . DS . 'directoryList');
define("DIR_DB_BACK_UP", DIR_TMP . DS . 'db_back_up');

define("DIR_DEFINE", DIR_CORE . DS . 'define');
define("DIR_DEFINES", DIR_DEFINE . DS . 'defines');

define("DIR_LIBRARY", DIR_CORE . DS . 'library');
define("DIR_LIBRARY_THIRD_PARTY", DIR_LIBRARY . DS . DIR_NAME_THIRD_PARTY);

define("DIR_MODULE", DIR_CORE . DS . 'module');
define("DIR_MODULE_THIRD_PARTY", DIR_MODULE . DS . DIR_NAME_THIRD_PARTY);

//システム自体の配置ディレクトリをINCから無理やり取得する
define("DIR_TOP", str_replace(DS . 'core', '', DIR_CORE));

//core外ディレクトリ
define("DIR_VIEW", DIR_TOP . DS . 'view');
define("DIR_COMPONENT", DIR_VIEW . DS . '_COMPONENT');
define("DIR_LANGUAGE", DIR_VIEW . DS . '_LANGUAGE');
define("DIR_PUBLIC", DIR_TOP . DS . 'public');

//イベント(マイページ or 管理画面)でアップロードされる画像のパス
define("DIR_SYSTEM_IMG_TMP", DIR_PUBLIC . DS . 'images' . DS . 'tmp');
define("DIR_PUBLIC_IMG", DIR_PUBLIC . DS . 'images');
?>
