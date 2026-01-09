<?php

/* * **********************************
 * NAME:DebugBarData
 * DESC:
 *  DebugBar用のテーブル
 * NOTICE:
 * CREATE: 2015.08.27 hesaka
 * *********************************** */
class DebugBarData implements DatabaseDesign {

	private $table_name = 'debug_bar_data';
	
	/* * **********************************
	 * NAME  : get_table_name
	 * INPUT : NONE
	 * OUTPUT: string / テーブル名
	 * DESC  :
	 *  テーブル名を返す
	 * NOTICE:
	 * CREATE: 2015.08.27 hesaka
	 * *********************************** */
	public function get_table_name() {
		return $this->table_name;
	}

	/* * **********************************
	 * NAME  : get_table_comment
	 * INPUT : NONE
	 * OUTPUT: string / TABLE用のコメント
	 *         NULL / オプション不要の場合
	 * DESC  :
	 *  テーブルの説明を設定する
	 * NOTICE:
	 *  ※ない場合はNULLを返すこと
	 * CREATE: 2016.09.07 hesaka
	 * *********************************** */
	public function get_table_comment() {
		return "デバッグバー専用ログテーブル";
	}
	
	/* * **********************************
	 * NAME  : get_design
	 * INPUT : NONE
	 * OUTPUT: string / CREATE TABLE に用いる構造テキスト
	 * DESC  :
	 *  テーブルの構造を返す
	 * NOTICE:
	 * CREATE: 2015.08.27 hesaka
	 * *********************************** */
	public function get_design() {

		return "
			`id` BIGINT(32) UNSIGNED NOT NULL AUTO_INCREMENT,
			`data` TEXT COMMENT 'データ本体',
			`meta_utime` CHAR(255) COMMENT 'システムタイム',
			`meta_datetime` DATETIME COMMENT '時刻',
			`meta_uri` CHAR(255) COMMENT 'アクセスURL',
			`meta_ip` CHAR(255) COMMENT 'アクセス元IPアドレス',
			`meta_method` CHAR(255) COMMENT 'POST or GET',

			PRIMARY KEY (`id`),
			INDEX idx_debugbar_meta_datetime (`meta_datetime`),
			INDEX idx_debugbar_meta_uri (`meta_uri`),
			INDEX idx_debugbar_meta_ip (`meta_ip`)
		";

	}

	/* * **********************************
	 * NAME  : get_pre_set_records
	 * INPUT : NONE
	 * OUTPUT: string / INSERT に用いるレコードテキスト
	 *         NULL / 初期INSERT不要の場合
	 * DESC  :
	 *  プリセットレコードがあれば指定する
	 * NOTICE:
	 *  ※ない場合はNULLを返すこと
	 * CREATE: 2015.08.27 hesaka
	 * *********************************** */
	public function get_pre_set_records() {
		return NULL;
	}

	/* * **********************************
	 * NAME  : pre_import
	 * INPUT : NONE
	 * OUTPUT: NONE
	 * DESC  :
	 *  最初にCSVからインポートする必要があれば
	 *  それを行う
	 * NOTICE:
	 *  ※ない場合はNULLを返すこと
	 * CREATE: 2015.12.10 hesaka
	 * *********************************** */
	public function pre_import() {
		return NULL;
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
		return "AUTO_INCREMENT=1";
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
