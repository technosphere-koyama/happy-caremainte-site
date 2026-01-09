<?php get_header(); ?>

<?php if ( is_front_page() ) : ?>
	<div id="left_banner">
		<div id="left_banner_inner">
			<div id="left_banner_off"><img src="https://www.kyoto-happy.co.jp/wp/wp-content/themes/HAPPY_Dark/item/close.png"></div>
			<a href="https://www.kyoto-happy.co.jp/sachi/"><img src="https://www.kyoto-happy.co.jp/wp/wp-content/themes/HAPPY_Dark/img/sachi-20230825.png" alt=""></a>
		</div>
		<div id="left_banner_inner2">
			<div id="left_banner_off2"><img src="https://www.kyoto-happy.co.jp/wp/wp-content/themes/HAPPY_Dark/item/close.png"></div>
			<a href="https://www.kyoto-happy.co.jp/2021/03/18/2478/"><img src="https://www.kyoto-happy.co.jp/wp/wp-content/themes/HAPPY_Dark/img/care_line-20230825.png" alt=""></a>
		</div>
	</div>
<?php endif; ?>
<style>
	#mobile_below_banner{
		display: none;
	}
	#pc_banner_img{
		width: 100%;
		margin-bottom: -1%;
	}
@media screen and (max-width: 450px) {
	#pc_below_banner{
		display: none;
	}
	#mobile_below_banner{
		display: inline;
		max-width: 90%;
		display:block;
        margin:auto;
		margin-top: 5% !important;
	}
	#mobile_banner_img{
		width: 100%;
		margin-bottom: -2.3%;
	}
	
}

