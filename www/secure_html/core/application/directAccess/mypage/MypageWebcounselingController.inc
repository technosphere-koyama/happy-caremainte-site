<?php

/* * **********************************
 * NAME:MypageWebcounselingController (Copy of History controller)
 * DESC:
 *  
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
 * CREATE: 2021.10.01 UKS MS
 * UPDATE: 2021.10.01 UKS MS
 * *********************************** */
class MypageWebcounselingController extends MypageBaseCommonControllerFrame {

	private $sGroup;
	private $public_user_data;

	/* Constructor */
	public function __construct($type) {

		//$this->page_type = $type;

		//parent::__construct();
		//$this->sGroup = CONF::read('LOGIN_CATEGORY.PUBLIC') . ".wardrobe";
		//セッションからユーザ情報を取得
		//$this->public_user_data = SESSION::read(CONF::read('LOGIN_CATEGORY.PUBLIC'));

		//最終公開状態（sslからhttpコンテンツの取得）対策により画像変換ライブラリを作成
		//$this->external_target = CONF::read("EXTERNAL_IMAGE.TARGET_SURL");

		//$this->set("page_group", "mypage");
	}

    /*	 * **********************************
	 * NAME  : index
	 * INPUT : NONE
	 * OUTPUT: NONE
	 * DESC  :
	 * NOTICE:
	 * CREATE: 2021.10.01 UKS MS
	 * *********************************** */
	public function index($sort = "ASC") { 
        //print_r('hlo'); exit;
    }

    /*	 * **********************************
	 * NAME  : anketViewFtuser
	 * INPUT : NONE
	 * OUTPUT: NONE
	 * DESC  : To display first time user details
	 * NOTICE:
	 * CREATE: 2021.10.01 UKS MS
	 * *********************************** */
	public function anketViewFtuser($sort = "ASC") { 
		// URL param details decoded recived from _GET method
        $chart_no = base64_decode($_GET['param1']);
        $visitor_no = base64_decode($_GET['param2']);
        $amount = base64_decode($_GET['param3']);

		// object intialization for api connection
		$api = new Rest();

		// variables used in query
		$user_type = "first";
		$pp = 10;
		$pd = 0;
		$final_list = array();

		$user_details = $api->get_webcounseling_user_details($visitor_no,$pd,$pp);
		$user_name = $user_details['visitorname'];
		
		if((isset($user_details)) && (empty($user_details))) {
			$this->redirect("/mypage/webcounseling/invalid.html");
			exit;
		 } else {
			// Checking link status, Expired or not
			$link_status = $api->get_webcounseling_link_details($visitor_no,$chart_no,$pd,$pp);

			if($link_status == '1' || $link_status['expiry_flag'] == '1') { 
				
				$link_status = '1';

				// Getting Anket details from DB
				$anket_lists = $api->get_webcounseling_anket_list($user_type,$pd,$pp);

				// Getting Answer details from DB
				$answer_lists = $api->get_webcounseling_answer_list($user_type,$pd,$pp);
				
				// Getting User name and other details for user
				//$user_details = $api->get_webcounseling_user_details($visitor_no,$pd,$pp);
				//$user_name = $user_details['visitorname'];
				
				// postions to place "/"
				$position = array(4,7);

				// Get delivery dates from DB
				$delivery_dates = $api->get_delivery_date_details($visitor_no,$chart_no,$pd,$pp);
				
				// Converting number string into date format yyyy-mm-dd
				$delivery_date_list = array();
				
				// converting result array into single array
				foreach($delivery_dates as $delivery_date) {
					foreach ($position as $pos) {
						$string = substr_replace($delivery_date['reportscheduleddate'], '/', $pos, 0);
						$delivery_date['reportscheduleddate'] = $string;
					}
					array_push($delivery_date_list,$string);
				}

				$first_date = min($delivery_date_list); 

				// Collecting Anket details and Answer details to feed in view screen
				foreach($anket_lists as $keys => $value) { 
					foreach($answer_lists as $key_ans => $val_ans) {
						if($value['anket_id'] == $val_ans['anket_id']) {
							$final_list[$value['anket_id']][$val_ans['answer_id']] = $val_ans;
						}
					}
				}

				// Setting variabled used in view page
				$this->set('final_list', $final_list);
				$this->set('delivery_date_list', $delivery_date_list);
				$this->set('first_date', $first_date);
			} else {
				if($link_status['counselingchartok'] == '1' && $link_status['paymentmethod'] == '1') {
					$this->redirect("/mypage/webcounseling/payment_confirm.html?param1=".$_GET['param1']."&param2=".$_GET['param2']."&param3=".$_GET['param3']);
					exit;
				} else {
					$this->set('link_status', $link_status);
				}
			}

			// Setting variabled used in view page
			//$this->set('final_list', $final_list);
			$this->set('link_status', $link_status);
			$this->set('user_name', $user_name);
			$this->set('chart_no', $chart_no);
			$this->set('visitor_no', $visitor_no);
			$this->set('amount', $amount);
		} 

    }

