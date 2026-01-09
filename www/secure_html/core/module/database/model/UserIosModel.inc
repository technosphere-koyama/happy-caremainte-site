<?php

/* * **********************************
 * NAME:UserAndroidModel
 * DESC:
 *		アンドロイドトークンを管理するクラス
 * NOTICE:
 * CREATE: 2016.11.17 aoyama
 * *********************************** */
class UserIosModel extends DbShell {

	private $table_name = "user_ios";
	private $table_user = "user_public";

	public function __construct() {
		parent::__construct();
	}

	/*	 * **********************************
	 * NAME  : get_token
	 * INPUT : user_id / string / ユーザID
	 * OUTPUT: array
	 * DESC  :
	 * 		スマホのtokenを持っているユーザーのリストを取得
	 * NOTICE:
	 * CREATE: 2016.11.30 aoyama
	 * *********************************** */
	public function get_token($user_id) {
		//登録トークンを取得
		$result = $this->query("
			SELECT
				 device_token
			FROM
				" . $this->table_name . " AS mv
			WHERE
				mv.user_id = " . DbCast::id($user_id) . "
				AND
				mv.active = " . DB_ACTIVE_ON
		);
		
		return $result;
	}
	
	/*	 * **********************************
	 * NAME  : set
	 * INPUT : user_id / string / ユーザID
	 *         target_id / string / フォローするユーザID
	 * OUTPUT:
	 * DESC  :
	 * 		スマホアプリ連携用のtoken登録
	 *		ログ出力必須
	 * NOTICE:
	 * CREATE: 2016.11.17 aoyama
	 * *********************************** */
	public function set($user_id, $token) {
		
		//既存の登録数をカウント
		$already = $this->query("
			SELECT
				COUNT(mt.id) AS num
			FROM
				" . $this->table_name . " AS mt
			WHERE
				mt.user_id = " . DbCast::id($user_id) . "
				AND
				mt.device_token = " . DbCast::string($token) . "
				AND
				mt.active = " . DB_ACTIVE_ON
		);
		
		//登録があれば終了
		if ($already[0]['num'] > 0) {
			return false;
		}

		//登録処理
		//現在日時を取得
		$cur_time = DbCast::datetime(DbDateTime::get_cur_datetime());

		$param_list = array(
			"create_time" => $cur_time,
			"update_time" => $cur_time,
			"active" => DB_ACTIVE_ON,
			"user_id" => DbCast::id($user_id),
			"device_token" => DbCast::string($token)
		);

		// 登録失敗した場合
		if ($this->db_shell_insert($this->table_name, $param_list)) {
			return true;
		}

		// 処理なのでログに残す
		LOGS_ERR($param_list);
		return false;
	}
	
	/*	 * **********************************
	 * NAME  : select
	 * INPUT : select_list / array / 取得したいカラム名配列
	 *         condition / array / whereに用いる検索条件の連想配列
	 * OUTPUT: db_shecll_select()のレスポンス
	 * DESC  :
	 *  SELECT
	 * NOTICE:
	 * CREATE: 2015.08.27 hesaka
	 * *********************************** */
	public function select($select_list, $condition = NULL) {
		return $this->db_shell_select($this->table_name, $select_list, $condition);
	}	
	
	/*	 * **********************************
	 * NAME  : update
	 * INPUT : param_list / array / 更新したいカラム名配列
	 *         condition / array / whereに用いる検索条件の連想配列
	 * OUTPUT: db_shecll_update()のレスポンス
	 * DESC  :
	 *  UPDATE
	 * NOTICE:
	 * CREATE: 2015.10.04 hesaka
	 * *********************************** */
	public function update($param_list, $condition = NULL) {
		LOGS_DBG_LV1('*** QUERY [UPDATE] START ***');
		return $this->db_shell_update($this->table_name, $param_list, $condition);
	}

	/*	 * **********************************
	 * NAME  : delete
	 * INPUT : table_name / string / テーブル名
	 *         condition / array / whereに用いる検索条件の連想配列
	 * OUTPUT: db_shecll_delete()のレスポンス
	 * DESC  :
	 * NOTICE:
	 * CREATE: 2015.12.07 hesaka
	 * *********************************** */
	public function delete($condition = NULL) {
		return $this->db_shell_delete($this->table_name, $condition);
	}
}

?>
