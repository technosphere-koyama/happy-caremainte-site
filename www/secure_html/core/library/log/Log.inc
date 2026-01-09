<?php

/* * **********************************
 * NAME  : LOGS_ERR
 * INPUT : text / string / 出力したい内容
 * OUTPUT: NONE
 * DESC  :
 *  errorログ出力
 *  LOG.IS_ERR_OPENがtrueになっていた場合に出力される
 * 
 * ------------------------------------
 *  errorログの定義
 *  エラーと判断すべきもの
 * ------------------------------------
 * 
 * NOTICE:
 *  debug_backtrace()を使用しているため、関数にまとめようとすると
 *  メソッド名などが変わってしまうため、同じ処理を複数各形となるが、
 *  纏めずにこのまま置いておくこと
 * 
 *  現在は、MODEにより「local」「papertrail」があり、それぞれ
 *  テキストファイル出力か、ペーパートレイルという
 *  サードパーティ製プラグインへの出力か指定できる
 *  後に、DBにも出力できるように変更したい
 * 
 * CREATE: 2015.08.27 hesaka
 * UPDATE: 2016.10.26 aoyama
 * 		PHP5.3系対応のため「debug_backtrace」の第二引数を削除
 * 		これによりスタックトレースの制限がなくなる。。
 * 		また、ここにセットされる「DEBUG_BACKTRACE_PROVIDE_OBJECT」は
 * 		環境依存になるため（netbeanのphpruntime？）、
 * 		あえてSystemConfig.incなどに明示的にdefineしてやる。
 * 		define ('DEBUG_BACKTRACE_PROVIDE_OBJECT', true);
 * 		これによる5.4系以降への影響は不明。
 * *********************************** */
function LOGS_ERR($text = "") {
	if (CONF::read("LOG.IS_ERR_OPEN")) {
		$out = $text;
		if (is_array($text)) {
			$out = PHP_EOL . print_r($text, true);
		}
		$trace = debug_backtrace(DEBUG_BACKTRACE_PROVIDE_OBJECT);
		$targetFile = basename($trace[0]["file"]);
		$function = ((empty($trace[1]["function"])) ? ('<none>') : ($trace[1]["function"]));
		$lineNumber = $trace[0]["line"];
		$output_text = "[" . date('Y/m/d H:i:s') . "][" . USER_IP . "][" . $targetFile . "::" . $function . "][" . $lineNumber . "]:" . $out;
		put_log('ERROR', $output_text . PHP_EOL, 3, CONF::read("LOG.ERR_FILE_PATH"));
		//画面出力
		if (CONF::read("LOG.IS_ERR_PRINT")) {
			print '
			<p style="background-color:#f43;padding:5px;margin:3px 0;">
				<span style="font-weight:bold;">[ERROR]</span> 
				' . $output_text . '
			</p>';
		}
		//debug bar に出力
		if (CONF::read('DEBUG_BAR.IS_ACTIVE'))
			DebugBarMaster::error($output_text);
	}
}

/* * **********************************
 * NAME  : LOGS_ALERT
 * INPUT : text / string / 出力したい内容
 * OUTPUT: NONE
 * DESC  :
 *  alertログ出力
 *  LOG.IS_ALERT_OPENがtrueになっていた場合に出力される
 * 
 * ------------------------------------
 *  alertログの定義
 *  「警告」として伝えておくべき内容
 *  alertログに出力された場合、
 *  担当者は必ずチェックしなければならない
 * ------------------------------------
 * 
 * NOTICE:
 *  ※LOGS_ERR()と同じ
 * CREATE: 2015.08.27 hesaka
 * *********************************** */
