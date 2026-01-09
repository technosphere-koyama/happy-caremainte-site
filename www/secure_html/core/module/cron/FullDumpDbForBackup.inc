<?php

/* * **********************************
 * NAME:FullDumpDbForBackup
 * DESC:
 *  HTML・PHPソースはサーバの1日1回バックアップ機能でバックアップできるが、
 *  DBデータはその対象外となる
 *  そこで、バックアップするタイミングの少し前に、クーロンでフルダンプして
 *  バックアップ対象ディレクトリにファイルとして配置しておけば事実上
 *  バックアップできるよねというものである
 *  保存先は、ブラウザからアクセス出来ない場所である必要がある
 * NOTICE:
 *  バックアップ時間より1時間ほどは前に実行すること
 * CREATE: 2015.10.15 hesaka 側だけ作成
 * *********************************** */
class FullDumpDbForBackup {

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
	 *  CREATE文も吐いておき、phpmyadminからインポートしたら動く形にしておきたい
	 *  なので、mysqldumpを使用する
	 * CREATE: 2016.01.04 hesaka
	 * UPDATE: 2016.12.15 hesaka ZIP圧縮対応
	 *                           古いバックアップを削除する処理対応
	 * *********************************** */
	public function exec() {

		/*
		 * db_back_upディレクトリが無ければ作成
		 */
		if (!is_dir(CONF::read('FULL_DUMP_DB.SAVE_PATH'))) {
			StaticFunction::create_dir(CONF::read('FULL_DUMP_DB.SAVE_PATH'));
		}

		/*
		 * DBユーザ・パスワードファイルを一時的に作成する
		 * ※直接コマンドに指定できるが、直接するとNoticeがでる
		 * 　historyにパスワードが直接残るので良くないと。。。確かに。。。
		 * 　なので、一時的に作成し、ダンプが完了したら当該ファイルを削除する
		 */
		StaticFunction::file_write(
			CONF::read('FULL_DUMP_DB.SAVE_PATH') . DS . 'pw',
			'[client]' . PHP_EOL . 
			'user = ' . CONF::read('DB.USER_ID') . PHP_EOL . 
			'password = ' . CONF::read('DB.USER_PW') . PHP_EOL . 
			'host = localhost'
		);

		/*
		 * コマンド生成
		 */
		//mysqlへのパスを指定
		if (PHP_OS !== 'WIN32' && PHP_OS !== 'WINNT') {
			$cmd = '/usr/bin/mysqldump';				//windows以外
		} else {
			$cmd = 'C:\xampp\mysql\bin\mysqldump.exe';		//windows
		}

		//ユーザ名・パスワード記載ファイル指定
		$cmd .= ' --defaults-extra-file=' . CONF::read('FULL_DUMP_DB.SAVE_PATH') . DS . 'pw';

		//$cmd .= ' --skip-lock-tables';										//ロックしない
	
		//トランザクション考慮
		//※これでロックされなくなる
		//　ロックはされないが、トランザクションを考慮してくれるので、
		//　innoDBの不整合は起こらない
		//　が、MyISAMは、トランザクションが効かないので不整合が起こる可能性がある
		//　なので、MyISAMについては、リストア時にテーブル削除してプリインポートする方が良いかと思われる
		$cmd .= ' --single-transaction';

		//drop table 付けない
		$cmd .= ' --skip-add-drop-table';

		//$cmd .= ' -u ' . CONF::read('DB.USER_ID');								//DBユーザ指定
		//$cmd .= ' -p' . CONF::read('DB.USER_PW');								//DBユーザパスワード指定

		//DB名指定
		$cmd .= ' ' . CONF::read('DB.NAME');

		/*
		 * 保存先指定
		 * 20161215
		 * ファイル名に日時を追加
		 */
		$cur_datetime = DbDateTime::get_cur_datetime();
		$file_path = 
			CONF::read('FULL_DUMP_DB.SAVE_PATH')
			. DS . CONF::read('DB.NAME') . '_dump_'
			. $cur_datetime;
		$cmd .= ' > ' . $file_path . '.sql';

		/*
		 * ダンプ実行
		 */
		if (system($cmd) === false) {
			//falseが返ってきた場合は失敗らしい
			return false;
		}

		/*
		 * パスワードファイルを削除する
		 */
		unlink(CONF::read('FULL_DUMP_DB.SAVE_PATH') . DS . 'pw');
		
		/*
		 * 20161215
		 * ZIP圧縮する
		 */
		$zip = new ZipArchive();
		if ($zip->open($file_path . '.zip', ZipArchive::CREATE)) {

			//zipにファイルを追加
			$zip->addFile(
				$file_path . '.sql', 
				CONF::read('DB.NAME') . '_dump_' . $cur_datetime . '.sql'
			);

			//ここでZIPファイル生成完了
			$zip->close();

			//圧縮に成功したら、ファイルを削除する
			unlink($file_path . '.sql');
		}

		/*
		 * 20161215
		 * 指定日数より古いバックアップファイルは削除する
		 * ※ダンプに成功した後に削除しないと、バックアップが全て無くなってしまうため
		 * 　最後に実行する
		 */
		$check_date = DbDateTime::get_datetime_change(
			DbDateTime::get_cur_date(), 
			'-' . CONF::read('FULL_DUMP_DB.SAVE_PERIOD') . ' days'
		);
		//ダンプディレクトリのファイルリスト生成
		$file_list = FunctionForSetUp::get_file_name_on_dir(CONF::read('FULL_DUMP_DB.SAVE_PATH'));
		foreach ($file_list as $file_path) {

			//ファイル名取得
			$path_list = explode(DS, $file_path);
			$file_name = $path_list[count($path_list) - 1];

			//日時を取得
			$file_exp = explode('_', $file_name);
			$file_date = str_replace('.zip', '', $file_exp[count($file_exp) - 1]);

			//日時が指定日数より古いバックアップファイルは削除
			if ($file_date < $check_date) {
				unlink($file_path);
			}
		}

		LOGS_NOTICE('!!! FULL DUMP DB FOR BACKUP SUCCESS !!!');

		return true;
	}
	
}

?>
