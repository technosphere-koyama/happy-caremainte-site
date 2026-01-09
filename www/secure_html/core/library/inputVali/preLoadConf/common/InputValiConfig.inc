<?php

/*
 * PHPでのバリデーションチェック用
 * 
 * UPDATE 2017.4.7 aoyama
 *      文字数制限をバイト数で制限するため項目を追加
 *      NAME_HALF、KANA_HALF、HOUSE_START、BLDG_START
 */
$config["INPUTVALI"] = array(
	"SYSTEM_ID_START" => 32,
	"SYSTEM_ID_END" => 64,
	"LOGIN_START" => 4,
	"LOGIN_END" => 16,
	"PASSWORD_START" => 5,
	"PASSWORD_END" => 8,
	"USER_NAME_START" => 1,
	"USER_NAME_END" => 30,
	"NAME_KANA_START" => 1,
	"NAME_KANA_END" => 30,
	"NAME_HALF_START" => 1,
	"NAME_HALF_END" => 15,
	"KANA_HALF_START" => 1,
	"KANA_HALF_END" => 15,
	"ZIP_START" => 1,
	"ZIP_END" => 20,
	"PHONE_START" => 1,
	"PHONE_END" => 15,
	"ADDRESS_START" => 1,
	"ADDRESS_END" => 22,
	"HOUSE_START" => 1,
	"HOUSE_END" => 32,
	"BLDG_START" => 1,
	"BLDG_END" => 32,
    "BIRTH_Y_BOTTOM" => 19,
	"BIRTH_Y_RANGE" => 120,
	"HISTORY_Y_START" => 1990,
);
?>
