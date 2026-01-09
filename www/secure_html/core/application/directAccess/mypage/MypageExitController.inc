<?php

/* * **********************************
 * NAME:MypageExitController
 * DESC:
 * マイページ退会完了画面を表示するため
 * マイページ退会後、CloseControllerでは、
 * セッション情報を保持していない為、ページ閲覧ができない。
 * そのため、マイページ系で唯一OpenControllerで処理を行う。
 *
 * しかし、むやみにアクセスされるのもよくないので、
 * exit.htmlから遷移する場合はセッションをつけておいて
 * なければトップページにリダイレクトする。
 * NOTICE:
 * CREATE: 2015.11.26 sonoda
 * *********************************** */
class MypageExitController extends MypageOpenControllerFrame {

	/* Constructor */
	public function __construct() {
		parent::__construct();
		$this->sGroup = 'mypage';
	}

	/*	 * **********************************
	 * NAME  : exec
	 * INPUT : NONE
	 * OUTPUT: NONE
	 * DESC  :
	 * 退会完了後に表示されるページ
	 * NOTICE:
	 * CREATE: 2015.09.14 sonoda
	 * UPDATE: 2015.12.17 hesaka user_memberセッションもクリア
	 * *********************************** */
	public function exec() {

		//indexからきた、もしくはポストがある以外はトップへ
		if (StaticFunction::is_empty(SESSION::read($this->sGroup . '.exit')) && !REQUEST::is_post()) {
			$this->redirect('../index.html');
		}

		//F5押下対策として、マイページ関連のセッション削除
		SESSION::delete($this->sGroup);

		//ログアウトにするために、user_memberのセッションも削除
		SESSION::delete(CONF::read('LOGIN_CATEGORY.PUBLIC'));

		/*
		 * 退会する場合は、カートをクリアしておく
		 * 会員しか見れない・買えない商品があるため、保持しておくと、
		 * カートに行くとエラーになる可能性がある
		 * なのでここでクリア
		 * ※ログアウト状態でカートに入れたあとにログインする場合は保持する
		 */
		SESSION::delete('shop_cart');
	}

}

?>
