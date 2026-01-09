<?php

/* * **********************************
 * NAME:PAGING
 * DESC:
 *  ページング用のモジュール
 *  
 *  ユーザから見たページングの挙動としては以下となる
 *  最初は、どこのリストに行っても初期値の件数で表示される
 *  画面で、表示件数を変更すると、当該セッショングループに
 *  「paging」として値を保存する
 *  pagingのセレクトでは、選択した値がプリセットされる
 *  セッションがクリアされたら初期にの件数に戻る
 *  ※よって、違う画面に行くとデフォルト件数になっている
 *  　これにより、画面毎に設定を変えられるようにする
 *  何ページ目が表示されているかは、URLのGETパラメータで
 *  「p=2」と表示する
 * NOTICE:
 * CREATE: 2015.11.08 hesaka
 * *********************************** */
class PAGING {

	private static $cur_page;
	private static $user_category;
	private static $num_per_page;

	/* * **********************************
	 * NAME  : initialize
	 * INPUT : user_category / string / ユーザの種類を示す文字列
	 *         session_group / string / セッショングループ
	 * OUTPUT: true / 成功
	 *         false / 異常事態
	 * DESC  :
	 * NOTICE:
	 * CREATE: 2015.11.08 hesaka
	 * UPDATE: 2016.07.19 hesaka pp, pに異常な値が指定されたらfalseを返すように変更
	 *                           ※呼び出し元で、false返ってきたらinternal_errorページに飛ぶように調整すること
	 * *********************************** */
	public static function initialize($user_category, $session_group = NULL) {

		self::$user_category = $user_category;

		//GETの「pp」に表示件数がセットされていたらその値をセット
		if (!StaticFunction::is_empty(REQUEST::get_data('pp'))) {

			/*
			 * 20160719
			 * ppに変な文字列を指定されることがある
			 * その場合はエラーとしてfalseを返す
			 * ※正の整数以外はエラーとする
			 * ※コントローラでinternal_errorページに流すようにする
			 */
			if (!ctype_digit(REQUEST::get_data('pp'))) {
				return false;
			}

			self::$num_per_page = REQUEST::get_data('pp');

		//セッションにない場合は、カテゴリから、初期設定を取得
		} else {

			switch (self::$user_category) {
				case CONF::read('PAGING.SYSTEM'):
					self::$num_per_page = CONF::read('PAGING.DEFAULT_NUM_SYSTEM');
					break;
				default:
					self::$num_per_page = CONF::read('PAGING.DEFAULT_NUM_PUBLIC');
					break;
			}
		}

		//GETの「p」に何ページ目かがセットされていたらその値をセット
		if (!StaticFunction::is_empty(REQUEST::get_data('pd'))) {

			/*
			 * 20160719
			 * pに変な文字列を指定されることがある
			 * その場合はエラーとしてfalseを返す
			 * ※正の整数以外はエラーとする
			 * ※コントローラでinternal_errorページに流すようにする
			 */
			if (!ctype_digit(REQUEST::get_data('pd'))) {
				return false;
			}

			self::$cur_page = REQUEST::get_data('pd');

		} else {

			//セットされていなければ初期値1をセット
			self::$cur_page = 1;
		}

		//セッショングループ指定がある場合、セッションにppとpを保存する
		//※これは、一覧から詳細画面に遷移し、戻ってくる際に使用するものである
		if (!StaticFunction::is_empty($session_group)) {
			SESSION::write($session_group . '.cpp', self::$num_per_page);
			SESSION::write($session_group . '.cp', self::$cur_page);
		}

		/*
		 * 20160719
		 * 無事成功した場合はtrueを返す
		 */
		return true;
	}

	/* * **********************************
	 * NAME  : get_limit
	 * INPUT : NONE
	 * OUTPUT: string / クエリに用いるLIMIT文字列
	 * DESC  :
	 * NOTICE:
	 * CREATE: 2015.11.08 hesaka
	 * *********************************** */
	public static function get_limit() {

		//initializeされていない場合は、強制的にPUBLICで初期化する
		if (StaticFunction::is_empty(self::$num_per_page)) {
			self::initialize(CONF::read('PAGING.PUBLIC'));
		}
		
		return 'LIMIT ' . (self::$num_per_page * (self::$cur_page - 1)) .  ', ' . self::$num_per_page;
	}

