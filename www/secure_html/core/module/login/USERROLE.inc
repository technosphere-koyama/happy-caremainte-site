<?php

/* * **********************************
 * NAME:USERROLE
 * DESC:
 *  ユーザのロール(権限)に関する処理クラス
 * NOTICE:
 *  現状、PUBLICユーザに限定されたものであり、
 *  システムユーザ側には使用しないこと！
 * CREATE: 2016.09.13 hesaka
 * *********************************** */
class USERROLE {

	/* * **********************************
	 * NAME  : IS_GUEST
	 * INPUT : NONE
	 * OUTPUT: true / ゲスト権限を持つ
	 *         false / ゲスト権限を持たない
	 * DESC  :
	 *  ログインユーザがゲスト権限を持つか確認する
	 * NOTICE:
	 *  セッションに保持するユーザ情報から判断する
	 *  PUBLICユーザ限定で使用を許可するメソッドである
	 * CREATE: 2016.09.13 hesaka
	 * *********************************** */
	public static function IS_GUEST() {
		$guest = SESSION::read(CONF::read('USER_ROLE_INFO.GUEST'));
		if (is_array($guest) && !StaticFunction::is_empty($guest['extend_id'])) {
			return true;
		}
		return false;
	}

	/* * **********************************
	 * NAME  : GET_GUEST_EXTEND_ID
	 * INPUT : NONE
	 * OUTPUT: string / extend_id
	 *         NULL / extend_idが存在しない場合
	 * DESC  :
	 *  当該ユーザのGUEST権限のextend_idを取得する
	 * NOTICE:
	 *  セッションに保持するユーザ情報から判断する
	 *  PUBLICユーザ限定で使用を許可するメソッドである
	 *  -----------------------------------------------
	 *  extend_idはunsigned big intなので、通常のinteger型に
	 *  するとオーバーフローしてしまう
	 *  なので、明示的にstring型にキャストして返す
	 *  -----------------------------------------------
	 * CREATE: 2016.09.19 hesaka
	 * *********************************** */
	public static function GET_GUEST_EXTEND_ID() {
		$guest = SESSION::read(CONF::read('USER_ROLE_INFO.GUEST'));
		if (is_array($guest) && !StaticFunction::is_empty($guest['extend_id'])) {
			return (string)$guest['extend_id'];
		}
		return NULL;
	}
	
	/* * **********************************
	 * NAME  : IS_HOST
	 * INPUT : NONE
	 * OUTPUT: true / ホスト権限を持つ
	 *         false / ホスト権限を持たない
	 * DESC  :
	 *  ログインユーザがホスト権限を持つか確認する
	 * NOTICE:
	 *  セッションに保持するユーザ情報から判断する
	 *  PUBLICユーザ限定で使用を許可するメソッドである
	 * CREATE: 2016.09.13 hesaka
	 * *********************************** */
	public static function IS_HOST() {
		$host = SESSION::read(CONF::read('USER_ROLE_INFO.HOST'));
		if (is_array($host) && !StaticFunction::is_empty($host['extend_id'])) {
			return true;
		}
		return false;
	}

	/* * **********************************
	 * NAME  : GET_HOST_EXTEND_ID
	 * INPUT : NONE
	 * OUTPUT: string / extend_id
	 *         NULL / extend_idが存在しない場合
	 * DESC  :
	 *  当該ユーザのHOST権限のextend_idを取得する
	 * NOTICE:
	 *  セッションに保持するユーザ情報から判断する
	 *  PUBLICユーザ限定で使用を許可するメソッドである
	 *  -----------------------------------------------
	 *  extend_idはunsigned big intなので、通常のinteger型に
	 *  するとオーバーフローしてしまう
	 *  なので、明示的にstring型にキャストして返す
	 *  -----------------------------------------------
	 * CREATE: 2016.09.19 hesaka
	 * *********************************** */
	public static function GET_HOST_EXTEND_ID() {
		$host = SESSION::read(CONF::read('USER_ROLE_INFO.HOST'));
		if (is_array($host) && !StaticFunction::is_empty($host['extend_id'])) {
			return (string)$host['extend_id'];
		}
		return NULL;
	}

	/* * **********************************
	 * NAME  : IS_SUPPLIER
	 * INPUT : NONE
	 * OUTPUT: true / サプライヤ権限を持つ
	 *         false / サプライヤ権限を持たない
	 * DESC  :
	 *  ログインユーザがサプライヤ権限を持つか確認する
	 * NOTICE:
	 *  セッションに保持するユーザ情報から判断する
	 *  PUBLICユーザ限定で使用を許可するメソッドである
	 * CREATE: 2016.09.13 hesaka
	 * *********************************** */
	public static function IS_SUPPLIER() {
		$supplier = SESSION::read(CONF::read('USER_ROLE_INFO.SUPPLIER'));
		if (is_array($supplier) && !StaticFunction::is_empty($supplier['extend_id'])) {
			return true;
		}
		return false;
	}
	
	/* * **********************************
	 * NAME  : GET_SUPPLIER_EXTEND_ID
	 * INPUT : NONE
	 * OUTPUT: string / extend_id
	 *         NULL / extend_idが存在しない場合
	 * DESC  :
	 *  当該ユーザのSUPPLIER権限のextend_idを取得する
	 * NOTICE:
	 *  セッションに保持するユーザ情報から判断する
	 *  PUBLICユーザ限定で使用を許可するメソッドである
	 *  -----------------------------------------------
	 *  extend_idはunsigned big intなので、通常のinteger型に
	 *  するとオーバーフローしてしまう
	 *  なので、明示的にstring型にキャストして返す
	 *  -----------------------------------------------
	 * CREATE: 2016.09.19 hesaka
	 * *********************************** */
	public static function GET_SUPPLIER_EXTEND_ID() {
		$supplier = SESSION::read(CONF::read('USER_ROLE_INFO.SUPPLIER'));
		if (is_array($supplier) && !StaticFunction::is_empty($supplier['extend_id'])) {
			return (string)$supplier['extend_id'];
		}
		return NULL;
	}
	
}

?>
