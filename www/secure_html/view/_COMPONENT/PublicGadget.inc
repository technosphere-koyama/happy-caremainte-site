<?php
/* * **********************************
 * NAME:UserGadget
 * DESC:
 *  ガジェットパーツ
 * NOTICE:
 * CREATE: 2016.10.24 aoyama
 * *********************************** */
class PublicGadget {

	private $link_contact;
	private $link_recruit;
	private $link_privacypolicy;
	private $link_about;
	private $link_sitemap;
	private $link_order;

	/* Constructor */
	public function __construct() {

		$this->link_contact = "/contact/";
		$this->link_recruit = "/recruit/";
		$this->link_privacypolicy = "/privacypolicy/";
		$this->link_about = "/about/";
		$this->link_sitemap = "/sitemap/";

		$this->link_order = "/order/";
	}

	/*
	 * .html_error_array
	 * エラー配列を受け取った時に表示
	 */
	public function html_error_array($array) {
		if (!StaticFunction::is_empty($array)) {
			?>
			<ul class="error_box">
				<?php
				foreach ($array as $value) {
					echo '<li>・ ' . $value['message'] . '</li>';
				}
				?>
			</ul>
			<?php
		}
	}

	/*	 * **********************************
	 * NAME  : get_sns_code
	 * INPUT : message / str / 表示内容
	 * OUTPUT: html標準出力
	 * DESC  :
	 * NOTICE:
	 * CREATE: 2016.11.2 aoyama
	 * *********************************** */
	public function get_sns_code() {
		?>
		<!-- FB script ▼ -->
		<div id="fb-root"></div>
		<script>(function (d, s, id) {
				var js, fjs = d.getElementsByTagName(s)[0];
				if (d.getElementById(id))
					return;
				js = d.createElement(s);
				js.id = id;
				js.src = "//connect.facebook.net/ja_JP/sdk.js#xfbml=1&version=v2.3&appId=755562857883941";
				fjs.parentNode.insertBefore(js, fjs);
			}(document, 'script', 'facebook-jssdk'));</script>
		<!-- FB script ▲ -->
		<!-- Twitter script ▼ -->
		<script>!function (d, s, id) {
				var js, fjs = d.getElementsByTagName(s)[0];
				if (!d.getElementById(id)) {
					js = d.createElement(s);
					js.id = id;
					js.src = "//platform.twitter.com/widgets.js";
					fjs.parentNode.insertBefore(js, fjs);
				}
			}(document, "script", "twitter-wjs");</script>
		<!-- Twitter script ▲ -->
		<?php
	}

	/*	 * **********************************
	 * NAME  : get_news
	 * INPUT : message / str / 表示内容
	 * OUTPUT: html標準出力
	 * DESC  :
	 * NOTICE:
	 * CREATE: 2016.10.24 aoyama
	 * *********************************** */
	public function get_news() {

		$title = "Happy 掲示板";
		$message = "毎年悩む、衣替えのタイミング。" . PHP_EOL;
		$message .= "まだ暑い？もぅ寒い！時期を見極めるポイントは気温です。秋の衣替えは20℃前後の気温が安定的に続いてきたらはじめましょう。" . PHP_EOL;
		$message .= PHP_EOL;
		$message .= "日々の気温を参考に衣替えのタイミングを逃さないようにしましょう。";

		/* WPの情報取得テスト */
		if (file_exists('../../public/wp/wp-load.php')) {

			require_once('../../public/wp/wp-load.php');
			$args = array(
				'post_type'=> 'sns_message',
				'posts_per_page' => 1
			);
			query_posts($args);
			if(have_posts()):
				while(have_posts()): the_post();
			$message = get_the_content();
				endwhile;
			endif;
			wp_reset_query();
		} else if (file_exists('../../../public/wp/wp-load.php')) {

			require_once('../../../public/wp/wp-load.php');
			$args = array(
				'post_type'=> 'sns_message',
				'posts_per_page' => 1
			);
			query_posts($args);
			if(have_posts()):
				while(have_posts()): the_post();
			$message = get_the_content();
				endwhile;
			endif;
			wp_reset_query();
		}
		?>
		<div class="happyInfo">
			<h5><?php echo $title; ?></h5>
			<p><?php echo nl2br($message); ?></p>
		</div>
		<div class="happyOrder"><a href="/carementeh_search/"><img src="/_assets/img/mypage/ico_search.png" alt="つなぐ">さがす</a></div>
		<div class="happyOrder"><a href="/review/"><img src="/_assets/img/mypage/ico_review.png" alt="きづく">きづく</a></div>
        <div class="happyOrder"><a href="/mypage/"><img src="/_assets/img/mypage/ico_mypage.png" alt="マイページ">マイページ</a></div>
        <div class="happyOrder"><a href="/order/"><img src="/_assets/img/mypage/ico_order.png" alt="ご注文">ご注文</a></div>
		<?php
	}

	/*
	 */


	public function html_mypage_navi_sp() {

		if (!session_id()) {
			session_name("kh");
			session_save_path($_SERVER['DOCUMENT_ROOT']."/../core/tmp/session");
			session_start();
		}
		$count = (isset($_SESSION['PUBLIC_USER']['message_count']) && $_SESSION['PUBLIC_USER']['message_count'] > 0) ? '<div class="unreadMsgNumber"><span>'. $_SESSION['PUBLIC_USER']['message_count'] . '</span></div>' : '';

		?>
		<li class="navi1"><a href="/mypage/sns.html" <?php echo_current("sns.html"); ?>><dl><dt></dt><dd>トップ</dd></dl></a></li>
        <li class="navi2"><a href="/mypage/friend/" <?php echo_current("friend"); ?>><dl><dt></dt><dd>フレンド</dd></dl></a></li>
        <li class="navi3"><a href="/community/" <?php echo_current("community"); ?>><dl><dt></dt><dd>コミュニティ</dd></dl></a></li>
        <li class="navi4"><a href="/mypage/message/" <?php echo_current("message"); ?>><dl><dt></dt><dd>メッセージ</dd></dl></a><?php echo $count ?></li>
        <li class="navi5"><a href="/profile/" <?php echo_current("profile"); ?>><dl><dt></dt><dd>プロフィール</dd></dl></a></li>
        <script type="text/javascript">
			if ((navigator.userAgent.indexOf('iPhone') > 0) || navigator.userAgent.indexOf('iPod') > 0 || navigator.userAgent.indexOf('Android') > 0 || navigator.userAgent.indexOf('CareMenteh App User') != -1){
				document.write('<link rel="stylesheet" type="text/css" href="/_assets/css/app_mypage.css?190517">');
			}else {
			}
		</script>

		<?php
	}

	/*
	 */
	public function html_chart_button() {
		?>
		<div><a href="/mypage/history/">過去のケアメンテご利用履歴</a></div>
		<div><a href="/mypage/ordered/">ただいまのお預かり品</a></div>
		<div><a href="/mypage/wardrobe/">ワードローブお預かり品</a></div>
		<?php
	}

	/*
	 * SSLバッジ
	 */
	public function html_verisign_mark() {
		?>
		<div class="contactSSL PCpart"><span id="ss_img_wrapper_gmogs_image_125-50_en_dblue"><a href="https://jp.globalsign.com/" target="_blank" rel="nofollow"><img alt="SSL GlobalSign Site Seal" border=0 id="ss_img" src="//seal.globalsign.com/SiteSeal/images/gs_noscript_125-50_en.gif"></a></span><script type="text/javascript" src="//seal.globalsign.com/SiteSeal/gmogs_image_125-50_en_dblue.js" defer="defer"></script><br><span class="style3">このサイトはプライバシー保護のためSSL暗号通信を採用しています。</span></div>
		<?php
	}