function LOGS_ALERT($text = "") {
	if (CONF::read("LOG.IS_ALERT_OPEN")) {
		$out = $text;
		if (is_array($text)) {
			$out = PHP_EOL . print_r($text, true);
		}
		$trace = debug_backtrace(DEBUG_BACKTRACE_PROVIDE_OBJECT);
		$targetFile = basename($trace[0]["file"]);
		$function = ((empty($trace[1]["function"])) ? ('<none>') : ($trace[1]["function"]));
		$lineNumber = $trace[0]["line"];
		$output_text = "[" . date('Y/m/d H:i:s') . "][" . USER_IP . "][" . $targetFile . "::" . $function . "][" . $lineNumber . "]:" . $out;
		put_log('ALERT', $output_text . PHP_EOL, 3, CONF::read("LOG.ALERT_FILE_PATH"));
		//画面出力
		if (CONF::read("LOG.IS_ALERT_PRINT")) {
			print '
			<p style="background-color:#f43;padding:5px;margin:3px 0;">
				<span style="font-weight:bold;">[ALERT]</span> 
				' . $output_text . '
			</p>';
		}
		//debug bar に出力
		if (CONF::read('DEBUG_BAR.IS_ACTIVE'))
			DebugBarMaster::alert($output_text);
	}
}

/* * **********************************
 * NAME  : LOGS_WARN
 * INPUT : text / string / 出力したい内容
 * OUTPUT: NONE
 * DESC  :
 *  warningログ出力
 *  LOG.IS_WARN_OPENがtrueになっていた場合に出力される
 * 
 * ------------------------------------
 *  warningログの定義
 *  alertよりは少し弱く、伝えておいたほうが良いと思われる内容
 *  warningログに出力された場合、
 *  担当者は、気になるものはチェックすること
 * ------------------------------------
 * 
 * NOTICE:
 *  ※LOGS_ERR()と同じ
 * CREATE: 2015.08.27 hesaka
 * *********************************** */
function LOGS_WARN($text = "") {
	if (CONF::read("LOG.IS_WARN_OPEN")) {
		$out = $text;
		if (is_array($text)) {
			$out = PHP_EOL . print_r($text, true);
		}
		$trace = debug_backtrace(DEBUG_BACKTRACE_PROVIDE_OBJECT);
		$targetFile = basename($trace[0]["file"]);
		$function = ((empty($trace[1]["function"])) ? ('<none>') : ($trace[1]["function"]));
		$lineNumber = $trace[0]["line"];
		$output_text = "[" . date('Y/m/d H:i:s') . "][" . USER_IP . "][" . $targetFile . "::" . $function . "][" . $lineNumber . "]:" . $out;
		put_log('WARNING', $output_text . PHP_EOL, 3, CONF::read("LOG.WARN_FILE_PATH"));
		//画面出力
		if (CONF::read("LOG.IS_WARN_PRINT")) {
			print '
			<p style="background-color:#f43;padding:5px;margin:3px 0;">
				<span style="font-weight:bold;">[WARNING]</span> 
				' . $output_text . '
			</p>';
		}
		//debug bar に出力
		if (CONF::read('DEBUG_BAR.IS_ACTIVE'))
			DebugBarMaster::warning($output_text);
	}
}

/* * **********************************
 * NAME  : LOGS_NOTICE
 * INPUT : text / string / 出力したい内容
 * OUTPUT: NONE
 * DESC  :
 *  noticeログ出力
 *  LOG.IS_NOTICE_OPENがtrueになっていた場合に出力される
 * 
 * ------------------------------------
 *  noticeログの定義
 *  warningよりも弱く、「気付き」として気になったので
 *  ロギングしておく程度の内容
 *  noticeログに出力された場合、
 *  担当者は、デバッグする際にたまにチェックする程度で良い
 * ------------------------------------
 * 
 * NOTICE:
 *  ※LOGS_ERR()と同じ
 * CREATE: 2015.08.27 hesaka
 * *********************************** */
