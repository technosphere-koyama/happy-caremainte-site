<?php get_header(); ?>
<section id="banner">
	<div class="container">
		<p>カルテの作成が完了しました。カウンセリングからご確認くださいませ。</p>
	</div>
</section>
<!--　/#banner -->

<section id="member_point">
	<div class="container tac">
		<div class="member_point_box">
			<div class="member_point_box_inner">
				<h2>ポイント</h2>
				<p class="member_point_data"><span>25</span>/50</p>
				<p class="member_point_rank">GOLD</p>
			</div>
			<canvas id="DoughnutChart"></canvas>
		</div>
		<p class="member_point_ticket">使用可能な1,000円分チケット<span>1</span>枚</p>
	</div>
</section>
<!--　/#member_point -->
		
<section id="member_information">
	<div class="container">
		<div class="member_information_box">
			<div class="member_information_name">
				<img src="<?php echo get_stylesheet_directory_uri(); ?>/img/user.png" alt="USER">
				<div class="member_information_name_txt">
					<h2>USER NAME <span>様</span></h2>
					<p>お客様番号：<span>000000</span></p>
				</div>
			</div>
		</div>
		<div class="btnArea">
			<div class="btn">
				<a href=""><img src="<?php echo get_stylesheet_directory_uri(); ?>/img/mypage03.png" alt="セール情報（会員ご優待）"><span>セール情報<br><span class="small">（会員ご優待）</span></span></a>
			</div>
			<div class="order">
				<a href=""><img src="<?php echo get_stylesheet_directory_uri(); ?>/img/order.png" alt="お申し込み"><span>お申し込み</span></a>
			</div>
		</div>
	</div>
</section>
<!--　/#member_information -->

<section id="member_menu">
	<div class="container">
		<ul>
			<li>
				<div class="member_menu_img">
					<img src="<?php echo get_stylesheet_directory_uri(); ?>/img/mypage01.png" alt="カウンセリング">
					<span class="badge">1</span>
				</div>
				<h3>カウンセリング</h3>
			</li>
			<li>
				<div class="member_menu_img">
					<img src="<?php echo get_stylesheet_directory_uri(); ?>/img/mypage02.png" alt="ただいまのお預かり品">
				</div>
				<h3>ただいまの<br>お預かり品</h3>
			</li>
			<li>
				<div class="member_menu_img">
					<img src="<?php echo get_stylesheet_directory_uri(); ?>/img/mypage03.png" alt="過去のケアメンテご利用履歴">
				</div>
				<h3>過去のケアメンテ<br>ご利用履歴</h3>
			</li>
			<li>
				<div class="member_menu_img">
					<img src="<?php echo get_stylesheet_directory_uri(); ?>/img/mypage04.png" alt="ワードローブ お預かり品">
				</div>
				<h3>ワードローブ<br>お預かり品</h3>
			</li>
		</ul>
	</div>
</section>
<!--　/#member_menu -->

<section id="member_menu_sub">
	<div class="container">
		<ul>
			<li><a href="">登録情報の変更</a></li>
			<li><a href="">事故賠償制度</a></li>
			<li><a href="">マイページの操作方法</a></li>
		</ul>
	</div>
</section>
<!--　/#member_menu_sub -->

<section id="case">
	<div class="container">
		<!-- <div class="case_top"><img src="<?php echo get_stylesheet_directory_uri(); ?>/img/header01_w.png" alt="さがす"><br>さがす</div> -->
		<h2><span>Before & After 実例集</span>ケアメンテ®️の実例をチェック</h2>
		<p class="tit_txt">クリーニングで取れなかったシミ汚れを<br class="sp">キレイにする。<br>
		Before & After実例集から検索して<br class="sp">仕上がり感をイメージできます。</p>
		<ul class="slick_case_list">
			<li>
				<img src="/_assets/wp/dummy/case01.png" alt="case01">
				<div class="case_list_txt">
					<h3>MOGA<span>婦人ジャケット</span></h3>
					<p>ﾚｰﾖﾝ82% ｼﾙｸ10% ﾎﾟﾘｴｽﾃﾙ4% ｷｭﾌﾟﾗ4%<br>
						緑系チェック</p>
				</div>
			</li>
			<li>
				<img src="/_assets/wp/dummy/case02.png" alt="case02">
				<div class="case_list_txt">
					<h3>NARACAMICIE<span>長袖ブラウス</span></h3>
					<p>綿50% ﾎﾟﾘｴｽﾃﾙ50%<br><br>白系ストライプ</p>
				</div>
			</li>
			<li>
				<img src="/_assets/wp/dummy/case03.png" alt="case03">
				<div class="case_list_txt">
					<h3>BAZAR<span>婦人上着</span></h3>
					<p>ｳｰﾙ90% ﾅｲﾛﾝ10%<br><br>茶系チェック</p>
				</div>
			</li>
			<li>
				<img src="/_assets/wp/dummy/case04.png" alt="case04">
				<div class="case_list_txt">
					<h3>MONCLER<span>ダウンコート</span></h3>
					<p>ﾅｲﾛﾝ100%<br><br>紫系</p>
				</div>
			</li>
			<li>
				<img src="/_assets/wp/dummy/case01.png" alt="case01">
				<div class="case_list_txt">
					<h3>MOGA<span>婦人ジャケット</span></h3>
					<p>ﾚｰﾖﾝ82% ｼﾙｸ10% ﾎﾟﾘｴｽﾃﾙ4% ｷｭﾌﾟﾗ4%<br>
						緑系チェック</p>
				</div>
			</li>
		</ul>
		<div class="btn">
			<a href="">事例集をもっと見る</a>
		</div>
	</div>