	/*
	 * ワードローブ検索のアイテムセレクト
	 */
	public function html_wardrobe_select_item($val = null) {
		$array[] = array("number" => "01", "text" => "上着類");
		$array[] = array("number" => "02", "text" => "パンツ・ズボン類");
		$array[] = array("number" => "03", "text" => "スカート類");
		$array[] = array("number" => "04", "text" => "シャツ類");
		$array[] = array("number" => "05", "text" => "ベスト類");
		$array[] = array("number" => "06", "text" => "ワンピース類");
		$array[] = array("number" => "07", "text" => "ニット製品類");
		$array[] = array("number" => "08", "text" => "コート類");
		$array[] = array("number" => "09", "text" => "ダウン製品類");
		$array[] = array("number" => "15", "text" => "小物類");
		$array[] = array("number" => "16", "text" => "寝具類");
		$array[] = array("number" => "18", "text" => "和服類");
		$array[] = array("number" => "19", "text" => "皮革・毛皮製品類");
		$array[] = array("number" => "20", "text" => "インテリア類");
		$array[] = array("number" => "21", "text" => "その他");
		$array[] = array("number" => "22", "text" => "ベビー用品類");
		$array[] = array("number" => "23", "text" => "ドレス類");
		?>
		<select name="item" id="item" value="" class="selectable3">
			<option value="">選択してください</option>
		<?php foreach ($array AS $value) { ?>
			<?php $selected = ($val == $value['number']) ? ' selected="selected"' : ''; ?>
				<option value="<?php echo $value['number'] ?>" title="<?php echo $value['text'] ?>"<?php echo $selected ?>><?php echo $value['text'] ?></option>
		<?php } ?>
		</select>
		<?php
	}

