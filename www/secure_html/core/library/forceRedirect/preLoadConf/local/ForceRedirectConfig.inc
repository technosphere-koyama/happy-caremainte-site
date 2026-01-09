<?php

$config["FORCE_REDIRECT"] = array(
	"IS_ACTIVE" => false,							//有効 or 無効
	"DESTINATION" => CONF::read('URL_PUBLIC_ROOT') . "maintenance.html"	//飛び先
);

/*
 * 時限設定
 * STARTからENDまでの間制限が有効となる
 * ※0を指定すると、制限なくずっと有効となる
 * STARTを0、ENDは時間指定とすると、
 * 設定直後から有効となり、ENDが来たら無効となる
 * 逆に、STARTは時間指定して、ENDは0とすると、
 * START指定までは無効で、START指定まできたら、以降はずっと有効となる
 * 時間指定を行う場合は、strtotime()にて行うこと
 * 設定文字列については
 * 　<年>-<月>-<日> <時>:<分>:<秒>
 * 　各パラメータは全て2桁にすること
 * 　※年も2桁で
 */
$config["FORCE_REDIRECT_TIMER"] = array(
	"START" => 0,					//開始(開始時刻設定無し)
	//"START" => strtotime('15-10-15 19:51:00'),	//開始
	"END" => 0					//終了(終了時刻設定無し)
	//"END" => strtotime('15-10-15 19:52:10')	//終了
);

?>
