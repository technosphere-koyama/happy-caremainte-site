<?php

/* * **********************************
 * NAME:DbCast
 * DESC:
 *  DBに対してクエリを発行する際にテーブル名、カラム名、値について
 *  一定のルールで調整(空の場合の値判定・シングルクオテで囲むなど)を
 *  行う必要がある
 *  それをこのクラスで一元管理・対応するものである
 *  
 * NOTICE:
 *  ものによっては、ただキャストするだけでは問題があるものがある
 *  現時点でわかっているものとしては
 *  datetimeがある
 * 
 *  【datetime】
 *  datetimeは、DBの「DATETIME」型ではなく、
 *  BIGINT14桁にて日時を取り扱うようにしている
 *  ここで、db_shellのinsert(), update()で文字列型なら
 *  自動的に「'」を付けてクエリを作成するようにしているため、
 *  stringで渡してしまうと型の不一致でエラーとなってしまう
 *  ※14桁の数字はINTではオーバーフローするためphp上ではstringもしくはfloatになる
 *  なので、db_shellに渡す前にfloatでキャストする必要がある
 *  datetimeはNULLを許可しており、未指定となるものは極力NULLとして保存したい
 *  ここで、NULLをfloatにキャストすると自動的に0となってしまう
 *  なので、NULL, 0, 空文字の場合は(string)NULLをクエリに組み込みたい
 *  よって、単なる(float)キャストではなく場合分けしてのキャストを行う必要があるのである
 * 
 *  現状では上記のみだが、
 *  後日、型を変えたい際などに、ここさえ変えれば全範囲に調整が効くように
 *  しておきたいのでかならず当該staticメソッドによりキャストすること！
 * 
 * --------------------------------------------------------
 *  DBに値をセット(insert, update)する場合は、
 *  かならず当該staticメソッドによりキャストすることを制約する
 *  ※通常のキャスト((string)など)は使用してはならない
 * --------------------------------------------------------
 * 
 * CREATE: 2015.11.17 hesaka
 * UPDATE: 2016.09.10 hesaka ticket_code(), id()を追加
 * UPDATE: 2016.09.27 hesaka system_id()を追加
 * *********************************** */
class DbCast {

	/* * **********************************
	 * NAME  : table_name
	 * INPUT : value / string / テーブル名
	 * OUTPUT: string / 「`」で囲んだ文字列
	 * DESC  :
	 *  クエリに使用するテーブル名用のキャスト
	 * NOTICE:
	 *  ----------------------------------
	 *  テーブル名に「-」を使用したい場合は
	 *  「`」を使用する必要がある
	 *  ということから当該メソッドが生まれた
	 *  正しくは「`」で囲むのが正解みたいなので、
	 *  もー全てに適応することになった
	 *  クエリを組む際には当該メソッドを使用すること
	 *  ----------------------------------
	 * CREATE: 2016.10.04 hesaka
	 * *********************************** */
	public static function table_name($value) {
		//テーブル名が空の場合はアラート出しておく
		if (StaticFunction::is_empty($value)) {
			LOGS_ALERT('input empty!! ' . $value);
		//空じゃない場合、念のため前後に「`」があったら削除しておく
		} else {
			$value = ltrim($value, "`");
			$value = rtrim($value, "`");
		}
		//どーやってもクエリエラーになると思われるので、
		//空の場合も通常通り返す
		return "`" . $value . "`";
	}
	
	/* * **********************************
	 * NAME  : boolean
	 * INPUT : value / void / キャストしたい値
	 * OUTPUT: 1 / 0, NULL, falseでない場合
	 *         0 / 0, NULL, falseの場合
	 * DESC  :
	 *  指定された値を1か0に変換してintegerの型で返す
	 *  ※integerの理由としては、MySQLにはBooleanは存在せず、
	 *    integerで1か0が入るためである
	 * NOTICE:
	 *  色々な値を入れてしまうとバグるので、
	 *  DB用にdefine定義した「DB_TRUE」「DB_FALSE」にて
	 *  返すことになる
	 *  ※「DB_TRUE」「DB_FALSE」は既にdefineにてintegerにキャストされている
	 * CREATE: 2015.11.17 hesaka
	 * *********************************** */
	public static function boolean($value) {
		//0, NULL, falseの場合は0(MySQL的にはfalseと同義)
		/*if ($value === 0 || $value === NULL || $value === false) {*/
		if (StaticFunction::is_empty($value)) {
			return DB_FALSE;
		}
		return DB_TRUE;
	}

