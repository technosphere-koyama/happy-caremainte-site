<?php

/* * **********************************
 * NAME:Mail
 * DESC:
 *  メールクラス
 * NOTICE:
 *  メールを送る際に、コントローラからアクセスするのは当該クラスとなる
 *  MailCoreクラスにはコントローラから直接触らないように
 *  各用途に合わせたメールメソッドを作成し、それをコントローラから叩くこと
 * CREATE: 2015.10.07 hesaka
 * *********************************** */
class Mail extends MailCore {

	/*
	 * メールでURLを送る場合のベースパスとなる
	 * 会員とシステムユーザでパスが変わるので
	 * 当該メンバを処理に用いる
	 */

	private $document_root;
	private $url_login_path;
	private $url_id_remainder_path;
	private $url_password_reset_path;
	private $url_user_add_path;
	private $ds = '/';

	/*
	 * constructor
	 */
	public function __construct() {
		parent::__construct();
		//デフォルトとして会員側のパスを設定する
		$this->document_root = CONF::read('URL_PUBLIC_ROOT');
		$this->url_login_path = $this->document_root . 'mypage' . $this->ds . 'login.html';
		$this->url_id_remainder_path = $this->document_root . 'remainder' . $this->ds;
		$this->url_password_reset_path = $this->document_root . 'pwreset' . $this->ds;
		$this->url_user_add_path = $this->document_root . $this->ds . 'register' . $this->ds . 'complete.html';
	}

	/*	 * **********************************
	 * NAME  : set_target_system
	 * INPUT : NONE
	 * OUTPUT: NONE
	 * DESC  :
	 *  メールに貼るURLのベースパスを、管理者側のものに変更
	 * NOTICE:
	 *  使い方としては、管理画面ユーザにメールを送る場合は
	 *  当該メソッドを叩く
	 * CREATE: 2015.10.16 hesaka
	 * *********************************** */
	public function set_target_system() {
		$this->document_root = CONF::read('URL_SYSTEM_ROOT');
		$this->url_login_path = $this->document_root . 'login' . $this->ds;
		$this->url_id_remainder_path = $this->document_root . 'remainder' . $this->ds;
		$this->url_password_reset_path = $this->document_root . 'pwreset' . $this->ds;
	}

	/*	 * **********************************
	 * NAME  : template
	 * INPUT : NONE
	 * OUTPUT: true / 送信成功の場合
	 *         false / 送信失敗の場合
	 * DESC  :
	 *  テスト・指定方法確認用のメソッドである
	 * NOTICE:
	 *  DESCにあるように、当該メソッドはシステム上使用するものではなく
	 *  動作確認用に使用することと、MailCoreのsend()の引数指定方法を
	 *  確認するためのものである
	 *
	 *  SwiftMailerの使い方参考サイト
	 *  http://swiftmailer.org/docs/messages.html
	 * CREATE: 2015.10.13 hesaka
	 * *********************************** */
	public function template() {

		$ret = $this->send(
			array(
				/*
				 * FROM
				 * 複数指定しないこと
				 */
				CONF::read('MAIL_ELEMENT.FROM') => CONF::read("MAIL_ADDRESS.FROM"),
				/*
				 * TO
				 * 下記のように複数指定可能
				 */
				CONF::read('MAIL_ELEMENT.TO') => array(
					't.hesaka@xaicom.jp',
					'クリラボさま' => 'tomo@create-lab.com'
				),
				/*
				 * CC
				 * 下記のように複数指定可能
				 */
				CONF::read('MAIL_ELEMENT.CC') => array(
					't.sonoda@xaicom.jp',
					'クリラボさま2' => 'c-i.beam.h_g-z.freedom@i.softbank.jp'
				),
				/*
				 * BCC
				 * 下記のように複数指定可能
				 */
				CONF::read('MAIL_ELEMENT.BCC') => array(
					't.aoyama@xaicom.jp',
					'クリラボさま3' => 'tomo@create-lab.com'
				),
				/*
				 * SUBJECT
				 * １つのみ、文字列にて指定すること
				 */
				CONF::read('MAIL_ELEMENT.SUBJECT') => '【MINPAKU CONCIERGE】ログインIDをご連絡いたします。',
				/*
				 * ATTACH
				 * 下記のように複数指定可能
				 */
				CONF::read('MAIL_ELEMENT.ATTACH') => array(
					'logo_test.png' => DIR_PUBLIC . '/common/images/login_logo.png',
					'logo_header.png' => DIR_PUBLIC . '/common/images/header_logo.png'
				),
				/*
				 * MESSAGE
				 * １つのみ、文字列にて指定すること
				 *  改行は「PHP_EOL」を使用すること
				 *  $this->get_autograph()により署名を付け加えることが可能
				 */
				CONF::read('MAIL_ELEMENT.MESSAGE') =>
				'testです。' . PHP_EOL .
				PHP_EOL .
				PHP_EOL .
				$this->get_autograph()
			)
		);

		//失敗した場合その旨ログを出力してfalseを返す
		if (!$ret) {
			LOGS_MAIL('[ERROR] *** send mail failed ***');
			return false;
		}

		LOGS_MAIL('[SUCCESS] send mail success');
		return true;
	}

	/*	 * **********************************
	 * NAME  : send_user_regist
	 * INPUT : $user_array / array / 会員情報配列
	 * OUTPUT: true / 送信成功の場合
	 *         false / 送信失敗の場合
	 * DESC  :
	 * 		会員登録メールお客様控えを送る
	 * NOTICE:
	 * CREATE: 2016.11.4 aoyama
	 * UPDATE: 2016.11.4 aoyama
	 * 		お客さま控えは送らないとのことなので停止
	 * *********************************** */
	public function send_user_regist($user_array) {
		/*
		  //パラメータチェック
		  if (StaticFunction::is_empty($user_array)) {
		  LOGS_MAIL('[ERROR] *** invalid parameter ***');
		  return false;
		  }

		  $message = "------------------------------------------------------------------" . PHP_EOL .
		  "　ＩＤ発行のお申し込み受付通知" . PHP_EOL .
		  "------------------------------------------------------------------" . PHP_EOL .
		  "Happy ケアメンテをご利用頂き誠にありがとうございます。" . PHP_EOL .
		  "下記の内容でＩＤ発行のお申し込みを頂戴しました。" . PHP_EOL .
		  "このあと、ＩＤ・パスワード、利用方法の案内メールをお送りいたします。" . PHP_EOL .
		  "■お名前" . PHP_EOL .
		  $user_array['name'] . PHP_EOL .
		  "■ふりがな" . PHP_EOL .
		  $user_array['kana'] . PHP_EOL .
		  "■電話番号" . PHP_EOL .
		  $user_array['tel'] . PHP_EOL .
		  "■メールアドレス" . PHP_EOL .
		  $user_array['email'] . PHP_EOL .
		  "■メールアドレス（サブ）" . PHP_EOL .
		  $user_array['email2'] . PHP_EOL .
		  "■住所" . PHP_EOL .
		  "〒" . $user_array['zip'] . PHP_EOL .
		  $user_array['state'] . $user_array['addr1'] . PHP_EOL .
		  $user_array['addr2'] . PHP_EOL .
		  $user_array['addr3'] . PHP_EOL .
		  "■パスワード" . PHP_EOL .
		  $user_array['pass'] . PHP_EOL .
		  "■受付日時" . PHP_EOL .
		  DbDateTime::get_datetime_type_hyphen(DbDateTime::get_cur_datetime());

		  $ret = $this->send(
		  array(
		  CONF::read('MAIL_ELEMENT.FROM') => CONF::read("MAIL_REGIST.FROM"),
		  CONF::read('MAIL_ELEMENT.TO') => $user_array['email'],
		  //CONF::read('MAIL_ELEMENT.BCC') => CONF::read("MAIL_ADDRESS.ADMIN"),
		  CONF::read('MAIL_ELEMENT.SUBJECT') => "ＩＤ発行のお申し込み",
		  CONF::read('MAIL_ELEMENT.MESSAGE') => $message
		  )
		  );

		  //失敗した場合その旨ログを出力してfalseを返す
		  if (!$ret) {
		  LOGS_MAIL('[ERROR] *** send mail failed *** address=' . $message);
		  return false;
		  }

		  LOGS_MAIL('[SUCCESS] send mail success.');
		  return true;
		 */
	}

	/*	 * **********************************
	 * NAME  : send_core_system_regist
	 * INPUT : $user_array / array / 会員情報配列
	 * OUTPUT: true / 送信成功の場合
	 *         false / 送信失敗の場合
	 * DESC  :
	 * 		基幹システムへ会員情報変更メールを送る
	 * NOTICE:
	 * CREATE: 2016.11.15 aoyama
	 * *********************************** */
	public function send_core_user_edit($old_array, $user_array) {

		//パラメータチェック
		if (StaticFunction::is_empty($user_array)) {
			LOGS_MAIL('[ERROR] *** invalid parameter ***');
			return false;
		}

		// DBからケアメンテ登録用メッセージの取得
		$mail = new MailMasterModel();

		//受付日時を作成
		$date = DbDateTime::get_datetime_type_slash(DbDateTime::get_cur_datetime());

		/* お客様控え */

		$message_user = "" .
			"------------------------------------------------------------------" . PHP_EOL .
			"登録住所等の変更を受付けました。" . PHP_EOL .
			"------------------------------------------------------------------" . PHP_EOL .
			"【変更前】" . PHP_EOL .
			"■お名前" . PHP_EOL .
			$old_array['name'] . PHP_EOL .
			"■住所" . PHP_EOL .
			"〒" . $old_array['zip'] . PHP_EOL .
			$old_array['state'] . $old_array['addr1'] . PHP_EOL .
			$old_array['addr2'] . PHP_EOL .
			$old_array['addr3'] . PHP_EOL .
			"■電話番号" . PHP_EOL .
			$old_array['tel'] . PHP_EOL .
			"■FAX番号" . PHP_EOL .
			PHP_EOL .
			"■メールアドレス" . PHP_EOL .
			$old_array['email'] . PHP_EOL .
			PHP_EOL .
			"【変更内容】" . PHP_EOL .
			"■お名前" . PHP_EOL .
			$user_array['name'] . PHP_EOL .
			"■住所" . PHP_EOL .
			"〒" . $user_array['zip'] . PHP_EOL .
			$user_array['state'] . $user_array['addr1'] . PHP_EOL .
			$user_array['addr2'] . PHP_EOL .
			$user_array['addr3'] . PHP_EOL .
			"■電話番号" . PHP_EOL .
			$user_array['tel'] . PHP_EOL .
			"■FAX番号" . PHP_EOL .
			PHP_EOL .
			"■メールアドレス" . PHP_EOL .
			$user_array['email'] . PHP_EOL .
			"■備考" . PHP_EOL .
			PHP_EOL .
			"■受付日時" . PHP_EOL .
			"受付日時： " . $date . PHP_EOL .
			'' . PHP_EOL .
			'============================================================' . PHP_EOL .
			'●申込した覚えがない方へ' . PHP_EOL .
			'上記日時に申し込みをされた覚えがない場合は、似たアドレスをお持ちの方が' . PHP_EOL .
			'誤って申し込みをされた可能性があります。' . PHP_EOL .
			'お心あたりのない場合は、たいへんお手数ですが、' . PHP_EOL .
			'送信者 happy@kyoto-happy.co.jp までお知らせいただくとともに、' . PHP_EOL .
			'本メールを削除くださいますようお願い申し上げます' . PHP_EOL .
			'' . PHP_EOL .
			'ご不明な点がございましたら、下記までお気軽にご連絡くださいませ。';

		$ret = $this->send(
			array(
				CONF::read('MAIL_ELEMENT.FROM') => CONF::read("MAIL_REGIST.FROM"),
				CONF::read('MAIL_ELEMENT.TO') => $user_array['email'],
				//CONF::read('MAIL_ELEMENT.BCC') => CONF::read("MAIL_ADDRESS.ADMIN"),
				CONF::read('MAIL_ELEMENT.SUBJECT') => "登録住所等の変更を受付けました。 ",
				CONF::read('MAIL_ELEMENT.MESSAGE') => StaticFunction::convert_zen_kana($message_user) .
				PHP_EOL .
				$mail->get_mail_text('autograph') // 署名
			)
		);
		//失敗した場合その旨ログを出力してfalseを返す
		if (!$ret) {
			LOGS_ERR('[ERROR] *** send mail failed *** address=' . $message_user);
		}

		/* 　管理者宛メール　 */
		$message = "" .
			"-----------------------------------------------------------------" . PHP_EOL .
			"登録住所等の変更を受付けました。" . PHP_EOL .
			"------------------------------------------------------------------" . PHP_EOL .
			"【変更前】" . PHP_EOL .
			PHP_EOL .
			"お名前： " . $old_array['name'] . PHP_EOL .
			"郵便番号： " . $old_array['zip'] . PHP_EOL .
			"住所： " . $old_array['state'] . $old_array['addr1'] . $old_array['addr2'] . $old_array['addr3'] . PHP_EOL .
			"電話番号： " . $old_array['tel'] . PHP_EOL .
			"FAX番号： " . PHP_EOL .
			"メールアドレス： " . $old_array['email'] . PHP_EOL .
			PHP_EOL .
			"【変更内容】" . PHP_EOL .
			"お名前： " . $user_array['name'] . PHP_EOL .
			"郵便番号： " . $user_array['zip'] . PHP_EOL .
			"住所： " . $user_array['state'] . $user_array['addr1'] . $user_array['addr2'] . $user_array['addr3'] . PHP_EOL .
			"電話番号： " . $user_array['tel'] . PHP_EOL .
			"FAX番号： " . PHP_EOL .
			"メールアドレス： " . $user_array['email'] . PHP_EOL .
			"備考： " . PHP_EOL .
			"受付日時： " . $date . PHP_EOL .
			"------------------------------------------------------------------";

		$ret = $this->send(
			array(
				CONF::read('MAIL_ELEMENT.FROM') => CONF::read("MAIL_REGIST.FROM"),
				CONF::read('MAIL_ELEMENT.TO') => CONF::read("MAIL_REGIST.TO"),
				//CONF::read('MAIL_ELEMENT.BCC') => CONF::read("MAIL_ADDRESS.ADMIN"),
				CONF::read('MAIL_ELEMENT.SUBJECT') => "申込 住所等の変更登録受付",
				CONF::read('MAIL_ELEMENT.MESSAGE') => StaticFunction::convert_zen_kana($message)
			)
		);

		//失敗した場合その旨ログを出力してfalseを返す
		if (!$ret) {
			LOGS_ERR('[ERROR] *** send mail failed *** address=' . $message);
			return false;
		}

		return true;
	}

