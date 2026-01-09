<?php

//$file = dirname(__FILE__)."/../core/tmp/session/";


date_default_timezone_set('Asia/Tokyo');

//削除期限
$expire = strtotime("1 months ago");
//$expire = strtotime("1 minute ago");

//ディレクトリ
//$dir = dirname(__FILE__) . '/dir/';
$dir = dirname(__FILE__)."/../core/tmp/session/";



$list = scandir($dir);



foreach($list as $value){
    $file = $dir . $value;
    if(!is_file($file)) continue;
    $mod = filemtime( $file );
    if($mod < $expire){
        chmod($file, 0666);
        unlink($file);
    }
}

/*
while ($strFile = readdir($strDir)) {
	if ($strFile != '.' && $strFile != '..') {
		unlink($file . '/' . $strFile);
	}
}
rmdir($file);
*/
