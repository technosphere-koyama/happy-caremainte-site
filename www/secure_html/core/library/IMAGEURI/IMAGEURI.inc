<?php

/* * **********************************
 * NAME:IMAGEURI
 * DESC:
 *  画像URL計算用ライブラリ
 *
 *  画像数が膨大になる可能性がある場合、
 *  ディレクトリの構成を考える必要がある
 *  ※32bitOSの場合、1ディレクトリに保存できる最大数が
 *  　65535となるからである
 * 
 *  画像の種類によって、それぞれルールを設けて
 *  URIを計算する
 *   
 * NOTICE:
 * CREATE: 2015.11.16 hesaka
 * *********************************** */
class IMAGEURI {

	/* * **********************************
	 * NAME  : item
	 * INPUT : width / integer / 横幅
	 *         height / integer / 縦幅
	 *         type / integer / 画像タイプ 
	 *         detail_path / string / 追加パス(追加する必要があれば)
	 *         item_id / string / 商品ID
	 *         number / integer / 連番(追加する必要があれば)
	 *         extension / string / 拡張子
	 * OUTPUT: string / ドメインからのフルパス
	 * DESC  :
	 *  商品画像のURLを返す
	 *  例としては以下のようになる
	 *  http://demo-shop.com/_ASSETS/images/item/1/0001/<detail_path>/<number>.<extension>
	 * 
	 * NOTICE:
	 *  商品画像のディレクトリ構成は以下の仕組みとなる
	 * 
	 *  public/_ASSETS/images/item/<1桁からのカウンタ(0オリジン)>/<0000～9999>/
	 * 
	 *  1ディレクトリに最大1万ディレクトリ・ファイルとなるよう、
	 *  1万ディレクトリ毎に区切ることにした
	 *  これであれば、item直下ディレクトリがオーバフローするのに必要な商品数は
	 *  65535 x 10000となり、更に下の階層は1万を超えることがなく、その下の階層でも
	 *  各商品で画像が6万をこえなければ問題ないということになる
	 * 
	 *  また、その数値を決定するものは商品ID(インクリメンタルカウンタ)により判断する
	 * 
	 *  0～9999		→ 0/0000～9999
	 *  10000～19999		→ 1/0000～9999
	 *  という感じになる
	 * 
	 * ------------------------------------------------------
	 *  プレースホルダー画像が欲しいだけなら、width, heightのみ
	 *  引数に指定すれば取得できる
	 * ------------------------------------------------------
	 * CREATE: 2015.11.17 hesaka
	 * UPDATE: 2015.12.09 hesaka 画像名を<system_id>_<number>.<ext>から<number>.<ext>に変更した
	 *                           ※LIMEさまからもらう画像がitem_id依存なため
	 * *********************************** */
	public static function item($width, $height, $type = IMAGE_URI_TYPE_NO_IMAGE, 
					$detail_path = '', $item_id = NULL, $number = 1, $extension = NULL) {

		//width, heightが空の場合はエラー
		if (StaticFunction::is_empty($width) || StaticFunction::is_empty($height)) {
			return NULL;
		}

		//item_id, extensionが指定無しの場合は、画像URL作れないので、プレースホルダー画像URLを返す
		if (StaticFunction::is_empty($item_id)
			|| StaticFunction::is_empty($extension)
		) {
			//exp:https://placehold.jp/3d4070/ffffff/38x50.png
			return self::get_placehold_uri($width, $height, $type);
		}

		return CONF::read('URL_PUBLIC_ROOT') . '_ASSETS/images/item/' . 
			self::get_item_detail_path($item_id) . 
			(($detail_path) ? ($detail_path . '/') : ('')) . 
			(($number !== NULL && strlen((string)$number) > 0) ? ($number) : (1)) . 
			'.' . $extension;
	}

