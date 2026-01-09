<?php

/* * **********************************
 * NAME:CommunityTopController
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
class CommunityTopController extends PublicOpenControllerFrame {

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
        
        $this->set("page_group", "community");
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
     * NAME  : detail
     * INPUT : NONE
     * OUTPUT: NONE
     * DESC  :
     *   コミュニティの詳細を表示するが、
     *   TOPコミュニティ以外の詳細にアクセスしようとするとログインしていない人はログイン画面にリダイレクトさせる。
     *
     *   TOPコミュニティの判定は「community_thread.topcom_flg」が１＝有効
     *
     * CREATE: 2019.01.23 aoyama
     * *********************************** */
    public function detail() {

        $login = new Login();
        $community = new CommunityModel();

        //コミュニティの詳細を取得する
        $thread = $community->get_detail_by_id($this->get_data('tid'));

        if (StaticFunction::is_empty($thread)) {
            $this->set("error", "ご指定のコミュニティが見つかりません。");
            return;
        }

        /*
         * 2019.01.23
         * 通常コミュニティの場合は
         * ログイン状態をチェックし未ログイン状態ではログインページへリダイレクト
         */
        if($thread[0]['topcom_flg'] != 1 && !$login->is_sns_login()){
            //ログインページへリダイレクト
            $login->redirect_login(URL_FULL);
        }

        $tid = $this->get_data('tid');

        //コミュニティ参加ボタンからアクセスされた場合
        if ($this->get_data("mode") == "entry") {
            $this->entry_thread($this->public_user_data['user_id'], $tid);
        }

        //画面表示処理
        $image = new Image();

        if (!$login->is_sns_login()) {
            $this->public_user_data['system_id'] = "";
            $this->public_user_data['user_id'] = "";
            $this->public_user_data['nickname'] = "";
        }

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
        $this->set("is_login", $login->is_sns_login()); // コミュニティの一般公開に合わせて追加 2019.01.24


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

    private function get_data($param){

        return REQUEST::get_data($param);
    }
}