	/*	 * **********************************
	 * NAME  : send_core_system_regist
	 * INPUT : $user_array / array / 会員情報配列
	 * OUTPUT: true / 送信成功の場合
	 *         false / 送信失敗の場合
	 * DESC  :
	 * 		基幹システムへ会員登録メールを送る
	 * NOTICE:
	 * CREATE: 2016.11.4 aoyama
	 * *********************************** */
	public function send_core_system_regist($user_array) {

		//パラメータチェック
		if (StaticFunction::is_empty($user_array)) {
			LOGS_MAIL('[ERROR] *** invalid parameter ***');
			return false;
		}

		$message = "------------------------------------------------------------------" . PHP_EOL .
			"　ＩＤ発行のお申し込み受付通知" . PHP_EOL .
			"------------------------------------------------------------------" . PHP_EOL .
			"ＩＤ発行のお申し込みを受け付けました。" . PHP_EOL .
			PHP_EOL .
			"お名前： " . $user_array['name'] . PHP_EOL .
			"ふりがな： " . $user_array['kana'] . PHP_EOL .
			"電話番号： " . $user_array['tel'] . PHP_EOL .
			"メールアドレス： " . $user_array['email'] . PHP_EOL .
			"メールアドレス2： " . $user_array['email2'] . PHP_EOL .
			"郵便番号： " . $user_array['zip'] . PHP_EOL .
			"住所１： " . $user_array['state'] . PHP_EOL .
			"住所２： " . $user_array['addr1'] . PHP_EOL .
			"住所３： " . $user_array['addr2'] . PHP_EOL .
			"住所４： " . $user_array['addr3'] . PHP_EOL .
			"受付日時： " . DbDateTime::get_datetime_type_slash(DbDateTime::get_cur_datetime()) . PHP_EOL .
			"パスワード： " . $user_array['pass'] . PHP_EOL .
			"生年月日： " . $user_array['birth'] . PHP_EOL .
			"性別： " . $user_array['sex'] . PHP_EOL .
			"職種： " . $user_array['wkbn'] . PHP_EOL .
			"------------------------------------------------------------------";

		$ret = $this->send(
			array(
				CONF::read('MAIL_ELEMENT.FROM') => CONF::read("MAIL_ENTRY.FROM"),
				CONF::read('MAIL_ELEMENT.TO') => CONF::read("MAIL_ENTRY.TO"),
				//CONF::read('MAIL_ELEMENT.BCC') => CONF::read("MAIL_ENTRY.BCC"),
				CONF::read('MAIL_ELEMENT.SUBJECT') => "ＩＤ発行のお申し込み",
				CONF::read('MAIL_ELEMENT.MESSAGE') => StaticFunction::convert_zen_kana($message)
			)
		);

		//失敗した場合その旨ログを出力してfalseを返す
		if (!$ret) {
			LOGS_ERR('[ERROR] *** send mail failed *** address=' . $message);
			return false;
		}

		return true;
	}

	/*	 * **********************************
	 * NAME  : send_order_wardrobe
	 * INPUT : セッションから取得
	 * OUTPUT: true / 送信成功の場合
	 *         false / 送信失敗の場合
	 * DESC  :
	 * 		サードローブ受付のメールを送る
	 * 		お客様控えのみ
	 * NOTICE:
	 * CREATE: 2016.11.11 aoyama
	 * *********************************** */
	public function send_order_wardrobe($sGroup, $email) {

		// DBからケアメンテ登録用メッセージの取得
		$mail = new MailMasterModel();

		//対象物件文字列を生成
		//sMail + "  " + thingnumber + "  " + classificationname + "／" + color  + CRLF;
		$item_list = "";
		foreach (SESSION::read($sGroup . '.item_array') AS $item) {
			$item_list .= "　" . StaticFunction::format_item_id($item['item_id']) . "　" . $item['classificationname'] . "／" . $item['color'] . PHP_EOL;
		}

		$title_for_customer = 'ワードローブお届け変更希望日を受付けました。';
		$message_for_customer = '' .
			'-----------------------------------------------------------------' . PHP_EOL .
			'ワードローブお届け変更希望日の受付通知' . PHP_EOL .
			'------------------------------------------------------------------' . PHP_EOL .
			'下記の内容で、お届け日の変更希望日を受付けました。' . PHP_EOL .
			'ハッピー本社にて発送日を確認のうえ、翌営業日中には、折り返し、お届け' . PHP_EOL .
			'日変更手続き完了のご連絡をさせていただきますのでお待ちくださいませ。' . PHP_EOL .
			'選択されたご希望日時によっては、ご希望に添えない場合がありますので、' . PHP_EOL .
			'ご了承くださいますようお願いいたします。' . PHP_EOL .
			PHP_EOL .
			'■お届け先' . PHP_EOL .
			'郵便番号　　：' . SESSION::read($sGroup . '.zip') . PHP_EOL .
			'住所　　　　：' . SESSION::read($sGroup . '.state') . SESSION::read($sGroup . '.addr1') . SESSION::read($sGroup . '.addr2') . SESSION::read($sGroup . '.addr3') . PHP_EOL .
			'お名前　　　：' . StaticFunction::marge_name(SESSION::read($sGroup . '.name1'), SESSION::read($sGroup . '.name2')) . PHP_EOL .
			'電話番号　　：' . StaticFunction::marge_phone(SESSION::read($sGroup . '.telephone'), SESSION::read($sGroup . '.telephone2'), SESSION::read($sGroup . '.telephone3')) . PHP_EOL .
			'お届け希望日　　：' . DbDateTime::get_date_type_slash(StaticFunction::marge_birth(SESSION::read($sGroup . '.year_c'), SESSION::read($sGroup . '.month_c'), SESSION::read($sGroup . '.day_c'))) . PHP_EOL .
			'お届け希望時間　：' . SESSION::read($sGroup . '.time') . PHP_EOL .
			'同時引取り　：' . SESSION::read($sGroup . '.hikitori') . PHP_EOL .
			'お支払い方法：' . SESSION::read($sGroup . '.pays') . PHP_EOL .
			PHP_EOL .
			'■対象物件番号' . PHP_EOL .
			$item_list . PHP_EOL .
			'' . PHP_EOL .
			'============================================================' . PHP_EOL .
			'●申込した覚えがない方へ' . PHP_EOL .
			'上記日時に申し込みをされた覚えがない場合は、似たアドレスをお持ちの方が' . PHP_EOL .
			'誤って申し込みをされた可能性があります。' . PHP_EOL .
			'お心あたりのない場合は、たいへんお手数ですが、' . PHP_EOL .
			'送信者 happy@kyoto-happy.co.jp までお知らせいただくとともに、' . PHP_EOL .
			'本メールを削除くださいますようお願い申し上げます' . PHP_EOL .
			'' . PHP_EOL .
			'ご不明な点がございましたら、下記までお気軽にご連絡くださいませ。';


		//お客様控え
		$ret_user = $this->send(
			array(
				CONF::read('MAIL_ELEMENT.FROM') => CONF::read("MAIL_ES.FROM"),
				CONF::read('MAIL_ELEMENT.TO') => $email,
				CONF::read('MAIL_ELEMENT.SUBJECT') => $title_for_customer,
				CONF::read('MAIL_ELEMENT.MESSAGE') => StaticFunction::convert_zen_kana($message_for_customer) .
				PHP_EOL .
				$mail->get_mail_text('autograph') // 署名
			)
		);
		//失敗した場合その旨ログを出力してfalseを返す
		if (!$ret_user) {
			LOGS_ERR('[ERROR] *** send mail failed eSystem *** address=' . $email);
			return false;
		}

		//管理者へメール
		$ret_system = $this->send(
			array(
				CONF::read('MAIL_ELEMENT.FROM') => CONF::read("MAIL_ES.FROM"),
				CONF::read('MAIL_ELEMENT.TO') => CONF::read("MAIL_ES.TO"),
				CONF::read('MAIL_ELEMENT.SUBJECT') => $title_for_customer,
				CONF::read('MAIL_ELEMENT.MESSAGE') => StaticFunction::convert_zen_kana($message_for_customer) .
				PHP_EOL .
				$mail->get_mail_text('autograph') // 署名
			)
		);
		//失敗した場合その旨ログを出力してfalseを返す
		if (!$ret_system) {
			LOGS_ERR('[ERROR] *** send mail failed eSystem *** address=' . $email);
		}
		return true;
	}

	// ------------------------------------------------- UKS MS WEBCOUNSELING mail config --------------------------------------------------
	// ------------------------------------------------- 2021-10-05 -------- START ---------------------------------------------
	/*	 * **********************************
	 * NAME  : send_webcounseling_details
	 * INPUT : User choosen Webcouseling details
	 * OUTPUT: true / 送信成功の場合
	 *         false / 送信失敗の場合
	 * DESC  : mail sent after successful entry of records
	 * NOTICE:
	 * CREATE: 2021.10.05 UKS MS
	 * *********************************** */
	public function send_webcounseling_details($mail_contents, $email) {
		$bcc_mail = 'counseling@kyoto-happy.co.jp';

		// DBからケアメンテ登録用メッセージの取得
		$mail = new MailMasterModel();

		// Setting variables to attach in mail
		$chart_no = $mail_contents['chartno'];
		$visitorno = $mail_contents['visitorno'];
		$amount = $mail_contents['amount'];
		$user_name = $mail_contents['user_name'];
		$ec_firstdocconfirm = (isset($mail_contents['AK006'])) ? $mail_contents['AK006'] : '';
		$ec_counselingchartok = (isset($mail_contents['AK007'])) ? $mail_contents['AK007'] : $mail_contents['AK001'];
		$ec_maintenancechange = (isset($mail_contents['SA001'])) ? 'はい' : 'いいえ';
		$ec_hopecontents = (isset($mail_contents['SA001'])) ? $mail_contents['SA001'] : '';
		$ec_wardrobeuse = (isset($mail_contents['SA002'])) ? 'はい' : 'いいえ';
		$ec_wardrobeusageperiod = (isset($mail_contents['SA002'])) ? $mail_contents['SA002'] : '';
		$ec_paymentmethod = (isset($mail_contents['AK008'])) ? $mail_contents['AK008'] : $mail_contents['AK002'];
		$ec_deliverydate = (isset($mail_contents['AK010'])) ? $mail_contents['AK010'] : $mail_contents['AK004'];
		$ec_deliverytime = (isset($mail_contents['AK011'])) ? $mail_contents['AK011'] : $mail_contents['AK005'];
		//$ec_shippingdate = $mail_contents['shippingdate'];
		$ec_reportscheduleddate = $mail_contents['reportscheduleddate'];
		
		$today = date('Y-m-d H:i:s');

		// if first time user
		if($ec_firstdocconfirm == 'はい') {
			$first_user = '「初めてのご利用のお客様へ」の内容確認： ' . $ec_firstdocconfirm;
		} else {
			$first_user = '';
		}

		// if maintaince change is opted
		if($ec_maintenancechange == 'はい') {
			$maintain_change_body = 'ご希望： ' . $ec_hopecontents . PHP_EOL;
		} else {
			$maintain_change_body = '';
		}

		//  if wadrobe is selected
		if($ec_wardrobeuse == 'はい') {
			$wadrobe_body = 'ご利用期間： ' . $ec_wardrobeusageperiod . '（ヶ月間）' . PHP_EOL;
		} else {
			$wadrobe_body = '';
		}

		//  if wadrobe is selected
		if($ec_counselingchartok == 'はい') {
			$payment = 'お支払い方法： ' . $ec_paymentmethod . PHP_EOL;
			$deli_date = 'お届け希望日： ' . $ec_reportscheduleddate . PHP_EOL;
			$deli_time = 'お届け時間： ' . $ec_deliverytime . PHP_EOL;
		} else {
			$payment = '';
			$deli_date = '';
			$deli_time = '';
		}

		$title_for_customer = 'カウンセリングの回答を受付けました。';
		
		$message_for_customer = '' .
			$user_name . ' 様' . PHP_EOL .
			PHP_EOL .
			'ハッピーケアメンテでございます。' . PHP_EOL .
			'以下の内容で、カウンセリングの回答を受付けました。' . PHP_EOL . 
			PHP_EOL .
			'============================================================' . PHP_EOL .
			$first_user . PHP_EOL .
			'「カウンセリングカルテ」の内容で良い： ' . $ec_counselingchartok . PHP_EOL .
			'メンテナンスの変更： ' . $ec_maintenancechange . PHP_EOL .
			$maintain_change_body  .
			'「ハッピーワードローブ」利用： ' . $ec_wardrobeuse . PHP_EOL .
			$wadrobe_body . 
			$payment .
			$deli_date .
			$deli_time .
			'------------------------------------------------------------' .  PHP_EOL . 
			'ID： ' . $visitorno . PHP_EOL .
			'受付日時： ' . $today . PHP_EOL .
			'カルテ番号： ' . $chart_no . PHP_EOL .
			'============================================================' . PHP_EOL .
			'・上記回答内容によってお見積り金額等が変わる場合は、修正したカルテと共に再度メールにて「回答フォーム」をお送りいたします。' . PHP_EOL .
			'・お見積り金額等に変更がない場合は、お届け日時等のご案内メールをお送りしますので、いましばらくお待ちください。' . PHP_EOL .
			'・翌営業日を過ぎても当社からの応答がない場合は、恐れ入りますがご連絡くださいますようお願い申し上げます。' . PHP_EOL .
			'・その他、ご不明な点は下記までお気軽にご連絡くださいませ。' . PHP_EOL .
			'━━━━━━━━━━━━━━━━━━━━━━━━━━━━ ';
			
		$signature_message = '' .
			'株式会社ハッピー（カウンセラー代表）' . PHP_EOL .
			'E-MAIL: counseling@kyoto-happy.co.jp' . PHP_EOL .
			PHP_EOL .
			'〒611-0041 京都府宇治市槙島町目川７０番地の１' . PHP_EOL .
			'TEL ： 0120-88-6868  FAX ： 0120-88-3937' . PHP_EOL .
			'【営業時間】 月～土／ 9:00～18：00 （日・祝祭日除く）' . PHP_EOL .
			'営業時間外や電話が混み合っている場合は、お手数ですが音声' . PHP_EOL .
			'ガイダンスにしたがって、お名前・お電話番号・ご用件を録音してください。' . PHP_EOL .
			'順次、担当者より折り返しご連絡させていただきます。' . PHP_EOL .
			PHP_EOL .
			'E-MAIL（ハッピー代表）: happy@kyoto-happy.co.jp' . PHP_EOL .
			'URL: https://www.kyoto-happy.co.jp/' . PHP_EOL .
			'━━━━━━━━━━━━━━━━━━━━━━━━━━━━' . PHP_EOL .
			PHP_EOL .
			'※本メールにお心当たりのないお客様は、大変お手数ですが、上記までご連絡くださいますようお願い申し上げます。';
		
		//お客様控え
		$ret_user = $this->send(
			array(
				CONF::read('MAIL_ELEMENT.FROM') => CONF::read("UKS_WEBCOUNSELING.FROM"),
				CONF::read('MAIL_ELEMENT.TO') => $email,
				CONF::read('MAIL_ELEMENT.BCC') => $bcc_mail,
				CONF::read('MAIL_ELEMENT.SUBJECT') => $title_for_customer,
				CONF::read('MAIL_ELEMENT.MESSAGE') => StaticFunction::convert_zen_kana($message_for_customer) .
				PHP_EOL .
				$signature_message 
			)
		);

		//失敗した場合その旨ログを出力してfalseを返す
		if (!$ret_user) {
			LOGS_ERR('[ERROR] *** send mail failed eSystem *** address=' . $email);
			return false;
		}

		return true;
	}

