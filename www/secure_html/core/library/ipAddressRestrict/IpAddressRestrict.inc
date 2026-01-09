<?php

/* * **********************************
 * NAME:IpAddressRestrict
 * DESC:
 *  IPアドレス アクセス制限 クラス
 * NOTICE:
 * CREATE: 2015.08.27 hesaka
 * *********************************** */
class IpAddressRestrict {

	/* Constructor */
	public function __construct() {
	}

	/* * **********************************
	 * NAME  : verification
	 * INPUT : NONE
	 * OUTPUT: true / 許可する場合
	 *         false /  許可しない場合
	 * DESC  :
	 *  許可IPアドレスかチェックする
	 * NOTICE:
	 *  IP_RESTRICT.IS_ACTIVEがtrueでない場合はtrueを返す
	 *  チェック対象開始時刻・終了時刻の範囲外の場合は対象外となるのでtrueを返す
	 *  user_ipが取得できなければfalseを返しアクセスを禁止する
	 * CREATE: 2015.08.27 hesaka
	 * *********************************** */
	public function verification() {

		if (CONF::read('IP_RESTRICT.IS_ACTIVE') === true) {

			/*
			 * まずは有効時間判断
			 */
			//開始時刻が現在時刻より未来ならチェック対応外なのでtrueを返す
			if (CONF::read('IP_RESTRICT_TIMER.START') > time()) {
				return true;
			}
			
			//終了時刻が0でなく、かつ現在時刻が終了時刻より未来ならチェック対応外なのでtrueを返す
			//※0の場合は、エンドは無くチェック対応となるので、ここで終わること無く次へ進む必要がある
			if (CONF::read('IP_RESTRICT_TIMER.END') && CONF::read('IP_RESTRICT_TIMER.END') < time()) {
				return true;
			}
				
			/*
			 * user_ipが取得できていなければエラーログに出力し、アクセスを禁止する
			 */
			if (empty(USER_IP)) {
				LOGS_ERR('*** USER IP NOT FOUND! ***');
				return false;
			}
		
			/*
			 * 許可IPチェック
			 */
			foreach (CONF::read('IP_LIST') as $ip_address) {
				
				//許可IPアドレスがあればtrueへ
				if (USER_IP == $ip_address) {
					return true;
				}
			}

			//ここまでくるということは、許可されないということなのでfalseを返す
			LOGS_ALERT('*** IP ADDRESS RESTRICT OUT! [ access ip = ' . USER_IP . ' ] ***');
			return false;
		}
		
		//ここまでくるということは、IS_ACTIVEがfalseなのでtrueを返す
		return true;
	}

}

?>
