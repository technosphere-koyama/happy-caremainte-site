<?php

$config["DEBUG_BAR"] = array(
	"IS_ACTIVE" => false,
	"BASE_URL" => CONF::read('URL_PUBLIC_ROOT') . '_DEBUG_BAR',			//debugbar用js&cssディレクトリの場所
	"BASE_PATH" => DIR_PUBLIC . DS . '_DEBUG_BAR',					//debugbar用js&cssディレクトリのフルパス
	"IS_DB_ON" => false,								//テーブルに生成データを保存するかどうか
	"TABLE_NAME" => 'debug_bar_data'						//テーブル名
	//"STORAGE_PATH" => DIR_MODULE_THIRD_PARTY . '\DebugBar\PrevStorage'		//データを保存する場所(ファイル保存の場合)
);

//実行
//ここで実行しないと先にMaster呼ばれておかしくなる
DebugBarMaster::exec();

?>