	/*	 * **********************************
	 * NAME  : is_paging_over
	 * INPUT : total_num / integer / 検索結果総数
	 * OUTPUT: true / 超えている
	 *         false / 超えていない
	 * DESC  :
	 *  self::$cur_pageが、引数に指定される
	 *  total_numから算出する最大ページを超えているか判断する
	 * NOTICE:
	 * CREATE: 2015.11.13 hesaka
	 * *********************************** */
	public static function is_page_over($total_num) {

		//アクセスしようとしているページが最大値を超えている場合はtrueを返す
		if (self::$cur_page > self::get_max_page($total_num)) {
			return true;
		}

		return false;
	}

	/*	 * **********************************
	 * NAME  : is_paging_over
	 * INPUT : total_num / integer / 検索結果総数
	 * OUTPUT: true / 超えている
	 *         false / 超えていない
	 * DESC  :
	 *  self::$cur_pageが、引数に指定される
	 *  total_numから算出する最大ページを超えているか判断する
	 * NOTICE:
	 * CREATE: 2015.11.13 hesaka
	 * *********************************** */
	public static function get_max_request_parameter($total_num) {
		return '?pp=' . self::$num_per_page . '&p=' . self::get_max_page($total_num);
	}
	
	/* * **********************************
	 * NAME  : get_display_data
	 * INPUT : total_num / integer / 検索結果総数
	 * OUTPUT: array / 画面表示に必要なページングデータ
	 *         false / 失敗の場合
	 * DESC  :
	 *  画面に表示するページング用のデータを生成して返す
	 * 
	 * 返す形は以下となる
	 * 例：CONF::read('PAGING.DISPLAY_NUM')が6、self::$num_per_pageが30、
	 *　　 カレントページが9、total_numが355の場合
	 * 
	 * array(
	 *	'pp' => 30,
	 *	'first' => 1,
	 *	'prev' => 8,
	 *	'cur' => 9,
	 *	'next' => 10,
	 *	'last' => 12,
	 *	'get_parameter' => 'get1=aaa&get2=bbb',
	 *	'numbers' => array(
	 *		[0]('number' => 7),
	 *		[1]('number' => 8),
	 *		[2]('number' => 9),
	 *		[3]('number' => 10),
	 *		[4]('number' => 11),
	 *		[5]('number' => 12)
	 *	)
	 * )
	 * 
	 * NOTICE:
	 * CREATE: 2015.11.08 hesaka
	 * *********************************** */
	public static function get_display_data($total_num) {

		if (StaticFunction::is_empty($total_num)) {
			return false;
		}

		//initializeされていない場合は、強制的にPUBLICで初期化する
		if (StaticFunction::is_empty(self::$num_per_page)) {
			self::initialize(CONF::read('PAGING.PUBLIC'));
		}

		//1ページに収まる場合もfalseを返す
		if (intval($total_num / self::$num_per_page) <= 0 || $total_num == self::$num_per_page) {
			return false;
		}
		
		//total_numから、最大ページ数を取得
		$last = self::get_max_page($total_num);

		/*
		 * カレントページが最大値を超えている場合はラストにする
		 * ※最大値を超えている場合は、最後のページもクリックできるように
		 * 　cur_pageはそのままにしておく
		if (self::$cur_page > $last) {
			self::$cur_page = $last;
		}
		 */

		//ブロック数を算出
		$block_num = intval($last / CONF::read('PAGING.DISPLAY_NUM')) + (($last % CONF::read('PAGING.DISPLAY_NUM')) ? (1) : (0));

		//表示すべきページ番号を算出
		for ($cur_block = 1; $cur_block <= $block_num; $cur_block++) {
			if ($cur_block * CONF::read('PAGING.DISPLAY_NUM') >= self::$cur_page) {
				break;
			}
		}
		$numbers = array();
		for ($i = 1; $i <= CONF::read('PAGING.DISPLAY_NUM'); $i++) {
			$number = (CONF::read('PAGING.DISPLAY_NUM') * ($cur_block - 1)) + $i;
			//最大値に届いた場合は終了
			if ($number > $last) {
				break;
			}
			$numbers[] = array('number' => $number);
		}
		
		//現状URLのGETパラメータ(ppとpは抜き)
		$get_param_list = REQUEST::get_data();
		if (isset($get_param_list['p'])) { unset($get_param_list['p']); }
		if (isset($get_param_list['pp'])) { unset($get_param_list['pp']); }
		$get_param = array();
		foreach ($get_param_list as $key => $value) {
			$get_param[] = $key . '=' . $value;
		}
		
		//返す配列を作成
		$ret = array(
			//pp:1ページに表示するコンテンツ数
			'pp' => self::$num_per_page,
			//first:最初のページより後ろの場合は1を。最初のページの場合はNULLをセット
			'first' => ((self::$cur_page > 1) ? (1) : (NULL)),
			//prev:最初のページより後ろの場合はカレント-1を。最初のページの場合はNULLをセット
			'prev' => ((self::$cur_page > 1) ? (self::$cur_page - 1) : (NULL)),
			//cur:
			'cur' => self::$cur_page,
			//next:最後のページより前の場合はカレント＋1を。最後のページの場合はNULLをセット
			'next' => ((self::$cur_page < $last) ? (self::$cur_page + 1) : (NULL)),
			//last:最後のページ番号(total_num / num_per_page + (余りが出たらプラス1))
			'last' => $last,
			//get_parameter:現状URLのGETパラメータ(ppとpは抜き)
			'get_parameter' => implode('&', $get_param),
			//numbers:表示する番号の配列
			//例：array('number' => 2)
			'numbers' => $numbers
		);

		return $ret;
	}

