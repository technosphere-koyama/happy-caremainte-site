<?php

/* * **********************************
 * NAME:ZipSearchAddress
 * DESC:
 * 	郵便番号から、住所を検索する。
 *  json形式で以下のように返す。
 *
 * NOTICE:
 * CREATE: 2015.10.26 sonoda
 * *********************************** */
class ZipSearchAddress {

	/* Constructor */
	public function __construct() {
		$this->url = CONF::read('ZIP_SEARCH_ADDRESS.URL');
//		$this->get_address_data();
	}

	/*	 * **********************************
	 * NAME  : get_address_data
	 * INPUT : NONE
	 * OUTPUT: NONE
	 * DESC  :
	 *  POSTで要求された郵便番号から、アドレスを検索する。
	 *  国外対応(国内チェックと桁数チェックを無効)
	 * NOTICE:
	 * CREATE: 2016.08.05 sonoda
	 * *********************************** */
	public function get_address_data($postNumber, $countryCode) {
		$cm = new CountryModel();

		$returnArray = array(
			'address' => '',
		);

		/*
		 * 日本語で一旦住所検索をして、郵便番号に該当する国コードを取得する処理。
		 * 今回はセレクトでユーザが指定する形にしたので、ここの処理は不要。
		 *
		$googleMapsApiData = json_decode(@file_get_contents($this->url . $postNumber . '&language=ja'), true);
		//結果チェック
		if ($googleMapsApiData['status'] !== 'OK') {
			echo "指定された郵便番号は、存在しません。(取得エラー)";
			return false;
		}

		$addressArray = $googleMapsApiData['results'][0]['address_components'];

		//国情報を取得する。
		foreach ($addressArray as $key => $val) {
			if($val['types'][0] == 'country') {
				$country = $val;
				break;
			}
		}

		$returnArray['country_name'] = $country['long_name'];
		$country_code = $country['short_name'];
		 */

		//国の第一言語を取得する。
		$lang_data = $cm->get_country_lang($countryCode);
//		echo $lang_data[0]['lang_code'];
		if ($cm->db_select_check_empty($lang_data) ||
			$cm->db_select_check_error($lang_data)) {
			echo $countryCode . ' empty';
			return false;
		}

		/*
		 * 選択された国コードでjsonを実行する。
		 */
		$local_data = json_decode(@file_get_contents($this->url . urlencode($postNumber) . '&language=' . $lang_data[0]['lang_code']), true);
//		var_dump($local_data);

		/*
		 * addresscomponemtsから住所を取得する場合
		 */
		//addresscomponentsの数を確認して、
		//複数ある場合
		//・選択した国のものを優先する。
		//・選択した国がなければ、一番上。
		//一つだけの場合は、それを表示する。
		$tml_address = $local_data['results'][0]['address_components'];

		if (count($local_data['results']) != 1) {
			foreach ($local_data['results'] AS $record_key => $record_val) {
				foreach (($record_val['address_components']) AS $key => $val) {
					if ($val['short_name'] == $countryCode) {
						$tml_address = $local_data['results'][$record_key]['address_components'];
						break;
					}
				}
			}
		}
//		var_dump($tml_address);
		//typeがpostalcodeかcountryであれば、
		//住所として不要な情報なので対象外とする。
		foreach ($tml_address as $key => $val) {
			if ($val['types'][0] != 'country' && $val['types'][0] != 'postal_code') {
				$local_address[] = $val;
			}
		}

		$local_address = array_reverse($local_address);

		//住所を配列に格納していく
		foreach ($local_address as $v) {
			$returnArray['address'] .= $v['long_name'] . ' ';
		}

		/*
		 * formatted_addressから住所を取得する場合
		 * 日本の住所検索とかすると郵便番号と日本という文字列だけしか返ってこない。
		 *  〒573-0071, 日本
		 * なので、こっちはなしかな。
		  $returnArray['municipal'] =$local_data['results'][0]['formatted_address'];
		 */

		echo json_encode($returnArray);
	}

