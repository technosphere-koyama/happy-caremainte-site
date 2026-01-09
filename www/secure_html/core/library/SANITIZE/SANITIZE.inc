<?php

/* * **********************************
 * NAME:SANITIZE
 * DESC:
 * サニタイズを独立staticメソッドにした。
 * NOTICE:
 * UPDATE: 2015.11.23 sonoda
 * *********************************** */

class SANITIZE {

	/* * **********************************
	 * NAME  : exec
	 * INPUT : target / string / サニタイズを行うパラメータ
	 * OUTPUT: string / サニタイズが完了したパラメータ
	 * DESC  :
	 *  サニタイズを行う
	 * NOTICE:
	 *  ※セキュリティについて詳しく書かれているサイト
	 *  http://www.asahi-net.or.jp/~wv7y-kmr/memo/php_security.html#NullByteAttack_about
	 * CREATE: 2015.08.27 hesaka
	 * UPDATE: 2015.11.23 sonoda 独立staticメソッドにした。
	 * *********************************** */
	public static function exec($target) {

		//空の場合はそのまま返す
		if (empty($target)) {
			return $target;
		}

		$str = $target;

		/*
		 * NULLバイト攻撃対策
		 */
		$str = str_replace("\0", "", $str);

		/*
		 * クォートされた文字列を元に戻す
		 * \"は"に、\'は'に、\\は\へと変換
		 */
		$str = stripslashes($str);

		/*
		 * JS, PHP的に有効とされるタグを除去
		 * ※これは、閉じタグがないなどミスがあると、軒並み消される可能性がある
		 * 現状としては利用しない
		 *
		  $str = strip_tags($str);
		 */

		/*
		 * 特殊エンティティをコードに変換する
		 * 
		 * '&' → '&amp;' 
		 * '<' → '&lt;' 
		 * '>' → '&gt;' 
		 * '"'  → '&quot;'
		 * "'" → '&#039;' (あるいは &apos;) ※ENT_QUOTESが指定されている場合のみ
		 */
		$str = htmlspecialchars($str, ENT_QUOTES);

		/*
		 * 全角英数字を半角英数字へ
		 */
		//$str = mb_convert_kana($str, 'a', CHARACTER_ENCODING);

		/*
		 * 半角カナ(濁点あり含め)を全角カナへ
		 */
		//$str = mb_convert_kana($str, 'KV', CHARACTER_ENCODING);

		return $str;
	}

}
?>