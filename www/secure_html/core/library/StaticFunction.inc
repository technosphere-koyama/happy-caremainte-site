<?php

//is_empty()用定義
define("ZERO_EMPTY", 1);
define("ZERO_NOT_EMPTY", 2);

/* * **********************************
 * NAME:StaticFunction
 * DESC:
 *  単発のstaticな関数群
 * NOTICE:
 *  クラスに依存するようなものではなく、
 *  どこからでも呼びたくなる単機能関数を
 *  展開する想定
 * CREATE: 2015.08.27 hesaka
 * *********************************** */
class StaticFunction {

	/*	 * **********************************
	 * NAME  : is_empty
	 * INPUT : data / void / チェック対象
	 *         zero / integer / 0の取り扱い(define ZERO_...定義)
	 * OUTPUT: true / 空ということ
	 *         false / 空ではないということ
	 * DESC  :
	 *  empty()のラッパー
	 * 
	 *  is_empty()動作定義
	 *  ------------------------------------------------------------
	 *  名称         |  具体例  | 判定(ZERO_EMPTY) | 判定(ZERO_NOT_EMPTY)
	 *  ------------------------------------------------------------
	 *  数値のゼロ      0, 0.0         true              false
	 *  文字列のゼロ     "0"           true              false
	 *  空文字列         ""            true              true
	 *  空配列        [], array()      true              true
	 *  ヌル	            null           true              true
	 *  偽              false          true              true
	 *  ------------------------------------------------------------
	 * ZERO_EMPTY(デフォルト): 質量(SCALA)判定
	 * ZERO_NOT_EMPTY : 質量ではなく、「値として入っているか」(NOT_SCALA)判定
	 *             ややこしいが、数値・文字列の0はscala的には「空」だが、
	 *             セットされているかどうかでいくと「空」ではない
	 * NOTICE:
	 *  emptyに関数のリターン値を直接セットするとエラーとなる(PHP5.4以前)
	 *  ※引数に関数を指定できるのは、PHP5.5以上からとのこと
	 *  なので、ラッパー関数で実行することとする
	 * 
	 *  以下重要注意点
	 *  ------------------------------------------------------------
	 *  ★「boolean」「object」について
	 * 
	 *  渡されてくる引数の型の想定として
	 *  「boolean」「object」は想定外である
	 *  そもそもこれらをempty()で空判定するのはおかしい
	 *  objectに関しては、それぞれで内容が変わるため、それぞれ独自に判定すること！
	 *  ------------------------------------------------------------
	 * 
	 *  ------------------------------------------------------------
	 *  ★多次元配列について
	 * 
	 *  2次元目の配列に空配列が入っていた場合(以下の状態)
	 *  array(array())
	 *  これの空判定だが、多次元判定も許容しようと思うと再帰処理が必要になる
	 *  標準関数のempty()も、上記状態ならfalse(すなわち空ではない)を返すようになっている
	 *  それにしたがって、当該メソッドでもfalseを返す状態にしておく
	 *  なので、多次元配列は、当該メソッドで判定しないこと！
	 *  ------------------------------------------------------------
	 * 
	 * CREATE: 2015.10.23 hesaka
	 * UPDATE: 2016.09.27 hesaka 第2引数に0の取り扱いを指定できるよう調整
	 * UPDATE: 2016.09.27 hesaka booleanが渡されてきたらアラートログ出力するよう調整
	 * *********************************** */
	public static function is_empty($data, $zero = ZERO_EMPTY) {

		//booleanが渡されてきたらアラートログを出す
		if (is_bool($data)) {
			LOGS_ALERT('*** EMERGENCY ALERT!!! *** boolean use is_empty!!!');
		}

		/*
		 * 0判定
		 * ZERO_NOT_EMPTYが指定されており、数値・文字列の0だった場合は
		 * false(つまり空ではない)を返す
		 */
		if ($zero == ZERO_NOT_EMPTY && ($data === 0 || $data === '0')) {
			return false;
		}

		//標準関数のempty()にかける
		return empty($data);
	}

