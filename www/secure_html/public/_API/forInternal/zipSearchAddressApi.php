<?php
require '../../../../core/PreLoad.inc';
$ajax = new ZipSearchAddressApiController();
$ajax->set_type(REQUEST::post_data('zipNumber'), REQUEST::post_data('countryCode'));
$ajax->exec();
?>