</style>

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
<div class="bg">
	<section id="news" class="news-area">
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
		<h1>
			<div class="new-top-on top-new-area" style="margin-top:20px;">
				<p class="fcw top-f">クリーニングのしみ抜き、<br class="pc-none">高級クリーニングの先をゆくハッピーケアメンテ&reg;<br />クリーニングの駆け込み寺&reg;</p>
			</div>
		</h1>
		<ul class="new-banner-area">
			<li><div class="new-banner-block"><a href="<?php the_field('top-banner-link-01',3210); ?>"><img src="<?php the_field('top-benner-01',3210); ?>" alt="<?php the_field('top-benner-text-01',3210); ?>" /></a></div></li>
			<li><div class="new-banner-block"><a href="<?php the_field('top-banner-link-02',3210); ?>"><img src="<?php the_field('top-banner-02',3210); ?>" alt="<?php the_field('top-benner-text-02',3210); ?>" /></a></div></li>
			<li><div class="new-banner-block"><a href="<?php the_field('top-banner-link-03',3210); ?>"><img src="<?php the_field('top-banner-03',3210); ?>" alt="<?php the_field('top-benner-text-03',3210); ?>" /></a></div></li>
			<li><div class="new-banner-block"><a href="<?php the_field('top-banner-link-04',3210); ?>"><img src="<?php the_field('top-banner-04',3210); ?>" alt="<?php the_field('top-benner-text-04',3210); ?>" /></a></div></li>
		</ul>
		<div class="container" id="pc_below_banner">
			<div class="pc_saiful_banner">
				<a href="<?php the_field('sale-link',3210); ?>" target="_blank"><img src="<?php the_field('sale-banner',3210); ?>" alt="" /></a>
			</div>
		</div>

		<div class="container" id="mobile_below_banner">
			<div class="mobile_saiful_banner">
				<a href="<?php the_field('sale-link',3210); ?>" target="_blank"><img src="<?php the_field('sale-banner',3210); ?>" alt="" /></a>
			</div>
		</div>
		<?php if(get_post_meta(3210, 'pc-top-banner', true)): ?>
		<div class="container" id="pc_below_banner">
			<div class="pc_saiful_banner">
				<a href="<?php the_field('top-link',3210); ?>" target="_blank"><img src="<?php the_field('pc-top-banner',3210); ?>" alt="" /></a>
			</div>
		</div>
		<?php endif; ?>
		<?php if(get_post_meta(3210, 'sp-top-banner', true)): ?>
		<div class="container" id="mobile_below_banner">
			<div class="mobile_saiful_banner">
				<a href="<?php the_field('top-link',3210); ?>" target="_blank"><img src="<?php the_field('sp-top-banner',3210); ?>" alt="" /></a>
			</div>
		</div>
		<?php endif; ?>
	</section>
	<section class="service pd00 sppt30">
		<h2 class="tac-top">＼衣服やクリーニングのお悩みなど、お気軽にご相談ください ／</h2>
	</section>
	<div class="service900">
		<div class="order-useL">
			<a href="tel:0120-88-6868"><img src="https://www.kyoto-happy.co.jp/wp/wp-content/themes/HAPPY_Dark/img/tel_sp-ver2.png"></a>
		</div>
		<div class="order-useR">
			<a href="/order/form.html"><img src="https://www.kyoto-happy.co.jp/wp/wp-content/themes/HAPPY_Dark/img/net_ver.png"></a>
		</div>
		<div class="order-useL">
			<a href="/contact/"><img src="https://www.kyoto-happy.co.jp/wp/wp-content/themes/HAPPY_Dark/img/mail_ver.png"></a>
		</div>
		<div class="order-useR">
			<a href="tel:0120-88-3040" class="hermes-button">Hermes（エルメス）お客様専用ダイヤル<br />0120-88-3040</a>
		</div>
		<br clear="all">
		<div class="textArea">
			テレ東/カンブリア宮殿・WBS、NHK/ルソンの壺・ためしてガッテン、TBS/がっちりマンデー、テレ朝/報道ステーション・ナイトスクープ、フジ/アゲるテレビ、日テレ/ミヤネ屋などなど、日経新聞/社説、その他情報誌、書籍で100以上のメディアで紹介されています…詳しくは<a href="https://www.kyoto-happy.co.jp/corporate/media/past/">コチラ</a>。
		</div>
	</div>
	<section class="service sppt30">
		<div class="container">
			<h2 class="tac">ケアメンテBefore&Afterの技術</h2>
			<div class="float-L">
				<div class="check-text">● <?php the_field('top-ba-01-text',3210); ?> ●</div>
				<img src="<?php the_field('top-ba-01-img',3210); ?>">
			</div>
			<div class="float-R">
				<div class="check-text">● <?php the_field('top-ba-02-text',3210); ?> ●</div>
				<img src="<?php the_field('top-ba-02-img',3210); ?>">
			</div>
			<br clear="all" class="sp-none">
			<div class="float-C">
				<div class="check-text">● <?php the_field('top-ba-03-text',3210); ?> ●</div>
				<img src="<?php the_field('top-ba-03-img',3210); ?>">
			</div>
			<div class="area-form-button"><a href="https://www.kyoto-happy.co.jp/carementeh_search/form.html" class="form-button" target="_blank"><div class="form-button-info">お悩みごと・困りごとを解決します</div>2100点を超える<br />ケアメンテBefore＆After実例集<div class="form-button-info">お客様の許可を得て掲載しております</div></a></div>
		</div>
	</section>
	<section id="technology">
		<div class="container">
			<div class="technology_pv">
				<h2 class="tac">動画で分かる！<br class="sp">驚きのケアメンテ&reg;サービス</h2>
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
					<div class="btn"><img class="sp-slider-none" src="https://www.kyoto-happy.co.jp/wp/wp-content/themes/HAPPY_Dark/img/youtube.png" alt="youtube" class="youtube_logo" width="90" height="21"><a href="https://www.youtube.com/channel/UCZyJC69VvnDqIAgsEQ-rTeQ">チャンネル登録はこちら</a>
					</div>
					<div class="btn btn-lh32">
						<a href="/movie/">ハッピープロモーション動画を見る</a>
					</div>
				</div>

			</div>

		</div>
	</section>
	<!--　/#technology -->
	<section id="partner">
		<div class="container">
			<h2 class="tac">ラグジュアリーブランド・デパートの<br class="sp">ファッションを<br class="pc">サポートする</h2>
			<div class="partner-01">クリーニングの駆け込み寺&reg;<br class="sp">「ハッピーケアメンテ&reg;」</div>
			<p class="color-bl">日本の三大セレクトショップ、ラグジュアリーブランド、デパートなど、<br class="pc">ケアメンテ&reg;を推奨する業務提携先と「いい服長持ち」に取り組んでいます。</p>
			<div class="sp partner-img"><img src="<?php echo get_stylesheet_directory_uri(); ?>/img/partner_sp.jpg" alt="ラグジュアリーブランド・デパートのファッションをサポートするハッピーケアメンテ"></a></div>
			<div class="partner-02">業務提携先</div>
			<div class="sptc"><p>全国約200店舗でお預かりしています。<br />ご利用特典・取扱い店舗などの詳細は<br class="sp">下記アイコンをクリックしてください。<br />皆様のご来店を心よりお待ちしております。</p></div>
			<ul class="tac">
				<li><a href="/shop/brand/tomorrowland/">
					<img src="<?php echo get_stylesheet_directory_uri(); ?>/img/partner_logo_01.png" alt="TOMORROWLAND"></a>
				</li>
				<li><a href="/shop/brand/beams/">
					<img src="<?php echo get_stylesheet_directory_uri(); ?>/img/partner_logo_02.png" alt="BEAMS"></a>
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
					<span class="hermes-L">Hermes（エルメス）お客様専用ダイヤル</span><br class="sp"><span class="hermes-R">0120-88-3040</span></a>
				</div>
			</div>
		</div>
	</section>
	<!--　/#partner -->
	<section class="service pcmt00">
		<div class="container">
			<div class="check-text-02">● 基本洗浄（基本料金）『アクアドライ&reg;』 ●</div>
			<div class="top-fee-tax">【価格一例（税込）】</div>
			<table class="table-top-fee">
				<tr>
					<td class="sp-block">
						<table class="table-fee">
							<tr>
								<th><img src="<?php the_field('fee-img-01',3210); ?>" alt="<?php the_field('fee-text-01',3210); ?>" /></th>
								<td><?php the_field('fee-text-01',3210); ?></td>
								<td class="table-fee-en">￥<?php the_field('fee-01',3210); ?></td>
							</tr>
						</table>
					</td>
					<td class="sp-block">
						<table class="table-fee">
							<tr>
								<th><img src="<?php the_field('fee-img-02',3210); ?>" alt="<?php the_field('fee-text-02',3210); ?>" /></th>
								<td><?php the_field('fee-text-02',3210); ?></td>
								<td class="table-fee-en">￥<?php the_field('fee-02',3210); ?></td>
							</tr>
						</table>
					</td>
				</tr>
				<tr>
					<td class="sp-block">
						<table class="table-fee">
							<tr>
								<th><img src="<?php the_field('fee-img-03',3210); ?>" alt="<?php the_field('fee-text-03',3210); ?>" /></th>
								<td><?php the_field('fee-text-03',3210); ?></td>
								<td class="table-fee-en">￥<?php the_field('fee-03',3210); ?></td>
							</tr>
						</table>
					</td>
					<td class="sp-block">
						<table class="table-fee">
							<tr>
								<th><img src="<?php the_field('fee-img-04',3210); ?>" alt="<?php the_field('fee-text-04',3210); ?>" /></th>
								<td><?php the_field('fee-text-04',3210); ?></td>
								<td class="table-fee-en">￥<?php the_field('fee-04',3210); ?></td>
							</tr>
						</table>
					</td>
				</tr>
				<tr>
					<td class="sp-block">
						<table class="table-fee">
							<tr>
								<th><img src="<?php the_field('fee-img-05',3210); ?>" alt="<?php the_field('fee-text-05',3210); ?>" /></th>
								<td><?php the_field('fee-text-05',3210); ?></td>
								<td class="table-fee-en">￥<?php the_field('fee-05',3210); ?></td>
							</tr>
						</table>
					</td>
					<td class="sp-block">
						<table class="table-fee">
							<tr>
								<th><img src="<?php the_field('fee-img-06',3210); ?>" alt="<?php the_field('fee-text-06',3210); ?>" /></th>
								<td><?php the_field('fee-text-06',3210); ?></td>
								<td class="table-fee-en">￥<?php the_field('fee-06',3210); ?></td>
							</tr>
						</table>
					</td>
				</tr>
				<tr>
					<td class="sp-block">
						<table class="table-fee">
							<tr>
								<th><img src="<?php the_field('fee-img-07',3210); ?>" alt="<?php the_field('fee-text-07',3210); ?>" /></th>
								<td><?php the_field('fee-text-07',3210); ?></td>
								<td class="table-fee-en">￥<?php the_field('fee-07',3210); ?></td>
							</tr>
						</table>
					</td>
					<td class="sp-block">
						<table class="table-fee">
							<tr>
								<th><img src="<?php the_field('fee-img-08',3210); ?>" alt="<?php the_field('fee-text-08',3210); ?>" /></th>
								<td><?php the_field('fee-text-08',3210); ?></td>
								<td class="table-fee-en">￥<?php the_field('fee-08',3210); ?></td>
							</tr>
						</table>
					</td>
				</tr>
				<tr>
					<td class="sp-block">
						<table class="table-fee">
							<tr>
								<th><img src="<?php the_field('fee-img-09',3210); ?>" alt="<?php the_field('fee-text-09',3210); ?>" /></th>
								<td><?php the_field('fee-text-09',3210); ?></td>
								<td class="table-fee-en">￥<?php the_field('fee-09',3210); ?></td>
							</tr>
						</table>
					</td>
					<td class="sp-block">
						<table class="table-fee">
							<tr>
								<th><img src="<?php the_field('fee-img-10',3210); ?>" alt="<?php the_field('fee-text-10',3210); ?>" /></th>
								<td><?php the_field('fee-text-10',3210); ?></td>
								<td class="table-fee-en">￥<?php the_field('fee-10',3210); ?></td>
							</tr>
						</table>
					</td>
				</tr>
				<tr>
					<td class="sp-block">
						<table class="table-fee">
							<tr>
								<th><img src="<?php the_field('fee-img-11',3210); ?>" alt="<?php the_field('fee-text-11',3210); ?>" /></th>
								<td><?php the_field('fee-text-11',3210); ?></td>
								<td class="table-fee-en">￥<?php the_field('fee-11',3210); ?></td>
							</tr>
						</table>
					</td>
					<td class="sp-block"><div class="fee-text">※シミ汚れ落とし、黄ばみ取り他、追加オプションは別料金です。<br />　詳しくは状態を拝見してお見積りいたします。</div></td>
				</tr>
			</table>
			<div class="pricelist-button"><a href="https://www.kyoto-happy.co.jp/use/price/pricelist/" class="arrow-button" target="_blank">詳しい料金表はコチラ</a></div>
		</div>
	</section>
	<section class="news-area" style="text-align:center;">
