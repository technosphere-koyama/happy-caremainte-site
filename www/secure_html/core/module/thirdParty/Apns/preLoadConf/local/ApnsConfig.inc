<?php
$config["APNS_CONF"] += array(
	"SANDBOX" => false, //Apnsのpush通知をSANDBOXに行うかどうか。
	"PEM_FILE" => dirname(__FILE__) . "/../../HappyCarementeh.pem", //使用するpemファイル
	"LOG" => false //APNSで用意されているechoログを有効にするかどうか。
);
?>
