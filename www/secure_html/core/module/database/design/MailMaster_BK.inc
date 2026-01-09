<?php

/* * **********************************
 * NAME:MailMaster
 * DESC:
 *  メール系マスタテーブル
 * NOTICE:
 * CREATE: 2016.10.17 aoyama
 * *********************************** */
class MailMaster implements DatabaseDesign {

	private $table_name = 'mail_master';

	/*	 * **********************************
	 * NAME  : get_table_name
	 * INPUT : NONE
	 * OUTPUT: string / テーブル名
	 * DESC  :
	 *  テーブル名を返す
	 * NOTICE:
	 * CREATE: 2015.08.27 hesaka
	 * *********************************** */
	public function get_table_name() {
		return $this->table_name;
	}

	/*	 * **********************************
	 * NAME  : get_table_comment
	 * INPUT : NONE
	 * OUTPUT: string / TABLE用のコメント
	 *         NULL / オプション不要の場合
	 * DESC  :
	 *  テーブルの説明を設定する
	 * NOTICE:
	 *  ※ない場合はNULLを返すこと
	 * CREATE: 2016.10.17 aoyama
	 * *********************************** */
	public function get_table_comment() {
		return "メールマスタ";
	}

	/*	 * **********************************
	 * NAME  : get_design
	 * INPUT : NONE
	 * OUTPUT: string / CREATE TABLE に用いる構造テキスト
	 * DESC  :
	 *  テーブルの構造を返す
	 * NOTICE:
	 * CREATE: 2016.10.17 aoyama
	 * *********************************** */
	public function get_design() {

		return "
			message_type VARCHAR(255) NOT NULL PRIMARY KEY COMMENT 'メール用メッセージ種別(必須)',
			create_time BIGINT NOT NULL COMMENT '登録日時(必須)',
			update_time BIGINT NOT NULL COMMENT 'イベント表示件数PC',
			message_text LONGTEXT COMMENT 'メール用テキスト'
		";
	}

	/*	 * **********************************
	 * NAME  : get_pre_set_records
	 * INPUT : NONE
	 * OUTPUT: string / INSERT に用いるレコードテキスト
	 *         NULL / 初期INSERT不要の場合
	 * DESC  :
	 *  プリセットレコードがあれば指定する
	 * NOTICE:
	 *  ※ない場合はNULLを返すこと
	 * CREATE: 2015.08.27 hesaka
	 * *********************************** */
	public function get_pre_set_records() {

		$datetime = DbDateTime::get_cur_datetime();
		return "
			(
				message_type,
				create_time,
				update_time,
				message_text
			)
			VALUES 
			(
				'autograph',
				" . $datetime . ",
				" . $datetime . ",
				'" . $this->mail_autograph() . "'
			),
			(
				'user_add_title',
				" . $datetime . ",
				" . $datetime . ",
				'" . $this->user_add_title() . "'
			),
			(
				'user_add',
				" . $datetime . ",
				" . $datetime . ",
				'" . $this->user_add() . "'
			),
			(
				'catalog_add_title',
				" . $datetime . ",
				" . $datetime . ",
				'" . $this->catalog_add_title() . "'
			),
			(
				'catalog_add',
				" . $datetime . ",
				" . $datetime . ",
				'" . $this->catalog_add() . "'
			),
			(
				'friend_send_title',
				" . $datetime . ",
				" . $datetime . ",
				'" . $this->friend_send_title() . "'
			),
			(
				'friend_send',
				" . $datetime . ",
				" . $datetime . ",
				'" . $this->friend_send() . "'
			),
			(
				'friend_send_target_title',
				" . $datetime . ",
				" . $datetime . ",
				'" . $this->friend_send_target_title() . "'
			),
			(
				'friend_send_target',
				" . $datetime . ",
				" . $datetime . ",
				'" . $this->friend_send_target() . "'
			),
			(
				'order_care_title',
				" . $datetime . ",
				" . $datetime . ",
				'" . $this->order_care_title() . "'
			),
			(
				'order_care',
				" . $datetime . ",
				" . $datetime . ",
				'" . $this->order_care() . "'
			),
			(
				'maimag_add_title',
				" . $datetime . ",
				" . $datetime . ",
				'" . $this->maimag_add_title() . "'
			),
			(
				'mailmag_add',
				" . $datetime . ",
				" . $datetime . ",
				'" . $this->mailmag_add() . "'
			);";
	}

