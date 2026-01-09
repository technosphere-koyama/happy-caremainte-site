<?php

/* * **********************************
 * NAME:DbDateTime
 * DESC:
 *  DBの日時関係カラムに使用する日時値を作るクラス
 * NOTICE:
 *  MySQLのDATE型、DATETIME型では、NULLを入れると
 *  「0000-00-00 00:00:00」となってしまい、検索時などで
 *  NULLを指定すると結果がおかしくなってしまう
 *  さらに、これらの型は結局文字列となり、検索時には文字列検索となり
 *  処理が重くなる
 *  そこで、日時関係は全て UNSIGNED BIG INTにして
 *  強制14桁の数字として取り扱うことにする
 * 
 *  また、日にちであろうが、日時であろうが、
 *  共通で時間迄含むこととする
 *  なので、日にちだけセットする場合でも時・分・秒を000000で
 *  セットすることとする
 * 
 * --------------------------------------------------------
 *  DBに日時をセットする場合、検索に使用する場合でも
 *  かならず当該staticメソッドを通すことを制約する
 * --------------------------------------------------------
 * 
 * CREATE: 2015.10.21 hesaka
 * *********************************** */
class DbDateTime {

	/* * **********************************
	 * NAME  : get_cur_datetime
	 * INPUT : NONE
	 * OUTPUT: string / 日時(14桁)
	 * DESC  :
	 *  現在日時を取得
	 * NOTICE:
	 *  DBの日時用カラム用に、14桁で返す
	 * CREATE: 2015.10.21 hesaka
	 * *********************************** */
	public static function get_cur_datetime() {
		return date("YmdHis");
	}

	/* * **********************************
	 * NAME  : get_cur_year
	 * INPUT : NONE
	 * OUTPUT: string / 日時(14桁)
	 * DESC  :
	 *  現在年を取得
	 * NOTICE:
	 *  DBの日時用カラム用に、14桁で返す
	 * CREATE: 2015.10.21 hesaka
	 * *********************************** */
	public static function get_cur_year() {
		return date("Y") . '0000000000';
	}

	/* * **********************************
	 * NAME  : get_cur_month
	 * INPUT : NONE
	 * OUTPUT: string / 日時(14桁)
	 * DESC  :
	 *  現在月を取得
	 * NOTICE:
	 *  DBの日時用カラム用に、14桁で返す
	 * CREATE: 2015.10.21 hesaka
	 * *********************************** */
	public static function get_cur_month() {
		return date("Ym") . '00000000';
	}

	/* * **********************************
	 * NAME  : get_cur_date
	 * INPUT : NONE
	 * OUTPUT: string / 日時(14桁)
	 * DESC  :
	 *  現在日を取得
	 * NOTICE:
	 *  DBの日時用カラム用に、14桁で返す
	 * CREATE: 2015.10.21 hesaka
	 * *********************************** */
	public static function get_cur_date() {
		return date("Ymd") . '000000';
	}

	/* * **********************************
	 * NAME  : get_cur_hour
	 * INPUT : NONE
	 * OUTPUT: string / 日時(14桁)
	 * DESC  :
	 *  現在時を取得
	 * NOTICE:
	 *  DBの日時用カラム用に、14桁で返す
	 * CREATE: 2015.10.21 hesaka
	 * *********************************** */
	public static function get_cur_hour() {
		return date("YmdH") . '0000';
	}

	/* * **********************************
	 * NAME  : get_cur_minute
	 * INPUT : NONE
	 * OUTPUT: string / 日時(14桁)
	 * DESC  :
	 *  現在分を取得
	 * NOTICE:
	 *  DBの日時用カラム用に、14桁で返す
	 * CREATE: 2015.10.21 hesaka
	 * *********************************** */
	public static function get_cur_minute() {
		return date("YmdHi") . '00';
	}

