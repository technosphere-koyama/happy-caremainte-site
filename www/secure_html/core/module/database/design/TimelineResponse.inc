<?php

/* * **********************************
 * NAME:Timeline
 * DESC:
 *  タイムライン返信用テーブル
 * NOTICE:
 * CREATE: 2016.12.13 aoyama
 * *********************************** */
class TimelineResponse implements DatabaseDesign {

	private $table_name = 'timeline_response';

	/*	 * **********************************
	 * NAME  : get_table_name
	 * INPUT : NONE
	 * OUTPUT: string / テーブル名
	 * DESC  :
	 *  テーブル名を返す
	 * NOTICE:
	 * CREATE: 2016.10.21 aoyama
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
	 * CREATE: 2016.10.21 aoyama
	 * *********************************** */
	public function get_table_comment() {
		return "タイムラインコメントテーブル";
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
			timeline_response_id BIGINT NOT NULL PRIMARY KEY auto_increment COMMENT '管理用インクリメンタルID',
			create_time BIGINT NOT NULL,
			update_time BIGINT NOT NULL,
			active INT NOT NULL default 1,
			user_id BIGINT NOT NULL COMMENT '投稿者のuser_id',
			response_text MEDIUMTEXT NOT NULL COMMENT 'コメント文',
			timeline_id BIGINT NOT NULL COMMENT 'タイムライン投稿ID',
			parent_id BIGINT NOT NULL default 0 COMMENT '現在使用していない。'
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
		return NULL;
	}

	/*	 * **********************************
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

	/*	 * **********************************
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
		return "AUTO_INCREMENT=0";
//		return NULL;
	}

	/*	 * **********************************
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
