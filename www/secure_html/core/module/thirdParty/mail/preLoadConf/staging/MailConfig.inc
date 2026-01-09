<?php

/*
 * メール系の設定ファイル：happy.ini
 * 
 * JDBC=jdbc:postgresql://localhost/kh00012g?user=kh00012g&password=jh8MT9Fw * &useUnicode=true&characterEncoding=EUC-JP
 * POP=mail.kyoto-happy.co.jp
 * SMTP=mail.kyoto-happy.co.jp
 * ACCOUNT=xaicom3@gmail.com
 * PASSWORD=mailhappy
 * FROM=ar-kyoto@kyoto-happy.co.jp
 * FROM2=xaicom3@gmail.com
 * TO=xaicom3@gmail.com
 * CHARTJPEG=/home/www/public_html/chart/
 * 
 * UPDATE: 2016/11/17 aoyama
 * 
 */

$config["MAIL"] = array(
	"IS_ACTIVE" => true		//これをfalseにするとメールを送らなくなる
);

$config["SMTP"] = array(
	"USER"		=> "",
	"PASSWORD"	=> "",
	"PORT"		=> "25",
	"SERVER"	=> "localhost" 
);

/* 基幹システムへ送信（会員登録） */
$config["MAIL_ENTRY"] = array(
	"RETURN" => "xaicom3@gmail.com",
	"FROM" => "xaicom3@gmail.com",
	"TO" => "xaicom3@gmail.com"
);

/* 管理者へ送信（メルマガ登録） */
$config["MAIL_MAILMAG"] = array(
	"RETURN" => "xaicom3@gmail.com",
	"FROM" => "xaicom3@gmail.com",
	"TO" => "xaicom3@gmail.com"
);

/* 管理者へ送信（登録情報の変更） */
$config["MAIL_REGIST"] = array(
	"RETURN" => "xaicom3@gmail.com",
	"FROM" => "xaicom3@gmail.com",
	"TO" => "xaicom3@gmail.com"
);

/* 管理者へ送信（オーダー系で送信） */
$config["MAIL_ORDER"] = array(
	"RETURN" => "xaicom3@gmail.com",
	"FROM" => "xaicom3@gmail.com",
	"TO" => "xaicom3@gmail.com"
);
/* 管理者へ送信（オーダー系でヤマトへ送信） */
$config["MAIL_YAMATO"] = array(
	"RETURN" => "xaicom3@gmail.com",
	"FROM" => "xaicom3@gmail.com",
	"TO" => "order@kyoto-happy.co.jp"
);

/* 管理者へ送信（カタログ請求で送信） */
$config["MAIL_CATALOG"] = array(
	"RETURN" => "xaicom3@gmail.com",
	"FROM" => "xaicom3@gmail.com",
	"TO" => "xaicom3@gmail.com"
);

/* 管理者へ送信（お問合せ） */
$config["MAIL_CONTACT"] = array(
	"RETURN" => "xaicom3@gmail.com",
	"FROM" => "xaicom3@gmail.com",
	"TO" => "xaicom3@gmail.com"
);

/* 管理者へ送信（友達紹介で送信） */
$config["MAIL_FRIEND"] = array(
	"RETURN" => "xaicom3@gmail.com",
	"FROM" => "xaicom3@gmail.com",
	"TO" => "xaicom3@gmail.com"
);

/* 基幹システムへ送信するメール（EnterpriseSystem） */
$config["MAIL_ES"] = array(
	"RETURN" => "xaicom3@gmail.com",
	"FROM" => "xaicom3@gmail.com",
	"TO" => "xaicom3@gmail.com"
);

$config["MAIL_ADDRESS"] = array(
	"BASE"=> "xaicom3@gmail.com",				//return path・sender・reply to に用いる用(名前の連想配列は使わないこと！)
	"FROM"=> "xaicom3@gmail.com",	//メール送信元(運営のinfoなどのアドレス)
	"TO"=> "xaicom3@gmail.com",	//メール送信先(お問い合わせなど、お客様からくるものを送信するアドレス)
	"ADMIN"=> "xaicom3@gmail.com",		//運営の管理者アドレス
	"BCC"=> "xaicom3@gmail.com",			//メール送信内容チェック用
	"DIRECTOR"=> "xaicom3@gmail.com",	//ディレクター(運営とやり取りを行っている人)
	"DEVELOPER"=> "xaicom3@gmail.com"		//システム開発者(システム関連の通知を行う場合に用いる)
);


?>