	/*	 * **********************************
	 * NAME  : paymentConfirm
	 * INPUT : NONE
	 * OUTPUT: NONE
	 * DESC  : To display Payment screen if user missed link before payment
	 * NOTICE: Payment status is unkown. 
	 * CREATE: 2021.11.01 UKS MS
	 * *********************************** */
	public function paymentConfirm() {
		// URL param details decoded recived from _GET method
        $chart_no = base64_decode($_GET['param1']);
        $visitor_no = base64_decode($_GET['param2']);
        $amount = base64_decode($_GET['param3']);

		// object intialization for api connection
		$api = new Rest();

		// Getting User name and other details for user
		$pp = 10;
		$pd = 0;
		$user_details = $api->get_webcounseling_user_details($visitor_no,$pd,$pp);
		$user_name = $user_details['visitorname'];

		// Setting variabled used in view page
		$this->set('user_name', $user_name);
		$this->set('chart_no', $chart_no);
		$this->set('visitor_no', $visitor_no);
		$this->set('amount', $amount);
		
	}

	/*	 * **********************************
	 * NAME  : anketViewconfirm
	 * INPUT : NONE
	 * OUTPUT: NONE
	 * DESC  : To display first time user details to confirm before submission
	 * NOTICE:
	 * CREATE: 2021.10.01 UKS MS
	 * *********************************** */
	public function anketViewconfirm() {
		// Post data recived from ftuser form
		$post_data = $_POST;
        $chart_no = $_POST['chartno'];
        $visitor_no = $_POST['visitorno'];
        $amount = $_POST['amount'];

		// object intialization for api connection
		$api = new Rest();

		// variables used in query
		$user_type = "first";
		$pp = 10;
		$pd = 0;
		$final_list = array();

		// Getting Anket details from DB
		$anket_lists = $api->get_webcounseling_anket_list($user_type,$pd,$pp);

		// Getting Answer details from DB
		$answer_lists = $api->get_webcounseling_answer_list($user_type,$pd,$pp);
		
		// Getting User name and other details for user
		$user_details = $api->get_webcounseling_user_details($visitor_no,$pd,$pp);
		$user_name = $user_details['visitorname'];
		

		// Collecting Anket details and Answer details to feed in view screen
		foreach($anket_lists as $keys => $value) { 
			foreach($answer_lists as $key_ans => $val_ans) {
				if($value['anket_id'] == $val_ans['anket_id']) {
					$final_list[$value['anket_id']][$val_ans['answer_id']] = $val_ans;
				}
			}
		}

		// Setting variabled used in view page
		$this->set('post_data', $post_data);
		$this->set('final_list', $final_list);
		$this->set('user_name', $user_name);
		$this->set('chart_no', $chart_no);
		$this->set('visitor_no', $visitor_no);
		$this->set('amount', $amount);

	}

