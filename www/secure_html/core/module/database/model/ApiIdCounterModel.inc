<?php

/* * **********************************
 * NAME:ApiIdCounterModel
 * DESC:
 *  ApiIdCounterテーブル用モデルクラス
 * NOTICE:
 *  基本的にはDbShellクラスを継承し、そちらでPDOインスタンスアクセスを行う
 *  場合によっては当該クラスで直接触ることもあるかも知れないが、
 *  できるだけDbShellクラスにて行うこと！
 * CREATE: 2015.08.27 hesaka
 * UPDATE: 2016.09.29 hesaka GMO専用から、API関係で使用するものに用途を拡大
 * *********************************** */
class ApiIdCounterModel extends DbShell {

	private $table_name = "api_id_counter";
	
	public function __construct() {
		parent::__construct();
	}

	/* * **********************************
	 * NAME  : get_order_id
	 * INPUT : target_prefix / string / 取得対象カウンターのprefix
	 * OUTPUT: order_id / 新しく発行されたオーダーID
	 *         NULL / 処理に失敗した場合
	 * DESC  :
	 *  使用するオーダーIDを取得する
	 * NOTICE:
	 * ------------------------------------
	 *  次のためにインクリメントさせる
	 * ------------------------------------
	 * CREATE: 2015.09.29 hesaka
	 * *********************************** */
	public function get_order_id($target_prefix) {
	
		//パラメータチェック
		if (StaticFunction::is_empty($target_prefix, ZERO_NOT_EMPTY)) {
			LOGS_ERR('invalid parameter');
			return NULL;
		}
		
		/*
		 * 取得
		 */
		$data = $this->db_shell_select(
			$this->table_name, 
			array(
			    "counter_id",
			    "service_prefix",
			    "target_prefix",
			    "counter"
			),
			array(
				"WHERE" => array(
					"target_prefix" => DbCast::string($target_prefix)
				)
			)
		);
		//取得できなければエラー
		if ($this->db_select_check_error($data) 
			|| $this->db_select_check_empty($data)) {
			LOGS_ERR('*** GET ORDER ID ERROR ***');
			return NULL;
		}

		//現在DBにセットされている値を今回使用する
		$order_id = $data[0]["service_prefix"] . $data[0]["target_prefix"] . date("ymd") . $data[0]["counter"];

		LOGS_DBG_LV1('*** GET ORDER ID:' . $order_id . ' ***');

		//取得後、次のためにインクリメントしておく
		$this->db_shell_update(
			$this->table_name, 
			array(
			    "counter" => DbCast::id($data[0]["counter"] + 1)
			), 
			array(
			    "WHERE" =>
				array(
				    "counter_id" => DbCast::id($data[0]["counter_id"])
				)
			)
		);

		return $order_id;
	}

}

?>
