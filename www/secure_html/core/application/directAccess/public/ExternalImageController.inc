<?php

/* * **********************************
 * NAME:CatalogController
 * DESC:
 * 		カタログお取り寄せページのコントローラー
 * NOTICE:
 * CREATE: 2016.11.6 aoyama
 * *********************************** */
class ExternalImageController extends PublicOpenControllerFrame {

	private $sGroup;
	private $magArray;

	/* Constructor */
	public function __construct() {
		parent::__construct();
	}

	/*	 * **********************************
	 * NAME  : exec
	 * INPUT : 
	 * OUTPUT: 
	 * DESC  : 
	 * 		登録フォーム
	 * 		セッションにセットするのはここだけ。
	 * 		同時にバリデーションチェックも実施
	 * NOTICE:
	 * CREATE: 2016.10.16 aoyama
	 * *********************************** */
	public function exec() {
		
		// POSTデータがある場合、セッションに登録する。
		if ($this->checkSafeUrl(REQUEST::get_data('url'))) {
			
			$image = new Image();
			$image->get_external_image(REQUEST::get_data('url'));
		}
	}
	private function checkSafeUrl($url) {
		
		if(preg_match("/^https?:\/\/kh01\.kyoto\-happy\.co\.jp\//", $url)) {
			return true;
		}
		return false;
	}
	
}

?>
