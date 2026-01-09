<?php

define("USER_AGENT", mb_strtolower((isset($_SERVER['HTTP_USER_AGENT']) ? ($_SERVER['HTTP_USER_AGENT']) : (''))));	//小文字にしておく

//デバイスタイプ設定
define("DEVICE_TYPE_PC", 1);
define("DEVICE_TYPE_TABLET", 2);
define("DEVICE_TYPE_SP", 3);
define("DEVICE_TYPE_MOBILE", 4);
define("DEVICE_TYPE_APP", 5);
$config["DEVICE_NAME"] = array(
	DEVICE_TYPE_PC => 'PC',
	DEVICE_TYPE_TABLET => 'TABLET',
	DEVICE_TYPE_SP => 'SP',
	DEVICE_TYPE_MOBILE => '携帯',
	DEVICE_TYPE_APP => 'アプリ'
);

/*
 * デバイス判定
 */

//アプリ
if(USER_AGENT == 'CareMenteh App User') {
	define("DEVICE_TYPE", DEVICE_TYPE_APP);
}

//スマホ
else if(
	(strpos(USER_AGENT,'iphone') !== false)
	|| (strpos(USER_AGENT,'ipod') !== false)
	|| (strpos(USER_AGENT,'blackberry') !== false)
	|| ((strpos(USER_AGENT,'android') !== false) && (strpos(USER_AGENT, 'mobile') !== false))
	|| ((strpos(USER_AGENT,'windows') !== false) && (strpos(USER_AGENT, 'phone') !== false))
	|| ((strpos(USER_AGENT,'firefox') !== false) && (strpos(USER_AGENT, 'mobile') !== false))
){
	define("DEVICE_TYPE", DEVICE_TYPE_SP);
}

//タブレット
else if (
	(strpos(USER_AGENT,'ipad') !== false)
	|| (strpos(USER_AGENT,'playbook') !== false)
	|| ((strpos(USER_AGENT,'windows') !== false) && (strpos(USER_AGENT, 'touch') !== false))
	|| ((strpos(USER_AGENT,'android') !== false) && (strpos(USER_AGENT, 'mobile') === false))
	|| ((strpos(USER_AGENT,'firefox') !== false) && (strpos(USER_AGENT, 'tablet') !== false))
	|| ((strpos(USER_AGENT,'kindle') !== false) || (strpos(USER_AGENT, 'silk') !== false))
){

	define("DEVICE_TYPE", DEVICE_TYPE_TABLET);

}
//PC
else {

	define("DEVICE_TYPE", DEVICE_TYPE_PC);

}

?>