	/* * **********************************
	 * NAME  : event
	 * INPUT : width / integer / 横幅
	 *         height / integer / 縦幅
	 *         type / integer / 画像タイプ
	 *         detail_path / string / 追加パス(追加する必要があれば)
	 *         item_id / string / 商品ID
	 *         number / integer / 連番(追加する必要があれば)
	 *         extension / string / 拡張子
	 * OUTPUT: string / ドメインからのフルパス
	 * DESC  :
	 *  商品画像のURLを返す
	 *  例としては以下のようになる
	 *  http://demo-shop.com/_ASSETS/images/event/1/0001/<detail_path>/<number>.<extension>
	 *
	 * NOTICE:
	 *  商品画像のディレクトリ構成は以下の仕組みとなる
	 *
	 *  public/_ASSETS/images/item/<1桁からのカウンタ(0オリジン)>/<0000～9999>/
	 *
	 *  1ディレクトリに最大1万ディレクトリ・ファイルとなるよう、
	 *  1万ディレクトリ毎に区切ることにした
	 *  これであれば、item直下ディレクトリがオーバフローするのに必要な商品数は
	 *  65535 x 10000となり、更に下の階層は1万を超えることがなく、その下の階層でも
	 *  各商品で画像が6万をこえなければ問題ないということになる
	 *
	 *  また、その数値を決定するものは商品ID(インクリメンタルカウンタ)により判断する
	 *
	 *  0～9999		→ 0/0000～9999
	 *  10000～19999		→ 1/0000～9999
	 *  という感じになる
	 *
	 * ------------------------------------------------------
	 *  プレースホルダー画像が欲しいだけなら、width, heightのみ
	 *  引数に指定すれば取得できる
	 * ------------------------------------------------------
	 * CREATE: 2016.10.05 sonoda itemをベースにevent用の関数を作成
	 * *********************************** */
	public static function event($width, $height, $type = IMAGE_URI_TYPE_NO_IMAGE,
					$detail_path = '', $item_id = NULL, $number = 1, $extension = NULL) {

		//width, heightが空の場合はエラー
		if (StaticFunction::is_empty($width) || StaticFunction::is_empty($height)) {
			return NULL;
		}

		//item_id, extensionが指定無しの場合は、画像URL作れないので、プレースホルダー画像URLを返す
		if (StaticFunction::is_empty($item_id)
			|| StaticFunction::is_empty($extension)
		) {
			//exp:https://placehold.jp/3d4070/ffffff/38x50.png
			return self::get_placehold_uri($width, $height, $type);
		}

		return CONF::read('URL_PUBLIC_ROOT') . '_ASSETS/images/event/' .
			self::get_item_detail_path($item_id) .
			(($detail_path) ? ($detail_path . '/') : ('')) .
			(($number !== NULL && strlen((string)$number) > 0) ? ($number) : (1)) .
			'.' . $extension;
	}

	/* * **********************************
	 * NAME  : item_save_path
	 * INPUT : item_id / string / 商品ID
	 *         detail_path / string / 追加パス(追加する必要があれば)
	 * OUTPUT: string / ドメインからのフルパス
	 * DESC  :
	 *  商品画像の保存先パスを返す
	 * NOTICE:
	 * CREATE: 2015.11.18 hesaka
	 * *********************************** */
	public static function item_save_path($item_id = NULL, $detail_path = NULL) {

		//item_idが空の場合はエラー
		if (StaticFunction::is_empty($item_id)) {
			return NULL;
		}
		
		return DIR_PUBLIC_IMG . '/item/' . 
			self::get_item_detail_path($item_id) . 
			(($detail_path) ? ($detail_path . '/') : (''));
	}

	/* * **********************************
	 * NAME  : event_save_path
	 * INPUT : event_id / string / イベントID
	 *         detail_path / string / 追加パス(追加する必要があれば)
	 * OUTPUT: string / ドメインからのフルパス
	 * DESC  :
	 *  イベント画像の保存先パスを返す
	 * NOTICE:
	 * CREATE: 2016.10.05 sonoda
	 * *********************************** */
	public static function event_save_path($event_id = NULL, $detail_path = NULL) {

		//event_idが空の場合はエラー
		if (StaticFunction::is_empty($event_id)) {
			return NULL;
		}

		return DIR_PUBLIC_IMG . '/event/' .
			self::get_item_detail_path($event_id) .
			(($detail_path) ? ($detail_path . '/') : (''));
	}

