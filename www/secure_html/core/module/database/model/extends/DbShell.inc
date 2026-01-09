<?php

/* * **********************************
 * NAME:DbShell
 * DESC:
 *  各MODELクラスが継承するクラス
 *  DBにクエリを飛ばす際に、ここのメソッドを利用して
 *  アクセスすることを基本とする
 * NOTICE:
 *  ※PDOの使い方によっては、当該クラスを経由せずに直接PDOインスタンスを
 *    触る可能性があるが、できるだけ当該クラスを経由すること！
 * CREATE: 2015.08.27 hesaka
 * *********************************** */
class DbShell {

	protected $PDO = NULL;
	protected $PDO_STMT = NULL;

	private $is_query_display = QUERY_DISPLAY_OFF;

	/*
	 *constructor
	 */

	public function __construct() {

		/*
		 * 初めて当該クラスのインスタンスを生成された場合は
		 * DbCoreが実行されていないので実行する
		 * ※そこでPDOが生成され、DBにコネクションされる
		 * 　DbCoreは、ただ一度だけ実行される想定
		 */
		if (!isset(DbCore::$PDO)) {
			/*
			 * DB初期化実行
			 * ・DBコネクト
			 * ・DB、テーブルが無ければ作る
			 */
			DbCore::db_initialize();
		}

		/*
		 * PDOオブジェクトをセット
		 */
		$this->PDO = DbCore::$PDO;

	}

	/* * **********************************
	 * NAME  : QUERY_DISPLAY_ONE_TIME
	 * INPUT : NONE
	 * OUTPUT: NONE
	 * DESC  :
	 *  これを叩くと、以降で1度だけ叩く以下クエリの
	 *  生成クエリ文を画面に表示する
	 * NOTICE:
	 *  デバッグ用
	 * CREATE: 2015.08.27 hesaka
	 * *********************************** */
	public function QUERY_DISPLAY_ONE_TIME() {
		$this->is_query_display = QUERY_DISPLAY_ON;
	}

	/* * **********************************
	 * NAME  : db_select_check_error
	 * INPUT : result / void / PDOでSELECTした結果
	 * OUTPUT: true / SELECTの結果としてエラーが返された場合
	 *         false / SELECTの結果としてエラーが返されていない場合
	 * DESC  :
	 *  DbShell::query()でSELECTした場合
	 *  db_shell_select()で結果取得した場合
	 *  に、結果がエラーなのか判断する処理
	 * NOTICE:
	 *  PDOのクエリによりSELECTして、fetchAllすると、
	 *  からの場合は空配列が返される
	 *  これを単純に、empty()や、「if (!$ret) {」と判断すると、
	 *  falseと同じ判定となり、PDOでエクセプションを吐くエラーに
	 *  なった場合との判断が付かない
	 *  そのため、
	 *  失敗の場合は型判定含めたfalse判定
	 *  空の場合は、is_array()の配列判定とcount()が0の0件判定
	 *  を行う必要がある
	 *  それを都度ベタ書きでやるのは面倒なので、
	 *  ここに纏めるものとする
	 * CREATE: 2015.11.16 hesaka
	 * *********************************** */
	public function db_select_check_error($result) {
		if ($result === false) {
			return true;
		}
		return false;
	}

	/* * **********************************
	 * NAME  : db_select_check_empty
	 * INPUT : result / void / PDOでSELECTした結果
	 * OUTPUT: true / SELECTの結果として0件が返された場合
	 *         false / SELECTの結果として0件が返されていない場合
	 * DESC  :
	 *  DbShell::query()でSELECTした場合
	 *  db_shell_select()で結果取得した場合
	 *  に、結果が0件なのか判断する処理
	 * NOTICE:
	 *  上にあるdb_select_check_error()のNOTICEに同じ
	 * CREATE: 2015.11.16 hesaka
	 * *********************************** */
	public function db_select_check_empty($result) {
		if (is_array($result) && count($result) <= 0) {
			return true;
		}
		return false;
	}
	