	/*	 * **********************************
	 * NAME  : send_webcounseling_details_test
	 * INPUT : User choosen Webcouseling details
	 * OUTPUT: true / 送信成功の場合
	 *         false / 送信失敗の場合
	 * DESC  : mail sent after successful entry of records
	 * NOTICE:
	 * CREATE: 2021.10.05 UKS MS
	 * *********************************** */
	public function send_webcounseling_details_test($mail_contents, $email) {
		$bcc_mail = 'counseling@kyoto-happy.co.jp';
		//$bcc_mail = 'manjunathgouda@usindia.com';

		// DBからケアメンテ登録用メッセージの取得
		$mail = new MailMasterModel();

		// Setting variables to attach in mail
		$chart_no = $mail_contents['chartno'];
		$visitorno = $mail_contents['visitorno'];
		$amount = $mail_contents['amount'];
		$user_name = $mail_contents['user_name'];
		$ec_firstdocconfirm = (isset($mail_contents['AK006'])) ? $mail_contents['AK006'] : '';
		$ec_counselingchartok = (isset($mail_contents['AK007'])) ? $mail_contents['AK007'] : $mail_contents['AK001'];
		$ec_maintenancechange = (isset($mail_contents['SA001'])) ? 'はい' : 'いいえ';
		$ec_hopecontents = (isset($mail_contents['SA001'])) ? $mail_contents['SA001'] : '';
		$ec_wardrobeuse = (isset($mail_contents['SA002'])) ? 'はい' : 'いいえ';
		$ec_wardrobeusageperiod = (isset($mail_contents['SA002'])) ? $mail_contents['SA002'] : '';
		$ec_paymentmethod = (isset($mail_contents['AK008'])) ? $mail_contents['AK008'] : $mail_contents['AK002'];
		$ec_deliverydate = (isset($mail_contents['AK010'])) ? $mail_contents['AK010'] : $mail_contents['AK004'];
		$ec_deliverytime = (isset($mail_contents['AK011'])) ? $mail_contents['AK011'] : $mail_contents['AK005'];
		//$ec_shippingdate = $mail_contents['shippingdate'];
		$ec_reportscheduleddate = $mail_contents['reportscheduleddate'];
		
		$today = date('Y-m-d H:i:s');

		// if first time user
		if($ec_firstdocconfirm == 'はい') {
			$first_user = '「初めてのご利用のお客様へ」の内容確認： ' . $ec_firstdocconfirm;
		} else {
			$first_user = '';
		}

		// if maintaince change is opted
		if($ec_maintenancechange == 'はい') {
			$maintain_change_body = 'ご希望： ' . $ec_hopecontents . PHP_EOL;
		} else {
			$maintain_change_body = '';
		}

		//  if wadrobe is selected
		if($ec_wardrobeuse == 'はい') {
			$wadrobe_body = 'ご利用期間： ' . $ec_wardrobeusageperiod . '（ヶ月間）' . PHP_EOL;
		} else {
			$wadrobe_body = '';
		}

		//  if wadrobe is selected
		if($ec_counselingchartok == 'はい') {
			$payment = 'お支払い方法： ' . $ec_paymentmethod . PHP_EOL;
			$deli_date = 'お届け希望日： ' . $ec_reportscheduleddate . PHP_EOL;
			$deli_time = 'お届け時間： ' . $ec_deliverytime . PHP_EOL;
		} else {
			$payment = '';
			$deli_date = '';
			$deli_time = '';
		}

		$title_for_customer = 'カウンセリングの回答を受付けました。';
		
		$message_for_customer = '' .
			$user_name . ' 様' . PHP_EOL .
			PHP_EOL .
			'ハッピーケアメンテでございます。' . PHP_EOL .
			'以下の内容で、カウンセリングの回答を受付けました。' . PHP_EOL . 
			PHP_EOL .
			'============================================================' . PHP_EOL .
			$first_user . PHP_EOL .
			'「カウンセリングカルテ」の内容で良い： ' . $ec_counselingchartok . PHP_EOL .
			'メンテナンスの変更： ' . $ec_maintenancechange . PHP_EOL .
			$maintain_change_body  .
			'「ハッピーワードローブ」利用： ' . $ec_wardrobeuse . PHP_EOL .
			$wadrobe_body . 
			$payment .
			$deli_date .
			$deli_time .
			'------------------------------------------------------------' .  PHP_EOL . 
			'ID： ' . $visitorno . PHP_EOL .
			'受付日時： ' . $today . PHP_EOL .
			'カルテ番号： ' . $chart_no . PHP_EOL .
			'============================================================' . PHP_EOL .
			'・上記回答内容によってお見積り金額等が変わる場合は、修正したカルテと共に再度メールにて「回答フォーム」をお送りいたします。' . PHP_EOL .
			'・お見積り金額等に変更がない場合は、お届け日時等のご案内メールをお送りしますので、いましばらくお待ちください。' . PHP_EOL .
			'・翌営業日を過ぎても当社からの応答がない場合は、恐れ入りますがご連絡くださいますようお願い申し上げます。' . PHP_EOL .
			'・その他、ご不明な点は下記までお気軽にご連絡くださいませ。' . PHP_EOL .
			'━━━━━━━━━━━━━━━━━━━━━━━━━━━━ ';
			
		$signature_message = '' .
			'株式会社ハッピー（カウンセラー代表）' . PHP_EOL .
			'E-MAIL: counseling@kyoto-happy.co.jp' . PHP_EOL .
			PHP_EOL .
			'〒611-0041 京都府宇治市槙島町目川７０番地の１' . PHP_EOL .
			'TEL ： 0120-88-6868  FAX ： 0120-88-3937' . PHP_EOL .
			'【営業時間】 月～土／ 9:00～18：00 （日・祝祭日除く）' . PHP_EOL .
			'営業時間外や電話が混み合っている場合は、お手数ですが音声' . PHP_EOL .
			'ガイダンスにしたがって、お名前・お電話番号・ご用件を録音してください。' . PHP_EOL .
			'順次、担当者より折り返しご連絡させていただきます。' . PHP_EOL .
			PHP_EOL .
			'E-MAIL（ハッピー代表）: happy@kyoto-happy.co.jp' . PHP_EOL .
			'URL: https://www.kyoto-happy.co.jp/' . PHP_EOL .
			'━━━━━━━━━━━━━━━━━━━━━━━━━━━━' . PHP_EOL .
			PHP_EOL .
			'※本メールにお心当たりのないお客様は、大変お手数ですが、上記までご連絡くださいますようお願い申し上げます。';
		
		//お客様控え
		$ret_user = $this->send(
			array(
				CONF::read('MAIL_ELEMENT.FROM') => CONF::read("UKS_WEBCOUNSELING.FROM"),
				//CONF::read('MAIL_ELEMENT.TO') => $email,
				//CONF::read('MAIL_ELEMENT.TO') => array(
					//'manjunathgouda@usindia.com',
					//'bharat@usindia.com'
				//),
				CONF::read('MAIL_ELEMENT.TO') => array(
					'y-imada@kyoto-happy.co.jp',
					'kandc1112@yahoo.co.jp'
				),
				CONF::read('MAIL_ELEMENT.BCC') => $bcc_mail,
				CONF::read('MAIL_ELEMENT.SUBJECT') => $title_for_customer,
				CONF::read('MAIL_ELEMENT.MESSAGE') => StaticFunction::convert_zen_kana($message_for_customer) .
				PHP_EOL .
				$signature_message 
			)
		);

		//失敗した場合その旨ログを出力してfalseを返す
		if (!$ret_user) {
			LOGS_ERR('[ERROR] *** send mail failed eSystem *** address=' . $email);
			return false;
		}

		return true;
	}

	// -------------------------------------------- UKS MS Webcounseling config ENDS ---------------------------------------------

