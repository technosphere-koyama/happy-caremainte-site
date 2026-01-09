<?php

/* ---------------------------------------
 * アクセス元IPアドレスを取得
 * 
 * ロードバランサがかんでいる場合、REMOTE_ADDRは
 * ロードバランサのprivateIPとなる
 * よって状況によって判断する必要がある
 * HTTP_X_FORWARDED_FORに値がセットされている場合は、コンマ区切りの
 * 最初の値となる
 * HTTP_X_FORWARDED_FORに値がセットされていない場合は
 * REMOTE_ADDRをそのまま使用する
  ---------------------------------------- */
$tmp = '<none>';
if (isset($_SERVER["HTTP_X_FORWARDED_FOR"])) {
	$tmp_list = explode(',', $_SERVER["HTTP_X_FORWARDED_FOR"]);
	$tmp = (string)$tmp_list[0];
} else if (isset($_SERVER["REMOTE_ADDR"])) {
	$tmp = (string)$_SERVER["REMOTE_ADDR"];
}
define("USER_IP", ($tmp == '::1') ? ('localhost') : ($tmp));		//アクセス元のIPアドレス(::1の場合はローカルなのでlocalhostとしておく)

/* ---------------------------------------
 * portも同じく
 * ※ただし、HTTP_X_FORWARDED_PORTがない場合、REMOTE_PORTではなくSERVER_PORTとなる
  ---------------------------------------- */
$tmp = '<none>';
if (isset($_SERVER["HTTP_X_FORWARDED_PORT"])) {
	$tmp_list = explode(',', $_SERVER["HTTP_X_FORWARDED_PORT"]);
	$tmp = (string)$tmp_list[0];
} else if (isset($_SERVER["SERVER_PORT"])) {
	$tmp = (string)$_SERVER["SERVER_PORT"];
}
define("USER_PORT", $tmp);

/* ---------------------------------------
  url
  ---------------------------------------- */
define("URL_SCHEME_HTTP", 'http');
define("URL_SCHEME_HTTPS", 'https');
//フルURLを生成するには、「URL_SCHEME . '://' . URL_HOST . URL_REQUEST」とすればGETパラメータまでいける
define("URL_SCHEME", ((USER_PORT == '443') ? (URL_SCHEME_HTTPS) : (URL_SCHEME_HTTP)));	//$_SERVER['HTTPS']では、ロードバランサとかかませるとおかしくなるのでこちらで判断
define("URL_HOST", (isset($_SERVER["HTTP_HOST"]) ? ($_SERVER["HTTP_HOST"]) : ('')));
define("URL_REQUEST", (isset($_SERVER["REQUEST_URI"]) ? ($_SERVER["REQUEST_URI"]) : ('')));
define("URL_PATH", parse_url(URL_REQUEST, PHP_URL_PATH));			//ドメイン以降(クエリパラメータ含まず)
define("URL_QUERY", parse_url(URL_REQUEST, PHP_URL_QUERY));		//クエリパラメータのみ
define("URL_FULL_NOT_QUERY", URL_SCHEME . '://' . URL_HOST . URL_PATH);	//クエリパラメータは含まないフルパス
define("URL_FULL", URL_SCHEME . '://' . URL_HOST . URL_REQUEST);		//クエリパラメータも含めたフルパス

/* ---------------------------------------
  set CurrentPageName
  ---------------------------------------- */
$pathinfo = pathinfo($_SERVER['PHP_SELF']);
define("FILENAME", $pathinfo['basename']);

/* ---------------------------------------
  set BeforePageName
  ---------------------------------------- */
define("BEFORE", ((!empty($_SERVER['HTTP_REFERER'])) ? (basename($_SERVER['HTTP_REFERER'])) : ('')));

?>
