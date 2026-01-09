<?php

/* * **********************************
 * NAME:DirectoryList
 * DESC:
 *  オートロード対象ディレクトリリストを
 *  予め作成しておくクラス
 * NOTICE:
 *  都度リストを生成すると無駄な処理となるので、一度作成し
 *  保持しておき、要求が出されたらそれを返すようにした
 * CREATE: 2015.08.27 hesaka
 * UPDATE: 2015.09.28 hesaka 
 *  さらに処理を軽くするため、JSONに吐き出しておき、ロードする方法を追加した
 *  ※都度ロードする形だと300msも時間を要していた
 *  　JSONロードにすると1msにまで短縮できた
 * *********************************** */
class DirectoryList {

	private static $base_dir;
	private static $additional_dir;

	/* * **********************************
	 * NAME  : load
	 * INPUT : NONE
	 * OUTPUT: NONE
	 * DESC  :
	 *  システムの基本となるディレクトリを、取得する
	 * NOTICE:
	 *  モードによって、都度直接舐める方式と、保存しておいたlist.jsonからロードする方式がある
	 *  開発段階で、ディレクトリ・ファイルがよく変わるタイミングではnormal
	 *  運用フェーズに入り、ソースをあまりいじらない場合はlightにしておくほうが負荷がだいぶ下がる
	 * CREATE: 2015.09.28 hesaka
	 * *********************************** */
	public static function load() {

		/*
		 * モードチェック
		 */
		switch (DIR_LIST_LOAD_MODE) {

			/*
			 * lightモード
			 * 1日に1度、最初にアクセスした際に、ディレクトリをロードして
			 * 「DirectoryList.json」を生成、以降は「DirectoryList.json」をロードする
			 */
			case DIR_LIST_LOAD_MODE_LIGHT:
				//JSONが無ければ作る
				if (!is_file(DIR_LIST_FILE_PATH)) {
					//ディレクトリが無ければ作る
					if (!is_dir(DIR_DIRECTORY_LIST)) {
						FunctionForSetUp::create_dir(DIR_DIRECTORY_LIST);
					}
					//direct_loadする
					self::direct_load();
					//ファイルに保存する
					self::file_save();

				//既にあればロードする
				} else {
					self::file_load();
				}

				break;

			/*
			 * normalモード
			 * 都度ディレクトリを検索する
			 */
			case DIR_LIST_LOAD_MODE_NORMAL:
			default:

				self::direct_load();

				break;
		}
 
	}

	/* * **********************************
	 * NAME  : file_save
	 * INPUT : NONE
	 * OUTPUT: NONE
	 * DESC  :
	 *  システムの基本となるディレクトリのパス情報をファイルに保存する
	 * NOTICE:
	 *  ファイル保存に失敗した場合、既にdirect_loadは行っているので処理はエラーなく続行できる
	 *  ただ、lightモード設定なのにnormalと同じ挙動をするので負荷は下がらないことになる
	 * CREATE: 2015.09.28 hesaka
	 * *********************************** */
	private static function file_save() {
		FunctionForSetUp::file_write(
			DIR_LIST_FILE_PATH, 
			json_encode(
				array_merge(
					array('save_time' => time()),
					array('save_time_view' => date('YmdHis')),
					array('base_dir' => self::$base_dir),
					array('additional_dir' => self::$additional_dir)
				)
			)
		);
	}

	/* * **********************************
	 * NAME  : file_load
	 * INPUT : NONE
	 * OUTPUT: NONE
	 * DESC  :
	 *  システムの基本となるディレクトリのパス情報を保存しているファイルからロードする
	 * NOTICE:
	 * CREATE: 2015.09.28 hesaka
	 * *********************************** */
	private static function file_load() {

		//list.jsonから取得
		$list = json_decode(FunctionForSetUp::file_load(DIR_LIST_FILE_PATH));

		//前回のリスト作成時刻から、指定時間以上経っていたら更新する
		if (($list->save_time + DIR_LIST_REMAKE_LIMIT) < time()) {
			//direct_loadする
			self::direct_load();
			//ファイルに保存する
			self::file_save();

		//一日経っていなければ、取得した内容をそれぞれメンバにセットする
		} else {
			self::$base_dir = $list->base_dir;
			self::$additional_dir = $list->additional_dir;
		}
	}

