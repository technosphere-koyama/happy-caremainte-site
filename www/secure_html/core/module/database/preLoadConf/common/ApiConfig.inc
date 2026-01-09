<?php

/*
 * 外部APIサービス系 設定情報
 */

/* -----------
 * GENGO
 * ----------- */
/*
 * 案件の種類
 * ※keyの値は、DBに入れる値と直結しているので変更しないこと！
 * order_translate_jobテーブルの「type」に用いる
 */
define("DB_GENGO_TYPE_TEXT", (string)'text');
define("DB_GENGO_TYPE_FILE", (string)'file');
$config["DB_GENGO_TYPE"] = array(
	DB_GENGO_TYPE_TEXT => 'テキスト',
	DB_GENGO_TYPE_FILE => 'ファイル'
);

/*
 * 翻訳のトーン(テイスト)
 * order_translate_jobテーブルの「tone」に用いる
 */
define("DB_GENGO_TONE_INFORMAL", (string)'堅苦しくない');
define("DB_GENGO_TONE_FORMAL", (string)'フォーマル');
define("DB_GENGO_TONE_FRIENDLY", (string)'フレンドリー');
define("DB_GENGO_TONE_BUSINESS", (string)'ビジネス');

/*
 * 翻訳の目的
 * order_translate_jobテーブルの「purpose」に用いる
 */
define("DB_GENGO_PURPOSE_PRIVATE", (string)'個人使用');
define("DB_GENGO_PURPOSE_BUSINESS", (string)'ビジネス');
define("DB_GENGO_PURPOSE_ONLINE_CONTENTS", (string)'オンラインコンテンツ');
define("DB_GENGO_PURPOSE_WEB_OR_LOCAL", (string)'ウェブまたはアプリローカリゼーション');
define("DB_GENGO_PURPOSE_OTHER", (string)'その他');

/*
 * 翻訳品質レベル
 * ※keyの値は、DBに入れる値と直結しているので変更しないこと！
 * order_translate_jobテーブルの「ta_tier」に用いる
 */
define("DB_GENGO_QUALITY_STANDARD", (string)'standard');
define("DB_GENGO_QUALITY_PRO", (string)'pro');
$config["DB_GENGO_QUALITY"] = array(
	DB_GENGO_QUALITY_STANDARD => '標準',
	DB_GENGO_QUALITY_PRO => 'プロ'
);

/*
 * ステータス
 * ※keyの値は、DBに入れる値と直結しているので変更しないこと！
 * order_translate_jobテーブルの「ta_status」に用いる
 */
define("DB_GENGO_STATUS_QUEUED", (string)'queued');
define("DB_GENGO_STATUS_AVAILABLE", (string)'available');
define("DB_GENGO_STATUS_PENDING", (string)'pending');
define("DB_GENGO_STATUS_REVIEWABLE", (string)'reviewable');
define("DB_GENGO_STATUS_APPROVED", (string)'approved');
define("DB_GENGO_STATUS_REVISING", (string)'revising');
define("DB_GENGO_STATUS_REJECTED", (string)'rejected');
define("DB_GENGO_STATUS_CANCELED", (string)'canceled');
define("DB_GENGO_STATUS_HOLD", (string)'hold');
$config["DB_GENGO_QUALITY"] = array(
	DB_GENGO_STATUS_QUEUED => '新着案件',
	DB_GENGO_STATUS_AVAILABLE => '翻訳待機',
	DB_GENGO_STATUS_PENDING => '翻訳中',
	DB_GENGO_STATUS_REVIEWABLE => '翻訳完了',
	DB_GENGO_STATUS_APPROVED => '承認済み',
	DB_GENGO_STATUS_REVISING => '修正中',
	DB_GENGO_STATUS_REJECTED => '拒否',
	DB_GENGO_STATUS_CANCELED => 'キャンセル',
	DB_GENGO_STATUS_HOLD => '保留'
);
/* GENGO ここまで */

?>
