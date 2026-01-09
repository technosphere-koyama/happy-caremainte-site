<?php

/* * **********************************
 * NAME:LatestCareApiController
 * DESC:
 * NOTICE:
 * CREATE: 2016.10.27 aoyama
 * *********************************** */
class LatestCareApi {

	/* Constructor */
	public function __construct() {
//		parent::__construct();

//		header('Content-Type: application/json');
	}

	/*	 * **********************************
	 * NAME  : exec
	 * INPUT : 
	 * OUTPUT: 
	 * 		true or false
	 * DESC  :
	 * NOTICE:
	 * CREATE: 2016.11.16 aoyama
	 * UPDATE: 2017.2.13 aoyama
	 *		画像複数添付方式に対応
	 * *********************************** */
	public function exec() {

		$community_id = 1000038;
		$community_user_id = 10000001;

		$ret = array();

		//最新のケアメンテ投稿を1件のみ取得
		$api = new Rest();
		if (!$result = $api->get_item_care_search("", "", "", "", "", "", "", 0, 1)) {
			$ret = array(
				"code" => 401,
				"message" => "API failed"
			);
			$this->return_json($ret);
		}

		if ($result['code'] != "200") {
			$ret = array(
				"code" => 402,
				"message" => "valid response"
			);
			$this->return_json($ret);
		}
		
		$item_id = $result['item_list'][0]['item_id'];

		//既存のものと比較
		$care_news = new CareNewsModel();

		if (!$care_news->update_care_item_id($item_id)) {
			$ret = array(
				"code" => 403,
				"message" => "update_care_item_id failed"
			);
			$this->return_json($ret);
			return;
		}

		//最新のcareを取得できたので詳細情報をAPIから取得
		$care_detail = $api->get_item_care_detail($item_id);
		
		//after画像の1枚目を取得
		$file = new Image();

		//一時ファイル名を生成
		$file_tmp_hash = Encrypt::member_regist_token('12345678', time());
		
//		$extra_file = $file->get_external_image('http://kh01.kyoto-happy.co.jp'.$care_detail['item']['image_1_after'],false);

		//ロード
		$ret = $file->load('http://kh01.kyoto-happy.co.jp'.$care_detail['item']['image_1_after']);
		
		$file->resize();

		//拡張子取得
		$thumb_ext = $file->get_image_type();

		//保存ファイル名
		$tmp_file_name = $file_tmp_hash . '.' . $thumb_ext;


		/*
		 * 新規事例の投稿処理
		 *「タイムラインに書き込み」から
		 * 「Happyケアメンテコミュニティでの投稿」に変更
		 *	thread_id = 1000038
		 *
		 */
		$comment = 'ケアメンテ検索に新しい事例が追加されました。ケアメンテの品質をぜひご覧ください。' . PHP_EOL;
		$comment .= '<a href="/carementeh_search/detail.html?item_id=' . $item_id . '">詳細はこちらから</a>';

		// 画像を直接コミュニティディレクトリにアップロード
		$file->save( DIR_PUBLIC_IMG . DS . "community" . DS . $community_id . DS, $tmp_file_name);

		$community = new CommunityModel();

		$datetime = DbDateTime::get_cur_datetime();
		// レスポンス登録処理
		// 配列にPOSTデータを格納
		$param_array = array(
			'update_time' => DbCast::datetime($datetime),
			'create_time' => DbCast::datetime($datetime),
			"response_text" => DbCast::string($comment),
			"thread_id" => $community_id,
			'user_id' => $community_user_id,
			"active" => DbCast::float(DB_ACTIVE_ON)
		);

		/* コミュニティのレスポンステーブル[community_response]にインサート */
		if (!$insert_id = $community->post_response($param_array)) {
			$ret = array(
				"code" => 403,
				"message" => "post_response failed"
			);
			$this->return_json($ret);
			return;
		}

		// 添付画像を画像用テーブル「community_response_file」に登録
		$community->add_community_response_file($insert_id,$tmp_file_name,$datetime);

	}

	private function return_json($array) {
		echo json_encode($array);
		exit;
	}

}

?>