	/*	 * **********************************
	 * NAME  : get_max_page
	 * INPUT : total_num / integer / 検索結果総数
	 * OUTPUT: integer / 最大ページ数
	 * DESC  :
	 *  total_numから、最大ページ数を取得する
	 * NOTICE:
	 * CREATE: 2015.11.13 hesaka
	 * *********************************** */
	private static function get_max_page($total_num) {

		//件数が0件の場合、「1ページ」を返す
		if ($total_num == 0) { 
			return 1;
		}

		return intval($total_num / self::$num_per_page) + (($total_num % self::$num_per_page) ? (1) : (0));
	}
	
	
	/* ページング用機能追加
	 * ( 現在のページ(pd)数, 変数配列, URL, 表示件数, 手前の表示件数, 全ページ数 ) */
	/*	 * **********************************
	 * NAME  : make_paging
	 * INPUT : total_num / integer / 検索結果総数
	 * OUTPUT: integer / 最大ページ数
	 * DESC  :
	 *		pp -> 1ページに表示する件数
	 *		pd -> ～ページ目。0が1ページ目
	 * NOTICE:
	 * CREATE: 2016.10.17 aoyama
	 * *********************************** */

	public function make_paging($total_num) {

		//現状URLのGETパラメータ(ppとpdは抜き)
		$get_param_list = REQUEST::get_data();
		if (isset($get_param_list['pd'])) { unset($get_param_list['pd']); }
		if (isset($get_param_list['pp'])) { unset($get_param_list['pp']); }
		
		$get_query = http_build_query($get_param_list);
		$url = $_SERVER['SCRIPT_NAME']."?".$get_query;
		
		// 1ページの表示件数を設定
		$pp = (InputVali::is_num(REQUEST::get_data('pp')) AND REQUEST::get_data('pp') <= CONF::read('PAGING.DEFAULT_NUM_MAX')) ? REQUEST::get_data('pp') : CONF::read('PAGING.DEFAULT_NUM_PUBLIC');
		
		//全ページ数
		$maxPage = ceil((int)$total_num/$pp);
		
		$pgLeftView = CONF::read('PAGING.DISPLAY_PREV_NUM');
		$pgMaxView = CONF::read('PAGING.DISPLAY_NUM');
		
		//現在のページ初期化
		$nowPage = 0;

		//-------pdがあれば～ページ目を設定-------
		$nowPage = ( preg_match("/^[0-9]{1,}$/", REQUEST::get_data("pd")) ) ? REQUEST::get_data("pd") : 0;

		//----- html生成 -----
		$pagingHtml = '';
		
		/* 全ページ数が1以上で現ページが1以上のときに手前に戻るボタンを設置 */
		if ($maxPage > 1 && $nowPage > 0) {
			$pagingHtml .= '<li><a href="' . $url . '&pd=' . ($nowPage - 1) . '&pp='.$pp.'">&lt;</a></li>';
		}
		
		if ($maxPage <= $pgMaxView) {
			for ($i = 0; $i < $maxPage; $i++) {
				if ($i == $nowPage) {
					$pagingHtml .= '<li><span class="current">' . ($i+1) . '</span></li>';
				} else {
					$pagingHtml .= '<li class="PCpart"><a href="' . $url . '&pd=' . $i . '&pp='.$pp.'">' . ($i+1) . '</a></li>';
				}
			}
		} else {

			$startPage = $nowPage - ($pgLeftView);
			$dotNext = '';
			$dotPrev = '';
			/* ドットページャー */
			if ($nowPage > $pgLeftView) {
				$pagingHtml .= '<li class="PCpart"><a href="' . $url . '&pd=0&pp='.$pp.'">1</a></li>';
				$pagingHtml .= '<li><span class="dots">…</span></li>';
			}

			if ($nowPage <= $pgLeftView) {
				for ($i = 0; $i < $pgMaxView; $i++) {
					if ($i == $nowPage) {
						$pagingHtml .= '<li><span class="current">' . ($i+1) . '</span></li>';
					} else {
						$pagingHtml .= '<li class="PCpart"><a href="' . $url . '&pd=' . $i . '&pp='.$pp.'">' . ($i+1) . '</a></li>';
					}
				}
				$dotNext = $pgMaxView + 1;
			} else if ($nowPage >= $maxPage - $pgLeftView -1) { //23,27,3
				for ($i = $maxPage - $pgMaxView ; $i < $maxPage; $i++) {
					if ($i == $nowPage) {
						$pagingHtml .= '<li><span class="current">' . ($i+1) . '</span></li>';
					} else {
						$pagingHtml .= '<li class="PCpart"><a href="' . $url . '&pd=' . $i . '&pp='.$pp.'">' . ($i+1) . '</a></li>';
					}
				}
				$dotPrev = $maxPage - $pgMaxView;
			} else {
				for ($i = $startPage; $i < $startPage + $pgMaxView; $i++) {
					if ($i == $nowPage) {
						$pagingHtml .= '<li><span class="current">' . ($i+1) . '</span></li>';
					} else {
						$pagingHtml .= '<li class="PCpart"><a href="' . $url . '&pd=' . $i . '&pp='.$pp.'">' . ($i+1) . '</a></li>';
					}
				}
				$dotPrev = $startPage - 1;
				$dotNext = $startPage + $pgMaxView;
			}
			/* ドットページャー */
			if ($maxPage - $nowPage > $pgMaxView - $pgLeftView) {
				$pagingHtml .= '<li><span class="dots">…</span></li>';
				$pagingHtml .= '<li class="PCpart"><a href="' . $url . '&pd='.($maxPage-1).'&pp='.$pp.'">'.$maxPage.'</a></li>';
			}
		}

		/* 全ページ数が1以上で現ページがページ数よりも小さい場合は次へボタンを設置 */
		if ($maxPage > 1 && $maxPage > ($nowPage + 1) ) {
			$pagingHtml .= '<li><a href="' . $url . '&pd=' . ($nowPage + 1) . '&pp='.$pp.'">&gt;</a></li>';
		}
		return $pagingHtml;
	}	
	
}

?>
