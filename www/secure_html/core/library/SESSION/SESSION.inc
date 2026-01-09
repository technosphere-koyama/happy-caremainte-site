<?php

/*
 * セッションについて
 * 
 * セッションが破棄されるタイミング
 * session_start()が行われたときに、session.gc_probabilityを分子、session.gc_divisorを分母とする確率で、 
 * session.gc_maxlifetimeよりファイル更新日付の古いファイルをsession.save_pathから削除します。
 * デフォルトでは、1/100の確率で、24分より古いセッションファイルが消えます。
 * という具合に、ガベージコレクトされる
 * 
 * session_destroy	
 * セッションに登録されたデータを全て破棄する
 * この関数は、 セッションに関するグローバル変数を破棄しません。 また、セッションクッキーを破棄しません。 セッション変数の利用を再開するには session_start() をコールする必要があります。
 * 
 * session_unset
 * 全てのセッション変数を開放する
 * 
 * ユーザーがログアウトするときのように、セッションを切断するには、 セッション ID の割り当ても解除する必要があります。
 * セッション ID の受け渡しに クッキーが使用されている場合（デフォルト）には、セッションクッキーも 削除されなければなりません。
 * そのためには setcookie() が利用できます。
 */
class SESSION {

	/* * **********************************
	 * NAME  : start
	 * INPUT : NONE
	 * OUTPUT: NONE
	 * DESC  :
	 *  セッション関係設定を行い、セッションスタートを行うメソッド
	 * NOTICE:
	 *  メソッド作成時にコメントヘッダを付けなかったので、
	 *  いつ作成したかわからない。。。
	 *  コメントヘッダをつけたのは20160127
	 * CREATE: 2015.xx.xx hesaka
	 * *********************************** */
	public static function start() {

		if (CONF::read('DEBUG_BAR.IS_ACTIVE')) DebugBarMaster::start_measure('session_start', '【SESSION】start');
		
		/*
		 * session_save_path 設定
		 */
		//ディレクトリがなければ作る
		if (!is_dir(CONF::read('SESSION.SAVE_PATH'))) {
			StaticFunction::create_dir(CONF::read('SESSION.SAVE_PATH'));
		}
		if (!StaticFunction::is_empty(CONF::read('SESSION.SAVE_PATH'))) session_save_path(CONF::read('SESSION.SAVE_PATH'));
		
		/*
		 * セッション 有効期限 設定
		 */
		ini_set('session.gc_maxlifetime', CONF::read('SESSION.MAX_LIFE_TIME'));
		
		/*
		 * セッション 有効期限 設定
		 */
		ini_set('session.cookie_lifetime', CONF::read('SESSION.MAX_LIFE_TIME'));

		/*
		 * session_name 設定
		 */
		session_name(CONF::read('SESSION.NAME'));

		/*
		 * session_cache_limiter 設定
		 */
		session_cache_limiter(CONF::read('SESSION.CACHE_LIMITER'));

		/*
		 * session_cache_expire 設定
		 */
		session_cache_expire(CONF::read('SESSION.CACHE_EXPIRE'));



		/*
		 * session_set_cookie_params 設定
		 * 
		 * lifetime:セッションクッキーの有効期限
		 * path:クッキーの対象となるドメイン上のパス
		 * domain:クッキーの対象となるドメイン
		 * secure:セキュアな接続の場合にのみクッキーを送信する
		 * httponly:セッションクッキーを設定する際に、httponlyフラグの送信を試みる
		 * 
		 * とあるが、lifetime, pathのみを設定する
		 */
		session_set_cookie_params(CONF::read('COOKIE.LIFE_TIME'), CONF::read('COOKIE.TARGET_PATH'));

		/*
		 * セッション スタート
		 * ※session_name()指定のセッションが生きていれば、そのセッション情報を_SESSIONにロード
		 * 　生きていなければ、新しくセッションIDを生成し、クッキーにもsession_name()指定の名前で保存することになる
		 */
		session_start();

		/*
		 * 期限切れチェック
		 */
		if (!self::expire_action()) {
			if (CONF::read('DEBUG_BAR.IS_ACTIVE')) DebugBarMaster::stop_measure('session_start');
			return;
		}
		
		/*
		 * 期限が切れていなければ、セッションIDを更新
		 * ※セッションハイジャック対策
		 */
		self::regenerate_id();
		
		//LOGS_DBG_LV1('session id = ' . session_id());
		//LOGS_DBG_LV1('session module name = ' . session_module_name());
		//LOGS_DBG_LV1('session name = ' . session_name());
		//LOGS_DBG_LV1('session save path = ' . session_save_path());

		if (CONF::read('DEBUG_BAR.IS_ACTIVE')) DebugBarMaster::stop_measure('session_start');
	}

