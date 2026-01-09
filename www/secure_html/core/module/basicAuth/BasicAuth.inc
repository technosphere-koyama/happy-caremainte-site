<?php

/* * **********************************
 * NAME:BasicAuth
 * DESC:
 *  ベーシック認証を実現する
 * NOTICE:
 *  htaccessでも実現はできるが
 *  サーバによっては動かないし、動く環境でも既にhtaccessを使用していた場合
 *  ぶつかって動かない可能性もあるので、PHPで実現することにする
 * CREATE: 2015.10.06 hesaka
 * *********************************** */
class BasicAuth {

	/* Constructor */
	public function __construct() {
	}

	/*	 * **********************************
	 * NAME  : verification
	 * INPUT : NONE
	 * OUTPUT: true / 認証成功
	 *         exit / 認証失敗
	 * DESC  :
	 *  ベーシック認証を行う
	 * NOTICE:
	 *  未認証の場合、もしくは認証失敗の場合は認証ダイアログを表示
	 *  ※SERVER変数のPHP_AUTH_USERとPHP_AUTH_PWは初期化できないらしく
	 *  　一度認証失敗したら、しばらく失敗した文字列を持ち続ける
	 *  　そーなると、ずっと失敗し続け、403ページなどにリダイレクトさせるようにしておくと
	 *  　しばらく認証画面すら出してもらえなくなる
	 *  　なので、逆にリダイレクトはさせず「成功するまでダイアログを表示」するしか方法がない
	 *  　なので、「未認証の場合、もしくは認証失敗の場合は認証ダイアログを表示」となる
	 *  認証に成功した場合はtrueを返す
	 * CREATE: 2015.10.07 hesaka
	 * *********************************** */
	public function verification() {

		if (CONF::read('BASIC_AUTH.IS_ACTIVE') === true) {

			//認証を行っていない場合
			if (!isset($_SERVER["PHP_AUTH_USER"]) || !isset($_SERVER["PHP_AUTH_PW"])) {

				//ダイアログ表示して終了
				$this->dialogue();
				exit;

			} else {

				//認証
				if (!(CONF::read('BASIC_AUTH.USER') == $_SERVER["PHP_AUTH_USER"] && CONF::read('BASIC_AUTH.PASSWORD') == $_SERVER["PHP_AUTH_PW"])) {

					//認証失敗の場合はログを出して
					LOGS_NOTICE('*** BASIC AUTH VERIFY MISSMATCH ! [ user=' . $_SERVER["PHP_AUTH_USER"] . ', pwd=' . $_SERVER["PHP_AUTH_PW"] . ' ] ***');

					//再度ダイアログ表示して終了
					$this->dialogue();
					exit;
				}
			}
		}

		return true;
	}

	/*	 * **********************************
	 * NAME  : dialogue
	 * INPUT : NONE
	 * OUTPUT: NONE
	 * DESC  :
	 *  ベーシック認証ダイアログを表示する
	 * NOTICE:
	 * CREATE: 2015.10.07 hesaka
	 * *********************************** */
	private function dialogue() {

		header('WWW-Authenticate: Basic realm="Please Enter Your Password"');
		header('HTTP/1.0 401 Unauthorized');

		//キャンセル時の表示
		print CONF::read('BASIC_AUTH.CANCEL_DIALOGUE_TEXT');
	}

}

?>