	/* * **********************************
	 * NAME  : query
	 * INPUT : query_str / string / クエリ文(全文)
	 * OUTPUT: true / クエリが成功した場合
	 *         false / 引数が空もしくはPDOクエリが失敗した場合
	 * DESC  :
	 *  PDOのクエリを実行するラッパーメソッド
	 *  これに限っては、モデルインスタンスを生成したところから
	 *  直接叩けるようにpublicにしておく
	 * NOTICE:
	 *  デバッグ用にクエリ文を出力する機能を有する
	 * 
	 * ---------------------------------------
	 *  UPDATE, INSERT, DELETE のクエリを実行した後 fetch を
	 *  かけると、「Genenral error」というエクセプションを
	 *  吐いてしまう
	 *  なので、当該メソッドではUPDATE, INSERT, DELETEを
	 *  叩かないこと！！
	 *  それらについては、新しく作成したexec()を使用すること！
	 * ---------------------------------------
	 * 
	 * CREATE: 2015.08.27 hesaka
	 * *********************************** */
	protected function query($query_str) {

		/* 処理負荷を考慮してコメントアウト
		if (empty($query_str)) {
			LOGS_ERR('query string is blank');
			return false;
		}
		 */

		/*
		 * デバッグ用にクエリ文を出力したい場合は
		 * 表示させる
		 * ※処理負荷を考慮してコメントアウト
		if ($this->is_query_display == QUERY_DISPLAY_ON) {
			$this->display($query_str);
			$this->is_query_display = QUERY_DISPLAY_OFF;
		}
		LOGS_DBG_LV3($query_str);
		 */

		/*
		 * クエリ実行
		 */
		try {
			if (CONF::read('DEBUG_BAR.IS_ACTIVE')) DebugBarMaster::start_measure('DB_query', $query_str);
			$stmt = $this->PDO->query($query_str);
			if (CONF::read('DEBUG_BAR.IS_ACTIVE')) DebugBarMaster::stop_measure('DB_query');
			$ret = $stmt->fetchAll();
			$stmt->closeCursor();	//PDOStatementを開放

		//失敗したら終了
		} catch (PDOException $e) {

			LOGS_ERR($e->getMessage());
			//UPDATE, INSERT, DELETEを当該メソッドにかけると「General error」がスローされる
			//その場合はログにクエリを吐き出すようにしておく
			if (strpos($e->getMessage(), 'General error') !== false) {
				LOGS_ERR('issue = ' . $query_str);
			}
			LOGS_ERR('issue = ' . $query_str);
			return false;

		}
		return $ret;
	}

	/* * **********************************
	 * NAME  : exec
	 * INPUT : query_str / string / クエリ文(全文)
	 * OUTPUT: true / クエリが成功した場合
	 *         false / クエリが失敗した場合
	 * DESC  :
	 *  PDOのクエリを実行するラッパーメソッド
	 * NOTICE:
	 *  同機能を持つメソッドに、query()があるが、
	 *  query()は、クエリの結果取得(フェッチ)を行うものであり、
	 *  UPDATE, INSERT, DELETEなど、結果を求めないものはquery()は
	 *  適切ではなく、フェッチ時にエクセプションをスロー(General error)
	 *  されてしまうため、それらに関してはexec()を使用すべきとして
	 *  当該メソッドを作成した次第である
	 * 
	 * ---------------------------------------
	 *  UPDATE, INSERT, DELETE などフェッチを必要としないものは
	 *  query()ではなく当該メソッドを使用すること！
	 * ---------------------------------------
	 * 
	 * CREATE: 2016.01.28 hesaka
	 * *********************************** */
	protected function exec($query_str) {

		/*
		 * クエリ実行
		 */
		try {
			if (CONF::read('DEBUG_BAR.IS_ACTIVE')) DebugBarMaster::start_measure('DB_exec', $query_str);
			$count = $this->PDO->exec($query_str);
			if (CONF::read('DEBUG_BAR.IS_ACTIVE')) DebugBarMaster::stop_measure('DB_exec');

		//失敗したら終了
		} catch (PDOException $e) {

			LOGS_ERR($e->getMessage());
			return false;
		}

		return true;
	}
	
