<?php

/* * **********************************
 * NAME:FashionTypeMasterModel
 * DESC:
 *  ファッション系統マスターテーブル用モデルクラス
 * NOTICE:
 *  基本的にはDbShellクラスを継承し、そちらでPDOインスタンスアクセスを行う
 *  場合によっては当該クラスで直接触ることもあるかも知れないが、
 *  できるだけDbShellクラスにて行うこと！
 * CREATE: 2016.10.14 aoyama
 * *********************************** */
class FashionTypeMasterModel extends DbShell {

	private $table_name = "fashion_type_master";

	public function __construct() {
		parent::__construct();
	}

	/*	 * **********************************
	 * NAME  : get_basic_data
	 * INPUT : NONE
	 * OUTPUT: array / データ
	 * DESC  :
	 *  ファッション系統の全リストを取得する
	 * NOTICE:
	 * CREATE: 2016.10.14 aoyama
	 * *********************************** */
	public function get_basic_data() {

		$fashionArray = $this->query('
			SELECT
				ftm.fashion_id,
				ftm.fashion_name
			FROM
				' . DbCast::table_name($this->table_name) . ' AS ftm
			ORDER BY sort_num
		');
		foreach ($fashionArray AS $val) {
			$ret[$val['fashion_id']] = $val['fashion_name'];
		}
		return $ret;
	}

	/*	 * **********************************
	 * NAME  : verify_datetime
	 * INPUT : start / string / 開始日時
	 *         end / string / 終了日時
	 *         cur_datetime / string / 現在日時
	 * OUTPUT: true / 制限対象内
	 *         false / 制限対象外
	 * DESC  :
	 *  現在日時(cur_datetime)が、start_time, end_time判定により
	 *  指定制限対象かどうかを判定する
	 * NOTICE:
	 *  start指定があるがend指定がない場合はstart以降はずっと対象内となる
	 *  逆もまたしかり
	 *  ただし、どちらも指定がない場合は、対象外となる
	 * CREATE: 2015.11.23 hesaka
	 * *********************************** */
	private function verify_datetime($start, $end, $cur_datetime) {

		//開始、終了両方指定がない場合は対象外となる
		if (StaticFunction::is_empty($start) && StaticFunction::is_empty($end)) {
			return false;
		}

		//開始時刻が現在時刻より未来ならチェック対応外なのでfalse(制限外)を返す
		if ($start > $cur_datetime) {
			return false;
		}

		//終了時刻が0でなく、かつ現在時刻が終了時刻より未来ならチェック対応外なのでfalse(制限外)を返す
		//※0の場合は、エンドは無くチェック対応となるので、ここで終わること無く次へ進む必要がある
		if ($end && $end < $cur_datetime) {
			return false;
		}

		//上記以外は期間内なので制限内となる
		return true;
	}

}

?>
