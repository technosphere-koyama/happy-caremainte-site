<?php

/* * **********************************
 * NAME:FashionTypeMaster
 * DESC:
 *  ファッションタイプマスタテーブル
 * NOTICE:
 * CREATE: 2016.10.11 aoyama
 * *********************************** */
class FashionTypeMaster implements DatabaseDesign {

	private $table_name = 'fashion_type_master';

	/* * **********************************
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

	/* * **********************************
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
		return "ファッションタイプマスタ";
	}

	/* * **********************************
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
			fashion_id BIGINT NOT NULL PRIMARY KEY auto_increment,
			create_time BIGINT NOT NULL,
			update_time BIGINT NOT NULL,
			active INT NOT NULL default 1,
			sort_num INT,
			fashion_name TEXT NOT NULL
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
	 * CREATE: 2016.10.11 aoyama
	 * *********************************** */
	public function get_pre_set_records() {

		$datetime = DbDateTime::get_cur_datetime();
		return "
			(
				create_time,
				update_time,
				active,
				sort_num,
				fashion_name
			)
			VALUES 
			(
				".$datetime.", 
				".$datetime.", 
				" . DB_ACTIVE_ON . ",
				1,
				'カジュアル'
			),
			(
				".$datetime.", 
				".$datetime.", 
				" . DB_ACTIVE_ON . ",
				2,
				'コンサバ'
			),
			(
				".$datetime.", 
				".$datetime.", 
				" . DB_ACTIVE_ON . ",
				3,
				'モード'
			),
			(
				".$datetime.", 
				".$datetime.", 
				" . DB_ACTIVE_ON . ",
				4,
				'フォーマル'
			),
			(
				".$datetime.", 
				".$datetime.", 
				" . DB_ACTIVE_ON . ",
				5,
				'フェミニン'
			),
			(
				".$datetime.", 
				".$datetime.", 
				" . DB_ACTIVE_ON . ",
				6,
				'ガーリー'
			),
			(
				".$datetime.", 
				".$datetime.", 
				" . DB_ACTIVE_ON . ",
				7,
				'ナチュラル'
			),
			(
				".$datetime.", 
				".$datetime.", 
				" . DB_ACTIVE_ON . ",
				8,
				'トラッド'
			),
			(
				".$datetime.", 
				".$datetime.", 
				" . DB_ACTIVE_ON . ",
				9,
				'マニッシュ'
			),
			(
				".$datetime.", 
				".$datetime.", 
				" . DB_ACTIVE_ON . ",
				10,
				'スポーティ'
			),
			(
				".$datetime.", 
				".$datetime.", 
				" . DB_ACTIVE_ON . ",
				11,
				'アメカジ'
			),
			(
				".$datetime.", 
				".$datetime.", 
				" . DB_ACTIVE_ON . ",
				12,
				'ストリート'
			),
			(
				".$datetime.", 
				".$datetime.", 
				" . DB_ACTIVE_ON . ",
				13,
				'アウトドア' 
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
	 *  ※ない場合はNULLを返すこと
	 * CREATE: 2016.10.11 aoyama
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
	 * CREATE: 2016.10.11 aoyama
	 * *********************************** */
	public function get_option() {
		return "AUTO_INCREMENT=1";
	}

	/* * **********************************
	 * NAME  : get_strage_engine
	 * DESC  :
	 *  CREATE TABLEする際にストレージエンジンを指定する
	 * NOTICE:
	 * CREATE: 2016.10.11 aoyama
	 * *********************************** */
	public function get_strage_engine() {
		return "INNODB";
	}

}

?>
