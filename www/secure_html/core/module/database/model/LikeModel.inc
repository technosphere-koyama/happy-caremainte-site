<?php

/* * **********************************
 * NAME:LikeModel
 * DESC:
 *  タイムラインテーブル用モデルクラス
 *  上記テーブルに対してアクセス(クエリなど)する場合は
 *  当該クラスにて行うこと！
 * NOTICE:
 *  基本的にはDbShellクラスを継承し、そちらでPDOインスタンスアクセスを行う
 *  場合によっては当該クラスで直接触ることもあるかも知れないが、
 *  できるだけDbShellクラスにて行うこと！
 * CREATE: 2016.10.28 aoyama
 * *********************************** */
class LikeModel extends DbShell {

	private $user_public = "user_public";
	private $thread_table = "community_thread";
	private $response_table = "community_response";
	private $review_table = "review";
	private $timeline_table = "timeline";
	private $care_response_table = "care_response";
	
	private $thread_like = "thread_like";
	private $response_like = "response_like";
	private $review_like = "review_like";
	private $timeline_like = "timeline_like";
	private $care_response_like = "care_response_like";
	private $mypage_limit = 200;

	public function __construct() {
		parent::__construct();
	}

	/*	 * **********************************
	 * NAME  : get_mypage_like_own
	 * INPUT :
	 * 		$thread_id / int / コミュニティID
	 * 		$pd  / int / paged
	 * 		$pp / int / post per page
	 * OUTPUT: array / メンバー一覧
	 * DESC  :
	 * 		マイページの1ページに表示されたビューのうち、
	 * 		対象ユーザーがいいねしているリストを配列で返す。
	 * 		他と違い、複合likeテーブルを検索対象とする
	 * NOTICE:
	 * CREATE: 2016.11.2 aoyama
	 * *********************************** */
	public function get_mypage_like_own($user_id, $reviewAllArray) {

		//パラメータチェック
		if (StaticFunction::is_empty($reviewAllArray)) {
			return array();
		}

		//配列をIN用に成形
		$in_response_array = array();
		$in_timeline_array = array();
		foreach ($reviewAllArray AS $val) {

			if ($val['prefix'] == "response") {
				$in_response_array[] = $val['mypage_id'];
			} else if ($val['prefix'] == "timeline") {
				$in_timeline_array[] = $val['mypage_id'];
			}
		}

		$data_response = array();
		if (!StaticFunction::is_empty($in_response_array)) {
			$in_response_value = implode(",", $in_response_array);
			$data_response = $this->query("
			SELECT
				'response' AS prefix,
				rl.target_id
			FROM
				" . $this->response_like . " AS rl
			WHERE
				rl.user_id = " . DbCast::id($user_id) . "
				AND
				rl.target_id IN (" . $in_response_value . ")
				AND
				rl.active=" . DB_ACTIVE_ON
			);
		}
		$data_timeline = array();
		if (!StaticFunction::is_empty($in_timeline_array)) {
			$in_timeline_value = implode(",", $in_timeline_array);
			$data_timeline = $this->query("
			SELECT
				'timeline' AS prefix,
				tl.target_id
			FROM
				" . $this->timeline_like . " AS tl
			WHERE
				tl.user_id = " . DbCast::id($user_id) . "
				AND
				tl.target_id IN (" . $in_timeline_value . ")
				AND
				tl.active=" . DB_ACTIVE_ON
			);
		}

		$data = array_merge($data_response, $data_timeline);
//		var_dump($data);
//		exit;

		//エラー・空の場合
		if ($this->db_select_check_error($data) || $this->db_select_check_empty($data)) {
			return array();
		}
		

		return $data;
	}