	/*	 * **********************************
	 * NAME  : is_empties
	 * INPUT : data_list / array / チェック対象(配列)
	 *         zero / integer / 0の取り扱い(define ZERO_...定義)
	 * OUTPUT: true / 空ということ
	 *         false / 空ではないということ
	 * DESC  :
	 *  複数のデータを纏めて空チェックするもの
	 *  各パラメータをempty()に渡すラッパー
	 * 
	 * NOTICE:
	 *  気を付けないといけないのは、いづれかが空の場合は、
	 *  空として判定するということ
	 *  全てが空ではない場合のみ空でないと判定される
	 * CREATE: 2016.09.27 hesaka
	 * *********************************** */
	public static function is_empties($data_list, $zero = ZERO_EMPTY) {

		//そもそもdata_listが空(もしくは空配列)の場合はtrue(空)を返す
		//※ここでは0も空と判定するので強制的にZERO_EMPTYを指定する
		if (self::is_empty($data_list, ZERO_EMPTY)) {
			return true;
		}

		//配列じゃないものが渡されてきたらアラートログを出してtrue(空)を返す
		if (!is_array($data_list)) {
			LOGS_ALERT('*** EMERGENCY ALERT!!! *** not array use is_empties!!!');
			return true;
		}

		foreach ($data_list as $value) {
			//一つでも空があった場合はtrue(空)を返す
			if (self::is_empty($value, $zero)) {
				return true;
			}
		}

		//全てが「空ではない」場合はfalseを返す
		return false;
	}

	/*	 * **********************************
	 * NAME  : create_id
	 * INPUT : NONE
	 * OUTPUT: string / 生成したID
	 * DESC  :
	 *  ユニークな32桁のIDを作る
	 * NOTICE:
	 * CREATE: 2015.08.27 hesaka
	 * *********************************** */
	public static function create_id() {
		return md5(uniqid(rand(), 1));
	}

	/*	 * **********************************
	 * NAME  : create_id_40
	 * INPUT : NONE
	 * OUTPUT: string / 生成したID
	 * DESC  :
	 *  ユニークな40桁のIDを作る
	 * NOTICE:
	 * CREATE: 2015.08.27 hesaka
	 * *********************************** */
	public static function create_id_40() {
		return sha1(uniqid(rand(), 1));
	}

	/*	 * **********************************
	 * NAME  : create_dir
	 * INPUT : dir_path / string / ディレクトリパス
	 * OUTPUT: NONE
	 * DESC  :
	 *  ディレクトリを作る
	 * NOTICE:
	 * CREATE: 2015.08.27 hesaka
	 * *********************************** */
	public static function create_dir($dir_path) {
		if (!is_dir($dir_path)) {
			//途中ディレクトリも無ければ作成する
			mkdir($dir_path, 0777, true);
			chmod($dir_path,0777);
		}
	}

	/*	 * **********************************
	 * NAME  : delete_dir
	 * INPUT : dir_path / string / ディレクトリパス
	 * OUTPUT: NONE
	 * DESC  :
	 *  ディレクトリを削除する
	 * NOTICE:
	 * CREATE: 2015.08.27 hesaka
	 * *********************************** */
	public static function delete_dir($dir_path) {
		$strDir = opendir($dir_path);
		while ($strFile = readdir($strDir)) {
			if ($strFile != '.' && $strFile != '..') {
				unlink($dir_path . '/' . $strFile);
			}
		}
		rmdir($dir_path);
	}

	/*	 * **********************************
	 * NAME  : lf_to_crlf
	 * INPUT : str / string / 変換対象文字列
	 * OUTPUT: string / 変換後の文字列
	 * DESC  :
	 *  LFをCRLFに変換
	 * NOTICE:
	 * CREATE: 2015.08.27 hesaka
	 * *********************************** */
	public static function lf_to_crlf($str) {
		return preg_replace("/\n/", "\r\n", $str);
	}

	/*	 * **********************************
	 * NAME  : nl_to_space
	 * INPUT : str / string / 変換対象文字列
	 * OUTPUT: string / 変換後の文字列
	 * DESC  :
	 *  NLをスペースに変換
	 * NOTICE:
	 * CREATE: 2015.08.27 hesaka
	 * *********************************** */
	public static function nl_to_space($str) {
		//return str_replace("</p>", " </p>", $str);
		return str_replace("\r\n", " ", $str);
	}

	/*	 * **********************************
	 * NAME  : is_exist_word
	 * INPUT : string / string / 検索対象文字列
	 *         search / string / 検索文字
	 * OUTPUT: true / 含まれていた場合
	 *         false / 含まれていない場合
	 * DESC  :
	 *  $string に対して、$searchがあるか検索を行う
	 * NOTICE:
	 * CREATE: 2015.08.27 hesaka
	 * *********************************** */
	public static function is_exist_word($string, $search) {
		if (is_numeric(@mb_strpos($string, $search))) {
			return true;
		} else {
			return false;
		}
	}

	/*	 * **********************************
	 * NAME  : file_load
	 * INPUT : file_path / string / 対象ファイルパス
	 * OUTPUT: string / 成功した場合にファイルの中身
	 *         false / 失敗した場合
	 * DESC  :
	 *  file_pathのファイルの中身をロードする
	 * NOTICE:
	 * CREATE: 2015.09.27 hesaka
	 * *********************************** */
	public static function file_load($file_path) {
		return file_get_contents($file_path);
	}

