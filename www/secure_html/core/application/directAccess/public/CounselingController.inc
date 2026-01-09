<?php

/* * **********************************
 * NAME:IndexController
 * DESC:
 *  トップページ用コントローラ
 * NOTICE:
 * CREATE: 2016.10.11 aoyama
 * *********************************** */
class CounselingController extends PublicOpenControllerFrame {

	private $sGroup;
	private $public_user_data;

	/* Constructor */
	public function __construct() {
		parent::__construct();
		$this->sGroup = 'counseling';

		//セッションからユーザ情報を取得
		$this->public_user_data = SESSION::read(CONF::read('LOGIN_CATEGORY.PUBLIC'));

		$this->external_target = CONF::read("EXTERNAL_IMAGE.TARGET_SURL");
	}

	/*	 * **********************************
	 * NAME  : exec
	 * INPUT : NONE
	 * OUTPUT: NONE
	 * DESC  :
	 * NOTICE:
	 * CREATE: 2016.10.11 aoyama
	 * *********************************** */
	public function index() {

		if(!isset($this->public_user_data['system_user_id'])){
			$this->redirect('/login/');
			return;
		}

		$user_id = $this->public_user_data['system_user_id'];

		$url = Conf::read('REST_API.BASE_URL') . "/getUserChartList/?user_id=$user_id&type=1&date_sort=DESC";
		$res = $this->curl_api_get($url);

		$counseling_all = [];

		$karte_list = $res['chart_list'];
		foreach ($karte_list as $row) {
			$status = $row['webcounselingstatus'];
			if (is_null($status)) {
				$status = 0;
			}

			$data = [
				'number' => $row['chart_id'],
                'date' => $row['date'],
                'name' => 'ご注文のお預かり品',
                'order_num' => $row['count'],
                'price' => $row['price'],
				'status' => $status,
			];

			$counseling_all[] = $data;
		}

		$this->set("counseling_all", $counseling_all);

		//ページング出力
		$page = new PAGING();
		$this->set("pageng_html", $page->make_paging($res['chart_count']));
		
    }

    /*	 * **********************************
	 * NAME  : exec
	 * INPUT : NONE
	 * OUTPUT: NONE
	 * DESC  :
	 * NOTICE:
	 * CREATE: 2016.10.11 aoyamas
	 * *********************************** */
	public function index_comment01() {
		/*
		$api = new Rest();
		// getUserChartList
		if (!$itemDetail = $api->get_item_care_detail(REQUEST::get_data("item_id"))) {
			$this->set("alert", "ケアメンテアイテムが見つかりません。");
			return;
		}
		*/

		if(!isset($this->public_user_data['system_user_id'])){
			$this->redirect('/login/');
			return;
		}

		$user_id = $this->public_user_data['system_user_id'];

		$chart_id = REQUEST::get_data("chart_id");

		$url = Conf::read('REST_API.BASE_URL') . "/getItemSearch/?user_id=$user_id&type=1&chart_id=$chart_id&date_sort=ASC";
		$res = $this->curl_api_get($url);

		if ($res['code'] != '200') {
			$this->redirect('/counseling/');
			return;
		}

		$url = Conf::read('REST_API.BASE_URL') . "/updateWebCounselingStatus";
		$post_data = [
			'user_id'  => $user_id,
			'chart_id' => $chart_id,
		];
		$this->curl_api_post($url, $post_data);

		$complete_count = 0;
		$item_count = $res['item_count'];

		$record_all = [];
		foreach ($res['item_list'] as $row) {
			$status = 0;
			if ($row['webcounselingstatus'] == 2) {
				$status = 1;
				$complete_count++;
			} else if ($row['inspectionnecessity'] == 1) {
				$status = 2;
			} else if ($row['cancelflg'] == 1) {
				$status = 3;
			}

			$reference_no = $row['item_id'];

			$item_split_str = str_split($reference_no, 3);
			$reference_no = implode("-", $item_split_str);

			$data = [
				'thumb_url' => $this->external_target . "/netkuroku/images/" . $row['item_id'] . ".jpg&type=chart",
				'chart_id' => $row['chart_id'],
				'item_id'  => $row['item_id'],
				'reference_no' => $reference_no,
                'reference_name' => $row['brand_name'],
                'status_name' => $row['item_name'],
                'status' => $status,
			];

			$record_all[] = $data;
		}

		
		
		$this->set("counseling_all", $record_all);


		// 全カルテが終わったとき
		$karte_status = REQUEST::get_data("karte_status");
		if (is_null($karte_status)) {
			if ($item_count == $complete_count) {
				$karte_status = 1;
			}
		}

		$http_query = [];
		
		$http_query['chart_id'] = $chart_id;
		$http_query['karte_status'] = $karte_status+1;

		$comment = REQUEST::get_data("comment");
		if (isset($comment)) {			
			$http_query['comment'] = $comment;

			SESSION::write($this->sGroup.".comment", $comment);
		}

		$delivery_array = [
			'01' => '仕上がり次第いつでもOK',
			'02' => '平日よりも土日祝',
			'03' => '土日祝よりも平日',
		];

		$delivery = REQUEST::get_data("delivery");
		if (isset($delivery)) {			
			$http_query['delivery'] = $delivery;

			SESSION::write($this->sGroup.".schedulerequestname", $delivery_array[$delivery]);
		}
		

		// 仕上がり品のお届け日時
		$scheduletimezone_array = [
			'00'=> "指定なし",
			'01'=> "8 ～12時",
			'02'=> "12 ～14時",
			'03'=> "14 ～16時",
			'04'=> "16 ～18時",
			'05'=> "18 ～20時",
			'06'=> "18 ～21時",
			'07'=> "19 ～21時",
		];

		$scheduletimezone = REQUEST::get_data("scheduletimezone");
		if (isset($scheduletimezone)) {			
			$http_query['scheduletimezone'] = $scheduletimezone;

			SESSION::write($this->sGroup.".scheduletimezonename", $scheduletimezone_array[$scheduletimezone]);
		}

		$paymentmethod_array = [
			'18' => "クレジット決済（Web決済）",
			'02' => "郵便振替",
			'03' => "銀行振込",
			'04' => "コンビニ",
			'06' => "デポジット",
		];

		$paymentmethod = REQUEST::get_data("paymentmethod");
		if (isset($paymentmethod)) {			
			$http_query['paymentmethod'] = $paymentmethod;

			SESSION::write($this->sGroup.".paymentmethodname", $paymentmethod_array[$paymentmethod]);
		}

		if ($karte_status == 6) {

			$sGroup = $this->sGroup;

			$shipping = $this->shipping_calc($item_count);

			$user_id = $this->public_user_data['user_id'];

			SESSION::write($sGroup . '.user_id', $user_id);

			$name1 = $this->public_user_data['name1'];
			$name2 = $this->public_user_data['name2'];

			SESSION::write($sGroup . '.name1', $name1);
			SESSION::write($sGroup . '.name2', $name2);

			$name1 = $this->public_user_data['kana1'];
			$name2 = $this->public_user_data['kana2'];

			SESSION::write($sGroup . '.kana1', $name1);
			SESSION::write($sGroup . '.kana2', $name2);

			$tel = $this->public_user_data['tel'];

			SESSION::write($sGroup . '.telephone', $tel);

			$email = $this->public_user_data['email'];

			SESSION::write($sGroup . '.email', $email);


			// orderCarementeh
			$url = Conf::read('REST_API.BASE_URL') . "/orderCarementeh";
			$post_data = [
				'user_id' => $user_id,
				'chart_id' => $chart_id,
				'comment'  => $comment,
				'schedulerequest' => $delivery,
				'scheduletimezone' => $scheduletimezone,
				'paymentmethod' => $paymentmethod,
				'shipping' => $shipping,
			];
			$res = $this->curl_api_post($url, $post_data);
			//$this->redirect("/counseling/");
			//return;

			/**
			 * メールを作成する
			 */

			$item_array = $this->selectedItemArray($chart_id);

			SESSION::write($sGroup . '.chart_id', $chart_id);
			SESSION::write($sGroup . '.item_array', $item_array);

			//対象物件文字列を生成
			$mail = new Mail();
			if (!$mail->send_webcounseling($this->sGroup)) {
				LOGS_ERR('*** ウェブカウンセリングでエラーが発生しました ***');
				$this->set('alert', 'エラーが発生しました。お手数ですが、再度お試し下さい。');
				return;
			}

			//登録用セッションを削除
			SESSION::delete($this->sGroup);
		}

		$this->set("karte_status", $karte_status);
		$this->set("chart_id", $chart_id);
		$this->set("comment", $comment);
		$this->set("delivery", $delivery);
		$this->set("scheduletimezone", $scheduletimezone);
		
		$this->set("http_query", http_build_query($http_query));
    }