	/* * **********************************
	 * NAME  : is_today
	 * INPUT : datetime / string / 日時
	 * OUTPUT: true / 本日
	 *         false / 本日ではない
	 * DESC  :
	 *  指定日時が本日かどうか判定する
	 * NOTICE:
	 *  DBの日時用カラム用に、14桁で返す
	 * CREATE: 2015.12.19 hesaka
	 * *********************************** */
	public static function is_today($datetime) {

		//パラメータチェック
		if (StaticFunction::is_empty($datetime)) {
			return false;
		}

		//本日(0時)を取得
		$today = self::get_cur_date();
		//パラメータからYYYYMMDDを抜き出し、右0埋めする
		//こうすることで、その日の0時を取得することができる
		$fairing = self::fairing_digit_14(self::fairing_digit_8($datetime));

		//等しい場合は当日と判定
		if ($today == $fairing) {
			return true;
		}

		//ここに来たということは本日ではない
		return false;
	}
	
	/* * **********************************
	 * NAME  : is_cur_month
	 * INPUT : datetime / string / 日時
	 * OUTPUT: true / 当月
	 *         false / 当月ではない
	 * DESC  :
	 *  指定日時が当月かどうか判定する
	 * NOTICE:
	 *  DBの日時用カラム用に、14桁で返す
	 * CREATE: 2015.12.19 hesaka
	 * *********************************** */
	public static function is_cur_month($datetime) {

		//パラメータチェック
		if (StaticFunction::is_empty($datetime)) {
			return false;
		}

		//当月(0日0時)を取得
		$cur_month = self::get_cur_month();
		//パラメータからYYYYMMを抜き出し、右0埋めする
		//こうすることで、その月の0日0時を取得することができる
		$fairing = self::fairing_digit_14(self::fairing_digit_6($datetime));

		//等しい場合は当月と判定
		if ($cur_month == $fairing) {
			return true;
		}

		//ここに来たということは当月ではない
		return false;
	}
	
	/* * **********************************
	 * NAME  : get_datetime_by_part
	 * INPUT : year / integer or string / 年
	 *         month / integer or string / 月
	 *         day / integer or string / 日
	 *         hour / integer or string / 時
	 *         minute / integer or string / 分
	 *         second / integer or string / 秒
	 * OUTPUT: string / 日時(14桁)
	 *         NULL / 失敗した場合
	 * DESC  :
	 *  指定日時を取得
	 * NOTICE:
	 *  指定カラム以外は0をセットする
	 *  年は、指定がなければ現在年をセットする
	 *  DBの日時用カラム用に、14桁で返す
	 * CREATE: 2015.10.21 hesaka
	 * *********************************** */
	public static function get_datetime_by_part($year = NULL, $month = 0, $day = 0, $hour = 0, $minute = 0, $second = 0) {

		//YがNULLなら現在年を
		if (empty($year)) {
			$year = date("Y");
		}

		$datetime = new DateTime();

		//日付系をセット
		if ($datetime->setDate($year, $month, $day) === false) {
			LOGS_ERR('datetime setDate error, year=' . $year . ', month=' . $month . ', day=' . $day);
			LOGS_ERR($datetime->getLastErrors());
			return NULL;
		}

		//時間系をセット
		if ($datetime->setTime($hour, $minute, $second) === false) {
			LOGS_ERR('datetime setTime error, hour=' . $hour . ', minute=' . $minute . ', second=' . $second);
			LOGS_ERR($datetime->getLastErrors());
			return NULL;
		}
		
		return $datetime->format('YmdHis');
	}

	/* * **********************************
	 * NAME  : get_timestamp
	 * INPUT : datetime / string / 日時
	 * OUTPUT:  int / 日時(10桁)
	 * DESC  :
	 *  YYYY-MM-DD HH:ii:ss をUNIXタイムスタンプで返す
	 * NOTICE:
	 * CREATE: 2016.10.25 aoyama
	 * *********************************** */
	public static function get_timestamp($datetime) {
		return strtotime($datetime);
	}

	/* * **********************************
	 * NAME  : get_datetime_by_part
	 * INPUT : datetime / integer or string / 日時
	 * OUTPUT: string / 日時(14桁)
	 *         NULL / 失敗した場合
	 * DESC  :
	 *  指定日時を取得
	 * NOTICE:
	 *  DBの日時用カラム用に、14桁で返す
	 * CREATE: 2015.10.21 hesaka
	 * *********************************** */
	public static function get_datetime($datetime) {
		return date('YmdHis', $datetime);
	}