	/*	 * **********************************
	 * NAME  : send_order_care_test
	 * INPUT : セッションから取得
	 * OUTPUT: true / 送信成功の場合
	 *         false / 送信失敗の場合
	 * DESC  :
	 * 		オーダー受付のメールを送る
	 * 		メールの署名、テキストをDBから取得
	 * NOTICE:
	 *  指定の仕方については、Mail.incのtemplate()を参照すること
	 * CREATE: 2016.10.18 aoyama
	 * UPDATE: 2016.11.14 aoyama
	 * 		友達紹介、ヤマトへの送信を追加
     * UPDATE: 2017.4.10 aoyama
     *      管理者宛のメールを半角カタカナに変換する
	 * *********************************** */
	public function send_order_care_test($sGroup, $sSpecial) {

		//パラメータチェック
		if (StaticFunction::is_empty(SESSION::read($sGroup))) {
			LOGS_MAIL('[ERROR] *** invalid parameter ***');
			return false;
		}

		// DBからケアメンテ登録用メッセージの取得
		$mail = new MailMasterModel();

		$title = $mail->get_mail_text('order_care_title');
		$message = $mail->get_mail_text('order_care');

		//受付日時を作成
		$date = DbDateTime::get_datetime_type_slash(DbDateTime::get_cur_datetime());

		//名前をセット
		$name = StaticFunction::marge_name(SESSION::read($sGroup . '.name1'), SESSION::read($sGroup . '.name2'));
		$kana = StaticFunction::marge_name(SESSION::read($sGroup . '.kana1'), SESSION::read($sGroup . '.kana2'));

		//住所文字列を整形
		$addr = "";
		$addr .= "〒" . SESSION::read($sGroup . '.zip') . " " . SESSION::read($sGroup . '.state');
		$addr .= SESSION::read($sGroup . '.addr1') . SESSION::read($sGroup . '.addr2') . SESSION::read($sGroup . '.addr3');

		//電話番号系を整形
		$tel = StaticFunction::marge_phone(SESSION::read($sGroup . '.telephone'), SESSION::read($sGroup . '.telephone2'), SESSION::read($sGroup . '.telephone3'));
		$fax = StaticFunction::marge_phone(SESSION::read($sGroup . '.faxnum'), SESSION::read($sGroup . '.faxnum2'), SESSION::read($sGroup . '.faxnum3'));

		//送付先住所を整形
		$s_addr = "";
		$s_addr .= "〒" . SESSION::read($sGroup . '.s_zip') . " " . SESSION::read($sGroup . '.s_state');
		$s_addr .= SESSION::read($sGroup . '.s_addr1') . SESSION::read($sGroup . '.s_addr2') . SESSION::read($sGroup . '.s_addr3');

		//送付先電話番号系を整形
		$s_tel = StaticFunction::marge_phone(SESSION::read($sGroup . '.s_telephone'), SESSION::read($sGroup . '.s_telephone2'), SESSION::read($sGroup . '.s_telephone3'));

		// 集荷日をスラッシュ型に変更
		$taking = DbDateTime::get_date_type_slash(StaticFunction::marge_birth(SESSION::read($sGroup . '.taking_y'), SESSION::read($sGroup . '.taking_m'), SESSION::read($sGroup . '.taking_d')));

		$carrier = SESSION::read($sGroup . '.carrier');
		if ($carrier == 0) { $carrier = 1; }

		$time_view_array = array();
		if (!StaticFunction::is_empty(SESSION::read($sGroup . '.time'))) {
			foreach (SESSION::read($sGroup . '.time') AS $value) {
                if (InputVali::is_array_key($value, CONF::read('SHIPPING_TIMEZONE_ARRAY_TEST.' . (string)$carrier))) {
					$time_view_array[] = CONF::read('SHIPPING_TIMEZONE_ARRAY_TEST.' . (string)$carrier . '.' . (string)$value);
				}
			}
		}
		$time_view = implode(PHP_EOL, $time_view_array);

		//アンケート
		$cause = (!StaticFunction::is_empty(SESSION::read($sGroup . '.cause'))) ? CONF::read("ORDER_ENQUETE." . SESSION::read($sGroup . '.cause')) : "";

		switch (SESSION::read($sGroup . '.cause')) {

			case 1:
				$cause_text = SESSION::read($sGroup . '.cause_t3') . PHP_EOL;
				break;
			case 2:
				$cause_text = SESSION::read($sGroup . '.cause_t1') . PHP_EOL;
				break;
			case 6:
				$cause_text = SESSION::read($sGroup . '.cause_t2') . PHP_EOL;
				break;
			default:
				$cause_text = "";
				break;
		}

		/*
		 * 基幹システムへの送信(ヤマトへの送信？)
		 * 友達紹介なら「紹介キャンペーン」が
		 * SALEページ経由も追加（2016.12.13）
		 */
		//友達紹介またはSALEページ経由ならメールのタイトルをセット
		$refer_friend_text = "";
		if (SESSION::read($sSpecial . '.mode') == CONF::read('REFER_FRIEND.PARAM')) {
			$refer_friend_text = "紹介キャンペーン ";
		}
		//友達紹介状態ならメールのタイトルをセット
		if (SESSION::read($sSpecial . '.mode') == CONF::read('REFER_SALE.PARAM')) {
			$refer_friend_text = "SALE ";
		}

		/*
		 * ※可変のものは置き換える
		 */
		$message_replace = StaticFunction::language_text_replace(array(
				'SEARCH' => array(
					'name1', 'kana1', 'addr', 'tel', 'fax', 'email',
					's_name1', 's_kana1', 's_addr', 's_tel',
					'taking', 'time', 'kutisu', 'catalog', 'mailmag', 'wardrobe',
					'carrier_notice',
					'cause', 'cause_text', 'user_id', 'date', 'sex', 'wkbn', 'refer_friend_text', 'comm'
				),
				'REPLACE' => array(
					$name,
					$kana,
					$addr,
					$tel,
					$fax,
					SESSION::read($sGroup . '.email'),
					SESSION::read($sGroup . '.s_name1'),
					SESSION::read($sGroup . '.s_kana1'),
					$s_addr,
					$s_tel,
					$taking,
					$time_view,
					SESSION::read($sGroup . '.kutisu'),
					CONF::read('CATALOG_ORDER.' . SESSION::read($sGroup . '.cat')),
					CONF::read('MAILMAG.' . SESSION::read($sGroup . '.mag')),
					CONF::read('WARDROBE_ORDER.' . SESSION::read($sGroup . '.kep')),
					CONF::read('SHIPPING_TRADER_MAIL_NOTICE.' . $carrier),
					$cause,
					$cause_text,
					SESSION::read(CONF::read('LOGIN_CATEGORY.PUBLIC') . '.system_user_id'),
					$date,
					SESSION::read($sGroup . '.sex'),
					SESSION::read($sGroup . '.wkbn'),
					$refer_friend_text,
					SESSION::read($sGroup . '.comm')
				),
				'TARGET' => $message
		));

		//お客様控えを送信
		$ret = $this->send(
			array(
				CONF::read('MAIL_ELEMENT.FROM') => CONF::read("MAIL_ORDER_TEST.FROM"),
				CONF::read('MAIL_ELEMENT.TO') => SESSION::read($sGroup . '.email'),
				CONF::read('MAIL_ELEMENT.BCC') => CONF::read("MAIL_ORDER_TEST.BCC"),
				CONF::read('MAIL_ELEMENT.SUBJECT') => $title,
				CONF::read('MAIL_ELEMENT.MESSAGE') =>
				StaticFunction::convert_zen_kana($message_replace) .
				PHP_EOL .
				PHP_EOL .
				$mail->get_mail_text('autograph') // 署名
			)
		);

		$email = SESSION::read($sGroup . '.email');
		//失敗した場合その旨ログを出力してfalseを返す
		if (!$ret) {
			LOGS_MAIL('[ERROR] *** send mail failed *** address=' . $email);
			return false;
		}

		$title_for_system = '申し込み控え ';
		$time_mail_text = "";
		foreach (SESSION::read($sGroup . '.time') AS $value) {
			$time_mail_text .= CONF::read('SHIPPING_TIMEZONE_ARRAY2_TEST.' . (string)$carrier . '.' . (string)$value) . PHP_EOL;
		}

		$message_for_system = '' .
			'-----------------------------------------------------------------' . PHP_EOL .
			'ケアメンテ申込受付通知' . PHP_EOL .
			'------------------------------------------------------------------' . PHP_EOL .
			'ケアメンテの申込を受け付けました。' . PHP_EOL .
			PHP_EOL .
			'電話番号： ' . StaticFunction::marge_phone(SESSION::read($sGroup . '.telephone'), SESSION::read($sGroup . '.telephone2'), SESSION::read($sGroup . '.telephone3')) . PHP_EOL .
			'運送業者： ' . CONF::read('SHIPPING_TRADER.' . $carrier) . PHP_EOL .
			'引取日： ' . StaticFunction::marge_birth(SESSION::read($sGroup . '.taking_y'), SESSION::read($sGroup . '.taking_m'), SESSION::read($sGroup . '.taking_d')) . PHP_EOL .
			'引取時間： ' . $time_mail_text .
			PHP_EOL .
			'-----------------------------------------------------------------' . PHP_EOL .
			'お客様情報欄' . PHP_EOL .
			'------------------------------------------------------------------' . PHP_EOL .
			'お名前： ' . StaticFunction::marge_name(SESSION::read($sGroup . '.name1'), SESSION::read($sGroup . '.name2')) . PHP_EOL .
			'ふりがな： ' . StaticFunction::convert_han_kana(StaticFunction::marge_name(SESSION::read($sGroup . '.kana1'), SESSION::read($sGroup . '.kana2'))) . PHP_EOL .
			'生年月日： ' . StaticFunction::marge_birth(SESSION::read($sGroup . '.birth_y'), SESSION::read($sGroup . '.birth_m'), SESSION::read($sGroup . '.birth_d')) . PHP_EOL .
			'郵便番号： ' . SESSION::read($sGroup . '.zip') . PHP_EOL .
			'都道府県： ' . SESSION::read($sGroup . '.state') . PHP_EOL .
			'住所1： ' . StaticFunction::convert_han_kana(SESSION::read($sGroup . '.addr1')) . PHP_EOL .
			'住所2： ' . StaticFunction::convert_han_kana(SESSION::read($sGroup . '.addr2')) . PHP_EOL .
			'住所3： ' . StaticFunction::convert_han_kana(SESSION::read($sGroup . '.addr3')) . PHP_EOL .
			'FAX番号： ' . StaticFunction::marge_phone(SESSION::read($sGroup . '.faxnum'), SESSION::read($sGroup . '.faxnum2'), SESSION::read($sGroup . '.faxnum3')) . PHP_EOL .
			'メールアドレス： ' . SESSION::read($sGroup . '.email') . PHP_EOL .
			'メールアドレス2： ' . SESSION::read($sGroup . '.email') . PHP_EOL .
			'送付先のお名前： ' . StaticFunction::marge_name(SESSION::read($sGroup . '.s_name1'), SESSION::read($sGroup . '.s_name2')) . PHP_EOL .
			'送付先のふりがな： ' . StaticFunction::convert_han_kana(StaticFunction::marge_name(SESSION::read($sGroup . '.s_kana1'), SESSION::read($sGroup . '.s_kana2'))) . PHP_EOL .
			'送付先の郵便番号： ' . SESSION::read($sGroup . '.s_zip') . PHP_EOL .
			'送付先の都道府県： ' . SESSION::read($sGroup . '.s_state') . PHP_EOL .
			'送付先の住所1： ' . StaticFunction::convert_han_kana(SESSION::read($sGroup . '.s_addr1')) . PHP_EOL .
			'送付先の住所2： ' . StaticFunction::convert_han_kana(SESSION::read($sGroup . '.s_addr2')) . PHP_EOL .
			'送付先の住所3： ' . StaticFunction::convert_han_kana(SESSION::read($sGroup . '.s_addr3')) . PHP_EOL .
			'送付先の電話番号： ' . StaticFunction::marge_phone(SESSION::read($sGroup . '.s_telephone'), SESSION::read($sGroup . '.s_telephone2'), SESSION::read($sGroup . '.s_telephone3')) . PHP_EOL .
			'利用規約： 同意する' . PHP_EOL .
			'今回利用されたきっかけ： ' . $cause . PHP_EOL .
			$cause_text .
			'ID： ' . SESSION::read(CONF::read('LOGIN_CATEGORY.PUBLIC') . '.system_user_id') . PHP_EOL .
			'受付日時： ' . $date . PHP_EOL .
			'性別： ' . SESSION::read($sGroup . '.sex') . PHP_EOL .
			'職種： ' . SESSION::read($sGroup . '.wkbn') . PHP_EOL .
			'通信欄： ' . $refer_friend_text . SESSION::read($sGroup . '.comm') . PHP_EOL .
			'------------------------------------------------------------------	';

		//管理者宛の控え
		$ret_system = $this->send_hankaku(
			array(
				CONF::read('MAIL_ELEMENT.FROM') => CONF::read("MAIL_ORDER_TEST.FROM"),
				CONF::read('MAIL_ELEMENT.TO') => CONF::read("MAIL_ORDER_TEST.TO"),
				CONF::read('MAIL_ELEMENT.SUBJECT') => $title_for_system,
				CONF::read('MAIL_ELEMENT.MESSAGE') => $message_for_system
			)
		);

		$email = CONF::read("MAIL_ORDER_TEST.TO");
		//失敗した場合その旨ログを出力してfalseを返す
		if (!$ret_system) {
			LOGS_ERR('[ERROR] *** send mail failed eSystem *** address=' . $email);
			return false;
		}

		//ヤマト宛のメール生成
		$message_for_yamato = '' .
			'-----------------------------------------------------------------' . PHP_EOL .
			'ケアメンテ申込受付通知' . PHP_EOL .
			'------------------------------------------------------------------' . PHP_EOL .
			'ケアメンテの申込を受け付けました。' . PHP_EOL .
			'運送業者： ' . CONF::read('SHIPPING_TRADER.' . $carrier) . PHP_EOL .
			'引取日： ' . StaticFunction::marge_birth(SESSION::read($sGroup . '.taking_y'), SESSION::read($sGroup . '.taking_m'), SESSION::read($sGroup . '.taking_d')) . PHP_EOL .
			'引取時間： ' . $time_mail_text .
			'-----------------------------------------------------------------' . PHP_EOL .
			'お客様情報欄' . PHP_EOL .
			'------------------------------------------------------------------' . PHP_EOL .
			'お名前： ' . StaticFunction::marge_name(SESSION::read($sGroup . '.name1'), SESSION::read($sGroup . '.name2')) . PHP_EOL .
			'ふりがな： ' . StaticFunction::convert_han_kana(StaticFunction::marge_name(SESSION::read($sGroup . '.kana1'), SESSION::read($sGroup . '.kana2'))) . PHP_EOL .
			'生年月日： ' . StaticFunction::marge_birth(SESSION::read($sGroup . '.birth_y'), SESSION::read($sGroup . '.birth_m'), SESSION::read($sGroup . '.birth_d')) . PHP_EOL .
			'郵便番号： ' . StaticFunction::format_zip_no_hyphen(SESSION::read($sGroup . '.zip')) . PHP_EOL .
			'都道府県： ' . SESSION::read($sGroup . '.state') . PHP_EOL .
			'住所1： ' . StaticFunction::convert_han_kana(SESSION::read($sGroup . '.addr1')) . PHP_EOL .
			'住所2： ' . StaticFunction::convert_han_kana(SESSION::read($sGroup . '.addr2')) . PHP_EOL .
			'住所3： ' . StaticFunction::convert_han_kana(SESSION::read($sGroup . '.addr3')) . PHP_EOL .
			'電話番号： ' . StaticFunction::marge_phone(SESSION::read($sGroup . '.telephone'), SESSION::read($sGroup . '.telephone2'), SESSION::read($sGroup . '.telephone3')) . PHP_EOL .
			'FAX番号： ' . StaticFunction::marge_phone(SESSION::read($sGroup . '.faxnum'), SESSION::read($sGroup . '.faxnum2'), SESSION::read($sGroup . '.faxnum3')) . PHP_EOL .
			'メールアドレス： ' . SESSION::read($sGroup . '.email') . PHP_EOL .
			'メールアドレス2： ' . SESSION::read($sGroup . '.email') . PHP_EOL .
			'送付先のお名前： ' . StaticFunction::marge_name(SESSION::read($sGroup . '.s_name1'), SESSION::read($sGroup . '.s_name2')) . PHP_EOL .
			'送付先のふりがな： ' . StaticFunction::convert_han_kana(StaticFunction::marge_name(SESSION::read($sGroup . '.s_kana1'), SESSION::read($sGroup . '.s_kana2'))) . PHP_EOL .
			'送付先の郵便番号： ' . SESSION::read($sGroup . '.s_zip') . PHP_EOL .
			'送付先の都道府県： ' . SESSION::read($sGroup . '.s_state') . PHP_EOL .
			'送付先の住所1： ' . StaticFunction::convert_han_kana(SESSION::read($sGroup . '.s_addr1')) . PHP_EOL .
			'送付先の住所2： ' . StaticFunction::convert_han_kana(SESSION::read($sGroup . '.s_addr2')). PHP_EOL .
			'送付先の住所3： ' . StaticFunction::convert_han_kana(SESSION::read($sGroup . '.s_addr3')) . PHP_EOL .
			'送付先の電話番号： ' . StaticFunction::marge_phone(SESSION::read($sGroup . '.s_telephone'), SESSION::read($sGroup . '.s_telephone2'), SESSION::read($sGroup . '.s_telephone3')) . PHP_EOL .
			'利用規約： 同意する' . PHP_EOL .
			'今回利用されたきっかけ： ' . $cause . PHP_EOL .
			$cause_text .
			'ID： ' . SESSION::read(CONF::read('LOGIN_CATEGORY.PUBLIC') . '.system_user_id') . PHP_EOL .
			'受付日時： ' . $date . PHP_EOL .
			'性別： ' . SESSION::read($sGroup . '.sex') . PHP_EOL .
			'職種： ' . SESSION::read($sGroup . '.wkbn') . PHP_EOL .
			'通信欄： ' . $refer_friend_text . SESSION::read($sGroup . '.comm') . PHP_EOL .
			'------------------------------------------------------------------	';
		//ヤマト宛の控え
		for ($i = 1; $i <= (int) SESSION::read($sGroup . '.kutisu'); $i++) {

			$title_for_yamato = '申し込み　（' . $i . '／' . SESSION::read($sGroup . '.kutisu') . '個口）';

			$yamato = $this->send_hankaku(
				array(
					CONF::read('MAIL_ELEMENT.FROM') => CONF::read("MAIL_YAMATO.FROM"),
					CONF::read('MAIL_ELEMENT.TO') => CONF::read("MAIL_YAMATO.TO"),
					CONF::read('MAIL_ELEMENT.SUBJECT') => $title_for_yamato,
					CONF::read('MAIL_ELEMENT.MESSAGE') => $message_for_yamato
				)
			);

			$email = CONF::read("MAIL_YAMATO.TO");
			//失敗した場合その旨ログを出力してfalseを返す
			if (!$yamato) {
				LOGS_ERR('[ERROR] *** send mail failed eSystem *** address=' . $email);
			}
		}

		return true;
	}

	// ------------------------------------------------- UKS MS Order Care Test mail config --------------------------------------------------
	// ------------------------------------------------- 2022-02-14 -------- START ---------------------------------------------

