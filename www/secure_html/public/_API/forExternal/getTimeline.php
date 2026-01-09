<?php
require $_SERVER['DOCUMENT_ROOT'] . '/../core/PreLoad.inc';
$ajax = new TimelineApiController();
$ajax->exec();

