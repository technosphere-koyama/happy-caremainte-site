<?php

require_once(dirname(__FILE__) . '/lib/qrcode_img.php');


/* * **********************************
 * NAME:Qr
 * DESC:
 *  QRコード生成クラス
 * NOTICE:
 * CREATE: 2016.09.05 aoyama
 * *********************************** */
class Qr extends Qrcode_image {
	
	/* Constructor */
	public function __construct() {
	}

	/*	 * **********************************
	 * NAME  : makeQr
	 * INPUT : GET::s
	 * OUTPUT: 画像データ
	 * DESC  :
	 * サイズ指定
	 * #3:87
	 * #4:116
	 * #5:145
	 * #6:174
	 * バージョン設定
	 * #$z->set_qrcode_version(1);           # set qrcode version 1
	 * NOTICE:
	 * CREATE: 2016.09.05 aoyama
	 * UPDATE: 2016.10.11 aoyama
	 *		?s=http://～～/?s=[文字列]としてパラメータを渡すとpng出力される
	 * *********************************** */
	public function makeQr($text) {
		Header("Content-type: image/png");

		$z = new Qrcode_image;
		$z->set_module_size(3);
		$z->qrcode_image_out($text, "png");
	}
}
