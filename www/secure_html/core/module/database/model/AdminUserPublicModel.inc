<?php

/* * **********************************
 * NAME: AdminUserPublicModel
 * DESC:
 *  サービサ側の会員情報用のモデルクラス
 * NOTICE:
 * CREATE: 2015.11.15 sonoda
 * UPDATE: 2016.11.14 aoyama
 *		※削除
 * *********************************** */
class Admin__DELETE__UserPublicModel extends DbShell {

	private $sGroup_guest;
	private $sGroup_host;
	private $sGroup_supplier;
	private $table_name = "user_public";
	private $table_name_extend_guest = "user_public_extend_guest";
	private $table_name_extend_host = "user_public_extend_host";
	private $table_name_extend_supplier = "user_public_extend_supplier";
	private $search_condition;

	public function __construct() {
		parent::__construct();
		$this->sGroup_guest = 'admin_guest';
		$this->sGroup_host = 'admin_host';
		$this->sGroup_supplier = 'admin_supplier';

		//検索conditionパラメータ初期化
		$this->search_condition = '';
	}

	/*	 * **********************************
	 * NAME  : user_insert
	 * INPUT : param_list / array / 更新したいカラム名配列
	 * OUTPUT: true / 成功, false / 失敗
	 * DESC  :
	 * ユーザ登録処理
	 * 引数で渡されたroleを基に、ユーザ情報を追加する。
	 *
	 * まず、user_publicに情報を登録し、成功すれば
	 * user_public_extend_xxxxに情報を登録する。
	 *
	 * 登録処理が複数回にわたるため、transactionをかけておくこと。
	 *
	 * パスワードのpassword_encryptに使用するため、
	 * user_publicのcreate_timeはコントローラ側で設定している。
	 * NOTICE:
	 * CREATE: 2016.09.26 sonoda
	 * *********************************** */
	public function user_insert($param_list, $role = NULL) {
		LOGS_DBG_LV1('*** QUERY [INSERT] START ***');

		//extendテーブルを設定する。
		switch ($role) {
			case DB_ROLE_GUEST:
				$extend_table = $this->table_name_extend_guest;
				break;

			case DB_ROLE_HOST:
				$extend_table = $this->table_name_extend_host;
				break;

			case DB_ROLE_SUPPLIER:
				$extend_table = $this->table_name_extend_supplier;
				break;

			default :
				LOGS_ERR('role set empty!!');
				return false;
		}

		//後述の処理でsystem_idを使用するので、param_listに設定されているか
		//事前に確認しておく。
		if (!array_key_exists('system_id', $param_list)) {
			LOGS_ERR('system id empty!!');
			return false;
		}

		$sid = $param_list['system_id'];

		$this->TRANSACTION_START();

		//まず、ユーザテーブルにデータ追加。
		if (!$this->db_shell_insert($this->table_name, $param_list)) {
			LOGS_ERR('user_public insert error!!');
			$this->TRANSACTION_ROLLBACK();
			return false;
		}

		//成功した場合、user_idを取得する。
		//コントローラ側でsidをキャストしているので、ここではキャスト不要。
		$tmp_user = $this->db_shell_select($this->table_name, array('user_id'), array('WHERE' => array(('system_id') => $sid)));

		if ($this->db_select_check_empty($tmp_user) ||
			$this->db_select_check_error($tmp_user)) {
			LOGS_ERR('user info get error!!');
			$this->TRANSACTION_ROLLBACK();
			return false;
		}

		//ここまでくれば、ユーザ情報は正常にテーブルに追加できたので、
		//extendテーブルに情報を登録する。
		if (!$this->db_shell_insert($extend_table, array(
				'system_id' => DbCast::system_id(StaticFunction::create_id()),
				'public_user_id' => DbCast::float($tmp_user[0]['user_id']),
				'active' => DB_ACTIVE_ON,
				'create_time' => DbDateTime::get_cur_datetime(),
			))) {
			LOGS_ERR('user_public_extend insert error!!');
			$this->TRANSACTION_ROLLBACK();
			return false;
		}

		//すべてのデータが登録できたので、正常終了
		$this->TRANSACTION_COMMIT();
		return true;
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
	 * CREATE: 2016.09.22 sonoda
	 * *********************************** */
	public function update($sid, $param_list) {

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
	 * NAME  : get_list
	 * INPUT : NONE
	 * OUTPUT: array / リスト
	 * DESC  :
	 *  管理画面、会員管理一覧を表示するために
	 *  user_memberを検索する
	 *  検索条件はセッションの保持しているデータを使用する。
	 *  ブラックリスト機能はphase1では搭載していないので、コメントアウト。
	 * NOTICE:
	 *  sGroup->search_parameterを参照すること。
	 *  sGroupには、ページングのセッションが格納されていたので、
	 *  一括で消去できないため、別でセッションを保持する。
	 * CREATE: 2016.09.26 sonoda
	 * *********************************** */
	public function get_list_supplier() {

		//入力された検索条件を作成
		$this->set_search_where_parameters(DB_ROLE_SUPPLIER);

		$data = $this->query("
			SELECT
				up.system_id,
				up.user_id,
				up.first_name,
				up.last_name,
				up.country_id,
				up.phone,
				up.mail_address,
				up.active,
				up.create_time
			FROM
				" . $this->table_name_extend_supplier . " AS upe
			LEFT JOIN
				user_public AS up ON upe.public_user_id = up.user_id
			LEFT JOIN
				shop AS sp ON sp.extend_id = upe.extend_id
			LEFT JOIN
				shop_extend_ja AS sej ON sp.shop_id = sej.shop_id
			WHERE
				(upe.active=" . DB_ACTIVE_ON . " OR upe.active=" . DB_ACTIVE_OFF . " OR upe.active=" . DB_ACTIVE_TEMPORARY . ") AND
				(up.active=" . DB_ACTIVE_ON . " OR up.active=" . DB_ACTIVE_OFF . " OR up.active=" . DB_ACTIVE_TEMPORARY . ")
				" . $this->search_condition . "
			ORDER BY up.create_time DESC, up.user_id DESC
			" . PAGING::get_limit());

		return $data;
	}

	/*	 * **********************************
	 * NAME  : get_admin_list_num
	 * INPUT : NONE
	 * OUTPUT: integer / レコード数
	 * DESC  :
	 *  ユーザ数を取得する
	 *  検索条件はセッションから取得する。
	 *  引数で取得したROLEの値をもとに、検索対象のDBを設定する。
	 *  このROLEはset_search_where_parametersにも渡し、
	 *  検索条件が格納されているセッションがどれかを判定するのに
	 *  使用している。
	 *
	 * 検索条件だが、user_public_xxxxとuser_publicのステータスが、
	 * 有効・無効・仮登録ユーザを対象とする。
	 * publicユーザが退会した場合は、ステータスは無効となるが、
	 * そのユーザ情報も管理者は閲覧するケースも考えられるので。
	 *
	 * ユーザを削除した場合、user_publicとuser_public_xxxxの両方が
	 * 削除となることを想定しているが、万が一user_publicが削除で
	 * user_public_xxxxが有効なんて場合もあるかもしれない。
	 * が、上記は無効ユーザで問題ないと考えてリスト対象外となっている。
	 *
	 * NOTICE:
	 *  sGroup->search_parameterを参照すること。
	 *  sGroupには、ページングのセッションが格納されていたので、
	 *  一括で消去できないため、別でセッションを保持する。
	 * CREATE: 2016.09.23 sonoda
	 * *********************************** */
	public function get_list_num_supplier() {

		//入力された検索条件を作成
		$this->set_search_where_parameters(DB_ROLE_SUPPLIER);

		$data = $this->query("
			SELECT
				COUNT(up.user_id) AS num
			FROM
				" . $this->table_name_extend_supplier . " AS upe
			LEFT JOIN
				user_public AS up ON upe.public_user_id = up.user_id
			LEFT JOIN
				shop AS sp ON sp.extend_id = upe.extend_id
			LEFT JOIN
				shop_extend_ja AS sej ON sp.shop_id = sej.shop_id
			WHERE
				(upe.active=" . DB_ACTIVE_ON . " OR upe.active=" . DB_ACTIVE_OFF . " OR upe.active=" . DB_ACTIVE_TEMPORARY . ") AND
				(up.active=" . DB_ACTIVE_ON . " OR up.active=" . DB_ACTIVE_OFF . " OR up.active=" . DB_ACTIVE_TEMPORARY . ")
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
	 * NAME  : get_list
	 * INPUT : NONE
	 * OUTPUT: array / リスト
	 * DESC  :
	 *  管理画面、会員管理一覧を表示するために
	 *  user_memberを検索する
	 *  検索条件はセッションの保持しているデータを使用する。
	 *  ブラックリスト機能はphase1では搭載していないので、コメントアウト。
	 * NOTICE:
	 *  sGroup->search_parameterを参照すること。
	 *  sGroupには、ページングのセッションが格納されていたので、
	 *  一括で消去できないため、別でセッションを保持する。
	 * CREATE: 2016.09.26 sonoda
	 * *********************************** */
	public function get_list_guest() {

		//入力された検索条件を作成
		$this->set_search_where_parameters(DB_ROLE_GUEST);

		$data = $this->query("
			SELECT
				up.system_id,
				up.user_id,
				up.first_name,
				up.last_name,
				up.country_id,
				up.phone,
				up.mail_address,
				up.active,
				up.create_time
			FROM
				" .  $this->table_name_extend_guest . " AS upe
			LEFT JOIN
				user_public AS up ON upe.public_user_id = up.user_id
			WHERE
				(upe.active=" . DB_ACTIVE_ON . " OR upe.active=" . DB_ACTIVE_OFF . " OR upe.active=" . DB_ACTIVE_TEMPORARY . ") AND
				(up.active=" . DB_ACTIVE_ON . " OR up.active=" . DB_ACTIVE_OFF . " OR up.active=" . DB_ACTIVE_TEMPORARY . ")
				" . $this->search_condition . "
			ORDER BY up.create_time DESC, up.user_id DESC
			" . PAGING::get_limit());

		return $data;
	}

	/*	 * **********************************
	 * NAME  : get_admin_list_num
	 * INPUT : NONE
	 * OUTPUT: integer / レコード数
	 * DESC  :
	 *  ユーザ数を取得する
	 *  検索条件はセッションから取得する。
	 *  引数で取得したROLEの値をもとに、検索対象のDBを設定する。
	 *  このROLEはset_search_where_parametersにも渡し、
	 *  検索条件が格納されているセッションがどれかを判定するのに
	 *  使用している。
	 *
	 * 検索条件だが、user_public_xxxxとuser_publicのステータスが、
	 * 有効・無効・仮登録ユーザを対象とする。
	 * publicユーザが退会した場合は、ステータスは無効となるが、
	 * そのユーザ情報も管理者は閲覧するケースも考えられるので。
	 *
	 * ユーザを削除した場合、user_publicとuser_public_xxxxの両方が
	 * 削除となることを想定しているが、万が一user_publicが削除で
	 * user_public_xxxxが有効なんて場合もあるかもしれない。
	 * が、上記は無効ユーザで問題ないと考えてリスト対象外となっている。
	 *
	 * NOTICE:
	 *  sGroup->search_parameterを参照すること。
	 *  sGroupには、ページングのセッションが格納されていたので、
	 *  一括で消去できないため、別でセッションを保持する。
	 * CREATE: 2016.09.23 sonoda
	 * *********************************** */
	public function get_list_num_guest() {

		//入力された検索条件を作成
		$this->set_search_where_parameters(DB_ROLE_GUEST);

		$data = $this->query("
			SELECT
				COUNT(up.user_id) AS num
			FROM
				" .  $this->table_name_extend_guest . " AS upe
			LEFT JOIN
				user_public AS up ON upe.public_user_id = up.user_id
			LEFT JOIN
				room AS rm ON rm.extend_id = upe.extend_id
			WHERE
				(upe.active=" . DB_ACTIVE_ON . " OR upe.active=" . DB_ACTIVE_OFF . " OR upe.active=" . DB_ACTIVE_TEMPORARY . ") AND
				(up.active=" . DB_ACTIVE_ON . " OR up.active=" . DB_ACTIVE_OFF . " OR up.active=" . DB_ACTIVE_TEMPORARY . ")
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
	 * NAME  : get_list_host
	 * INPUT : NONE
	 * OUTPUT: array / リスト
	 * DESC  :
	 *  管理画面、会員管理一覧を表示するために
	 *  user_memberを検索する
	 *  検索条件はセッションの保持しているデータを使用する。
	 *  ブラックリスト機能はphase1では搭載していないので、コメントアウト。
	 * NOTICE:
	 *  sGroup->search_parameterを参照すること。
	 *  sGroupには、ページングのセッションが格納されていたので、
	 *  一括で消去できないため、別でセッションを保持する。
	 * CREATE: 2016.09.26 sonoda
	 * *********************************** */
	public function get_list_host() {

		//入力された検索条件を作成
		$this->set_search_where_parameters(DB_ROLE_HOST);

		$data = $this->query("
			SELECT
				up.system_id,
				up.user_id,
				up.first_name,
				up.last_name,
				up.country_id,
				up.phone,
				up.mail_address,
				up.active,
				up.create_time
			FROM
				" . $this->table_name_extend_host . " AS upe
			LEFT JOIN
				user_public AS up ON upe.public_user_id = up.user_id
			LEFT JOIN
				room AS rm ON rm.extend_id = upe.extend_id
			WHERE
				(upe.active=" . DB_ACTIVE_ON . " OR upe.active=" . DB_ACTIVE_OFF . " OR upe.active=" . DB_ACTIVE_TEMPORARY . ") AND
				(up.active=" . DB_ACTIVE_ON . " OR up.active=" . DB_ACTIVE_OFF . " OR up.active=" . DB_ACTIVE_TEMPORARY . ")
				" . $this->search_condition . "
			ORDER BY up.create_time DESC, up.user_id DESC
			" . PAGING::get_limit());

		return $data;
	}

	/*	 * **********************************
	 * NAME  : get_list_num_host
	 * INPUT : NONE
	 * OUTPUT: integer / レコード数
	 * DESC  :
	 * NOTICE:
	 *  sGroup->search_parameterを参照すること。
	 *  sGroupには、ページングのセッションが格納されていたので、
	 *  一括で消去できないため、別でセッションを保持する。
	 * CREATE: 2016.09.23 sonoda
	 * *********************************** */
	public function get_list_num_host() {

		//入力された検索条件を作成
		$this->set_search_where_parameters(DB_ROLE_HOST);

		$data = $this->query("
			SELECT
				COUNT(up.user_id) AS num
			FROM
				" . $this->table_name_extend_host . " AS upe
			LEFT JOIN
				user_public AS up ON upe.public_user_id = up.user_id
			LEFT JOIN
				room AS rm ON rm.extend_id = upe.extend_id
			WHERE
				(upe.active=" . DB_ACTIVE_ON . " OR upe.active=" . DB_ACTIVE_OFF . " OR upe.active=" . DB_ACTIVE_TEMPORARY . ") AND
				(up.active=" . DB_ACTIVE_ON . " OR up.active=" . DB_ACTIVE_OFF . " OR up.active=" . DB_ACTIVE_TEMPORARY . ")
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
	 * NAME  : get_detail
	 * INPUT : system_id / string / システムID
	 * OUTPUT: array / データ
	 * DESC  :
	 *  user_memberから、指定されたシステムIDレコードの
	 *  詳細情報を取得する
	 * NOTICE:
	 * CREATE: 2015.11.15 sonoda
	 * *********************************** */
	public function get_detail($system_id) {

		if (StaticFunction::is_empty($system_id)) {
			return false;
		}

		return $this->query("
			SELECT
				up.user_id,
				up.system_id,
				up.first_name,
				up.last_name,
				up.middle_name,
				up.sex,
				up.active,
				up.create_time,
				up.birthday,
				up.zip_code,
				up.address,
				up.phone,
				up.phone_country_id,
				up.country_id,
				up.mail_address,
				up.memo,
				CASE
					WHEN pc.pa_guest_card_id IS NULL THEN '未登録'
					ELSE '登録済み'
				END AS card_text
			FROM (
				SELECT
					user_id,
					system_id,
					first_name,
					last_name,
					middle_name,
					sex,
					active,
					create_time,
					birthday,
					zip_code,
					address,
					phone,
					phone_country_id,
					country_id,
					mail_address,
					memo
				FROM " . $this->table_name . "
				WHERE
					system_id=" . DbCast::string($system_id) . "
					AND (active=" . DB_ACTIVE_ON . " OR active=" . DB_ACTIVE_OFF . " OR active=" . DB_ACTIVE_TEMPORARY . ")
			) AS up
			LEFT OUTER JOIN (
				SELECT
					extend_id,
					pa_guest_card_id
				FROM
					pa_guest_card
				WHERE
					active=" . DB_ACTIVE_ON . "
			) AS pc ON pc.extend_id=up.user_id");
	}

	/*	 * **********************************
	 * NAME  : get_detail_host
	 * INPUT : system_id / string / システムID
	 * OUTPUT: array / データ
	 * DESC  :
	 * ホスト詳細情報を取得。
	 * 振込先を追加取得
	 * NOTICE:
	 * CREATE: 2016.09.26 sonoda
	 * *********************************** */
	public function get_detail_host($system_id) {

		if (StaticFunction::is_empty($system_id)) {
			return false;
		}

		return $this->query("
			SELECT
				up.user_id,
				up.system_id,
				up.first_name,
				up.last_name,
				up.middle_name,
				up.sex,
				up.active,
				up.create_time,
				up.birthday,
				up.zip_code,
				up.address,
				up.phone,
				up.phone_country_id,
				up.country_id,
				up.mail_address,
				up.memo,
				bi.bank_master_id,
				bi.code,
				bi.bank_name,
				bi.branch_name,
				bi.branch_code,
				bi.account_number,
				bi.account_type,
				bi.account_name
			FROM (
				SELECT
					user_id,
					system_id,
					first_name,
					last_name,
					middle_name,
					sex,
					active,
					create_time,
					birthday,
					zip_code,
					address,
					phone,
					phone_country_id,
					country_id,
					mail_address,
					memo
				FROM " . $this->table_name . "
				WHERE
					system_id=" . DbCast::string($system_id) . "
					AND (active=" . DB_ACTIVE_ON . " OR active=" . DB_ACTIVE_OFF . " OR active=" . DB_ACTIVE_TEMPORARY . ")
			) AS up
			LEFT JOIN "
				. $this->table_name_extend_host . " AS ue ON ue.public_user_id=up.user_id
			LEFT OUTER JOIN (
				SELECT
					bh.bank_id,
					bh.extend_id,
					bh.bank_master_id,
					bh.branch_name,
					bh.branch_code,
					bh.account_number,
					bh.account_type,
					bh.account_name,
					bm.code,
					bm.name AS bank_name
				FROM
					bank_host AS bh
				LEFT JOIN
					bank_master AS bm ON bh.bank_master_id=bm.bank_master_id
				WHERE
					bh.active=" . DB_ACTIVE_ON . "
			) AS bi ON bi.extend_id=ue.extend_id");
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
	private function set_search_where_parameters($type) {

		switch ($type) {
			case DB_ROLE_GUEST:
				$session_name = 'admin_guest';
				break;

			case DB_ROLE_HOST:
				$session_name = 'admin_host';
				break;

			case DB_ROLE_SUPPLIER:
				$session_name = 'admin_supplier';
				break;
			default:
				LOGS_ERR('type empty!!');
				return false;
		}

		$conditions = SESSION::read($session_name . '.search_parameter');

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
						$member_condition_list[] = "up." . $key . " LIKE " . DbCast::string("%" . $value . "%");
					} else {
						//「*」を指定された場合の判定は「あるかどうか」
						$member_condition_list[] = "up." . $key . " IS NOT NULL";
					}
					break;

				//登録日(開始)
				case 'create_time_start':
					$member_condition_list[] = "up.create_time>=" . DbCast::datetime(DbDateTime::fairing_for_insert($value));
					break;

				//登録日(終了)
				case 'create_time_end':
					$member_condition_list[] = "up.create_time<=" . DbCast::datetime(DbDateTime::fairing_for_insert_endsec($value));
					break;

				//ショップ名(サプライヤ限定)
				case 'shop_name':
					$member_condition_list[] = "sej.name LIKE " . DbCast::string("%" . $value . "%");
					break;

				//ショップ住所(サプライヤ限定)
				case 'shop_address':
					$member_condition_list[] = "sej.address LIKE " . DbCast::string("%" . $value . "%");
					break;

				//ルーム名(ホスト限定)
				case 'room_name':
					$member_condition_list[] = "rm.name LIKE " . DbCast::string("%" . $value . "%");
					break;

				//ルーム住所(ホスト限定)
				case 'room_address':
					$member_condition_list[] = "rm.address LIKE " . DbCast::string("%" . $value . "%");
					break;

				case 'active':
					if($value == DB_ACTIVE_ON ||
						$value == DB_ACTIVE_OFF) {
						$member_condition_list[] = "upe.active=" . DbCast::float($value);
					}
					break;

				//名前
				case 'name':
					$member_condition_list[] = "(up.first_name LIKE " . DbCast::string("%" . $value . "%") .
						" OR up.middle_name LIKE " . DbCast::string("%" . $value . "%") .
						" OR up.last_name LIKE " . DbCast::string("%" . $value . "%") . ")";
					break;

				//その他の条件
				default:
					$member_condition_list[] = "up." . $key . " LIKE " . DbCast::string("%" . $value . "%");
			}
		}

		//conditionメンバにセット
		if (!StaticFunction::is_empty($member_condition_list)) {
			$this->search_condition = " AND " . implode(" AND ", $member_condition_list);
		}
	}

}

?>
