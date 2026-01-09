<?php

/* * **********************************
 * NAME:TicketCodeModel
 * DESC:
 *  チケットコードテーブル用モデルクラス
 * NOTICE:
 *  基本的にはDbShellクラスを継承し、そちらでPDOインスタンスアクセスを行う
 *  場合によっては当該クラスで直接触ることもあるかも知れないが、
 *  できるだけDbShellクラスにて行うこと！
 * CREATE: 2016.08.08 hesaka
 * *********************************** */
class TicketCodeModel extends DbShell {

	private $table_ticket_code = "ticket_code";
	
	public function __construct() {
		parent::__construct();
	}

	/* ***********************************
	 * NAME  : get_ticket_code
	 * INPUT : NONE
	 * OUTPUT: array / ブロック毎に分かれたコード配列
	 *         NULL / 生成失敗時
	 * DESC  :
	 *  チケットの発行を行う
	 * NOTICE:
	 * -----------------------------
	 *  生成済みコード(DBに保存していてまだ活きているやつ)との
	 *  重複チェックや精製後のDB登録、死にチケットのテーブル移動も併せて行う
	 * -----------------------------
	 * CREATE: 2016.08.05 hesaka
	 * *********************************** */
	public function get_ticket_code() {

		/*
		 * ticket_codeテーブルロック
		 */
		$this->WRITE_LOCK_TABLES(array($this->table_ticket_code));

		/*
		 * 指定期間より古い使用済みチケットを削除
		 */
		$this->destroy();

		/*
		 * 制限に抵触した場合は繰り返す
		 */
		$is_generate = false;
		$times = 0;
		$generate_retry_times = CONF::read('TICKET.GENERATE_RETRY_TIMES');
		$number_of_blocks = CONF::read('TICKET.NUMBER_OF_BLOCKS');
		$number_of_digits = CONF::read('TICKET.NUMBER_OF_DIGITS');
		do {

			$times++;

			/*
			 * コードを生成
			 */
			$blocks = array();
			for ($i = 0; $i < $number_of_blocks; $i++) {
				$blocks[$i] = 
					//頭が0の場合、桁が足りなくなるので0埋めする
					str_pad(
						//0～指定桁数の「9」の間でランダム数生成
						mt_rand(0, intval(str_pad(9, $number_of_digits, 9, STR_PAD_LEFT))),
						$number_of_digits, 
						0, 
						STR_PAD_LEFT
					);
			}

			/*
			 * 制限チェック
			 */
			//頭が0でないか(DBのカラム型を数値にするため)
			if (mb_substr($blocks[0], 0, 1) == '0') {
				//LOGS_WARN('TICKETING CONFLICT WITH RESTRICTION[TIMES=' . $times . '] reason=head is 0, code=' . implode('', $blocks));
				//これ1/10くらいの確立で発生するので、この場合は、再度1桁目だけ1～9でランダム生成
				$blocks[0] = $blocks[0] + (mt_rand(1, 9) * pow(10, $number_of_digits - 1));
			}

			//各ブロックにてゾロ目はダメ
			for ($i = 0; $i < $number_of_blocks; $i++) {
				//ゾロ目
				if(preg_match("/^([1-9])\\1{" . ($number_of_blocks - 1) . ",}$/", $blocks[$i])){
					LOGS_WARN('TICKETING CONFLICT WITH RESTRICTION[TIMES=' . $times . '] reason=repdigit, ticket_code=' . implode('', $blocks));
					//生成しなおし
					continue;
				}
			}

			//過去使用したコードと重複してるか確認を行う
			//※また、末尾1桁目の値を、インクリメントしたもの、デクリメントしたもの
			//　が存在していないか、それらについても重複確認を行う
			//　これらが重複していなければ、連番にはならないので
			//　上でゾロ目チェックを行うので、ここで「0000」になることはありえない
			//　なので、デクリメントに関しても、純粋に-1すれば良い
			$decriment = $blocks;
			$decriment[$number_of_blocks - 1] = $decriment[$number_of_blocks - 1] - 1;
			$incriment = $blocks;
			$incriment[$number_of_blocks - 1] = $incriment[$number_of_blocks - 1] + 1;
//print 'decri=' . implode('', $decriment) . '<br>';
//print 'code=' . implode('', $blocks) . '<br>';
//print 'incri=' . implode('', $incriment) . '<br>';
			if (!$this->check_duplicate(
				array(
					implode('', $decriment), 
					implode('', $blocks), 
					implode('', $incriment)
				)
			)) {
				LOGS_WARN('TICKETING CONFLICT WITH RESTRICTION[TIMES=' . $times . '] reason=duplication, ticket_code=' . implode('', $blocks));
				//生成しなおし
				continue;
			}

			//ここまで来たら有効なコード
			$is_generate = true;

		} while ($times < $generate_retry_times && !$is_generate);

		/*
		 * 20160805
		 * リトライ何回やっても無理な場合は終了
		 */
		if (!$is_generate) {
			/*
			 * ticket_codeテーブルロック解除
			 */
			$this->UNLOCK_TABLES();
			LOGS_ERR("TICKETING FAILED...");
			return NULL;
		}

		/*
		 * DBにセット
		 */
		if (!$this->insert_ticket_code(
			array(
				'system_id' => DbCast::system_id(StaticFunction::create_id()),
				'ticket_code' => DbCast::ticket_code(implode('', $blocks)),
				'active' => DbCast::integer(DB_ACTIVE_ON),
				//登録日時
				'create_time' => DbCast::datetime(DbDateTime::get_cur_datetime())
			)
		)) {
			/*
			 * ticket_codeテーブルロック解除
			 */
			$this->UNLOCK_TABLES();
			LOGS_ERR("INSERT TICKET ERROR! ticket_code=" . implode('', $blocks));
			return NULL;
		}

		/*
		 * ticket_codeテーブルロック解除
		 */
		$this->UNLOCK_TABLES();

		//ブロック配列のまま返す
		return $blocks;
	}