<h1>
	<div class="new-top-on top-new-area">
		<p class="fcw top-f">失敗しない「ハッピーケアメンテ&reg;」…高級、宅配クリーニングの失敗で、お客様からクリーニングの駆け込み寺・高級クリーニングの先をゆく「ハッピーケアメンテ&reg;」への相談、依頼が増えていますが、高級、宅配クリーニングの失敗を「ハッピーケアメンテ&reg;」で解決してお客様に喜ばれています。<a href="https://www.kyoto-happy.co.jp/nofailures/">続きはコチラ</a></p>
		<br />
		<p>クリーニングは、シミ・汚れ・黄ばみ・変色、風合いをキレイに「出来ない」ので、衣類・衣服の寿命が短命化して「困っている」という難題を多くの消費者から相談を受けて、「ハッピーケアメンテ&reg;」は、キレイに「出来る」洗浄技術で新品同様を維持し、衣類・衣服を長命化して百年単位で着続けられるようにしました。それがクリーニングの駆け込み寺「ハッピーケアメンテ&reg;」の真価です。つまり、お洒落なファッションを思う存分楽しめる高級クリーニングの先をゆく「ハッピーケアメンテ&reg;」です...<a href="https://www.kyoto-happy.co.jp/keepclothes/">続きはコチラ</a></p>
	</div>