	/*	 * **********************************
	 * NAME  : file_write
	 * INPUT : file_path / string / 対象ファイルパス
	 *         data / string / 保存内容
	 * OUTPUT: none
	 * DESC  :
	 *  file_pathにdataを内容としてファイル保存を行う
	 * NOTICE:
	 * CREATE: 2015.09.27 hesaka
	 * *********************************** */
	public static function file_write($file_path, $data) {
		$fp = fopen($file_path, "w");
		flock($fp, LOCK_EX);
		fputs($fp, $data);
		flock($fp, LOCK_UN);
		fclose($fp);
	}

	/*	 * **********************************
	 * NAME  : file_add_write
	 * INPUT : file_path / string / 対象ファイルパス
	 *         add_data / string / 追加保存する内容
	 * OUTPUT: none
	 * DESC  :
	 *  file_pathにadd_dataを内容の追加としてファイル保存を行う
	 * NOTICE:
	 * CREATE: 2015.09.27 hesaka
	 * *********************************** */
	public static function file_add_write($file_path, $add_data) {
		$fp = fopen($file_path, "a");
		flock($fp, LOCK_EX);
		fputs($fp, $add_data);
		flock($fp, LOCK_UN);
		fclose($fp);
	}

	/*	 * **********************************
	 * NAME  : money_format_yen
	 * INPUT : money / string / 金額
	 * OUTPUT: string / 金額
	 * DESC  :
	 *  3桁区切りと「円」を付与して返す
	 * NOTICE:
	 * CREATE: 2015.11.18 hesaka
	 * *********************************** */
	public static function money_format_yen($money) {
		return number_format($money) . '円';
	}

	public static function fgetcsv_reg(&$handle, $length = null, $d = ',', $e = '"') {
		$d = preg_quote($d);
		$e = preg_quote($e);
		$_line = "";
		$eof = false;
		while (($eof != true) and ( !feof($handle))) {
			$_line .= ( empty($length) ? fgets($handle) : fgets($handle, $length));
			$itemcnt = preg_match_all('/' . $e . '/', $_line, $dummy);
			if ($itemcnt % 2 == 0)
				$eof = true;
		}
		$_csv_line = preg_replace('/(?:\\r\\n|[\\r\\n])?$/', $d, trim($_line));
		$_csv_pattern = '/(' . $e . '[^' . $e . ']*(?:' . $e . $e . '[^' . $e . ']*)*' . $e . '|[^' . $d . ']*)' . $d . '/';
		preg_match_all($_csv_pattern, $_csv_line, $_csv_matches);
		$_csv_data = $_csv_matches[1];
		for ($_csv_i = 0; $_csv_i < count($_csv_data); $_csv_i++) {
			$_csv_data[$_csv_i] = preg_replace('/^' . $e . '(.*)' . $e . '$/s', '$1', $_csv_data[$_csv_i]);
			$_csv_data[$_csv_i] = str_replace($e . $e, $e, $_csv_data[$_csv_i]);
		}
		return empty($_line) ? false : $_csv_data;
	}

	/*	 * **********************************
	 * NAME  : csv_associative_load_from_sjis
	 * INPUT : file_path / string / ファイルパス
	 * OUTPUT: array / 連想配列
	 * DESC  :
	 * NOTICE:
	 * CREATE: 2015.12.09 hesaka
	 * UPDATE: 2016.06.27 hesaka(sonoda) MAC改行コード(\n)にも対応
	 * *********************************** */
	public static function csv_associative_load_from_sjis($file_path) {

		$counter = 0;
		$first = true;
		$point = "";
		$nameAry = array();

		$fp = fopen($file_path, "r");
		setlocale(LC_ALL, 'ja_JP');

		$buf = file_get_contents($file_path);
		$buf = preg_replace("/\r\n|\r|\n/", "\r\n", $buf);
		$fp = tmpfile();
		fwrite($fp, $buf);
		rewind($fp);

		while ($data = StaticFunction::fgetcsv_reg($fp, 50000)) {

			if ($first) {
				$dataMax = count($data);
				for ($k = 0; $k < $dataMax; $k++) {
					$nameAry[$k] = mb_convert_encoding($data[$k], "UTF-8", "SJIS-win");
					$nameAry[$k] = str_replace('　', "", $nameAry[$k]);
					$nameAry[$k] = str_replace(' ', "", $nameAry[$k]);
				}
				$first = false;
			} else {
				$dataMax = count($data);
				for ($k = 0; $k < $dataMax; $k++) {
					$point[$counter][$nameAry[$k]] = mb_convert_encoding($data[$k], "UTF-8", "SJIS-win");
					//$point[$counter][$nameAry[$k]] = strip_tags($point[$counter][$nameAry[$k]]);
					$point[$counter][$nameAry[$k]] = htmlspecialchars($point[$counter][$nameAry[$k]], ENT_QUOTES);
					$point[$counter][$nameAry[$k]] = mb_convert_kana($point[$counter][$nameAry[$k]], 'a');
					$point[$counter][$nameAry[$k]] = mb_convert_kana($point[$counter][$nameAry[$k]], 'K');
					$point[$counter][$nameAry[$k]] = str_replace("'", "’", $point[$counter][$nameAry[$k]]);
				}
				$counter++;
			}
		}//While

		fclose($fp);
		return $point;
	}

