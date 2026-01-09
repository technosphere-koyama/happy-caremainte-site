<?php

/*
 * PHPの基本設定 
 */

/* ---------------------------------------
  MultiByteSet
  ---------------------------------------- */
define("CHARACTER_ENCODING", "UTF-8");
mb_language("ja");
mb_internal_encoding(CHARACTER_ENCODING);
mb_regex_encoding(CHARACTER_ENCODING);
mb_http_output(CHARACTER_ENCODING);

/* ---------------------------------------
  timezone setting
  ---------------------------------------- */
date_default_timezone_set("Asia/Tokyo");

/*
 * coreの場所はcore直下で行う必要があるのでここで
 */
define("DIR_CORE", dirname(__FILE__));

?>
