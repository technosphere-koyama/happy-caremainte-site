<?php

/* * **********************************
 * NAME:SslRedirect
 * DESC:
 *  http to https リダイレクト クラス
 * NOTICE:
 * CREATE: 2015.08.27 hesaka
 * UPDATE: 2016.02.08 hesaka 443リダイレクト以外にも80リダイレクトもできるように変更
 * *********************************** */
class SslRedirect{

	/* Constructor */
	public function __construct() {
	}

	/* * **********************************
	 * NAME  : verification
	 * INPUT : NONE
	 * OUTPUT: true / リダイレクト不要
	 *         false / リダイレクト必要
	 * DESC  :
	 *  ポート番号をチェックする
	 * NOTICE:
	 *  SSL_REDIRECT.IS_ACTIVEがtrueでない場合はtrueを返す
	 *  user_PORTが取得できていなければtrueを返し、リダイレクトさせないようにする
	 * CREATE: 2015.08.27 hesaka
	 * UPDATE: 2016.02.08 hesaka 443リダイレクト以外にも80リダイレクトもできるように変更
	 * *********************************** */
	public function verification() {

		$ret = true;

		if (CONF::read('SSL_REDIRECT.IS_ACTIVE') === true) {

			/*
			 * まずは有効時間判断
			 */
			//開始時刻が現在時刻より未来ならチェック対応外なのでtrueを返す
			if (CONF::read('SSL_RESTRICT_TIMER.START') > time()) {
				return true;
			}
			
			//終了時刻が0でなく、かつ現在時刻が終了時刻より未来ならチェック対応外なのでtrueを返す
			//※0の場合は、エンドは無くチェック対応となるので、ここで終わること無く次へ進む必要がある
			if (CONF::read('SSL_RESTRICT_TIMER.END') && CONF::read('SSL_RESTRICT_TIMER.END') < time()) {
				return true;
			}

			//user_PORTが取得できていなければwarningログに出力し、リダイレクトしないようにtrueを返す
			if (StaticFunction::is_empty(USER_PORT)) {
				LOGS_WARN('*** USER PORT NOT FOUND! ***');
				return true;
			}

			/*
			 * TYPE設定によりリダイレクトスキーマを決定する
			 */
			$port = 0;
			switch (CONF::read('SSL_REDIRECT.TYPE')) {
				//80ポートへ
				case SSL_RESTRICT_TYPE_NOT_SSL:
					if (USER_PORT != SSL_RESTRICT_TYPE_NOT_SSL) {
						$port = SSL_RESTRICT_TYPE_NOT_SSL;
						$ret = URL_SCHEME_HTTP;
					}
					break;
				//443ポートへ
				case SSL_RESTRICT_TYPE_SSL:
					if (USER_PORT != SSL_RESTRICT_TYPE_SSL) {
						$port = SSL_RESTRICT_TYPE_SSL;
						$ret = URL_SCHEME_HTTPS;
					}
					break;
				//CONFIGのTYPE設定が想定外の場合はエラーとしてdie()する
				default:
					LOGS_ERR('*** SSL REDIRECT CONFIG ERROR! [type=' . CONF::read('SSL_REDIRECT.TYPE') . '] ***');
					die('SSLリダイレクト設定エラー');
					return;
			}
			/* 上記に変更
			 * SSLポート(443)以外の場合はfalseを返す
			if (USER_PORT != '443') {
				$ret = false;
			}
			 */
		}

		//noticeログに出力
		if ($ret !== true) {
			LOGS_NOTICE('*** SSL REDIRECT! [ from=' . USER_PORT . ', to=' . $port . ' ] ***');
		}
		
		return $ret;
	}

}

?>
