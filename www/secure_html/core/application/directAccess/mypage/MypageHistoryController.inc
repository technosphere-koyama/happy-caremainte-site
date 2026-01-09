<?php

/* * **********************************
 * NAME:MypageHistoryController
 * DESC:
 *  マイページ用のコントローラ(クローズエリア)
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
 * CREATE: 2016.10.25 aoyama
 * UPDATE: 2016.12.3 aoyama
 * 		マイページをSNSと基幹で分離することになったので
 * 		こちらはSNS登録なしでも表示するように調整
 * *********************************** */
class MypageHistoryController extends MypageBaseCommonControllerFrame {

	private $sGroup;
	private $public_user_data;

	/* Constructor */
	public function __construct($type) {

		$this->page_type = $type;

		parent::__construct();
		$this->sGroup = CONF::read('LOGIN_CATEGORY.PUBLIC') . ".wardrobe";
		//セッションからユーザ情報を取得
		$this->public_user_data = SESSION::read(CONF::read('LOGIN_CATEGORY.PUBLIC'));

		//最終公開状態（sslからhttpコンテンツの取得）対策により画像変換ライブラリを作成
		$this->external_target = CONF::read("EXTERNAL_IMAGE.TARGET_SURL");

		$this->set("page_group", "mypage");
	}

	/*	 * **********************************
	 * NAME  : index
	 * INPUT : NONE
	 * OUTPUT: NONE
	 * DESC  :
	 * 		過去のケアメンテご利用履歴(カルテ一覧)より実行されるメソッド
	 * NOTICE:
	 * CREATE: 2016.10.25 aoyama
	 * *********************************** */
	public function indexbac20210929($sort = "ASC") {

		$api = new Rest();

		//一覧用
		//ページ指定文字のサニタイズ
		$pd = (InputVali::is_num(REQUEST::get_data('pd'))) ? REQUEST::get_data('pd') : 0;
		$pp = (InputVali::is_num(REQUEST::get_data('pp'))) ? REQUEST::get_data('pp') : CONF::read('PAGING.DEFAULT_NUM_PUBLIC');

		// 1：過去のケア～　2：ただいまの～　3：ハッピーワードローブ
        $careList = $api->get_user_chart_list($this->public_user_data['system_user_id'], 1, $pd, $pp, "ASC");
        $history_count = $careList['chart_count'];

        $careList = $api->get_user_chart_list($this->public_user_data['system_user_id'], 2, $pd, $pp, "ASC");
        $ordered_count = $careList['chart_count'];

        $careList = $api->get_user_chart_list($this->public_user_data['system_user_id'], 3, $pd, $pp, "ASC");
        $wordrobe_count = $careList['chart_count'];

        $this->set('history_count', $history_count);
        $this->set('ordered_count', $ordered_count);
        $this->set('wordrobe_count', $wordrobe_count);

		if (!$chartList = $api->get_user_chart_list($this->public_user_data['system_user_id'], $this->page_type, $pd, $pp,$sort)) {
			$this->set("alert", "カルテが見つかりません。");
			return;
		}

		if ($chartList['code'] != '200') {
			$this->set("alert", "アイテムが見つかりません。");
			$this->set("chartAllArray", array());
            return;
        }

		if (StaticFunction::is_empty($chartList['chart_list'])) {
			$this->set("alert", "カルテが見つかりません。");
			$this->set("chartAllArray", array());
			return;
		}

		foreach ($chartList['chart_list'] AS $value) {

			$chartAllArray[] = array(
				"chart_id" => $value['chart_id'],
				"chart_link" => "/mypage/" . CONF::read("REST_ORDER_NAME." . $this->page_type) . "/chart.html?chart_id=" . $value['chart_id'],
				"date" => DbDateTime::get_date_type_slash(DbDateTime::get_datetime(DbDateTime::get_timestamp($value['date']))),
				"price" => StaticFunction::count_num_format($value['price']),
				"count" => StaticFunction::count_num_format($value['count'])
			);
		}
		$this->set("chartAllArray", $chartAllArray);

		//ページング出力
		$page = new PAGING();
		$this->set("pageng_html", $page->make_paging($chartList['chart_count']));

		//ブランドリストの取得
		$brand_array = array();
		$brand_result = $api->get_user_brand_search($this->public_user_data['system_user_id']);
		if (!StaticFunction::is_empty($brand_result['brand_list'])) {
			foreach ($brand_result['brand_list'] AS $value) {
				$brand_array[] = $value;
			}
		}
		$this->set("brand_array", $brand_array);

		
	}
	// ------------------------ START of Modification by Manjunathgouda 2021/09/13 ---------------------------------
	/*	 * **********************************
	 * NAME  : index
	 * INPUT : NONE
	 * OUTPUT: NONE
	 * DESC  :
	 * 		過去のケアメンテご利用履歴(カルテ一覧)より実行されるメソッド
	 * NOTICE:
	 * CREATE: 2016.10.25 aoyama
	 * *********************************** */
	public function index($sort = "ASC") {

		$api = new Rest();

		//一覧用
		//ページ指定文字のサニタイズ
		$pd = (InputVali::is_num(REQUEST::get_data('pd'))) ? REQUEST::get_data('pd') : 0;
		$pp = (InputVali::is_num(REQUEST::get_data('pp'))) ? REQUEST::get_data('pp') : CONF::read('PAGING.DEFAULT_NUM_PUBLIC');
	
		// 1：過去のケア～　2：ただいまの～　3：ハッピーワードローブ
        $careList = $api->get_user_chart_list_uks($this->public_user_data['system_user_id'], 1, $pd, $pp, "ASC");
        $history_count = $careList['chart_count'];

        $careList = $api->get_user_chart_list_uks($this->public_user_data['system_user_id'], 2, $pd, $pp, "ASC");
        $ordered_count = $careList['chart_count'];

        $careList = $api->get_user_chart_list_uks($this->public_user_data['system_user_id'], 3, $pd, $pp, "ASC");
        $wordrobe_count = $careList['chart_count'];

        $this->set('history_count', $history_count);
        $this->set('ordered_count', $ordered_count);
        $this->set('wordrobe_count', $wordrobe_count);

		if (!$chartList = $api->get_user_chart_list_uks($this->public_user_data['system_user_id'], $this->page_type, $pd, $pp,$sort)) {
			$this->set("alert", "カルテが見つかりません。");
			return;
		}
		
		if ($chartList['code'] != '200') {
			$this->set("alert", "アイテムが見つかりません。");
			$this->set("chartAllArray", array());
            return;
        }

		if (StaticFunction::is_empty($chartList['chart_list'])) {
			$this->set("alert", "カルテが見つかりません。");
			$this->set("chartAllArray", array());
			return;
		}

		foreach ($chartList['chart_list'] AS $value) {
			$paymentStatus = $value['price'] - $value['balanceamount'];
			$chartAllArray[] = array(
				"chart_id" => $value['chart_id'],
				"chart_link" => "/mypage/" . CONF::read("REST_ORDER_NAME." . $this->page_type) . "/chart.html?chart_id=" . $value['chart_id'],
				"councelingchart_link" => "https://www.kyoto-happy.co.jp/mypage/" . CONF::read("REST_ORDER_NAME." . $this->page_type) . "/pdfdownloader.php?chart_id=" . $value['chart_id']."_カウンセリングカルテ.pdf",
				"seikyusho_link" => "https://www.kyoto-happy.co.jp/mypage/" . CONF::read("REST_ORDER_NAME." . $this->page_type) . "/pdfdownloader.php?chart_id=" . $value['chart_id']."_請求書.pdf",
				"nohinsho_link" => "https://www.kyoto-happy.co.jp/mypage/" . CONF::read("REST_ORDER_NAME." . $this->page_type) . "/merger.php?remotefile1=" . $value['chart_id']."_納品書.pdf&remotefile2=" . $value['chart_id']."_納品書付属書類.pdf",
				"date" => DbDateTime::get_date_type_slash(DbDateTime::get_datetime(DbDateTime::get_timestamp($value['date']))),
				"price" => StaticFunction::count_num_format($value['price']),
				"depositeamount" => StaticFunction::count_num_format($value['balanceamount']),
				"paymentStatus" => $paymentStatus,
				"count" => StaticFunction::count_num_format($value['count'])
			);
		}
		$this->set("chartAllArray", $chartAllArray);

		//ページング出力
		$page = new PAGING();
		$this->set("pageng_html", $page->make_paging($chartList['chart_count']));

		//ブランドリストの取得
		$brand_array = array();
		$brand_result = $api->get_user_brand_search($this->public_user_data['system_user_id']);
		if (!StaticFunction::is_empty($brand_result['brand_list'])) {
			foreach ($brand_result['brand_list'] AS $value) {
				$brand_array[] = $value;
			}
		}
		$this->set("brand_array", $brand_array);

		
	}
	
