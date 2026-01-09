<?php

/* * **********************************
 * NAME:ServiceNews
 * DESC:
 *  サービスニューステーブル
 * NOTICE:
 * CREATE: 2016.10.19 aoyama
 * *********************************** */
class ServiceNews implements DatabaseDesign {

	private $table_name = 'service_news';

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
		return "サービスニュース";
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
			news_id BIGINT NOT NULL PRIMARY KEY auto_increment COMMENT 'インクリメンタルID(必須)',
			create_time BIGINT NOT NULL COMMENT '登録日時',
			update_time BIGINT NOT NULL COMMENT '更新日時',
			news_title TEXT NOT NULL COMMENT 'ニュースタイトル',
			news_text MEDIUMTEXT NOT NULL COMMENT 'ニュースの本文'
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

		$datetime = DbDateTime::get_cur_datetime();
		return "
			(
				create_time,
				update_time,
				news_title,
				news_text
			)
			VALUES 
			(
				" . $datetime . ",
				" . $datetime . ",
					'ハッピーからのご案内',
				'毎年悩む、衣替えのタイミング。
まだ暑い？もぅ寒い！時期を見極めるポイントは気温です。秋の衣替えは20℃前後の気温が安定的に続いてきたらはじめましょう。

日々の気温を参考に衣替えのタイミングを逃さないようにしましょう。'
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
		return "AUTO_INCREMENT=10001";
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
