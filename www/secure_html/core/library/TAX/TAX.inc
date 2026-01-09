<?php

/* * **********************************
 * NAME:TAX
 * DESC:
 *  税額計算用ライブラリ
 * NOTICE:
 *  税率自体は、shop_masterテーブルのtax_rateカラムに
 *  入っている数値を利用する
 *  ※8%なら「8」と入っている
 * 
 * -------------------------------------------
 *  消費税を計算するルール
 * 
 * 【税別金額からの計算】
 *  ・商品金額に(tax_rate/100)を掛けて税額のみ算出
 *  　その際端数がでた場合は「切り捨て」
 *  　その値を税額とする
 *  　税込金額は，商品金額にその税額を足したものとする
 * 
 * 【税込金額からの計算】
 *  ・税込金額に(tax_rate/100)を割って税額のみ算出
 *  　その際に端数がでた場合は「切り上げ」
 *  　その値を税額とする
 *  　税抜き金額は、税込み金額から税額を引いたものとする
 * 
 *  ・複数商品の税額計算を行う場合は、トータルに掛けるのではなく、
 *  　1商品ずつ算出したものを合算すること
 *  　※1商品だけキャンセルされた場合などにずれが生じる可能性があるため
 * -------------------------------------------
 * 
 * CREATE: 2015.11.23 hesaka
 * *********************************** */
class TAX {

	/* * **********************************
	 * NAME  : get_tax_by_item_price
	 * INPUT : item_price / integer / 商品単価(税抜き)
	 * OUTPUT: integer / 税額
	 * DESC  :
	 *  税抜き商品単価から税額を取得する
	 * NOTICE:
	 *  返される値は税込み商品金額ではないので注意すること！
	 * CREATE: 2015.11.23 hesaka
	 * *********************************** */
	public static function get_tax_by_item_price($item_price) {

		//引数が空の場合はエラー
		if (StaticFunction::is_empty($item_price)) {
			return NULL;
		}

		/*
		 *  ・商品金額に(tax_rate/100)を掛けて税額のみ算出
		 *  　その際端数がでた場合は「切り捨て」
		 *  　その値を税額とする
		 */
		return floor($item_price * (float)(CONF::read('DB_SERVICE_MASTER.TAX_RATE') / 100));
	}

	/* * **********************************
	 * NAME  : get_include_by_item_price
	 * INPUT : item_price / integer / 商品単価(税抜き)
	 * OUTPUT: integer / 税込み商品金額
	 * DESC  :
	 *  税抜き商品単価から税込み商品金額を取得する
	 * NOTICE:
	 *  返される値は税額ではないので注意すること！
	 * CREATE: 2015.11.23 hesaka
	 * *********************************** */
	public static function get_include_by_item_price($item_price) {

		//引数が空の場合はエラー
		if (StaticFunction::is_empty($item_price)) {
			return NULL;
		}

		/*
		 *  　税込金額は，商品金額にその税額を足したものとする
		 */
		return $item_price + self::get_tax_by_item_price($item_price);
	}

	/* * **********************************
	 * NAME  : get_tax_by_included
	 * INPUT : included / integer / 税込み商品金額
	 * OUTPUT: integer / 税額
	 * DESC  :
	 *  税込み商品金額から税額を取得する
	 * NOTICE:
	 *  返される値は税込み商品金額ではないので注意すること！
	 * CREATE: 2015.11.23 hesaka
	 * *********************************** */
	public static function get_tax_by_included($included) {

		//引数が空の場合はエラー
		if (StaticFunction::is_empty($included)) {
			return NULL;
		}

		/*
		 *  ・税込金額に(tax_rate/100)を割って税額のみ算出
		 *  　その際に端数がでた場合は「切り上げ」
		 *  　その値を税額とする
		 * 
		 * 税込み額 × 消費税率 ÷ (100 ＋ 消費税率) = 消費税額
		 */
		return ceil($included * CONF::read('DB_SERVICE_MASTER.TAX_RATE') / (100 + CONF::read('DB_SERVICE_MASTER.TAX_RATE')));
	}

	/* * **********************************
	 * NAME  : get_item_price_by_included
	 * INPUT : included / integer / 税込み商品金額
	 * OUTPUT: integer / 税抜き商品単価
	 * DESC  :
	 *  税込み商品金額から税抜き商品単価を取得する
	 * NOTICE:
	 *  返される値は税額ではないので注意すること！
	 * CREATE: 2015.11.23 hesaka
	 * *********************************** */
	public static function get_item_price_by_included($included) {

		//引数が空の場合はエラー
		if (StaticFunction::is_empty($included)) {
			return NULL;
		}

		/*
		 *  　税抜き金額は、税込み金額から税額を引いたものとする
		 */
		return $included - self::get_tax_by_included($included);
	}

}

?>
