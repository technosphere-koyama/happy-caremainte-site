<?php

/* * **********************************
 * NAME:MailCore
 * DESC:
 *  メールコアクラス
 * NOTICE:
 *  実際にメールを送信するのは当該クラス
 *  サードパーティ製モジュール(SwiftMailer)を利用して送信する
 * CREATE: 2015.10.07 hesaka
 * *********************************** */
class MailCore {

	private $mailer;
	private $message;
	
	/*
	 * constructor
	 */
	public function __construct() {

		/*
		 * swift mailer 初期設定
		 */
		require_once 'swiftMailerLib' . DS . 'swift_required.php';
		// 日本語に関する初期設定
		Swift::init(function () {
			Swift_DependencyContainer::getInstance()
				->register('mime.qpheaderencoder')
				->asAliasOf('mime.base64headerencoder');
//			Swift_Preferences::getInstance()->setCharset('iso-2022-jp');
		});

		/*
		 *  SMTP サーバーとの接続設定
		 */
		$transport = Swift_SmtpTransport::newInstance(CONF::read('SMTP.SERVER'), CONF::read('SMTP.PORT'));

		//ユーザ設定があれば追加
		//※SSL設定もここで追加
		if (!StaticFunction::is_empty(CONF::read('SMTP.USER'))) {
			$transport->setUsername(CONF::read('SMTP.USER'));
			/*
			 * カゴヤサーバでこれ入れてるとswiftmailerでfatalerrorになるので外しておく
			 * ※でも、ローカルでコメントアウトするとエラーになる。。。
			 * 　ポートを標準に戻してSSLなしで行けるようにするかなー。。。
			 */
			if (CONF::read('SMTP.SERVER') == "465" ) $transport->setEncryption('ssl');
			if (CONF::read('SMTP.SERVER') == "587" ) $transport->setEncryption('tls');
		}

		//パスワード設定があれば追加
		if (!StaticFunction::is_empty(CONF::read('SMTP.PASSWORD'))) {
			$transport->setPassword(CONF::read('SMTP.PASSWORD'));
		}
 
		/*
		 * メールインスタンス生成
		 */
		$this->mailer = Swift_Mailer::newInstance($transport);
	}
	
