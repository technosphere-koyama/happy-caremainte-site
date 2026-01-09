<?php
$webroot = $_SERVER['DOCUMENT_ROOT'];
$stylesheet_directory_uri = get_stylesheet_directory_uri();
//include($webroot."/include/footer.php");
include($webroot."/include/body_retargeting_cord.php");
?>
<div class="footer_sns">
	<div class="container">
		<ul>
			<li><a href="https://www.facebook.com/pages/%e3%83%8f%e3%83%83%e3%83%94%e3%83%bc%2d%e3%82%b1%e3%82%a2%e3%83%a1%e3%83%b3%e3%83%86Happy%2dCareMenteh%2f107312759374049" target="_blank"><i class="fa fa-facebook" aria-hidden="true"></i></a></li>
			<li><a href="https://twitter.com/Happy_KYOTO" target="_blank"><i class="fa fa-twitter" aria-hidden="true"></i></a></li>
			<li><a href="https://www.instagram.com/happycarementeh/" target="_blank"><i class="fa fa-instagram" aria-hidden="true"></i></a></li>
			<li><a href="https://www.youtube.com/channel/UCZyJC69VvnDqIAgsEQ-rTeQ" target="_blank"><i class="fa fa-youtube" aria-hidden="true"></i></a></li>
	</ul>
	</div>
</div>
<div class="footer_pagetop pagetop">
	<div class="container">
		<ul>
			<li><a href="#top"><i class="fa fa-angle-up" aria-hidden="true"></i><span>Top</span></a></li>
		</ul>
	</div>
