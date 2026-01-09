<?php

/* * **********************************
 * NAME:UserSystemModel
 * DESC:
 *  SalesforceAuthSettingテーブル用モデルクラス
 *  上記テーブルに対してアクセス(クエリなど)する場合は
 *  当該クラスにて行うこと！
 * NOTICE:
 *  基本的にはDbShellクラスを継承し、そちらでPDOインスタンスアクセスを行う
 *  場合によっては当該クラスで直接触ることもあるかも知れないが、
 *  できるだけDbShellクラスにて行うこと！
 * CREATE: 2015.08.27 hesaka
 * *********************************** */
class UserSystemModel extends DbShell {

	private $table_name = "user_system";
	private $table_name_log_login = "log_login";
	
	public function __construct() {
		parent::__construct();
	}

	/* * **********************************
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
	
	/* * **********************************
	 * NAME  : verification
	 * INPUT : mail_address / string / メールアドレス
	 *         password_hash / string / 暗号化したパスワード
	 * OUTPUT: array / 検索結果配列
	 * DESC  :
	 *  ログイン認証用メソッド
	 * NOTICE:
	 *  PUBLICのextend対応でselectと分ける必要が出たため、
	 *  SYSTEM側でも分ける
	 * CREATE: 2016.09.13 hesaka
	 * UPDATE: 2016.10.06 hesaka 引数にuser_idを追加
	 *                           ※uesr_idで検索するのはsession_verification
	 * *********************************** */
	public function verification($mail_address, $password_hash, $user_id) {

		/*
		 * 検索条件作成
		 * ※user_idがあれば優先する
		 */
		if (!StaticFunction::is_empty($user_id))  {
			$where = " AND user_id=" . DbCast::id($user_id);
		} else {
			$where = " AND mail_address=" . DbCast::string($mail_address);
			$where .= " AND password=" . DbCast::string($password_hash);
		}

		return $this->query("
			SELECT 
				user_id, system_id, mail_address, " . /* password, 外す */ "
				login_time, last_access_time, login_failed_count, 
				first_name, middle_name, last_name,
				extension_photo, create_time, modify_time,
				authority_id, head_name
			FROM " . DbCast::table_name($this->table_name) . "
			WHERE
				active=" . DB_ACTIVE_ON
				. $where
		);
	}
	
	/* * **********************************
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
			$this->table_name_log_login, 
			array(
			    'user_type' => DB_USER_TYPE_SYSTEM,
			    'user_id' => DbCast::id($user_id),
			    'login_time' => DbCast::datetime(DbDateTime::get_cur_datetime())
			)
		);
	}

	/* * **********************************
	 * NAME  : get_user_by_mail
	 * INPUT : $mail_address / string / メールアドレス
	 * OUTPUT: array / ユーザ情報
	 * DESC  :
	 *  指定メールアドレスからユーザ情報を取得する
	 * NOTICE:
	 *  LIMEから引き継いだデータには、メールアドレスが
	 *  重複しているものが多数ある
	 *  そのデータに対してメールアドレスだけで取得を行うと
	 *  何がとれるかはランダムとなる
	 *  なので、登録日時の降順でソートして、一番目のものを
	 *  ターゲットとして取得する
	 *  これは、ユーザの登録タイミングが最新のものが、
	 *  今使用しているユーザであるだろうというところからのものである
	 * CREATE: 2015.11.25 hesaka
	 * *********************************** */
	public function get_user_by_mail($mail_address) {
		LOGS_DBG_LV1('*** QUERY [SELECT] START ***');

		//引数が空ならエラー
		if (StaticFunction::is_empty($mail_address)) {
			return false;
		}

		return $this->query("
			SELECT mail_address, name
			FROM " . $this->table_name . "
			WHERE 
				mail_address=" . DbCast::string($mail_address) . "
				AND active=" . DB_ACTIVE_ON . "
			ORDER BY create_time DESC
			LIMIT 0, 1"
		);
	}
	
	/* * **********************************
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
	
}

?>
