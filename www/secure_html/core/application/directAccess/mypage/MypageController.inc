<?php

/* * **********************************
 * NAME:MypageController
 * DESC:
 *  マイページ用のコントローラ(クローズエリア)
 * 
 *  コントローラの継承
 *  MypageController
 *  ↓
 *  MypageBaseCommonControllerFrame
 *  ↓
 *  ControllerCore
 *  となる
 * 
 * NOTICE:
 * CREATE: 2016.10.13 aoyama
 * UPDATE: 2016.12.3 aoyama
 * 		マイページをSNSと基幹で分離することになったので
 * 		こちらはSNS登録なしでも表示するように
 * *********************************** */
class MypageController extends MypageBaseCommonControllerFrame {

	private $sGroup;
	private $public_user_data;
    private $comunityCategoryArray;


    /* Constructor */
	public function __construct() {

		parent::__construct();

		//セッショングループを設定
		$this->sGroup = 'mypage';

		//セッションからユーザ情報を取得
        $this->public_user_data = SESSION::read(CONF::read('LOGIN_CATEGORY.PUBLIC'));
        
        $this->set("page_group", "mypage");
	}

	/*	 * **********************************
	 * NAME  : index
	 * INPUT : NONE
	 * OUTPUT: NONE
	 * DESC  :
	 *  マイページのトップ画面アクセスした際にフロントより実行されるメソッド
	 * NOTICE:
	 * CREATE: 2016.10.21 aoyama
	 * UPDATE: 2017.08.13 aoyama
	 * 		機能のないページだったが実装
	 * *********************************** */
	public function index() {

        $this->set('API_BASE_URL', Conf::read('REST_API.BASE_URL'));

        $api = new Rest();

        // トップコミュニティ一覧用
        $top_community_array = $this->getTopCommList();
        $this->set("top_community_array",$top_community_array);

        $timeline = new TimelineModel();
        $image = new Image();
        $community = new CommunityModel();

        $tvViewArray = array();
        $timeline_ids = array();
        $thread_ids = array();

        if(!isset($this->public_user_data['user_id'])){
            $this->public_user_data['user_id'] = null;
        }

        $response_ids = array();

        foreach ($timeline->get_timeline_for_index(0, 20) AS $tlValue) {

            // 画像ファイルの表示用配列初期化(2017.2.13 aoyama)
            $file_url = array();

            switch ($tlValue['type']) {

                case "response":
                    $file_url = $community->get_community_response_image($tlValue['thread_id'], $tlValue['code']);
                    $prefix = 'community';
                    $response_ids[] = $tlValue['code'];
                    $thread_ids[] = $tlValue['thread_id'];
                    $mypost = false;
                    break;
                case "timeline":
                    //imageクラスではなくtimelineクラスで取得する方式に変更
                    //$file_url = $image->get_timeline_url($tlValue['system_id'], $tlValue['code']);
                    $file_url = $timeline->get_timeline_image($tlValue['system_id'], $tlValue['code']);
                    $prefix = 'timeline';
                    $mypost = ($tlValue['user_id'] == $this->public_user_data['user_id']) ? true : false;
                    $timeline_ids[] = $tlValue['code'];
                    break;
            }

            $tvViewArray[] = array(
                "mypage_id" => $tlValue['code'],
                "prefix" => $prefix,
                "thread_id" => $tlValue['thread_id'],
                "thread_name" => $tlValue['thread_name'],
                "system_id" => $tlValue['system_id'],
                "nickname" => $tlValue['nickname'],
                "like_count" => $tlValue['like_count'],
                "text" => $tlValue['text'],
                "text_view" => StaticFunction::decode_view_text(nl2br($tlValue['text'])),
                "file_url" => $file_url,
                "publication" => $tlValue['publication'],
                "avatar" => $image->get_avatar_url($tlValue['system_id']),
                "update_time" => DbDateTime::get_date_type_dot($tlValue['update_time']),
                "is_my_post" => $mypost
            );
        }
        $this->set("timeline_array", $tvViewArray);

        /* 自身が参加しているコミュニティの配列をviewに渡す */
        $topComms = array();
        foreach($top_community_array AS $top_com){
            $topComms[] = $top_com['thread_id'];
        }
        $this->set("community_match", $community->get_community_match_user($topComms,$this->public_user_data['user_id']));

        /* timeline返信を取得しviewに渡す */
        $timeline_response_array = array();
        foreach ($timeline->get_timeline_response($timeline_ids) AS $value) {

            $edit_response_link = "";
            // 自分のレビューコメントの時はレビューの編集ボタンリンクを設定。これをviewの表示判定にも使用。
            if ($value['user_id'] == $this->public_user_data['user_id']) {
                $edit_response_link = "/mypage/response_delete.html?tr_id=" . $value['timeline_response_id'];
                $edit_response_link .= "&token=" . SESSION::read('EXPIRES.ORIGINAL_TOKEN');
            }

            $timeline_response_array[$value['timeline_id']][] = array(
                "timeline_response_id" => $value['timeline_response_id'],
                "user_id" => $value['user_id'],
                "nickname" => $value['nickname'],
                "avatar" => $image->get_avatar_url($value['system_id']),
                "user_link" => "/profile/?uid=" . $value['system_id'],
                "timeline_id" => $value['timeline_id'],
                "response_text" => StaticFunction::decode_view_text(nl2br($value['response_text'])),
                "update_time" => DbDateTime::get_date_type_dot($value['update_time']),
                "edit_link" => $edit_response_link
            );
        }
        $this->set("timeline_response_array", $timeline_response_array);

        // コミュニティのコメントを取得
        $comment_array = array();
        foreach ($community->get_comment_list($response_ids) AS $value) {
            $edit_response_link = "";
            // 自分のレビューコメントの時はレビューの編集ボタンリンクを設定。これをviewの表示判定にも使用。
            if ($value['user_id'] == $this->public_user_data['user_id']) {
                $edit_response_link = "/community/comment_delete.html?comment_id=" . $value['comment_id'];
                $edit_response_link .= "&token=" . SESSION::read('EXPIRES.ORIGINAL_TOKEN');
            }
            $comment_array[$value['response_id']][] = array(
                "nickname" => $value['nickname'],
                "avatar" => $image->get_avatar_url($value['system_id']),
                "user_link" => "/profile/?uid=" . $value['system_id'],
                "comment_id" => $value['comment_id'],
                "comment_text" => StaticFunction::decode_view_text(nl2br($value['comment_text'])),
                "update_time" => DbDateTime::get_date_type_dot($value['update_time']),
                "edit_link" => $edit_response_link
            );
        }


        $this->set("comment_array", $comment_array);

        // カウンセリングデータ
        $user_id = $this->public_user_data['system_user_id'];

		$url = Conf::read('REST_API.BASE_URL') . "/getUserChartList/?user_id=$user_id&type=1&pp=9999&pd=0";
        $res = $this->curl_api_get($url);

        $chart_flg = 0;
        $chart_count = 0;
        
        $chart_list = $res['chart_list'];
		foreach ($chart_list as $row) {
			if (is_null($row['webcounselingstatus']) or $row['webcounselingstatus'] == "0") {
				$chart_count++;
			}
        }
        
        $this->set("chart_count", $chart_count);


        // 1：過去のケア～　2：ただいまの～　3：ハッピーワードローブ
        $pd = (InputVali::is_num(REQUEST::get_data('pd'))) ? REQUEST::get_data('pd') : 0;
        $pp = (InputVali::is_num(REQUEST::get_data('pp'))) ? REQUEST::get_data('pp') : CONF::read('PAGING.DEFAULT_NUM_PUBLIC');
        
        $careList = $api->get_user_chart_list($this->public_user_data['system_user_id'], 1, $pd, $pp, "ASC");
        $history_count = $careList['chart_count'];

        $careList = $api->get_user_chart_list($this->public_user_data['system_user_id'], 2, $pd, $pp, "ASC");
        $ordered_count = $careList['chart_count'];

        $careList = $api->get_user_chart_list($this->public_user_data['system_user_id'], 3, $pd, $pp, "ASC");
        $wordrobe_count = $careList['chart_count'];

        $this->set('history_count', $history_count);
        $this->set('ordered_count', $ordered_count);
        $this->set('wordrobe_count', $wordrobe_count);
	}
	