	/* * **********************************
	 * NAME  : direct_load
	 * INPUT : NONE
	 * OUTPUT: NONE
	 * DESC  :
	 *  システムのディレクトリ(下層ディレクトリも含め)の
	 *  フルパスリストを生成し、staticメンバに保存する
	 * 
	 *  ここに指定すれば、オートロードによりクラスが使えるようになる
	 * 
	 * ------------------------------------------------------------
	 * ※マスターディレクトリを追加した場合は、ここにも追加を行うこと！
	 * ------------------------------------------------------------
	 * 
	 * get_dir_list()
	 * これで指定すれば、指定ディレクトリ以下全てのファイルが対象となる
	 * 
	 * get_dir_list_for_add_on()
	 * これで指定すれば、preLoadConf/<env_dir_name>/ONがあるかどうかで
	 * そのディレクトリ以下を対象とするか判定し、なければ対象とならない 
	 * NOTICE:
	 *  システム起動時に一度だけ実行する想定
	 *  ※都度検索を行うと負荷が上がるため
	 *  ※ただし、それでも負荷がかかる場合は、クーロンなどで
	 *  　予め生成する方法をとることも考える必要がある
	 * CREATE: 2015.08.27 hesaka
	 * *********************************** */
	private static function direct_load() {
		self::$base_dir = 
			array_merge(
				/*
				 * applicationディレクトリ
				 * get_dir_list()により全ディレクトリを取得
				 */
				FunctionForSetUp::get_dir_list(DIR_APPLICATION),
				/*
				 * confディレクトリ
				 * get_dir_list()により全ディレクトリを取得
				 */
				FunctionForSetUp::get_dir_list(DIR_CONF),
				/*
				 * componentディレクトリ
				 * get_dir_list()により全ディレクトリを取得
				 * ※componentは直下にソースを配置するので意図的にDIR_COMPONENTを追加する
				 */
				array(DIR_COMPONENT),
				FunctionForSetUp::get_dir_list(DIR_COMPONENT)
			);
//var_dump(self::$base_dir);
		self::$additional_dir = 
			array_merge(
				/*
				 * libraryディレクトリ
				 * preLoadConfにてOFFとされているライブラリはリスト化されないよう
				 * get_dir_list_for_add_on()により取得
				 */
				FunctionForSetUp::get_dir_list_for_add_on(DIR_LIBRARY), 
				/*
				 * moduleディレクトリ
				 * preLoadConfにてOFFとされているモジュールはリスト化されないよう
				 * get_dir_list_for_add_on()により取得
				 */
				FunctionForSetUp::get_dir_list_for_add_on(DIR_MODULE)
			);
//var_dump(self::$additional_dir);
	}

	/* * **********************************
	 * NAME  : get_base_dir
	 * INPUT : NONE
	 * OUTPUT: array / システムのベースディレクトリリスト
	 * DESC  :
	 *  システムの基本となるディレクトリのフルパスリストを返す
	 * NOTICE:
	 * CREATE: 2015.08.27 hesaka
	 * *********************************** */
	public static function get_base_dir() {
		return self::$base_dir;
	}

	/* * **********************************
	 * NAME  : get_additional_dir
	 * INPUT : NONE
	 * OUTPUT: array / システムの追加要素ディレクトリリスト
	 * DESC  :
	 *  システムの基本以外で、追加したディレクトリの
	 *  フルパスリストを返す
	 * NOTICE:
	 * CREATE: 2015.08.27 hesaka
	 * *********************************** */
	public static function get_additional_dir() {
		return self::$additional_dir;
	}

	/* * **********************************
	 * NAME  : get_all_dir
	 * INPUT : NONE
	 * OUTPUT: array / システム全体のディレクトリリスト
	 * DESC  :
	 *  システム全体のディレクトリのフルパスリストを返す
	 * NOTICE:
	 * CREATE: 2015.08.27 hesaka
	 * *********************************** */
	public static function get_all_dir() {
		return array_merge(
				self::$base_dir,
				self::$additional_dir
			);
	}
}
DirectoryList::load();

?>