	// ------------------------ END of Modification by Manjunathgouda ---------------------------------
	/*	 * **********************************
	 * NAME  : items
	 * INPUT : NONE
	 * OUTPUT: NONE
	 * DESC  :
	 * 		過去のケアメンテ「アイテム一覧」より実行されるメソッド
	 * 		検索と共用
	 * NOTICE:
	 * CREATE: 2016.11.7 aoyama
	 * UPDATE: 2016.12.8 aoyama
	 * 		sortをパラメータで指定する方法に切り替え
	 * *********************************** */
	public function items($sort = "ASC") {

		$api = new Rest();

		//一覧用

		$pd = (InputVali::is_num(REQUEST::get_data('pd'))) ? REQUEST::get_data('pd') : 0;
		$pp = (InputVali::is_num(REQUEST::get_data('pp'))) ? REQUEST::get_data('pp') : CONF::read('PAGING.DEFAULT_NUM_PUBLIC');

		// 1：過去のケア～　2：ただいまの～　3：ハッピーワードローブ
        $careList = $api->get_user_chart_list($this->public_user_data['system_user_id'], 1, $pd, $pp, "ASC");
        $history_count = $careList['chart_count'];

        $careList = $api->get_user_chart_list($this->public_user_data['system_user_id'], 2, $pd, $pp, "ASC");
        $ordered_count = $careList['chart_count'];

        $careList = $api->get_user_chart_list($this->public_user_data['system_user_id'], 3, $pd, $pp, "ASC");
		$wordrobe_count = $careList['chart_count'];
		
		$this->set('history_count', $history_count);
        $this->set('ordered_count', $ordered_count);
        $this->set('wordrobe_count', $wordrobe_count);


		$api_array = array();
		$api_array['type'] = $this->page_type;
		$api_array['date_sort'] = $sort;
		$api_array['pd'] = $pd * $pp;
		$api_array['pp'] = $pp;
		$api_array['user_id'] = $this->public_user_data['system_user_id'];

		$api_array['item'] = (InputVali::is_num(REQUEST::get_data('item'))) ? REQUEST::get_data('item') : "";
		$api_array['item2'] = (InputVali::is_num(REQUEST::get_data('item2'))) ? REQUEST::get_data('item2') : "";
		$api_array['select'] = (!StaticFunction::is_empty(REQUEST::get_data('select'))) ? REQUEST::get_data('select') : "";
		$api_array['color'] = (InputVali::is_num(REQUEST::get_data('color'))) ? REQUEST::get_data('color') : "";
		$api_array['color2'] = (InputVali::is_num(REQUEST::get_data('color2'))) ? REQUEST::get_data('color2') : "";
		$api_array['fyy'] = (InputVali::is_num(REQUEST::get_data('year'))) ? REQUEST::get_data('year') : "";
		$api_array['fmm'] = (InputVali::is_num(REQUEST::get_data('month'))) ? REQUEST::get_data('month') : "";
		$api_array['fdd'] = (InputVali::is_num(REQUEST::get_data('day'))) ? REQUEST::get_data('day') : "";
		$api_array['tyy'] = (InputVali::is_num(REQUEST::get_data('year_b'))) ? REQUEST::get_data('year_b') : "";
		$api_array['tmm'] = (InputVali::is_num(REQUEST::get_data('month_b'))) ? REQUEST::get_data('month_b') : "";
		$api_array['tdd'] = (InputVali::is_num(REQUEST::get_data('day_b'))) ? REQUEST::get_data('day_b') : "";

		if (!$itemList = $api->get_chart_item_list($api_array)) {
			$this->set("alert", "アイテムが見つかりません。");
			return;
		}

		if ($itemList['code'] != '200') {
			$this->set("alert", "アイテムが見つかりません。");
			$this->set("itemAllArray", array());
            return;
        }

		if (StaticFunction::is_empty($itemList['item_list'])) {
			//全件数をviewへ
			$this->set("result_count", 0);
			return;
		}

		$itemAllArray = array();
		foreach ($itemList['item_list'] AS $value) {

			$itemAllArray[] = array(
				"thumb_url" => $this->external_target . "/netkuroku/images/" . $value['item_id'] . ".jpg&type=chart",
				"item_id" => StaticFunction::format_item_id($value['item_id']),
				"brand_name" => $value['brand_name'],
				"item_name" => $value['item_name'],
				"medkaterm" => $value['medkaterm'],
				"item_link" => "/mypage/" . CONF::read("REST_ORDER_NAME." . $this->page_type) . "/detail.html?chart_id=" . $value['chart_id'] . "&item_id=" . $value['item_id'],
				"date" => DbDateTime::get_date_type_slash(DbDateTime::get_datetime(DbDateTime::get_timestamp($value['reportscheduleddate']))),
				"status_text" => $value['status_text']
			);
		}
		$this->set("itemAllArray", $itemAllArray);

		//全件数をviewへ
		$this->set("result_count", StaticFunction::count_num_format($itemList['item_count']));

		//ページング出力
		$page = new PAGING();
		$this->set("pageng_html", $page->make_paging($itemList['item_count']));

		//ブランドリストの取得
		$brand_array = array();
		$brand_result = $api->get_user_brand_search($this->public_user_data['system_user_id']);
		if (!StaticFunction::is_empty($brand_result['brand_list'])) {
			foreach ($brand_result['brand_list'] AS $value) {
				$brand_array[] = $value;
			}
		}
		$this->set("brand_array", $brand_array);
	}