    /*	 * **********************************
	 * NAME  : exec
	 * INPUT : NONE
	 * OUTPUT: NONE
	 * DESC  :
	 * NOTICE:
	 * CREATE: 2016.10.11 aoyamas
	 * *********************************** */
	public function record01() {

		if(!isset($this->public_user_data['system_user_id'])){
			$this->redirect('/login/');
			return;
		}

		$user_id = $this->public_user_data['system_user_id'];

		$karte_info = [
            'no' => '9999999',
            'karte_date' => 'YYYY/MM/DD 10:00:00',
            'name' => "苗字 名前",
            'reference_no' => "999-999-999",
            'half_code' => "濃いグレー",
            'brand_name' => "ブランド名",
            'material_name' => "ウール ポリエステル",
            'delivery_date' => "2020/12/01 ～ 12/03",
            'maker_name' => "メーカー名",
        ];
                
		$this->set("karte_info", $karte_info);

		$chart_id = REQUEST::get_data("chart_id");
		$item_id = REQUEST::get_data("item_id");

		$url = Conf::read('REST_API.BASE_URL') . "/getItemDetail/?user_id=$user_id&chart_id=$chart_id&item_id=$item_id";
		
		$res = $this->curl_api_get($url);

		if ($res['code'] != '200') {
			$this->redirect('/counseling/');
			return;
		}


		$karte_item_info = $res['item'];

		//画像用

		$image_base = "/mypage/chart_image.html?mode=" . $karte_item_info['imagecode'];

		$this->set("image_1_url", $image_base . "&small=" . $karte_item_info['dirtscreendetailsfront'] . "&large=" . $karte_item_info['dirtscreenexpansionfront']);
		$this->set("image_2_url", $image_base . "&small=" . $karte_item_info['dirtscreendetailsafter'] . "&large=" . $karte_item_info['dirtscreenexpansionafter']);
		$this->set("image_3_url", $image_base . "&small=" . $karte_item_info['comprehensioncheckscreendetailsfront'] . "&large=" . $karte_item_info['comprehensioncheckscreenexpansionfront']);
		$this->set("image_4_url", $image_base . "&small=" . $karte_item_info['comprehensioncheckscreendetailsafter'] . "&large=" . $karte_item_info['comprehensioncheckscreenexpansionafter']);

		$karte_info = [
            'no' => '9999999',
            'karte_date' => 'YYYY/MM/DD 10:00:00',
            'name' => "苗字 名前",
            'reference_no' => "999-999-999",
            'half_code' => "濃いグレー",
            'brand_name' => "ブランド名",
            'material_name' => "ウール ポリエステル",
            'delivery_date' => "2020/12/01 ～ 12/03",
            'maker_name' => "メーカー名",
		];
		
		$karte_info['no'] = $karte_item_info['chart_id'];

		$reference_no = str_split($karte_item_info['item_id'], 3);
		$reference_no = implode("-", $reference_no);

		$karte_info['reference_no'] = $reference_no;
		$karte_info['name'] = $karte_item_info['counselingpersonname'];
		$karte_info['karte_date'] = $karte_item_info['counselingdate'];
		$karte_info['class'] = $karte_item_info['classificationname'];
		$karte_info['half_code'] = $karte_item_info['colorname'];
		$karte_info['brand_name'] = $karte_item_info['brand'];
		$karte_info['material_name'] = $karte_item_info['sozai'];
		$karte_info['delivery_date'] = $karte_item_info['reportscheduleddate'];
		$karte_info['maker_name'] = $karte_item_info['brand'];
                
		$this->set("karte_info", $karte_info);


		// 画像
		if (count($karte_item_info['thingimages'])) {
			$this->set("thumb_url", $this->external_target . $karte_item_info['thingimages'][0]);
		} else {
			$this->set("thumb_url", "");
		}
	

		$this->set("dirtscreennote", $karte_item_info['dirtscreennote']);
		$this->set("comprehensioncheckscreennote", $karte_item_info['comprehensioncheckscreennote']);


		$care_condition = [
            '黄ばんでいる'
		];

		$care_condition = [];
		if (isset($karte_item_info['chartdetailspresentcondition'])) {
			foreach ($karte_item_info['chartdetailspresentcondition'] as $row) {
				$care_condition[] = $row['text'];
			}
		}
		

        $this->set("care_condition", $care_condition);

        $change_condition = [
            '白っぽくなる 色が薄くなる',
            '移染',
            '変色／脱色',
            '色むら',
            '生地折れ',
            '風合い変わり',
		];
		
		$change_condition = [];
		if (isset($karte_item_info['chartdetailsdamage'])) {
			foreach ($karte_item_info['chartdetailsdamage'] as $row) {
				$change_condition[] = $row['text'];
			}
		}

        $this->set("change_condition", $change_condition);

        $confirm_things = [
            'ボタン脱着（アクアドレイのみ→不要）',
		];

		$confirm_things = [];
		if (isset($karte_item_info['chartdetailsfinish'])) {
			foreach ($karte_item_info['chartdetailsfinish'] as $row) {
				$confirm_things[] = $row['text'];
			}
		}

        $this->set("confirm_things", $confirm_things);

		$note = "製品洗い→シワ感あり 裏地オフ白";
		$note = $karte_item_info['thingnote'];

        $this->set("note", $note);

        $evaluation = [
            [
                'name' => "風合い",
                'value' => 3,
            ],
            [
                'name' => "色合い",
                'value' => 3,
            ],
            [
                'name' => "風繊維の状態合い",
                'value' => 3,
            ],
            [
                'name' => "シルエットの状態",
                'value' => 3,
            ],
            [
                'name' => "シミ／汚れの状態",
                'value' => 3,
            ],
        ];

		$this->set("evaluation", $evaluation);

		/**
		 * ここから確認項目の欄
		 */

		$counseling_navl_list = [];

		
		$index = (!StaticFunction::is_empty(REQUEST::get_data('index'))) ? REQUEST::get_data('index') : 1;
		$replon = (!StaticFunction::is_empty(REQUEST::get_data('replon'))) ? REQUEST::get_data('replon') : "";

		$http_query_all = [];
		$http_query_all['chart_id'] = $chart_id;
		$http_query_all['item_id'] = $item_id;
		if (!isset($replon)) {
			$http_query_all['replin'] = $replon;
		}

		$http_query = http_build_query($http_query_all);

		$this->set("http_query", $http_query);

		$is_cansel = REQUEST::get_data('cansel');
		if (!isset($is_cansel)) {
			$cancelflg = $karte_item_info['cancelflg'];
			$this->set("is_cansel", $cancelflg);
		} else if (isset($is_cansel)) {	
			// cancelItem
			$url = Conf::read('REST_API.BASE_URL') . "/cancelItem";
			$post_data = [
				'user_id' => $user_id,
				'chart_id' => $chart_id,
				'item_id'  => $item_id,
				'cancelflg' => $is_cansel,
			];
			$this->curl_api_post($url, $post_data);
			$this->set("is_cansel", $is_cansel);
		}


		// 仕上げコード
		// 1050 : センターラインあり
		// 1051 : センターラインなし
		// 1075 : シャツ皴付けあり

		// 検品フラグ
		// 1:検品必要 2:検品済み 0~null:検品不要
		$inspectionnecessity = $karte_item_info['inspectionnecessity'];

		$chart_index = REQUEST::get_data('chart_index');
		if (!isset($index)) {
			$chart_index = 0;
		} else {
			$http_query_all['chart_index'] = $chart_index;
		}

		$this->set("class_sub", "");

		$index = REQUEST::get_data('index');
		if (!isset($index)) {
			$index = 0;
		} else {
			$http_query_all['index'] = $index;
		}

		$navi_str = "";

		// 検品を調べる
		if ($inspectionnecessity == 1) {
			$chartdetailsinspection = $karte_item_info['chartdetailsinspection'];
			/*
			$chartdetailsinspection = [
				[
					'chart_id' => $chart_id,
					'item_id'  => $item_id,
					'lineno'   => 1,
					'lineno2'  => 1,
					'text'     => '濃い色に染め替えされますか？（リプロン染め替え 16,500 円 ）',
					'inspectionflg' => 0,
				]
			];
			*/

			$chart_answer = REQUEST::get_data('chart_answer');
			if (isset($chart_answer)) {
				$url = Conf::read('REST_API.BASE_URL') . "/updateInspection";
				$chart_detail = $chartdetailsinspection[$chart_index];
	
				$post_data = [
					'user_id'  => $user_id,
					'chart_id' => $chart_id,
					'item_id'  => $item_id,
					'lineno'   => [$chart_detail['lineno']],
					'lineno2'  => [$chart_detail['lineno2']],
					'answer'   => [$chart_answer],
					'inspection' => 2,
				];
				$this->curl_api_post($url, $post_data);
				$chart_index++;
			}
	
			if ($chart_index < count($chartdetailsinspection)) {
				$chart_detail = $chartdetailsinspection[$chart_index];
	
				$navi_str = "<p>".$chart_detail['text']."</p>";
	
				$navi_str.= <<<HTML
<form method="GET"><input type="hidden" name="chart_id" value="{$chart_id}"><input type="hidden" name="item_id" value="{$item_id}"><input type="hidden" name="chart_index" value="{$chart_index}"><div class="btnArea aln"><div class="comment"><textarea name="chart_answer" placeholder="ご希望の入力"></textarea></div><div class="btn"><button type="submit" class="mt0">送  信</button></div></div></form>
HTML;
	
				$counseling_navl_list = [
					htmlspecialchars($navi_str),
				];
	
				$this->set("class_sub", "sub");
				$this->set("counseling_navl_list", $counseling_navl_list);
				return;
			}
		}
		

		/**
		 * 仕上備考コードの変更が入っていたら
		 * 更新を行いindexを進める
		 */
		$change_code = REQUEST::get_data('change_code');
		if (isset($change_code)) {
			$http_query_all['change_code'] = $change_code;

			$url = Conf::read('REST_API.BASE_URL') . "/updateStateProcessing";

			$item_detail = $karte_item_info['chartdetailsfinish'][$index];

			$post_data = [
				'user_id'  => $user_id,
				'chart_id' => $chart_id,
				'lineno'   => $item_detail['lineno'],
				'lineno2'  => $item_detail['lineno2'],
				'code'     => $change_code,
			];
			$this->curl_api_post($url, $post_data);
			$index++;
		}

		
		/**
		 * 確認項目がすべて終わり、
		 * 検品フラグおよび同意フラグも全て確認済みの場合
		 */
		$max_cousenling_count = 0;
		foreach ($karte_item_info['chartdetailsfinish'] as $row) {
			/*
-- ズボンのセンターライン 1050:あり、1051:なし
-- シャツの仕上げ 1075:糊付け、1078:糊なし、1077:糊固め
以外はカウントしない
			 */
			$confirm_code = [1050, 1051, 1075, 1078, 1077];
			if (in_array($row['code'], $confirm_code)) {
				$max_cousenling_count++;
			}
		}

		/*
		$finish_confirm = REQUEST::get_data('confirm');
		if (isset($finish_confirm)) {
			$http_query_all['confirm'] = $finish_confirm;
		}

		if ($index < $max_cousenling_count) {

			// コードを確認
			$finish_code = $karte_item_info['chartdetailsfinish'][$index]['code'];

 			if (in_array($finish_code, [1050, 1051])) {
				if ($finish_code == 1050) {
					$confirm_change_str = "あり";
					$confirm_yesno_str = "なし";
				} else {
					$confirm_change_str = "なし";
					$confirm_yesno_str = "あり";
				}

				if (isset($finish_confirm)) {
					$navi_str = '<p>ズボンのセンターライン「'.$confirm_yesno_str.'」に変更します。<br>よろしいでしょうか？</p>';
					$http_query_all['index'] = $index;

					$yes_query = $http_query_all;
					$no_query  = $http_query_all;

					$yes_query['change_code'] = 1051;

					//$navi_str.= "<div class='btnArea'><div class='btn'><form action='./record01.html' method='get'><button type='submit' class='mt0'>確 定</button></form></div></div>";	
				} else {
					$navi_str = '<p>仕上げのお好みをお聞かせください。<br>ズボンのセンターラインは「'.$confirm_change_str.'」でよろしいでしょうか？</p>';
					$http_query_all['index'] = $index;

					$yes_query = $http_query_all;
					$no_query  = $http_query_all;

					$yes_query['change_code'] = 1050;
					$no_query['confirm'] = 1;
				}

				$http_query_yes = http_build_query($yes_query);
				$http_query_no  = http_build_query($no_query);

				$navi_str.= <<<HTML
<div class="btnArea"><div class="btn"><button type="submit" class="mt0" href="record01.html?{$http_query_yes}">は い</button></div><div class="btn"><button type="reset" class="reset mt0" href="record01.html?{$http_query_no}">いいえ</button></div></div>
HTML;

			} else if (in_array($finish_code, [1075, 1078, 1077])) {
				$navi_str = '<p>仕上げのお好みをお聞かせください。<br>シャツの糊付けのご希望ございますか？</p>';
				$http_query_all['index'] = $index;

				$http_query  = http_build_query($http_query_all);

				$navi_str.= <<<HTML
<div class="btnArea spLayout"><div class="btn"><button type="submit" href="record01.html?{$http_query}&change_code=1075">普 通</button></div><div class="btn"><button type="submit" href="record01.html?{$http_query}&change_code=1078">強 め</button></div><div class="btn"><button type="reset" class="reset mt0" href="record01.html?{$http_query}&change_code=1077">糊付けなし</button></div></div>
HTML;
			}

			$counseling_navl_list = [
				htmlspecialchars($navi_str)
			];

			$this->set("counseling_navl_list", $counseling_navl_list);

			return;
		}
		*/

		// 同意
		$consent = REQUEST::get_data('consent');
		$consentdocumentflg = $karte_item_info['consentdocumentflg'];
		$this->set('consentdocumentflg', $consentdocumentflg);

		if (!isset($consentdocumentflg) or $consentdocumentflg == 1) {

			if (!isset($consent)) {
				$http_query = http_build_query($http_query_all);

				$navi_str = '<p>こちらのお預かり品は、繊維・素材・染色等の特性や汚損状況を総合的に<br>診断した結果、カルテに記載の損傷が起こる可能性が<br>通常よりも高いアイテムです。</p>';
				//$navi_str.= "<div class='btnArea'><div class='btn'><a href='./record01.html?replon=1'>はい</a><a href='./record01.html?index=2&replon=2'>いいえ</a></div></div>";
				$navi_str.= <<<HTML
<div class="btnArea"><div class="btn"><button type="submit" class="mt0" href="record01.html?{$http_query}&consent=1">は い</button></div></div>
HTML;
	
				$counseling_navl_list = [
					htmlspecialchars($navi_str),
				];
	
				$this->set("counseling_navl_list", $counseling_navl_list);
				return;
			} else if ($consent == 1) {
				$http_query = http_build_query($http_query_all);

				$navi_str = '<p>十分注意して作業しますが、状態によってはお届け日時を<br>延長する場合があるほか、万一着用・使用できなくなった場合に<br>弁償や代金返金等の対応は致しかねます。</p>';
				//$navi_str.= "<div class='btnArea'><div class='btn'><a href='./record01.html?replon=1'>はい</a><a href='./record01.html?index=2&replon=2'>いいえ</a></div></div>";
				$navi_str.= <<<HTML
<div class="btnArea spLayout spLayout03"><div class="btn"><button type="submit" class="mt0" href="record01.html?{$http_query}&consent=2">同意する</button></div><div class="btn mr0"><button type="reset" class="reset mt0" href="record01.html?{$http_query}">同意しない</button></div><span class="small">（ケアラベルが付いていない場合も含みます）</span></div>
HTML;
	
				$counseling_navl_list = [
					htmlspecialchars($navi_str),
				];
	
				$this->set("counseling_navl_list", $counseling_navl_list);
				return;
			} else if ($consent == 2) {
				// updateConsent
				$url = Conf::read('REST_API.BASE_URL') . "/updateConsent";

				$item_detail = $karte_item_info['chartdetailsfinish'][$index];

				$post_data = [
					'user_id'  => $user_id,
					'chart_id' => $chart_id,
					'item_id'  => $item_id,
				];
				$this->curl_api_post($url, $post_data);
			}			
		}




		$navi_str = '<p>電子カルテをご確認いただけましたら、<br>次はメンテナンス内容と金額の確認にまいりましょう。</p>';

		$http_query = http_build_query($http_query_all);
		$navi_str.= <<<HTML
<div class="btnArea"><div class="btn"><button type="submit" class="mt0" href="record01_estimate.html?{$http_query}">は い</button></div></div>
HTML;

		$counseling_navl_list = [
			htmlspecialchars($navi_str)
		];

		/*
		if ($index == 2) {
			$http_query_all['index'] = 3;
			$finish_code = 1050;

			if ($finish_code == 1050) {
				$navi_str = '<p>仕上げのお好みをお聞かせください。<br>ズボンのセンターラインは「あり」でよろしいでしょうか？</p>';
				//$navi_str.= "<div class='btnArea'><div class='btn'><form action='./record01.html' method='get'><button type='submit' class='mt0'>確 定</button></form></div></div>";

				$http_query = http_build_query($http_query_all);

				$navi_str.= <<<HTML
<div class="btnArea"><div class="btn"><button type="submit" class="mt0" href="record01.html?{$http_query}&finish=1">は い</button></div><div class="btn"><button type="reset" class="reset mt0" href="record01.html?{$http_query}&finish=2">いいえ</button></div></div>
HTML;
				$counseling_navl_list[] = $navi_str;
			}

			$counseling_navl_list = [
				htmlspecialchars($navi_str)
			];
		}

		if ($index == 3) {
			$navi_str = '<p>ズボンのセンターライン「なし」変更します。<br>よろしいでしょうか？</p>';

			$http_query_all['index'] = 4;

			$http_query = http_build_query($http_query_all);

			$http_query_all['index'] = 2;

			$http_query_back = http_build_query($http_query_all);

			$navi_str.= <<<HTML
<div class="btnArea"><div class="btn"><button type="submit" class="mt0" href="record01.html?{$http_query}&finish=1">は い</button></div><div class="btn"><button type="reset" class="reset mt0" href="record01.html?{$http_query_back}">いいえ</button></div></div>
HTML;

			$counseling_navl_list = [
				htmlspecialchars($navi_str)
			];
		}

		if ($index == 4) {
			$navi_str = '<p>電子カルテをご確認いただけましたら、<br>次はメンテナンス内容と金額の確認にまいりましょう。</p>';

			$navi_str.= <<<HTML
<div class="btnArea"><div class="btn"><button type="submit" class="mt0" href="record01_estimate.html">は い</button></div></div>
HTML;

			$counseling_navl_list = [
				htmlspecialchars($navi_str)
			];
		}
		*/

		/*
		$finish_code = 1050;

		if ($finish_code == 1050) {
			$navi_str = '仕上げのお好みをお聞かせください。<br>ズボンのセンターラインは「あり」でよろしいでしょうか？';
			$navi_str.= "<div class='btnArea'><div class='btn'><form action='./record01.html' method='get'><button type='submit' class='mt0'>確 定</button></form></div></div>";
		}
		
		$counseling_navl_list = [
			"<p>電子カルテをご確認いただけましたら<br>次はメンテナンス内容と金額の確認にまいりましょう。</p>",
			"<p>電子カルテをご確認いただけましたら<br>次はメンテナンス内容と金額の確認にまいりましょう。</p><div class='btnArea'><div class='btn'><form action='./index_comment01.html' method='get'><button type='submit' class='mt0'>確 定</button></form></div></div>",
		];
		*/
		
		$this->set("counseling_navl_list", $counseling_navl_list);
    }

