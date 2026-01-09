<?php

/* * **********************************
 * クーロン用コントローラ
 * 全クーロンは、当該ファイルをcrontabに登録し、
 * 引数に環境、対象クラスを設定することとする
 * 
 * 書き方
 * CronController.php env=local class=GetInstagramData
 * 
 * /usr/bin/php /home/www/secure_html/core/application/API/forExternal/controller/LatestCareApiController.inc
 * /usr/bin/php /home/www/secure_html/core/application/cron/CronController.inc env=staging class=LatestCareApi
 * /usr/bin/php /home/www/secure_html/core/application/cron/CronController.inc env=staging class=LatestCareApi

 * env:環境指定
 *	local, staging, release を指定する
 * class:実行対象クラス
 *	対象のクラスでは、「exec()」を作成すること
 *	exec()が実行されることになる
 * *********************************** */

/*
 * クーロンの引数をkey, valueに分解
 */
foreach($argv as $strArg){
	$arrTmp = explode('=', $strArg);
	if (is_array($arrTmp) && isset($arrTmp[1])) {
		$parameter[$arrTmp[0]] = $arrTmp[1];
	}
}

/*
 * 引数に指定された「env」から環境判断
 */
switch ($parameter['env']) {
	//本番環境
	case 'release':
		define("ENV_DIR_NAME", 'release');
		break;
	//ステージング(テスト)環境
	case 'staging':
		define("ENV_DIR_NAME", 'staging');
		break;
	//開発環境
	case 'local':
		define("ENV_DIR_NAME", 'local');
		break;
	//上記3つ以外はエラーとなる
	//※フレームワークのロード前なのでログ出力できない。。。
	//なので、終わるだけとなる
	default:
		return;
}

//フレームワークロード
require dirname(__FILE__) . '/../../PreLoad.inc';

LOGS_NOTICE(PHP_EOL . '-----------------------------' . PHP_EOL . ' CRON START env=' . ENV_DIR_NAME . ', class=' . $parameter['class'] . PHP_EOL . '-----------------------------');

//class指定チェック
if (StaticFunction::is_empty($parameter['class'])) {
	LOGS_ERR('*** CRON ERROR, NOT INSTRUCTION CLASS NAME!!!');
	return;
}

/*
 * 指定クラスインスタンス生成&exec()実行
 */
//$ret = (new $parameter['class']())->exec();

$dbDump = new FullDumpDbForBackup();
$dbDump->exec();

$ret = new LatestCareApi();
$ret->exec();

LOGS_NOTICE(PHP_EOL . '-----------------------------' . PHP_EOL . ' CRON END result=' . $ret . PHP_EOL . '-----------------------------');

return;
