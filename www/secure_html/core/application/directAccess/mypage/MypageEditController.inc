<?php

/* * **********************************
 * NAME:MypageEditController
 * DESC:
 *  マイページ用のコントローラ(クローズエリア)
 * 
 *  コントローラの継承
 *  MypageController
 *  ↓
 *  MypageCloseCommonControllerFrame
 *  ↓
 *  MypageBaseCommonControllerFrame
 *  ↓
 *  ControllerCore
 *  となる
 * 
 * NOTICE:
 * CREATE: 2016.10.14 aoyama
 * UPDATE: 2016.10.21 aoyama
 * 		SNSデータも更新対象に
 * *********************************** */
class MypageEditController extends MypageCloseCommonControllerFrame {

	private $sGroup;
	private $public_user_data;

	/* Constructor */
	public function __construct() {

		parent::__construct();
		$this->sGroup = "edit_user";

		//ファッション系統の配列を取得してvuewに渡す
		$fashionMaster = new FashionTypeMasterModel();
		$this->fashionMasterArray = $fashionMaster->get_basic_data();
		$this->set("fashionTypeArray", $this->fashionMasterArray);

		//セッションからユーザ情報を取得
		$this->public_user_data = SESSION::read(CONF::read('LOGIN_CATEGORY.PUBLIC'));
	}

	/*	 * **********************************
	 * NAME  : index
	 * INPUT : 
	 * OUTPUT: 
	 * DESC  : 
	 * 		登録フォーム
	 * 		セッションにセットするのはここだけ。
	 * 		同時にバリデーションチェックも実施
	 * NOTICE:
	 * CREATE: 2016.10.13 aoyama
	 * *********************************** */
	public function index() {

		$this->set("nickname", $this->public_user_data['nickname']);
		$this->set("like_brand", $this->public_user_data['like_brand']);
		$this->set("fashion_id", $this->public_user_data['fashion_id']);
		if (!StaticFunction::is_empty($this->public_user_data['fashion_id'])) {
			$this->set("fashion_id_view", $this->fashionMasterArray[$this->public_user_data['fashion_id']]);
		}
		$this->set("comment", $this->public_user_data['comment']);

		// POSTデータがある場合、セッションに登録する。
		if (!StaticFunction::is_empty(REQUEST::post_data())) {

			// SNS用
			SESSION::write($this->sGroup . '.nickname', REQUEST::post_data('nickname'));
			SESSION::write($this->sGroup . '.comment', REQUEST::post_data('comment'));
			SESSION::write($this->sGroup . '.fashion_id', REQUEST::post_data('fashion_id'));
			SESSION::write($this->sGroup . '.like_brand', REQUEST::post_data('like_brand'));

			// バリデーション
			$error_array = $this->checkSessionParameter();
			if (StaticFunction::is_empty($error_array)) {
				//問題なければ確認画面へ
				$this->redirect("./confirm.html");
			}
			$this->set('error_array', $error_array);
			$this->formReturn();
		}
	}

	/*	 * **********************************
	 * NAME  : confirm
	 * INPUT : 
	 * OUTPUT: 
	 * DESC  : 
	 *  入力確認画面用
	 *  セッションがあればとりあえず表示する
	 *  ここではバリデーション無し
	 * NOTICE:
	 * CREATE: 2016.10.14 aoyama
	 * *********************************** */
	public function confirm() {
		// POSTデータがないので「戻るボタン」の可能性。setしそのまま表示
		$this->formReturn();
	}

