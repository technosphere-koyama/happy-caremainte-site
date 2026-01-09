<?php

/* * **********************************
 * NAME:ControllerCore
 * DESC:
 *  コントローラ系の、継承最上位クラスとなる
 *  クラス全てに必要な機能を有し、極力末端やフレームの
 *  クラスでは何もしなくてもここで自動で行う実装ができると理想
 * NOTICE:
 *  コントローラの継承構造設計は、
 *  Controller
 *  ↓
 *  ControllerFrame
 *  ↓
 *  ControllerCore
 *  となる
 * CREATE: 2015.08.27 hesaka
 * *********************************** */
class ControllerCore {

	private $view_data;
	private $child_name;
	
	/* * **********************************
	 * NAME  : __construct
	 * INPUT : child_name / string / 子クラス名
	 * OUTPUT: NONE
	 * DESC  :
	 *  コンストラクタ
	 *  サービスマスタから情報取得
	 *  view用メンバの初期化
	 * NOTICE:
	 * CREATE: 2015.xx.xx hesaka
	 * *********************************** */
	public function __construct($child_name = NULL) {

		//ログにより開始を出力
		LOGS_DBG_LV1(PHP_EOL . '-----------------------------' . PHP_EOL . $this->child_name . ' START' . PHP_EOL . '-----');

		/*
		 * サービスマスタをDBから取得して
		 * CONFIGにセット
		 */
		global $config;
		$shop = new ServiceMasterModel();
		$config['DB_SERVICE_MASTER'] = $shop->get_basic_data();

		//view_data初期化
		$this->view_data = array();

		//子クラス名を取得
		$this->child_name = !empty($child_name) ? $child_name : get_class($this);
	}

	/* Destructor */
	public function __destruct() {

		//DebugBarの生成したデータをDBに保存
		if (CONF::read('DEBUG_BAR.IS_ACTIVE') && CONF::read('DEBUG_BAR.IS_DB_ON')) DebugBarMaster::set_db_storage(array('VIEW_DATA' => $this->view_data));

		//ログにより終了を出力
		LOGS_DBG_LV1(PHP_EOL . '-----' . PHP_EOL . $this->child_name . ' END' . PHP_EOL . '-----------------------------');
	}

	/* * **********************************
	 * NAME  : get
	 * INPUT : name / string / セットされたパラメータ名
	 * OUTPUT: string or array / 成功時、パラメータ値を返す
	 *         NULL / 引数が空・値が存在しない場合
	 * DESC  :
	 *　当該クラスsetメソッドにて保存したコントローラからの情報を
	 *  当メソッドにより取得する
	 *  VIEWから実行される想定
	 * NOTICE:
	 *  配列状態の物に対しては「.」でつないだ文字列で取得ができる
	 * CREATE: 2015.08.27 hesaka
	 * UPDATE: 2015.11.25 hesaka 存在するしないチェックをemptyからissetへ
	 *                           ※emptyだと、0が存在しない判定となってしまっていた
	 * *********************************** */
	public function get($name = '') {

		if (empty($name)) {
			LOGS_ERR('name is empty, for get view data');
			return NULL;
		}

		$ret = $this->view_data;
		$param_list = explode(".", $name);
		foreach($param_list as $param) {
			//存在しない場合はNULLを返す
			if (!isset($ret[$param])) {
				return NULL;
			}
			$ret = $ret[$param];
		}
		
		return $ret;
	}

	/* * **********************************
	 * NAME  : get_all
	 * INPUT : NONE
	 * OUTPUT: array / set()メソッドにより保存した全パラメータ
	 * DESC  :
	 *  Controller から画面側に渡したパラメータを全てチェックするために
	 *  debug bar に渡す専用
	 * NOTICE:
	 *  画面側では使用してはならない
	 * CREATE: 2015.08.27 hesaka
	 * *********************************** */
	public function get_all() {
		return array('VIEWに渡すデータ' => $this->view_data);
	}
	
