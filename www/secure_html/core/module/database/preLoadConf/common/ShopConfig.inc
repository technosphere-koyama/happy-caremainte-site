<?php

/*
 * ショップ系設定情報
 */


/* -----------
 * フォロー系
 * ----------- */
define("DB_FOLLOW_STATUS_OFF", (int)0);
define("DB_FOLLOW_STATUS_ON", (int)1);
$config["DB_FOLLOW_STATUS"] = array(
	DB_FOLLOW_STATUS_OFF => '未承認',
	DB_FOLLOW_STATUS_ON => '承認'
);

/* -----------
 * イベント系
 * ----------- */
/*
 * イベント承認依頼ステータス
 * サプライヤがイベントを登録する際に取り得るステータス。
 * ※keyの値は、DBに入れる値と直結しているので変更しないこと！
 * host_bankテーブルの「type」に用いる
 */
define("DB_EVENT_STATUS_DRAFT", (int)1);
define("DB_EVENT_STATUS_RECEPTION", (int)2);
define("DB_EVENT_STATUS_TRANSLATION", (int)3);
define("DB_EVENT_STATUS_CHECK", (int)4);
define("DB_EVENT_STATUS_REJECT", (int)5);
define("DB_EVENT_STATUS_ADD_DRAFT", (int)6);
define("DB_EVENT_STATUS_ADD_RECEPTION", (int)7);
define("DB_EVENT_STATUS_ADD_TRANSLATION", (int)8);
define("DB_EVENT_STATUS_ADD_CHECK", (int)9);
define("DB_EVENT_STATUS_ADD_REJECT", (int)10);
define("DB_EVENT_STATUS_APPROVAL", (int)11);
$config["DB_EVENT_STATUS"] = array(
	DB_EVENT_STATUS_DRAFT => '下書き',
	DB_EVENT_STATUS_RECEPTION => '受付',
	DB_EVENT_STATUS_TRANSLATION => '翻訳中',
	DB_EVENT_STATUS_CHECK => 'チェック中',
	DB_EVENT_STATUS_REJECT => '否認',
	DB_EVENT_STATUS_ADD_DRAFT => '追加下書き',
	DB_EVENT_STATUS_ADD_RECEPTION => '追加受付',
	DB_EVENT_STATUS_ADD_TRANSLATION => '追加翻訳中',
	DB_EVENT_STATUS_ADD_CHECK => '追加チェック中',
	DB_EVENT_STATUS_ADD_REJECT => '追加否認',
	DB_EVENT_STATUS_APPROVAL => '承認済み'
);

/*
 * イベント属性inputタイプ
 * ※keyの値は、DBに入れる値と直結しているので変更しないこと！
 * event_attributeテーブルの「input_type」に用いる
 */
define("DB_EVENT_ATTR_INPUT_TYPE_CHECK", (int)1);
define("DB_EVENT_ATTR_INPUT_TYPE_RADIO", (int)2);
define("DB_EVENT_ATTR_INPUT_TYPE_SELECT", (int)3);


/* -----------
 * ショップ系
 * ----------- */
/*
 * ショップ承認依頼ステータス
 * サプライヤがショップを登録する際に取り得るステータス。
 * ※keyの値は、DBに入れる値と直結しているので変更しないこと！
 * host_bankテーブルの「type」に用いる
 */
define("DB_SHOP_STATUS_DRAFT", (int)1);
define("DB_SHOP_STATUS_RECEPTION", (int)2);
define("DB_SHOP_STATUS_TRANSLATION", (int)3);
define("DB_SHOP_STATUS_CHECK", (int)4);
define("DB_SHOP_STATUS_REJECT", (int)5);
define("DB_SHOP_STATUS_APPROVAL", (int)6);
$config["DB_SHOP_STATUS"] = array(
	DB_SHOP_STATUS_DRAFT => '下書き',
	DB_SHOP_STATUS_RECEPTION => '受付',
	DB_SHOP_STATUS_TRANSLATION => '翻訳中',
	DB_SHOP_STATUS_CHECK => 'チェック中',
	DB_SHOP_STATUS_REJECT => '否認',
	DB_SHOP_STATUS_APPROVAL => '承認済み'
);


/* -----------
 * 決済系
 * ----------- */
/*
 * 決済タイプ
 * ※api_id_counterでのレコード特定に使用されるので変更の際は気を付けること！
 */
define("DB_PAYMENT_TYPE_EVENT", (string)'E');
define("DB_PAYMENT_TYPE_TRANSLATE", (string)'T');

/*
 * 決済方法
 * ※keyの値は、DBに入れる値と直結しているので変更しないこと！
 * order_event, order_translateテーブルの「payment_method」に用いる
 */