function LOGS_NOTICE($text = "") {
	if (CONF::read("LOG.IS_NOTICE_OPEN")) {
		$out = $text;
		if (is_array($text)) {
			$out = PHP_EOL . print_r($text, true);
		}
		$trace = debug_backtrace(DEBUG_BACKTRACE_PROVIDE_OBJECT);
		$targetFile = basename($trace[0]["file"]);
		$function = ((empty($trace[1]["function"])) ? ('<none>') : ($trace[1]["function"]));
		$lineNumber = $trace[0]["line"];
		$output_text = "[" . date('Y/m/d H:i:s') . "][" . USER_IP . "][" . $targetFile . "::" . $function . "][" . $lineNumber . "]:" . $out;
		put_log('NOTICE', $output_text . PHP_EOL, 3, CONF::read("LOG.NOTICE_FILE_PATH"));
		//debug bar に出力
		if (CONF::read('DEBUG_BAR.IS_ACTIVE'))
			DebugBarMaster::notice($output_text);
	}
}

/* * **********************************
 * NAME  : LOGS_LOGIN
 * INPUT : text / string / 出力したい内容
 * OUTPUT: NONE
 * DESC  :
 *  ログイン・ログアウト関係ログ出力
 *  LOG.IS_LOGIN_OPENがtrueになっていた場合に出力される
 * 
 * ------------------------------------
 *  loginログの定義
 *  ログイン成功・失敗、ログアウトに関するログ専用のファイル
 * ------------------------------------
 * 
 * NOTICE:
 *  ※LOGS_ERR()と同じ
 * CREATE: 2015.10.02 hesaka
 * *********************************** */
function LOGS_LOGIN($text = "") {
	if (CONF::read("LOG.IS_LOGIN_OPEN")) {
		$out = $text;
		if (is_array($text)) {
			$out = PHP_EOL . print_r($text, true);
		}
		$trace = debug_backtrace(DEBUG_BACKTRACE_PROVIDE_OBJECT);
		$targetFile = basename($trace[0]["file"]);
		$function = ((empty($trace[1]["function"])) ? ('<none>') : ($trace[1]["function"]));
		$lineNumber = $trace[0]["line"];
		$output_text = "[" . date('Y/m/d H:i:s') . "][" . USER_IP . "][" . $targetFile . "::" . $function . "][" . $lineNumber . "]:" . $out;
		put_log('LOGIN', $output_text . PHP_EOL, 3, CONF::read("LOG.LOGIN_FILE_PATH"));
		//debug bar に出力
		if (CONF::read('DEBUG_BAR.IS_ACTIVE'))
			DebugBarMaster::notice($output_text);
	}
}

/* * **********************************
 * NAME  : LOGS_API
 * INPUT : text / string / 出力したい内容
 * OUTPUT: NONE
 * DESC  :
 *  ログイン・ログアウト関係ログ出力
 *  LOGS_LOGINを複製
 * CREATE: 2016.12.19 aoyama
 * *********************************** */
function LOGS_API($text = "") {
	if (CONF::read("LOG.IS_API_OPEN")) {
		$out = $text;
		if (is_array($text)) {
			$out = PHP_EOL . print_r($text, true);
		}
		$trace = debug_backtrace(DEBUG_BACKTRACE_PROVIDE_OBJECT);
		$targetFile = basename($trace[0]["file"]);
		$function = ((empty($trace[1]["function"])) ? ('<none>') : ($trace[1]["function"]));
		$lineNumber = $trace[0]["line"];
		$output_text = "[" . date('Y/m/d H:i:s') . "][" . USER_IP . "][" . $targetFile . "::" . $function . "][" . $lineNumber . "]:" . $out;
		put_log('API ', $output_text . PHP_EOL, 3, CONF::read("LOG.API_FILE_PATH"));
		//debug bar に出力
		if (CONF::read('DEBUG_BAR.IS_ACTIVE'))
			DebugBarMaster::notice($output_text);
	}
}