	/*	 * **********************************
	 * NAME  : complete
	 * INPUT : 
	 * OUTPUT: 
	 * DESC  : 
	 *  入力完了画面用
	 *  APIで情報を送信
	 * NOTICE:
	 *  API送信処理あり（セッションバリデーション含む）
	 * CREATE: 2016.10.14 aoyama
	 * *********************************** */
	public function complete() {

		if (StaticFunction::is_empty(SESSION::read($this->sGroup))) {
			$this->redirect("./");
		}

		$error_array = $this->checkSessionParameter();
		if (!StaticFunction::is_empty($error_array)) {
			$this->redirect("./");
		}

		//DB情報を更新
		$user = new UserPublicModel();

		$params = array(
			"nickname" => DbCast::string(SESSION::read($this->sGroup . '.nickname')),
			"comment" => DbCast::string(SESSION::read($this->sGroup . '.comment')),
			"like_brand" => DbCast::string(SESSION::read($this->sGroup . '.like_brand')),
			"fashion_id" => DbCast::integer(SESSION::read($this->sGroup . '.fashion_id'))
		);

		$condition = array(
			"WHERE" => array(
				"user_id" => DbCast::id($this->public_user_data['user_id'])
			)
		);
		if (!$user->update($params, $condition)) {
			$error_array[] = array('target' => 'comment', "message" => "SNS登録情報の更新に失敗しました。");
			$this->set('error_array', $error_array);
		}

		//入力内容をセッションに登録する
		SESSION::write(CONF::read('LOGIN_CATEGORY.PUBLIC') . '.nickname', SESSION::read($this->sGroup . '.nickname'));
		SESSION::write(CONF::read('LOGIN_CATEGORY.PUBLIC') . '.fashion_id', DbCast::integer(SESSION::read($this->sGroup . '.fashion_id')));
		SESSION::write(CONF::read('LOGIN_CATEGORY.PUBLIC') . '.like_brand',SESSION::read($this->sGroup . '.like_brand'));
		SESSION::write(CONF::read('LOGIN_CATEGORY.PUBLIC') . '.comment', SESSION::read($this->sGroup . '.comment'));

		//正常終了時はセッションを削除
		SESSION::delete($this->sGroup);
		
		$this->redirect("/mypage/sns.html");

	}

	/*	 * **********************************
	 * NAME:checkSessionParameter
	 * DESC:
	 *  メルマガ登録専用のセッション情報バリデーション
	 * NOTICE:
	 * CREATE: 2016.10.14 aoyama
	 * *********************************** */
	private function checkSessionParameter() {

		$error_array = array();

		if (!InputVali::is_nickname(SESSION::read($this->sGroup . '.nickname'))) {
			$error_array[] = array('target' => 'nickname', 'message' => 'ニックネームは20文字以内で入力してください');
		}
		if ((SESSION::read($this->sGroup . '.nickname') == CONF::read("MASTER_USER.NICKNAME")) && CONF::read("MASTER_USER.USER_ID") != $this->public_user_data['user_id']) {
			$error_array[] = array('target' => 'nickname', 'message' => 'ニックネームに「' . CONF::read("MASTER_USER.NICKNAME") . '」を設定することはできません');
		}

		if (!StaticFunction::is_empty(SESSION::read($this->sGroup . '.fashion_id'))) {
			if (!InputVali::is_array_key(SESSION::read($this->sGroup . '.fashion_id'), $this->fashionMasterArray)) {
				$error_array[] = array('target' => 'zip', 'message' => 'ファッション系統は選択肢から選んでください。');
			}
		}

		if (!StaticFunction::is_empty(SESSION::read($this->sGroup . '.like_brand'))) {
			if (!InputVali::is_brand_name(SESSION::read($this->sGroup . '.like_brand'))) {
				$error_array[] = array('target' => 'like_brand', 'message' => '好きなブランド名は20文字以内で入力してください。');
			}
		}

		if (!StaticFunction::is_empty(SESSION::read($this->sGroup . '.comment'))) {
			if (!InputVali::is_prof_comment(SESSION::read($this->sGroup . '.comment'))) {
				$error_array[] = array('target' => 'comment', 'message' => '自己紹介は200文字以内で入力してください。');
			}
		}
		return $error_array;
	}

	/*	 * **********************************
	 * NAME:formReturn
	 * DESC:
	 *  セッション情報をフォームに渡すためにセットする機能
	 * NOTICE:
	 * CREATE: 2015.11.27 aoyama
	 * UPDATE: 2016.10.13 aoyama
	 * *********************************** */
	private function formReturn() {

		// セッションの情報をセットしてviewに渡す
		if (!StaticFunction::is_empty(SESSION::read($this->sGroup))) {

			$this->set("tmp_avatar", SESSION::read($this->sGroup . '.tmp_avatar'));
			$this->set("tmp_avatar_date", SESSION::read($this->sGroup . '.tmp_avatar_date'));
			$this->set("nickname", SESSION::read($this->sGroup . '.nickname'));
			$this->set("fashion_id", SESSION::read($this->sGroup . '.fashion_id'));
			if (!StaticFunction::is_empty(SESSION::read($this->sGroup . '.fashion_id'))) {
				$this->set("fashion_id_view", $this->fashionMasterArray[SESSION::read($this->sGroup . '.fashion_id')]);
			}
			$this->set("like_brand", SESSION::read($this->sGroup . '.like_brand'));
			$this->set("comment", SESSION::read($this->sGroup . '.comment'));
		}
	}
}

?>