	/*	 * **********************************
	 * NAME  : delete_timeline_image
	 * INPUT : NONE
	 * OUTPUT: NONE
	 * DESC  :
	 *		タイムラインの画像を削除する
	 * NOTICE:
	 * CREATE: 2017.2.13 aoyama
	 * *********************************** */
	public function delete_timeline_image() {
		
		$timeline_id = REQUEST::get_data('tid');
		
		$path =  REQUEST::get_data('file_name');
		$filename = strrchr( $path, "/" );// /postname.html
		$file_name = substr( $filename, 1 );// postname.html

		//タイムラインのユーザー情報を取得
		$timeline = new TimelineModel();
		$tl_detail = $timeline->get_detail_by_id($timeline_id,$this->public_user_data['user_id']);
		
		if(!StaticFunction::is_empty($tl_detail)){
			$timeline->delete_timeline_file($this->public_user_data['system_id'],$timeline_id,$file_name);
		}
		
		//問題なければ確認画面へ
		$pageing = (!StaticFunction::is_empty(REQUEST::post_data('pd'))) ? "?pd=" . REQUEST::post_data('pd') . "&pp=" . REQUEST::post_data('pp') : "";
		$this->redirect("/mypage/sns.html" . $pageing);
	}

	/*	 * **********************************
	 * NAME  : chart_image
	 * INPUT : NONE
	 * OUTPUT: NONE
	 * DESC  :
	 *  アバターを変更するメソッド
	 * NOTICE:
	 * CREATE: 2016.10.27 aoyama
	 * *********************************** */
	public function chart_image() {

		$image = new Image();

		//リサイズ
		$image->create_chart(REQUEST::get_data('mode'), REQUEST::get_data('small'), REQUEST::get_data('large'));
	}
    /*
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

        //コミュニティカテゴリ（固定）を取得し配列に。
        $this->comunityCategoryArray = $community->get_category_list();

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
     * push 通知する用のAPIを呼び出す
     */
    public function push()
    {
        // リクエストでユーザIDおよび紐付けID
        $user_id = REQUEST::post_data('user_id');
        $token = REQUEST::post_data('registration_token');

        $url = Conf::read('REST_API.BASE_URL') . "/updateUserNotification/";
        $data = array(
            'user_id' => $user_id,
            'registration_token' => $token,
        );
        $res = $this->curl_api_post($url, $data);
    }