	/* * **********************************
	 * NAME  : db_shell_select
	 * INPUT : table_name / string / テーブル名
	 *         select_list / array / 対象カラムの配列
	 *         condition / array / whereに用いる検索条件の連想配列
	 * OUTPUT: array / 取得結果リスト
	 *         false / 引数が空、配列ではないもしくはPDOクエリが失敗した場合
	 * DESC  :
	 *  PDOのクエリを用いてSELECTを行うメソッド
	 *  デバッグ用にクエリ文を出力する機能を有する
	 * NOTICE:
	 * ------------------------------------
	 *  本来は、PDOのqueryはサニタイズを行わないので使わないほうが良い
	 *  しかし、クエリによってはPDOのprepare()では実装が難しい
	 *  巨大なクエリを実装しなければならないシーンも存在する
	 *  しっかりサニタイズなど対策を行った上であれば、当該メソッドを実行することを許可する
	 * ------------------------------------
	 * CREATE: 2015.08.27 hesaka
	 * UPDATE: 2015.11.20 hesaka is_string, NULL判定をやめた(DbCastでやってくれる)
	 * *********************************** */
	protected function db_shell_select($table_name, $select_list, $conditions = NULL) {

		if (empty($table_name) || empty($select_list) || !is_array($select_list)) {
			LOGS_ERR('invalid parameter');
			return false;
		}

		//condition
		$add_conditions = "";
		if (!empty($conditions) && is_array($conditions)) {
			foreach ($conditions as $category => $condition) {
				$condition_list = array();
				foreach ($condition as $key => $value) {
					/*
					 * DbCastの中で判定して、NULLとしたいところはNULLという文字を渡してくる
					 * $condition_list[] = $key . "=" . ((is_string($value)) ? ("'" . $value . "'") : ($value));
					 */
					$condition_list[] = "`" . $key . "`=" . $value;
				}
				$add_conditions .= " " . $category . " " . implode(" AND ", $condition_list);
			}
		}
		
		/*
		 * クエリ文を作成
		 */
		$query_str = "SELECT `" . implode("`, `", $select_list) . "` FROM " . DbCast::table_name($table_name) . $add_conditions;
	
		/*
		 * デバッグ用にクエリ文を出力したい場合は
		 * 表示させる
		 */
		if ($this->is_query_display == QUERY_DISPLAY_ON) {
			$this->display($query_str);
			$this->is_query_display = QUERY_DISPLAY_OFF;
		}

		LOGS_DBG_LV3($query_str);
		
		/*
		 * SELECT実行
		 */
		try {

			if (CONF::read('DEBUG_BAR.IS_ACTIVE')) DebugBarMaster::start_measure('DB_select', $query_str);
			$stmt = $this->PDO->query($query_str);
			if (CONF::read('DEBUG_BAR.IS_ACTIVE')) DebugBarMaster::stop_measure('DB_select');
			$ret = $stmt->fetchAll();
			$stmt->closeCursor();	//PDOStatementを開放

		//失敗したら終了
		} catch (PDOException $e) {

			LOGS_ERR($e->getMessage());
			return false;

		}

		return $ret;
	}

	/* * **********************************
	 * NAME  : db_shell_insert
	 * INPUT : table_name / string / テーブル名
	 *         insert_list / array / 対象カラムと値の連想配列
	 * OUTPUT: string / INSERT処理に成功した場合:生成されたインクリメンタルID(BIGINT)
	 *         false / 引数が空、配列ではないもしくはPDOクエリが失敗した場合
	 * DESC  :
	 *  PDOのクエリを用いてINSERTを行うメソッド
	 *  デバッグ用にクエリ文を出力する機能を有する
	 * NOTICE:
	 *  INSERTに成功した場合はtrueではなく、インクリメンタルIDを
	 *  返すので、失敗判定は「!」で良いが、成功判定する場合は
	 *  「!== false」で行うこと！
	 * ------------------------------------
	 *  本来は、PDOのqueryはサニタイズを行わないので使わないほうが良い
	 *  しかし、クエリによってはPDOのprepare()では実装が難しい
	 *  巨大なクエリを実装しなければならないシーンも存在する
	 *  しっかりサニタイズなど対策を行った上であれば、当該メソッドを実行することを許可する
	 * ------------------------------------
	 * CREATE: 2015.08.27 hesaka
	 * UPDATE: 2015.11.20 hesaka is_string, NULL判定をやめた(DbCastでやってくれる)
	 * UPDATE: 2016.01.28 hesaka PDOのメソッドをquery()からexec()に変更(フェッチが必要ないため)
	 * *********************************** */
	protected function db_shell_insert($table_name, $insert_list) {

		if (empty($table_name) || empty($insert_list) || !is_array($insert_list)) {
			LOGS_ERR('invalid parameter');
			return false;
		}

		/*
		 * クエリ文を作成
		 */
		$key_array = array();
		$value_array = array();
		foreach ($insert_list as $key => $value) {
			$key_array[] = "`" . $key . "`";
			/*
			 * DbCastの中で判定して、NULLとしたいところはNULLという文字を渡してくる
			 * $value_array[] = ((is_string($value)) ? ("'" . $value . "'") : ($value));
			 */
			$value_array[] = $value;
		}
		$query_str = "
			INSERT INTO " . DbCast::table_name($table_name) . " 
				(" . implode(", ", $key_array) . ") 
			VALUES 
				(" . implode(", ", $value_array) . ");";

		/*
		 * デバッグ用にクエリ文を出力したい場合は
		 * 表示させる
		 */
		if ($this->is_query_display == QUERY_DISPLAY_ON) {
			$this->display($query_str);
			$this->is_query_display = QUERY_DISPLAY_OFF;
		}

		LOGS_DBG_LV3($query_str);

		/*
		 * INSERT実行
		 */
		try {

			if (CONF::read('DEBUG_BAR.IS_ACTIVE')) DebugBarMaster::start_measure('DB_insert', $query_str);
			$count = $this->PDO->exec($query_str);
			if (CONF::read('DEBUG_BAR.IS_ACTIVE')) DebugBarMaster::stop_measure('DB_insert');

			//IDを取得
			$id = $this->PDO->lastInsertId();

		//失敗したら終了
		} catch (PDOException $e) {

			LOGS_ERR($e->getMessage());
			return false;
		}

		//成功した場合は生成したIDを返す
		return $id;
	}

