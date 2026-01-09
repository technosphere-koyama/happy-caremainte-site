<?php


$sns_name = (strlen(SESSION::read('PUBLIC_USER.nickname'))) ? '<span class="PCpart">'.SESSION::read('PUBLIC_USER.nickname').'</span>' : '';

var_dump(SESSION::read('PUBLIC_USER'));

?>
<div class="title"><a href="/"><img src="/_assets/img/header/logo.png" width="186" height="68" alt="ハッピー ケアメンテ"></a></div>
    <div class="sublink">
		<ul>
			<li class="OrderBtn PCpart"><a href="/order/">ご注文・お申し込み</a></li>
			<li><a href="/carementeh_search/"><img src="/_assets/img/header/icon_search.gif" width="14" height="14" alt="SEARCH"></a></li>
			<li><a href="/mypage/"><img src="/_assets/img/header/icon_sns.gif" width="17" height="16" alt="SNS"><?php echo $sns_name ?></a></li>
			<li class="first"><a href="/contact/"><img src="/_assets/img/header/icon_mail.gif" width="16" height="13" alt="MAIL"></a></li>
            <li class="tel SPpart"><a href="tel:0120886868"><img src="/_assets/img/header/icon_tel.gif" width="15" height="15" alt="TEL"></a></li>
            <li class="tel PCpart"><!--<span>お問い合せ・ご質問・集荷依頼： </span>-->0120-88-6868</li>
		</ul>
	</div>

<!--PC-->
<div class="PCpart">
	<div class="navi">
		<ul class="PCmenu">
			<li class="menu__mega">
            	<a href="/use/"<?php echo_current("use");?>>ご注文／価格表</a>
                <div class="menu__second-level gnavi01">
                	<div class="menu__1st">
                    	<h3 class="headline">ご注文方法</h3>
                        <ul>
                            <li><a href="/use/howtoorder/web/">ホームページから</a></li>
                            <li><a href="/use/howtoorder/app/">スマホアプリから</a></li>
                            <li><a href="/use/howtoorder/tel/">電話・FAXから</a></li>
                            <li><a href="/use/howtoorder/shop/">提携ショップから</a></li>
                            <li><a href="/use/howtoorder/mail/">郵便局・コンビニから</a></li>
                            <li><a href="/use/howtoorder/payment/">お支払い方法</a></li>
                        </ul>
                    </div>
                    <div class="menu__2nd noHeadline">
                        <ul>
                            <li><a href="/use/howtoorder/point/">ハッピーポイントについて</a></li>
                            <li><a href="/use/howtoorder/reparation/">事故賠償制度</a></li>
                            <li><a href="/use/howtoorder/package/">仕上り品のパッケージ（箱）について</a></li>
                            <li><a href="/use/howtoorder/reasonable/">「ケアメンテ&reg;」をリーズナブルにご利用いただく方法</a></li>
                            <li><a href="/use/howtoorder/similarity/">類似サービスにご注意ください</a></li>
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
                        </ul>
                    </div>
                    <div class="menu__4th">
                    	<h3 class="headline">評価</h3>
                        <ul>
                        	<li><a href="/review/">お客様のレビュー</a></li>
                            <li><a href="/use/evaluate/blog/">ブログでの第三者評価</a></li>
                            <li><a href="/use/evaluate/value/">ケアメンテ&reg;とクリーニングの評価</a></li>
                        </ul>
                    </div>
                </div>
			</li>
			<li class="menu__mega">
            	<a href="/carementeh/"<?php echo_current("carementeh");?>>サービス概要・メニュー一覧</a>
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
                            <li><a href="/carementeh/overview/difference/">ケアメンテ&reg;とクリーニングはどう違う？</a></li>
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
            	<a href="/technology/"<?php echo_current("technology");?>>ケアメンテ&reg;の技術</a>
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
                            <li><a href="/technology/before_after/leather/">皮革・毛皮</a></li>
                        </ul>
                    </div>
                    <div class="menu__3rd noHeadline">
                        <ul>
                            <li><a href="/technology/before_after/bag/">バッグ</a></li>
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
                            <li><a href="/technology/data/comparison/">汗汚れの洗浄比較実験</a></li>
                            <li><a href="/technology/data/tradition/yuzen/">京の伝統技法とケアメンテ</a></li>
                            <li><a href="/technology/data/brand/">ブランド各社からの洗浄依頼品</a></li>
                            <li><a href="/technology/data/monograph/">ケアメンテ水系洗浄の学会誌掲載論文一覧</a></li>
                        </ul>
                    </div>
                </div>
			</li>
			<li class="menu__mega">
            	<a href="/shop/"<?php echo_current("shop");?>>提携ブランド・取扱い店舗一覧</a>
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
                            <li><a href="/shop/brand/abeno_harukas/">あべのハルカス近鉄本店</a></li>
                            <li><a href="/shop/brand/sinjuku_takashimaya/">新宿タカシマヤ</a></li>
                            <li><a href="/shop/brand/yokohama_takashimaya/">横浜タカシマヤ</a></li>
                            <li><a href="/shop/brand/seibu_ikebukuro/">西武池袋本店</a></li>
                        </ul>
                    </div>
                    <div class="menu__3rd noHeadline">
                        <ul>
                            <li><a href="/shop/brand/tomorrowland/">TOMORROWLAND</a></li>
                            <li><a href="/shop/brand/beams/">BEAMS</a></li>
                            <li><a href="/shop/brand/united-arrows/">UNITED ARROWS</a></li>
                        </ul>
                    </div>
                </div>
			</li>
			<li class="menu__mega">
            	<a href="/corporate/"<?php echo_current("corporate");?>>会社情報</a>
                <div class="menu__second-level gnavi05">
                	<div class="menu__1st">
                        <h3 class="headline">会社概要</h3>
                        <ul>
                            <li><a href="/corporate/company/profile/">企業情報</a></li>
                            <li><a href="/corporate/company/winning/">認定・受賞一覧</a></li>
                            <li><a href="/corporate/company/ip/">知的財産（特許・商標）</a></li>
                            <li><a href="/pdf/fukusyoku.pdf">服飾関連の皆様へ</a></li>
                            <li><a href="/pdf/kanren_brand.pdf">アパレル業の皆様へ</a></li>
                            <li><a href="/pdf/kanren_ryutu.pdf">流通業の皆様へ</a></li>
                            <li><a href="/pdf/kanren_kaden.pdf">洗濯機メーカーの皆様へ</a></li>
                        </ul>
                    </div>
                    <div class="menu__2nd">
                        <h3 class="headline">メディア情報</h3>
                        <ul class="row">
                            <li><a href="/corporate/media/literary/">メディア報道特集</a></li>
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
                            <li><a href="/corporate/recruit/cultivation/">人材育成について</a></li>
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
                            <li><a href="/corporate/csr/unicef/">世界の子供達を応援しよう</a></li>
                        </ul>
                        <h3 class="headline">ハッピー顧客満足度指数</h3>
                        <ul>
                            <li><a href="/corporate/satisfaction/">顧客満足度指数</a></li>
                        </ul>
                    </div>
                </div>
			</li>
		</ul>
	</div>
