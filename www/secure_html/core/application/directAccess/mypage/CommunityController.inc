<?php

/* * **********************************
 * NAME:MypageController
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
class CommunityController extends MypageCloseCommonControllerFrame {

	private $sGroup;
	private $sGroupResponse;
	private $public_user_data;
	private $comunityCategoryArray;

	private $comm;
	private $is_admin;
    private $is_comm_admin;

	/* Constructor */
	public function __construct() {

		parent::__construct();

		//セッショングループを設定
		$this->sGroup = 'community';
		$this->sGroupResponse = 'response';

		//セッションからユーザ情報を取得
		$this->public_user_data = SESSION::read(CONF::read('LOGIN_CATEGORY.PUBLIC'));

		//プロフィールリンク用に
		$this->set("user_link", "/profile/?uid=" . $this->public_user_data['system_id']);

		//コミュニティカテゴリ（固定）を取得し配列に。
		$com = new CommunityModel();
		$this->comunityCategoryArray = $com->get_category_list();

		$this->set("comunityCategoryArray", $this->comunityCategoryArray);
        $communityCategoryArrayRet[0] = array(
        	'category_name' => "新着",
            'category_icon'    => "/_assets/img/mypage/ico_category01.gif",
            'category_url'    => "/community/",
			'is_active'     => (empty($this->get_data['c'])) ? "active" : ""
	    );

        foreach($this->comunityCategoryArray AS $ccaKey => $ccaVal) {
            $communityCategoryArrayRet[$ccaKey] = array(
                'category_name'    => $ccaVal,
                'category_icon'    => "/_assets/img/mypage/ico_category".sprintf('%02d', $ccaKey+1).".gif",
                'category_url'    => "/community/?c=".$ccaKey,
                'is_active'        => ($ccaKey == REQUEST::get_data('c')) ? "active" : ""
            );
        }
        $this->set("communityCategoryParentArray", $communityCategoryArrayRet);

		$this->comm = new CommunityModel();
	}

	/*	 * **********************************
	 * NAME  : index
	 * INPUT : NONE
	 * OUTPUT: NONE
	 * DESC  :
	 *  コミュニティTOPを表示するメソッド
	 * NOTICE:
	 * CREATE: 2016.10.19 aoyama
	 * UPDATE: 2016.10.26 aoyama
	 * 		カテゴリ検索を実装
	 * *********************************** */
	public function index() {

		$community = new CommunityModel();
		$image = new Image();

		$category = "";
		if (InputVali::is_array_key(REQUEST::get_data('c'), $this->comunityCategoryArray)) {
			$category = (InputVali::is_num(REQUEST::get_data('c'))) ? REQUEST::get_data('c') : null;
			$this->set("category_view", "カテゴリ：" . $this->comunityCategoryArray[REQUEST::get_data('c')]);
		}

        // トップコミュニティ一覧用
        $topCommArray = $this->getTopCommList();
        $this->set("top_community_array",$topCommArray);

        /* 自身が参加しているコミュニティの配列をviewに渡す */
        $thread_ids = array();
        foreach ($topCommArray AS $tlValue) {
            $thread_ids[] = $tlValue['thread_id'];
        }
        $this->set("community_match", $community->get_community_match_user($thread_ids,$this->public_user_data['user_id']));


		//一覧用
		//ページ指定文字のサニタイズ
		$pd = (InputVali::is_num(REQUEST::get_data('pd'))) ? REQUEST::get_data('pd') : 0;
		$pp = (InputVali::is_num(REQUEST::get_data('pp'))) ? REQUEST::get_data('pp') : CONF::read('PAGING.DEFAULT_NUM_PUBLIC');

		$communityAllList = $community->get_thread_list($pd, $pp, $category);

		$communityAllArray = array();
		if (!StaticFunction::is_empty($communityAllList)) {
			foreach ($communityAllList AS $value) {

				$communityAllArray[] = array(
					"thread_id" => $value['thread_id'],
					"community_name" => $value['community_name'],
					"community_detail" => $value['community_detail'],
					"category_id" => $value['category_id'],
					"category_name" => $this->comunityCategoryArray[$value['category_id']],
                    "topcom" => ($value['topcom_flg'] == 1) ? '<span class="top-community">&lt;トップコミュニティ&gt;</span>' : "",
					"avatar" => $image->get_avatar_thread_url($value['thread_id'], $value['image_file'])
				);
			}
		}
		$this->set("communityAllArray", $communityAllArray);

		//コミュニティ総数を取得
		$community_num = $community->get_thread_num($category);

		//ページング出力
		$page = new PAGING();
		$this->set("pageng_html", $page->make_paging($community_num));
	}

	/*	 * **********************************
	 * NAME  : leave
	 * INPUT : NONE
	 * OUTPUT: NONE
	 * DESC  :
	 *  コミュニティ退出を確認するメソッド
	 * NOTICE:
	 * CREATE: 2016.10.20 aoyama
	 * *********************************** */
	public function leave() {

		$community = new CommunityModel();

		//コミュニティの詳細を取得する
		$thread = $community->get_detail_by_id(REQUEST::get_data('tid'));

		if (StaticFunction::is_empty($thread)) {
			$this->set("error", "ご指定のコミュニティが見つかりません。");
			return;
		}

		//画面表示処理
		$image = new Image();

		//コミュニティ参加人数を取得
		$match_num = $community->match_num(REQUEST::get_data('tid'));

		//コミュニティメンバーリストを取得
		$match_array = $community->get_match_list(REQUEST::get_data('tid'));
		$match_array_view = array();
		foreach ($match_array AS $values) {
			$match_array_view[] = array(
				"system_id" => $values['system_id'],
				"nickname" => $values['nickname'],
				"avatar" => $image->get_avatar_url($values['system_id'])
			);
		}

		// 表示に必要な情報をセット
		$this->set("thread_id", $thread[0]['thread_id']);
		$this->set("community_name", $thread[0]['community_name']);
		$this->set("community_detail", $thread[0]['community_detail']);
		$this->set("category_id", $thread[0]['category_id']);
		$this->set("category_name", $this->comunityCategoryArray[$thread[0]['category_id']]);
		$this->set("user_id", $thread[0]['user_id']);
		$this->set("system_id", $thread[0]['system_id']);
		$this->set("nickname", $thread[0]['nickname']);
		$this->set("avatar", $image->get_avatar_thread_url($thread[0]['thread_id'], $thread[0]['image_file']));
		$this->set("avatar_user", $image->get_avatar_url($thread[0]['system_id']));
		$this->set("match_num", StaticFunction::count_num_format($match_num) . '人');
		$this->set("match_array", $match_array_view);

		//自分のスレッドの場合は解除できない。
		if ($this->public_user_data['user_id'] == $thread[0]['user_id']) {
			$this->set("error", "管理者は退出できません。");
			return;
		}

		//登録済みかチェック。
		if (!$community->registered_community($this->public_user_data['user_id'], REQUEST::get_data('tid'))) {

			$this->set("error", "既に退出されています。");
			return;
		}
	}

	/*	 * **********************************
	 * NAME  : leave_complete
	 * INPUT : 
	 * OUTPUT: 
	 * DESC  :
	 *  コミュニティを退出するメソッド
	 * NOTICE:
	 * CREATE: 2016.10.20 aoyama
	 * *********************************** */
	public function leave_complete() {

		$community = new CommunityModel();

		//コミュニティの詳細を取得する
		$thread = $community->get_detail_by_id(REQUEST::get_data('tid'));

		if (StaticFunction::is_empty($thread)) {
			$this->set("error", "ご指定のコミュニティが見つかりません。");
			return;
		}

		// 画面表示処理
		$image = new Image();

		//コミュニティ参加人数を取得
		$match_num = $community->match_num(REQUEST::get_data('tid'));

		//コミュニティメンバーリストを取得
		$match_array = $community->get_match_list(REQUEST::get_data('tid'));
		$match_array_view = array();
		foreach ($match_array AS $values) {
			$match_array_view[] = array(
				"system_id" => $values['system_id'],
				"nickname" => $values['nickname'],
				"avatar" => $image->get_avatar_url($values['system_id'])
			);
		}

		// 表示に必要な情報をセット
		$this->set("thread_id", $thread[0]['thread_id']);
		$this->set("community_name", $thread[0]['community_name']);
		$this->set("community_detail", $thread[0]['community_detail']);
		$this->set("category_id", $thread[0]['category_id']);
		$this->set("category_name", $this->comunityCategoryArray[$thread[0]['category_id']]);
		$this->set("user_id", $thread[0]['user_id']);
		$this->set("system_id", $thread[0]['system_id']);
		$this->set("nickname", $thread[0]['nickname']);
		$this->set("avatar", $image->get_avatar_thread_url($thread[0]['thread_id'], $thread[0]['image_file']));
		$this->set("avatar_user", $image->get_avatar_url($thread[0]['system_id']));
		$this->set("match_num", StaticFunction::count_num_format($match_num) . '人');
		$this->set("match_array", $match_array_view);

		// 自分のスレッドの場合は解除できない。
		if ($this->public_user_data['user_id'] == $thread[0]['user_id']) {
			$this->set("error", "管理者は退出できません。");
			return;
		}

		// 登録済みかチェック。
		if (!$community->registered_community($this->public_user_data['user_id'], REQUEST::get_data('tid'))) {
			$this->set("error", "既に退出されています。");
			return;
		}

		// コミュニティ退出処理
		if ($community->leave_community($this->public_user_data['user_id'], REQUEST::get_data('tid'))) {
			//問題なければ確認画面へ
			$this->redirect("/community/detail.html?tid=" . REQUEST::get_data('tid'));
		}

		$this->set("error", "退出処理処理が完了しませんでした。");
		return;
	}

	/*	 * **********************************
	 * NAME  : edit
	 * INPUT : NONE
	 * OUTPUT: NONE
	 * DESC  :
	 *  コミュニティTOPを編集するメソッド
	 * NOTICE:
	 * CREATE: 2016.12.21 aoyama
	 * *********************************** */
	public function edit() {

        $community = new CommunityModel();

		//コミュニティの詳細を取得する
		$thread = $community->get_detail_by_id(REQUEST::get_data('tid'));

		// コミュニティが見つからない場合は新規作成にリダイレクト
		if (StaticFunction::is_empty($thread)) {
            $this->redirect("/community/form.html");
		}

        // 管理者状態をviewに渡す
        $this->is_comm_admin = $community->is_community_admin($this->public_user_data['user_id'],REQUEST::get_data('tid'));
        $this->set("is_comm_admin", $this->is_comm_admin);

		//自分の投稿かチェック→admin権限がなければ新規作成にリダイレクト
		if (!$this->is_comm_admin) {
            $this->redirect("/community/form.html");
		}

        // 関連ユーザーリストをviewに渡す
        $list_comm_author = $community->list_comm_author(REQUEST::get_data('tid'));
        $g_author = array();
		foreach($list_comm_author AS $val) {
		    $g_author[$val['group_id']][] = array(
		        'system_user_id' => $val['system_user_id'],
                'nickname' => $val['nickname']
            );
        }
        $this->set("list_comm_author", $g_author);


        // 関連ユーザーグループリストをviewに渡す
        $list_comm_author_group = $community->list_comm_author_group(REQUEST::get_data('tid'));

        $this->set("list_comm_author_group", $list_comm_author_group);

        $user = new UserPublicModel();
        $owner_array = $user->get_user_detail_by_user_id($thread[0]['topcom_owner_user_id']);

		$this->set("tid", REQUEST::get_data('tid'));
		$this->set("name", $thread[0]['community_name']);
		$this->set("category", $thread[0]['category_id']);
		$this->set("comment", $thread[0]['community_detail']);
		$this->set("file", $thread[0]['image_file']);
        $this->set("topcom_flg", $thread[0]['topcom_flg']);
        $this->set("topcom_owner_system_id", $owner_array[0]['system_user_id']);
        $this->set("topcom_description", $thread[0]['topcom_description']);
        $this->set("topcom_url", $thread[0]['topcom_url']);
        $this->set("topcom_twitter", $thread[0]['topcom_twitter']);
        $this->set("topcom_facebook", $thread[0]['topcom_facebook']);
        $this->set("topcom_instagram", $thread[0]['topcom_instagram']);
        $this->set("topcom_youtube", $thread[0]['topcom_youtube']);

		if (!StaticFunction::is_empty(SESSION::read($this->sGroup . '.error_array'))) {
			$this->set("error_array", SESSION::read($this->sGroup . '.error_array'));
			SESSION::delete($this->sGroup . '.error_array');
		}
		$this->formReturn();
		//リターンしたのでセッションは消す。
		SESSION::delete($this->sGroup);
	}

	/*	 * **********************************
	 * NAME  : edit_complete
	 * INPUT : NONE
	 * OUTPUT: NONE
	 * DESC  :
	 *  コミュニティTOPを編集するメソッド
	 * NOTICE:
	 * CREATE: 2016.12.21 aoyama
	 * *********************************** */
	public function edit_complete() {

		$community = new CommunityModel();

		//コミュニティの詳細を取得する
		$thread = $community->get_detail_by_id(REQUEST::post_data('tid'));

		if (StaticFunction::is_empty($thread)) {
            $this->redirect("/community/form.html");
		}

		//自分の投稿かチェック→admin権限かチェック
        $this->is_comm_admin = $community->is_community_admin($this->public_user_data['user_id'],REQUEST::post_data('tid'));
		if (!$this->is_comm_admin) {
            $this->redirect("/community/form.html");
		}

		// POSTデータがある場合、セッションに登録する。
		if (!StaticFunction::is_empty(REQUEST::post_data())) {

			SESSION::write($this->sGroup . '.tid', REQUEST::post_data('tid'));
			SESSION::write($this->sGroup . '.name', REQUEST::post_data('name'));
			SESSION::write($this->sGroup . '.category', REQUEST::post_data('category'));
			SESSION::write($this->sGroup . '.comment', REQUEST::post_data('comment'));
			SESSION::write($this->sGroup . '.file', true);
            SESSION::write($this->sGroup . '.topcom_owner_system_id', REQUEST::post_data('topcom_owner_system_id'));
            SESSION::write($this->sGroup . '.topcom_description', REQUEST::post_data('topcom_description'));
            SESSION::write($this->sGroup . '.topcom_flg', REQUEST::post_data('topcom_flg'));
            SESSION::write($this->sGroup . '.topcom_file', true);
            SESSION::write($this->sGroup . '.topcom_url', REQUEST::post_data('topcom_url'));
            SESSION::write($this->sGroup . '.topcom_twitter', REQUEST::post_data('topcom_twitter'));
            SESSION::write($this->sGroup . '.topcom_facebook', REQUEST::post_data('topcom_facebook'));
            SESSION::write($this->sGroup . '.topcom_instagram', REQUEST::post_data('topcom_instagram'));
            SESSION::write($this->sGroup . '.topcom_youtube', REQUEST::post_data('topcom_youtube'));

			//アバター登録がある場合
			if ($_FILES['avatar']['error'] == UPLOAD_ERR_OK) {

				$thumb = new Image();

				//一時画像ファイル名を生成
				$avatar_tmp_hash = Encrypt::member_regist_token($_SERVER['REMOTE_ADDR'], time());

				//ロード
				if (!$ret = $thumb->load($_FILES['avatar']['tmp_name'])) {
					SESSION::write($this->sGroup . '.file', false);
				} else {
					//拡張子取得
					$thumb_ext = $thumb->get_image_type();

					//リサイズ
					$thumb->resize_avatar(CONF::read("AVATAR.WIDTH"));

					//ファイル名
					$date_dir = DbDateTime::fairing_digit_8(DbDateTime::get_cur_datetime());
					$tmp_file_name = $avatar_tmp_hash . '.jpg';

					//tmp保存先システムディレクトリ[/public/images/tmp/日付]
					$avatar_tmp_dir = DIR_SYSTEM_IMG_TMP . DS . $date_dir . DS;

					//tmpディレクトリに保存
					$ret = $thumb->save_jpeg($avatar_tmp_dir, $tmp_file_name);

					SESSION::write($this->sGroup . '.tmp_avatar', $tmp_file_name);
					SESSION::write($this->sGroup . '.tmp_avatar_date', $date_dir);
				}
			}

            //トップコミュニティ背景画像登録がある場合
            if ($_FILES['topcom_image_file']['error'] == UPLOAD_ERR_OK) {

                $thread_bg = new Image();

                //一時画像ファイル名を生成
                $thread_bg_tmp_hash = Encrypt::member_regist_token($_SERVER['REMOTE_ADDR']."topcom", time());

                //ロード
                if (!$bg = $thread_bg->load($_FILES['topcom_image_file']['tmp_name'])) {
                    SESSION::write($this->sGroup . '.topcom_file', false);
                } else {
                    //リサイズ
                    $thread_bg->resize("3000");

                    //tmpファイル名
                    $date_dir = DbDateTime::fairing_digit_8(DbDateTime::get_cur_datetime());
                    $tmp_file_name = $thread_bg_tmp_hash . '.jpg';

                    //tmp保存先システムディレクトリ[/public/images/tmp/日付]
                    $thread_bg_tmp_dir = DIR_SYSTEM_IMG_TMP . DS . $date_dir . DS;

                    //tmpディレクトリに保存
                    $bg = $thread_bg->save_jpeg($thread_bg_tmp_dir, $tmp_file_name);

                    SESSION::write($this->sGroup . '.tmp_thread_bg', $tmp_file_name);
                    SESSION::write($this->sGroup . '.tmp_thread_bg_date', $date_dir);
                }
            }
		}

		// バリデーション
		$error_array = $this->checkSessionParameter();
		if (!StaticFunction::is_empty($error_array)) {
			SESSION::write($this->sGroup . '.error_array', $error_array);
			$this->redirect("/community/edit.html?tid=" . SESSION::read($this->sGroup . '.tid'));
		}

		$datetime = DbDateTime::get_cur_datetime();


		// トップコミュニティの管理者表示アカウントに入力があった場合はuser_idを参照する
        if(!StaticFunction::is_empty(SESSION::read($this->sGroup . '.topcom_owner_system_id'))){
            $user = new UserPublicModel();
            $topcom_owner_user = $user->verification(SESSION::read($this->sGroup . '.topcom_owner_system_id'));
        }

		// スレッド更新処理
		// 配列にPOSTデータを格納
		$param_array = array(
			"tid" => SESSION::read($this->sGroup . '.tid'),
			"community_name" => SESSION::read($this->sGroup . '.name'),
			"community_detail" => SESSION::read($this->sGroup . '.comment'),
			"category_id" => SESSION::read($this->sGroup . '.category'),
			"image_file" => SESSION::read($this->sGroup . '.tmp_avatar'),
            "topcom_owner_user_id" => $topcom_owner_user[0]['user_id'],
            "topcom_description" => (SESSION::read($this->sGroup . '.topcom_description')),
            "topcom_url" => (SESSION::read($this->sGroup . '.topcom_url')),
            "topcom_twitter" => (SESSION::read($this->sGroup . '.topcom_twitter')),
            "topcom_facebook" => (SESSION::read($this->sGroup . '.topcom_facebook')),
            "topcom_instagram" => (SESSION::read($this->sGroup . '.topcom_instagram')),
            "topcom_youtube" => (SESSION::read($this->sGroup . '.topcom_youtube')),
			'update_time' => $datetime
		);

		// トップコミュニティで添付画像がある場合
        if (!StaticFunction::is_empty(SESSION::read($this->sGroup . '.tmp_thread_bg'))) {
            $param_array += array('topcom_image_file' => SESSION::read($this->sGroup . '.tmp_thread_bg'));
        }

//        var_dump($param_array);
//        exit;

		/* DB登録エラー */
		if (!$community->update_thread($param_array)) {
			$error_array[] = array("message" => "コミュニティ編集に失敗しました。");
			SESSION::write($this->sGroup . '.error_array', $error_array);
			$this->redirect("/community/edit.html?tid=" . SESSION::read($this->sGroup . '.tid'));
		}

		//アバター画像がある場合は画像をコミュニティディレクトリに移動
		if (!StaticFunction::is_empty(SESSION::read($this->sGroup . '.tmp_avatar'))) {

			$img = new Image();
			$ret = $img->set_thread_avatar_public(SESSION::read($this->sGroup . '.tmp_avatar_date'),
				SESSION::read($this->sGroup . '.tmp_avatar'), SESSION::read($this->sGroup . '.tid'));

			//失敗時
			if (!$ret) {
				//失敗時はアラートメール送信
			}
		}
        //トップコミュニティの背景画像がある場合は画像をコミュニティディレクトリに移動
        if (!StaticFunction::is_empty(SESSION::read($this->sGroup . '.tmp_thread_bg'))) {

            $img = new Image();
            $ret = $img->set_thread_bg_public(SESSION::read($this->sGroup . '.tmp_thread_bg_date'),
				SESSION::read($this->sGroup . '.tmp_thread_bg'), SESSION::read($this->sGroup . '.tid'));
            //失敗時
            if (!$ret) {
                //失敗時はアラートメール送信
            }
        }
		//正常終了時はセッションを削除
		$tid = SESSION::read($this->sGroup . '.tid');
		SESSION::delete($this->sGroup);

		$this->redirect("/community/detail.html?tid=" . $tid);
	}

	/*	 * **********************************
	 * NAME  : form
	 * INPUT : NONE
	 * OUTPUT: NONE
	 * DESC  :
	 *  コミュニティTOPを表示するメソッド
	 * NOTICE:
	 * CREATE: 2016.10.19 aoyama
	 * UPDATE: 2017.08.06 aoyama
	 *   管理者権限の判定を追加
	 * *********************************** */
	public function form() {

        $community = new CommunityModel();

        $this->is_admin = $community->is_admin($this->public_user_data['user_id']);
        $this->set("is_admin", $this->is_admin);

		// POSTデータがある場合、セッションに登録する。
		if (!StaticFunction::is_empty(REQUEST::post_data())) {

			SESSION::write($this->sGroup . '.name', REQUEST::post_data('name'));
			SESSION::write($this->sGroup . '.category', REQUEST::post_data('category'));
			SESSION::write($this->sGroup . '.comment', REQUEST::post_data('comment'));
			SESSION::write($this->sGroup . '.file', true);
            SESSION::write($this->sGroup . '.topcom_flg', REQUEST::post_data('topcom_flg'));
            SESSION::write($this->sGroup . '.topcom_description', REQUEST::post_data('topcom_description'));
            SESSION::write($this->sGroup . '.topcom_file', true);
            SESSION::write($this->sGroup . '.topcom_url', REQUEST::post_data('topcom_url'));
            SESSION::write($this->sGroup . '.topcom_twitter', REQUEST::post_data('topcom_twitter'));
            SESSION::write($this->sGroup . '.topcom_facebook', REQUEST::post_data('topcom_facebook'));
            SESSION::write($this->sGroup . '.topcom_instagram', REQUEST::post_data('topcom_instagram'));
            SESSION::write($this->sGroup . '.topcom_youtube', REQUEST::post_data('topcom_youtube'));

			//アバター登録がある場合
			if ($_FILES['avatar']['error'] == UPLOAD_ERR_OK) {

				$thumb = new Image();

				//一時画像ファイル名を生成
				$avatar_tmp_hash = Encrypt::member_regist_token($_SERVER['REMOTE_ADDR']."avatar", time());

				//ロード
				if (!$ret = $thumb->load($_FILES['avatar']['tmp_name'])) {
					SESSION::write($this->sGroup . '.file', false);
				} else {
					//拡張子取得
					$thumb_ext = $thumb->get_image_type();

					//リサイズ
					$thumb->resize_avatar(CONF::read("AVATAR.WIDTH"));

					//ファイル名
					$date_dir = DbDateTime::fairing_digit_8(DbDateTime::get_cur_datetime());
					$tmp_file_name = $avatar_tmp_hash . '.jpg';

					//tmp保存先システムディレクトリ[/public/images/tmp/日付]
					$avatar_tmp_dir = DIR_SYSTEM_IMG_TMP . DS . $date_dir . DS;

					//tmpディレクトリに保存
					$ret = $thumb->save_jpeg($avatar_tmp_dir, $tmp_file_name);

					SESSION::write($this->sGroup . '.tmp_avatar', $tmp_file_name);
					SESSION::write($this->sGroup . '.tmp_avatar_date', $date_dir);
				}
			}

            //アバター登録がある場合
            if ($_FILES['topcom_image_file']['error'] == UPLOAD_ERR_OK) {

                $thread_bg = new Image();

                //一時画像ファイル名を生成
                $thread_bg_tmp_hash = Encrypt::member_regist_token($_SERVER['REMOTE_ADDR']."topcom", time());

                //ロード
                if (!$bg = $thread_bg->load($_FILES['topcom_image_file']['tmp_name'])) {
                    SESSION::write($this->sGroup . '.topcom_file', false);
                } else {
                    //リサイズ
                    $thread_bg->resize("1000");

                    //tmpファイル名
                    $date_dir = DbDateTime::fairing_digit_8(DbDateTime::get_cur_datetime());
                    $tmp_file_name = $thread_bg_tmp_hash . '.jpg';

                    //tmp保存先システムディレクトリ[/public/images/tmp/日付]
                    $thread_bg_tmp_dir = DIR_SYSTEM_IMG_TMP . DS . $date_dir . DS;

                    //tmpディレクトリに保存
                    $bg = $thread_bg->save_jpeg($thread_bg_tmp_dir, $tmp_file_name);

                    SESSION::write($this->sGroup . '.tmp_thread_bg', $tmp_file_name);
                    SESSION::write($this->sGroup . '.tmp_thread_bg_date', $date_dir);
                }
            }

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
	 * CREATE: 2016.10.19 aoyama
	 * *********************************** */
	public function confirm() {

		$community = new CommunityModel();
        $this->is_admin = $community->is_admin($this->public_user_data['user_id']);
        $this->set("is_admin", $this->is_admin);

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

		if (!StaticFunction::is_empty(SESSION::read($this->sGroup))) {

			/*
			 * バリデーション:エラーのときはindex.htmlに飛ばす
			 * indexのcheckSessionParameterとエラー情報の渡し方が異なる理由として
			 * ここでバリデーションに引っかかるということは予期しないアクセスなので
			 * そこまで親切にしなくてもいいかなと。(aoyama)
			 */


			$error_array = $this->checkSessionParameter();
			if (!StaticFunction::is_empty($error_array)) {
				$this->redirect("./");
			} else {

				$datetime = DbDateTime::get_cur_datetime();
				// スレッド登録処理
				// 配列にPOSTデータを格納
				$param_array = array(
					"community_name" => DbCast::string(SESSION::read($this->sGroup . '.name')),
					"community_detail" => DbCast::string(SESSION::read($this->sGroup . '.comment')),
					"category_id" => DbCast::string(SESSION::read($this->sGroup . '.category')),
					"image_file" => DbCast::string(SESSION::read($this->sGroup . '.tmp_avatar')),
					'user_id' => DbCast::id($this->public_user_data['user_id']),
                    "topcom_url" => DbCast::string(SESSION::read($this->sGroup . '.topcom_url')),
                    "topcom_twitter" => DbCast::string(SESSION::read($this->sGroup . '.topcom_twitter')),
                    "topcom_facebook" => DbCast::string(SESSION::read($this->sGroup . '.topcom_facebook')),
                    "topcom_instagram" => DbCast::string(SESSION::read($this->sGroup . '.topcom_instagram')),
                    "topcom_youtube" => DbCast::string(SESSION::read($this->sGroup . '.topcom_youtube')),
					'update_time' => DbCast::datetime($datetime),
					'create_time' => DbCast::datetime($datetime),
					"active" => DbCast::float(DB_ACTIVE_ON)
				);

                if (SESSION::read($this->sGroup . '.topcom_flg') == TOPCOM_FLG_ON) {
                    $param_array += array('topcom_flg' => TOPCOM_FLG_ON);
                    //トップコミュニティの背景画像がある場合は画像をコミュニティディレクトリに移動
                    if (!StaticFunction::is_empty(SESSION::read($this->sGroup . '.tmp_thread_bg'))) {
                        $param_array += array('topcom_image_file' => DbCast::string(SESSION::read($this->sGroup . '.tmp_thread_bg')));
                    }
                }

//                var_dump($param_array);
//                exit;


				$community = new CommunityModel();
				/* DB登録エラー */
				if (!$insert_id = $community->post_community($param_array)) {
					$error_array[] = array("message" => "コミュニティ作成に失敗しました。");
					$this->set('error_array', $error_array);
					return;
				}

				//アバター画像がある場合は画像をコミュニティディレクトリに移動
				if (!StaticFunction::is_empty(SESSION::read($this->sGroup . '.tmp_avatar'))) {

					$img = new Image();
					$ret = $img->set_thread_avatar_public(SESSION::read($this->sGroup . '.tmp_avatar_date'), SESSION::read($this->sGroup . '.tmp_avatar'), $insert_id);

					//失敗時
					if (!$ret) {
						//失敗時はアラートメール送信
					}
				}

                //トップコミュニティの背景画像がある場合は画像をコミュニティディレクトリに移動
                if (!StaticFunction::is_empty(SESSION::read($this->sGroup . '.tmp_thread_bg'))) {

                    $img = new Image();
                    $ret = $img->set_thread_bg_public(SESSION::read($this->sGroup . '.tmp_thread_bg_date'), SESSION::read($this->sGroup . '.tmp_thread_bg'), $insert_id);


                    //失敗時
                    if (!$ret) {
                        //失敗時はアラートメール送信
                    }
                }

				//作成者をコミュニティ参加者に登録する
				// 配列にPOSTデータを格納
				$match_array = array(
					'create_time' => DbCast::datetime($datetime),
					'update_time' => DbCast::datetime($datetime),
					"user_id" => DbCast::id($this->public_user_data['user_id']),
					'thread_id' => DbCast::id($insert_id),
					"active" => DbCast::float(DB_ACTIVE_ON)
				);

				if (!$community->entry_community($match_array)) {

					//失敗時はアラートメール送信
				}

				//正常終了時はセッションを削除
				SESSION::delete($this->sGroup);
			}
		} else {
            $this->redirect("/community/");
		}
	}

	/*	 * **********************************
	 * NAME:checkSessionParameter
	 * DESC:
	 * 		スレッドタイトルは20文字以内
	 * NOTICE:
	 * CREATE: 2016.10.19 aoyama
	 * *********************************** */
	private function checkSessionParameter() {

		$error_array = array();

		if (!SESSION::read($this->sGroup . '.file')) {
			$error_array[] = array('target' => 'file', 'message' => '添付できるファイルは画像のみです。');
		}

		if (!InputVali::is_name_thread(SESSION::read($this->sGroup . '.name'))) {
			$error_array[] = array('target' => 'name', 'message' => 'コミュニティ名は20文字以内で入力してください');
		}

		if (!array_key_exists(SESSION::read($this->sGroup . '.category'), $this->comunityCategoryArray)) {
			$error_array[] = array('target' => 'category', 'message' => 'カテゴリーを選んでください。');
		}
        if (!StaticFunction::is_empty(SESSION::read($this->sGroup . '.topcom_description'))) {
            if (!InputVali::is_topcom_description(SESSION::read($this->sGroup . '.topcom_description'))) {
                $error_array[] = array('target' => 'topcom_description', 'message' => 'コミュニティ概要は200文字以内で入力してください。');
            }
        }

		if (!StaticFunction::is_empty(SESSION::read($this->sGroup . '.comment'))) {
			if (!InputVali::is_comment_thread(SESSION::read($this->sGroup . '.comment'))) {
				$error_array[] = array('target' => 'comment', 'message' => 'コミュニティ紹介は00文字以内で入力してください。');
			}
		}

		return $error_array;
	}

	/*	 * **********************************
	 * NAME:formReturn
	 * DESC:
	 *  セッション情報をフォームに渡すためにセットする機能
	 * NOTICE:
	 * CREATE: 2016.10.19 aoyama
	 * *********************************** */
	private function formReturn() {

		// セッションの情報をセットしてviewに渡す
		if (!StaticFunction::is_empty(SESSION::read($this->sGroup))) {
			$this->set("name", SESSION::read($this->sGroup . '.name'));
			$this->set("category", SESSION::read($this->sGroup . '.category'));
			$this->set("category_view", $this->comunityCategoryArray[SESSION::read($this->sGroup . '.category')]);
			$this->set("comment", SESSION::read($this->sGroup . '.comment'));
			$this->set("tmp_avatar", SESSION::read($this->sGroup . '.tmp_avatar'));
			$this->set("tmp_avatar_date", SESSION::read($this->sGroup . '.tmp_avatar_date'));
            $this->set("tmp_thread_bg", SESSION::read($this->sGroup . '.tmp_thread_bg'));
            $this->set("tmp_thread_bg_date", SESSION::read($this->sGroup . '.tmp_thread_bg_date'));
            $this->set("topcom_url", SESSION::read($this->sGroup . '.topcom_url'));
            $this->set("topcom_twitter", SESSION::read($this->sGroup . '.topcom_twitter'));
            $this->set("topcom_facebook", SESSION::read($this->sGroup . '.topcom_facebook'));
            $this->set("topcom_instagram", SESSION::read($this->sGroup . '.topcom_instagram'));
            $this->set("topcom_youtube", SESSION::read($this->sGroup . '.topcom_youtube'));

			if(SESSION::read($this->sGroup . '.topcom_flg') == TOPCOM_FLG_ON) {
				$topcom_flg_view = CONF::read("TOPCOM_FLG.".TOPCOM_FLG_ON);
			} else {
                $topcom_flg_view = CONF::read("TOPCOM_FLG.".TOPCOM_FLG_OFF);
			}
            $this->set("topcom_flg_view", $topcom_flg_view);

		}
	}

	/*	 * **********************************
	 * NAME  : detail
	 * INPUT : NONE
	 * OUTPUT: NONE
	 * DESC  :
	 * 		コミュニティ詳細を表示するメソッド
	 * 		レスポンス（コメント）を投稿するフォームも兼ねる
	 * NOTICE:
	 * CREATE: 2016.10.19 aoyama
	 * UPDATE: 2016.10.31 aoyama
	 * 		いいね用の配列を返す
	 * *********************************** */
	public function detail() {

		$community = new CommunityModel();

		//コミュニティの詳細を取得する
		$thread = $community->get_detail_by_id($this->get_data('tid'));



		if (StaticFunction::is_empty($thread)) {
			$this->set("error", "ご指定のコミュニティが見つかりません。");
			return;
		}

		$tid = $this->get_data('tid');

		//コミュニティ参加ボタンからアクセスされた場合
		if ($this->get_data("mode") == "entry") {
            $this->entry_thread($this->public_user_data['user_id'], $tid);
		}

		//画面表示処理
		$image = new Image();

        // 自分のユーザー情報をviewに渡す（コメントフォームに表示するため）
        $this->set("my_avatar", $image->get_avatar_url($this->public_user_data['system_id']));
        $this->set("my_nickname", $this->public_user_data['nickname']);

        //thread作成者状態をviewに渡す
        $this->set("is_owner_thread", $community->is_owner_thread($this->public_user_data['user_id'],$tid));

		//参加状態をviewに渡す
        $this->set("is_entry", $community->registered_community($this->public_user_data['user_id'], $tid));

		//admin権限状態をviewに渡す（関連ユーザーはtrue）
        $this->set("is_comm_admin", $community->is_community_admin($this->public_user_data['user_id'],$tid));

		//コミュニティ参加人数を取得
		$match_num = $community->match_num($tid);

		//コミュニティメンバーリストを取得
		$match_array = $community->get_match_list($tid);
		$match_array_view = array();
		foreach ($match_array AS $values) {
			$match_array_view[] = array(
				"system_id" => $values['system_id'],
				"nickname" => $values['nickname'],
				"avatar" => $image->get_avatar_url($values['system_id'])
			);
		}

        $is_top_community =  ($thread[0]['topcom_flg']) == 1 ? true : false;
		// 表示に必要な情報をセット
        $this->set("pd",REQUEST::get_data('pd'));
        $this->set("pp",REQUEST::get_data('pp'));
		$this->set("thread_id", $thread[0]['thread_id']);
		$this->set("community_name", $thread[0]['community_name']);
		$this->set("community_detail", $thread[0]['community_detail']);
        $this->set("topcom_description", $thread[0]['topcom_description']);
        $this->set("topcom_url", $thread[0]['topcom_url']);
        $this->set("topcom_twitter", $thread[0]['topcom_twitter']);
        $this->set("topcom_facebook", $thread[0]['topcom_facebook']);
        $this->set("topcom_instagram", $thread[0]['topcom_instagram']);
        $this->set("topcom_youtube", $thread[0]['topcom_youtube']);
		$this->set("category_id", $thread[0]['category_id']);
		$this->set("category_name", $this->comunityCategoryArray[$thread[0]['category_id']]);
		$this->set("user_id", $thread[0]['user_id']);
		$this->set("system_id", $thread[0]['system_id']);
		$this->set("nickname", $thread[0]['nickname']);
		$this->set("avatar", $image->get_avatar_thread_url($thread[0]['thread_id'], $thread[0]['image_file']));
		$this->set("avatar_user", $image->get_avatar_url($thread[0]['system_id']));
		$this->set("match_num", StaticFunction::count_num_format($match_num) . '人');
		$this->set("match_array", $match_array_view);
        $this->set("is_top_community", $is_top_community);
        $this->set("topcom_bg_url", $image->get_avatar_thread_url($thread[0]['thread_id'], $thread[0]['topcom_image_file']));


        // トップコミュニティの場合は関連ユーザーを表示
        if ($thread[0]['topcom_flg'] == 1) {
            
            $user = new UserPublicModel();

            if(!StaticFunction::is_empty($thread[0]['topcom_owner_user_id'])){
                $topcom_owner_user = $user->get_user_detail_by_user_id($thread[0]['topcom_owner_user_id']);
                $this->set("avatar_user", $image->get_avatar_url($topcom_owner_user[0]['system_id']));
                $this->set("system_id", $topcom_owner_user[0]['system_id']);
                $this->set("nickname", $topcom_owner_user[0]['nickname']);
            }

            // 関連ユーザーリストをviewに渡す
            $list_comm_author = $community->list_comm_author($tid);
            $g_author = array();
            foreach ($list_comm_author AS $val) {
                $g_author[$val['group_id']][] = array(
                    "user_link"      => "/profile/?uid=" . $val['system_id'],
                    "avatar"         => $image->get_avatar_url($val['system_id']),
                    'system_user_id' => $val['system_user_id'],
                    'nickname'       => $val['nickname']
                );
            }
            $this->set("list_comm_author", $g_author);

            // 関連ユーザーグループリストをviewに渡す
            $list_comm_author_group = $community->list_comm_author_group($tid);
            $this->set("list_comm_author_group", $list_comm_author_group);

            //管理者のフレンドリストを表示
            $friend = new UserMatchModel();
            $friendList = $friend->get_friend_list($thread[0]['topcom_owner_user_id'],0,5,'commit');

            $friendArray = array();
            if (!StaticFunction::is_empty($friendList)) {
                foreach ($friendList AS $value) {

                    $friendArray[] = array(
                        "nickname" => $value['nickname'],
                        "user_link" => '/profile/?uid='.$value['system_id'],
                        "avatar" => $image->get_avatar_url($value['system_id'])
                    );
                }
            }
            $this->set("friendArray", $friendArray);
        }


		/*
		 * コメント一覧用
		 */
		//ページ指定文字のサニタイズ
		$pd = (InputVali::is_num($this->get_data('pd'))) ? $this->get_data('pd') : 0;
		$pp = (InputVali::is_num($this->get_data('pp'))) ? $this->get_data('pp') : CONF::read('PAGING.DEFAULT_NUM_PUBLIC');

		$responseAllList = $community->get_response_list($thread[0]['thread_id'], $pd, $pp);
		$responseAllArray = array();
        $response_ids = array();
		if (!StaticFunction::is_empty($responseAllList)) {
			foreach ($responseAllList AS $value) {

                // 画像ファイルの表示用配列初期化(2017.2.13 aoyama)
                $file_url = array();

                $file_url = $community->get_community_response_image($value['thread_id'], $value['response_id']);

                if($value['user_id'] == $this->public_user_data['user_id']){
                    $edit_link = "/comunity/response_edit.html?rid=" . $value['response_id'];
                    $is_my_post = true;
                } else {
                    $edit_link = "";
                    $is_my_post = false;
                }

                $responseAllArray[] = array(
                    "response_id"        => $value['response_id'],
                    "thread_id"          => $value['thread_id'],
                    "response_text"      => $value['response_text'],
                    "response_text_view" => StaticFunction::decode_view_text(nl2br($value['response_text'])),
                    "update_time"        => DbDateTime::get_date_type_dot($value['update_time']),
                    "system_id"          => $value['system_id'],
                    "nickname"           => $value['nickname'],
                    "avatar"             => $image->get_avatar_url($value['system_id']),
                    "file_url"           => $file_url,
                    "like_count"         => $value['like_count'],
                    "response_id"        => $value['response_id'],
                    "like_link"          => "/_API/forExternal/likeApi.php?type=response&target_id=" . $value['response_id'],
                    "edit_link"          => $edit_link,
                    "is_my_post"         => $is_my_post
                );
                $response_ids[] = DbCast::integer($value['response_id']);
			}
		}
		$this->set("responseAllArray", $responseAllArray);

		//いいねしているレスポンスの配列を取得
		$like = new LikeModel();
		$like_for_js = $like->get_response_like_own($this->public_user_data['user_id'], $responseAllArray);

		$in_array = array();
		foreach ($like_for_js AS $val) {
			$in_array[] = "'response:" . $val['target_id'] . "'";
		}
        $response_like_array = implode(",", $in_array);
		$this->set("response_like_array", $response_like_array);

		// レスポンスにつけられたコメントを取得
        $comment_array = array();

        $commentList = $community->get_comment_list($response_ids);
        if (!StaticFunction::is_empty($commentList)) {
            foreach ($commentList AS $value) {

                $edit_comment_link = "";
                // 自分のコメントの時はレビューの編集ボタンリンクを設定。これをviewの表示判定にも使用。
                if ($value['user_id'] == $this->public_user_data['user_id']) {
                    $edit_comment_link = "/community/comment_delete.html?comment_id=" . $value['comment_id'];
                    $edit_comment_link .= "&token=" . SESSION::read('EXPIRES.ORIGINAL_TOKEN');
                    $edit_comment_link .= "&tid=" . $tid;
                    $edit_comment_link .= "&pd=" . $this->get_data('pd');
                    $edit_comment_link .= "&pp=" . $this->get_data('pp');
                }

                $comment_array[$value['response_id']][] = array(
                    "comment_id"   => $value['comment_id'],
                    "user_id"      => $value['user_id'],
                    "nickname"     => $value['nickname'],
                    "avatar"       => $image->get_avatar_url($value['system_id']),
                    "user_link"    => "/profile/?uid=" . $value['system_id'],
                    "comment_text" => StaticFunction::decode_view_text(nl2br($value['comment_text'])),
                    "update_time"  => DbDateTime::get_date_type_dot($value['update_time']),
                    "edit_link"    => $edit_comment_link
                );
            }
        }
        $this->set("comment_array", $comment_array);

		//コミュニティ総数を取得
		$comment_num = $community->get_response_num($thread[0]['thread_id']);

		//ページング出力
		$page = new PAGING();
		$this->set("pageng_html", $page->make_paging($comment_num));

		/*
		 *  POSTデータがある場合、セッションに登録する。
		 * UPDATE: 2016.10.28 aoyama
		 * 		編集機能を追加
		 */
		if (!StaticFunction::is_empty(REQUEST::post_data())) {

			SESSION::write($this->sGroupResponse . '.tid', $this->get_data('tid'));
			SESSION::write($this->sGroupResponse . '.comment', REQUEST::post_data('comment'));
			SESSION::write($this->sGroup . '.file', true);
			if (!StaticFunction::is_empty(REQUEST::post_data('rid'))) {
				SESSION::write($this->sGroupResponse . '.rid', REQUEST::post_data('rid'));
			}

			//ファイル添付がある場合
			/*
			 * 今のところ画像ファイルだけだが、
			 * 動画ファイルなどが対象になると大幅に工数UPになるかなと
			 * ファイル用のライブラリも必要になる
			 */

            $file = new Image();

            //POSTされた画像のカウントをリセット
            $file_count = 0;
            // 一時ファイルのセッション用配列を初期化
            $tmp_file_name = array();
            $tmp_date_dir = array();

            foreach ($_FILES['response_file']['error'] AS $post_image_array) {
                if ($post_image_array == UPLOAD_ERR_OK) {


                    //一時ファイル名を生成
                    $file_tmp_hash = Encrypt::member_regist_token($_SERVER['REMOTE_ADDR'], time());
                    $file_tmp_hash .= "_" . $file_count;

                    //ロード
                    $ret = $file->load($_FILES['response_file']['tmp_name'][$file_count]);

                    //拡張子取得
                    $thumb_ext = $file->get_image_type();

                    //リサイズ
                    //$thumb->resize_avatar(CONF::read("AVATAR.WIDTH"));
                    //tmp保存先システムディレクトリ[/public/images/tmp/[yyyymm]]
                    $date_dir[$file_count] = DbDateTime::fairing_digit_8(DbDateTime::get_cur_datetime());
                    $tmp_date_dir = DIR_SYSTEM_IMG_TMP . DS . $date_dir[$file_count] . DS;

                    //一時ファイル名
                    $tmp_file_name[$file_count] = $file_tmp_hash . '.' . $thumb_ext;

                    //tmpディレクトリに保存
                    //$ret = $file->save_jpeg($avatar_tmp_dir, $tmp_file_name);
                    //tmpフォルダに移動
                    $file->move_file("", $_FILES['response_file']['tmp_name'][$file_count], $tmp_date_dir, $tmp_file_name[$file_count]);
                }
                $file_count++;
            } // end foreach

            //一時ファイルのファイル名と一時ディレクトリをセッションに保存
            SESSION::write($this->sGroupResponse . '.tmp_file_name', $tmp_file_name);
            SESSION::write($this->sGroupResponse . '.tmp_file_date', $date_dir);

			//セッションのフォームデータをチェック
			$error_array = $this->checkResponseSessionParameter();

			if (!StaticFunction::is_empty($error_array)) {
				$this->set('error_array', $error_array);
				$this->formResponseReturn();
				return;
			}

			//問題なければ確認画面へ
			$this->redirect("./response_complete.html?tid=" . $this->get_data('tid'));
		}
		$this->formResponseReturn();

		//topに返したのでセッション削除
		SESSION::delete($this->sGroupResponse);
		/* ---------------レスポンス投稿処理ここまで--------------- */
	}

	/*	 * **********************************
	 * NAME  : response_confirm
	 * INPUT : NONE
	 * OUTPUT: NONE
	 * DESC  :
	 *  レスポンスを確認するメソッド
	 * NOTICE:
	 * CREATE: 2016.10.20 aoyama
	 * *********************************** */
	public function response_confirm() {

		$community = new CommunityModel();

		//コミュニティの詳細を取得する
		$thread = $community->get_detail_by_id(REQUEST::get_data('tid'));

		if (StaticFunction::is_empty($thread)) {
			$this->set("error", "ご指定のコミュニティが見つかりません。");
			return;
		}

		//画面表示処理
		$image = new Image();

		//参加ボタン制御
		$entry_view = true;
		$leave_view = true;
		//参加済みなら
		if ($community->registered_community($this->public_user_data['user_id'], REQUEST::get_data('tid'))) {
			$entry_view = false;
		}

		//自分のスレッドの場合は解除できない。
		if ($this->public_user_data['user_id'] == $thread[0]['user_id']) {
			$leave_view = false;
		}

		//コミュニティ参加人数を取得
		$match_num = $community->match_num(REQUEST::get_data('tid'));

		//コミュニティメンバーリストを取得
		$match_array = $community->get_match_list(REQUEST::get_data('tid'));
		$match_array_view = array();
		foreach ($match_array AS $values) {
			$match_array_view[] = array(
				"system_id" => $values['system_id'],
				"nickname" => $values['nickname'],
				"avatar" => $image->get_avatar_url($values['system_id'])
			);
		}


		// 表示に必要な情報をセット
		$this->set("thread_id", $thread[0]['thread_id']);
		$this->set("community_name", $thread[0]['community_name']);
		$this->set("community_detail", $thread[0]['community_detail']);
		$this->set("category_id", $thread[0]['category_id']);
		$this->set("category_name", $this->comunityCategoryArray[$thread[0]['category_id']]);
		$this->set("user_id", $thread[0]['user_id']);
		$this->set("system_id", $thread[0]['system_id']);
		$this->set("nickname", $thread[0]['nickname']);
		$this->set("avatar", $image->get_avatar_thread_url($thread[0]['thread_id'], $thread[0]['image_file']));
		$this->set("avatar_user", $image->get_avatar_url($thread[0]['system_id']));
		$this->set("entry_view", $entry_view);
		$this->set("leave_view", $leave_view);
		$this->set("match_num", StaticFunction::count_num_format($match_num) . '人');
		$this->set("match_array", $match_array_view);

		$this->formResponseReturn();

	}

	/*	 * **********************************
	 * NAME  : response_complete
	 * INPUT : NONE
	 * OUTPUT: NONE
	 * DESC  :
	 *  レスポンスを確認するメソッド
	 * NOTICE:
	 * CREATE: 2016.10.20 aoyama
	 * *********************************** */
	public function response_complete() {

        $community = new CommunityModel();

        //権限チェック
        if(!$community->is_community_admin($this->public_user_data['user_id'],REQUEST::get_data('tid'))){
            $this->redirect("/community/");
        }


		if (StaticFunction::is_empty(SESSION::read($this->sGroupResponse))) {
			$this->redirect("/community/");
		}

		$error_array = $this->checkResponseSessionParameter();
		if (!StaticFunction::is_empty($error_array)) {
			$this->redirect("/community/");
		}

		/*
		 * 既に登録されているかチェック。
		 * 登録されていなければ強制的にTOPページへ
		 * 未登録者がここまで来ることはないので。
		 */
		if (!$community->registered_community($this->public_user_data['user_id'], REQUEST::get_data('tid'))) {
			LOGS_ERR("コミュニティに参加せずにコメントを投稿しようとしている。" . $this->public_user_data['user_id']);
			$this->redirect("/community/");
		}

		//現在時刻を生成
		$datetime = DbDateTime::get_cur_datetime();


		//編集モード
		if (!StaticFunction::is_empty(SESSION::read($this->sGroupResponse . '.rid'))) {

			// レスポンス更新処理
            $response_id = SESSION::read($this->sGroupResponse . '.rid');

			// 配列にPOSTデータを格納
			$param_list = array(
				'update_time' => DbCast::datetime($datetime),
				"response_text" => DbCast::string(SESSION::read($this->sGroupResponse . '.comment'))
			);

			$condition = array(
				"WHERE" => array(
					"response_id" => DbCast::id($response_id)
				)
			);
			/* DB登録エラー */
			if (!$insert_id = $community->edit_response($param_list, $condition)) {
				$error_array[] = array("message" => "コメント編集に失敗しました。");
				$this->set('error_array', $error_array);
				exit;
			}
        }
		//新規登録モード
		else {
			// レスポンス登録処理
			// 配列にPOSTデータを格納
			$param_array = array(
				'update_time' => DbCast::datetime($datetime),
				'create_time' => DbCast::datetime($datetime),
				"response_text" => DbCast::string(SESSION::read($this->sGroupResponse . '.comment')),
				"thread_id" => DbCast::id(SESSION::read($this->sGroupResponse . '.tid')),
				"image_file" => DbCast::string(SESSION::read($this->sGroupResponse . '.tmp_file_name'[0])),
				'user_id' => DbCast::id($this->public_user_data['user_id']),
				"active" => DbCast::float(DB_ACTIVE_ON)
			);

			/* DB登録エラー */
			if (!$insert_id = $community->post_response($param_array)) {
				$error_array[] = array("message" => "投稿に失敗しました。");
				$this->set('error_array', $error_array);
				return;
			}
            //画像保存用にタイムラインIDを保持(2017.2.13)
            $response_id = $insert_id;
		}

        /*
         * 添付画像がある場合は画像をthreadディレクトリに移動
         * ↓
         * /images/tmp/[日付]/[tmp名] → /images/community/[threadID]/[tmp名]
         * ※レスポンスIDではなくthreadIDに集約させる。
         */
        if (!StaticFunction::is_empty(SESSION::read($this->sGroupResponse . '.tmp_file_name'))) {

            $img = new Image();

            //セッション配列を配列変数に代入
            $image_array = SESSION::read($this->sGroupResponse . '.tmp_file_name');
            $tmp_date_array = SESSION::read($this->sGroupResponse . '.tmp_file_date');

            //画像個数分、ループ処理
            $sort_num = 0;
            foreach ($image_array AS $img_key => $img_name_value) {

                $ret = $img->set_community_response_public(
                    $tmp_date_array[$img_key]
                    , $img_name_value
                    , SESSION::read($this->sGroupResponse . '.tid') /* コミュニティID */
                    ,$response_id
                    , $sort_num
                );

                //失敗時
                if (!$ret) {
                    //失敗時はアラートメール送信
                }
                $sort_num++;
            }
        }

		//添付画像がある場合は画像をコミュニティディレクトリに移動
//		if (!StaticFunction::is_empty(SESSION::read($this->sGroupResponse . '.tmp_file_name'))) {
//
//			$img = new Image();
//			$ret = $img->set_response_public(SESSION::read($this->sGroupResponse . '.tmp_file_date'), SESSION::read($this->sGroupResponse . '.tmp_file_name'), SESSION::read($this->sGroupResponse . '.tid'));
//
//			//失敗時
//			if (!$ret) {
//				//失敗時はアラートメール送信
//			}
//		}
		//正常終了時はセッションを削除
		SESSION::delete($this->sGroupResponse);
		$this->redirect("/community/detail.html?tid=" . REQUEST::get_data('tid'));
	}

	/*	 * **********************************
	 * NAME  : response_delete
	 * INPUT : NONE
	 * OUTPUT: NONE
	 * DESC  :
	 * 		コメントを削除するメソッド
	 * 		確認画面はなくダイレクトに削除処理を実行
	 * NOTICE:
	 * CREATE: 2016.10.30 aoyama
	 * *********************************** */
	public function response_delete() {

		/* ハッシュチェック */
		if (!StaticFunction::check_token($this->get_data('token'))) {
			//問題なければ確認画面へ
			$this->redirect("./detail.html?tid=" . $this->get_data('tid'));
		}


		//rid（コメントID）の有無を確認
		if (StaticFunction::is_empty($this->get_data('rid'))) {
			$this->redirect("./detail.html?tid=" . $this->get_data('tid'));
		}

		//コメントの情報を取得
		$community = new CommunityModel();
		$response = $community->get_response_from_rid($this->get_data('rid'));

		//対象がなければ終了
		if (StaticFunction::is_empty($response)) {
			$this->redirect("./detail.html?tid=" . $this->get_data('tid'));
		}

		$like = new LikeModel();
		//いいねを削除
		$like->delete_response_like($this->get_data('rid'));

		//画像があれば削除処理
		if (!StaticFunction::is_empty($response[0]['image_file'])) {
			$img = new Image();
			if (!$img->delete(DIR_PUBLIC_IMG . DS . "community" . DS . $response[0]['thread_id'] . DS, $response[0]['image_file'])) {
				echo '$img->delete error';
				exit;
			}
		}

		//DBのactiveをOFFにする
		$param_list = array(
			"active" => DB_ACTIVE_OFF,
			"image_file" => DbCast::string("")
		);
		$condition = array(
			"WHERE" => array(
				"response_id" => DbCast::id($this->get_data('rid'))
			)
		);

		$community->delete_response($param_list, $condition);


		//問題なければ確認画面へ
		$this->redirect("./detail.html?tid=" . $this->get_data('tid'));
	}

    /**
     * コメントを削除する
     * INPUT : NONE
     * OUTPUT: NONE
     * DESC  :
     * NOTICE:
     * CREATE: 2017.09.15 aoyama
     */
    public function comment_delete() {

        /* TOKENチェック */
        if (!StaticFunction::check_token($this->get_data('token'))) {
            $this->redirect("/community/");
        }

        $community = new CommunityModel();

        //DBのactiveをOFFにする
        $datetime = DbDateTime::get_cur_datetime();
        $param_list = array(
            'update_time' => DbCast::datetime($datetime),
            "active" => DB_ACTIVE_OFF
        );
        $condition = array(
            "WHERE" => array(
                "comment_id" => DbCast::id($this->get_data('comment_id'))
            )
        );

        $community->delete_comment($param_list, $condition);

        $thread = $community->get_thread_from_comment_id($this->get_data('comment_id'));


        //問題なければ確認画面へ
        $this->redirect("/community/detail.html?tid=" . $thread[0]['thread_id']);
    }

	/*	 * **********************************
	 * NAME:checkResponseSessionParameter
	 * DESC:
	 *  レスポンス専用ののセッション情報バリデーション
	 * NOTICE:
	 * CREATE: 2016.10.20 aoyama
	 * *********************************** */
	private function checkResponseSessionParameter() {

		$error_array = array();

		if (!SESSION::read($this->sGroup . '.file')) {
			$error_array[] = array('target' => 'file', 'message' => '添付できるファイルは画像のみです。');
		}

		if (!InputVali::is_comment_thread(SESSION::read($this->sGroupResponse . '.comment'))) {
			$error_array[] = array('target' => 'comment', 'message' => 'コミュニティコメントは400文字以内で入力してください。');
		}

		return $error_array;
	}

	/*	 * **********************************
	 * NAME:formResponseReturn
	 * DESC:
	 *  セッション情報をレスポンス用フォームに渡すためにセットする機能
	 * NOTICE:
	 * CREATE: 2016.10.20 aoyama
	 * UPDATE: 2016.11.16 aoyama
	 * 		画像編集タイプの調整
	 * *********************************** */
	private function formResponseReturn() {

// セッションの情報をセットしてviewに渡す
		if (!StaticFunction::is_empty(SESSION::read($this->sGroupResponse))) {
			$this->set("tid", SESSION::read($this->sGroupResponse . '.tid'));
			$this->set("rid", SESSION::read($this->sGroupResponse . '.rid'));
			$this->set("comment", SESSION::read($this->sGroupResponse . '.comment'));
			$this->set("comment_view", StaticFunction::decode_view_text(nl2br(SESSION::read($this->sGroupResponse . '.comment'))));
			$this->set("tmp_file_name", SESSION::read($this->sGroupResponse . '.tmp_file_name'));
			$this->set("tmp_file_date", SESSION::read($this->sGroupResponse . '.tmp_file_date'));

			$image = new Image();
			$community = new CommunityModel();
			$file_url = "";

			//編集モードの場合は既存の情報を取得
			if (!StaticFunction::is_empty(SESSION::read($this->sGroupResponse . ".rid"))) {
				$response_detail = $community->get_response_from_rid(SESSION::read($this->sGroupResponse . ".rid"));
				//詳細が取得できたので画像のパスを取得
				if (!StaticFunction::is_empty($response_detail)) {
					$file_url = $image->get_response_url(SESSION::read($this->sGroupResponse . ".tid"), $response_detail[0]['image_file']);
				}
			}

			/* プレビューでの画像ファイル */
			//まずはセッションにtmp画像が入っている場合は上書き
			if (!StaticFunction::is_empty(SESSION::read($this->sGroupResponse . '.tmp_file_name'))) {
				$file_url = $image->get_tmp_file_url(SESSION::read($this->sGroupResponse . '.tmp_file_date'), SESSION::read($this->sGroupResponse . '.tmp_file_name'));
			}

			$this->set("file_link", $file_url);


        }
	}

	/*	 * **********************************
	 * NAME  : delete_thread
	 * INPUT : NONE
	 * OUTPUT: NONE
	 * DESC  :
	 * 		コミュニティを削除する
	 * 		一応detail.htmlと同等の内容を表示しておく。
	 * NOTICE:
	 * CREATE: 2016.10.28 aoyama
	 * *********************************** */
	public function delete_thread() {

		$community = new CommunityModel();

//コミュニティの詳細を取得する
		$thread = $community->get_detail_by_id($this->get_data('tid'));

		if (StaticFunction::is_empty($thread)) {
			$this->set("error", "ご指定のコミュニティが見つかりません。");
			return;
		}

		if ($thread[0]['user_id'] == $this->public_user_data['user_id']) {
			if ($community->delete_thread($this->get_data('tid'), $this->public_user_data['user_id'])) {
				//削除が成功したのでコミュニティTOPへリダイレクト。
				$this->redirect("/community/");
			}
		}

//画面表示処理
		$image = new Image();

//参加ボタン制御
		$entry_view = true;
		$leave_view = true;
//参加済みなら
		if ($community->registered_community($this->public_user_data['user_id'], $this->get_data('tid'))) {
			$entry_view = false;
		}

//自分のスレッドの場合は解除できない。
		if ($this->public_user_data['user_id'] == $thread[0]['user_id']) {
			$leave_view = false;
		}

//コミュニティ参加人数を取得
		$match_num = $community->match_num($this->get_data('tid'));

//コミュニティメンバーリストを取得
		$match_array = $community->get_match_list($this->get_data('tid'));
		$match_array_view = array();
		foreach ($match_array AS $values) {
			$match_array_view[] = array(
				"system_id" => $values['system_id'],
				"nickname" => $values['nickname'],
				"avatar" => $image->get_avatar_url($values['system_id'])
			);
		}

// 表示に必要な情報をセット
		$this->set("thread_id", $thread[0]['thread_id']);
		$this->set("community_name", $thread[0]['community_name']);
		$this->set("community_detail", $thread[0]['community_detail']);
		$this->set("category_id", $thread[0]['category_id']);
		$this->set("category_name", $this->comunityCategoryArray[$thread[0]['category_id']]);
		$this->set("user_id", $thread[0]['user_id']);
		$this->set("system_id", $thread[0]['system_id']);
		$this->set("nickname", $thread[0]['nickname']);
		$this->set("avatar", $image->get_avatar_thread_url($thread[0]['thread_id'], $thread[0]['image_file']));
		$this->set("avatar_user", $image->get_avatar_url($thread[0]['system_id']));
		$this->set("entry_view", $entry_view);
		$this->set("leave_view", $leave_view);
		$this->set("match_num", StaticFunction::count_num_format($match_num) . '人');
		$this->set("match_array", $match_array_view);


		$error_array[] = array(
			"message" => "存在しないか削除する権限がありません。"
		);

		$this->set("error_array", $error_array);
	}

	/**
	 * NAME  : getTopCommList
	 * INPUT : NONE
	 * OUTPUT: NONE
	 * DESC  :
	 * 		トップコミュニティ一覧を取得
	 * NOTICE:
	 * CREATE: 2017.08.12 aoyama
	 */
	public function getTopCommList()
    {
        $community = new CommunityModel();
        $image = new Image();
        $top_community_array = $community->getTopCommunityList();
        foreach ($top_community_array AS $value) {
            $ret[] = array(
                "thread_id"        => $value['thread_id'],
                "community_name"   => $value['community_name'],
                "community_detail" => $value['community_detail'],
                "category_id"      => $value['category_id'],
                "category_name"    => $this->comunityCategoryArray[$value['category_id']],
                "avatar"           => $image->get_avatar_thread_url($value['thread_id'], $value['image_file']),
				"thread_link" => "/community/detail.html?tid=".$value['thread_id']
            );
        }
        return $ret;
    }

    /**
     * コミュニティ管理者を追加する
     * 2017.09.10 aoyama
     */
    public function authorAdd()
    {
        $user = new UserPublicModel();
        $author_user_array = $user->verification(REQUEST::post_data('author_uid'));

        if(StaticFunction::is_empty($author_user_array)) {
            // TODO エラー表示をviewに渡す。[ユーザーが見つかりません。]
            $error_array[] = array("message" => "ユーザーが見つかりません。");
            SESSION::write($this->sGroup . '.error_array', $error_array);
            $this->redirect("/community/edit.html/?tid=".REQUEST::post_data('tid'));
        }
        $param_array = array(
            'user_id'     => $author_user_array[0]['user_id'],
            'thread_id'   => REQUEST::post_data('tid'),
            'create_time' => DbDateTime::get_cur_datetime(),
            'update_time' => DbDateTime::get_cur_datetime()
        );

        $community = new CommunityModel();
        if($community->is_entry_author($param_array)) {
            // TODO エラー表示をviewに渡す。[既に登録されています。]
            $error_array[] = array("message" => "既に登録されています。");
            SESSION::write($this->sGroup . '.error_array', $error_array);
            $this->redirect("/community/edit.html/?tid=".REQUEST::post_data('tid'));
		}

        if(!$community->entry_author($param_array)) {
            $error_array[] = array("message" => "登録に失敗しました。");
            SESSION::write($this->sGroup . '.error_array', $error_array);
            $this->redirect("/community/edit.html/?tid=".REQUEST::post_data('tid'));
		}

		// 関連登録できたユーザーはフォロー状態にする
        $this->entry_thread($author_user_array[0]['user_id'],REQUEST::post_data('tid'));

		// 編集画面に戻る
        $this->redirect("/community/edit.html/?tid=".REQUEST::post_data('tid'));
    }

    /**
     * コミュニティ関連グループを追加する
     * 2017.09.10 aoyama
     */
    public function groupAdd()
    {
        $user = new UserPublicModel();
        $author_user_array = $user->verification(REQUEST::post_data('_uid'));

//        var_dump($author_user_array);
//        exit;

        if(StaticFunction::is_empty(REQUEST::post_data('group_name'))) {
            // TODO エラー表示をviewに渡す。[ユーザーが見つかりません。]
            $error_array[] = array("message" => "グループ名を入力してください。");
            SESSION::write($this->sGroup . '.error_array', $error_array);
            $this->redirect("/community/edit.html/?tid=".REQUEST::post_data('tid'));
        }
        $param_array = array(
            'group_name'  => DbCast::string(REQUEST::post_data('group_name')),
            'thread_id'   => REQUEST::post_data('tid'),
            'create_time' => DbDateTime::get_cur_datetime(),
            'update_time' => DbDateTime::get_cur_datetime()
        );

        $community = new CommunityModel();

        if($community->entry_author_group($param_array)) {
            $error_array[] = array("message" => "登録に失敗しました。");
            SESSION::write($this->sGroup . '.error_array', $error_array);
            $this->redirect("/community/edit.html/?tid=".REQUEST::post_data('tid'));
        }

        // 編集画面に戻る
        $this->redirect("/community/edit.html/?tid=".REQUEST::post_data('tid'));
    }

    /**
     * コミュニティグループを並べ替える
     * 2017.09.10 aoyama
     */
    public function authorSort()
    {
        $group_null = "null";
        $group_id = $group_null;
        $author_id = "";
        $group_count = 1;
        $author_count = 1;

        $json = json_decode($_POST['author_json'],true);

        $community = new CommunityModel();
        // TODO threadの管理者とグループを全削除
        $community->delete_author_group(REQUEST::post_data('tid'));

        foreach($json AS $val){
            list($type,$id,$name) = array_pad(explode("-",$val['id']), 3, null);
            switch(true){
                case ($type == "group"):
                    // TODO グループ追加クエリ
                    if($id != $group_null) {
                        $param_array = array(
                            'group_name'  => DbCast::string($name),
                            'thread_id'   => REQUEST::post_data('tid'),
                            'sort_id'     => DbCast::integer($group_count),
                            'create_time' => DbDateTime::get_cur_datetime(),
                            'update_time' => DbDateTime::get_cur_datetime()
                        );
                        $group_id = $community->entry_author_group($param_array);
                        $group_count++;
                    } else {
                        $group_id = $group_null;
                    }

                    break;
                case ($type == "author") :
                    $author_id = $id;
                    // TODO 管理者追加クエリ

                    $user = new UserPublicModel();
                    $author_user_array = $user->verification($author_id);
                    if(!StaticFunction::is_empty($author_user_array)) {
                        $author_array = array(
                            'user_id'     => DbCast::integer($author_user_array[0]['user_id']),
                            'thread_id'   => REQUEST::post_data('tid'),
                            'sort_id'     => DbCast::integer($author_count),
                            'create_time' => DbDateTime::get_cur_datetime(),
                            'update_time' => DbDateTime::get_cur_datetime()
                        );
                        if($group_id != $group_null) {
                            $author_array += array('group_id'    =>  DbCast::integer($group_id));
                        }
                        $community->entry_author($author_array);
                        $author_count++;
                    }
                    break;
            }
        }

        // 編集画面に戻る
        $this->redirect("/community/edit.html/?tid=".REQUEST::post_data('tid'));
    }

    /**
     * コミュニティの投稿に対するコメントを登録する。
     * INPUT :
     * OUTPUT:
     * DESC  :
     * 		タイムライン投稿に対するレスポンスを登録する。
     * NOTICE:
     * CREATE: 2017.09.14 aoyama
     */
    public function comment() {

        $return_url = "/community/detail.html?tid=".REQUEST::post_data('thread_id');

        $comment_text = REQUEST::post_data('comment_text');

        //コメントが未入力の時もリダイレクト（JSチェック推奨）
        if (StaticFunction::is_empty($comment_text)) {
            $this->redirect($return_url);
        }

        /* ハッシュチェック */
        if (!StaticFunction::check_token(REQUEST::post_data('token'))) {
            $this->redirect($return_url);
        }

        $pageing = (!StaticFunction::is_empty(REQUEST::post_data('pd'))) ? "?pd=" . REQUEST::post_data('pd') . "&pp=" . REQUEST::post_data('pp') : "";


        //入力チェック（JSバリデーションを期待）
        $error_array = $this->checkCommentParameter($comment_text);
        if (!StaticFunction::is_empty($error_array)) {
            LOGS_ERR($error_array);
            $this->redirect($return_url);
        }

        $datetime = DbDateTime::get_cur_datetime();

        $community = new CommunityModel();
        // 親コミュニティのupdate_timeを更新
        $param_list = array(
            'update_time' => DbCast::datetime($datetime)
        );
        $condition = array(
            "WHERE" => array(
                "thread_id" => DbCast::id(REQUEST::post_data('thread_id'))
            )
        );
        $community->update($param_list, $condition);

        // 親レスポンスのupdate_timeを更新
        $condition = array(
            "WHERE" => array(
                "response_id" => DbCast::id(REQUEST::post_data('response_id'))
            )
        );
        $community->update_response($param_list, $condition);

        // スレッド登録処理
        // 配列にPOSTデータを格納
        $param_array = array(
            'update_time' => DbCast::datetime($datetime),
            'create_time' => DbCast::datetime($datetime),
            "active" => DB_ACTIVE_ON,
            'user_id' => DbCast::id($this->public_user_data['user_id']),
            "response_id" => DbCast::id(REQUEST::post_data('response_id')),
            "comment_text" => DbCast::string($comment_text)
        );

        if ($community->post_response_comment($param_array)) {
            //ページングが発生している場合はページング情報をセット
            $this->redirect($return_url);
        }

        $this->redirect($return_url);
    }

    /**
     * コメント用のバリデーション
     * DESC:
     * NOTICE:
     * CREATE: 2017.09.14 aoyama
     */
    private function checkCommentParameter($comment_text) {

        $error_array = array();

        if (!InputVali::is_comment_thread($comment_text)) {
            $error_array[] = array('target' => 'comment', 'message' => 'コミュニティコメントは400文字以内で入力してください。');
        }

        return $error_array;
    }


    private function entry_thread($user_id,$thread_id)
    {
        $community = new CommunityModel();

        //既に登録されているかチェック。登録されていればそのままスルー。
        if (!$community->registered_community($user_id, $thread_id)) {

            //作成者をコミュニティ参加者に登録する
            // 配列にPOSTデータを格納
            $datetime = DbDateTime::get_cur_datetime();
            $match_array = array(
                'create_time' => DbCast::datetime($datetime),
                'update_time' => DbCast::datetime($datetime),
                "user_id" => DbCast::id($user_id),
                'thread_id' => DbCast::id($thread_id),
                "active" => DbCast::float(DB_ACTIVE_ON)
            );

            if (!$community->entry_community($match_array)) {
                //失敗時はアラートメール送信
            }
        }
    }


    /**
     * レスポンスの画像をDB、フォルダから削除
     * INPUT : NONE
     * OUTPUT: NONE
     * DESC  :
     * NOTICE:
     * CREATE: 2017.09.20 aoyama
     * *********************************** */
    public function delete_response_image()
    {
        $cm = new CommunityModel();

        $response_id = REQUEST::get_data('rid');

        // thread_idを逆引き
        $thread = $cm->get_thread_from_response_id($response_id);

        //権限チェック
        if(!$cm->is_community_admin($this->public_user_data['user_id'],$thread[0]['thread_id'])){
            $this->redirect("/community/");
        }

        // URLからファイル名を抽出
        $path = REQUEST::get_data('file_name');
        $filename = strrchr($path, "/");// /postname.html
        $file_name = substr($filename, 1);// postname.html

        // DBとフォルダから同時にファイル削除
        $cm->delete_response_file($thread[0]['thread_id'], $response_id, $file_name);

        // リダイレクト処理
        $pageing = (!StaticFunction::is_empty(REQUEST::get_data('pd'))) ? "&pd=" . REQUEST::get_data('pd') . "&pp=" . REQUEST::get_data('pp') : "";
        $this->redirect("/community/detail.html?tid=" . $thread[0]['thread_id'] . $pageing);
    }

    private function get_data($param){

        return $_GET[$param];
    }
}