	/* * **********************************
	 * NAME  : db_shell_insert_values
	 * INPUT : table_name / string / テーブル名
	 *         key_list / array / 対象カラム名の配列
	 *         value_list / array / 値の配列
	 * OUTPUT: true / INSERT処理に成功した場合
	 *         false / 失敗した場合
	 * DESC  :
	 *  PDOのクエリを用いてINSERTを行うメソッド
	 *  ※VALUESとして複数を一度に入れる
	 *  デバッグ用にクエリ文を出力する機能を有する
	 *  valueを複数指定することが可能。
	 *  当関数では、INSERTするカラムを指定しないため、
	 *  呼び出し側でTABLEに合わせた配列を用意すること。
	 * NOTICE:
	 * ------------------------------------
	 *  本来は、PDOのqueryはサニタイズを行わないので使わないほうが良い
	 *  しかし、クエリによってはPDOのprepare()では実装が難しい
	 *  巨大なクエリを実装しなければならないシーンも存在する
	 *  しっかりサニタイズなど対策を行った上であれば、当該メソッドを実行することを許可する
	 * ------------------------------------
	 * CREATE: 2015.11.16 hesaka
	 * UPDATE: 2015.11.20 hesaka is_string, NULL判定をやめた(DbCastでやってくれる)
	 * UPDATE: 2016.01.28 hesaka PDOのメソッドをquery()からexec()に変更(フェッチが必要ないため)
	 * *********************************** */
	protected function db_shell_insert_values($table_name, $key_list, $value_list) {

		if (empty($table_name) 
			|| empty($key_list) || !is_array($key_list)
			|| empty($value_list) || !is_array($value_list)
		) {
			LOGS_ERR('invalid parameter');
			return false;
		}

		/*
		 * クエリ文を作成
		 */
		$value_array = array();
		foreach ($value_list as $value_in_list) {
			$tmp_array = array();
			foreach ($value_in_list as $value) {
				/*
				 * DbCastの中で判定して、NULLとしたいところはNULLという文字を渡してくる
				if ($value === NULL) {
					$value = "NULL";
				} else if (is_string($value)) {
					$value = "'" . $value . "'";
				}
				*/
				$tmp_array[] = $value;
			}
			$value_array[] = "(" . implode(", ", $tmp_array) . ")";
		}

		$query_str = "
			INSERT INTO " . DbCast::table_name($table_name) . "
			(`" . implode("`, `", $key_list) . "`)
			VALUES 
			". implode(",", $value_array) .";";

		/*
		 * デバッグ用にクエリ文を出力したい場合は
		 * 表示させる
		 */
		if ($this->is_query_display == QUERY_DISPLAY_ON) {
			$this->display($query_str);
			$this->is_query_display = QUERY_DISPLAY_OFF;
		}

		LOGS_DBG_LV3($query_str);

		/*
		 * INSERT実行
		 */
		try {

			if (CONF::read('DEBUG_BAR.IS_ACTIVE')) DebugBarMaster::start_measure('DB_insert', $query_str);
			$count = $this->PDO->exec($query_str);
			if (CONF::read('DEBUG_BAR.IS_ACTIVE')) DebugBarMaster::stop_measure('DB_insert');

		//失敗したら終了
		} catch (PDOException $e) {

			LOGS_ERR($e->getMessage());
			return false;
		}

		return true;
	}

