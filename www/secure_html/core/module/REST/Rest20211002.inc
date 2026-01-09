<?php

/* * **********************************
 * NAME:Rest
 * DESC:
 *  SFのAPIを叩く処理群
 * NOTICE:
 *  APIと通信を行う(認証系ではなくデータアクセス系)処理は
 *  ここに纏めること！
 * CREATE: 2016.10.12 aoyama
 * *********************************** */
class Rest {

	/*
	 * constructor
	 */
	public function __construct() {
		
	}

	/*	 * **********************************
	 * NAME  : order_delivery_wardrobe
	 * INPUT :
	 * 		$item_id / string / 基幹システム用のアイテムID
	 * 		$comment / string / フォームに入力されたコメント
	 * OUTPUT: APIからのレスポンス
	 *         false / 失敗した場合
	 * DESC  :
	 * 		ワードローブの配送注文
	 * NOTICE:
	 * CREATE: 2016.11.28 aoyama
	 * *********************************** */
	public function order_delivery_wardrobe($param_array) {

//		echo "検証中なのでAPIのPOSTをvar_dumpして終了します。<br>";
//		var_dump($param_array);
//		exit;

		/* 認証用URI */

		$url = Conf::read('REST_API.BASE_URL') . "/orderDeliveryWardrobe/";

		// POSTリクエスト実行
		if (!($res = $this->rest_exec_post($url,$param_array))) {
			LOGS_ERR('requst failed ' . $url);
			return false;
		}

		return $res;
	}

	/*	 * **********************************
	 * NAME  : post_chart_item_comment
	 * INPUT :
	 * 		$item_id / string / 基幹システム用のアイテムID
	 * 		$comment / string / フォームに入力されたコメント
	 * OUTPUT: APIからのレスポンス
	 *         false / 失敗した場合
	 * DESC  :
	 * 		電磁カルテのコメントを変更する
	 * NOTICE:
	 * CREATE: 2016.11.28 aoyama
	 * *********************************** */
	public function post_chart_item_comment($param_array) {

		/* 認証用URI */
		$url = Conf::read('REST_API.BASE_URL') . "/postItemComment/";
		
		/*
		 * POSTリクエスト実行
		 */
		if (!($res = $this->rest_exec_post($url, $param_array))) {
			LOGS_ERR('requst failed' . $url);
			return false;
		}

		return $res;
	}

	/*	 * **********************************
	 * NAME  : get_item_care_category
	 * INPUT : 
	 * OUTPUT: APIからのレスポンス
	 *         false / 失敗した場合
	 * DESC  :
	 * 		公開ケアメンテのブランドを取得する
	 * NOTICE:
	 * CREATE: 2016.11.8 aoyama
	 * *********************************** */
	public function get_item_care_category() {

		/* 認証用URI */
		$url = Conf::read('REST_API.BASE_URL') . "/getItemCareCategory/";

		/*
		 * GETリクエスト実行
		 */
		if (!($res = $this->rest_exec_get($url))) {
			LOGS_ERR('requst failed' . $url);
			return false;
		}

		return $res;
	}

	/*	 * **********************************
	 * NAME  : get_item_care_brand_initial
	 * INPUT : $mojicode
	 * OUTPUT: APIからのレスポンス
	 *         false / 失敗した場合
	 * DESC  :
	 * 		公開ケアメンテのブランドを取得する
	 * NOTICE:
	 * CREATE: 2016.11.8 aoyama
	 * *********************************** */
	public function get_item_care_brand($mojicode) {

		/* 認証用URI */
		$url = Conf::read('REST_API.BASE_URL') . "/getItemCareBrand/?mojicode=" . $mojicode;

		/*
		 * GETリクエスト実行
		 */
		if (!($res = $this->rest_exec_get($url))) {
			LOGS_ERR('requst failed' . $url);
			return false;
		}

		return $res;
	}