	/* * **********************************
	 * NAME  : expire_action
	 * INPUT : NONE
	 * OUTPUT: true / 成功時
	 *         false / 失敗時
	 * DESC  :
	 *  期限切れ関係の処理を行う
	 * NOTICE:
	 *  メソッド作成時にコメントヘッダを付けなかったので、
	 *  いつ作成したかわからない。。。
	 *  コメントヘッダをつけたのは20160127
	 * CREATE: 2015.xx.xx hesaka
	 * *********************************** */
	public static function expire_action(){

		/*
		 * まずはクッキーチェック
		 * これが無いということは、クッキーの有効期限が切れたかクリアされたかである
		 * 
		 * これ、session_startした後では意味が無い
		 * session_startすると新しく生成されるので
		 * いやまてよ、はじめてセッションつくられたときは、ローカルにもってないので
		 * 有効か？
		 * 
		if(!isset($_COOKIE[CONF::read('SESSION.NAME')])){
			return false;
		}
		 */

		/*
		 * 次に、独自に決めた期限によるチェックを行う
		 * 
		 * UPDATE: 2016.10.21 aoyama
		 *		フォージェリ対策のためにORIGINAL_TOKENを発行
		 */
		//初めての場合は現在時刻をセット
		if(StaticFunction::is_empty(self::read('EXPIRES.ORIGINAL_SESSION'))){
			self::write('EXPIRES.ORIGINAL_SESSION', (time() + CONF::read('SESSION.ORIGINAL_EXPIRE')));
			self::write('EXPIRES.ORIGINAL_TOKEN', Encrypt::request_token( time() + CONF::read('SESSION.ORIGINAL_EXPIRE')) );
		}

		/*
		 * 切れていないかチェック
		 */
		if (self::read('EXPIRES.ORIGINAL_SESSION') < time()) {

			LOGS_NOTICE('!!! SESSION EXPIRED !!! session id = ' . session_id());

			//切れていれば、セッションをdestroyしてfalseを返す
			self::destroy();

			return false;
		}

		//範囲内の場合は、期限を更新する
		self::write('EXPIRES.ORIGINAL_SESSION', (time() + CONF::read('SESSION.ORIGINAL_EXPIRE')));

		return true;
	}

	/* * **********************************
	 * NAME  : regenerate_id
	 * INPUT : NONE
	 * OUTPUT: NONE
	 * DESC  :
	 * セッションIDがずっと同じだと、セッションハイジャック攻撃を受けて乗っ取られる可能性がある
	 * そこで、セッションIDの更新を行う
	 * ただし、アクセス毎に更新を行うと、F5連打や、システム的にリダイレクトを行っている場合に
	 * 間髪入れずにsession_regenerate_id()が実行され、その処理が絶妙なタイミングに入ると
	 * 1回目に作られたIDに旧IDからデータを移植する前に、2回目の処理が新しく作ったIDを削除してしまい
	 * 移植したいデータが宙に舞ってしまうという現象が発生する
	 * 
	 * それを防ぐため、
	 * ランダムで処理を行うのと、前回更新時刻より指定時間経っていたら更新するという
	 * ダブルチェックをとることにする
	 * ※これでも完全に防げるかというと、限りなく発生率を下げるというくらいである
	 * 
	 * NOTICE:
	 *  メソッド作成時にコメントヘッダを付けなかったので、
	 *  いつ作成したかわからない。。。
	 *  コメントヘッダをつけたのは20160127
	 * CREATE: 2015.xx.xx hesaka
	 * *********************************** */
	private static function regenerate_id() {

		//初めての場合はEXPIRES.GENERATE_LOCKに現在時刻をセット
		if(StaticFunction::is_empty(self::read('EXPIRES.GENERATE_LOCK'))){
			self::write('EXPIRES.GENERATE_LOCK', time());
		}

		/*
		 * EXPIRES.GENERATE_LOCKによる時間制約だけでは、
		 * 時間を更新する前に次がきた場合には防げない
		 * なので、ランダムで処理するというゆらぎを設定する
		 */
		if(mt_rand(1, CONF::read('SESSION.REGENERATE_ID_RANDAM_TIME')) === 1) {
			$cur = time();
			//前回の更新から指定秒以上経っていたら更新
			if (self::read('EXPIRES.GENERATE_LOCK') + CONF::read('SESSION.REGENERATE_ID_WAIT_TIME') < $cur) {
				$old = session_id();
				//時間更新
				self::write('EXPIRES.GENERATE_LOCK', $cur);
				//ID更新
				session_regenerate_id(true);
				//ログが多量に出るのでコメントアウト
				//LOGS_NOTICE('!!! SESSION REGENERATE ID !!! old=' . $old . ', new=' . session_id());
			}
		}
	}
	
