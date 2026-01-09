<?php

$config["LOG"] = array(
	/*
	 * ログファイル パス
	 * ※種類を増やしたら、LogArchive.incも増やすこと！
	 */
	/* デイリー */
	"API_FILE_PATH" => DIR_LOG . DS . 'api_' . date('Ymd') . '.log',
	"LOGIN_FILE_PATH" => DIR_LOG . DS . 'login_' . date('Ymd') . '.log',
	"MAIL_FILE_PATH" => DIR_LOG . DS . 'mail_' . date('Ymd') . '.log',
	"DB_FILE_PATH" => DIR_LOG . DS . 'db_' . date('Ymd') . '.log',
	"DBG_FILE_PATH" => DIR_LOG . DS . 'debug_' . date('Ymd') . '.log',
	/* マンスリー */
	"ERR_FILE_PATH" => DIR_LOG . DS . 'error_' . date('Ym') . '.log',
	"ALERT_FILE_PATH" => DIR_LOG . DS . 'alert_' . date('Ym') . '.log',
	"WARN_FILE_PATH" => DIR_LOG . DS . 'warning_' . date('Ym') . '.log',
	"NOTICE_FILE_PATH" => DIR_LOG . DS . 'notice_' . date('Ym') . '.log',
	"ENV_FILE_PATH" => DIR_LOG . DS . 'env_' . date('Ym') . '.log',
	"GENGO_FILE_PATH" => DIR_LOG . DS . 'gengo_' . date('Ym') . '.log'
);

/* ---------------------------------------
 * アーカイブタイミング(月)
 * アーカイブを行うタイミングを設定する
 * ※MODEが「local」の場合のみ処理を行う
 * ※配列指定を行うこと
 * 例：
 * 　array(1, 7)
 * 　この場合
 * 　1月と7月に、アーカイブされていない、先月以前のものを纏めてZIP圧縮する
 * 　ということになり、半年に一度アーカイブすることとなる
  ---------------------------------------- */
$config["LOG_ARCHIVE"] = array(
	"IS_ACTIVE" => true,
	"TIMING" => array(1, 3, 5, 7, 9, 11)
);
?>
