<?php

$config["LOGIN"] = array(
	"IS_ACTIVE" => true,		//有効/無効
	"LOCK_COUNT" => 30		//アカウントをロックする制限回数
);

$config["LOGIN_CATEGORY"] = array(
	"SYSTEM" => 'SYSTEM_USER',								//管理画面ログイン
	"SYSTEM_TOP_URL" => 'mc_admin' . DS . 'dashboard' . DS,			//管理画面側のトップページ
	"SYSTEM_LOGIN_URL" => 'mc_admin' . DS .'login' . DS,			//管理画面側のログインページ
	"PUBLIC" => 'PUBLIC_USER',								//会員ユーザログイン
	"PUBLIC_TOP_URL" => 'mypage' . DS,			//サイト側のログイン関係的なトップページ
	"PUBLIC_LOGIN_URL" => 'mypage' . DS . 'login' . DS	//サイト側のログインページ
);

/*
 * USERROLE関係
 * セッションに持つPUBLICユーザのextendパラメータに
 * 直接アクセス(CONF::read()で)するパスを設定する
 */
$config["USER_ROLE_INFO"] = array(
	"GUEST" => CONF::read('LOGIN_CATEGORY.PUBLIC') . '.EXTEND.GUEST',
	"HOST" => CONF::read('LOGIN_CATEGORY.PUBLIC') . '.EXTEND.HOST',
	"SUPPLIER" => CONF::read('LOGIN_CATEGORY.PUBLIC') . '.EXTEND.SUPPLIER'
);

?>
