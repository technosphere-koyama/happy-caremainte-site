<?php

/* * **********************************
 * NAME  : FunctionForSetUp
 * DESC  :
 *  初期ロード・セットアップ時専用 静的関数群
 * NOTICE:
 *  初期ロード・セットアップ以外で使用するものを
 *  追加してはならない！
 *  ※ログモジュールのrequire()前なので、ログは使えない！
 * CREATE: 2015.08.27 hesaka
 * *********************************** */

class FunctionForSetUp {

	/* * **********************************
	 * NAME  : get_dir_list_for_add_on
	 * INPUT : dir / string / 検索対象となるディレクトリへのフルパス 
	 * OUTPUT: array / ディレクトリフルパスのリスト
	 * 　      階層については、以下のように文字列で1次元配列で返す
	 *         /inc
	 *         /inc/conf
	 * DESC  :
	 *  INPUT dir 指定ディレクトリ以下にある全てのディレクトリを取得する
	 *  preLoadConf/<env_dir_name>/ONがあるかどうかで
	 *  そのディレクトリ以下を対象とするか判定し、なければ対象とならない  
	 * NOTICE:
	 *  これはadditional directory(libraryとmoduleなど)の、
	 *  conf読み込みとオートロード時に用いる専用
	 * CREATE: 2015.08.27 hesaka
	 * *********************************** */
	public static function get_dir_list_for_add_on($dir) {

		$all_list = FunctionForSetUp::get_dir_list($dir);

		$valid_list = array();

		/*
		 * まずは無効ライブラリ・モジュールの判定を行う
		 */
		foreach ($all_list as $path) {

			//library, moduleまでを外してディレクトリ名を配列へ
			$dir_list = explode(DS, str_replace($dir . DS, '', $path));

			/*
			 * パスを検出
			 */
			if ($dir_list[0] == DIR_NAME_THIRD_PARTY) {

				//thirdPartyの場合
				$module_path = $dir . DS . $dir_list[0] . DS . ((!empty($dir_list[1])) ? ($dir_list[1]) : (''));
				$pre_load_path = $dir . DS . $dir_list[0] . DS . ((!empty($dir_list[1])) ? ($dir_list[1]) : ('')) . DS . DIR_NAME_PRE_LOAD_CONF;
				$guess_pre_load_name = ((!empty($dir_list[2])) ? ($dir_list[2]) : (''));
				$guess_env_name = ((!empty($dir_list[3])) ? ($dir_list[3]) : (''));
			} else {

				//オリジナルの場合
				$module_path = $dir . DS . $dir_list[0];
				$pre_load_path = $dir . DS . $dir_list[0] . DS . DIR_NAME_PRE_LOAD_CONF;
				$guess_pre_load_name = ((!empty($dir_list[1])) ? ($dir_list[1]) : (''));
				$guess_env_name = ((!empty($dir_list[2])) ? ($dir_list[2]) : (''));
			}

			//対象外ディレクトリはここで終了
			if (!isset($guess_env_name)) {
				continue;
			}

			/*
			 * 判定処理本体
			 */

			//ステージングの場合は、ステージングディレクトリがなければローカルを使用する
			$target_env_dir = FunctionForSetUp::get_target_env_name($pre_load_path);

			//preLoadConf/local or release/に有効ファイルがあるか判定
			if ($guess_pre_load_name == DIR_NAME_PRE_LOAD_CONF && $guess_env_name == $target_env_dir && (file_exists($pre_load_path . DS . $target_env_dir . DS . FILE_NAME_VALID_MODULE_ON))) {

				//有効設定があれば、モジュール名までをリストに追加
				$valid_list[] = $module_path;
			}
		}

		/*
		 * 有効モジュールの詳細ディレクトリをリストアップ
		 */
		$ret_list = array();
		foreach ($valid_list as $path) {
			$ret_list = array_merge($ret_list, array($path), FunctionForSetUp::get_dir_list($path));
		}

//var_dump($ret_list);

		return $ret_list;
	}

	/* * **********************************
	 * NAME  : get_dir_list
	 * INPUT : dir / string / 検索対象となるディレクトリへのフルパス 
	 * OUTPUT: array / ディレクトリフルパスのリスト
	 * 　      階層については、以下のように文字列で1次元配列で返す
	 *         /inc
	 *         /inc/conf
	 * DESC  :
	 *  INPUT dir 指定ディレクトリ以下にある全てのディレクトリを取得する
	 * NOTICE:
	 * CREATE: 2015.08.27 hesaka
	 * *********************************** */
	public static function get_dir_list($dir) {

		$files = scandir($dir);
		$files = array_filter($files, function ($file) {
			return !in_array($file, array('.', '..'));
		});

		$list = array();
		foreach ($files as $file) {

			$fullpath = rtrim($dir, DS) . DS . $file;

			if (is_dir($fullpath)) {
				$list[] = $fullpath;
				$list = array_merge($list, FunctionForSetUp::get_dir_list($fullpath));
			}
		}

		return $list;
	}