	/* * **********************************
	 * NAME  : get_datetime_change
	 * INPUT : target_datetime / integer or string / 対象日時
	 *         add / string / 加算・減算情報(strtotime()引数)
	 * OUTPUT: string / 日時(14桁)
	 *         NULL / 失敗した場合
	 * DESC  :
	 *  target_datetimeに指定した日時から、addで指定した分変更した
	 *  DB用の日時を取得
	 *  ※範囲検索用を使用目的とする
	 * NOTICE:
	 *  addに指定する値は、DateTime->modify()に指定できる文字列とする
	 * 
	 *  例
	 * ('-7 seconds');			// 7秒前
	 * ('+1 minutes');			// 1分後
	 * ('-6 hours');				// 6時間前
	 * ('+2 days');				// 2日後
	 * ('-4 months');			// 4ヶ月前
	 * ('+5 years');				// 5年後
	 * ('+1 weeks');				// 1週間後
	 * ('+1 months + 2 days + 3 hours');	// 1ヶ月2日3時間後
	 * ('noon');				// 正午に
	 * ('first day of this months');		// 当月1日
	 * ('last day of this months');		// 当月末尾
	 * ('first day of next months');		// 来月1日
	 * ('first day of last months');		// 先月1日
	 * ('sunday');				// 次の日曜日
	 * ('monday of this week');		// 今週の月曜日
	 * ('third sunday of this months')	// 第三日曜日
	 * 
	 * ---------------------------------------------------------
	 * 範囲検索に使用する場合、「当日中」を検索したい場合などには
	 * 「<=, >=」で含んでしまうと、翌日の0時0分0秒を含んでしまうので
	 * 気をつけること！
	 * ---------------------------------------------------------
	 * 
	 *  DBの日時用カラム用に、14桁で返す
	 * CREATE: 2015.10.21 hesaka
	 * *********************************** */
	public static function get_datetime_change($target_datetime, $add) {

		//引数が指定されていなければNULLを返す
		if (empty($target_datetime) || empty($add)) {
			LOGS_ERR('parameter is empty');
			return NULL;
		}
		
		//文字型にキャスト
		$target_datetime = strval($target_datetime);

		//桁数チェック
		if (mb_strlen($target_datetime) < 14) {
			LOGS_WARN('invalid number of digits = ' . mb_strlen($target_datetime));
			$target_datetime = str_pad($target_datetime, 14, '0', STR_PAD_RIGHT);
		}

		$datetime = new DateTime($target_datetime);
		
		//変更を加える
		if ($datetime->modify($add) === false) {
			//失敗した場合はNULLを返す
			LOGS_ERR('datetime modify error, add string = ' . $add);
			LOGS_ERR($datetime->getLastErrors());
			return NULL;
		}

		return $datetime->format('YmdHis');
	}

	/* * **********************************
	 * NAME  : get_datetime_type_hyphen
	 * INPUT : target_datetime / float or string / 日時
	 * OUTPUT: string / 日時
	 * DESC  :
	 *  指定日時を、ハイフンの表示形式にして返す
	 *  「yyyy-mm-dd hh:mm:ss」
	 * NOTICE:
	 * CREATE: 2015.11.12 hesaka
	 * *********************************** */
	public static function get_datetime_type_hyphen($target_datetime) {

		//文字型にキャスト
		$target_datetime = (string)$target_datetime;

		$ret = '';
		$len = mb_strlen($target_datetime);
		if ($len >= 4) { $ret .= mb_substr($target_datetime, 0, 4); }			//年
		if ($len >= 6) { $ret .= '-' . mb_substr($target_datetime, 4, 2); }		//月
		if ($len >= 8) { $ret .= '-' . mb_substr($target_datetime, 6, 2); }		//日
		if ($len >= 10) { $ret .= ' ' . mb_substr($target_datetime, 8, 2); }		//時
		if ($len >= 12) { $ret .= ':' . mb_substr($target_datetime, 10, 2); }		//分
		if ($len >= 14) { $ret .= ':' . mb_substr($target_datetime, 12, 2); }		//秒

		return $ret;
	}
	