	/* * **********************************
	 * NAME  : integer
	 * INPUT : value / void / キャストしたい値
	 * OUTPUT: integer / 数値
	 * DESC  :
	 *  指定された値をintegerにキャストして返す
	 * NOTICE:
	 *  empty()判断により、
	 *  NULL, array{}, falseは0にして返すことになる
	 * CREATE: 2015.11.17 hesaka
	 * *********************************** */
	public static function integer($value) {
		if (StaticFunction::is_empty($value)) {
			return (integer)0;
		}
		return (integer)$value;
	}

	/* * **********************************
	 * NAME  : string
	 * INPUT : value / void / キャストしたい値
	 * OUTPUT: string / 文字列
	 * DESC  :
	 *  指定された値をstringにキャストして返す
	 * NOTICE:
	 *  できるだけ、「空」の認識のものは空文字ではなく
	 *  NULLで返したい
	 *  この方が検索が早いからである
	 *  しかし、NOT NULLのstring型のところにNULLを
	 *  入れようとするとエラーとなってしまう
	 *  なので、現時点では、仕方ないので空文字が入ることを
	 *  許可するものとする
	 *  ある程度運用してみてから、ここを縛るようにするかは判断する
	 * CREATE: 2015.11.17 hesaka
	 * UPDATE: 2015.11.20 hesaka 異常判定された場合はNULLという文字を返すように変更
	 * UPDATE: 2015.11.20 hesaka シングルクオテで囲って返すように変更
	 * *********************************** */
	public static function string($value) {
		//NULL,false,空文字の場合はNULLという文字列を返す
		//※0の場合は、0という文字列が欲しい場合があるので外しておく
		if ($value === NULL || $value === false || strlen($value) == 0) {
			return (string)'NULL';
		}
		return (string)"'" . $value . "'";
	}

	/* * **********************************
	 * NAME  : float
	 * INPUT : value / void / キャストしたい値
	 * OUTPUT: float / 数値
	 * DESC  :
	 *  指定された値をfloatにキャストして返す
	 * NOTICE:
	 *  empty()判断により、
	 *  NULL, array{}, falseは0にして返すことになる
	 * CREATE: 2015.11.17 hesaka
	 * *********************************** */
	public static function float($value) {
		if (StaticFunction::is_empty($value)) {
			return (float)0;
		}
		return (float)$value;
	}
	
	/* * **********************************
	 * NAME  : datetime
	 * INPUT : value / void / キャストしたい値
	 * OUTPUT: string / 正常値の場合
	 *         string / NULLという文字列(異常値の場合)
	 * DESC  :
	 *  指定された値を日時用にキャストして返す
	 * NOTICE:
	 *  datetimeは、DBの「DATETIME」型ではなく、
	 *  BIGINT14桁にて日時を取り扱うようにしている
	 *  ここで、db_shellのinsert(), update()で文字列型なら
	 *  自動的に「'」を付けてクエリを作成するようにしているため、
	 *  stringで渡してしまうと型の不一致でエラーとなってしまう
	 *  ※14桁の数字はINTではオーバーフローするためphp上ではstringもしくはfloatになる
	 *  なので、db_shellに渡す前にfloatでキャストする必要がある
	 *  datetimeはNULLを許可しており、未指定となるものは極力NULLとして保存したい
	 *  ここで、NULLをfloatにキャストすると自動的に0となってしまう
	 *  なので、NULL, 0, 空文字の場合は(string)NULLをクエリに組み込みたい
	 * CREATE: 2015.11.17 hesaka
	 * UPDATE: 2015.11.20 hesaka 異常判定された場合はNULLという文字を返すように変更
	 * UPDATE: 2015.12.22 aoyama phpスクリプト上でfloatにすると「2.0121007126E+16」みたいになってしまうので、
	 *                           stringで扱うこと。query文はstring文字列なので問題無いはず。
	 * *********************************** */
	public static function datetime($value) {
		/*if ($value === 0 || $value === NULL || $value === false) {*/
		if (StaticFunction::is_empty($value)) {
			return (string)'NULL';
		}
		return (string)$value;
	}