	/*
	 * ワードローブ検索のアイテムサブセレクト
	 */
	public function html_wardrobe_subselect_item($val = null) {
		$array[] = array("number" => "02", "class" => "上着類", "text" => "婦人上着");
		$array[] = array("number" => "03", "class" => "上着類", "text" => "ジャケット");
		$array[] = array("number" => "04", "class" => "上着類", "text" => "ブレザー");
		$array[] = array("number" => "06", "class" => "上着類", "text" => "婦人ブレザー");
		$array[] = array("number" => "10", "class" => "上着類", "text" => "紳士ジャケット");
		$array[] = array("number" => "11", "class" => "上着類", "text" => "婦人ジャケット");
		$array[] = array("number" => "12", "class" => "上着類", "text" => "紳士ブレザー");
		$array[] = array("number" => "13", "class" => "上着類", "text" => "半袖紳士上着");
		$array[] = array("number" => "14", "class" => "上着類", "text" => "半袖婦人上着");
		$array[] = array("number" => "15", "class" => "上着類", "text" => "モーニング");
		$array[] = array("number" => "16", "class" => "上着類", "text" => "紳士上着");
		$array[] = array("number" => "17", "class" => "上着類", "text" => "背広上着");
		$array[] = array("number" => "18", "class" => "上着類", "text" => "ジャンパー(ブルゾン)");
		$array[] = array("number" => "20", "class" => "上着類", "text" => "婦人上着(綿・麻・ポリ)");
		$array[] = array("number" => "21", "class" => "上着類", "text" => "ジャケット(綿・麻・ポリ)");
		$array[] = array("number" => "22", "class" => "上着類", "text" => "ブレザー(綿・麻・ポリ)");
		$array[] = array("number" => "23", "class" => "上着類", "text" => "婦人ブレザー(綿・麻・ポリ)");
		$array[] = array("number" => "24", "class" => "上着類", "text" => "紳士ジャケット(綿・麻・ポリ)");
		$array[] = array("number" => "25", "class" => "上着類", "text" => "婦人ジャケット(綿・麻・ポリ)");
		$array[] = array("number" => "26", "class" => "上着類", "text" => "紳士ブレザー(綿・麻・ポリ)");
		$array[] = array("number" => "27", "class" => "上着類", "text" => "半袖紳士上着(綿・麻・ポリ)");
		$array[] = array("number" => "28", "class" => "上着類", "text" => "半袖婦人上着(綿・麻・ポリ)");
		$array[] = array("number" => "29", "class" => "上着類", "text" => "モーニング(綿・麻・ポリ)");
		$array[] = array("number" => "30", "class" => "上着類", "text" => "紳士上着(綿・麻・ポリ)");
		$array[] = array("number" => "31", "class" => "上着類", "text" => "背広上着(綿・麻・ポリ)");
		$array[] = array("number" => "32", "class" => "上着類", "text" => "ジャンパー(ブルゾン)(綿・麻・ポリ)");
		$array[] = array("number" => "33", "class" => "上着類", "text" => "上着類(綿・麻・ポリ)");
		$array[] = array("number" => "99", "class" => "上着類", "text" => "上着類");
		$array[] = array("number" => "01", "class" => "パンツ・ズボン類", "text" => "ズボン");
		$array[] = array("number" => "02", "class" => "パンツ・ズボン類", "text" => "婦人パンツ");
		$array[] = array("number" => "03", "class" => "パンツ・ズボン類", "text" => "ジーパン");
		$array[] = array("number" => "04", "class" => "パンツ・ズボン類", "text" => "スキーパンツ");
		$array[] = array("number" => "09", "class" => "パンツ・ズボン類", "text" => "半ズボン");
		$array[] = array("number" => "12", "class" => "パンツ・ズボン類", "text" => "ズボン(獣毛)");
		$array[] = array("number" => "13", "class" => "パンツ・ズボン類", "text" => "婦人パンツ(獣毛)");
		$array[] = array("number" => "14", "class" => "パンツ・ズボン類", "text" => "カーゴパンツ");
		$array[] = array("number" => "99", "class" => "パンツ・ズボン類", "text" => "パンツ類");
		$array[] = array("number" => "01", "class" => "スカート類", "text" => "タイトスカート");
		$array[] = array("number" => "02", "class" => "スカート類", "text" => "フレアースカート");
		$array[] = array("number" => "03", "class" => "スカート類", "text" => "ギャザースカート");
		$array[] = array("number" => "04", "class" => "スカート類", "text" => "ジャンバースカート");
		$array[] = array("number" => "05", "class" => "スカート類", "text" => "プリーツスカート");
		$array[] = array("number" => "06", "class" => "スカート類", "text" => "ボックススカート");
		$array[] = array("number" => "07", "class" => "スカート類", "text" => "キュロットスカート");
		$array[] = array("number" => "09", "class" => "スカート類", "text" => "アコーディオンプリーツスカート");
		$array[] = array("number" => "10", "class" => "スカート類", "text" => "巻きスカート");
		$array[] = array("number" => "11", "class" => "スカート類", "text" => "ヒダ付きスカート");
		$array[] = array("number" => "12", "class" => "スカート類", "text" => "バルーンスカート");
		$array[] = array("number" => "13", "class" => "スカート類", "text" => "セミフレアースカート");
		$array[] = array("number" => "15", "class" => "スカート類", "text" => "タイトスカート(綿・麻・ポリ)");
		$array[] = array("number" => "16", "class" => "スカート類", "text" => "フレアースカート(綿・麻・ポリ)");
		$array[] = array("number" => "17", "class" => "スカート類", "text" => "ギャザースカート(綿・麻・ポリ)");
		$array[] = array("number" => "18", "class" => "スカート類", "text" => "ジャンバースカート(綿・麻・ポリ)");
		$array[] = array("number" => "19", "class" => "スカート類", "text" => "プリーツスカート(綿・麻・ポリ)");
		$array[] = array("number" => "20", "class" => "スカート類", "text" => "ボックススカート(綿・麻・ポリ)");
		$array[] = array("number" => "21", "class" => "スカート類", "text" => "キュロットスカート(綿・麻・ポリ)");
		$array[] = array("number" => "22", "class" => "スカート類", "text" => "アコーディオンプリーツスカート(綿・麻・ポリ)");
		$array[] = array("number" => "23", "class" => "スカート類", "text" => "巻きスカート(綿・麻・ポリ)");
		$array[] = array("number" => "24", "class" => "スカート類", "text" => "ヒダ付きスカート(綿・麻・ポリ)");
		$array[] = array("number" => "25", "class" => "スカート類", "text" => "バルーンスカート(綿・麻・ポリ)");
		$array[] = array("number" => "26", "class" => "スカート類", "text" => "セミフレアースカート(綿・麻・ポリ)");
		$array[] = array("number" => "99", "class" => "スカート類", "text" => "スカート類");
		$array[] = array("number" => "01", "class" => "シャツ類", "text" => "ワイシャツ　長袖");
		$array[] = array("number" => "02", "class" => "シャツ類", "text" => "ワイシャツ半袖");
		$array[] = array("number" => "03", "class" => "シャツ類", "text" => "長袖シャツ");
		$array[] = array("number" => "04", "class" => "シャツ類", "text" => "半袖シャツ");
		$array[] = array("number" => "05", "class" => "シャツ類", "text" => "長袖ブラウス");
		$array[] = array("number" => "06", "class" => "シャツ類", "text" => "半袖ブラウス");
		$array[] = array("number" => "07", "class" => "シャツ類", "text" => "半袖Ｔシャツ");
		$array[] = array("number" => "08", "class" => "シャツ類", "text" => "長袖Ｔシャツ");
		$array[] = array("number" => "09", "class" => "シャツ類", "text" => "キャミソール");
		$array[] = array("number" => "10", "class" => "シャツ類", "text" => "カットソー");
		$array[] = array("number" => "11", "class" => "シャツ類", "text" => "長袖ポロシャツ");
		$array[] = array("number" => "12", "class" => "シャツ類", "text" => "半袖ポロシャツ");
		$array[] = array("number" => "13", "class" => "シャツ類", "text" => "ノースリーブブラウス");
		$array[] = array("number" => "14", "class" => "シャツ類", "text" => "タンクトップ");
		$array[] = array("number" => "15", "class" => "シャツ類", "text" => "トレーナー");
		$array[] = array("number" => "16", "class" => "シャツ類", "text" => "ノースリーブシャツ");
		$array[] = array("number" => "99", "class" => "シャツ類", "text" => "シャツ類");
		$array[] = array("number" => "01", "class" => "ベスト類", "text" => "ベスト");
		$array[] = array("number" => "05", "class" => "ベスト類", "text" => "ベスト(綿・麻・ポリ)");
		$array[] = array("number" => "06", "class" => "ベスト類", "text" => "ベスト類(綿・麻・ポリ)");
		$array[] = array("number" => "99", "class" => "ベスト類", "text" => "ベスト類");
		$array[] = array("number" => "01", "class" => "ワンピース類", "text" => "ﾀｲﾄﾜﾝﾋﾟｰｽ");
		$array[] = array("number" => "02", "class" => "ワンピース類", "text" => "ﾌﾚｱｰﾜﾝﾋﾟｰｽ");
		$array[] = array("number" => "03", "class" => "ワンピース類", "text" => "ｷﾞｬｻﾞｰﾜﾝﾋﾟｰｽ");
		$array[] = array("number" => "04", "class" => "ワンピース類", "text" => "ｾﾐﾌﾚｱｰﾜﾝﾋﾟｰｽ");
		$array[] = array("number" => "05", "class" => "ワンピース類", "text" => "ひだ付きﾜﾝﾋﾟｰｽ");
		$array[] = array("number" => "06", "class" => "ワンピース類", "text" => "ﾉｰｽﾘｰﾌﾞｷﾞｬｻﾞｰﾜﾝﾋﾟｰｽ");
		$array[] = array("number" => "08", "class" => "ワンピース類", "text" => "半袖ひだ付きﾜﾝﾋﾟｰｽ");
		$array[] = array("number" => "09", "class" => "ワンピース類", "text" => "ﾉｰｽﾘｰﾌﾞひだ付きﾜﾝﾋﾟｰｽ");
		$array[] = array("number" => "11", "class" => "ワンピース類", "text" => "半袖ﾌﾟﾘｰﾂﾜﾝﾋﾟｰｽ");
		$array[] = array("number" => "12", "class" => "ワンピース類", "text" => "ﾉｰｽﾘｰﾌﾞ・ﾌﾟﾘｰﾂﾜﾝﾋﾟｰｽ");
		$array[] = array("number" => "15", "class" => "ワンピース類", "text" => "ﾉｰｽﾘｰﾌﾞﾀｲﾄﾜﾝﾋﾟｰｽ");
		$array[] = array("number" => "16", "class" => "ワンピース類", "text" => "ﾌﾟﾘｰﾂﾜﾝﾋﾟｰｽ");
		$array[] = array("number" => "17", "class" => "ワンピース類", "text" => "ﾉｰｽﾘｰﾌﾞｾﾐﾌﾚｱｰﾜﾝﾋﾟｰｽ");
		$array[] = array("number" => "18", "class" => "ワンピース類", "text" => "ﾉｰｽﾘｰﾌﾞﾌﾚｱｰﾜﾝﾋﾟｰｽ");
		$array[] = array("number" => "19", "class" => "ワンピース類", "text" => "半袖ﾀｲﾄﾜﾝﾋﾟｰｽ");
		$array[] = array("number" => "20", "class" => "ワンピース類", "text" => "半袖ｾﾐﾌﾚｱｰﾜﾝﾋﾟｰｽ");
		$array[] = array("number" => "21", "class" => "ワンピース類", "text" => "半袖ﾌﾚｱｰﾜﾝﾋﾟｰｽ");
		$array[] = array("number" => "22", "class" => "ワンピース類", "text" => "半袖ｷﾞｬｻﾞｰﾜﾝﾋﾟｰｽ");
		$array[] = array("number" => "25", "class" => "ワンピース類", "text" => "ﾀｲﾄﾜﾝﾋﾟｰｽ(綿・麻・ポリ)");
		$array[] = array("number" => "26", "class" => "ワンピース類", "text" => "ﾌﾚｱｰﾜﾝﾋﾟｰｽ(綿・麻・ポリ)");
		$array[] = array("number" => "27", "class" => "ワンピース類", "text" => "ｷﾞｬｻﾞｰﾜﾝﾋﾟｰｽ(綿・麻・ポリ)");
		$array[] = array("number" => "28", "class" => "ワンピース類", "text" => "ｾﾐﾌﾚｱｰﾜﾝﾋﾟｰｽ(綿・麻・ポリ)");
		$array[] = array("number" => "29", "class" => "ワンピース類", "text" => "ひだ付きﾜﾝﾋﾟｰｽ(綿・麻・ポリ)");
		$array[] = array("number" => "30", "class" => "ワンピース類", "text" => "ﾉｰｽﾘｰﾌﾞｷﾞｬｻﾞｰﾜﾝﾋﾟｰｽ(綿・麻・ポリ)");
		$array[] = array("number" => "31", "class" => "ワンピース類", "text" => "半袖ひだ付きﾜﾝﾋﾟｰｽ(綿・麻・ポリ)");
		$array[] = array("number" => "32", "class" => "ワンピース類", "text" => "ﾉｰｽﾘｰﾌﾞひだ付きﾜﾝﾋﾟｰｽ(綿・麻・ポリ)");
		$array[] = array("number" => "33", "class" => "ワンピース類", "text" => "半袖ﾌﾟﾘｰﾂﾜﾝﾋﾟｰｽ(綿・麻・ポリ)");
		$array[] = array("number" => "34", "class" => "ワンピース類", "text" => "ﾉｰｽﾘｰﾌﾞ・ﾌﾟﾘｰﾂﾜﾝﾋﾟｰｽ(綿・麻・ポリ)");
		$array[] = array("number" => "35", "class" => "ワンピース類", "text" => "ﾉｰｽﾘｰﾌﾞﾀｲﾄﾜﾝﾋﾟｰｽ(綿・麻・ポリ)");
		$array[] = array("number" => "36", "class" => "ワンピース類", "text" => "ﾌﾟﾘｰﾂﾜﾝﾋﾟｰｽ(綿・麻・ポリ)");
		$array[] = array("number" => "37", "class" => "ワンピース類", "text" => "ﾉｰｽﾘｰﾌﾞｾﾐﾌﾚｱｰﾜﾝﾋﾟｰｽ(綿・麻・ポリ)");
		$array[] = array("number" => "38", "class" => "ワンピース類", "text" => "ﾉｰｽﾘｰﾌﾞﾌﾚｱｰﾜﾝﾋﾟｰｽ(綿・麻・ポリ)");
		$array[] = array("number" => "39", "class" => "ワンピース類", "text" => "半袖ﾀｲﾄﾜﾝﾋﾟｰｽ(綿・麻・ポリ)");
		$array[] = array("number" => "40", "class" => "ワンピース類", "text" => "半袖ｾﾐﾌﾚｱｰﾜﾝﾋﾟｰｽ(綿・麻・ポリ)");
		$array[] = array("number" => "41", "class" => "ワンピース類", "text" => "半袖ﾌﾚｱｰﾜﾝﾋﾟｰｽ(綿・麻・ポリ)");
		$array[] = array("number" => "42", "class" => "ワンピース類", "text" => "半袖ｷﾞｬｻﾞｰﾜﾝﾋﾟｰｽ(綿・麻・ポリ)");
		$array[] = array("number" => "43", "class" => "ワンピース類", "text" => "ワンピース類(綿・麻・ポリ)");
		$array[] = array("number" => "99", "class" => "ワンピース類", "text" => "ワンピース類");
		$array[] = array("number" => "01", "class" => "ニット製品類", "text" => "長袖セーター");
		$array[] = array("number" => "02", "class" => "ニット製品類", "text" => "ハイネックセーター");
		$array[] = array("number" => "03", "class" => "ニット製品類", "text" => "タートルネックセーター");
		$array[] = array("number" => "04", "class" => "ニット製品類", "text" => "カーディガン");
		$array[] = array("number" => "05", "class" => "ニット製品類", "text" => "ニットベスト");
		$array[] = array("number" => "06", "class" => "ニット製品類", "text" => "ニットスカート");
		$array[] = array("number" => "07", "class" => "ニット製品類", "text" => "ニットジャンバー");
		$array[] = array("number" => "09", "class" => "ニット製品類", "text" => "ニットワンピース");
		$array[] = array("number" => "10", "class" => "ニット製品類", "text" => "ニットパンツ");
		$array[] = array("number" => "11", "class" => "ニット製品類", "text" => "ノースリーブセーター");
		$array[] = array("number" => "12", "class" => "ニット製品類", "text" => "ニットキャミソール");
		$array[] = array("number" => "13", "class" => "ニット製品類", "text" => "半袖セーター");
		$array[] = array("number" => "14", "class" => "ニット製品類", "text" => "丸首セーター");
		$array[] = array("number" => "15", "class" => "ニット製品類", "text" => "Ｖネックセーター");
		$array[] = array("number" => "16", "class" => "ニット製品類", "text" => "ニットハーフコート");
		$array[] = array("number" => "17", "class" => "ニット製品類", "text" => "ニットコート");
		$array[] = array("number" => "18", "class" => "ニット製品類", "text" => "ニットロングコート");
		$array[] = array("number" => "19", "class" => "ニット製品類", "text" => "ニットジャケット");
		$array[] = array("number" => "20", "class" => "ニット製品類", "text" => "半袖丸首ｾｰﾀｰ");
		$array[] = array("number" => "21", "class" => "ニット製品類", "text" => "半袖Vﾈｯｸｾｰﾀｰ");
		$array[] = array("number" => "22", "class" => "ニット製品類", "text" => "半袖ﾊｲﾈｯｸｾｰﾀｰ");
		$array[] = array("number" => "23", "class" => "ニット製品類", "text" => "半袖ﾀｰﾄﾙﾈｯｸｾｰﾀｰ");
		$array[] = array("number" => "24", "class" => "ニット製品類", "text" => "半袖ｶｰﾃﾞｨｶﾞﾝ");
		$array[] = array("number" => "25", "class" => "ニット製品類", "text" => "ﾉｰｽﾘｰﾌﾞ丸首ｾｰﾀｰ");
		$array[] = array("number" => "26", "class" => "ニット製品類", "text" => "ﾉｰｽﾘｰﾌﾞVﾈｯｸｾｰﾀｰ");
		$array[] = array("number" => "27", "class" => "ニット製品類", "text" => "ﾉｰｽﾘｰﾌﾞﾊｲﾈｯｸｾｰﾀｰ");
		$array[] = array("number" => "28", "class" => "ニット製品類", "text" => "ﾉｰｽﾘｰﾌﾞﾀｰﾄﾙﾈｯｸｾｰﾀｰ");
		$array[] = array("number" => "29", "class" => "ニット製品類", "text" => "ニット上着");
		$array[] = array("number" => "30", "class" => "ニット製品類", "text" => "長袖セーター(太糸）");
		$array[] = array("number" => "31", "class" => "ニット製品類", "text" => "ハイネックセーター（太糸）");
		$array[] = array("number" => "32", "class" => "ニット製品類", "text" => "タートルネックセーター（太糸）");
		$array[] = array("number" => "33", "class" => "ニット製品類", "text" => "カーディガン（太糸）");
		$array[] = array("number" => "34", "class" => "ニット製品類", "text" => "ニットベスト（太糸）");
		$array[] = array("number" => "35", "class" => "ニット製品類", "text" => "ニットスカート（太糸）");
		$array[] = array("number" => "36", "class" => "ニット製品類", "text" => "ニットジャンバー（太糸）");
		$array[] = array("number" => "37", "class" => "ニット製品類", "text" => "ニットワンピース（太糸）");
		$array[] = array("number" => "38", "class" => "ニット製品類", "text" => "ニットパンツ（太糸）");
		$array[] = array("number" => "39", "class" => "ニット製品類", "text" => "ノースリーブセーター（太糸）");
		$array[] = array("number" => "40", "class" => "ニット製品類", "text" => "ニットキャミソール（太糸）");
		$array[] = array("number" => "41", "class" => "ニット製品類", "text" => "半袖セーター（太糸）");
		$array[] = array("number" => "42", "class" => "ニット製品類", "text" => "丸首セーター（太糸）");
		$array[] = array("number" => "43", "class" => "ニット製品類", "text" => "Ｖネックセーター（太糸）");
		$array[] = array("number" => "44", "class" => "ニット製品類", "text" => "ニットハーフコート（太糸）");
		$array[] = array("number" => "45", "class" => "ニット製品類", "text" => "ニットコート（太糸）");
		$array[] = array("number" => "46", "class" => "ニット製品類", "text" => "ニットロングコート（太糸）");
		$array[] = array("number" => "47", "class" => "ニット製品類", "text" => "ニットジャケット（太糸）");
		$array[] = array("number" => "48", "class" => "ニット製品類", "text" => "半袖丸首ｾｰﾀｰ（太糸）");
		$array[] = array("number" => "49", "class" => "ニット製品類", "text" => "半袖Vﾈｯｸｾｰﾀｰ（太糸）");
		$array[] = array("number" => "50", "class" => "ニット製品類", "text" => "半袖ﾊｲﾈｯｸｾｰﾀｰ（太糸）");
		$array[] = array("number" => "51", "class" => "ニット製品類", "text" => "半袖ﾀｰﾄﾙﾈｯｸｾｰﾀｰ（太糸）");
		$array[] = array("number" => "52", "class" => "ニット製品類", "text" => "半袖ｶｰﾃﾞｨｶﾞﾝ（太糸）");
		$array[] = array("number" => "53", "class" => "ニット製品類", "text" => "ﾉｰｽﾘｰﾌﾞ丸首ｾｰﾀｰ（太糸）");
		$array[] = array("number" => "54", "class" => "ニット製品類", "text" => "ﾉｰｽﾘｰﾌﾞVﾈｯｸｾｰﾀｰ（太糸）");
		$array[] = array("number" => "55", "class" => "ニット製品類", "text" => "ﾉｰｽﾘｰﾌﾞﾊｲﾈｯｸｾｰﾀｰ（太糸）");
		$array[] = array("number" => "56", "class" => "ニット製品類", "text" => "ﾉｰｽﾘｰﾌﾞﾀｰﾄﾙﾈｯｸｾｰﾀｰ（太糸）");
		$array[] = array("number" => "57", "class" => "ニット製品類", "text" => "ニット上着（太糸）");
		$array[] = array("number" => "58", "class" => "ニット製品類", "text" => "ニット製品類（太糸）");
		$array[] = array("number" => "99", "class" => "ニット製品類", "text" => "ニット製品類");
		$array[] = array("number" => "01", "class" => "コート類", "text" => "ハーフコート");
		$array[] = array("number" => "02", "class" => "コート類", "text" => "コート");
		$array[] = array("number" => "03", "class" => "コート類", "text" => "ロングコート");
		$array[] = array("number" => "04", "class" => "コート類", "text" => "トレンチコート");
		$array[] = array("number" => "05", "class" => "コート類", "text" => "ピーコート");
		$array[] = array("number" => "06", "class" => "コート類", "text" => "レインコート");
		$array[] = array("number" => "07", "class" => "コート類", "text" => "ニットコート");
		$array[] = array("number" => "08", "class" => "コート類", "text" => "ガウン");
		$array[] = array("number" => "09", "class" => "コート類", "text" => "パーカー");
		$array[] = array("number" => "10", "class" => "コート類", "text" => "ダッフル・コート");
		$array[] = array("number" => "11", "class" => "コート類", "text" => "ハーフコート(綿・麻・ポリ)");
		$array[] = array("number" => "12", "class" => "コート類", "text" => "コート(綿・麻・ポリ)");
		$array[] = array("number" => "13", "class" => "コート類", "text" => "ロングコート(綿・麻・ポリ)");
		$array[] = array("number" => "99", "class" => "コート類", "text" => "コート類");
		$array[] = array("number" => "01", "class" => "ダウン製品類", "text" => "ダウンジャンバー");
		$array[] = array("number" => "02", "class" => "ダウン製品類", "text" => "ダウンパーカー");
		$array[] = array("number" => "03", "class" => "ダウン製品類", "text" => "ダウンコート");
		$array[] = array("number" => "04", "class" => "ダウン製品類", "text" => "ダウンフード");
		$array[] = array("number" => "05", "class" => "ダウン製品類", "text" => "ダウンベスト");
		$array[] = array("number" => "06", "class" => "ダウン製品類", "text" => "ダウンハーフコート");
		$array[] = array("number" => "07", "class" => "ダウン製品類", "text" => "ダウンロングコート");
		$array[] = array("number" => "08", "class" => "ダウン製品類", "text" => "ダウンジャケット");
		$array[] = array("number" => "99", "class" => "ダウン製品類", "text" => "ダウン製品類");
		$array[] = array("number" => "01", "class" => "小物類", "text" => "腰ベルト");
		$array[] = array("number" => "02", "class" => "小物類", "text" => "肩ベルト");
		$array[] = array("number" => "03", "class" => "小物類", "text" => "袖口ベルト");
		$array[] = array("number" => "04", "class" => "小物類", "text" => "首ベルト");
		$array[] = array("number" => "05", "class" => "小物類", "text" => "チンウォーマー");
		$array[] = array("number" => "06", "class" => "小物類", "text" => "ボー");
		$array[] = array("number" => "07", "class" => "小物類", "text" => "衿");
		$array[] = array("number" => "08", "class" => "小物類", "text" => "するめ");
		$array[] = array("number" => "09", "class" => "小物類", "text" => "フード");
		$array[] = array("number" => "10", "class" => "小物類", "text" => "ライナー");
		$array[] = array("number" => "11", "class" => "小物類", "text" => "マフラー");
		$array[] = array("number" => "12", "class" => "小物類", "text" => "スカーフ");
		$array[] = array("number" => "13", "class" => "小物類", "text" => "手袋");
		$array[] = array("number" => "14", "class" => "小物類", "text" => "ストール");
		$array[] = array("number" => "15", "class" => "小物類", "text" => "カフス");
		$array[] = array("number" => "17", "class" => "小物類", "text" => "フードファー");
		$array[] = array("number" => "19", "class" => "小物類", "text" => "ふくさ");
		$array[] = array("number" => "20", "class" => "小物類", "text" => "カマーベルト");
		$array[] = array("number" => "21", "class" => "小物類", "text" => "ネクタイ");
		$array[] = array("number" => "22", "class" => "小物類", "text" => "アスコットタイ");
		$array[] = array("number" => "23", "class" => "小物類", "text" => "蝶ネクタイ");
		$array[] = array("number" => "24", "class" => "小物類", "text" => "帽子");
		$array[] = array("number" => "30", "class" => "小物類", "text" => "傘");
		$array[] = array("number" => "31", "class" => "小物類", "text" => "バッグ");
		$array[] = array("number" => "32", "class" => "小物類", "text" => "ショール");
		$array[] = array("number" => "33", "class" => "小物類", "text" => "靴");
		$array[] = array("number" => "99", "class" => "小物類", "text" => "小物類");
		$array[] = array("number" => "01", "class" => "寝具類", "text" => "毛布　S");
		$array[] = array("number" => "02", "class" => "寝具類", "text" => "毛布　W");
		$array[] = array("number" => "03", "class" => "寝具類", "text" => "羽毛布団　S");
		$array[] = array("number" => "04", "class" => "寝具類", "text" => "羽毛布団　W");
		$array[] = array("number" => "05", "class" => "寝具類", "text" => "羊毛布団　S");
		$array[] = array("number" => "06", "class" => "寝具類", "text" => "羊毛布団　W");
		$array[] = array("number" => "07", "class" => "寝具類", "text" => "肌布団　S");
		$array[] = array("number" => "08", "class" => "寝具類", "text" => "肌布団　W");
		$array[] = array("number" => "10", "class" => "寝具類", "text" => "コタツ布団");
		$array[] = array("number" => "16", "class" => "寝具類", "text" => "布団カバー");
		$array[] = array("number" => "17", "class" => "寝具類", "text" => "ピロケース");
		$array[] = array("number" => "18", "class" => "寝具類", "text" => "シルク毛布　S");
		$array[] = array("number" => "19", "class" => "寝具類", "text" => "シルク毛布　W");
		$array[] = array("number" => "23", "class" => "寝具類", "text" => "羊毛布団");
		$array[] = array("number" => "27", "class" => "寝具類", "text" => "ベッドカバー");
		$array[] = array("number" => "28", "class" => "寝具類", "text" => "羽毛肌布団　S");
		$array[] = array("number" => "29", "class" => "寝具類", "text" => "羽毛肌布団　W");
		$array[] = array("number" => "30", "class" => "寝具類", "text" => "ベッドパット　S");
		$array[] = array("number" => "31", "class" => "寝具類", "text" => "ベッドパット　W");
		$array[] = array("number" => "99", "class" => "寝具類", "text" => "寝具類");
		$array[] = array("number" => "01", "class" => "和服類", "text" => "着物");
		$array[] = array("number" => "02", "class" => "和服類", "text" => "羽織");
		$array[] = array("number" => "03", "class" => "和服類", "text" => "帯");
		$array[] = array("number" => "04", "class" => "和服類", "text" => "長襦袢");
		$array[] = array("number" => "05", "class" => "和服類", "text" => "半襟");
		$array[] = array("number" => "06", "class" => "和服類", "text" => "足袋");
		$array[] = array("number" => "07", "class" => "和服類", "text" => "ゆかた");
		$array[] = array("number" => "09", "class" => "和服類", "text" => "雨コート");
		$array[] = array("number" => "10", "class" => "和服類", "text" => "袴");
		$array[] = array("number" => "13", "class" => "和服類", "text" => "一つ身着物");
		$array[] = array("number" => "14", "class" => "和服類", "text" => "四つ身着物");
		$array[] = array("number" => "16", "class" => "和服類", "text" => "振袖");
		$array[] = array("number" => "17", "class" => "和服類", "text" => "中振袖");
		$array[] = array("number" => "18", "class" => "和服類", "text" => "道行コート");
		$array[] = array("number" => "19", "class" => "和服類", "text" => "留袖");
		$array[] = array("number" => "20", "class" => "和服類", "text" => "甚平");
		$array[] = array("number" => "21", "class" => "和服類", "text" => "法衣");
		$array[] = array("number" => "23", "class" => "和服類", "text" => "肌襦袢");
		$array[] = array("number" => "25", "class" => "和服類", "text" => "浄衣");
		$array[] = array("number" => "26", "class" => "和服類", "text" => "帯揚げ");
		$array[] = array("number" => "27", "class" => "和服類", "text" => "半てん");
		$array[] = array("number" => "28", "class" => "和服類", "text" => "作務衣　上");
		$array[] = array("number" => "29", "class" => "和服類", "text" => "作務衣　下");
		$array[] = array("number" => "99", "class" => "和服類", "text" => "和服類");
		$array[] = array("number" => "01", "class" => "皮革・毛皮製品類", "text" => "皮革ジャンバー");
		$array[] = array("number" => "03", "class" => "皮革・毛皮製品類", "text" => "皮革パンツ");
		$array[] = array("number" => "04", "class" => "皮革・毛皮製品類", "text" => "皮革スカート");
		$array[] = array("number" => "05", "class" => "皮革・毛皮製品類", "text" => "スエードジャンバー");
		$array[] = array("number" => "07", "class" => "皮革・毛皮製品類", "text" => "スエードパンツ");
		$array[] = array("number" => "08", "class" => "皮革・毛皮製品類", "text" => "スエードスカート");
		$array[] = array("number" => "09", "class" => "皮革・毛皮製品類", "text" => "皮革コート");
		$array[] = array("number" => "14", "class" => "皮革・毛皮製品類", "text" => "毛皮ハーフコート");
		$array[] = array("number" => "15", "class" => "皮革・毛皮製品類", "text" => "毛皮コート");
		$array[] = array("number" => "16", "class" => "皮革・毛皮製品類", "text" => "毛皮ロングコート");
		$array[] = array("number" => "17", "class" => "皮革・毛皮製品類", "text" => "毛皮襟巻");
		$array[] = array("number" => "18", "class" => "皮革・毛皮製品類", "text" => "毛皮衿");
		$array[] = array("number" => "19", "class" => "皮革・毛皮製品類", "text" => "皮革ベルト");
		$array[] = array("number" => "20", "class" => "皮革・毛皮製品類", "text" => "スエードジャケット");
		$array[] = array("number" => "21", "class" => "皮革・毛皮製品類", "text" => "皮革ジャケット");
		$array[] = array("number" => "24", "class" => "皮革・毛皮製品類", "text" => "皮革手袋");
		$array[] = array("number" => "25", "class" => "皮革・毛皮製品類", "text" => "スエード手袋");
		$array[] = array("number" => "26", "class" => "皮革・毛皮製品類", "text" => "皮革半コート");
		$array[] = array("number" => "28", "class" => "皮革・毛皮製品類", "text" => "毛皮フードファー");
		$array[] = array("number" => "29", "class" => "皮革・毛皮製品類", "text" => "毛皮ベスト");
		$array[] = array("number" => "31", "class" => "皮革・毛皮製品類", "text" => "スエード半コート");
		$array[] = array("number" => "32", "class" => "皮革・毛皮製品類", "text" => "皮革ベスト");
		$array[] = array("number" => "33", "class" => "皮革・毛皮製品類", "text" => "皮革ロングコート");
		$array[] = array("number" => "34", "class" => "皮革・毛皮製品類", "text" => "皮革上着");
		$array[] = array("number" => "35", "class" => "皮革・毛皮製品類", "text" => "スエードベスト");
		$array[] = array("number" => "36", "class" => "皮革・毛皮製品類", "text" => "スエードコート");
		$array[] = array("number" => "37", "class" => "皮革・毛皮製品類", "text" => "スエードロングコート");
		$array[] = array("number" => "38", "class" => "皮革・毛皮製品類", "text" => "スエード上着");
		$array[] = array("number" => "39", "class" => "皮革・毛皮製品類", "text" => "スエードベルト");
		$array[] = array("number" => "40", "class" => "皮革・毛皮製品類", "text" => "毛皮ジャンパー");
		$array[] = array("number" => "41", "class" => "皮革・毛皮製品類", "text" => "毛皮ジャケット");
		$array[] = array("number" => "42", "class" => "皮革・毛皮製品類", "text" => "毛皮カフス");
		$array[] = array("number" => "96", "class" => "皮革・毛皮製品類", "text" => "皮革製品類");
		$array[] = array("number" => "97", "class" => "皮革・毛皮製品類", "text" => "スエード製品類");
		$array[] = array("number" => "98", "class" => "皮革・毛皮製品類", "text" => "毛皮製品類");
		$array[] = array("number" => "99", "class" => "皮革・毛皮製品類", "text" => "皮革・毛皮類");
		$array[] = array("number" => "03", "class" => "インテリア類", "text" => "カーテン");
		$array[] = array("number" => "04", "class" => "インテリア類", "text" => "テーブルクロス");
		$array[] = array("number" => "05", "class" => "インテリア類", "text" => "ソファーカバー");
		$array[] = array("number" => "07", "class" => "インテリア類", "text" => "タッセル");
		$array[] = array("number" => "12", "class" => "インテリア類", "text" => "ソファーカバー(S)");
		$array[] = array("number" => "13", "class" => "インテリア類", "text" => "ソファーカバー(M)");
		$array[] = array("number" => "14", "class" => "インテリア類", "text" => "ソファーカバー(L)");
		$array[] = array("number" => "15", "class" => "インテリア類", "text" => "ソファーカバー(LL)");
		$array[] = array("number" => "16", "class" => "インテリア類", "text" => "ソファーカバー(XL)");
		$array[] = array("number" => "99", "class" => "インテリア類", "text" => "インテリア類");
		$array[] = array("number" => "01", "class" => "その他", "text" => "その他");
		$array[] = array("number" => "05", "class" => "その他", "text" => "スキーつなぎ");
		$array[] = array("number" => "06", "class" => "その他", "text" => "つなぎ");
		$array[] = array("number" => "10", "class" => "その他", "text" => "ぬいぐるみ");
		$array[] = array("number" => "11", "class" => "その他", "text" => "サロペット");
		$array[] = array("number" => "12", "class" => "その他", "text" => "ケープ");
		$array[] = array("number" => "13", "class" => "その他", "text" => "吊りバンド");
		$array[] = array("number" => "14", "class" => "その他", "text" => "スキーパンツ");
		$array[] = array("number" => "15", "class" => "その他", "text" => "スキーサロペット");
		$array[] = array("number" => "01", "class" => "ベビー用品類", "text" => "ベビードレス");
		$array[] = array("number" => "02", "class" => "ベビー用品類", "text" => "ベビーケープ");
		$array[] = array("number" => "03", "class" => "ベビー用品類", "text" => "ベビーよだれかけ");
		$array[] = array("number" => "04", "class" => "ベビー用品類", "text" => "ベビー帽子");
		$array[] = array("number" => "05", "class" => "ベビー用品類", "text" => "ベビーおくるみ");
		$array[] = array("number" => "06", "class" => "ベビー用品類", "text" => "ベビー毛布");
		$array[] = array("number" => "07", "class" => "ベビー用品類", "text" => "ベビー布団");
		$array[] = array("number" => "08", "class" => "ベビー用品類", "text" => "ベビー用品類");
		$array[] = array("number" => "01", "class" => "ドレス類", "text" => "ドレス");
		$array[] = array("number" => "02", "class" => "ドレス類", "text" => "ｳｴﾃﾞｨﾝｸﾞﾄﾞﾚｽ");
		$array[] = array("number" => "99", "class" => "ドレス類", "text" => "ドレス類");
		?>
		<select name="item2" id="item2" class="selectable3">
			<option value="">さらに絞り込む</option>
		<?php foreach ($array AS $value) { ?>
			<?php $selected = ($val == $value['number']) ? ' selected="selected"' : ''; ?>
				<option value="<?php echo $value['number'] ?>" class="<?php echo $value['class'] ?>" title="<?php echo $value['text'] ?>"<?php echo $selected ?>><?php echo $value['text'] ?></option>
		<?php } ?>
		</select>
		<?php
	}