    /*	 * **********************************
	 * NAME  : exec
	 * INPUT : NONE
	 * OUTPUT: NONE
	 * DESC  :
	 * NOTICE:
	 * CREATE: 2016.10.11 aoyamas
	 * *********************************** */
	public function record01_cancel() {

		$karte_info = [
            'no' => '9999999',
            'karte_date' => 'YYYY/MM/DD 10:00:00',
            'name' => "苗字 名前",
            'reference_no' => "999-999-999",
            'half_code' => "濃いグレー",
            'brand_name' => "ブランド名",
            'material_name' => "ウール ポリエステル",
            'delivery_date' => "2020/12/01 ～ 12/03",
            'maker_name' => "メーカー名",
        ];
                
        $this->set("karte_info", $karte_info);

        $care_condition = [
            '黄ばんでいる'
        ];

        $this->set("care_condition", $care_condition);

        $change_condition = [
            '白っぽくなる 色が薄くなる',
            '移染',
            '変色／脱色',
            '色むら',
            '生地折れ',
            '風合い変わり',
        ];

        $this->set("change_condition", $change_condition);

        $confirm_things = [
            'ボタン脱着（アクアドレイのみ→不要）',
        ];

        $this->set("confirm_things", $confirm_things);

        $note = "製品洗い→シワ感あり 裏地オフ白";

        $this->set("note", $note);

        $evaluation = [
            [
                'name' => "風合い",
                'value' => 3,
            ],
            [
                'name' => "色合い",
                'value' => 3,
            ],
            [
                'name' => "風繊維の状態合い",
                'value' => 3,
            ],
            [
                'name' => "シルエットの状態",
                'value' => 3,
            ],
            [
                'name' => "シミ／汚れの状態",
                'value' => 3,
            ],
        ];

        $this->set("evaluation", $evaluation);
		
    }