	/*	 * **********************************
	 * NAME  : get_item_care_brand_initial
	 * INPUT :
	 * OUTPUT: APIからのレスポンス
	 *         false / 失敗した場合
	 * DESC  :
	 * 		公開ケアメンテのブランドイニシャルを取得する
	 * NOTICE:
	 * CREATE: 2016.11.8 aoyama
	 * *********************************** */
	public function get_item_care_brand_initial() {

		/* 認証用URI */
		$url = Conf::read('REST_API.BASE_URL') . "/getItemCareBrandInitial/";

		/*
		 * GETリクエスト実行
		 */
		if (!($res = $this->rest_exec_get($url))) {
			LOGS_ERR('requst failed' . $url);
			return false;
		}

		return $res;
	}

	/*	 * **********************************
	 * NAME  : get_user_password_reset
	 * INPUT :
	 * 		$item_id / string / 
	 * OUTPUT: APIからのレスポンス
	 *         false / 失敗した場合
	 * DESC  :
	 * 		公開ケアメンテの詳細をを取得する
	 * NOTICE:
	 * CREATE: 2016.11.6 aoyama
	 * *********************************** */
	public function get_user_password_reset($item_id, $email) {

		if (StaticFunction::is_empty($item_id) || StaticFunction::is_empty($email)) {
			return false;
		}

		/* 認証用URI */
		$url = Conf::read('REST_API.BASE_URL') . "/userPasswordReset/?user_id=" . $item_id . "&ml=" . $email;

		/*
		 * GETリクエスト実行
		 */
		if (!($res = $this->rest_exec_get($url))) {
			LOGS_ERR('requst failed' . $url);
			return false;
		}

		return $res;
	}

	/*	 * **********************************
	 * NAME  : get_item_care_detail
	 * INPUT :
	 * 		$item_id / string / 
	 * OUTPUT: APIからのレスポンス
	 *         false / 失敗した場合
	 * DESC  :
	 * 		公開ケアメンテの詳細をを取得する
	 * NOTICE:
	 * CREATE: 2016.11.6 aoyama
	 * *********************************** */
	public function get_item_care_detail($item_id) {

		/* 認証用URI */
		$url = Conf::read('REST_API.BASE_URL') . "/getItemCareDetail/?item_id=" . $item_id;

		/*
		 * GETリクエスト実行
		 */
		if (!($res = $this->rest_exec_get($url))) {
			LOGS_ERR('requst failed' . $url);
			return false;
		}

		return $res;
	}

	/*	 * **********************************
	 * NAME  : get_item_care_search
	 * INPUT :
	 * 		$user_id / bigint / system_user_id（基幹システムのユーザーID）
	 * OUTPUT: APIからのレスポンス
	 *         false / 失敗した場合
	 * DESC  :
	 * 		複数条件から公開ケアメンテを取得する
	 * NOTICE:
	 * CREATE: 2016.11.6 aoyama
	 * *********************************** */
	public function get_item_care_search($item, $id5, $select, $sozai0, $color, $color2, $parano, $pd, $pp) {

		$get_array = array();

		$get_array["pp"] = $pp;
		$get_array["pd"] = $pp * $pd;
		$get_array["item"] = $item;
		$get_array["id5"] = $id5;
		$get_array["select"] = $select;
		$get_array["sozai0"] = $sozai0;
		$get_array["color"] = $color;
		$get_array["color2"] = $color2;
		$get_array["parano"] = $parano;

		$get_query = http_build_query($get_array);

		/* 認証用URI */
		$url = Conf::read('REST_API.BASE_URL') . "/getItemCareSearch/?" . $get_query;

		/*
		 * GETリクエスト実行
		 */
		if (!($res = $this->rest_exec_get($url))) {
			LOGS_ERR('requst failed' . $url);
			return false;
		}

		return $res;
	}

	/*	 * **********************************
	 * NAME  : get_user_detail
	 * INPUT :
	 * 		$user_id / bigint / system_user_id（基幹システムのユーザーID）
	 * OUTPUT: APIからのレスポンス
	 *         false / 失敗した場合
	 * DESC  :
	 * 		ユーザーIDから個人情報を取得する
	 * NOTICE:
	 * CREATE: 2016.11.4 aoyama
	 * *********************************** */
	public function get_user_detail($user_id) {

		/* 認証用URI */
		$url = Conf::read('REST_API.BASE_URL') . "/getUserDetail/?user_id=" . $user_id;

		/*
		 * GETリクエスト実行
		 */
		if (!($res = $this->rest_exec_get($url))) {
			LOGS_ERR('requst failed' . $url);
			return false;
		}

		return $res;
	}