/* * **********************************
 * NAME  : LOGS_DBG_LV1
 * INPUT : text / string / 出力したい内容
 * OUTPUT: NONE
 * DESC  :
 *  debug ログ 出力 LV1
 *  LOG.IS_DBG_OPENがtrue かつ LOG.DBG_LVが1以上 
 *  になっていた場合に出力される
 * 
 * ------------------------------------
 *  debugログの定義
 *  開発時に処理の流れや詳細を確認するための内容
 *  
 *  LV1の定義
 *  重要度：高
 *  処理の根幹、大きな処理ブロックの開始タイミング、
 *  外部API連携時の挙動など、キーとなる情報を出力するレベル
 *  あまり細かすぎると、ログが長くなりわかりにくくなるので
 *  しっかり考えて設定すること
 *  また、本番環境で運用開始後も、通常ではLV1をONにしておいて
 *  監視することを想定する
 * ------------------------------------
 * 
 * NOTICE:
 *  ※LOGS_ERR()と同じ
 * CREATE: 2015.08.27 hesaka
 * *********************************** */
function LOGS_DBG_LV1($text = "") {
	if (CONF::read("LOG.IS_DBG_OPEN") && CONF::read("LOG.DBG_LV") >= 1) {
		$out = $text;
		if (is_array($text)) {
			$out = PHP_EOL . print_r($text, true);
		}
		$trace = debug_backtrace(DEBUG_BACKTRACE_PROVIDE_OBJECT);
		$targetFile = basename($trace[0]["file"]);
		$function = ((empty($trace[1]["function"])) ? ('<none>') : ($trace[1]["function"]));
		$lineNumber = $trace[0]["line"];
		$output_text = "[" . date('Y/m/d H:i:s') . "][" . USER_IP . "][" . $targetFile . "::" . $function . "][" . $lineNumber . "][LV1]:" . $out . PHP_EOL;
		put_log('DEBUG', $output_text, 3, CONF::read("LOG.DBG_FILE_PATH"));
		//debug bar に出力
		if (CONF::read('DEBUG_BAR.IS_ACTIVE'))
			DebugBarMaster::info($output_text);
	}
}

/* * **********************************
 * NAME  : LOGS_DBG_LV2
 * INPUT : text / string / 出力したい内容
 * OUTPUT: NONE
 * DESC  :
 *  debug ログ 出力 LV2
 *  LOG.IS_DBG_OPENがtrue かつ LOG.DBG_LVが2以上 
 *  になっていた場合に出力される
 * 
 * ------------------------------------
 *  debugログの定義
 *  LV1のヘッダに記載
 *  
 *  LV2の定義
 *  重要度：中
 *  LV1のログを主軸として、もう少し細かくロギングしたいと
 *  思う範囲の内容
 *  本番運用開始後、問題が発生し、LV1では追い切れない場合、
 *  LV2をONにして監視運用を行う
 *  あまりに多く出力すると処理負荷がかかり、ユーザに影響が出るので
 *  出力内容についてはしっかり考えること
 * ------------------------------------
 * 
 * NOTICE:
 *  ※LOGS_ERR()と同じ
 * CREATE: 2015.08.27 hesaka
 * *********************************** */
function LOGS_DBG_LV2($text = "") {
	if (CONF::read("LOG.IS_DBG_OPEN") && CONF::read("LOG.DBG_LV") >= 2) {
		$out = $text;
		if (is_array($text)) {
			$out = PHP_EOL . print_r($text, true);
		}
		$trace = debug_backtrace(DEBUG_BACKTRACE_PROVIDE_OBJECT);
		$targetFile = basename($trace[0]["file"]);
		$function = ((empty($trace[1]["function"])) ? ('<none>') : ($trace[1]["function"]));
		$lineNumber = $trace[0]["line"];
		$output_text = "[" . date('Y/m/d H:i:s') . "][" . USER_IP . "][" . $targetFile . "::" . $function . "][" . $lineNumber . "][LV2]:" . $out . PHP_EOL;
		put_log('DEBUG', $output_text, 3, CONF::read("LOG.DBG_FILE_PATH"));
		//debug bar に出力
		if (CONF::read('DEBUG_BAR.IS_ACTIVE'))
			DebugBarMaster::info($output_text);
	}
}