	/* * **********************************
	 * NAME  : ticket_code
	 * INPUT : value / void / キャストしたい値
	 * OUTPUT: string / 正常値の場合
	 *         string / NULLという文字列(異常値の場合)
	 * DESC  :
	 *  指定された値をチケットコード用にキャストして返す
	 * NOTICE:
	 *  チケットコードは、日時と同じくunsigned big intとなっている
	 *  なので、string以外の型で持つとオーバーフローしてしまう
	 * CREATE: 2016.08.10 hesaka
	 * UPDATE: 2016.09.10 hesaka datetime()をラップする形に変更
	 * *********************************** */
	public static function ticket_code($value) {
		return DbCast::datetime($value);
	}
	
	/* * **********************************
	 * NAME  : id
	 * INPUT : value / void / キャストしたい値
	 * OUTPUT: string / 正常値の場合
	 *         string / NULLという文字列(異常値の場合)
	 * DESC  :
	 *  指定された値をID(unsigned big int)用にキャストして返す
	 * NOTICE:
	 *  IDは、unsigned big intとなっている
	 *  なので、string以外の型で持つとオーバーフローしてしまう
	 *  ※string()で対応していたが、どれ使うんだっけ？と迷ってしまうため
	 *    明示的にid()としてわかりやすいくする
	 *  ※string()をラップする形で対応する
	 * CREATE: 2016.09.10 hesaka
	 * *********************************** */
	public static function id($value) {
		//NULL,false,空文字の場合はNULLという文字列を返す
		//※0の場合は、0という文字列が欲しい場合があるので外しておく
		if ($value === NULL || $value === false || strlen($value) == 0) {
			return (string)'NULL';
		}
		return (string)$value;
	}

	/* * **********************************
	 * NAME  : system_id
	 * INPUT : value / void / キャストしたい値
	 * OUTPUT: string / 正常値の場合
	 *         string / NULLという文字列(異常値の場合)
	 * DESC  :
	 *  指定された値をsystem_id(char)用にキャストして返す
	 * NOTICE:
	 *  ※string()で対応していたが、どれ使うんだっけ？と迷ってしまうため
	 *    明示的にsystem_id()としてわかりやすいくする
	 *  ※string()をラップする形で対応する
	 * CREATE: 2016.09.27 hesaka
	 * *********************************** */
	public static function system_id($value) {
		return DbCast::string($value);
	}

	/* * **********************************
	 * NAME  : geo
	 * INPUT : latitude / void / 緯度
	 * 		   longitude / void / 経度
	 * OUTPUT: string / 正常値の場合
	 *         string / NULLという文字列(異常値の場合)
	 * DESC  :
	 *  指定された値をgeometry用にキャストして返す
	 *  エラー判定は以下の2つ
	 * 　・マイナス、数字、.(ドット)以外の文字が含まれる
	 * 　・いずれかのINPUTが空(0はあり得る)
	 *
	 * geometryとして、緯度経度のいずれか空として使うことも
	 * 可能なのしれないが、現状、そのような使い方は想定して
	 * いないのでエラーとしておく。
	 * NOTICE:
	 * CREATE: 2016.09.28 sonoda
	 * *********************************** */
	public static function geo($latitude, $longitude) {

		//まず空チェック
		if (StaticFunction::is_empty($latitude, ZERO_NOT_EMPTY) ||
			StaticFunction::is_empty($longitude, ZERO_NOT_EMPTY)){
			LOGS_ALERT('input empty!!' . $latitude . $longitude);
			return (string)'NULL';
		}

		//空でなければ文字構成チェック
		$pattern = '/^[-]?([0-9]+|[0-9]+[.]{1}[0-9]+)$/';
		if(!preg_match($pattern, $latitude) ||
			!preg_match($pattern, $longitude)){
			LOGS_ALERT('input format error!![lati=' . $latitude .' long='. $longitude . ']');
			return (string)'NULL';
		}

		return "GeomFromText('POINT( " . $latitude . " " . $longitude . " )')";
	}
}

?>