	/*	 * **********************************
	 * NAME  : get_user_brand_search
	 * INPUT :
	 * 		$user_id / string / item_id(基幹システムのユーザーID)
	 * OUTPUT: APIからのレスポンス
	 *         false / 失敗した場合
	 * DESC  :
	 * 		ユーザーIDからブランド一覧を取得する
	 * 		検索のセレクトボックスを生成するため
	 * NOTICE:
	 * CREATE: 2016.10.31 aoyama
	 * *********************************** */
	public function get_user_brand_search($system_user_id) {

		/* 認証用URI */
		$url = Conf::read('REST_API.BASE_URL') . "/getUserBrandSearch/?user_id=" . $system_user_id;

		/*
		 * GETリクエスト実行
		 */
		if (!($res = $this->rest_exec_get($url))) {
			LOGS_ERR('requst failed' . $url);
			return false;
		}

		return $res;
	}

	/*	 * **********************************
	 * NAME  : get_item_detail
	 * INPUT :
	 * 		$item_id / string / item_id(基幹システムのアイテム[物件]ID)
	 * OUTPUT: APIからのレスポンス
	 *         false / 失敗した場合
	 * DESC  :
	 * 		カルテIDからアイテム一覧を取得する
	 * NOTICE:
	 * CREATE: 2016.10.25 aoyama
	 * *********************************** */
	public function get_item_detail($item_id, $chart_id, $user_id) {

		/* 認証用URI */
		$url = Conf::read('REST_API.BASE_URL') . "/getItemDetail/?item_id=" . $item_id . "&chart_id=" . $chart_id . "&user_id=" . $user_id;

		/*
		 * GETリクエスト実行
		 */
		if (!($res = $this->rest_exec_get($url))) {
			LOGS_ERR('requst failed' . $url);
			return false;
		}

		return $res;
	}

	/*	 * **********************************
	 * NAME  : get_chart_item_list
	 * INPUT :
	 * 		$user_id / bigint / system_user_id（基幹システムのユーザーID）
	 * 		$chart_id / string / カルテID
	 * 		$pd / int / ～ページ目
	 * 		$pp / int / 1ページに表示する件数
	 * OUTPUT: APIからのレスポンス
	 *         false / 失敗した場合
	 * DESC  :
	 * 		カルテIDからアイテム一覧を取得する
	 * NOTICE:
	 * CREATE: 2016.10.25 aoyama
	 * UPDATE: 2016.11.4 aoyama
	 * 		APIをgetChartItemsからgetItemSearchに変更
	 * *********************************** */
	public function get_chart_item_list($api_array) {

		$get_array = array();

		$get_query = http_build_query($api_array);

		/* 認証用URI */
		$url = Conf::read('REST_API.BASE_URL') . "/getItemSearch/?" . $get_query;
			LOGS_ERR('requst log' . $url);

		/*
		 * GETリクエスト実行
		 */
		if (!($res = $this->rest_exec_get($url))) {
			LOGS_ERR('requst failed' . $url);
			return false;
		}

		return $res;
	}

	/*	 * **********************************
	 * NAME  : get_user_chart_list
	 * INPUT :
	 * 		$user_id / bigint / system_user_id（基幹システムのユーザーID）
	 * 		$type / int / 1：過去のケア～　2：ただいまの～　3：ハッピーワードローブ
	 * 		$pd / int / ～ページ目
	 * 		$pp / int / 1ページに表示する件数
	 * OUTPUT: APIからのレスポンス
	 *         false / 失敗した場合
	 * DESC  :
	 * 		ユーザーIDからカルテ一覧を取得する
	 * NOTICE:
	 * CREATE: 2016.10.25 aoyama
	 * *********************************** */
	public function get_user_chart_list($user_id, $type = REST_ORDER_PAST, $pd, $pp, $sort) {

		/* 認証用URI */
		$url = Conf::read('REST_API.BASE_URL') . "/getUserChartList/?user_id=" . $user_id . "&date_sort=" . $sort . "&type=" . $type . "&pd=" . ($pd * $pp) . "&pp=" . $pp;

		/*
		 * GETリクエスト実行
		 */
		if (!($res = $this->rest_exec_get($url))) {
			LOGS_ERR('requst failed' . $url);
			return false;
		}

		return $res;
	}

