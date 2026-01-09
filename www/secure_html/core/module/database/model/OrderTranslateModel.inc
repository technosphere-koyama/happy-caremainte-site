<?php

/* * **********************************
 * NAME:OrderTranslateModel
 * DESC:
 *  翻訳受注関係処理用モデル
 * NOTICE:
 *  基本的にはDbShellクラスを継承し、そちらでPDOインスタンスアクセスを行う
 *  場合によっては当該クラスで直接触ることもあるかも知れないが、
 *  できるだけDbShellクラスにて行うこと！
 * CREATE: 2016.09.29 hesaka
 * *********************************** */
class OrderTranslateModel extends DbShell {

	private $table_name = "order_translate";
	private $table_name_request = "order_translate_request";
	private $table_name_job = "order_translate_job";
	private $table_name_payment_result = "order_translate_payment_result";

	private $search_condition;

	public function __construct() {
		parent::__construct();
		$this->sGroup = 'order';

		//検索conditionパラメータ初期化
		$this->search_condition = '';
	}

	/*	 * **********************************
	 * NAME  : insert
	 * INPUT : master_param_list / array / order_translateにINSERTする情報
	 *         request_param_list / array / order_translate_requestにINSERTする情報
	 *         job_param_list / array / order_translate_jobにINSERTする情報
	 * OUTPUT: order_id / オーダーID(成功時)
	 *         NULL / 失敗時
	 * DESC  :
	 *  購入時のINSERT
	 * NOTICE:
	 *  INSERTした際に作成されたorder_idを返す
	 * CREATE: 2016.09.29 hesaka
	 * *********************************** */
	public function insert($master_param_list, $request_param_list, $job_param_list) {

		LOGS_DBG_LV1('*** PURCHASE INSERT ACTION START ***');

		//パラメータチェック
		if (StaticFunction::is_empties(
			array($master_param_list, $request_param_list, $job_param_list))
		) {
			LOGS_ERR('parameter is empty');
			return NULL;
		}

		//現在時刻を取得しておく
		$cur_datetime = DbDateTime::get_cur_datetime();

		//トランザクションスタート
		$this->TRANSACTION_START();

		/*
		 * order_translateにINSERT
		 */
		$order_id = $this->db_shell_insert(
			$this->table_name,
			//基本となる情報はここで入れるようにしておく
			$master_param_list + array(
			'system_id' => DbCast::system_id(StaticFunction::create_id()),
			'tax_rate' => DbCast::integer(CONF::read('DB_SERVICE_MASTER.TAX_RATE')),
			'device_type' => DEVICE_TYPE,
			'active' => DB_ACTIVE_ON,
			'create_time' => DbCast::datetime($cur_datetime)
			)
		);

		/*
		 * order_translate_requestにINSERT
		 */
		$request_id = $this->db_shell_insert(
			$this->table_name_request,
			//基本となる情報はここで入れるようにしておく
			$request_param_list + array(
			'system_id' => DbCast::system_id(StaticFunction::create_id()),
			'order_translate_id' => DbCast::id($order_id),
			'order_time' => DbCast::datetime($cur_datetime),
			'active' => DB_ACTIVE_ON,
			'create_time' => DbCast::datetime($cur_datetime)
			)
		);
		
		/*
		 * order_translate_jobにINSERT
		 */
		foreach ($job_param_list as $record) {

			$job_id = $this->db_shell_insert(
				$this->table_name_job,
				//基本となる情報はここで入れるようにしておく
				//※system_idはGENGOに送信したcustom_dataをセットしてある
				$record + array(
				'order_translate_request_id' => DbCast::id($request_id),
				'active' => DB_ACTIVE_ON,
				'create_time' => DbCast::datetime($cur_datetime)
				)
			);
		}

		//コミット
		$this->TRANSACTION_COMMIT();

		LOGS_DBG_LV1('*** PURCHASE INSERT ACTION SUCCESS END ***');
		LOGS_NOTICE('*** 無事翻訳決済処理が成功しました *** order_id=' . $order_id .
			(($master_param_list['extend_id']) ? (' supplier extend_id=' . $master_param_list['extend_id']) : ('')) .
			' request_data=' . json_encode($request_param_list));

		//order_idを返す
		return $order_id;
	}

