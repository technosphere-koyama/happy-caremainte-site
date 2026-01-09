<?php

/* * **********************************
 * NAME:DbCore
 * DESC:
 *  文字通り、DBのコアとなるところ
 *  PDOを生成し、コネクションをはる
 *  また、
 *  DBをチェックし、不足があればCREATEし、
 *  初期レコード設定の要求があれば、それをINSERTする
 * NOTICE:
 *  ※本フレームワークでは、PDOインスタンスをstaticに持ち、一度起こすと
 * 　 以降は起こさない想定である
 * 　 各モデルインスタンスを生成すると、継承するDbShellクラスでPDOを参照し
 * 　 ただ1つのPDOでDBアクセスを行う
 * 　 PDO生成時にATTR_PERSISTENTを設定すれば、複数PDOを生成しても
 * 　 コネクションは使いまわすということで同じことができるのだが、これを設定すると
 * 　 たまに「MySQL server has gone away」というwarningが出て接続できなくなる
 * 　 ため、本仕様としている
 * CREATE: 2015.08.27 hesaka
 * UPDATE: 2016.08.05 hesaka DBコネクションに失敗したらリトライするよう調整
 * *********************************** */
class DbCore {

	public static $PDO = NULL;

	/*	 * **********************************************
	 * 
	 * 初期化系処理
	 * 
	 * ********************************************** */

	/* * **********************************
	 * NAME  : get_tables
	 * INPUT : NONE
	 * OUTPUT: array / テーブル配列
	 * DESC  :
	 *  テーブル名を添え字として、中身に各テーブルDesignインスタンスを
	 *  持つ連想配列を生成する
	 * NOTICE:
	 * CREATE: 2016.10.11 aoyama
	 * *********************************** */
	public static function get_tables() {

		$instances = array();
		$tables = array();

		/*
		 * テーブルクラスを設定
		 * ※使用するテーブルのクラスはここに登録して下さい
		 */
		$instances[] = new ServiceMaster();				//サービスマスタ用テーブル
		$instances[] = new ServiceNews();				//サービスニュース用テーブル
		$instances[] = new MailMaster();				//メールマスタ用テーブル

		$instances[] = new UserPublic();				//Publicユーザー用テーブル
		$instances[] = new FashionTypeMaster();			//ファッションマスタ用テーブル

		$instances[] = new UserIos();					//iosマッチング用テーブル
		$instances[] = new UserAndroid();				//androidマッチング用テーブル
		
		$instances[] = new CommunityCategoryMaster();	//コミュニティカテゴリマスタ用テーブル
		$instances[] = new CommunityThread();			//コミュニティ用テーブル
		$instances[] = new CommunityResponse();			//コミュニティコメント用テーブル
		$instances[] = new CommunityMatch();			//コミュニティ参加マッチング用テーブル
		$instances[] = new CommunityThreadLike();		//コミュニティスレッドいいね用テーブル
		$instances[] = new CommunityResponseLike();		//コミュニティコメントいいね用テーブル
        $instances[] = new CommunityAuthor();			//コミュニティ管理者登録テーブル

		$instances[] = new Message();					//メッセージ用テーブル
		
		$instances[] = new FriendMatch();				//フレンドマッチング用テーブル
		
		$instances[] = new Review();					//レビュー用テーブル
		$instances[] = new ReviewResponse();			//レビューコメント用テーブル
		$instances[] = new ReviewLike();				//レビューいいね用テーブル
		
		$instances[] = new Timeline();					//タイムライン用テーブル
		$instances[] = new TimelineLike();				//タイムラインいいね用テーブル
		$instances[] = new TimelineResponse();			//タイムライン返信用テーブル
		$instances[] = new TimelineFile();			//タイムラインファイル用テーブル

		$instances[] = new CareResponse();				//公開ケアメンテに対する投稿用テーブル
		$instances[] = new CareResponseLike();			//ケアメンテのコメントのいいねを保存するテーブル
		$instances[] = new CareNewsLog();				//ケアメンテの新着を保存するテーブル
		
		$instances[] = new DebugBarData();				//DebugBarで生成したデバッグデータ用テーブル
		$instances[] = new LogLogin();					//ログイン履歴ログテーブル

		/*
		 * テーブル配列を作成
		 */
		foreach ($instances as $instance) {
			$tables[$instance->get_table_name()] = $instance;
		}

		return $tables;
	}

