<?php

/* * **********************************
 * NAME:UserPublicModel
 * DESC:
 *  会員情報用のモデルクラス
 * NOTICE:
 * CREATE: 2015.11.15 sonoda
 * *********************************** */
class UserPublicModel extends DbShell {

	private $sGroup;
	private $table_name = "user_public";
	private $table_name_log_login = "log_login";
	private $search_condition;

	public function __construct() {
		parent::__construct();
		$this->sGroup = 'user_public';

		//検索conditionパラメータ初期化
		$this->search_condition = '';
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
	 * NAME  : verification
	 * INPUT : $system_user_id / string / 基幹ユーザーコード(077777とか)
	 * OUTPUT: array / 検索結果配列
	 * DESC  :
	 * NOTICE:
	 * CREATE: 2016.09.13 hesaka
	 * UPDATE: 2016.10.13 aoyama
	 *		セッションのsystem_user_idで検索する。
	 *		Login.incのverificationメソッドで使われているので影響ないように
	 *		変数はNULLとしているが厳密なチェックがあったほうがいいかも。
	 * *********************************** */
	public function verification($system_user_id) {
		
		return $this->query("
			SELECT "
				/* user_public */ . "
				up.user_id,
				up.system_id,
				up.create_time,
				up.update_time,
				up.active,
				up.nickname,
				up.comment,
				up.role,
				up.fashion_id,
				up.like_brand
			FROM
				" . $this->table_name . " AS up
			WHERE
				up.system_user_id=" . DbCast::string($system_user_id) . "
				AND up.active=" . DB_ACTIVE_ON
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
			'user_type' => DB_USER_TYPE_PUBLIC,
			'user_id' => DbCast::id($user_id),
			'login_time' => DbCast::datetime(DbDateTime::get_cur_datetime())
			)
		);
	}

	/*	 * **********************************
	 * NAME  : get_user_id_by_system_id
	 * INPUT : $system_id / string / システムID
	 * OUTPUT: integer / ユーザID
	 *         false / 失敗の場合
	 * DESC  :
	 *  システムIDからユーザIDを取得する
	 * NOTICE:
	 * CREATE: 2015.12.05 hesaka
	 * *********************************** */
	public function get_user_id_by_system_id($system_id) {

		//引数が空ならエラー
		if (StaticFunction::is_empty($system_id) || !InputVali::is_system_id($system_id)) {
			return false;
		}

		$data = $this->query("
			SELECT user_id
			FROM " . $this->table_name . "
			WHERE 
				system_id=" . DbCast::string($system_id) . "
				AND (active=" . DB_ACTIVE_ON . " OR active=" . DB_ACTIVE_OFF . ")
			ORDER BY create_time DESC
			LIMIT 0, 1"
		);
		//エラー・空の場合
		if ($this->db_select_check_error($data) || $this->db_select_check_empty($data)) {
			return false;
		}

		return $data[0]['user_id'];
	}

	/*	 * **********************************
	 * NAME  : get_user_detail_by_user_id
	 * INPUT : role / integer / ROLEの定義値(DB_ROLE_...)
	 *         extend_id / string / サプライヤのextend_id
	 * OUTPUT: array / データ
	 * DESC  :
	 *  指定roleのextend_idからuser_publicの情報を取得する
	 * NOTICE:
	 * CREATE: 2016.10.19 aoyama
	 * *********************************** */
	public function get_user_detail_by_user_id($user_id) {

		//パラメータチェック
		if (StaticFunction::is_empty($user_id)) {
			return false;
		}

		return $this->query("
			SELECT 
				up.user_id,
				up.system_id,
				up.system_user_id, 
				up.active,
				up.nickname,
				up.comment,
				up.role,
				up.fashion_id,
				up.like_brand,
				up.update_time
			FROM
				" . $this->table_name . " AS up
			WHERE
				up.user_id=" . DbCast::integer($user_id) . "
				AND up.active=" . DB_ACTIVE_ON
		);
	}	
	
	/*	 * **********************************
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
			SELECT mail_address, first_name, middle_name, last_name
			FROM " . $this->table_name . "
			WHERE 
				mail_address=" . DbCast::string($mail_address) . "
				AND active=" . DB_ACTIVE_ON . "
			ORDER BY create_time DESC
			LIMIT 0, 1"
		);
	}

	/*	 * **********************************
	 * NAME  : regist
	 * INPUT : param_list / array / 登録したいカラム名配列
	 * OUTPUT: db_shell_insert()のレスポンス(成功時：user_id, 失敗時:false)
	 * DESC  :
	 *  INSERT
	 * NOTICE:
	 * CREATE: 2016.10.15 aoyama
	 * *********************************** */
	public function regist($param_list) {
		LOGS_DBG_LV1('*** QUERY [INSERT] START ***');
		return $this->db_shell_insert($this->table_name, $param_list);
	}

