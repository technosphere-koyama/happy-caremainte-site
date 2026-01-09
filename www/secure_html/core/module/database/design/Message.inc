<?php

/* * **********************************
 * NAME:UserPublic
 * DESC:
 *  PUBLIC側ユーザ情報を保存するテーブル
 * NOTICE:
 * CREATE: 2016.10.11 aoyama
 * *********************************** */
class Message implements DatabaseDesign {

	private $table_name = 'message';

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
		return "メッセージの送信テーブル";
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
			message_id BIGINT NOT NULL PRIMARY KEY auto_increment,
			create_time BIGINT NOT NULL,
			update_time BIGINT NOT NULL,
			user_id BIGINT NOT NULL,
			user_show INT NOT NULL default 1 COMMENT '送信者側の表示状態 0:非表示 1:表示',
			message_comment MEDIUMTEXT NOT NULL,
			read_status INT NOT NULL default 1 COMMENT '1：未読　2：既読',
			target_user BIGINT NOT NULL COMMENT '送信先ユーザーID',
			target_show INT NOT NULL default 1,
			active INT NOT NULL default 1,
			image_file VARCHAR(255) COMMENT '画像ファイル名'
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