</h1>

		<?php if(get_post_meta(3871, 'top-img-banner', true)): ?>
		<div class="container" id="pc_below_banner" style="margin-top:30px">
			<div class="pc_saiful_banner">
				<a href="https://www.kyoto-happy.co.jp/difference2/"><img src="<?php the_field('top-img-banner',3871); ?>" alt="クリーニングとケアメンテの違い…ここが知りたい" /></a>
			</div>
		</div>
		<?php endif; ?>
		<?php if(get_post_meta(3871, 'top-img-banner', true)): ?>
		<div class="container" id="mobile_below_banner">
			<div class="mobile_saiful_banner">
				<a href="https://www.kyoto-happy.co.jp/difference2/"><img src="<?php the_field('top-img-banner',3871); ?>" alt="クリーニングとケアメンテの違い…ここが知りたい" /></a>
			</div>
		</div>
		<?php endif; ?>


		<?php if(get_post_meta(3826, 'top-img-banner', true)): ?>
		<div class="container <?php if(get_post_meta(3871, 'top-img-banner', true)): ?>pc_mt20<?php endif; ?>" id="pc_below_banner">
			<div class="pc_saiful_banner">
				<a href="https://www.kyoto-happy.co.jp/merchandising/"><img src="<?php the_field('top-img-banner',3826); ?>" alt="ハイ・ブランド服飾品のマーチャンダイジングが変わる" /></a>
			</div>
		</div>
		<?php endif; ?>
		<?php if(get_post_meta(3826, 'top-img-banner', true)): ?>
		<div class="container" id="mobile_below_banner">
			<div class="mobile_saiful_banner <?php if(get_post_meta(3871, 'top-img-banner', true)): ?>sp_mt<?php endif; ?>">
				<a href="https://www.kyoto-happy.co.jp/merchandising/"><img src="<?php the_field('top-img-banner',3826); ?>" alt="ハイ・ブランド服飾品のマーチャンダイジングが変わる" /></a>
			</div>
		</div>
		<?php endif; ?>

		<?php if(get_post_meta(3757, 'top-img-banner', true)): ?>
		<div class="container <?php if(get_post_meta(3826, 'top-img-banner', true)): ?>pc_mt20<?php endif; ?>" id="pc_below_banner">
			<div class="pc_saiful_banner">
				<a href="https://www.kyoto-happy.co.jp/real_value/"><img src="<?php the_field('top-img-banner',3757); ?>" alt="本物の「真・価値」創造" /></a>
			</div>
		</div>
		<?php endif; ?>
		<?php if(get_post_meta(3757, 'top-img-banner', true)): ?>
		<div class="container" id="mobile_below_banner">
			<div class="mobile_saiful_banner <?php if(get_post_meta(3826, 'top-img-banner', true)): ?>sp_mt<?php endif; ?>">
				<a href="https://www.kyoto-happy.co.jp/real_value/"><img src="<?php the_field('top-img-banner',3757); ?>" alt="本物の「真・価値」創造" /></a>
			</div>
		</div>
		<?php endif; ?>

		<?php if(get_post_meta(3210, 'infomag-banner', true)): ?>
		<div class="container pc_mt20" id="pc_below_banner">
			<div class="pc_saiful_banner">
				<a href="<?php the_field('infomag-link',3210); ?>" target="_blank"><img src="<?php the_field('infomag-banner',3210); ?>" alt="Happyケアメンテ通信" /></a>
			</div>
		</div>
		<?php endif; ?>
		<?php if(get_post_meta(3210, 'infomag-banner', true)): ?>
		<div class="container" id="mobile_below_banner">
			<div class="mobile_saiful_banner sp_mt">
				<a href="<?php the_field('infomag-link',3210); ?>" target="_blank"><img src="<?php the_field('infomag-banner',3210); ?>" alt="Happyケアメンテ通信" /></a>
			</div>
		</div>
		<?php endif; ?>
	</section>

	<section class="service service2" id="use">
		<h2 class="tac">ケアメンテ&reg;ってなに？</h2>
		<div class="new-top-concept tltl">
			クリーニングの限界を解消した「ケアメンテ&reg;」とは、どのようなサービスなのか。
		</div>
		<ul class="service2_list">
			<li>
				<div class="itemBox">
					<a href="https://www.kyoto-happy.co.jp/carementeh/overview/difference/">
					<img src="<?php echo get_stylesheet_directory_uri(); ?>/img/top-difference.jpg" alt="クリーニングとケアメンテ&reg;の違い">
					<div class="technology_txt">
						<h4>クリーニングとケアメンテ&reg;の違い</h4>
						<p>ハッピーが「クリーニングの駆け込み寺」と呼ばれるワケ</p>
					</div>
					</a>
				</div>

			</li>
			<li>
				<div class="itemBox">
					<a href="https://www.kyoto-happy.co.jp/corporate/csr/reuse/">
					<img src="<?php echo get_stylesheet_directory_uri(); ?>/img/top-change.jpg" alt="ケアメンテ&reg;で地球環境を守る">
					<div class="technology_txt">
						<h4>自然災害を減らす「ケアメンテ&reg;」</h4>
						<p>資源・自然循環型の「いい服長持ち&reg;/捨てられない」を推進しています</p>
					</div>
					</a>
				</div>
			</li>
			<li>
				<div class="itemBox">
					<a href="https://www.kyoto-happy.co.jp/carementeh/overview/style/">
					<img src="<?php echo get_stylesheet_directory_uri(); ?>/img/top-style.jpg" alt="ハッピーケアメンテの仕事スタイル">
					<div class="technology_txt">
						<h4>ハッピーケアメンテの仕事スタイル</h4>
						<p>クリーニングの限界を解消した「ハッピーケアメンテ&reg;」の仕事への取り組み</p>
					</div>
					</a>
				</div>
			</li>
		</ul>
	</section>

	<section id="technology-2">
		<div class="container">
			<h2 class="tac">ケアメンテ&reg;を支える<br class="sp">テクノロジー</h2>
			<div class="tac">
				<p>愛着ある大切な服飾品を新品同様の状態で、長く着用・愛用し続けるために開発された世界初の独自技術</p>
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
	<section class="service mt0">
		<div class="container">
			<h2 class="tac">ケアメンテ&reg;技術の検証データ</h2>
			<div class="banner mt30">
				<a href="https://www.kyoto-happy.co.jp/technology/data/weightlessness/ma_test/">
					<img src="https://www.kyoto-happy.co.jp/wp/wp-content/themes/HAPPY_Dark/img/service_data.jpg" alt="ケアメンテ&reg;技術の検証データ">
					<div class="banner_txt">
						<h2>ケアメンテ&reg; 技術エビデンス</h2>
						<p>海外の研究機関・大学でも評価されている<br class="sp">ハッピーの技術を<br />科学的根拠に基づいてご案内しています。</p>
					</div>
				</a>
			</div>
		</div>
	</section>
	<section id="service">
		<div class="container">
			<h2 class="tac">ハッピーだけの安心サービス</h2>
			<div class="tac">
				<p>お気に入りのアイテムを永くご愛用いただくために、<br class="pc">お客様の思いとしっかり向き合い、安心してご利用いただけるサービスをご提供いたします。</p>
			</div>
			<ul class="service_list">
				<li>
					<img src="https://www.kyoto-happy.co.jp/wp/wp-content/themes/HAPPY_Dark/img/service01.jpg" alt="全業務を一元管理する「電子カルテ」">
					<h4><img src="https://www.kyoto-happy.co.jp/wp/wp-content/themes/HAPPY_Dark/img/service_tit01.png" alt="全業務を一元管理する「電子カルテ」" width="65" height="285"></h4>
					<div class="service_list_link"><a href="/carementeh/overview/karte/">ハッピー電子カルテシステム</a></div>
				</li>
				<li>
					<img src="https://www.kyoto-happy.co.jp/wp/wp-content/themes/HAPPY_Dark/img/service05.jpg" alt="お客様のお困りの声にじっくりと耳を傾ける">
					<h4><img src="https://www.kyoto-happy.co.jp/wp/wp-content/themes/HAPPY_Dark/img/service_tit05.png" alt="お客様のお困りの声にじっくりと耳を傾ける" width="65" height="284"></h4>
					<div class="service_list_link"><a href="/carementeh/overview/counseling/">カウンセリング</a></div>
				</li>
				<li>
					<img src="https://www.kyoto-happy.co.jp/wp/wp-content/themes/HAPPY_Dark/img/service02.jpg" alt="服は息をしている保管お預かりサービス">
					<h4><img src="https://www.kyoto-happy.co.jp/wp/wp-content/themes/HAPPY_Dark/img/service_tit02.png" alt="服は息をしている保管お預かりサービス" width="65" height="284"></h4>
					<div class="service_list_link"><a href="/carementeh/service/wardrobe/">保管お預りハッピーワードローブ&reg;</a></div>
				</li>
				<li>
					<img src="https://www.kyoto-happy.co.jp/wp/wp-content/themes/HAPPY_Dark/img/service06.jpg" alt="美しいシルエットのまま大切にお届けする">
					<h4><img src="https://www.kyoto-happy.co.jp/wp/wp-content/themes/HAPPY_Dark/img/service_tit06.png" alt="美しいシルエットのまま大切にお届けする" width="65" height="285"></h4>
					<div class="service_list_link"><a href="/use/howtoorder/package/">配送パッケージ</a></div>
				</li>
			</ul>
		</div>
		<div class="container">
			<div class="service900 sp-slider-none">
				<div class="order-useL">
					<a href="/contact/"><img src="https://www.kyoto-happy.co.jp/wp/wp-content/themes/HAPPY_Dark/img/mail_ver.png"></a>
				</div>
				<div class="order-useR">
					<a href="/use/price/catalog/"><img src="https://www.kyoto-happy.co.jp/wp/wp-content/themes/HAPPY_Dark/img/cate_ver.png"></a>
				</div>
				<div class="order-useL">
					<a href="tel:0120-88-6868"><img src="https://www.kyoto-happy.co.jp/wp/wp-content/themes/HAPPY_Dark/img/tel_sp-ver2.png"></a>
				</div>
				<div class="order-useR">
					<a href="/order/form.html"><img src="https://www.kyoto-happy.co.jp/wp/wp-content/themes/HAPPY_Dark/img/net_ver.png"></a>
				</div>
			</div>
		</div>
		<div class="service900 pc-slider-none">
			<div class="order-useL">
				<a href="tel:0120-88-6868"><img src="https://www.kyoto-happy.co.jp/wp/wp-content/themes/HAPPY_Dark/img/tel_sp-ver2.png"></a>
			</div>
			<div class="order-useL">
				<a href="/contact/"><img src="https://www.kyoto-happy.co.jp/wp/wp-content/themes/HAPPY_Dark/img/mail_ver.png"></a>
			</div>
			<div class="order-useR">
				<a href="/use/price/catalog/"><img src="https://www.kyoto-happy.co.jp/wp/wp-content/themes/HAPPY_Dark/img/cate_ver.png"></a>
			</div>
			<div class="order-useR">
				<a href="/order/form.html"><img src="https://www.kyoto-happy.co.jp/wp/wp-content/themes/HAPPY_Dark/img/net_ver.png"></a>
			</div>
		</div>
	</section>
	<!--　/#service -->
	<section id="member">
		<div class="container">
			<h2 class="tac">
				＼お得に、便利に／<br />
				マイページ会員のご案内
			</h2>
			<p class="tltl">Happyケアメンテ&reg;をもっとお得に、もっと便利にお使いいただけるマイページ会員募集中。</p>
			<ul>
				<li>
					<a href="https://www.kyoto-happy.co.jp/sale/">
						<img src="<?php echo get_stylesheet_directory_uri(); ?>/img/member01.png" alt="セール情報">
						<h3>セール情報</h3>
						<p>マイページ会員だけの<br>
							お得なセール情報を<br>
							ご案内します</p>
					</a>
				</li>
				<li>
					<a href="https://www.kyoto-happy.co.jp/order/form.html">
						<img src="<?php echo get_stylesheet_directory_uri(); ?>/img/member02.png" alt="簡単注文">
						<h3>簡単注文</h3>
						<p>ケアメンテ&reg;の<br>
							お申し込みを大幅に<br>
							簡略化できます</p>
					</a>
				</li>
				<li>
					<a href="https://www.kyoto-happy.co.jp/mypage/sns.html">
						<img src="<?php echo get_stylesheet_directory_uri(); ?>/img/member03.jpg" alt="ハッピー SNS">
						<h3>「つなぐ」</h3>
						<p>他のお客様とフレンドに<br>
							なったり共通の話題で<br>
							盛り上がろう</p>
					</a>
				</li>
				<li>
					<a href="https://www.kyoto-happy.co.jp/mypage/">
						<img src="<?php echo get_stylesheet_directory_uri(); ?>/img/member04.png" alt="MyPage">
						<h3>MyPage</h3>
						<p>注文や履歴、<br>
							ケアメンテ&reg;のカルテなど<br>
							いつでも確認</p>
					</a>
				</li>
			</ul>
			<div class="btnArea">
				<div class="btn btn230">
					<a href="/mypageuse/use_mypage/">マイページについて詳しくは</a>
				</div>
				<div class="btn btn230">
					<a href="/entry/">会員登録をする</a>
				</div>
				<div class="login">
					<a href="/mypage/">既に会員の方はこちらからログイン</a>
				</div>
			</div>
		</div>
	</section>
	<!--　/#member -->
	<section id="app">
		<div class="container">
			<h3 class="tac">スマホアプリでもっと便利に</h3>
			<div class="appBox">
				<div class="app_img"><img src="app/img/app_img.png" alt="ケアメンテ"></div>
				<div class="app_txt">
					<h2><img src="https://www.kyoto-happy.co.jp/wp/wp-content/themes/HAPPY_Dark/img/app_icon.png" alt="ケアメンテ">ハッピーケアメンテ</h2>
					<div class="app_store"><img src="https://www.kyoto-happy.co.jp/wp/wp-content/themes/HAPPY_Dark/img/app_store.png" alt="Apple Android"></div>
					<p>ケアメンテアプリは、ケアメンテ事例集「さがす」や、ご依頼品のご注文、<br class="pc">マイページでケアメンテご依頼品のご利用履歴の確認や電子カルテの閲覧など、<br class="pc">お手持ち衣類の管理ツールとしてもご活用いただける便利なアプリです。</p>
					<div class="moreBtn">
						<div class="btn">
							<a href="/app/">機能紹介はこちら</a>
						</div>
					</div>
					<div class="btnArea">
						<div class="btn">
							<a href="https://apps.apple.com/jp/app/%E3%83%8F%E3%83%83%E3%83%94%E3%83%BC%E3%82%B1%E3%82%A2%E3%83%A1%E3%83%B3%E3%83%86/id1537339559?l=ja&ls=1&mt=8">iPhone版</a>
						</div>
						<div class="btn">
							<a href="https://play.google.com/store/apps/details?id=jp.happy.CareMenteh">Android版</a>
						</div>
					</div>
				</div>
			</div>
		</div>
	</section>
	<!--　/#app -->
	<section class="service mt0">
		<div class="container">
			<h2 class="tac">ケアメンテ&reg;で実現する<br class="con-br">「脱炭素社会＝カーボンゼロ」</h2>
			<div class="tac">
				<p style="text-align:center;">
					「着捨てる・使い捨てる服飾文化」から<br class="con-br">「愛用・着用し続ける服飾文化」へ<br />異常気象に歯止めをかけるために、<br class="con-br">脱炭素社会＝カーボンゼロへの取組みを<br class="con-br">改めて宣言します。
				</p>
			</div>
			<div class="banner mt30">
				<a href="/corporate/csr/reuse/">
					<img src="https://www.kyoto-happy.co.jp/wp/wp-content/themes/HAPPY_Dark/img/service_bnr.jpg" alt="自然循環型産業の創出">
					<div class="banner_txt">
						<h2>自然循環型産業の創出</h2>
						<p>「ハッピーケアメンテ&reg;」は、<br class="sp">良い服／良いモノを<br>長もちさせる究極の“自然循環型産業”です</p>
					</div>
				</a>
			</div>
		</div>
	</section>
	<!--　/#service -->
	<section class="service saiful-area">
		<div class="container">
			<div class="banner sp-saiful-banner">
				<table class="saiful-table">
					<tr>
						<td>
							<a href="<?php the_field('saiful-link',3210); ?>" target="_blank"><img src="<?php the_field('L-saiful-banner',3210); ?>" alt="HAPPYサイフル" /></a>
						</td>
						<td class="saiful-area">
							<div class="saiful-title"><?php the_field('R-saiful-title',3210); ?></div>
							<div class="saiful-text"><?php the_field('R-saiful-text',3210); ?> <a href="<?php the_field('R-saiful-link',3210); ?>" target="_blank">続きはコチラ＞</a></div>
						</td>
					</tr>
				</table>
			</div>
		</div>
	</section>
	<div class="order-text-block">
		<div class="order-text-02"><a href="https://www.kyoto-happy.co.jp/corporate/csr/sdgsdx/">SDGs・DX・GX・ESGの「一本の道」を歩み続ける
		<div class="dx-sdgs"><img src="<?php echo get_stylesheet_directory_uri(); ?>/img/top-dx-2022.jpg" alt="DX認定" /><img src="<?php echo get_stylesheet_directory_uri(); ?>/img/top-sdgs-2022.jpg" alt="SDGSへの取り組み" /></div>
		<div class="order-text-icon"><i class="fa fa-chevron-down"></i></div>
		</a></div>
	</div>
	<div class="service900">
		<div class="order-useL">
			<a href="tel:0120-88-6868"><img src="https://www.kyoto-happy.co.jp/wp/wp-content/themes/HAPPY_Dark/img/tel_sp-ver2.png"></a>
		</div>
		<div class="order-useR">
			<a href="/order/form.html"><img src="https://www.kyoto-happy.co.jp/wp/wp-content/themes/HAPPY_Dark/img/net_ver.png"></a>
		</div>
	</div>
	<section class="service">
		<div class="container">
			<h2 class="tac">第三者評価</h2>
			<div class="tac">
				<p>ハッピーは公的機関の認定を受けています。</p>
			</div>
			<div class="technology_award">
				<ul>
					<li><img src="https://www.kyoto-happy.co.jp/wp/wp-content/themes/HAPPY_Dark/img/b-award07.png" alt="DX認証"></li>
					<li><img src="https://www.kyoto-happy.co.jp/wp/wp-content/themes/HAPPY_Dark/img/b-award02.png" alt="中小企業IT経営力大賞 経済産業大臣賞"></li>
					<li><img src="https://www.kyoto-happy.co.jp/wp/wp-content/themes/HAPPY_Dark/img/b-award01.png" alt="第一回「日本サービス大賞」 優秀賞（SPRING賞）受賞"></li>
					<li><img src="https://www.kyoto-happy.co.jp/wp/wp-content/themes/HAPPY_Dark/img/b-award03.png" alt="ハイ・サービス日本300選"></li>
					<li><img src="https://www.kyoto-happy.co.jp/wp/wp-content/themes/HAPPY_Dark/img/b-award04.png" alt="おもてなし経営企業選 選出企業"></li>
					<li><img src="https://www.kyoto-happy.co.jp/wp/wp-content/themes/HAPPY_Dark/img/award05.png" alt="おもてなし規格認証2016"></li>
					<li><img src="https://www.kyoto-happy.co.jp/wp/wp-content/themes/HAPPY_Dark/img/award06.png" alt="ソーシャル企業認証制度 S認証"></li>
				</ul>
			</div>
			<div class="technology_award_sp">
				<ul>
					<li><img src="https://www.kyoto-happy.co.jp/wp/wp-content/themes/HAPPY_Dark/img/b-award07.png" alt="DX認証"></li>
					<li><img src="https://www.kyoto-happy.co.jp/wp/wp-content/themes/HAPPY_Dark/img/b-award02.png" alt="中小企業IT経営力大賞 経済産業大臣賞"></li>
					<li><img src="https://www.kyoto-happy.co.jp/wp/wp-content/themes/HAPPY_Dark/img/b-award01.png" alt="第一回「日本サービス大賞」 優秀賞（SPRING賞）受賞"></li>
					<li><img src="https://www.kyoto-happy.co.jp/wp/wp-content/themes/HAPPY_Dark/img/b-award03.png" alt="ハイ・サービス日本300選"></li>
					<li><img src="https://www.kyoto-happy.co.jp/wp/wp-content/themes/HAPPY_Dark/img/b-award04.png" alt="おもてなし経営企業選 選出企業"></li>
					<li><img src="https://www.kyoto-happy.co.jp/wp/wp-content/themes/HAPPY_Dark/img/award05.png" alt="おもてなし規格認証2016"></li>
					<li><img src="https://www.kyoto-happy.co.jp/wp/wp-content/themes/HAPPY_Dark/img/award06.png" alt="ソーシャル企業認証制度 S認証"></li>
				</ul>
				<br clear="all">
			</div>
			<div class="order-useL">
				<div class="btn btn-lh32">
					<a href="/corporate/company/winning/">認定・受賞一覧</a>
				</div>
			</div>
			<div class="order-useR smb50">
				<div class="btn btn-lh32">
					<a href="/corporate/media/media_list/">メディア報道一覧</a>
				</div>
			</div>
			<br clear="all">
		</div>
	</section>
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
				<img class="lp-img" src="https://www.kyoto-happy.co.jp/wp/wp-content/themes/HAPPY_Dark/img/004-2.jpg" alt="出たわね！クリ忍軍シミ太郎！" />
			</div>
			<div class="lp-link-btn"><a class="arrow-button" href="https://www.kyoto-happy.co.jp/lp/">続きはコチラ</a></div>

		</section>
	</section>
	<!--　/#technology -->
	<br clear="all">
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
				<a href="/knowledge/">オシャレの雑学をもっと見る</a>
			</div>
		</div>
	</section>
	<!--　/#knowledge -->
	<section id="reading">
		<div class="container">
			<div class="banner">
				<a href="/sachi/">
					<img src="<?php echo get_stylesheet_directory_uri(); ?>/img/reading_bnr_sachi.jpg" alt="京の伝統工芸職人を追うWebマガジン 「幸」 -sachi-">
					<div class="banner_txt">
						<p>“技”を持つ職人達。華やかな表舞台の裏には人知れず腕を磨き精進する姿がある。職人技と呼ばれる“極み”を完成した人々、”ケアメンテ”も縁の下の力持ちに徹し、静かに”技”を研鑽している。伝統工芸の職人技とケアメンテの職人技は共通しており、それぞれの技の“極み”を発見してもらうために「幸」がある。長年に渡りご紹介してきたハッピーの季刊誌 「幸（sachi）」が、WEB版に生まれ変わり待望の復刊です。</p>
					</div>
				</a>
			</div>
			<div class="banner">
				<a href="https://www.kyoto-happy.co.jp:8443/pdf/Manga.pdf?ver1.1">
					<img src="<?php echo get_stylesheet_directory_uri(); ?>/img/reading_bnr_comic.jpg" alt="マンガで分かる「ケアメンテサービス」">
					<div class="banner_txt">
						<h2>マンガで分かる<br><span class="indent">「ケアメンテサービス」</span></h2>
						<p>ケアメンテであなたのファッションライフが変わる</p>
					</div>
				</a>
			</div>
		</div>
	</section>
	<!--　/#reading -->


	<?php get_template_part( 'shared/front-bottom-2' ); ?>
	<?php get_footer(); ?>
