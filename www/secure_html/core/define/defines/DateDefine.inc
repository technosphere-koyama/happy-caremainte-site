<?php

/* ---------------------------------------
  Date
  ---------------------------------------- */
$date = new DateTime();
define("DATETIME_STR_YMD", $date->format('Y-m-d'));
define("DATETIME_INT_YMD", $date->format('Ymd'));
define("DATETIME_STR_Y", $date->format('Y'));
define("DATETIME_STR_Y_DIGIT_2", $date->format('y'));
define("DATETIME_STR_M", $date->format('m'));
define("DATETIME_STR_D", $date->format('d'));
/*
 * 秒が絡むものは、使用時とずれる可能性があるので定義しない
 * DbDateTimeに同じ機能のものがあるのでそちらで。。。
 */
//define("DATETIME_STR_YMDHIS", $date->format('Y-m-d H:i:s'));
//define("DATETIME_INT_YMDHIS", date("YmdHis"));

?>