/* * **********************************
 * NAME  : LOGS_DBG_LV3
 * INPUT : text / string / 出力したい内容
 * OUTPUT: NONE
 * DESC  :
 *  debug ログ 出力 LV3
 *  LOG.IS_DBG_OPENがtrue かつ LOG.DBG_LVが3以上 
 *  になっていた場合に出力される
 * 
 * ------------------------------------
 *  debugログの定義
 *  LV1のヘッダに記載
 *  
 *  LV3の定義
 *  重要度：低
 *  debugログの最低レベルの出力となる
 *  このログは、本番運用でONにするのはごく短時間の
 *  調査に用いる場合のみと想定しているため、好きなだけ
 *  細かく出力することを許されるものである
 *  開発時に多数埋め込むことでデバッグが進むのであれば
 *  LV3を使用するべきである
 *  ただ、開発が進んだ後、調査などに不要であると思われるものは
 *  削除すべきである
 * ------------------------------------
 * 
 * NOTICE:
 *  ※LOGS_ERR()と同じ
 * CREATE: 2015.08.27 hesaka
 * *********************************** */
function LOGS_DBG_LV3($text = "") {
	if (CONF::read("LOG.IS_DBG_OPEN") && CONF::read("LOG.DBG_LV") >= 3) {
		$out = $text;
		if (is_array($text)) {
			$out = PHP_EOL . print_r($text, true);
		}
		$trace = debug_backtrace(DEBUG_BACKTRACE_PROVIDE_OBJECT);
		$targetFile = basename($trace[0]["file"]);
		$function = ((empty($trace[1]["function"])) ? ('<none>') : ($trace[1]["function"]));
		$lineNumber = $trace[0]["line"];
		$output_text = "[" . date('Y/m/d H:i:s') . "][" . USER_IP . "][" . $targetFile . "::" . $function . "][" . $lineNumber . "][LV3]:" . $out . PHP_EOL;
		put_log('DEBUG', $output_text, 3, CONF::read("LOG.DBG_FILE_PATH"));
		//debug bar に出力
		if (CONF::read('DEBUG_BAR.IS_ACTIVE'))
			DebugBarMaster::info($output_text);
	}
}

/* * **********************************
 * NAME  : LOGS_MAIL
 * INPUT : text / string / 出力したい内容
 * OUTPUT: NONE
 * DESC  :
 *  mail ログ
 *  LOG.IS_MAIL_OPENがtrueになっていた場合に出力される
 * 
 * ------------------------------------
 *  MAILログの定義
 *  メール関係ログは基本的には当該ログに出力する
 *  内容としてNOTICE, ALERT, WARNINGとかぶる場合は悩ましいが
 *  基本的には、その旨分かりやすい形でMAILログに出力する
 * ------------------------------------
 * 
 * NOTICE:
 *  ※LOGS_ERR()と同じ
 * CREATE: 2015.10.13 hesaka
 * *********************************** */
function LOGS_MAIL($text = "") {
	if (CONF::read("LOG.IS_MAIL_OPEN")) {
		$out = $text;
		if (is_array($text)) {
			$out = PHP_EOL . print_r($text, true);
		}
		$trace = debug_backtrace(DEBUG_BACKTRACE_PROVIDE_OBJECT);
		$targetFile = basename($trace[0]["file"]);
		$function = ((empty($trace[1]["function"])) ? ('<none>') : ($trace[1]["function"]));
		$lineNumber = $trace[0]["line"];
		$output_text = "[" . date('Y/m/d H:i:s') . "][" . USER_IP . "][" . $targetFile . "::" . $function . "][" . $lineNumber . "]:" . $out . PHP_EOL;
		put_log('MAIL', $output_text, 3, CONF::read("LOG.MAIL_FILE_PATH"));
		//debug bar に出力
		if (CONF::read('DEBUG_BAR.IS_ACTIVE'))
			DebugBarMaster::info($output_text);
	}
}