</div>
<!--　/.footer_sns -->
<?php if ( is_home() || is_front_page() ) : ?>
<?php else : ?>
<div class="guideNav SPpart">
  <h2>サチコのハッピーナビ</h2>
  <div class="guideNavtxt">
    <div class="guideNavtxt_img">
      <img src="<?php echo $stylesheet_directory_uri; ?>/img/counseling.png" alt="">
    </div>
    <div class="guideNavtxt_box">
      <p>私サチコがご案内します。<br>何をご覧になりたいですか？</p>
    </div>
  </div>
  <ul class="guideNav_btm">
    <li class="menu__first-level">
      <a>ケアメンテの利用方法を知りたい。<br><span>ケアメンテのご利用方法や価格表、お近くの店舗検索や提携ブランド、ケアメンテの評価をご覧頂けます。</span></a>
      <div class="menu__second-level">
        <div class="container">
          <div class="menu__second-column">
            <h3 class="headline act">ご利用方法・価格表</h3>
            <div class="menu__second-body menu__two_column">
              <ul>
                <li><a href="/use/">ご利用方法を知りたい</a></li>
                <li><a href="/use/price/list/">価格表を見たい</a></li>
                <li><a href="/use/price/catalog/">カタログを請求したり、<br>カタログPDFを閲覧したい</a></li>
                <li><a href="/use/howtoorder/point/">ハッピーポイントについて知りたい</a></li>
              </ul>
              <ul>
								<li><a href="/kiyaku/">利用規約について知りたい</a></li>
                <li><a href="/use/howtoorder/reparation/">事故賠償制度について知りたい</a></li>
                <li><a href="/use/howtoorder/similarity/">類似サービスにご注意ください</a></li>
                <li><a href="/faq/">よくあるご質問</a></li>
              </ul>
            </div>
          </div>
          <div class="menu__second-column">
            <h3 class="headline">提携ブランド/全国取扱い店舗一覧</h3>
            <div class="menu__second-body">
              <ul>
                <li><a href="/shop_search/">現在地から取扱店を検索する</a></li>
                <li><a href="/shop/">全国の取り扱いショップを見る</a></li>
                <li class="PCpart">&nbsp;</li>
                <li class="PCpart">&nbsp;</li>
              </ul>
            </div>
          </div>
          <div class="menu__second-column">
            <h3 class="headline">ケアメンテの評価</h3>
            <div class="menu__second-body">
              <ul>
                <li><a href="/use/evaluate/blog/">ブログでの第三者評価</a></li>
                <li><a href="/use/evaluate/satisfaction/">ハッピー顧客満足度指数</a></li>
                <li><a href="/use/evaluate/value/">ケアメンテとクリーニングの評価</a></li>
                <li class="PCpart">&nbsp;</li>
              </ul>
            </div>
          </div>
        </div>
      </div>
    </li>
    <li class="menu__first-level">
			<a>ケアメンテのサービス・技術を知りたい。<br><span>ケアメンテのサービスやケアメンテを支える技術を詳しくご案内いたします。</span></a>
			<div class="menu__second-level">
					<div class="container">
						<div class="menu__second-column">
							<h3 class="headline">サービス概要</h3>
							<div class="menu__second-body">
								<ul>
									<li><a href="/carementeh/overview/style/">ケアメンテの仕事スタイルを知りたい</a></li>
									<li><a href="/carementeh/overview/etymology/">ケアメンテの語源は？</a></li>
									<li><a href="/carementeh/overview/flow/">ケアメンテの仕事の流れを見たい</a></li>
									<li><a href="/carementeh/overview/karte/">ハッピー電子カルテシステムとは？</a></li>
									<li><a href="/carementeh/overview/counseling/">カウンセリングとは？</a></li>
									<li><a href="/carementeh/overview/difference/">クリーニングと「ケアメンテ」は<br>どこが違うの？</a></li>
								</ul>
							</div>
						</div>
						<div class="menu__second-column">
							<h3 class="headline">サービス一覧</h3>
							<div class="menu__second-body">
								<ul>
									<li><a href="/carementeh/service/aquadry/">基本洗浄「水油系アクアドライ&reg;」とは？</a></li>
									<li><a href="/carementeh/service/ripron/">再生技術「リプロン&reg;」とは？</a></li>
									<li><a href="/carementeh/service/valueon/">加工技術「バリューON&reg;」とは？</a></li>
									<li><a href="/carementeh/service/grain/">レザー修復「レザーGRAIN再現加工」とは？</a></li>
									<li><a href="/carementeh/service/kimono/">きもの・仕立てたままで水洗い<br>「きもの無重力」とは？</a></li>
									<li><a href="/carementeh/service/reform/">お直し／リフォームについて知りたい</a></li>
									<li><a href="/carementeh/service/wardrobe/">保管お預かり<br>「ハッピーワードローブ&reg;」とは？</a></li>
								</ul>
							</div>
						</div>
						<div class="menu__second-column">
							<h3 class="headline">ケアメンテを支える技術</h3>
							<div class="menu__second-body">
								<ul>
									<li><a href="/technology/innovation/weightlessness/">ハッピー独自の技術<br>「無重力バランス洗浄技法」とは？</a></li>
									<li><a href="/technology/innovation/lecirian/">サイジング技法「レシリアン」とは？</a></li>
									<li><a href="/technology/innovation/press/">仕上げ技術「シルエットプレス&reg;」とは？</a></li>
								</ul>
							</div>
						</div>

						<div class="menu__second-column">
							<h3 class="headline">技術の検証データ</h3>
							<div class="menu__second-body">
								<ul>
									<li><a href="/technology/data/weightlessness/ma_test/">「無重力バランス洗浄技法(特許)」検証データ</a></li>
									<li><a href="/technology/data/tradition/yuzen/">京の伝統技法とケアメンテ</a></li>
									<li><a href="/technology/data/comparison/">汗汚れの洗浄比較実験</a></li>
									<li><a href="/technology/data/brand/">ブランド各社からの洗浄依頼品</a></li>
									<li><a href="/technology/data/monograph/">ケアメンテ水系洗浄の<br>学会誌掲載論文一覧</a></li>
								</ul>
							</div>
						</div>
					</div>
				</div>
		</li>
    <li class="menu__first-level">
			<a>ケアメンテの事例やレビューを知りたい。<br><span>2000点を超えるBefore&Afterの事例集やお客様のレビューをご覧頂けます。</span></a>
			<div class="menu__second-level">
					<div class="container">
						<div class="menu__second-column">
							<h3 class="headline">Before&amp;After /ケアメンテ事例集</h3>
							<div class="menu__second-body">
								<ul>
									<li><a href="/technology/before_after/list/">Before &amp; After集</a></li>
									<li><a href="/technology/before_after/suit/">上質スーツ</a></li>
									<li><a href="/technology/before_after/down/">最高級ダウン</a></li>
									<li><a href="/technology/before_after/shirt/">上質シャツ</a></li>
									<li><a href="/technology/before_after/bag/">バッグ</a></li>
									<li><a href="/technology/before_after/leather/">皮革・毛皮</a></li>
								</ul>
							</div>
						</div>
						<div class="menu__second-column">
							<h3 class="headline pc">&nbsp;</h3>
							<div class="menu__second-body">
								<ul>
									<li><a href="/technology/before_after/wedding/">ウェディングドレス</a></li>
									<li><a href="/technology/before_after/macintosh/">マッキントッシュ</a></li>
									<li><a href="/technology/before_after/lifecare/">インテリア・ファニチャー・羽毛布団</a></li>
									<li><a href="/technology/before_after/tenpyou/">天平の古代染めを洗う</a></li>
									<li><a href="/technology/before_after/kimono-2/">百年昔の「きもの」を洗う</a></li>
									<li class="PCpart">&nbsp;</li>
								</ul>
							</div>
						</div>
						<div class="menu__second-column">
							<h3 class="headline"><a href="/carementeh_search/"><img src="/wp/wp-content/themes/HAPPY_Dark/img/header01_w.png" alt="">Before&amp;After 検索 / 概算お見積り事例集「さがす」</a></h3>
							<h3 class="headline"><a href="/review/"><img src="/wp/wp-content/themes/HAPPY_Dark/img/header02_w.png" alt="">お客さまレビュー「きづく」</a></h3>
							<h3 class="headline"><a href="/mypage/sns.html"><img src="/wp/wp-content/themes/HAPPY_Dark/img/header03_w.png" alt="">ハッピー SNS「つなぐ」</a></h3>
