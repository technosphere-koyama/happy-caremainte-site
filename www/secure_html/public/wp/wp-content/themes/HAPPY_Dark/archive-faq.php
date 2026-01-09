<?php get_header(); ?>

<div id="Contents">
	<div class="mainvisual__section">
		<div>FAQ<br><p>よくあるご質問</p></div>
	</div>

	<?php breadcrumb(); ?>

	<div class="content">
		<div class="LColumn">
			<div class="pagettl"><h1>よくあるご質問</h1></div>
			<div class="pagettl-sub"></div>
			<p>皆さまからよくいただくご質問をまとめました。</p>
			<!--<ul class="faqlist">
		 <li><a href="#order-about">ご注文に<br class="sp-br">ついて</a></li>
		 <li><a href="#care-about">ケアメンテに<br class="sp-br">ついて</a></li>
		 <li><a href="#happy-about">ハッピーに<br class="sp-br">ついて</a></li>
		 </ul>-->
		 <h2 id="order-about">ご注文について</h2>
		 <ul class="faq-detail">

			 <?php if(have_posts()): while(have_posts()): the_post(); ?>
			 <li class="q-list"><?php the_field('faq_Q') ?></li>
			 <li class="a-list"><?php the_field('faq_A') ?></li>
			 <?php endwhile; endif; ?>

		 </ul>
		</div>	

		<div class="Ltwitter">
			<div class="Ltwitter-banner">
				<h3>ハッピー公式Twitter</h3>
				<p>
				こちらのページで紹介されていないご質問などがありましたら、ハッピー公式ツイッターでお気軽にお問い合わせください。
				</p>
			</div>
			<a href="https://twitter.com/Happy_KYOTO" target="_blank">ハッピー公式Twitterを開く</a>
		</div>

	</div><!--/content--> 

</div><!--/Contents--> 

<?php get_footer(); ?>
