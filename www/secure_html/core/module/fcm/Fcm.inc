<?php

/* * **********************************
 * NAME:Fcm
 * DESC:
 *  Androidにpush通知などを行う処理群
 * NOTICE:
 *  Androidに関する通信を行う処理は
 *  ここに纏めること！
 * CREATE: 2016.11.22 sonoda
 * *********************************** */
class Fcm {

	/*
	 * constructor
	 */
	public function __construct() {
		
	}

	/*	 * **********************************
	 * NAME  : post_push
	 * INPUT : to / string / デバイストークン
	 *         title / string / メッセージタイトル
	 *         body / string / メッセージ内容
	 * OUTPUT: 実行結果
	 *         false / 失敗した場合
	 * DESC  : push通知を行う
	 * NOTICE:
	 * CREATE: 2016.11.22 sonoda
	 * *********************************** */
	public function post_push($to, $title, $body) {

		$message = array(
			'to' => $to,
			'notification' => array(
				'title' => $title,
				'body' => $body
			)
		);

		$retry_count = CONF::read('FCM_CONF.RETRY_COUNT');
		$interval = CONF::read('FCM_CONF.INTERVAL');

		$ch = curl_init(CONF::read('FCM_CONF.GOOGLE_API_URL'));

		$header = array("Content-Type:application/json",
			"Authorization:key=" . CONF::read('FCM_CONF.GOOGLE_API_KEY'));

		curl_setopt($ch, CURLOPT_HTTPHEADER, $header);
		curl_setopt($ch, CURLOPT_POST, true);
		curl_setopt($ch, CURLOPT_POSTFIELDS, json_encode($message));

		curl_setopt($ch, CURLOPT_SSL_VERIFYPEER, false);
		curl_setopt($ch, CURLOPT_SSL_VERIFYHOST, false);

		curl_setopt($ch, CURLOPT_RETURNTRANSFER, true);
		curl_setopt($ch, CURLOPT_FAILONERROR, true);

		for ($i = 1; $i <= $retry_count; $i++) {
			//実行
			if ($result = curl_exec($ch)) {
				//--成功したので次の処理へ
				curl_close($ch);
				$arr = json_decode($result, true);
				if($arr['failure']) {
					LOGS_ERR('push error!![' . $result . ' / retry_count= ' .$retry_count. ' / count=' .$i. ']');
					return false;
				}
				return $result;
			} else {
				LOGS_ERR('CONNECTION ERROR  Err_No[' . curl_errno($ch) . ']<br>'
					. '  app[ ' . GOOGLE_API_URL . ' ] <br>'
					. '  execNo[' . $i . ']<br>'
					. '  msg[' . curl_error($ch) . ']<br></span>');
				return false;
			}
			// インターバル設定
			sleep($interval);
		}
	}

}