	/*	 * **********************************
	 * NAME  : send_order_care
	 * INPUT : セッションから取得
	 * OUTPUT: true / 送信成功の場合
	 *         false / 送信失敗の場合
	 * DESC  :
	 * 		オーダー受付のメールを送る
	 * 		メールの署名、テキストをDBから取得
	 * NOTICE:
	 *  指定の仕方については、Mail.incのtemplate()を参照すること
	 * *********************************** */
	public function send_order_care($sGroup, $sSpecial) {

		//パラメータチェック
		if (StaticFunction::is_empty(SESSION::read($sGroup))) {
			LOGS_MAIL('[ERROR] *** invalid parameter ***');
			return false;
		}

		// DBからケアメンテ登録用メッセージの取得
		$mail = new MailMasterModel();

		$title = $mail->get_mail_text('order_care_title');
		$message = $mail->get_mail_text('order_care');

		//受付日時を作成
		$date = DbDateTime::get_datetime_type_slash(DbDateTime::get_cur_datetime());

		//名前をセット
		$name = StaticFunction::marge_name(SESSION::read($sGroup . '.name1'), SESSION::read($sGroup . '.name2'));
		$kana = StaticFunction::marge_name(SESSION::read($sGroup . '.kana1'), SESSION::read($sGroup . '.kana2'));

		//住所文字列を整形
		$addr = "";
		$addr .= "〒" . SESSION::read($sGroup . '.zip') . " " . SESSION::read($sGroup . '.state');
		$addr .= SESSION::read($sGroup . '.addr1') . SESSION::read($sGroup . '.addr2') . SESSION::read($sGroup . '.addr3');

		//電話番号系を整形
		$tel = StaticFunction::marge_phone(SESSION::read($sGroup . '.telephone'), SESSION::read($sGroup . '.telephone2'), SESSION::read($sGroup . '.telephone3'));
		$fax = StaticFunction::marge_phone(SESSION::read($sGroup . '.faxnum'), SESSION::read($sGroup . '.faxnum2'), SESSION::read($sGroup . '.faxnum3'));

		//送付先住所を整形
		$s_addr = "";
		$s_addr .= "〒" . SESSION::read($sGroup . '.s_zip') . " " . SESSION::read($sGroup . '.s_state');
		$s_addr .= SESSION::read($sGroup . '.s_addr1') . SESSION::read($sGroup . '.s_addr2') . SESSION::read($sGroup . '.s_addr3');

		//送付先電話番号系を整形
		$s_tel = StaticFunction::marge_phone(SESSION::read($sGroup . '.s_telephone'), SESSION::read($sGroup . '.s_telephone2'), SESSION::read($sGroup . '.s_telephone3'));

		// 集荷日をスラッシュ型に変更
		$taking = DbDateTime::get_date_type_slash(StaticFunction::marge_birth(SESSION::read($sGroup . '.taking_y'), SESSION::read($sGroup . '.taking_m'), SESSION::read($sGroup . '.taking_d')));

		$carrier = SESSION::read($sGroup . '.carrier');
		if ($carrier == 0) { $carrier = 1; }

		$time_view_array = array();
		if (!StaticFunction::is_empty(SESSION::read($sGroup . '.time'))) {
			foreach (SESSION::read($sGroup . '.time') AS $value) {
                if (InputVali::is_array_key($value, CONF::read('SHIPPING_TIMEZONE_ARRAY.' . (string)$carrier))) {
					$time_view_array[] = CONF::read('SHIPPING_TIMEZONE_ARRAY.' . (string)$carrier . '.' . (string)$value);
				}
			}
		}
		$time_view = implode(PHP_EOL, $time_view_array);

		//アンケート
		/*
		//$cause = (!StaticFunction::is_empty(SESSION::read($sGroup . '.cause'))) ? CONF::read("ORDER_ENQUETE." . SESSION::read($sGroup . '.cause')) : "";
		
		switch (SESSION::read($sGroup . '.cause')) {

			case 1:
				$cause_text = SESSION::read($sGroup . '.cause_t3') . PHP_EOL;
				break;
			case 2:
				$cause_text = SESSION::read($sGroup . '.cause_t1') . PHP_EOL;
				break;
			case 6:
				$cause_text = SESSION::read($sGroup . '.cause_t2') . PHP_EOL;
				break;
			default:
				$cause_text = "";
				break;
		}
		*/
		// Added by Manjunthgouda on 20220214
		if(SESSION::read($sGroup . '.netsearchcheck') == '1') {
			$netsearchcheck = CONF::read("ORDER_ENQUETE_TEST.1") . ' [' .SESSION::read($sGroup . '.netsearchcomment') .']' . PHP_EOL;
			//$netsearchcomment = SESSION::read($sGroup . '.netsearchcomment') . PHP_EOL; 
		} else {
			$netsearchcheck = '';
			// $netsearchcomment = '';
		}

		if(SESSION::read($sGroup . '.webadvertisingcheck') == '1') {
			$webadvertisingcheck = CONF::read("ORDER_ENQUETE_TEST.2") . PHP_EOL; 
		} else {
			$webadvertisingcheck = '';
		}

		if(SESSION::read($sGroup . '.facebookcheck') == '1') {
			$facebookcheck = CONF::read("ORDER_ENQUETE_TEST.3") . PHP_EOL; 
		} else {
			$facebookcheck = '';
		}

		if(SESSION::read($sGroup . '.instagramcheck') == '1') {
			$instagramcheck = CONF::read("ORDER_ENQUETE_TEST.4") . PHP_EOL; 
		} else {
			$instagramcheck = '';
		}

		if(SESSION::read($sGroup . '.twittercheck') == '1') {
			$twittercheck = CONF::read("ORDER_ENQUETE_TEST.5") . PHP_EOL; 
		} else {
			$twittercheck = '';
		}

		if(SESSION::read($sGroup . '.youtubecheck') == '1') {
			$youtubecheck = CONF::read("ORDER_ENQUETE_TEST.6") . PHP_EOL; 
		} else {
			$youtubecheck = '';
		}

		if(SESSION::read($sGroup . '.shopcheck') == '1') {
			$shopcheck = CONF::read("ORDER_ENQUETE_TEST.7") . PHP_EOL; 
		} else {
			$shopcheck = '';
		}

		if(SESSION::read($sGroup . '.acquaintanceintroductioncheck') == '1') {
			$acquaintanceintroductioncheck = CONF::read("ORDER_ENQUETE_TEST.8") . PHP_EOL; 
		} else {
			$acquaintanceintroductioncheck = '';
		}

		if(SESSION::read($sGroup . '.tvcheck') == '1') {
			$tvcheck = CONF::read("ORDER_ENQUETE_TEST.9") . ' [' .SESSION::read($sGroup . '.tvcomment') .']' . PHP_EOL; 
			// $tvcomment = SESSION::read($sGroup . '.tvcomment') . PHP_EOL;
		} else {
			$tvcheck = '';
			//$tvcomment = '';
		}

		if(SESSION::read($sGroup . '.changeclothescheck') == '1') {
			$changeclothescheck = CONF::read("ORDER_ENQUETE_TEST.10") . PHP_EOL; 
		} else {
			$changeclothescheck = '';
		}

		if(SESSION::read($sGroup . '.salecheck') == '1') {
			$salecheck = CONF::read("ORDER_ENQUETE_TEST.11") . PHP_EOL; 
		} else {
			$salecheck = '';
		}

		if(SESSION::read($sGroup . '.otherscheck') == '1') {
			$otherscheck = CONF::read("ORDER_ENQUETE_TEST.12") . ' [' .SESSION::read($sGroup . '.otherscomment') .']' . PHP_EOL; 
			//$otherscomment = SESSION::read($sGroup . '.otherscomment') . PHP_EOL;
		} else {
			$otherscheck = '';
			//$otherscomment = '';
		}

		$cause = "" . PHP_EOL;
		$cause .= $netsearchcheck . $webadvertisingcheck . $facebookcheck . $instagramcheck . $twittercheck . $youtubecheck . $shopcheck . $acquaintanceintroductioncheck . $tvcheck . $changeclothescheck . $salecheck . $otherscheck;
		
		$cause_text = "";
		// $cause_text .= $netsearchcomment . $tvcomment . $otherscomment;

		/*
		 * 基幹システムへの送信(ヤマトへの送信？)
		 * 友達紹介なら「紹介キャンペーン」が
		 * SALEページ経由も追加（2016.12.13）
		 */
		//友達紹介またはSALEページ経由ならメールのタイトルをセット
		$refer_friend_text = "";
		if (SESSION::read($sSpecial . '.mode') == CONF::read('REFER_FRIEND.PARAM')) {
			$refer_friend_text = "紹介キャンペーン ";
		}
		//友達紹介状態ならメールのタイトルをセット
		if (SESSION::read($sSpecial . '.mode') == CONF::read('REFER_SALE.PARAM')) {
			$refer_friend_text = "SALE ";
		}

		/*
		 * ※可変のものは置き換える
		 */
		$message_replace = StaticFunction::language_text_replace(array(
				'SEARCH' => array(
					'name1', 'kana1', 'addr', 'tel', 'fax', 'email',
					's_name1', 's_kana1', 's_addr', 's_tel',
					'taking', 'time', 'kutisu', 'catalog', 'mailmag', 'wardrobe',
					'carrier_notice',
					'cause', 'cause_text', 'user_id', 'date', 'sex', 'wkbn', 'refer_friend_text', 'comm'
				),
				'REPLACE' => array(
					$name,
					$kana,
					$addr,
					$tel,
					$fax,
					SESSION::read($sGroup . '.email'),
					SESSION::read($sGroup . '.s_name1'),
					SESSION::read($sGroup . '.s_kana1'),
					$s_addr,
					$s_tel,
					$taking,
					$time_view,
					SESSION::read($sGroup . '.kutisu'),
					CONF::read('CATALOG_ORDER.' . SESSION::read($sGroup . '.cat')),
					CONF::read('MAILMAG.' . SESSION::read($sGroup . '.mag')),
					CONF::read('WARDROBE_ORDER.' . SESSION::read($sGroup . '.kep')),
					CONF::read('SHIPPING_TRADER_MAIL_NOTICE.' . $carrier),
					$cause,
					$cause_text,
					SESSION::read(CONF::read('LOGIN_CATEGORY.PUBLIC') . '.system_user_id'),
					$date,
					SESSION::read($sGroup . '.sex'),
					SESSION::read($sGroup . '.wkbn'),
					$refer_friend_text,
					SESSION::read($sGroup . '.comm')
				),
				'TARGET' => $message
		));

	 // SESSION::read($sGroup . '.email'), CONF::read('MAIL_ELEMENT.BCC') => CONF::read("MAIL_ORDER.BCC"),
		//お客様控えを送信
		$ret = $this->send(
			array(
				CONF::read('MAIL_ELEMENT.FROM') => CONF::read("MAIL_ORDER.FROM"),
				CONF::read('MAIL_ELEMENT.TO') => SESSION::read($sGroup . '.email'),
				CONF::read('MAIL_ELEMENT.BCC') => CONF::read("MAIL_ORDER.BCC"),
				CONF::read('MAIL_ELEMENT.SUBJECT') => $title,
				CONF::read('MAIL_ELEMENT.MESSAGE') =>
				StaticFunction::convert_zen_kana($message_replace) .
				PHP_EOL .
				PHP_EOL .
				$mail->get_mail_text('autograph') // 署名
			)
		);

		$email = SESSION::read($sGroup . '.email');
		//失敗した場合その旨ログを出力してfalseを返す
		if (!$ret) {
			LOGS_MAIL('[ERROR] *** send mail failed *** address=' . $email);
			return false;
		}

		$title_for_system = '申し込み控え ';
		$time_mail_text = "";
		foreach (SESSION::read($sGroup . '.time') AS $value) {
			$time_mail_text .= CONF::read('SHIPPING_TIMEZONE_ARRAY2.' . (string)$carrier . '.' . (string)$value) . PHP_EOL;
		}

		$message_for_system = '' .
			'-----------------------------------------------------------------' . PHP_EOL .
			'ケアメンテ申込受付通知' . PHP_EOL .
			'------------------------------------------------------------------' . PHP_EOL .
			'ケアメンテの申込を受け付けました。' . PHP_EOL .
			PHP_EOL .
			'電話番号： ' . StaticFunction::marge_phone(SESSION::read($sGroup . '.telephone'), SESSION::read($sGroup . '.telephone2'), SESSION::read($sGroup . '.telephone3')) . PHP_EOL .
			'運送業者： ' . CONF::read('SHIPPING_TRADER.' . $carrier) . PHP_EOL .
			'引取日： ' . StaticFunction::marge_birth(SESSION::read($sGroup . '.taking_y'), SESSION::read($sGroup . '.taking_m'), SESSION::read($sGroup . '.taking_d')) . PHP_EOL .
			'引取時間： ' . $time_mail_text .
			PHP_EOL .
			'-----------------------------------------------------------------' . PHP_EOL .
			'お客様情報欄' . PHP_EOL .
			'------------------------------------------------------------------' . PHP_EOL .
			'お名前： ' . StaticFunction::marge_name(SESSION::read($sGroup . '.name1'), SESSION::read($sGroup . '.name2')) . PHP_EOL .
			'ふりがな： ' . StaticFunction::convert_han_kana(StaticFunction::marge_name(SESSION::read($sGroup . '.kana1'), SESSION::read($sGroup . '.kana2'))) . PHP_EOL .
			'生年月日： ' . StaticFunction::marge_birth(SESSION::read($sGroup . '.birth_y'), SESSION::read($sGroup . '.birth_m'), SESSION::read($sGroup . '.birth_d')) . PHP_EOL .
			'郵便番号： ' . SESSION::read($sGroup . '.zip') . PHP_EOL .
			'都道府県： ' . SESSION::read($sGroup . '.state') . PHP_EOL .
			'住所1： ' . StaticFunction::convert_han_kana(SESSION::read($sGroup . '.addr1')) . PHP_EOL .
			'住所2： ' . StaticFunction::convert_han_kana(SESSION::read($sGroup . '.addr2')) . PHP_EOL .
			'住所3： ' . StaticFunction::convert_han_kana(SESSION::read($sGroup . '.addr3')) . PHP_EOL .
			'FAX番号： ' . StaticFunction::marge_phone(SESSION::read($sGroup . '.faxnum'), SESSION::read($sGroup . '.faxnum2'), SESSION::read($sGroup . '.faxnum3')) . PHP_EOL .
			'メールアドレス： ' . SESSION::read($sGroup . '.email') . PHP_EOL .
			'メールアドレス2： ' . SESSION::read($sGroup . '.email2') . PHP_EOL .
			'利用規約： 同意する' . PHP_EOL .
			'今回利用されたきっかけ： ' . 
			$cause . PHP_EOL .
			$cause_text .
			'ID： ' . SESSION::read(CONF::read('LOGIN_CATEGORY.PUBLIC') . '.system_user_id') . PHP_EOL .
			'受付日時： ' . $date . PHP_EOL .
			'性別： ' . SESSION::read($sGroup . '.sex') . PHP_EOL .
			'職種： ' . SESSION::read($sGroup . '.wkbn') . PHP_EOL .
			'通信欄： ' . $refer_friend_text . SESSION::read($sGroup . '.comm') . PHP_EOL .
			'------------------------------------------------------------------	';

		//管理者宛の控え
		$ret_system = $this->send_hankaku(
			array(
				CONF::read('MAIL_ELEMENT.FROM') => CONF::read("MAIL_ORDER.FROM"),
				CONF::read('MAIL_ELEMENT.TO') => CONF::read("MAIL_ORDER.TO"),
				CONF::read('MAIL_ELEMENT.SUBJECT') => $title_for_system,
				CONF::read('MAIL_ELEMENT.MESSAGE') => $message_for_system
			)
		);

		$email = CONF::read("MAIL_ORDER.TO");
		//失敗した場合その旨ログを出力してfalseを返す
		if (!$ret_system) {
			LOGS_ERR('[ERROR] *** send mail failed eSystem *** address=' . $email);
			return false;
		}

		//ヤマト宛のメール生成
		$message_for_yamato = '' .
			'-----------------------------------------------------------------' . PHP_EOL .
			'ケアメンテ申込受付通知' . PHP_EOL .
			'------------------------------------------------------------------' . PHP_EOL .
			'ケアメンテの申込を受け付けました。' . PHP_EOL .
			'運送業者： ' . CONF::read('SHIPPING_TRADER.' . $carrier) . PHP_EOL .
			'引取日： ' . StaticFunction::marge_birth(SESSION::read($sGroup . '.taking_y'), SESSION::read($sGroup . '.taking_m'), SESSION::read($sGroup . '.taking_d')) . PHP_EOL .
			'引取時間： ' . $time_mail_text .
			'-----------------------------------------------------------------' . PHP_EOL .
			'お客様情報欄' . PHP_EOL .
			'------------------------------------------------------------------' . PHP_EOL .
			'お名前： ' . StaticFunction::marge_name(SESSION::read($sGroup . '.name1'), SESSION::read($sGroup . '.name2')) . PHP_EOL .
			'ふりがな： ' . StaticFunction::convert_han_kana(StaticFunction::marge_name(SESSION::read($sGroup . '.kana1'), SESSION::read($sGroup . '.kana2'))) . PHP_EOL .
			'生年月日： ' . StaticFunction::marge_birth(SESSION::read($sGroup . '.birth_y'), SESSION::read($sGroup . '.birth_m'), SESSION::read($sGroup . '.birth_d')) . PHP_EOL .
			'郵便番号： ' . StaticFunction::format_zip_no_hyphen(SESSION::read($sGroup . '.zip')) . PHP_EOL .
			'都道府県： ' . SESSION::read($sGroup . '.state') . PHP_EOL .
			'住所1： ' . StaticFunction::convert_han_kana(SESSION::read($sGroup . '.addr1')) . PHP_EOL .
			'住所2： ' . StaticFunction::convert_han_kana(SESSION::read($sGroup . '.addr2')) . PHP_EOL .
			'住所3： ' . StaticFunction::convert_han_kana(SESSION::read($sGroup . '.addr3')) . PHP_EOL .
			'電話番号： ' . StaticFunction::marge_phone(SESSION::read($sGroup . '.telephone'), SESSION::read($sGroup . '.telephone2'), SESSION::read($sGroup . '.telephone3')) . PHP_EOL .
			'FAX番号： ' . StaticFunction::marge_phone(SESSION::read($sGroup . '.faxnum'), SESSION::read($sGroup . '.faxnum2'), SESSION::read($sGroup . '.faxnum3')) . PHP_EOL .
			'メールアドレス： ' . SESSION::read($sGroup . '.email') . PHP_EOL .
			'メールアドレス2： ' . SESSION::read($sGroup . '.email2') . PHP_EOL .
			'利用規約： 同意する' . PHP_EOL .
			'今回利用されたきっかけ： ' . 
			$cause . PHP_EOL .
			$cause_text .
			'ID： ' . SESSION::read(CONF::read('LOGIN_CATEGORY.PUBLIC') . '.system_user_id') . PHP_EOL .
			'受付日時： ' . $date . PHP_EOL .
			'性別： ' . SESSION::read($sGroup . '.sex') . PHP_EOL .
			'職種： ' . SESSION::read($sGroup . '.wkbn') . PHP_EOL .
			'通信欄： ' . $refer_friend_text . SESSION::read($sGroup . '.comm') . PHP_EOL .
			'------------------------------------------------------------------	';
		//ヤマト宛の控え
		for ($i = 1; $i <= (int) SESSION::read($sGroup . '.kutisu'); $i++) {

			$title_for_yamato = '申し込み　（' . $i . '／' . SESSION::read($sGroup . '.kutisu') . '個口）';
		 // CONF::read('MAIL_ELEMENT.TO') => CONF::read("MAIL_YAMATO.TO"),
			/*$yamato = $this->send_hankaku(
				array(
					CONF::read('MAIL_ELEMENT.FROM') => CONF::read("MAIL_YAMATO.FROM"),
					CONF::read('MAIL_ELEMENT.TO') => array(
						'y-imada@kyoto-happy.co.jp',
						'kandc1112@yahoo.co.jp',
						'bharat@usindia.com'
					),
					CONF::read('MAIL_ELEMENT.SUBJECT') => $title_for_yamato,
					CONF::read('MAIL_ELEMENT.MESSAGE') => $message_for_yamato
				)
			); */

			//$email = 'kandc1112@yahoo.co.jp';
			//失敗した場合その旨ログを出力してfalseを返す
			//if (!$yamato) {
				//LOGS_ERR('[ERROR] *** send mail failed eSystem *** address=' . $email);
			//}
		}

		return true;
	}

