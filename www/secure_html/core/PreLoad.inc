<?php

/*
 * 初期読み込み
 * ※順番変えるとバグる
 */

/*
 * setup load
 */
define("SETUP_LOAD_START", microtime(true));
require dirname(__FILE__) . DIRECTORY_SEPARATOR . 'PreSetUp.inc';
require dirname(__FILE__) . DIRECTORY_SEPARATOR . 'FunctionForSetUp.inc';
require dirname(__FILE__) . DIRECTORY_SEPARATOR . 'define' . DIRECTORY_SEPARATOR . 'LoadDefine.inc';
require dirname(__FILE__) . DIRECTORY_SEPARATOR . 'DirectoryList.inc';					//JSONロード形式に変更したので早い
require dirname(__FILE__) . DIRECTORY_SEPARATOR . 'AutoLoad.inc';
define("SETUP_LOAD_STOP", microtime(true));

/*
 * conf load
 */
define("CONFIG_LOAD_START", microtime(true));
require dirname(__FILE__) . DIRECTORY_SEPARATOR . 'conf' .  DIRECTORY_SEPARATOR . 'CONF.inc';
require dirname(__FILE__) . DIRECTORY_SEPARATOR . 'conf' .  DIRECTORY_SEPARATOR . 'LoadConf.inc';	//ディレクトリ舐めるのでシステム大きくなれば遅くなる可能性がある
														//JSONロード形式にすると、defineがJSONに取り込めないのと、
														//preLoadConfなどで呼び出すするクラスメソッドでCONF::read()が使えないため
														//動かない
														//ここを軽くするためには別の方法をとる必要がある
define("CONFIG_LOAD_STOP", microtime(true));

/*
 * library load
 * ※ライブラリは、処理の根幹に関わるので、
 * ロードの順番を間違えるとエラーになるものが多い
 * なので、ここで明示的にロードしておく
 */
define("LIBRARY_LOAD_START", microtime(true));
require dirname(__FILE__) . DIRECTORY_SEPARATOR . 'library' . DIRECTORY_SEPARATOR . 'log' . DIRECTORY_SEPARATOR . 'Log.inc';
require dirname(__FILE__) . DIRECTORY_SEPARATOR . 'library' . DIRECTORY_SEPARATOR . 'REQUEST' . DIRECTORY_SEPARATOR . 'REQUEST.inc';
require dirname(__FILE__) . DIRECTORY_SEPARATOR . 'library' . DIRECTORY_SEPARATOR . 'StaticFunction.inc';
define("LIBRARY_LOAD_STOP", microtime(true));


//環境判断値をログ出力
LOGS_DBG_LV1(PHP_EOL . PHP_EOL . 
	'***************************************' . PHP_EOL . 
	'*** SYSTEM START (' . ENV_DIR_NAME . ':' . (defined('FILENAME') ? FILENAME : '<none>') . ') ***' . PHP_EOL . 
	'***************************************');

//ENVのログを出力
LOGS_ENV('*** ' . ENV_DIR_NAME . ' ***');

//システム起動の所要時間をTimelineに出力
//※LOGレベルは2とする
if (CONF::read('DEBUG_BAR.IS_ACTIVE')) {

	DebugBarMaster::start_measure('measure_print', '*【SEQ_MEASURE_PRINT】', NULL, 2);

	//セットアップロード
	DebugBarMaster::start_measure('setup_load_sequence', '【FRAME_WORK_SEQ】setup_load', SETUP_LOAD_START, 2);
	DebugBarMaster::stop_measure('setup_load_sequence', SETUP_LOAD_STOP, 2);
	//configロード
	DebugBarMaster::start_measure('config_load_sequence', '【FRAME_WORK_SEQ】config_load', CONFIG_LOAD_START, 2);
	DebugBarMaster::stop_measure('config_load_sequence', CONFIG_LOAD_STOP, 2);
	//libraryロード
	DebugBarMaster::start_measure('library_load_sequence', '【FRAME_WORK_SEQ】library_load', LIBRARY_LOAD_START, 2);
	DebugBarMaster::stop_measure('library_load_sequence', LIBRARY_LOAD_STOP, 2);

	DebugBarMaster::stop_measure('measure_print', NULL, 2);
}

?>