	/*	 * **********************************
	 * NAME  : chart
	 * INPUT : NONE
	 * OUTPUT: NONE
	 * DESC  :
	 *  過去のケアメンテ「カルテ明細」より実行されるメソッド
	 * NOTICE:
	 * CREATE: 2016.10.25 aoyama
	 * UPDATE: 2016.12.12 aoyama
	 *		カルテの並べ替えは標準で古い順
	 * *********************************** */
	public function chart($sort = "ASC") {

		$api = new Rest();

		// 1：過去のケア～　2：ただいまの～　3：ハッピーワードローブ
        $pd = (InputVali::is_num(REQUEST::get_data('pd'))) ? REQUEST::get_data('pd') : 0;
        $pp = (InputVali::is_num(REQUEST::get_data('pp'))) ? REQUEST::get_data('pp') : CONF::read('PAGING.DEFAULT_NUM_PUBLIC');
        
        $careList = $api->get_user_chart_list($this->public_user_data['system_user_id'], 1, $pd, $pp, "ASC");
        $history_count = $careList['chart_count'];

        $careList = $api->get_user_chart_list($this->public_user_data['system_user_id'], 2, $pd, $pp, "ASC");
        $ordered_count = $careList['chart_count'];

        $careList = $api->get_user_chart_list($this->public_user_data['system_user_id'], 3, $pd, $pp, "ASC");
        $wordrobe_count = $careList['chart_count'];

        $this->set('history_count', $history_count);
        $this->set('ordered_count', $ordered_count);
        $this->set('wordrobe_count', $wordrobe_count);

		//一覧用
		$api_array = array();
		$api_array['type'] = $this->page_type;
		$api_array['date_sort'] = $sort;
		$api_array['pd'] = (InputVali::is_num(REQUEST::get_data('pd'))) ? (REQUEST::get_data('pd')*CONF::read('PAGING.DEFAULT_NUM_PUBLIC')) : 0;
		$api_array['pp'] = (InputVali::is_num(REQUEST::get_data('pp'))) ? REQUEST::get_data('pp') : CONF::read('PAGING.DEFAULT_NUM_PUBLIC');
		$api_array['user_id'] = $this->public_user_data['system_user_id'];
		$api_array['chart_id'] = (InputVali::is_num(REQUEST::get_data('chart_id'))) ? REQUEST::get_data('chart_id') : "";


		if (!$itemList = $api->get_chart_item_list($api_array)) {
			$this->set("alert", "カルテが見つかりません。");
			return;
		}

		if (StaticFunction::is_empty($itemList['item_list'])) {
			$this->set("alert", "カルテが見つかりません。");
			return;
		}

		//カルテ情報のview用セット
		$this->set("chart_id", REQUEST::get_data("chart_id"));
		$this->set("counseling_date", $itemList['counselingdate']);
		$this->set("total_price", StaticFunction::count_num_format($itemList['total_price']));
		$this->set("item_count", StaticFunction::count_num_format($itemList['item_count']));

		foreach ($itemList['item_list'] AS $value) {

			$itemAllArray[] = array(
				"thumb_url" => $this->external_target . "/netkuroku/images/" . $value['item_id'] . ".jpg",
				"item_id" => StaticFunction::format_item_id($value['item_id']),
				"brand_name" => $value['brand_name'],
				"item_name" => $value['item_name'],
				"item_link" => "/mypage/" . CONF::read("REST_ORDER_NAME." . $this->page_type) . "/detail.html?item_id=" . $value['item_id'] . "&chart_id=" . REQUEST::get_data("chart_id"),
				"date" => DbDateTime::get_date_type_slash(DbDateTime::get_datetime(DbDateTime::get_timestamp($value['reportscheduleddate']))),
				"status_text" => $value['status_text']
			);
		}
		$this->set("itemAllArray", $itemAllArray);

		//ページング出力
		$page = new PAGING();
		$this->set("pageng_html", $page->make_paging($itemList['item_count']));		
	}