	/*	 * **********************************
	 * NAME  : pre_import
	 * INPUT : NONE
	 * OUTPUT: NONE
	 * DESC  :
	 *  最初にCSVからインポートする必要があれば
	 *  それを行う
	 * NOTICE:
	 *  ※ない場合はNULLを返すこと
	 * CREATE: 2015.12.10 hesaka
	 * *********************************** */
	public function pre_import() {
		return NULL;
	}

	/*	 * **********************************
	 * NAME  : get_option
	 * INPUT : NONE
	 * OUTPUT: string / CREATE TABLE のオプション
	 *         NULL / オプション不要の場合
	 * DESC  :
	 *  オプションがあれば指定する
	 * NOTICE:
	 *  ※ない場合はNULLを返すこと
	 * CREATE: 2016.10.17 aoyama
	 * *********************************** */
	public function get_option() {
		return NULL;
	}

	/*	 * **********************************
	 * NAME  : get_strage_engine
	 * DESC  :
	 *  CREATE TABLEする際にストレージエンジンを指定する
	 * NOTICE:
	 * CREATE: 2015.11.17 hesaka
	 * *********************************** */
	public function get_strage_engine() {
		return "INNODB";
	}

	
	/*	 * **********************************
	 * NAME  : order_care_title
	 * DESC  :
	 *  メールタイトル（友達申請登録完了時：送信者宛）
	 * NOTICE:
	 * CREATE: 2016.10.18 aoyama
	 * *********************************** */
	private function order_care_title() {
		return 'ケアメンテのご依頼を承りました。';
	}
	/*	 * **********************************
	 * NAME  : order_care_send
	 * DESC  :
	 *  メール本文（友達申請登録完了時：送信者宛）
	 * NOTICE:
	 * CREATE: 2016.10.18 aoyama
	 * *********************************** */
	private function order_care() {
		return '{{{name1}}}様<{{{email}}}>' . PHP_EOL .
			PHP_EOL .
			'この度はケアメンテをご依頼いただきまして、誠にありがとうございました。' . PHP_EOL .
			'以下の内容でケアメンテを承りましたのでお知らせ致します。' . PHP_EOL .
			PHP_EOL .
			'============================================================' . PHP_EOL .
			'お名前：{{{name1}}}' . PHP_EOL .
			'ふりがな：{{{kana1}}}' . PHP_EOL .
			'お引取先住所：{{{addr}}}' . PHP_EOL .
			'電話番号：{{{tel}}}' . PHP_EOL .
			'FAX番号：{{{fax}}}' . PHP_EOL .
			'メールアドレス ：{{{email}}}' . PHP_EOL .
			'------------------------------------------------------------' . PHP_EOL .
			'お届け先' . PHP_EOL .
			'お名前：{{{s_name1}}}' . PHP_EOL .
			'ふりがな：{{{s_kana1}}}' . PHP_EOL .
			'お引取先住所：{{{s_addr}}}' . PHP_EOL .
			'電話番号：{{{s_tel}}}' . PHP_EOL .
			'------------------------------------------------------------' . PHP_EOL .
			'引取日：{{{taking}}}' . PHP_EOL .
			'取引時間：' . PHP_EOL .
			'{{{time}}}' . PHP_EOL .
			'荷物個口数：{{{kutisu}}}個口' . PHP_EOL .
			'カタログ送付：{{{catalog}}}' . PHP_EOL .
			'メールマガジン：{{{mailmag}}}' . PHP_EOL .
			'保管お預かり：{{{wardrobe}}}' . PHP_EOL .
			'============================================================';
	}
	
	
	/*	 * **********************************
	 * NAME  : mail_autograph
	 * DESC  :
	 *  メール署名
	 * NOTICE:
	 * CREATE: 2016.10.17 aoyama
	 * *********************************** */
	private function mail_autograph() {
		return '━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━' . PHP_EOL .
			'株式会社　ハッピー' . PHP_EOL .
			'〒611-0041 京都府宇治市槙島町目川７０番地の１' . PHP_EOL .
			'ＴＥＬ ： 0120-88-6868 ＦＡＸ ： 0120-88-3937' . PHP_EOL .
			'ＵＲＬ ： http://www.kyoto-happy.co.jp/' . PHP_EOL .
			'Ｅ－ＭＡＩＬ　：　infores@kyoto-happy.co.jp' . PHP_EOL .
			'記事の無断転載を禁じます。' . PHP_EOL .
			'━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━' . PHP_EOL .
			'※このメールには、本来の宛先の方のみに限定された情報が含まれている場合がございます。' . PHP_EOL .
			'　お心あたりのない場合は、たいへんお手数ですが、送信者までお知らせいただくとともに、' . PHP_EOL .
			'　本メールを削除くださいますようお願いいたします。' . PHP_EOL .
			'';
	}