    /*	 * **********************************
	 * NAME  : exec
	 * INPUT : NONE
	 * OUTPUT: NONE
	 * DESC  :
	 * NOTICE:
	 * CREATE: 2016.10.11 aoyamas
	 * *********************************** */
	public function record01_estimate() {

		if(!isset($this->public_user_data['system_user_id'])){
			$this->redirect('/login/');
			return;
		}

		$user_id = $this->public_user_data['system_user_id'];

		$chart_id = REQUEST::get_data("chart_id");
		$item_id = REQUEST::get_data("item_id");

		// 送料を計算する

		// アイテム一覧を取得
		$url = Conf::read('REST_API.BASE_URL') . "/getItemSearch/?user_id=$user_id&type=1&chart_id=$chart_id";
		$res = $this->curl_api_get($url);

		// アイテム個数
		$item_count = $res['item_count'];
		$item_list = $res['item_list'];

		$record_all = [];
		if ($res['code'] == '200') {
			foreach ($res['item_list'] as $row) {
				$status = 0;

				$reference_no = $row['item_id'];

				$item_split_str = str_split($reference_no, 3);
				$reference_no = implode("-", $item_split_str);

				$data = [
					'thumb_url' => $this->external_target . "/netkuroku/images/" . $row['item_id'] . ".jpg&type=chart",
					'chart_id' => $row['chart_id'],
					'item_id'  => $row['item_id'],
					'reference_no' => $reference_no,
					'reference_name' => $row['brand_name'],
					'status_name' => $row['item_name'],
				];

				$record_all[] = $data;
			}
		}

		$this->set("counseling_all", $record_all);

		$camainte_total_price = 0;
		$option_total_price = 0;

		$caremainte_menu = [];
		$option_menu = [];

		$url = Conf::read('REST_API.BASE_URL') . "/getItemDetail/?user_id=$user_id&chart_id=$chart_id&item_id=$item_id";
		$res = $this->curl_api_get($url);

		if ($res['code'] != '200') {
			$this->redirect('/counseling/');
			return;
		}

		$karte_item_info = $res['item'];		

		$karte_info = [
			'no' => '9999999',
			'karte_date' => 'YYYY/MM/DD 10:00:00',
			'name' => "苗字 名前",
			'reference_no' => "999-999-999",
			'half_code' => "濃いグレー",
			'brand_name' => "ブランド名",
			'material_name' => "ウール ポリエステル",
			'delivery_date' => "2020/12/01 ～ 12/03",
			'maker_name' => "メーカー名",
		];
		
		$karte_info['no'] = $karte_item_info['chart_id'];

		$reference_no = str_split($karte_item_info['item_id'], 3);
		$reference_no = implode("-", $reference_no);

		$karte_info['reference_no'] = $reference_no;
		$karte_info['name'] = $karte_item_info['counselingpersonname'];
		$karte_info['karte_date'] = $karte_item_info['counselingdate'];
		$karte_info['half_code'] = $karte_item_info['colorname'];
		$karte_info['brand_name'] = $karte_item_info['brand'];
		$karte_info['material_name'] = $karte_item_info['sozai'];
		$karte_info['delivery_date'] = $karte_item_info['reportscheduleddate'];
		$karte_info['maker_name'] = ""; // $karte_item_info['brand'];
		$karte_info['class'] = $karte_item_info['classificationname'];
				
		$this->set("karte_info", $karte_info);

		// メンテナンス情報を取得
		$chartdetailsmaintenance = $karte_item_info['chartdetailsmaintenance'];
		
		foreach ($chartdetailsmaintenance as $row_data) {
			if ($row_data['maintenancetype'] > 0) {

				$group_id = $row_data['maintenancegroup'];
				if (!isset($caremainte_menu[$group_id])) {
					$caremainte_menu[$group_id] = [
						'name' => $row_data['maintenancegroupname'],
						'list' => [],
					];
				}

				$requred_flg = 0;
				if ($row_data['maintenancetype'] == 2) {
					$requred_flg = 1;
				}

				$subtract_flg = 0;
				$check_flg = 1;
				if ($row_data['maintenanceunitprice'] < 0) {
					$check_flg = 0;
					$subtract_flg = 1;		
					$requred_flg = 0;			
				}

				$caremainte_menu[$group_id]['list'][] = [
					'name' => $row_data['maintenancename'],
					'price' => $row_data['maintenanceunitprice'],
					'required_flg' => $requred_flg,
					'subtract_flg' => $subtract_flg,
					'check_flg' => $check_flg,
				];

			}
		}
		
		foreach ($chartdetailsmaintenance as $row_data) {
			if ($row_data['maintenancetype'] == 0) {

				$group_id = $row_data['maintenancegroup'];
				if (!isset($option_menu[$group_id])) {
					$option_menu[$group_id] = [
						'name' => $row_data['maintenancegroupname'],
						'list' => [],
					];
				}

				$requred_flg = 0;
				if ($row_data['maintenancetype'] == 2) {
					$requred_flg = 1;
				}

				$subtract_flg = 0;
				$check_flg = 1;
				if ($row_data['maintenanceunitprice'] < 0) {
					$check_flg = 0;
					$subtract_flg = 1;		
					$requred_flg = 0;			
				}

				$option_menu[$group_id]['list'][] = [
					'name' => $row_data['maintenancename'],
					'price' => $row_data['maintenanceunitprice'],
					'txt' => "",
					'required_flg' => $requred_flg,
					'subtract_flg' => $subtract_flg,
					'check_flg' => $check_flg,
				];

			}
		}

		$this->set("caremainte_menu", $caremainte_menu);
		$this->set("option_menu", $option_menu);

		// 合計金額を算出する
		foreach ($caremainte_menu as $key => $val) {
			foreach ($val['list'] as $row) {
				$camainte_total_price += $row['price'];		
			}
		}

		// 合計金額を算出する			
		foreach ($option_menu as $key => $val) {
			foreach ($val['list'] as $row) {
				if ($row['check_flg']) {
					$option_total_price += $row['price'];
				}				
			}
		}

		// 合計金額
		$this->set("all_total_price", $camainte_total_price + $option_total_price);		

		$counseling_navl_list = [
			"<p>電子カルテをご確認いただけましたら<br>次はメンテナンス内容と金額の確認にまいりましょう。</p>",
		];
		
		$this->set("counseling_navl_list", $counseling_navl_list);

		$this->set("chart_id", $chart_id);
		$this->set("item_id", $item_id);		
    }

