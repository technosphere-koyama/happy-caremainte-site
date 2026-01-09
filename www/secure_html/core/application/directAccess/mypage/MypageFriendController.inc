<?php

/* * **********************************
 * NAME:MypageFriendController
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
 * CREATE: 2016.10.19 aoyama
 * *********************************** */
class MypageFriendController extends MypageCloseCommonControllerFrame {

	private $sGroup;
	private $public_user_data;

	/* Constructor */
	public function __construct() {

		parent::__construct();
		$this->sGroup = CONF::read('LOGIN_CATEGORY.PUBLIC');
		//セッションからユーザ情報を取得
		$this->public_user_data = SESSION::read(CONF::read('LOGIN_CATEGORY.PUBLIC'));

		//プロフィールリンク用に
		$this->set("user_link", "/profile/?uid=" . $this->public_user_data['system_id']);

		$this->set("page_group", "community");
	}

	/*	 * **********************************
	 * NAME  : search
	 * INPUT : NONE
	 * OUTPUT: NONE
	 * DESC  :
	 * 		mypageのフレンド検索一覧情報をviewに渡すメソッド
	 * NOTICE:
	 * CREATE: 2017.2.10 aoyama
	 * *********************************** */
	public function search() {

		// 表示に必要な情報をセット
		$this->set("nickname", $this->public_user_data['nickname']);
		$this->set("system_id", $this->public_user_data['system_id']);
		$this->set("system_user_id", $this->public_user_data['system_user_id']);


		//フレンドリストを表示
		$friend = new UserMatchModel();
		$image = new Image();

		//ファッション系統タイトル
		if ($this->public_user_data['fashion_id'] == 0) {
			$fashion_title = 'ファッション系統を選択していないユーザー';
		} else {
			//ファッション系統の配列を取得してvuewに渡す
			$fashionMaster = new FashionTypeMasterModel();
			$this->fashionMasterArray = $fashionMaster->get_basic_data();
			$fashion_title = 'ファッション系統「' . $this->fashionMasterArray[$this->public_user_data['fashion_id']] . '」のユーザー';
		}
		$this->set("friendFashionTitle", $fashion_title);

		//ファッション一覧用
		$friendFashionList = $friend->get_friend_list_fashion($this->public_user_data['user_id'], $this->public_user_data['fashion_id'], null);
		$friendFashionArray = array();
		if (!StaticFunction::is_empty($friendFashionList)) {
			foreach ($friendFashionList AS $value) {

				$friendFashionArray[] = array(
					"nickname" => $value['show_nickname'],
					"system_id" => $value['show_system_id'],
					"friend_count" => $value['show_friend_count'],
					"avatar" => $image->get_avatar_url($value['show_system_id'])
				);
			}
		}
		$this->set("friendFashionArray", $friendFashionArray);

		//ブランド一覧用 未入力時は検索しない
		$this->set("friendBrandTitle", $this->public_user_data['like_brand']);
		if (!StaticFunction::is_empty($this->public_user_data['like_brand'])) {
			$friendBrandList = $friend->get_friend_list_fashion($this->public_user_data['user_id'], "", $this->public_user_data['like_brand']);
			$friendBrandArray = array();
			if (!StaticFunction::is_empty($friendBrandList)) {
				foreach ($friendBrandList AS $value) {

					$friendBrandArray[] = array(
						"nickname" => $value['show_nickname'],
						"system_id" => $value['show_system_id'],
						"friend_count" => $value['show_friend_count'],
						"avatar" => $image->get_avatar_url($value['show_system_id'])
					);
				}
			}
			$this->set("friendBrandArray", $friendBrandArray);
		}

		//フレンド総数を取得
//		$frined_num = $friend->get_friend_num($this->public_user_data['user_id']);
		//ページング出力
//		$page = new PAGING();
//		$this->set("pageng_html", $page->make_paging($frined_num));
		//フレンドリストを表示（左カラム用）
		$friendList = $friend->get_friend_list($this->public_user_data['user_id'], 0, 5, 'commit');

		$friendArray = array();
		if (!StaticFunction::is_empty($friendList)) {
			foreach ($friendList AS $value) {

				$friendArray[] = array(
					"nickname" => $value['nickname'],
					"system_id" => $value['system_id'],
					"avatar" => $image->get_avatar_url($value['system_id'])
				);
			}
		}
		$this->set("friendArray", $friendArray);
	}

