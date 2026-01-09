<?php

/* * **********************************
 * NAME: MypageCloseCommonControllerFrame
 * DESC:
 *  マイページ画面の共通部分に用いるフレーム
 *  （クローズで尚且つログインファーストが通過できたもののみ）
 * NOTICE:
 * CREATE: 2016.10.13 aoyama
 * *********************************** */
class MypageCloseCommonControllerFrame extends MypageBaseCommonControllerFrame {

	/* * **********************************
	 * NAME  : __construct
	 * INPUT : NONE
	 * OUTPUT: NONE
	 * DESC  :
	 *  マイページ画面の共通部分に用いる
	 *  フレームのコンストラクタ
	 *  下記内容を処理する
	 *  ・初回ログイン処理を通過しているかの判定
	 * 　　ログイン常態は親クラスで実施
	 * NOTICE:
	 * --------------------------------------
	 *  当該フレーム定義に必要な認証は
	 *  コントローラではなくここで行う
	 * --------------------------------------
	 * CREATE: 2016.10.13 aoyama
	 * UPDATE: 2016.10.24 aoyama
	 *		ガジェット用にview情報をセット
	 * UPDATE: 2016.12.5 aoyama
	 *		ログインとSNS利用を分離したので
	 *		情報取得部分を「MypageBaseCommonControllerFrame」に移行
	 * *********************************** */
	private $public_user_data;
	
	public function __construct() {

		//子クラス名をControllerCoreに渡す
		parent::__construct(get_class($this));
		
		/* 
		 * セッションに「user_id」があるかチェック。
		 * 無いときはlogin_firstにリダイレクト。
		 */
		if (!$this->is_sns_entry()) {
			//初回ログインページへリダイレクト
			$this->redirect(CONF::read('URL_PUBLIC_ROOT') . 'mypage/login_first');
		}
	}
}

?>
