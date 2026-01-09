<?php

/* * **********************************
 * NAME:DebugBarMaster
 * DESC:
 *  DebugBarを使用する自作コントローラ
 * NOTICE:
 *  デバッグバーだけで
 *  0.6sかかってる。。。
 * 
 *  うちわけとしては
 *  defines = 0.1s
 *  rendering = 0.2s
 *  その他の処理 = 0.3s
 * 
 *  symfony使ってるし、自作したほうが良いかも
 * 
 * CREATE: 2015.08.27 hesaka
 * *********************************** */
class DebugBarMaster {

	private static $debug_bar;
	private static $debug_bar_renderer;

	/* * **********************************
	 * NAME  : exec
	 * INPUT : NONE
	 * OUTPUT: NONE
	 * DESC  :
	 *  デバッグバーの用意するクラスインスタンスを生成
	 * NOTICE:
	 * CREATE: 2015.08.27 hesaka
	 * *********************************** */
	public static function exec() {
		//スタンダードな機能をプリセットされたクラス生成
		self::$debug_bar = new DebugBar\StandardDebugBar();
		//プロジェクトのHTMLソース側にdebugbar用のcss,jsを配置するのは無粋
		//なので、xampp環境のドキュメントルートに配置する
		//サーバでは動かないので気をつけること！
		self::$debug_bar_renderer = self::$debug_bar->getJavascriptRenderer(
				CONF::read('DEBUG_BAR.BASE_URL'),
				CONF::read('DEBUG_BAR.BASE_PATH')
		);
	}

	/* * **********************************
	 * NAME  : html_source_render
	 * INPUT : view_data / array / configに表示するデータ 連想多次元配列
	 * OUTPUT: string / HTMLソース
	 * DESC  :
	 *  debug bar のHTMLソース部分を出力するメソッド
	 * NOTICE:
	 *  下記１行をbody直下に放り込めば良い
	 * 
	 *  ※DebugBarディレクトリに「_」を入れて向こうにしても、
	 *  　CONFのロードでNULLが返ってきて実行されないのでエラーにはならない
	 * 
	 *  <?php ((CONF::read('DEBUG_BAR.IS_ACTIVE')) ? (DebugBarMaster::html_source_render($view_data)) : ('')); ?>
	 * CREATE: 2015.08.27 hesaka
	 * *********************************** */
	public static function html_source_render($view_data = NULL) {

		//viewのstop_measure()はここに集約する
		DebugBarMaster::stop_measure('view');

		DebugBarMaster::start_measure('debug_bar_output', 'debug_bar_output');

		/*
		 * defineの配列について
		 * userを「ユーザ定義」に変更
		 * 
		 */
		$defines = get_defined_constants(true);
		/*
		$keys=array_keys($defines);
		$keys[array_search('user',$keys)]='ユーザ定義';
		$defines = array_combine($keys, $defines);
		 */

		//configとdefinesをセット
		$config = array_merge(
			array('*** CONFIG START ***' => ''), 
			CONF::read(''), 
			array('*** CONFIG END ***' => ''),
			array('*** DEFINES START ***' => ''), 
			//$defines, ユーザ定義以外は、重たいので普段は外しておく
			//array('DEFINE' => $defines), 
			array('DEFINE' => $defines['user']), 
			array('*** DEFINES END ***' => '')
		);

		//view_dataの指定があればセット
		if (!empty($view_data)) {
			$config = array_merge($view_data, $config);
		}

		self::$debug_bar->addCollector(new DebugBar\DataCollector\ConfigCollector($config));
		
		DebugBarMaster::stop_measure('debug_bar_output');

		return self::$debug_bar_renderer->renderHead() . self::$debug_bar_renderer->render();
	}

	/* * **********************************
	 * NAME  : set_PDO
	 * INPUT : pdo / instance / 当該システムで利用するPDOインスタンス
	 * OUTPUT: instance / PDOインスタンス
	 * DESC  :
	 *  PDOで叩くクエリの情報が出力されるようにする登録処理
	 * NOTICE:
	 * CREATE: 2015.08.27 hesaka
	 * *********************************** */
	public static function set_PDO($pdo) {
		if (empty($pdo)) {
			return NULL;
		}
		$ret_pdo = new DebugBar\DataCollector\PDO\TraceablePDO($pdo);
		self::$debug_bar->addCollector(new DebugBar\DataCollector\PDO\PDOCollector($ret_pdo));
		//debugbarを通したPDOインスタンスを返す
		return $ret_pdo;
	}

