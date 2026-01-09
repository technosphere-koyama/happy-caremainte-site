<?php

/* * **********************************
 * NAME:LatestCareApiController
 * DESC:
 * NOTICE:
 * CREATE: 2016.10.27 aoyama
 * *********************************** */
class LatestCareApiController extends ExternalApiCloseControllerFrame {

	/* Constructor */
	public function __construct() {
		parent::__construct();

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
	 * *********************************** */
	public function exec() {

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
				"message" => "DB update failed"
			);
			$this->return_json($ret);
		}

		//最新のcareを取得できたので詳細情報をAPIから取得
		$care_detail = $api->get_item_care_detail($item_id);
		
		//after画像の1枚目を取得
		$file = new Image();

		//一時ファイル名を生成
		$file_tmp_hash = Encrypt::member_regist_token($_SERVER['REMOTE_ADDR'], time());
		
//		$extra_file = $file->get_external_image('http://kh01.kyoto-happy.co.jp'.$care_detail['item']['image_1_after'],false);

		//ロード
		$ret = $file->load('http://kh01.kyoto-happy.co.jp'.$care_detail['item']['image_1_after']);
		
		$file->resize();

		//拡張子取得
		$thumb_ext = $file->get_image_type();

		//保存ファイル名
		$tmp_file_name = $file_tmp_hash . '.' . $thumb_ext;

		
		
		//タイムラインに書き込み
		$timeline = new TimelineModel();
		$comment = 'ケアメンテ検索に新しい事例が追加されました。ケアメンテの品質をぜひご覧ください。' . PHP_EOL;
		$comment .= '<a href="/carementeh_search/detail.html?item_id=' . $item_id . '">詳細はこちらから</a>';

		$datetime = DbDateTime::get_cur_datetime();
		// スレッド登録処理
		// 配列にPOSTデータを格納
		$param_array = array(
			'update_time' => DbCast::datetime($datetime),
			'create_time' => DbCast::datetime($datetime),
			"active" => DbCast::float(DB_ACTIVE_ON),
			'user_id' => DbCast::id(CONF::read('MASTER_USER.USER_ID')),
			"comment" => DbCast::string($comment),
			"image_file" => DbCast::string($tmp_file_name)
		);

		$new_timeline_id = $timeline->post_timeline($param_array);

		//tmpディレクトリに保存
		//$ret = $file->save_jpeg($avatar_tmp_dir, $tmp_file_name);
		//tmpフォルダに移動
		$file->save( DIR_PUBLIC_IMG . DS . "user" . DS . CONF::read('MASTER_USER.SYSTEM_ID') . DS, $tmp_file_name);

	}

	private function return_json($array) {
		echo json_encode($array);
		exit;
	}

}

?>
