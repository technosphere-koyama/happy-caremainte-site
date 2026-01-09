<?php

/* * **********************************
 * NAME:MypageCommunityController
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
 * CREATE: 2016.10.24 aoyama
 * *********************************** */
class MypageCommunityController extends MypageCloseCommonControllerFrame {

	private $sGroup;
	private $public_user_data;

	/* Constructor */
	public function __construct() {

		parent::__construct();
		$this->sGroup = CONF::read('LOGIN_CATEGORY.PUBLIC');
		//セッションからユーザ情報を取得
		$this->public_user_data = SESSION::read(CONF::read('LOGIN_CATEGORY.PUBLIC'));

		$this->set("page_group", "community");
	}

	/*	 * **********************************
	 * NAME  : exec
	 * INPUT : NONE
	 * OUTPUT: NONE
	 * DESC  :
	 *  マイページのトップ画面アクセスした際にフロントより実行されるメソッド
	 * NOTICE:
	 * CREATE: 2016.10.24 aoyama
	 * *********************************** */
	public function index() {

		// 表示に必要な情報をセット
		$this->set("nickname", $this->public_user_data['nickname']);
		$this->set("system_id", $this->public_user_data['system_id']);
		$this->set("system_user_id", $this->public_user_data['system_user_id']);

		//フレンドリストを表示
		$image = new Image();
		$friend = new UserMatchModel();
		$friendList = $friend->get_friend_list($this->public_user_data['user_id'],0,5,'commit');

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
		
		$community = new CommunityModel();

		//一覧用
		//ページ指定文字のサニタイズ
		$pd = (InputVali::is_num(REQUEST::get_data('pd'))) ? REQUEST::get_data('pd') : 0;
		$pp = (InputVali::is_num(REQUEST::get_data('pp'))) ? REQUEST::get_data('pp') : CONF::read('PAGING.DEFAULT_NUM_PUBLIC');

		$communityAllList = $community->get_thread_from_user($this->public_user_data['user_id'], $pd, $pp);
		$communityAllArray = array();
		if (!StaticFunction::is_empty($communityAllList)) {
			foreach ($communityAllList AS $value) {

				$communityAllArray[] = array(
					"community_link" => "/community/detail.html?tid=".$value['thread_id'],
					"community_name" => $value['community_name'],
					"community_detail" => $value['community_detail'],
					"category_name" => $value['category_name'],
					"category_link" => $value['category_name'],
					"join_count" => $value['join_count'],
					"avatar" => $image->get_avatar_thread_url($value['thread_id'],$value['image_file'])
				);
			}
		}
		$this->set("communityAllArray", $communityAllArray);

		//参加コミュニティ総数を取得
		$thread_num = $community->get_thread_num_from_user($this->public_user_data['user_id']);
		
		//ページング出力
		$page = new PAGING();
		$this->set("pageng_html", $page->make_paging($thread_num));
	}
}
?>
