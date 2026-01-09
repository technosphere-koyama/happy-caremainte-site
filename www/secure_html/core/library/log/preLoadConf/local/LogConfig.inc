<?php

$config["LOG"] += array(
	//error ログ
	"IS_ERR_OPEN" => true,		//ON/OFF
	"IS_ERR_PRINT" => false,	//画面出力 ON/OFF
	//alert ログ
	"IS_ALERT_OPEN" => true,	//ON/OFF
	"IS_ALERT_PRINT" => false,	//画面出力 ON/OFF
	//warning ログ
	"IS_WARN_OPEN" => true,		//ON/OFF
	"IS_WARN_PRINT" => false,	//画面出力 ON/OFF
	//login ログ
	"IS_LOGIN_OPEN" => true,	//ON/OFF
	//api ログ
	"IS_API_OPEN" => true,	//ON/OFF
	//notice ログ
	"IS_NOTICE_OPEN" => true,	//ON/OFF
	//debug ログ
	"IS_DBG_OPEN" => true,		//ON/OFF
	//mail ログ
	"IS_MAIL_OPEN" => true,		//ON/OFF
	//env ログ
	"IS_ENV_OPEN" => true,		//ON/OFF
	//GENGO コールバック ログ
	"IS_GENGO_OPEN" => true		//ON/OFF
);

/*---------------------------------------
 * ログモード
 * herokuサーバはGITでデプロイする以外にファイル書き込みを行うと消されてしまうため、
 * ログはpaper trailというものに吐き出すようにする必要がある
 * そのためにログモードを作成
 * 
 * local
 * papertrail
  ---------------------------------------- */
$config["LOG"] += array(
	"MODE" => 'local'
);

/*---------------------------------------
   デバッグログレベル 
 	LV1=重要ログ用
 	LV2=重要度中ログ用
 	LV3=細かく見たいとき用
 
 	1を指定するとLV1のもののみ出力
 	2を指定するとLV1,2を出力
 	3を指定するとLV1,2,3全てを出力
  ---------------------------------------- */
$config["LOG"] += array(
	"DBG_LV" => 3
);

?>