/* * **********************************
 * NAME  : LOGS_ENV
 * INPUT : text / string / 出力したい内容
 * OUTPUT: NONE
 * DESC  :
 *  envログ出力
 *  LOG.IS_ENV_OPENがtrueになっていた場合に出力される
 * 
 * ------------------------------------
 *  envログの定義
 *  フレームワークの根幹に関与する、ENVによる環境判断
 *  そのENVがどの環境を選択しているかのログ
 * ------------------------------------
 * 
 * NOTICE:
 *  ※LOGS_ERR()と同じ
 * CREATE: 2015.12.22 hesaka
 * *********************************** */
function LOGS_ENV($text = "") {
	if (CONF::read("LOG.IS_ENV_OPEN")) {
		$out = $text;
		if (is_array($text)) {
			$out = PHP_EOL . print_r($text, true);
		}
		$trace = debug_backtrace(DEBUG_BACKTRACE_PROVIDE_OBJECT);
		$targetFile = basename($trace[0]["file"]);
		$function = ((empty($trace[1]["function"])) ? ('<none>') : ($trace[1]["function"]));
		$lineNumber = $trace[0]["line"];
		$output_text = "[" . date('Y/m/d H:i:s') . "][" . USER_IP . "][" . $targetFile . "::" . $function . "][" . $lineNumber . "]:" . $out;
		put_log('ENV', $output_text . PHP_EOL, 3, CONF::read("LOG.ENV_FILE_PATH"));
		//debug bar に出力
		if (CONF::read('DEBUG_BAR.IS_ACTIVE'))
			DebugBarMaster::info($output_text);
	}
}

/* * **********************************
 * NAME  : LOGS_DB
 * INPUT : text / string / 出力したい内容
 * OUTPUT: NONE
 * DESC  :
 * 		DB DELETE処理をログ出力
 * NOTICE:
 *  ※LOGS_ERR()と同じ
 * CREATE: 2016.10.26 aoyama
 * *********************************** */
function LOGS_DELETE($text = "") {
	$out = $text;
	if (is_array($text)) {
		$out = PHP_EOL . print_r($text, true);
	}
	$trace = debug_backtrace(DEBUG_BACKTRACE_PROVIDE_OBJECT);
	$targetFile = basename($trace[0]["file"]);
	$function = ((empty($trace[1]["function"])) ? ('<none>') : ($trace[1]["function"]));
	$lineNumber = $trace[0]["line"];
	$output_text = "[" . date('Y/m/d H:i:s') . "][" . USER_IP . "][" . $targetFile . "::" . $function . "][" . $lineNumber . "]:" . $out;
	put_log('DB_DELETE', $output_text . PHP_EOL, 3, CONF::read("LOG.DB_FILE_PATH"));
	//debug bar に出力
	if (CONF::read('DEBUG_BAR.IS_ACTIVE'))
		DebugBarMaster::info($output_text);
}

/* * **********************************
 * NAME  : put_log
 * INPUT : type / string / LOGの種類(ex:ERR,WARN etc...)
 * OUTPUT: false / 処理エラーの場合
 * DESC  :
 *  ログ出力処理
 *  LOG.MODEの設定により出力方法が変わる
 * 
 *  MODE
 *  local:テキストファイル出力
 *  papertrail:ペーパートレイル出力(サードパーティ製プラグイン)
 * 
 *  ※後に、DBにも出力できるように変更したい
 * 
 * NOTICE:
 * CREATE: 2015.08.27 hesaka
 * *********************************** */
function put_log($type, $text = '', $mode = 3, $target = '') {
	if (empty($target)) {
		return false;
	}
	switch (strval(CONF::read('LOG.MODE'))) {
		case 'local':
			//ディレクトリが無ければ作成
			if (!is_dir(DIR_LOG)) {
				FunctionForSetUp::create_dir(DIR_LOG);
			}
			xc_error_log($text, $mode, $target);
			break;
		case 'papertrail':
			$stdout = fopen('php://stdout', 'w');
			fwrite($stdout, '[' . $type . ']' . $text . "\n");
			break;
		default:
	}
}

