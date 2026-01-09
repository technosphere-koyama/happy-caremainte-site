<?php

/* * **********************************
 * NAME:MypageLogoutController
 * DESC:
 *   ログアウトする
 * NOTICE:
 * CREATE: 2015.11.24 hesaka
 * *********************************** */
class MypageLogoutController extends PublicOpenControllerFrame {

	/* Constructor */
	public function __construct() {
		parent::__construct();
		$this->sGroup = 'login';
	}

	/*	 * **********************************
	 * NAME  : exec
	 * INPUT : NONE
	 * OUTPUT: NONE
	 * DESC  :
	 *  PUBLIC画面ログイン状態からログアウトする
	 * NOTICE:
	 *  ログアウトして、PUBLIC画面トップへリダイレクトする
	 * CREATE: 2015.11.24 hesaka
	 * UPDATE: 2016.10.12 aoyama
	 *		ユーザーのカテゴリ判定を解除
	 * *********************************** */
	public function exec() {

		/*
		 * ログアウト処理を行い、PUBLIC画面トップへリダイレクトする
		 * ※ログアウト状態であれば、フレームでリダイレクトされているので、
		 * 　ここにくるということは、ログイン済み状態であるということ
		 */
		$login = new Login();
		if($login->logout()) {
			//PUBLIC側は、ログアウトしたらトップへ
			$this->redirect(CONF::read('URL_PUBLIC_ROOT'));
		}
	}

    /**
     * ログアウト後にentryにリダイレクトする
     * INPUT : NONE
     * OUTPUT: NONE
     * DESC  :
     *  TOPコミュニティ編集画面に「アカウント作成」というボタンを設置したので、
	 * 	このボタンを押すとログアウト→新規登録 という形で遷移させる
	 * 	（/entry/はログイン常態だとmypageにリダイレクトされてしまうため）
     * CREATE: 2017.09.14 aoyama
     * *********************************** */
    public function entry() {
        $login = new Login();
        if($login->logout()) {
            $this->redirect('/entry/');
        }
    }
}

?>