<a href="https://www.kyoto-happy.co.jp/">高級クリーニングの先をゆくハッピーケアメンテ&reg;</a>
						</div>
					</div>
				</div>
		</li>
    <li class="menu__first-level">
			<a>特集・読み物を見たい。<br><span>おしゃれの雑学、こだわりのディテールやWEBマガジン幸（Sachi）他をお楽しみ頂けます。</span></a>
			<div class="menu__second-level">
					<div class="container">
						<div class="menu__second-column">
							<h3 class="headline"><a href="/knowledge/">おしゃれの雑学</a></h3>
						</div>
						<div class="menu__second-column">
							<h3 class="headline"><a href="/movie/">プロモーションビデオ</a></h3>
						</div>
						<div class="menu__second-column">
							<h3 class="headline"><a href="/detail/">こだわりのディテール</a></h3>
						</div>
						<div class="menu__second-column">
							<h3 class="headline"><a href="https://www.kyoto-happy.co.jp:8443/pdf/Manga_01.pdf?ver1.0" target="_blank">マンガで分かる「ケアメンテサービス」</a></h3>
						</div>
						<div class="menu__second-column">
							<h3 class="headline"><a href="/sachi/">WEB マガジン 幸(sachi)</a></h3>
						</div>
					</div>
				</div>
		</li>
    <li class="menu__first-level">
			<a>会社情報・リクルート情報を知りたい。<br><span>当社の会社概要やリクルート情報、環境への取り組みなどをご案内いたします。</span></a>
			<div class="menu__second-level">
					<div class="container">
						<div class="menu__second-column">
							<h3 class="headline">会社概要</h3>
							<div class="menu__second-body">
								<ul>
									<li><a href="/corporate/company/profile/">企業情報</a></li>
									<li><a href="/corporate/company/winning/">認定・受賞一覧</a></li>
									<li><a href="/corporate/company/ip/">知的財産（特許・商標）</a></li>
									<li><a href="/pdf/fukusyoku.pdf" target="_blank">服飾関連の皆様へ</a></li>
									<li><a href="/pdf/kanren_brand.pdf" target="_blank">アパレル業の皆様へ</a></li>
									<li><a href="/pdf/kanren_ryutu.pdf" target="_blank">流通業の皆様へ</a></li>
									<li><a href="/pdf/kanren_kaden.pdf" target="_blank">洗濯機メーカーの皆様へ</a></li>
									<li><a href="/privacy/">特定商取引法に基づく表記</a></li>
								</ul>
							</div>
						</div>
						<div class="menu__second-column">
							<h3 class="headline">メディア情報</h3>
							<div class="menu__second-body">
								<ul>
									<li><a href="/corporate/media/media_list/">メディア報道特集</a></li>
									<li><a href="/corporate/media/past/">過去の報道記録</a></li>
									<li><a href="/corporate/media/lecture/">講演活動の記録</a></li>
									<li><a href="/corporate/media/literary/">著作物一覧</a></li>
								</ul>
							</div>
							<h3 class="headline">リクルート</h3>
							<div class="menu__second-body">
								<ul>
									<li><a href="/corporate/recruit/cultivation/">人財育成について</a></li>
									<li><a href="/corporate/recruit/staff/">ケアメンテスタッフの募集</a></li>
									<li><a href="/corporate/recruit/executive/">経営幹部候補の募集</a></li>
								</ul>
							</div>
						</div>
						<div class="menu__second-column">
							<h3 class="headline">環境への取組み</h3>
							<div class="menu__second-body">
								<ul>
									<li><a href="/corporate/csr/sdgsdx/">SDGs・DX・GX・ESGの「一本の道」を歩み続ける</a></li>
									<li><a href="/corporate/csr/reuse/">自然循環型産業の創出</a></li>
									<li><a href="/corporate/csr/weightlessness/">無重力バランス洗浄による環境保護</a></li>
									<li><a href="/corporate/csr/world2007/">環境と洗浄の世界大会 2007 秋</a></li>
									<li><a href="/corporate/csr/unicef/">ハッピーワールド助け愛プロジェクト</a></li>
								</ul>
							</div>
						</div>
						<div class="menu__second-column">
							<h3 class="headline">ヨーロッパ洗浄技術交流紀行</h3>
							<div class="menu__second-body">
								<ul>
									<li><a href="/corporate/europe/2013_summer/">ヨーロッパ交流紀行 2013 初夏</a></li>
									<li><a href="/corporate/europe/2012_autumn/">ヨーロッパ交流紀行 2012 初秋</a></li>
									<li><a href="/corporate/europe/2006_summer/">ヨーロッパ交流紀行 2006 夏</a></li>
									<li><a href="/corporate/europe/2006_spring/">ヨーロッパ交流紀行 2006 春</a></li>
									<li><a href="/corporate/europe/2005_autumn/">ヨーロッパ交流紀行 2005 秋</a></li>
								</ul>
							</div>
						</div>
					</div>
				</div>
		</li>
  </ul>