	/*	 * **********************************
	 * NAME  : detail
	 * INPUT : NONE
	 * OUTPUT: NONE
	 * DESC  :
	 *  過去のケアメンテ「アイテム明細」より実行されるメソッド
	 * NOTICE:
	 * CREATE: 2016.10.25 aoyama
	 * UPDATE: 2016.11.14 aoyama
	 * 		コメント編集機能の追加
	 * *********************************** */
	public function detail() {

		$api = new Rest();

		// 1：過去のケア～　2：ただいまの～　3：ハッピーワードローブ
        $pd = (InputVali::is_num(REQUEST::get_data('pd'))) ? REQUEST::get_data('pd') : 0;
        $pp = (InputVali::is_num(REQUEST::get_data('pp'))) ? REQUEST::get_data('pp') : CONF::read('PAGING.DEFAULT_NUM_PUBLIC');
        
        $careList = $api->get_user_chart_list($this->public_user_data['system_user_id'], 1, $pd, $pp, "ASC");
        $history_count = $careList['chart_count'];

        $careList = $api->get_user_chart_list($this->public_user_data['system_user_id'], 2, $pd, $pp, "ASC");
        $ordered_count = $careList['chart_count'];

        $careList = $api->get_user_chart_list($this->public_user_data['system_user_id'], 3, $pd, $pp, "ASC");
        $wordrobe_count = $careList['chart_count'];

        $this->set('history_count', $history_count);
        $this->set('ordered_count', $ordered_count);
        $this->set('wordrobe_count', $wordrobe_count);

		if (!$itemDetail = $api->get_item_detail(REQUEST::get_data("item_id"), REQUEST::get_data("chart_id"), $this->public_user_data['system_user_id'])) {
			$this->set("alert", "カルテが見つかりません。");
			return;
		}
		if ($itemDetail['code'] != "200") {
			$this->set("alert", $itemDetail['message']);
			$this->redirect("/mypage/history/");
			return;
		}

		/*
		 * コメント編集（2016.11.28 aoyama）
		 */
		if (InputVali::is_comment_item(REQUEST::post_data('comment')) && StaticFunction::check_token(REQUEST::post_data('token'))) {

			$param_array = array(
				"chart_id" => REQUEST::get_data("chart_id"),
				"item_id" => $itemDetail["item"]["item_id"],
				"user_id" => $this->public_user_data['system_user_id'],
				"comment" => REQUEST::post_data('comment')
			);

			if (!$api->post_chart_item_comment($param_array)) {
				LOGS_ERR("電子カルテのアイテムコメントの変更に失敗しました。：" . REQUEST::post_data('comment'));
				$error_array[] = array('target' => 'comment', "message" => "レビュー投稿に失敗しました。");
				$this->set('error_array', $error_array);
			}

			//アイテム情報の再取得
			if (!$itemDetail = $api->get_item_detail(REQUEST::get_data("item_id"), REQUEST::get_data("chart_id"), $this->public_user_data['system_user_id'])) {
				$this->set("alert", "カルテが見つかりません。");
				return;
			}
		}

		//viewに渡す個別情報をセット
		$this->set("chart_id", REQUEST::get_data("chart_id"));
		$this->set("item_detail", $itemDetail["item"]);
		$this->set("counseling_date", DbDateTime::get_date_type_slash(DbDateTime::get_datetime(DbDateTime::get_timestamp($itemDetail["item"]["counselingdate"]))));
		$this->set("report_scheduled_date", DbDateTime::get_date_type_slash(DbDateTime::get_datetime(DbDateTime::get_timestamp($itemDetail["item"]["reportscheduleddate"]))));
//		$this->set("price_format", StaticFunction::count_num_format($itemDetail["item"]["price"]));

		$this->set("item_id", StaticFunction::format_item_id($itemDetail["item"]["item_id"]));

		//一覧画像（2016.11.14 aoyama）
		$thingimages_array = array();
		if (!StaticFunction::is_empty($itemDetail["item"]["thingimages"])) {
			foreach ($itemDetail["item"]["thingimages"] AS $img_val) {
				$thingimages_array[] = CONF::read("EXTERNAL_IMAGE.TARGET_SURL") . $img_val;
			}
		}
		$this->set("thingimages", $thingimages_array);

		//「お預かり時の状態」配列
		$conditionArray = array();
		if (!StaticFunction::is_empty($itemDetail['item']['chartdetailspresentcondition'])) {
			foreach ($itemDetail['item']['chartdetailspresentcondition'] AS $condition) {
				$conditionArray[] = $condition['text'];
			}
		}
		$this->set("conditionArray", $conditionArray);

		//「起こり得る状態」配列
		$damageArray = array();
		if (!StaticFunction::is_empty($itemDetail['item']['chartdetailsdamage'])) {
			foreach ($itemDetail['item']['chartdetailsdamage'] AS $damage) {
				$damageArray[] = $damage['text'];
			}
		}
		$this->set("damageArray", $damageArray);

		//「確認事項」配列
		$finishArray = array();
		if (!StaticFunction::is_empty($itemDetail['item']['chartdetailsfinish'])) {
			foreach ($itemDetail['item']['chartdetailsfinish'] AS $finish) {
				$finishArray[] = $finish['text'];
			}
		}
		$this->set("finishArray", $finishArray);

		//「メンテナンス」配列
		$maintheArray = array();
		$mainthe_price = 0;
		if (!StaticFunction::is_empty($itemDetail['item']['chartdetailsmaintenance'])) {
			foreach ($itemDetail['item']['chartdetailsmaintenance'] AS $mainthe) {
				$maintheArray[] = array(
					"col1" => $mainthe['maintenancename'],
					"col2" => StaticFunction::count_num_format($mainthe['maintenanceunitprice']),
					"col3" => $mainthe['workccompletionflg'],
					"col4" => $mainthe['riyuu']
				);
				$mainthe_price += (int) $mainthe['maintenanceunitprice'];
			}
		}
		$this->set("maintheArray", $maintheArray);
		$this->set("mainthe_price", StaticFunction::count_num_format($mainthe_price));

		//画像用

		$image_base = "/mypage/chart_image.html?mode=" . $itemDetail['item']['imagecode'];

		$this->set("image_1_url", $image_base . "&small=" . $itemDetail['item']['dirtscreendetailsfront'] . "&large=" . $itemDetail['item']['dirtscreenexpansionfront']);
		$this->set("image_2_url", $image_base . "&small=" . $itemDetail['item']['dirtscreendetailsafter'] . "&large=" . $itemDetail['item']['dirtscreenexpansionafter']);
		$this->set("image_3_url", $image_base . "&small=" . $itemDetail['item']['comprehensioncheckscreendetailsfront'] . "&large=" . $itemDetail['item']['comprehensioncheckscreenexpansionfront']);
		$this->set("image_4_url", $image_base . "&small=" . $itemDetail['item']['comprehensioncheckscreendetailsafter'] . "&large=" . $itemDetail['item']['comprehensioncheckscreenexpansionafter']);
	}

