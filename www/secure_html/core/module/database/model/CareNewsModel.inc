<?php

/* * **********************************
 * NAME:ReviewModel
 * DESC:
 *  タイムラインテーブル用モデルクラス
 *  上記テーブルに対してアクセス(クエリなど)する場合は
 *  当該クラスにて行うこと！
 * NOTICE:
 *  基本的にはDbShellクラスを継承し、そちらでPDOインスタンスアクセスを行う
 *  場合によっては当該クラスで直接触ることもあるかも知れないが、
 *  できるだけDbShellクラスにて行うこと！
 * CREATE: 2016.11.15 aoyama
 * *********************************** */
class CareNewsModel extends DbShell {

	private $user_public = "user_public";
	private $care_news = "care_news_log";

	public function __construct() {
		parent::__construct();
	}

	/*	 * **********************************
	 * NAME  : post_review_response
	 * INPUT : $thread_id / int / コミュニティID
	 * OUTPUT: string / コメントの数
	 * DESC  :
	 * 		ケアメンテのアイテムIDを検索し1以上ならスルー
	 * 		０なら更新処理
	 * NOTICE:
	 * CREATE: 2016.11.15 aoyama
	 * *********************************** */
	public function update_care_item_id($care_item_id) {

		$data = $this->query("
			SELECT
				count(cn.care_news_id) AS count_num
			FROM
				" . $this->care_news . " AS cn
			WHERE
				cn.care_item_id = " . DbCast::string($care_item_id)
		);

		if ($data[0]['count_num'] > 0) {
			return false;
		}

		$param_array = array(
			"update_time" => DbDateTime::get_cur_datetime(),
			"care_item_id" => DbCast::string($care_item_id)
		);
		$condition = array(
			"WHERE" => array(
				"care_news_id" => 10001
			)
		);

		return $this->db_shell_update($this->care_news, $param_array, $condition);
	}

	/*	 * **********************************
	 * NAME  : edit_review
	 * INPUT : param_list / array / 登録したいカラム名配列
	 * OUTPUT: db_shell_insert()のレスポンス(成功時：user_id, 失敗時:false)
	 * DESC  :
	 * 		レビューを編集する
	 * NOTICE:
	 * CREATE: 2016.11.14 aoyama
	 * *********************************** */
	public function edit_review($param_list, $condition) {
		return $this->db_shell_update($this->review, $param_list, $condition);
	}

}

?>