	/* * **********************************
	 * NAME  : get_datetime_type_slash
	 * INPUT : target_datetime / float or string / 日時
	 * OUTPUT: string / 日時
	 * DESC  :
	 *  指定日時を、スラッシュの表示形式にして返す
	 *  「yyyy/mm/dd hh:mm:ss」
	 * NOTICE:
	 * CREATE: 2015.11.12 hesaka
	 * *********************************** */
	public static function get_datetime_type_slash($target_datetime) {
		//文字型にキャスト
		$target_datetime = (string)$target_datetime;

		$ret = '';
		$len = mb_strlen($target_datetime);
		if ($len >= 4) { $ret .= mb_substr($target_datetime, 0, 4); }			//年
		if ($len >= 6) { $ret .= '/' . mb_substr($target_datetime, 4, 2); }		//月
		if ($len >= 8) { $ret .= '/' . mb_substr($target_datetime, 6, 2); }		//日
		if ($len >= 10) { $ret .= ' ' . mb_substr($target_datetime, 8, 2); }		//時
		if ($len >= 12) { $ret .= ':' . mb_substr($target_datetime, 10, 2); }		//分
		if ($len >= 14) { $ret .= ':' . mb_substr($target_datetime, 12, 2); }		//秒

		return $ret;
	}
	/* * **********************************
	 * NAME  : get_date_type_slash
	 * INPUT : target_datetime / float or string / 日時
	 * OUTPUT: string / 日時
	 * DESC  :
	 *  指定日時を、スラッシュの表示形式にして返す
	 *  「yyyy/mm/dd」
	 * NOTICE:
	 * CREATE: 2016.10.17 aoyama
	 * *********************************** */
	public static function get_date_type_slash($target_datetime) {
		//文字型にキャスト
		$target_datetime = (string)$target_datetime;

		$ret = '';
		$len = mb_strlen($target_datetime);
		if ($len >= 4) { $ret .= mb_substr($target_datetime, 0, 4); }			//年
		if ($len >= 6) { $ret .= '/' . mb_substr($target_datetime, 4, 2); }		//月
		if ($len >= 8) { $ret .= '/' . mb_substr($target_datetime, 6, 2); }		//日

		return $ret;
	}	
	/* * **********************************
	 * NAME  : get_datetime_type_dot
	 * INPUT : target_datetime / float or string / 日時
	 * OUTPUT: string / 日時
	 * DESC  :
	 *  指定日時を、ドットの表示形式にして返す
	 *  「yyyy.mm.dd hh:mm:ss」
	 * NOTICE:
	 * CREATE: 2015.11.12 hesaka
	 * *********************************** */
	public static function get_datetime_type_dot($target_datetime) {

		//文字型にキャスト
		$target_datetime = (string)$target_datetime;

		$ret = '';
		$len = mb_strlen($target_datetime);
		if ($len >= 4) { $ret .= mb_substr($target_datetime, 0, 4); }			//年
		if ($len >= 6) { $ret .= '.' . mb_substr($target_datetime, 4, 2); }		//月
		if ($len >= 8) { $ret .= '.' . mb_substr($target_datetime, 6, 2); }		//日
		if ($len >= 10) { $ret .= ' ' . mb_substr($target_datetime, 8, 2); }		//時
		if ($len >= 12) { $ret .= ':' . mb_substr($target_datetime, 10, 2); }		//分
		if ($len >= 14) { $ret .= ':' . mb_substr($target_datetime, 12, 2); }		//秒

		return $ret;
	}
	/* * **********************************
	 * NAME  : get_date_type_dot
	 * INPUT : target_datetime / float or string / 日時
	 * OUTPUT: string / 日
	 * DESC  :
	 *  指定日時を、ドットの表示形式にして返す
	 *  「yyyy.mm.dd」
	 * NOTICE:
	 * CREATE: 2016.10.17 aoyama
	 * *********************************** */
	public static function get_date_type_dot($target_datetime) {

		//文字型にキャスト
		$target_datetime = (string)$target_datetime;

		$ret = '';
		$len = mb_strlen($target_datetime);
		if ($len >= 4) { $ret .= mb_substr($target_datetime, 0, 4); }			//年
		if ($len >= 6) { $ret .= '.' . mb_substr($target_datetime, 4, 2); }		//月
		if ($len >= 8) { $ret .= '.' . mb_substr($target_datetime, 6, 2); }		//日

		return $ret;
	}