	/* Added by UKS Manjunathgouda on 20210914
	*	Editing for mypage history aditional features
	* ------------------- START -----------------------------
	*/
	public function get_user_chart_list_uks($user_id, $type = REST_ORDER_PAST, $pd, $pp, $sort) {

		/* 認証用URI */
		$url = Conf::read('REST_API.BASE_URL') . "/getUserChartListUks/?user_id=" . $user_id . "&date_sort=" . $sort . "&type=" . $type . "&pd=" . ($pd * $pp) . "&pp=" . $pp;

		/*
		 * GETリクエスト実行
		 */
		if (!($res = $this->rest_exec_get($url))) {
			LOGS_ERR('requst failed' . $url);
			return false;
		}

		return $res;
	}

	public function get_download_pdf_uks($user_id, $type = REST_ORDER_PAST, $pd, $pp, $sort, $chartid) {
		
		/* 認証用URI */
		$url = Conf::read('REST_API.BASE_URL') . "/getdownloadpdfUks/?user_id=" . $user_id . "&date_sort=" . $sort . "&type=" . $type . "&pd=" . ($pd * $pp) . "&pp=" . $pp . "&chartid=" . $chartid;

		/*
		 * GETリクエスト実行
		 */
		if (!($res = $this->rest_exec_get($url))) {
			//LOGS_ERR('requst failed' . $url);
			return false;
		}
//echo $res; exit;
		return $res;
	}

	// ------------- END ---------------
	/*	 * **********************************
	 * NAME  : user_add
	 * INPUT : 会員登録用の配列
	 * OUTPUT: APIからのレスポンス
	 *         false / 失敗した場合
	 * DESC  :
	 * NOTICE:
	 * CREATE: 2016.10.18 aoyama
	 * *********************************** */
	public function order_care($array) {

		/* 認証用URI */
		$url = Conf::read('REST_API.BASE_URL') . "/orderCare/";

		/*
		 * POSTリクエスト実行
		 */
		if (!($res = $this->rest_exec_post($url, $array))) {
			LOGS_ERR('requst failed' . $url);
			return false;
		}

		return $res;
	}

	/*	 * **********************************
	 * NAME  : user_add
	 * INPUT : 会員登録用の配列
	 * OUTPUT: APIからのレスポンス
	 *         false / 失敗した場合
	 * DESC  :
	 * NOTICE:
	 * CREATE: 2016.10.16 aoyama
	 * *********************************** */
	public function user_add($array) {

		/* 認証用URI */
		$url = Conf::read('REST_API.BASE_URL') . "/addUser/";

		/*
		 * POSTリクエスト実行
		 */
		if (!($res = $this->rest_exec_post($url, $array))) {
			LOGS_ERR('requst failed' . $url);
			return false;
		}

		return $res['user_id'];
	}

	/*	 * **********************************
	 * NAME  : user_edit
	 * INPUT : 登録情報変更用の配列
	 * OUTPUT: APIからのレスポンス
	 *         false / 失敗した場合
	 * DESC  :
	 * NOTICE:
	 * CREATE: 2016.10.21 aoyama
	 * *********************************** */
	public function user_edit($array) {

		/* 認証用URI */
		$url = Conf::read('REST_API.BASE_URL') . "/updateUser/";

		/*
		 * POSTリクエスト実行
		 */
		if (!($res = $this->rest_exec_post($url, $array))) {
			LOGS_ERR('requst failed' . $url);
			return false;
		}

		return $res;
	}

	/*	 * **********************************
	 * NAME  : catalog_add
	 * INPUT : カタログ請求登録用の配列
	 * OUTPUT: APIからのレスポンス
	 *         false / 失敗した場合
	 * DESC  :
	 * NOTICE:
	 * CREATE: 2016.10.17 aoyama
	 * *********************************** */
	public function catalog_add($array) {

		/* 認証用URI */
		$url = Conf::read('REST_API.BASE_URL') . "/requestCatalog/";

		/*
		 * POSTリクエスト実行
		 */
		if (!($res = $this->rest_exec_post($url, $array))) {
			LOGS_ERR('requst failed' . $url);
			return false;
		}

		return $res;
	}

