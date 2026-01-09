<?php

/* * **********************************
 * NAME:TimelineModel
 * DESC:
 *  タイムラインテーブル用モデルクラス
 *  上記テーブルに対してアクセス(クエリなど)する場合は
 *  当該クラスにて行うこと！
 * NOTICE:
 *  基本的にはDbShellクラスを継承し、そちらでPDOインスタンスアクセスを行う
 *  場合によっては当該クラスで直接触ることもあるかも知れないが、
 *  できるだけDbShellクラスにて行うこと！
 * CREATE: 2016.10.21 aoyama
 * *********************************** */
class TimelineModel extends DbShell {

	private $user_public = "user_public";
	private $timeline = "timeline";
	private $timeline_response = "timeline_response";
	private $timeline_file = "timeline_file";
	private $mypage_limit = 200;

	public function __construct() {
		parent::__construct();
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
	public function delete_timeline_file($system_id,$timeline_id,$file_name) {	
		$query = "
			DELETE
			FROM
				" . $this->timeline_file . "
			WHERE 
				timeline_id=" . DbCast::id($timeline_id) . "
				AND
				file_name=" . DbCast::string($file_name) . "
			";
		$data = $this->exec($query);

		//削除できた場合はファイルの削除処理も実行
		if ($data) {
			//DELETE 処理なのでログに残す
			LOGS_DELETE($query);
			
			$image = new Image();
			
			$target_dir = DIR_PUBLIC_IMG . DS . "user" . DS . $system_id . DS . $timeline_id . DS;
			$image->delete($target_dir, $file_name);

			return true;
		}
		return false;
	}
	
	
	/*	 * **********************************
	 * NAME  : get_timeline_image
	 * INPUT : $timeline_id
	 * OUTPUT: 
	 * 		
	 * DESC  :
	 * 		タイムラインの画像を取得する
	 * NOTICE:
	 * CREATE: 2016.12.16 aoyama
	 * *********************************** */
	public function get_timeline_image($system_id, $timeline_id) {
		
		$file_url = array();
		
		$data = $this->query("
			SELECT
				file_name
			FROM
				". $this->timeline_file ."
			WHERE
				timeline_id = ".DbCast::id($timeline_id). "
			ORDER BY
				update_time DESC, sort_number
		");

		if($data){
			foreach($data AS $value) {
				$file_url[] = CONF::read('URL_PUBLIC_ROOT') . "images/user/" . $system_id . "/" . $timeline_id . "/" . $value['file_name'];
			}
		}
		return $file_url;		
	}	
	/*	 * **********************************
	 * NAME  : insert_file
	 * INPUT : $user_id / int / user_id
	 * OUTPUT: 
	 * 		boolean
	 * DESC  :
	 * 		タイムラインの画像をDB登録する
	 * NOTICE:
	 * CREATE: 2017.2.13 aoyama
	 * *********************************** */
	public function insert_file($timeline_id,$file_name,$time,$sort_num = 0) {
		
		if(StaticFunction::is_empty($timeline_id) OR StaticFunction::is_empty($file_name)) {
			return false;
		}
		
		$param_array = array(
			"timeline_id" => DbCast::id($timeline_id)
			,"create_time" => $time
			,"update_time" => $time
			,"sort_number" => DbCast::integer($sort_num)
			,"file_name" => DbCast::string($file_name)
		);
		
		$this->db_shell_insert($this->timeline_file, $param_array);
	}	
	
	/*	 * **********************************
	 * NAME  : get_timeline_profile
	 * INPUT : $user_id / int / user_id
	 * OUTPUT: 
	 * 		array
	 * DESC  :
	 * 		happyさんのタイムラインを取得
	 * NOTICE:
	 * CREATE: 2016.12.16 aoyama
	 * *********************************** */
	public function get_timeline_happy($user_id, $pd = 0, $pp = 20) {

		$data = $this->query("
			(
				SELECT
					'response' AS type,
					ct.community_name AS thread_name,
					cr.response_id AS code,
					cr.response_text AS text,
					cr.update_time AS update_time,
					cr.user_id AS user_id,
					cr.image_file AS file_name,
					null AS publication,
					cr.thread_id AS thread_id,
					cr.like_count AS like_count,
					up.nickname AS nickname,
					up.system_id AS system_id
				FROM
					community_response AS cr
				LEFT JOIN
					user_public AS up
				ON
					cr.user_id = up.user_id
				LEFT JOIN
					community_thread AS ct
				ON
					cr.thread_id = ct.thread_id
				LEFT JOIN
					community_match AS cm
				ON
					cr.thread_id = cm.thread_id
				WHERE
					cr.user_id = " . DbCast::id($user_id) . "
					AND
					cm.user_id = " . DbCast::id($user_id) . "
					AND
					cr.active = " . DB_ACTIVE_ON . "
					AND
					ct.active = " . DB_ACTIVE_ON . "
				LIMIT
					0, " . $this->mypage_limit . "
			)
			UNION
			(
				SELECT
					'timeline' AS type,
					null AS thread_name,
					tl.timeline_id AS code,
					tl.comment AS text,
					tl.update_time AS update_time,
					tl.user_id AS user_id,
					tl.image_file AS file_name,
					tl.publication AS publication,
					null AS thread_id,
					tl.like_count AS like_count,
					up2.nickname AS nickname,
					up2.system_id AS system_id
				FROM
					timeline AS tl
				LEFT JOIN
					user_public AS up2
				ON
					tl.user_id = up2.user_id
				WHERE
					" /* または全公開しているもの */ . "
					tl.user_id = " . DbCast::id($user_id) . "
					AND
					tl.publication = " . TL_PUBLICATION_ALL . "
					AND
					tl.active = " . DB_ACTIVE_ON . "

				ORDER BY
					tl.update_time DESC
				LIMIT
					0, " . $this->mypage_limit . "
			)
			ORDER BY
				update_time DESC
			LIMIT
				" . ($pd * $pp) . "," . $pp . "	"
		);
		return $data;
	}	

	/*	 * **********************************
	 * NAME  : get_timeline_happy_num
	 * INPUT : $user_id / int / user_id
	 * OUTPUT: 
	 * 		array
	 * DESC  :
	 * 		happyさんのタイムラインを取得
	 * NOTICE:
	 * CREATE: 2016.12.16 aoyama
	 * *********************************** */
	public function get_timeline_happy_num($user_id) {

		$data = $this->query("
			SELECT SUM(code) AS tl_cunt FROM (
			(
			SELECT
				count(cr.response_id) AS code
			FROM
				community_response AS cr
			LEFT JOIN
				user_public AS up
			ON
				cr.user_id = up.user_id
			LEFT JOIN
				community_thread AS ct
			ON
				cr.thread_id = ct.thread_id
			LEFT JOIN
				community_match AS cm
			ON
				cr.thread_id = cm.thread_id
			WHERE
					cr.user_id = " . DbCast::id($user_id) . "
					AND
					cm.user_id = " . DbCast::id($user_id) . "
					AND
					cr.active = " . DB_ACTIVE_ON . "
					AND
					ct.active = " . DB_ACTIVE_ON . "
			LIMIT
				0, " . $this->mypage_limit . "
			)
			UNION ALL
			(
				SELECT
					count(tl.timeline_id) AS code
				FROM
					timeline AS tl
				LEFT JOIN
					user_public AS up2
				ON
					tl.user_id = up2.user_id
				WHERE
					tl.publication = " . TL_PUBLICATION_ALL . "
					AND
					tl.user_id = " . DbCast::id($user_id) . "
					AND
					tl.active = " . DB_ACTIVE_ON . "
				LIMIT
					0, " . $this->mypage_limit . "
									)
			) AS cts"
		);
		return $data[0]['tl_cunt'];
	}	
	

	/*	 * **********************************
	 * NAME  : get_timeline_profile
	 * INPUT : $user_id / int / user_id
	 * OUTPUT: 
	 * 		array
	 * DESC  :
	 * 		マイページTOPのタイムラインを取得
	 * NOTICE:
	 * CREATE: 2016.12.12 aoyama
	 * 		タイムラインの公開範囲設定
	 * *********************************** */
	public function get_timeline_profile($user_id, $pd = 0, $pp = 20, $viewer_id = 'self') {

		$data = $this->query("
			(
				SELECT
					'response' AS type,
					ct.community_name AS thread_name,
					cr.response_id AS code,
					cr.response_text AS text,
					cr.update_time AS update_time,
					cr.user_id AS user_id,
					cr.image_file AS file_name,
					null AS publication,
					cr.thread_id AS thread_id,
					cr.like_count AS like_count,
					up.nickname AS nickname,
					up.system_id AS system_id
				FROM
					community_response AS cr
				LEFT JOIN
					user_public AS up
				ON
					cr.user_id = up.user_id
				LEFT JOIN
					community_thread AS ct
				ON
					cr.thread_id = ct.thread_id
				LEFT JOIN
					community_match AS cm
				ON
					cr.thread_id = cm.thread_id
				WHERE
					cm.user_id = " . DbCast::id($user_id) . "
						AND
					cr.active = " . DB_ACTIVE_ON . "
						AND
					ct.active = " . DB_ACTIVE_ON . "
				ORDER BY cr.update_time DESC
				LIMIT
					0, " . $this->mypage_limit . "
			)
			UNION
			(
				SELECT
					'timeline' AS type,
					null AS thread_name,
					tl.timeline_id AS code,
					tl.comment AS text,
					tl.update_time AS update_time,
					tl.user_id AS user_id,
					tl.image_file AS file_name,
					tl.publication AS publication,
					null AS thread_id,
					tl.like_count AS like_count,
					up2.nickname AS nickname,
					up2.system_id AS system_id
				FROM
					timeline AS tl
				LEFT JOIN
					user_public AS up2
				ON
					tl.user_id = up2.user_id
				LEFT JOIN
					"/* friend_matchでフレンド分マッチング */ . "
					(	
						" /* まずは自分から申請しているパターン */ . "
						(
						SELECT
							fm1.user_id AS user_id,
							fm1.friend_id AS friend_id
						FROM
							friend_match AS fm1
						WHERE 
							fm1.user_id=" . DbCast::id($user_id) . "
							AND
							fm1.commit_status = 1
						)
						UNION
						" /* 申請されているパターン */ . "
						(
						SELECT
							fm2.friend_id AS user_id,
							fm2.user_id AS friend_id
						FROM
							friend_match AS fm2
						WHERE 
							fm2.friend_id=" . DbCast::id($user_id) . "
							AND
							fm2.commit_status = 1
						)
					) AS fm
				ON
					tl.user_id = fm.user_id
				WHERE
					(
						" /* フレンドに限り公開しているもの */ . "
						(
							tl.user_id = " . DbCast::id($user_id) . "
							AND
							fm.friend_id = " . DbCast::id($viewer_id) . "
							AND
							tl.publication = " . TL_PUBLICATION_FRIEND . "
						)
						OR
						" /* または全公開しているもの */ . "
						(
							tl.user_id = " . DbCast::id($user_id) . "
							AND
							tl.publication = " . TL_PUBLICATION_ALL . "
						)
					)
					AND
					tl.active = " . DB_ACTIVE_ON . "

				ORDER BY
					tl.update_time DESC
				LIMIT
					0, " . $this->mypage_limit . "
			)
			ORDER BY
				update_time DESC
			LIMIT
				" . ($pd * $pp) . "," . $pp . "	"
		);
		return $data;
	}

	
	/*	 * **********************************
	 * NAME  : get_timeline_count
	 * INPUT : $user_id / int / ユーザーID
	 * OUTPUT: 数値
	 * DESC  :
	 * 		マイページTOPのタイムラインの数を取得
	 * NOTICE:
	 * CREATE: 2016.10.27 aoyama
	 * *********************************** */
	public function get_timeline_profile_count($user_id, $viewer_id = 'self') {

		$data = $this->query("
			SELECT SUM(code) AS tl_cunt FROM (
			(
			SELECT
				count(cr.response_id) AS code
			FROM
				community_response AS cr
			LEFT JOIN
				user_public AS up
			ON
				cr.user_id = up.user_id
			LEFT JOIN
				community_thread AS ct
			ON
				cr.thread_id = ct.thread_id
			LEFT JOIN
				community_match AS cm
			ON
				cr.thread_id = cm.thread_id
			WHERE
				cm.user_id = " . DbCast::id($user_id) . "
					AND
				cr.active = " . DB_ACTIVE_ON . "
					AND
				ct.active = " . DB_ACTIVE_ON . "
			LIMIT
				0, " . $this->mypage_limit . "
			)
			UNION ALL
			(
			SELECT
				count(tl.timeline_id) AS code
			FROM
				timeline AS tl
			LEFT JOIN
				user_public AS up2
			ON
				tl.user_id = up2.user_id
			LEFT JOIN
				(	
					" /* まずは自分から申請しているパターン */ . "
					(
					SELECT
						fm1.user_id AS user_id,
						fm1.friend_id AS friend_id
					FROM
						friend_match AS fm1
					WHERE 
						fm1.user_id=" . DbCast::id($user_id) . "
						AND
						fm1.commit_status = 1
					)
					UNION
					" /* 申請されているパターン */ . "
					(
					SELECT
						fm2.friend_id AS user_id,
						fm2.user_id AS friend_id
					FROM
						friend_match AS fm2
					WHERE 
						fm2.friend_id=" . DbCast::id($user_id) . "
						AND
						fm2.commit_status = 1
					)
				) AS fm
			ON
				tl.user_id = fm.friend_id
			WHERE
				(
					" /* フレンドに限り公開しているもの */ . "
					(
						tl.user_id = " . DbCast::id($user_id) . "
						AND
						fm.friend_id = " . DbCast::id($viewer_id) . "
						AND
						tl.publication = " . TL_PUBLICATION_FRIEND . "
					)
					OR
					" /* または全公開しているもの */ . "
					(
						tl.user_id = " . DbCast::id($user_id) . "
						AND
						tl.publication = " . TL_PUBLICATION_ALL . "
					)
				)
				AND
				tl.active = " . DB_ACTIVE_ON . "
			ORDER BY
				tl.update_time DESC
			LIMIT
				0, " . $this->mypage_limit . "
			)
			) AS cts"
		);
		return $data[0]['tl_cunt'];
	}	
	
	/*	 * **********************************
	 * NAME  : get_timeline_public
	 * INPUT : $user_id / int / user_id
	 * OUTPUT: 
	 * 		array
	 * DESC  :
	 * 		マイページTOPのタイムラインを取得
	 * NOTICE:
	 * CREATE: 2016.10.21 aoyama
	 * UPDATE: 2016.10.31 aoyama
	 * 		メッセージはタイムラインに表示しない
	 * UPDATE: 2016.12.12 aoyama
	 * 		タイムラインの公開範囲を制限
	 * UPDATE: 2017.2.8 aoyama
	 *		レスポンスの時刻をtimelineに反映
	 * *********************************** */
	public function get_timeline_self($user_id, $pd = 0, $pp = 20, $viewer = 'self') {

		$data = $this->query("
			(
			SELECT
				'response' AS type,
				ct.community_name AS thread_name,
				cr.response_id AS code,
				cr.response_text AS text,
				cr.update_time AS update_time,
				cr.update_time AS sort_time,
				cr.user_id AS user_id,
				cr.image_file AS file_name,
				null AS publication,
				cr.thread_id AS thread_id,
				cr.like_count AS like_count,
				up.nickname AS nickname,
				up.system_id AS system_id
			FROM
				community_response AS cr
			LEFT JOIN
				user_public AS up
			ON
				cr.user_id = up.user_id
			LEFT JOIN
				community_thread AS ct
			ON
				cr.thread_id = ct.thread_id
			LEFT JOIN
				community_match AS cm
			ON
				cr.thread_id = cm.thread_id
			WHERE
			(
				cm.user_id = " . DbCast::id($user_id) . "
					AND
				cr.active = " . DB_ACTIVE_ON . "
					AND
				ct.active = " . DB_ACTIVE_ON . "
				)
				OR
			(
				ct.topcom_flg = " . DB_ACTIVE_ON . "
					AND
				cr.active = " . DB_ACTIVE_ON . "
					AND
				ct.active = " . DB_ACTIVE_ON . "
				)
			group by code
			order by code DESC
			LIMIT
				0, " . $this->mypage_limit . "
			)
			UNION
			(
			SELECT
				'timeline' AS type,
				null AS thread_name,
				tl.timeline_id AS code,
				tl.comment AS text,
				tl.create_time AS update_time," /* update 2017.2.8 update_timeからcreate_time */ . "
				tl.update_time AS sort_time," /* 　　　　sort用に新設 */ . "
				tl.user_id AS user_id,
				tl.image_file AS file_name,
				tl.publication AS publication,
				null AS thread_id,
				tl.like_count AS like_count,
				up2.nickname AS nickname,
				up2.system_id AS system_id
			FROM
				timeline AS tl
			LEFT JOIN
				user_public AS up2
			ON
				tl.user_id = up2.user_id
			LEFT JOIN
				(	
					" /* まずは自分から申請しているパターン */ . "
					(
					SELECT
						fm1.user_id AS user_id,
						fm1.friend_id AS friend_id
					FROM
						friend_match AS fm1
					WHERE 
						fm1.user_id=" . DbCast::id($user_id) . "
						AND
						fm1.commit_status = 1
					)
					UNION
					" /* 申請されているパターン */ . "
					(
					SELECT
						fm2.friend_id AS user_id,
						fm2.user_id AS friend_id
					FROM
						friend_match AS fm2
					WHERE 
						fm2.friend_id=" . DbCast::id($user_id) . "
						AND
						fm2.commit_status = 1
					)
				" /* fm.friend_id が友達のIDとなる  */ . "
				) AS fm
			ON
				tl.user_id = fm.friend_id
			WHERE
				(
					" /* フレンドに限らず全公開  期間限定（2017.2.9～ユーザーが増えるまで。 */ . "
					tl.publication = " . TL_PUBLICATION_ALL . "
					OR
					" /* フレンドに限らず全公開  ここまで */ . "
					(
					" /* フレンド関係 AND （全公開 or　友達のみに公開） */ . "
						fm.user_id = " . DbCast::id($user_id) . "
						AND
						(
							tl.publication = " . TL_PUBLICATION_ALL . "
								OR
							tl.publication = " . TL_PUBLICATION_FRIEND . "
						)
					)
					OR
					" /* または自分自身の投稿 */ . "
					tl.user_id = " . DbCast::id($user_id) . "
				)
				AND
				tl.active = " . DB_ACTIVE_ON . "

			ORDER BY
				tl.update_time DESC
			LIMIT
				0, " . $this->mypage_limit . "
			)
			ORDER BY
				sort_time DESC
			LIMIT
				" . ($pd * $pp) . "," . $pp . "	"
		);
		return $data;
	}

    /*	 * **********************************
 * NAME  : get_timeline_public
 * INPUT : $user_id / int / user_id
 * OUTPUT:
 * 		array
 * DESC  :
 * 		TOPページに表示するタイムラインを取得
 * NOTICE:
 * CREATE: 2017.09.13 aoyama
 * *********************************** */
    public function get_timeline_for_index($pd = 0, $pp = 20) {

        $data = $this->query("
			(
			SELECT
				'response' AS type,
				ct.community_name AS thread_name,
				cr.response_id AS code,
				cr.response_text AS text,
				cr.update_time AS update_time,
				cr.update_time AS sort_time," /* update 2017.2.8 sort用に新設 */ . "
				cr.user_id AS user_id,
				cr.image_file AS file_name,
				null AS publication,
				cr.thread_id AS thread_id,
				cr.like_count AS like_count,
				up.nickname AS nickname,
				up.system_id AS system_id
			FROM
				community_response AS cr
			LEFT JOIN
				user_public AS up
			ON
				cr.user_id = up.user_id
			LEFT JOIN
				community_thread AS ct
			ON
				cr.thread_id = ct.thread_id
			WHERE
				cr.active = " . DB_ACTIVE_ON . "
					AND
				ct.active = " . DB_ACTIVE_ON . "
					AND
				ct.topcom_flg = 1
			ORDER BY cr.update_time DESC
			LIMIT
				0, " . $this->mypage_limit . "
			)
			UNION
			(
			SELECT
				'timeline' AS type,
				null AS thread_name,
				tl.timeline_id AS code,
				tl.comment AS text,
				tl.create_time AS update_time," /* update 2017.2.8 update_timeからcreate_time */ . "
				tl.update_time AS sort_time," /* 　　　　sort用に新設 */ . "
				tl.user_id AS user_id,
				tl.image_file AS file_name,
				tl.publication AS publication,
				null AS thread_id,
				tl.like_count AS like_count,
				up2.nickname AS nickname,
				up2.system_id AS system_id
			FROM
				timeline AS tl
			LEFT JOIN
				user_public AS up2
			ON
				tl.user_id = up2.user_id
			WHERE
				(
					" /* フレンドに限らず全公開  期間限定（2017.2.9～ユーザーが増えるまで。 */ . "
					tl.publication = " . TL_PUBLICATION_ALL . "
				)
				AND
				tl.active = " . DB_ACTIVE_ON . "

			ORDER BY
				tl.update_time DESC
			LIMIT
				0, " . $this->mypage_limit . "
			)
			ORDER BY
				sort_time DESC
			LIMIT
				" . ($pd * $pp) . "," . $pp . "	"
        );
        return $data;
    }

	/*	 * **********************************
	 * NAME  : get_timeline_count
	 * INPUT : $user_id / int / ユーザーID
	 * OUTPUT: 数値
	 * DESC  :
	 * 		マイページTOPのタイムラインの数を取得
	 * NOTICE:
	 * CREATE: 2016.12.20 aoyama
	 * *********************************** */
	public function get_timeline_self_count($user_id) {

		$data = $this->query("
			SELECT SUM(code) AS tl_cunt FROM (
			(
			SELECT
				count(cr.response_id) AS code
			FROM
				community_response AS cr
			LEFT JOIN
				user_public AS up
			ON
				cr.user_id = up.user_id
			LEFT JOIN
				community_thread AS ct
			ON
				cr.thread_id = ct.thread_id
			LEFT JOIN
				community_match AS cm
			ON
				cr.thread_id = cm.thread_id
			WHERE
				cm.user_id = " . DbCast::id($user_id) . "
					AND
				cr.active = " . DB_ACTIVE_ON . "
					AND
				ct.active = " . DB_ACTIVE_ON . "
			LIMIT
				0, " . $this->mypage_limit . "
			)
			UNION ALL
			(
			SELECT
				count(tl.timeline_id) AS code
			FROM
				timeline AS tl
			LEFT JOIN
				user_public AS up2
			ON
				tl.user_id = up2.user_id
			LEFT JOIN
				(	
					" /* まずは自分から申請しているパターン */ . "
					(
					SELECT
						fm1.user_id AS user_id,
						fm1.friend_id AS friend_id
					FROM
						friend_match AS fm1
					WHERE 
						fm1.user_id=" . DbCast::id($user_id) . "
						AND
						fm1.commit_status = 1
					)
					UNION
					" /* 申請されているパターン */ . "
					(
					SELECT
						fm2.friend_id AS user_id,
						fm2.user_id AS friend_id
					FROM
						friend_match AS fm2
					WHERE 
						fm2.friend_id=" . DbCast::id($user_id) . "
						AND
						fm2.commit_status = 1
					)
				) AS fm
			ON
				tl.user_id = fm.friend_id
			WHERE
				(
					(
						fm.user_id = " . DbCast::id($user_id) . "
						AND
						(
							tl.publication = " . TL_PUBLICATION_ALL . "
								OR
							tl.publication = " . TL_PUBLICATION_FRIEND . "
						)
					)
					OR
					tl.user_id = " . DbCast::id($user_id) . "
				)
				AND
				tl.active = " . DB_ACTIVE_ON . "
			ORDER BY
				tl.update_time DESC
			LIMIT
				0, " . $this->mypage_limit . "
			)
			) AS cts"
		);
		return $data[0]['tl_cunt'];
	}


	/*	 * **********************************
	 * NAME  : post_timeline
	 * INPUT : param_list / array / 登録したいカラム名配列
	 * OUTPUT: db_shell_insert()のレスポンス(成功時：user_id, 失敗時:false)
	 * DESC  :
	 *  INSERT
	 * NOTICE:
	 * CREATE: 2016.10.19 aoyama
	 * *********************************** */
	public function post_timeline($param_list) {
		return $this->db_shell_insert($this->timeline, $param_list);
	}
	
	/*	 * **********************************
	 * NAME  : post_timeline_response
	 * INPUT : param_list / array / 登録したいカラム名配列
	 * OUTPUT: db_shell_insert()のレスポンス(成功時：user_id, 失敗時:false)
	 * DESC  :
	 * NOTICE:
	 * CREATE: 2016.12.13 aoyama
	 * *********************************** */
	public function post_timeline_response($param_array) {
		$data = $this->query("
			SELECT
				count(tl.timeline_id) AS count_num
			FROM
				" . $this->timeline . " AS tl
			WHERE
				tl.active = " . DB_ACTIVE_ON . "
				AND
				tl.timeline_id = " . DbCast::id($param_array['timeline_id'])
		);
		if ($this->db_select_check_error($data) || $this->db_select_check_empty($data)) {
			return false;
		}

		if ($data[0]['count_num'] == 1) {
			$this->db_shell_insert($this->timeline_response, $param_array);
			return true;
		}
		return false;
	}	
	
	/*	 * **********************************
	 * NAME  : get_timeline_response
	 * INPUT : $timeline_ids　/ array / 表示されるタイムラインのID配列
	 * OUTPUT: db_shell_insert()のレスポンス(成功時：user_id, 失敗時:false)
	 * DESC  :
	 *		マイページのタイムラインのレスポンスを取得する
	 *		できれば１クエリで処理したいが時間もないので分割することとした。
	 * NOTICE:
	 * CREATE: 2016.12.13 aoyama
	 * *********************************** */
	public function get_timeline_response($timeline_ids) {
		
		if(!StaticFunction::is_empty($timeline_ids)) {
			$in_value = implode(",",$timeline_ids);
			
			$data = $this->query("
				SELECT
					tr.timeline_response_id,
					tr.user_id,
					tr.timeline_id,
					tr.response_text,
					tr.update_time,
					
					up.system_id,
					up.nickname
				FROM
					" . $this->timeline_response . " AS tr
				LEFT JOIN
					" . $this->user_public . " AS up
				ON
					tr.user_id = up.user_id
				WHERE
					tr.active = " . DB_ACTIVE_ON . "
					AND
					tr.timeline_id IN (" . $in_value . ")
				ORDER BY
					tr.update_time ASC
				"
			);
			if ($this->db_select_check_error($data) || $this->db_select_check_empty($data)) {
				return array();
			}
			return $data;
		}
		
		return array();
	}		
	
	/*	 * **********************************
	 * NAME  : is_timeline_response
	 * INPUT : $rr_id / int / レビューのコメントID
	 * OUTPUT: array / 結果配列
	 * DESC  :
	 *		タイムラインコメントの詳細取得
	 * NOTICE:
	 * CREATE: 2016.12.13 aoyama
	 * *********************************** */
	public function is_timeline_response($tr_id) {

		$data = $this->query("
			SELECT
				rr.update_time AS view_time,
				rr.user_id,
				rr.timeline_id
			FROM
				" . $this->timeline_response . " AS rr
			WHERE
				rr.active = " . DB_ACTIVE_ON . "
				AND
				rr.timeline_response_id = " . DbCast::id($tr_id)
		);
		if ($this->db_select_check_error($data) || $this->db_select_check_empty($data)) {
			return false;
		}

		return $data;
	}	
	
	/*	 * **********************************
	 * NAME  : delete_timeline_response
	 * INPUT : $rr_id / int / レビューのコメントID
	 * OUTPUT: array / 結果配列
	 * DESC  :
	 *		タイムライン返信の削除
	 * NOTICE:
	 * CREATE: 2016.11.20 aoyama
	 * *********************************** */
	public function delete_timeline_response($param_list,$condition) {
		return $this->db_shell_update($this->timeline_response, $param_list,$condition);
	}

	/*	 * **********************************
	 * NAME  : get_detail_by_id
	 * INPUT : $timeline_id / integer / タイムラインID
	 * OUTPUT: array / データ
	 * DESC  :
	 * 		$timeline_idからタイムラインの詳細情報を取得する
	 * NOTICE:
	 * CREATE: 2016.11.10 aoyama
	 * *********************************** */
	public function get_detail_by_id($timeline_id, $user_id) {

		//パラメータチェック
		if (StaticFunction::is_empty($timeline_id) || !InputVali::is_num($timeline_id)) {
			return false;
		}

		return $this->query("
			SELECT 
				tl.timeline_id,
				tl.create_time,
				tl.update_time,
				tl.comment,
				tl.image_file,
				tl.user_id,
				tl.like_count
			FROM
				" . $this->timeline . " AS tl
			LEFT JOIN
				user_public AS up
			ON
				tl.user_id = up.user_id
			WHERE
				tl.timeline_id=" . DbCast::id($timeline_id) . "
				AND
				tl.user_id=" . DbCast::id($user_id) . "
				AND
				tl.active=" . DB_ACTIVE_ON
		);
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
		return $this->db_shell_update($this->timeline, $param_list, $condition);
	}

	/*	 * **********************************
	 * NAME  : delete_response
	 * INPUT : param_list / array / 登録したいカラム名配列
	 * OUTPUT: db_shell_insert()のレスポンス(成功時：user_id, 失敗時:false)
	 * DESC  :
	 *  コミュニティのコメントを削除
	 * NOTICE:
	 * CREATE: 2016.11.10 aoyama
	 * *********************************** */
	public function delete($param_list, $condition) {
		return $this->db_shell_update($this->timeline, $param_list, $condition);
	}

}

?>
