<?php

/* * **********************************
 * NAME  : __autoload
 * INPUT : class / string / クラス名
 * OUTPUT: NONE
 * DESC  :
 *  オートロード
 * NOTICE:
 *  クラスを生成する際に自動で呼び出される
 * CREATE: 2015.08.27 hesaka
 * *********************************** */
/** function __autoload($class) {
	class_load($class);
}*/

/*
 * 20151016 add
 * __autoload()を設定後、spl_autoload_register()を呼び出されると
 * __autoload()を無効化されるという鬼畜仕様であることに気付いた
 * 実際にSwiftMailerでspl_autoload_register()が実行され、無効化される
 * 現象に見舞われた
 * ということで、__autoload()をspl_autoload_register()に登録することで
 * 無効化ではなく、「2つ目に呼ばれるメソッドとして登録」されるよう対応
 */
spl_autoload_register('class_load');

/* * **********************************
 * NAME  : class_load
 * INPUT : class / string / クラス名
 * OUTPUT: NONE
 * DESC  :
 *  オートロードによりキックされ、
 *  有効な対象ディレクトリを検索し、
 *  対象のクラスファイルを発見したら
 *  require_once()する
 * NOTICE:
 * CREATE: 2015.08.27 hesaka
 * *********************************** */
function class_load($class) {

	/*
	 * namespace対策
	 * 
	 * namespaceでは、クラスインスタンス生成の際に
	 * DebugBar\StandardDebugBar()のように生成する
	 * そうすると、ここでも「DebugBar\StandardDebugBar」と渡されて
	 * 存在しないディレクトリとなってしまう
	 * なので、「\」で切って最後のクラス名のみで検索する用調整する
	 */
	if (is_numeric(@mb_strpos($class, '\\'))) {
		$tmp = explode('\\', $class);
		$class = $tmp[(count($tmp) - 1)];
	}
	$all_dir = DirectoryList::get_all_dir();
	foreach ($all_dir as $dir) {
		$target = $dir . DS . $class;
//print $target . '.inc' . '<br>';
		if (is_file($target . '.inc')) {
//print $target . '.inc<br>';
			require_once $target . '.inc';
			return;
		} else if (is_file($target . '.php')) {
//print $target . '.php<br>';
			require_once $target . '.php';
			return;
		}
	}
}

?>
