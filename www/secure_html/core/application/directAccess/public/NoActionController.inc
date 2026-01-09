<?php

/* * **********************************
 * NAME:NoActionController
 * DESC:
 *  特商ページ、コンセプトページなど、コントローラを
 *  必要としない静的ページ用のコントローラ
 * NOTICE:
 *  コントローラ的な処理を行わないが、サイト共通処理の
 *  強制リダイレクトやIP制限などがあった場合、他と同じく
 *  コントローラの親フレームなどで処理を行わないといけないので
 *  そのような画面の際には当該コントローラを生成すること
 *  exec()は不要なため作成しない
 * CREATE: 2015.09.25 hesaka
 * *********************************** */
class NoActionController extends PublicOpenControllerFrame {

	/* Constructor */
	public function __construct() {
		parent::__construct();
	}

}

?>
