<?php

/* * **********************************
 * NAME:UserPublic
 * DESC:
 *  PUBLIC側ユーザ情報を保存するテーブル
 * NOTICE:
 * CREATE: 2016.09.07 hesaka
 * *********************************** */
class UserPublic implements DatabaseDesign {

	private $table_name = 'user_public';

	/*	 * **********************************
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
		return "SNSユーザマスタテーブル\n※各権限はフラグで管理";
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
			user_id BIGINT NOT NULL PRIMARY KEY auto_increment COMMENT '内部管理用',
			system_id VARCHAR(255) NOT NULL,
			system_user_id VARCHAR(255) UNIQUE ,
			create_time BIGINT NOT NULL,
			update_time BIGINT NOT NULL,
			active INT NOT NULL default 1,
			nickname TEXT NOT NULL,
			comment MEDIUMTEXT,
			role INT NOT NULL default 1 COMMENT '１：通常　２：管理　９：マスター',
			fashion_id INT COMMENT 'ファッション系統ID',
			like_brand TEXT COMMENT '好きなブランド',
			friend_count BIGINT NOT NULL default 0 COMMENT 'フレンドカウント',
			UNIQUE `system_id_UNIQUE` (`system_user_id`),
			INDEX `system_id_INDEX` (`system_user_id`),
			" /* 一度退会して再度登録もあり得るので、UNIQUEをかけずにcreate_timeが最新のもので照合するようにすることで対処
			  UNIQUE `mail_address_UNIQUE` (`mail_address`), */ . "
			INDEX `create_time_INDEX` (`create_time`)
		";
	}

	/*	 * **********************************
	 * NAME  : get_pre_set_records
	 * INPUT : NONE
	 * OUTPUT: string / INSERT に用いるレコードテキスト
	 *         NULL / 初期INSERT不要の場合
	 * DESC  :
	 *  プリセットレコードがあれば指定する
	 *	
	 *	パスワードハッシュを生成するときは
	 *	Encrypt::password_encrypt('labomen3', $system_id2, $datetime)
	 *	を使用する！
	 * 
	 * NOTICE:
	 *  ※ない場合はNULLを返すこと
	 * CREATE: 2015.08.27 hesaka
	 * UPDATE: 2016.10.27 aoyama
	 *		ハッピー様アカウントはハッシュも固定にしておく
	 * *********************************** */
	public function get_pre_set_records() {

//		$system_id1 = StaticFunction::create_id(); /* システムIDの発行 */
		$datetime = DbDateTime::get_cur_datetime();

		return "
			(
				system_id,
				system_user_id,
				create_time,
				update_time,
				active,
				nickname,
				comment,
				role,
				fashion_id,
				like_brand
			)
			VALUES
			(
				'" . CONF::read("MASTER_USER.SYSTEM_ID") . "',
				'" . CONF::read("MASTER_USER.SYSTEM_USER_ID") . "', " .		/* 仮のシステムID */ "
				" . $datetime . ",
				" . $datetime . ",
				" . DB_ACTIVE_ON . ",
				'" . CONF::read("MASTER_USER.NICKNAME") . "',
				'ハッピーの公式アカウントです',
				9, " .					/* 管理者権限 */ "
				1, " .					/* ファッションIDは1 */ "
				'どんなブランドでもお任せください'
			);";
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
		return "AUTO_INCREMENT=10000001";
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