	/*	 * **********************************
	 * NAME  : wardrobe_index
	 * INPUT : NONE
	 * OUTPUT: NONE
	 * DESC  :
	 * 		ワードローブ用アイテムを表示するメソッド
	 * NOTICE:
	 * CREATE: 2016.11.7 aoyama
	 * *********************************** */
	public function wardrobe_index() {
        LOGS_ERR("wardrobe_index::start");
        LOGS_ERR(SESSION::read($this->sGroup . '.error_array'));

		//通常表示
		$api = new Rest();

		// 1：過去のケア～　2：ただいまの～　3：ハッピーワードローブ
        $pd = (InputVali::is_num(REQUEST::get_data('pd'))) ? REQUEST::get_data('pd') : 0;
        $pp = (InputVali::is_num(REQUEST::get_data('pp'))) ? REQUEST::get_data('pp') : CONF::read('PAGING.DEFAULT_NUM_PUBLIC');
        
        $careList = $api->get_user_chart_list($this->public_user_data['system_user_id'], 1, $pd, $pp, "ASC");
        $history_count = $careList['chart_count'];

        $careList = $api->get_user_chart_list($this->public_user_data['system_user_id'], 2, $pd, $pp, "ASC");
        $ordered_count = $careList['chart_count'];

        $careList = $api->get_user_chart_list($this->public_user_data['system_user_id'], 3, $pd, $pp, "ASC");
        $wordrobe_count = $careList['chart_count'];

        $this->set('history_count', $history_count);
        $this->set('ordered_count', $ordered_count);
        $this->set('wordrobe_count', $wordrobe_count);

		//ユーザー情報をviewにセット
		$this->set("user_name", StaticFunction::marge_name($this->public_user_data['name1'], $this->public_user_data['name2']));
		$this->set("tel", $this->public_user_data['tel']);
		$this->set("address", "〒" . $this->public_user_data['zip'] . " " . $this->public_user_data['state'] . $this->public_user_data['addr1'] . $this->public_user_data['addr2'] . $this->public_user_data['addr3']);

		//form用に情報をセット
		$telSplit = explode("-", SESSION::read(CONF::read('LOGIN_CATEGORY.PUBLIC') . '.tel'));

		$this->set("name1", SESSION::read(CONF::read('LOGIN_CATEGORY.PUBLIC') . '.name1'));
		$this->set("name2", SESSION::read(CONF::read('LOGIN_CATEGORY.PUBLIC') . '.name2'));
		$this->set("email", SESSION::read(CONF::read('LOGIN_CATEGORY.PUBLIC') . '.email'));
		$this->set("zip", SESSION::read(CONF::read('LOGIN_CATEGORY.PUBLIC') . '.zip'));
		$this->set("state", SESSION::read(CONF::read('LOGIN_CATEGORY.PUBLIC') . '.state'));
		$this->set("addr1", SESSION::read(CONF::read('LOGIN_CATEGORY.PUBLIC') . '.addr1'));
		$this->set("addr2", SESSION::read(CONF::read('LOGIN_CATEGORY.PUBLIC') . '.addr2'));
		$this->set("addr3", SESSION::read(CONF::read('LOGIN_CATEGORY.PUBLIC') . '.addr3'));
		$this->set("telephone", StaticFunction::convert_zen_to_han_num($telSplit[0]));
		$this->set("telephone2", StaticFunction::convert_zen_to_han_num($telSplit[1]));
		$this->set("telephone3", StaticFunction::convert_zen_to_han_num($telSplit[2]));

		//配達希望日は明日以降をセット
		$date_src = DbDateTime::get_date_type_slash(DbDateTime::get_datetime_change(DbDateTime::get_cur_datetime(), Conf::read("MASTER_SHOP.DELIVER_LATE")));
		$date = explode("/", $date_src);

		$this->set("year_c", $date[0]);
		$this->set("month_c", $date[1]);
		$this->set("day_c", $date[2]);

		//一覧用
		$api_array = array();
		$api_array['type'] = $this->page_type;
		$api_array['pd'] = (InputVali::is_num(REQUEST::get_data('pd'))) ? REQUEST::get_data('pd') : 0;
		$api_array['pp'] = (InputVali::is_num(REQUEST::get_data('pp'))) ? REQUEST::get_data('pp') : CONF::read('PAGING.DEFAULT_NUM_PUBLIC');
		$api_array['user_id'] = $this->public_user_data['system_user_id'];
		$api_array['chart_id'] = (InputVali::is_num(REQUEST::get_data('chart_id'))) ? REQUEST::get_data('chart_id') : "";

		if (!$itemList = $api->get_chart_item_list($api_array)) {
			$this->set("error_array", array(array('message' => "アイテムが取得できません。")));
			$this->set("itemAllArray", array());
//			$this->set("alert", "アイテムが見つかりません。");
			return;
		}

		if ($itemList['code'] != '200') {
			$this->set("alert", "アイテムが見つかりません。");
			$this->set("itemAllArray", array());
            return;
        }

		if (StaticFunction::is_empty($itemList['item_list'])) {
			$this->set("error_array", array(array('message' => "お預かりしているアイテムは現在ございません。")));
			$this->set("itemAllArray", array());
//			$this->set("alert", "アイテムが見つかりません。");
			return;
		}

		$itemAllArray = array();
		foreach ($itemList['item_list'] AS $value) {

			$itemAllArray[] = array(
				"thumb_url" => $this->external_target . "/netkuroku/images/" . $value['item_id'] . ".jpg&type=chart",
				"chart_id" => $value['chart_id'],
				"item_id" => $value['item_id'],
				"format_item_id" => StaticFunction::format_item_id($value['item_id']),
				"brand_name" => $value['brand_name'],
				"item_name" => $value['item_name'],
				"medkaterm" => DbDateTime::get_date_type_slash(DbDateTime::get_datetime(DbDateTime::get_timestamp($value['medkaterm']))), // 保管期限
				"item_link" => "/mypage/" . CONF::read("REST_ORDER_NAME." . $this->page_type) . "/detail.html?chart_id=" . $value['chart_id'] . "&item_id=" . $value['item_id'],
				"date" => DbDateTime::get_date_type_slash(DbDateTime::get_datetime(DbDateTime::get_timestamp($value['reportscheduleddate']))), // 変更後のお届け日
				"status_text" => $value['status_text']
			);
		}
		$this->set("itemAllArray", $itemAllArray);

		//全件数をviewへ
		$this->set("result_count", StaticFunction::count_num_format($itemList['item_count']));

		//ページング出力
		$page = new PAGING();
		$this->set("pageng_html", $page->make_paging($itemList['item_count']));

		//ブランドリストの取得
		$brand_array = array();
		$brand_result = $api->get_user_brand_search($this->public_user_data['system_user_id']);
		if (!StaticFunction::is_empty($brand_result['brand_list'])) {
			foreach ($brand_result['brand_list'] AS $value) {
				$brand_array[] = $value;
			}
		}
		$this->set("brand_array", $brand_array);

        LOGS_ERR(SESSION::read($this->sGroup . '.error_array'));

		if(!StaticFunction::is_empty(SESSION::read($this->sGroup . '.error_array'))){
			$this->set("error_array", SESSION::read($this->sGroup . '.error_array'));
			SESSION::delete($this->sGroup . '.error_array');
		}
		$this->formReturn();
		//リターンしたのでセッションは消す。
		SESSION::delete($this->sGroup);

	}

