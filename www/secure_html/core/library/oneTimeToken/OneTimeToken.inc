<?php

/*
 * ワンタイムトークン クラス
 * 
 * フォームのポストなどで、F5連打とかされた際に1回目のみ通す必要などある
 * その場合に当該クラスにて認証を行う
 * ※セッションを使用するのでセッションを有効にしておく必要がある
 * 
 * 使い方
 * 
 * 埋め込むとき
 * <form method="post" action="">
 * <input type="hidden" name="token" value="<?=Token::generate()?>" />
 * <input type="submit" value="送信" />
 * </form>
 * 
 * 検証するとき(返り値チェックタイプ)
 * if (!isset($_POST['token']) || !Token::validate($_POST['token'])) {
 *     die('不正な処理が行われました');
 * }
 * 
 * 検証するとき(例外タイプ)
 * try {
 *     Token::validate(isset($_POST['token']) ? $_POST['token'] : null, true);
 * } catch (RuntimeException $e) {
 *     die($e->getMessage());
 * } 
 * 
 */
class OneTimeToken {

	private static $name = "\0__TOKENS__\0";
	private static $max = 10;

	/*
	 * 
	 */
	public static function generate() {
		self::initialize();
		$_SESSION[self::$name] = array(($new = base64_encode(openssl_random_pseudo_bytes(20))) => 1) +
			array_slice($_SESSION[self::$name], 0, self::$max - 1, true)
		;
		return $new;
	}

	/*
	 * 
	 */
	public static function validate($token, $throw = false) {
		self::initialize();
		$token = (string) filter_var($token);
		if (isset($_SESSION[self::$name][$token])) {
			unset($_SESSION[self::$name][$token]);
			return true;
		}
		if ($throw) {
			throw new RuntimeException('不正な処理が行われました');
		} else {
			return false;
		}
	}

	/*
	 * 
	 */
	private static function initialize() {
		if (!isset($_SESSION)) {
			throw new BadMethodCallException('セッションが開始されていません');
		}
		if (!isset($_SESSION[self::$name]) || !is_array($_SESSION[self::$name])) {
			$_SESSION[self::$name] = array();
		}
	}

}

?>
