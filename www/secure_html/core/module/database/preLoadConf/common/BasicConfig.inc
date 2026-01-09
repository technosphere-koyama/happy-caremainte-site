<?php

/*
 * 基本系設定情報
 */

/*
 * クエリでエラーが発生した際にクエリ文を取得して
 * phpMyAdminで直接叩きたいことがある
 * それ用のデファイン値
 */
define("QUERY_DISPLAY_ON", true);
define("QUERY_DISPLAY_OFF", false);

/*
 * DB接続エラー時のリトライ設定
 */
define("DB_CONNECTION_RETRY_TIMES", 5);			//リトライ回数
define("DB_CONNECTION_RETRY_SLEEP_TIME", 0.5);		//リトライ時スリープ時間(秒)

/*
 * DB用true/false
 * MySQLではBOOLEAN型でカラムを指定するとTINYINTとなり、
 * DEFAULTでtrueを指定すると「1」となる
 * trueを入れたつもりでtrueと型含めた比較「===」を行うと
 * おかしな結果になる可能性がある
 * なので、DB用のtrue/falseとして「1」「0」をデファインして
 * 使用することとする
 */
define("DB_TRUE", (int)1);
define("DB_FALSE", (int)0);

/*
 * 有効/無効値
 * ユーザや、以外にもテーブルのレコード自体の有効無効を表す値
 * どこのテーブルにもだいたいある「active」に用いる
 */
define("DB_ACTIVE_ON", (int)1);			//有効
define("DB_ACTIVE_OFF", (int)2);			//無効(停止)
define("DB_ACTIVE_TEMPORARY", (int)3);			//一時的な(仮登録など)
define("DB_ACTIVE_FORCE_DELETE", (int)6);		//削除(問題発生等による、管理側からの強制削除)
define("DB_ACTIVE_DELETE", (int)9);			//削除(通常の削除)

/*
 * active用 有効無効用
 * ※有効無効のみに限定
 * ※全て(削除系含む)を使いたい場合は別で作ること
 * ※keyの値は、DBに入れる値と直結しているので変更しないこと！
 */
$config["DB_ACTIVE_ON_OFF"] = array(
	DB_ACTIVE_ON => '有効',
	DB_ACTIVE_OFF => '無効'
);

/*
 * active 会員管理用
 * ※仮登録状態がある、会員用となる
 * ※keyの値は、DBに入れる値と直結しているので変更しないこと！
 */
$config["DB_ACTIVE_FOR_MEMBER"] = array(
	DB_ACTIVE_ON => '有効',
	DB_ACTIVE_OFF => '無効',
	DB_ACTIVE_TEMPORARY => '仮登録'
);

/*
 * ユーザタイプ
 * ※keyの値は、DBに入れる値と直結しているので変更しないこと！
 * log_loginテーブルの「user_type」に用いる
 */
define("DB_USER_TYPE_PUBLIC", (int)1);
define("DB_USER_TYPE_SYSTEM", (int)2);

/*
 * ユーザ種別
 * ※keyの値は、DBに入れる値と直結しているので変更しないこと！
 * newsテーブルの「target_role」などに用いる
 */
define("DB_ROLE_GUEST", (int)1);
define("DB_ROLE_HOST", (int)2);
define("DB_ROLE_SUPPLIER", (int)3);
define("DB_ROLE_ALL", (int)4);
$config["DB_ROLE"] = array(
	DB_ROLE_GUEST => 'ゲスト',
	DB_ROLE_HOST => 'ホスト',
	DB_ROLE_SUPPLIER => 'サプライヤ',
	DB_ROLE_ALL => '全て'
);

/*
 * ROLEによって分けているテーブル名取得配列
 * まったく同じ構造だが、ROLEごとに分けているテーブルについては
 * 同じ処理で対象テーブルだけ変更して処理させるのが再利用性が高く
 * 良いと思われる
 * その際に当該配列を使用すること
 */