	/* * **********************************
	 * NAME  : get_time_colon
	 * INPUT : target_datetime / float or string / 日時
	 * OUTPUT: string / 時間(コロン)
	 * DESC  :
	 *  指定日時から時間だけ抽出し、「：」で割った文字列として返す
	 *  「hh:mm:ss」
	 * NOTICE:
	 * CREATE: 2015.11.23 hesaka
	 * *********************************** */
	public static function get_time_colon($target_datetime) {
		//文字型にキャスト
		$target_datetime = (string)$target_datetime;

		$ret = mb_substr($target_datetime, -6, 2);		//時
		$ret .= ':' . mb_substr($target_datetime, -4, 2); 	//分
		$ret .= ':' . mb_substr($target_datetime, -2, 2); 	//秒
		return $ret;
	}	

	/* * **********************************
	 * NAME  : get_time_colon_digit_4
	 * INPUT : target_datetime / float or string / 日時
	 * OUTPUT: string / 時間(コロン)
	 * DESC  :
	 *  指定日時から時間だけ抽出し、「：」で割った文字列として返す
	 *  「hh:mm」
	 * NOTICE:
	 * CREATE: 2015.11.27 hesaka
	 * *********************************** */
	public static function get_time_colon_digit_4($target_datetime) {
		//文字型にキャスト
		$target_datetime = (string)$target_datetime;

		$ret = mb_substr($target_datetime, -6, 2);		//時
		$ret .= ':' . mb_substr($target_datetime, -4, 2); 	//分
		return $ret;
	}	
	
	/* * **********************************
	 * NAME  : exclusion_char
	 * INPUT : datetime_with_char / string / 文字が入った時間
	 * OUTPUT: string / 日時
	 * DESC  :
	 *  「yyyy/mm/dd hh:mm:ss」
	 *  など、数字以外が入った時間を、数字のみに変換して返す
	 * NOTICE:
	 * CREATE: 2015.11.13 hesaka
	 * *********************************** */
	public static function exclusion_char($datetime_with_char) {
		return mb_ereg_replace('[^0-9]', '', $datetime_with_char);
	}
	
	/* * **********************************
	 * NAME  : fairing_digit_6
	 * INPUT : datetime / string / 日時
	 * OUTPUT: string / 年月まで
	 * DESC  :
	 *  「yyyymm」に整形して返す
	 * NOTICE:
	 *  6桁なければ0埋め(右側)する
	 * CREATE: 2015.12.19 hesaka
	 * *********************************** */
	public static function fairing_digit_6($datetime) {

		//空ならNULLを返す
		if (StaticFunction::is_empty($datetime)) {
			return NULL;
		}
		
		$datetime = (string)$datetime;

		//6桁なければ0埋め(右側)する
		if (mb_strlen($datetime) < 6) {
			return str_pad($datetime, 6, '0', STR_PAD_RIGHT);
		//6桁以上あれば、左から6桁取得する
		} else {
			return mb_substr($datetime, 0, 6);
		}
	}
	
	/* * **********************************
	 * NAME  : fairing_digit_8
	 * INPUT : datetime / string / 日時
	 * OUTPUT: string / 年月日まで
	 * DESC  :
	 *  「yyyymmdd」に整形して返す
	 * NOTICE:
	 *  8桁なければ0埋め(右側)する
	 * CREATE: 2015.11.15 hesaka
	 * UPDATE: 2015.12.07 hesaka 空が渡されたらNULLを返すよう変更
	 * *********************************** */
	public static function fairing_digit_8($datetime) {

		//空ならNULLを返す
		if (StaticFunction::is_empty($datetime)) {
			return NULL;
		}
		
		$datetime = (string)$datetime;

		//8桁なければ0埋め(右側)する
		if (mb_strlen($datetime) < 8) {
			return str_pad($datetime, 8, '0', STR_PAD_RIGHT);
		//8桁以上あれば、左から8桁取得する
		} else {
			return mb_substr($datetime, 0, 8);
		}
	}

