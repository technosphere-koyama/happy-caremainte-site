<?php

/* * **********************************
 * NAME:CommunityModel
 * DESC:
 *  コミュニティ系テーブル用モデルクラス
 *  上記テーブルに対してアクセス(クエリなど)する場合は
 *  当該クラスにて行うこと！
 * NOTICE:
 *  基本的にはDbShellクラスを継承し、そちらでPDOインスタンスアクセスを行う
 *  場合によっては当該クラスで直接触ることもあるかも知れないが、
 *  できるだけDbShellクラスにて行うこと！
 * CREATE: 2016.10.19 aoyama
 * *********************************** */
class CommunityModel extends DbShell {

	private $user_public = "user_public";
	private $category_master = "community_category_master";
	private $table_thread = "community_thread";
	private $table_response = "community_response";
	private $table_match = "community_match";
    private $community_author = "community_author";
    private $community_author_group = "community_author_group";
    private $community_comment = "community_comment";
    private $community_response_file = "community_response_file";

	public function __construct() {
		parent::__construct();
	}

	/*	 * **********************************
	 * NAME  : get_response_from_rid
	 * INPUT : $response_id / int / レスポンスID
	 * OUTPUT:　数値
	 * DESC  :
	 * 		レスポンスの詳細を取得するメソッド
	 * NOTICE:
	 * CREATE: 2016.10.25 aoyama
	 * *********************************** */
	public function get_response_from_rid($response_id) {

		$result = $this->query("
			SELECT
			rs.thread_id,
				rs.user_id,
				rs.image_file
			FROM
				" . $this->table_response . " AS rs
			WHERE
				rs.response_id = " . DbCast::id($response_id) . "
				AND
				rs.active = " . DB_ACTIVE_ON
		);
		
		return $result;
		
	}	
	
	/*	 * **********************************
	 * NAME  : get_thread_num_from_user
	 * INPUT : $user_id / string / コミュニティID
	 * OUTPUT:　数値
	 * DESC  :
	 * 		参加しているコミュニティ数取得用メソッド
	 * NOTICE:
	 * CREATE: 2016.10.25 aoyama
	 * *********************************** */
	public function get_thread_num_from_user($user_id) {

		$match_count = $this->query("
			SELECT
				COUNT(tm.thread_id) AS num
			FROM
				" . $this->table_match . " AS tm
			WHERE
				tm.user_id = " . DbCast::id($user_id) . "
				AND
				tm.active = " . DB_ACTIVE_ON
		);

		if (!$match_count) {
			return 0;
		}
		return (int) $match_count[0]['num']; //intキャストは必須！
	}

	/*	 * **********************************
	 * NAME  : get_thread_from_user
	 * INPUT :
	 * 		$user_id / int / コミュニティID
	 * 		$pd  / int / paged
	 * 		$pp / int / post per page
	 * OUTPUT: array / コミュニティ一覧
	 * DESC  :
	 *  ユーザーIDからコミュニティリストを取得する
	 * NOTICE:
	 * 		失敗など通常はfalseを返すが今回はarray()を返す。
	 * CREATE: 2016.10.24 aoyama
	 * *********************************** */
	public function get_thread_from_user($user_id, $pd = 0, $pp = 20) {

		//パラメータチェック
		if (StaticFunction::is_empty($user_id)) {
			return array();
		}

		$thread_list = $this->query("
			SELECT
				tm.thread_id
			FROM
				" . $this->table_match . " AS tm
			WHERE
				tm.user_id = " . DbCast::id($user_id) . "
				AND
				tm.active=" . DB_ACTIVE_ON . "
			ORDER BY
				tm.create_time DESC
			LIMIT
				" . ($pd * $pp) . ", " . $pp
		);

		if (StaticFunction::is_empty($thread_list)) {

			return array();
		}
		$inArray = array();
		foreach ($thread_list AS $val) {
			$inArray[] = (int) $val['thread_id'];
		}

		$in = implode(",", $inArray);

		$data = $this->query("
			SELECT
				tm.thread_id,
				ct.community_name,
				ct.community_detail,
				ct.image_file,
				ccm.category_name,
				COUNT(tm.user_id) AS `join_count`
			FROM
				" . $this->table_match . " AS tm
			LEFT JOIN
				" . $this->table_thread . " AS ct
			ON
				tm.thread_id = ct.thread_id
			LEFT JOIN
				" . $this->category_master . " AS ccm
			ON
				ct.category_id = ccm.category_id
			WHERE
				tm.thread_id IN (" . $in . ")
				AND
				ct.active=" . DB_ACTIVE_ON . "
			GROUP BY
				tm.thread_id
			ORDER BY
				tm.create_time DESC"

		);
		//エラー・空の場合
		if ($this->db_select_check_error($data) || $this->db_select_check_empty($data)) {
			return array();
		}

		return $data;
	}

