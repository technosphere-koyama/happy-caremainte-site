<?php

/* * **********************************
 * NAME:ServiceMaster
 * DESC:
 *  サービスマスタテーブル
 * NOTICE:
 * CREATE: 2015.11.04 hesaka
 * *********************************** */
class ServiceMaster implements DatabaseDesign {

	private $table_name = 'service_master';

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
		return "サービスマスタ";
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
			`service_id` BIGINT(16) UNSIGNED NOT NULL AUTO_INCREMENT COMMENT 'インクリメンタルID(必須)',

			`list_event_display_num_pc` INT(8) DEFAULT 20 COMMENT 'イベント表示件数PC',
			`list_event_display_num_smp` INT(8) DEFAULT 5 COMMENT 'イベント表示件数SMP',

			`event_new_period` INT(8) DEFAULT 7 COMMENT 'Newイベント表示期間(必須)',

			" . 
			/* 現状銀行振り込み系は不要
			`bank_transfer_alert_period` INT(8) DEFAULT 5 COMMENT '銀行振込で注文日からの経過でアラート出す日数',
			現状ポイントは不要
			`point_temporary_period` INT(8) DEFAULT 10 COMMENT '仮ポイント期間(必須)(変更すると本ポイントが仮ポイントになる人が出てくる)',
			`point_valid_period` INT(8) COMMENT 'ポイント有効期間(ポイント失効までの期間(日数)(NULLの場合は無期限))',
			`point_present_rate` INT(8) DEFAULT 1 COMMENT 'プレゼントポイント率(イベント価格 x X %)(必須)',
			`point_use_yen_par_point` INT(8) DEFAULT 1 COMMENT 'ポイント使用時1ポイント換算円(X円/1ポイント)(必須)',
			`point_use_under_limit` INT(8) DEFAULT 100 COMMENT '1回の購入で使えるポイント下限(必須)',
			`point_use_over_limit` INT(8) DEFAULT 10000 COMMENT '1回の購入で使えるポイント上限(必須)', */ "

			`host_margin_rate` INT(8) NOT NULL COMMENT 'ホストへの報酬率(%)(必須)',
			`supplier_margin_rate` INT(8) NOT NULL COMMENT 'サプライヤへの報酬率(%)(必須)',

			`translate_fee_by_word` INT(8) NOT NULL COMMENT '翻訳手数料(サービサ利益分)(円/語)(必須)',

			`purchase_lock_start_time` BIGINT(14) UNSIGNED COMMENT '購入不可開始時間',
			`purchase_lock_end_time` BIGINT(14) UNSIGNED COMMENT '購入不可終了時間',

			`maintenance_start_time` BIGINT(14) UNSIGNED COMMENT 'メンテナンス開始時間',
			`maintenance_end_time` BIGINT(14) UNSIGNED COMMENT 'メンテナンス終了時間',

			`tax_rate` INT(8) NOT NULL COMMENT '消費税率(%)(必須)',
			`tax_rate_modify_time` BIGINT(14) UNSIGNED COMMENT '消費税率更新日時',

			`stock_display_delta_point` INT(8) DEFAULT 5 COMMENT 'イベント詳細画面の在庫量表現アイコン三角のブレイクポイント(必須)',

			`create_time` BIGINT(14) UNSIGNED NOT NULL COMMENT '登録日時(必須)',

			PRIMARY KEY (`service_id`)
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
				list_event_display_num_pc, list_event_display_num_smp, event_new_period, 
				host_margin_rate, supplier_margin_rate, translate_fee_by_word, tax_rate,
				maintenance_start_time, maintenance_end_time, create_time
			)
			VALUES 
			(
				20, 
				6, 
				7, 
				5, 
				80, 
				2, 
				8, 
				20151223000000,
				20151223110000,
				" . $datetime . "
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
