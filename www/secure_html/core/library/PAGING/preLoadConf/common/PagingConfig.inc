<?php

$config["PAGING"] = array(
	"IS_ACTIVE" => true,				//有効無効
	"DISPLAY_PREV_NUM" => 2,				//ページングに表示するページ番号数
	"DISPLAY_NUM" => 5,				//ページングに表示するページ番号数
	"PUBLIC" => 1,					//一般画面ID
	"DEFAULT_NUM_PUBLIC" => 20,			//デフォルト(一般画面)の表示数/ページ
	"DEFAULT_NUM_MAX" => 100,			//表示数/ページの最大数
	"SYSTEM" => 2,					//管理画面ID
	"DEFAULT_NUM_SYSTEM" => 10			//デフォルト(管理画面)の表示数/ページ
);

/*
 * 選択できる表示数のパターン
 */
$config["PAGING_PATERN"] = array(
	1 => 20,
	2 => 40,
	3 => 60,
	4 => 100
);

?>