	/*	 * **********************************
	 * NAME  : user_add_title
	 * DESC  :
	 *  メールタイトル（会員登録完了時）
	 * NOTICE:
	 * CREATE: 2016.10.17 aoyama
	 * *********************************** */
	private function user_add_title() {
		return '会員登録が完了しました。';
	}
	/*	 * **********************************
	 * NAME  : mail_message_user_add
	 * DESC  :
	 *  メール本文（会員登録完了時）
	 * NOTICE:
	 * CREATE: 2016.10.17 aoyama
	 * *********************************** */
	private function user_add() {
		return '{{{name1}}} 様' . PHP_EOL .
			PHP_EOL .
			'このたびはＩＤとパスワードをお申し込みいただきまして、' . PHP_EOL .
			'ありがとうございます。' . PHP_EOL .
			PHP_EOL .
			'ＩＤとパスワードを下記の通り登録しましたのでお知らせします。' . PHP_EOL .
			PHP_EOL .
			'ID：{{{syste_user_id}}}' . PHP_EOL .
			'PASSWORD：{{{password}}}' . PHP_EOL .
			PHP_EOL .
			'「MYページ」（スマホ版・PC版）及び「ケアメンテアプリ」より' . PHP_EOL .
			'ログインしていただきますと、下記サービスをご利用いただけます。' . PHP_EOL .
			PHP_EOL .
			'①マイe電子カルテ' . PHP_EOL .
			'→ケアメンテをご利用いただいたすべての履歴がご覧いただけます。' . PHP_EOL .
			'※翌日から閲覧可能となります。' . PHP_EOL .
			PHP_EOL .
			'②保管お預かりサービス「ハッピーワードローブ」' . PHP_EOL .
			'→保管・お預かりサービスをご利用いただいているアイテムがご覧いただけます。' . PHP_EOL .
			'※翌日から閲覧可能となります。' . PHP_EOL .
			PHP_EOL .
			'③ご注文「集荷・申込み」機能' . PHP_EOL .
			'→ご依頼品の引取日時を入力するだけで手続き完了！' . PHP_EOL .
			'→ワンクリックでお客様専用フリーダイヤルに繋がります。' . PHP_EOL .
			'※今すぐご利用いただけます。';
	}

