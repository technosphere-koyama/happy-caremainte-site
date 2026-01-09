<?php

/* ---------------------------------------
  database (Docker環境用)
  ---------------------------------------- */
$config["DB"] = array(
	"DBMS" => "mysql",
	"HOST" => "db",
	"PORT" => "3306",
	"CHAR_SET" => "utf8",
	"NAME" => "happy_sns",
	"USER_ID" => "happy_sns",
	"USER_PW" => "happy_sns_pass",

	"IS_CHECK_TABLES" => false
);

?>