    /*	 * **********************************
	 * NAME  : exec
	 * INPUT : NONE
	 * OUTPUT: NONE
	 * DESC  :
	 * NOTICE:
	 * CREATE: 2016.10.11 aoyamas
	 * *********************************** */
	public function record01_estimate02() {

		
		/*

		

		$record_all = [
            [
                'reference_no' => '999-999-999',
                'reference_name' => 'お預かり品目',
                'status_name' => 'カルテ状態',
                'status' => 0,
            ],
            [
                'reference_no' => '999-999-999',
                'reference_name' => 'お預かり品目',
                'status_name' => 'カルテ状態',
                'status' => 1,
            ],
            [
                'reference_no' => '999-999-999',
                'reference_name' => 'お預かり品目',
                'status_name' => 'カルテ状態',
                'status' => 2,
            ],
            [
                'reference_no' => '999-999-999',
                'reference_name' => 'お預かり品目',
                'status_name' => 'カルテ状態',
                'status' => 3,
            ],
        ];
		
		$this->set("counseling_all", $record_all);
		*/

		if(!isset($this->public_user_data['system_user_id'])){
			$this->redirect('/login/');
			return;
		}

		$user_id = $this->public_user_data['system_user_id'];

		// POST データ受け取り
		$post_data = REQUEST::post_data();	

		// ケアメンテチェックフラグ
		$caremainte_check_flg = REQUEST::post_data('caremainte_check_flg');

		$chart_id = REQUEST::post_data("chart_id");
		$item_id = REQUEST::post_data("item_id");

		// アイテム一覧を取得
		$url = Conf::read('REST_API.BASE_URL') . "/getItemSearch/?user_id=$user_id&type=1&chart_id=$chart_id";
		$res = $this->curl_api_get($url);


		$camainte_total_price = 0;
		$option_total_price = 0;

		$caremainte_menu = [];
		$option_menu = [];

		$record_all = [];

		$item_list = $res['item_list'];
		if ($res['code'] == '200') {
			foreach ($res['item_list'] as $row) {
				$status = 0;
				// 承認済み
				if ($row['consentdocumentflg'] == 1) {
					$status = 1;
				} 
				
				// 検品
				if ($row['inspectionnecessity'] == 1) {
					$status = 2;
				} 

				// キャンセル
				if ($row['cancelflg'] == 1) {
					$status = 3;
				}

				$reference_no = $row['item_id'];

				$item_split_str = str_split($reference_no, 3);
				$reference_no = implode("-", $item_split_str);

				$data = [
					'thumb_url' => $this->external_target . "/netkuroku/images/" . $row['item_id'] . ".jpg&type=chart",
					'chart_id' => $row['chart_id'],
					'item_id'  => $row['item_id'],
					'reference_no' => $reference_no,
					'reference_name' => $row['brand_name'],
					'status_name' => $row['item_name'],
					'status' => $status,
				];

				$record_all[] = $data;
			}
		}

		$this->set("counseling_all", $record_all);

		$url = Conf::read('REST_API.BASE_URL') . "/getItemDetail/?user_id=$user_id&chart_id=$chart_id&item_id=$item_id";
		$res = $this->curl_api_get($url);

		if ($res['code'] != '200') {
			$this->redirect('/counseling/');
			return;
		}

		$url = Conf::read('REST_API.BASE_URL') . "/getItemDetail/?user_id=$user_id&chart_id=$chart_id&item_id=$item_id";
		$res = $this->curl_api_get($url);

		if ($res['code'] != '200') {
			$this->redirect('/counseling/');
			return;
		}

		$karte_item_info = $res['item'];		

		$karte_info = [
			'no' => '9999999',
			'karte_date' => 'YYYY/MM/DD 10:00:00',
			'name' => "苗字 名前",
			'reference_no' => "999-999-999",
			'half_code' => "濃いグレー",
			'brand_name' => "ブランド名",
			'material_name' => "ウール ポリエステル",
			'delivery_date' => "2020/12/01 ～ 12/03",
			'maker_name' => "メーカー名",
		];
		
		$karte_info['no'] = $karte_item_info['chart_id'];

		$reference_no = str_split($karte_item_info['item_id'], 3);
		$reference_no = implode("-", $reference_no);

		$karte_info['reference_no'] = $reference_no;
		$karte_info['name'] = $karte_item_info['counselingpersonname'];
		$karte_info['karte_date'] = $karte_item_info['counselingdate'];
		$karte_info['half_code'] = $karte_item_info['colorname'];
		$karte_info['brand_name'] = $karte_item_info['brand'];
		$karte_info['material_name'] = $karte_item_info['sozai'];
		$karte_info['delivery_date'] = $karte_item_info['reportscheduleddate'];
		$karte_info['maker_name'] = ""; // $karte_item_info['brand'];
		$karte_info['class'] = $karte_item_info['classificationname'];
				
		$this->set("karte_info", $karte_info);

		// メンテナンス情報を取得
		$chartdetailsmaintenance = $karte_item_info['chartdetailsmaintenance'];

		$lineno = [];
		$lineno2 = [];
		$enableflg = [];
		
		foreach ($chartdetailsmaintenance as $row_data) {
			if ($row_data['maintenancetype'] > 0) {

				$group_id = $row_data['maintenancegroup'];
				if (!isset($caremainte_menu[$group_id])) {
					$caremainte_menu[$group_id] = [
						'name' => $row_data['maintenancegroupname'],
						'list' => [],
					];
				}

				$requred_flg = 0;
				if ($row_data['maintenancetype'] == 2) {
					$requred_flg = 1;
				}

				$subtract_flg = 0;
				$check_flg = 1;
				if ($row_data['maintenanceunitprice'] < 0) {
					$check_flg = 0;
					$subtract_flg = 1;		
					$requred_flg = 0;			
				}

				$caremainte_menu[$group_id]['list'][] = [
					'name' => $row_data['maintenancename'],
					'price' => $row_data['maintenanceunitprice'],
					'required_flg' => $requred_flg,
					'subtract_flg' => $subtract_flg,
					'check_flg' => $check_flg,
				];

				$lineno[] = $row_data['lineno'];
				$lineno2[] = $row_data['lineno2'];
				$enableflg[] = $row_data['enableflg'];

			}
		}

		foreach ($caremainte_menu as $key => $val) {
			foreach($val['list'] as $row_key => $row) {
				if (isset($caremainte_check_flg[$key][$row_key])) {
					$caremainte_menu[$key]['list'][$row_key]['check_flg'] = $caremainte_check_flg[$key][$row_key];
				} else {
					$caremainte_menu[$key]['list'][$row_key]['check_flg'] = 0;
				}
			}
		}
		
		foreach ($chartdetailsmaintenance as $row_data) {
			if ($row_data['maintenancetype'] == 0) {

				$group_id = $row_data['maintenancegroup'];
				if (!isset($option_menu[$group_id])) {
					$option_menu[$group_id] = [
						'name' => $row_data['maintenancegroupname'],
						'list' => [],
					];
				}

				$requred_flg = 0;
				if ($row_data['maintenancetype'] == 2) {
					$requred_flg = 1;
				}

				$subtract_flg = 0;
				$check_flg = 1;
				if ($row_data['maintenanceunitprice'] < 0) {
					$check_flg = 0;
					$subtract_flg = 1;		
					$requred_flg = 0;			
				}

				$option_menu[$group_id]['list'][] = [
					'name' => $row_data['maintenancename'],
					'price' => $row_data['maintenanceunitprice'],
					'txt' => "",
					'required_flg' => $requred_flg,
					'subtract_flg' => $subtract_flg,
					'check_flg' => $check_flg,
				];

				$lineno[] = $row_data['lineno'];
				$lineno2[] = $row_data['lineno2'];
				$enableflg[] = $row_data['enableflg'];
			}
		}

		foreach ($option_menu as $key => $val) {
			foreach($val['list'] as $row_key => $row) {
				if (isset($caremainte_check_flg[$key][$row_key])) {
					$option_menu[$key]['list'][$row_key]['check_flg'] = $caremainte_check_flg[$key][$row_key];
				} else {
					$option_menu[$key]['list'][$row_key]['check_flg'] = 0;
				}
			}
		}

		$this->set("caremainte_menu", $caremainte_menu);
		$this->set("option_menu", $option_menu);

		// 合計金額を算出する
		$camainte_total_price = 0;
		foreach ($caremainte_menu as $key => $val) {
			foreach ($val['list'] as $row) {
				if ($row['check_flg']) {
					$camainte_total_price += $row['price'];
				}				
			}
		}

		$option_check_flg = REQUEST::post_data('option_check_flg');

		foreach ($option_menu as $key => $val) {
			foreach($val['list'] as $row_key => $row) {
				if (isset($option_check_flg[$key][$row_key])) {
					$option_menu[$key]['list'][$row_key]['check_flg'] = $option_check_flg[$key][$row_key];
				} else {
					$option_menu[$key]['list'][$row_key]['check_flg'] = 0;
				}
			}
		}
		
		// 合計金額を算出する
		$option_total_price = 0;
		foreach ($option_menu as $key => $val) {
			foreach ($val['list'] as $row) {
				if ($row['check_flg']) {
					$option_total_price += $row['price'];
				}				
			}
		}
		
		// ①＋②＝合計金額
		$this->set("all_total_price", $camainte_total_price + $option_total_price );

		$this->set("chart_id", $chart_id);
		$this->set("item_id", $item_id);

		// POSTデータがある場合、セッションに登録する。
		/*
		if (!StaticFunction::is_empty(REQUEST::post_data())) {

			SESSION::write($this->sGroup . '.chart_id', REQUEST::post_data('chart_id'));
			SESSION::write($this->sGroup . '.item_id', REQUEST::post_data('item_id'));
			SESSION::write($this->sGroup . '.option_check_flg', REQUEST::post_data('option_check_flg'));
			SESSION::write($this->sGroup . '.caremainte_check_flg', REQUEST::post_data('caremainte_check_flg'));
			SESSION::write($this->sGroup . '.shipping', REQUEST::post_data('shipping'));

			return;
		}
		*/

		// WEBカウンセリング状態
		$url = Conf::read('REST_API.BASE_URL') . "/updateMaintenanceEnable";
		$post_data = [
			'user_id' => $user_id,
			'chart_id' => $chart_id,
			'item_id' => $item_id,
			'lineno'  => $lineno,
			'lineno2'  => $lineno2,
			'enableflg' => $enableflg,
			'webcounselingstatus' => 2,
		];
		$this->curl_api_post($url, $post_data);


		// コンプリートフラグ
		$url = Conf::read('REST_API.BASE_URL') . "/getItemSearch/?user_id=$user_id&type=1&chart_id=$chart_id";
		$res = $this->curl_api_get($url);

		$complete_flg = 1;
		if ($res['code'] == '200') {
			foreach ($res['item_list'] as $row) {

				if ($row['item_id'] == $item_id) {
					continue;
				}

				if (is_null($row['webcounselingstatus'])) {
					$complete_flg = 0;
					break;
				}
			}
		}

		$this->set('complete_flg', $complete_flg);
	}

