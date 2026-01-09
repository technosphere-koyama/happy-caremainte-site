<?php

/* * **********************************
 * NAME:ApiControllerCore
 * DESC:
 *  APIのコントローラ系の、継承最上位クラスとなる
 *  APIクラス全てに必要な機能を有し、極力末端やフレームの
 *  クラスでは何もしなくてもここで自動で行う実装ができると理想
 * NOTICE:
 *  コントローラの継承構造設計は、
 *  ApiController
 *  ↓
 *  ApiControllerFrame
 *  ↓
 *  ApiControllerCore
 *  となる
 * CREATE: 2015.10.02 hesaka
 * UPDATE: 2016.07.25 hesaka ApiErrorMessageMapをextends
 * UPDATE: 2016.10.06 hesaka ApiErrorMessageMapをextendsからロードへ変更
 * *********************************** */
class ApiControllerCore {

	private $output_data;
	private $child_name;

	private $error_message_map = NULL;
	
	/* * **********************************
	 * NAME  : __construct
	 * INPUT : child_name / string / 子クラス名
	 * OUTPUT: NONE
	 * DESC  :
	 *  コンストラクタ
	 *  サービスマスタから情報取得
	 *  output用メンバの初期化
	 * NOTICE:
	 * CREATE: 2015.xx.xx hesaka
	 * *********************************** */
	public function __construct($child_name = NULL) {

		//ログにより開始を出力
		LOGS_DBG_LV1(PHP_EOL . '-----------------------------' . PHP_EOL . '[API] ' . $this->child_name . ' START' . PHP_EOL . '-----');

		/*
		 * サービスマスタをDBから取得して
		 * CONFIGにセット
		 */
		global $config;
		$shop = new ServiceMasterModel();
		$config['DB_SERVICE_MASTER'] = $shop->get_basic_data();
		
		//output_data初期化
		$this->output_data = array();

		//子クラス名を取得
		$this->child_name = !empty($child_name) ? $child_name : get_class($this);
	}

	/* Destructor */
	public function __destruct() {

		//DebugBarの生成したデータをDBに保存
		if (CONF::read('DEBUG_BAR.IS_ACTIVE') && CONF::read('DEBUG_BAR.IS_DB_ON')) DebugBarMaster::set_db_storage(array('OUTPUT_DATA' => $this->output_data));

		//ログにより終了を出力
		LOGS_DBG_LV1(PHP_EOL . '-----' . PHP_EOL . $this->child_name . ' END' . PHP_EOL . '-----------------------------');
	}

	/* * **********************************
	 * NAME  : output
	 * INPUT : NONE
	 * OUTPUT: json / set()メソッドにより保存した全パラメータ
	 * DESC  :
	 *  Controller から画面側に渡したパラメータを全てJSON形式にして返す
	 * NOTICE:
	 *  ------------------------------------
	 *  API側のフレームワーク化に伴い
	 *  API実行元に成功データを返す際には
	 *  set()メソッドで値をセットし、
	 *  当該メソッドによりJSON形式で値を
	 *  取得する必要がある！
	 *  ------------------------------------
	 * CREATE: 2016.10.03 hesaka
	 * *********************************** */
	public function output() {

		//output空チェック
		if (count($this->output_data) <= 0) {
			LOGS_NOTICE('output_data is empty');
			return NULL;
		}

		/*
		 * 1次元目にdataを強制的にセットして返す
		 * ※API側のフレーワーク化でErrorとの関係により
		 * 　正しい値は「data」として返すことになった
		 */
		return json_encode(
			array(
				'data' => $this->output_data
			)
		);
	}

	/* * **********************************
	 * NAME  : stand_by_error_message
	 * INPUT : NONE
	 * OUTPUT: NONE
	 * DESC  :
	 *  エラーメッセージマップをロードする
	 * NOTICE:
	 *  コントローラフレームから呼び出されることを想定
	 *  CURRENT_LANGUAGE define後にロードする必要が出たため
	 *  ここでロードすることにした
	 * CREATE: 2016.10.06 hesaka
	 * *********************************** */
	protected function stand_by_error_message() {
		
		$apiErr = new ApiErrorMessageMap();
		$this->error_message_map = $apiErr->load();
	}
	
