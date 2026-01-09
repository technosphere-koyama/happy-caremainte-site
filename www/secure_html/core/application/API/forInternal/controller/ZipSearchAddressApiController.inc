<?php

/* * **********************************
 * NAME:ZipSearchAddressApiController
 * DESC:
 *  郵便番号から住所検索用のAjaxコントローラ
 * NOTICE: set_typeでセットされた郵便番号に対して、住所検索を行う。
 * CREATE: 2015.10.26 sonoda
 * *********************************** */
class ZipSearchAddressApiController extends InternalApiOpenControllerFrame {

	private $type = "";
	private $code = "";
	private $sGroup;

	/* Constructor */
	public function __construct() {
		parent::__construct();
		$this->sGroup = 'customerRegistApi';
	}

	/*	 * **********************************
	 * NAME  : set_type
	 * INPUT : NONE
	 * OUTPUT: NONE
	 * DESC  :
	 * NOTICE:
	 * CREATE: 2015.10.26 sonoda
	 * *********************************** */
	public function set_type($type, $code) {
		$this->type = $type;
		$this->code = $code;
	}

	/*	 * **********************************
	 * NAME  : exec
	 * INPUT : NONE
	 * OUTPUT: NONE
	 * DESC  :
	 * NOTICE:
	 * CREATE: 2015.10.26 sonoda
	 * *********************************** */
	public function exec() {

		//アクセス制限チェック
//		if ($this->get_is_error()) {
//			//制限に引っかかったら不正なアクセスと判断してfalseを返す
//			$this->set('result', false);
//			print $this->json_decode();
//			return;
//		}
		/*
		 * 対象テーブル用のモデルを生成
		 */
		switch (REQUEST::get_data('md')) {

			//番号検索
			case 'single':
				$this->get_address_post();
				break;

			case 'roman':
				$this->get_address_roman_post();
				break;

			default:
				print 'error:エラーが発生しました';
		}

	}

	/*	 * **********************************
	 * NAME  : get_address_post
	 * INPUT : NONE
	 * OUTPUT: NONE
	 * DESC  :
	 * NOTICE:
	 * CREATE: 2015.10.26 sonoda
	 * *********************************** */
	public function get_address_post() {

		//入力された場合の挙動
		if (REQUEST::is_post()) {
			//番号検索を行う。
			$db = new ZipSearchAddress();
			$db->get_address_data($this->type, $this->code);
		}
	}

	/*	 * **********************************
	 * NAME  : get_address_romman_post
	 * INPUT : NONE
	 * OUTPUT: NONE
	 * DESC  :
	 * NOTICE:
	 * CREATE: 2015.10.26 sonoda
	 * *********************************** */
	public function get_address_roman_post() {

		//入力された場合の挙動
		if (REQUEST::is_post()) {
			//番号検索を行う。
			$db = new ZipSearchAddress();
			$db->get_address_roman_data($this->type, $this->code);
		}
	}
}

?>