	/* * **********************************
	 * NAME  : send
	 * INPUT : data / array / メールの内容
	 * OUTPUT: true / 送信成功の場合
	 *         false / 送信失敗の場合
	 * DESC  :
	 *  テキストメールを送る
	 * NOTICE:
	 *  指定の仕方については、Mail.incのtemplate()を参照すること
	 * CREATE: 2015.10.13 hesaka
	 * *********************************** */
	protected function send($data) {

		//パラメータチェック
		if (empty($data) || !is_array($data)) {
			LOGS_MAIL('[ERROR] invalid parameter');
			return false;
		}
		

		//必須項目チェック
		if (empty($data[CONF::read('MAIL_ELEMENT.TO')]) 
			|| empty($data[CONF::read('MAIL_ELEMENT.FROM')]) 
			|| empty($data[CONF::read('MAIL_ELEMENT.SUBJECT')]) 
			|| empty($data[CONF::read('MAIL_ELEMENT.MESSAGE')])) {
			LOGS_MAIL('[ERROR] must parameter invalid');
			return false;
		}
		
		$mail_addres_base_array = CONF::read('MAIL_ADDRESS.BASE');

		//メールインスタンス生成＆基本セット
		$this->message = Swift_Message::newInstance()
			->setCharset('iso-2022-jp')
			->setEncoder(Swift_Encoding::get7BitEncoding())
			/*
			 * 優先度設定
			 * 1.Highest
			 * 2.High
			 * 3.Normal
			 * 4.Low
			 * 5.Lowest
			 * ->setPriority(3)
			 */
			/*
			 * メール開かれたら通知してくれる設定
			 * ※普段は使わない
			 * ->setReadReceiptTo(CONF::read('MAIL_ADDRESS.FROM'))
			 */
			/*
			 * エラーなど発生したら通知してくれる設定
			 * UPDATE: 2016.11.4 aoyama
			 *		送信者に設定。
			 */
			//->setReturnPath(CONF::read('MAIL_ADDRESS.BASE')[0])
			->setReturnPath($data[CONF::read('MAIL_ELEMENT.FROM')])
			/*
			 * 送信者表示設定
			 */
			->setSender($mail_addres_base_array[0]);
		
		$headers = $this->message->getHeaders();
		$headers->addTextHeader('X-Mailer', 'WebForm');
 
		//メール内容セット
		foreach ($data as $key => $value) {

			/*
			 * サニタイズされたデータをデコードする
			 */
			$value = $this->get_sanitize_decode_value($key, $value);
			
			switch ($key) {
				/*
				 * 以下のようにやることで表示名の指定ができる
				 * ->setFrom(array('some@address.tld' => 'The Name'));
				 */
				case CONF::read('MAIL_ELEMENT.FROM'):
					$this->set_address_element($value, 'addFrom');
					//この設定を行うと、返信の際に宛先としてくれる設定
					$this->message->setReplyTo($value);
					break;
				/*
				 * 以下のようにやることで複数指定ができる
				 * ->setTo(array('some@address.tld' => 'The Name', 'other@address.tld'));
				 */
				case CONF::read('MAIL_ELEMENT.TO'):
					$this->set_address_element($value, 'addTo');
					break;
				/*
				 * 以下のようにやることで複数指定ができる
				 * ->setCc(array('some@address.tld' => 'The Name', 'other@address.tld'));
				 */
				case CONF::read('MAIL_ELEMENT.CC'):
					$this->set_address_element($value, 'addCc');
					break;
				/*
				 * 以下のようにやることで複数指定ができる
				 * ->setBcc(array('some@address.tld' => 'The Name', 'other@address.tld'));
				 */
				case CONF::read('MAIL_ELEMENT.BCC'):
					$this->set_address_element($value, 'addBcc');
					break;
				/*
				 * ->setSubject('subject desu.');
				 */
				case CONF::read('MAIL_ELEMENT.SUBJECT'):
					$this->message->setSubject($value);
					break;
				/*
				 * ->setBody('content desu.');
				 */
				case CONF::read('MAIL_ELEMENT.MESSAGE'):
					$this->message->setBody($value);
					break;
				/*
				 * 添付ファイル
				 * 保存されているファイルからの場合
				 * ->attach(Swift_Attachment::fromPath('/path/to/image.jpg')->setFilename('cool.jpg'));
				 * 
				 * 指定可能方法
				 * '/path/filename.jpg'
				 * array('/path/filename.jpg')
				 * array('filename.png' => '/path/filename.jpg')
				 */
				case CONF::read('MAIL_ELEMENT.ATTACH'):
					if (is_array($value)) {
						foreach ($value as $file_name => $path) {
							if (is_int($file_name)) {
								$this->message->attach(Swift_Attachment::fromPath($path));
							} else {
								$this->message->attach(Swift_Attachment::fromPath($path)
									->setFilename($file_name));
							}
						}
					} else {
						$this->message->attach(Swift_Attachment::fromPath($value));
					}
					break;
				/*
				 * 添付ファイル
				 * PGで生成したファイルをそのまま添付する場合
				 * ->attach(Swift_Attachment::newInstance($pdf_data, 'my-file.pdf', 'application/pdf'));
				 * 
				 * 指定可能方法
				 * array(
				 *	CONF::read('ATTACH_RAW_ELEMENT.DATA') => $data, 
				 *	CONF::read('ATTACH_RAW_ELEMENT.NAME') => 'filename.jpg', 
				 *	CONF::read('ATTACH_RAW_ELEMENT.TYPE') => 'application/pdf'
				 * )
				 * ※この指定どおりでなければ無視される
				 */
				case CONF::read('MAIL_ELEMENT.ATTACH_RAW'):
					if (is_array($value)) {
						$data = NULL;
						$name = '';
						$type = '';
						foreach ($value as $key => $value) {
							switch ($key) {
								case CONF::read('ATTACH_RAW_ELEMENT.DATA'):
									$data = $value;
									break;
								case CONF::read('ATTACH_RAW_ELEMENT.NAME'):
									$name = $value;
									break;
								case CONF::read('ATTACH_RAW_ELEMENT.TYPE'):
									$type= $value;
									break;
								default:
							}
							if (!empty($data) && !empty($name) && !empty($type)) {
								$this->message->attach(
									Swift_Attachment::newInstance()
										->setFilename($name)
										->setContentType($type)
										->setBody($data)
								);
							}
						}
					}
					break;

				default:
			}
		}
		
		/*
		 * 送信
		 * ※IS_ACTIVEがtrueの場合のみ送信
		 */
		if (CONF::read('MAIL.IS_ACTIVE')) {
			if (!$this->mailer->send($this->message, $failers)) {
				//失敗した場合、ログ出力してfalseを返す
				LOGS_MAIL('[ERROR] *** mail send failed *** mail=' . $data['to']);
				LOGS_MAIL($failers);
				return false;
			}
		}
		
		//すべてのメールをロギング
		LOGS_MAIL($data);


		//メッセージオブジェクト初期化
		$this->message = NULL;

		return true;
	}