	/* * **********************************
	 * NAME  : get_error_message
	 * INPUT : key / integer / messageMapのキー
	 * OUTPUT: string / 配列をjson化した文字列
	 * DESC  :
	 *  呼び出し元に返すエラー内容必要情報を纏めて返す
	 * NOTICE:
	 *  JSONで返すか悩ましいところだが、
	 *  最初はjson_encodeして返すようにして様子を見る
	 * CREATE: 2016.07.25 hesaka
	 * *********************************** */
	protected function get_error_message($key) {

		//引数のkeyが不正(指定なし含む)の場合は強制的にその他エラーを出力するため
		//ここで初期設定しておく
		$judge_key = API_ERR_OTHER;

		//指定key有効性判断
		if (!StaticFunction::is_empty($key) 
			&& array_key_exists($key, $this->error_message_map)) {
			$judge_key = $key;
		}

		/*
		 * 受け取った側がエラーかどうか判定できるように
		 * 「ERROR」配列にラップして出力する
		 */
		return json_encode(
			array(
				'ERROR' => $this->error_message_map[$judge_key]
			)
		);
	}

	/* * **********************************
	 * NAME  : set
	 * INPUT : name / string / セットする情報のキーとなる名前(get時に必要となる)
	 *         data / string or array / セットしたいデータ
	 * OUTPUT: true / セット完了の場合
	 *         false / 引数が空の場合
	 * DESC  :
	 *  API実行元に渡すためのデータをセットする
	 *  Controllerから実行される想定
	 * NOTICE:
	 *  配列をセットすることも可能
	 *  その場合は、get()する際に「a.b」とすれば取得できる
	 * 
	 *  ※getに指定するように「a.b」と指定することは不可能
	 *  　それで設定したい場合は、連想配列で指定すること
	 *  ------------------------------------
	 *  API側のフレームワーク化に伴い
	 *  API実行元に成功データを返す際には
	 *  set()メソッドで値をセットし、
	 *  当該メソッドによりJSON形式で値を
	 *  取得する必要がある！
	 *  ------------------------------------
	 * CREATE: 2016.10.03 hesaka directaccess側のControllerCoreから持ってきた
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
		$this->set_output_data($name_list, $this->output_data, $data);

		/*
		 * 参照受けモードにする前は、これだけだった
		 * 「name」にドットが入っていなければ、多次元配列でも
		 * そのまま放り込んでいた
		 * 参照受けモードがエラーとかになったら、下記に戻す必要がある
		 * 
		 * $name_list = explode('.', $name);
		 * $this->set_output_data($name_list, $this->output_data, $data);
		 * を削除し、
		 * 
		 * $this->output_data[$name] = $data;
		 * を記述する
		 */

		return true;
	}

	/*	 * **********************************
	 * NAME  : set_output_data
	 * INPUT : list / array / セット対象となる添字配列
	 *         output / array(ポインタ) / output_dataから辿る配列(再帰のため)
	 *         data / void / セットしたいデータ(型は問わず)
	 * OUTPUT: NONE
	 * DESC  :
	 *  output_dataに、listに指定された目的地となる次元・添字位置に
	 *  dataをセットする
	 *  再帰関数となる
	 * NOTICE:
	 *  道中、存在しない箇所がある場合は空の配列をセットする
	 * CREATE: 2016.10.03 hesaka directaccess側のControllerCoreから持ってきた
	 * *********************************** */
	private function set_output_data($list, &$output, $data) {

		//頭から1つ抜く
		$tmp = array_shift($list);

		//ここが最後ならdataをセットして終了
		if (StaticFunction::is_empty($list)) {
			$output[$tmp] = $data;
			return;
		}

		//指定添字にセットされていなかったら空配列をセットする
		if (!isset($output[$tmp])) {
			$output[$tmp] = array();
		}

		$this->set_output_data($list, $output[$tmp], $data);
	}

}

?>
