<?php

/* * **********************************
 * NAME:ReviewModel
 * DESC:
 *  タイムラインテーブル用モデルクラス
 *  上記テーブルに対してアクセス(クエリなど)する場合は
 *  当該クラスにて行うこと！
 * NOTICE:
 *  基本的にはDbShellクラスを継承し、そちらでPDOインスタンスアクセスを行う
 *  場合によっては当該クラスで直接触ることもあるかも知れないが、
 *  できるだけDbShellクラスにて行うこと！
 * CREATE: 2016.10.21 aoyama
 * *********************************** */
class ReviewModel extends DbShell {

	private $user_public = "user_public";
	private $review = "review";
	private $review_response = "review_response";

	public function __construct() {
		parent::__construct();
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
	public function post_review($param_list) {
		return $this->db_shell_insert($this->review, $param_list);
	}

	/*	 * **********************************
	 * NAME  : get_review
	 * INPUT : $review_id
	 * OUTPUT: 配列
	 * DESC  :
	 * 		レビューの詳細情報
	 * NOTICE:
	 * CREATE: 2016.11.14 aoyama
	 * *********************************** */
	public function get_review($review_id) {

		$data = $this->query("
			SELECT
				rv.review_id,
				rv.comment,
				rv.update_time,
				rv.create_time,
				rv.old_nickname,
				rv.evaluation_1,
				rv.evaluation_2,
				rv.like_count,
				rv.image_file,
				up.nickname,
				up.system_id
			FROM
				" . $this->review . " AS rv
			LEFT JOIN
				user_public AS up
			ON
				rv.user_id = up.user_id
			WHERE
				rv.active = " . DB_ACTIVE_ON . "
				AND
				rv.review_id = ".DbCast::id($review_id)
		);
		//エラー・空の場合
		if ($this->db_select_check_error($data) || $this->db_select_check_empty($data)) {
			return array();
		}

		return $data;
	}

	/*	 * **********************************
	 * NAME  : get_review_package
	 * INPUT : 
	 * OUTPUT: 配列
	 * DESC  :
	 * 		レビューとそれに紐づくコメントを取得
	 * NOTICE:
	 * CREATE: 2016.10.31 aoyama
	 * *********************************** */
	public function get_review_package($pd = 0, $pp = 20) {

		$data = $this->query("
			SELECT
				rr.active AS rr_active,
				rr.review_response_id,
				rr.create_time AS response_time,
				rr.response_text,
				rr.old_nickname AS response_old_nickname,
				up2.nickname AS response_nickname,
				up2.system_id AS response_system_id,
				up2.user_id AS response_user_id,
				
				rv2.review_id,
				rv2.comment AS review_comment,
				rv2.old_nickname AS review_old_nickname,
				rv2.evaluation_1 AS review_evaluation_1,
				rv2.evaluation_2 AS review_evaluation_2,
				rv2.like_count AS review_like_count,
				rv2.evaluation_1 AS evaluation_1,
				rv2.evaluation_2 AS evaluation_2,
				rv2.image_file AS review_image_file,
				rv2.nickname AS review_nickname,
				rv2.user_id AS review_user_id,
				rv2.system_id AS review_system_id,
				rv2.create_time AS review_time
			FROM
				(
					SELECT
						rv.review_id,
						rv.comment,
						rv.update_time,
						rv.create_time,
						rv.old_nickname,
						rv.evaluation_1,
						rv.evaluation_2,
						rv.like_count,
						rv.image_file,
						up.user_id,
						up.system_id,
						up.nickname
					FROM
						" . $this->review . " AS rv
					LEFT JOIN
						user_public AS up
					ON
						rv.user_id = up.user_id
					WHERE
						rv.active = " . DB_ACTIVE_ON . "
					ORDER BY
						rv.create_time DESC
					LIMIT
						" . ($pd * $pp) . ", " . $pp . "
				) AS rv2
			LEFT JOIN
				" . $this->review_response . " AS rr
			ON
				rv2.review_id = rr.review_id
			LEFT JOIN
				user_public AS up2
			ON
				rr.user_id = up2.user_id
			WHERE
				rr.active = " . DB_ACTIVE_ON . "
				OR
				rr.active IS NULL
			ORDER BY
				review_time DESC,response_time ASC
			"
		);
		//エラー・空の場合
		if ($this->db_select_check_error($data) || $this->db_select_check_empty($data)) {
			return array();
		}

		return $data;
	}

	/*	 * **********************************
	 * NAME  : get_review_count
	 * INPUT : 
	 * OUTPUT: 配列
	 * DESC  :
	 * 		レビューのカウント
	 * NOTICE:
	 * CREATE: 2016.10.31 aoyama
	 * *********************************** */
	public function get_review_count() {

		$data = $this->query("
			SELECT
				count(rv.review_id) AS code
			FROM
				" . $this->review . " AS rv
			WHERE
				rv.active = " . DB_ACTIVE_ON
		);
		return $data[0]['code'];
	}

	/*	 * **********************************
	 * NAME  : post_review_response
	 * INPUT : $param_array / array / レスポンス情報の配列
	 * OUTPUT: string / コメントの数
	 * DESC  :
	 *		レビューの存在確認後にレスポンスを投稿する処理
	 * NOTICE:
	 * CREATE: 2016.10.31 aoyama
	 * *********************************** */
	public function post_review_response($param_array) {

		$data = $this->query("
			SELECT
				count(rv.review_id) AS code
			FROM
				" . $this->review . " AS rv
			WHERE
				rv.active = " . DB_ACTIVE_ON . "
				AND
				rv.review_id = " . DbCast::id($param_array['review_id'])
		);
		if ($this->db_select_check_error($data) || $this->db_select_check_empty($data)) {
			return false;
		}

		if ($data[0]['code'] == 1) {
			$this->db_shell_insert($this->review_response, $param_array);
			return true;
		}
		return false;
	}
	
	/*	 * **********************************
	 * NAME  : get_review_response
	 * INPUT : $rr_id / int / レビューのコメントID
	 * OUTPUT: array / 結果配列
	 * DESC  :
	 *		レビューコメントの詳細取得
	 * NOTICE:
	 * CREATE: 2016.11.20 aoyama
	 * *********************************** */
	public function get_review_response($rr_id) {

		$data = $this->query("
			SELECT
				rr.update_time AS view_time,
				rr.user_id,
				rr.review_id,
				rr.old_nickname
			FROM
				" . $this->review_response . " AS rr
			WHERE
				rr.active = " . DB_ACTIVE_ON . "
				AND
				rr.review_response_id = " . DbCast::id($rr_id)
		);
		if ($this->db_select_check_error($data) || $this->db_select_check_empty($data)) {
			return false;
		}

		return $data;
	}	

		/*	 * **********************************
	 * NAME  : get_review_response
	 * INPUT : $rr_id / int / レビューのコメントID
	 * OUTPUT: array / 結果配列
	 * DESC  :
	 *		レビューコメントの詳細取得
	 * NOTICE:
	 * CREATE: 2016.11.20 aoyama
	 * *********************************** */
	public function delete($param_list,$condition) {
		return $this->db_shell_update($this->review, $param_list,$condition);
	}

	/*	 * **********************************
	 * NAME  : get_review_response
	 * INPUT : $rr_id / int / レビューのコメントID
	 * OUTPUT: array / 結果配列
	 * DESC  :
	 *		レビューコメントの詳細取得
	 * NOTICE:
	 * CREATE: 2016.11.20 aoyama
	 * *********************************** */
	public function delete_review_response($param_list,$condition) {
		return $this->db_shell_update($this->review_response, $param_list,$condition);
	}
	/*	 * **********************************
	 * NAME  : edit_review
	 * INPUT : param_list / array / 登録したいカラム名配列
	 * OUTPUT: db_shell_insert()のレスポンス(成功時：user_id, 失敗時:false)
	 * DESC  :
	 *		レビューを編集する
	 * NOTICE:
	 * CREATE: 2016.11.14 aoyama
	 * *********************************** */
	public function edit_review($param_list,$condition) {
		return $this->db_shell_update($this->review, $param_list,$condition);
	}
	
}

?>
