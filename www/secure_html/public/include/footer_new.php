
<div class="footer_pagetop pagetop" <?php if($this->get("page_group") == "community") {?>style="line-height:1.0"<?php }?>>
	<div class="container">
		<ul>
			<li><a href="#top"><i class="fa fa-angle-up" aria-hidden="true"></i><span>Top</span></a></li>
		</ul>
	</div>
</div>
<!--　/.footer_sns -->

<?php if($this->get("page_group") != "search" and
		 $this->get("page_group") != "review" and
	     $this->get("page_group") != "community") {?>
<div class="guideNav SPpart">
  <h2>サチコのハッピーナビ</h2>
  <div class="guideNavtxt">
    <div class="guideNavtxt_img">
      <img src="/wp/wp-content/themes/HAPPY_Dark/img/counseling.png" alt="">
    </div>
    <div class="guideNavtxt_box">
      <p>私サチコがご案内します。<br>何をご覧になりたいですか？</p>
    </div>
  </div>
  <ul class="guideNav_btm">
    <li class="menu__first-level">
      <a>ケアメンテの利用方法を知りたい。<br><span>ケアメンテのご利用方法や価格表、お近くの店舗検索や提携ブランド、ケアメンテの評価をご覧頂けます。</span></a>
      <div class="menu__second-level" style="display: none;">
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
								<li><a href="/order/kiyaku.html">利用規約について知りたい</a></li>
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
			<div class="menu__second-level" style="display: none;">
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
									<li><a href="/carementeh/service/aquadry/">基本洗浄「水油系アクアドライ®」とは？</a></li>
									<li><a href="/carementeh/service/ripron/">再生技術「リプロン®」とは？</a></li>
									<li><a href="/carementeh/service/valueon/">加工技術「バリューON®」とは？</a></li>
									<li><a href="/carementeh/service/grain/">レザー修復「レザーGRAIN再現加工」とは？</a></li>
									<li><a href="/carementeh/service/kimono/">きもの・仕立てたままで水洗い<br>「きもの無重力」とは？</a></li>
									<li><a href="/carementeh/service/reform/">お直し／リフォームについて知りたい</a></li>
									<li><a href="/carementeh/service/wardrobe/">保管お預かり<br>「ハッピーワードローブ®」とは？</a></li>
								</ul>
							</div>
						</div>
						<div class="menu__second-column">
							<h3 class="headline">ケアメンテを支える技術</h3>
							<div class="menu__second-body">
								<ul>
									<li><a href="/technology/innovation/weightlessness/">ハッピー独自の技術<br>「無重力バランス洗浄技法」とは？</a></li>
									<li><a href="/technology/innovation/lecirian/">サイジング技法「レシリアン」とは？</a></li>
									<li><a href="/technology/innovation/press/">仕上げ技術「シルエットプレス®」とは？</a></li>
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
			<a>ケアメンテの事例やレビューを知りたい。<br><span>2000点を超えるBefore&amp;Afterの事例集やお客様のレビューをご覧頂けます。</span></a>
			<div class="menu__second-level" style="display: none;">
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
							<h3 class="headline"><a href="/carementeh_search/"><img src="/wp/wp-content/themes/HAPPY_Dark/img/header01_w.png" alt="">ケアメンテ®検索エンジン「さがす」</a></h3>
							<h3 class="headline"><a href="/review/"><img src="/wp/wp-content/themes/HAPPY_Dark/img/header02_w.png" alt="">お客さまレビュー「きづく」</a></h3>
							<h3 class="headline"><a href="/mypage/sns.html"><img src="/wp/wp-content/themes/HAPPY_Dark/img/header03_w.png" alt="">ハッピー SNS「つなぐ」</a></h3>
						</div>
					</div>
				</div>
		</li>
    <li class="menu__first-level">
			<a>特集・読み物を見たい。<br><span>おしゃれの雑学、こだわりのディテールやWEBマガジン幸（Sachi）他をお楽しみ頂けます。</span></a>
			<div class="menu__second-level" style="display: none;">
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
			<div class="menu__second-level" style="display: none;">
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
									<li><a href="/corporate/csr/reuse/">自然循環型産業の創出</a></li>
									<li><a href="/corporate/csr/weightlessness/">無重力バランス洗浄による環境保護</a></li>
									<li><a href="/corporate/csr/world2007/">環境と洗浄の世界大会 2007 秋</a></li>
									<li><a href="/corporate/csr/unicef/">ハッピーワールド助け合いプロジェクト</a></li>
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
<?php }?>
<!--　/.guideNav -->

<?php
$webroot = $_SERVER['DOCUMENT_ROOT'];
include($webroot."/include/footer_nav.php");
?>