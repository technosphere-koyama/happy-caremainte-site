<?php

/* * **********************************
 * NAME:ServiceMasterModel
 * DESC:
 *  ショップマスターテーブル用モデルクラス
 *  上記テーブルに対してアクセス(クエリなど)する場合は
 *  当該クラスにて行うこと！
 * NOTICE:
 *  基本的にはDbShellクラスを継承し、そちらでPDOインスタンスアクセスを行う
 *  場合によっては当該クラスで直接触ることもあるかも知れないが、
 *  できるだけDbShellクラスにて行うこと！
 * CREATE: 2015.11.23 hesaka
 * *********************************** */
class ServiceMasterModel extends DbShell {

	private $table_name = "service_master";

	public function __construct() {
		parent::__construct();
	}

	/*	 * **********************************
	 * NAME  : get_basic_data
	 * INPUT : NONE
	 * OUTPUT: array / データ
	 * DESC  :
	 *  フレームワーク起動後にロードする
	 *  サービスマスター情報を取得する
	 * NOTICE:
	 *  管理画面にてサービスマスタ情報を変更する際には
	 *  このメソッドで取得してはならない
	 *  別メソッドを作成すること
	 * 
	 *  多言語対応したので、現在の言語設定に従って
	 *  取得先テーブルを判定している
	 * CREATE: 2016.09.09 hesaka
	 * *********************************** */
	public function get_basic_data() {

		$data =  $this->query('
			SELECT
				sm.list_event_display_num_pc, sm.list_event_display_num_smp, 
				sm.event_new_period, sm.host_margin_rate, sm.supplier_margin_rate,
				sm.translate_fee_by_word,
				sm.purchase_lock_start_time, sm.purchase_lock_end_time, 
				sm.maintenance_start_time, sm.maintenance_end_time, 
				sm.tax_rate, sm.tax_rate_modify_time, sm.stock_display_delta_point
			FROM ' . DbCast::table_name($this->table_name) . ' sm
		');
		//取得に失敗した場合はエラーとして完全に終了する
		if ($this->db_select_check_error($data)
			|| $this->db_select_check_empty($data)) {
			die('エラーが発生しました。');
		}

		/*
		 * 期間系情報を判断
		 */
		$cur_datetime = DbDateTime::get_cur_datetime();

		//購入ロック
		$data[0]['is_purchase_lock'] 
			= $this->verify_datetime(
				$data[0]['purchase_lock_start_time'], 
				$data[0]['purchase_lock_end_time'],
				$cur_datetime
			);

		//メンテナンス
		$data[0]['is_maintenance'] 
			= $this->verify_datetime(
				$data[0]['maintenance_start_time'], 
				$data[0]['maintenance_end_time'],
				$cur_datetime
			);
		
		//NEWとしての閾時間
		$data[0]['new_limit_date'] = DbDateTime::get_datetime_change(DbDateTime::get_cur_datetime(),'-'.$data[0]['event_new_period'].' days');	

		//キーを全て大文字にして返す
		return array_change_key_case($data[0], CASE_UPPER);
	}

	/*	 * **********************************
	 * NAME  : verify_datetime
	 * INPUT : start / string / 開始日時
	 *         end / string / 終了日時
	 *         cur_datetime / string / 現在日時
	 * OUTPUT: true / 制限対象内
	 *         false / 制限対象外
	 * DESC  :
	 *  現在日時(cur_datetime)が、start_time, end_time判定により
	 *  指定制限対象かどうかを判定する
	 * NOTICE:
	 *  start指定があるがend指定がない場合はstart以降はずっと対象内となる
	 *  逆もまたしかり
	 *  ただし、どちらも指定がない場合は、対象外となる
	 * CREATE: 2015.11.23 hesaka
	 * *********************************** */
	private function verify_datetime($start, $end, $cur_datetime) {

		//開始、終了両方指定がない場合は対象外となる
		if (StaticFunction::is_empty($start)
			&& StaticFunction::is_empty($end)) {
			return false;
		}
		
		//開始時刻が現在時刻より未来ならチェック対応外なのでfalse(制限外)を返す
		if ($start > $cur_datetime) {
			return false;
		}

		//終了時刻が0でなく、かつ現在時刻が終了時刻より未来ならチェック対応外なのでfalse(制限外)を返す
		//※0の場合は、エンドは無くチェック対応となるので、ここで終わること無く次へ進む必要がある
		if ($end && $end < $cur_datetime) {
			return false;
		}

		//上記以外は期間内なので制限内となる
		return true;
	}

}

?>
