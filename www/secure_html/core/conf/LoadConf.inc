<?php

/* ---------------------------------------
  共通の
  configをロード
  ---------------------------------------- */
$file_list = array();
$list1 = FunctionForSetUp::get_file_name_on_dir(DIR_CONF . DS . 'common');
if (!empty($list1)) {
	$file_list = $list1;
}
$list2 = FunctionForSetUp::get_file_name_on_target_env_dir(DIR_CONF);
if (!empty($list2)) {
	$file_list = array_merge($file_list, $list2);
}
//print '<br>common load!<br>';
//var_dump($file_list);

if (!empty($file_list)) {
	foreach ($file_list as $file) {
		$path_info = pathinfo($file);
		switch ($path_info['extension']) {
			case 'php':
			case 'inc':
				require_once $file;
				break;
			default:
		}
	}
}

/* ---------------------------------------
  library, moduleの
  configをロード
  ---------------------------------------- */
$additional_dir = DirectoryList::get_additional_dir();
foreach ($additional_dir as $dir) {
	$dir_array = explode(DS, $dir);
	if ($dir_array[count($dir_array) - 1] == DIR_NAME_PRE_LOAD_CONF) {

		$pre_load_conf_list = array();
		$list1 = FunctionForSetUp::get_file_name_on_dir($dir . DS . 'common');
		if (!empty($list1)) {
			$pre_load_conf_list = $list1;
		}

		$list2 = FunctionForSetUp::get_file_name_on_target_env_dir($dir);
		if (!empty($list2)) {
			$pre_load_conf_list = array_merge($pre_load_conf_list, $list2);
		}

		if (empty($pre_load_conf_list)) {
			continue;
		}
//print '<br>additional load!<br>';
//var_dump($pre_load_conf_list);

		foreach ($pre_load_conf_list as $file) {
			$path_info = pathinfo($file);
			switch ($path_info['extension']) {
				case 'php':
				case 'inc':
					require_once $file;
					break;
				default:
			}
		}
	}
}

?>
