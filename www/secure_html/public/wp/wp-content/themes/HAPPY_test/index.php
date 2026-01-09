<?php get_header() ?>


	<div id="Contents">
		<h1>ハッピーケアメンテは高級品クリーニングの駆け込み寺</h1>
	
		<div id="container">
			<div id="theTarget">
				<div style="background-image: url(https://www.kyoto-happy.co.jp:8443/_assets/img/index/pct_newkv01.jpg)"><a href="/carementeh/">ハッピー「ケアメンテ」で幸福をつくろう</a></div>
				<div style="background-image: url(https://www.kyoto-happy.co.jp:8443/_assets/img/index/pct_newkv02.jpg)"><a href="/movie/">ケアメンテ プロモーションビデオ</a></div>
				<div style="background-image: url(https://www.kyoto-happy.co.jp:8443/_assets/img/index/pct_newkv03.jpg)"><a href="/community/">ハッピー公認トップコミュニティー</a></div>
				<div style="background-image: url(https://www.kyoto-happy.co.jp:8443/_assets/img/index/pct_newkv04.jpg)"><a href="/shop/">提携ブランド・取扱い店舗一覧</a></div>
			</div>
			<div id="theTargetSP">
				<div style="background-image: url(https://www.kyoto-happy.co.jp:8443/_assets/img/index/pct_newkv01_sp.jpg)"><a href="/carementeh/">ハッピー「ケアメンテ」で幸福をつくろう</a></div>
				<div style="background-image: url(https://www.kyoto-happy.co.jp:8443/_assets/img/index/pct_newkv02_sp.jpg)"><a href="/movie/">ケアメンテ プロモーションビデオ</a></div>
				<div style="background-image: url(https://www.kyoto-happy.co.jp:8443/_assets/img/index/pct_newkv03_sp.jpg)"><a href="/community/">ハッピー公認トップコミュニティー</a></div>
				<div style="background-image: url(https://www.kyoto-happy.co.jp:8443/_assets/img/index/pct_newkv04_sp.jpg)"><a href="/shop/">提携ブランド・取扱い店舗一覧</a></div>
			</div>
		</div>


	<div class="bgGray">
	
		<div class="sale_headline">
			<a href="/sale/">	
				<div class="box">■■■　セールご案内・ご優待　■■■</div>
			</a>
		</div>

        <div class="news_headline-Ver2">
        
		<?php
			$args = array(
				'post_type' => 'top_headline',
				'posts_per_page' => 3
				);
				$my_posts = get_posts( $args );
				foreach ( $my_posts as $post ):
        ?>
  			<div class="box">
				<a href="<?php the_field('news_otherURL'); ?>" class="box_link" target="_blank">
					<div class="title"><?php the_title()?></div>
					<div class="txt"><?php the_field('news_headlineTxt') ?></div>
				</a>
			</div>
		<?php endforeach; ?>
		</div>
	
		<section class="tel__section SPpart">
			<a href="tel:0120-88-6868"><img src="https://www.kyoto-happy.co.jp:8443/_assets/img/index/sp_tel.gif" alt="0120-88-6868"></a>
		</section>
	
		<section class="link_top__section">
			<div class="wrap">
				<ul>
					<li>
						<a href="/use/">
							<img src="https://www.kyoto-happy.co.jp:8443/_assets/img/index/pct_menu01.jpg" alt="ORDER">
							<div class="label">ORDER</div>
							<h2>ご注文方法／価格表</h2>
							<p>ケアメンテご依頼品のお引取り・<br>SHOP持参・着払い送付方法について<br>ご案内します。</p>
						</a>
					</li>
					<li>
						<a href="/carementeh/">
							<img src="https://www.kyoto-happy.co.jp:8443/_assets/img/index/pct_menu02_.jpg" alt="CAREMENTEH">
							<div class="label">SERVICE</div>
							<h2>サービス概要・メニュー一覧</h2>
							<p>クリーニングの限界を超えたハッピーの<br>「ケアメンテ」についてご紹介します。</p>
						</a>
					</li>
					<li>
						<a href="/technology/">
							<img src="https://www.kyoto-happy.co.jp:8443/_assets/img/index/pct_menu03.jpg" alt="KNOWLEDGE">
							<div class="label">TECHNOLOGY</div>
							<h2>ケアメンテの技術</h2>
							<p>科学的根拠に基づいたケアメンテの<br>技術や実証論文をご紹介します。</p>
						</a>
					</li>
					<li>
						<a href="/corporate/">
							<img src="https://www.kyoto-happy.co.jp:8443/_assets/img/index/pct_menu04.jpg" alt="CORPORATE">
							<div class="label">CORPORATE / RECRUIT</div>
							<h2>会社情報・リクルート</h2>
							<p>衣服再生産（ケアメンテ）という産業分野の<br>社会活動をご覧ください。</p>
						</a>
					</li>
				</ul>
			</div>
		</section>
		
		<section class="lp_top__section">
			<div class="wrap">
				<h2><img src="https://www.kyoto-happy.co.jp:8443/_assets/img/lp/h2_01.png" alt="着たいのに着れない… おっと、こんな時どうする?"></h2>
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
				<p>ハッピー独自の技術・サービスが、<br class="SPpart">衣服の悩みを解決します。</p>
				<ul>
					<li><a href="/carementeh/overview/counseling/"><img src="https://www.kyoto-happy.co.jp:8443/_assets/img/lp/topic_01.png" alt="カウンセリング／電子カルテシステム 「お客さまのお話に、じっくりと耳を傾ける」"></a></li>
					<li><a href="/technology/innovation/weightlessness/"><img src="https://www.kyoto-happy.co.jp:8443/_assets/img/lp/topic_02.png" alt="無重力バランス洗浄 洗浄の常識を覆した独自の水系洗浄技術"></a></li>
					<li><a href="/use/howtoorder/package/"><img src="https://www.kyoto-happy.co.jp:8443/_assets/img/lp/topic_03.png" alt="美しいシルエットのままお届け ケアメンテの技術品質を安全にお届けします"></a></li>
				</ul>
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
        
		<section class="link_2nd__section">
			<div class="wrap">
				<ul>
					<li><a href="/detail/"><img src="https://www.kyoto-happy.co.jp:8443/_assets/img/lp/topic_04.png" alt="こだわりのシルエット・ディテールを演出するケアメンテ おしゃれの裏づけ ハッピーが選んだハイグレードアイテムをご紹介。"></a></li>
					<li><a href="#inline-content3" class="popup"><img src="https://www.kyoto-happy.co.jp:8443/_assets/img/lp/topic_05.png" alt="ぞくぞくと寄せられる「きれい」の声 ケアメンテ体験者の声 ご注文・お問合わせはお気軽にお電話ください 0120-88-6868"></a></li>
				</ul>
			</div>
		</section>
		
		<section class="sachi__section">
			<div class="wrap">
				<div class="logo"><img src="https://www.kyoto-happy.co.jp:8443/_assets/img/index/sachi_logo.png" alt="幸 sachi"></div>
				<div class="pct"><img src="https://www.kyoto-happy.co.jp:8443/_assets/img/index/sachi_img.jpg?180517" alt="世界に誇る木版技術を後世に残すためにいま取り組むべきこと"></div>
				<div class="contents">
					<div class="title"><img src="https://www.kyoto-happy.co.jp:8443/_assets/img/index/sachi_title.png" alt="京の伝統工芸職人を追う"></div>
					<div class="txt">京都の伝統工芸・匠の技をケアメンテの視点でご紹介します。<br class="PCpart" />
					旧版（冊子版）の<a href="sachi/#backnumber"><u>バックナンバーもPDFで</u></a>ご覧いただけます。</div>
				</div>
			</div>
			<div class="bottomWrap">
				<div class="title"><span>WEBマガジン　</span><br class="PCpart" />幸（sachi）とは？</div>
				<div class="txt">“技”を持つ職人達。華やかな表舞台の裏には人知れず腕を磨き精進する姿がある。<br />
				職人技と呼ばれる“極み”を完成した人々、"ケアメンテ"も縁の下の力持ちに徹し、<br class="PCpart" />
				静かに"技"を研鑽している。伝統工芸の職人技とケアメンテの職人技は共通しており、 <br class="PCpart" />
				それぞれの技の“極み”を発見してもらうために「幸」がある。<br />
				長年に渡りご紹介してきたハッピーの季刊誌 「幸（sachi）」が、WEB版に生まれ変わり待望の復刊です。</div>
				<div class="linkbtn">
					<a href="sachi/"><div class="btn">幸sachiを読む<i class="fa fa-angle-right" aria-hidden="true"></i></div></a>
				</div>
			</div>
		</section>
		
		<section class="link_3rd__section">
			<div class="wrap">
				<ul class="menu1">
					<li>
						<a href="/carementeh_search/">
							<h2><span>Before & After事例集</span>さがす</h2>
							<img src="https://www.kyoto-happy.co.jp:8443/_assets/img/index/ico_search.svg" alt="さがす">
							<p>Before & After事例集から検索して<br class="PCpart">仕上がり感をイメージできます。</p>
						</a>
					</li>
					<li>
						<a href="/review/">
							<h2><span>お客さまレビュー</span>きづく</h2>
							<img src="https://www.kyoto-happy.co.jp:8443/_assets/img/index/ico_review.svg" alt="きづく">
							<p>お客様の”体験談”を<br>ご紹介します。</p>
						</a>
					</li>
					<li>
						<a href="/mypage/sns.html">
							<h2><span>ハッピーSNS</span>つなぐ</h2>
							<img src="https://www.kyoto-happy.co.jp:8443/_assets/img/index/ico_sns.svg" alt="つなぐ">
							<p>ケアメンテをご利用のお客様間で<br class="PCpart">情報交換ができます。</p>
						</a>
					</li>
					<li>
						<a href="/mypage/">
							<h2><span>お客さま専用ページ</span>マイページ</h2>
							<img src="https://www.kyoto-happy.co.jp:8443/_assets/img/index/ico_mypage.svg" alt="マイページ">
							<p>ケアメンテのご利用履歴などが<br class="PCpart">画像付きでいつでも確認できます。</p>
						</a>
					</li>
				</ul>
				
				<div class="happySNS">
					<div class="topWrap">
						<div class="left">
							<h2><span>ハッピーSNS</span>『つなぐ』</h2>
							<p>ハッピー公認のトップコミュニティーで、<br class="SPpart">話題の情報を<br class="PCpart">キャッチしよう！<br>「つなぐ」でしか知ることのできない知的で貴重な情報も！</p>
							<div class="btn"><a href="/mypage/sns.html">チェックする<i class="fa fa-angle-right" aria-hidden="true"></i></a></div>
						</div>
						<div class="right">
							<ul id="snsSlide">
								<?php
									$args = array(
										'post_type' => 'recommend_community',
										'posts_per_page' => 20
										);
										$my_posts = get_posts( $args );
										foreach ( $my_posts as $post ):
						        ?>
								<li><a href="<?php the_field('recommend_URL') ?>" class="tooltip" data-tooltip="<?php if(mb_strlen(get_field('recommend_text'))>100) { $rec_tex= mb_substr(get_field('recommend_text'),0,99) ; echo $rec_tex. … ;} else {echo get_field('recommend_text');} ?>"><img src="<?php the_field('recommend_avatar') ?>" alt="<?php the_field('recommend_title') ?>"><h3><?php the_field('recommend_title') ?></h3><span><?php the_field('recommend_type') ?></span></a></li>
								<?php endforeach; ?>
							</ul>
						</div>
					</div>
					<div class="bottomWrap">
						<div class="left">
							<div class="head">ハッピーSNS『つなぐ』 最新の投稿</div>
							<div class="timeline">

							<?php //require(dirname(__FILE__).'/../../../../../view/modules/index_timeline.html'); ?>
							<?php
							$url = "https://www.kyoto-happy.co.jp/modules/index_timeline.html";