    /**
     * CURL 経由でAPIを呼び出し
     *
     * @param string $url
     * @return void
     */
    private function curl_api_get($url) {
		// cURLセッションを初期化
		$ch = curl_init();

		// オプションを設定
		curl_setopt($ch, CURLOPT_URL, $url); // 取得するURLを指定
		curl_setopt($ch, CURLOPT_RETURNTRANSFER, true); // 実行結果を文字列で返す
		curl_setopt($ch, CURLOPT_SSL_VERIFYPEER, false); // サーバー証明書の検証を行わない

		// URLの情報を取得
		$response =  curl_exec($ch);

		$res = json_decode($response, true);

		return $res;
    }

    

	/**
	 * CURLでAPIと通信する（POST)
	 *
	 * @param string $url
	 * @param array $post_data
	 * @return void
	 */
	private function curl_api_post($url, $post_data) {
		// cURLセッションを初期化
		$ch = curl_init();

		// オプションを設定
		curl_setopt($ch, CURLOPT_URL, $url); // 取得するURLを指定
		curl_setopt($ch,CURLOPT_POST, TRUE);
		curl_setopt($ch, CURLOPT_RETURNTRANSFER, true); // 実行結果を文字列で返す
		curl_setopt($ch, CURLOPT_SSL_VERIFYPEER, false); // サーバー証明書の検証を行わない
		curl_setopt($ch, CURLOPT_POSTFIELDS, http_build_query($post_data));

		// URLの情報を取得
		$response =  curl_exec($ch);

		$res = json_decode($response, true);

		return $res;
	}

}

?>