	/* * **********************************
	 * NAME  : brand_save_path
	 * INPUT : brand_id / string / ブランドID
	 *         detail_path / string / 追加パス(追加する必要があれば)
	 * OUTPUT: string / ドメインからのフルパス
	 * DESC  :
	 *  ブランド画像の保存先パスを返す
	 * NOTICE:
	 * CREATE: 2016.01.20 sonoda
	 * *********************************** */
	public static function brand_save_path($detail_path = NULL) {

		//item_idが空の場合はエラー
		if (StaticFunction::is_empty($detail_path)) {
			return NULL;
		}

		return DIR_PUBLIC_IMG . '/brand/' .
			(($detail_path) ? ($detail_path . '/') : (''));
	}

	/* * **********************************
	 * NAME  : top_slide_save_path
	 * INPUT : NONE
	 * OUTPUT: string / ドメインからのフルパス
	 * DESC  :
	 *  トップスライド画像の保存先パスを返す
	 * NOTICE:
	 * CREATE: 2016.03.08 hesaka
	 * *********************************** */
	public static function top_slide_save_path() {
		return DIR_PUBLIC . '/images/topics/';
	}
	
	/* * **********************************
	 * NAME  : feature
	 * INPUT : width / integer / 横幅
	 *         height / integer / 縦幅
	 *         type / integer / 画像タイプ 
	 *         detail_path / string / 追加パス(追加する必要があれば)
	 *         feature_id / string / 特集のシステムID
	 *         extension / string / 拡張子
	 * OUTPUT: string / ドメインからのフルパス
	 * DESC  :
	 *  特集画像のURLを返す
	 *  例としては以下のようになる
	 *  http://demo-shop.com/_ASSETS/images/feature/<detail_path>/<sysmte_id>.<extension>
	 * 
	 * NOTICE:
	 * ------------------------------------------------------
	 *  プレースホルダー画像が欲しいだけなら、width, heightのみ
	 *  引数に指定すれば取得できる
	 * ------------------------------------------------------
	 * CREATE: 2015.11.17 hesaka
	 * UPDATE: 2015.12.09 hesaka 画像名をsystem_idからfeature_idに変更
	 * *********************************** */
	public static function feature($width, $height, $type = IMAGE_URI_TYPE_NO_IMAGE,
					$detail_path = '', $feature_id = NULL, $extension = NULL) {

		//width, heightが空の場合はエラー
		if (StaticFunction::is_empty($width) || StaticFunction::is_empty($height)) {
			return NULL;
		}

		//feature_id, extensionが指定無しの場合は、画像URL作れないので、プレースホルダー画像URLを返す
		if (StaticFunction::is_empty($feature_id) || StaticFunction::is_empty($extension)) {
			//exp:https://placehold.jp/3d4070/ffffff/38x50.png
			return self::get_placehold_uri($width, $height, $type);
		}

		return CONF::read('URL_PUBLIC_ROOT') . '_ASSETS/images/feature/' . 
			(($detail_path) ? ($detail_path . '/') : ('')) . $feature_id . '.' . $extension;
	}
	
	/* * **********************************
	 * NAME  : brand
	 * INPUT : width / integer / 横幅
	 *         height / integer / 縦幅
	 *         type / integer / 画像タイプ 
	 *         detail_path / string / 追加パス(追加する必要があれば)
	 *         brand_id / string / ブランドID
	 *         extension / string / 拡張子
	 * OUTPUT: string / ドメインからのフルパス
	 * DESC  :
	 *  ブランド画像のURLを返す
	 *  例としては以下のようになる
	 *  http://demo-shop.com/_ASSETS/images/brand/<detail_path>/<brand_id>.<extension>
	 * 
	 * NOTICE:
	 * ------------------------------------------------------
	 *  プレースホルダー画像が欲しいだけなら、width, heightのみ
	 *  引数に指定すれば取得できる
	 * ------------------------------------------------------
	 * 
	 * !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	 * system_idではなく、brand_idをファイル名に使用する
	 * データ移植を考えると、DBにデータをインサートする度に
	 * 値が変わってしまうシステムIDは面倒
	 * インクリメンタルIDであれば、さらから入れなおす分には
	 * 綺麗である
	 * !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	 * 
	 * CREATE: 2015.11.30 hesaka
	 * *********************************** */
	public static function brand($width, $height, $type = IMAGE_URI_TYPE_NO_IMAGE,
					$detail_path = '', $brand_id = NULL, $extension = NULL) {

		//width, heightが空の場合はエラー
		if (StaticFunction::is_empty($width) || StaticFunction::is_empty($height)) {
			return NULL;
		}

		//brand_id, extensionが指定無しの場合は、画像URL作れないので、プレースホルダー画像URLを返す
		if (StaticFunction::is_empty($brand_id) || StaticFunction::is_empty($extension)) {
			//exp:https://placehold.jp/3d4070/ffffff/38x50.png
			return self::get_placehold_uri($width, $height, $type);
		}

		return CONF::read('URL_PUBLIC_ROOT') . '_ASSETS/images/brand/' . 
			(($detail_path) ? ($detail_path . '/') : ('')) . $brand_id . '.' . $extension;
	}

