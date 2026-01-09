<?php get_header(); ?>

<?php if ( is_front_page() ) : ?>
	<div id="left_banner">
		<div id="left_banner_inner">
			<div id="left_banner_off"><img src="https://www.kyoto-happy.co.jp/wp/wp-content/themes/HAPPY_Dark/item/close.png"></div>
			<a href="https://www.kyoto-happy.co.jp/carementeh_search/form.html"><img src="https://www.kyoto-happy.co.jp/wp/wp-content/themes/HAPPY_Dark/item/care_maintenance-02.png" alt=""></a>
		</div>

		<div id="left_banner_inner2">
			<div id="left_banner_off2"><img src="https://www.kyoto-happy.co.jp/wp/wp-content/themes/HAPPY_Dark/item/close.png"></div>
			<a href="https://www.kyoto-happy.co.jp/wp/wp-content/uploads/2021/03/%E7%99%BA%E8%A6%8B%E3%83%BB%E6%84%9F%E5%8B%95%E3%83%BB%E4%BD%93%E6%84%9F%E5%93%81%E8%B3%AA%E3%80%8C%E3%81%84%E3%81%84%E6%9C%8D%E9%95%B7%E6%8C%81%E3%81%A1%E3%80%8D.pdf" target="_blank"><img src="https://www.kyoto-happy.co.jp/wp/wp-content/themes/HAPPY_Dark/item/care_manga.png" alt=""></a>
		</div>

		<div id="left_banner_inner3">
			<div id="left_banner_off3"><img src="https://www.kyoto-happy.co.jp/wp/wp-content/themes/HAPPY_Dark/item/close.png"></div>
			<a href="https://www.kyoto-happy.co.jp/2021/03/18/2478/"><img src="https://www.kyoto-happy.co.jp/wp/wp-content/themes/HAPPY_Dark/item/care_line.png" alt=""></a>
		</div>
	</div>
<?php endif; ?>

<section id="hero">
	<div class="youtube_wrap wrap">

		<!--div id="youtube"></div-->
	</div>
</section>

<!--　/#hero -->

<div class="sp_banner">
	<div class="btn">
		<a href="/corporate/media/media_list/">メディア報道特集</a>
	</div>
	<div class="btn">
		<a href="/corporate/company/winning/">認定・受賞一覧</a>
	</div>
</div>





<div class="arrow">
	<a href="#news"><img src="<?php echo get_stylesheet_directory_uri(); ?>/img/arrow.png" alt="" id="arrow"></a>
</div>
<div class="bg">
	<section id="news">