	/* * **********************************
	 * NAME  : info
	 * INPUT : message / string / メッセージ部に出力する内容
	 * OUTPUT: NONE
	 * DESC  :
	 *  メッセージ部に出力する内容をmessages配列のinfoに登録する処理
	 * NOTICE:
	 *  Debug Bar を無効にした時のことを考えて、使い方は以下のようにすること
	 *  if (CONF::read('DEBUG_BAR.IS_ACTIVE')) DebugBarMaster::info('message');
	 * CREATE: 2015.08.27 hesaka
	 * *********************************** */
	public static function info($message) {
		self::$debug_bar['messages']->info($message);
	}
	
	/* * **********************************
	 * NAME  : notice
	 * INPUT : message / string / メッセージ部に出力する内容
	 * OUTPUT: NONE
	 * DESC  :
	 *  メッセージ部に出力する内容をmessages配列のnoticeに登録する処理
	 * NOTICE:
	 *  Debug Bar を無効にした時のことを考えて、使い方は以下のようにすること
	 *  if (CONF::read('DEBUG_BAR.IS_ACTIVE')) DebugBarMaster::notice('message');
	 * CREATE: 2015.08.27 hesaka
	 * *********************************** */
	public static function notice($message) {
		self::$debug_bar['messages']->notice($message);
	}
	
	/* * **********************************
	 * NAME  : warning
	 * INPUT : message / string / メッセージ部に出力する内容
	 * OUTPUT: NONE
	 * DESC  :
	 *  メッセージ部に出力する内容をmessages配列のwarningに登録する処理
	 * NOTICE:
	 *  Debug Bar を無効にした時のことを考えて、使い方は以下のようにすること
	 *  if (CONF::read('DEBUG_BAR.IS_ACTIVE')) DebugBarMaster::warning('message');
	 * CREATE: 2015.08.27 hesaka
	 * *********************************** */
	public static function warning($message) {
		self::$debug_bar['messages']->warning($message);
	}

	/* * **********************************
	 * NAME  : alert
	 * INPUT : message / string / メッセージ部に出力する内容
	 * OUTPUT: NONE
	 * DESC  :
	 *  メッセージ部に出力する内容をmessages配列のalertに登録する処理
	 * NOTICE:
	 *  Debug Bar を無効にした時のことを考えて、使い方は以下のようにすること
	 *  if (CONF::read('DEBUG_BAR.IS_ACTIVE')) DebugBarMaster::alert('message');
	 * CREATE: 2015.08.27 hesaka
	 * *********************************** */
	public static function alert($message) {
		self::$debug_bar['messages']->alert($message);
	}
	
	/* * **********************************
	 * NAME  : error
	 * INPUT : message / string / メッセージ部に出力する内容
	 * OUTPUT: NONE
	 * DESC  :
	 *  メッセージ部に出力する内容をmessages配列のerrorに登録する処理
	 * NOTICE:
	 *  Debug Bar を無効にした時のことを考えて、使い方は以下のようにすること
	 *  if (CONF::read('DEBUG_BAR.IS_ACTIVE')) DebugBarMaster::error('message');
	 * CREATE: 2015.08.27 hesaka
	 * *********************************** */
	public static function error($message) {
		self::$debug_bar['messages']->error($message);
	}
	
	/* * **********************************
	 * NAME  : start_measure
	 * INPUT : name / string / measureの登録名(処理に対してユニークなIDとして使用されるので、止めるためにstop_measure()に引き継ぐ必要がある)
	 *         display_title / DebugBar表示のときに使用される表示名
	 *         ※以下2つは特殊なタイミングで指定するもの
	 *           通常は使用しないこと！
	 *         microtime / string / 現在時刻ではなく、開始時刻を指定する際に設定する時刻
	 *         log_level / integer / デバッグログに表示する際のレベル指定
	 * OUTPUT: NONE
	 * DESC  :
	 *  timeline部に表示する内容のスタートタイムを登録する処理
	 * NOTICE:
	 *  Debug Bar を無効にした時のことを考えて、使い方は以下のようにすること
	 *  if (CONF::read('DEBUG_BAR.IS_ACTIVE')) DebugBarMaster::start_measure('name', 'measure');
	 *  ※引数の「$microtime」と「$log_level」は、システム起動シーケンス時間を図るために開始時間を指定できるようにしたもの
	 *  　通常は使用しないこと！
	 * CREATE: 2015.08.27 hesaka
	 * *********************************** */
	public static function start_measure($name = 'measure', $display_title = 'measure', $microtime = NULL, $log_level = 1) {
		if ($log_level == 2) {
			LOGS_DBG_LV2('[ START MEASURE(' . $name . ') ]');
		} else {
			LOGS_DBG_LV1('[ START MEASURE(' . $name . ') ]');
		}
		self::$debug_bar['time']->startMeasure($name, $display_title, $microtime);
	}