	/*	 * **********************************
	 * NAME  : json_to_array
	 * INPUT : json文字列
	 * OUTPUT: array / 連想配列
	 * DESC  :
	 *  jsonを配列に変換する
	 * NOTICE:
	 *  json_decode()の第2引数にtrueを指定することで
	 *  objectではなく配列にする
	 * CREATE: 2016.09.07 hesaka
	 * *********************************** */
	public static function json_to_array($json) {
		return json_decode($json, true);
	}

	/*	 * **********************************
	 * NAME  : language_text_replace
	 * INPUT : data / array /  リプレイス指示データ
	 * 
	 *         array(
	 *              'SEARCH' => array('name1', 'name2', ...),
	 *              'REPLACE' => array(
	 *                      'replace1',
	 *                      'replace2',
	 *                      ...
	 *              ),
	 *              'TARGET' => 'target'
	 *         )
	 * 
	 * OUTPUT: string / 変換後文字列
	 *         '' / 失敗時
	 * DESC  :
	 *  文字列の置き換えを行う
	 *  用途としては、language_textにあるテキストの
	 *  指定パラメータ置き換えである
	 * NOTICE:
	 * CREATE: 2016.10.06 hesaka
	 * *********************************** */
	public static function language_text_replace($data) {

		/*
		 * パラメータチェック
		 * ちょっと厳しめにチェックしておく
		 */
		if (StaticFunction::is_empty($data) || !is_array($data) || !is_array($data['SEARCH']) || !is_array($data['REPLACE']) || StaticFunction::is_empty($data['TARGET'])
		) {
			LOGS_ERR('invalid parameter');
			return '';
		}

		/*
		 * 変換対象の指定に従って対象名を囲う
		 */
		$search = array();
		foreach ($data['SEARCH'] as $value) {
			$search[] = '{{{' . $value . '}}}';
		}

		return str_replace($search, $data['REPLACE'], $data['TARGET']);
	}

	/*	 * **********************************
	 * NAME:changePasswordText
	 * DESC:
	 *  パスワードの文字を「*」に置き換え
	 * NOTICE:
	 * CREATE: 2016.10.16 aoyama
	 * *********************************** */
	public static function changePasswordText($str) {

		$num = mb_strlen($str, CHARACTER_ENCODING);

		$mask = "";
		for ($i = 0; $i < $num; $i++) {
			$mask .= "*";
		}
		return $mask;
	}

	/*	 * **********************************
	 * NAME  : count_num_format
	 * INPUT : $int / string / 数値
	 * OUTPUT: string / フォーマットされた数値
	 * DESC  :
	 *  3桁区切りを返す
	 * NOTICE:
	 * CREATE: 2016.10.20 aoyama
	 * *********************************** */
	public static function count_num_format($int) {
		return number_format((int) $int);
	}

	/*	 * **********************************
	 * NAME  : name_to_array
	 * INPUT : $string / string / 名前文字列
	 * OUTPUT: array / 名前を分割
	 * DESC  :
	 * 		スペース区切りで氏名を分割
	 * 		APIからどんな形で指名が入ってくるか不明なので柔軟性を持たせておく。
	 * 		分割できないものについてはそのまま姓に渡す。
	 * NOTICE:
	 * 		[吉田太郎]はNG
	 * 		[　吉田　太郎]はNG
	 * 		[吉田　　太郎]はOK
	 * 		[吉田　太郎　]は[太郎]のみ
	 * CREATE: 2016.10.27 aoyama
	 * *********************************** */
	public static function name_to_array($string) {

		$splitter = ' ';

		$ret = trim(mb_convert_kana($string, "s", 'UTF-8'));

		$match = array();
		if (preg_match('/^([^\s]+)[\s]+([^\s]+)/', $ret, $match)) {

			return array(0 => $match[1], 1 => $match[2]);
		}
		return array(0 => $ret, 1 => "");
	}