	/* * **********************************
	 * NAME  : read
	 * INPUT : name / string / 取得対象添字文字列
	 * OUTPUT: string / 取得内容
	 * DESC  :
	 *  セッションに保持している、内容を取得する
	 * NOTICE:
	 *  メソッド作成時にコメントヘッダを付けなかったので、
	 *  いつ作成したかわからない。。。
	 *  コメントヘッダをつけたのは20160127
	 * CREATE: 2015.xx.xx hesaka
	 * *********************************** */
	public static function read($name) {

		if (StaticFunction::is_empty($name)) {
			LOGS_ERR('parameter is empty');
			return NULL;
		}

		$ret = $_SESSION;

		$param_list = explode(".", $name);
		foreach($param_list as $param) {
			//存在しなければNULLを返す
			if (!isset($ret[$param])) {
				return NULL;
			}
			$ret = $ret[$param];
		}

		return $ret;
	}

	/* * **********************************
	 * NAME  : write
	 * INPUT : name / string / セッション配列添え字名
	 *         data / void / 保存するデータ
	 * OUTPUT: NONE
	 * DESC  :
	 *  セッションに指定nameの添字配列を作成し、
	 *  dataを保存する
	 * NOTICE:
	 *  引数のdataには、どのような型でもセット可能
	 *  配列も可能
	 * CREATE: 2015.XX.XX hesaka
	 * UPDATE: 2015.12.04 hesaka パラメータチェックをemptyからissetに変更(emptyだと0が弾かれてしまう)
	 * *********************************** */
	public static function write($name, $data) {

		if (!isset($name)) {
			LOGS_ERR('parameter is empty');
			return NULL;
		}

		$parent = '';
		$point = '';
		$check = $_SESSION;

		//eval用に添字の文字列を作成
		$name_list = explode(".", $name);
		$count = count($name_list);
		for ($i = 1; $i <= $count; $i++) {
			if ($i < $count) {
				$parent .= "['" . $name_list[$i - 1] . "']";
				//配列か確認するように親の情報を取得しておく
				if (!isset($check[$name_list[$i - 1]])) {
					$check = NULL;
				} else {
					$check = $check[$name_list[$i - 1]];
				}
			}
			$point .= "['" . $name_list[$i - 1] . "']";
		}
		
		//親が配列でない場合は親をクリア
		if (isset($check) && !is_array($check)) {
			//ないと思うが、parentが空だとセッションが完全にクリアされるのでチェック
			if (StaticFunction::is_empty($parent)) {
				LOGS_ALERT('[emergency alert] this path is session all clear! check me now!!!');
				return NULL;
			}
			eval('$_SESSION' . $parent . ' = NULL;');
		//親が配列の場合はセット対象位置をクリア
		} else {
			//ないと思うが、pointが空だとセッションが完全にクリアされるのでチェック
			if (StaticFunction::is_empty($point)) {
				LOGS_ALERT('[emergency alert] this path is session all clear! check me now!!!');
				return NULL;
			}
			eval('$_SESSION' . $point . ' = NULL;');
		}

		//配列の場合は再帰で1つずつパラメータセットする必要がある
		if (is_array($data)) {
			self::write_array($point , $data);
		//配列でなければここでセット
		} else {
			/*
			 * stringの場合もしくは空の場合はダブルクオテが必要
			 * 20160127
			 * ダブルクオテにすると、「$」を入れるとevalの中で、
			 * 変数と認識されるみたいで、おかしな挙動になってしまう
			 * なので、囲むのはシングルクオテで行うよう変更
			 */
			$quote = '';
			if (is_string($data) || StaticFunction::is_empty($data)) {
				$quote = "'";
			}
			//セット
			eval('$_SESSION' . $point . ' = ' . $quote . $data . $quote . ';');
		}

	}
	