	/*
	 * ワードローブ検索のアイテムセレクト
	 */
	public function html_wardrobe_select_color($val = null) {
		$array[] = array("number" => "01", "text" => "赤");
		$array[] = array("number" => "02", "text" => "白");
		$array[] = array("number" => "03", "text" => "黒");
		$array[] = array("number" => "04", "text" => "黄");
		$array[] = array("number" => "05", "text" => "緑");
		$array[] = array("number" => "06", "text" => "青");
		$array[] = array("number" => "07", "text" => "茶");
		$array[] = array("number" => "08", "text" => "グレー");
		$array[] = array("number" => "09", "text" => "紫");
		$array[] = array("number" => "10", "text" => "金・銀");
		$array[] = array("number" => "11", "text" => "ピンク");
		$array[] = array("number" => "14", "text" => "多色");
		?>
		<select name="color" id="color" class="selectable2">
			<option value="">選択してください</option>
		<?php foreach ($array AS $value) { ?>
			<?php $selected = ($val == $value['number']) ? ' selected="selected"' : ''; ?>
				<option value="<?php echo $value['number'] ?>" title="<?php echo $value['text'] ?>"<?php echo $selected ?>><?php echo $value['text'] ?></option>
		<?php } ?>
		</select>
		<?php
	}

	/*
	 * ワードローブ検索の色・柄サブセレクト
	 */
	public function html_wardrobe_subselect_color($val = null) {

		$array[] = array("number" => "01", "class" => "赤", "text" => "赤");
		$array[] = array("number" => "03", "class" => "赤", "text" => "赤系");
		$array[] = array("number" => "10", "class" => "赤", "text" => "赤系水玉");
		$array[] = array("number" => "11", "class" => "赤", "text" => "赤系千鳥格子");
		$array[] = array("number" => "12", "class" => "赤", "text" => "赤系杉織り");
		$array[] = array("number" => "14", "class" => "赤", "text" => "赤系横縞");
		$array[] = array("number" => "15", "class" => "赤", "text" => "赤系縦縞");
		$array[] = array("number" => "16", "class" => "赤", "text" => "赤系ストライプ");
		$array[] = array("number" => "17", "class" => "赤", "text" => "赤系花柄");
		$array[] = array("number" => "18", "class" => "赤", "text" => "赤系柄");
		$array[] = array("number" => "19", "class" => "赤", "text" => "赤系チェック");
		$array[] = array("number" => "20", "class" => "赤", "text" => "赤白チェック");
		$array[] = array("number" => "21", "class" => "赤", "text" => "赤地に白の水玉");
		$array[] = array("number" => "22", "class" => "赤", "text" => "ワイン色");
		$array[] = array("number" => "01", "class" => "白", "text" => "白");
		$array[] = array("number" => "02", "class" => "白", "text" => "オフ白");
		$array[] = array("number" => "03", "class" => "白", "text" => "クリーム");
		$array[] = array("number" => "04", "class" => "白", "text" => "白黒");
		$array[] = array("number" => "05", "class" => "白", "text" => "白紺");
		$array[] = array("number" => "11", "class" => "白", "text" => "白系千鳥格子");
		$array[] = array("number" => "12", "class" => "白", "text" => "白黒横縞");
		$array[] = array("number" => "13", "class" => "白", "text" => "白黒縦縞");
		$array[] = array("number" => "14", "class" => "白", "text" => "白系横縞");
		$array[] = array("number" => "15", "class" => "白", "text" => "白系縦縞");
		$array[] = array("number" => "16", "class" => "白", "text" => "白系ストライプ");
		$array[] = array("number" => "17", "class" => "白", "text" => "白系花柄");
		$array[] = array("number" => "18", "class" => "白", "text" => "白系柄");
		$array[] = array("number" => "19", "class" => "白", "text" => "白系チェック");
		$array[] = array("number" => "20", "class" => "白", "text" => "白に黒の縁取り");
		$array[] = array("number" => "21", "class" => "白", "text" => "白黒チェック");
		$array[] = array("number" => "22", "class" => "白", "text" => "白に紺の縁取り");
		$array[] = array("number" => "23", "class" => "白", "text" => "白紺チエック");
		$array[] = array("number" => "24", "class" => "白", "text" => "白に黒の水玉");
		$array[] = array("number" => "25", "class" => "白", "text" => "白に紺の水玉");
		$array[] = array("number" => "26", "class" => "白", "text" => "白紺縦縞");
		$array[] = array("number" => "27", "class" => "白", "text" => "白紺横縞");
		$array[] = array("number" => "28", "class" => "白", "text" => "白系杉織り");
		$array[] = array("number" => "30", "class" => "白", "text" => "白黒柄");
		$array[] = array("number" => "32", "class" => "白", "text" => "白系水玉");
		$array[] = array("number" => "01", "class" => "黒", "text" => "黒");
		$array[] = array("number" => "02", "class" => "黒", "text" => "黒系");
		$array[] = array("number" => "03", "class" => "黒", "text" => "黒系シモフリ");
		$array[] = array("number" => "04", "class" => "黒", "text" => "黒系杉織り");
		$array[] = array("number" => "05", "class" => "黒", "text" => "黒白千鳥格子");
		$array[] = array("number" => "14", "class" => "黒", "text" => "黒系横縞");
		$array[] = array("number" => "15", "class" => "黒", "text" => "黒系縦縞");
		$array[] = array("number" => "16", "class" => "黒", "text" => "黒系ストライプ");
		$array[] = array("number" => "17", "class" => "黒", "text" => "黒系花柄");
		$array[] = array("number" => "18", "class" => "黒", "text" => "黒系柄");
		$array[] = array("number" => "19", "class" => "黒", "text" => "黒系チェック");
		$array[] = array("number" => "20", "class" => "黒", "text" => "黒に白の縁取り");
		$array[] = array("number" => "21", "class" => "黒", "text" => "黒に白の水玉");
		$array[] = array("number" => "22", "class" => "黒", "text" => "黒系水玉");
		$array[] = array("number" => "23", "class" => "黒", "text" => "黒系千鳥格子");
		$array[] = array("number" => "24", "class" => "黒", "text" => "黒白");
		$array[] = array("number" => "25", "class" => "黒", "text" => "黒白横縞");
		$array[] = array("number" => "26", "class" => "黒", "text" => "黒白縦縞");
		$array[] = array("number" => "27", "class" => "黒", "text" => "黒白チェック");
		$array[] = array("number" => "28", "class" => "黒", "text" => "黒白柄");
		$array[] = array("number" => "01", "class" => "黄", "text" => "黄");
		$array[] = array("number" => "02", "class" => "黄", "text" => "オレンジ");
		$array[] = array("number" => "03", "class" => "黄", "text" => "黄色系");
		$array[] = array("number" => "14", "class" => "黄", "text" => "黄系横縞");
		$array[] = array("number" => "15", "class" => "黄", "text" => "黄系縦縞");
		$array[] = array("number" => "16", "class" => "黄", "text" => "黄系ストライプ");
		$array[] = array("number" => "17", "class" => "黄", "text" => "黄系花柄");
		$array[] = array("number" => "18", "class" => "黄", "text" => "黄系柄");
		$array[] = array("number" => "19", "class" => "黄", "text" => "黄系チェック");
		$array[] = array("number" => "20", "class" => "黄", "text" => "やまぶき色");
		$array[] = array("number" => "21", "class" => "黄", "text" => "黄系水玉");
		$array[] = array("number" => "22", "class" => "黄", "text" => "黄系千鳥格子");
		$array[] = array("number" => "23", "class" => "黄", "text" => "黄系杉織り");
		$array[] = array("number" => "24", "class" => "黄", "text" => "オレンジ系柄");
		$array[] = array("number" => "01", "class" => "緑", "text" => "緑");
		$array[] = array("number" => "02", "class" => "緑", "text" => "黄緑");
		$array[] = array("number" => "03", "class" => "緑", "text" => "ミントグリーン");
		$array[] = array("number" => "04", "class" => "緑", "text" => "緑系");
		$array[] = array("number" => "14", "class" => "緑", "text" => "緑系横縞");
		$array[] = array("number" => "15", "class" => "緑", "text" => "緑系縦縞");
		$array[] = array("number" => "16", "class" => "緑", "text" => "緑系ストライプ");
		$array[] = array("number" => "17", "class" => "緑", "text" => "緑系花柄");
		$array[] = array("number" => "18", "class" => "緑", "text" => "緑系柄");
		$array[] = array("number" => "19", "class" => "緑", "text" => "緑系チェック");
		$array[] = array("number" => "20", "class" => "緑", "text" => "濃モスグリーン");
		$array[] = array("number" => "21", "class" => "緑", "text" => "薄モスグリーン");
		$array[] = array("number" => "22", "class" => "緑", "text" => "緑系水玉");
		$array[] = array("number" => "23", "class" => "緑", "text" => "緑系千鳥格子");
		$array[] = array("number" => "24", "class" => "緑", "text" => "緑系杉織り");
		$array[] = array("number" => "25", "class" => "緑", "text" => "モスグリーン");
		$array[] = array("number" => "01", "class" => "青", "text" => "青");
		$array[] = array("number" => "02", "class" => "青", "text" => "水色");
		$array[] = array("number" => "03", "class" => "青", "text" => "紺");
		$array[] = array("number" => "04", "class" => "青", "text" => "青系");
		$array[] = array("number" => "14", "class" => "青", "text" => "青系横縞");
		$array[] = array("number" => "15", "class" => "青", "text" => "青系縦縞");
		$array[] = array("number" => "16", "class" => "青", "text" => "青系ストライプ");
		$array[] = array("number" => "17", "class" => "青", "text" => "青系花柄");
		$array[] = array("number" => "18", "class" => "青", "text" => "青系柄");
		$array[] = array("number" => "19", "class" => "青", "text" => "青系チェック");
		$array[] = array("number" => "20", "class" => "青", "text" => "紺に白の縁取り");
		$array[] = array("number" => "21", "class" => "青", "text" => "紺に白の水玉");
		$array[] = array("number" => "22", "class" => "青", "text" => "濃紺");
		$array[] = array("number" => "23", "class" => "青", "text" => "青系水玉");
		$array[] = array("number" => "24", "class" => "青", "text" => "青系千鳥格子");
		$array[] = array("number" => "25", "class" => "青", "text" => "青系杉織り");
		$array[] = array("number" => "01", "class" => "茶", "text" => "茶");
		$array[] = array("number" => "02", "class" => "茶", "text" => "ベージュ");
		$array[] = array("number" => "03", "class" => "茶", "text" => "焦げ茶");
		$array[] = array("number" => "04", "class" => "茶", "text" => "茶系");
		$array[] = array("number" => "05", "class" => "茶", "text" => "茶系杉織り");
		$array[] = array("number" => "14", "class" => "茶", "text" => "茶系横縞");
		$array[] = array("number" => "15", "class" => "茶", "text" => "茶系縦縞");
		$array[] = array("number" => "16", "class" => "茶", "text" => "茶系ストライプ");
		$array[] = array("number" => "17", "class" => "茶", "text" => "茶系花柄");
		$array[] = array("number" => "18", "class" => "茶", "text" => "茶系柄");
		$array[] = array("number" => "19", "class" => "茶", "text" => "茶系チェック");
		$array[] = array("number" => "20", "class" => "茶", "text" => "キャメル");
		$array[] = array("number" => "21", "class" => "茶", "text" => "カーキ");
		$array[] = array("number" => "22", "class" => "茶", "text" => "からし色");
		$array[] = array("number" => "23", "class" => "茶", "text" => "あずき色");
		$array[] = array("number" => "24", "class" => "茶", "text" => "茶系水玉");
		$array[] = array("number" => "25", "class" => "茶", "text" => "茶系千鳥格子");
		$array[] = array("number" => "01", "class" => "グレー", "text" => "グレー");
		$array[] = array("number" => "02", "class" => "グレー", "text" => "濃いグレー");
		$array[] = array("number" => "03", "class" => "グレー", "text" => "薄いグレー");
		$array[] = array("number" => "04", "class" => "グレー", "text" => "グレー系");
		$array[] = array("number" => "14", "class" => "グレー", "text" => "グレー系横縞");
		$array[] = array("number" => "15", "class" => "グレー", "text" => "グレー系縦縞");
		$array[] = array("number" => "16", "class" => "グレー", "text" => "グレー系ストライプ");
		$array[] = array("number" => "17", "class" => "グレー", "text" => "グレー系花柄");
		$array[] = array("number" => "18", "class" => "グレー", "text" => "グレー系柄");
		$array[] = array("number" => "19", "class" => "グレー", "text" => "グレー系チェック");
		$array[] = array("number" => "21", "class" => "グレー", "text" => "グレー系水玉");
		$array[] = array("number" => "22", "class" => "グレー", "text" => "グレー千鳥格子");
		$array[] = array("number" => "23", "class" => "グレー", "text" => "グレー系杉織り");
		$array[] = array("number" => "01", "class" => "紫", "text" => "紫");
		$array[] = array("number" => "02", "class" => "紫", "text" => "濃い紫");
		$array[] = array("number" => "03", "class" => "紫", "text" => "薄い紫");
		$array[] = array("number" => "04", "class" => "紫", "text" => "紫系花柄");
		$array[] = array("number" => "05", "class" => "紫", "text" => "紫系柄");
		$array[] = array("number" => "06", "class" => "紫", "text" => "紫系");
		$array[] = array("number" => "07", "class" => "紫", "text" => "紫系横縞");
		$array[] = array("number" => "08", "class" => "紫", "text" => "紫系縦縞");
		$array[] = array("number" => "09", "class" => "紫", "text" => "紫系ストライプ");
		$array[] = array("number" => "10", "class" => "紫", "text" => "紫系チェック");
		$array[] = array("number" => "11", "class" => "紫", "text" => "紫系水玉");
		$array[] = array("number" => "12", "class" => "紫", "text" => "紫系千鳥格子");
		$array[] = array("number" => "13", "class" => "紫", "text" => "紫系杉織り");
		$array[] = array("number" => "01", "class" => "金・銀", "text" => "ゴールド");
		$array[] = array("number" => "02", "class" => "金・銀", "text" => "シルバー");
		$array[] = array("number" => "06", "class" => "金・銀", "text" => "ゴールド系柄");
		$array[] = array("number" => "07", "class" => "金・銀", "text" => "シルバー系柄");
		$array[] = array("number" => "01", "class" => "ピンク", "text" => "ピンク");
		$array[] = array("number" => "02", "class" => "ピンク", "text" => "濃ピンク");
		$array[] = array("number" => "03", "class" => "ピンク", "text" => "薄ピンク");
		$array[] = array("number" => "04", "class" => "ピンク", "text" => "ピンク系花柄");
		$array[] = array("number" => "05", "class" => "ピンク", "text" => "サーモンピンク");
		$array[] = array("number" => "06", "class" => "ピンク", "text" => "ピンク系");
		$array[] = array("number" => "07", "class" => "ピンク", "text" => "ピンク系縦縞");
		$array[] = array("number" => "08", "class" => "ピンク", "text" => "ピンク系横縞");
		$array[] = array("number" => "09", "class" => "ピンク", "text" => "ピンク系チェック");
		$array[] = array("number" => "11", "class" => "ピンク", "text" => "ピンク系柄");
		$array[] = array("number" => "12", "class" => "ピンク", "text" => "ピンク系ストライプ");
		$array[] = array("number" => "13", "class" => "ピンク", "text" => "ピンク系水玉");
		$array[] = array("number" => "14", "class" => "ピンク", "text" => "ピンク系千鳥格子");
		$array[] = array("number" => "15", "class" => "ピンク", "text" => "ピンク系杉織り");
		$array[] = array("number" => "01", "class" => "多色", "text" => "多色");
		$array[] = array("number" => "02", "class" => "多色", "text" => "多色柄");
		$array[] = array("number" => "03", "class" => "多色", "text" => "多色横縞");
		$array[] = array("number" => "04", "class" => "多色", "text" => "多色縦縞");
		$array[] = array("number" => "05", "class" => "多色", "text" => "多色ストライプ");
		$array[] = array("number" => "06", "class" => "多色", "text" => "多色花柄");
		$array[] = array("number" => "07", "class" => "多色", "text" => "多色チェック");
		$array[] = array("number" => "08", "class" => "多色", "text" => "多色水玉");
		?>
		<select name="color2" id="color2" class="selectable2">
			<option value="">さらに絞り込む</option>
		<?php foreach ($array AS $value) { ?>
			<?php $selected = ($val == $value['number']) ? ' selected="selected"' : ''; ?>
				<option value="<?php echo $value['number'] ?>" class="<?php echo $value['class'] ?>" title="<?php echo $value['text'] ?>"<?php echo $selected ?>><?php echo $value['text'] ?></option>
		<?php } ?>
		</select>
		<?php
	}

}
?>