	/*	 * **********************************
	 * NAME  : phone_to_array
	 * INPUT : $string / string / 名前文字列
	 * OUTPUT: array / 名前を分割
	 * DESC  :
	 * 		ハイフン区切りでphoneナンバーを分割
	 * 		APIからどんな形で指名が入ってくるか不明なので柔軟性を持たせておく。
	 * 		分割できないものについてはそのまま１に渡す。
	 * NOTICE:
	 * CREATE: 2016.10.27 aoyama
	 * *********************************** */
	public static function phone_to_array($string) {

		$ret = trim(mb_convert_kana($string, "as", 'UTF-8'));
		$ret = preg_replace('/[^0-9\-]/', '', $ret);

		$match = array();
		if (preg_match('/^([0-9]+)[\-]+([0-9]+)[\-]+([0-9]+)/', $ret, $match)) {
			return array(0 => $match[1], 1 => $match[2], 2 => $match[3]);
		}
		return array(0 => $ret, 1 => "", 2 => "");
	}

	/*	 * **********************************
	 * NAME  : marge_name
	 * INPUT : 
	 * 		$sei / string / 名前文字列
	 * 		$mei / string / 名前文字列
	 * OUTPUT: array / 名前を結合
	 * DESC  :
	 * 		全角スペース区切りで氏名を結合
	 * NOTICE:
	 * CREATE: 2016.10.27 aoyama
	 * *********************************** */
	public static function marge_name($sei, $mei) {

		$splitter = '　';

		return $sei . $splitter . $mei;
	}
	/*	 * **********************************
	 * NAME  : marge_kana
	 * INPUT : 
	 * 		$sei / string / 名前文字列
	 * 		$mei / string / 名前文字列
	 * OUTPUT: string / 半角カナ
	 * DESC  :
	 * 		ふりがなを半角に変換し結合
	 * NOTICE:
	 * CREATE: 2017.4.7 aoyama
	 * *********************************** */
	public static function marge_kana($sei, $mei) {

		$splitter = '';

		return mb_convert_kana($sei. $splitter . $mei, "khsa") ;
	}
	/*	 * **********************************
	 * NAME  : marge_phone
	 * INPUT : 
	 * 		$tel1 / string / 名前文字列
	 * 		$tel2 / string / 名前文字列
	 * 		$tel3 / string / 名前文字列
	 * OUTPUT: array / 電話番号を結合
	 * DESC  :
	 * 		ハイフン区切りで電話番号を結合
	 * NOTICE:
	 * CREATE: 2016.10.27 aoyama
	 * *********************************** */
	public static function marge_phone($tel1, $tel2, $tel3) {
		
		if(StaticFunction::is_empty($tel1) && StaticFunction::is_empty($tel2) && StaticFunction::is_empty($tel3)) {
			return "";
		}
		
		$splitter = '-';
		return $tel1 . $splitter . $tel2 . $splitter . $tel3;
	}

	/*	 * **********************************
	 * NAME  : format_zero_fill
	 * INPUT : 
	 * 		$y / string / 名前文字列
	 * 		$m / string / 名前文字列
	 * 		$d / string / 名前文字列
	 * OUTPUT: array / 電話番号を結合
	 * DESC  :
	 * 		
	 * NOTICE:
	 * CREATE: 2016.11.28 aoyama
	 * *********************************** */
	public static function format_zero_fill($int, $length = 1) {

		if (preg_match("/^[0-9]+$/", $int)) {
			return str_pad($int, $length, 0, STR_PAD_LEFT);
		}

		return 0;
	}

	/*	 * **********************************
	 * NAME  : marge_birth
	 * INPUT : 
	 * 		$y / string / 名前文字列
	 * 		$m / string / 名前文字列
	 * 		$d / string / 名前文字列
	 * OUTPUT: array / 電話番号を結合
	 * DESC  :
	 * 		
	 * NOTICE:
	 * CREATE: 2016.11.4 aoyama
	 * *********************************** */
	public static function marge_birth($y, $m, $d) {
		return $y . sprintf("%02d", $m) . sprintf("%02d", $d);
	}

	/*	 * **********************************
	 * NAME  : format_item_id
	 * INPUT : 
	 * 		$y / string / 名前文字列
	 * 		$m / string / 名前文字列
	 * 		$d / string / 名前文字列
	 * OUTPUT: array / 電話番号を結合
	 * DESC  :
	 * 		
	 * NOTICE:
	 * CREATE: 2016.11.6 aoyama
	 * *********************************** */
	public static function format_item_id($item_id) {

		$ret = "";
		if (preg_match("/^[0-9]{9}$/", $item_id)) {

			$ret .= mb_substr($item_id, 0, 3);
			$ret .= '-' . mb_substr($item_id, 3, 3);
			$ret .= '-' . mb_substr($item_id, 6, 3);

			return $ret;
		}
		return false;
	}

