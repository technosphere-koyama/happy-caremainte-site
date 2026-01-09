<?php

/* * **********************************
 * NAME:Apns
 * DESC:
 *  iphoneにpush通知を行う
 * NOTICE:
 *  現状はpush通知を行うのみなので、必要に応じて通知すること。
 * CREATE: 2016.11.30 sonoda
 * *********************************** */
class Apns {

	/*
	 * constructor
	 */
	public function __construct() {
		require_once 'ApnsPHP/Autoload.php';
	}

	/*	 * **********************************
	 * NAME  : post_push
	 * INPUT : to / string / デバイストークン
	 *         body / string / メッセージ内容
	 *         id / string / メッセージ識別子
	 *         badge / integer / バッチ数(アイコンに表示)
	 * OUTPUT: 実行結果
	 *         false / 失敗した場合
	 * DESC  : push通知を行う
	 * NOTICE:
	 * CREATE: 2016.11.22 sonoda
	 * *********************************** */
	public function post_push($to, $body, $id, $badge=0) {

		$pem_file = CONF::read('APNS_CONF.PEM_FILE');
		$auth_file = CONF::read('APNS_CONF.AUTH_FILE');

		if(StaticFunction::is_empties(array($pem_file, $auth_file))) {
			LOGS_ALERT('pem not set!!');
			return false;
		}

		if(CONF::read('APNS_CONF.SANDBOX')) {
			$push = new ApnsPHP_Push(
				ApnsPHP_Abstract::ENVIRONMENT_SANDBOX,
				$pem_file
			);
		} else {
			$push = new ApnsPHP_Push(
				ApnsPHP_Abstract::ENVIRONMENT_PRODUCTION,
				$pem_file
			);
		}

		//APNSのechoログを表示しない場合はログ機能をoffにする。
		//デフォルトでonになっている。
		if(!CONF::read('APNS_CONF.LOG')) {
			$push->setLogger(new ApnsPHP_Log_Custom);
		}

		// 2.のentrust_root.pemを指定する
		$push->setRootCertificationAuthority($auth_file);

		// Connect to the Apple Push Notification Service
		$push->connect();

		// Instantiate a new Message with a single recipient
		$message = new ApnsPHP_Message($to);

		// エラー時のための識別子
		$message->setCustomIdentifier($id);

		// 数値を指定する
		if(!StaticFunction::is_empty($badge,ZERO_NOT_EMPTY)) {
			$message->setBadge($badge);
		}

		// Set a simple welcome text
		$message->setText($body);

		// Play the default sound
		$message->setSound();

		$message->setExpiry(30);

		// Add the message to the message queue
		$push->add($message);

		// Send all messages in the message queue
		$push->send();

		// Disconnect from the Apple Push Notification Service
		$push->disconnect();

		// Examine the error message container
		$aErrorQueue = $push->getErrors();
		if (!empty($aErrorQueue)) {
			LOGS_ERR(implode($aErrorQueue));
		}

		return;
	}

}