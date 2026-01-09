<?php

/* * **********************************
 * NAME:DatabaseDesign
 * DESC:
 *  Interface
 *  DBの構造用クラスで使用するインターフェース
 * NOTICE:
 * CREATE: 2015.08.27 hesaka
 * *********************************** */
interface DatabaseDesign {

	/* * **********************************
	 * NAME  : get_table_name
	 * DESC  :
	 *  テーブル名取得用メソッド
	 * NOTICE:
	 * CREATE: 2015.08.27 hesaka
	 * *********************************** */
	function get_table_name();

	/* * **********************************
	 * NAME  : get_design
	 * DESC  :
	 *  テーブルの構造(カラムなど)を取得するためのメソッド
	 * NOTICE:
	 *  PDO起動時のチェックでテーブルがない場合に、
	 *  テーブルを作るために使用される
	 * CREATE: 2015.08.27 hesaka
	 * *********************************** */
	function get_design();

	/* * **********************************
	 * NAME  : get_pre_set_records
	 * DESC  :
	 *  PDO起動時のチェックでテーブルのテーブル作成時に、
	 *  初期レコードインストールを行う必要がある場合に実行され
	 *  INSERT文が取得される
	 * NOTICE:
	 * CREATE: 2015.08.27 hesaka
	 * *********************************** */
	function get_pre_set_records();

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
	function pre_import();

	/* * **********************************
	 * NAME  : get_strage_engine
	 * DESC  :
	 *  CREATE TABLEする際にストレージエンジンを指定する
	 * NOTICE:
	 * CREATE: 2015.11.17 hesaka
	 * *********************************** */
	function get_strage_engine();
	
}

?>