	/* * **********************************
	 * NAME  : send_html
	 * INPUT : data / array / メールの内容
	 * OUTPUT: NONE
	 * DESC  :
	 *  HTMLメールを送る
	 * NOTICE:
	 *  現在はまだ不要なので側だけ置いておく
	 * CREATE: 2015.10.13 hesaka
	 * *********************************** */
	protected function send_html($data) {
/*
//埋め込み画像のIDを生成
$cid = $this->message->embed(Swift_Image::fromPath('image.png'));
//生成したIDをBody中のimgタグのsrcに指定することでいけるらしい
$this->message->setBody(
'<html>' .
' <head></head>' .
' <body>' .
'  Here is an image <img src="' . $cid . '" alt="Image" />' .
'  Rest of message' .
' </body>' .
'</html>',
  'text/html'
);
 */
/*
 * メール埋め込み画像
 * ※HTMLメールでimgタグを埋め込む場合にsrcに設定する
 * 
 * $cid = $this->message->embed(Swift_Image::fromPath('image.png'));
 * 
 * $this->message->setBody(
 * '<html>' .
 * ' <head></head>' .
 * ' <body>' .
 * '  Here is an image <img src="' . $cid . '" alt="Image" />' .
 * '  Rest of message' .
 * ' </body>' .
 * '</html>',
 * 'text/html' // Mark the content-type as HTML
 * );
 */
/*
case CONF::read('MAIL_ELEMENT.EMBED'):
	//現状では難しいので使わない
	break;
 */
	}

	/* * **********************************
	 * NAME  : get_autograph
	 * INPUT : NONE
	 * OUTPUT: string / 署名文字列
	 * DESC  :
	 *  署名を返す
	 * NOTICE:
	 * CREATE: 2015.10.13 hesaka
	 * UPDATE: 2016.10.07 hesaka 言語対応によりてきすとをViewに配置した
	 * *********************************** */
	protected function get_autograph() {
		return
			PHP_EOL .
			PHP_EOL .
			//各国語の署名を出力
			CONF::read('LANG_TEXT.MAIL.AUTOGRAPH');
	}

	/* * **********************************
	 * NAME  : set_address_element 
	 * INPUT : data / array or string / アドレス、宛名
	 * OUTPUT: NONE
	 * DESC  :
	 *  From, To, Cc, BccをSwiftMailerにセットする
	 * NOTICE:
	 *  引数に指定する「data」は、
	 *  宛名とアドレスを指定する場合は array("宛名" => "address")となる
	 *  アドレスのみ指定する場合は、array("address")もしくは"address"と指定することが可能
	 * CREATE: 2015.10.13 hesaka
	 * *********************************** */
	private function set_address_element($data, $method_name)  {

		if (is_array($data)) {
			foreach ($data as $name => $address) {
				if (is_int($name)) {
					call_user_func(array($this->message, $method_name), $address);
				} else {
					call_user_func(array($this->message, $method_name), $address, $name);
				}
			}
		} else {
				call_user_func(array($this->message, $method_name), $data);
		}
	}
	