	/* * **********************************
	 * NAME  : db_initialize
	 * INPUT : NONE
	 * OUTPUT: NONE
	 * DESC  :
	 *  ・DBコネクト
	 *  ・テーブルが無ければ作る(DB.IS_CHECK_TABLESがtrueなら)
	 * NOTICE:
	 * CREATE: 2015.08.27 hesaka
	 * *********************************** */
	public static function db_initialize() {

		/*
		 * DBコネクト(PDO生成)
		 */
		DbCore::db_connect();

		/*
		 * 各テーブルをチェックし、無ければ作る
		 */
		if (CONF::read('DB.IS_CHECK_TABLES')) DbCore::check_and_create_tables();
	}

	/* * **********************************
	 * NAME  : db_connect
	 * INPUT : NONE
	 * OUTPUT: NONE
	 * DESC  :
	 *  PDOを生成し、DBの接続を確立する
	 * NOTICE:
	 *  接続が確立できたら、生成したPDOインスタンスはstaticメンバにセットする
	 *  以後DBへのアクションは、そのPDOインスタンスを用いて実行すること！
	 *  都度DBコネクトしないように、一度だけPDOを生成し、staticに扱えるよう考慮した
	 *  ※スクリプトが終了してもデータベースへの接続を維持し、次回に再利用するという
	 *    オプションがあるのだが、これを利用すると「MySQL server has gone away」と
	 *    怒られるので使うのをやめた
	 * CREATE: 2015.08.27 hesaka
	 * UPDATE: 2016.08.05 hesaka DBコネクションに失敗したらリトライするよう調整
	 * *********************************** */
	public static function db_connect() {

		if (CONF::read('DEBUG_BAR.IS_ACTIVE')) DebugBarMaster::start_measure('db_connect', '【DB_CONNECT】');

		/*
		 * 接続初期化
		 */
		$dsn = CONF::read("DB.DBMS") . ':' .
				'dbname=' . CONF::read("DB.NAME") . ';' .
				'host=' . CONF::read("DB.HOST") . ';' .
				'port=' . CONF::read("DB.PORT");

		/*
		 * attributeを設定
		 * ※詳細は以下を参照
		 * http://php.net/manual/ja/pdo.setattribute.php
		 * ※ここのサイトが丁寧に説明してくれてる
		 * http://qiita.com/mpyw/items/b00b72c5c95aac573b71#2-12
		 */
		$options = array(
			//例外を投げるようにする
			PDO::ATTR_ERRMODE => PDO::ERRMODE_EXCEPTION,
			//結果の配列は、連想配列で取得できるモードにする
			PDO::ATTR_DEFAULT_FETCH_MODE => PDO::FETCH_ASSOC,
			//[MySQL専用]バッファクエリは全ての情報をSQLサーバーから全て取得してきておく
			//非バッファクエリはフェッチの度にSQLサーバーへ取りに行く
			//取得した量がメモリに収まりきらない程ならきついが、でなければ負荷軽減となる
			PDO::MYSQL_ATTR_USE_BUFFERED_QUERY => true,
			//DBから取得した値が空文字の場合はNULLに変換されるようにする
			PDO::ATTR_ORACLE_NULLS => PDO::NULL_EMPTY_STRING
			//スクリプトが終了してもデータベースへの接続を維持し、次回に再利用する
			//※これ有効にすると、まぁまぁの頻度で下記warningが出る
			//　「MySQL server has gone away」
			//　なのでこれはつかわないようにする
			//PDO::ATTR_PERSISTENT => true
		);

		/*
		 * phpのバージョンが5.3.6以下の場合、dsnでのcharsetができないため、
		 * 仕方なく「SET NAMES utf8」を行う
		 * ※参考サイト
		 * http://qiita.com/hiro_y/items/6fabdef669e35e92bdc4
		 */
		if (!defined('PHP_VERSION_ID')) {
			$version = explode('.', PHP_VERSION);
			define('PHP_VERSION_ID', ($version[0] * 10000 + $version[1] * 100 + $version[2]));
		}
		if (PHP_VERSION_ID <= 50306) {
			array_merge(
					$options, array(PDO::MYSQL_ATTR_INIT_COMMAND => 'SET NAMES utf8') //MySQL専用
			);
			LOGS_NOTICE('php lower version than 5.3.6 cur_ver=' . PHP_VERSION_ID);
		} else {
			$dsn .= ';charset=' . CONF::read("DB.CHAR_SET");
		}

		/*
		 * PDO生成(DB接続)
		 * ※20160126
		 * 　環境によって、PDOのエクセプションで「MySQL server has gone away」のwarningが出ることがある
		 * 　調べたところ、max_allowed_packetが小さいとPDOがコネクションを切るらしく、その後改めてクエリ
		 * 　叩くとその際に「どっか行っちゃった」となるらしい
		 * 　max_allowed_packetを大きくしたら発生しなくなった
		 * 　max_allowed_packet以外でも問題があると接続断する可能性があるので、気に留めておくこと
		 * 
		 * 20160805
		 * 今後、DBサーバを別にするシーンなどあった場合、接続に失敗することがある
		 * その場合、指定回数(DB_CONNECTION_RETRY_TIMES)リトライするよう調整する
		 */
		$is_connect = false;
		$times = 0;
		$exception = NULL;
		do {
			$times++;
			try {
				//DebugBarが有効の場合、一度DebugBarに通す
				if (CONF::read('DEBUG_BAR.IS_ACTIVE')) {
					DbCore::$PDO = 
						DebugBarMaster::set_PDO(
							new PDO(
								$dsn, 
								CONF::read("DB.USER_ID"), 
								CONF::read("DB.USER_PW"), 
								$options
							)
						);
				} else {
					DbCore::$PDO = new PDO(
						$dsn, 
						CONF::read("DB.USER_ID"), 
						CONF::read("DB.USER_PW"), 
						$options
					);
				}
				$is_connect = true;
			//失敗
			} catch (PDOException $e) {
				$exception = $e;
				LOGS_ERR("DB CONNECTION ERROR! try " . $times . " time, message=" . $e->getMessage());
				//念のため指定秒(DB_CONNECTION_RETRY_SLEEP_TIME)スリープさせる
				sleep(DB_CONNECTION_RETRY_SLEEP_TIME);
			}
		} while ($times < DB_CONNECTION_RETRY_TIMES && !$is_connect);

		/*
		 * 20160805
		 * リトライ何回やっても無理な場合は終了
		 */
		if (!$is_connect) {
			LOGS_ERR("DB CONNECTION FAILED... message=" . $exception->getMessage());
			die('[DB] ' . $exception->getMessage());
		}

		LOGS_DBG_LV1('*** PDO START UP! ***');

		if (CONF::read('DEBUG_BAR.IS_ACTIVE')) DebugBarMaster::stop_measure('db_connect');
	}

