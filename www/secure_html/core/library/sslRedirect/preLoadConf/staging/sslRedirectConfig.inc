<?php

/*
 * SSL REDIRECT
 * 
 * 80番アクセスの場合に443番へリダイレクトする処理
 * htaccessではなくPGで行う場合これを使用すること
 */

$config["SSL_REDIRECT"] = array(
	"IS_ACTIVE" => true,				//リダイレクトの on/off
	"TYPE" => SSL_RESTRICT_TYPE_SSL		//リダイレクトタイプ(80へ)
);

?>