	/*	 * **********************************
	 * NAME  : catalog_add_title
	 * DESC  :
	 *  メールタイトル（カタログ請求登録完了時）
	 * NOTICE:
	 * CREATE: 2016.10.17 aoyama
	 * *********************************** */
	private function catalog_add_title() {
		return 'カタログ請求が完了しました。';
	}
	/*	 * **********************************
	 * NAME  : catalog_add
	 * DESC  :
	 *  メール本文（カタログ請求登録完了時）
	 * NOTICE:
	 * CREATE: 2016.10.17 aoyama
	 * *********************************** */
	private function catalog_add() {
		return '-----------------------------------------------------------------' . PHP_EOL .
			'カタログ請求登録を受付けました' . PHP_EOL .
			'------------------------------------------------------------------' . PHP_EOL .
			PHP_EOL .
			'■お名前' . PHP_EOL .
			'{{{name1}}}' . PHP_EOL .
			'■ふりがな' . PHP_EOL .
			'{{{kana1}}}' . PHP_EOL .
			'■生年月日' . PHP_EOL .
			'{{{birth}}}' . PHP_EOL .
			'■住所' . PHP_EOL .
			'〒{{{zip}}}' . PHP_EOL .
			'{{{addr}}}' . PHP_EOL .
			PHP_EOL .
			'■電話番号' . PHP_EOL .
			'{{{tel}}}' . PHP_EOL .
			'■FAX番号' . PHP_EOL .
			'{{{fax}}}' . PHP_EOL .
			'■メールアドレス' . PHP_EOL .
			'{{{email}}}' . PHP_EOL .
			'■メルマガ購読' . PHP_EOL .
			'{{{mag}}}' . PHP_EOL .
			PHP_EOL .
			'■受付日時' . PHP_EOL .
			'{{{entry_time}}}' . PHP_EOL .
			PHP_EOL .
			'●申込した覚えがない方へ' . PHP_EOL .
			'上記日時に申込を行った記憶がない場合は、似たアドレスをお持ちの方が' . PHP_EOL .
			'間違って申込をされた可能性があります。その際にはご面倒をおかけ致し' . PHP_EOL .
			'ますが、happy@kyoto-happy.co.jp まで、このメールをそのまま転送して' . PHP_EOL .
			'ください。よろしくお願い致します。' . PHP_EOL .
			PHP_EOL .
			'その他、ご不明な点がございましたら、お気軽にご連絡ください。' . PHP_EOL .
			'今後ともHappy ケアメンテをよろしくお願い致します。';
	}	
	