	/*	 * **********************************
	 * NAME  : marge_address_for_view
	 * INPUT : 
	 * OUTPUT: string
	 * DESC  :
	 * 		viewに渡すために住所情報をマージして返す
	 * NOTICE:
	 * CREATE: 2016.10.27 aoyama
	 * *********************************** */
	public static function marge_address_for_view($zip, $state, $addr1, $addr2, $addr3 = null) {
		return "〒" . $zip . " " . $state . $addr1 . $addr2 . $addr3;
	}

	/*	 * **********************************
	 * NAME  : marge_birth_for_view
	 * INPUT : 
	 * OUTPUT: string
	 * DESC  :
	 * 		viewに渡すために日時をマージして返す
	 * NOTICE:
	 * CREATE: 2016.10.27 aoyama
	 * *********************************** */
	public static function marge_birth_for_view($year, $month, $day) {
		return $year . "年" . $month . "月" . $day . "日";
	}

	/*	 * **********************************
	 * NAME  : marge_birth_for_view
	 * INPUT : 
	 * OUTPUT: string
	 * DESC  :
	 * 		viewに渡すために日時をマージして返す
	 * NOTICE:
	 * CREATE: 2016.10.27 aoyama
	 * *********************************** */
	public static function check_token($token) {

		if ($token == SESSION::read('EXPIRES.ORIGINAL_TOKEN')) {
			return true;
		} else {
			return false;
		}
	}

	/*	 * **********************************
	 * NAME  : format_zip_hyphen
	 * INPUT : string
	 * OUTPUT: string
	 * DESC  :
	 * 		基幹システムから返却される郵便番号の形式が不明
	 * 		フォームではハイフンを指定しているがDBにはハイフンなしで登録されているよう
	 * 		（ただ単にバリデーションが聞いていないだけかもしれない）
	 * 		連続した数値の場合は分割して、
	 * 		ハイフンを含んでいる場合は一旦ハイフンを削除して再整形
	 * NOTICE:
	 * CREATE: 2016.11.11 aoyama
	 * *********************************** */
	public static function format_zip_hyphen($str) {

		$array = StaticFunction::zip_to_array($str);
		$ret = StaticFunction::array_to_zip($array);
		return $ret;
	}

	/*	 * **********************************
	 * NAME  : format_zip_no_hyphen
	 * INPUT : string
	 * OUTPUT: string
	 * DESC  :
	 * 		ヤマトに送信するメールのフォーマットがハイフンなしのものなので
	 *		取り急ぎ合わせる形でハイフンを削除する
	 * NOTICE:
	 * CREATE: 2016.12.24 aoyama
	 * *********************************** */
	public static function format_zip_no_hyphen($str) {
		$ret = str_replace(array("-", " "), "", mb_convert_kana($str, "a", CHARACTER_ENCODING));
		return $ret;
	}
	
	/*	 * **********************************
	 * NAME  : zip_to_array
	 * INPUT : string
	 * OUTPUT: $array
	 * DESC  :
	 * 		基幹システムから返却される郵便番号の形式が不明
	 * 		フォームではハイフンを指定しているがDBにはハイフンなしで登録されているよう
	 * 		（ただ単にバリデーションが聞いていないだけかもしれない）
	 * 		連続した数値の場合は分割して、
	 * 		ハイフンを含んでいる場合は一旦ハイフンを削除して再整形
	 * NOTICE:
	 * CREATE: 2016.11.11 aoyama
	 * *********************************** */
	public static function zip_to_array($str) {

		//まず数字のみにフィルタリング
		$reset = mb_ereg_replace('[^0-9]', '', mb_convert_kana($str, "a", CHARACTER_ENCODING));

		//配列に3桁と4桁を分割
		$ret = array();
		if (!StaticFunction::is_empty($reset)) {
			$ret[0] = mb_substr($reset, 0, 3);
			$ret[1] = mb_substr($reset, 3, 4);
		}

		return $ret;
	}

	/*	 * **********************************
	 * NAME  : array_to_zip
	 * INPUT : $array
	 * OUTPUT: string
	 * DESC  :
	 * 		ハイフンを含んでいる場合は一旦ハイフンを削除して再整形
	 * NOTICE:
	 * CREATE: 2016.11.11 aoyama
	 * *********************************** */
	public static function array_to_zip($array) {
		$ret = "";
		if (!StaticFunction::is_empty($array)) {
			$ret = $array[0] . "-" . $array[1];
		}
		return $ret;
	}