	/*	 * **********************************
	 * NAME  : contact_add
	 * INPUT : お問合せ登録用の配列
	 * OUTPUT: APIからのレスポンス
	 *         false / 失敗した場合
	 * DESC  :
	 * NOTICE:
	 * CREATE: 2016.10.16 aoyama
	 * *********************************** */
	public function contact_add($array) {

		/* 認証用URI */
		$url = Conf::read('REST_API.BASE_URL') . "/sendInquiry/";

		/*
		 * POSTリクエスト実行
		 */
		if (!($res = $this->rest_exec_post($url, $array))) {
			LOGS_ERR('requst failed' . $url);
			return false;
		}

		return $res;
	}

	/*	 * **********************************
	 * NAME  : mailmag_add
	 * INPUT : メルマガ登録用の配列
	 * OUTPUT: APIからのレスポンス
	 *         false / 失敗した場合
	 * DESC  :
	 * NOTICE:
	 * CREATE: 2016.10.14 aoyama
	 * *********************************** */
	public function mailmag_add($array) {

		/* 認証用URI */
		$url = Conf::read('REST_API.BASE_URL') . "/addMailmagazine/";

		/*
		 * POSTリクエスト実行
		 */
		if (!($res = $this->rest_exec_post($url, $array))) {
			LOGS_ERR('requst failed' . $url);
			return false;
		}

		return $res;
	}

	/*	 * **********************************
	 * NAME  : introduce_add
	 * INPUT : 友達紹介登録用の配列
	 * OUTPUT: APIからのレスポンス
	 *         false / 失敗した場合
	 * DESC  :
	 * NOTICE:
	 * CREATE: 2016.10.18 aoyama
	 * *********************************** */
	public function introduce_add($array) {

		/* 認証用URI */
		$url = Conf::read('REST_API.BASE_URL') . "/addIntroduce/";

		/*
		 * POSTリクエスト実行
		 */
		if (!($res = $this->rest_exec_post($url, $array))) {
			LOGS_ERR('requst failed' . $url);
			return false;
		}

		return $res;
	}

	/*	 * **********************************
	 * NAME  : user_login
	 * INPUT : param_list / array / SFに投げる要素名と値の連想配列
	 * OUTPUT: APIからのレスポンス
	 *         false / 失敗した場合
	 * DESC  :
	 * NOTICE:
	 * CREATE: 2016.10.12 aoyama
	 * *********************************** */
	public function user_login($user_id, $password) {

		/* 認証用URI */
		$url = Conf::read('REST_API.BASE_URL') . "/userLogin/?user_id=" . $user_id . "&password=" . $password;

		/*
		 * GETリクエスト実行
		 */
		if (!($res = $this->rest_exec_get($url))) {
			LOGS_ERR('requst failed' . $url);
			return false;
		}
		LOGS_ERR($res);

		return $res;
	}

	/*	 * **********************************
	 * NAME  : curl_post
	 * INPUT : url / string / 通信先URL
	 * OUTPUT: APIからのレスポンス / レスポンスJSONのdecodeしたarray
	 *         false / 失敗した場合
	 * DESC  :
	 * NOTICE:
	 * CREATE: 2016.10.12 aoyama
	 * *********************************** */
	private function curl_post($url = '', $post_array) {

		$curl = curl_init("URL");
		curl_setopt($curl, CURLOPT_POST, TRUE);
		// ↓はmultipartリクエストを許可していないサーバの場合はダメっぽいです
		// @DrunkenDad_KOBAさん、Thanks
		//curl_setopt($curl,CURLOPT_POSTFIELDS, $POST_DATA);
		curl_setopt($curl, CURLOPT_POSTFIELDS, http_build_query($POST_DATA));
		curl_setopt($curl, CURLOPT_SSL_VERIFYPEER, FALSE);  // オレオレ証明書対策
		curl_setopt($curl, CURLOPT_SSL_VERIFYHOST, FALSE);  // 
		curl_setopt($curl, CURLOPT_RETURNTRANSFER, TRUE);
		curl_setopt($curl, CURLOPT_COOKIEJAR, 'cookie');
		curl_setopt($curl, CURLOPT_COOKIEFILE, 'tmp');
		curl_setopt($curl, CURLOPT_FOLLOWLOCATION, TRUE); // Locationヘッダを追跡
		//curl_setopt($curl,CURLOPT_REFERER,        "REFERER");
		//curl_setopt($curl,CURLOPT_USERAGENT,      "USER_AGENT"); 

		$result = curl_exec($curl);
		curl_close($curl);

		return $result;
	}