	/*	 * **********************************
	 * NAME  : maimag_add_title
	 * DESC  :
	 *  メールタイトル（会員登録完了時）
	 * NOTICE:
	 * CREATE: 2016.10.17 aoyama
	 * *********************************** */
	private function maimag_add_title() {
		return 'メールマガジン登録が完了しました。';
	}
	/*	 * **********************************
	 * NAME  : mailmag_add
	 * DESC  :
	 *  メール本文（メルマガ登録完了時）
	 * NOTICE:
	 * CREATE: 2016.10.17 aoyama
	 * *********************************** */
	private function mailmag_add() {
		return '-----------------------------------------------------------------' . PHP_EOL .
			'ケアメンテ メルマガの登録を受付けました' . PHP_EOL .
			'------------------------------------------------------------------' . PHP_EOL .
			PHP_EOL .
			'■お名前' . PHP_EOL .
			'{{{name1}}}' . PHP_EOL .
			'■メールアドレス' . PHP_EOL .
			'{{{email}}}' . PHP_EOL .
			'■住所' . PHP_EOL .
			'〒{{{zip}}}' . PHP_EOL .
			'{{{addr1}}}' . PHP_EOL .
			'{{{addr2}}}' . PHP_EOL .
			'{{{addr3}}}' . PHP_EOL .
			PHP_EOL .
			'■電話番号' . PHP_EOL .
			'{{{tel}}}' . PHP_EOL .
			'■FAX番号' . PHP_EOL .
			'{{{fax}}}' . PHP_EOL .
			PHP_EOL .
			'■受付日時' . PHP_EOL .
			'{{{entry_time}}}' . PHP_EOL .
			PHP_EOL .
			'●申込した覚えがない方へ' . PHP_EOL .
			'上記日時に申込を行った記憶がない場合は、似たアドレスをお持ちの方が' . PHP_EOL .
			'間違って申込をされた可能性があります。その際にはご面倒をおかけ致し' . PHP_EOL .
			'ますが、happy@kyoto-happy.co.jp まで、このメールをそのまま転送して' . PHP_EOL .
			'ください。よろしくお願い致します。' . PHP_EOL .
			PHP_EOL .
			'その他、ご不明な点がございましたら、お気軽にご連絡ください。' . PHP_EOL .
			'今後ともHappy ケアメンテをよろしくお願い致します。';
	}
	/*	 * **********************************
	 * NAME  : catalog_add_title
	 * DESC  :
	 *  メールタイトル（友達申請登録完了時：送信者宛）
	 * NOTICE:
	 * CREATE: 2016.10.18 aoyama
	 * *********************************** */
	private function friend_send_title() {
		return '{{{friend_name}}}様へお送りしたメールです。';
	}
	/*	 * **********************************
	 * NAME  : catalog_add
	 * DESC  :
	 *  メール本文（友達申請登録完了時：送信者宛）
	 * NOTICE:
	 * CREATE: 2016.10.18 aoyama
	 * *********************************** */
	private function friend_send() {
		return '{{{name1}}}様<{{{email}}}>' . PHP_EOL .
			PHP_EOL .
			'この度はお友達をご紹介いただきまして、誠にありがとうございました。' . PHP_EOL .
			'{{{friend_name}}}様<{{{friend_email}}}>に、以下の内容でメールを送信しましたので' . PHP_EOL .
			'お知らせ致します。' . PHP_EOL .
			PHP_EOL .
			'============================================================' . PHP_EOL .
			'お送りしたメール' . PHP_EOL .
			'============================================================' . PHP_EOL .
			PHP_EOL
			;
	}
	/*	 * **********************************
	 * NAME  : catalog_add_title
	 * DESC  :
	 *  メールタイトル（友達申請登録完了時：受信者宛）
	 * NOTICE:
	 * CREATE: 2016.10.18 aoyama
	 * *********************************** */
	private function friend_send_target_title() {
		return '{{{name1}}}様からのご紹介メールです。';
	}
	/*	 * **********************************
	 * NAME  : catalog_add
	 * DESC  :
	 *  メール本文（友達申請登録完了時：受信者宛）
	 * NOTICE:
	 * CREATE: 2016.10.18 aoyama
	 * *********************************** */
	private function friend_send_target() {
		return '{{{friend_name}}}様<{{{friend_email}}}>' . PHP_EOL .
			PHP_EOL .
			'ハッピーケアメンテでございます。' . PHP_EOL .
			'このたび、ハッピーの「お友達紹介キャンペーン」にて、' . PHP_EOL .
			'{{{name1}}}様<{{{email}}}>よりご紹介がございました。' . PHP_EOL .
			'下記の専用URLからご注文いただきますと、' . PHP_EOL .
			'リプロン50％OFF（シミ汚れ落としや黄ばみ取りなど）' . PHP_EOL .
			'さらに３点以上ご利用いただくと、' . PHP_EOL .
			'次回のご利用からお使いいただけるハッピーギフトチケット' . PHP_EOL .
			'￥５００をプレゼントいたします。' . PHP_EOL .
			PHP_EOL .
			'{{{name1}}}様からのメッセージ' . PHP_EOL .
			'------------------------------------------------------------' . PHP_EOL .
			'{{{comment}}}' . PHP_EOL .
			'------------------------------------------------------------' . PHP_EOL .
			PHP_EOL .
			'ご注文はコチラ！' . PHP_EOL .
			'{{{friend_url}}}' . PHP_EOL .
			PHP_EOL .
			'※このURLはお友達紹介キャンペーン専用です。' . PHP_EOL .
			PHP_EOL .
			'【お友達紹介キャンペーン】プレゼント内容' . PHP_EOL .
			'============================================================' . PHP_EOL .
			'【プレゼント その1】' . PHP_EOL .
			'　リプロン５０％ＯＦＦ' . PHP_EOL .
			'　※除外品' . PHP_EOL .
			'　　皮革毛皮製品（部分皮革毛皮製品含む）・和服類・寝具類・インテリア類・鞄類' . PHP_EOL .
			'　　リプロン染め替え リプロン植毛・リプロン編み目ひろい・リプロン糸引き直し' . PHP_EOL .

			'　リプロンの詳細はコチラ' . PHP_EOL .
			'　　http://www.kyoto-happy.co.jp/happy/29ripron.html' . PHP_EOL .
			'【プレゼント その2】' . PHP_EOL .
			'　　３点以上ご利用いただくと、次回のご利用からお使いいただける' . PHP_EOL .
			'　　ハッピーギフトチケット￥５００をプレゼントいたします。' . PHP_EOL .
			'　※既にハッピーケアメンテをご利用されたことのあるお客様は、' . PHP_EOL .
			'　　お友達紹介キャンペーンの対象外となりますので、ご了承ください。' . PHP_EOL .
			'============================================================';
	}		
}

?>