	/*	 * **********************************
	 * NAME  : get_match_list
	 * INPUT :
	 * 		$thread_id / int / コミュニティID
	 * 		$pd  / int / paged
	 * 		$pp / int / post per page
	 * OUTPUT: array / メンバー一覧
	 * DESC  :
	 *  コミュニティIDからメンバーリストを取得する
	 * NOTICE:
	 * 		失敗など通常はfalseを返すが今回はarray()を返す。
	 * CREATE: 2016.10.20 aoyama
	 * *********************************** */
	public function get_match_list($thread_id, $pd = 0, $pp = 20) {

		//パラメータチェック
		if (StaticFunction::is_empty($thread_id) || !InputVali::is_num($thread_id)) {
			return array();
		}

		$data = $this->query("
			SELECT
				up.user_id,
				up.nickname,
				up.system_id
			FROM
				" . $this->table_match . " AS tm
			LEFT JOIN
				user_public AS up
			ON
				tm.user_id = up.user_id
			WHERE
				tm.thread_id = " . DbCast::id($thread_id) . "
				AND
				tm.active=" . DbCast::integer(DB_ACTIVE_ON) . "
			LIMIT
				" . ($pd * $pp) . ", " . $pp
		);
		//エラー・空の場合
		if ($this->db_select_check_error($data) || $this->db_select_check_empty($data)) {
			return array();
		}

		return $data;
	}

	/*	 * **********************************
	 * NAME  : match_num
	 * INPUT : thread_id / string / コミュニティID
	 * OUTPUT:
	 * 		true / 既に登録されている
	 * 		false / 登録されていない
	 * DESC  :
	 * 		コミュニティに参加している人数取得用メソッド
	 * NOTICE:
	 * CREATE: 2016.10.20 aoyama
	 * *********************************** */
	public function match_num($thread_id) {

		$match_count = $this->query("
			SELECT
				COUNT(tm.thread_id) AS num
			FROM
				" . $this->table_match . " AS tm
			WHERE
				tm.thread_id = " . DbCast::id($thread_id) . "
				AND
				tm.active = " . DB_ACTIVE_ON
		);

		if (!$match_count) {
			return 0;
		}
		return (int) $match_count[0]['num']; //intキャストは必須！
	}

	/*	 * **********************************
	 * NAME  : registered_community
	 * INPUT : user_id / string / ユーザID
	 *         thread_id / string / コミュニティID
	 * OUTPUT:
	 * 		true / 既に登録されている
	 * 		false / 登録されていない
	 * DESC  :
	 * 		コミュニティに参加しているかのチェック用メソッド
	 * NOTICE:
	 * CREATE: 2016.10.20 aoyama
	 * *********************************** */
	public function registered_community($user_id, $thread_id) {

		$already = $this->query("
			SELECT
				COUNT(tm.thread_id) AS num
			FROM
				" . $this->table_match . " AS tm
			WHERE
				tm.user_id = " . DbCast::id($user_id) . "
				AND
				tm.thread_id = " . DbCast::id($thread_id) . "
				AND
				tm.active = " . DB_ACTIVE_ON
		);

		if ($already[0]['num'] > 0) {
			return true;
		} else {
			return false;
		}
	}

	/*	 * **********************************
	 * NAME  : entry_community
	 * INPUT : param_list / array / 登録したいカラム名配列
	 * OUTPUT: db_shell_insert()のレスポンス(成功時：user_id, 失敗時:false)
	 * DESC  :
	 *  コミュニティに参加するモデル
	 * NOTICE:
	 * CREATE: 2016.10.20 aoyama
	 * *********************************** */
	public function entry_community($param_list) {
		return $this->db_shell_insert($this->table_match, $param_list);
	}

