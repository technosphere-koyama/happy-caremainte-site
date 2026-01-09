<?php

/* ---------------------------------------
  database (Docker ローカル環境用)
  ※本番環境には絶対に接続しない設定
  ---------------------------------------- */
$config["DB"] = array(
	"DBMS" => "mysql",
	"HOST" => "db",              // Dockerコンテナ名
	"PORT" => "3306",
	"CHAR_SET" => "utf8",
	"NAME" => "happy_sns",
	"USER_ID" => "happy_sns",
	"USER_PW" => "happy_sns_pass",

	"IS_CHECK_TABLES" => false
);

?>
