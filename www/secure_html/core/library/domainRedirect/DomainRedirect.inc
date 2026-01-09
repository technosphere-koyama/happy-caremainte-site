<?php

/* * **********************************
 * NAME:DomainRedirect
 * DESC:
 *  ドメイン リダイレクト クラス
 * NOTICE:
 *  SSL証明書の適応ドメインの制約があるために産まれたクラス
 *  指定ドメイン以外でアクセスしてきた場合にドメインを調整する
 *  くらいのもの
 * CREATE: 2015.12.01 hesaka
 * *********************************** */
class DomainRedirect{

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
	 * *********************************** */
	public function verification() {

		$ret = true;

		if (CONF::read('DOMAIN_REDIRECT.IS_ACTIVE') === true) {

			/*
			 * まずは有効時間判断
			 */
			//開始時刻が現在時刻より未来ならチェック対応外なのでtrueを返す
			if (CONF::read('DOMAIN_REDIRECT_TIMER.START') > time()) {
				return true;
			}
			
			//終了時刻が0でなく、かつ現在時刻が終了時刻より未来ならチェック対応外なのでtrueを返す
			//※0の場合は、エンドは無くチェック対応となるので、ここで終わること無く次へ進む必要がある
			if (CONF::read('DOMAIN_REDIRECT_TIMER.END') && CONF::read('DOMAIN_REDIRECT_TIMER.END') < time()) {
				return true;
			}

			/*
			 * サブドメイン部分判定
			 * 現状は、www有りドメインに持っていくのは手間がかかるので、
			 * サブドメなし対応のみとする
			 */
			$parts = explode('.', URL_HOST);
			//もう1階層増やすと、アパッチがスルーするようにしているので、
			//ドットの数が2個のときのみ処理を行うようにしておく
			if (count($parts) == 3) {
				unset($parts[0]);
				$ret = URL_SCHEME . '://' . implode('.', $parts) . URL_REQUEST;
			}
		}

		//noticeログに出力
		if ($ret !== true) {
			LOGS_NOTICE('*** DOMAIN REDIRECT! [ access host = ' . URL_HOST . ' ] ***');
		}
		
		return $ret;

	}

}

?>