	/*	 * **********************************
	 * NAME  : index
	 * INPUT : NONE
	 * OUTPUT: NONE
	 * DESC  :
	 * 		mypageのフレンド一覧情報をviewに渡すメソッド
	 * 			commit:フレンド状態
	 * 			request:$user_idが申請している状態
	 * 			confirm:$user_idの承認待ち状態
	 * NOTICE:
	 * CREATE: 2016.10.19 aoyama
	 * UPDATE: 2016.10.26 aoyama
	 * 		承認ボタンを設置
	 * *********************************** */
	public function index() {

		// 表示に必要な情報をセット
		$this->set("nickname", $this->public_user_data['nickname']);
		$this->set("system_id", $this->public_user_data['system_id']);
		$this->set("system_user_id", $this->public_user_data['system_user_id']);


		//フレンドリストを表示
		$friend = new UserMatchModel();
		$image = new Image();

		//一覧用
		//ページ指定文字のサニタイズ
		$pd = (InputVali::is_num(REQUEST::get_data('pd'))) ? REQUEST::get_data('pd') : 0;
		$pp = (InputVali::is_num(REQUEST::get_data('pp'))) ? REQUEST::get_data('pp') : CONF::read('PAGING.DEFAULT_NUM_PUBLIC');

		$friendAllList = $friend->get_friend_list($this->public_user_data['user_id'], $pd, $pp);
		if (!StaticFunction::is_empty($friendAllList)) {
			foreach ($friendAllList AS $value) {

				$friendAllArray[] = array(
					"match_id" => $value['match_id'],
					"nickname" => $value['nickname'],
					"system_id" => $value['system_id'],
					"friend_count" => $value['friend_count'],
					"friend_status" => $value['friend_status'],
					"avatar" => $image->get_avatar_url($value['system_id'])
				);
			}
		}
		$this->set("friendAllArray", $friendAllArray);

		//フレンド総数を取得
		$frined_num = $friend->get_friend_num($this->public_user_data['user_id']);

		//ページング出力
		$page = new PAGING();
		$this->set("pageng_html", $page->make_paging($frined_num));


		//フレンドリストを表示
		$friend = new UserMatchModel();
		$friendList = $friend->get_friend_list($this->public_user_data['user_id'], 0, 5, 'commit');

		$friendArray = array();
		if (!StaticFunction::is_empty($friendList)) {
			foreach ($friendList AS $value) {

				$friendArray[] = array(
					"nickname" => $value['nickname'],
					"system_id" => $value['system_id'],
					"avatar" => $image->get_avatar_url($value['system_id'])
				);
			}
		}
		$this->set("friendArray", $friendArray);
	}

	/*	 * **********************************
	 * NAME  : complete
	 * INPUT : NONE
	 * OUTPUT: NONE
	 * DESC  :
	 * 		フレンド申請を承認するメソッド
	 * NOTICE:
	 * CREATE: 2016.10.26 aoyama
	 * *********************************** */
	public function complete() {

		//フレンドリストを表示
		$friend = new UserMatchModel();
		$message = new MypageMessageModel();

		$match_id = REQUEST::get_data('fid');

		if (!StaticFunction::is_empty($match_id) && InputVali::is_num($match_id)) {

			$matchArray = $friend->select(
				array(
				"user_id"
				), array(
				"WHERE" => array(
					"match_id" => $match_id
				)
				)
			);

			$message_text = "フレンド申請を承認しました。";

			//1件以上更新されたのでメッセージを送信する
			if ($friend->set_friend_commit($this->public_user_data['user_id'], $match_id)) {
				$message->send_message($this->public_user_data['user_id'], $matchArray[0]['user_id'], $message_text);

				//各人のカウントを更新
				$friend->set_friend_count($this->public_user_data['user_id']);
				$friend->set_friend_count($matchArray[0]['user_id']);
			}
		}

		//フレンド一覧へリダイレクト
		$this->redirect(CONF::read('URL_PUBLIC_ROOT') . "mypage/friend/");
	}

}

?>