	/*	 * **********************************
	 * NAME  : exec
	 * INPUT : NONE
	 * OUTPUT: NONE
	 * DESC  :
	 * NOTICE:
	 * CREATE: 2016.10.11 aoyamas
	 * *********************************** */
	public function record01_result() {

		if(!isset($this->public_user_data['system_user_id'])){
			$this->redirect('/login/');
			return;
		}

		$user_id = $this->public_user_data['system_user_id'];

		$chart_id = REQUEST::get_data('chart_id');

		// アイテム一覧を取得
		$url = Conf::read('REST_API.BASE_URL') . "/getItemSearch/?user_id=$user_id&type=1&chart_id=$chart_id";
		$res = $this->curl_api_get($url);

		if ($res['code'] != '200') {
			$this->redirect('/counseling/');
			return;
		}

		$item_count = $res['item_count'];

		$record_all = [];


		$caremainte_menu = [];
		$camainte_total_price = 0;

		$option_menu = [];
		$option_total_price = 0;


		if ($res['code'] == '200') {
			foreach ($res['item_list'] as $row) {
				$status = 0;

				$reference_no = $row['item_id'];

				$item_split_str = str_split($reference_no, 3);
				$reference_no = implode("-", $item_split_str);

				$data = [
					'thumb_url' => $this->external_target . "/netkuroku/images/" . $row['item_id'] . ".jpg&type=chart",
					'chart_id' => $row['chart_id'],
					'item_id'  => $row['item_id'],
					'reference_no' => $reference_no,
					'reference_name' => $row['brand_name'],
					'status_name' => $row['item_name'],
					'status' => $status,
				];

				$record_all[] = $data;

				$item_id = $row['item_id'];

				$url = Conf::read('REST_API.BASE_URL') . "/getItemDetail/?user_id=$user_id&chart_id=$chart_id&item_id=$item_id";
				$res_detail = $this->curl_api_get($url);

				$karte_item_info = $res_detail['item'];

				// メンテナンス情報を取得
				$chartdetailsmaintenance = $karte_item_info['chartdetailsmaintenance'];

				foreach ($chartdetailsmaintenance as $row_data) {
					if ($row_data['maintenancetype'] > 0) {
		
						$group_id = $row_data['maintenancegroup'];
						if (!isset($caremainte_menu[$group_id])) {
							$caremainte_menu[$group_id] = [
								'name' => $row_data['maintenancegroupname'],
								'list' => [],
							];
						}
		
						$requred_flg = 0;
						if ($row_data['maintenancetype'] == 2) {
							$requred_flg = 1;
						}
		
						$subtract_flg = 0;
						if ($row_data['maintenanceunitprice'] < 0) {
							$check_flg = 0;
							$subtract_flg = 1;		
							$requred_flg = 0;			
						}
		
						$caremainte_menu[$group_id]['list'][] = [
							'name' => $row_data['maintenancename'],
							'price' => $row_data['maintenanceunitprice'],
							'required_flg' => $requred_flg,
							'subtract_flg' => $subtract_flg,
							'lineno'  => $row_data['lineno'],
							'lineno2' => $row_data['lineno2'],
							'check_flg' => 1,
						];

						$camainte_total_price += $row_data['maintenanceunitprice'];

					} else if ($row_data['maintenancetype'] == 0) {

						$group_id = $row_data['maintenancegroup'];
						if (!isset($option_menu[$group_id])) {
							$option_menu[$group_id] = [
								'name' => $row_data['maintenancegroupname'],
								'list' => [],
							];
						}
		
						$requred_flg = 0;
						if ($row_data['maintenancetype'] == 2) {
							$requred_flg = 1;
						}
		
						$subtract_flg = 0;
						$check_flg = 1;
						if ($row_data['maintenanceunitprice'] < 0) {
							$check_flg = 0;
							$subtract_flg = 1;		
							$requred_flg = 0;			
						}
		
						$option_menu[$group_id]['list'][] = [
							'name' => $row_data['maintenancename'],
							'price' => $row_data['maintenanceunitprice'],
							'required_flg' => $requred_flg,
							'subtract_flg' => $subtract_flg,
							'check_flg' => 1,
							'tet' => "",
						];

						$option_total_price += $row_data['maintenanceunitprice'];
		
					}
				}
			}
		}

		$this->set("counseling_all", $record_all);

		$this->set("caremainte_menu", $caremainte_menu);
		$this->set("option_menu", $option_menu);
		
		$shipping = $this->shipping_calc($item_count);
		$this->set("shipping", $shipping);

		// ①＋②＝合計金額
		$this->set("all_total_price", $camainte_total_price + $option_total_price + $shipping);	

		$this->set("chart_id", $chart_id);
		$this->set("item_id", $item_id);
	}
	
	
    /*	 * **********************************
	 * NAME  : exec
	 * INPUT : NONE
	 * OUTPUT: NONE
	 * DESC  :
	 * NOTICE:
	 * CREATE: 2016.10.11 aoyamas
	 * *********************************** */
	public function shipping_calc($item_count) {

		// 送料を計算する
		$shipping = 0;
		if ($item_count >= 31) {
			$shipping += 6000;
		} else if ($item_count <= 30 and $item_count >= 26) {
			$shipping += 5000;
		} else if ($item_count <= 25 and $item_count >= 16) {
			$shipping += 4000;
		} else if ($item_count <= 15 and $item_count >= 11) {
			$shipping += 3000;
		} else if ($item_count <= 10 and $item_count >= 6) {
			$shipping += 2000;
		} else if ($item_count <= 5) {
			$shipping += 1000;
		}

		// 消費税
		$shipping = $shipping * 1.1;

		// ○届先都道府県が"北海道"か"沖縄県"の場合、送料にプラス1000円+消費税加算

		$state = SESSION::read(CONF::read('LOGIN_CATEGORY.PUBLIC') . '.state');
		
		if ($state == "北海道" or $state == "沖縄県") {
			$shipping += 1000 * 1.1;
		}

		SESSION::write($this->sGroup . '.shipping', $shipping);
		
		return $shipping;
	}
	
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
	 * NAME:selectedItemArray
	 * DESC:
	 *  セッション情報をフォームに渡すためにセットする機能
	 * NOTICE:
	 * 		一覧、メール送信用に成形されたアイテム情報配列を返す
	 * CREATE: 2016.11.18 aoyama
	 * UPDATE: 2017.10.30 aoyama
	 * *********************************** */
	private function selectedItemArray($chart_id)
    {
        $api = new Rest();

        $all = false;

        $ret_array = array();
        $format_post_items = array();

        //一覧用を流用して
        $api_array = array();
        $api_array['type'] = 1; // $this->page_type;
        $api_array['pd'] = 0;
        $api_array['pp'] = 99999;
        $api_array['user_id'] = $this->public_user_data['system_user_id'];
        $api_array['chart_id'] = $chart_id;

        if (!$itemList = $api->get_chart_item_list($api_array)) {
            // 無ければ空配列のまま返す
            return $ret_array;
        }

        if (StaticFunction::is_empty($itemList['item_list'])) {
            // 登録が1件もない場合もから配列のまま返す
            return $ret_array;
        }
		foreach ($itemList['item_list'] AS $value) {
            $item_detail = $api->get_item_detail($value['item_id'], $value['chart_id'], $this->public_user_data['system_user_id']);

			if ($item_detail['code'] === '200') {
//                var_dump($item_detail);
				$ret_array[] = array(
					"chart_id" => $value['chart_id'],
					"item_id" => $value['item_id'],
					"classificationname" => $item_detail['item']['classificationname'],
					"color" => $item_detail['item']['colorname'],
					"thumb_url" => $this->external_target . "/netkuroku/images/" . $value['item_id'] . ".jpg",
					"medkaterm" => $value['medkaterm'],
				);
			}
		}

		return $ret_array;
	}