<h1><div class="new-top-on">
<small>高級クリーニングの先をゆくハッピーケアメンテ&reg;</p></small>
</div></h1>
		<div class="container">
			<div class="news">
				<div class="news_wrap">
					<h2>お知らせ</h2>
					<div class="scroll">

	<?php
		$args = array(
			'post_type' => 'post',
			'posts_per_page' => 1,
			'meta_query' => array(
				'relation' => 'OR',
				array(
					 'key' => 'news_headline',
					 'value' => true,
					 'compare' => 'NOT EXISTS'
				),
				array(
					'key' => 'news_headline',
					'value' => '1',
					'compare' => '!='
				),
			)
			);
			$my_posts = get_posts( $args );

			foreach ( $my_posts as $post ): ?>
			<p>
				<a href="<?php echo get_news_permalink(); ?>"><?php the_title(); ?></a>
			</p>
	<?php endforeach; ?>

	</div>
				</div>
			</div>
		</div>
	</section>
	<div class="dx-sdgs"><img src="<?php echo get_stylesheet_directory_uri(); ?>/img/top-dx.png" alt="DX認定" /><img src="<?php echo get_stylesheet_directory_uri(); ?>/img/top-sdgs.jpg" alt="SDGSへの取り組み" /></div>
	<div class="order-text-02 mt40"><a href="https://www.kyoto-happy.co.jp/corporate/csr/sdgsdx/">SDGs・DX・GX・ESGの<br class="sp">「一本の道」を歩み続ける</a></div>
	<div class="order-text-01 mt40"><a href="https://www.kyoto-happy.co.jp/use/">感動・体感品質を全国宅配しています</a></div>
	<div class="order-useL">
		<div class="order-use-mail"><a href="/contact/"><img src="<?php echo get_stylesheet_directory_uri(); ?>/img/top-truck.png" alt="お問い合わせ">WEBからのご注文はこちら　＞</a></div>
	</div>
	<div class="order-useR smb50">
		<div class="order-use-tel"><a href="tel:0120-88-6868"><span class="order-use-tel-01">お電話でのご注文はこちら</span>0120-88-6868</a></div>
	</div>
	<br clear="all">

	<section class="service pd00">
		<h2 class="tac">コンセプトと使命</h2>
	</section>
	<div class="new-top-concept">
		<div class="new-top-concept-title">― 「いい服長持ち&reg;」で地球環境を守ろう ―</div>
		ファッション業界では<br class="con-br">驚くべき地球環境汚染が問題となっています。<br />
		国連貿易開発会議(UNCTAD)は、<br class="con-br">ファッション業界を世界第２位の<br class="con-br">環境汚染産業として指摘しており、<br />
		日本では年間51万トンもの衣料品が<br class="con-br">廃棄されています（環境省広報）。<br /><br />
		そこで、私たちハッピーケアメンテ&reg;は、<br class="con-br">ファッション業界の環境汚染を解決するために、<br />
		年間わずか４～５万点ですが、<br class="con-br">「ケアメンテ技術」によって、<br class="con-br">捨てられる運命の服飾品を<br />
		着続けられるように、<br class="con-br">持ち続けられるように<br class="con-br">「再生産」のビジネスモデルを提供しています。<br /><br />
		それが、脱炭素社会（カーボンニュートラル）を推進し、<br class="con-br">地球環境を守ることにつながると考えているからです。
	</div>
	<script src="https://www.kyoto-happy.co.jp/_assets/js/skippr.min_170920.js"></script>
	<link rel="stylesheet" href="https://www.kyoto-happy.co.jp/_assets/css/jquery.bxslider_170920.css">
	<script src="https://www.kyoto-happy.co.jp/_assets/js/jquery.bxslider.min_170920.js"></script>
	<script type="text/javascript">
	$(document).on('mousedown','.bx-viewport a',function(){
		var $this = $(this),
				myHref = $this.attr('href'),
				myTarget = $this.attr('target');
		if(myTarget === '_blank'){
			window.open(myHref);
		}else{
			window.location.href = myHref;
		}
	});
	$(function() {
		$('#lp_slider').bxSlider({
			slideWidth: 370,
			auto: true,
			infiniteLoop: true,
			slideMargin: 15,
			autoHover: true,
			pause:6000
		});
	});
	</script>
	<section id="case">
		<div class="container">
			<!-- <div class="case_top"><img src="<?php echo get_stylesheet_directory_uri(); ?>/img/header01_w.png" alt="さがす"><br>さがす</div> -->
			<h2 class="tac">
				<span class="color-code-g">＼ おうちのクローゼットは「宝の山」／</span><br />
				<span>ケアメンテ Before & After 検索<span class="pc"> / </span><br class="sp">概算お見積り事例集</span><br />
				<img src="https://www.kyoto-happy.co.jp/wp/wp-content/themes/HAPPY_Dark/img/header01_w_or.png" alt=""><span class="color-code">「さがす」</span>
			</h2>
			<p class="tit_txt">
				クローゼットの中は「宝の山」です。<br />
				2000点を超えるケアメンテbefore&after事例集で<br class="pc-none">お確かめください。<br />
				「着用できない、持てない」と諦めていた<br class="pc-none">お手持ちの服や鞄類が<br />
				新品同様に蘇る感動品質が体感できます。<br />
				お困り・お悩みの服飾品（類似品）を<br class="pc-none">「さがす」で検索してください。<br />
				ケアメンテbefore&afterと概算のお見積りが<br class="pc-none">確認できます。
			</p>
			<div class="balloon">
				<div class="faceicon">
			    		<img src="https://www.kyoto-happy.co.jp/wp/wp-content/themes/HAPPY_Dark/img/face-icon.png" alt="2000点を超えるケアメンテ before&Afterの事例集はコチラ" />
				</div>
				<div class="chatting">
					<div class="says">
						<p>
							フリマアプリで<br class="pc-none">中古ラグジュアリー服飾品を売る前に<br />
							「ちょっとでも高く売れたらなぁ」<br />
							そんな時あなたならどうする！？<br />
							そうだ、「ハッピーケアメンテ&reg;」に<br class="pc-none">頼んでみよう！！
						</p>
					</div>
				</div>
			</div>
			<div class="btn">
				<a href="/carementeh_search/">2000点を超えるケアメンテ<br class="pc-none">before&Afterの事例集はコチラ</a>
			</div>
			<p class="tit_txt">イメージサンプル…写真をクリックしてください。<br />「さがす」検索サイトと同様のケアメンテbefore&after、 概算お見積り他、詳細をご覧いただけます。</p>
			<ul class="slick_case_list sp-none-img">
				<li>
					<a href="/carementeh_search/detail.html?item_id=0001413">
					<div class="link-icon">
						<img src="https://www.kyoto-happy.co.jp/external_image.html?url=http://kh01.kyoto-happy.co.jp/netkuroku/images/N00014138.jpg" alt="case01">
						<div class="pc-link-icon"><img src="https://www.kyoto-happy.co.jp/wp/wp-content/uploads/2021/08/link.png"></div>
						<div class="sp-link-icon"><img src="https://www.kyoto-happy.co.jp/wp/wp-content/uploads/2021/08/tap.png"></div>
					</div>
					<div class="case_list_txt">
						<h3>HERMES<span>バッグ</span></h3>
						<p>皮革100%<br><br>水色</p>
					</div>
				</a>
				</li>
				<li>
					<a href="/carementeh_search/detail.html?item_id=0002913">
					<div class="link-icon">
						<img src="https://www.kyoto-happy.co.jp/external_image.html?url=http://kh01.kyoto-happy.co.jp/netkuroku/images/N00029138.jpg" alt="case01">
						<div class="pc-link-icon"><img src="https://www.kyoto-happy.co.jp/wp/wp-content/uploads/2021/08/link.png"></div>
						<div class="sp-link-icon"><img src="https://www.kyoto-happy.co.jp/wp/wp-content/uploads/2021/08/tap.png"></div>
					</div>
					<div class="case_list_txt">
						<h3>GUCCI<span>バッグ</span></h3>
						<p><br><br>青系柄</p>
					</div>
				</a>
				</li>
				<li>
					<a href="/carementeh_search/detail.html?item_id=0001228">
					<div class="link-icon">
						<img src="https://www.kyoto-happy.co.jp/external_image.html?url=http://kh01.kyoto-happy.co.jp/netkuroku/images/N00012287.jpg" alt="case01">
						<div class="pc-link-icon"><img src="https://www.kyoto-happy.co.jp/wp/wp-content/uploads/2021/08/link.png"></div>
						<div class="sp-link-icon"><img src="https://www.kyoto-happy.co.jp/wp/wp-content/uploads/2021/08/tap.png"></div>
					</div>
					<div class="case_list_txt">
						<h3>MONCLER<span>ダウンジャンパー</span></h3>
						<p>ナイロン100%<br><br>クリーム</p>
					</div>
				</a>
				</li>
				<li>
					<a href="/carementeh_search/detail.html?item_id=0002797">
					<div class="link-icon">
						<img src="https://www.kyoto-happy.co.jp/external_image.html?url=http://kh01.kyoto-happy.co.jp/netkuroku/images/N00027977.jpg" alt="case02">
						<div class="pc-link-icon"><img src="https://www.kyoto-happy.co.jp/wp/wp-content/uploads/2021/08/link.png"></div>
						<div class="sp-link-icon"><img src="https://www.kyoto-happy.co.jp/wp/wp-content/uploads/2021/08/tap.png"></div>
					</div>
					<div class="case_list_txt">
						<h3>Aquascutum<span>ロングコート</span></h3>
						<p>綿100％<br><br>茶系</p>
					</div>
					</a>
				</li>
				<li>
					<a href="/carementeh_search/detail.html?item_id=0002861">
					<div class="link-icon">
						<img src="https://www.kyoto-happy.co.jp:8443/_assets/img/search/index/0002861.jpg" alt="case03">
						<div class="pc-link-icon"><img src="https://www.kyoto-happy.co.jp/wp/wp-content/uploads/2021/08/link.png"></div>
						<div class="sp-link-icon"><img src="https://www.kyoto-happy.co.jp/wp/wp-content/uploads/2021/08/tap.png"></div>
					</div>
					<div class="case_list_txt">
						<h3>LOUIS VUIT…<span>婦人ジャケット</span></h3>
						<p>綿100%<br><br>ピンク系</p>
					</div>
					</a>
				</li>
				<li>
					<a href="/carementeh_search/detail.html?item_id=0003092">
					<div class="link-icon">
						<img src="https://www.kyoto-happy.co.jp:8443/_assets/img/search/index/0003092.jpg" alt="case04">
						<div class="pc-link-icon"><img src="https://www.kyoto-happy.co.jp/wp/wp-content/uploads/2021/08/link.png"></div>
						<div class="sp-link-icon"><img src="https://www.kyoto-happy.co.jp/wp/wp-content/uploads/2021/08/tap.png"></div>
					</div>
					<div class="case_list_txt">
						<h3>DOLCE＆GAB…<span>紳士ジャケット</span></h3>
						<p>麻100%<br><br>水色</p>
					</div>
					</a>
				</li>
				<li>
					<a href="/carementeh_search/detail.html?item_id=0003200">
					<div class="link-icon">
						<img src="https://www.kyoto-happy.co.jp:8443/_assets/img/search/index/0003200.jpg" alt="case01">
						<div class="pc-link-icon"><img src="https://www.kyoto-happy.co.jp/wp/wp-content/uploads/2021/08/link.png"></div>
						<div class="sp-link-icon"><img src="https://www.kyoto-happy.co.jp/wp/wp-content/uploads/2021/08/tap.png"></div>
					</div>
					<div class="case_list_txt">
						<h3>MACKINTOSH<span>ハーフコート</span></h3>
						<p>綿100%<br><br>
							黄緑</p>
					</div>
				</a>
				</li>
				<li>
					<a href="/carementeh_search/detail.html?item_id=0003138">
					<div class="link-icon">
						<img src="https://www.kyoto-happy.co.jp:8443/_assets/img/search/index/0003138.jpg" alt="case01">
						<div class="pc-link-icon"><img src="https://www.kyoto-happy.co.jp/wp/wp-content/uploads/2021/08/link.png"></div>
						<div class="sp-link-icon"><img src="https://www.kyoto-happy.co.jp/wp/wp-content/uploads/2021/08/tap.png"></div>
					</div>
					<div class="case_list_txt">
						<h3>LoroPiana<span>長袖シャツ</span></h3>
						<p>綿100%<br><br>水色</p>
					</div>
				</a>
				</li>
				<li>
					<a href="/carementeh_search/detail.html?item_id=0003489">
					<div class="link-icon">
						<img src="https://www.kyoto-happy.co.jp:8443/_assets/img/search/index/0003489.jpg" alt="case01">
						<div class="pc-link-icon"><img src="https://www.kyoto-happy.co.jp/wp/wp-content/uploads/2021/08/link.png"></div>
						<div class="sp-link-icon"><img src="https://www.kyoto-happy.co.jp/wp/wp-content/uploads/2021/08/tap.png"></div>
					</div>
					<div class="case_list_txt">
						<h3>Moschino<span>ﾉｰｽﾘｰﾌﾞﾀｲﾄﾜﾝﾋﾟｰｽ</span></h3>
						<p>綿100%<br><br>白系柄</p>
					</div>
				</a>
				</li>
				<li>
					<a href="/carementeh_search/detail.html?item_id=0003974">
					<div class="link-icon">
						<img src="/external_image.html?url=http://kh01.kyoto-happy.co.jp/netkuroku/images/N00039747.jpg" alt="case01">
						<div class="pc-link-icon"><img src="https://www.kyoto-happy.co.jp/wp/wp-content/uploads/2021/08/link.png"></div>
						<div class="sp-link-icon"><img src="https://www.kyoto-happy.co.jp/wp/wp-content/uploads/2021/08/tap.png"></div>
					</div>
					<div class="case_list_txt">
						<h3>BORRELLI<span>長袖シャツ</span></h3>
						<p>綿100%<br><br>白系縦縞</p>
					</div>
				</a>
				</li>
			</ul>
			<ul class="slick_case_list pc-none-img">
				<li>
					<a href="/carementeh_search/detail.html?item_id=0001413">
					<div class="link-icon">
						<img src="https://www.kyoto-happy.co.jp/external_image.html?url=http://kh01.kyoto-happy.co.jp/netkuroku/images/N00014138.jpg" alt="case01">
						<div class="pc-link-icon"><img src="https://www.kyoto-happy.co.jp/wp/wp-content/uploads/2021/08/link.png"></div>
						<div class="sp-link-icon"><img src="https://www.kyoto-happy.co.jp/wp/wp-content/uploads/2021/08/tap.png"></div>
					</div>
					<div class="case_list_txt">
						<h3>HERMES<span>バッグ</span></h3>
						<p>皮革100%<br><br>水色</p>
					</div>
				</a>
				</li>
				<li>
					<a href="/carementeh_search/detail.html?item_id=0001228">
					<div class="link-icon">
						<img src="https://www.kyoto-happy.co.jp/external_image.html?url=http://kh01.kyoto-happy.co.jp/netkuroku/images/N00012287.jpg" alt="case01">
						<div class="pc-link-icon"><img src="https://www.kyoto-happy.co.jp/wp/wp-content/uploads/2021/08/link.png"></div>
						<div class="sp-link-icon"><img src="https://www.kyoto-happy.co.jp/wp/wp-content/uploads/2021/08/tap.png"></div>
					</div>
					<div class="case_list_txt">
						<h3>MONCLER<span>ダウンジャンパー</span></h3>
						<p>ナイロン100%<br><br>クリーム</p>
					</div>
				</a>
				</li>
				<li>
					<a href="/carementeh_search/detail.html?item_id=0002913">
					<div class="link-icon">
						<img src="https://www.kyoto-happy.co.jp/external_image.html?url=http://kh01.kyoto-happy.co.jp/netkuroku/images/N00029138.jpg" alt="case01">
						<div class="pc-link-icon"><img src="https://www.kyoto-happy.co.jp/wp/wp-content/uploads/2021/08/link.png"></div>
						<div class="sp-link-icon"><img src="https://www.kyoto-happy.co.jp/wp/wp-content/uploads/2021/08/tap.png"></div>
					</div>
					<div class="case_list_txt">
						<h3>GUCCI<span>バッグ</span></h3>
						<p><br><br>青系柄</p>
					</div>
				</a>
				</li>
				<li>
					<a href="/carementeh_search/detail.html?item_id=0002797">
					<div class="link-icon">
						<img src="https://www.kyoto-happy.co.jp/external_image.html?url=http://kh01.kyoto-happy.co.jp/netkuroku/images/N00027977.jpg" alt="case02">
						<div class="pc-link-icon"><img src="https://www.kyoto-happy.co.jp/wp/wp-content/uploads/2021/08/link.png"></div>
						<div class="sp-link-icon"><img src="https://www.kyoto-happy.co.jp/wp/wp-content/uploads/2021/08/tap.png"></div>
					</div>
					<div class="case_list_txt">
						<h3>Aquascutum<span>ロングコート</span></h3>
						<p>綿100％<br><br>茶系</p>
					</div>
					</a>
				</li>
				<li>
					<a href="/carementeh_search/detail.html?item_id=0002861">
					<div class="link-icon">
						<img src="https://www.kyoto-happy.co.jp:8443/_assets/img/search/index/0002861.jpg" alt="case03">
						<div class="pc-link-icon"><img src="https://www.kyoto-happy.co.jp/wp/wp-content/uploads/2021/08/link.png"></div>
						<div class="sp-link-icon"><img src="https://www.kyoto-happy.co.jp/wp/wp-content/uploads/2021/08/tap.png"></div>
					</div>
					<div class="case_list_txt">
						<h3>LOUIS VUIT…<span>婦人ジャケット</span></h3>
						<p>綿100%<br><br>ピンク系</p>
					</div>
					</a>
				</li>
				<li>
					<a href="/carementeh_search/detail.html?item_id=0003092">
					<div class="link-icon">
						<img src="https://www.kyoto-happy.co.jp:8443/_assets/img/search/index/0003092.jpg" alt="case04">
						<div class="pc-link-icon"><img src="https://www.kyoto-happy.co.jp/wp/wp-content/uploads/2021/08/link.png"></div>
						<div class="sp-link-icon"><img src="https://www.kyoto-happy.co.jp/wp/wp-content/uploads/2021/08/tap.png"></div>
					</div>
					<div class="case_list_txt">
						<h3>DOLCE＆GAB…<span>紳士ジャケット</span></h3>
						<p>麻100%<br><br>水色</p>
					</div>
					</a>
				</li>
				<li>
					<a href="/carementeh_search/detail.html?item_id=0003200">
					<div class="link-icon">
						<img src="https://www.kyoto-happy.co.jp:8443/_assets/img/search/index/0003200.jpg" alt="case01">
						<div class="pc-link-icon"><img src="https://www.kyoto-happy.co.jp/wp/wp-content/uploads/2021/08/link.png"></div>
						<div class="sp-link-icon"><img src="https://www.kyoto-happy.co.jp/wp/wp-content/uploads/2021/08/tap.png"></div>
					</div>
					<div class="case_list_txt">
						<h3>MACKINTOSH<span>ハーフコート</span></h3>
						<p>綿100%<br><br>
							黄緑</p>
					</div>
				</a>
				</li>
				<li>
					<a href="/carementeh_search/detail.html?item_id=0003138">
					<div class="link-icon">
						<img src="https://www.kyoto-happy.co.jp:8443/_assets/img/search/index/0003138.jpg" alt="case01">
						<div class="pc-link-icon"><img src="https://www.kyoto-happy.co.jp/wp/wp-content/uploads/2021/08/link.png"></div>
						<div class="sp-link-icon"><img src="https://www.kyoto-happy.co.jp/wp/wp-content/uploads/2021/08/tap.png"></div>
					</div>
					<div class="case_list_txt">
						<h3>LoroPiana<span>長袖シャツ</span></h3>
						<p>綿100%<br><br>水色</p>
					</div>
				</a>
				</li>
				<li>
					<a href="/carementeh_search/detail.html?item_id=0003489">
					<div class="link-icon">
						<img src="https://www.kyoto-happy.co.jp:8443/_assets/img/search/index/0003489.jpg" alt="case01">
						<div class="pc-link-icon"><img src="https://www.kyoto-happy.co.jp/wp/wp-content/uploads/2021/08/link.png"></div>
						<div class="sp-link-icon"><img src="https://www.kyoto-happy.co.jp/wp/wp-content/uploads/2021/08/tap.png"></div>
					</div>
					<div class="case_list_txt">
						<h3>Moschino<span>ﾉｰｽﾘｰﾌﾞﾀｲﾄﾜﾝﾋﾟｰｽ</span></h3>
						<p>綿100%<br><br>白系柄</p>
					</div>
				</a>
				</li>
				<li>
					<a href="/carementeh_search/detail.html?item_id=0003974">
					<div class="link-icon">
						<img src="/external_image.html?url=http://kh01.kyoto-happy.co.jp/netkuroku/images/N00039747.jpg" alt="case01">
						<div class="pc-link-icon"><img src="https://www.kyoto-happy.co.jp/wp/wp-content/uploads/2021/08/link.png"></div>
						<div class="sp-link-icon"><img src="https://www.kyoto-happy.co.jp/wp/wp-content/uploads/2021/08/tap.png"></div>
					</div>
					<div class="case_list_txt">
						<h3>BORRELLI<span>長袖シャツ</span></h3>
						<p>綿100%<br><br>白系縦縞</p>
					</div>
				</a>
				</li>
			</ul>
		</div>
	</section>
	<!--　/#case -->
	<section id="technology">
		<div class="container">
			<div class="technology_pv">
				<h2 class="tac">動画で見るアイテム別 <br class="sp">驚異のケアメンテ&reg;</h2>
				<ul class="slick_technology_list">
					<li><a href="https://www.youtube.com/embed/pOZPaiVtIVE" class="popup cboxElement" target="_blank">
						<p class="number">00</p>
						<div class="img"><img src="https://www.kyoto-happy.co.jp/wp/wp-content/themes/HAPPY_Dark/img/technology_pv00.jpg" alt="" class="thum"><img src="https://www.kyoto-happy.co.jp/wp/wp-content/themes/HAPPY_Dark/img/technology_pv00.png" alt="" class="font" width="275" height="113"><img src="https://www.kyoto-happy.co.jp/wp/wp-content/themes/HAPPY_Dark/img/technology_pv_play.png" alt="" class="play" width="71" height="71"></div>
						<h4 class="tac">完結編</h4></a>
					</li>
					<li><a href="https://www.youtube.com/embed/yzTc75yHZ0M" class="popup cboxElement" target="_blank">
						<p class="number">01</p>
						<div class="img"><img src="https://www.kyoto-happy.co.jp/wp/wp-content/themes/HAPPY_Dark/img/technology_pv01.jpg" alt="" class="thum"><img src="https://www.kyoto-happy.co.jp/wp/wp-content/themes/HAPPY_Dark/img/technology_pv01.png" alt="" class="font" width="98" height="50"><img src="https://www.kyoto-happy.co.jp/wp/wp-content/themes/HAPPY_Dark/img/technology_pv_play.png" alt="" class="play" width="71" height="71"></div>
						<h4 class="tac">ダウン類</h4></a>
					</li>
					<li><a href="https://www.youtube.com/embed/A7kSrLF3mdg" class="popup cboxElement" target="_blank">
						<p class="number">02</p>
						<div class="img"><img src="https://www.kyoto-happy.co.jp/wp/wp-content/themes/HAPPY_Dark/img/technology_pv02.jpg" alt="" class="thum"><img src="https://www.kyoto-happy.co.jp/wp/wp-content/themes/HAPPY_Dark/img/technology_pv02.png" alt="" class="font" width="178" height="57"><img src="https://www.kyoto-happy.co.jp/wp/wp-content/themes/HAPPY_Dark/img/technology_pv_play.png" alt="" class="play" width="71" height="71"></div>
						<h4 class="tac">レザーグレイン</h4></a>
					</li>
					<li><a href="https://www.youtube.com/embed/ZF5HM76OxZw" class="popup cboxElement" target="_blank">
						<p class="number">03</p>
						<div class="img"><img src="https://www.kyoto-happy.co.jp/wp/wp-content/themes/HAPPY_Dark/img/technology_pv03.jpg" alt="" class="thum"><img src="https://www.kyoto-happy.co.jp/wp/wp-content/themes/HAPPY_Dark/img/technology_pv03.png" alt="" class="font" width="140" height="55"><img src="https://www.kyoto-happy.co.jp/wp/wp-content/themes/HAPPY_Dark/img/technology_pv_play.png" alt="" class="play" width="71" height="71"></div>
						<h4 class="tac">メンズスーツ</h4></a>
					</li>
					<li><a href="https://www.youtube.com/embed/IgkwDl84V9g" class="popup cboxElement" target="_blank">
						<p class="number">04</p>
						<div class="img"><img src="https://www.kyoto-happy.co.jp/wp/wp-content/themes/HAPPY_Dark/img/technology_pv04.jpg" alt="" class="thum"><img src="https://www.kyoto-happy.co.jp/wp/wp-content/themes/HAPPY_Dark/img/technology_pv04.png" alt="" class="font" width="140" height="55"><img src="https://www.kyoto-happy.co.jp/wp/wp-content/themes/HAPPY_Dark/img/technology_pv_play.png" alt="" class="play" width="71" height="71"></div>
						<h4 class="tac">レディースシルク</h4></a>
					</li>
					<li><a href="https://www.youtube.com/embed/Cv9idLb6GFw" class="popup cboxElement" target="_blank">
						<p class="number">05</p>
						<div class="img"><img src="https://www.kyoto-happy.co.jp/wp/wp-content/themes/HAPPY_Dark/img/technology_pv05.jpg" alt="" class="thum"><img src="https://www.kyoto-happy.co.jp/wp/wp-content/themes/HAPPY_Dark/img/technology_pv05.png" alt="" class="font" width="140" height="55"><img src="https://www.kyoto-happy.co.jp/wp/wp-content/themes/HAPPY_Dark/img/technology_pv_play.png" alt="" class="play" width="71" height="71"></div>
						<h4 class="tac">シルエット・ディティール</h4></a>
					</li>
					<li><a href="https://www.youtube.com/embed/6b8L-JpDj2s" class="popup cboxElement" target="_blank">
						<p class="number">06</p>
						<div class="img"><img src="https://www.kyoto-happy.co.jp/wp/wp-content/themes/HAPPY_Dark/img/technology_pv06.jpg" alt="" class="thum"><img src="https://www.kyoto-happy.co.jp/wp/wp-content/themes/HAPPY_Dark/img/technology_pv06.png" alt="" class="font" width="140" height="55"><img src="https://www.kyoto-happy.co.jp/wp/wp-content/themes/HAPPY_Dark/img/technology_pv_play.png" alt="" class="play" width="71" height="71"></div>
						<h4 class="tac">ゴム引き（マッキントッシュ）</h4></a>
					</li>
				</ul>
				<div class="btnArea">
					<div class="btn"><img src="https://www.kyoto-happy.co.jp/wp/wp-content/themes/HAPPY_Dark/img/youtube.png" alt="youtube" class="youtube_logo" width="90" height="21"><a href="https://www.youtube.com/channel/UCZyJC69VvnDqIAgsEQ-rTeQ">チャンネル登録はこちら</a>
					</div>
					<div class="btn">
						<a href="/movie/">Happy動画集をもっと見る</a>
					</div>
				</div>

			</div>

		</div>
	</section>
	<!--　/#technology -->


	<section id="use">
		<div class="container">
			<h2 class="tac">ご利用方法／価格表</h2>
			<p class="tit_txt">お客様のご都合に合わせたお申込み方法を選びください。</p>
			<div class="btnArea">
				<div class="banner">
					<h2>ご注文からお届けまでのフローについて詳しくご案内</h2>
					<a href="/use/">
						<img src="<?php echo get_stylesheet_directory_uri(); ?>/img/use_bnr01.jpg" alt="ご注文方法">
						<div class="banner_txt">
							<h3 class="banner_txt_f18"><span class="banner_txt_ls">ご注文方法</span><br />ご利用の流れ</h3>
						</div>
					</a>
				</div>
				<div class="banner">
					<h2>ケアメンテ&reg;のオプションを含む価格一覧はこちら。</h2>
					<a href="/use/price/pricelist/">
						<img src="<?php echo get_stylesheet_directory_uri(); ?>/img/use_bnr02.jpg" alt="価格表">
						<div class="banner_txt">
							<h3>価格表</h3>
						</div>
					</a>
				</div>
			</div>
			<div id="tel" class="sp">
				<div class="tel_section"><a href="tel:0120-88-6868"><img src="<?php echo get_stylesheet_directory_uri(); ?>/img/tel_sp-ver2.png" alt="ご注文・お問い合わせもお気軽にお電話ください。 0120-88-6868 月?土 9:00~18:00（日曜・祝祭日は除く）"></a></div>
				<div class="mail_section"><a href="/contact/"><img src="<?php echo get_stylesheet_directory_uri(); ?>/img/mail_sp-ver2.png" alt="お問い合わせ"></a></div>
				<div class="mail_section"><a href="/use/price/catalog/"><img src="<?php echo get_stylesheet_directory_uri(); ?>/img/catalog_sp-ver2.png" alt="カタログ請求"></a></div>
			</div>
		</div>
	</section>
	<!--　/#use -->
	<div class="order-text-01 mt40 sp-none"><a href="https://www.kyoto-happy.co.jp/use/">感動・体感品質を全国宅配しています</a></div>
	<div class="order-useL">
		<div class="order-use-mail"><a href="/contact/"><img src="<?php echo get_stylesheet_directory_uri(); ?>/img/top-truck.png" alt="お問い合わせ">WEBからのご注文はこちら　＞</a></div>
	</div>
	<div class="order-useR smb50 sp-none">
		<div class="order-use-tel"><a href="tel:0120-88-6868"><span class="order-use-tel-01">お電話でのご注文はこちら</span>0120-88-6868</a></div>
	</div>
	<br clear="all">
	<section id="partner">
		<div class="container">
			<h2 class="tac">ラグジュアリーブランド・デパートの<br class="sp">ファッションを<br class="pc">サポートする</h2>
			<div class="partner-01">クリーニングの駆け込み寺&reg;<br class="sp">「ハッピーケアメンテ&reg;」</div>
			<p class="color-bl">日本の三大セレクトショップ、ラグジュアリーブランド、デパートなど、<br class="pc">ケアメンテ&reg;を推奨する業務提携先と「いい服長持ち」に取り組んでいます。</p>
			<div class="sp partner-img"><img src="<?php echo get_stylesheet_directory_uri(); ?>/img/partner_sp.jpg" alt="ラグジュアリーブランド・デパートのファッションをサポートするハッピーケアメンテ"></a></div>
			<div class="partner-02">業務提携先<br />全国約300店舗でお預かりしています。</div>
			<div class="sptc"><p>ご利用特典・取扱い店舗などの詳細は<br class="sp">下記アイコンをクリックしてください。<br />皆様のご来店を心よりお待ちしております。</p></div>
			<ul class="tac">
				<li><a href="/shop/brand/tomorrowland/">
					<img src="<?php echo get_stylesheet_directory_uri(); ?>/img/partner_logo_01.png" alt="TOMORROWLAND"></a>
				</li>
				<li><a href="/shop/brand/beams/">
					<img src="<?php echo get_stylesheet_directory_uri(); ?>/img/partner_logo_02.png" alt="BEAMS"></a>
				</li>
				<li><a href="/shop/brand/united-arrows/">
					<img src="<?php echo get_stylesheet_directory_uri(); ?>/img/partner_logo_03.png" alt="UNITED ARROWS"></a>
				</li>
				<li><a href="/shop/brand/komehyo/">
					<img src="<?php echo get_stylesheet_directory_uri(); ?>/img/partner_logo_10.png" alt="KOMEHYO"></a>
				</li>
				<li><a href="/shop/brand/sinjuku_takashimaya/">
					<img src="<?php echo get_stylesheet_directory_uri(); ?>/img/partner_logo_06.png" alt="新宿タカシマヤ"></a>
				</li>
				<li><a href="/shop/brand/yokohama_takashimaya/">
					<img src="<?php echo get_stylesheet_directory_uri(); ?>/img/partner_logo_09.png" alt="横浜タカシマヤ"></a>
				</li>
				<li><a href="/shop/brand/abeno_harukas/">
					<img src="<?php echo get_stylesheet_directory_uri(); ?>/img/partner_logo_08.png" alt="あべのハルカス 近鉄本店"></a>
				</li>
				<li><a href="/shop/brand/seibu_ikebukuro/">
					<img src="<?php echo get_stylesheet_directory_uri(); ?>/img/partner_logo_07.png" alt="西武池袋本店"></a>
				</li>
			</ul>
			<div class="btnArea">
				<table class="partner-teble">
					<tr>
						<th><img src="<?php echo get_stylesheet_directory_uri(); ?>/img/partner_img.png" alt="便利なショップ検索機能"></th>
						<td>
							<div class="partner-teble-01"><i class="fa fa-map-marker" aria-hidden="true"></i> 便利なショップ検索機能</div>
							ご自宅・会社・出張先など、全国どこでも「今いる場所」から<br />スマホでショップ検索。<br />
							全国約300店舗でお預かりできます。
							<div class="btn tac">
								<a href="/shop_search/">近くのショップを検索</a>
							</div>
						</td>
					</tr>
				</table>
			</div>
			<div class="btnArea">
				<div class="hermes">
					<a href="tel:0120-88-3040">
					<span class="hermes-L">エルメス公認 お客様専用ダイヤル</span><br class="sp"><span class="hermes-R">0120-88-3040</span></a>
				</div>
			</div>
		</div>
	</section>
	<!--　/#partner -->
	<section id="technology-2">
		<section class="lp_top__section mb100">
			<div class="container">
				<h2 class="tac s4-5vw">もっと早く知りたかった！<br />こんな“お困り･お悩みごと”ありませんか</h2>
				<div class="lp_slider-text">クリーニングの疑問 etc...<br / >「どうしてもあきらめきれない！」お困りの声<br />「ハッピーケアメンテ」で解決します。</div>
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
			</div>
			<div class="container new-lp-img">
				<img src="https://www.kyoto-happy.co.jp/wp/wp-content/themes/HAPPY_Dark/img/new-lp/001.jpg" alt="免許皆伝「虎の巻」シミ忍者撃退の術" />
				<img class="lp-img" src="https://www.kyoto-happy.co.jp/wp/wp-content/themes/HAPPY_Dark/img/new-lp/002.jpg" alt="クリーニング後の衣装に忍び寄る汗ジミ・黄ばみの黒い影･･･" />
				<img class="lp-img" src="https://www.kyoto-happy.co.jp/wp/wp-content/themes/HAPPY_Dark/img/new-lp/003.jpg" alt="残った汚れ成分が酸化して衣類に定着！あとから浮き出る「シミ・黄ばみの原因」に！" />
				<img class="lp-img" src="https://www.kyoto-happy.co.jp/wp/wp-content/themes/HAPPY_Dark/img/new-lp/004-1.jpg" alt="出たわね！クリ忍軍シミ太郎！" />
				<div class="lp-btn">
					<a href="https://www.kyoto-happy.co.jp/lp/">続きはこちら ＞</a>
				</div>
			</div>
			<div class="lp_slider-text-02 mt40 smb00"><a href="/carementeh/overview/difference/">高級クリーニングの先をゆくハッピーケアメンテ&reg;<br />クリーニングとケアメンテ&reg;は何が違うの？</a></div>
		</section>
		<div class="container">
			<h2 class="tac">ケアメンテ&reg;を支える<br class="sp">テクノロジー</h2>
			<div class="tac">
				<p>大切な服を新品状態で永く着続けるために開発された世界初の独自技術。</p>
			</div>
			<ul class="technology_list">
				<li>
					<h3>基本洗浄</h3>
					<div class="itemBox">
						<a href="/carementeh/service/aquadry/">
						<img src="<?php echo get_stylesheet_directory_uri(); ?>/img/technology01.png" alt="基本洗浄">
						<div class="technology_txt">
							<h4>水油系アクアドライ&reg;</h4>
							<p>洗浄の常識を覆したハッピー独自の水系洗浄技術がクリーニングの欠陥を克服します。</p>
						</div>
						</a>
					</div>
				</li>
				<li>
					<h3>再生技術</h3>
					<div class="itemBox">
					<a href="/carementeh/service/ripron/">
						<img src="<?php echo get_stylesheet_directory_uri(); ?>/img/technology02-1.jpg" alt="再生技術">
						<div class="technology_txt">
							<h4>リプロン&reg;</h4>
							<p>シミ汚れ・黄ばみ他、様々なトラブルで諦めていた衣服を独自の再生技術で蘇らせます。</p>
						</div>
					</a>
					</div>
				</li>
				<li>
					<h3>加工技術</h3>
					<div class="itemBox">
					<a class="itemBox" href="/carementeh/service/valueon/">
						<img src="<?php echo get_stylesheet_directory_uri(); ?>/img/technology03-1.jpg" alt="加工技術">
						<div class="technology_txt">
							<h4>バリューＯＮ&reg;</h4>
							<p>お気に入りの衣服に新たな機能性をもたせるのがハッピー独自の加工技術「バリューON&reg;」です</p>
						</div>
					</a>
					</div>
				</li>
				<li>
					<h3>仕上げ技術</h3>
					<div class="itemBox">
					<a class="itemBox" href="/technology/innovation/press/">
						<img src="https://www.kyoto-happy.co.jp/wp/wp-content/themes/HAPPY_Dark/img/technology04-1.jpg" alt="仕上げ技術">
						<div class="technology_txt">
							<h4>シルエットプレス&reg;</h4>
							<p>あらゆる衣服の特徴に合わせて独自開発したプレス手法で本来のシルエットと風合いを復元します。</p>
						</div>
					</a>
					</div>
				</li>
			</ul>
		</div>
	</section>
	<!--　/#technology -->

	<section id="service">
		<div class="container">
			<h2 class="tac">ハッピーのサービス</h2>
			<div class="tac">
				<p>お気に入りのアイテムを永くご愛用いただくために、<br class="pc">お客様の思いとしっかり向き合い、安心してご利用いただけるサービスをご提供いたします。</p>
			</div>
			<ul class="service_list">
				<li>
					<img src="https://www.kyoto-happy.co.jp/wp/wp-content/themes/HAPPY_Dark/img/service01.jpg" alt="全業務を一元管理する「電子カルテ」">
					<h4><img src="https://www.kyoto-happy.co.jp/wp/wp-content/themes/HAPPY_Dark/img/service_tit01.png" alt="全業務を一元管理する「電子カルテ」" width="65" height="285"></h4>
					<a href="/carementeh/overview/karte/">ハッピー電子カルテシステム</a>
				</li>
				<li>
					<img src="https://www.kyoto-happy.co.jp/wp/wp-content/themes/HAPPY_Dark/img/service05.jpg" alt="お客様のお困りの声にじっくりと耳を傾ける">
					<h4><img src="https://www.kyoto-happy.co.jp/wp/wp-content/themes/HAPPY_Dark/img/service_tit05.png" alt="お客様のお困りの声にじっくりと耳を傾ける" width="65" height="284"></h4>
					<a href="/carementeh/overview/counseling/">カウンセリング</a>
				</li>
				<li>
					<img src="https://www.kyoto-happy.co.jp/wp/wp-content/themes/HAPPY_Dark/img/service02.jpg" alt="服は息をしている保管お預かりサービス">
					<h4><img src="https://www.kyoto-happy.co.jp/wp/wp-content/themes/HAPPY_Dark/img/service_tit02.png" alt="服は息をしている保管お預かりサービス" width="65" height="284"></h4>
					<a href="/carementeh/service/wardrobe/">ハッピーワードローブ&reg;</a>
				</li>
				<li>
					<img src="https://www.kyoto-happy.co.jp/wp/wp-content/themes/HAPPY_Dark/img/service06.jpg" alt="美しいシルエットのまま大切にお届けする">
					<h4><img src="https://www.kyoto-happy.co.jp/wp/wp-content/themes/HAPPY_Dark/img/service_tit06.png" alt="美しいシルエットのまま大切にお届けする" width="65" height="285"></h4>
					<a href="/use/howtoorder/package/">配送パッケージ</a>
				</li>
			</ul>
			<div class="lp_slider-text-02 mt30">
				<a href="/carementeh/overview/difference/">高級クリーニングの先をゆくハッピーケアメンテ&reg;<br />クリーニングとケアメンテ&reg;は何が違うの？</a>
			</div>
		</div>
	</section>
	<!--　/#service -->
	<section id="member">
		<div class="container">
			<h2 class="tac">マイページ会員のご案内</h2>
			<p>Happyケアメンテ&reg;をもっとお得に、もっと便利にお使いいただけるマイページ会員募集中。</p>
			<ul>
				<li>
					<img src="<?php echo get_stylesheet_directory_uri(); ?>/img/member01.png" alt="セール情報">
					<h3>セール情報</h3>
					<p>マイページ会員だけの<br>
						お得なセール情報を<br>
						ご案内します</p>
				</li>
				<li>
					<img src="<?php echo get_stylesheet_directory_uri(); ?>/img/member02.png" alt="簡単注文">
					<h3>簡単注文</h3>
					<p>ケアメンテ&reg;の<br>
						お申し込みを大幅に<br>
						簡略化できます</p>
				</li>
				<li>
					<img src="<?php echo get_stylesheet_directory_uri(); ?>/img/member03.png" alt="ハッピー SNS">
					<h3>ハッピー SNS</h3>
					<p>他のお客様とフレンドに<br>
						なったり共通の話題で<br>
						盛り上がろう</p>
				</li>
				<li>
					<img src="<?php echo get_stylesheet_directory_uri(); ?>/img/member04.png" alt="MyPage">
					<h3>MyPage</h3>
					<p>注文や履歴、<br>
						ケアメンテ&reg;のカルテなど<br>
						いつでも確認</p>
				</li>
			</ul>
			<div class="btnArea">
				<div class="btn">
					<a href="/mypageuse/use_mypage/">マイページについて詳しくは</a>
				</div>
				<div class="btn">
					<a href="/entry/">会員登録をする</a>
				</div>
				<div class="login">
					<a href="/mypage/">既に会員の方はこちらからログイン</a>
				</div>
			</div>
		</div>
	</section>
	<!--　/#member -->
	<div class="order-text-01 mt40"><a href="https://www.kyoto-happy.co.jp/use/">感動・体感品質を全国宅配しています</a></div>
	<div class="order-useL">
		<div class="order-use-mail"><a href="/contact/"><img src="<?php echo get_stylesheet_directory_uri(); ?>/img/top-truck.png" alt="お問い合わせ">WEBからのご注文はこちら　＞</a></div>
	</div>
	<div class="order-useR smb50">
		<div class="order-use-tel"><a href="tel:0120-88-6868"><span class="order-use-tel-01">お電話でのご注文はこちら</span>0120-88-6868</a></div>
	</div>
	<br clear="all">

	<section class="service mt0">
		<div class="container">
			<h2 class="tac">ハッピーの「衣文化価値創造」</h2>
			<div class="banner">
				<a href="/corporate/csr/reuse/">
					<img src="https://www.kyoto-happy.co.jp/wp/wp-content/themes/HAPPY_Dark/img/service_bnr.jpg" alt="自然循環型産業の創出">
					<div class="banner_txt">
						<h2>自然循環型産業の創出</h2>
						<p>「ハッピーケアメンテ&reg;」は、良い服／良いモノを<br>長もちさせる究極の“自然循環型産業”です</p>
					</div>
				</a>
			</div>
			<div class="banner mt30">
				<a href="/carementeh/overview/style/">
					<img src="https://www.kyoto-happy.co.jp/wp/wp-content/themes/HAPPY_Dark/img/service_bnr-2.jpg" alt="ハッピーケアメンテの仕事スタイル">
					<div class="banner_txt">
						<h2>ハッピーケアメンテの仕事スタイル</h2>
						<p>クリーニングの限界を解消した<br />「ハッピーケアメンテ&reg;」の仕事への取り組み</p>
					</div>
				</a>
			</div>

		</div>
	</section>
	<!--　/#service -->

	<section class="service">
		<div class="container">
			<h2 class="tac">第三者評価</h2>
			<div class="tac">
				<p>ハッピーは公的機関の認定を受けています。</p>
			</div>
			<div class="technology_award">
				<ul>
					<li><img src="https://www.kyoto-happy.co.jp/wp/wp-content/themes/HAPPY_Dark/img/award07.png" alt="DX認証"></li>
					<li><img src="https://www.kyoto-happy.co.jp/wp/wp-content/themes/HAPPY_Dark/img/award06.png" alt="ソーシャル企業認証制度 S認証"></li>
					<li><img src="https://www.kyoto-happy.co.jp/wp/wp-content/themes/HAPPY_Dark/img/award02.png" alt="中小企業IT経営力大賞 経済産業大臣賞"></li>
					<li><img src="https://www.kyoto-happy.co.jp/wp/wp-content/themes/HAPPY_Dark/img/award01.png" alt="第一回「日本サービス大賞」 優秀賞（SPRING賞）受賞"></li>
					<li><img src="https://www.kyoto-happy.co.jp/wp/wp-content/themes/HAPPY_Dark/img/award03.png" alt="ハイ・サービス日本300選"></li>
					<li><img src="https://www.kyoto-happy.co.jp/wp/wp-content/themes/HAPPY_Dark/img/award04.png" alt="おもてなし経営企業選 選出企業"></li>
					<li><img src="https://www.kyoto-happy.co.jp/wp/wp-content/themes/HAPPY_Dark/img/award05.png" alt="おもてなし規格認証2016"></li>

				</ul>
			</div>
			<div class="technology_award_sp">
				<ul>
					<li><img src="https://www.kyoto-happy.co.jp/wp/wp-content/themes/HAPPY_Dark/img/award07.png" alt="DX認証"></li>
					<li><img src="https://www.kyoto-happy.co.jp/wp/wp-content/themes/HAPPY_Dark/img/award06.png" alt="ソーシャル企業認証制度 S認証"></li>
					<li><img src="https://www.kyoto-happy.co.jp/wp/wp-content/themes/HAPPY_Dark/img/award02.png" alt="中小企業IT経営力大賞 経済産業大臣賞"></li>
					<li><img src="https://www.kyoto-happy.co.jp/wp/wp-content/themes/HAPPY_Dark/img/award01.png" alt="第一回「日本サービス大賞」 優秀賞（SPRING賞）受賞"></li>
					<li><img src="https://www.kyoto-happy.co.jp/wp/wp-content/themes/HAPPY_Dark/img/award03.png" alt="ハイ・サービス日本300選"></li>
					<li><img src="https://www.kyoto-happy.co.jp/wp/wp-content/themes/HAPPY_Dark/img/award04.png" alt="おもてなし経営企業選 選出企業"></li>
					<li><img src="https://www.kyoto-happy.co.jp/wp/wp-content/themes/HAPPY_Dark/img/award05.png" alt="おもてなし規格認証2016"></li>
				</ul>
				<br clear="all">
			</div>
			<div class="btn">
				<a href="/corporate/company/winning/">認定・受賞一覧</a>
			</div>
			<div class="btn">
				<a href="/corporate/media/media_list/">メディア報道一覧</a>
			</div>
			<div class="lp_slider-text-02 mt60 mb00">
				<a href="/carementeh/overview/difference/">高級クリーニングの先をゆくハッピーケアメンテ&reg;<br />クリーニングとケアメンテ&reg;は何が違うの？</a>
			</div>
		</div>
	</section>
	<section id="knowledge">
		<div class="container">
			<h2 class="tac"><span>おしゃれを楽しむ情報満載</span><br>
				おしゃれの雑学</h2>
			<p class="tit_txt">「シミ・黄ばみの正体」や「素材・繊維の特徴」など、<br class="pc">オシャレをもっと楽しむための知って得する情報が満載です。随時更新しています。</p>
			<ul class="slick_knowledge_list">
				<li>
					<a href="/knowledge/stain/">
						<img src="/wp/wp-content/uploads/2016/10/img1-1.jpg" alt="knowledge01">
						<div class="knowledge_list_txt">
							<h3>シミ・黄ばみの正体<br><br class="pc"></h3>
							<p>黄ばみのメカニズムを徹底解剖 クリーニングに出しているのに黄ばんでしまう？</p>
						</div>
					</a>
				</li>
				<li>
					<a href="/knowledge/dry_cleaning/">
						<img src="/wp/wp-content/uploads/2016/10/img2-1.jpg" alt="knowledge02">
						<div class="knowledge_list_txt">
							<h3>ドライクリーニングの<br class="pc">実態</h3>
							<p>ドライクリーニングの長所と短所を徹底解剖 ドライクリーニングって何？</p>
						</div>
					</a>
				</li>
				<li>
					<a href="/knowledge/chemical_fiber/">
						<img src="/wp/wp-content/uploads/2016/10/img3-1.jpg" alt="knowledge03">
						<div class="knowledge_list_txt">
							<h3 class="indent">「染色」と「塗色」は<br class="pc">違います！</h3>
							<p>「染色」と「塗色」は違います！クローゼットなどで保管中に、洋服の生地が色あせ…</p>
						</div>
					</a>
				</li>
				<li>
					<a href="/knowledge/discoloration/">
						<img src="/wp/wp-content/uploads/2016/10/img5-1.jpg" alt="knowledge04">
						<div class="knowledge_list_txt">
							<h3>色焼け・変色と<br class="pc">その原因</h3>
							<p>黄ばみのメカニズムを徹底解剖 クリーニングに出しているのに黄ばんでしまう？</p>
						</div>
					</a>
				</li>
				<li>
					<a href="/knowledge/silk/">
						<img src="/wp/wp-content/uploads/2016/10/img11-1.jpg" alt="knowledge01">
						<div class="knowledge_list_txt">
							<h3>最も美しい繊維「絹」<br><br class="pc"></h3>
							<p>繊維の女王 絹（シルク）は、日本では主に和装に使われていましたが、今では『繊維…</p>
						</div>
					</a>
				</li>
				<li>
					<a href="/knowledge/jyuban/">
						<img src="/wp/wp-content/uploads/2016/10/img4-1.jpg" alt="knowledge01">
						<div class="knowledge_list_txt">
							<h3>ひそかなお洒落<br class="pc">「襦袢」<br class="pc"></h3>
							<p>「襦袢」とは 襦袢とは、着物の下、肌着の上に着るものです。 きものの裏側の汚れ…</p>
						</div>
					</a>
				</li>
			</ul>
			<div class="btn">
				<a href="/knowledge/">おしゃれの雑学をもっと見る</a>
			</div>
		</div>
	</section>
	<!--　/#knowledge -->


	<section id="reading">
		<div class="container">
			<div class="banner">
				<a href="https://www.kyoto-happy.co.jp:8443/pdf/Manga_01.pdf?ver1.0&_fsi=4C6UrMQW">
					<img src="<?php echo get_stylesheet_directory_uri(); ?>/img/reading_bnr_comic.jpg" alt="マンガで分かる「ケアメンテサービス」">
					<div class="banner_txt">
						<h2>マンガで分かる<br><span class="indent">「ケアメンテサービス」</span></h2>
						<p>ケアメンテであなたのファッションライフが変わる</p>
					</div>
				</a>
			</div>
			<div class="banner">
				<a href="/sachi/">
					<img src="<?php echo get_stylesheet_directory_uri(); ?>/img/reading_bnr_sachi.jpg?220121" alt="京の伝統工芸職人を追うWebマガジン 「幸」 -sachi-">
					<div class="banner_txt">
						<p>“技”を持つ職人達。華やかな表舞台の裏には人知れず腕を磨き精進する姿がある。職人技と呼ばれる“極み”を完成した人々、”ケアメンテ”も縁の下の力持ちに徹し、静かに”技”を研鑽している。伝統工芸の職人技とケアメンテの職人技は共通しており、それぞれの技の“極み”を発見してもらうために「幸」がある。長年に渡りご紹介してきたハッピーの季刊誌 「幸（sachi）」が、WEB版に生まれ変わり待望の復刊です。</p>
					</div>
				</a>
			</div>
		</div>
	</section>
	<!--　/#reading -->



	<?php get_template_part( 'shared/front-bottom' ); ?>
	<?php get_footer(); ?>
