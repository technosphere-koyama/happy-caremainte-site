<?php

/*
 * APEX APIの処理結果
 * OK, ERROR設定値
 */
define("SF_APEX_STATUS_CODE_OK", 1);
define("SF_APEX_STATUS_CODE_ERR", 0);

/*
 * post, getメソッドによる通信のリトライ回数
 */
define("REST_RETRY_COUNT", 5);

/*
 * オーダーケアメンテのステータス設定
 * 1：過去のケア～　2：ただいまの～　3：ハッピーワードローブ
 * CREATE: 2016.11.7 aoyama
 */
define("REST_ORDER_PAST", (int)1);
define("REST_ORDER_HOLD", (int)2);
define("REST_ORDER_ROBE", (int)3);
$config["REST_ORDER_NAME"] = array(
	REST_ORDER_PAST => "history",
	REST_ORDER_HOLD => "ordered",
	REST_ORDER_ROBE => "wardrobe"
);

?>