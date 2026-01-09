<?php

/* * **********************************
 * NAME:ForceRedirect
 * DESC:
 *  強制的にリダイレクトさせる
 *  使い方としては、全ページアクセスしてきたら403などに飛ばし、
 *  「現在工事中です。」など一時的にサイトを停止する時に使用することを
 *  想定する
 * NOTICE:
 * CREATE: 2015.09.07 hesaka
 * *********************************** */
class ForceRedirect {

	/* * **********************************
	 * NAME  : verification
	 * INPUT : NONE
	 * OUTPUT: true / リダイレクト不要
	 *         false / リダイレクト必要
	 * DESC  :
	 * NOTICE:
	 * CREATE: 2015.09.07 hesaka
	 * *********************************** */
	public function verification() {

		/*
		 * 特に処理を行う必要はない
		 * 有効になっていた場合はリダイレクトが必要
		 */
		if (CONF::read('FORCE_REDIRECT.IS_ACTIVE')) {

			/*
			 * 有効時間判断
			 */
			//開始時刻が現在時刻より未来ならチェック対応外なのでfalseを返す
			if (CONF::read('FORCE_REDIRECT_TIMER.START') > time()) {
				return true;
			}
			
			//終了時刻が0でなく、かつ現在時刻が終了時刻より未来ならチェック対応外なのでfalseを返す
			//※0の場合は、エンドは無くチェック対応となるので、ここで終わること無く次へ進む必要がある
			if (CONF::read('FORCE_REDIRECT_TIMER.END') && CONF::read('FORCE_REDIRECT_TIMER.END') < time()) {
				return true;
			}

			return false;
		}

		return true;
	}

}

?>