	/* ***********************************
	 * NAME  : collect
	 * INPUT : ticket_code / float / チケットコード
	 * OUTPUT: true / 成功時
	 *         false / チケットが無い、すでに無効であるなど失敗時
	 * DESC  :
	 *  チケットの回収(使用)処理
	 *  ※activeをOFFへ
	 *  　use_timeをセット
	 * NOTICE:
	 * CREATE: 2016.08.08 hesaka
	 * *********************************** */
	public function collect($ticket_code) {

		//パラメータチェック
		if (StaticFunction::is_empty($ticket_code)) {
			return false;
		}

		/*
		 * テーブルロック
		 * ticket_codeテーブルロック
		 */
		$this->WRITE_LOCK_TABLES(array($this->table_ticket_code));

		/*
		 * 指定チケットコードの
		 * activeをOFFへ
		 * 使用日時をセット
		 */
		$ret = true;
		if (!$this->db_shell_update(
			$this->table_ticket_code, 
			array(
				'active' => DbCast::integer(DB_ACTIVE_OFF),
				'use_time' => DbCast::datetime(DbDateTime::get_cur_datetime())
			),
			array(
				'WHERE' => array(
					'ticket_code' => DbCast::ticket_code($ticket_code)
				)
			)
		)) {
			//失敗した場合はfalseをセット
			$ret = false;
		}

		/*
		 * ticket_codeテーブルロック解除
		 */
		$this->UNLOCK_TABLES();

		return $ret;
	}
	
	/* ***********************************
	 * NAME  : insert_ticket_code
	 * INPUT : ticket_list / array / チケット情報
	 * OUTPUT: id / string / ID
	 * DESC  :
	 *  新規登録
	 * NOTICE:
	 * CREATE: 2016.08.08 hesaka
	 * *********************************** */
	private function insert_ticket_code($ticket_list) {
		return $this->db_shell_insert($this->table_ticket_code, $ticket_list);
	}
	
