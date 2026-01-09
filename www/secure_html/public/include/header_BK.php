<?php


$redirect_url = urlencode($_SERVER["REQUEST_URI"]);

if(class_exists ('StaticFunction')) {

	if (!StaticFunction::is_empty(SESSION::read("PUBLIC_USER.name1"))) {
		$sns_name = '<div class="PCpart"><a href="/mypage/"><i class="fa fa-user" aria-hidden="true"></i>' . SESSION::read("PUBLIC_USER.name1") . " " . SESSION::read("PUBLIC_USER.name2") . 'さま</a><a href="/mypage/logout/" class="logout"></a></div><div class="SPpart"><a href="/mypage/"><i class="fa fa-user" aria-hidden="true"></i>' . SESSION::read("PUBLIC_USER.name1") . " " . SESSION::read("PUBLIC_USER.name2") . 'さま</a></div>';
		$tsunagu_link = "/mypage/sns.html";
	}
	else {
		$sns_name = '<div><a href="/login/?callback='.$redirect_url.'"><i class="fa fa-user" aria-hidden="true"></i>ログイン<span class="SPpart">／新規会員登録</span></a><a href="/entry/" class="signin"></a></div>';
		$tsunagu_link = "/login/happy.html";
	}
}
else {
	if (!session_id()) {
		session_name("kh");
		session_save_path($_SERVER['DOCUMENT_ROOT'] . "/../core/tmp/session");
		@session_start();
	}

	if (isset($_SESSION['PUBLIC_USER']['name1'])) {
		$sns_name = '<div class="PCpart"><a href="/mypage/"><i class="fa fa-user" aria-hidden="true"></i>' . $_SESSION['PUBLIC_USER']['name1'] . " " . $_SESSION['PUBLIC_USER']['name2'] . 'さま</a><a href="/mypage/logout/" class="logout"></a></div><div class="SPpart"><a href="/mypage/"><i class="fa fa-user" aria-hidden="true"></i>' . $_SESSION['PUBLIC_USER']['name1'] . " " . $_SESSION['PUBLIC_USER']['name2'] . 'さま</a></div>';
		$tsunagu_link = "/mypage/sns.html";
	}
	else {
		$sns_name = '<div><a href="/login/?callback='.$redirect_url.'"><i class="fa fa-user" aria-hidden="true"></i>ログイン<span class="SPpart">／新規会員登録</span></a><a href="/entry/" class="signin"></a></div>';
		$tsunagu_link = "/login/happy.html";
	}
}

?>

		<link href="https://maxcdn.bootstrapcdn.com/font-awesome/4.7.0/css/font-awesome.min.css" rel="stylesheet" integrity="sha384-wvfXpqpZZVQGK6TAh5PVlGOfQNHSoD2xbE+QkPxCAFlNEevoEH3Sl0sibVcOQVnN" crossorigin="anonymous">

		<script type="text/javascript">
		if(navigator.userAgent.indexOf('Android') > 0){
			$("html").addClass("android");
		}
		</script>

		<div class="top_head">
			<div class="seo_txt">クリーニングの駆け込み寺ハッピーケアメンテ。高級な衣服をケアメンテしています。</div>
			<div class="submenu PCpart">
				<ul>
					<li><?php echo $sns_name ?></li>
					<li><a href="/contact/">お問い合わせ</a></li>
					<li><a href="/corporate/recruit/cultivation/">リクルート</a></li>
				</ul>
				<ul class="submenuSNS">
					<li><a href="https://www.facebook.com/pages/%e3%83%8f%e3%83%83%e3%83%94%e3%83%bc%2d%e3%82%b1%e3%82%a2%e3%83%a1%e3%83%b3%e3%83%86Happy%2dCareMenteh%2f107312759374049" target="_blank"><i class="fa fa-facebook" aria-hidden="true"></i></a></li>
					<li><a href="https://twitter.com/Happy_KYOTO" target="_blank"><i class="fa fa-twitter" aria-hidden="true"></i></a></li>
					<li><a href="https://www.instagram.com/happycarementeh/" target="_blank"><i class="fa fa-instagram" aria-hidden="true"></i></a></li>
					<li><a href="/movie/" target="_blank"><i class="fa fa-youtube" aria-hidden="true"></i></a></li>
				</ul>
			</div>
		</div>