	/* * **********************************
	 * NAME  : get_sanitize_decode_value 
	 * INPUT : element / string / CONFIG ELEMENT値
	 *         data / array or string / データ本体
	 * OUTPUT: array or string / decodeしたデータ
	 * DESC  :
	 *  サニタイズされたデータをdecodeする
	 * NOTICE:
	 *  現時点では、htmlspecialchars()でエンコードされた内容をデコードする
	 *  ※ENT_QUOTESを指定し、シングルクオテも元に戻す
	 * 
	 *  POSTされてサニタイズしたものや、それをDBに入れて、取得したものなど
	 *  画面に表示する分にはサニタイズされたままで良いが、メールとして配信すると
	 *  エンコードされた文字列として表示されてしまう
	 *  なので、テキストメールの場合はパラメータをここでデコードすることとなる
	 *  ※HTMLメールの場合はデコードすると動いてしまう可能性があるので、表示するということから
	 *  　エンコードされたまま送ることとする
	 * CREATE: 2015.10.29 hesaka
	 * *********************************** */
	private function get_sanitize_decode_value($element, $data)  {

		$ret = $data;

		switch ($element) {

			/*
			 * decodeする必要のないものは$dataをそのまま返す
			 * ※現状では、ATTACH, ATTACH_RAWが対象となる
			 */
			case CONF::read('MAIL_ELEMENT.ATTACH'):
			case CONF::read('MAIL_ELEMENT.ATTACH_RAW'):
				break;

			/*
			 * 対象となるものは、decodeを行う
			 */
			default:
				//配列の場合はkey, value共にdecodeする
				if (is_array($data)) {
					$ret = array();
					foreach ($data as $key => $value) {
						$ret += array(
							htmlspecialchars_decode($key, ENT_QUOTES) => htmlspecialchars_decode($value, ENT_QUOTES)
						);
					}
				//配列でない場合はそのままdecodeする
				} else {
					$ret = htmlspecialchars_decode($data, ENT_QUOTES);
				}
		}

		return $ret;
	}