	/*	 * **********************************
	 * NAME  : regist_sns
	 * INPUT : param_list / array / 更新したいカラム名配列
	 * OUTPUT: db_shecll_insert()のレスポンス(成功時：user_id, 失敗時:false)
	 * DESC  :
	 * 			SNS登録用のINSERTクエリー実行
	 *  INSERT
	 * NOTICE:
	 * CREATE: 2016.9.30 aoyama
	 * *********************************** */
	public function regist_sns($param_list) {
		LOGS_DBG_LV1('*** QUERY [INSERT] START regist_sns ***');
		
		//現在日時を取得
		$cur_time = DbDateTime::get_cur_datetime();
		/* 新規ハッシュ */
		$gu_sid = StaticFunction::create_id();
		
		/* public_user登録処理 */
		$guest_id = $this->db_shell_insert($this->table_name, $param_list);
		
		if ($guest_id) {
			$this->db_shell_insert(CONF::read('DB_TABLE_ROLE_USER_EXTEND_LIST.DB_ROLE_GUEST'),
				array(
					"system_id" => DbCast::system_id($gu_sid),
					'public_user_id' => DbCast::float($guest_id),
					'create_time' => DbCast::datetime($cur_time),
					'active' => DB_ACTIVE_ON
				)
			);
		}
		return $guest_id;
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

	/*	 * **********************************
	 * NAME  : get_admin_list
	 * INPUT : NONE
	 * OUTPUT: array / リスト
	 * DESC  :
	 *  管理画面、会員管理一覧を表示するために
	 *  user_memberを検索する
	 *  検索条件はセッションの保持しているデータを使用する。
	 *  その際、ブラックリストに該当する会員がどうかも判定。
	 * NOTICE:
	 *  sGroup->search_parameterを参照すること。
	 *  sGroupには、ページングのセッションが格納されていたので、
	 *  一括で消去できないため、別でセッションを保持する。
	 * CREATE: 2015.11.15 sonoda
	 * UPDATE: 2016.01.13 hesaka 検索条件作成をprivate functionに纏めた
	 * *********************************** */
	public function get_admin_list($role = DB_ROLE_GUEST) {

		//入力された検索条件を作成
		$this->set_search_where_parameters();

		/*
		 * 複数のクエリ実行するのでトランザクション
		 */
		$this->TRANSACTION_START();

		//ブラックリスト取得
		$black = $this->query("
			SELECT
				operation,
				is_active_1, key_1, value_1,
				is_active_2, key_2, value_2,
				is_active_3, key_3, value_3
			FROM black
			WHERE active=" . DB_ACTIVE_ON);
		//エラーの場合
		if ($this->db_select_check_error($black)) {
			$this->TRANSACTION_ROLLBACK();
			return false;
		}

		$black_list = array();
		//空でなければ検索条件作成
		if (!$this->db_select_check_empty($black)) {
			foreach ($black as $record) {
				$tmp = array();
				for ($i = 1; $i <= 3; $i++) {
					if ($record['is_active_' . $i]) {
						$tmp[] = $record['key_' . $i] . " LIKE " . DbCast::string("%" . $record['value_' . $i] . "%");
					}
				}
				if (!StaticFunction::is_empty($tmp)) {
					$black_list[] = '(' . implode(' ' . $record['operation'] /* ここはDbCast::string()してはいけない！ */ . ' ', $tmp) . ')';
				}
			}
		}

		//ユーザ検索
		$data = $this->query("
			SELECT
				um.user_id, um.system_id, um.first_name, um.last_name, " .
			((!StaticFunction::is_empty($black_list)) ? (" umb.is_black,") : ('')) .
			"um.phone, um.mail_address,
				um.active, um.create_time,
				CASE um.active
					WHEN " . DB_ACTIVE_ON . " THEN '有効'
					WHEN " . DB_ACTIVE_TEMPORARY . " THEN '仮登録'
					ELSE '無効'
				END AS active_text
			FROM " . $this->table_name . " um
				" . ((!StaticFunction::is_empty($black_list)) ?
				("LEFT JOIN (
					SELECT user_id, 1 AS is_black
					FROM " . $this->table_name . "
					WHERE
						" . (implode(" OR ", $black_list)) . "
				) umb ON um.user_id=umb.user_id") : ("")) . "
			WHERE
				(um.active=" . DB_ACTIVE_ON . " OR um.active=" . DB_ACTIVE_OFF . " OR um.active=" . DB_ACTIVE_TEMPORARY . ")
				" . $this->search_condition . "
				AND role=" . $role . "
			ORDER BY um.create_time DESC, um.user_id DESC
			" . PAGING::get_limit());
		if ($this->db_select_check_error($data)) {
			$this->TRANSACTION_ROLLBACK();
			return false;
		}

		$this->TRANSACTION_COMMIT();

		return $data;
	}

	/*	 * **********************************
	 * NAME  : get_admin_list_num
	 * INPUT : NONE
	 * OUTPUT: integer / レコード数
	 * DESC  :
	 *  ユーザ数を取得する
	 *  検索条件はセッションから取得する。
	 * NOTICE:
	 *  sGroup->search_parameterを参照すること。
	 *  sGroupには、ページングのセッションが格納されていたので、
	 *  一括で消去できないため、別でセッションを保持する。
	 * CREATE: 2015.11.15 sonoda
	 * UPDATE: 2016.01.13 hesaka 検索条件作成をprivate functionに纏めた
	 * *********************************** */
	public function get_admin_list_num($role = DB_ROLE_GUEST) {

		//入力された検索条件を作成
		$this->set_search_where_parameters();

		$data = $this->query("
			SELECT
				COUNT(um.user_id) AS num
			FROM " . $this->table_name . " um
			WHERE
				(um.active=" . DB_ACTIVE_ON . " OR um.active=" . DB_ACTIVE_OFF . " OR um.active=" . DB_ACTIVE_TEMPORARY . ")
				AND role=" . $role . "
				" . $this->search_condition
		);
		if ($this->db_select_check_error($data)) {
			return false;
		}

		//空の場合は0をセット
		if ($this->db_select_check_empty($data)) {
			$num = 0;
		} else {
			$num = $data[0]['num'];
		}

		return $num;
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
	 * NAME  : get_data_for_csv
	 * INPUT : NONE
	 * OUTPUT: NONE
	 * DESC  :
	 * セッションの情報を条件にした検索。
	 * CSV出力に使用するため、LIMITは設定しないこと。
	 * NOTICE:
	 * CREATE: 2015.11.18 sonoda
	 * *********************************** */
	public function get_data_for_csv() {

		//入力された検索条件を作成
		$this->set_search_where_parameters();

		//データ取得
		$data = $this->query("
			SELECT
				um.user_id, um.name, um.mail_address, um.sex, um.birth_date,
				um.zip_code, um.prefecture, um.municipality, um.house_number, um.building,
				um.phone, um.question_id, um.interim_regist_accept_time, um.interim_regist_token,
				um.create_time, um.modify_time, um.delete_time, um.memo, um.answer,
				CASE um.active
					WHEN " . DB_ACTIVE_ON . " THEN '有効'
					WHEN " . DB_ACTIVE_TEMPORARY . " THEN '仮登録'
					ELSE '無効'
				END AS active_text
			FROM " . $this->table_name . " um
			WHERE
				(um.active=" . DB_ACTIVE_ON . " OR um.active=" . DB_ACTIVE_OFF . " OR um.active=" . DB_ACTIVE_TEMPORARY . ")
				" . $this->search_condition . "
			ORDER BY um.create_time DESC, um.user_id DESC");

		return $data;
	}

	/*	 * **********************************
	 * NAME  : check_login_id
	 * INPUT : NONE
	 * OUTPUT: NONE
	 * DESC  :
	 * セッションの情報を条件にした検索。
	 * CSV出力に使用するため、LIMITは設定しないこと。
	 * NOTICE:
	 * CREATE: 2015.11.18 sonoda
	 * *********************************** */
	public function check_login_id($login_id) {

		$data = $this->query('
			SELECT count(um.user_id) AS login_num
			FROM ' . $this->table_name . ' um
			WHERE um.login_id = ' . DbCast::string($login_id) . '
		');

		if ($data[0]['login_num'] > 0) {
			return false;
		} else {
			return true;
		}
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

	/*	 * **********************************
	 * NAME  : get_user_detail_by_regist_token
	 * INPUT : $token / string / ハッシュキー
	 * OUTPUT: array / データ
	 * DESC  :
	 *  仮登録用のハッシュキーを元に「user_public」の
	 *  詳細情報を取得する
	 * NOTICE:
	 * CREATE: 2015.11.29 aoyama
	 * UPDATE: 2016.03.24 hesaka 仮登録時、パスワード平文をchar_1に入れておく方式に変更するので、
	 *                           system_id, char_1の取得が必要になった
	 * UPDATE: 2016.10.3 aoyama
	 * 		カラム名が変更(last_nameなど)になったのでクエリーを調整。
	 * 		
	 * *********************************** */
	public function get_user_detail_by_regist_token($token) {

		if (StaticFunction::is_empty($token)) {
			return false;
		}

		return $this->query("
			SELECT 
				user_id, system_id, last_name, first_name, mail_address, char_1,
				interim_regist_accept_time
			FROM " . $this->table_name . "
			WHERE
				interim_regist_token = " . DbCast::string($token) . "
				AND (active=" . DB_ACTIVE_ON . " OR active=" . DB_ACTIVE_TEMPORARY . ")
		");
	}

	/*	 * **********************************
	 * NAME  : update_user_regist
	 * INPUT : user_id / float / ユーザID
	 *         sid / string / システムID
	 *         password / string / 仮登録時に入力されたパスワード(平文)
	 * OUTPUT: boolean
	 * DESC  :
	 *  [dev-aler] point付与機能はべた書きしているのでモデル化すること！
	 * 	仮登録用のハッシュキーを元に「user_public」を更新
	 *
	 * NOTICE:
	 * CREATE: 2015.11.28 aoyama
	 * UPDATE: 2015.12.07 hesaka 引数をuser_idへ、ポイントをモジュール呼び出しへ
	 * UPDATE: 2016.01.14 hesaka 仮登録受付日時は消さずに置いておくよう変更
	 *                           create_timeを「本登録日時」扱いとして、現在時刻で更新するよう修正
	 * UPDATE: 2016.03.24 hesaka 01.14の修正の影響で、ユーザ登録後ログインできなくなる問題が発生
	 *                           ※create_timeを更新したため
	 *                           なので、仮登録時にカラム「char_1」にパスワード平文を入れておき
	 *                           正式化時のcreate_time更新後にパスワードハッシュを生成するよう変更
	 * UPDATE: 2016.10.3
	 *		ゲストユーザー拡張テーブル「user_public_extend_guest」にINSERT処理
	 * *********************************** */
	public function update_user_regist($user_id, $sid, $password) {

		LOGS_DBG_LV1('*** QUERY [USER REGIST NORMAL] START ***');

		//引数が空ならエラー
		if (StaticFunction::is_empty($user_id) || StaticFunction::is_empty($sid) || StaticFunction::is_empty($password)) {
			return false;
		}


		//現在日時を取得
		$cur_time = DbDateTime::get_cur_datetime();
		//パスワードハッシュ生成
		$pwd_hash = Encrypt::password_encrypt($password, $sid, $cur_time);
		/* 新規ハッシュ */
		$gu_sid = StaticFunction::create_id();
		
		/*
		 * ゲストユーザー拡張テーブル「user_public_extend_guest」にINSERT処理
		 * CREATE: 2016.10.4 aoyama
		 */
		$this->db_shell_insert(CONF::read('DB_TABLE_ROLE_USER_EXTEND_LIST.DB_ROLE_GUEST'),
			array(
				"system_id" => DbCast::system_id($gu_sid),
				'public_user_id' => DbCast::float($user_id),
				'create_time' => DbCast::datetime($cur_time),
				'active' => DB_ACTIVE_ON
			)
		);

		/*
		 * ユーザ情報更新
		 */
		return $this->db_shell_update(
				$this->table_name, array(
				/*
				 * 20160324
				 * ここでパスワードハッシュを設定するよう変更
				 * ※char_1はクリアする
				 */
				'password' => DbCast::string($pwd_hash),
				'char_1' => DbCast::string(NULL),
				'active' => DB_ACTIVE_ON,
				'modify_time' => DbCast::datetime($cur_time),
				//create_timeは、レコード登録日時という意味だが、CSV出力に必要なこともあって、
				//「本登録日時」となるように、ここで現在時刻を入れるようにする
				'create_time' => DbCast::datetime($cur_time),
				'interim_regist_token' => DbCast::string(NULL)/* ,
				 * 仮登録受付日時は消さずに置いておく
				  'interim_regist_accept_time' => DbCast::string(NULL) */
				), array(
				'WHERE' => array(
					'user_id' => DbCast::float($user_id)
				)
				)
		);
	}

	
	
	/*	 * **********************************
	 * NAME  : get_user_detail_by_extend_id
	 * INPUT : role / integer / ROLEの定義値(DB_ROLE_...)
	 *         extend_id / string / サプライヤのextend_id
	 * OUTPUT: array / データ
	 * DESC  :
	 *  指定roleのextend_idからuser_publicの情報を取得する
	 * NOTICE:
	 * CREATE: 2016.09.29 hesaka
	 * *********************************** */
	public function get_user_detail_by_extend_id($role, $extend_id) {

		//パラメータチェック
		if (StaticFunction::is_empties(array($role, $extend_id))) {
			return false;
		}

		//roleチェック
		if (!array_key_exists($role, CONF::read('DB_TABLE_ROLE_USER_EXTEND_LIST'))) {
			LOGS_ERR('param error! invalid role=' . $role);
			return false;
		}

		return $this->query("
			SELECT 
				up.user_id, up.system_id, up.mail_address, 
				up.first_name, up.middle_name, up.last_name,
				up.first_name_en, up.middle_name_en, up.last_name_en,
				up.sex, up.birthday, up.zip_code, up.address,
				up.country_id, up.prefecture, up.phone, 
				up.phone_country_id, up.extension_photo,
				up.memo,
				upe.extend_id, upe.system_id AS extend_system_id,
				upe.is_regist_mailmagazine
			FROM " . DbCast::table_name(CONF::read('DB_TABLE_ROLE_USER_EXTEND_LIST.'.$role)) . " upe
				INNER JOIN " . $this->table_name . " up ON up.user_id=upe.public_user_id
			WHERE
				upe.extend_id=" . DbCast::id($extend_id) . "
				AND up.active=" . DB_ACTIVE_ON . " 
				AND upe.active=" . DB_ACTIVE_ON .
				/* 念のためuser_idでGROUP BYしておく */ "
			GROUP BY up.user_id
		");
	}

	/*	 * **********************************
	 * NAME  : set_search_where_parameters
	 * INPUT : NONE
	 * OUTPUT: string / where 文字列
	 * DESC  :
	 *  一覧検索条件のwhere句を生成（共通）
	 * 条件はsessionから引き継ぐ
	 * NOTICE:
	 * CREATE: 2016.01.13 hesaka
	 * *********************************** */
	private function set_search_where_parameters() {

		$conditions = SESSION::read($this->sGroup . '.search_parameter');

		//空もしくは配列でない場合は空文字を返す
		if (StaticFunction::is_empty($conditions) || !is_array($conditions)) {
			return "";
		}

		//tmp配列初期化
		$member_condition_list = array();

		foreach ($conditions as $key => $value) {

			//valueに指定がなければ次へ
			if ($value == '') {
				continue;
			}

			switch ($key) {

				//メモ
				case 'memo':
					if ($value != '*') {
						$member_condition_list[] = "um." . $key . " LIKE " . DbCast::string("%" . $value . "%");
					} else {
						//「*」を指定された場合の判定は「あるかどうか」
						$member_condition_list[] = "um." . $key . " IS NOT NULL";
					}
					break;

				//登録日(開始)
				case 'create_time_start':
					//現状「指定しない」チェックが入っていたらstart飛んでこないけど、一応チェックかけておく
					//「指定しない」チェックが入っていない場合に1で飛んでくる
					if ($conditions['create_time_check']) {
						$member_condition_list[] = "um.create_time>=" . DbCast::datetime(DbDateTime::fairing_for_insert($value));
					}
					break;

				//登録日(終了)
				case 'create_time_end':
					//現状「指定しない」チェックが入っていたらstart飛んでこないけど、一応チェックかけておく
					//「指定しない」チェックが入っていない場合に1で飛んでくる
					if ($conditions['create_time_check']) {
						$member_condition_list[] = "um.create_time<=" . DbCast::datetime(DbDateTime::fairing_for_insert_endsec($value));
					}
					break;

				//登録日指定しない
				case 'create_time_check':
					//ここでは何もしない
					break;

				//名前
				case 'name':
					$member_condition_list[] = "(um.name LIKE " . DbCast::string("%" . $value . "%") .
						" OR um.name_kana LIKE " . DbCast::string("%" . $value . "%") . ")";
					break;

				//その他の条件
				default:
					$member_condition_list[] = "um." . $key . " LIKE " . DbCast::string("%" . $value . "%");
			}
		}

		//conditionメンバにセット
		if (!StaticFunction::is_empty($member_condition_list)) {
			$this->search_condition = " AND " . implode(" AND ", $member_condition_list);
		}
	}

}

?>