    /*	 * **********************************
     * NAME  : decode_view_text
     * INPUT : $array
     * OUTPUT: string
     * DESC  :
     * 		viewに渡すコメントでencodeされているものに対して
     * 		特定のタグのみdecodeする
     * NOTICE:
     * CREATE: 2016.11.16 aoyama
     * *********************************** */
    public static function decode_view_json($text) {

//		$ret = "";
//
//		//<a>タグにマッチする文字列を$pattarn[0][0]から順番に格納した
//		preg_match_all("/&lt;a href=.*&lt;\/a&gt;/iu", $text, $pattarn);
//
//		foreach ($pattarn[0] as $key => $val) {
//			//urlとして正しいものが含まれている場合は処理をする
//			if (preg_match("/(http|https):\/\/[-\w\.]+(:\d+)?(\/[^\s]*)?$/", $pattarn[0][$key])) {
//				//htmlspecialchars_decodeでエスケープ処理を解除した
//				$replace[] = htmlspecialchars_decode($pattarn[0][$key]);
//			} else {
//				//urlとして正しいものが含まれていない場合は処理しない
//				$replace[] = $pattarn[0][$key];
//			}
//		}
//		$ret = str_replace($pattarn[0], $replace, $text);
//		&lt;a href=&quot;http://yahoo.co.jp&quot;&gt;ヤフーリンク&lt;/a&gt;
//		$pattern = '/(&lt;a\s)(.*)(&gt;)(.*)(&lt;\/a&gt;)/';
//		$replacement = "<a $2>$4</a>";
//		preg_replace($pattern,$replacement,$text);
		$ret = $text;

//        $ret = preg_replace("/(&lt;a href=)(&quot;)(.*?)(&quot;)(&gt;)(.*?)(&lt;\/a&gt;)/", "<a href=\"$3\">$6</a>", $ret);
//
//        $ret = StaticFunction::convert_url_to_link($ret);
        $ret = urlencode($ret);
        return $ret;
    }

	/*	 * **********************************
	 * NAME  : decode_view_text
	 * INPUT : $array
	 * OUTPUT: string
	 * DESC  :
	 * 		viewに渡すコメントでencodeされているものに対して
	 * 		特定のタグのみdecodeする
	 * NOTICE:
	 * CREATE: 2016.11.16 aoyama
	 * *********************************** */
	public static function decode_view_text($text) {

//		$ret = "";
//			
//		//<a>タグにマッチする文字列を$pattarn[0][0]から順番に格納した
//		preg_match_all("/&lt;a href=.*&lt;\/a&gt;/iu", $text, $pattarn);
//
//		foreach ($pattarn[0] as $key => $val) {
//			//urlとして正しいものが含まれている場合は処理をする
//			if (preg_match("/(http|https):\/\/[-\w\.]+(:\d+)?(\/[^\s]*)?$/", $pattarn[0][$key])) {
//				//htmlspecialchars_decodeでエスケープ処理を解除した
//				$replace[] = htmlspecialchars_decode($pattarn[0][$key]);
//			} else {
//				//urlとして正しいものが含まれていない場合は処理しない
//				$replace[] = $pattarn[0][$key];
//			}
//		}
//		$ret = str_replace($pattarn[0], $replace, $text);
//		&lt;a href=&quot;http://yahoo.co.jp&quot;&gt;ヤフーリンク&lt;/a&gt;
//		$pattern = '/(&lt;a\s)(.*)(&gt;)(.*)(&lt;\/a&gt;)/';
//		$replacement = "<a $2>$4</a>";
//		preg_replace($pattern,$replacement,$text);

		$ret = preg_replace("/(&lt;a href=)(&quot;)(.*?)(&quot;)(&gt;)(.*?)(&lt;\/a&gt;)/", "<a href=\"$3\">$6</a>", $text);

		$ret = StaticFunction::convert_url_to_link($ret);
		return $ret;
	}

	/*	 * **********************************
	 * NAME  : chart_item_to_array
	 * INPUT : string
	 * OUTPUT: $array
	 * DESC  :
	 * 		カルテIDとアイテムIDが「_」で結合されている場合は
	 * 		配列にして返す。
	 * NOTICE:
	 * CREATE: 2016.11.18 aoyama
	 * *********************************** */
	public static function chart_item_to_array($str) {

		$ret = array();
		if (!preg_match("/[0-9]+_[0-9]+/", $str)) {
			return $ret;
		}

		list($chart_id, $item_id) = explode("_", $str);
		$ret = array(
			"chart_id" => $chart_id,
			"item_id" => $item_id
		);
		return $ret;
	}