	/* * **********************************
	 * NAME  : get_file_name_on_dir
	 * INPUT : dir / string / 検索対象となるディレクトリへのフルパス 
	 * OUTPUT: array / ファイル名(フルパス)のリスト
	 * 　      階層については、以下のように文字列で1次元配列で返す
	 *         /inc/xxx.inc
	 *         /inc/conf/xxx.php
	 * DESC  :
	 *  指定ディレクトリにあるファイルパスリストを取得する
	 * NOTICE:
	 *  ※そこにあるディレクトリの中のファイルは取得しない
	 *  ※有効無効判定ファイル「ON」「OFF」は省く
	 * CREATE: 2015.08.27 hesaka
	 * *********************************** */
	public static function get_file_name_on_dir($dir) {

		//ディレクトリが存在しなければ終了
		if (!is_dir($dir)) {
			return NULL;
		}

		//エラーの場合は終了
		if (($files = scandir($dir)) === false) {
			return NULL;
		}

		$files = array_filter($files, function ($file) {
			return !in_array($file, array('.', '..', FILE_NAME_VALID_MODULE_ON, FILE_NAME_VALID_MODULE_OFF));
		});

		$list = array();
		foreach ($files as $file) {
			$fullpath = rtrim($dir, DS) . DS . $file;
			if (is_file($fullpath)) {
				$list[] = $fullpath;
			}
		}

//var_dump($list);

		return $list;
	}

	/* * **********************************
	 * NAME  : get_file_name_on_target_env_dir
	 * INPUT : dir / string / 検索対象となるディレクトリへのフルパス 
	 * OUTPUT: array / ファイル名(フルパス)のリスト
	 * 　      階層については、以下のように文字列で1次元配列で返す
	 *         /inc/xxx.inc
	 *         /inc/conf/xxx.php
	 * DESC  :
	 *  環境判断値(ENV_DIR_NAME)により決定した、PreLoadConfの環境ディレクトリ
	 *  にあるファイルパスリストを取得する
	 * NOTICE:
	 *  ※そこにあるディレクトリの中のファイルは取得しない
	 *  ※有効無効判定ファイル「ON」「OFF」は省く
	 * CREATE: 2015.08.27 hesaka
	 * *********************************** */
	public static function get_file_name_on_target_env_dir($dir) {
		return FunctionForSetUp::get_file_name_on_dir($dir . DS . FunctionForSetUp::get_target_env_name($dir));
	}

	/* * **********************************
	 * NAME  : get_target_env_name
	 * INPUT : dir / string / 検索対象となるディレクトリへのフルパス 
	 * OUTPUT: string / 環境ディレクトリ名
	 * DESC  :
	 *  環境判断値(ENV_DIR_NAME)により決定した、PreLoadConfの環境ディレクトリ名を取得する
	 * NOTICE:
	 *  現状、「release」「staging」「local」の3つがあり、
	 *  設定値がstagingの場合で、ステージングディレクトリが存在しない場合は
	 *  ローカルを使用するようにするため、その場合は「local」を返すことになる
	 * CREATE: 2015.08.27 hesaka
	 * *********************************** */
	public static function get_target_env_name($dir) {
		if (ENV_DIR_NAME == ENV_NAME_STAGING && !file_exists($dir . DS . ENV_NAME_STAGING)) {
			return ENV_NAME_DEVELOP;
		} else {
			return ENV_DIR_NAME;
		}
	}

	/* * **********************************
	 * NAME  : file_write
	 * INPUT : file_path / string / 対象ファイルパス
	 *         data / string / 保存内容
	 * OUTPUT: true / 成功時
	 *         false / 失敗時
	 * DESC  :
	 *  file_pathにdataを内容としてファイル保存を行う
	 * NOTICE:
	 * CREATE: 2015.09.27 hesaka
	 * *********************************** */
	public static function file_write($file_path, $data) {

		if (($fp = fopen($file_path, "w")) === false) {
			//オープンに失敗した場合はfalseを返す
			return false;
		}

		flock($fp, LOCK_EX);
		fputs($fp, $data);
		flock($fp, LOCK_UN);
		fclose($fp);

		return true;
	}

	/* * **********************************
	 * NAME  : file_load
	 * INPUT : file_path / string / 対象ファイルパス
	 * OUTPUT: string / 成功した場合にファイルの中身
	 *         false / 失敗した場合
	 * DESC  :
	 *  file_pathのファイルの中身をロードする
	 * NOTICE:
	 * CREATE: 2015.09.27 hesaka
	 * *********************************** */
	public static function file_load($file_path) {
		return file_get_contents($file_path);
	}
	
	/* * **********************************
	 * NAME  : create_dir
	 * INPUT : dir_path / string / ディレクトリパス
	 * OUTPUT: NONE
	 * DESC  :
	 *  ディレクトリを作る
	 * NOTICE:
	 * CREATE: 2015.08.27 hesaka
	 * UPDATE: 2016.05.12 hesaka 途中ディレクトリが存在していなければ、強制的に作成するよう変更
	 * *********************************** */
	public static function create_dir($dir_path) {
		if (!is_dir($dir_path)) {
			mkdir($dir_path, 0777, true);
		}
	}
	
}

?>