	/*	 * **********************************
	 * NAME  : confirm
	 * INPUT : 
	 * OUTPUT: 
	 * DESC  : 
	 *  入力確認画面用
	 *  セッションがあればとりあえず表示する
	 *  ここではバリデーション無し
	 * NOTICE:
	 * CREATE: 2016.11.11 aoyama
	 * *********************************** */
	public function confirm() {

		// POSTデータがある場合、セッションに登録する。
		if (!StaticFunction::is_empty(REQUEST::post_data())) {

			SESSION::write($this->sGroup . '.name1', REQUEST::post_data('name1'));
			SESSION::write($this->sGroup . '.name2', REQUEST::post_data('name2'));
			SESSION::write($this->sGroup . '.zip', StaticFunction::convert_zen_to_han_num(REQUEST::post_data('zip')));
			SESSION::write($this->sGroup . '.state', REQUEST::post_data('state'));
			SESSION::write($this->sGroup . '.addr1', REQUEST::post_data('addr1'));
			SESSION::write($this->sGroup . '.addr2', REQUEST::post_data('addr2'));
			SESSION::write($this->sGroup . '.addr3', REQUEST::post_data('addr3'));
			SESSION::write($this->sGroup . '.telephone', StaticFunction::convert_zen_to_han_num(REQUEST::post_data('telephone')));
			SESSION::write($this->sGroup . '.telephone2', StaticFunction::convert_zen_to_han_num(REQUEST::post_data('telephone2')));
			SESSION::write($this->sGroup . '.telephone3', StaticFunction::convert_zen_to_han_num(REQUEST::post_data('telephone3')));
			SESSION::write($this->sGroup . '.time', REQUEST::post_data('time'));
			SESSION::write($this->sGroup . '.year_c', REQUEST::post_data('year_c'));
			SESSION::write($this->sGroup . '.month_c', REQUEST::post_data('month_c'));
			SESSION::write($this->sGroup . '.day_c', REQUEST::post_data('day_c'));
			SESSION::write($this->sGroup . '.hikitori', REQUEST::post_data('hikitori'));
			SESSION::write($this->sGroup . '.pays', REQUEST::post_data('pays'));
			SESSION::write($this->sGroup . '.chkAll', REQUEST::post_data('chkAll'));

			//選択されたアイテムの情報を配列にセット
			SESSION::write($this->sGroup . '.item_array', $this->selectedItemArray());

			// バリデーション
			$error_array = $this->checkSessionParameter();

            LOGS_ERR($error_array);

			if (!StaticFunction::is_empty($error_array)) {

                LOGS_ERR("StaticFunction::is_empty");

				SESSION::write($this->sGroup . '.error_array', $error_array);

                LOGS_ERR(SESSION::read($this->sGroup . '.error_array'));

				$this->redirect("/mypage/wardrobe/");
			}

			$this->formReturn();
			return;
		}
		
		//POSTのないアクセスなのでindexへリダイレクト
		$this->redirect("/mypage/wardrobe/");
	}

