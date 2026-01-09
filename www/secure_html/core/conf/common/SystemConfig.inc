<?php


$config["PASSWORD"] = array(
	//"IS_ACTIVE" => true,			//on/off
	"ENCRYPT_KEY" => md5('q)13kMDi8o-A'),	//暗号化時に用いるキー
	"SYSTEM_ID_CHAR_NUM" => 4		//暗号化時に用いるシステムIDの使用文字数
);

$config["PASSWORD_RESET_TOKEN"] = array(
	"ENCRYPT_KEY" => md5('A0*1kOewla9['),	//暗号化時に用いるキー
	"EXPIRE" => (60 * 30)			//有効期限30分(単位：秒)
);

$config["MEMBER_REGIST_TOKEN"] = array(
	"ENCRYPT_KEY" => md5('7)eAq*P,HB4/'),	//暗号化時に用いるキー
	"EXPIRE" => (60 * 60 * 12)		//有効期限12時間(単位：秒)
);

/*
 * 権限設定
 * 権限によって、できることを制限する
 * 
 * 定義値は、ビット演算値方式をとる
 * これを利用するメリットとしては、
 * 特定の複数を指定する際に、それぞれの値を合算して指定できることである
 * ※これとこれ、もしくはこれとこれという重複パターンがありえないので、
 * 　DB的に高速なintegerでありながら、自由に設定できる
 * 
 * 00000001:1
 * 00000010:2	
 * 00000100:4
 * 00001000:8
 * 00010000:16
 * 00100000:32
 */
define("AUTHORITY_DEVELOPER",	1);	//開発者。adminよりもできることが多い
define("AUTHORITY_DIRECTOR",	2);	//代理店・プロダクションの人が多い。案件総監督。権限はadministratorと一緒
define("AUTHORITY_ADMIN",	4);	//クライアントの管理者。クライアント範囲は全てできる
define("AUTHORITY_STAFF",	8);	//一般作業員。できないことはあるが、管理範囲以外は更新も可能
define("AUTHORITY_VIEWER",	16);	//閲覧のみ
$config["AUTHORITY"] = array(
	AUTHORITY_DEVELOPER => "開発者",
	AUTHORITY_DIRECTOR => "ディレクター",
	AUTHORITY_ADMIN => "管理者",
	AUTHORITY_STAFF => "スタッフ",
	AUTHORITY_VIEWER => "閲覧のみ"
);

/*
 * kh01への画像取得設定 (2016.11.15 aoyama)
 */
$config["EXTERNAL_IMAGE"] = array(
	"METHOD_URL" => "/external_image.html?url=",
	"TARGET_URL" => "/external_image.html?url=http://kh01.kyoto-happy.co.jp",
	"TARGET_SURL" => "/external_image.html?url=https://kh01.kyoto-happy.co.jp"
);	

?>
