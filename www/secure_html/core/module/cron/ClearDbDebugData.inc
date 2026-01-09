<?php

/* * **********************************
 * NAME:ClearDbDebugData
 * DESC:
 *  DBに溜めているデバッグバーのログを、定期的にお掃除するもの
 * NOTICE:
 * CREATE: 2015.10.21 hesaka 側だけ作成
 * *********************************** */

//保存期間(月)より前のものは削除する
CONF::read('CLEAR_DB_DEBUG_DATA.STAY_PERIOD_MONTH');

?>