	/* * **********************************
	 * NAME  : check_and_create_tables
	 * INPUT : NONE
	 * OUTPUT: NONE
	 * DESC  :
	 *  各テーブルをチェックし、無ければ作る
	 * NOTICE:
	 * CREATE: 2015.08.27 hesaka
	 * *********************************** */
	public static function check_and_create_tables() {

		if (CONF::read('DEBUG_BAR.IS_ACTIVE')) DebugBarMaster::start_measure('check_and_create_tables', '*【CHECK_AND_CREATE_TABLES】');

		/*
		 * テーブルリストを取得
		 */
		$tables = DbCore::get_tables();

		/*
		 * DBから取得したテーブルリストをチェックし、
		 * 作られている場合は配列から抜く
		 */
		try {
			$query = "SHOW TABLES FROM " . CONF::read("DB.NAME") . ";";
			if (CONF::read('DEBUG_BAR.IS_ACTIVE')) DebugBarMaster::start_measure('DB_show_tables', $query);
			$stmt = DbCore::$PDO->query($query);
			if (CONF::read('DEBUG_BAR.IS_ACTIVE')) DebugBarMaster::stop_measure('DB_show_tables');
			while ($row = $stmt->fetch()) {
				if (!empty($tables[$row['Tables_in_' . CONF::read("DB.NAME")]])) {
					unset($tables[$row['Tables_in_' . CONF::read("DB.NAME")]]);
				}
			}
			//PDOStatementを開放
			$stmt->closeCursor();
		} catch (PDOException $e) {
			LOGS_ERR($e->getMessage());
			return;
		}

		/*
		 * 配列に残っていたら、作られていないということなのでcreateする
		 */
		if (!empty($tables)) {

			LOGS_NOTICE($tables);

			foreach ($tables as $instance) {
				if (!DbCore::create_table(
					$instance->get_table_name(), 
					$instance->get_design(),
					$instance->get_pre_set_records(),
					$instance->get_option(),
					$instance->get_table_comment(),
					$instance->get_strage_engine())
				) {
					//失敗した場合ALERTログのみ吐いておく
					LOGS_ALERT('create table error -> ' . $instance->get_table_name());
				}
				/*
				 * CSVをロードしてインポートする必要があれば実行
				 */
				$instance->pre_import();
			}

		}

		if (CONF::read('DEBUG_BAR.IS_ACTIVE')) DebugBarMaster::stop_measure('check_and_create_tables');
	}