	/*	 * **********************************
	 * NAME  : anketSubmission
	 * INPUT : NONE
	 * OUTPUT: NONE
	 * DESC  : To submit Counseling details and insert data inside DB
	 * NOTICE:
	 * CREATE: 2021.10.01 UKS MS
	 * *********************************** */
	public function anketSubmission() {
		session_start();
		if ($_SESSION['timeout'] + 10 * 60 < time()) {
			// session timed out
			session_destroy();
			$this->redirect("/mypage/webcounseling/timeout.html");
			exit;
		}
		// Getting form data submitted by user
		$form_data = $_POST;

		// object intialization for api connection
		$api = new Rest();
		
		// Post data recived from ftuser form
		$post_data = $_POST;
        $chart_no = $_POST['chartno'];
        $visitor_no = $_POST['visitorno'];
        $amount = $_POST['amount'];
		$pp = 10;
		$pd = 0;

		// -------------------------- DATE conversion and calculation ---------------------------
		$selected_date = (isset($form_data['AK010'])) ? $form_data['AK010'] : $form_data['AK004'];
		
		$reportscheduleddate = str_replace('/', '', $selected_date);
		// Getting Shipping date
		$shipping_dates = $api->get_shipping_date_details($visitor_no,$chart_no,$reportscheduleddate,$pd,$pp);
		$shipping_date = $shipping_dates['shippingdate'];
		// ----------------------------------- END ----------------------------------

		// Getting User name and other details for user
		$user_details = $api->get_webcounseling_user_details($visitor_no,$pd,$pp);
		$user_name = $user_details['visitorname'];
		$mailaddress = $user_details['mailaddress'];
		$mailaddress2 = $user_details['mailaddress2'];

		// Array useed as api param
		$api_array = array();

		$api_array['chart_no'] = $form_data['chartno'];
		$api_array['visitorno'] = $form_data['visitorno'];
		$api_array['amount'] = $form_data['amount'];
		$api_array['user_type'] = $form_data['user_type'];
		$api_array['firstdocconfirm'] = (isset($form_data['AK006'])) ? $form_data['AK006'] : '';
		$api_array['counselingchartok'] = (isset($form_data['AK007'])) ? $form_data['AK007'] : $form_data['AK001'];
		$api_array['maintenancechange'] = (isset($form_data['SA001'])) ? '1' : '2';
		$api_array['hopecontents'] = (isset($form_data['SA001'])) ? $form_data['SA001'] : '';
		$api_array['wardrobeuse'] = (isset($form_data['SA002'])) ? '1' : '2';
		$api_array['wardrobeusageperiod'] = (isset($form_data['SA002'])) ? $form_data['SA002'] : '';
		$api_array['paymentmethod'] = (isset($form_data['AK008'])) ? $form_data['AK008'] : $form_data['AK002'];
		$api_array['deliverydate'] = '';
		$api_array['deliverytime'] = (isset($form_data['AK011'])) ? $form_data['AK011'] : $form_data['AK005'];
		$api_array['shippingdate'] = $shipping_date;
		$api_array['reportscheduleddate'] = $reportscheduleddate;

		// Getting Ansers details selected by User
		$mail_contents = $api->get_webcounseling_answer_details($form_data);
		$mail_contents['chartno'] = $chart_no;
		$mail_contents['visitorno'] = $visitor_no;
		$mail_contents['amount'] = $amount;
		$mail_contents['user_name'] = $user_name;
		//$mail_contents['shippingdate'] = $shippingdate_date;
		$mail_contents['reportscheduleddate'] = $selected_date;

		if (!$insertres = $api->update_webcounseling_user_details($api_array)) {
			$this->set("alert", "アイテムが見つかりません。");
			return;
		} else {
			$qry_response = "success";

			$mail = new Mail();

			if (!$result = $mail->send_webcounseling_details($mail_contents, $mailaddress)) {
				//LOGS_ERR('*** WORDROBE ORDER MAIL SEND FAILED. ***');
				//$error_array[] = array("message" => "ワードローブ申し込みのメール送信エラーが発生しました。");
				//$this->set('error_array', $error_array);
				return;
			} 
		}

		// Conditional variables
		$counselingchartok = $api_array['counselingchartok'];
		$paymentmethod = $api_array['paymentmethod'];

		// Setting variabled used in view page
		$this->set('post_data', $post_data);
		$this->set('mail_contents', $mail_contents);
		$this->set('qry_response', $qry_response);
		$this->set('user_name', $user_name);
		$this->set('chart_no', $chart_no);
		$this->set('visitor_no', $visitor_no);
		$this->set('amount', $amount);
		$this->set('counselingchartok', $counselingchartok);
		$this->set('paymentmethod', $paymentmethod);

	}

	
	/*	 * **********************************
	 * NAME  : anketViewRptuser
	 * INPUT : NONE
	 * OUTPUT: NONE
	 * DESC  : To display repeat user details
	 * NOTICE:
	 * CREATE: 2021.10.01 UKS MS
	 * *********************************** */
	public function anketViewRptuser($sort = "ASC") { 
		// URL param details decoded recived from _GET method
        $chart_no = base64_decode($_GET['param1']);
        $visitor_no = base64_decode($_GET['param2']);
        $amount = base64_decode($_GET['param3']);

		// object intialization for api connection
		$api = new Rest();

		// variables used in query
		$user_type = "repeat";
		$pp = 10;
		$pd = 0;
		$final_list = array();

		// Getting User name and other details for user
		$user_details = $api->get_webcounseling_user_details($visitor_no,$pd,$pp);
		$user_name = $user_details['visitorname'];

		if((isset($user_details)) && (empty($user_details))) {
			$this->redirect("/mypage/webcounseling/invalid.html");
			exit;
		 } else {
			// Checking link status, Expired or not
			$link_status = $api->get_webcounseling_link_details($visitor_no,$chart_no,$pd,$pp);

			if($link_status == '1' || $link_status['expiry_flag'] == '1') { 

				$link_status = '1';

				// Getting Anket details from DB
				$anket_lists = $api->get_webcounseling_anket_list($user_type,$pd,$pp);

				// Getting Answer details from DB
				$answer_lists = $api->get_webcounseling_answer_list($user_type,$pd,$pp);
				
				// Getting User name and other details for user
				//$user_details = $api->get_webcounseling_user_details($visitor_no,$pd,$pp);
				//$user_name = $user_details['visitorname'];
				
				// postions to place "/"
				$position = array(4,7);

				// Get delivery dates from DB
				$delivery_dates = $api->get_delivery_date_details($visitor_no,$chart_no,$pd,$pp);
				
				// Converting number string into date format yyyy-mm-dd
				$delivery_date_list = array();
				
				// converting result array into single array
				foreach($delivery_dates as $delivery_date) {
					foreach ($position as $pos) {
						$string = substr_replace($delivery_date['reportscheduleddate'], '/', $pos, 0);
						$delivery_date['reportscheduleddate'] = $string;
					}
					array_push($delivery_date_list,$string);
				}

				$first_date = min($delivery_date_list);

				// Collecting Anket details and Answer details to feed in view screen
				foreach($anket_lists as $keys => $value) { 
					foreach($answer_lists as $key_ans => $val_ans) {
						if($value['anket_id'] == $val_ans['anket_id']) {
							$final_list[$value['anket_id']][$val_ans['answer_id']] = $val_ans;
						}
					}
				}
				
				// Setting variabled used in view page
				$this->set('final_list', $final_list);
				$this->set('delivery_date_list', $delivery_date_list);
				$this->set('first_date', $first_date);
			} else {
				if($link_status['counselingchartok'] == '1' && $link_status['paymentmethod'] == '1') {
					$this->redirect("/mypage/webcounseling/payment_confirm.html?param1=".$_GET['param1']."&param2=".$_GET['param2']."&param3=".$_GET['param3']);
					exit;
				} else {
					$this->set('link_status', $link_status);
				}
			}
			// Setting variabled used in view page
			$this->set('link_status', $link_status);
			$this->set('user_name', $user_name);
			$this->set('chart_no', $chart_no);
			$this->set('visitor_no', $visitor_no);
			$this->set('amount', $amount);
		}

    }

