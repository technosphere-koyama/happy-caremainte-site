<?php


//$file = dirname(__FILE__)."/../core/tmp/directoryList";
$file = dirname(__FILE__)."/wp/wp-content/themes/HAPPY_Dark/img";
//$file = dirname(__FILE__)."/wp/wp-content/themes/HAPPY_Dark";

$strDir = opendir($file);

while ($strFile = readdir($strDir)) {
	if ($strFile != '.' && $strFile != '..') {
		if (chmod($file."/".$strFile,0777)) {
			echo "ok";
		}
	}
}




//usr/bin/php /home/www/secure_html/core/application/cron/CronController.inc env=staging class=LatestCareApi





//	$file = dirname(__FILE__)."/wp/wp-content/themes/HAPPY_Dark/css";
//	if (chmod($file,0777)) {
//		echo "ok";
//	}