</div>
<?php endif; ?>
<!--　/.guideNav -->
</div>
<!--　/.bg -->

<div class="footer_nav">
	<div class="container">
		<ul id="footer_nav_pc">
			<li class="menu__new-level">
				<a href="https://www.kyoto-happy.co.jp/order/form.html">ご注文・お申込み<img class="new-lavel-img" src="https://www.kyoto-happy.co.jp/wp/wp-content/themes/HAPPY_Dark/img/footer00.png" alt="ご注文・お申込み"></a>
			</li>
			<li class="menu__first-level">
				<a><img src="<?php echo $stylesheet_directory_uri; ?>/img/footer01.png" alt="ご利用方法・価格表"><span>ご利用方法 価格表</span></a>
				<div class="menu__second-level">
					<div class="container">
						<div class="menu__second-column">
							<h3 class="headline act">ご利用方法・価格表</h3>
							<div class="menu__second-body menu__two_column">
								<ul>
									<li<?php if(get_the_ID()==88)echo' class=act';?>><a href="/use/">ご利用方法</a></li>
									<li<?php if(get_the_ID()==90)echo' class=act';?>><a href="/use/price/list/">価格表</a></li>
									<li<?php if(get_the_ID()==354)echo' class=act';?>><a href="/use/price/catalog/">カタログ請求／PDF閲覧</a></li>
									<li<?php if(get_the_ID()==83)echo' class=act';?>><a href="/use/howtoorder/point/">ハッピーポイントについて</a></li>
								</ul>
								<ul>
									<li><a href="/kiyaku/">利用規約</a></li>
									<li<?php if(get_the_ID()==82)echo' class=act';?>><a href="/use/howtoorder/reparation/">事故賠償制度</a></li>
									<li<?php if(get_the_ID()==360)echo' class=act';?>><a href="/use/howtoorder/similarity/">類似サービスにご注意ください</a></li>
									<li<?php if(get_the_ID()==1631)echo' class=act';?>><a href="/faq/">よくあるご質問</a></li>
								</ul>
							</div>
						</div>
						<div class="menu__second-column">
							<h3 class="headline">提携ブランド/全国取扱い店舗一覧</h3>
							<div class="menu__second-body">
								<ul>
									<li<?php if(get_the_ID()==292)echo' class=act';?>><a href="/shop_search/">現在地から取扱店を検索</a></li>
									<li<?php if(get_the_ID()==2192)echo' class=act';?>><a href="/shop/">ショップ情報</a></li>
									<li class="PCpart">&nbsp;</li>
									<li class="PCpart">&nbsp;</li>
								</ul>
							</div>
						</div>
						<div class="menu__second-column">
							<h3 class="headline">ケアメンテの評価</h3>
							<div class="menu__second-body">
								<ul>
									<li<?php if(get_the_ID()==355)echo' class=act';?>><a href="/use/evaluate/blog/">ブログでの第三者評価</a></li>
									<li<?php if(get_the_ID()==459)echo' class=act';?>><a href="/use/evaluate/satisfaction/">ハッピー顧客満足度指数</a></li>
									<li<?php if(get_the_ID()==356)echo' class=act';?>><a href="/use/evaluate/value/">ケアメンテとクリーニングの評価</a></li>
									<li class="PCpart">&nbsp;</li>
								</ul>
							</div>
						</div>
					</div>
				</div>
			</li>
			<li class="menu__first-level">
				<a><img src="<?php echo $stylesheet_directory_uri; ?>/img/footer02.png" alt="サービス・技術"><span>サービス・技術</span></a>
				<div class="menu__second-level">
					<div class="container">
						<div class="menu__second-column">
							<h3 class="headline">サービス概要</h3>
							<div class="menu__second-body">
								<ul>
									<li<?php if(get_the_ID()==6)echo' class=act';?>><a href="/carementeh/overview/style/">ケアメンテ仕事スタイル</a></li>
									<li<?php if(get_the_ID()==7)echo' class=act';?>><a href="/carementeh/overview/etymology/">ケアメンテの語源</a></li>
									<li<?php if(get_the_ID()==8)echo' class=act';?>><a href="/carementeh/overview/flow/">ケアメンテの仕事の流れ</a></li>
									<li<?php if(get_the_ID()==12)echo' class=act';?>><a href="/carementeh/overview/karte/">ハッピー電子カルテシステム</a></li>
									<li<?php if(get_the_ID()==13)echo' class=act';?>><a href="/carementeh/overview/counseling/">カウンセリング</a></li>
									<li<?php if(get_the_ID()==361)echo' class=act';?>><a href="/carementeh/overview/difference/">クリーニングと「ケアメンテ」は<br>どこが違うの？</a></li>
								</ul>
							</div>
						</div>
						<div class="menu__second-column">
							<h3 class="headline">サービス一覧</h3>
							<div class="menu__second-body">
								<ul>
									<li<?php if(get_the_ID()==14)echo' class=act';?>><a href="/carementeh/service/aquadry/">基本洗浄「水油系アクアドライ&reg;」</a></li>
									<li<?php if(get_the_ID()==341)echo' class=act';?>><a href="/carementeh/service/ripron/">再生技術「リプロン&reg;」</a></li>
									<li<?php if(get_the_ID()==15)echo' class=act';?>><a href="/carementeh/service/valueon/">加工技術「バリューON&reg;」</a></li>
									<li<?php if(get_the_ID()==342)echo' class=act';?>><a href="/carementeh/service/grain/">レザー修復「レザーGRAIN再現加工」</a></li>
									<li<?php if(get_the_ID()==22)echo' class=act';?>><a href="/carementeh/service/kimono/">きもの・仕立てたままで水洗い<br>「きもの無重力」</a></li>
									<li<?php if(get_the_ID()==366)echo' class=act';?>><a href="/carementeh/service/reform/">お直し／リフォーム</a></li>
									<li<?php if(get_the_ID()==344)echo' class=act';?>><a href="/carementeh/service/wardrobe/">保管お預かり<br>「ハッピーワードローブ&reg;」</a></li>
								</ul>
							</div>
						</div>
						<div class="menu__second-column">
							<h3 class="headline">ケアメンテを支える技術</h3>
							<div class="menu__second-body">
								<ul>
									<li<?php if(get_the_ID()==362)echo' class=act';?>><a href="/technology/innovation/weightlessness/">ハッピー独自の技術<br>「無重力バランス洗浄技法」</a></li>
									<li<?php if(get_the_ID()==363)echo' class=act';?>><a href="/technology/innovation/lecirian/">サイジング技法「レシリアン」</a></li>
									<li<?php if(get_the_ID()==364)echo' class=act';?>><a href="/technology/innovation/press/">仕上げ技術「シルエットプレス&reg;」</a></li>
								</ul>
							</div>
						</div>

						<div class="menu__second-column">
							<h3 class="headline">技術の検証データ</h3>
							<div class="menu__second-body">
								<ul>
									<li<?php if(get_the_ID()==377 || get_the_ID()==378 || get_the_ID()==380 || get_the_ID()==386)echo' class=act';?>><a href="/technology/data/weightlessness/ma_test/">「無重力バランス洗浄技法(特許)」<br>検証データ</a></li>
									<li<?php if(get_the_ID()==383 || get_the_ID()==384)echo' class=act';?>><a href="/technology/data/tradition/yuzen/">京の伝統技法とケアメンテ</a></li>
									<li<?php if(get_the_ID()==385)echo' class=act';?>><a href="/technology/data/comparison/">汗汚れの洗浄比較実験</a></li>
									<li<?php if(get_the_ID()==382)echo' class=act';?>><a href="/technology/data/brand/">ブランド各社からの洗浄依頼品</a></li>
									<li<?php if(get_the_ID()==381)echo' class=act';?>><a href="/technology/data/monograph/">ケアメンテ水系洗浄の<br>学会誌掲載論文一覧</a></li>
								</ul>
							</div>
						</div>
					</div>
				</div>
			</li>
			<li class="menu__first-level">
				<a><img src="<?php echo $stylesheet_directory_uri; ?>/img/footer03.png" alt="事例・レビュー"><span>事例・レビュー</span></a>
				<div class="menu__second-level">
					<div class="container">
						<div class="menu__second-column">
							<h3 class="headline">Before&amp;After /ケアメンテ事例集</h3>
							<div class="menu__second-body">
								<ul>
									<li<?php if(get_the_ID()==367)echo' class=act';?>><a href="/technology/before_after/list/">Before &amp; After集</a></li>
									<li<?php if(get_the_ID()==368)echo' class=act';?>><a href="/technology/before_after/suit/">上質スーツ</a></li>
									<li<?php if(get_the_ID()==369)echo' class=act';?>><a href="/technology/before_after/down/">最高級ダウン</a></li>
									<li<?php if(get_the_ID()==370)echo' class=act';?>><a href="/technology/before_after/shirt/">上質シャツ</a></li>
									<li<?php if(get_the_ID()==372)echo' class=act';?>><a href="/technology/before_after/bag/">バッグ</a></li>
									<li<?php if(get_the_ID()==371)echo' class=act';?>><a href="/technology/before_after/leather/">皮革・毛皮</a></li>
								</ul>
							</div>
						</div>
						<div class="menu__second-column">
							<h3 class="headline pc">&nbsp;</h3>
							<div class="menu__second-body">
								<ul>
									<li<?php if(get_the_ID()==373)echo' class=act';?>><a href="/technology/before_after/wedding/">ウェディングドレス</a></li>
									<li<?php if(get_the_ID()==374)echo' class=act';?>><a href="/technology/before_after/macintosh/">マッキントッシュ</a></li>
									<li<?php if(get_the_ID()==375)echo' class=act';?>><a href="/technology/before_after/lifecare/">インテリア・ファニチャー・羽毛布団</a></li>
									<li<?php if(get_the_ID()==376)echo' class=act';?>><a href="/technology/before_after/tenpyou/">天平の古代染めを洗う</a></li>
									<li<?php if(get_the_ID()==386)echo' class=act';?>><a href="/technology/before_after/kimono-2/">百年昔の「きもの」を洗う</a></li>
									<li class="PCpart">&nbsp;</li>
								</ul>
							</div>
						</div>
						<div class="menu__second-column">
							<h3 class="headline"><a href="/carementeh_search/"><img src="<?php echo $stylesheet_directory_uri; ?>/img/header01_w.png" alt="">Before&amp;After<span class="pc"> 検索</span> / 概算お見積り事例集「さがす」</a></h3>
							<h3 class="headline"><a href="/review/"><img src="<?php echo $stylesheet_directory_uri; ?>/img/header02_w.png" alt="">お客さまレビュー「きづく」</a></h3>
							<h3 class="headline"><a href="/mypage/sns.html"><img src="<?php echo $stylesheet_directory_uri; ?>/img/header03_w.png" alt="">ハッピー SNS「つなぐ」</a></h3>