	// ---------------------------------------- manjunathgouda Order Care test end -------------------------------------------------------------

	/*	 * **********************************
	 * NAME  : send_password_reset_complete
	 * INPUT : $mail / string / 送り先人名
	 *         $password / string / パスワード
	 * OUTPUT: true / 送信成功の場合
	 *         false / 送信失敗の場合
	 * DESC  :
	 * 		パスワードを記載したメールを送る
	 * NOTICE:
	 * CREATE: 2016.11.8 aoyama
	 * *********************************** */
	public function send_password_reset($mail, $password) {

		//パラメータチェック
		if (empty($mail) || empty($password)) {
			LOGS_MAIL('[ERROR] *** invalid parameter ***');
			return false;
		}

		$message = "------------------------------------------------------------------" . PHP_EOL .
			"パスワードのお知らせ" . PHP_EOL .
			"------------------------------------------------------------------" . PHP_EOL .
			"いつもハッピーケアメンテをご利用いただきありがとうございます。" . PHP_EOL .
			PHP_EOL .
			"お問い合わせのありましたパスワードをお知らせいたします。" . PHP_EOL .
			"パスワード：" . $password . PHP_EOL .
			PHP_EOL .
			"■ログインは下記のURLよりお願いいたします。" . PHP_EOL .
			"https://www.kyoto-happy.co.jp/login/" . PHP_EOL .
			PHP_EOL .
			"※このメールは送信専用メールアドレスから配信されております。" . PHP_EOL .
			"このメールにご返信いただきましても、お答えできませんのでご了承ください。" . PHP_EOL .
			"お問い合わせは下記のメールアドレスへお願いいたします。" . PHP_EOL .
			"E-MAIL: happy@kyoto-happy.co.jp" . PHP_EOL .
			PHP_EOL .
			"============================================================" . PHP_EOL .
			"●申込した覚えがない方へ" . PHP_EOL .
			"上記日時に申し込みをされた覚えがない場合は、似たアドレスをお持ちの方が" . PHP_EOL .
			"誤って申し込みをされた可能性があります。" . PHP_EOL .
			"お心あたりのない場合は、たいへんお手数ですが、" . PHP_EOL .
			"送信者 happy@kyoto-happy.co.jp までお知らせいただくとともに、" . PHP_EOL .
			"本メールを削除くださいますようお願い申し上げます。" . PHP_EOL .
			PHP_EOL .
			"ご不明な点がございましたら、下記までお気軽にご連絡くださいませ。" . PHP_EOL .
			PHP_EOL .
			"━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━" . PHP_EOL .
			"株式会社 ハッピー　" . PHP_EOL .
			"〒611-0041 京都府宇治市槙島町目川７０番地の１" . PHP_EOL .
			"TEL ： 0120-88-6868  FAX ： 0120-88-3937" . PHP_EOL .
			PHP_EOL .
			"【営業時間】 月～土／ 9:00～18：00 （日・祝祭日除く）" . PHP_EOL .
			"営業時間外や電話が混み合っている場合は、お手数ですが音声ガイダンスに" . PHP_EOL .
			"したがってお名前・お電話番号・ご用件を録音してください。" . PHP_EOL .
			"順次、担当者より折り返しご連絡させていただきます。" . PHP_EOL .
			PHP_EOL .
			"【カウンセリング対応時間のご案内】" . PHP_EOL .
			"カウンセリングにつきましては、本社営業日（日曜・祝祭日を除く月～土）" . PHP_EOL .
			"の 9：00～18：30 の間で対応させていただきますことをご了承ください。" . PHP_EOL .
			PHP_EOL .
			"E-MAIL: happy@kyoto-happy.co.jp" . PHP_EOL .
			"URL ： https://www.kyoto-happy.co.jp/" . PHP_EOL .
			"━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━";

		$ret = $this->send(
			array(
				CONF::read('MAIL_ELEMENT.FROM') => CONF::read("MAIL_ENTRY.FROM"),
				CONF::read('MAIL_ELEMENT.TO') => $mail,
				CONF::read('MAIL_ELEMENT.SUBJECT') => "パスワード再発行のお知らせ",
				CONF::read('MAIL_ELEMENT.MESSAGE') => StaticFunction::convert_zen_kana($message)
			)
		);

		//失敗した場合その旨ログを出力してfalseを返す
		if (!$ret) {
			LOGS_MAIL('[ERROR] *** send mail failed *** address=' . $message);
			return false;
		}

		return true;
	}

	/*	 * **********************************
	 * NAME  : send_user_info_change
	 * INPUT : mail_address_new / string / 変更後のメールアドレス
	 * 		   mail_address_old / string / 変更前のメールアドレス
	 * OUTPUT: true / 送信成功の場合
	 *         false / 送信失敗の場合
	 * DESC  :
	 * マイページのユーザ情報変更時に送信する。
	 * 旧メールアドレスと新メールアドレスに変更した旨を送信する。
	 * 旧メールアドレスが使用できない場合も想定して
	 * 認証はなしとする。
	 *
	 * NOTICE:
	 *  指定の仕方については、Mail.incのtemplate()を参照すること
	 * CREATE: 2015.11.25 sonoda
	 * UPDATE: 2016.10.07 hesaka ベーステキストをlanguage_textから読み込むように変更
	 * *********************************** */
	public function send_user_info_change($mail_address_new = '', $mail_address_old = '') {

		//パラメータチェック
		if (empty($mail_address_new) || empty($mail_address_old)) {
			LOGS_MAIL('[ERROR] *** invalid parameter ***');
			return false;
		}

		$ret = $this->send(
			array(
				CONF::read('MAIL_ELEMENT.FROM') => CONF::read("MAIL_ADDRESS.FROM"),
				CONF::read('MAIL_ELEMENT.TO') => $mail_address_new,
				CONF::read('MAIL_ELEMENT.CC') => $mail_address_old,
				//CONF::read('MAIL_ELEMENT.BCC') => CONF::read("MAIL_ADDRESS.ADMIN"),
				CONF::read('MAIL_ELEMENT.SUBJECT') => CONF::read('LANG_TEXT.MAIL.USER_INFO_CHANGE.TITLE'),
				CONF::read('MAIL_ELEMENT.MESSAGE') =>
				CONF::read('LANG_TEXT.MAIL.USER_INFO_CHANGE.MESSAGE') .
				PHP_EOL .
				$this->get_autograph()
			)
		);

		//失敗した場合その旨ログを出力してfalseを返す
		if (!$ret) {
			LOGS_MAIL('[ERROR] *** send mail failed *** address=' . $mail_address_new . ', ' . $mail_address_old);
			return false;
		}

		LOGS_MAIL('[SUCCESS] send mail success. address=' . $mail_address_new . ', ' . $mail_address_old);
		return true;
	}

	/*	 * **********************************
	 * NAME  : send_frend_complete
	 * INPUT : name / string / 送り先人名
	 *         mail_address / string / メールアドレス
	 * OUTPUT: true / 送信成功の場合
	 *         false / 送信失敗の場合
	 * DESC  :
	 * 		友達紹介のメールを送る
	 * 		送信者、受信者双方に送信する。
	 * 		メールの署名、テキストをDBから取得
	 * NOTICE:
	 *  指定の仕方については、Mail.incのtemplate()を参照すること
	 * CREATE: 2015.10.18 aoyama
	 * UPDATE: 2016.11.14 aoyama
	 * 		友達紹介のURLもリプレース化
	 * *********************************** */
	public function send_frend_complete($mail_param) {

		//パラメータチェック
		if (StaticFunction::is_empty($mail_param)) {
			LOGS_MAIL('[ERROR] *** invalid parameter ***');
			return false;
		}

		// DBからメール用テキストの取得用インスタンス
		$mail = new MailMasterModel();

		//受信者へのメールを構成
		$target_title = $mail->get_mail_text('friend_send_target_title');
		$target_message = $mail->get_mail_text('friend_send_target');

		$target_title_replace = StaticFunction::language_text_replace(array(
				'SEARCH' => array('name1'),
				'REPLACE' => array($mail_param['name']),
				'TARGET' => $target_title
		));

		$target_message_replace = StaticFunction::language_text_replace(array(
				'SEARCH' => array('friend_name', 'friend_email', 'name1', 'email', 'comment', 'friend_url'),
				'REPLACE' => array($mail_param['friend_name'], $mail_param['friend_email'], $mail_param['name'], $mail_param['email'], $mail_param['comment'], CONF::read('SITE_URL.HOME') . CONF::read('REFER_FRIEND.MAIL_TARGET_URL')),
				'TARGET' => $target_message
		));

		//送信者へのメール
		$title = $mail->get_mail_text('friend_send_title');
		$message = $mail->get_mail_text('friend_send');

		$title_replace = StaticFunction::language_text_replace(array(
				'SEARCH' => array('friend_name'),
				'REPLACE' => array($mail_param['friend_name']),
				'TARGET' => $title
		));
		$message_replace = StaticFunction::language_text_replace(array(
				'SEARCH' => array('friend_name', 'friend_email', 'name1', 'email'),
				'REPLACE' => array($mail_param['friend_name'], $mail_param['friend_email'], $mail_param['name'], $mail_param['email']),
				'TARGET' => $message
		));

		//受信者へのメール送信処理
		$ret_target = $this->send(
			array(
				CONF::read('MAIL_ELEMENT.FROM') => CONF::read("MAIL_ADDRESS.FROM"),
				CONF::read('MAIL_ELEMENT.TO') => $mail_param['friend_email'],
				//CONF::read('MAIL_ELEMENT.BCC') => CONF::read("MAIL_ADDRESS.ADMIN"),
				CONF::read('MAIL_ELEMENT.SUBJECT') => $target_title_replace,
				CONF::read('MAIL_ELEMENT.MESSAGE') =>
				StaticFunction::convert_zen_kana($target_message_replace) .
				PHP_EOL .
				PHP_EOL .
				$mail->get_mail_text('autograph') // 署名
			)
		);

		//失敗した場合その旨ログを出力してfalseを返す
		if (!$ret_target) {
			LOGS_MAIL('[ERROR] *** send mail failed(target) *** address=' . $mail_param['friend_email']);
			return false;
		}

		//送信者へのメール送信処理
		$ret = $this->send(
			array(
				CONF::read('MAIL_ELEMENT.FROM') => CONF::read("MAIL_ADDRESS.FROM"),
				CONF::read('MAIL_ELEMENT.TO') => $mail_param['email'],
				//CONF::read('MAIL_ELEMENT.BCC') => CONF::read("MAIL_ADDRESS.ADMIN"),
				CONF::read('MAIL_ELEMENT.SUBJECT') => $title_replace,
				CONF::read('MAIL_ELEMENT.MESSAGE') =>
				StaticFunction::convert_zen_kana($message_replace . $target_message_replace) .
				PHP_EOL .
				PHP_EOL .
				$mail->get_mail_text('autograph') // 署名
			)
		);

		//失敗した場合その旨ログを出力してfalseを返す
		if (!$ret) {
			LOGS_MAIL('[ERROR] *** send mail failed *** address=' . $mail_param['email']);
			return false;
		}

		return true;
	}