	/*	 * **********************************
	 * NAME  : anketViewRptconfirm
	 * INPUT : NONE
	 * OUTPUT: NONE
	 * DESC  : To display Repeat user details to confirm before submission
	 * NOTICE:
	 * CREATE: 2021.10.01 UKS MS
	 * *********************************** */
	public function anketViewRptconfirm() {
		// Post data recived from ftuser form
		$post_data = $_POST;
        $chart_no = $_POST['chartno'];
        $visitor_no = $_POST['visitorno'];
        $amount = $_POST['amount'];

		// object intialization for api connection
		$api = new Rest();

		// variables used in query
		$user_type = "repeat";
		$pp = 10;
		$pd = 0;
		$final_list = array();

		// Getting Anket details from DB
		$anket_lists = $api->get_webcounseling_anket_list($user_type,$pd,$pp);

		// Getting Answer details from DB
		$answer_lists = $api->get_webcounseling_answer_list($user_type,$pd,$pp);
		
		// Getting User name and other details for user
		$user_details = $api->get_webcounseling_user_details($visitor_no,$pd,$pp);
		$user_name = $user_details['visitorname'];
		

		// Collecting Anket details and Answer details to feed in view screen
		foreach($anket_lists as $keys => $value) { 
			foreach($answer_lists as $key_ans => $val_ans) {
				if($value['anket_id'] == $val_ans['anket_id']) {
					$final_list[$value['anket_id']][$val_ans['answer_id']] = $val_ans;
				}
			}
		}

		// Setting variabled used in view page
		$this->set('post_data', $post_data);
		$this->set('final_list', $final_list);
		$this->set('user_name', $user_name);
		$this->set('chart_no', $chart_no);
		$this->set('visitor_no', $visitor_no);
		$this->set('amount', $amount);

	}

	/*	 * **********************************
	 * NAME  : invalid
	 * INPUT : NONE
	 * OUTPUT: NONE
	 * DESC  : To display Invalid user details
	 * NOTICE:
	 * CREATE: 2021.10.01 UKS MS
	 * *********************************** */
	public function invalid() {

	}

	/*	 * **********************************
	 * NAME  : timeout
	 * INPUT : NONE
	 * OUTPUT: NONE
	 * DESC  : To display timeout message 
	 * NOTICE:
	 * CREATE: 2021.10.01 UKS MS
	 * *********************************** */
	public function timeout() {

	}

}