<?php



/* * **********************************
 * NAME:TimelineApiController
 * DESC:
 * NOTICE:
 * CREATE: 2016.10.27 aoyama
 * *********************************** */
class TimelineApiController extends ExternalApiCloseControllerFrame {

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
        $timeline = new TimelineModel();
        $community = new CommunityModel();
        $image = new Image();

        $tvViewArray = array();
        $timeline_ids = array();
        foreach ($timeline->get_timeline_for_index(0, 20) AS $tlValue) {

            // 画像ファイルの表示用配列初期化(2017.2.13 aoyama)
            $file_url = array();

            switch ($tlValue['type']) {
                // community_response
                case "response":
                    $file_url[] = $image->get_response_url($tlValue['code'], $tlValue['file_name']);
                    $prefix = 'community';
                    $response_ids[] = $tlValue['code'];
                    break;
                // timeline
                case "timeline":
                    $file_url = $timeline->get_timeline_image($tlValue['system_id'], $tlValue['code']);
                    $prefix = 'timeline';
                    $timeline_ids[] = $tlValue['code'];
                    break;
            }

            $tvViewArray[] = array(
                "parent_id" => $tlValue['code'],
                "prefix" => $prefix,
                "thread_id" => $tlValue['thread_id'],
                "thread_name" => $tlValue['thread_name'],
                "system_id" => $tlValue['system_id'],
                "nickname" => $tlValue['nickname'],
                "like_count" => $tlValue['like_count'],
                "text_view" => StaticFunction::decode_view_json(nl2br($tlValue['text'])),
                "file_url" => $file_url,
                "avatar" => $image->get_avatar_url($tlValue['system_id']),
                "update_time" => DbDateTime::get_date_type_dot($tlValue['update_time'])
            );
        }
//        echo json_encode($tvViewArray);

        /* timeline返信を取得しviewに渡す */
        $timeline_response_array = array();
        foreach ($timeline->get_timeline_response($timeline_ids) AS $value) {
            $edit_response_link = "";
            $timeline_response_array[$value['timeline_id']][] = array(
                "timeline_response_id" => $value['timeline_response_id'],
                "user_id" => $value['user_id'],
                "nickname" => $value['nickname'],
                "avatar" => $image->get_avatar_url($value['system_id']),
                "user_link" => "/profile/?uid=" . $value['system_id'],
                "timeline_id" => $value['timeline_id'],
                "response_text" => StaticFunction::decode_view_json(nl2br($value['response_text'])),
                "update_time" => DbDateTime::get_date_type_dot($value['update_time']),
                "edit_link" => $edit_response_link
            );
        }

        // コミュニティのコメントを取得
        $comment_array = array();
        foreach ($community->get_comment_list($response_ids) AS $value) {
            $edit_response_link = "";
            $comment_array[$value['response_id']][] = array(
                "nickname" => $value['nickname'],
                "avatar" => $image->get_avatar_url($value['system_id']),
                "user_link" => "/profile/?uid=" . $value['system_id'],
                "comment_id" => $value['comment_id'],
                "comment_text" => StaticFunction::decode_view_json(nl2br($value['comment_text'])),
                "update_time" => DbDateTime::get_date_type_dot($value['update_time'])
            );
        }


//        echo json_encode($timeline_response_array);

        echo json_encode(
            array(
                'parents' => $tvViewArray,
                'timeline' => $timeline_response_array,
                'community' => $comment_array
            )
        );
	}

}