	/*	 * **********************************
	 * NAME  : complete
	 * INPUT : 
	 * OUTPUT: 
	 * DESC  : 
	 *  入力完了画面用
	 *  APIで情報を送信
	 * NOTICE:
	 *  API送信処理あり（セッションバリデーション含む）
	 * CREATE: 2016.10.14 aoyama
	 * *********************************** */
	public function complete() {

		//セッションチェック
		if (StaticFunction::is_empty(SESSION::read($this->sGroup))) {
			$this->redirect("/mypage/wardrobe/");
		}

		// バリデーション
		$error_array = $this->checkSessionParameter();
		if (!StaticFunction::is_empty($error_array)) {
			SESSION::write($this->sGroup . '.error_array', $error_array);
			$this->redirect("/mypage/wardrobe/");
		}

		/*
		 * API接続
		 * API完成（2016.11.28 aoyama）
		 */

		$api = new Rest();

		// 郵便番号を分割
		$zip_array = StaticFunction::zip_to_array(SESSION::read($this->sGroup . '.zip'));

		//アイテムを配列に
		foreach (SESSION::read($this->sGroup . '.item_array') AS $item_value) {
			$item_array[] = $item_value['item_id'];
		}

		// 配列にPOSTデータを格納
		
		$address2 = (!StaticFunction::is_empty(SESSION::read($this->sGroup . '.addr2'))) ? SESSION::read($this->sGroup . '.addr2') : "　";
		$address3 = (!StaticFunction::is_empty(SESSION::read($this->sGroup . '.addr3'))) ? SESSION::read($this->sGroup . '.addr3') : "　";
		
		$param_array = array(
			"user_id" => $this->public_user_data['system_user_id'],
			"item_id" => $item_array, // 配列で渡す。
			"zip1" => $zip_array[0],
			"zip2" => $zip_array[1],
			"allprefectures" => SESSION::read($this->sGroup . '.state'),
			"address1" => SESSION::read($this->sGroup . '.addr1'),
			"address2" => $address2,
			"address3" => $address3,
			"tel1" => SESSION::read($this->sGroup . '.telephone'),
			"tel2" => SESSION::read($this->sGroup . '.telephone2'),
			"tel3" => SESSION::read($this->sGroup . '.telephone3'),
			"named" => StaticFunction::marge_name(SESSION::read($this->sGroup . '.name1'), SESSION::read($this->sGroup . '.name2')),
			"nowdate1" => SESSION::read($this->sGroup . '.year_c'),
			"nowdate2" => StaticFunction::format_zero_fill(SESSION::read($this->sGroup . '.month_c'), 2),
			"nowdate3" => StaticFunction::format_zero_fill(SESSION::read($this->sGroup . '.day_c'), 2),
			"times" => SESSION::read($this->sGroup . '.time'),
			"hikitori" => SESSION::read($this->sGroup . '.hikitori'),
			"pays" => SESSION::read($this->sGroup . '.pays')
		);
		//APIへのPOSTレスポンスを格納
		$result = $api->order_delivery_wardrobe($param_array);

		// API通信エラー
		if (!$result) {
			LOGS_ERR("ワードローブ配送オーダーの失敗：API");
			$error_array[] = array("message" => "ワードローブ配送オーダーの登録通信に失敗しました。<br>お手数をおかけしますが時間をおいて再度登録してください。");
			$this->set('error_array', $error_array);
			return;
		}

		// APIレスポンスが異常コードの時はviewにメッセージを渡す
		if ($result["code"] != "200") {
			LOGS_ERR("ワードローブ配送オーダーの失敗:コード" . $result["code"]);
			$error_array[] = array("message" => $result["message"]);
			$this->set('error_array', $error_array);
			return;
		}

		//オーダー完了したのでメール送信（お客様控え）
		$mail = new Mail();
		if (!$mail->send_order_wardrobe($this->sGroup, $this->public_user_data['email'])) {
		//if (!$mail->send_order_wardrobe($this->sGroup, 'samurai0929@gmail.com')) {
			LOGS_ERR('*** WORDROBE ORDER MAIL SEND FAILED. ***');
			$error_array[] = array("message" => "ワードローブ申し込みのメール送信エラーが発生しました。");
			$this->set('error_array', $error_array);
			return;
		}

//		$this->redirect("./");
	}