	/* * **********************************
	 * NAME  : db_shell_update
	 * INPUT : table_name / string / テーブル名
	 *         insert_list / array / 対象カラムと値の連想配列
	 *         condition / array / whereに用いる検索条件の連想配列
	 * OUTPUT: true / INSERT処理に成功した場合
	 *         false / 引数が空、配列ではないもしくはPDOクエリが失敗した場合
	 * DESC  :
	 *  PDOのクエリを用いてUPDATEを行うメソッド
	 *  デバッグ用にクエリ文を出力する機能を有する
	 * NOTICE:
	 * ------------------------------------
	 *  本来は、PDOのqueryはサニタイズを行わないので使わないほうが良い
	 *  しかし、クエリによってはPDOのprepare()では実装が難しい
	 *  巨大なクエリを実装しなければならないシーンも存在する
	 *  しっかりサニタイズなど対策を行った上であれば、当該メソッドを実行することを許可する
	 * ------------------------------------
	 * CREATE: 2015.08.27 hesaka
	 * UPDATE: 2015.11.20 hesaka is_string, NULL判定をやめた(DbCastでやってくれる)
	 * UPDATE: 2016.01.28 hesaka PDOのメソッドをquery()からexec()に変更(フェッチが必要ないため)
	 * *********************************** */
	protected function db_shell_update($table_name, $update_list, $conditions = NULL) {

		if (empty($table_name) || empty($update_list) || !is_array($update_list)) {
			LOGS_ERR('invalid parameter');
			return false;
		}

		//condition
		$add_conditions = "";
		if (!empty($conditions) && is_array($conditions)) {
			foreach ($conditions as $category => $condition) {
				$condition_list = array();
				foreach ($condition as $key => $value) {
				/*
				 * DbCastの中で判定して、NULLとしたいところはNULLという文字を渡してくる
					if ($value === NULL) {
						$set = "NULL";
					} else if (is_string($value)) {
						$set = "'" . $value . "'";
					}
				 */
					$condition_list[] = "`" . $key . "`=" . $value;
				}
				$add_conditions .= " " . $category . " " . implode(" AND ", $condition_list);
			}
		}
		
		/*
		 * クエリ文を作成
		 */
		$tmp_array = array();
		foreach ($update_list as $key => $value) {
			/*
			 * DbCastの中で判定して、NULLとしたいところはNULLという文字を渡してくる
			if ($value === NULL) {
				$set = "NULL";
			} else if (is_string($value)) {
				$set = "'" . $value . "'";
			}
			 */
			$tmp_array[] = "`" . $key . "`=" . $value;
		}
		$query_str = 
			"UPDATE " . DbCast::table_name($table_name) . 
			" SET " . implode(", ", $tmp_array) . 
			$add_conditions;
	
		/*
		 * デバッグ用にクエリ文を出力したい場合は
		 * 表示させる
		 */
		if ($this->is_query_display == QUERY_DISPLAY_ON) {
			$this->display($query_str);
			$this->is_query_display = QUERY_DISPLAY_OFF;
		}

		LOGS_DBG_LV3($query_str);

		/*
		 * UPDATE実行
		 */
		try {

			if (CONF::read('DEBUG_BAR.IS_ACTIVE')) DebugBarMaster::start_measure('DB_update', $query_str);
			$count = $this->PDO->exec($query_str);
			if (CONF::read('DEBUG_BAR.IS_ACTIVE')) DebugBarMaster::stop_measure('DB_update');

		//失敗したら終了
		} catch (PDOException $e) {

			LOGS_ERR($e->getMessage());
			return false;
		}

		/*
		 * 結果が1件も無い場合は失敗と判断する
		 * ※20160122
		 * 　PDOのupdateでは、更新内容が、前と変わっていない場合は更新を行わず、
		 * 　rowCount()が0となる。なので、0だからといって失敗としてしまっては問題となるのでログを吐くだけにした
		 * UPDATE: 2016.10.26 aoyama
		 *		更新件数は必要なのでaffected lowsはリターンさせる
		 */
		//if (!$count) {
		//	LOGS_DBG_LV3('UPDATE RECORD = 0!!!');
		//	return $count;
		//}
		//return true;
		
		return $count;
	}
	
