<?php

/* * **********************************
 * NAME: LogLogin
 * DESC:
 *  ログインログ用テーブル
 * NOTICE:
 * CREATE: 2016.09.07 hesaka
 * *********************************** */
class LogLogin implements DatabaseDesign {

	private $table_name = 'log_login';

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
		return "ログインログ用テーブル\n※将来ログイン集計する際に必要になるので予め取得だけしておく";
	}
	
	/* * **********************************
	 * NAME  : get_design
	 * INPUT : NONE
	 * OUTPUT: string / CREATE TABLE に用いる構造テキスト
	 * DESC  :
	 *  テーブルの構造を返す
	 * NOTICE:
	 * CREATE: 2016.09.07 hesaka
	 * *********************************** */
	public function get_design() {

		return "
			`log_id` BIGINT(16) UNSIGNED NOT NULL AUTO_INCREMENT COMMENT 'イベントID(必須)',

			`user_type` INT(8) NOT NULL DEFAULT " . DB_USER_TYPE_PUBLIC . " COMMENT 'ユーザタイプ(1:パブリックユーザ, 2:システムユーザ)',
			`user_id` BIGINT(16) UNSIGNED NOT NULL COMMENT 'ユーザID',
			`login_time` BIGINT(14) UNSIGNED NULL COMMENT 'ログイン時刻',

			PRIMARY KEY (`log_id`),
			INDEX `user_id_INDEX` (`user_id`),
			INDEX `login_time_INDEX` (`login_time`)
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
		return "MYISAM";
	}

}

?>