<a href="https://www.kyoto-happy.co.jp/">高級クリーニングの先をゆくハッピーケアメンテ&reg;</a>
						</div>
					</div>
				</div>
			</li>
			<li class="menu__first-level">
				<a><img src="<?php echo $stylesheet_directory_uri; ?>/img/footer04.png" alt="特集・読みもの"><span>特集・読みもの</span></a>
				<div class="menu__second-level">
					<div class="container">
						<div class="menu__second-column">
							<h3 class="headline<?php if($GLOBALS['bodyId']=='knowledge')echo' act';?>"><a href="/knowledge/">おしゃれの雑学</a></h3>
						</div>
						<div class="menu__second-column">
							<h3 class="headline<?php if($GLOBALS['bodyId']=='movie')echo' act';?>"><a href="/movie/">プロモーションビデオ</a></h3>
						</div>
						<div class="menu__second-column">
							<h3 class="headline<?php if($GLOBALS['bodyId']=='detail')echo' act';?>"><a href="/detail/">こだわりのディテール</a></h3>
						</div>
						<div class="menu__second-column">
							<h3 class="headline"><a href="https://www.kyoto-happy.co.jp:8443/pdf/Manga_01.pdf?ver1.0" target="_blank">マンガで分かる「ケアメンテサービス」</a></h3>
						</div>
						<div class="menu__second-column">
							<h3 class="headline<?php if($GLOBALS['bodyId']=='review_top' || $GLOBALS['bodyId']=='pTop')echo' act';?>"><a href="/sachi/">WEB マガジン 幸(sachi)</a></h3>
						</div>
					</div>
				</div>
			</li>
			<li class="menu__first-level">
				<a><img src="<?php echo $stylesheet_directory_uri; ?>/img/footer05.png" alt="会社情報・地球環境への取り組み"><span>会社情報・地球環境への取り組み</span></a>
				<div class="menu__second-level">
					<div class="container">
						<div class="menu__second-column">
							<h3 class="headline">会社概要</h3>
							<div class="menu__second-body">
								<ul>
									<li<?php if(get_the_ID()==323)echo' class=act';?>><a href="/corporate/company/profile/">企業情報</a></li>
									<li<?php if(get_the_ID()==392)echo' class=act';?>><a href="/corporate/company/winning/">認定・受賞一覧</a></li>
									<li<?php if(get_the_ID()==393)echo' class=act';?>><a href="/corporate/company/ip/">知的財産（特許・商標）</a></li>
									<li><a href="/pdf/fukusyoku.pdf" target="_blank">服飾関連の皆様へ</a></li>
									<li><a href="/pdf/kanren_brand.pdf" target="_blank">アパレル業の皆様へ</a></li>
									<li><a href="/pdf/kanren_ryutu.pdf" target="_blank">流通業の皆様へ</a></li>
									<li><a href="/pdf/kanren_kaden.pdf" target="_blank">洗濯機メーカーの皆様へ</a></li>
									<li<?php if(get_the_ID()==446)echo' class=act';?>><a href="/privacy/">特定商取引法に基づく表記</a></li>
								</ul>
							</div>
						</div>
						<div class="menu__second-column">
							<h3 class="headline">メディア情報</h3>
							<div class="menu__second-body">
								<ul>
									<li<?php if(get_the_ID()==324)echo' class=act';?>><a href="/corporate/media/media_list/">メディア報道特集</a></li>
									<li<?php if(get_the_ID()==325)echo' class=act';?>><a href="/corporate/media/past/">過去の報道記録</a></li>
									<li<?php if(get_the_ID()==997)echo' class=act';?>><a href="/corporate/media/lecture/">講演活動の記録</a></li>
									<li<?php if(get_the_ID()==327)echo' class=act';?>><a href="/corporate/media/literary/">著作物一覧</a></li>
								</ul>
							</div>
							<h3 class="headline">リクルート</h3>
							<div class="menu__second-body">
								<ul>
									<li<?php if(get_the_ID()==328)echo' class=act';?>><a href="/corporate/recruit/cultivation/">人財育成について</a></li>
									<li<?php if(get_the_ID()==329)echo' class=act';?>><a href="/corporate/recruit/staff/">ケアメンテスタッフの募集</a></li>
									<li<?php if(get_the_ID()==330)echo' class=act';?>><a href="/corporate/recruit/executive/">経営幹部候補の募集</a></li>
								</ul>
							</div>
						</div>
						<div class="menu__second-column">
							<h3 class="headline">環境への取組み</h3>
							<div class="menu__second-body">
								<ul>
									<li<?php if(get_the_ID()==2609)echo' class=act';?>><a href="/corporate/csr/sdgsdx/">SDGs・DX・GX・ESGの「一本の道」を歩み続ける</a></li>
									<li<?php if(get_the_ID()==2052)echo' class=act';?>><a href="/corporate/csr/reuse/">自然循環型産業の創出</a></li>
									<li<?php if(get_the_ID()==331)echo' class=act';?>><a href="/corporate/csr/weightlessness/">無重力バランス洗浄による環境保護</a></li>
									<li<?php if(get_the_ID()==332)echo' class=act';?><?php if(get_the_ID()==373)echo' class=act';?>><a href="/corporate/csr/world2007/">環境と洗浄の世界大会 2007 秋</a></li>
									<li<?php if(get_the_ID()==334)echo' class=act';?>><a href="/corporate/csr/unicef/">ハッピーワールド助け愛プロジェクト</a></li>
								</ul>
							</div>
						</div>
						<div class="menu__second-column">
							<h3 class="headline">ヨーロッパ洗浄技術交流紀行</h3>
							<div class="menu__second-body">
								<ul>
									<li<?php if(get_the_ID()==339)echo' class=act';?>><a href="/corporate/europe/2013_summer/">ヨーロッパ交流紀行 2013 初夏</a></li>
									<li<?php if(get_the_ID()==338)echo' class=act';?>><a href="/corporate/europe/2012_autumn/">ヨーロッパ交流紀行 2012 初秋</a></li>
									<li<?php if(get_the_ID()==337)echo' class=act';?>><a href="/corporate/europe/2006_summer/">ヨーロッパ交流紀行 2006 夏</a></li>
									<li<?php if(get_the_ID()==336)echo' class=act';?>><a href="/corporate/europe/2006_spring/">ヨーロッパ交流紀行 2006 春</a></li>
									<li<?php if(get_the_ID()==335)echo' class=act';?>><a href="/corporate/europe/2005_autumn/">ヨーロッパ交流紀行 2005 秋</a></li>
								</ul>
							</div>
						</div>
					</div>
				</div>
			</li>
		</ul>
	</div>