	/* * **********************************
	 * NAME  : write_array
	 * INPUT : parent / string / 親添字文字列
	 *         data_list / string or array / 書き込みたいデータ
	 * OUTPUT: NONE
	 * DESC  :
	 *  self::write()に指定されたデータが配列の場合は、
	 *  そのままセットするとおかしくなってしまうため、
	 *  配列を解析してひとつずつセットしていく必要がある
	 *  それを行うメソッドである
	 * NOTICE:
	 *  -----------------------------------
	 *  再帰関数
	 *  -----------------------------------
	 * 
	 *  メソッド作成時にコメントヘッダを付けなかったので、
	 *  いつ作成したかわからない。。。
	 *  コメントヘッダをつけたのは20160127
	 * CREATE: 2015.xx.xx hesaka
	 * *********************************** */
	private static function write_array($parent, $data_list) {

		foreach ($data_list as $key => $value) {

			$parents = $parent . "['" . $key . "']";
			
			//配列なら再帰
			if (is_array($value)) {

				self::write_array($parents, $value);

			//配列でないならセッションにセット
			} else {

				/*
				 * stringの場合もしくは空の場合はダブルクオテが必要
				 * 20160127
				 * ダブルクオテにすると、「$」を入れるとevalの中で、
				 * 変数と認識されるみたいで、おかしな挙動になってしまう
				 * なので、囲むのはシングルクオテで行うよう変更
				 */
				$quote = '';
				if (is_string($value) || StaticFunction::is_empty($value)) {
					$quote = "'";
				}
				eval('$_SESSION' . $parents . ' = ' . $quote . $value . $quote . ';');
			}
		}
	}
	
	/* * **********************************
	 * NAME  : delete
	 * INPUT : name / string / セッション配列添え字名
	 * OUTPUT: NULL
	 * DESC  :
	 *  指定添え字のパラメータを削除する
	 * NOTICE:
	 * ※当該メソッドでは、セッションを完全にクリアすることはできない
	 * 　完全クリアを行いたい場合は、clear()を使用すること！
	 * ※スーパーグローバルを使用したセッション変数の登録が不可能になってしまうため、
	 *   unset($_SESSION) を使って $_SESSION を完全に unset してはならない！
	 * 　ここでは、unset($_SESSION['xxx'])として、一部をクリアすることである
	 * 
	 *  メソッド作成時にコメントヘッダを付けなかったので、
	 *  いつ作成したかわからない。。。
	 *  コメントヘッダをつけたのは20160127
	 * CREATE: 2015.xx.xx hesaka
	 * *********************************** */
	public static function delete($name) {

		if (StaticFunction::is_empty($name)) {
			LOGS_ERR('parameter is empty');
			return NULL;
		}

		$str = '';
		$param_list = explode(".", $name);
		foreach($param_list as $param) {
			//空の場合('first.'とかで渡されると２次元目が空になる)終了
			if (StaticFunction::is_empty($param)) {
				LOGS_ALERT('invalid parameter. param=' . $name);
				return NULL;
			}
			$str .= "['" . $param . "']";
		}

		eval('unset($_SESSION' . $str . ');');
	}

	/* * **********************************
	 * NAME  : clear
	 * INPUT : NONE
	 * OUTPUT: NONE
	 * DESC  :
	 *  セッションにある情報をクリアする
	 * NOTICE:
	 * ※destroy()するわけではないので、セッションIDは破棄されない
	 * ※session_unset()も使用してはならないとのこと
	 * ※delete()にも書いたが、unset($_SESSION)は、セッション変数の登録が不可能になってしまうためやってはならない
	 * 　なので、クリアは、空配列を入れて参照を外すことを行う
	 *   そのうちガーベージコレクションが中身をクリアしてくれる
	 * 
	 *  メソッド作成時にコメントヘッダを付けなかったので、
	 *  いつ作成したかわからない。。。
	 *  コメントヘッダをつけたのは20160127
	 * CREATE: 2015.xx.xx hesaka
	 * *********************************** */
	public static function clear() {
		LOGS_DBG_LV1('session clear!!!');
		$_SESSION = array();
	}

	/* * **********************************
	 * NAME  : destroy
	 * INPUT : NONE
	 * OUTPUT: NONE
	 * DESC  :
	 *  セッションの完全破棄を行う
	 * NOTICE:
	 *  ・セッション変数の解除を行う
	 *  ・クッキーに残るセッションIDの破棄を行う
	 *  ・セッションIDの破棄を行う
	 * 
	 *  参考サイト
	 *  http://d.hatena.ne.jp/Kappuccino/20080726/1217049706
	 * 
	 *  メソッド作成時にコメントヘッダを付けなかったので、
	 *  いつ作成したかわからない。。。
	 *  コメントヘッダをつけたのは20160127
	 * CREATE: 2015.xx.xx hesaka
	 * *********************************** */
	public static function destroy() {

		//セッション変数を全て解除する
		self::clear();

		//セッションを切断するにはセッションクッキーも削除する
		if (isset($_COOKIE[session_name()])) {
			LOGS_DBG_LV1('cookie clear!!! name = ' . session_name());
			setcookie(session_name(), '', time()-42000, '/');
		}

		// 最終的に、セッションを破壊する
		session_destroy();

		LOGS_DBG_LV1('*** SESSION DESTROY COMPLETE ***');
	}
	
}

?>
