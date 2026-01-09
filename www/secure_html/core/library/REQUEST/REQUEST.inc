<?php

/* * **********************************
 * NAME:REQUEST
 * DESC:
 *  $_POST, $_GETメソッド
 *  パラメータ管理クラス
 * NOTICE:
 *  ※それぞれサニタイズしてセットする
 *  ※直接$_POST,$_GETは触らず、当該クラスにて触ること！
 * CREATE: 2015.08.27 hesaka
 * *********************************** */
class REQUEST {

	private static $get = array();
	private static $is_get_exist = false;

	private static $post = array();
	private static $is_post_exist = false;

	/* * **********************************
	 * NAME  : exec
	 * INPUT : NONE
	 * OUTPUT: NONE
	 * DESC  :
	 *  $_POST,$_GETパラメータを取得し、サニタイズを行って
	 *  各パラメータセット用のメンバにセットする
	 * NOTICE:
	 * CREATE: 2015.08.27 hesaka
	 * *********************************** */
	public static function exec() {
		REQUEST::get_sanitize();
		REQUEST::post_sanitize();
	}

	/* * **********************************
	 * NAME  : is_get
	 * INPUT : NONE
	 * OUTPUT: true / $_GETに値がセットされていた
	 *         false / $_GETに値がセットされていなかった
	 * DESC  :
	 *  $_GETデータの有無を返す
	 * NOTICE:
	 * CREATE: 2015.08.27 hesaka
	 * *********************************** */
	public static function is_get() {
		return REQUEST::$is_get_exist;
	}
	
	/* * **********************************
	 * NAME  : is_post
	 * INPUT : NONE
	 * OUTPUT: true / $_POSTに値がセットされていた
	 *         false / $_POSTに値がセットされていなかった
	 * DESC  :
	 *  $_POSTデータの有無を返す
	 * NOTICE:
	 * CREATE: 2015.08.27 hesaka
	 * *********************************** */
	public static function is_post() {
		return REQUEST::$is_post_exist;
	}

	/* * **********************************
	 * NAME  : get_data
	 * INPUT : target_name / 取得したいGETデータの名前
	 * OUTPUT: string or array / 指定名GETパラメータ
	 *         NULL / 指定名がない場合
	 * DESC  :
	 *  指定される名前のGETデータを返す
	 * NOTICE:
	 *  $target_nameが空の場合は全部返す
	 * CREATE: 2015.08.27 hesaka
	 * UPDATE: 2015.11.09 hesaka 引数空の場合全て返すよう変更
	 * UPDATE: 2016.01.12 hesaka ログ出力先をnoticeからDBG_LV3へ(出すぎるため)
	 * *********************************** */
	public static function get_data($target_name = NULL) {

		//空が指定された場合は全部返す
		if (empty($target_name)) {
			return REQUEST::$get;
		}

		//指定された名前のパラメータがない場合はnoticeログ出力
		if (!isset(REQUEST::$get[$target_name])) {
			//※確認も含めて、このパスを通ることがあるのでログはDBG_LV3へ
			LOGS_DBG_LV3('not exist GET PARAM, target_name:' . $target_name);
			return NULL;
		}

		return REQUEST::$get[$target_name];
	}
	
	/* * **********************************
	 * NAME  : post_data
	 * INPUT : target_name / 取得したいPOSTデータの名前
	 * OUTPUT: string or array / 指定名POSTパラメータ
	 *         NULL / 指定名がない場合
	 * DESC  :
	 *  指定される名前のPOSTデータを返す
	 * NOTICE:
	 *  $target_nameが空の場合は全部返す
	 * CREATE: 2015.08.27 hesaka
	 * UPDATE: 2015.11.09 hesaka 引数空の場合全て返すよう変更
	 * UPDATE: 2016.01.12 hesaka ログ出力先をnoticeからDBG_LV3へ(出すぎるため)
	 * *********************************** */
	public static function post_data($target_name = NULL) {

		//空が指定された場合は全部返す
		if (empty($target_name)) {
			return REQUEST::$post;
		}

		//指定された名前のパラメータがない場合はnoticeログ出力
		if (!isset(REQUEST::$post[$target_name])) {
			//※確認も含めて、このパスを通ることがあるのでログはDBG_LV3へ
			LOGS_DBG_LV3('not exist POST PARAM, target_name:' . $target_name);
			return NULL;
		}

		return REQUEST::$post[$target_name];
	}



	/* * **********************************
	 * NAME  : get_sanitize
	 * INPUT : NONE
	 * OUTPUT: NONE
	 * DESC  :
	 *  $_GETのサニタイズ処理
	 * 
	 *  ※空の場合は
	 *  　$getは空配列
	 *  　$is_get_existはfalse
	 * 　 のままにしておく
	 * 
	 * NOTICE:
	 * CREATE: 2015.08.27 hesaka
	 * *********************************** */
	private static function get_sanitize() {
		if (($ret = REQUEST::sanitize($_GET)) === false) {
			//空の場合ログだけ吐いておく
			LOGS_DBG_LV3('GET is empty');
		} else {
			REQUEST::$is_get_exist = true;
			REQUEST::$get = $ret;
		}

	}
	
	/* * **********************************
	 * NAME  : post_sanitize
	 * INPUT : NONE
	 * OUTPUT: NONE
	 * DESC  :
	 *  $_POSTのサニタイズ処理
	 * 
	 *  ※空の場合は
	 *  　$postは空配列
	 *  　$is_post_existはfalse
	 * 　 のままにしておく
	 * 
	 * NOTICE:
	 * CREATE: 2015.08.27 hesaka
	 * *********************************** */
	private static function post_sanitize() {
		//print_r($_POST);
		$ret = REQUEST::sanitize($_POST);		
		if ($ret === false) {
			//空の場合ログだけ吐いておく
			LOGS_DBG_LV3('POST is empty');
		} else {
			REQUEST::$is_post_exist = true; 
			REQUEST::$post  = $ret;
		}

	}

	/* * **********************************
	 * NAME  : sanitize
	 * INPUT : target / array / サニタイズを行う配列
	 *         ※現時点では、$_POST,$_GETのみを想定
	 * OUTPUT: array / サニタイズが完了した配列
	 * DESC  :
	 *  サニタイズを行う
	 *  ※実際に行うのはsanitize_core()である
	 * NOTICE:
	 *  2次元配列までを想定している
	 *  それ以上になる場合はカスタマイズが必要となる！
	 * CREATE: 2015.08.27 hesaka
	 * UPDATE: 2015.11.13 hesaka 3次元目対応
	 * *********************************** */
	private static function sanitize($target) {
		//print_r($target);
		if (empty($target)) {
			return false;
		}

		$param_list = array();

		foreach ($target as $key => &$value) {

			//２次元目
			if (is_array($value)) {

				$param_list[$key] = array();
				foreach ($value as $key2 => &$value2) {

					//3次元配列まで対応可能
					if (is_array($value2)) {

						$param_list[$key][$key2] = array();
						foreach ($value2 as $key3 => &$value3) {
							$param_list[$key][$key2][$key3] = SANITIZE::exec($value3);
						}

					} else {
						$param_list[$key][$key2] = SANITIZE::exec($value2);
					}
				}

			} else {
				$param_list[$key] = SANITIZE::exec($value);
			}
		}
		//print_r($param_list);		exit;
		return $param_list;
	}

}

//実行
REQUEST::exec();

?>