	/*	 * **********************************
	 * NAME  : leave_community
	 * INPUT : 
	 * 		$user_id / int / ユーザーID
	 * 		$thread_id / int / コミュニティのID
	 * OUTPUT: 
	 * 		成功時：true
	 * 		失敗時:false
	 * DESC  :
	 * 		コミュニティから外れるモデル
	 * 		ここでは自分が管理者か？などはチェックしないので
	 * 		コントローラー側で調整がチェックすること！
	 * NOTICE:
	 * CREATE: 2016.11.1 aoyama
	 * *********************************** */
	public function leave_community($user_id, $thread_id) {
		
		//ハッピーさんアカウントは解除させない
		if ($target_id == CONF::read("MASTER_USER.USER_ID")) {
			return false;
		}

		$query = "
			DELETE
			FROM
				" . $this->table_match . "
			WHERE 
				user_id=" . DbCast::id($user_id) . "
				AND
				thread_id=" . DbCast::id($thread_id) . "
			";

		$data = $this->exec($query);

		//エラー・空の場合
		if ($data) {
			//DELETE 処理なのでログに残す
			LOGS_DELETE($query);

			return true;
		}

		return false;
	}

	/*	 * **********************************
	 * NAME  : get_category_list
	 * INPUT : 
	 * OUTPUT: array / カテゴリ配列
	 * DESC  :
	 *  メソッド
	 * NOTICE:
	 * CREATE: 2016.10.19 aoyama
	 * *********************************** */
	public function get_category_list() {

		$categoryArray = $this->query("
			SELECT "
			/* user_public */ . "
				cm.category_id,
				cm.category_name,
				cm.category_comment
			FROM
				" . $this->category_master . " AS cm
			WHERE
				cm.active=" . DB_ACTIVE_ON . "
			ORDER BY
				cm.sort_num ASC"
		);
		foreach ($categoryArray AS $val) {
			$ret[$val['category_id']] = $val['category_name'];
		}
		return $ret;
	}

	/*	 * **********************************
	 * NAME  : regist
	 * INPUT : param_list / array / 登録したいカラム名配列
	 * OUTPUT: db_shell_insert()のレスポンス(成功時：user_id, 失敗時:false)
	 * DESC  :
	 *  INSERT
	 * NOTICE:
	 * CREATE: 2016.10.19 aoyama
	 * *********************************** */
	public function post_community($param_list) {
		return $this->db_shell_insert($this->table_thread, $param_list);
	}

	/*	 * **********************************
	 * NAME  : post_response
	 * INPUT : param_list / array / 登録したいカラム名配列
	 * OUTPUT: db_shell_insert()のレスポンス(成功時：user_id, 失敗時:false)
	 * DESC  :
	 *  コミュニティのコメントをINSERT
	 * NOTICE:
	 * CREATE: 2016.10.20 aoyama
	 * *********************************** */
	public function post_response($param_list) {
		return $this->db_shell_insert($this->table_response, $param_list);
	}

	/*	 * **********************************
	 * NAME  : edit_response
	 * INPUT : param_list / array / 登録したいカラム名配列
	 * OUTPUT: db_shell_insert()のレスポンス(成功時：user_id, 失敗時:false)
	 * DESC  :
	 *  コミュニティのコメントをINSERT
	 * NOTICE:
	 * CREATE: 2016.10.20 aoyama
	 * *********************************** */
	public function edit_response($param_list,$condition) {
		return $this->db_shell_update($this->table_response, $param_list,$condition);
	}
	
	/*	 * **********************************
	 * NAME  : delete_response
	 * INPUT : param_list / array / 登録したいカラム名配列
	 * OUTPUT: db_shell_insert()のレスポンス(成功時：user_id, 失敗時:false)
	 * DESC  :
	 *  コミュニティのコメントを削除
	 * NOTICE:
	 * CREATE: 2016.10.30 aoyama
	 * *********************************** */
	public function delete_response($param_list,$condition) {
		return $this->db_shell_update($this->table_response, $param_list,$condition);
	}	
	
