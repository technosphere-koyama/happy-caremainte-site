<?php

/* * **********************************
 * NAME:CareResponse
 * DESC:
 *  ケアメンテの最新情報を格納。CRONで定期取得し差があれば更新。1レコードのみ
 * NOTICE:
 * CREATE: 2016.11.14 aoyama
 * *********************************** */
class CareNewsLog implements DatabaseDesign {

	private $table_name = 'care_news_log';

	/*	 * **********************************
	 * NAME  : get_table_name
	 * INPUT : NONE
	 * OUTPUT: string / テーブル名
	 * DESC  :
	 *  テーブル名を返す
	 * NOTICE:
	 * CREATE: 2016.10.11 aoyama
	 * *********************************** */
	public function get_table_name() {
		return $this->table_name;
	}

	/*	 * **********************************
	 * NAME  : get_table_comment
	 * INPUT : NONE
	 * OUTPUT: string / TABLE用のコメント
	 *         NULL / オプション不要の場合
	 * DESC  :
	 *  テーブルの説明を設定する
	 * NOTICE:
	 *  ※ない場合はNULLを返すこと
	 * CREATE: 2016.10.11 aoyama
	 * *********************************** */
	public function get_table_comment() {
		return "ケアメンテの最新情報を格納。CRONで定期取得し差があれば更新するテーブル";
	}

	/*	 * **********************************
	 * NAME  : get_design
	 * INPUT : NONE
	 * OUTPUT: string / CREATE TABLE に用いる構造テキスト
	 * DESC  :
	 *  テーブルの構造を返す
	 * NOTICE:
	 * CREATE: 2016.10.11 aoyama
	 * *********************************** */
	public function get_design() {

		return "
			care_news_id BIGINT NOT NULL PRIMARY KEY auto_increment,
			create_time BIGINT NOT NULL,
			update_time BIGINT NOT NULL,
			care_item_id VARCHAR(255) NOT NULL
		";
	}

	/*	 * **********************************
	 * NAME  : get_pre_set_records
	 * INPUT : NONE
	 * OUTPUT: string / INSERT に用いるレコードテキスト
	 *         NULL / 初期INSERT不要の場合
	 * DESC  :
	 * NOTICE:
	 *  ※ない場合はNULLを返すこと
	 * CREATE: 2015.08.27 hesaka
	 * *********************************** */
	public function get_pre_set_records() {

//		$system_id1 = StaticFunction::create_id(); /* システムIDの発行 */
		$datetime = DbDateTime::get_cur_datetime();
		
		return "
			(
				create_time,
				update_time,
				care_item_id
			)
			VALUES
			(
				" . $datetime . ",
				" . $datetime . ",
				''
			);";
	}


/* * **********************************
 * NAME  : pre_import
 * INPUT : NONE
 * OUTPUT: NONE
 * DESC  :
 *  最初にCSVからインポートする必要があれば
 *  それを行う
 * NOTICE:
 *  create_timeに空が存在する。なので現在時間を入れる。
 * CREATE: 2015.12.12 aoyama
 * *********************************** */
public function pre_import() {
return;
}

/* * **********************************
 * NAME  : get_option
 * INPUT : NONE
 * OUTPUT: string / CREATE TABLE のオプション
 *         NULL / オプション不要の場合
 * DESC  :
 *  オプションがあれば指定する
 * NOTICE:
 *  ※ない場合はNULLを返すこと
 * CREATE: 2015.08.27 hesaka
 * *********************************** */
public function get_option() {
return "AUTO_INCREMENT=10001";
//		return NULL;
}

/* * **********************************
 * NAME  : get_strage_engine
 * DESC  :
 *  CREATE TABLEする際にストレージエンジンを指定する
 * NOTICE:
 * CREATE: 2015.11.17 hesaka
 * *********************************** */
public function get_strage_engine() {
return "INNODB";
}

}

?>