	/* ---------------------------------
	 * 
	 * 	通信メソッド
	 * 
	 * ---------------------------------/

	  /* * **********************************
	 * NAME  : rest_exec_get
	 * INPUT : url / string / 通信先URL
	 * OUTPUT: APIからのレスポンス / レスポンスJSONのdecodeしたarray
	 *         false / 失敗した場合
	 * DESC  :
	 *  getメソッドで rest api を実行する
	 * NOTICE:
	 *  処理途中でも通信エラーレベルのものが発生した場合は最大5回までリトライ
	 * CREATE: 2015.08.27 hesaka
	 * *********************************** */
	private function rest_exec_get($url = '') {
		
		LOGS_API("GET_URL:".$url);

		$i = 0;
		$json_response = false;

		/*
		 * 最大5回までトライ
		 */
		do {

			$i = $i + 1;

			LOGS_DBG_LV1('*** TRY TIMES = ' . $i . ' ***');
			$success = false;

			$curl = curl_init($url);
			//echo $curl; exit;
			curl_setopt($curl, CURLOPT_CUSTOMREQUEST, 'GET');
			curl_setopt($curl, CURLOPT_SSL_VERIFYPEER, false); // 証明書の検証を行わない
			curl_setopt($curl, CURLOPT_RETURNTRANSFER, true);

			/*
			 * 実行
			 */
			if (CONF::read('DEBUG_BAR.IS_ACTIVE'))
				DebugBarMaster::start_measure('REST_get', 'REST_get');
			$response = curl_exec($curl);
			
			if (CONF::read('DEBUG_BAR.IS_ACTIVE'))
				DebugBarMaster::stop_measure('REST_get');
			$status = curl_getinfo($curl, CURLINFO_HTTP_CODE);
			curl_close($curl);

			switch ($status) {

				/*
				 * 通信成功
				 */
				case 200:

					$json_response = StaticFunction::json_to_array($response);
					LOGS_API($json_response);
					if (empty($json_response)) {
						LOGS_DBG_LV1('*** JSON_DECODE RETURN EMPTY!!! ***');
					}
					$success = true;

					break;

				/*
				 * 通信失敗(トークン切れ)
				 */
				case 401:

					$json_response = StaticFunction::json_to_array($response);
					LOGS_ERR($json_response);
					if (count($json_response) == 1) {
						if (isset($json_response[0]['errorCode']) &&
							$json_response[0]['errorCode'] == 'INVALID_SESSION_ID') {

							//warningログにアクセストークン切れ出力
							LOGS_WARN('*** ACCESS TOKEN EXPIRED ***');

							/*
							 * トークンをリフレッシュ
							 */
							if (!$this->refresh_token()) {
								LOGS_ERR('*** TOKEN REFRESH FAILED ***');
								return false;
							} else {
								LOGS_WARN('*** BUT TOKEN REFRESH SUCCESS!!! ***');
							}
						}
					}
					break;

				/*
				 * 通信失敗
				 */
				case 400:

					$json_response = StaticFunction::json_to_array($response);
					LOGS_ERR($json_response);

					return false;

				/*
				 * リトライすべきケース（単純通信エラーなど）はもう少し調査が必要
				 * 実際に通信を沢山実施して検証するなど
				 */
				default:
					LOGS_ALERT('*** GET UNKNOWN STATUS NUMBER = ' . $status . ' ***');
			}
		} while ($i < REST_RETRY_COUNT && !$success);

		LOGS_DBG_LV1('*** REST EXEC [GET] END ***');

		return $json_response;
	}