	/*	 * **********************************
	 * NAME  : get_response_list
	 * INPUT :
	 * 		$thread_id / int / コミュニティID
	 * 		$pd  / int / paged
	 * 		$pp / int / post per page
	 * OUTPUT: array / コメント一覧
	 * DESC  :
	 *  レスポンスリストを取得する
	 * NOTICE:
	 * 
	 * CREATE: 2016.10.20 aoyama
	 * *********************************** */
	public function get_response_list($thread_id, $pd = 0, $pp = 20) {

		$data = $this->query("
			SELECT
				tr.thread_id,
				tr.response_text,
				tr.image_file,
				tr.user_id,
				tr.response_id,
				tr.update_time,
				tr.like_count,
				up.user_id,
				up.system_id,
				up.nickname
			FROM
				" . $this->table_response . " AS tr
			LEFT JOIN
				" . $this->user_public . " AS up
			ON
				tr.user_id = up.user_id
			WHERE 
				tr.active=" . DbCast::integer(DB_ACTIVE_ON) . "
				AND
				tr.thread_id = " . DbCast::id($thread_id) . "
			ORDER BY
				tr.create_time DESC
			LIMIT
				" . ($pd * $pp) . ", " . $pp
		);
		//エラー・空の場合
		if ($this->db_select_check_error($data) || $this->db_select_check_empty($data)) {
			return false;
		}

		return $data;
	}

    /**
     * コメントリストを取得する
     * INPUT :
     * 		$thread_id / int / コミュニティID
     * 		$pd  / int / paged
     * 		$pp / int / post per page
     * OUTPUT: array / コメント一覧
     * CREATE: 2017.09.14 aoyama
     * *********************************** */
    public function get_comment_list($thread_ids) {

        //カテゴリ指定がある場合は絞り込み
        if (StaticFunction::is_empty($thread_ids)) {
            return array();
        }

        $in_id = implode(",",$thread_ids);

        $data = $this->query("
			SELECT
				cc.response_id,
				cc.comment_id,
				cc.comment_text,
				cc.update_time,
				up.user_id,
				up.system_id,
				up.nickname
			FROM
				" . $this->community_comment . " AS cc
			LEFT JOIN
				" . $this->user_public . " AS up
			ON
				cc.user_id = up.user_id
			WHERE 
				cc.active=" . DbCast::integer(DB_ACTIVE_ON) . "
				AND
				cc.response_id IN (" . $in_id . ")
			ORDER BY
				cc.create_time ASC"
        );
        //エラー・空の場合
        if ($this->db_select_check_error($data) || $this->db_select_check_empty($data)) {
            return array();
        }

        return $data;
    }

    /*	 * **********************************
	 * NAME  : get_response_num
	 * INPUT : $thread_id / int / コミュニティID
	 * OUTPUT: string / コメントの数
	 * DESC  :
	 *  コメント総数を取得する
	 * NOTICE:
	 * CREATE: 2016.10.19 aoyama
	 * *********************************** */
	public function get_response_num($thread_id) {

		$where = "";

		$data = $this->query("
			SELECT
				count(tr.thread_id) AS num
			FROM
				" . $this->table_response . " AS tr
 			WHERE 
				tr.active=" . DbCast::integer(DB_ACTIVE_ON) . "
				AND
				tr.thread_id = " . DbCast::id($thread_id)
		);
		//エラー・空の場合
		if ($this->db_select_check_error($data) || $this->db_select_check_empty($data)) {
			return 0;
		}

		return $data[0]['num'];
	}

	/*	 * **********************************
	 * NAME  : get_thread_list
	 * INPUT :
	 * 		$category / int / カテゴリID
	 * 		$pd  / int / paged
	 * 		$pp / int / post per page
	 * OUTPUT: array / コミュニティ一覧
	 * DESC  :
	 *  コミュニティリストを取得する
	 * NOTICE:
	 * 
	 * CREATE: 2016.10.19 aoyama
	 * *********************************** */
	public function get_thread_list($pd = 0, $pp = 20, $category = null) {

		$where = "";

		//カテゴリ指定がある場合は絞り込み
		if (!StaticFunction::is_empty($category)) {
			$where = " AND category_id = " . DbCast::integer($category) . " ";
		}

		$data = $this->query("
			SELECT
				th.thread_id,
				th.community_name,
				th.community_detail,
				th.category_id,
				th.topcom_flg,
				th.image_file
			FROM
				" . $this->table_thread . " AS th
			WHERE 
				th.active=" . DbCast::integer(DB_ACTIVE_ON) . "
				" . $where . "
			ORDER BY
				th.update_time DESC
			LIMIT
				" . ($pd * $pp) . ", " . $pp
		);
		//エラー・空の場合
		if ($this->db_select_check_error($data) || $this->db_select_check_empty($data)) {
			return false;
		}

		return $data;
	}

