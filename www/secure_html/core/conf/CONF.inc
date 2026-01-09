<?php

/* * **********************************
 * NAME:CONF
 * DESC:
 *  $configに設定した値を取得する為のクラス
 *  $configにセットするのは、各configフォルダで
 *  配列として追加すること
 *  各機能毎に1次元目を作り、それに纏わるパラメータは
 *  2次元目にセットすることでグループとして管理できるようにすること
 * NOTICE:
 *  $configは単なるグローバル変数なので、どこでも変更できてしまうが
 *  それは行わないこと！
 *  config設定以降は、CONF::read()にて読み込む以外
 *  タッチしないこと！
 * CREATE: 2015.08.27 hesaka
 * *********************************** */
class CONF {

	/* * **********************************
	 * NAME  : read
	 * INPUT : str / string / $configから読み出したいパラメータ名
	 * OUTPUT: array / 成功時、パラメータ値を返す
	 *         NULL / 存在しない場合
	 *         ※strに空文字を指定された場合は$config全てを返す
	 * DESC  :
	 *  define扱いとして宣言した「$config」のパラメータを取得する
	 * NOTICE:
	 *  strに「.」区切りで指定すると、多次元配列として検索する
	 * 
	 *  アクセスする場合は
	 *  CONF::read("CONF_GROUP.CONF_NAME")のように使用すること
	 * 
	 * CREATE: 2015.08.27 hesaka
	 * *********************************** */
	public static function read($str = NULL) {

		//グローバルに宣言する「$config」を参照する
		global $config;
		$ret = $config;

		/*
		 * 空文字の場合は丸々返す
		 * ※とりあえずの使い道はDebugBar用
		 */
		if (empty($str)) {
			return $ret;
		}

		$param_list = explode(".", $str);
		foreach ($param_list as $param) {
			//存在しなければNULLを返す
			if (!isset($ret[$param])) {
				return null;
			}
			$ret = $ret[$param];
		}

		return $ret;
	}

}

?>
