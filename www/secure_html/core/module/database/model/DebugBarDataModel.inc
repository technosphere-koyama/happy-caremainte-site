<?php

/* * **********************************
 * NAME:DebugBarDataModel
 * DESC:
 *  DebugBarDataテーブル用モデルクラス
 *  上記テーブルに対してアクセス(クエリなど)する場合は
 *  当該クラスにて行うこと！
 * NOTICE:
 *  基本的にはDbShellクラスを継承し、そちらでPDOインスタンスアクセスを行う
 *  場合によっては当該クラスで直接触ることもあるかも知れないが、
 *  できるだけDbShellクラスにて行うこと！
 * CREATE: 2015.08.27 hesaka
 * *********************************** */
class DebugBarDataModel extends DbShell {

	private $table_name = "debug_bar_data";
	
	public function __construct() {
		parent::__construct();
	}

	/* * **********************************
	 * NAME  : get_data
	 * INPUT : wheres / array / クエリに指定する検索条件の連想配列
	 *         orderbys / array / クエリに指定するソート条件の連想配列
	 * OUTPUT: array / 取得結果リスト
	 *         false / PDOクエリが失敗した場合
	 * DESC  :
	 *  Debug Bar にて取得した情報をDBに録りためてある
	 *  その情報を取得する
	 * NOTICE:
	 *  DbSell()にあるquery()メソッド(PDOのquery()のラッパー)を使用しているので
	 *  セキュリティ的にはあまりよろしくない
	 * CREATE: 2015.08.27 hesaka
	 * *********************************** */
	public function get_data($wheres = array(), $orderbys = array()) {
	
		LOGS_DBG_LV1('*** QUERY [GET DATA] START ***');

		$where = '';
		$where_list = array();
		if (!empty($wheres)) {
			foreach ($wheres as $key => $value) {
				$where_list[] = $key . "=" . $value;
			}
			$where = " WHERE " . implode(" AND ", $where_list);
		}

		$orderby = '';
		$orderby_list = array();
		if (!empty($orderbys)) {
			foreach ($orderbys as $key => $value) {
				$orderby_list[] = $key . " " . $value;
			}
			$orderby = " ORDER BY " . implode(" AND ", $orderby_list);
		}

		//取得
		if (empty($ret = $this->query("SELECT * FROM " . $this->table_name . $where . $orderby))) {
			LOGS_ERR('get list error');
			return false;
		}

		return $ret;
	}

}

?>