	/*	 * **********************************
	 * NAME  : get_address_roman_data
	 * INPUT : NONE
	 * OUTPUT: NONE
	 * DESC  :
	 *  POSTで要求された郵便番号から、アドレスを検索する。
	 *  合わせて、ローマ字表示も返す。
	 * NOTICE:
	 * UPDATE: 2016.08.05 sonoda 国外対応(国内チェックと桁数チェックを無効)
	 * *********************************** */
	public function get_address_roman_data($postNumber, $countryCode) {
		$cm = new CountryModel();

		$returnArray = array(
			'local' => array('address' => ''),
			'roman' => array('address' => '')
		);

		//国の第一言語を取得する。
		$lang_data = $cm->get_country_lang($countryCode);
		if ($cm->db_select_check_empty($lang_data) ||
			$cm->db_select_check_error($lang_data)) {
			echo $countryCode . ' empty';
			return false;
		}

//		echo $lang_data[0]['lang_code'];

		/*
		 * 国コードでjsonを実行する。
		 */
		$local_data = json_decode(@file_get_contents($this->url . $postNumber . '&language=' . $lang_data[0]['lang_code']), true);
		$local_result = $this->parce_address($local_data, $countryCode);
		if ($local_result == false) {
			return false;
		}

		/*
		 * ローマ字表記のデータ取得
		 */
		$roman_data = json_decode(@file_get_contents($this->url . $postNumber . '&language=en'), true);
		$roman_result = $this->parce_address($roman_data,  $countryCode);
		if ($roman_result == false) {
			return false;
		}

		$returnArray['local']['address'] = $local_result;
		$returnArray['roman']['address'] = $roman_result;

		echo json_encode($returnArray);
	}

	/*	 * **********************************
	 * NAME  : parce_address
	 * INPUT : NONE
	 * OUTPUT: NONE
	 * DESC  : GoogleMapApiの実行結果からaddress情報をパースする。
	 * NOTICE:
	 * UPDATE: 2016.08.05 sonoda
	 * *********************************** */
	static function parce_address($address_data, $countryCode) {

		$address = '';

		/*
		 * addresscomponemtsから住所を取得する場合
		 */
		//addresscomponentsの数を確認して、
		//複数ある場合
		//・選択した国のものを優先する。
		//・選択した国がなければ、一番上。
		//一つだけの場合は、それを表示する。
		$tml_address = $address_data['results'][0]['address_components'];

		if (count($address_data['results']) != 1) {
			foreach ($address_data['results'] AS $record_key => $record_val) {
				foreach (($record_val['address_components']) AS $key => $val) {
					if ($val['short_name'] == $countryCode) {
						$tml_address = $address_data['results'][$record_key]['address_components'];
						break;
					}
				}
			}
		}
//		var_dump($tml_address);
		//typeがpostalcodeかcountryであれば、
		//住所として不要な情報なので対象外とする。
		foreach ($tml_address as $key => $val) {
			if ($val['types'][0] != 'country' && $val['types'][0] != 'postal_code') {
				$local_address[] = $val;
			}
		}

		$local_address = array_reverse($local_address);

		//住所を配列に格納していく
		foreach ($local_address as $v) {
			$address .= $v['long_name'] . ' ';
		}

		/*
		 * formatted_addressから住所を取得する場合
		 * 日本の住所検索とかすると郵便番号と日本という文字列だけしか返ってこない。
		 *  〒573-0071, 日本
		 * なので、こっちはなしかな。
		  $returnArray['municipal'] =$local_data['results'][0]['formatted_address'];
		 */

		return $address;
	}

	/*	 * **********************************
	 * NAME  : check_zip_format
	 * INPUT : country_code / string / 国コード
	 * OUTPUT: true or false
	 * DESC  : 指定された国コードのフォーマとに従った
	 *  zpiコードかどうかチェックする。
	 * NOTICE:
	 * UPDATE: 2016.08.31 sonoda
	 * *********************************** */
	static function check_zip_format($post_number, $country_code) {

		//郵便番号が空ならエラー
		if(StaticFunction::is_empty($post_number) ||
			StaticFunction::is_empty($country_code === NULL)){
			return false;
		}

		switch ($country_code) {
			case 'jp':
				if (preg_match('/^\d{5}$/', $post_number) !== 1) {
					$result = false;
				} else {
					$result = true;
				}
				break;

			default:
				$result = false;
				break;
		}

		return $result;

	}

}

?>
