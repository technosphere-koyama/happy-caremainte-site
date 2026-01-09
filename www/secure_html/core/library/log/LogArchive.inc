<?php

/* * **********************************
 * NAME:LogArchive
 * DESC:
 *  ログファイルをアーカイブする
 * NOTICE:
 * CREATE: 2016.07.14 hesaka
 * *********************************** */
class LogArchive {

	/* Constructor */
	public function __construct() {
	}

	/*	 * **********************************
	 * NAME  : exec
	 * INPUT : NONE
	 * OUTPUT: NONE
	 * DESC  :
	 *  CronController()から実行されるメソッド
	 * NOTICE:
	 * CREATE: 2017.07.14 hesaka
	 * *********************************** */
	public function exec() {

		LOGS_NOTICE('!!! LOG ARCHIVE START !!!');

		//archiveディレクトリが無ければ作成
		if (!is_dir(DIR_LOG_ARCHIVE)) {
			StaticFunction::create_dir(DIR_LOG_ARCHIVE);
		}

		//ログディレクトリのファイルリスト生成
		$file_list = FunctionForSetUp::get_file_name_on_dir(DIR_LOG);

		//圧縮対象のファイルを計算する
		$to_archive_list = array();
		foreach ($file_list as $file_path) {

			$path_list = explode(DS, $file_path);
			$file_name = $path_list[count($path_list) - 1];

			$file_exp = explode('_', $file_name);
			$file_type = $file_exp[0];
			$file_date = str_replace('.log', '', $file_exp[1]);

			switch ($file_type) {

				//一日ごとにログファイルを生成するものの判断
				case 'debug':
				case 'mail':
				case 'login':
				case 'api':
					if (intval(mb_substr($file_date, 0, 6)) < intval(DATETIME_STR_Y . DATETIME_STR_M)) {
						$to_archive_list[$file_name] = $file_path;
					}
					break;

				//月ごとにログファイルを生成するものの判断
				case 'notice':
				case 'warning':
				case 'alert':
				case 'error':
				case 'env':
				case 'gengo':
				default:
					if (intval($file_date) < intval(DATETIME_STR_Y . DATETIME_STR_M)) {
						$to_archive_list[$file_name] = $file_path;
					}
			}
		}

		//圧縮すべきものがあれば圧縮する
		if (count($to_archive_list) > 0) {

			$zip = new ZipArchive();
			if ($zip->open(DIR_LOG_ARCHIVE . DS . 'archive_' . DATETIME_STR_Y . DATETIME_STR_M . '.zip', ZipArchive::CREATE)) {

				//zipにファイルを追加
				foreach ($to_archive_list as $key => $value) {
					$zip->addFile($value, $key);
				}

				//ここでZIPファイル生成完了
				$zip->close();

				//圧縮に成功したら、ファイルを削除する
				foreach ($to_archive_list as $value) {
					unlink($value);
				}

				LOGS_NOTICE($to_archive_list);
				LOGS_NOTICE('!!! LOG ARCHIVE COMPLETE !!!');
			}

		//圧縮するものがない場合はログだけ吐いておく
		} else {
			LOGS_NOTICE('!!! LOG ARCHIVE TARGET NOT FOUND !!!');
		}

		return true;
	}

}
		
?>