	/*	 * **********************************
	 * NAME  : create_star
	 * INPUT : string
	 * OUTPUT: $array
	 * DESC  :
	 * 		評価数値に対して★を返す
	 * NOTICE:
	 * CREATE: 2016.11.24 aoyama
	 * *********************************** */
	public static function create_star($int = 0) {

		$star_on = "★";
		$star_off = "☆";

		$ret = "";
		for ($i = 1; $i <= 5; $i++) {
			if ($i <= $int) {
				$ret .= $star_on;
			} else {
				$ret .= $star_off;
			}
		}
		return $ret;
	}

	/*	 * **********************************
	 * NAME  : is_admin
	 * INPUT : string
	 * OUTPUT: boolean
	 * DESC  :
	 * 		管理者か判定
	 * NOTICE:
	 * CREATE: 2016.12.14 aoyama
	 * *********************************** */
	public static function is_admin($role) {
		if ((int) $role === ROLE_ADMIN) {
			return true;
		} else {
			return false;
		}
	}

	/*	 * **********************************
	 * NAME  : convert_zen_kana
	 * INPUT : string
	 * OUTPUT: string
	 * DESC  :
	 * 		半角カタカナが入るとメール送信が失敗するため
	 * 		このメソッドを作成しメール送信処理に追記した
	 * NOTICE:
	 * CREATE: 2016.12.19 aoyama
	 * *********************************** */
	public static function convert_zen_kana($text) {

		$ret = $text;
		$ret = mb_convert_kana($ret, 'KV', CHARACTER_ENCODING);
		return $ret;
	}
	/*	 * **********************************
	 * NAME  : convert_han_kana
	 * INPUT : string
	 * OUTPUT: string
	 * DESC  :
	 * 		半角カタカナに変換する。
	 * NOTICE:
	 * CREATE: 2017.4.10 aoyama
	 * UPDATE: 2017.5.15 aoyama
	 * 		半角カタカナ変換のひらがな→半カナを解除
	 * 		（読み仮名バリデーションでカタカナのみを受け付けるので汎用化）
	 * *********************************** */
	public static function convert_han_kana($text) {

		$ret = $text;
		$ret = mb_convert_kana($ret, 'aks', CHARACTER_ENCODING);
		return $ret;
	}    

	/*	 * **********************************
	 * NAME  : convert_zen_to_han_num
	 * INPUT : string
	 * OUTPUT: int
	 * DESC  :
	 * 		全角数値を半角数値に。
	 * NOTICE:
	 * CREATE: 2016.12.19 aoyama
	 * *********************************** */
	public static function convert_zen_to_han_num($text) {

		$ret = str_replace(array(" ", "　"), "", mb_convert_kana($text, "a", CHARACTER_ENCODING));
		return $ret;
	}

	/*	 * **********************************
	 * NAME  : convert_url_to_link
	 * INPUT : string
	 * OUTPUT: string
	 * DESC  :
	 * 		文字列中にURLが含まれた場合はリンクに書き換え
	 * NOTICE:
	 * CREATE: 2016.12.19 aoyama
	 * *********************************** */
	public static function convert_url_to_link($body, $link_title = null) {
		
		$pattern = '/(?<!href=")https?:\/\/[-_.!~*\'()a-zA-Z0-9;\/?:@&=+$,%#]+/';
		$body = preg_replace_callback($pattern, function($matches) use ($link_title) {
			
			
//			$link_title = $link_title ? : $matches[0];
			
			$link_title = mb_strimwidth($matches[0],0, 50, "...");
			
			return "<a href=\"{$matches[0]}\" target=\"_blank\">$link_title</a>";
		}, $body);
		return $body;
	}
    
	/*	 * **********************************
	 * NAME  : text_length
	 * INPUT : 
	 * 		$str / string / 名前文字列
	 * OUTPUT: int / バイト数
	 * DESC  :
     *      エンコード環境に依存することなく全角を2バイトと判定するため
     *      全てSJIS変換して文字数を算出
	 * NOTICE:
     *      これは厳密なバイト数を返すのではなく、
     *      UTF-8などでも全角を2バイト、半角を1バイトとして計算する。
     *      happyさんのメール処理ではバイト数制限があるためこのメソッドを追加
     * CREATE: 2017.4.7 aoyama
	 * *********************************** */
	public static function text_length($str) {

		$ret = 0;
        
        $ret = strlen( mb_convert_encoding($str, 'SJIS', CHARACTER_ENCODING) );
        
		return $ret;
	}
}

?>
