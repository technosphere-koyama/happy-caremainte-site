<?php

/*
 * 画像がない場合に表示するダミー画像種類
 */
define('IMAGE_URI_TYPE_NO_IMAGE', 1);			//No Image
define('IMAGE_URI_TYPE_NO_IMAGE_NO_BORDER', 3);		//枠線なしの No Image
define('IMAGE_URI_TYPE_SIZE_IMAGE', 2);			//縦横サイズを表示した画像

$config["IMAGE_URI"] = array(
	"IS_ACTIVE" => true			//on/off
);

/*
 * 外部のサービスに、URLをぱーすしてプレースホルダーとなる画像を返してくれるサービスがある
 * 今回それを利用するので、それに関する設定を以下にて行う
 */
$config["IMAGE_PH_SIZE_IMAGE"] = array(
	"URL" => "https://placehold.jp/",	//さーびすURL
	"BG_COLOR" => "3d4070",			//背景色
	"COLOR" => "ffffff",			//文字色
	"EXT" => "png"				//拡張子
);
$config["IMAGE_PH_NO_IMAGE"] = array(
	"URL" => "https://placehold.jp/",	//さーびすURL
	"BG_COLOR" => "ffffff",			//背景色
	"COLOR" => "666666",			//文字色
	"EXT" => "png",				//拡張子
	"TEXT" => "No" . PHP_EOL . "Image",	//表示文字
	"CSS" => '{"height":"[HEIGHT]px", "border":"solid 1px #CCC"}'	//CSSで行間を調整
);
$config["IMAGE_PH_NO_IMAGE_NO_BORDER"] = array(
	"URL" => "https://placehold.jp/",	//さーびすURL
	"BG_COLOR" => "ffffff",			//背景色
	"COLOR" => "666666",			//文字色
	"EXT" => "png",				//拡張子
	"TEXT" => "No" . PHP_EOL . "Image",	//表示文字
	"CSS" => '{"height":"[HEIGHT]px"}'	//CSSで行間を調整
);

?>