	/* * **********************************
	 * NAME  : stop_measure
	 * INPUT : name / string / measureの登録名(処理に対してユニークなIDとして使用されるもの。start_measure()で指定したnameを指定することで止めることが出来る)
	 *         ※以下2つは特殊なタイミングで指定するもの
	 *           通常は使用しないこと！
	 *         microtime / string / 現在時刻ではなく、終了時刻を指定する際に設定する時刻
	 *         log_level / integer / デバッグログに表示する際のレベル指定
	 * OUTPUT: NONE
	 * DESC  :
	 *  stop_measure()で開始したストップウォッチを止める処理
	 * NOTICE:
	 *  Debug Bar を無効にした時のことを考えて、使い方は以下のようにすること
	 *  if (CONF::read('DEBUG_BAR.IS_ACTIVE')) DebugBarMaster::stop_measure('measure');
	 *  ※引数の「$microtime」と「$log_level」は、システム起動シーケンス時間を図るために終了時間を指定できるようにしたもの
	 *  　通常は使用しないこと！
	 * CREATE: 2015.08.27 hesaka
	 * *********************************** */
	public static function stop_measure($name = 'measure', $microtime = NULL, $log_level = 1) {
		self::$debug_bar['time']->stopMeasure($name, $microtime);
		if ($log_level == 2) {
			LOGS_DBG_LV2('[ STOP MEASURE(' . $name . ') ]');
		} else {
			LOGS_DBG_LV1('[ STOP MEASURE(' . $name . ') ]');
		}
	}
	
	/* * **********************************
	 * NAME  : set_file_storage
	 * INPUT : view_data / array / configに表示するデータ 連想多次元配列
	 * OUTPUT: NONE
	 * DESC  :
	 *  結果をJSONファイルとして吐き出す処理
	 * NOTICE:
	 *  まだテスト段階
	 *  test.jsonとして１世代だけ、redirect()する際に上書きするようにしている
	 * CREATE: 2015.08.27 hesaka
	 * *********************************** */
	public static function set_file_storage($view_data) {
		$storage = new DebugBar\Storage\FileStorage(CONF::read('DEBUG_BAR.STORAGE_PATH'));
		//いつも通りに画面に表示するのはこっち
		$storage->save('test', self::html_source_render($view_data));
		//コアデータだけ保存しておいて、表示はカスタマイズする場合はこっち
		//$storage->save('test', self::$debug_bar->getData());
		self::$debug_bar->setStorage($storage);
	}
	
	/* * **********************************
	 * NAME  : get_file_storage
	 * INPUT : NONE
	 * OUTPUT: array / set_file_storageで保存した情報をdecodeした配列
	 * DESC  :
	 *  set_file_storageで保存したjsonをdecodeして取得して表示する
	 * NOTICE:
	 * CREATE: 2015.08.27 hesaka
	 * *********************************** */
	public static function get_file_storage() {
		$storage = new DebugBar\Storage\FileStorage(CONF::read('DEBUG_BAR.STORAGE_PATH'));
		return $storage->get('test');
	}
	
	/* * **********************************
	 * NAME  : set_db_storage
	 * INPUT : view_data / array / configに表示するデータ 連想多次元配列
	 * OUTPUT: NONE
	 * DESC  :
	 *  録り溜めたデバッグ情報をDBに保存する
	 * NOTICE:
	 *  ※現状、コントローラのデストラクタでのみ実行する
	 * CREATE: 2015.08.27 hesaka
	 * *********************************** */
	public static function set_db_storage($view_data) {
		//処理の中でDBを使用していない場合、PDOが起きていないので、
		//その場合はここで起こす
		if (!isset(DbCore::$PDO)) {
			DbCore::db_initialize();
		}
		//ConfigCollectorをaddしてなければここでadd
		if (!self::$debug_bar->hasCollector('config')) {
			$config = CONF::read('');
			if (!empty($view_data)) {
				$config = array_merge($view_data, $config);
			}
			self::$debug_bar->addCollector(new DebugBar\DataCollector\ConfigCollector($config));
		}
		$storage = new DebugBar\Storage\PdoStorage(DbCore::$PDO, CONF::read('DEBUG_BAR.TABLE_NAME'));
		$storage->save(StaticFunction::create_id(), self::$debug_bar->getData());
	}
	
}

?>
