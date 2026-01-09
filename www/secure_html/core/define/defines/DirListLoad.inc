<?php

/*
 * ディレクトリロードのモード種類
 * 
 * NORMAL: 都度ディレクトリを舐めて処理を進める方式
 *　メリット：ディレクトリ・ファイルを追加・変更・削除した際にすぐついてくる
 *　デメリット：都度舐める処理が重く、だいたい300msほど時間を要する
 * 
 * LIGHT: JSONにリストを保存しておき、それをロードしてきて処理に用いる方式
 *　※ファイルが無ければ作成し、前回作成した日時が1日以上前の場合は更新する
 *　メリット：処理が軽い(1ms程度)
 *　デメリット：現状ディレクトリを都度チェックしないので、更新を忘れると、
 *　次更新するまではエラーが発生したりする
 */
define("DIR_LIST_LOAD_MODE_NORMAL", 'normal');
define("DIR_LIST_LOAD_MODE_LIGHT", 'light');

/*
 * ロードモード指定
 * ここに指定したモードで動作する
 */
define("DIR_LIST_LOAD_MODE", DIR_LIST_LOAD_MODE_NORMAL);

/*
 * ディレクトリリストのリメイクタイミング(秒)
 * 前回の生成から指定時間以上経っていたら作り直しを行う
 * ※デフォルトは1時間
 */
define("DIR_LIST_REMAKE_LIMIT", (60 * 60 * 1));

/*
 * directory_listファイルの保存先パス
 */
define("DIR_LIST_FILE_PATH", DIR_DIRECTORY_LIST . DS . 'list.json');

?>