	/*	 * **********************************
	 * NAME  : get_care_response_like_own
	 * INPUT :
	 * 		$thread_id / int / コミュニティID
	 * 		$pd  / int / paged
	 * 		$pp / int / post per page
	 * OUTPUT: array / メンバー一覧
	 * DESC  :
	 * 		1ページに表示されたビューのうち、
	 * 		対象ユーザーがいいねしているリストを配列で返す
	 * NOTICE:
	 * CREATE: 2016.11.11 aoyama
	 * *********************************** */
	public function get_care_response_like_own($user_id, $careAllArray) {

		//パラメータチェック
		if (StaticFunction::is_empty($careAllArray)) {
			return array();
		}

		//配列をIN用に成形
		$in_array = array();
		foreach ($careAllArray AS $val) {
			$in_array[] = $val['target_id'];
		}

		$in_value = implode(",", $in_array);

		$data = $this->query("
			SELECT
				crl.target_id
			FROM
				" . $this->care_response_like . " AS crl
			WHERE
				crl.user_id = " . DbCast::id($user_id) . "
				AND
				crl.target_id IN (" . $in_value . ")
				AND
				crl.active=" . DbCast::integer(DB_ACTIVE_ON)
		);

		//エラー・空の場合
		if ($this->db_select_check_error($data) || $this->db_select_check_empty($data)) {
			return array();
		}

		return $data;
	}	
	
	/*	 * **********************************
	 * NAME  : get_review_like_own
	 * INPUT :
	 * 		$thread_id / int / コミュニティID
	 * 		$pd  / int / paged
	 * 		$pp / int / post per page
	 * OUTPUT: array / メンバー一覧
	 * DESC  :
	 * 		1ページに表示されたビューのうち、
	 * 		対象ユーザーがいいねしているリストを配列で返す
	 * NOTICE:
	 * CREATE: 2016.11.2 aoyama
	 * *********************************** */
	public function get_review_like_own($user_id, $reviewAllArray) {

		//パラメータチェック
		if (StaticFunction::is_empty($reviewAllArray)) {
			return array();
		}

		//配列をIN用に成形
		$in_array = array();
		foreach ($reviewAllArray AS $val) {
			$in_array[] = $val['review_id'];
		}

		$in_value = implode(",", $in_array);

		$data = $this->query("
			SELECT
				rl.target_id
			FROM
				" . $this->review_like . " AS rl
			WHERE
				rl.user_id = " . DbCast::id($user_id) . "
				AND
				rl.target_id IN (" . $in_value . ")
				AND
				rl.active=" . DbCast::integer(DB_ACTIVE_ON)
		);

		//エラー・空の場合
		if ($this->db_select_check_error($data) || $this->db_select_check_empty($data)) {
			return array();
		}

		return $data;
	}

	/*	 * **********************************
	 * NAME  : get_response_like_own
	 * INPUT :
	 * 		$thread_id / int / コミュニティID
	 * 		$pd  / int / paged
	 * 		$pp / int / post per page
	 * OUTPUT: array / メンバー一覧
	 * DESC  :
	 * 		1ページに表示されたコメントのうち、
	 * 		対象ユーザーがいいねしているリストを配列で返す
	 * NOTICE:
	 * CREATE: 2016.10.31 aoyama
	 * *********************************** */
	public function get_response_like_own($user_id, $commentAllArray) {

		//パラメータチェック
		if (StaticFunction::is_empty($commentAllArray)) {
			return array();
		}

		//配列をIN用に成形
		$in_array = array();
		foreach ($commentAllArray AS $val) {
			$in_array[] = $val['response_id'];
		}

		$in_value = implode(",", $in_array);


		$data = $this->query("
			SELECT
				rl.target_id
			FROM
				" . $this->response_like . " AS rl
			WHERE
				rl.user_id = " . DbCast::id($user_id) . "
				AND
				rl.target_id IN (" . $in_value . ")
				AND
				rl.active=" . DbCast::integer(DB_ACTIVE_ON)
		);

		//エラー・空の場合
		if ($this->db_select_check_error($data) || $this->db_select_check_empty($data)) {
			return array();
		}

		return $data;
	}



