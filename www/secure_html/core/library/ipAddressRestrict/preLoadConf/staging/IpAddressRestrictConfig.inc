<?php

/*
 * IP ADDRESS RESTRICT
 * 
 * ipアドレスによる、アクセス制限の設定
 * IS_ACTIVEをtrueにし、IP_LISTに許可するIPアドレスを
 * 入れれば、それら以外のアクセスが来た場合REDIRECT_URLに
 * 飛ぶようになる
 */

$config["IP_RESTRICT"] = array(
	"IS_ACTIVE" => false,							//IPアドレスによるアクセス制限の on/off
	"REDIRECT_URL" => CONF::read('URL_PUBLIC_ROOT') . "not_found.html"	//制限に引っかかった場合の飛ばし先URL
);

?>
