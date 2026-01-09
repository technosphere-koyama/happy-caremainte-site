<?php

/*
 * メール系の設定ファイル：happy.ini
 *
 * JDBC=jdbc:postgresql://localhost/kh00012g?user=kh00012g&password=jh8MT9Fw * &useUnicode=true&characterEncoding=EUC-JP
 * POP=mail.kyoto-happy.co.jp
 * SMTP=mail.kyoto-happy.co.jp
 * ACCOUNT=happy@kyoto-happy.co.jp
 * PASSWORD=mailhappy
 * FROM=ar-kyoto@kyoto-happy.co.jp
 * FROM2=happy@kyoto-happy.co.jp
 * TO=happy@kyoto-happy.co.jp
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
	"PORT"		=> "587",
	"SERVER"	=> "mail.kyoto-happy.co.jp"
);

/* 基幹システムへ送信（会員登録） */
$config["MAIL_ENTRY"] = array(
	"RETURN" => "idpass@kyoto-happy.co.jp",
	"FROM" => "idpass@kyoto-happy.co.jp",
	"TO" => array("idpass@kyoto-happy.co.jp","happy@kyoto-happy.co.jp"),
	"BCC" => "happy@kyoto-happy.co.jp"
);

/* 管理者へ送信（メルマガ登録） */
$config["MAIL_MAILMAG"] = array(
	"RETURN" => "happy@kyoto-happy.co.jp",
	"FROM" => "happy@kyoto-happy.co.jp",
	"TO" => "happy@kyoto-happy.co.jp"
);

/* 管理者へ送信（登録情報の変更） */
$config["MAIL_REGIST"] = array(
	"RETURN" => "happy@kyoto-happy.co.jp",
	"FROM" => "happy@kyoto-happy.co.jp",
	"TO" => "happy@kyoto-happy.co.jp"
);

/* 管理者へ送信（オーダー系で送信） */
$config["MAIL_ORDER"] = array(
	"RETURN" => "happy@kyoto-happy.co.jp",
	"FROM" => "happy@kyoto-happy.co.jp",
	"TO" => "happy@kyoto-happy.co.jp",
	"BCC" => "shuuka-tsuuchi@kyoto-happy.co.jp", //メール送信内容チェック用
);

/* 管理者へ送信（オーダー系で送信） */
$config["MAIL_ORDER_TEST"] = array(
	"RETURN" => "happy@kyoto-happy.co.jp",
	"FROM" => "happy@kyoto-happy.co.jp",
	"TO" => array("y-imada@kyoto-happy.co.jp", "kandc1112@yahoo.co.jp"),
	"BCC" => array("y-imada@kyoto-happy.co.jp", "kandc1112@yahoo.co.jp"), //メール送信内容チェック用
);

/* 管理者へ送信（オーダー系でヤマトへ送信） */
$config["MAIL_YAMATO"] = array(
	"RETURN" => "happy@kyoto-happy.co.jp",
	"FROM" => "happy@kyoto-happy.co.jp",
	"TO" => "order@kyoto-happy.co.jp"
);

/* 管理者へ送信（カタログ請求で送信） */
$config["MAIL_CATALOG"] = array(
	"RETURN" => "happy@kyoto-happy.co.jp",
	"FROM" => "happy@kyoto-happy.co.jp",
	"TO" => "happy@kyoto-happy.co.jp"
);

/* 管理者へ送信（お問合せ） */
$config["MAIL_CONTACT"] = array(
	"RETURN" => "happy@kyoto-happy.co.jp",
	"FROM" => "happy@kyoto-happy.co.jp",
	"TO" => "happy@kyoto-happy.co.jp"		
);

/* 管理者へ送信（友達紹介で送信） */
$config["MAIL_FRIEND"] = array(
	"RETURN" => "happy@kyoto-happy.co.jp",
	"FROM" => "happy@kyoto-happy.co.jp",
	"TO" => "happy@kyoto-happy.co.jp"
);

/* 基幹システムへ送信するメール（EnterpriseSystem） */
$config["MAIL_ES"] = array(
	"RETURN" => "happy@kyoto-happy.co.jp",
	"FROM" => "happy@kyoto-happy.co.jp",
	"TO" => "happy@kyoto-happy.co.jp"	
);

/* 管理者へ送信（ウェブカウンセリングで送信） */
$config["MAIL_WEBCOUNSELING"] = array(
	"RETURN" => "web-counseling@kyoto-happy.co.jp",
	"FROM" => "web-counseling@kyoto-happy.co.jp",
	"TO" => "web-counseling@kyoto-happy.co.jp"
);

$config["MAIL_ADDRESS"] = array(
	"BASE"=> "happy@kyoto-happy.co.jp",				//return path・sender・reply to に用いる用(名前の連想配列は使わないこと！)
	"FROM"=> "happy@kyoto-happy.co.jp",	//メール送信元(運営のinfoなどのアドレス)
	"TO"=> "happy@kyoto-happy.co.jp",	//メール送信先(お問い合わせなど、お客様からくるものを送信するアドレス)
	"ADMIN"=> "happy@kyoto-happy.co.jp",		//運営の管理者アドレス
	"BCC"=> "happy@kyoto-happy.co.jp",			//メール送信内容チェック用
	"DIRECTOR"=> "happy@kyoto-happy.co.jp",	//ディレクター(運営とやり取りを行っている人)
	"DEVELOPER"=> "happy@kyoto-happy.co.jp"		//システム開発者(システム関連の通知を行う場合に用いる)
);

/* Added By UKS MS for webcounseling mail configuration */
$config["UKS_WEBCOUNSELING"] = array(
	"RETURN" => "web-counseling@kyoto-happy.co.jp",
	"FROM" => "counseling@kyoto-happy.co.jp"
);

?>