	/* * **********************************
	 * NAME  : check_and_create_tables
	 * INPUT : table_name / string / テーブル名
	 *         columns / string / 作成するカラム情報
	 *         pre_set_records / string / 初期INSERTするレコード情報
	 *         add_option / string / 追加で指定するオプション
	 *         table_comment / string / テーブル説明
	 *         engine / string / ストレージエンジン指定
	 * OUTPUT: true / 成功した場合
	 *         false / 失敗した場合
	 * DESC  :
	 *  テーブルを作成する
	 * NOTICE:
	 * CREATE: 2015.08.27 hesaka
	 * UPDATE: 2016.09.07 hesaka table_comment追加
	 * *********************************** */
	public static function create_table(
		$table_name, $columns, $pre_set_records, 
		$add_option = "", $table_comment = "", $engine = "INNODB") {

		if (empty($table_name) || empty($columns)) {
			LOGS_ERR("table_name or columns is empty!");
			return false;
		}

		$option = "";
		if (!empty($add_option)) {
			$option .= " " . $add_option;
		}
		//20160907 追加
		if (!empty($table_comment)) {
			$option .= " COMMENT = '" . $table_comment . "'";
		}

		/*
		 * テーブル作成
		 */
		try {
			$query = "
			CREATE TABLE IF NOT EXISTS " . DbCast::table_name($table_name) . " (
				" . $columns . "
			)ENGINE = " . $engine . " CHARACTER SET utf8 COLLATE utf8_general_ci" . $option . ";";
			if (CONF::read('DEBUG_BAR.IS_ACTIVE')) DebugBarMaster::start_measure('DB_create_table', $query);
			$stmt = DbCore::$PDO->query($query);
			if (CONF::read('DEBUG_BAR.IS_ACTIVE')) DebugBarMaster::stop_measure('DB_create_table');
			//PDOStatementを開放
			$stmt->closeCursor();

			/*
			 * 初期化としてINSERTしておきたいレコードがある場合はセットする
			 */
			if (!empty($pre_set_records)) {
				$query = "INSERT INTO " . DbCast::table_name($table_name) . " " . $pre_set_records;
				if (CONF::read('DEBUG_BAR.IS_ACTIVE')) DebugBarMaster::start_measure('DB_initial_insert', $query);
				$stmt = DbCore::$PDO->query($query);
				if (CONF::read('DEBUG_BAR.IS_ACTIVE')) DebugBarMaster::stop_measure('DB_initial_insert');
				//PDOStatementを開放
				$stmt->closeCursor();
			}
		} catch (PDOException $e) {
			LOGS_ERR($e->getMessage());
			//強制終了
			die($e->getMessage());
			//return false;
		}

		return true;

	}

	/* * **********************************
	 * NAME  : db_close
	 * INPUT : NONE
	 * OUTPUT: NONE
	 * DESC  :
	 *  コネクションを閉じる
	 * NOTICE:
	 * CREATE: 2015.08.27 hesaka
	 * *********************************** */
	public static function db_close() {
		DbCore::$PDO = NULL;
	}

}

?>