	/* * **********************************
	 * NAME  : top_slide
	 * INPUT : width / integer / 横幅
	 *         height / integer / 縦幅
	 *         type / integer / 画像タイプ 
	 *         slide_id / string / スライドID
	 *         extension / string / 拡張子
	 * OUTPUT: string / ドメインからのフルパス
	 * DESC  :
	 *  トップページのスライドショー画像のURLを返す
	 *  例としては以下のようになる
	 *  http://demo-shop.com/images/topics/<slide_id>.<extension>
	 * 
	 * NOTICE:
	 * ------------------------------------------------------
	 *  プレースホルダー画像が欲しいだけなら、width, heightのみ
	 *  引数に指定すれば取得できる
	 * ------------------------------------------------------
	 * 
	 * !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	 * system_idではなく、slide_idをファイル名に使用する
	 * データ移植を考えると、DBにデータをインサートする度に
	 * 値が変わってしまうシステムIDは面倒
	 * インクリメンタルIDであれば、さらから入れなおす分には
	 * 綺麗である
	 * !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	 * 
	 * CREATE: 2016.03.08 hesaka
	 * *********************************** */
	public static function top_slide($width, $height, $type = IMAGE_URI_TYPE_NO_IMAGE,
					$slide_id = NULL, $extension = NULL) {

		//width, heightが空の場合はエラー
		if (StaticFunction::is_empty($width) || StaticFunction::is_empty($height)) {
			return NULL;
		}

		//slide_id, extensionが指定無しの場合は、画像URL作れないので、プレースホルダー画像URLを返す
		if (StaticFunction::is_empty($slide_id) || StaticFunction::is_empty($extension)) {
			//exp:https://placehold.jp/3d4070/ffffff/38x50.png
			return self::get_placehold_uri($width, $height, $type);
		}

		return CONF::read('URL_PUBLIC_ROOT') . 'images/topics/' . 
			$slide_id . '.' . $extension;
	}
	
	/* * **********************************
	 * NAME  : get_item_detail_path
	 * INPUT : item_id / string / 商品ID
	 * OUTPUT: string / 商品IDによって決まる詳細ディレクトリパス
	 * DESC  :
	 *  指定商品IDにより詳細ディレクトリパスを決定して返す
	 * NOTICE:
	 * CREATE: 2015.11.18 hesaka
	 * *********************************** */
	private static function get_item_detail_path($item_id) {

		$str = str_pad((string)$item_id, 5, '0', STR_PAD_LEFT);

		return mb_substr($str, 0, (mb_strlen($str) - 4)) . '/' . mb_substr($str, -4) . '/';
	}
	
