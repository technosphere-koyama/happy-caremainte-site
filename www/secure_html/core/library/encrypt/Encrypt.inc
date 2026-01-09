<?php

/* * **********************************
 * NAME:Encrypt
 * DESC:
 *  暗号化・復号化を行うクラス
 * NOTICE:
 *  md5()やsha1()はもはや解読されてしまうらしく、
 *  sha512など、ハイレベルの暗号化方式を使う必要があるとのこと
 * 
 *  PHP5.5.0からであれば、
 *  password_hash()：暗号化
 *  password_verify()：照合
 *  というものがあり、password_hash()については
 *  都度最適な暗号化方式があれば採用方式を変更してくれるというものである
 *  ※現段階では、PASSWORD_BCRYPTという方式しかないため、72文字までのパスワードでないと
 *    照合時にちゃんと照合できなくなるという問題がある(72文字以降は切り捨てられるため)
 *    http://blog.ohgaki.net/password_hash-important-limitation
 *  ただ、まだLINUXサーバのPHPインストールバージョンが標準では5.3.0なため、これらを
 *  使うと環境によってはエラーになってしまう
 *  5.5.0がスタンダードになったら使用することを検討したいところ
 *  ※暗号化方式を自動で変えた場合に、照合できなくならないかとか確認事項はあるが
 * 
 *  さらに、2要素認証というものもあり、Googleなどは既に採用している
 *  どの程度手間をかけるかだが、場合によっては使用する必要など出てくる可能性もある
 *  http://blog.ohgaki.net/use-2-factor-authentication-with-your-web-sites
 * 
 *  また、可逆な関数crypt()を使用すると、PHP5.3.7RC5で、
 *  「パスワードがどんな文字列でもログインできてしまう重大なバグ」が発生しているため
 *  crypt()は使用しないほうが良い
 * 　http://blog.tokumaru.org/2011/08/php537crypt.html
 * CREATE: 2015.09.30 hesaka
 * *********************************** */
class Encrypt{

	/* * **********************************
	 * NAME  : password_encrypt
	 * INPUT : password / string / パスワード
	 *         system_id / string / システムID
	 *         create_time / string / 登録日時
	 * OUTPUT: string / 暗号化したパスワード
	 *         NULL / 失敗した場合
	 * DESC  :
	 *  パスワードを独自のやり方で暗号化する
	 * 
	 * ロジックは以下の通り
	 * 
	 *  ソルトアンドペッパーを使用する
	 *  ※一度ハッシュ化した値に、ソルトを使ったハッシュ化を更に組み合わせる手法
	 * 
	 * ハッシュ化キー(固定文字列)
	 * create_time
	 * system_id(前と後ろから4文字ずつ
	 * で3回hash → sha1, sha256, sha512で
	 * 
	 * NOTICE:
	 *  可逆にするか不可逆にするかは、案件によって変える必要があると思われる
	 *  それに合わせてdecrypt()を実装するか変えれば良い
	 * CREATE: 2015.09.30 hesaka
	 * *********************************** */
	public static function password_encrypt($password, $system_id, $create_time) {

		//パラメータ空チェック
		if (empty($password) || empty($system_id) || (mb_strlen($system_id) < CONF::read('PASSOWRD.SYSTEM_ID_CHAR_NUM')) || empty($create_time) ) {
			LOGS_WARN('!!! invalid parameter !!! password=' . $password . ', system_id=' . $system_id . ', create_time=' . $create_time);
			return NULL;
		}

		//ハッシュ化キーにより暗号化
		$password_hash = hash('sha1', CONF::read('PASSWORD.ENCRYPT_KEY') . $password);

		/*
		 * 登録日時により暗号化
		 * ※カゴヤサーバにあげたらパスワードの登録と認証が合わなくなった。。。
		 * 　デバッグバーでクエリを見てみたら、create_timeがfloatで入っていた
		 * 　でも恐らく、DBから取ってきてencryptするときにはstring的な感じになっていて
		 * 　値が変わっていたと思われる
		 * 　floatにキャストすることにより解決
		 */
		$password_hash = hash('sha256', $password_hash . (float)$create_time);

		//システムIDにより暗号化
		$password_hash = hash('sha512', mb_substr($system_id, 0, CONF::read('PASSOWRD.SYSTEM_ID_CHAR_NUM')) . $password_hash . mb_substr($system_id, (-1 * CONF::read('PASSOWRD.SYSTEM_ID_CHAR_NUM'))));

		return $password_hash;
	}

	/* * **********************************
	 * NAME  : password_decrypt
	 * INPUT : encrypted_password / string / 暗号化されたパスワード
	 * OUTPUT: string / 復号化したパスワード
	 *         NULL / 失敗した場合
	 * DESC  :
	 *  パスワードの復号化を行う
	 * NOTICE:
	 *  基本的には、暗号化方式には不可逆方式を取るほうが良いので、
	 *  その場合は当該メソッドは使えなくなる
	 *  どーしても可逆にする必要が有る場合のみ当該メソッドを実装すること
	 * CREATE: 2015.09.30 hesaka
	 * *********************************** */
	public static function password_decrypt($encrypted_password) {
		//何もしない
		return NULL;
	}

	/* * **********************************
	 * NAME  : password_reset_token
	 * INPUT : id / string / ID
	 *         time / string / 時間
	 * OUTPUT: string / 暗号化したトークン
	 * DESC  :
	 *  パスワード再設定のトークンを生成する
	 * NOTICE:
	 *  不可逆
	 * CREATE: 2015.10.13 hesaka
	 * *********************************** */
	public static function password_reset_token($id, $time) {
		return hash('sha256', $id . $time . CONF::read('PASSWORD_RESET_TOKEN.ENCRYPT_KEY'));
	}

	/* * **********************************
	 * NAME  : member_regist_token
	 * INPUT : id / string / ID
	 *         time / string / 時間
	 * OUTPUT: string / 暗号化したトークン
	 * DESC  :
	 *  会員登録時仮登録トークンを生成する
	 * NOTICE:
	 *  不可逆
	 * CREATE: 2015.12.07 hesaka
	 * *********************************** */
	public static function member_regist_token($id, $time) {
		return hash('sha256', $id . $time . CONF::read('MEMBER_REGIST_TOKEN.ENCRYPT_KEY'));
	}
	
	/* * **********************************
	 * NAME  : request_token
	 * INPUT : $string / string / ID
	 * OUTPUT: string / 暗号化したトークン
	 * DESC  :
	 *		フォージェリ対策用のトークンを発行
	 * NOTICE:
	 *  不可逆
	 * CREATE: 2016.10.20 aoyama
	 * *********************************** */
	public static function request_token($string) {
		return hash('sha256', $string . CONF::read('PASSWORD_RESET_TOKEN.ENCRYPT_KEY'));
	}	
}

?>