	/*	 * **********************************
	 * NAME:checkSessionParameter
	 * DESC:
	 * 		セッション情報バリデーション
	 * NOTICE:
	 * CREATE: 2016.11.7 aoyama
	 * *********************************** */
	private function checkSessionParameter()
    {

        $error_array = array();

        if (StaticFunction::is_empty(SESSION::read($this->sGroup . '.item_array'))) {
            $error_array[] = array('target' => 'item_order', 'message' => 'アイテムを選択してください');
        }

        if (!InputVali::is_user_name(SESSION::read($this->sGroup . '.name1'))) {
            $error_array[] = array('target' => 'name1', 'message' => 'お名前を入力してください');
        }
        if (!InputVali::is_user_name(SESSION::read($this->sGroup . '.name2'))) {
            $error_array[] = array('target' => 'name2', 'message' => 'お名前を入力してください');
        }

        if (!InputVali::is_zip(SESSION::read($this->sGroup . '.zip'))) {
            $error_array[] = array('target' => 'zip', 'message' => '郵便番号は半角数字を入れてください。');
        }
        if (!InputVali::is_prefecture(SESSION::read($this->sGroup . '.state'))) {
            $error_array[] = array('target' => 'state', 'message' => '都道府県を選択してください。');
        }

        if (!InputVali::is_municipality(SESSION::read($this->sGroup . '.addr1'))) {
            $error_array[] = array('target' => 'addr1', 'message' => '市区郡を入力してください。');
        }
        if (!InputVali::is_municipality(SESSION::read($this->sGroup . '.addr2'))) {
            $error_array[] = array('target' => 'addr2', 'message' => '町村・番地を入力してください。');
        }
        if (!StaticFunction::is_empty(SESSION::read($this->sGroup . '.addr3'))) {
            if (!InputVali::is_municipality(SESSION::read($this->sGroup . '.addr3'))) {
                $error_array[] = array('target' => 'addr3', 'message' => 'ビル・マンション名を入力してください。');
            }
        }
        if (!InputVali::is_num(SESSION::read($this->sGroup . '.telephone'), true, 1, 5) ||
            !InputVali::is_num(SESSION::read($this->sGroup . '.telephone2'), true, 1, 5) ||
            !InputVali::is_num(SESSION::read($this->sGroup . '.telephone3'), true, 1, 5)) {
            $error_array[] = array('target' => 'tel', 'message' => '電話番号はハイフン無しの半角文字で入力して下さい。');
        }

        /* お届け希望 */
        if (!InputVali::is_pichup_date(SESSION::read($this->sGroup . '.year_c'),
            SESSION::read($this->sGroup . '.month_c'), SESSION::read($this->sGroup . '.day_c'))) {
            $error_array[] = array('target' => 'tel', 'message' => 'お届け希望日は一週間後以降の日時を指定してください。');
        }

        //お届け時間指定
        if (!InputVali::is_array_value(SESSION::read($this->sGroup . '.time'), CONF::read('SHIPPING_TIMEZONE'))) {
            $error_array[] = array('target' => 'time', 'message' => 'お届け時間指定を選択してください。');
        }

        //同時引取り
        if (!InputVali::is_array_value(SESSION::read($this->sGroup . '.hikitori'), CONF::read('ORDER_PICKUP'))) {
            $error_array[] = array('target' => 'hikitori', 'message' => '同時引取りを選択してください。');
        }

        //お支払い方法
        $item_array = SESSION::read($this->sGroup . '.item_array');
        if (!InputVali::is_pickup_free(
        	$item_array,
			SESSION::read($this->sGroup . '.year_c'),
			SESSION::read($this->sGroup . '.month_c'),
			SESSION::read($this->sGroup . '.day_c'))) {
			if (!InputVali::is_array_value(SESSION::read($this->sGroup . '.pays'), CONF::read('PAY_METHOD'))) {
				$error_array[] = array('target' => 'pays', 'message' => 'お支払い方法を選択してください。');
			}
		}


		return $error_array;
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

	/*	 * **********************************
	 * NAME:selectedItemArray
	 * DESC:
	 *  セッション情報をフォームに渡すためにセットする機能
	 * NOTICE:
	 * 		一覧、メール送信用に成形されたアイテム情報配列を返す
	 * CREATE: 2016.11.18 aoyama
	 * UPDATE: 2017.10.30 aoyama
	 * *********************************** */
	private function selectedItemArray()
    {

        $api = new Rest();

        $all = false;

        $ret_array = array();
        $format_post_items = array();

        //一覧用を流用して
        $api_array = array();
        $api_array['type'] = $this->page_type;
        $api_array['pd'] = 0;
        $api_array['pp'] = 99999;
        $api_array['user_id'] = $this->public_user_data['system_user_id'];
        $api_array['chart_id'] = "";

        if (!$itemList = $api->get_chart_item_list($api_array)) {
            // 無ければ空配列のまま返す
            return $ret_array;
        }

        if (StaticFunction::is_empty($itemList['item_list'])) {
            // 登録が1件もない場合もから配列のまま返す
            return $ret_array;
        }

        //全アイテムが選択されている場合
        if (SESSION::read($this->sGroup . '.chkAll') == "all") {
            $all = true;
        }

        $post_items = REQUEST::post_data('item_order');
        if (!StaticFunction::is_empties($post_items)) {
			foreach ($post_items AS $value) {
				$format_item = StaticFunction::chart_item_to_array($value);
				$format_post_items[] = $format_item['item_id'];
			}
		}

		foreach ($itemList['item_list'] AS $value) {
            $item_detail = $api->get_item_detail($value['item_id'], $value['chart_id'], $this->public_user_data['system_user_id']);

			if ($item_detail['code'] === '200' && (in_array($value['item_id'],$format_post_items,true) || $all)) {
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

}

?>