	/* * **********************************
	 * NAME  : fairing_digit_12
	 * INPUT : datetime / string / 日時
	 * OUTPUT: string / 日時(分まで)
	 * DESC  :
	 *  「yyyymmddhhmm」に整形して返す
	 * NOTICE:
	 *  12桁なければ0埋め(右側)する
	 * CREATE: 2015.11.13 hesaka
	 * UPDATE: 2015.12.07 hesaka 空が渡されたらNULLを返すよう変更
	 * *********************************** */
	public static function fairing_digit_12($datetime) {

		//空ならNULLを返す
		if (StaticFunction::is_empty($datetime)) {
			return NULL;
		}

		$datetime = (string)$datetime;

		//12桁なければ0埋め(右側)する
		if (mb_strlen($datetime) < 12) {
			return str_pad($datetime, 12, '0', STR_PAD_RIGHT);
		//12桁以上あれば、左から12桁取得する
		} else {
			return mb_substr($datetime, 0, 12);
		}
	}
	
	/* * **********************************
	 * NAME  : fairing_digit_14
	 * INPUT : datetime / string / 日時
	 * OUTPUT: string / 日時(秒まで)
	 * DESC  :
	 *  「yyyymmddhhmmss」に整形して返す
	 * NOTICE:
	 *  14桁なければ0埋め(右側)する
	 * CREATE: 2015.11.13 hesaka
	 * UPDATE: 2015.12.07 hesaka 空が渡されたらNULLを返すよう変更
	 * *********************************** */
	public static function fairing_digit_14($datetime) {

		//空ならNULLを返す
		if (StaticFunction::is_empty($datetime)) {
			return NULL;
		}

		$datetime = (string)$datetime;

		//14桁なければ0埋め(右側)する
		if (mb_strlen($datetime) < 14) {
			return str_pad($datetime, 14, '0', STR_PAD_RIGHT);
		//14桁以上あれば、左から14桁取得する
		} else {
			return mb_substr($datetime, 0, 14);
		}
	}

	/* * **********************************
	 * NAME  : fairing_digit_14
	 * INPUT : datetime / string / 日時
	 * OUTPUT: string / 日時(秒まで)
	 * DESC  :
	 *  「yyyymmddhhmmss」に整形して返す
	 * NOTICE:
	 *  14桁なければ0埋め(右側)する
	 *  秒数は59を入れる。
	 * CREATE: 2015.11.16 sonoda
	 * *********************************** */
	public static function fairing_digit_14_endsec($datetime) {

		return DbDateTime::fairing_digit_12($datetime) . '59';
//		$datetime = (string)$datetime;
//
//		//12桁なければ0埋め(右側)する
//		if (mb_strlen($datetime) < 12) {
//			$datetime = str_pad($datetime, 12, '0', STR_PAD_RIGHT);
//		//12桁以上あれば、左から12桁取得する
//		} else {
//			$datetime = mb_substr($datetime, 0, 12);
//		}

//		return $datetime = $datetime . '59';
//		$datetime = (string)$datetime;

		//14桁なければ0埋め(右側)する
//		if (mb_strlen($datetime) < 14) {
//			return str_pad($datetime, 14, '0', STR_PAD_RIGHT);
//		14桁以上あれば、左から14桁取得する
//		} else {
//			return mb_substr($datetime, 0, 14);
//		}
	}

	/* * **********************************
	 * NAME  : fairing_digit_14_end_date
	 * INPUT : datetime / string / 日時
	 * OUTPUT: string / 日時(秒まで)
	 * DESC  :
	 *  引数に指定された日時の年月日を取得し、
	 *  時分秒にはEND(235959)をセットして返す
	 * NOTICE:
	 * CREATE: 2016.10.05 hesaka
	 * *********************************** */
	public static function fairing_digit_14_end_date($datetime) {
		return DbDateTime::fairing_digit_8($datetime) . '235959';
	}

	/*	 * **********************************
	 * NAME  : datetime_fairing_for_calendar
	 * INPUT : datetime / string / 日時
	 * OUTPUT: string / 日時
	 * DESC  :
	 *  カレンダー用インプットに表示する形(ハイフンなど有りの12桁)に整形する
	 * NOTICE:
	 *  空の場合はNULLを返す
	 * CREATE: 2015.11.13 hesaka
	 * *********************************** */
	public static function fairing_for_calendar($datetime) {
		//空の場合はNULを返す
		if (StaticFunction::is_empty($datetime)) {
			return NULL;
		}
		return self::get_datetime_type_hyphen(
				self::fairing_digit_12($datetime)
			);
	}