	/* * **********************************
	 * NAME  : send_hankaku
	 * INPUT : data / array / メールの内容
	 * OUTPUT: true / 送信成功の場合
	 *         false / 送信失敗の場合
	 * DESC  :
	 *      管理者宛などの半角カナメールを送信するときに使用
	 * NOTICE:
	 *      このメソッドでは特定のメールクライアントをターゲットとしているので
     *      汎用的なメールには使用しない方が良い。
	 * CREATE: 2017.4.7 aoyama
	 * *********************************** */
	protected function send_hankaku($data) {


		//パラメータチェック
		if (empty($data) || !is_array($data)) {
			LOGS_MAIL('[ERROR] invalid parameter');
			return false;
		}
		

		//必須項目チェック
		if (empty($data[CONF::read('MAIL_ELEMENT.TO')]) 
			|| empty($data[CONF::read('MAIL_ELEMENT.FROM')]) 
			|| empty($data[CONF::read('MAIL_ELEMENT.SUBJECT')]) 
			|| empty($data[CONF::read('MAIL_ELEMENT.MESSAGE')])) {
			LOGS_MAIL('[ERROR] must parameter invalid');
			return false;
		}
		
		$mail_addres_base_array = CONF::read('MAIL_ADDRESS.BASE');

		//メールインスタンス生成＆基本セット
		$this->message = Swift_Message::newInstance()
			->setCharset('UTF-8')
//			->setEncoder(Swift_Encoding::get7BitEncoding())
            ->setEncoder(Swift_Encoding::getBase64Encoding())
			->setReturnPath($data[CONF::read('MAIL_ELEMENT.FROM')])
			->setSender($mail_addres_base_array[0]);
		
		$headers = $this->message->getHeaders();
		$headers->addTextHeader('X-Mailer', 'WebForm');
 
		//メール内容セット
		foreach ($data as $key => $value) {

			/*
			 * サニタイズされたデータをデコードする
			 */
			$value = $this->get_sanitize_decode_value($key, $value);
			
			switch ($key) {
				/*
				 * 以下のようにやることで表示名の指定ができる
				 * ->setFrom(array('some@address.tld' => 'The Name'));
				 */
				case CONF::read('MAIL_ELEMENT.FROM'):
					$this->set_address_element($value, 'addFrom');
					//この設定を行うと、返信の際に宛先としてくれる設定
					$this->message->setReplyTo($value);
					break;
				/*
				 * 以下のようにやることで複数指定ができる
				 * ->setTo(array('some@address.tld' => 'The Name', 'other@address.tld'));
				 */
				case CONF::read('MAIL_ELEMENT.TO'):
					$this->set_address_element($value, 'addTo');
					break;
				/*
				 * 以下のようにやることで複数指定ができる
				 * ->setCc(array('some@address.tld' => 'The Name', 'other@address.tld'));
				 */
				case CONF::read('MAIL_ELEMENT.CC'):
					$this->set_address_element($value, 'addCc');
					break;
				/*
				 * 以下のようにやることで複数指定ができる
				 * ->setBcc(array('some@address.tld' => 'The Name', 'other@address.tld'));
				 */
				case CONF::read('MAIL_ELEMENT.BCC'):
					$this->set_address_element($value, 'addBcc');
					break;
				/*
				 * ->setSubject('subject desu.');
				 */
				case CONF::read('MAIL_ELEMENT.SUBJECT'):
					$this->message->setSubject($value);
					break;
				/*
				 * ->setBody('content desu.');
				 */
				case CONF::read('MAIL_ELEMENT.MESSAGE'):
					$this->message->setBody($value);
					break;
				/*
				 * 添付ファイル
				 * 保存されているファイルからの場合
				 * ->attach(Swift_Attachment::fromPath('/path/to/image.jpg')->setFilename('cool.jpg'));
				 * 
				 * 指定可能方法
				 * '/path/filename.jpg'
				 * array('/path/filename.jpg')
				 * array('filename.png' => '/path/filename.jpg')
				 */
				case CONF::read('MAIL_ELEMENT.ATTACH'):
					if (is_array($value)) {
						foreach ($value as $file_name => $path) {
							if (is_int($file_name)) {
								$this->message->attach(Swift_Attachment::fromPath($path));
							} else {
								$this->message->attach(Swift_Attachment::fromPath($path)
									->setFilename($file_name));
							}
						}
					} else {
						$this->message->attach(Swift_Attachment::fromPath($value));
					}
					break;
				/*
				 * 添付ファイル
				 * PGで生成したファイルをそのまま添付する場合
				 * ->attach(Swift_Attachment::newInstance($pdf_data, 'my-file.pdf', 'application/pdf'));
				 * 
				 * 指定可能方法
				 * array(
				 *	CONF::read('ATTACH_RAW_ELEMENT.DATA') => $data, 
				 *	CONF::read('ATTACH_RAW_ELEMENT.NAME') => 'filename.jpg', 
				 *	CONF::read('ATTACH_RAW_ELEMENT.TYPE') => 'application/pdf'
				 * )
				 * ※この指定どおりでなければ無視される
				 */
				case CONF::read('MAIL_ELEMENT.ATTACH_RAW'):
					if (is_array($value)) {
						$data = NULL;
						$name = '';
						$type = '';
						foreach ($value as $key => $value) {
							switch ($key) {
								case CONF::read('ATTACH_RAW_ELEMENT.DATA'):
									$data = $value;
									break;
								case CONF::read('ATTACH_RAW_ELEMENT.NAME'):
									$name = $value;
									break;
								case CONF::read('ATTACH_RAW_ELEMENT.TYPE'):
									$type= $value;
									break;
								default:
							}
							if (!empty($data) && !empty($name) && !empty($type)) {
								$this->message->attach(
									Swift_Attachment::newInstance()
										->setFilename($name)
										->setContentType($type)
										->setBody($data)
								);
							}
						}
					}
					break;

				default:
			}
		}
		
		/*
		 * 送信
		 * ※IS_ACTIVEがtrueの場合のみ送信
		 */
		if (CONF::read('MAIL.IS_ACTIVE')) {
			if (!$this->mailer->send($this->message, $failers)) {
				//失敗した場合、ログ出力してfalseを返す
				LOGS_MAIL('[ERROR] *** mail send failed *** mail=' . $data['to']);
				LOGS_MAIL($failers);
				return false;
			}
		}
		
		//すべてのメールをロギング
		LOGS_MAIL($data);


		//メッセージオブジェクト初期化
		$this->message = NULL;

		return true;
	}    
}

?>