define("DB_PAYMENT_METHOD_CARD", (int)1);
define("DB_PAYMENT_METHOD_CASH_ON_DELIVERY", (int)2);
define("DB_PAYMENT_METHOD_BANK_TRANSFER", (int)3);
$config['DB_PAYMENT_METHOD'] = array(
	DB_PAYMENT_METHOD_CARD => 'クレジットカード',
	DB_PAYMENT_METHOD_CASH_ON_DELIVERY => '代金引換払い',
	DB_PAYMENT_METHOD_BANK_TRANSFER => '銀行振込'
);
$config['DB_PAYMENT_METHOD_FOR_LIST'] = array(
	DB_PAYMENT_METHOD_CARD => 'クレ',
	DB_PAYMENT_METHOD_CASH_ON_DELIVERY => '代引',
	DB_PAYMENT_METHOD_BANK_TRANSFER => '銀振'
);


/* -----------
 * payment_result系
 * ----------- */
/*
 * 購入結果
 */
define("DB_PAYMENT_RESULT_SUCCESS", (int)1);
define("DB_PAYMENT_RESULT_ERR_GMO", (int)2);
define("DB_PAYMENT_RESULT_ERR_GENGO", (int)3);
define("DB_PAYMENT_RESULT_ERR_GENGO_BUT_SUCCESS_GMO", (int)4);
define("DB_PAYMENT_RESULT_ERR_HOLD_ON", (int)5);
define("DB_PAYMENT_RESULT_ERR_HOLD_OUT", (int)6);
define("DB_PAYMENT_RESULT_ERR_ORDER_INSERT", (int)7);
define("DB_PAYMENT_RESULT_ERR_OTHER", (int)8);
$config['DB_PAYMENT_RESULT'] = array(
	DB_PAYMENT_RESULT_SUCCESS => '成功',
	DB_PAYMENT_RESULT_ERR_GMO => 'GMO決済エラー',
	DB_PAYMENT_RESULT_ERR_GENGO => 'GENGO翻訳エラー',
	DB_PAYMENT_RESULT_ERR_GENGO_BUT_SUCCESS_GMO => 'GENGO失敗GMO成功エラー',
	DB_PAYMENT_RESULT_ERR_HOLD_ON => '仮押さえエラー',
	DB_PAYMENT_RESULT_ERR_HOLD_OUT => '仮押さえ開放エラー',
	DB_PAYMENT_RESULT_ERR_ORDER_INSERT => 'OrderInsertエラー',
	DB_PAYMENT_RESULT_ERR_OTHER => 'その他エラー'
);


/* -----------
 * 出金系
 * ----------- */
/*
 * 口座種別
 * ※keyの値は、DBに入れる値と直結しているので変更しないこと！
 * host_bankテーブルの「type」に用いる
 */
define("DB_BANK_ACCOUNT_TYPE_NORMAL", (int)1);
define("DB_BANK_ACCOUNT_TYPE_CURRENT", (int)2);
define("DB_BANK_ACCOUNT_TYPE_SAVINGS", (int)4);
$config["DB_BANK_ACCOUNT_TYPE"] = array(
	DB_BANK_ACCOUNT_TYPE_NORMAL => '普通',
	DB_BANK_ACCOUNT_TYPE_CURRENT => '当座',
	DB_BANK_ACCOUNT_TYPE_SAVINGS => '貯蓄',
);

/*
 * 出金ステータス
 * ゲストが購入したチケットに対して、サービサはホストとサプライヤに入金しないといけない。
 * ホストとサプライヤから出金申請があった場合に、サービサは出金を行う。
 * ※keyの値は、DBに入れる値と直結しているので変更しないこと！
 * withdrawalテーブルの「status」に用いる
 */
define("DB_WITHDRAWAL_STATUS_IMPOSSIBLE", (int)1);
define("DB_WITHDRAWAL_STATUS_POSSIBLE", (int)2);
define("DB_WITHDRAWAL_STATUS_REQUEST", (int)3);
define("DB_WITHDRAWAL_STATUS_COMPLETE", (int)4);
$config["DB_WITHDRAWAL_STATUS"] = array(
	DB_WITHDRAWAL_STATUS_IMPOSSIBLE => '-',
	DB_WITHDRAWAL_STATUS_POSSIBLE => '出金可能',
	DB_WITHDRAWAL_STATUS_REQUEST => '出金依頼中',
	DB_WITHDRAWAL_STATUS_COMPLETE => '出金済み'
);

/*
 * 出金確認ステータス
 * ゲスト・ホストが入金されたかを確認したかのステータス
 * ※keyの値は、DBに入れる値と直結しているので変更しないこと！
 * withdrawalテーブルの「is_check」に用いる
 */
define("DB_WITHDRAWAL_CONFIRM_NOT", (int)0);
define("DB_WITHDRAWAL_CONFIRM_DONE", (int)1);
$config['DB_WITHDRAWAL_CONFIRM'] = array(
	DB_WITHDRAWAL_CONFIRM_NOT => '未',
	DB_WITHDRAWAL_CONFIRM_DONE => '済み'
);

/*
 * ゆうちょ銀行の識別コード
 * ゆうちょ銀行かどうかの判定に使用する。
 * bank_masterを変更した場合は、こちらも修正すること。
 */
define("DB_BANK_JPBANK_CODE", (int)9900);

