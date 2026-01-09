<?php

//$file = dirname(__FILE__)."/wp/wp-config.php";

$file = dirname(__FILE__)."/../core/tmp/directoryList";

if ( chown( $file,"www" )) {
    echo "オーナー「user01」変更成功！！";
} else {
    echo "オーナー「user01」変更失敗！！";
}