	/* * **********************************
	 * NAME  : set
	 * INPUT : name / string / セットする情報のキーとなる名前(get時に必要となる)
	 *         data / string or array / セットしたいデータ
	 * OUTPUT: true / セット完了の場合
	 *         false / 引数が空の場合
	 * DESC  :
	 *  VIEWに渡すためのデータをセットする
	 *  Controllerから実行される想定
	 * NOTICE:
	 *  配列をセットすることも可能
	 *  その場合は、get()する際に「a.b」とすれば取得できる
	 * 
	 *  ※getに指定するように「a.b」と指定することは不可能
	 *  　それで設定したい場合は、連想配列で指定すること
	 * CREATE: 2015.08.27 hesaka
	 * UPDATE: 2015.11.17 hesaka $dataの空チェック外した
	 * UPDATE: 2015.11.20 hesaka 参照受け再帰処理により、「.」でセットできるようにした
	 * *********************************** */
	protected function set($name, $data) {

		//名前が空の場合はエラー
		if (empty($name)) {
			LOGS_ERR('parameter name is empty = ' . $name);
			return false;
		}
		
		//「.」を区切って配列へ
		$name_list = explode('.', $name);

		/*
		 * 20151120 hesaka
		 * name_listを回して多次元配列を降りて行き、セットしたいところで
		 * セットしてview_dataに保存されるようにするには、ポインタ機能が
		 * 必要となる
		 * php5.4以降は「参照渡し」がエラーになるが、
		 * これは関数呼び出し元で「&」を付けて渡すことで、
		 * 関数本体の引数で「&」を指定する、いわば「参照受け」は禁止されていないとのこと
		 * 恐らく、複数ある呼び出し元で&渡したり渡さなかったりするのではなく、
		 * 唯一記述の受け側で指定しろよとのことらしい
		 * ということで、ここで参照受けを用いてポインタアクセスを行う
		 */
		$this->set_view_data($name_list, $this->view_data, $data);

		/*
		 * 参照受けモードにする前は、これだけだった
		 * 「name」にドットが入っていなければ、多次元配列でも
		 * そのまま放り込んでいた
		 * 参照受けモードがエラーとかになったら、下記に戻す必要がある
		 * 
		 * $name_list = explode('.', $name);
		 * $this->set_view_data($name_list, $this->view_data, $data);
		 * を削除し、
		 * 
		 * $this->view_data[$name] = $data;
		 * を記述する
		 */

		return true;
	}

	/*	 * **********************************
	 * NAME  : set_view_data
	 * INPUT : list / array / セット対象となる添字配列
	 *         view / array(ポインタ) / view_dataから辿る配列(再帰のため)
	 *         data / void / セットしたいデータ(型は問わず)
	 * OUTPUT: NONE
	 * DESC  :
	 *  view_dataに、listに指定された目的地となる次元・添字位置に
	 *  dataをセットする
	 *  再帰関数となる
	 * NOTICE:
	 *  道中、存在しない箇所がある場合は空の配列をセットする
	 * CREATE: 2015.11.20 hesaka
	 * *********************************** */
	private function set_view_data($list, &$view, $data) {

		//頭から1つ抜く
		$tmp = array_shift($list);

		//ここが最後ならdataをセットして終了
		if (StaticFunction::is_empty($list)) {
			$view[$tmp] = $data;
			return;
		}

		//指定添字にセットされていなかったら空配列をセットする
		if (!isset($view[$tmp])) {
			$view[$tmp] = array();
		}

		$this->set_view_data($list, $view[$tmp], $data);
	}

	/*	 * **********************************
	 * NAME  : set_paging_param_to_enumerate
	 * INPUT : session_group / string / セッショングループ
	 * OUTPUT: NONE
	 * DESC  :
	 *  詳細ページにて、削除など行い一覧へ戻る場合に、
	 *  ページングの何ページに戻るかのGETパラメータをセットする
	 * NOTICE:
	 * CREATE: 2015.11.09 hesaka
	 * *********************************** */
	protected function set_paging_param_to_enumerate($session_group) {

		$list_get_parameter = array();
		if (!StaticFunction::is_empty(SESSION::read($session_group . '.cpp'))) {
			$list_get_parameter[] = 'pp=' . SESSION::read($session_group . '.cpp');
		}
		if (!StaticFunction::is_empty(SESSION::read($session_group . '.cp'))) {
			$list_get_parameter[] = 'p=' . SESSION::read($session_group . '.cp');
		}
		$this->set('list_get_parameter', ((!StaticFunction::is_empty($list_get_parameter)) ? ('?' . implode('&', $list_get_parameter)) : ('')));
	}

	/* * **********************************
	 * NAME  : redirect
	 * INPUT : path / string / リダイレクト先パス
	 * OUTPUT: false / パスが空の場合
	 *         ※成功すればリダイレクトを行うので、その場合は返らない
	 * DESC  :
	 *  リダイレクト処理
	 * NOTICE:
	 *  header:locationを行った際には、場合によってはその後の処理を少し
	 *  実行してしまうことがあるらしいので、直後にexit()を入れておく必要がある
	 *  ここでexit()するので、呼び出し元でexit()を行う必要はない
	 * CREATE: 2015.08.27 hesaka
	 * *********************************** */
	protected function redirect($path) {

		if (empty($path)) {
			LOGS_ERR('parameter is empty');
			return false;
		}

		LOGS_DBG_LV1('*** REDIRECT TO ' . $path . ' ***');

		header('location: ' . $path);
		exit();	
	}
	
}

?>