/* -----------
 * order_translate系
 * ----------- */
/*
 * 対象オブジェクト
 * ※keyの値は、DBに入れる値と直結しているので変更しないこと！
 * order_translate_requestテーブルの「target_object」に用いる
 * ※valueもテーブル名作成などに使用しているので変更しないこと！
 */
define("DB_ORDER_TRANSLATE_TARGET_SHOP", (int)1);
define("DB_ORDER_TRANSLATE_TARGET_EVENT", (int)2);
$config["DB_ORDER_TRANSLATE_TARGET"] = array(
	DB_ORDER_TRANSLATE_TARGET_SHOP => 'shop',
	DB_ORDER_TRANSLATE_TARGET_EVENT => 'event'
);

/*
 * ターゲットリスト日本語版
 * 翻訳履歴一覧の検索に用いる想定
 */
$config["DB_ORDER_TRANSLATE_TARGET_JP"] = array(
	DB_ORDER_TRANSLATE_TARGET_SHOP => 'ショップ',
	DB_ORDER_TRANSLATE_TARGET_EVENT => 'イベント'
);

/*
 * 翻訳ステータス(サプライヤの翻訳履歴用)
 * 翻訳履歴一覧に用いる想定
 */
define("DB_ORDER_TRANSLATE_STATUS_FOR_SUPPLIER_NOT_COMP", (int)1);
define("DB_ORDER_TRANSLATE_STATUS_FOR_SUPPLIER_COMP", (int)2);
define("DB_ORDER_TRANSLATE_STATUS_FOR_SUPPLIER_CANCEL", (int)3);
$config["DB_ORDER_TRANSLATE_STATUS_FOR_SUPPLIER"] = array(
	DB_ORDER_TRANSLATE_STATUS_FOR_SUPPLIER_NOT_COMP => '翻訳中',
	DB_ORDER_TRANSLATE_STATUS_FOR_SUPPLIER_COMP => '翻訳完了',
	DB_ORDER_TRANSLATE_STATUS_FOR_SUPPLIER_CANCEL=> 'キャンセル'
);

/* -----------
 * order_event系
 * ----------- */
/*
 * イベント申込みステータス
 * ゲストが購入したイベントに参加したかどうかのステータス。
 * ※keyの値は、DBに入れる値と直結しているので変更しないこと！
 * order_eventテーブルの「status」に用いる
 */
define("DB_ORDER_EVENT_STATUS_RECEPTION", (int)1);
define("DB_ORDER_EVENT_STATUS_COMPLETE", (int)2);
define("DB_ORDER_EVENT_STATUS_CANCEL", (int)3);
$config['DB_ORDER_EVENT_STATUS'] = array(
	DB_ORDER_EVENT_STATUS_RECEPTION => '注文受付',
	DB_ORDER_EVENT_STATUS_COMPLETE => '来店済',
	DB_ORDER_EVENT_STATUS_CANCEL => 'キャンセル'
);

/*
 * 販売モード
 * ※keyの値は、DBに入れる値と直結しているので変更しないこと！
 * order_event_byテーブルの「sale_mode」に用いる
 */
define("DB_SALE_MODE_NORMAL", (int)1);
define("DB_SALE_MODE_SPECIAL", (int)2);
$config['DB_SALE_MODE'] = array(
	DB_SALE_MODE_NORMAL => '通常',
	DB_SALE_MODE_SPECIAL => '特別'
);

/*
 * キャンセルの種類
 * ※keyの値は、DBに入れる値と直結しているので変更しないこと！
 * order_event_uniqueテーブルの「cancel_category」に用いる
 */
define("DB_CANCEL_CATEGORY_NOT_RETURN_STOCK", (int)1);
define("DB_CANCEL_CATEGORY_RETURN_STOCK", (int)2);
$config['DB_CANCEL_CATEGORY'] = array(
	DB_CANCEL_CATEGORY_NOT_RETURN_STOCK => '通常キャンセル(在庫戻らない)',
	DB_CANCEL_CATEGORY_RETURN_STOCK => '在庫戻しキャンセル'
);

/*
 * キャンセル理由
 * ※keyの値は、DBに入れる値と直結しているので変更しないこと！
 * order_event_uniqueテーブルの「cancel_reason」に用いる
 */
define("DB_CANCEL_REASON_CUSTOMER", (int)1);
define("DB_CANCEL_REASON_SUPPLIER", (int)2);
define("DB_CANCEL_REASON_STOCK_OUT", (int)3);
define("DB_CANCEL_REASON_DEFECT", (int)4);
define("DB_CANCEL_REASON_OTHER", (int)5);
$config['DB_CANCEL_REASON'] = array(
	DB_CANCEL_REASON_CUSTOMER => 'お客様都合',
	DB_CANCEL_REASON_SUPPLIER => 'サプライヤ都合',
	DB_CANCEL_REASON_STOCK_OUT => '在庫数問題',
	DB_CANCEL_REASON_DEFECT => 'サービス不備',
	DB_CANCEL_REASON_OTHER => 'その他'
);

?>