	/* * **********************************
	 * NAME  : db_shell_delete
	 * INPUT : table_name / string / テーブル名
	 *         condition / array / whereに用いる検索条件の連想配列
	 * OUTPUT: true / INSERT処理に成功した場合
	 *         false / 引数が空、配列ではないもしくはPDOクエリが失敗した場合
	 * DESC  :
	 *  PDOのクエリを用いてDELETEを行うメソッド
	 *  デバッグ用にクエリ文を出力する機能を有する
	 * NOTICE:
	 * ------------------------------------
	 *  本来は、PDOのqueryはサニタイズを行わないので使わないほうが良い
	 *  しかし、クエリによってはPDOのprepare()では実装が難しい
	 *  巨大なクエリを実装しなければならないシーンも存在する
	 *  しっかりサニタイズなど対策を行った上であれば、当該メソッドを実行することを許可する
	 * ------------------------------------
	 * CREATE: 2015.11.15 hesaka
	 * UPDATE: 2015.11.20 hesaka is_string, NULL判定をやめた(DbCastでやってくれる)
	 * UPDATE: 2016.01.28 hesaka PDOのメソッドをquery()からexec()に変更(フェッチが必要ないため)
	 * *********************************** */
	protected function db_shell_delete($table_name, $conditions = NULL) {

		if (empty($table_name)) {
			LOGS_ERR('invalid parameter');
			return false;
		}

		//condition
		$add_conditions = "";
		if (!empty($conditions) && is_array($conditions)) {
			foreach ($conditions as $category => $condition) {
				$condition_list = array();
				foreach ($condition as $key => $value) {
					/*
					 * DbCastの中で判定して、NULLとしたいところはNULLという文字を渡してくる
					if ($value === NULL) {
						$set = "NULL";
					} else if (is_string($value)) {
						$set = "'" . $value . "'";
					}
					 */
					$condition_list[] = "`" . $key . "`=" . $value;
				}
				$add_conditions .= " " . $category . " " . implode(" AND ", $condition_list);
			}
		}
		
		/*
		 * クエリ文を作成
		 */
		$query_str = 
			"DELETE FROM " . DbCast::table_name($table_name) . $add_conditions;
	
		/*
		 * デバッグ用にクエリ文を出力したい場合は
		 * 表示させる
		 */
		if ($this->is_query_display == QUERY_DISPLAY_ON) {
			$this->display($query_str);
			$this->is_query_display = QUERY_DISPLAY_OFF;
		}

		LOGS_DBG_LV3($query_str);

		/*
		 * UPDATE実行
		 */
		try {

			if (CONF::read('DEBUG_BAR.IS_ACTIVE')) DebugBarMaster::start_measure('DB_update', $query_str);
			$count = $this->PDO->exec($query_str);
			if (CONF::read('DEBUG_BAR.IS_ACTIVE')) DebugBarMaster::stop_measure('DB_update');

		//失敗したら終了
		} catch (PDOException $e) {

			LOGS_ERR($e->getMessage());
			return false;
		}

		return true;
	}
	
	/*
	 * prepare
	 *
	 * PDOのクエリを実行するラッパーメソッド
	 * デバッグ用にクエリ文を出力する機能を有する
	public function prepare() {

		$stmt = $this->PDO->prepare("SELECT * FROM gmo_order_id_counter WHERE head_card = :head_card ");
		$stmt2 = $this->PDO->prepare("SELECT * FROM salesforce_auth_setting WHERE auth_id = :auth_id ");

		$stmt->bindValue(":head_card", "CD", PDO::PARAM_STR);
		$stmt2->bindValue(":auth_id", "f13ff924aeb2e4dfcff7e9fe143c5163", PDO::PARAM_STR);

		$stmt2->execute();
		$stmt->execute();

		var_dump($stmt->fetchAll());
		var_dump($stmt2->fetchAll());

	}
	 */
	
	/*	 * **********************************************
	 * 
	 * トランザクション系処理
	 * 
	 * ********************************************** */