<div class="wrap">
			<div class="title PCpart"><a href="/"><img src="https://www.kyoto-happy.co.jp:8443/_assets/img/header/logo.gif" alt="ハッピー ケアメンテ"></a></div>
			<div class="title SPpart"><a href="/"><img src="https://www.kyoto-happy.co.jp:8443/_assets/img/header/logo_sp.gif" alt="ハッピー ケアメンテ"></a></div>
			<div class="sublink PCpart">
				<ul>
					<li><a href="/carementeh_search/"><dl><dt><img src="https://www.kyoto-happy.co.jp:8443/_assets/img/header/ico_search.svg" alt="さがす"></dt><dd><span>ケアメンテ実例集</span>さがす</dd></dl></a></li>
					<li><a href="/review/"><dl><dt><img src="https://www.kyoto-happy.co.jp:8443/_assets/img/header/ico_review.svg" alt="きづく"></dt><dd><span>お客さまレビュー</span>きづく</dd></dl></a></li>
					<li><a href="<?php echo $tsunagu_link ?>"><dl><dt><img src="https://www.kyoto-happy.co.jp:8443/_assets/img/header/ico_sns.svg" alt="つなぐ"></dt><dd><span>ハッピーSNS</span>つなぐ</dd></dl></a></li>
					<li><a href="/mypage/"><dl><dt><img src="https://www.kyoto-happy.co.jp:8443/_assets/img/header/ico_mypage.svg" alt="マイページ"></dt><dd><span>お客さま専用ページ</span>マイページ</dd></dl></a></li>
					<li class="tel"><a href="#inline-content5" class="popup"><img src="https://www.kyoto-happy.co.jp:8443/_assets/img/header/tel.gif" alt="ハッピーはお客さまとの会話を大切にしています 0120-88-6868 月～土 9:00～18:00（日曜・祝祭日は除く）"></a></li>
					<li class="OrderBtn"><a href="/order/">WEBからの<br>ご注文はこちら</a></li>
				</ul>
			</div>
			<!--<div class="tooltip_templates" style="display:none">
				<span id="tooltip_content">
					<ul>
						<li><a href="/mypage/">ログイン</a></li>
						<li><a href="/entry/">新規会員登録（ID発行）</a></li>
						<li><a href="/mypage/logout/">ログアウト</a></li>
					</ul>
				</span>
			</div>
			<script>
				$(document).ready(function() {
					$('.tooltip').tooltipster({
						interactive: true,
						contentCloning: true,
						trigger: 'click',
						theme: 'tooltipster-light'
					});
				});
			</script>-->

			<!--SP header-->
			<div class="wrapSP">
				<div class="submenuSNS">
					<ul>
						<li><a href="https://www.facebook.com/pages/%e3%83%8f%e3%83%83%e3%83%94%e3%83%bc%2d%e3%82%b1%e3%82%a2%e3%83%a1%e3%83%b3%e3%83%86Happy%2dCareMenteh%2f107312759374049" target="_blank"><i class="fa fa-facebook" aria-hidden="true"></i></a></li>
						<li><a href="https://twitter.com/Happy_KYOTO" target="_blank"><i class="fa fa-twitter" aria-hidden="true"></i></a></li>
						<li><a href="https://www.instagram.com/happycarementeh/" target="_blank"><i class="fa fa-instagram" aria-hidden="true"></i></a></li>
						<li><a href="/movie/" target="_blank"><i class="fa fa-youtube" aria-hidden="true"></i></a></li>
					</ul>
				</div>
				<div class="submenu">
					<ul>
						<li><div><?php echo $sns_name ?></div></li>
					</ul>
					<ul class="recruit">
						<li><a href="/corporate/recruit/cultivation/">リクルート</a></li>
					</ul>
				</div>

				<div class="mainmenu">
					<div class="OrderBtn"><a href="/order/">ご注文はこちら<i class="fa fa-angle-right" aria-hidden="true"></i></a></div>
					<div class="menu"><img src="https://www.kyoto-happy.co.jp:8443/_assets/img_sp/header/icon_menu.png" width="26" height="28" alt="MENU"></div>
					<span class="menu_bg"></span>

					<div class="menu_over">
						<div class="closebtn"><img src="https://www.kyoto-happy.co.jp:8443/_assets/img_sp/menu/btn_close.png" width="22" height="25" alt="CLOSE"></div>
						<div id="SPGnavi">
							<div class="menu1">
								<div class="SPGnavi_menu">ご注文方法/価格表</div>
								<ul>
									<li><h3>ご注文方法</h3></li>
									<li><a href="/use/">ご利用の流れ</a></li>
									<li><a href="/use/howtoorder/tel/">電話・FAXから</a></li>
									<li><a href="/use/howtoorder/web/">ホームページから</a></li>
									<li><a href="/use/howtoorder/apps/">スマホアプリから</a></li>
									<li><a href="/use/howtoorder/shop/">提携SHOPから</a></li>
									<li><a href="/use/howtoorder/mail/">郵便局・コンビニから</a></li>
									<li><a href="/use/howtoorder/payment/">お支払方法</a></li>
									<li><a href="/use/howtoorder/point/">ハッピーポイントについて</a></li>
									<li><a href="/use/howtoorder/reparation/">事故賠償制度</a></li>
									<li><a href="/use/howtoorder/package/">美しいシルエットのままお届けするために</a></li>
									<li><a href="/use/howtoorder/reasonable/">「ケアメンテ&reg;」をリーズナブルにご利用いただく方法</a></li>
									<li><a href="/faq/">よくあるご質問</a></li>
									<li><h3>価格表／カタログ請求</h3></li>
									<li><a href="/use/price/list/">価格表</a></li>
									<li><a href="/use/price/catalog/">カタログ請求／PDF閲覧</a></li>
									<li><h3>注文する</h3></li>
									<li><a href="/order/">お申し込み・ご注文</a></li>
									<li><a href="/entry/">新規会員登録（ID発行）</a></li>
									<li><h3>評価</h3></li>
									<li><a href="/review/">お客様のレビュー</a></li>
									<li><a href="/use/evaluate/value/">ケアメンテ&reg;とクリーニングの評価</a></li>
									<li><a href="/use/evaluate/blog/">ブログでの第三者評価</a></li>
									<li><a href="/use/evaluate/satisfaction/">顧客満足度指数</a></li>
								</ul>
								<div class="SPGnavi_menu">サービス概要・メニュー一覧</div>
								<ul>
									<li><h3>サービス概要</h3></li>
									<li><a href="/carementeh/overview/style/">ケアメンテ&reg; 仕事スタイル</a></li>
									<li><a href="/carementeh/overview/etymology/">ケアメンテ&reg;の語源</a></li>
									<li><a href="/carementeh/overview/flow/">ケアメンテ&reg;の仕事の流れ</a></li>
									<li><a href="/carementeh/overview/karte/">ハッピー電子カルテシステム</a></li>
									<li><a href="/carementeh/overview/counseling/">カウンセリング</a></li>
									<li><a href="/mypageuse/">マイページ・SNSの使い方</a></li>
									<li><h3>サービスメニュー一覧</h3></li>
									<li><a href="/carementeh/service/aquadry/">基本洗浄「水油系アクアドライ&reg;」</a></li>
									<li><a href="/carementeh/service/ripron/">再生技術「リプロン&reg;」</a></li>
									<li><a href="/carementeh/service/valueon/">加工技術「バリューON&reg;」</a></li>
									<li><a href="/carementeh/service/grain/">レザー修復「レザーGRAIN再現加工」</a></li>
									<li><a href="/carementeh/service/kimono/">きもの・仕立てたままで水洗い「きもの無重力」</a></li>
									<li><a href="/carementeh/service/reform/">お直し／リフォーム</a></li>
									<li><a href="/carementeh/service/wardrobe/">保管お預かり「ハッピーワードローブ&reg;」</a></li>
								</ul>
								<div class="SPGnavi_menu">ケアメンテを支える技術いろいろ</div>
								<ul>
									<li><h3>ハッピーの水系洗浄を支える技術</h3></li>
									<li><a href="/technology/innovation/weightlessness/">ハッピー独自の技術「無重力バランス洗浄技法」</a></li>
									<li><a href="/technology/innovation/lecirian/">サイジング技法「レシリアン」</a></li>
									<li><a href="/technology/innovation/press/">仕上げ技術「シルエットプレス&reg;」</a></li>
									<li><h3>Before &amp; After／ケアメンテ&reg;事例集</h3></li>
									<li><a href="/technology/before_after/ripron/">「リプロン」事例集</a></li>
									<li><a href="/technology/before_after/list/">Before &amp; After集</a></li>
									<li><a href="/technology/before_after/suit/">上質スーツ</a></li>
									<li><a href="/technology/before_after/down/">最高級ダウン</a></li>
									<li><a href="/technology/before_after/shirt/">上質シャツ</a></li>
									<li><a href="/technology/before_after/bag/">バッグ</a></li>
									<li><a href="/technology/before_after/leather/">皮革・毛皮</a></li>
									<li><a href="/technology/before_after/wedding/">ウェディングドレス</a></li>
									<li><a href="/technology/before_after/macintosh/">マッキントッシュ</a></li>
									<li><a href="/technology/before_after/lifecare/">インテリア・ファニチャー・羽毛布団</a></li>
									<li><a href="/technology/before_after/tenpyou/">天平の古代染めを洗う</a></li>
									<li><a href="/technology/before_after/kimono/">百年昔の「きもの」を洗う</a></li>
									<li><h3>ケアメンテ技術を支える検証データ</h3></li>
									<li><a href="/technology/data/weightlessness/ma_test/">「無重力バランス洗浄技法（特許）」関連</a></li>
									<li><a href="/technology/data/tradition/yuzen/">京の伝統技法とケアメンテ</a></li>
									<li><a href="/technology/data/comparison/">汗汚れの洗浄比較実験</a></li>
									<li><a href="/technology/data/brand/">ブランド各社からの洗浄依頼品</a></li>
									<li><a href="/technology/data/monograph/">ケアメンテ水系洗浄の学会誌掲載論文一覧</a></li>
								</ul>
								<div class="SPGnavi_menu">提携ブランド・取扱い店舗一覧</div>
								<ul>
									<li><h3>現在地から検索</h3></li>
									<li><a href="/shop_search/">GPSで検索する</a></li>
									<li><h3>ショップ情報</h3></li>
									<li><a href="/shop/brand/abeno_harukas/">あべのハルカス近鉄本店</a></li>
									<li><a href="/shop/brand/sinjuku_takashimaya/">新宿タカシマヤ</a></li>
									<li><a href="/shop/brand/yokohama_takashimaya/">横浜タカシマヤ</a></li>
									<li><a href="/shop/brand/seibu_ikebukuro/">西武池袋本店</a></li>
									<li><a href="/shop/brand/tomorrowland/">TOMORROWLAND</a></li>
									<li><a href="/shop/brand/beams/">BEAMS</a></li>
									<li><a href="/shop/brand/united-arrows/">UNITED ARROWS</a></li>
									<li><a href="/shop/brand/aquascutum/">Aquascutum</a></li>
									<li><a href="/shop/brand/durban/">DURBAN</a></li>
								</ul>
								<div class="SPGnavi_menu">会社情報</div>
								<ul>
									<li><h3>会社概要</h3></li>
									<li><a href="/corporate/company/profile/">企業情報</a></li>
									<li><a href="/corporate/company/winning/">認定・受賞一覧</a></li>
									<li><a href="/corporate/company/ip/">知的財産（特許・商標）</a></li>
									<li><a href="https://www.kyoto-happy.co.jp:8443/pdf/fukusyoku.pdf" target="_blank">服飾関連の皆様へ</a></li>
									<li><a href="https://www.kyoto-happy.co.jp:8443/pdf/kanren_brand.pdf" target="_blank">アパレル業の皆様へ</a></li>
									<li><a href="https://www.kyoto-happy.co.jp:8443/pdf/kanren_ryutu.pdf" target="_blank">流通業の皆様へ</a></li>
									<li><a href="https://www.kyoto-happy.co.jp:8443/pdf/kanren_kaden.pdf" target="_blank">洗濯機メーカーの皆様へ</a></li>
									<li><h3>メディア情報</h3></li>
									<li><a href="/corporate/media/media_list/">メディア報道特集</a></li>
									<li><a href="/corporate/media/past/">過去の報道記録</a></li>
									<li><a href="/corporate/media/lecture/">講演活動の記録</a></li>
									<li><a href="/corporate/media/literary/">著作物一覧</a></li>
									<li><h3>リクルート</h3></li>
									<li><a href="/corporate/recruit/cultivation/">人財育成について</a></li>
									<li><a href="/corporate/recruit/staff/">ケアメンテスタッフの募集</a></li>
									<li><a href="/corporate/recruit/executive/">経営幹部候補の募集</a></li>
									<li><h3>環境への取組み</h3></li>
									<li><a href="/corporate/csr/weightlessness/">無重力バランス洗浄による環境保護</a></li>
									<li><a href="/corporate/csr/world2007/">環境と洗浄の世界大会 2007 秋</a></li>
									<li><a href="/corporate/csr/moribito/">森びとプロジェクト委員会</a></li>
									<li><a href="/corporate/csr/unicef/">ハッピーワールド助け合いプロジェクト</a></li>
									<li><h3>ヨーロッパ洗浄技術交流紀行</h3></li>
									<li><a href="/corporate/europe/2013_summer/">2013 初夏</a></li>
									<li><a href="/corporate/europe/2012_autumn/">2012 初秋</a></li>
									<li><a href="/corporate/europe/2006_summer/">2006 夏</a></li>
									<li><a href="/corporate/europe/2006_spring/">2006 春</a></li>
									<li><a href="/corporate/europe/2005_autumn/">2005 秋</a></li>
								</ul>
							</div>

							<div class="menu2">
								<ul>
									<li><a href="/carementeh_search/"><img src="https://www.kyoto-happy.co.jp:8443/_assets/img/index/ico_search.svg" alt="さがす"><h2><span>Before &amp; After事例集</span>さがす</h2></a></li>
									<li><a href="/review/"><img src="https://www.kyoto-happy.co.jp:8443/_assets/img/index/ico_review.svg" alt="きづく"><h2><span>お客さまレビュー</span>きづく</h2></a></li>
									<li><a href="/mypage/sns.html"><img src="https://www.kyoto-happy.co.jp:8443/_assets/img/index/ico_sns.svg" alt="つなぐ"><h2><span>ハッピーSNS</span>つなぐ</h2></a></li>
									<li><a href="/mypage/"><img src="https://www.kyoto-happy.co.jp:8443/_assets/img/index/ico_mypage.svg" alt="マイページ"><h2><span>お客さま専用ページ</span>マイページ</h2></a></li>
								</ul>
							</div>

							<div class="menu3">
								<ul>
									<li><a href="https://www.facebook.com/pages/%e3%83%8f%e3%83%83%e3%83%94%e3%83%bc%2d%e3%82%b1%e3%82%a2%e3%83%a1%e3%83%b3%e3%83%86Happy%2dCareMenteh%2f107312759374049" target="_blank"><i class="fa fa-facebook" aria-hidden="true"></i></a></li>
									<li><a href="https://twitter.com/Happy_KYOTO" target="_blank"><i class="fa fa-twitter" aria-hidden="true"></i></a></li>
									<li><a href="https://www.instagram.com/happycarementeh/" target="_blank"><i class="fa fa-instagram" aria-hidden="true"></i></a></li>
									<li><a href="/movie/" target="_blank"><i class="fa fa-youtube" aria-hidden="true"></i></a></li>
								</ul>
							</div>
							<div class="menu4">
								<ul>
									<li><a href="/contact/">お問い合わせ</a></li>
									<li><a href="/corporate/recruit/cultivation/">リクルート</a></li>
									<li><a href="/privacy/">特定商取引法に基づく表記</a></li>
								</ul>
							</div>
						</div>
					</div>
				</div>
			</div>
		</div>

		<!--PC Gnavi-->
		<div class="PCpart">
			<div class="navi">
				<ul class="PCmenu">
					<li class="menu__mega">
						<a>ご注文方法／価格表</a>
						<div class="menu__second-level gnavi01">
							<div class="menu__1st">
								<h3 class="headline">ご注文方法</h3>
								<ul>
									<li><a href="/use/">ご利用の流れ</a></li>
									<li><a href="/use/howtoorder/tel/">電話・FAXから</a></li>
									<li><a href="/use/howtoorder/web/">ホームページから</a></li>
									<li><a href="/use/howtoorder/apps/">スマホアプリから</a></li>
									<li><a href="/use/howtoorder/shop/">提携SHOPから</a></li>
									<li><a href="/use/howtoorder/mail/">郵便局・コンビニから</a></li>
								</ul>
							</div>
							<div class="menu__2nd noHeadline">
								<ul>
									<li><a href="/use/howtoorder/payment/">お支払方法</a></li>
									<li><a href="/use/howtoorder/point/">ハッピーポイントについて</a></li>
									<li><a href="/use/howtoorder/reparation/">事故賠償制度</a></li>
									<li><a href="/use/howtoorder/package/">美しいシルエットのままお届けするために</a></li>
									<li><a href="/use/howtoorder/reasonable/">「ケアメンテ&reg;」をリーズナブルにご利用いただく方法</a></li>
									<li><a href="/faq/">よくあるご質問</a></li>
								</ul>
							</div>
							<div class="menu__3rd">
								<h3 class="headline">価格表／カタログ請求</h3>
								<ul class="row">
									<li><a href="/use/price/list/">価格表</a></li>
									<li><a href="/use/price/catalog/">カタログ請求／PDF閲覧</a></li>
								</ul>
								<h3 class="headline">注文する</h3>
								<ul>
									<li><a href="/order/">お申し込み・ご注文</a></li>
									<li><a href="/entry/">新規会員登録（ID発行）</a></li>
								</ul>
							</div>
							<div class="menu__4th">
								<h3 class="headline">評価</h3>
								<ul>
									<li><a href="/review/">お客様のレビュー</a></li>
									<li><a href="/use/evaluate/value/">ケアメンテ&reg;とクリーニングの評価</a></li>
									<li><a href="/use/evaluate/blog/">ブログでの第三者評価</a></li>
									<li><a href="/use/evaluate/satisfaction/">顧客満足度指数</a></li>
								</ul>
							</div>
						</div>
					</li>
					<li class="menu__mega">
						<a>サービス概要・メニュー一覧</a>
						<div class="menu__second-level gnavi02">
							<div class="menu__1st">
								<h3 class="headline">サービス概要</h3>
								<ul>
									<li><a href="/carementeh/overview/style/">ケアメンテ&reg; 仕事スタイル</a></li>
									<li><a href="/carementeh/overview/etymology/">ケアメンテ&reg;の語源</a></li>
									<li><a href="/carementeh/overview/flow/">ケアメンテ&reg;の仕事の流れ</a></li>
								</ul>
							</div>
							<div class="menu__2nd noHeadline">
								<ul>
									<li><a href="/carementeh/overview/karte/">ハッピー電子カルテシステム</a></li>
									<li><a href="/carementeh/overview/counseling/">カウンセリング</a></li>
									<li><a href="/mypageuse/">マイページ・SNSの使い方</a></li>
								</ul>
							</div>
							<div class="menu__3rd">
								<h3 class="headline">サービスメニュー一覧</h3>
								<ul>
									<li><a href="/carementeh/service/aquadry/">基本洗浄「水油系アクアドライ&reg;」</a></li>
									<li><a href="/carementeh/service/ripron/">再生技術「リプロン&reg;」</a></li>
									<li><a href="/carementeh/service/valueon/">加工技術「バリューON&reg;」</a></li>
									<li><a href="/carementeh/service/grain/">レザー修復「レザーGRAIN再現加工」</a></li>
								</ul>
							</div>
							<div class="menu__4th noHeadline">
								<ul>
									<li><a href="/carementeh/service/kimono/">きもの・仕立てたままで水洗い「きもの無重力」</a></li>
									<li><a href="/carementeh/service/reform/">お直し／リフォーム</a></li>
									<li><a href="/carementeh/service/wardrobe/">保管お預かり「ハッピーワードローブ&reg;」</a></li>
								</ul>
							</div>
						</div>
					</li>
					<li class="menu__mega">
						<a>ケアメンテを支える技術いろいろ</a>
						<div class="menu__second-level gnavi03">
							<div class="menu__1st">
								<h3 class="headline">ハッピーの水系洗浄を支える技術</h3>
								<ul>
									<li><a href="/technology/innovation/weightlessness/">ハッピー独自の技術「無重力バランス洗浄技法」</a></li>
									<li><a href="/technology/innovation/lecirian/">サイジング技法「レシリアン」</a></li>
									<li><a href="/technology/innovation/press/">仕上げ技術「シルエットプレス&reg;」</a></li>
								</ul>
							</div>
							<div class="menu__2nd">
								<h3 class="headline">Before &amp; After／ケアメンテ&reg;事例集</h3>
								<ul>
									<li><a href="/technology/before_after/ripron/">「リプロン」事例集</a></li>
									<li><a href="/technology/before_after/list/">Before &amp; After集</a></li>
									<li><a href="/technology/before_after/suit/">上質スーツ</a></li>
									<li><a href="/technology/before_after/down/">最高級ダウン</a></li>
									<li><a href="/technology/before_after/shirt/">上質シャツ</a></li>
									<li><a href="/technology/before_after/bag/">バッグ</a></li>
								</ul>
							</div>
							<div class="menu__3rd noHeadline">
								<ul>
									<li><a href="/technology/before_after/leather/">皮革・毛皮</a></li>
									<li><a href="/technology/before_after/wedding/">ウェディングドレス</a></li>
									<li><a href="/technology/before_after/macintosh/">マッキントッシュ</a></li>
									<li><a href="/technology/before_after/lifecare/">インテリア・ファニチャー・羽毛布団</a></li>
									<li><a href="/technology/before_after/tenpyou/">天平の古代染めを洗う</a></li>
									<li><a href="/technology/before_after/kimono/">百年昔の「きもの」を洗う</a></li>
								</ul>
							</div>
							<div class="menu__4th">
								<h3 class="headline">ケアメンテ技術を支える検証データ</h3>
								<ul>
									<li><a href="/technology/data/weightlessness/ma_test/">「無重力バランス洗浄技法（特許）」関連</a></li>
									<li><a href="/technology/data/tradition/yuzen/">京の伝統技法とケアメンテ</a></li>
									<li><a href="/technology/data/comparison/">汗汚れの洗浄比較実験</a></li>
									<li><a href="/technology/data/brand/">ブランド各社からの洗浄依頼品</a></li>
									<li><a href="/technology/data/monograph/">ケアメンテ水系洗浄の学会誌掲載論文一覧</a></li>
								</ul>
							</div>
						</div>
					</li>
					<li class="menu__mega">
						<a>提携ブランド・取扱い店舗一覧</a>
						<div class="menu__second-level gnavi04">
							<div class="menu__1st">
								<h3 class="headline">現在地から検索</h3>
								<ul>
									<li><a href="/shop_search/">GPSで検索する</a></li>
								</ul>
							</div>
							<div class="menu__2nd">
								<h3 class="headline">ショップ情報</h3>
								<ul>
									<li><a href="/shop/brand/tomorrowland/">TOMORROWLAND</a></li>
									<li><a href="/shop/brand/beams/">BEAMS</a></li>
									<li><a href="/shop/brand/united-arrows/">UNITED ARROWS</a></li>
									<li><a href="/shop/brand/aquascutum/">Aquascutum</a></li>
									<li><a href="/shop/brand/durban/">DURBAN</a></li>
								</ul>
							</div>
							<div class="menu__3rd noHeadline">
								<ul>
									<li><a href="/shop/brand/abeno_harukas/">あべのハルカス近鉄本店</a></li>
									<li><a href="/shop/brand/sinjuku_takashimaya/">新宿タカシマヤ</a></li>
									<li><a href="/shop/brand/yokohama_takashimaya/">横浜タカシマヤ</a></li>
									<li><a href="/shop/brand/seibu_ikebukuro/">西武池袋本店</a></li>
								</ul>
							</div>
						</div>
					</li>
					<li class="menu__mega">
						<a>会社情報</a>
						<div class="menu__second-level gnavi05">
							<div class="menu__1st">
								<h3 class="headline">会社概要</h3>
								<ul>
									<li><a href="/corporate/company/profile/">企業情報</a></li>
									<li><a href="/corporate/company/winning/">認定・受賞一覧</a></li>
									<li><a href="/corporate/company/ip/">知的財産（特許・商標）</a></li>
									<li><a href="https://www.kyoto-happy.co.jp:8443/pdf/fukusyoku.pdf" target="_blank">服飾関連の皆様へ</a></li>
									<li><a href="https://www.kyoto-happy.co.jp:8443/pdf/kanren_brand.pdf" target="_blank">アパレル業の皆様へ</a></li>
									<li><a href="https://www.kyoto-happy.co.jp:8443/pdf/kanren_ryutu.pdf" target="_blank">流通業の皆様へ</a></li>
									<li><a href="https://www.kyoto-happy.co.jp:8443/pdf/kanren_kaden.pdf" target="_blank">洗濯機メーカーの皆様へ</a></li>
								</ul>
							</div>
							<div class="menu__2nd">
								<h3 class="headline">メディア情報</h3>
								<ul class="row">
									<li><a href="/corporate/media/media_list/">メディア報道特集</a></li>
									<li><a href="/corporate/media/past/">過去の報道記録</a></li>
									<li><a href="/corporate/media/lecture/">講演活動の記録</a></li>
									<li><a href="/corporate/media/literary/">著作物一覧</a></li>
								</ul>
								<h3 class="headline">ヨーロッパ洗浄技術交流紀行</h3>
								<ul>
									<li><a href="/corporate/europe/2013_summer/">2013 初夏</a></li>
									<li><a href="/corporate/europe/2012_autumn/">2012 初秋</a></li>
									<li><a href="/corporate/europe/2006_summer/">2006 夏</a></li>
								</ul>
							</div>
							<div class="menu__3rd">
								<h3 class="headline">リクルート</h3>
								<ul class="row">
									<li><a href="/corporate/recruit/cultivation/">人財育成について</a></li>
									<li><a href="/corporate/recruit/staff/">ケアメンテスタッフの募集</a></li>
									<li><a href="/corporate/recruit/executive/">経営幹部候補の募集</a></li>
								</ul>
								<ul>
									<li><a href="/corporate/europe/2006_spring/">2006 春</a></li>
									<li><a href="/corporate/europe/2005_autumn/">2005 秋</a></li>
								</ul>
							</div>
							<div class="menu__4th">
								<h3 class="headline">環境への取組み</h3>
								<ul class="row">
									<li><a href="/corporate/csr/weightlessness/">無重力バランス洗浄による環境保護</a></li>
									<li><a href="/corporate/csr/world2007/">環境と洗浄の世界大会 2007 秋</a></li>
									<li><a href="/corporate/csr/moribito/">森びとプロジェクト委員会</a></li>
									<li><a href="/corporate/csr/unicef/">ハッピーワールド助け合いプロジェクト</a></li>
								</ul>
							</div>
						</div>
					</li>
				</ul>
			</div>
		</div>

		<!--Tel Popup-->
		<div style="display:none;" class="news_headline-detail">
			<section id="inline-content5">
				<h3>休業日（日曜・祝祭日）中の電話対応について</h3>
				<p>音声ガイダンスにしたがってお名前・お電話番号・ご用件を録音してください。<br>
					翌営業日に折返しご連絡させていただきます。<br>
					<br>
					ホームページからのご注文（ご依頼品お引取りのお申込み）につきましては、<br class="PCpart">
					24時間受付けております。<br>
					当社休業日に関わらず、日曜・祝祭日もご依頼品のお引取りに伺うことができますので、<br class="PCpart">
					ぜひご利用ください。<br>
					<br>
					ホームページからの<a href="/order/">ご注文はコチラ</a></p>
			</section>
		</div>

<?php
function is_current($uri = "") {
	$uri = trim($uri, "/");
	$request_uri = $_SERVER['REQUEST_URI'];

	if ($uri && strpos($request_uri . "/", "/" . $uri . "/", 0) !== FALSE) {
		return true;
	}

	if ($uri == 'products' && strpos($request_uri . "/", "/" . 'category' . "/", 0) !== FALSE) {
		return true;
	}

	$request_uri = trim(str_replace("/index.php", "", $request_uri), '/');
	if (!$uri && !$request_uri) {
		return true;
	}
	return false;
}

function echo_current($uri = "") {
	if (is_current($uri)) {
		echo ' class="on"';
	};
}
?>