//user_public_extend
$config["DB_TABLE_ROLE_USER_EXTEND_LIST"] = array(
	DB_ROLE_GUEST => 'user_public_extend_guest',
	DB_ROLE_HOST => 'user_public_extend_host',
	DB_ROLE_SUPPLIER => 'user_public_extend_supplier'
);
//bank
$config["DB_TABLE_ROLE_BANK_LIST"] = array(
	DB_ROLE_HOST => 'bank_host',
	DB_ROLE_SUPPLIER => 'bank_supplier'
);
//pa_card
$config["DB_TABLE_ROLE_PA_CARD_LIST"] = array(
	DB_ROLE_GUEST => 'pa_guest_card',
	DB_ROLE_SUPPLIER => 'pa_supplier_card' 
);

/*
 * 性別
 * ※keyの値は、DBに入れる値と直結しているので変更しないこと！
 * user_memberテーブルの「sex」に用いる
 */
define("DB_SEX_FEMALE", (int)2);
define("DB_SEX_MALE", (int)1);
$config["DB_SEX"] = array(
	DB_SEX_FEMALE => '女性',
	DB_SEX_MALE => '男性'
);

/*
 * ニュースタイプ
 * ※keyの値は、DBに入れる値と直結しているので変更しないこと！
 * newsテーブルの「type」に用いる
 */
define("DB_NEWS_TYPE_NORMAL", (int)1);
define("DB_NEWS_TYPE_ALERT", (int)2);
define("DB_NEWS_TYPE_WARNING", (int)3);
define("DB_NEWS_TYPE_IMPORTANT", (int)4);
$config["DB_NEWS_TYPE"] = array(
	DB_NEWS_TYPE_NORMAL => '通常',
	DB_NEWS_TYPE_ALERT => '注意',
	DB_NEWS_TYPE_WARNING => '警告',
	DB_NEWS_TYPE_IMPORTANT => '重要'
);

/*
 * メッセージタイプ
 * ※keyの値は、DBに入れる値と直結しているので変更しないこと！
 * messageテーブルの「type」に用いる
 */
define("DB_MESSAGE_TYPE_NORMAL", (int)1);
define("DB_MESSAGE_TYPE_ALERT", (int)2);
define("DB_MESSAGE_TYPE_WARNING", (int)3);
define("DB_MESSAGE_TYPE_IMPORTANT", (int)4);
define("DB_MESSAGE_TYPE_REPORT", (int)5);
$config["DB_MESSAGE_TYPE"] = array(
	DB_MESSAGE_TYPE_NORMAL => '通常',
	DB_MESSAGE_TYPE_ALERT => '注意',
	DB_MESSAGE_TYPE_WARNING => '警告',
	DB_MESSAGE_TYPE_IMPORTANT => '重要',
	DB_MESSAGE_TYPE_REPORT => '報告'
);

/*
 * メッセージカテゴリ
 * ※keyの値は、DBに入れる値と直結しているので変更しないこと！
 * messageテーブルの「category」に用いる
 */
define("DB_MESSAGE_CATEGORY_INQUIRY", (int)1);
define("DB_MESSAGE_CATEGORY_REQUEST", (int)2);
define("DB_MESSAGE_CATEGORY_TRANSLATE", (int)3);
define("DB_MESSAGE_CATEGORY_MONEY", (int)4);
define("DB_MESSAGE_CATEGORY_HOWTO", (int)5);
define("DB_MESSAGE_CATEGORY_CLAIM", (int)6);
define("DB_MESSAGE_CATEGORY_OTHER", (int)7);
$config["DB_MESSAGE_CATEGORY"] = array(
	DB_MESSAGE_CATEGORY_INQUIRY => '質問',
	DB_MESSAGE_CATEGORY_REQUEST => 'お願い',
	DB_MESSAGE_CATEGORY_TRANSLATE => '翻訳関係',
	DB_MESSAGE_CATEGORY_MONEY => '金銭関係',
	DB_MESSAGE_CATEGORY_HOWTO => 'サイトの使い方',
	DB_MESSAGE_CATEGORY_CLAIM => 'クレーム',
	DB_MESSAGE_CATEGORY_OTHER => 'その他'
);

?>