	/* * **********************************
	 * NAME  : TRANSACTION_START
	 * INPUT : NONE
	 * OUTPUT: NONE
	 * DESC  :
	 *  トランザクション 開始
	 * NOTICE:
	 *  MySQLでは、単クエリ毎に自動トランザクションを行ってくれるが、
	 *  複数クエリでの一括トランザクションの場合は意図してかける必要がある
	 *  また、基本的には実装時の意識としてしっかりとトランザクションを考慮して
	 *  かける必要があると思うので、必ずかけること！
	 * CREATE: 2015.08.27 hesaka
	 * *********************************** */
	protected function TRANSACTION_START() {
		LOGS_DBG_LV1("TRANSACTION START!!!");
		$this->PDO->beginTransaction();
	}

	/* * **********************************
	 * NAME  : TRANSACTION_ROLLBACK
	 * INPUT : NONE
	 * OUTPUT: NONE
	 * DESC  :
	 *  トランザクション ロールバック
	 * NOTICE:
	 *  MySQLでは、単クエリ毎に自動トランザクションを行ってくれるが、
	 *  複数クエリでの一括トランザクションの場合は意図してかける必要がある
	 *  また、基本的には実装時の意識としてしっかりとトランザクションを考慮して
	 *  かける必要があると思うので、必ずかけること！
	 * CREATE: 2015.08.27 hesaka
	 * *********************************** */
	protected function TRANSACTION_ROLLBACK() {
		LOGS_DBG_LV1("TRANSACTION ROLLBACK!!!");
		LOGS_ERR("TRANSACTION ROLLBACK!!!");
		$this->PDO->rollBack();
	}

	/* * **********************************
	 * NAME  : TRANSACTION_COMMIT
	 * INPUT : NONE
	 * OUTPUT: NONE
	 * DESC  :
	 *  トランザクション コミット
	 * NOTICE:
	 *  MySQLでは、単クエリ毎に自動トランザクションを行ってくれるが、
	 *  複数クエリでの一括トランザクションの場合は意図してかける必要がある
	 *  また、基本的には実装時の意識としてしっかりとトランザクションを考慮して
	 *  かける必要があると思うので、必ずかけること！
	 * CREATE: 2015.08.27 hesaka
	 * *********************************** */
	protected function TRANSACTION_COMMIT() {
		LOGS_DBG_LV1("TRANSACTION COMMIT!!!");
		$this->PDO->commit();
	}

	/* * **********************************
	 * NAME  : TRANSACTION_START
	 * INPUT : NONE
	 * OUTPUT: NONE
	 * DESC  :
	 *  トランザクション 開始
	 * NOTICE:
	 *  MySQLでは、単クエリ毎に自動トランザクションを行ってくれるが、
	 *  複数クエリでの一括トランザクションの場合は意図してかける必要がある
	 *  また、基本的には実装時の意識としてしっかりとトランザクションを考慮して
	 *  かける必要があると思うので、必ずかけること！
	 * CREATE: 2015.08.27 hesaka
	 * *********************************** */
	public static function TRANSACTION_START_static() {
		LOGS_DBG_LV1("static TRANSACTION START!!!");
		DbCore::$PDO->beginTransaction();
	}

	/* * **********************************
	 * NAME  : TRANSACTION_ROLLBACK
	 * INPUT : NONE
	 * OUTPUT: NONE
	 * DESC  :
	 *  トランザクション ロールバック
	 * NOTICE:
	 *  MySQLでは、単クエリ毎に自動トランザクションを行ってくれるが、
	 *  複数クエリでの一括トランザクションの場合は意図してかける必要がある
	 *  また、基本的には実装時の意識としてしっかりとトランザクションを考慮して
	 *  かける必要があると思うので、必ずかけること！
	 * CREATE: 2015.08.27 hesaka
	 * *********************************** */
	public static function TRANSACTION_ROLLBACK_static() {
		LOGS_DBG_LV1("TRANSACTION ROLLBACK!!!");
		LOGS_ERR("TRANSACTION ROLLBACK!!!");
		DbCore::$PDO->rollBack();
	}