/* * **********************************
 * NAME  : put_log
 * INPUT : type / string / LOGの種類(ex:ERR,WARN etc...)
 * OUTPUT: false / 処理エラーの場合
 * DESC  :
 *  ログ出力処理
 *  LOG.MODEの設定により出力方法が変わる
 * 
 *  MODE
 *  local:テキストファイル出力
 *  papertrail:ペーパートレイル出力(サードパーティ製プラグイン)
 * 
 *  ※後に、DBにも出力できるように変更したい
 * 
 * NOTICE:
 * CREATE: 2015.08.27 hesaka
 * *********************************** */


function xc_error_log($text, $mode, $target) {
    if (!file_exists($target)) {
        touch($target);
        chmod($target, 0777);
        chown($target, 48);
    }

    $fp = fopen($target, "a+");
    if ($fp === false) {
        // Handle the error here (e.g., log, throw an exception)
        // For example:
        // error_log("Failed to open the log file: $target");
        return;
    }

    $result = fwrite($fp, $text . "\n");
    if ($result === false) {
        // Handle the error here (e.g., log, throw an exception)
        // For example:
        // error_log("Failed to write to the log file: $target");
    }

    fclose($fp);
}
/* * **********************************
 * NAME  : log_archive
 * INPUT : NONE
 * OUTPUT: NONE
 * DESC  :
 *  ログのアーカイブを行う
 * NOTICE:
 *  MODEが「local」の場合のみ処理を行う
 *  処理自体は、画面からのタスクで行うとユーザを待たせることになるので
 *  別タスクを起こしてそちらで行ってもらう
 *  理論上は、アーカイブして削除する対象ファイルは先月以前のものとなるので、
 *  画面側で触ることのないログファイルとなるはずなので、競合など起こらない想定である
 * CREATE: 2015.10.01 hesaka
 * *********************************** */
function log_archive() {

	//IS_ACTIVE確認
	if (!CONF::read('LOG_ARCHIVE.IS_ACTIVE')) {
		return;
	}

	//モードがlocal以外の場合は終了
	if (CONF::read('LOG.MODE') !== 'local') {
		return;
	}

	//ARCHIVE_TIMING指定が配列でない場合は終了
	if (!is_array(CONF::read('LOG_ARCHIVE.TIMING'))) {
		return;
	}

	//今月がアーカイブタイミングかチェック
	foreach (CONF::read('LOG_ARCHIVE.TIMING') as $value) {

		//アーカイブタイミングの場合
		if (intval(DATETIME_STR_M) === $value) {

			//既にアーカイブされているかチェックし、あれば終了
			if (is_file(DIR_LOG_ARCHIVE . DS . 'archive_' . DATETIME_STR_Y . DATETIME_STR_M . '.zip')) {
				return;
			}

			/*
			 * タスクを起こしてアーカイブを依頼
			 * 20160714
			 * LogArchiveをクーロンから処理できる形に変更
			 * 実行タイミングはここで行うこととする
			 */
			//Linux
			if (PHP_OS !== 'WIN32' && PHP_OS !== 'WINNT') {
				exec('/usr/local/bin/php ' . DIR_APPLICATION . '/cron/CronController.inc env=' . ENV_DIR_NAME . ' class=LogArchive > /dev/null 2>&1 &');
				//windows
			} else {
				/* 20160714
				 * windows10にしてからどう調整しても動かなくなった
				 * なのでコメントアウトしておく
				 */
				$fp = popen('start C:\xampp\php\php.exe ' . DIR_APPLICATION . '\cron\CronController.inc env=' . ENV_DIR_NAME . ' class=LogArchive', 'r');
				pclose($fp);
			}

			return;
		}
	}
}

?>