	/*	 * **********************************
	 * NAME  : send_user_add_complete
	 * INPUT : name / string / 送り先人名
	 *         mail_address / string / メールアドレス
	 *         token / string / トークン
	 * OUTPUT: true / 送信成功の場合
	 *         false / 送信失敗の場合
	 * DESC  :
	 * 		会員登録受付のメールを送る
	 * NOTICE:
	 *  指定の仕方については、Mail.incのtemplate()を参照すること
	 * CREATE: 2015.10.28 aoyama
	 * UPDATE: 2016.10.07 hesaka ベーステキストをlanguage_textから読み込むように変更
	 * UPDATE: 2016.10.17 aoyama
	 * 		メールの署名、テキストをDBから取得
	 * *********************************** */
	public function send_user_add_complete($system_user_id, $pass, $name = '', $mail_address = '') {

		//パラメータチェック
		if (empty($name) || empty($mail_address)) {
			LOGS_MAIL('[ERROR] *** invalid parameter ***');
			return false;
		}

		// DBから会員登録用メッセージの取得
		$mail = new MailMasterModel();

		$message = $mail->get_mail_text('user_add');
		$title = $mail->get_mail_text('user_add_title');

		/*
		 * current_languageに合わせたメール内容を取得
		 * ※可変のものは置き換える
		 * 一時停止（2016.10.17 aoyama）
		 */
		$message = StaticFunction::language_text_replace(array(
				'SEARCH' => array('name1', 'syste_user_id', 'password'),
				'REPLACE' => array($name, $system_user_id, $pass),
				'TARGET' => $message
		));

		$ret = $this->send(
			array(
				CONF::read('MAIL_ELEMENT.FROM') => CONF::read("MAIL_ADDRESS.FROM"),
				CONF::read('MAIL_ELEMENT.TO') => $mail_address,
				//CONF::read('MAIL_ELEMENT.BCC') => CONF::read("MAIL_ADDRESS.ADMIN"),
				CONF::read('MAIL_ELEMENT.SUBJECT') => $title,
				CONF::read('MAIL_ELEMENT.MESSAGE') =>
				StaticFunction::convert_zen_kana($message) .
				PHP_EOL .
				PHP_EOL .
				$mail->get_mail_text('autograph') // 署名
			)
		);

		//失敗した場合その旨ログを出力してfalseを返す
		if (!$ret) {
			LOGS_MAIL('[ERROR] *** send mail failed *** address=' . $mail_address);
			return false;
		}

		LOGS_MAIL('[SUCCESS] send mail success. address=' . $mail_address);
		return true;
	}

	/*	 * **********************************
	 * NAME  : send_catalog_add_complete
	 * INPUT : name / string / 送り先人名
	 *         mail_address / string / メールアドレス
	 * OUTPUT: true / 送信成功の場合
	 *         false / 送信失敗の場合
	 * DESC  :
	 * 		会員登録受付のメールを送る
	 * NOTICE:
	 *  指定の仕方については、Mail.incのtemplate()を参照すること
	 * CREATE: 2016.10.17 aoyama
	 * UPDATE: 2016.10.17 aoyama
	 * 		メールの署名、テキストをDBから取得
	 * *********************************** */
	public function send_catalog_add_complete($sGroup) {

		// DBから会員登録用メッセージの取得
		$mail = new MailMasterModel();

		$title = $mail->get_mail_text('catalog_add_title');
		$message = $mail->get_mail_text('catalog_add');

		$date = DbDateTime::get_datetime_type_slash(DbDateTime::get_cur_datetime());

		/*
		 * ※可変のものは置き換える
		 */
		$message = StaticFunction::language_text_replace(array(
				'SEARCH' => array('name1', 'kana1', 'birth', 'zip', 'addr', 'tel', 'fax', 'email', 'mag', 'entry_time'),
				'REPLACE' => array(
					StaticFunction::marge_name(SESSION::read($sGroup . '.name1'), SESSION::read($sGroup . '.name2')),
					StaticFunction::marge_name(SESSION::read($sGroup . '.kana1'), SESSION::read($sGroup . '.kana2')),
					StaticFunction::marge_birth_for_view(SESSION::read($sGroup . '.birth_y'), SESSION::read($sGroup . '.birth_m'), SESSION::read($sGroup . '.birth_d')),
					SESSION::read($sGroup . '.zip'),
					SESSION::read($sGroup . '.addr1') . SESSION::read($sGroup . '.addr2') . SESSION::read($sGroup . '.addr3'),
					StaticFunction::marge_phone(SESSION::read($sGroup . '.telephone'), SESSION::read($sGroup . '.telephone2'), SESSION::read($sGroup . '.telephone3')),
					StaticFunction::marge_phone(SESSION::read($sGroup . '.faxnum'), SESSION::read($sGroup . '.faxnum2'), SESSION::read($sGroup . '.faxnum3')),
					SESSION::read($sGroup . '.email'),
					SESSION::read($sGroup . '.mag'),
					DbDateTime::get_datetime_type_slash(DbDateTime::get_cur_datetime())
				),
				'TARGET' => $message
		));


		/*
		 * 入力者への送信
		 */
		$ret = $this->send(
			array(
				CONF::read('MAIL_ELEMENT.FROM') => CONF::read("MAIL_ADDRESS.FROM"),
				CONF::read('MAIL_ELEMENT.TO') => SESSION::read($sGroup . '.email'),
				CONF::read('MAIL_ELEMENT.SUBJECT') => $title,
				CONF::read('MAIL_ELEMENT.MESSAGE') =>
				StaticFunction::convert_zen_kana($message) .
				PHP_EOL .
				PHP_EOL .
				$mail->get_mail_text('autograph') // 署名
			)
		);

		//失敗した場合その旨ログを出力するがスルー
		if (!$ret) {
			LOGS_ERR('[ERROR] *** send mail failed *** address=' . $email);
		}

		/*
		 * 基幹システムへの送信
		 */
		$title_for_system = '申し込み　カタログ';
		$message_for_system = '' .
			'-----------------------------------------------------------------' . PHP_EOL .
			'カタログ申込受付通知' . PHP_EOL .
			'------------------------------------------------------------------' . PHP_EOL .
			'カタログの申込を受け付けました。' . PHP_EOL .
			PHP_EOL .
			'お名前： ' . StaticFunction::marge_name(SESSION::read($sGroup . '.name1'), SESSION::read($sGroup . '.name2')) . PHP_EOL .
			'ふりがな： ' . StaticFunction::marge_name(SESSION::read($sGroup . '.kana1'), SESSION::read($sGroup . '.kana2')) . PHP_EOL .
			'生年月日： ' . StaticFunction::marge_birth(SESSION::read($sGroup . '.birth_y'), SESSION::read($sGroup . '.birth_m'), SESSION::read($sGroup . '.birth_d')) . PHP_EOL .
			'郵便番号： ' . SESSION::read($sGroup . '.zip') . PHP_EOL .
			'都道府県： ' . SESSION::read($sGroup . '.state') . PHP_EOL .
			'住所1： ' . SESSION::read($sGroup . '.addr1') . PHP_EOL .
			'住所2： ' . SESSION::read($sGroup . '.addr2') . PHP_EOL .
			'住所3： ' . SESSION::read($sGroup . '.addr3') . PHP_EOL .
			'電話番号： ' . StaticFunction::marge_phone(SESSION::read($sGroup . '.telephone'), SESSION::read($sGroup . '.telephone2'), SESSION::read($sGroup . '.telephone3')) . PHP_EOL .
			'FAX番号： ' . StaticFunction::marge_phone(SESSION::read($sGroup . '.faxnum'), SESSION::read($sGroup . '.faxnum2'), SESSION::read($sGroup . '.faxnum3')) . PHP_EOL .
			'メールアドレス： ' . SESSION::read($sGroup . '.email') . PHP_EOL .
			'メールマガジン： ' . SESSION::read($sGroup . '.mag') . PHP_EOL .
			'受付日時： ' . DbDateTime::get_datetime_type_slash(DbDateTime::get_cur_datetime()) . PHP_EOL .
			'------------------------------------------------------------------	';

		$ret_system = $this->send(
			array(
				CONF::read('MAIL_ELEMENT.FROM') => CONF::read("MAIL_ES.FROM"),
				CONF::read('MAIL_ELEMENT.TO') => CONF::read("MAIL_ES.TO"),
				CONF::read('MAIL_ELEMENT.SUBJECT') => $title_for_system,
				CONF::read('MAIL_ELEMENT.MESSAGE') => StaticFunction::convert_zen_kana($message_for_system)
			)
		);
		//失敗した場合その旨ログを出力してfalseを返す
		if (!$ret_system) {
			LOGS_ERR('[ERROR] *** send mail failed eSystem *** address=' . $email);
			return false;
		}


		return true;
	}

	/*	 * **********************************
	 * NAME  : send_contact
	 * INPUT : name / string / 送り先人名
	 *         mail_address / string / メールアドレス
	 * OUTPUT: true / 送信成功の場合
	 *         false / 送信失敗の場合
	 * DESC  :
	 * 		お問合せを基幹システムに送る
	 * NOTICE:
	 * CREATE: 2016.11.9 aoyama
	 * *********************************** */
	public function send_contact($sGroup) {

		/*
		 * 基幹システムへの送信
		 */
		$title_for_system = '申込　ハッピーへのメール受付';
		$message_for_system = '' .
			'-----------------------------------------------------------------' . PHP_EOL .
			'ハッピーへのメール受付通知' . PHP_EOL .
			'------------------------------------------------------------------' . PHP_EOL .
			PHP_EOL .
			'お名前： ' . StaticFunction::marge_name(SESSION::read($sGroup . '.name1'), SESSION::read($sGroup . '.name2')) . PHP_EOL .
			'ふりがな： ' . StaticFunction::marge_name(SESSION::read($sGroup . '.kana1'), SESSION::read($sGroup . '.kana2')) . PHP_EOL .
			'電話番号： ' . StaticFunction::marge_phone(SESSION::read($sGroup . '.telephone'), SESSION::read($sGroup . '.telephone2'), SESSION::read($sGroup . '.telephone3')) . PHP_EOL .
			'メールアドレス： ' . SESSION::read($sGroup . '.email') . PHP_EOL .
			'都道府県： ' . SESSION::read($sGroup . '.state') . PHP_EOL .
			'内容： ' . SESSION::read($sGroup . '.comment') . PHP_EOL .
			'受付日時： ' . DbDateTime::get_datetime_type_slash(DbDateTime::get_cur_datetime()) . PHP_EOL .
			'------------------------------------------------------------------	';

		$ret_system = $this->send(
			array(
				CONF::read('MAIL_ELEMENT.FROM') => CONF::read("MAIL_ES.FROM"),
				CONF::read('MAIL_ELEMENT.TO') => CONF::read("MAIL_ES.TO"),
				CONF::read('MAIL_ELEMENT.SUBJECT') => $title_for_system,
				CONF::read('MAIL_ELEMENT.MESSAGE') => StaticFunction::convert_zen_kana($message_for_system)
			)
		);
		//失敗した場合その旨ログを出力してfalseを返す
		if (!$ret_system) {
			LOGS_ERR('[ERROR] *** send mail failed eSystem *** address=' . $email);
			return false;
		}

		return true;
	}

	/*	 * **********************************
	 * NAME  : send_mailmag_add_complete
	 * INPUT : name / string / 送り先人名
	 *         mail_address / string / メールアドレス
	 * OUTPUT: true / 送信成功の場合
	 *         false / 送信失敗の場合
	 * DESC  :
	 * 		会員登録受付のメールを送る
	 * NOTICE:
	 *  指定の仕方については、Mail.incのtemplate()を参照すること
	 * CREATE: 2016.10.17 aoyama
	 * UPDATE: 2016.10.17 aoyama
	 * 		メールの署名、テキストをDBから取得
	 * *********************************** */
	public function send_mailmag_add_complete($sGroup) {

		// DBから会員登録用メッセージの取得
		$mail = new MailMasterModel();

		$title = $mail->get_mail_text('maimag_add_title');
		$message = $mail->get_mail_text('mailmag_add');

		$date = DbDateTime::get_datetime_type_slash(DbDateTime::get_cur_datetime());

		/*
		 * ※可変のものは置き換える
		 */
		$message = StaticFunction::language_text_replace(array(
				'SEARCH' => array('name1', 'email', 'zip', 'state', 'addr1', 'addr2', 'addr3', 'tel', 'fax', 'entry_time'),
				'REPLACE' => array(
					StaticFunction::marge_name(SESSION::read($sGroup . '.name1'), SESSION::read($sGroup . '.name2')),
					SESSION::read($sGroup . '.email'),
					SESSION::read($sGroup . '.zip'),
					SESSION::read($sGroup . '.state'),
					SESSION::read($sGroup . '.addr1'),
					SESSION::read($sGroup . '.addr2'),
					SESSION::read($sGroup . '.addr3'),
					StaticFunction::marge_phone(SESSION::read($sGroup . '.telephone'), SESSION::read($sGroup . '.telephone2'), SESSION::read($sGroup . '.telephone3')),
					StaticFunction::marge_phone(SESSION::read($sGroup . '.faxnum'), SESSION::read($sGroup . '.faxnum2'), SESSION::read($sGroup . '.faxnum3')),
					$date
				),
				'TARGET' => $message
		));

		$ret = $this->send(
			array(
				CONF::read('MAIL_ELEMENT.FROM') => CONF::read("MAIL_ADDRESS.FROM"),
				CONF::read('MAIL_ELEMENT.TO') => SESSION::read($sGroup . '.email'),
				CONF::read('MAIL_ELEMENT.SUBJECT') => $title,
				CONF::read('MAIL_ELEMENT.MESSAGE') =>
				StaticFunction::convert_zen_kana($message) .
				PHP_EOL .
				PHP_EOL .
				$mail->get_mail_text('autograph') // 署名
			)
		);

		//失敗した場合その旨ログを出力してfalseを返す
		if (!$ret) {
			LOGS_ERR('[ERROR] *** send mail failed *** address=' . $email);
		}

		/*
		 * 基幹システムへの送信
		 */
		$title_for_system = '申込　ケアメンテ メルマガ登録受付';
		$message_for_system = '' .
			'-----------------------------------------------------------------' . PHP_EOL .
			'ケアメンテ メルマガ登録を受付けました' . PHP_EOL .
			'-----------------------------------------------------------------' . PHP_EOL .
			PHP_EOL .
			'お名前： ' . StaticFunction::marge_name(SESSION::read($sGroup . '.name1'), SESSION::read($sGroup . '.name2')) . PHP_EOL .
			'メールアドレス： ' . SESSION::read($sGroup . '.email') . PHP_EOL .
			'郵便番号： ' . SESSION::read($sGroup . '.zip') . PHP_EOL .
			'住所： ' . SESSION::read($sGroup . '.state') . SESSION::read($sGroup . '.addr1') . SESSION::read($sGroup . '.addr2') . SESSION::read($sGroup . '.addr3') . PHP_EOL .
			'電話番号： ' . StaticFunction::marge_phone(SESSION::read($sGroup . '.telephone'), SESSION::read($sGroup . '.telephone2'), SESSION::read($sGroup . '.telephone3')) . PHP_EOL .
			'FAX番号： ' . StaticFunction::marge_phone(SESSION::read($sGroup . '.faxnum'), SESSION::read($sGroup . '.faxnum2'), SESSION::read($sGroup . '.faxnum3')) . PHP_EOL .
			'受付日時： ' . $date . PHP_EOL .
			'------------------------------------------------------------------';

		$ret_system = $this->send(
			array(
				CONF::read('MAIL_ELEMENT.FROM') => CONF::read("MAIL_ES.FROM"),
				CONF::read('MAIL_ELEMENT.TO') => CONF::read("MAIL_ES.TO"),
				CONF::read('MAIL_ELEMENT.SUBJECT') => $title_for_system,
				CONF::read('MAIL_ELEMENT.MESSAGE') => StaticFunction::convert_zen_kana($message_for_system)
			)
		);
		//失敗した場合その旨ログを出力してfalseを返す
		if (!$ret_system) {
			LOGS_ERR('[ERROR] *** send mail failed eSystem *** address=' . $email);
			return false;
		}

		return true;
	}