$options['ssl']['verify_peer']=false;
$options['ssl']['verify_peer_name']=false;
$response = file_get_contents($url, false, stream_context_create($options));
echo $response;
?>

							</div>
						</div>
						<div class="right">
							<div class="head">ハッピー公認オススメコミュニティ</div>
							<div class="pickup">
								<ul>
								<?php
									$args = array(
										'post_type' => 'recommend_community',
										'posts_per_page' => 2,
										'meta_key' => 'recommend_pickup',
										'meta_value' => true
										);
										$my_posts = get_posts( $args );
										foreach ( $my_posts as $post ):
										$loopcounter++;
						        ?>
						        <li>
									<a href="<?php the_field('recommend_URL') ?>" class="communityMore">
									<img src="<?php the_field('recommend_avatar') ?>" alt="TOMORROWLAND">
									<div class="title">
										<h3><?php the_field('recommend_title') ?></h3>
										<span><?php the_field('recommend_type') ?></span>
									</div>
									<p><?php the_field('recommend_text') ?></p>
									<div class="alert"><?php the_field('recommend_mes') ?></div>
									<div class="communityMorePC">
										<div class="moreUser">
											<img src="<?php the_field('recommend_avatar') ?>" alt="<?php the_field('recommend_title') ?>">
											<div class="userTxt"><?php the_field('recommend_title') ?><span><?php the_field('recommend_type') ?></span></div>
										</div>
										<p><?php the_field('recommend_text2') ?></p>
										<div class="moreLink">コミュニティページへ</div>
									</div>
									</a>										
									<div class="communityMoreSP">
										<a href="#moreText<?php if($loopcounter%2==0) { echo ('2'); } ?>"><span>もっと見る</span></a>
										<div class="moreFix" id="moreText<?php if($loopcounter%2==0) { echo ('2'); } ?>">&nbsp;</div>
										<div class="moreInfo">
											<div class="moreUser">
												<img src="<?php the_field('recommend_avatar') ?>" alt="<?php the_field('recommend_title') ?>">
												<div class="userTxt"><?php the_field('recommend_title') ?><span><?php the_field('recommend_type') ?></span></div>
											</div>
											<p><?php the_field('recommend_text2') ?></p>
											<div class="moreLink"><a href="<?php the_field('recommend_URL') ?>">コミュニティページへ</a></div>
										</div>
									</div>
								</li>
						        <?php endforeach; ?>
								</ul>
							</div>
						</div>
					</div>
				</div>
				
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
		
		<section class="link_4th__section">
			<div class="wrap">
				<div class="PCpart">
					<ul class="tel">
						<li><a href="tel:0120-88-3040"><img src="https://www.kyoto-happy.co.jp:8443/_assets/img/index/link_4th_tel_01_1.png" alt="エルメスお客様ご愛用ダイヤル 0120-88-3040"></a></li>
						<li><a href="tel:0120-88-6868"><img src="https://www.kyoto-happy.co.jp:8443/_assets/img/index/link_4th_tel_02.png" alt="ご注文・お問い合わせはお気軽にお電話ください 0120-88-6868"></a></li>
					</ul>
					<ul class="link">
						<li><a href="/mailmag/"><img src="https://www.kyoto-happy.co.jp:8443/_assets/img/index/link_4th_01.gif" alt="メールマガジン登録 Mail Magazine"></a></li>
						<li><a href="/corporate/recruit/cultivation/"><img src="https://www.kyoto-happy.co.jp:8443/_assets/img/index/link_4th_02.gif" alt="リクルート Recruit"></a></li>
						<li><a href="/corporate/media/literary/"><img src="https://www.kyoto-happy.co.jp:8443/_assets/img/index/link_4th_03.gif" alt="ハッピーの著作物一覧 Book"></a></li>
						<li><a href="/sale/"><img src="https://www.kyoto-happy.co.jp:8443/_assets/img/index/link_4th_04.gif" alt="SALE 優待券を取得"></a></li>
						<li><a href="/carementeh/overview/etymology/"><img src="https://www.kyoto-happy.co.jp:8443/_assets/img/index/link_4th_05.gif" alt="ケアメンテの語源 Etymology"></a></li>
						<li><a href="http://www.hashimoto-hideo.com" target="_blank" rel="nofollow"><img src="https://www.kyoto-happy.co.jp:8443/_assets/img/index/link_4th_06.gif" alt="当社代表のオフィシャルサイト 橋本英夫 Official Site"></a></li>
					</ul>
				</div>
				<div class="SPpart">
					<ul class="tel">
						<li><a href="tel:0120-88-3040"><img src="https://www.kyoto-happy.co.jp:8443/_assets/img/index/link_4th_tel_01_1.png" alt="エルメスお客様ご愛用ダイヤル 0120-88-3040"></a></li>
						<li><a href="tel:0120-88-6868"><img src="https://www.kyoto-happy.co.jp:8443/_assets/img/index/link_4th_tel_02.png" alt="ご注文・お問い合わせはお気軽にお電話ください 0120-88-6868"></a></li>						
					</ul>
					<ul class="link">
						<li><a href="/mailmag/">メールマガジン登録</a></li>
						<li><a href="/corporate/recruit/cultivation/">リクルート</a></li>
						<li><a href="/corporate/media/literary/">ハッピーの著作物一覧</a></li>
						<li><a href="/sale/">SALE</a></li>
						<li><a href="/carementeh/overview/etymology/">ケアメンテの語源</a></li>
						<li><a href="http://www.hashimoto-hideo.com" target="_blank" rel="nofollow">橋本英夫 Official Site</a></li>
					</ul>
				</div>
			</div>
		</section>
		
		<section class="news__section">
			<div class="wrap">
				<h2>News<a href="/news/"><i class="fa fa-list-ul" aria-hidden="true"></i>過去のニュースはこちら</a></h2>
				<ul>
				<?php
					$args = array(
						'post_type' => 'post',
						'posts_per_page' => 4,
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
		
						foreach ( $my_posts as $post ):
		        ?>
		
				<li><a href="<?php echo get_news_permalink()?>"><span class="date"><?php the_time('Y.m.d')?></span><span class="text"><?php the_title()?></span></a></li>
				<?php endforeach; ?>
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
		
        <div style="display:none;" class="news_headline-detail">
            <section id="inline-content3">
            	<div class="shoulder">お客さまやSHOPスタッフの方たちから、<br class="SPpart">こんなお声が届いています。
                <h3>ハイグレードな服の「メンテナンス」の悩みを教えて！</h3>
                    <ul>
                      <li>ハイグレードな服を長く着続けたいのですが、どうすればいいですか。</li>
                    　<li>クリーニングすると服が傷むからクリーニングしないようにと教えてもらった。ホントですか。</li>
                    　<li>汚れがなければブラッシングだけでよいと教えてもらった。ホントですか。</li>
                    　<li>シミがついたらシミの部分だけクリーニングしていると聞いた。ホントですか。</li>
                    　<li>クリーニングしているのに黄ばんできた。どうすればいいですか。</li>
                    　<li>ビキューナやカシミヤ、シルクなどウェットクリーニングでシワシワになって戻ってきた。<br>どうすればいいですか。</li>
                    　<li>ドライクリーニングは汚れが落ちないと教えてもらった。ホントですか。</li>
                    　<li>高級ブランド、上質な素材だとクリーニングで断られた。どうすればいいですか。</li>
                    　<li>ネット宅配クリーニングで戻って着たらシワシワ、どうすればいいですか。</li>
                    　<li>クリーニングについての疑問や質問が延々と続きます・・・・</li>
                    </ul>
                    <p class="arrow"><span>私たちが解決します</span><br><img src="/_assets/img_sp/common_page/icon_arrow_off.png"></p>
                    <ul class="block">
	                    <li><h5>お客さまの評判</h5><div><a href="/review/"><img src="https://www.kyoto-happy.co.jp:8443/_assets/img/index/icn_sns02.png" alt="きづく">お客さまレビュー『きづく』</a><br class="PCpart"><a href="/use/evaluate/blog/">お客さまのブログ（体験談）</a><p>あなたの質問・疑問にハッピーケアメンテ体験者のお客さまがお答えします。</p></div></li>
                        <li><h5>ビフォー・アフター事例集1800点</h5><div><a href="/carementeh_search/"><img src="https://www.kyoto-happy.co.jp:8443/_assets/img/index/icn_sns01.png" alt="さがす">ケアメンテ検索エンジン『さがす』</a><br class="PCpart"><p>お手持ち衣服に近い衣服をさがして、ケアメンテの仕上り感をイメージしていただけます。</p></div></li>
                    </ul>
            	</div>
            </section>
        </div>
        		
        <div style="display:none;" class="news_headline-detail">
            <section id="inline-content4">
            	<div class="shoulder">
                <h3>「カンブリア宮殿」で村上龍さんが注目した代表橋本の言葉『魂の宿る衣服』</h3>
                    <p><img src="https://www.kyoto-happy.co.jp:8443/_assets/img/index/inline-content4_img1.jpg" align="right"></p>　世の中が、猛スピードで変化しています。特にインターネット系業界は、猫の目のように目まぐるしく動いています。クリーニング業界においては、クリーニング会社が消費者になりすまして、クリーニング店の比較サイトを実質的に運営し、他社の営業妨害となる書込みをおこなって、自社サイトに誘導する悪質なサイトが目につきます。<br />
					　そのサイトに掲載されている情報が、仮に真実ならば消費者にとって有益な情報なのかもしれません。しかし、自社サイトに誘導するクリーニング会社のサイトを見たり、実際に利用して品質を確かめてみても、どれほどの技術と業務フローの仕組みがあるのか疑わしく、何の根拠や裏付けもないように見受けられます。このように、消費者になりすまして消費者を欺き、真面目に頑張る企業に便乗して自社サイトに誘導するネット手法に甚だ疑問を感じざるをえません。<br />
					　私たちハッピーは、クリーニングでお困りの方、「魂の宿った衣服」を新品で長くいつまでもお洒落を着続けたいと考えておられる消費者にケアメンテサービスをお届けしています。ケアメンテをおこなった衣服の体感品質は、経験した人でないと分かりません。お客さまの期待を裏切ることのないように、クリーニングとは一線を画した新しい再生産サービス産業を世界で展開しようとしています。<br />
					　だからこそ、ハッピーケアメンテは、デパート・セレクトショップ・ラグジュアリーブランドほか、あらゆるジャンルの方々からのご紹介が多いのです。<br />
					<br />
					<p><img src="https://www.kyoto-happy.co.jp:8443/_assets/img/index/inline-content4_img2.jpg" align="right"></p>　<a href="http://www.tv-tokyo.co.jp/cambria/backnumber/2011/0929/" target="_blank">2011年9月29日放送のテレビ東京「カンブリア宮殿」</a>でハッピーが紹介された際、司会の村上龍さんは番組の中で、「ハッピーケアメンテは、『魂の宿る衣服』を単に洗うのではなく、衣服の機能美を総合的にメンテナンスするビジネスだ」と評価くださいました。<br />
					　ハッピーでは、あなたの魂の宿った“こだわりの一着”の新品クオリティを維持するために、ヨーロッパで認められた世界初の水系洗浄方法や、ＩＣＴシステムによるマネジメントシステムを独自に開発し、日本はもとより、世界のラグジュアリーブランドから「信頼」を得ています。<br />
					　ハッピーの衣服に対する“こだわり”やクオリティは、ハッピーのお客さまをはじめ、多くのアパレル・ラグジュアリー・デパートやセレクトショップの満足度を高めています。<br />
					　そして、ハイグレードな衣服には、技術品質とサービス品質の最適価値が必要になります。だからこそハッピーは、お客さまとの会話（コミュニケーション）を何よりも大切にしているのです。<br />
					<br />
					　ところで、こんなお話が・・・。例えば、2000円位で購入されたファストファッションを、購入価格の5～10倍以上する価格でケアメンテをご依頼いただくケースも多いということです。ハッピーは、必ずしも何十万円、何百万円もするハイグレードな衣服だけを承っているわけではありません。衣服には、人それぞれの思い出があり、思い出が深ければ深いほど、新品に戻してほしいという要望が強いのです。<br />
					　ハッピーケアメンテは、購入時の新品状態で「いつまでも長く」着続けたい、捨てられる運命の衣服を新品同様に戻して「いつまでも長く」着続けたいという「あなた」の期待価値にお応えします。<br />
					　これが、一般のクリーニングや、ネット宅配クリーニングなどと一線を画し、似て非なる「ケアメンテサービス」なのです。これからの少子高齢化の時代は、希少的価値が進行していくことが予測されます。安ければ良いというものではありませんし、高ければ良いというものでもない。しかしながら、まとめて何十点が何千円というクリーニングで、あなたの魂の宿った服が十羽一絡げでクリーニング処理されても良いのでしょうか。<br />
					　モノもサービスも、本物の価値が求められる時代です。ハッピーケアメンテは、これからも、お客さまがお客さまを呼んでくださる、お客さまに愛されるクオリティを提供してまいります。
            	</div>
            </section>
        </div>
        
        <!--/POPUP Contents-->

		
</div><!--/Contents-->


		<link rel="stylesheet" href="/_assets/css/skippr_170920.css">
		<script src="/_assets/js/skippr.min_170920.js"></script>
		<script>
		$("#theTarget").skippr({
			transition: 'fade',
			speed: 1000,
			navType: 'bubble',
			autoPlay: true,
			autoPlayDuration: 6000,
			keyboardOnAlways: false
		});
		$("#theTargetSP").skippr({
			transition: 'fade',
			speed: 1000,
			navType: 'bubble',
			autoPlay: true,
			autoPlayDuration: 6000,
			keyboardOnAlways: false
		});
		</script>
		<link rel="stylesheet" href="/_assets/css/jquery.bxslider_170920.css">
		<script src="/_assets/js/jquery.bxslider.min_170920.js"></script>
		<script type="text/javascript">
		$(function() {
			$('#lp_slider').bxSlider({
				slideWidth: 370,
				pause: 7000,
				auto: true,
				infiniteLoop: true,
				slideMargin: 15,
				autoHover: true
			});
		});
		</script>
		
		<script type="text/javascript">
		$(function() {
			$('#snsSlide').bxSlider({
				slideWidth: 90,
				minSlides: 1,
				maxSlides: 3,
				moveSlides: 3,
				auto: true,
				infiniteLoop: true,
				slideMargin: 0,
				autoHover: true
			});
		});
		</script>
		
		<script>
		$('.sub_menu:not(:first)').hide();
		$('.main_menu').click(function () {
			$(this).next('.sub_menu').slideToggle('slow').siblings('.sub_menu').slideUp('slow');
			$(this).siblings('.main_menu').removeClass('active');
			$(this).toggleClass('active');
		});
		</script>
		
		<link rel="stylesheet" href="/_assets/css/darktooltip.css">
		<script src="/_assets/js/jquery.darktooltip_171121.js"></script>
		<script>
		$(document).ready( function(){
			$('.tooltip').darkTooltip({
				animation: 'fadeIn',
				gravity: 'north',
				theme: 'light'
			});
		});
		</script>
			
<?php get_footer() ?>