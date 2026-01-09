<?php

/* * **********************************
 * NAME:MailMasterModel
 * DESC:
 *  MailMaterテーブル用モデルクラス
 *  上記テーブルに対してアクセス(クエリなど)する場合は
 *  当該クラスにて行うこと！
 * NOTICE:
 *  基本的にはDbShellクラスを継承し、そちらでPDOインスタンスアクセスを行う
 *  場合によっては当該クラスで直接触ることもあるかも知れないが、
 *  できるだけDbShellクラスにて行うこと！
 * CREATE: 2016.10.17 aoyama
 * *********************************** */
class MailMasterModel extends DbShell {

	private $table_name = "mail_master";
	private $table_name_log_login = "log_login";

	public function __construct() {
		parent::__construct();
	}

	/*	 * **********************************
	 * NAME  : get_mail_text
	 * INPUT : $message_type / string / メッセージタイプ
	 * OUTPUT: string / メッセージテキスト（メールの本文）
	 * DESC  :
	 *  メソッド
	 * NOTICE:
	 * CREATE: 2016.10.17 aoyama
	 * *********************************** */
	public function get_mail_text($message_type) {

		if (StaticFunction::is_empty($message_type)) {
			return false;
		}
		if (!$ret = $this->select(
			array("message_text"), array(
			"WHERE" => array(
				"message_type" => DbCast::string($message_type)
			)
			)
			)) {
			return false;
		}

		return $ret[0]['message_text'];
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