	/*	 * **********************************
	 * NAME  : delete_review_like
	 * INPUT :
	 * 		$response_id / int / コメントID
	 * OUTPUT:
	 * 		true / false 
	 * DESC  :
	 * 		ケアメンテのコメントに対するいいねを削除するメソッド
	 * NOTICE:
	 * CREATE: 2016.11.11 aoyama
	 * *********************************** */
	public function delete_review_like($review_id) {

		$result = $this->exec("
			DELETE
			FROM
				" . $this->review_like . "
			WHERE
				target_id = " . DbCast::id($review_id) . "
		");

		return $result;
	}		
	
	/*	 * **********************************
	 * NAME  : delete_response_like
	 * INPUT :
	 * 		$response_id / int / コメントID
	 * OUTPUT:
	 * 		true / false 
	 * DESC  :
	 * 		ケアメンテのコメントに対するいいねを削除するメソッド
	 * NOTICE:
	 * CREATE: 2016.11.11 aoyama
	 * *********************************** */
	public function delete_care_response_like($care_response_id) {

		$result = $this->exec("
			DELETE
			FROM
				" . $this->care_response_like . "
			WHERE
				target_id = " . DbCast::id($care_response_id) . "
		");

		return $result;
	}	
	
	/*	 * **********************************
	 * NAME  : delete_response_like
	 * INPUT :
	 * 		$response_id / int / コメントID
	 * OUTPUT:
	 * 		true / false 
	 * DESC  :
	 * 		コミュニティに参加しているかのチェック用メソッド
	 * NOTICE:
	 * CREATE: 2016.10.26 aoyama
	 * *********************************** */
	public function delete_response_like($response_id) {

		$result = $this->exec("
			DELETE
			FROM
				" . $this->response_like . "
			WHERE
				target_id = " . DbCast::id($response_id) . "
		");

		return $result;
	}

	/*	 * **********************************
	 * NAME  : delete_timeline_like
	 * INPUT :
	 * 		$response_id / int / コメントID
	 * OUTPUT:
	 * 		true / false 
	 * DESC  :
	 * 		タイムラインの削除メソッド
	 * NOTICE:
	 * CREATE: 2016.11.10 aoyama
	 * *********************************** */
	public function delete_timeline_like($timeline_id) {

		$result = $this->exec("
			DELETE
			FROM
				" . $this->timeline_like . "
			WHERE
				target_id = " . DbCast::id($timeline_id) . "
		");

		return $result;
	}	
	
	/*	 * **********************************
	 * NAME  : set_dislike
	 * INPUT :
	 * 		 $type / string / コミュニティかコメントか
	 * 		user_id / string / ユーザID
	 * 		thread_id / string / コミュニティID
	 * OUTPUT:
	 * 		true / 既に登録されている
	 * 		false / 登録されていない
	 * DESC  :
	 * 		コミュニティに参加しているかのチェック用メソッド
	 * NOTICE:
	 * CREATE: 2016.10.31 aoyama
	 * UPDATE: 2016.11.11 aoyama
	 *		ケアメンテのコメントいいねに対応
	 * *********************************** */
	public function set_dislike($type, $target_id, $user_id) {


		switch ($type) {

			case "thread":
				$table_like = $this->thread_like;
				$table_name = $this->thread_table;
				$column_name = "thread_id";

				break;
			case "response":
				$table_like = $this->response_like;
				$table_name = $this->response_table;
				$column_name = "response_id";

				break;
			case "review":
				$table_like = $this->review_like;
				$table_name = $this->review_table;
				$column_name = "review_id";

				break;
			case "timeline":
				$table_like = $this->timeline_like;
				$table_name = $this->timeline_table;
				$column_name = "timeline_id";

				break;
			case "care_response":
				$table_like = $this->care_response_like;
				$table_name = $this->care_response_table;
				$column_name = "care_response_id";

				break;
			default :

				return false;
		}

		$this->TRANSACTION_START();
		$already = $this->query("
			SELECT
				COUNT(tbl1.target_id) AS num
			FROM
				" . $table_like . " AS tbl1
			WHERE
				tbl1.user_id = " . DbCast::id($user_id) . "
				AND
				tbl1.target_id = " . DbCast::id($target_id) . "
				AND
				tbl1.active = " . DB_ACTIVE_ON
		);

		if ($already[0]['num'] <= 0) {
			$this->TRANSACTION_ROLLBACK();
			return false;
		}

		//集計
		$like_count = $this->query("
			SELECT
				COUNT(tbl1.target_id) AS num
			FROM
				" . $table_like . " AS tbl1
			WHERE
				tbl1.target_id = " . DbCast::id($target_id) . "
				AND
				tbl1.active = " . DB_ACTIVE_ON
		);

		// カウントダウン処理
		$data = $this->exec("
			UPDATE
				" . $table_name . " AS tbl1
			SET
				tbl1.like_count = " . DbCast::integer($like_count[0]['num'] - 1) . "
			WHERE
				tbl1." . $column_name . " = " . DbCast::id($target_id) . "
		");

		//削除処理
		$query = "
			DELETE
			FROM
				" . $table_like . "
			WHERE 
				user_id=" . DbCast::id($user_id) . "
				AND
				target_id=" . DbCast::id($target_id) . "
			";

		$data = $this->exec($query);

		//エラー・空の場合
		if ($data) {
			//DELETE 処理なのでログに残す
			LOGS_DELETE($query);
			$this->TRANSACTION_COMMIT();
			return true;
		}

		$this->TRANSACTION_ROLLBACK();
		return false;
	}

	/*	 * **********************************
	 * NAME  : set_like
	 * INPUT :
	 * 		 $type / string / コミュニティかコメントか
	 * 		user_id / string / ユーザID
	 * 		thread_id / string / コミュニティID
	 * OUTPUT:
	 * 		true / 既に登録されている
	 * 		false / 登録されていない
	 * DESC  :
	 * 		コミュニティに参加しているかのチェック用メソッド
	 * NOTICE:
	 * CREATE: 2016.10.26 aoyama
	 * UPDATE: 2016.11.11 aoyama
	 *		ケアメンテのコメントいいねに対応
	 * *********************************** */
	public function set_like($type, $target_id, $user_id) {

		switch ($type) {

			case "thread":
				$table_like = $this->thread_like;
				$table_name = $this->thread_table;
				$column_name = "thread_id";

				break;
			case "response":
				$table_like = $this->response_like;
				$table_name = $this->response_table;
				$column_name = "response_id";

				break;
			case "review":
				$table_like = $this->review_like;
				$table_name = $this->review_table;
				$column_name = "review_id";

				break;
			case "timeline":
				$table_like = $this->timeline_like;
				$table_name = $this->timeline_table;
				$column_name = "timeline_id";

				break;
			case "care_response":
				$table_like = $this->care_response_like;
				$table_name = $this->care_response_table;
				$column_name = "care_response_id";

				break;
			default :

				return false;
		}

		$this->TRANSACTION_START();
		$already = $this->query("
			SELECT
				COUNT(tbl1.target_id) AS num
			FROM
				" . $table_like . " AS tbl1
			WHERE
				tbl1.user_id = " . DbCast::id($user_id) . "
				AND
				tbl1.target_id = " . DbCast::id($target_id) . "
				AND
				tbl1.active = " . DB_ACTIVE_ON
		);

		if ($already[0]['num'] > 0) {
			$this->TRANSACTION_ROLLBACK();
			return false;
		}

		//集計
		$like_count = $this->query("
			SELECT
				COUNT(tbl1.target_id) AS num
			FROM
				" . $table_like . " AS tbl1
			WHERE
				tbl1.target_id = " . DbCast::id($target_id) . "
				AND
				tbl1.active = " . DB_ACTIVE_ON
		);

		// カウントアップ処理
		$data = $this->exec("
			UPDATE
				" . $table_name . " AS tbl1
			SET
				tbl1.like_count = " . DbCast::integer($like_count[0]['num'] + 1) . "
			WHERE
				tbl1." . $column_name . " = " . DbCast::id($target_id) . "
		");

		$date = DbDateTime::get_cur_datetime();
		//登録処理
		$param_list = array(
			'target_id' => DbCast::id($target_id),
			'user_id' => DbCast::id($user_id),
			'create_time' => DbCast::datetime($date),
			'update_time' => DbCast::datetime($date),
			'active' => DB_ACTIVE_ON
		);

		$this->db_shell_insert($table_like, $param_list);

		$this->TRANSACTION_COMMIT();
		return true;
	}

	/*	 * **********************************
	 * NAME  : post_timeline
	 * INPUT : param_list / array / 登録したいカラム名配列
	 * OUTPUT: db_shell_insert()のレスポンス(成功時：user_id, 失敗時:false)
	 * DESC  :
	 *  INSERT
	 * NOTICE:
	 * CREATE: 2016.10.19 aoyama
	 * *********************************** */
	public function post_timeline($param_list) {
		return $this->db_shell_insert($this->timeline, $param_list);
	}

	/*	 * **********************************
	 * NAME  : get_timeline_public
	 * INPUT : param_list / array / 登録したいカラム名配列
	 * OUTPUT: db_shell_insert()のレスポンス(成功時：user_id, 失敗時:false)
	 * DESC  :
	 * 		マイページTOPのタイムラインを取得
	 * NOTICE:
	 * CREATE: 2016.10.21 aoyama
	 * *********************************** */
	public function get_timeline_public($user_id, $pd = 0, $pp = 20) {

		$data = $this->query("
			(
			SELECT
				'community' AS type,
				ct.community_name AS thread_name,
				cr.response_id AS code,
				cr.response_text AS text,
				cr.update_time AS update_time,
				cr.user_id AS user_id,
				cr.image_file AS file_name,
				cr.thread_id AS thread_id,
				up.nickname AS nickname,
				up.system_id AS system_id
			FROM
				community_response AS cr
			LEFT JOIN
				user_public AS up
			ON
				cr.user_id = up.user_id
			LEFT JOIN
				community_thread AS ct
			ON
				cr.thread_id = ct.thread_id
			LEFT JOIN
				community_match AS cm
			ON
				cr.thread_id = cm.thread_id
			WHERE
				cm.user_id = " . DbCast::id($user_id) . "
			LIMIT
				0, " . $this->mypage_limit . "
			)
			UNION
			(
			SELECT
				'timeline' AS type,
				null AS thread_name,
				tl.timeline_id AS code,
				tl.comment AS text,
				tl.update_time AS update_time,
				tl.user_id AS user_id,
				tl.image_file AS file_name,
				null AS thread_id,
				up2.nickname AS nickname,
				up2.system_id AS system_id
			FROM
				timeline AS tl
			LEFT JOIN
				user_public AS up2
			ON
				tl.user_id = up2.user_id
			LEFT JOIN
				friend_match AS fm
			ON
				tl.user_id = fm.friend_id
			WHERE
				fm.user_id = " . DbCast::id($user_id) . "
					OR
				tl.user_id = " . DbCast::id($user_id) . "
			ORDER BY
				tl.update_time DESC
			LIMIT
				0, " . $this->mypage_limit . "
			)
			ORDER BY
				update_time DESC
			LIMIT
				" . ($pd * $pp) . "," . $pp . "	"
		);
		return $data;
	}

	/*	 * **********************************
	 * NAME  : get_timeline_count
	 * INPUT : $user_id / int / ユーザーID
	 * OUTPUT: 数値
	 * DESC  :
	 * 		マイページTOPのタイムラインの数を取得
	 * NOTICE:
	 * CREATE: 2016.10.27 aoyama
	 * *********************************** */
	public function get_timeline_count($user_id) {

		$data = $this->query("
			SELECT SUM(code) AS tl_cunt FROM (
			(
			SELECT
				count(cr.response_id) AS code
			FROM
				community_response AS cr
			LEFT JOIN
				user_public AS up
			ON
				cr.user_id = up.user_id
			LEFT JOIN
				community_thread AS ct
			ON
				cr.thread_id = ct.thread_id
			LEFT JOIN
				community_match AS cm
			ON
				cr.thread_id = cm.thread_id
			WHERE
				cm.user_id = " . DbCast::id($user_id) . "
			LIMIT
				0, " . $this->mypage_limit . "
			)
			UNION ALL
			(
			SELECT
				count(tl.timeline_id) AS code
			FROM
				timeline AS tl
			LEFT JOIN
				user_public AS up2
			ON
				tl.user_id = up2.user_id
			LEFT JOIN
				friend_match AS fm
			ON
				tl.user_id = fm.friend_id
			WHERE
				fm.user_id = " . DbCast::id($user_id) . "
					OR
				tl.user_id = " . DbCast::id($user_id) . "
			ORDER BY
				tl.update_time DESC
			LIMIT
				0, " . $this->mypage_limit . "
			)
			) AS cts"
		);
		return $data[0]['tl_cunt'];
	}

	/*	 * **********************************
	 * NAME  : get_match_list
	 * INPUT :
	 * 		$thread_id / int / コミュニティID
	 * 		$pd  / int / paged
	 * 		$pp / int / post per page
	 * OUTPUT: array / メンバー一覧
	 * DESC  :
	 *  コミュニティIDからメンバーリストを取得する
	 * NOTICE:
	 * 		失敗など通常はfalseを返すが今回はarray()を返す。
	 * CREATE: 2016.10.20 aoyama
	 * *********************************** */
	public function get_match_list($thread_id, $pd = 0, $pp = 20) {

		//パラメータチェック
		if (StaticFunction::is_empty($thread_id) || !InputVali::is_num($thread_id)) {
			return array();
		}

		$data = $this->query("
			SELECT
				up.user_id,
				up.nickname,
				up.system_id
			FROM
				" . $this->table_match . " AS tm
			LEFT JOIN
				user_public AS up
			ON
				tm.user_id = up.user_id
			WHERE
				tm.thread_id = " . DbCast::id($thread_id) . "
				AND
				tm.active=" . DbCast::integer(DB_ACTIVE_ON) . "
			LIMIT
				" . ($pd * $pp) . ", " . $pp
		);
		//エラー・空の場合
		if ($this->db_select_check_error($data) || $this->db_select_check_empty($data)) {
			return array();
		}

		return $data;
	}

	/*	 * **********************************
	 * NAME  : match_num
	 * INPUT : user_id / string / ユーザID
	 *         thread_id / string / コミュニティID
	 * OUTPUT:
	 * 		true / 既に登録されている
	 * 		false / 登録されていない
	 * DESC  :
	 * 		コミュニティに参加している人数取得用メソッド
	 * NOTICE:
	 * CREATE: 2016.10.20 aoyama
	 * *********************************** */
	public function match_num($thread_id) {

		$match_count = $this->query("
			SELECT
				COUNT(tm.thread_id) AS num
			FROM
				" . $this->table_match . " AS tm
			WHERE
				tm.thread_id = " . DbCast::id($thread_id) . "
				AND
				tm.active = " . DB_ACTIVE_ON
		);

		if (!$match_count) {
			return 0;
		}
		return (int) $match_count[0]; //intキャストは必須！
	}

	/*	 * **********************************
	 * NAME  : registered_community
	 * INPUT : user_id / string / ユーザID
	 *         thread_id / string / コミュニティID
	 * OUTPUT:
	 * 		true / 既に登録されている
	 * 		false / 登録されていない
	 * DESC  :
	 * 		コミュニティに参加しているかのチェック用メソッド
	 * NOTICE:
	 * CREATE: 2016.10.20 aoyama
	 * *********************************** */
	public function registered_community($user_id, $thread_id) {

		$already = $this->query("
			SELECT
				COUNT(tm.thread_id) AS num
			FROM
				" . $this->table_match . " AS tm
			WHERE
				tm.user_id = " . DbCast::id($user_id) . "
				AND
				tm.thread_id = " . DbCast::id($thread_id) . "
				AND
				tm.active = " . DB_ACTIVE_ON
		);

		if ($already[0]['num'] > 0) {
			return true;
		} else {
			return false;
		}
	}

	/*	 * **********************************
	 * NAME  : entry_community
	 * INPUT : param_list / array / 登録したいカラム名配列
	 * OUTPUT: db_shell_insert()のレスポンス(成功時：user_id, 失敗時:false)
	 * DESC  :
	 *  INSERT
	 * NOTICE:
	 * CREATE: 2016.10.20 aoyama
	 * *********************************** */
	public function entry_community($param_list) {
		return $this->db_shell_insert($this->table_match, $param_list);
	}

	/*	 * **********************************
	 * NAME  : leave_community
	 * INPUT : 
	 * 		$user_id / int / ユーザーID
	 * 		$thread_id / int / コミュニティのID
	 * OUTPUT: 
	 * 		成功時：true
	 * 		失敗時:false
	 * DESC  :
	 * 		コミュニティから外れるモデル
	 * 		ここでは自分が管理者か？などはチェックしないので
	 * 		コントローラー側で調整がチェックすること！
	 * NOTICE:
	 * CREATE: 2016.10.20 aoyama
	 * *********************************** */
	public function leave_community($user_id, $thread_id) {
		return $this->db_shell_insert($this->table_match, $param_list);
	}

	/*	 * **********************************
	 * NAME  : get_category_list
	 * INPUT : 
	 * OUTPUT: array / カテゴリ配列
	 * DESC  :
	 *  メソッド
	 * NOTICE:
	 * CREATE: 2016.10.19 aoyama
	 * *********************************** */
	public function get_category_list() {

		$categoryArray = $this->query("
			SELECT "
			/* user_public */ . "
				cm.category_id,
				cm.category_name,
				cm.category_comment
			FROM
				" . $this->category_master . " AS cm
			WHERE
				cm.active=" . DB_ACTIVE_ON . "
			ORDER BY
				cm.sort_num ASC"
		);
		foreach ($categoryArray AS $val) {
			$ret[$val['category_id']] = $val['category_name'];
		}
		return $ret;
	}

	/*	 * **********************************
	 * NAME  : post_response
	 * INPUT : param_list / array / 登録したいカラム名配列
	 * OUTPUT: db_shell_insert()のレスポンス(成功時：user_id, 失敗時:false)
	 * DESC  :
	 *  コミュニティのコメントをINSERT
	 * NOTICE:
	 * CREATE: 2016.10.20 aoyama
	 * *********************************** */
	public function post_response($param_list) {
		return $this->db_shell_insert($this->table_response, $param_list);
	}

	/*	 * **********************************
	 * NAME  : get_response_list
	 * INPUT :
	 * 		$thread_id / int / コミュニティID
	 * 		$pd  / int / paged
	 * 		$pp / int / post per page
	 * OUTPUT: array / コメント一覧
	 * DESC  :
	 *  コメントリストを取得する
	 * NOTICE:
	 * 
	 * CREATE: 2016.10.20 aoyama
	 * *********************************** */
	public function get_response_list($thread_id, $pd = 0, $pp = 20) {

		$data = $this->query("
			SELECT
				tr.thread_id,
				tr.response_text,
				tr.image_file,
				tr.user_id,
				tr.response_id,
				tr.update_time,
				up.user_id,
				up.system_id,
				up.nickname
			FROM
				" . $this->table_response . " AS tr
			LEFT JOIN
				" . $this->user_public . " AS up
			ON
				tr.user_id = up.user_id
			WHERE 
				tr.active=" . DbCast::integer(DB_ACTIVE_ON) . "
				AND
				tr.thread_id = " . DbCast::id($thread_id) . "
			ORDER BY
				tr.create_time DESC
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
	 * INPUT : $thread_id / int / コミュニティID
	 * OUTPUT: string / コメントの数
	 * DESC  :
	 *  スレッド総数を取得する
	 * NOTICE:
	 * CREATE: 2016.10.19 aoyama
	 * *********************************** */
	public function get_response_num($thread_id) {

		$where = "";

		$data = $this->query("
			SELECT
				count(tr.thread_id) AS num
			FROM
				" . $this->table_response . " AS tr
 			WHERE 
				tr.active=" . DbCast::integer(DB_ACTIVE_ON) . "
				AND
				tr.thread_id = " . DbCast::id($thread_id)
		);
		//エラー・空の場合
		if ($this->db_select_check_error($data) || $this->db_select_check_empty($data)) {
			return 0;
		}

		return $data[0]['num'];
	}

	/*	 * **********************************
	 * NAME  : get_thread_list
	 * INPUT :
	 * 		$category / int / カテゴリID
	 * 		$pd  / int / paged
	 * 		$pp / int / post per page
	 * OUTPUT: array / コミュニティ一覧
	 * DESC  :
	 *  コミュニティリストを取得する
	 * NOTICE:
	 * 
	 * CREATE: 2016.10.19 aoyama
	 * *********************************** */
	public function get_thread_list($category = null, $pd = 0, $pp = 20) {

		$where = "";

		//
		//
		if (!StaticFunction::is_empty($category)) {
			$where = " AND category_id = " . DbCast::integer($category) . " ";
		}

		$data = $this->query("
			SELECT
				th.thread_id,
				th.community_name,
				th.community_detail,
				th.category_id,
				th.image_file
			FROM
				" . $this->table_thread . " AS th
			WHERE 
				th.active=" . DbCast::integer(DB_ACTIVE_ON) . "
				" . $where . "
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
	 * NAME  : get_thread_num
	 * INPUT : $category / int / カテゴリID
	 * OUTPUT: string / スレッドの数
	 * DESC  :
	 *  スレッド総数を取得する
	 * NOTICE:
	 * CREATE: 2016.10.19 aoyama
	 * *********************************** */
	public function get_thread_num($category = null) {

		$where = "";

		//
		if (!StaticFunction::is_empty($category)) {
			$where = " AND category_id = " . DbCast::integer($category) . " ";
		}

		$data = $this->query("
			SELECT
				count(th.thread_id) AS num
			FROM
				" . $this->table_thread . " AS th
 			WHERE 
				th.active=" . DbCast::integer(DB_ACTIVE_ON) . "
				" . $where
		);
		//エラー・空の場合
		if ($this->db_select_check_error($data) || $this->db_select_check_empty($data)) {
			return 0;
		}

		return $data[0]['num'];
	}

	/*	 * **********************************
	 * NAME  : get_detail_by_id
	 * INPUT : $thread_id / integer / コミュニティID
	 * OUTPUT: array / データ
	 * DESC  :
	 *  $thread_idからコミュニティの詳細情報を取得する
	 * NOTICE:
	 * CREATE: 2016.10.19 aoyama
	 * *********************************** */
	public function get_detail_by_id($thread_id) {

		//パラメータチェック
		if (StaticFunction::is_empty($thread_id) || !InputVali::is_num($thread_id)) {
			return false;
		}

		return $this->query("
			SELECT 
				th.thread_id,
				th.create_time,
				th.update_time,
				th.community_name,
				th.community_detail,
				th.category_id,
				th.user_id,
				th.active,
				th.image_file,
				up.nickname,
				up.system_id
			FROM
				" . $this->table_thread . " AS th
			LEFT JOIN
				user_public AS up
			ON
				th.user_id = up.user_id
			WHERE
				th.thread_id=" . DbCast::id($thread_id) . "
				AND th.active=" . DB_ACTIVE_ON
		);
	}

	/*	 * **********************************
	 * NAME  : log_login
	 * INPUT : user_id / string / ユーザID
	 * OUTPUT: NONE
	 * DESC  :
	 *  ログインをログとして保存する
	 * NOTICE:
	 * CREATE: 2016.09.13 hesaka
	 * *********************************** */
	public function log_login($user_id) {
		$this->db_shell_insert(
			$this->table_name_log_login, array(
			'user_type' => DB_USER_TYPE_SYSTEM,
			'user_id' => DbCast::id($user_id),
			'login_time' => DbCast::datetime(DbDateTime::get_cur_datetime())
			)
		);
	}

	/*	 * **********************************
	 * NAME  : select
	 * INPUT : select_list / array / 取得したいカラム名配列
	 *         condition / array / whereに用いる検索条件の連想配列
	 * OUTPUT: db_shecll_select()のレスポンス
	 * DESC  :
	 *  SELECT
	 * NOTICE:
	 * CREATE: 2016.10.17 aoyama
	 * *********************************** */
	public function select($select_list, $condition = NULL) {
		LOGS_DBG_LV1('*** QUERY [SELECT] START ***');
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
	 * CREATE: 2016.10.17 aoyama
	 * *********************************** */
	public function update($param_list, $condition = NULL) {
		LOGS_DBG_LV1('*** QUERY [UPDATE] START ***');
		return $this->db_shell_update($this->table_name, $param_list, $condition);
	}

}

?>
