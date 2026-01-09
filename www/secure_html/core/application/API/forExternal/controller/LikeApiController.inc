<?php

/* * **********************************
 * NAME:LikeApiController
 * DESC:
 * NOTICE:
 * CREATE: 2016.10.27 aoyama
 * *********************************** */
class LikeApiController extends ExternalApiCloseControllerFrame {

	/* Constructor */
	public function __construct() {
		parent::__construct();

//		header('Content-Type: application/json');
	}

	/*	 * **********************************
	 * NAME  : exec
	 * INPUT : 
	 * 		$user_id / string / system_id
	 * 		$target_id / int / コメントまたはコミュニティに対するいいね
	 * OUTPUT: 
	 * 		true or false
	 * DESC  :
	 * 		重複いいね禁止とかそれぐらい
	 * NOTICE:
	 * CREATE: 2016.10.27 aoyama
	 * *********************************** */
	public function exec() {

		$ret = array();

		if (StaticFunction::is_empty(SESSION::read(CONF::read('LOGIN_CATEGORY.PUBLIC') . '.user_id'))) {
			$ret = array(
				"code" => 400,
				"message" => "Invalid access"
			);
			$this->return_json($ret);
		}

		if (StaticFunction::is_empty(REQUEST::get_data('target_id')) || StaticFunction::is_empty(REQUEST::get_data('type'))) {
			$ret = array(
				"code" => 401,
				"message" => "Invalid Parameter"
			);
			$this->return_json($ret);
		}

		$like = new LikeModel();
		
		if (REQUEST::get_data('mode') == "like") {
			if ($like->set_like(REQUEST::get_data('type'), REQUEST::get_data('target_id'), SESSION::read(CONF::read('LOGIN_CATEGORY.PUBLIC') . '.user_id'))) {
				$ret = array(
					"code" => 200,
					"message" => "Ok."
				);
				$this->return_json($ret);
			} else {
				$ret = array(
					"code" => 301,
					"message" => "Liked"
				);
				$this->return_json($ret);
			}
		}
		if (REQUEST::get_data('mode') == "dislike") {
			if ($like->set_dislike(REQUEST::get_data('type'), REQUEST::get_data('target_id'), SESSION::read(CONF::read('LOGIN_CATEGORY.PUBLIC') . '.user_id'))) {
				$ret = array(
					"code" => 200,
					"message" => "Ok."
				);
				$this->return_json($ret);
			} else {
				$ret = array(
					"code" => 301,
					"message" => "Not Liked"
				);
				$this->return_json($ret);
			}
		}
	}

	private function return_json($array) {
		echo json_encode($array);
		exit;
	}

}

?>