	/*	 * **********************************
	 * NAME  : insert
	 * INPUT : param_list / array / INSERTする情報
	 * OUTPUT: NONE
	 * DESC  :
	 *  購入結果をINSERTする
	 * NOTICE:
	 *  ログ的に入れるものなので、INSERTのエラー判定は行わない
	 * CREATE: 2016.09.29 hesaka
	 * *********************************** */
	public function insert_payment_result($param_list) {

		//引数が空の場合は終了
		if (StaticFunction::is_empty($param_list)) {
			return;
		}
		
		/*
		 * INSERT実行
		 */
		$this->db_shell_insert(
			$this->table_name_payment_result, 
			$param_list
		);
	}

	/*	 * **********************************
	 * NAME  : insert
	 * INPUT : target_object / integer / 対象オブジェクト判定定義値(DB_ORDER_TRANSLATE_TARGET_...)
	 *         target_object_id / string / 対象オブジェクトID
	 * OUTPUT: true / 翻訳完了
	 *         false / 翻訳対応中
	 * DESC  :
	 *  指定オブジェクト・IDの翻訳依頼の翻訳が完了しているか判定する
	 * NOTICE:
	 * ---------------------------------------
	 *  注意点
	 *  翻訳依頼には複数の翻訳(JOB)が存在する
	 *  その全てが完了(GENGO的にはreviewable, approved)に
	 *  なっていた場合のみ「翻訳完了」と判断し、
	 *  それ以外は対応中となる
	 * ---------------------------------------
	 *  使用シーン想定としては、サービサが対象となる
	 *  shop or eventの「承認」「否認」アクションを
	 *  行って良いかの判断時に使用する
	 *  ※翻訳が完了して、やっとshop or event内容の
	 *  　可否判定ができるようになるからである
	 *  ※翻訳の方のステータスがreviewableの場合、
	 *  　翻訳完了状態ではないが、これの差し戻しなど
	 *  　行うのは別のインターフェース(翻訳依頼管理画面など)にて
	 *  　行うべきで、その権限は同じくサービサなので、
	 *  　このレスによってサービサが承認アクションを
	 *  　とったということは、GENGOに対しても了承(approved)した
	 *  　と同義であると捉えられるため、問題ないものとする
	 * CREATE: 2016.10.04 hesaka
	 * *********************************** */
	public function is_translate_complete($target_object, $target_object_id) {

		//パラメータチェック
		if (StaticFunction::is_empties(array($target_object, $target_object_id))
			|| !array_key_exists($target_object, CONF::read('DB_ORDER_TRANSLATE_TARGET'))) {
			return false;
		}

		/*
		 * 対象翻訳依頼の全JOBを取得する
		 */
		$data =  $this->query('
			SELECT otj.`order_translate_job_id`, otj.`ta_status`
			FROM ' . DbCast::table_name($this->table_name) . ' ot
				LEFT JOIN ' . DbCast::table_name($this->table_name_request) . ' otr ON ot.`order_translate_id`=otr.`order_translate_id`
				LEFT JOIN ' . DbCast::table_name($this->table_name_job) . ' otj ON otr.`order_translate_request_id`=otj.`order_translate_request_id`
			WHERE
				ot.`active`=' . DB_ACTIVE_ON . '
				AND otr.`active`=' . DB_ACTIVE_ON . '
				AND otj.`active`=' . DB_ACTIVE_ON . '
				AND ot.`target_object`=' . DbCast::integer($target_object) . '
				AND ot.`target_object_id`=' . DbCast::id($target_object_id) . '
			GROUP BY otj.`order_translate_job_id`
		');

		//エラーの場合はfalseを返す
		if ($this->db_select_check_error($data)) {
			LOGS_ERR('*** SELECT QUERY ERROR!!! ***');
			return false;
		}
		//取得できなかった場合は、
		//・そもそも依頼を出していない
		//・依頼は出したがavailableすらコールバックが返ってきていない
		//・ACTIVEをOFFにされたかレコード削除されたか
		//などの理由が考えられる
		//が、現状はとりあえずfalseを返す
		if ($this->db_select_check_empty($data)) {
			LOGS_ERR('*** DATA NOT FOUND!!! ***');
			return false;
		}

		/*
		 * 一つでも
		 * reviewable, approvedじゃないものがあったら
		 * falseを返す
		 */
		foreach ($data as $value) {
			switch ($value['ta_status']) {
				case DB_GENGO_STATUS_REVIEWABLE:
				case DB_GENGO_STATUS_APPROVED:
					break;
				default:
					//違う場合はここで終了
					return false;
			}
		}

		/* 
		 * ここに来たということは、全てが 
		 * reviewable もしくは approved のどちらかであるということ
		 */
		return true;
	}

}

?>