	/*	 * **********************************
	 * NAME  : datetime_fairing_for_calendar_digit_8
	 * INPUT : datetime / string / 日時
	 * OUTPUT: string / 日時
	 * DESC  :
	 *  カレンダー用インプットに表示する形(ハイフンなど有りの8桁)に整形する
	 *  年月日を表示する必要があるので。
	 * NOTICE:
	 *  空の場合はNULLを返す
	 * CREATE: 2016.08.29 sonoda
	 * *********************************** */
	public static function fairing_for_calendar_digit_8($datetime) {
		//空の場合はNULを返す
		if (StaticFunction::is_empty($datetime)) {
			return NULL;
		}
		return self::get_datetime_type_hyphen(
				self::fairing_digit_8($datetime)
			);
	}

	/*	 * **********************************
	 * NAME  : datetime_fairing_for_display
	 * INPUT : datetime / string / 日時
	 * OUTPUT: string / 日時
	 * DESC  :
	 *  一覧や、詳細画面に表示する形(スラッシュ有りの12桁)に整形する
	 * NOTICE:
	 *  空の場合はNULLを返す
	 * CREATE: 2015.11.13 hesaka
	 * *********************************** */
	public static function fairing_for_display($datetime) {
		//空の場合はNULを返す
		if (StaticFunction::is_empty($datetime)) {
			return NULL;
		}
		return self::get_datetime_type_hyphen(
				self::fairing_digit_12($datetime)
			);
	}

	/*	 * **********************************
	 * NAME  : datetime_fairing_for_display_slash
	 * INPUT : datetime / string / 日時
	 * OUTPUT: string / 日時
	 * DESC  :
	 *  一覧や、詳細画面に表示する形(スラッシュ有りの12桁)に整形する
	 * NOTICE:
	 *  空の場合はNULLを返す
	 * CREATE: 2016.09.05 sonoda
	 * *********************************** */
	public static function fairing_for_display_slash($datetime) {
		//空の場合はNULを返す
		if (StaticFunction::is_empty($datetime)) {
			return NULL;
		}
		return self::get_datetime_type_slash(
				self::fairing_digit_12($datetime)
			);
	}

	/*	 * **********************************
	 * NAME  : datetime_fairing_for_insert
	 * INPUT : datetime / string / 日時
	 * OUTPUT: string / 日時
	 * DESC  :
	 *  DBにインサート・アップデートできる形(14桁)に整形する
	 * NOTICE:
	 * CREATE: 2015.11.13 hesaka
	 * *********************************** */
	public static function fairing_for_insert($datetime) {
		//空の場合はNULLを返す
		if (StaticFunction::is_empty($datetime)) {
			return NULL;
		}
		return self::fairing_digit_14(
				self::exclusion_char($datetime)
			);
	}

	/*	 * **********************************
	 * NAME  : datetime_fairing_for_insert_endsec
	 * INPUT : datetime / string / 日時
	 * OUTPUT: string / 日時
	 * DESC  :
	 *  DBにインサート・アップデートできる形(14桁)に整形する
	 *  秒数は59を入れる
	 * NOTICE:
	 * CREATE: 2015.11.20 hesaka
	 * *********************************** */
	public static function fairing_for_insert_endsec($datetime) {
		//空の場合はNULLを返す
		if (StaticFunction::is_empty($datetime)) {
			return NULL;
		}
		return self::fairing_digit_14_endsec(
				self::exclusion_char($datetime)
			);
	}
	
	/*	 * **********************************
	 * NAME  : datetime_fairing_for_insert_end_date
	 * INPUT : datetime / string / 日時
	 * OUTPUT: string / 日時
	 * DESC  :
	 *  引数に指定された日時の年月日を取得し、
	 *  時分秒にはEND(235959)をセットして返す
	 * NOTICE:
	 * CREATE: 2016.10.05 hesaka
	 * *********************************** */
	public static function fairing_for_insert_end_date($datetime) {
		//空の場合はNULLを返す
		if (StaticFunction::is_empty($datetime)) {
			return NULL;
		}
		return self::fairing_digit_14_end_date(
			self::exclusion_char($datetime)
		);
	}

}

?>