</section>
<!--　/#case -->

<section id="reading">
	<div class="container">
		<div class="banner">
			<a href="">
				<img src="<?php echo get_stylesheet_directory_uri(); ?>/img/reading_bnr_sachi.jpg" alt="京の伝統工芸職人を追うWebマガジン 「幸」 -sachi-">
				<div class="banner_txt">
					<h2>京の伝統工芸職人を追う<span class="small">Vol. 25<br class="pc">中村藤𠮷本店</span>
						<br><span>Webマガジン 「幸」 -sachi-</span></h2>
					<p>甘味や旨味の中に「苦渋味」を感じる<br>
					お茶本来の味わいを楽しんでほしい</p>
				</div>
			</a>
		</div>
	</div>
</section>
<!--　/#reading -->		

<section id="member_sns">
	<div class="container">
		<div class="member_sns_tit tac"><h2><img src="<?php echo get_stylesheet_directory_uri(); ?>/img/sns_tit.png" alt="Happy_SNS"><br>トップコミュニティー</h2>
			<p>ハッピー公認のトップコミュニティーで、<br class="sp">話題の情報をキャッチしよう！</p>
		</div>
		<ul class="member_sns_list">
			<li class="tac">
				<div class="member_sns_list_img tac"><img src="/_assets/wp/dummy/sns01.png" alt="sns01"></div>
				<div class="member_sns_list_txt">
					<h3>松久 由宇</h3>
					<p>アート</p>
					<div class="btn">
						<a href="">フォローする</a>
					</div>
				</div>
			</li>
			<li class="tac">
				<div class="member_sns_list_img tac"><img src="/_assets/wp/dummy/sns02.png" alt="sns02"></div>
				<div class="member_sns_list_txt">
					<h3>TOMORROWLAND</h3>
					<p>ファッション</p>
					<div class="btn">
						<a href="">フォローする</a>
					</div>
				</div>
			</li>
			<li class="tac">
				<div class="member_sns_list_img tac"><img src="/_assets/wp/dummy/sns03.png" alt="sns03"></div>
				<div class="member_sns_list_txt">
					<h3>政道 徳門</h3>
					<p>その他</p>
					<div class="btn">
						<a href="">フォローする</a>
					</div>
				</div>
			</li>
			<li class="tac">
				<div class="member_sns_list_img tac"><img src="/_assets/wp/dummy/sns04.png" alt="sns04"></div>
				<div class="member_sns_list_txt">
					<h3>Happyケアメンテ</h3>
					<p>ファッション</p>
					<div class="btn">
						<a href="">フォローする</a>
					</div>
				</div>
			</li>
			<li class="tac">
				<div class="member_sns_list_img tac"><img src="/_assets/wp/dummy/sns01.png" alt="sns01"></div>
				<div class="member_sns_list_txt">
					<h3>松久 由宇</h3>
					<p>アート</p>
					<div class="btn">
						<a href="">フォローする</a>
					</div>
				</div>
			</li>
		</ul>
	</div>
</section>
<!--　/#member_sns -->

<section id="member_sns_sub">
	<div class="container">
		<h2>外部SNS連携</h2>
		<ul>
			<li><a href="https://www.facebook.com/pages/%e3%83%8f%e3%83%83%e3%83%94%e3%83%bc%2d%e3%82%b1%e3%82%a2%e3%83%a1%e3%83%b3%e3%83%86Happy%2dCareMenteh%2f107312759374049" target="_blank"><img src="<?php echo get_stylesheet_directory_uri(); ?>/img/sns_facebook.png" alt="sns_facebook" width="32" height="32">Facebookと連携する</a></li>
			<li><a href="https://twitter.com/Happy_KYOTO" target="_blank"><img src="<?php echo get_stylesheet_directory_uri(); ?>/img/sns_twitter.png" alt="sns_twitter" width="32" height="32">Twitterと連携する</a></li>
			<li><a href="https://www.instagram.com/happycarementeh/" target="_blank"><img src="<?php echo get_stylesheet_directory_uri(); ?>/img/sns_instagram.png" alt="sns_instagram" width="32" height="32">Instagramと連携する</a></li>
		</ul>
	</div>
</section>
<!--　/#member_sns_sub -->

<?php get_template_part( 'shared/front-bottom' ); ?>
<?php get_footer(); ?>
