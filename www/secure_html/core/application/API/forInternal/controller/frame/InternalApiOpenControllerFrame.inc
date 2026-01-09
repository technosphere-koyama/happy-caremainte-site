<?php

/* * **********************************
 * NAME:InternalApiOpenControllerFrame
 * DESC:
 *  一般公開されているサイト側などオープンな環境に
 *  用いるAPI用コントローラのフレームとなる
 * NOTICE:
 *  ApiControllerCoreクラスを継承し、__construct()に子クラス名を
 *  渡し、Coreでログ出力などに使用してもらう
 * 
 *  コントローラの継承構造設計は、
 *  ApiController
 *  ↓
 *  ApiControllerFrame
 *  ↓
 *  ApiControllerCore
 *  となる
 * CREATE: 2015.10.04 hesaka
 * UPDATE: 2016.07.27 hesaka エラー判定をis_errorフラグ方式からApiErrorMessageMap方式へ
 * *********************************** */
class InternalApiOpenControllerFrame extends ApiControllerCore {

	/* * **********************************
	 * NAME  : __construct
	 * INPUT : NONE
	 * OUTPUT: NONE
	 * DESC  :
	 *  一般公開されているサイト側などオープンな環境に
	 *  用いるAPI用コントローラフレームのコンストラクタ
	 *  下記内容を処理する
	 *  
	 *  ・コアの起動
	 *  ・セッションスタート
	 *  ・各種認証(verification)など
	 *  ・言語判定
	 * NOTICE:
	 * --------------------------------------
	 *  当該フレーム定義に必要な認証は
	 *  コントローラではなくここで行う
	 * --------------------------------------
	 * CREATE: 2015.xx.xx hesaka
	 * *********************************** */
	public function __construct() {

		if (CONF::read('DEBUG_BAR.IS_ACTIVE')) DebugBarMaster::start_measure('controller_constructor', '【FRAME_CONSTRUCTOR】');
		
		/*
		 * セッション スタート
		 */
		SESSION::start();
		
		//子クラス名をControllerCoreに渡す
		parent::__construct(get_class($this));

		/*
		 * エラーメッセージ スタンバイ
		 * ※CURRENT_LANGUAGE define後にロードする必要が出たためここで
		 */
		$this->stand_by_error_message();

		if (CONF::read('DEBUG_BAR.IS_ACTIVE')) DebugBarMaster::stop_measure('controller_constructor');

	}

}

?>