	/*	 * **********************************
	 * NAME  : rest_exec_post
	 * INPUT : url / string / 通信先URL
	 *         post_data / array / SFに投げる要素名と値の連想配列
	 * OUTPUT: APIからのレスポンス / レスポンスJSONのdecodeしたarray
	 *         false / 失敗した場合
	 * DESC  :
	 *  postメソッドで rest api を実行する
	 * NOTICE:
	 *  処理途中でも通信エラーレベルのものが発生した場合は最大5回までリトライ
	 * CREATE: 2015.08.27 hesaka
	 * UPDATE: 2016.10.14 aoyama
	 * 		happyさん用にアレンジ
	 * 		（Oauth認証方式を解除）
	 * *********************************** */
	private function rest_exec_post($url = '', $post_data = array()) {

		LOGS_API("POST_URL:".$url." data:".print_r($post_data, true));

		$i = 0;
		$json_response = false;

		/*
		 * 最大5回までトライ
		 */
		do {
			$i = $i + 1;
			LOGS_DBG_LV1('*** TRY TIMES = ' . $i . ' ***');
			$success = false;

			$curl = curl_init($url);
			curl_setopt($curl, CURLOPT_POST, TRUE);
			// ↓はmultipartリクエストを許可していないサーバの場合はダメっぽいです
			// @DrunkenDad_KOBAさん、Thanks
			//curl_setopt($curl,CURLOPT_POSTFIELDS, $POST_DATA);
			curl_setopt($curl, CURLOPT_POSTFIELDS, http_build_query($post_data));
			curl_setopt($curl, CURLOPT_SSL_VERIFYPEER, FALSE);  // オレオレ証明書対策
			curl_setopt($curl, CURLOPT_SSL_VERIFYHOST, FALSE);  // 
			curl_setopt($curl, CURLOPT_RETURNTRANSFER, TRUE);
			curl_setopt($curl, CURLOPT_COOKIEJAR, 'cookie');
			curl_setopt($curl, CURLOPT_COOKIEFILE, 'tmp');
			curl_setopt($curl, CURLOPT_FOLLOWLOCATION, TRUE); // Locationヘッダを追跡

			/*
			 * 実行
			 */
			$response = curl_exec($curl);
			$status = curl_getinfo($curl, CURLINFO_HTTP_CODE);
			curl_close($curl);

			switch ($status) {

				/*
				 * 通信成功
				 */
				case 200:
				case 201:

					$json_response = StaticFunction::json_to_array($response);
					LOGS_API($json_response);
					if (empty($json_response)) {
						LOGS_WARN('*** JSON_DECODE RETURN EMPTY!!! ***');
					}
					$success = true;

					break;

				/*
				 * 通信失敗(トークン切れ)
				 */
				case 401:

					$json_response = StaticFunction::json_to_array($response);
					LOGS_ERR($json_response);
					if (count($json_response) == 1) {
						if (isset($json_response[0]['errorCode']) &&
							$json_response[0]['errorCode'] == 'INVALID_SESSION_ID') {

							//warningログにアクセストークン切れ出力
							LOGS_WARN('*** ACCESS TOKEN EXPIRED ***');

							/*
							 * トークンをリフレッシュ
							 */
							if (!$this->refresh_token()) {
								LOGS_ERR('*** TOKEN REFRESH FAILED ***');
								return false;
							} else {
								LOGS_WARN('*** BUT TOKEN REFRESH SUCCESS!!! ***');
							}
						}
					}

					break;

				/*
				 * 通信失敗
				 */
				case 400:

					$json_response = StaticFunction::json_to_array($response);
					LOGS_ERR($json_response);

					return false;

				/*
				 * リトライすべきケース（単純通信エラーなど）はもう少し調査が必要
				 * 実際に通信を沢山実施して検証するなど
				 */
				default:
					LOGS_ALERT('*** POST UNKNOWN STATUS NUMBER = ' . $status . ' ***');
			}
		} while ($i < REST_RETRY_COUNT && !$success);

		LOGS_DBG_LV1('*** REST EXEC [POST] END ***');

		return $json_response;
	}

}

?>