	/* * **********************************
	 * NAME  : get_placehold_uri
	 * INPUT : width / integer / 横幅
	 *         height / integer / 縦幅
	 *         type / integer / 画像タイプ
	 * OUTPUT: string / ドメインからのフルパス
	 * DESC  :
	 *  指定サイズのプレースホールド画像のURLを返す
	 * NOTICE:
	 * CREATE: 2015.11.17 hesaka
	 * UPDATE: 2016.03.07 hesaka 枠線なしのNO_IMAGE(NO_IMAGE_NO_BORDER)を追加
	 * *********************************** */
	private static function get_placehold_uri($width, $height, $type) {

		switch ($type) {

			//SIZE_IMAGE
			case IMAGE_URI_TYPE_SIZE_IMAGE:
				return CONF::read('IMAGE_PH_SIZE_IMAGE.URL') . 
					CONF::read('IMAGE_PH_SIZE_IMAGE.BG_COLOR') . '/' . 
					CONF::read('IMAGE_PH_SIZE_IMAGE.COLOR') . '/' . 
					$width . 'x' . $height . '.' . CONF::read('IMAGE_PH_SIZE_IMAGE.EXT');

			//NO_IMAGE_NO_BORDER
			case IMAGE_URI_TYPE_NO_IMAGE_NO_BORDER:
				return CONF::read('IMAGE_PH_NO_IMAGE_NO_BORDER.URL') . 
					CONF::read('IMAGE_PH_NO_IMAGE_NO_BORDER.BG_COLOR') . '/' . 
					CONF::read('IMAGE_PH_NO_IMAGE_NO_BORDER.COLOR') . '/' . 
					$width . 'x' . $height . '.' . CONF::read('IMAGE_PH_NO_IMAGE_NO_BORDER.EXT') . 
					'?text=' . urlencode(CONF::read('IMAGE_PH_NO_IMAGE_NO_BORDER.TEXT')) . 
					'&css=' . urlencode(str_replace('[HEIGHT]', ($height - 2), CONF::read('IMAGE_PH_NO_IMAGE_NO_BORDER.CSS')));

			//NO_IMAGE
			case IMAGE_URI_TYPE_NO_IMAGE:
			//指定がない場合もNO_IMAGEを表示する
			default:
				return CONF::read('IMAGE_PH_NO_IMAGE.URL') . 
					CONF::read('IMAGE_PH_NO_IMAGE.BG_COLOR') . '/' . 
					CONF::read('IMAGE_PH_NO_IMAGE.COLOR') . '/' . 
					$width . 'x' . $height . '.' . CONF::read('IMAGE_PH_NO_IMAGE.EXT') . 
					'?text=' . urlencode(CONF::read('IMAGE_PH_NO_IMAGE.TEXT')) . 
					'&css=' . urlencode(str_replace('[HEIGHT]', ($height - 2), CONF::read('IMAGE_PH_NO_IMAGE.CSS')));
		}
	}

	/* * **********************************
	 * NAME  : item
	 * INPUT : width / integer / 横幅
	 *         height / integer / 縦幅
	 *         type / integer / 画像タイプ 
	 *         detail_path / string / 追加パス(追加する必要があれば)
	 *         item_id / string / 商品ID
	 *         number / integer / 連番(追加する必要があれば)
	 *         extension / string / 拡張子
	 * OUTPUT: string / ドメインからのフルパス
	 * DESC  :
	 *  商品画像のURLを返す
	 *  例としては以下のようになる
	 *  http://demo-shop.com/_ASSETS/images/item/1/0001/<detail_path>/<number>.<extension>
	 * 
	 * NOTICE:
	 *  商品画像のディレクトリ構成は以下の仕組みとなる
	 * 
	 *  public/_ASSETS/images/item/<1桁からのカウンタ(0オリジン)>/<0000～9999>/
	 * 
	 *  1ディレクトリに最大1万ディレクトリ・ファイルとなるよう、
	 *  1万ディレクトリ毎に区切ることにした
	 *  これであれば、item直下ディレクトリがオーバフローするのに必要な商品数は
	 *  65535 x 10000となり、更に下の階層は1万を超えることがなく、その下の階層でも
	 *  各商品で画像が6万をこえなければ問題ないということになる
	 * 
	 *  また、その数値を決定するものは商品ID(インクリメンタルカウンタ)により判断する
	 * 
	 *  0～9999		→ 0/0000～9999
	 *  10000～19999		→ 1/0000～9999
	 *  という感じになる
	 * 
	 * ------------------------------------------------------
	 *  プレースホルダー画像が欲しいだけなら、width, heightのみ
	 *  引数に指定すれば取得できる
	 * ------------------------------------------------------
	 * CREATE: 2015.11.17 hesaka
	 * UPDATE: 2015.12.09 hesaka 画像名を<system_id>_<number>.<ext>から<number>.<ext>に変更した
	 *                           ※LIMEさまからもらう画像がitem_id依存なため
	 * *********************************** */
	public static function insta($id){

		//width, heightが空の場合はエラー
		if (StaticFunction::is_empty($id)) {
			return NULL;
		}

		return CONF::read('URL_PUBLIC_ROOT') . 'images/insta/' . $id . '.jpg';
	}

}

?>
