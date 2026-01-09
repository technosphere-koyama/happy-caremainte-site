<?php
/* * **********************************
 * NAME:ApnsPHP_Log_Custom
 * DESC:
 *  Apnsデフォルトではログが出力されるので、非表示にするための関数。
 * NOTICE:
 *  Apnsのバージョンアップを行うとこの関数も合わせて見直すこと。
 * CREATE: 2016.11.30 sonoda
 * *********************************** */
class ApnsPHP_Log_Custom implements ApnsPHP_Log_Interface
{
	public function log($sMessage){}
}