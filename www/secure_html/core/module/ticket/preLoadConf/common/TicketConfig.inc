<?php

$config["TICKET"] = array(
	"NUMBER_OF_DIGITS" => 4,		//1ブロックの桁数
	"NUMBER_OF_BLOCKS" => 4,		//ブロック数
	"GENERATE_RETRY_TIMES" => 80,		//制限に抵触した際のリトライ上限
	"DESTROY_TIMING" => 3			//使用タイミングから何か月後に削除するか
);

?>
