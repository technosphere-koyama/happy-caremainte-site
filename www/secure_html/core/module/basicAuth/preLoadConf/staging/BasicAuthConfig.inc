<?php

/*
 * BASIC AUTH
 * 
 * ベーシック認証
 * htaccessではなくPGで行う場合これを使用すること
 */
$config["BASIC_AUTH"] = array(
	"IS_ACTIVE" => false,					//on/off
	"CANCEL_DIALOGUE_TEXT" => "Authorization Failed.",	//キャンセル時に画面に表示するテキスト
	"USER" => 'xaicom',
	"PASSWORD" => 'testpass'
);

?>