	/* * **********************************
	 * NAME  : check_duplicate
	 * INPUT : code_array / array / 確認したいコードの配列
	 * OUTPUT: true / 重複無し
	 *         false / 重複在り もしくは エラー
	 * DESC  :
	 *  指定チケットコードが存在しているかチェックする
	 * NOTICE:
	 *  複数コードを引数に指定することが可能
	 *  これは、インクリ・デクリして前後の値もチェックできるようにするためである
	 * CREATE: 2016.07.11 hesaka
	 * *********************************** */
	private function check_duplicate($code_array = NULL) {

		//パラメータチェック
		if (StaticFunction::is_empty($code_array) || !is_array($code_array)) {
			return false;
		}

		//WHERE句作成
		$condition_list = array();
		foreach ($code_array as $code) {
			$condition_list[] = "ticket_code=" . DbCast::ticket_code($code);
		}
		
		/*
		 * 件数取得
		 */
		$ret = $this->query("
			SELECT COUNT(ticket_code) AS num
			FROM " . $this->table_ticket_code . "
			WHERE " . implode(" OR ", $condition_list)
		);
		//1件でもあれば重複なのでfalseを返す
		if ($ret[0]['num'] > 0) {
			return false;
		}

		//ここまで来たら重複はないのでtrueを返す
		return true;
	}
	
	/* * **********************************
	 * NAME  : destroy
	 * INPUT : NONE
	 * OUTPUT: NONE
	 * DESC  :
	 *  使用後、古くなったチケットを削除する
	 * 
	 *  ------------------------------------
	 *  activeがOFFで、use_timeが現在時刻より
	 *  DESTROY_TIMING指定期間以上古いものが対象となる
	 * 
	 *  例)
	 *  現在時刻：20160809152055, DESTROY_TIMING：3 の場合
	 * 
	 *  activeがOFFで use_timeが
	 *  20160501000000
	 *  より古いもの(つまり、2016年4月のものより古いもの)は全て削除
	 *  ※指定期間が月なため、最長4か月(8月末日実行時も5月1日のものは残るため)保管
	 *  　最短としてDESTROY_TIMING指定月保証となる
	 *  ------------------------------------
	 * 
	 * NOTICE:
	 *  チケットレコードを削除してしまうが、
	 *  チケット発行時に受注テーブルに入れておくし、
	 *  使用タイミングには、受注テーブルに使用時刻を
	 *  セットするので、削除しても問題はないものと思われる
	 * CREATE: 2016.08.09 hesaka
	 * *********************************** */
	private function destroy() {

		/*
		 * DESTROY_TIMING指定値から、
		 * チェック対象日時を取得する
		 */
		$timing = DbDateTime::get_datetime_change(
			//本日の0時0分0秒を指定
			DbDateTime::get_cur_date(),
			//そこからDESTROY_TIMING月マイナスした初日を起点とする
			'first day of - ' . CONF::read('TICKET.DESTROY_TIMING') . ' months'
		);
		
		/*
		 * まずは削除対象があるか確認
		 */
		$check = $this->query("
			SELECT COUNT(ticket_code) AS num
			FROM " . $this->table_ticket_code . "
			WHERE 
				active = " . DB_ACTIVE_OFF . "
				AND use_time IS NOT NULL
				AND use_time < " . DbCast::datetime($timing)
		);
		//対象がなければここで終了
		if ($check[0]['num'] <= 0) {
			return;
		}

		LOGS_WARN('TICKET DESTROY count=' . $check[0]['num'] . ', under ' . $timing);

		/*
		 * テーブルロック
		 * ticket_codeテーブルロック
		 */
		$this->WRITE_LOCK_TABLES(array($this->table_ticket_code));
		
		/*
		 * 対象レコードを削除
		 */
		$check = $this->exec("
			DELETE FROM " . $this->table_ticket_code . "
			WHERE 
				active = " . DB_ACTIVE_OFF . "
				AND use_time IS NOT NULL
				AND use_time < " . DbCast::datetime($timing)
		);

		/*
		 * ticket_codeテーブルロック解除
		 */
		$this->UNLOCK_TABLES();
	}
	
}

?>