	/* * **********************************
	 * NAME  : TRANSACTION_COMMIT
	 * INPUT : NONE
	 * OUTPUT: NONE
	 * DESC  :
	 *  トランザクション コミット
	 * NOTICE:
	 *  MySQLでは、単クエリ毎に自動トランザクションを行ってくれるが、
	 *  複数クエリでの一括トランザクションの場合は意図してかける必要がある
	 *  また、基本的には実装時の意識としてしっかりとトランザクションを考慮して
	 *  かける必要があると思うので、必ずかけること！
	 * CREATE: 2015.08.27 hesaka
	 * *********************************** */
	public static function TRANSACTION_COMMIT_static() {
		LOGS_DBG_LV1("TRANSACTION COMMIT!!!");
		DbCore::$PDO->commit();
	}

	/* * **********************************
	 * NAME  : WRITE_LOCK_TABLES
	 * INPUT : table_list / array / ロック対象テーブル達
	 * OUTPUT: NONE
	 * DESC  :
	 *  指定テーブルにWRITEロックをかける
	 * NOTICE:
	 *  ロックが必要な処理が完了したら必ずUNLOCK_TABLESを実行すること！
	 * 
	 * -------------------------------------------------------------
	 *  ※当該セッションにて、一度ロックしたら、開放するまでの間に別テーブル参照(SELECTでも)するとエラーになる
	 *  　なので、ロック開放まで触る全てのテーブルをロックしないといけない
	 *  ※ちなみに、ロックを分けて行うと、1回めにロックしたほうが開放される 
	 * -------------------------------------------------------------
	 * 
	 * -------------------------------------------------------------
	 *  テーブルロックは、詳しくわからないところがあり、デッドロックになる危険性もある
	 *  現状、確認した内容としては、
	 *  ・ロックはちゃんと掛かっている(ロック中にスリープし、その間に別セッションでアクセスしたら待たされた)
	 *  ・待たされていた方は、開放された後ちゃんと動き出した
	 *  ・UNLOCKせずに関係ないテーブルを参照しようとしたらエクセプションを吐いた
	 *  ・UNLOCKせずにPHPが終了すると、UNLOCKされ、別セッションがアクセスしたらロックかかってなかった
	 *  　※PDOが、UNLOCKせずに抜けようとしたらUNLOCKしてくれるのではないかと推測する
	 *  となっている
	 *  まずは使ってみてデッドロックされるかなど、様子を見ることにする
	 * -------------------------------------------------------------
	 * 
	 * CREATE: 2015.11.22 hesaka
	 * *********************************** */
	public function WRITE_LOCK_TABLES($table_list = NULL) {

		//引数が不正(空、配列でない)な場合はここで終了する
		if (StaticFunction::is_empty($table_list) || !is_array($table_list)) {
			LOGS_ERR("LOCK TABLES parameter error!");
			print 'ERRORが発生しました。';
			exit();
		}

		LOGS_DBG_LV1("LOCK TABLES!!! " . implode(', ', $table_list));

		$tables = array();
		foreach ($table_list as $table_name) {
			$tables[] = DbCast::table_name($table_name) . " WRITE";
		}

		try {
			$stmt = $this->PDO->query("LOCK TABLE " . implode(", ", $tables) . ";");
			$stmt->closeCursor();	//PDOStatementを開放
		//失敗したら終了
		} catch (PDOException $e) {
			LOGS_ERR($e->getMessage());
		}
	}

	/* * **********************************
	 * NAME  : UNLOCK_TABLES
	 * INPUT : NONE
	 * OUTPUT: NONE
	 * DESC  :
	 *  テーブルロックを解除する
	 * NOTICE:
	 * CREATE: 2015.11.22 hesaka
	 * *********************************** */
	public function UNLOCK_TABLES() {
		LOGS_DBG_LV1("UNLOCK TABLES!!!");

		try {
			$stmt = $this->PDO->query("UNLOCK TABLES;");
			$stmt->closeCursor();	//PDOStatementを開放
		//失敗したら終了
		} catch (PDOException $e) {
			LOGS_ERR($e->getMessage());
		}
	}

	/* * **********************************
	 * NAME  : display
	 * INPUT : display / string / 表示文字列
	 * OUTPUT: NONE
	 * DESC  :
	 *  背景色を付けて、画面にテキストを表示する
	 * NOTICE:
	 *  デバッグ用
	 * CREATE: 2015.08.27 hesaka
	 * *********************************** */
	private function display($display) {
		print '
			<p style="background-color:#bef;padding:5px;margin:3px 0;">
				' . nl2br($display) . '
			</p>';
	}

}

?>