	/*	 * **********************************
	 * NAME  : getTopCommunityList
	 * INPUT :
	 * OUTPUT: array / コミュニティ一覧
	 * DESC  :
	 *  トップコミュニティリストを取得する
	 * NOTICE:
	 * CREATE: 2017.08.12 aoyama
	 * *********************************** */
    public function getTopCommunityList() {

        $data = $this->query("
			SELECT
				th.thread_id,
				th.community_name,
				th.community_detail,
				th.category_id,
				th.image_file
			FROM
				" . $this->table_thread . " AS th
			WHERE 
				th.active=" . DbCast::integer(DB_ACTIVE_ON) . "
				AND
				th.topcom_flg = " . DbCast::string(TOPCOM_FLG_ON) . "
			ORDER BY
				th.update_time DESC
        ");
        //エラー・空の場合
        if ($this->db_select_check_error($data) || $this->db_select_check_empty($data)) {
            return false;
        }

        return $data;
    }

	/*	 * **********************************
	 * NAME  : get_thread_num
	 * INPUT : $category / int / カテゴリID
	 * OUTPUT: string / スレッドの数
	 * DESC  :
	 *  スレッド総数を取得する
	 * NOTICE:
	 * CREATE: 2016.10.19 aoyama
	 * *********************************** */
	public function get_thread_num($category = null) {

		$where = "";

		//
		if (!StaticFunction::is_empty($category)) {
			$where = " AND category_id = " . DbCast::integer($category) . " ";
		}

		$data = $this->query("
			SELECT
				count(th.thread_id) AS num
			FROM
				" . $this->table_thread . " AS th
 			WHERE 
				th.active=" . DbCast::integer(DB_ACTIVE_ON) . "
				" . $where
		);
		//エラー・空の場合
		if ($this->db_select_check_error($data) || $this->db_select_check_empty($data)) {
			return 0;
		}

		return $data[0]['num'];
	}

	/*	 * **********************************
	 * NAME  : get_detail_by_id
	 * INPUT : $thread_id / integer / コミュニティID
	 * OUTPUT: array / データ
	 * DESC  :
	 *  $thread_idからコミュニティの詳細情報を取得する
	 * NOTICE:
	 * CREATE: 2016.10.19 aoyama
	 * *********************************** */
	public function get_detail_by_id($thread_id) {

		//パラメータチェック
		if (StaticFunction::is_empty($thread_id) || !InputVali::is_num($thread_id)) {
			return false;
		}

		return $this->query("
			SELECT 
				th.thread_id,
				th.create_time,
				th.update_time,
				th.community_name,
				th.community_detail,
				th.topcom_flg,
				th.topcom_image_file,
				th.community_detail,
				th.topcom_owner_user_id,
				th.topcom_description,
				th.topcom_url,
				th.topcom_twitter,
				th.topcom_facebook,
				th.topcom_instagram,
				th.topcom_youtube,
				th.category_id,
				th.user_id,
				th.active,
				th.image_file,
				up.nickname,
				up.system_id
			FROM
				" . $this->table_thread . " AS th
			LEFT JOIN
				user_public AS up
			ON
				th.user_id = up.user_id
			WHERE
				th.thread_id=" . DbCast::id($thread_id) . "
				AND th.active=" . DB_ACTIVE_ON
		);
	}

	/*	 * **********************************
	 * NAME  : update_thread
	 * DESC  :
	 *  UPDATE
	 * NOTICE:
	 * CREATE: 2016.12.21 aoyama
	 * *********************************** */
	public function update_thread($param_array) {
		LOGS_DBG_LV1('*** QUERY [UPDATE] START ***');
		
		
		$param_list = array(
            "community_name"       => DbCast::string($param_array['community_name']),
            "community_detail"     => DbCast::string($param_array['community_detail']),
            "topcom_owner_user_id" => DbCast::integer($param_array['topcom_owner_user_id']),
            "topcom_description"   => DbCast::string($param_array['topcom_description']),
            "topcom_url"           => DbCast::string($param_array['topcom_url']),
            "topcom_twitter"       => DbCast::string($param_array['topcom_twitter']),
            "topcom_facebook"      => DbCast::string($param_array['topcom_facebook']),
            "topcom_instagram"     => DbCast::string($param_array['topcom_instagram']),
            "topcom_youtube"       => DbCast::string($param_array['topcom_youtube']),
            "category_id"          => DbCast::integer($param_array['category_id']),
            'update_time'          => DbCast::datetime($param_array['update_time'])
        );
		
		if(!StaticFunction::is_empty($param_array['image_file'])) {
			$param_list += array("image_file" => DbCast::string($param_array['image_file']));
		}
        if(!StaticFunction::is_empty($param_array['topcom_image_file'])) {
            $param_list += array("topcom_image_file" => DbCast::string($param_array['topcom_image_file']));
        }

		$condition = array(
			"WHERE" => array(
				"thread_id" => DbCast::id($param_array['tid'])
			)
		);
		return $this->db_shell_update($this->table_thread,$param_list, $condition);
	}	
	
	/*	 * **********************************
	 * NAME  : delete_thread
	 * INPUT : $thread_id / int / コミュニティID
	 *         $user_id / array / ユーザーID
	 * OUTPUT: true / false
	 * DESC  :
	 *		コミュニティを削除するメソッド
	 * NOTICE:
	 * CREATE: 2016.10.28 aoyama
	 * *********************************** */
	public function delete_thread($thread_id, $user_id) {

		$param_list = array(
			"active" => DB_ACTIVE_OFF
		);

		$condition = array(
			"WHERE" => array(
				"thread_id" => DbCast::id($thread_id),
				"user_id" => DbCast::id($user_id)
			)
		);

		$ret = $this->db_shell_update($this->table_thread, $param_list, $condition);

		if ($ret == 1) {
			return true;
		}
		return false;
	}

    /**
	 * admin権限（happyさんアカウント）チェック
     * @param $user_id
     * @return bool
     */
	public function is_admin($user_id)
	{
        if($user_id == CONF::read("MASTER_USER.USER_ID")){
            return true;
        } else {
            return false;
		}
	}

    /**
     * 記事作成者か判定
     * @param $user_id
     * @param $thread_id
     * @return bool
     */
    public function is_owner_thread($user_id,$thread_id)
    {

        // コミュニティ作成者は管理者とする
        $thread = $this->query("
			SELECT 
				count(*) AS num
			FROM
				" . $this->table_thread . " AS ct
			WHERE
				ct.active=" . DB_ACTIVE_ON . "
			AND
				ct.thread_id = ".DbCast::id($thread_id) ."
            AND
            	ct.user_id = ".DbCast::id($user_id)
        );
        if ($thread[0]['num'] > 0) {
            return true;
        }
        return false;
    }

    /*	 * **********************************
     * NAME  : get_community_author
     * INPUT :
     * OUTPUT: array / カテゴリ配列
     * DESC  :
     *  コミュニティのコミュニティ管理者かどうかを判定
     * NOTICE:
     * CREATE: 2016.10.19 aoyama
     * *********************************** */
    public function is_community_admin($user_id,$thread_id) {

        // 公式アカウントは無条件に管理者とする
    	if($user_id == CONF::read("MASTER_USER.USER_ID")){
            return true;
		}

		// コミュニティ作成者は管理者とする
        $thread = $this->query("
			SELECT 
				count(*) AS num
			FROM
				" . $this->table_thread . " AS ct
			WHERE
				ct.active=" . DB_ACTIVE_ON . "
			AND
				ct.thread_id = ".DbCast::id($thread_id) ."
            AND
            	ct.user_id = ".DbCast::id($user_id)
        );
        if ($thread[0]['num'] > 0) {
            return true;
        }

		// 関連アカウントも管理者とする
        $author = $this->query("
			SELECT 
				count(*) AS num
			FROM
				" . $this->community_author . " AS ca
			WHERE
				ca.active=" . DB_ACTIVE_ON . "
			AND
				ca.thread_id = ".DbCast::id($thread_id) ."
            AND
            	ca.user_id = ".DbCast::id($user_id)
        );
        if ($author[0]['num'] > 0) {
            return true;
        }

        return false;
    }

    /*	 * **********************************
 * NAME  : get_community_author
 * INPUT :
 * OUTPUT: array / カテゴリ配列
 * DESC  :
 *  トップコミュニティのコミュニティ管理者一覧を取得
 * NOTICE:
 * CREATE: 2017.09.10 aoyama
 * *********************************** */
    public function list_comm_author($thread_id) {

        $author = $this->query("
			SELECT 
				up.nickname
				,up.user_id
				,ca.group_id
				,up.system_id
				,up.system_user_id
			FROM
				" . $this->community_author . " AS ca
			LEFT JOIN
				user_public AS up
			ON
				ca.user_id = up.user_id
			WHERE
				ca.active=" . DB_ACTIVE_ON . "
			AND
				ca.thread_id = ".DbCast::id($thread_id)
        );

        return $author;
    }

	/*	 * **********************************
	 * NAME  : select
	 * INPUT : select_list / array / 取得したいカラム名配列
	 *         condition / array / whereに用いる検索条件の連想配列
	 * OUTPUT: db_shecll_select()のレスポンス
	 * DESC  :
	 *  SELECT
	 * NOTICE:
	 * CREATE: 2016.10.17 aoyama
	 * *********************************** */
	public function select($select_list, $condition = NULL) {
		LOGS_DBG_LV1('*** QUERY [SELECT] START ***');
		return $this->db_shell_select($this->table_name, $select_list, $condition);
	}

	/*	 * **********************************
	 * NAME  : update
	 * INPUT : param_list / array / 更新したいカラム名配列
	 *         condition / array / whereに用いる検索条件の連想配列
	 * OUTPUT: db_shecll_update()のレスポンス
	 * DESC  :
	 *  UPDATE
	 * NOTICE:
	 * CREATE: 2016.10.17 aoyama
	 * *********************************** */
	public function update($param_list, $condition = NULL) {
		LOGS_DBG_LV1('*** QUERY [UPDATE] START ***');
		return $this->db_shell_update($this->table_name, $param_list, $condition);
	}

    public function update_response($param_list, $condition = NULL) {
        LOGS_DBG_LV1('*** QUERY [UPDATE] START ***');
        return $this->db_shell_update($this->table_response, $param_list, $condition);
    }

	public function is_entry_author($user_array)
	{
        $author = $this->query("
			SELECT
				COUNT(*) AS num
			FROM
				" . $this->community_author . " AS ca
			WHERE
				ca.user_id = " . DbCast::id($user_array['user_id']) . "
				AND
				ca.thread_id = " . DbCast::id($user_array['thread_id']) . "
				AND
				ca.active = " . DB_ACTIVE_ON
        );

        if ($author[0]['num'] > 0) {
            return true;
        } else {
            return false;
        }
	}

	public function entry_author($user_array)
	{
        return $this->db_shell_insert($this->community_author, $user_array);
    }

    public function entry_author_group($group_array)
    {
        return $this->db_shell_insert($this->community_author_group, $group_array);
    }

    public function delete_comment($param_list, $condition = NULL) {
        LOGS_DBG_LV1('*** QUERY [UPDATE] START ***');
        return $this->db_shell_update($this->community_comment, $param_list, $condition);
    }

	public function list_comm_author_group($thread_id)
    {
        $group = $this->query("
			SELECT 
				cag.group_name
				,cag.id
			FROM
				" . $this->community_author_group . " AS cag
			WHERE
				cag.active=" . DB_ACTIVE_ON . "
			AND
				cag.thread_id = " . DbCast::id($thread_id)."
			ORDER BY 
				cag.sort_id ASC"
        );

        return $group;
    }

    public function delete_author_group($thread_id)
	{
        $group = $this->query("
			DELETE 
			FROM
				" . $this->community_author_group . "
			WHERE
				thread_id = " . DbCast::id($thread_id)
        );
        $author = $this->query("
			DELETE 
			FROM
				" . $this->community_author . "
			WHERE
				thread_id = " . DbCast::id($thread_id)
        );
        return $group;
	}

    public function post_response_comment($array)
    {
        return $this->db_shell_insert($this->community_comment, $array);
    }

    /**
     * @param $community_response_array
     * @param $user_id
     * @return array $ret
     */
    public function get_community_match_user($community_response_array,$user_id)
    {

        //パラメータチェック
        $ret = array();
        if (StaticFunction::is_empty($community_response_array) || !is_array($community_response_array) ) {
            return array();
        }

        $in_value = implode(",",$community_response_array);

        $query = "
			SELECT
				tm.user_id,
				tm.thread_id
			FROM
				" . $this->table_match . " AS tm
			WHERE
				tm.thread_id IN (" . $in_value . ")
				AND
				tm.user_id =" . DbCast::integer($user_id) . "
				AND
				tm.active=" . DbCast::integer(DB_ACTIVE_ON);


        $data = $this->query($query);
        //エラー・空の場合
        if ($this->db_select_check_error($data) || $this->db_select_check_empty($data)) {
            return array();
        }

        foreach($data AS $value){
            $ret[] = $value['thread_id'];
        }
        return $ret;
    }

    public function get_thread_from_comment_id($comment_id)
    {
        $query = "
			SELECT 
				ct.thread_id
			FROM
				" . $this->community_comment . " AS cc
			LEFT JOIN
				" . $this->table_response . " AS cr
			ON
			    cc.response_id = cr.response_id
			LEFT JOIN
				" . $this->table_thread . " AS ct
			ON
			    cr.thread_id = ct.thread_id
			WHERE
				cc.comment_id = ".DbCast::id($comment_id)
        ;

        $thread = $this->query($query);
        return $thread;
    }

    public function get_thread_from_response_id($response_id)
    {
        $query = "
			SELECT 
				cr.thread_id
			FROM
				" . $this->table_response . " AS cr
			WHERE
				cr.response_id = ".DbCast::id($response_id)
        ;

        $thread = $this->query($query);
        return $thread;
    }

    /**
 * コミュニティレスポンス用の画像をDBに登録する
 * INPUT : $user_id / int / user_id
 * OUTPUT:
 * 		boolean
 * DESC  :
 * NOTICE:
 * CREATE: 2017.09.20 aoyama
 */
    public function add_community_response_file($response_id,$file_name,$time,$sort_num = 0) {

        if(StaticFunction::is_empty($response_id) OR StaticFunction::is_empty($file_name)) {
            return false;
        }

        $param_array = array(
            "response_id"  => DbCast::id($response_id)
            ,"create_time" => $time
            ,"update_time" => $time
            ,"sort_number" => DbCast::integer($sort_num)
            ,"file_name"   => DbCast::string($file_name)
        );

        $this->db_shell_insert($this->community_response_file, $param_array);
    }

    /**
     * コミュニティレスポンス用の画像をDBに登録する
     * INPUT : $user_id / int / user_id
     * OUTPUT:
     *        boolean
     * DESC  :
     * NOTICE:
     * CREATE: 2017.09.20 aoyama
     */
    public function get_community_response_image($thread_id,$response_id) {

        $file_url = array();

        $data = $this->query("
			SELECT
				file_name
			FROM
				". $this->community_response_file ."
			WHERE
				response_id = ".DbCast::id($response_id). "
			ORDER BY
				update_time DESC, sort_number
		");

        if($data){
            foreach($data AS $value) {
                $file_url[] = CONF::read('URL_PUBLIC_ROOT') . "images/community/" . $thread_id . "/" . $value['file_name'];
            }
        }
        return $file_url;
    }

    /*	 * **********************************
 * NAME  : delete_timeline_file
 * INPUT : $timeline_id
 * OUTPUT:
 * DESC  :
 * 		タイムラインのファイルを削除する
 * NOTICE:
 * CREATE: 2017.2.13 aoyama
 * *********************************** */
    public function delete_response_file($thread_id,$response_id,$file_name) {
        $query = "
			DELETE
			FROM
				" . $this->community_response_file . "
			WHERE 
				response_id=" . DbCast::id($response_id) . "
				AND
				file_name=" . DbCast::string($file_name) . "
			";
        $data = $this->exec($query);

        //削除できた場合はファイルの削除処理も実行
        if ($data) {
            //DELETE 処理なのでログに残す
            LOGS_DELETE($query);

            $image = new Image();

            $target_dir = DIR_PUBLIC_IMG . DS . "community" . DS . $thread_id . DS;
            $image->delete($target_dir, $file_name);

            return true;
        }
        return false;
    }

    /**
	*使用しない
     */
	public function get_timeline_for_index()
    {
        $timeline = $this->query("
        (
            SELECT
                'timeline' AS type
                ,timeline_id AS id
                ,update_time
                ,'' AS community_name
            FROM
                timeline AS tl
            WHERE
                tl.publication=1
            ORDER BY
                update_time DESC
            LIMIT 0,20
        )
        UNION
        (
            SELECT
                'community' AS type
                ,ct.thread_id AS id
                ,cr.update_time
                ,ct.community_name
            FROM
                community_response AS cr
            LEFT JOIN
                community_thread AS ct
            ON
                cr.thread_id = ct.thread_id
            WHERE
                ct.topcom_flg = 1
            AND
                ct.active = " . DB_ACTIVE_ON . "
            ORDER BY
                cr.update_time DESC
        )
            ORDER BY
                update_time DESC
        LIMIT 0,20
        ");

        return $timeline;
    }
}