	/*	 * **********************************
	 * NAME:formReturn
	 * DESC:
	 *  セッション情報をフォームに渡すためにセットする機能
	 * NOTICE:
	 * CREATE: 2015.11.27 aoyama
	 * UPDATE: 2016.10.13 aoyama
	 * *********************************** */
	private function formReturn() {

		// セッションの情報をセットしてviewに渡す
		if (!StaticFunction::is_empty(SESSION::read($this->sGroup))) {
			$this->set("name1", SESSION::read($this->sGroup . '.name1'));
			$this->set("name2", SESSION::read($this->sGroup . '.name2'));
			$this->set("name_view", StaticFunction::marge_name(SESSION::read($this->sGroup . '.name1'), SESSION::read($this->sGroup . '.name2')));
			$this->set("zip", SESSION::read($this->sGroup . '.zip'));
			$this->set("state", SESSION::read($this->sGroup . '.state'));
			$this->set("addr1", SESSION::read($this->sGroup . '.addr1'));
			$this->set("addr2", SESSION::read($this->sGroup . '.addr2'));
			$this->set("addr3", SESSION::read($this->sGroup . '.addr3'));
			$this->set("telephone", SESSION::read($this->sGroup . '.telephone'));
			$this->set("telephone2", SESSION::read($this->sGroup . '.telephone2'));
			$this->set("telephone3", SESSION::read($this->sGroup . '.telephone3'));
			$this->set("telephone_view", StaticFunction::marge_phone(SESSION::read($this->sGroup . '.telephone'), SESSION::read($this->sGroup . '.telephone2'), SESSION::read($this->sGroup . '.telephone3')));
			$this->set("year_c", SESSION::read($this->sGroup . '.year_c'));
			$this->set("month_c", SESSION::read($this->sGroup . '.month_c'));
			$this->set("day_c", SESSION::read($this->sGroup . '.day_c'));
			$this->set("time", SESSION::read($this->sGroup . '.time'));
			$this->set("hikitori", SESSION::read($this->sGroup . '.hikitori'));
			$this->set("pays", SESSION::read($this->sGroup . '.pays'));

			$this->set("item_array", SESSION::read($this->sGroup . '.item_array'));
		}
	}
}

?>
