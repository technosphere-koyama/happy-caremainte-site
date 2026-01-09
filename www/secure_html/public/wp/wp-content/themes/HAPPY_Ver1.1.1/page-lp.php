<?php
/*
Template Name: ランディングページ

*/
?>

<?php get_header(); ?>

	<div id="Contents">
       		<h1>ハッピーケアメンテは高級品クリーニングの駆け込み寺</h1>

		<div class="lp_top__kv">
			<img src="https://www.kyoto-happy.co.jp:8443/_assets/img/lp/img_kv.jpg" alt="ハッピーの誇るケアメンテ&reg;技術 ハッピー ケアメンテ&reg;は、クリーニングとは違います。お客様からお預かりした衣類を再生産し、まるで新品のような仕上がりでお届けします。" class="PCpart">
			<img src="https://www.kyoto-happy.co.jp:8443/_assets/img_sp/lp/img_kv.jpg" alt="ハッピーの誇るケアメンテ&reg;技術 ハッピー ケアメンテ&reg;は、クリーニングとは違います。お客様からお預かりした衣類を再生産し、まるで新品のような仕上がりでお届けします。" class="SPpart">
		</div>

	<div>

		<section class="lp_top__section">
			<div class="wrap">
				<h2><img src="https://www.kyoto-happy.co.jp:8443/_assets/img/lp/h2_01.png?190429" alt="クリーニングの駆け込み寺®ハッピーケアメンテとは？"></h2>
				<ul id="lp_slider">
					<?php if(have_rows('onayami',1536)): ?>
					<?php while(have_rows('onayami',1536)): the_row(); ?>
					<?php if(get_sub_field('onayami_self')): ?>
					<li><a href="<?php the_sub_field('onayami_url'); ?>" target="_blank"><div><?php the_sub_field('onayami_txt'); ?><span><i class="fa fa-angle-right" aria-hidden="true"></i>詳しく見る</span></div></a></li>
					<?php else : ?>
					<li><a href="<?php the_sub_field('onayami_url'); ?>"><div><?php the_sub_field('onayami_txt'); ?><span><i class="fa fa-angle-right" aria-hidden="true"></i>詳しく見る</span></div></a></li>
					<?php endif; ?>
					<?php endwhile; ?>
					<?php endif; ?>
				</ul>
				<div class="inner_button"><a href="/lp/">ケアメンテ&reg;技術を厳しくチェックする<img src="https://www.kyoto-happy.co.jp:8443/_assets/img/lp/btn_arrow.png"></a></div>
				<img src="https://www.kyoto-happy.co.jp:8443/_assets/img/lp/line_down.png" alt="クリーニングでこんな心配ありませんか?" class="lp_line PCpart">
			</div>
		</section>

		<section class="lp_2nd__section">
			<div class="wrap">
				<h2><img src="https://www.kyoto-happy.co.jp:8443/_assets/img/lp/h2_02.png" alt="ケアメンテ&reg;技術があなたの衣服の悩みを解決します。"></h2>
				<p>「クリーニングの駆け込み寺」と呼ばれる当社には、<br>
				クリーニングに出したために悲惨な状態になってしまった、<br class="SPpart">というお困りのお洋服が毎日のように届きます。<br>
				それは、ハッピーが衣服の洗浄・仕上げ技術を独自に開発し、<br>
				新品同様の状態を維持して長く着続けられるようにする技術を<br class="SPpart">有しているからに他なりません。</p>
				<div class="lp_2nd__right">
					<div class="lp_2nd__inner">
						<p class="inner_subtitle">カウンセリング／電子カルテシステム</p>
						<h3>「お客さまのお話に、<br>じっくりと耳を傾ける」</h3>
						<p class="inner_text">お預かりする一点ごとのお洋服に150科目3,000項目にわたって電子カルテを作成します。その電子カルテを基にしてお客さまに問診、つまりカウンセリングを行います。衣類の状態だけでなく、お客様とのコミュニケーションからわかる情報なども電子カルテに登録し、ご要望にあったメンテナンスを行います。</p>
						<div class="inner_button"><a href="/carementeh/overview/counseling/">詳細はこちら<img src="https://www.kyoto-happy.co.jp:8443/_assets/img/lp/btn_arrow.png"></a></div>
					</div>
					<div class="lp_2nd__image">
						<img src="https://www.kyoto-happy.co.jp:8443/_assets/img/lp/img_01.jpg" alt="「お客さまのお話に、じっくりと耳を傾ける」">
					</div>
                </div>
                <div class="lp_2nd__left">
					<div class="lp_2nd__inner">
						<p class="inner_subtitle">無重力バランス洗浄</p>
						<h3>洗浄の常識を覆した<br>独自の水系洗浄技術</h3>
						<p class="inner_text">ハッピーでは水洗いとドライクリーニングの致命的な欠陥を克服するために、物理的機械力を発生させることなく、手洗いよりも優しく水で洗うことのできる原理を発明。従来のクリーニングでは不可能な、衣類にやさしく、汚れが除去できるハッピー独自のシステムが、ご依頼品を傷めず洗浄できる秘密です。</p>
						<div class="inner_button"><a href="/technology/innovation/weightlessness/">詳細はこちら<img src="https://www.kyoto-happy.co.jp:8443/_assets/img/lp/btn_arrow.png"></a></div>
					</div>
					<div class="lp_2nd__image">
						<img src="https://www.kyoto-happy.co.jp:8443/_assets/img/lp/img_02.jpg" alt="無重力バランス洗浄">
					</div>
                </div>
                <div class="lp_2nd__right">
					<div class="lp_2nd__inner">
						<p class="inner_subtitle">美しいシルエットのままお届け</p>
						<h3>ケアメンテの技術品質を<br>安全にお届けします</h3>
						<p class="inner_text">ケアメンテした衣類は、シワがついたり型崩れを起こさないよう、適切なサイズのボックスに細心の注意をはらって梱包いたします。<br>ゆったりとしたパッケージで、美しいシルエットのままお客さまにお届けしたいという私どもの願いが込められています。</p>
						<div class="inner_button"><a href="/use/howtoorder/package/">詳細はこちら<img src="https://www.kyoto-happy.co.jp:8443/_assets/img/lp/btn_arrow.png"></a></div>
					</div>
					<div class="lp_2nd__image">
						<img src="https://www.kyoto-happy.co.jp:8443/_assets/img/lp/img_03.jpg" alt="美しいシルエットのままお届け">
					</div>
                </div>
			</div>
		</section>


		<section class="lp_3rd__section">
			<div class="wrap">
				<h2><img src="https://www.kyoto-happy.co.jp:8443/_assets/img/lp/h2_03.png" alt="ケアメンテ&reg;が解る Before &amp; After 実例集『さがす』を見る"></h2>
				<div class="inner_left">
					<img src="https://www.kyoto-happy.co.jp:8443/_assets/img/lp/img_capture.png" alt="ケアメンテ検索エンジン『さがす』">
				</div>
				<div class="inner_right">
					<p class="inner_text">豊富な経験値と、その実例集が物語る確かな技術。<br>
					ハッピーでは過去のケアメンテを行なった物件の中から、様々な事例をデータベース化。<br>
					あなたのお困りの衣服に似たアイテムを探して、「ケアメンテ」の洗い・仕上がり感をイメージしていただくことが可能です。</p>
					<div class="inner_button"><a href="/carementeh_search/">ケアメンテ検索エンジン『さがす』<img src="https://www.kyoto-happy.co.jp:8443/_assets/img/lp/btn_arrow.png"></a></div>
				</div>
			</div>
		</section>



		<section class="lp_bottom__section">
			<div class="wrap">
				<h2>業務提携先</h2>
				<div class="copy">様々なファッションブランドや<br class="SPpart">ショップ・企業がケアメンテ<sup>&reg;</sup>と提携。<br>全国の取扱い店舗の地図がご覧いただけます。</div>
				<ul>
					<li><a href="/shop/brand/tomorrowland/"><img src="https://www.kyoto-happy.co.jp:8443/_assets/img/lp/logo_02.jpg" alt="TOMORROWLAND"></a></li>
					<li><a href="/shop/brand/beams/"><img src="https://www.kyoto-happy.co.jp:8443/_assets/img/lp/logo_04.jpg" alt="BEAMS"></a></li>
					<li><a href="/shop/brand/united-arrows/"><img src="https://www.kyoto-happy.co.jp:8443/_assets/img/lp/logo_03.jpg" alt="UNITED ARROWS"></a></li>
					<li><a href="/shop/brand/aquascutum/"><img src="https://www.kyoto-happy.co.jp:8443/_assets/img/lp/logo_10.jpg" alt="Aquascutum"></a></li>
					<li><a href="/shop/brand/durban/"><img src="https://www.kyoto-happy.co.jp:8443/_assets/img/lp/logo_09.jpg" alt="DURBAN"></a></li>
					<li><a href="/shop/brand/sinjuku_takashimaya/"><img src="https://www.kyoto-happy.co.jp:8443/_assets/img/lp/logo_05.jpg" alt="Takashimaya SHINJUKU"></a></li>
					<li><a href="/shop/brand/seibu_ikebukuro/"><img src="https://www.kyoto-happy.co.jp:8443/_assets/img/lp/logo_06.jpg" alt="西武池袋本店 @office"></a></li>
					<li><a href="/shop/brand/abeno_harukas/"><img src="https://www.kyoto-happy.co.jp:8443/_assets/img/lp/logo_07.jpg" alt="近鉄あべのハルカス"></a></li>
					<li><a href="/shop/brand/yokohama_takashimaya/"><img src="https://www.kyoto-happy.co.jp:8443/_assets/img/lp/logo_08.jpg" alt="横浜タカシマヤ"></a></li>
				</ul>
			</div>
		</section>

		<section class="lp_hermes__section">
		　<a href="tel:0120-88-3040"><img src="https://www.kyoto-happy.co.jp:8443/_assets/img/lp/logo_01_1.png" alt="エルメスお客様ご愛用ダイヤル 0120-88-3040"></a>
		</section>

		<section class="link_3rd__section">
			<div class="wrap">
				<ul class="menu2">
					<li>
						<a href="/knowledge/">
							<img src="https://www.kyoto-happy.co.jp:8443/_assets/img/index/link_3rd-1.png" alt="おしゃれの雑学">
						</a>
					</li>
					<li>
						<a href="/movie/">
							<img src="https://www.kyoto-happy.co.jp:8443/_assets/img/index/link_3rd-2.png" alt="プロモーションビデオ">
						</a>
					</li>
					<li>
						<a href="/shop/">
							<img src="https://www.kyoto-happy.co.jp:8443/_assets/img/index/link_3rd-3.png" alt="おしゃれの雑学">
						</a>
					</li>
					<li>
						<a href="#inline-content2" class="popup cboxElement">
							<img src="https://www.kyoto-happy.co.jp:8443/_assets/img/index/link_3rd-4.png" alt="類似サービスにご注意">
						</a>
					</li>
					<li>
						<a href="/corporate/media/past/">
							<img src="https://www.kyoto-happy.co.jp:8443/_assets/img/index/link_3rd-5.png" alt="報道一覧">
						</a>
					</li>
				</ul>
			</div>
		</section>

		<section class="award__section">
			<ul class="wrap">
				<li><a href="/corporate/company/winning/"><img src="https://www.kyoto-happy.co.jp:8443/_assets/img/index/icn_award01.gif" alt="第一回「日本サービス大賞」 優秀賞（SPRING賞）受賞"></a></li>
				<li><a href="/corporate/company/winning/"><img src="https://www.kyoto-happy.co.jp:8443/_assets/img/index/icn_award02.gif" alt="中小企業IT経営力大賞 経済産業大臣賞"></a></li>
				<li><a href="/corporate/company/winning/"><img src="https://www.kyoto-happy.co.jp:8443/_assets/img/index/icn_award03.gif" alt="ハイ・サービス日本300選"></a></li>
				<li><a href="/corporate/company/winning/"><img src="https://www.kyoto-happy.co.jp:8443/_assets/img/index/icn_award04.gif" alt="おもてなし経営企業選 選出企業"></a></li>
				<li><a href="/corporate/company/winning/"><img src="https://www.kyoto-happy.co.jp:8443/_assets/img/index/icn_award05.gif" alt="おもてなし規格認証2016"></a></li>
			</ul>
		</section>

		<section class="link_bottom_txt">
			<ul class="wrap">
				<li><a href="/corporate/company/winning/">公的機関からの認定・受賞一覧<i class="fa fa-angle-right" aria-hidden="true"></i></a></li>
				<li><a href="/corporate/media/past/">報道の記録<i class="fa fa-angle-right" aria-hidden="true"></i></a></li>
				<li><a href="/corporate/media/lecture/">講演の記録<i class="fa fa-angle-right" aria-hidden="true"></i></a></li>
			</ul>
		</section>


		<!--POPUP Contents-->

        <div style="display:none;" class="news_headline-detail">
            <section id="inline-content2">
                <h3>類似・模倣サービスにご注意</h3>
                <p>本物を知る“あなた”にしか分からない、本物の技術・サービス体感品質。<br />
					インターネットで情報が溢れる社会 ―そんな今だからこそ騙されないで！</p>
					<p><a href="/carementeh/overview/difference/">「ケアメンテ」とクリーニングはどこが違うの？ </a></p>
					<p><a href="/use/howtoorder/similarity/">「ケアメンテ」はネット宅配クリーニングではありません</a></p>
					<p>ハッピーの登録商標「ケアメンテ」を使用して、ハッピーのサービスと混同を招いているクリーニング店が見受けられます。<br />
					また、当社サービスについて、クリーニング関係者によるものと思われる根拠の無い誹謗中傷かつ悪質な書込み、広告目的の比較評価サイト等には充分ご注意ください。</p>
					<p>ハッピーは、お客様とのコミュニケーションを大切にしています。</p>
					<p>「預けた私の服は今どうなっているの？」<br />
					「要望はちゃんと伝わっているの？」</p>
					<p>お預り時からお届けに至る全てのデータベースは「電子カルテシステム」等に記録されておりますので、すぐにお調べいたします。<br />
					<br />
					●お客さまダイヤル：0120-88-6868<br />
					●<a href="/contact/">お問い合わせフォーム</a><br />
					<br />
					※お預かり品の「電子カルテ」は<a href="/mypage/">『マイページ』</a>からもご確認いただけます</p>
            </section>
        </div>


  </div><!--/Contents-->

  		<script src="https://www.kyoto-happy.co.jp/_assets/js/skippr.min_170920.js"></script>
		<link rel="stylesheet" href="https://www.kyoto-happy.co.jp/_assets/css/jquery.bxslider_170920.css">
		<script src="https://www.kyoto-happy.co.jp/_assets/js/jquery.bxslider.min_170920.js"></script>
		<script type="text/javascript">
		$(function() {
			$('#lp_slider').bxSlider({
				slideWidth: 370,
				auto: true,
				infiniteLoop: true,
				slideMargin: 15,
				autoHover: true
			});
		});
		</script>

<?php get_footer(); ?>