</div>
<!--　/.footer_nav -->

<div class="footer_nav_sp">
	<div class="wrap">
		<div class="container">
			<nav id="menu_sp_trigger">
				<div>
					<span></span>
					<span></span>
					<span></span>
				</div>
				<p>MENU</p>
			</nav>
			<div class="gFooter">
				<ul>
					<?php if($GLOBALS['bodyId']=="top"):?>
					<li><a href="/"><div class="gFooterImg"><img src="<?php echo $stylesheet_directory_uri; ?>/img/icon_s_home_a.png" alt="HOME"></div><span class="act">ホーム</span></a></li>
					<?php else : ?>
					<li><a href="/"><div class="gFooterImg"><img src="<?php echo $stylesheet_directory_uri; ?>/img/icon_s_home.png" alt="HOME"></div><span>ホーム</span></a></li>
					<?php endif; ?>
					<li><a href="/carementeh_search/"><div class="gFooterImg"><img src="<?php echo $stylesheet_directory_uri; ?>/img/icon_s_sarch.png" alt="さがす"></div><span>さがす</span></a></li>
					<li><a href="/mypage/sns.html"><div class="gFooterImg"><img src="<?php echo $stylesheet_directory_uri; ?>/img/icon_s_global.png" alt="つなぐ"></div><span>つなぐ</span></a></li>
					<li><a href="/mypage/"><div class="gFooterImg"><img src="<?php echo $stylesheet_directory_uri; ?>/img/icon_s_user.png" alt="マイページ"></div><span>マイページ</span></a></li>
					<li><a href="tel:0120-88-6868"><div class="gFooterImg"><img src="<?php echo $stylesheet_directory_uri; ?>/img/icon_s_tel.png" alt="tel"></div><span>お電話</span></a></li>
					<li><a href="/order/"><div class="gFooterImg"><img src="<?php echo $stylesheet_directory_uri; ?>/img/icon_s_send.png" alt="ご注文"></div><span>ご注文</span></a></li>
				</ul>
			</div>
		</div>
	</div>
	<ul class="footer_Hidden">
		<li>
			<a><img src="<?php echo $stylesheet_directory_uri; ?>/img/footer01.png" alt="ご利用方法 価格表"><span>ご利用方法 価格表</span></a>
		</li>
		<li>
			<a><img src="<?php echo $stylesheet_directory_uri; ?>/img/footer02.png" alt="サービス・技術"><span>サービス・技術</span></a>
		</li>
		<li>
			<a><img src="<?php echo $stylesheet_directory_uri; ?>/img/footer03.png" alt="事例・レビュー"><span>事例・レビュー</span></a>
		</li>
		<li>
			<a><img src="<?php echo $stylesheet_directory_uri; ?>/img/footer04.png" alt="特集・読みもの"><span>特集・読みもの</span></a>
		</li>
		<li>
			<a><img src="<?php echo $stylesheet_directory_uri; ?>/img/footer05.png" alt="会社情報・地球環境への取り組み"><span>会社情報・地球環境への取り組み</span></a>
		</li>
	</ul>
</div>
<!--　/.footer_nav_sp -->
<?php if ( is_front_page() ) : ?>
</div>
<!--　/#PAGEWIDE　-->
<?php endif; ?>
<?php wp_footer(); ?>
</body>
</html>