</div>

<!--SP-->
<div class="SPpart">
	<div class="menu"><img src="/_assets/img_sp/header/icon_menu.png" width="26" height="28" alt="MENU"></div>
	<span class="menu_bg"></span>
	<div class="menu_over">
		<div class="closebtn"><img src="/_assets/img_sp/menu/btn_close.png" width="26" height="28" alt="CLOSE"></div>
		<div class="wrap">
			<ul class="link1">
				<li><a href="/use/"><img src="/_assets/img_sp/menu/btn_menu01.png" width="134" height="12" alt="ORDER 集荷依頼（ご注文）"/></a></li>
				<li><a href="/carementeh/"><img src="/_assets/img_sp/menu/btn_menu02.png" width="183" height="12" alt="CAREMENTEH ケアメンテとは？"/></a></li>
				<li><a href="/knowledge/"><img src="/_assets/img_sp/menu/btn_menu03.png" width="169" height="12" alt="KNOWLEDGE おしゃれの雑学"/></a></li>
				<li><a href="/shop/"><img src="/_assets/img_sp/menu/btn_menu04.png" width="204" height="12" alt="SHOP LIST 提携ブランド・取扱い店舗一覧"/></a></li>
				<li><a href="/corporate/"><img src="/_assets/img_sp/menu/btn_menu05.png" width="123" height="12" alt="COMPANY 会社情報"/></a></li>
			</ul>
			<ul class="link2">
				<li><a href=""><img src="/_assets/img_sp/menu/btn_facebook.png" width="10" height="21" alt="facebook"></a></li>
				<li><a href=""><img src="/_assets/img_sp/menu/btn_twitter.png" width="18" height="21" alt="twitter"></a></li>
				<li><a href=""><img src="/_assets/img_sp/menu/btn_instagram.png" width="18" height="21" alt="instagram"></a></li>
				<li><a href=""><img src="/_assets/img_sp/menu/btn_youtube.png" width="17" height="21" alt="youtube"></a></li>
			</ul>
			<ul class="link3">
				<li><a href="/contact/">お問い合わせ</a></li>
				<li><a href="">採用情報</a></li>
				<li><a href="">個人情報保護方針</a></li>
				<li><a href="">このサイトについて</a></li>
			</ul>
		</div>
	</div>
</div>

<?php
function is_current( $uri = "" ) {
	$uri = trim( $uri, "/" );
	$request_uri = $_SERVER['REQUEST_URI'];

	if( $uri && strpos($request_uri."/", "/".$uri."/", 0) !== FALSE ) {
		return true;
	}
	
	if( $uri == 'products' && strpos($request_uri."/", "/".'category'."/", 0) !== FALSE ) {
		return true;
	}
	
	$request_uri = trim(str_replace( "/index.php", "", $request_uri ), '/');
	if( !$uri && !$request_uri ) {
		return true;
	}
	return false;
}

function echo_current( $uri = "" ) {
	if(is_current( $uri )) {
		echo ' class="on"';
	};
}
?>
