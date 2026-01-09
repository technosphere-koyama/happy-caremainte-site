<?php

/* * **********************************
 * NAME:UserMatchModel
 * DESC:
 *  会員情報用のモデルクラス
 * NOTICE:
 * CREATE: 2016.10.19 aoyama
 * *********************************** */
class UserMatchModel extends DbShell {

	private $sGroup;
	private $table_name = "friend_match";
	private $table_user = "user_public";

	public function __construct() {
		parent::__construct();
		$this->sGroup = 'user_public';
	}

	/*	 * **********************************
	 * NAME  : get_friend_list_fashion
	 * INPUT : $user_id / string / ユーザーID
	 * OUTPUT: array / ユーザー一覧
	 * DESC  :
	 * 		ユーザーIDからフレンドではない、同じファッション属性のユーザーを取得する
	 * 		friend_status
	 * 			commit:フレンド状態
	 * 			request:$user_idが申請している状態
	 * 			confirm:$user_idの承認待ち状態
	 * CREATE: 2017.2.10 aoyama
	 * *********************************** */
	public function get_friend_list_fashion($user_id, $fashion_id, $brand,$pd = 0, $pp = 5) {

		//引数が空ならエラー
		if (StaticFunction::is_empty($user_id)) {
			return false;
		}
		
		/* where条件リセット */
		$where_val = "";
		/* fashion_id に値が入っていた場合 */
		if (preg_match("/^[0-9]{1,2}$/", $fashion_id)) {
			$where_val .= " AND up.fashion_id = " . $fashion_id . " ";
		}
		/* brand に値が入っていた場合 */
		if (!StaticFunction::is_empty($brand)) {
			$where_val .= " AND up.like_brand LIKE '" . $brand . "' ";
		}

		$data = $this->query("
				SELECT
					up.user_id AS show_user_id
					,up.system_id AS show_system_id
					,up.system_user_id  AS show_system_user_id
					,up.nickname AS show_nickname
					,up.friend_count AS show_friend_count
					,fm.user_id
				FROM
					" . $this->table_user . " AS up
				LEFT JOIN
					(
						" /* まずは自分から申請しているパターン */ . "
						(
						SELECT
							fm1.user_id AS user_id,
							fm1.friend_id AS friend_id
						FROM
							" . $this->table_name . " AS fm1
						WHERE 
							fm1.user_id=" . DbCast::id($user_id) . "
							AND
							fm1.commit_status = 1
						)
						UNION
						" /* 申請されているパターン */ . "
						(
						SELECT
							fm2.friend_id AS user_id,
							fm2.user_id AS friend_id
						FROM
							" . $this->table_name . " AS fm2
						WHERE 
							fm2.friend_id=" . DbCast::id($user_id) . "
							AND
							fm2.commit_status = 1
						)
					) AS fm
				ON
					up.user_id = fm.friend_id
				WHERE
					up.user_id != " . DbCast::id($user_id) . "
					AND
					fm.user_id IS NULL
					AND
					up.active = " . DB_ACTIVE_ON . "
					" . $where_val . /* ファッションIDまたはブランドが指定されていた場合 */ " 
				ORDER BY
					rand()
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
	 * NAME  : set_friend_commit
	 * INPUT : $user_id / int / ユーザーID
	 *         $match_id / int / マッチングID
	 * OUTPUT:
	 * 		true / 成功
	 * 		false / 失敗
	 * DESC  :
	 * NOTICE:
	 * CREATE: 2016.10.26 aoyama
	 * *********************************** */
	public function set_friend_commit($user_id, $match_id) {

		//フレンド数を取得

		$affected = $this->db_shell_update($this->table_name, array(
			"commit_status" => 1
			), array(
			'WHERE' => array(
				'friend_id' => DbCast::id($user_id),
				'match_id' => DbCast::id($match_id),
			)
			)
		);

		//エラー・空の場合
		if ($affected > 0) {
			return true;
		}
		return false;
	}

	/*	 * **********************************
	 * NAME  : set_friend_count
	 * INPUT : select_list / array / 取得したいカラム名配列
	 *         condition / array / whereに用いる検索条件の連想配列
	 * OUTPUT: 
	 * 		true / 成功
	 * 		false / 失敗
	 * DESC  :
	 * NOTICE:
	 * CREATE: 2016.10.26 aoyama
	 * *********************************** */
	public function set_friend_count($user_id) {

		//フレンド数を取得
		$friend_count = $this->get_friend_num($user_id);

		$data = $this->exec("
			UPDATE
				" . $this->table_user . "
			SET
				friend_count = " . DbCast::float($friend_count) . "
			WHERE 
				user_id=" . DbCast::id($user_id) . "
			"
		);

		//エラー・空の場合
		if ($data) {
			return true;
		}


		return $this->db_shell_select($this->table_name, $select_list, $condition);
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
	 * NAME  : set
	 * INPUT : user_id / string / ユーザID
	 *         target_id / string / フォローするユーザID
	 * OUTPUT:
	 * 		true / フレンドの場合
	 * 		false / フレンドではない場合
	 * DESC  :
	 * 		フォロー状態を返す
	 * NOTICE:
	 * CREATE: 2016.10.21 aoyama
	 * UPDATE: 2016.10.26 aoyama
	 * 		facebook方式に変更
	 * *********************************** */
	public function is_match($user_id, $target_id) {

		$already = $this->query("
			SELECT
				COUNT(fm.match_id) AS num
			FROM
				" . $this->table_name . " AS fm
			WHERE
			(
				fm.user_id = " . DbCast::id($user_id) . "
				AND
				fm.friend_id = " . DbCast::id($target_id) . "
			)
			OR
			(
				fm.friend_id = " . DbCast::id($user_id) . "
				AND
				fm.user_id = " . DbCast::id($target_id) . "
			)"
		);

//		var_dump($already);
//		exit;

		if ((int) $already[0]['num'] > 0) {
			return true;
		} else {
			return false;
		}
	}

	/*	 * **********************************
	 * NAME  : set
	 * INPUT : user_id / string / ユーザID
	 *         target_id / string / フォローするユーザID
	 * OUTPUT:
	 * 		true / 成功の場合
	 * 		false / 失敗の場合
	 * DESC  :
	 * 		SNSユーザーフォロー用メソッド
	 * NOTICE:
	 * CREATE: 2016.10.19 aoyama
	 * *********************************** */
	public function set($user_id, $target_id, $mode = 0) {

		if (!self::is_match($user_id, $target_id)) {

			//現在日時を取得
			$cur_time = DbDateTime::get_cur_datetime();

			$param_list = array(
				"create_time" => DbCast::datetime($cur_time),
				"update_time" => DbCast::datetime($cur_time),
				"user_id" => DbCast::id($user_id),
				"friend_id" => DbCast::id($target_id),
				"commit_status" => DbCast::integer($mode),
				"active" => DB_ACTIVE_ON
			);

			$this->db_shell_insert($this->table_name, $param_list);

			return true;
		}
		return false;
	}

	/*	 * **********************************
	 * NAME  : set
	 * INPUT : user_id / string / ユーザID
	 *         target_id / string / フォローするユーザID
	 * OUTPUT:
	 * 		true / 成功の場合
	 * 		false / 失敗の場合
	 * DESC  :
	 * 		SNSユーザーフォロー解除用メソッド
	 * NOTICE:
	 * 		ハッピーさんアカウントを解除しようとするとエラーにするが、
	 * 		それぞれのエラーメッセージ処理はコントローラで実施
	 * CREATE: 2016.10.19 aoyama
	 * UPDATE: 2016.10.26 aoyama
	 * 		フレンド解除時にもユーザーテーブルのフレンドカウントを更新
	 * *********************************** */
	public function un_set($user_id, $target_id) {

		//ハッピーさんアカウントは解除させない
		if ($target_id == CONF::read("MASTER_USER.USER_ID")) {
			return false;
		}

		$query = "
			DELETE
			FROM
				" . $this->table_name . "
			WHERE 
			(
				(
					user_id=" . DbCast::id($user_id) . "
						AND
					friend_id=" . DbCast::id($target_id) . "
				)
				OR
				(
					friend_id=" . DbCast::id($user_id) . "
						AND
					user_id=" . DbCast::id($target_id) . "
				)
			)";

		$data = $this->exec($query);

		//エラー・空の場合
		if ($data) {
			//DELETE 処理なのでログに残す
			LOGS_DELETE($query);

			return true;
		}

		return false;
	}

	/*	 * **********************************
	 * NAME  : get_friend_list
	 * INPUT : $user_id / string / ユーザーID
	 * OUTPUT: array / ユーザー一覧
	 * DESC  :
	 * 		ユーザーIDからフレンドリスト情報を取得する
	 * 
	 * 		friend_status
	 * 			commit:フレンド状態
	 * 			request:$user_idが申請している状態
	 * 			confirm:$user_idの承認待ち状態
	 * NOTICE:
	 * 		双方向チェックのためUNIONしている。
	 * CREATE: 2016.10.19 aoyama
	 * UPDATE: 2016.10.26 aoyama
	 * 		facebook方式に変更
	 * *********************************** */
	public function get_friend_list($user_id, $pd = 0, $pp = 20, $type = null) {

		//引数が空ならエラー
		if (StaticFunction::is_empty($user_id)) {
			return false;
		}

		/*
		 * ガジェット用などのフレンド状態が「complete」状態のものだけを
		 * 取得したい場合は有効にする
		 */
		$where_fm1 = "";
		$where_fm2 = "";
		if ($type == 'commit') {
			$where_fm1 = " AND fm1.commit_status = 1";
			$where_fm2 = " AND fm2.commit_status = 1";
		}

		$data = $this->query("
			" /* まずは自分から申請しているパターン */ . "
			(
			SELECT
				fm1.create_time AS create_time,
				fm1.match_id AS match_id,
				up1.system_id AS system_id,
				up1.nickname AS nickname,
				up1.friend_count AS friend_count,
				CASE
					fm1.commit_status
					WHEN 1 THEN 'commit'
					ELSE 'request'
				END AS friend_status
			FROM
				" . $this->table_name . " AS fm1
			LEFT JOIN
				" . $this->table_user . " AS up1
			ON
				fm1.friend_id=up1.user_id
			WHERE 
				fm1.user_id=" . DbCast::id($user_id) . "
					" . $where_fm1 . "
			)
			UNION
			
			" /* 申請されているパターン */ . "
			(
			SELECT
				fm2.create_time AS create_time,
				fm2.match_id AS match_id,
				up2.system_id AS system_id,
				up2.nickname AS nickname,
				up2.friend_count AS friend_count,
				CASE
					fm2.commit_status
					WHEN 1 THEN 'commit'
					ELSE 'confirm'
				END AS friend_status
			FROM
				" . $this->table_name . " AS fm2
			LEFT JOIN
				" . $this->table_user . " AS up2
			ON
				fm2.user_id = up2.user_id
			WHERE 
				fm2.friend_id=" . DbCast::id($user_id) . "
					" . $where_fm2 . "
			)
			ORDER BY
				create_time DESC
			" /* UNIONを絞り込む */ . "
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
	 * NAME  : get_friend_num
	 * INPUT : $user_id / string / ユーザーID
	 * OUTPUT: string / フレンドの数
	 * DESC  :
	 *  ユーザーIDからフレンド総数を取得する
	 * NOTICE:
	 * CREATE: 2016.10.19 aoyama
	 * *********************************** */
	public function get_friend_num($user_id) {

		//引数が空ならエラー
		if (StaticFunction::is_empty($user_id)) {
			return 0;
		}

		$data = $this->query("
			SELECT
				count(fm.match_id) AS num
			FROM
				" . $this->table_name . " AS fm
 			WHERE
				(
				fm.user_id=" . DbCast::id($user_id) . "
					OR
				fm.friend_id=" . DbCast::id($user_id) . "
				)
				AND fm.commit_status=" . DB_FOLLOW_STATUS_ON
		);
		//エラー・空の場合
		if ($this->db_select_check_error($data) || $this->db_select_check_empty($data)) {
			return 0;
		}

		return $data[0]['num'];
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

	/*	 * **********************************
	 * NAME  : update
	 * INPUT : param_list / array / 更新したいカラム名配列
	 *         sid / array / whereに用いるsid
	 * OUTPUT: db_shecll_update()のレスポンス
	 * DESC  :
	 *  UPDATE
	 * NOTICE:
	 * CREATE: 2015.11.15 sonoda
	 * UPDATE: 2015.11.24 hesaka 表側とメソッド名がかぶるので変更した
	 * *********************************** */
	public function admin_update($sid, $param_list) {

		//引数が空ならエラー
		if (StaticFunction::is_empty($sid) || StaticFunction::is_empty($param_list)) {
			return false;
		}

		LOGS_DBG_LV1('*** QUERY [UPDATE] START ***');

		return $this->db_shell_update(
				$this->table_name, $param_list += array(
				//更新日時も更新
				'modify_time' => DbCast::datetime(DbDateTime::get_cur_datetime())
				), array(
				'WHERE' => array(
					'system_id' => DbCast::system_id($sid)
				)
				)
		);
	}

	/*	 * **********************************
	 * NAME  : delete_by_system_id
	 * INPUT : system_id / string / システムID
	 * OUTPUT: true / 成功時
	 *         false / 失敗時
	 * DESC  :
	 *  削除フラグを立てるのみで、物理的には残す。
	 * NOTICE:
	 * CREATE: 2015.11.15 sonoda
	 * *********************************** */
	public function delete_by_system_id($system_id) {

		LOGS_DBG_LV1('*** QUERY [SELECT] START ***');

		return $this->db_shell_update(
				$this->table_name, array(
				'active' => DB_ACTIVE_DELETE,
				'delete_time' => DbCast::datetime(DbDateTime::get_cur_datetime())
				), array(
				'WHERE' => array(
					'system_id' => DbCast::system_id($system_id)
				)
				)
		);
	}

}

?>