	/*	 * **********************************
	 * NAME  : send_user_add_complete_mail
	 * INPUT : name / string / 送り先人名
	 *         mail_address / string / メールアドレス
	 * OUTPUT: true / 送信成功の場合
	 *         false / 送信失敗の場合
	 * DESC  :
	 *  メール認証完了後の会員登録完了メールを送信する
	 * NOTICE:
	 * CREATE: 2015.10.29 aoyama
	 * UPDATE: 2016.10.07 hesaka ベーステキストをlanguage_textから読み込むように変更
	 * *********************************** */
	public function send_user_add_complete_mail($name = '', $mail_address = '') {

		//パラメータチェック
		if (empty($name) || empty($mail_address)) {
			LOGS_MAIL('[ERROR] *** invalid parameter ***');
			return false;
		}

		/*
		 * current_languageに合わせたメール内容を取得
		 * ※可変のものは置き換える
		 */
		$message = StaticFunction::language_text_replace(array(
				'SEARCH' => array('name'),
				'REPLACE' => array($name),
				'TARGET' => CONF::read('LANG_TEXT.MAIL.USER_ADD_COMP.MESSAGE')
		));

		$ret = $this->send(
			array(
				CONF::read('MAIL_ELEMENT.FROM') => CONF::read("MAIL_ADDRESS.FROM"),
				CONF::read('MAIL_ELEMENT.TO') => $mail_address,
				//CONF::read('MAIL_ELEMENT.BCC') => CONF::read("MAIL_ADDRESS.ADMIN"),
				CONF::read('MAIL_ELEMENT.SUBJECT') => CONF::read('LANG_TEXT.MAIL.USER_ADD_COMP.TITLE'),
				CONF::read('MAIL_ELEMENT.MESSAGE') =>
				StaticFunction::convert_zen_kana($message) .
				PHP_EOL .
				PHP_EOL .
				$this->get_autograph()
			)
		);

		//失敗した場合その旨ログを出力してfalseを返す
		if (!$ret) {
			LOGS_MAIL('[ERROR] *** send mail failed *** address=' . $mail_address);
			return false;
		}

		/*
		 * 基幹システムへの送信
		 */
		$title_for_system = '申し込み　カタログ';
		$message_for_system = '' .
			'-----------------------------------------------------------------' . PHP_EOL .
			'カタログ申込受付通知' . PHP_EOL .
			'------------------------------------------------------------------' . PHP_EOL .
			'カタログの申込を受け付けました。' . PHP_EOL .
			PHP_EOL .
			'お名前： ' . StaticFunction::marge_name(SESSION::read($sGroup . '.name1'), SESSION::read($sGroup . '.name2')) . PHP_EOL .
			'ふりがな： ' . StaticFunction::marge_name(SESSION::read($sGroup . '.kana1'), SESSION::read($sGroup . '.kana2')) . PHP_EOL .
			'生年月日： ' . StaticFunction::marge_birth(SESSION::read($sGroup . '.birth_y'), SESSION::read($sGroup . '.birth_m'), SESSION::read($sGroup . '.birth_d')) . PHP_EOL .
			'郵便番号： ' . SESSION::read($sGroup . '.zip') . PHP_EOL .
			'都道府県： ' . SESSION::read($sGroup . '.state') . PHP_EOL .
			'住所1： ' . SESSION::read($sGroup . '.addr1') . PHP_EOL .
			'住所2： ' . SESSION::read($sGroup . '.addr2') . PHP_EOL .
			'住所3： ' . SESSION::read($sGroup . '.addr3') . PHP_EOL .
			'電話番号： ' . StaticFunction::marge_phone(SESSION::read($sGroup . '.telephone'), SESSION::read($sGroup . '.telephone2'), SESSION::read($sGroup . '.telephone3')) . PHP_EOL .
			'FAX番号： ' . StaticFunction::marge_phone(SESSION::read($sGroup . '.faxnum'), SESSION::read($sGroup . '.faxnum2'), SESSION::read($sGroup . '.faxnum3')) . PHP_EOL .
			'メールアドレス： ' . SESSION::read($sGroup . '.email') . PHP_EOL .
			'メールマガジン： ' . SESSION::read($sGroup . '.mag') . PHP_EOL .
			'受付日時： ' . DbDateTime::get_datetime_type_slash(DbDateTime::get_cur_datetime()) . PHP_EOL .
			'------------------------------------------------------------------	';

		$ret_system = $this->send(
			array(
				CONF::read('MAIL_ELEMENT.FROM') => CONF::read("MAIL_ES.FROM"),
				CONF::read('MAIL_ELEMENT.TO') => CONF::read("MAIL_ES.TO"),
				CONF::read('MAIL_ELEMENT.SUBJECT') => $title_for_system,
				CONF::read('MAIL_ELEMENT.MESSAGE') => StaticFunction::convert_zen_kana($message_for_system)
			)
		);
		//失敗した場合その旨ログを出力してfalseを返す
		if (!$ret_system) {
			LOGS_ERR('[ERROR] *** send mail failed eSystem *** address=' . $email);
			return false;
		}

		return true;
	}

	/*	 * **********************************
	 * NAME  : send_alert_developer
	 * INPUT : text / string / 内容説明
	 *         data / string / 処理に用いたデータ
	 * OUTPUT: NONE
	 * DESC  :
	 *  処理的に非常に問題のあるパスを通った場合に
	 *  エラー内容を開発者に通知するメールである
	 * NOTICE:
	 *  $dataには、配列の場合はjson_encode()したものを
	 *  渡すこと
	 * CREATE: 2015.13.04 hesaka
	 * UPDATE: 2016.10.07 hesaka ベーステキストをlanguage_textから読み込むように変更
	 * *********************************** */
	public function send_alert_developer($text, $data) {

		$this->send(
			array(
				CONF::read('MAIL_ELEMENT.FROM') => CONF::read("MAIL_ADDRESS.FROM"),
				CONF::read('MAIL_ELEMENT.TO') => CONF::read("MAIL_ADDRESS.DEVELOPER"),
				CONF::read('MAIL_ELEMENT.SUBJECT') => CONF::read('LANG_TEXT.MAIL.SYSTEM_ALERT.TITLE'),
				CONF::read('MAIL_ELEMENT.MESSAGE') =>
				CONF::read('LANG_TEXT.MAIL.SYSTEM_ALERT.MESSAGE') .
				PHP_EOL .
				$text .
				PHP_EOL .
				'-------------------------------' . PHP_EOL .
				$data . PHP_EOL .
				'-------------------------------' . PHP_EOL .
				PHP_EOL
			)
		);

		LOGS_MAIL('[ALERT DEVELOPER] THIS IS EMERGENCY ALERT!!!');
	}

	/*	 * **********************************
	 * NAME  : send_unique_mail
	 * INPUT : mail_address / string / メールアドレス
	 *         from / array / 送信元(表示名付き)
	 *         subject / string / 件名
	 *         message / string / 送信内容
	 * OUTPUT: true / 送信成功の場合
	 *         false / 送信失敗の場合
	 * DESC  : 引数に応じて自由にメールを送信する。
	 * NOTICE:
	 * CREATE: 2015.12.04 sonoda
	 * UPDATE: 2016.09.05 hesaka OFFにしていたBCCを別アドレスに変更して復活させた
	 * *********************************** */
	public function send_unique_mail($mail_address = '', $from = '', $subject = '', $message = '') {

		//パラメータチェック
		if (empty($mail_address) || empty($from) || empty($subject) || empty($message)) {
			LOGS_MAIL('[ERROR] *** invalid parameter ***');
			return false;
		}

		$ret = $this->send(
			array(
				CONF::read('MAIL_ELEMENT.FROM') => $from,
				CONF::read('MAIL_ELEMENT.TO') => $mail_address,
				CONF::read('MAIL_ELEMENT.BCC') => CONF::read("MAIL_ADDRESS.BCC"),
				CONF::read('MAIL_ELEMENT.SUBJECT') => $subject,
				CONF::read('MAIL_ELEMENT.MESSAGE') => $message . $this->get_autograph()
			)
		);

		//失敗した場合その旨ログを出力してfalseを返す
		if (!$ret) {
			LOGS_MAIL('[ERROR] *** send mail failed *** address=' . $mail_address);
			return false;
		}

		LOGS_MAIL('[SUCCESS] send mail success. address=' . $mail_address);
		return true;
	}

	/*	 * **********************************
	 * NAME  : send_webcounseling
	 * INPUT : セッションから取得
	 * OUTPUT: true / 送信成功の場合
	 *         false / 送信失敗の場合
	 * DESC  :
	 * 		基幹システムへウェブカウンセリング完了のメールを送る
	 * NOTICE:
	 * CREATE: 2020.12.15 ooi
	 * *********************************** */
	public function send_webcounseling($sGroup) {

		//パラメータチェック
		if (StaticFunction::is_empty(SESSION::read($sGroup))) {
			LOGS_MAIL('[ERROR] *** invalid parameter ***');
			return false;
		}

		// DBからケアメンテ登録用メッセージの取得
		$mail = new MailMasterModel();

		//受付日時を作成
		$date = DbDateTime::get_datetime_type_slash(DbDateTime::get_cur_datetime());

		/* お客様控え */
/*
		$message_user = "" .
			"------------------------------------------------------------------" . PHP_EOL .
			"登録住所等の変更を受付けました。" . PHP_EOL .
			"------------------------------------------------------------------" . PHP_EOL .
			"【変更前】" . PHP_EOL .
			"■お名前" . PHP_EOL .
			$old_array['name'] . PHP_EOL .
			"■住所" . PHP_EOL .
			"〒" . $old_array['zip'] . PHP_EOL .
			$old_array['state'] . $old_array['addr1'] . PHP_EOL .
			$old_array['addr2'] . PHP_EOL .
			$old_array['addr3'] . PHP_EOL .
			"■電話番号" . PHP_EOL .
			$old_array['tel'] . PHP_EOL .
			"■FAX番号" . PHP_EOL .
			PHP_EOL .
			"■メールアドレス" . PHP_EOL .
			$old_array['email'] . PHP_EOL .
			PHP_EOL .
			"【変更内容】" . PHP_EOL .
			"■お名前" . PHP_EOL .
			$user_array['name'] . PHP_EOL .
			"■住所" . PHP_EOL .
			"〒" . $user_array['zip'] . PHP_EOL .
			$user_array['state'] . $user_array['addr1'] . PHP_EOL .
			$user_array['addr2'] . PHP_EOL .
			$user_array['addr3'] . PHP_EOL .
			"■電話番号" . PHP_EOL .
			$user_array['tel'] . PHP_EOL .
			"■FAX番号" . PHP_EOL .
			PHP_EOL .
			"■メールアドレス" . PHP_EOL .
			$user_array['email'] . PHP_EOL .
			"■備考" . PHP_EOL .
			PHP_EOL .
			"■受付日時" . PHP_EOL .
			"受付日時： " . $date . PHP_EOL .
			'' . PHP_EOL .
			'============================================================' . PHP_EOL .
			'●申込した覚えがない方へ' . PHP_EOL .
			'上記日時に申し込みをされた覚えがない場合は、似たアドレスをお持ちの方が' . PHP_EOL .
			'誤って申し込みをされた可能性があります。' . PHP_EOL .
			'お心あたりのない場合は、たいへんお手数ですが、' . PHP_EOL .
			'送信者 happy@kyoto-happy.co.jp までお知らせいただくとともに、' . PHP_EOL .
			'本メールを削除くださいますようお願い申し上げます' . PHP_EOL .
			'' . PHP_EOL .
			'ご不明な点がございましたら、下記までお気軽にご連絡くださいませ。';

		$ret = $this->send(
			array(
				CONF::read('MAIL_ELEMENT.FROM') => CONF::read("MAIL_REGIST.FROM"),
				CONF::read('MAIL_ELEMENT.TO') => $user_array['email'],
				//CONF::read('MAIL_ELEMENT.BCC') => CONF::read("MAIL_ADDRESS.ADMIN"),
				CONF::read('MAIL_ELEMENT.SUBJECT') => "登録住所等の変更を受付けました。 ",
				CONF::read('MAIL_ELEMENT.MESSAGE') => StaticFunction::convert_zen_kana($message_user) .
				PHP_EOL .
				$mail->get_mail_text('autograph') // 署名
			)
		);
		//失敗した場合その旨ログを出力してfalseを返す
		if (!$ret) {
			LOGS_ERR('[ERROR] *** send mail failed *** address=' . $message_user);
		}
*/
		//対象物件文字列を生成
		$item_list = "";
		foreach (SESSION::read($sGroup . '.item_array') AS $item) {
			$item_list .= "　" . StaticFunction::format_item_id($item['item_id']) . "　" . $item['classificationname'] . "／" . $item['color'] . PHP_EOL;
		}

		/* 　管理者宛メール　 */
		$message = "" .
			"-----------------------------------------------------------------" . PHP_EOL .
			"ウェブカウンセリングを受付けました。" . PHP_EOL .
			"------------------------------------------------------------------" . PHP_EOL .
			"【内容】" . PHP_EOL .
			"お名前： " . StaticFunction::marge_name(SESSION::read($sGroup . '.name1'), SESSION::read($sGroup . '.name2')) . "(" . SESSION::read($sGroup . '.user_id') . ")" . PHP_EOL .
			// "電話番号： " . StaticFunction::marge_phone(SESSION::read($sGroup . '.telephone'), SESSION::read($sGroup . '.telephone2'), SESSION::read($sGroup . '.telephone3')) . PHP_EOL .
			"電話番号： " . SESSION::read($sGroup . '.telephone') . PHP_EOL .
			"メールアドレス： " . SESSION::read($sGroup . '.email') . PHP_EOL .
			"カルテNo： " . SESSION::read($sGroup . '.chart_id') . PHP_EOL .
			"対象物件番号： " . PHP_EOL .
			$item_list . PHP_EOL .
			"希望仕上りお届日時： " . SESSION::read($sGroup . '.schedulerequestname') . "　" . SESSION::read($sGroup . '.scheduletimezonename') . PHP_EOL .
			"希望お支払い方法： " . SESSION::read($sGroup . '.paymentmethodname') . PHP_EOL .
			"コメント： " . SESSION::read($sGroup . '.comment') . PHP_EOL .
			"受付日時： " . $date . PHP_EOL .
			"------------------------------------------------------------------";

		$ret = $this->send(
			array(
				CONF::read('MAIL_ELEMENT.FROM') => CONF::read("MAIL_WEBCOUNSELING.FROM"),
				CONF::read('MAIL_ELEMENT.TO') => CONF::read("MAIL_WEBCOUNSELING.TO"),
				//CONF::read('MAIL_ELEMENT.BCC') => CONF::read("MAIL_WEBCOUNSELING.ADMIN"),
				CONF::read('MAIL_ELEMENT.SUBJECT') => "申込 ウェブカウンセリング受付",
				CONF::read('MAIL_ELEMENT.MESSAGE') => StaticFunction::convert_zen_kana($message)
			)
		);

		//失敗した場合その旨ログを出力してfalseを返す
		if (!$ret) {
			LOGS_ERR('[ERROR] *** send mail failed *** address=' . $message);
			return false;
		}

		return true;
	}

}

?>
