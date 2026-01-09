<?php

/*
 * 優先的に読み込んでおく必要のあるものは、ここでrequireしておく
 */
require_once dirname(__FILE__) . DIRECTORY_SEPARATOR . 'defines' . DIRECTORY_SEPARATOR . 'EnvDefine.inc';
require_once dirname(__FILE__) . DIRECTORY_SEPARATOR . 'defines' . DIRECTORY_SEPARATOR . 'DirDefine.inc';

/*
 * define/definesに配置されている設定ファイルのロードを行う
 * define/definesの中には、基本的にはdefine以外置かないこと！
 */
$define_list = FunctionForSetUp::get_file_name_on_dir(dirname(__FILE__) . DIRECTORY_SEPARATOR . 'defines');
if (empty($define_list)) {
	die('load define error');
}
//var_dump($define_list);

//全define設定をロード
foreach ($define_list as $file) {
	$path_info = pathinfo($file);
	switch ($path_info['extension']) {
		case 'php':
		case 'inc':
			require_once $file;
		default:
	}
}

?>
