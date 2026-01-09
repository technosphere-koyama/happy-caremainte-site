<?php

/* * **********************************
 * NAME:MypageMessageModel
 * DESC:
 *  メッセージ用のモデルクラス
 * NOTICE:
 * CREATE: 2016.10.17 aoyama
 * *********************************** */
class MypageMessageModel extends DbShell {

	private $table_name = "message";

	public function __construct() {
		parent::__construct();
	}

	/*	 * **********************************
	 * NAME  : get_message_unlead_num
	 * INPUT : $status / int / ステータス
	 * OUTPUT: int
	 * DESC  :
	 *  受信側の未読メッセージ件数取得用メソッド
	 * NOTICE:
	 * CREATE: 2016.12.22 aoyama
	 * *********************************** */
	public function get_message_unlead_num($user_id) {

		$result = $this->query("
			SELECT
				count(ms.message_id) AS message_num
			FROM
				" . $this->table_name . " AS ms
			WHERE
				ms.target_user=" . DbCast::id($user_id) . "
				AND
				ms.read_status = 1
				AND
				ms.active=" . DB_ACTIVE_ON
		);
		if (!$result) {
			return 0;
		}

		return (int) $result[0]['message_num'];
	}	
	
	/*	 * **********************************
	 * NAME  : get_message_user_list
	 * INPUT : 
	 *		$from_user_id / int / 送信者ID
	 *		$to_user_id / int / 受信者ID
	 * OUTPUT: array / 検索結果配列
	 * DESC  :
	 *  受信側メッセージ一覧取得用メソッド
	 * NOTICE:
	 * CREATE: 2016.10.17 aoyama
	 * CREATE: 2016.12.15 aoyama
	 *		仕様変更により特定のユーザとのやり取りを取得
	 * *********************************** */
	public function get_message_user_list($user_id, $pd, $pp) {

		//ステータス指定がある場合	
//		$statusVal = ($status == 1 || $status == 2) ? 'AND ms.read_status=' . $status : "";

		
		return $this->query("
			SELECT
				ms.message_id,
				ms.create_time,
				ms.update_time,
				ms.message_comment,
				ms.message_id,
				ms.create_time,
				ms.update_time,
				ms.user_id AS from_user_id,
				ms.target_user AS to_user_id,
				ms.message_comment,
				ms.read_status,
				ms.active,
				ms.image_file,
				up1.nickname AS from_nickname,
				up1.system_id AS from_system_id,
				up2.nickname AS to_nickname,
				up2.system_id AS to_system_id,
				CASE
					WHEN ms.user_id=" . DbCast::id($user_id) . " THEN ms.target_user
					WHEN ms.target_user=" . DbCast::id($user_id) . " THEN ms.user_id
				END group_user,
				CASE
					WHEN ms.user_id=" . DbCast::id($user_id) . " THEN up2.system_id
					WHEN ms.target_user=" . DbCast::id($user_id) . " THEN up1.system_id
				END group_system_id,
				CASE
					WHEN ms.user_id=" . DbCast::id($user_id) . " THEN up2.nickname
					WHEN ms.target_user=" . DbCast::id($user_id) . " THEN up1.nickname
				END group_nickname
				
			FROM
				message AS ms
			INNER JOIN
				(
					SELECT
						MAX(create_time) AS max_obj,
						CASE
							WHEN user_id=" . DbCast::id($user_id) . " THEN target_user
							WHEN target_user=" . DbCast::id($user_id) . " THEN user_id
						END group_user
					FROM
						message AS ms2
					GROUP BY
						group_user

				) AS ms_sort
			ON
				group_user = ms_sort.group_user
				AND
				create_time = ms_sort.max_obj
				
			LEFT JOIN
				user_public AS up1
			ON
				ms.user_id = up1.user_id
			LEFT JOIN
				user_public AS up2
			ON
				ms.target_user = up2.user_id
			WHERE
				(
					ms.user_id=" . DbCast::id($user_id) . "
					OR
					ms.target_user=" . DbCast::id($user_id) . "
				)
				AND
				ms.active=" . DB_ACTIVE_ON . "


			ORDER BY
				create_time DESC
			LIMIT
				" . ($pd * $pp) . "," . $pp
		);
		

	}	
	/*	 * **********************************
	 * NAME  : get_message_user_list_num
	 * INPUT : 
	 *		$from_user_id / int / 送信者ID
	 *		$to_user_id / int / 受信者ID
	 * OUTPUT: array / 検索結果配列
	 * DESC  :
	 *  受信側メッセージ一覧取得用メソッド
	 * NOTICE:
	 * CREATE: 2016.10.17 aoyama
	 * CREATE: 2016.12.15 aoyama
	 *		仕様変更により特定のユーザとのやり取りを取得
	 * *********************************** */
	public function get_message_user_list_num($user_id) {

		//ステータス指定がある場合	
//		$statusVal = ($status == 1 || $status == 2) ? 'AND ms.read_status=' . $status : "";

		
		$result = $this->query("
			SELECT
				count(*) AS count_num
			FROM
				message AS ms
			INNER JOIN
				(
					SELECT
						MAX(create_time) AS max_obj,
						CASE
							WHEN user_id=" . DbCast::id($user_id) . " THEN target_user
							WHEN target_user=" . DbCast::id($user_id) . " THEN user_id
						END group_user
					FROM
						message AS ms2
					GROUP BY
						group_user

				) AS ms_sort
			ON
				group_user = ms_sort.group_user
				AND
				create_time = ms_sort.max_obj
			WHERE
				(
					ms.user_id=" . DbCast::id($user_id) . "
					OR
					ms.target_user=" . DbCast::id($user_id) . "
				)
				AND
				ms.active=" . DB_ACTIVE_ON
		);
		if (!$result) {
			return 0;
		}

		return (int) $result[0]['count_num'];

	}		
	/*	 * **********************************
	 * NAME  : send_message
	 * INPUT : select_list / array / 取得したいカラム名配列
	 *         condition / array / whereに用いる検索条件の連想配列
	 * OUTPUT: db_shecll_select()のレスポンス
	 * DESC  :
	 * 		メッセージを送信するメソッド
	 * NOTICE:
	 * CREATE: 2016.11.1 aoyama
	 * *********************************** */
	public function send_message($from_id, $to_id, $text, $file = null) {

		$date = DbDateTime::get_cur_datetime();

		return $this->db_shell_insert($this->table_name, array(
				"create_time" => DbCast::datetime($date),
				"update_time" => DbCast::datetime($date),
				"user_id" => DbCast::id($from_id),
				"message_comment" => DbCast::string($text),
				"target_user" => DbCast::id($to_id),
				"image_file" => DbCast::string($file),
				"active" => DB_ACTIVE_ON
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
	 * CREATE: 2015.08.27 hesaka
	 * *********************************** */
	public function select($select_list, $condition = NULL) {
		LOGS_DBG_LV1('*** QUERY [SELECT] START ***');
		return $this->db_shell_select($this->table_name, $select_list, $condition);
	}

	/*	 * **********************************
	 * NAME  : get_message_detail
	 * INPUT : 
	 * 		$message_id / int / メッセージID
	 * 		$user_id / int / 受信者ID
	 * OUTPUT: array / 検索結果配列
	 * DESC  :
	 *  メッセージ詳細取得用メソッド
	 * NOTICE:
	 * CREATE: 2016.10.23 aoyama
	 * *********************************** */
	public function get_message_recieve_detail($message_id, $user_id) {

		return $this->query("
			SELECT
				ms.message_id,
				ms.create_time,
				ms.update_time,
				ms.user_id,
				ms.message_comment,
				ms.read_status,
				ms.target_user,
				ms.image_file,
				up.nickname,
				up.system_id
			FROM
				" . $this->table_name . " AS ms
			LEFT JOIN
				user_public AS up
			ON
				ms.user_id = up.user_id
			WHERE
				ms.message_id = " . DbCast::id($message_id) . "
				AND
				ms.target_user=" . DbCast::id($user_id) . "
				AND
				ms.target_show=" . DB_ACTIVE_ON . "
				AND
				ms.active=" . DB_ACTIVE_ON
		);
	}

	/*	 * **********************************
	 * NAME  : get_message_list
	 * INPUT : 
	 *		$from_user_id / int / 送信者ID
	 *		$to_user_id / int / 受信者ID
	 * OUTPUT: array / 検索結果配列
	 * DESC  :
	 *  受信側メッセージ一覧取得用メソッド
	 * NOTICE:
	 * CREATE: 2016.10.17 aoyama
	 * CREATE: 2016.12.15 aoyama
	 *		仕様変更により特定のユーザとのやり取りを取得
	 * *********************************** */
	public function get_message_list($from_user_id, $to_user_id, $pd, $pp) {

		//ステータス指定がある場合	
//		$statusVal = ($status == 1 || $status == 2) ? 'AND ms.read_status=' . $status : "";

		return $this->query("
			SELECT "
				/* user_public */ . "
				ms.message_id,
				ms.create_time,
				ms.update_time,
				ms.user_id AS from_user_id,
				ms.target_user AS to_user_id,
				ms.message_comment,
				ms.read_status,
				ms.active,
				ms.image_file,
				up1.nickname AS from_nickname,
				up1.system_id AS from_system_id,
				up2.nickname AS to_nickname,
				up2.system_id AS to_system_id
			FROM
				" . $this->table_name . " AS ms
			LEFT JOIN
				user_public AS up1
			ON
				ms.user_id = up1.user_id
			LEFT JOIN
				user_public AS up2
			ON
				ms.target_user = up2.user_id
			WHERE
				(
					(
						ms.user_id=" . DbCast::id($from_user_id) . "
						AND
						ms.target_user=" . DbCast::id($to_user_id) . "
					)
					OR
					(
						ms.user_id=" . DbCast::id($to_user_id) . "
						AND
						ms.target_user=" . DbCast::id($from_user_id) . "
					)
				)
				AND
				ms.active=" . DB_ACTIVE_ON . "
			ORDER BY
				ms.create_time DESC
			LIMIT
				" . ($pd * $pp) . "," . $pp
		);
	}

	/*	 * **********************************
	 * NAME  : get_message_list_num
	 * INPUT : $status / int / ステータス
	 * OUTPUT: array / 検索結果配列
	 * DESC  :
	 *  受信側メッセージ一覧取得用メソッド
	 * NOTICE:
	 * CREATE: 2016.10.17 aoyama
	 * UPDATE: 2016.12.15 aoyama
	 *		仕様変更により調整
	 * *********************************** */
	public function get_message_list_num($from_user_id, $to_user_id, $status = 0) {

		//ステータス指定がある場合	
		//$statusVal = ($status == 1 || $status == 2) ? 'AND ms.read_status=' . DbCast::integer($status) : "";

		$result = $this->query("
			SELECT
				count(ms.message_id) AS message_num
			FROM
				" . $this->table_name . " AS ms
			WHERE
				(
					(
						ms.user_id=" . DbCast::id($from_user_id) . "
						AND
						ms.target_user=" . DbCast::id($to_user_id) . "
					)
					OR
					(
						ms.user_id=" . DbCast::id($to_user_id) . "
						AND
						ms.target_user=" . DbCast::id($from_user_id) . "
					)
				)
				AND
				ms.active=" . DB_ACTIVE_ON
		);
		if (!$result) {
			return 0;
		}

		return (int) $result[0]['message_num'];
	}

	/*	 * **********************************
	 * NAME  : show_disable_recieve
	 * INPUT : $message_id / int / 更新したいメッセージID
	 * OUTPUT:	
	 * DESC  :
	 *		メッセージの非表示処理（受信者側）
	 * NOTICE:
	 * CREATE: 2016.10.24 aoyama
	 * *********************************** */
	public function show_disable_recieve($message_id) {

		//引数が空ならエラー
		if (StaticFunction::is_empty($message_id)) {
			return false;
		}

		$affect = $this->db_shell_update(
			$this->table_name, array(
			'target_show' => DB_ACTIVE_OFF,
			'update_time' => DbCast::datetime(DbDateTime::get_cur_datetime())
			), array(
				'WHERE' => array(
					'message_id' => DbCast::id($message_id)
				)
			)
		);
		
		//変更するデータがあった場合
		if($affect > 0 ) {
			return true;
		}
		return false;
	}	
	
	/*	 * **********************************
	 * NAME  : unread_update
	 * INPUT : $user_id / int / 送信者のユーザーID
	 * OUTPUT:	
	 * DESC  :
	 *		メッセージの既読フラグを変更する（1→2：既読）
	 * NOTICE:
	 * CREATE: 2016.12.22 aoyama
	 * *********************************** */
	public function unread_update($from_user_id,$to_user_id) {

		//引数が空ならエラー
		if (StaticFunction::is_empty($from_user_id) || StaticFunction::is_empty($to_user_id)) {
			return false;
		}

		return $this->db_shell_update(
				$this->table_name, 
				array(
					'read_status' => 2,
					'update_time' => DbCast::datetime(DbDateTime::get_cur_datetime())
				),
				array(
					'WHERE' => array(
						'read_status' => 1,
						'user_id' => DbCast::id($from_user_id),
						'target_user' => DbCast::id($to_user_id),
						'active' => DB_ACTIVE_ON
					)
				)
		);
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
	 * NAME  : get_detail_for_purchase
	 * INPUT : user_id / string / ユーザID
	 * OUTPUT: array / データ
	 * DESC  :
	 *  user_idによりユーザ情報を取得する
	 * NOTICE:
	 *  購入処理にて、order_masterに入れるユーザ情報を
	 *  取得する際に使用することを目的としている
	 * CREATE: 2015.11.27 hesaka
	 * *********************************** */
	public function get_detail_for_purchase($user_id) {

		if (StaticFunction::is_empty($user_id)) {
			return false;
		}

		return $this->query("
			SELECT
				user_id, system_id, name, name_kana, sex,
				birth_date, zip_code, prefecture, municipality,
				house_number, building, phone, mail_address
			FROM " . $this->table_name . "
			WHERE
				user_id=" . DbCast::float($user_id) . "
				AND active=" . DB_ACTIVE_ON);
	}

	/*	 * **********************************
	 * NAME  : check_mail
	 * INPUT : $mail / string
	 * OUTPUT: NONE
	 * DESC  :
	 * NOTICE:
	 * CREATE: 2015.12.21 aoyama
	 * *********************************** */
	public function check_mail($mail) {

		$data = $this->query('
			SELECT
				count(um.user_id) AS mail_num
			FROM
				' . $this->table_name . ' um
			WHERE
				um.mail_address = ' . DbCast::string($mail) . '
				AND um.active = ' . DB_ACTIVE_ON . '
		');

		if ($data[0]['mail_num'] > 0) {
			return false;
		} else {
			return true;
		}
	}

}

?>
