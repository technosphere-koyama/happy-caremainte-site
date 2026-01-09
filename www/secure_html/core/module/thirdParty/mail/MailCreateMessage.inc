<?php

/* * **********************************
 * NAME:MailCreateMessage
 * DESC:
 *  メールbody作成クラス
 *  共通化が必要なbody作成をここに纏める
 * NOTICE:
 * CREATE: 2016.02.24 hesaka
 * *********************************** */
class MailCreateMessage {

	/*
	 * constructor
	 */
	public function __construct() {
	}
	
	/*	 * **********************************
	 * NAME  : get_translate_purchase_info
	 * INPUT : shop_code / string / ショップコード
	 *         shop_name / string / ショップ名
	 *         user_data / array / ユーザ情報
	 *         pay_result / array / 決済情報
	 *         quote / array / 見積もり情報
	 * OUTPUT: string / メール用に整形された購入情報
	 *         false / 失敗
	 * DESC  :
	 *  翻訳依頼完了時に送信するメールに記載する決済情報を作成する
	 * NOTICE:
	 *  そのまま記載できる形で生成するので、受け取り側は
	 *  そのまま記載すれば良い
	 * CREATE: 2016.09.28 hesaka
	 * *********************************** */
	public function get_translate_purchase_info($shop_code, $shop_name, $user_data, $pay_result, $quote) {

		/*
		 * 購入基本情報
		 */
		$order_info = StaticFunction::language_text_replace(array(
			'SEARCH' => array('order_id'),
			'REPLACE' => array($pay_result['order_id']),
			'TARGET' => CONF::read('LANG_TEXT.MAIL.PURCHASE_TRANSLATE.MESSAGE_2')
		));

		/*
		 * 注文者情報
		 */
		$order_info .= StaticFunction::language_text_replace(array(
			'SEARCH' => array('name', 'sex'),
			'REPLACE' => array(
				$user_data[0]['name'],
				CONF::read('DB_SEX')[$user_data[0]['sex']]
			),
			'TARGET' => CONF::read('LANG_TEXT.MAIL.PURCHASE_TRANSLATE.MESSAGE_3')
		));

		//登録されていれば生年月日も出力
		if (!StaticFunction::is_empty($user_data[0]['birthday'])) {
			$order_info .= StaticFunction::language_text_replace(array(
				'SEARCH' => array('birth_date'),
				'REPLACE' => array(
					DbDateTime::get_datetime_type_hyphen(
						DbDateTime::fairing_digit_8($user_data[0]['birthday'])
					)
				),
				'TARGET' => CONF::read('LANG_TEXT.MAIL.PURCHASE_TRANSLATE.MESSAGE_4')
			));
		}

		//登録されていれば生年月日も出力
		if (!StaticFunction::is_empty($user_data[0]['phone'])) {
			$order_info .= StaticFunction::language_text_replace(array(
				'SEARCH' => array('phone'),
				'REPLACE' => array($user_data[0]['phone']),
				'TARGET' => CONF::read('LANG_TEXT.MAIL.PURCHASE_TRANSLATE.MESSAGE_5')
			));
		}

		//メールアドレス
		$order_info .= StaticFunction::language_text_replace(array(
			'SEARCH' => array('mail_address'),
			'REPLACE' => array($user_data[0]['mail_address']),
			'TARGET' => CONF::read('LANG_TEXT.MAIL.PURCHASE_TRANSLATE.MESSAGE_6')
		));

		/*
		 * 購入情報
		 */
		$order_info .= StaticFunction::language_text_replace(array(
			'SEARCH' => array('shop_code', 'shop_name', 'unit_count', 'credits'),
			'REPLACE' => array(
				$shop_code,
				$shop_name,
				$quote['unit_count'],
				number_format($quote['service_credits'])	//サービス利用料含む方
			),
			'TARGET' => CONF::read('LANG_TEXT.MAIL.PURCHASE_TRANSLATE.MESSAGE_7')
		));

		return $order_info;
	}
	
}

?>
