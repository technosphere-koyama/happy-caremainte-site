<?php

/* * **********************************
 * NAME:SearchModel
 * DESC:
 *  タイムラインテーブル用モデルクラス
 *  上記テーブルに対してアクセス(クエリなど)する場合は
 *  当該クラスにて行うこと！
 * NOTICE:
 *  基本的にはDbShellクラスを継承し、そちらでPDOインスタンスアクセスを行う
 *  場合によっては当該クラスで直接触ることもあるかも知れないが、
 *  できるだけDbShellクラスにて行うこと！
 * CREATE: 2016.11.11 aoyama
 * *********************************** */
class SearchModel extends DbShell {

	private $user_public = "user_public";
	private $care_response = "care_response";

	public function __construct() {
		parent::__construct();
	}

	
	/*	 * **********************************
	 * NAME  : get_response_list
	 * INPUT :
	 * 		$care_system_id / int / ケアメンテの基幹システムID
	 * 		$pd  / int / paged
	 * 		$pp / int / post per page
	 * OUTPUT: array / コメント一覧
	 * DESC  :
	 *		コメントリストを取得する
	 * CREATE: 2016.11.11 aoyama
	 * *********************************** */
	public function get_response_list($care_system_id, $pd = 0, $pp = 20) {

		$data = $this->query("
			SELECT
				cr.care_response_id AS target_id,
				cr.comment AS comment,
				cr.update_time AS time,
				cr.like_count,
				up.user_id,
				up.system_id,
				up.nickname
			FROM
				" . $this->care_response . " AS cr
			LEFT JOIN
				" . $this->user_public . " AS up
			ON
				cr.user_id = up.user_id
			WHERE 
				cr.active=" . DbCast::integer(DB_ACTIVE_ON) . "
				AND
				cr.care_system_id = " . DbCast::string($care_system_id) . "
			ORDER BY
				cr.create_time DESC
			LIMIT
				" . ($pd * $pp) . ", " . $pp
		);
		//エラー・空の場合
		if ($this->db_select_check_error($data) || $this->db_select_check_empty($data)) {
			return false;
		}

		return $data;
	}

	/*	 * **********************************
	 * NAME  : get_response_num
	 * INPUT : $care_system_id / int / ケアメンテの基幹システムID
	 * OUTPUT: string / コメントの数
	 * DESC  :
	 *		公開ケアメンテのコメント総数を取得する
	 * NOTICE:
	 * CREATE: 2016.11.11 aoyama
	 * *********************************** */
	public function get_response_num($care_system_id) {

		$where = "";

		$data = $this->query("
			SELECT
				count(cr.care_response_id) AS num
			FROM
				" . $this->care_response . " AS cr
 			WHERE 
				cr.active=" . DbCast::integer(DB_ACTIVE_ON) . "
				AND
				cr.care_system_id = " . DbCast::string($care_system_id)
		);
		//エラー・空の場合
		if ($this->db_select_check_error($data) || $this->db_select_check_empty($data)) {
			return 0;
		}

		return $data[0]['num'];
	}	

	/*	 * **********************************
	 * NAME  : edit_response
	 * INPUT : param_list / array / 登録したいカラム名配列
	 * OUTPUT: db_shell_insert()のレスポンス(成功時：user_id, 失敗時:false)
	 * DESC  :
	 *		ケアメンテのコメントをINSERT
	 * NOTICE:
	 * CREATE: 2016.11.11 aoyama
	 * *********************************** */
	public function delete_response($param_list,$condition) {
		return $this->db_shell_update($this->care_response, $param_list,$condition);
	}	
	
	/*	 * **********************************
	 * NAME  : post_review
	 * INPUT : param_list / array / 登録したいカラム名配列
	 * OUTPUT: db_shell_insert()のレスポンス(成功時：user_id, 失敗時:false)
	 * DESC  :
	 *  INSERT
	 * NOTICE:
	 * CREATE: 2016.10.31 aoyama
	 * *********************************** */
	public function post_response($param_list) {
		return $this->db_shell_insert($this->care_response, $param_list);
	}
	
	/*	 * **********************************
	 * NAME  : edit_response
	 * INPUT : param_list / array / 登録したいカラム名配列
	 * OUTPUT: db_shell_insert()のレスポンス(成功時：user_id, 失敗時:false)
	 * DESC  :
	 *		ケアメンテのコメントをINSERT
	 * NOTICE:
	 * CREATE: 2016.11.11 aoyama
	 * *********************************** */
	public function edit_response($param_list,$condition) {
		return $this->db_shell_update($this->care_response, $param_list,$condition);
	}





}

?>
