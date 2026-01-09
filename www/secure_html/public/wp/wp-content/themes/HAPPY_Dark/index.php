<?php get_header() ?>

		<div id="Contents">
			<section class="keyvisual_section">
				<ul id="kv_slide" class="kv_slide">
					<li>
						<div class="kv_slide_img">
							<picture>
								<source srcset="https://www.kyoto-happy.co.jp:8443/_assets/img/index2019/kv_sp1.jpg?200501" media="(max-width:767px)">
								<img src="https://www.kyoto-happy.co.jp:8443/_assets/img/index2019/kv_1.jpg?200501" alt="上質で繊細な服を何年も着続けているのにいつも新調しているかのような装い。服が長持ちするから、着回しが楽しくなる。だから、上質で良い服が欲しくなる。">
							</picture>
						</div>
					</li>
					<li>
						<a href="https://www.kyoto-happy.co.jp:8443/pdf/Manga_01.pdf?ver1.0" target="_blank">
							<div class="kv_slide_img">
								<picture>
									<source srcset="https://www.kyoto-happy.co.jp:8443/_assets/img/index2019/kv_sp2.jpg?200501" media="(max-width:767px)">
									<img src="https://www.kyoto-happy.co.jp:8443/_assets/img/index2019/kv_2.jpg?200501" alt="上質で繊細な服を何年も着続けているのにいつも新調しているかのような装い。服が長持ちするから、着回しが楽しくなる。だから、上質で良い服が欲しくなる。">
								</picture>
							</div>
						</a>
					</li>
					<li>
						<a href="https://www.kyoto-happy.co.jp/sale/">
							<div class="kv_slide_img">
								<picture>
									<source srcset="https://www.kyoto-happy.co.jp:8443/_assets/img/index2019/kv_sp3.jpg?200501" media="(max-width:767px)">
									<img src="https://www.kyoto-happy.co.jp:8443/_assets/img/index2019/kv_3.jpg?200501" alt="上質で繊細な服を何年も着続けているのにいつも新調しているかのような装い。服が長持ちするから、着回しが楽しくなる。だから、上質で良い服が欲しくなる。">
								</picture>
							</div>
						</a>
					</li>
					<li>
						<a href="https://www.kyoto-happy.co.jp/carementeh/service/valueon/">
							<div class="kv_slide_img">
								<picture>
									<source srcset="https://www.kyoto-happy.co.jp:8443/_assets/img/index2019/kv_sp4.jpg?200501" media="(max-width:767px)">
									<img src="https://www.kyoto-happy.co.jp:8443/_assets/img/index2019/kv_4.jpg?200501" alt="上質で繊細な服を何年も着続けているのにいつも新調しているかのような装い。服が長持ちするから、着回しが楽しくなる。だから、上質で良い服が欲しくなる。">
								</picture>
							</div>
						</a>
					</li>
				</ul>
				<div class="topics">
					<div class="topics_wrap">
						<h2><span>お知らせ</span></h2>
						<p>
							<?php
								$args = array(
									'post_type' => 'top_headline',
									'posts_per_page' => 1
									);
									$my_posts = get_posts( $args );
									foreach ( $my_posts as $post ):
					        ?>
									<a href="<?php the_field('news_otherURL'); ?>"><?php the_title()?></a></p>
							<?php endforeach; ?>
					</div>
					<div class="topics_more"><a><i class="fa fa-angle-down" aria-hidden="true"></i><span class="PCpart">もっと見る</span><span class="SPpart">お知らせ</span></a></div>
				</div>
				<div class="topics_detail">
					<div class="topics_detail_wrap">
						<ul class="topics_list">
							<?php
								$args = array(
									'post_type' => 'top_headline',
									'posts_per_page' => 6
									);
									$my_posts = get_posts( $args );
									foreach ( $my_posts as $post ):
									?>
									<li><a href="<?php the_field('news_otherURL'); ?>"><?php the_title()?></a></li>
							<?php endforeach; ?>
						</ul>
						<h2 class="section_ttl">おすすめ</h2>
						<ul class="topics_pickup">
							<li>
								<a href="/corporate/csr/reuse/">
									<div class="topics_list_img"><img src="https://www.kyoto-happy.co.jp:8443/_assets/img/index2019/topics_img_05.jpg" alt="「ハッピーケアメンテ®」は良いモノを長もちさせる究極の“自然循環型産業”です"></div>
									<p>「ハッピーケアメンテ®」は良いモノを<br>長もちさせる究極の“自然循環型産業”です</p>
								</a>
							</li>
							<li>
								<a href="/sachi/#Shortcut">
									<div class="topics_list_img"><div class="topics_list_new"><img src="https://www.kyoto-happy.co.jp:8443/_assets/img/index2019/topics_new.png" alt="NEW"></div><img src="https://www.kyoto-happy.co.jp:8443/_assets/img/index2019/topics_img_01.jpg" alt="明治天皇・有栖川宮家の「着物」の遺品をケアメンテする"></div>
									<p>明治天皇・有栖川宮家の「着物」の<br>遺品をケアメンテする</p>
								</a>
							</li>
							<li>
								<a href="/mariopecora/">
									<div class="topics_list_img"><img src="https://www.kyoto-happy.co.jp:8443/_assets/img/index2019/topics_img_02.jpg" alt="シルエット・ディテールについて"></div>
									<p>シルエット・ディテールについて</p>
								</a>
							</li>
							<li>
								<a href="/technology/">
									<div class="topics_list_img"><img src="https://www.kyoto-happy.co.jp:8443/_assets/img/index2019/topics_img_03.jpg" alt="科学的根拠に基づいたケアメンテの技術や実証論文をご紹介します"></div>
									<p>科学的根拠に基づいたケアメンテの<br>技術や実証論文をご紹介します</p>
								</a>
							</li>
						</ul>
					</div>
				</div>
				<div class="tel_section"><a href="/use/"><img src="https://www.kyoto-happy.co.jp:8443/_assets/img/index2019/tel_order-ver2.gif?190828" alt="ご注文・ご利用方法はこちら"></a></div>
				<div class="tel_section"><a href="tel:0120-88-6868"><img src="https://www.kyoto-happy.co.jp:8443/_assets/img/index2019/tel_sp-ver2.gif?190828" alt="ご注文・お問い合わせもお気軽にお電話ください。 0120-88-6868 月〜土 9:00~18:00（日曜・祝祭日は除く）"></a></div>
				<div class="tel_section"><a href="tel:0120-88-3040"><img src="https://www.kyoto-happy.co.jp:8443/_assets/img/index2019/tel2_sp.gif?190828" alt="エルメス公認 お客様ご愛用ダイヤル"></a></div>
				<div class="sale_section">
					<a href="/sale/">
						<i class="fa fa-angle-right" aria-hidden="true"></i><div class="title"><img src="https://www.kyoto-happy.co.jp:8443/_assets/img/index2019/sale_title.png" alt="エルメス公認 お客様ご愛用ダイヤル"></div><span><?php the_field('sale_top',448); ?></span>
					</a>
				</div>
			</section>

			<div class="support_service">
				<a href="http://www.kyoto-happy.co.jp/support-service/">
					<h2>『ご支援サービス』のご案内</h2>
					<p><i class="fa fa-angle-right" aria-hidden="true"></i> クリーニング店様向けのサービスのご紹介、お申込みはこちら</p>
				</a>
			</div>

			<div class="PV_section">
				<h2>驚異のケアメンテ&reg;<br class="SPpart">これは頼む価値がありそうだ</h2>
				<ul>
					<li class="general">
						<video id="video" src="https://www.kyoto-happy.co.jp:8443/_assets/movie/technology_full.mp4" width="480" height="270" playsinline muted autoplay loop controls></video>
					</li>
					<li class="btn-area">
						<ul id="control">
							<li><a href="#technology_pv1" class="popup"><img src="https://www.kyoto-happy.co.jp:8443/_assets/movie/technology_pv1.jpg" alt="">完結版<br /><span class="time">4:18</span></a></li>
							<li><a href="#technology_pv2" class="popup"><img src="https://www.kyoto-happy.co.jp:8443/_assets/movie/technology_pv2.jpg" alt="">ダウン類<br /><span class="time">0:57</span></a></li>
							<li><a href="#technology_pv3" class="popup"><img src="https://www.kyoto-happy.co.jp:8443/_assets/movie/technology_pv3.jpg" alt="">レザーグレイン<br /><span class="time">0:57</span></a></li>
							<li><a href="#technology_pv4" class="popup"><img src="https://www.kyoto-happy.co.jp:8443/_assets/movie/technology_pv4.jpg" alt="">メンズスーツ<br /><span class="time">1:13</span></a></li>
							<li><a href="#technology_pv5" class="popup"><img src="https://www.kyoto-happy.co.jp:8443/_assets/movie/technology_pv5.jpg" alt="">レディースシルク<br /><span class="time">0:19</span></a></li>
							<li><a href="#technology_pv6" class="popup"><img src="https://www.kyoto-happy.co.jp:8443/_assets/movie/technology_pv6.jpg" alt="">シルエット・ディテール<br /><span class="time">0:29</span></a></li>
							<li><a href="#technology_pv7" class="popup"><img src="https://www.kyoto-happy.co.jp:8443/_assets/movie/technology_pv7.jpg" alt="">ゴム引き（マッキントッシュ）<br /><span class="time">0:23</span></a></li>
						</ul>
						<p class="subcopy">ケアメンテ＝再生産は、地球温暖化の防止に役立ちます</p>
					</li>
				</ul>
			</div>

			<!--Popup-->
			<div style="display:none;">
				<section id="technology_pv1"><div class="movie-wrap"><iframe width="854" height="480" src="https://www.youtube.com/embed/pOZPaiVtIVE" frameborder="0" allow="accelerometer; autoplay; encrypted-media; gyroscope; picture-in-picture" allowfullscreen></iframe></div></section>
				<section id="technology_pv2"><div class="movie-wrap"><iframe width="854" height="480" src="https://www.youtube.com/embed/yzTc75yHZ0M" frameborder="0" allow="accelerometer; autoplay; encrypted-media; gyroscope; picture-in-picture" allowfullscreen></iframe></div></section>
				<section id="technology_pv3"><div class="movie-wrap"><iframe width="854" height="480" src="https://www.youtube.com/embed/A7kSrLF3mdg" frameborder="0" allow="accelerometer; autoplay; encrypted-media; gyroscope; picture-in-picture" allowfullscreen></iframe></div></section>
				<section id="technology_pv4"><div class="movie-wrap"><iframe width="854" height="480" src="https://www.youtube.com/embed/ZF5HM76OxZw" frameborder="0" allow="accelerometer; autoplay; encrypted-media; gyroscope; picture-in-picture" allowfullscreen></iframe></div></section>
				<section id="technology_pv5"><div class="movie-wrap"><iframe width="854" height="480" src="https://www.youtube.com/embed/IgkwDl84V9g" frameborder="0" allow="accelerometer; autoplay; encrypted-media; gyroscope; picture-in-picture" allowfullscreen></iframe></div></section>
				<section id="technology_pv6"><div class="movie-wrap"><iframe width="854" height="480" src="https://www.youtube.com/embed/Cv9idLb6GFw" frameborder="0" allow="accelerometer; autoplay; encrypted-media; gyroscope; picture-in-picture" allowfullscreen></iframe></div></section>
				<section id="technology_pv7"><div class="movie-wrap"><iframe width="854" height="480" src="https://www.youtube.com/embed/6b8L-JpDj2s" frameborder="0" allow="accelerometer; autoplay; encrypted-media; gyroscope; picture-in-picture" allowfullscreen></iframe></div></section>
			</div>

			<div class="movie_section">
				<ul>
					<li class="general carementeh_search">
						<h2>感動の美しさ</h2>
						<a href="/carementeh_search/" class="link">
							<img src="https://www.kyoto-happy.co.jp:8443/_assets/img/index2019/carementeh_search.jpg" alt="感動の美しさ">
							<h3 class="section_ttl"><span>Before &amp; After実例集</span>ケアメンテ<sup>&reg;</sup>の実例をチェック</h3>
							<p>クリーニングで取れなかったシミ汚れをキレイにする。Before &amp; After実例集から検索して仕上がり感をイメージできます。</p>
						</a>
					</li>
					<li class="general">
						<h2>衝撃のはっ水</h2>
						<p><video src="https://www.kyoto-happy.co.jp:8443/_assets/movie/WaterRepellent_1201910.mp4" width="480" height="270" playsinline muted autoplay loop controls></video></p>
						<p class="subcopy">地球温暖化による「ゲリラ豪雨」から<br class="SPpart">上質高級な衣服を守ります</p>
					</li>
				</ul>
			</div>

			<section class="technology_section">
				<h2 class="section_ttl"><span>大切な服を新品状態で着続けるために</span>ケアメンテ<sup>&reg;</sup>を支えるテクノロジー</h2>
				<ul class="technology_list">
					<li>
						<div class="technology_list_img">
							<h3>洗浄技術<span>無重力バランス洗浄&reg;・<br>アクアドライ&reg;</span></h3>
							<img src="https://www.kyoto-happy.co.jp:8443/_assets/img/index2019/technology_img_01.jpg" alt="洗浄技術">
						</div>
						<div class="technology_list_accordion">
							<div class="technology_list_txt">
								<h3>洗浄技術<span>無重力バランス洗浄&reg;・<br>アクアドライ&reg;</span></h3>
								<p>洗浄の常識を覆したハッピー独自の水系洗浄技術がクリーニングの欠陥を克服します。</p>
							</div>
							<div class="technology_list_more"><a href="/technology/innovation/weightlessness/"><i class="fa fa-angle-right" aria-hidden="true"></i>詳しくはこちら</a></div>
						</div>
					</li>
					<li>
						<div class="technology_list_img">
							<h3>再生加工技術<span>リプロン&reg;×バリューON&reg;</span></h3>
							<img src="https://www.kyoto-happy.co.jp:8443/_assets/img/index2019/technology_img_02.jpg" alt="再生加工技術">
						</div>
						<div class="technology_list_accordion">
							<div class="technology_list_txt">
								<h3>再生加工技術<span>リプロン&reg;×バリューON&reg;</span></h3>
								<p>シミ汚れ・黄ばみ他、様々なトラブルで諦めていた衣服を独自の再生技術で蘇らせます。</p>
							</div>
							<div class="technology_list_more"><a href="/carementeh/service/ripron/"><i class="fa fa-angle-right" aria-hidden="true"></i>詳しくはこちら</a></div>
						</div>
					</li>
					<li>
						<div class="technology_list_img">
							<h3>感性技能<span>シルエットプレス&reg;</span></h3>
							<img src="https://www.kyoto-happy.co.jp:8443/_assets/img/index2019/technology_img_03.jpg" alt="感性技能">
						</div>
						<div class="technology_list_accordion">
							<div class="technology_list_txt">
								<h3>感性技能<span>シルエットプレス&reg;</span></h3>
								<p>プレス技能者が人体工学に基づくアイロンプレスツールを使って美しいシルエットを再現します。</p>
							</div>
							<div class="technology_list_more"><a href="/technology/innovation/press/"><i class="fa fa-angle-right" aria-hidden="true"></i>詳しくはこちら</a></div>
						</div>
					</li>
					<li>
						<div class="technology_list_img">
							<h3>情報システム<span>ハッピー電子カルテシステム</span></h3>
							<img src="https://www.kyoto-happy.co.jp:8443/_assets/img/index2019/technology_img_04.jpg" alt="情報システム">
						</div>
						<div class="technology_list_accordion">
							<div class="technology_list_txt">
								<h3>情報システム<span>ハッピー電子カルテシステム</span></h3>
								<p>大切なご依頼品を管理し、お客様と情報共有するために独自開発したITシステム。</p>
							</div>
							<div class="technology_list_more"><a href="/carementeh/overview/karte/"><i class="fa fa-angle-right" aria-hidden="true"></i>詳しくはこちら</a></div>
						</div>
					</li>
					<li>
						<div class="technology_list_img">
							<h3>自然との共存<span>地球環境を大切にする<br>自然循環</span></h3>
							<img src="https://www.kyoto-happy.co.jp:8443/_assets/img/index2019/technology_img_05.jpg" alt="自然との共存">
						</div>
						<div class="technology_list_accordion">
							<div class="technology_list_txt">
								<h3>自然との共存<span>地球環境を大切にする<br>自然循環</span></h3>
								<p>『衣服を長持ちさせること』が地球環境を守ることに繋がるとハッピーは考えます。</p>
							</div>
							<div class="technology_list_more"><a href="/corporate/csr/weightlessness/"><i class="fa fa-angle-right" aria-hidden="true"></i>詳しくはこちら</a></div>
						</div>
					</li>
					<li class="technology_list_sub">
						<ul>
							<li><a href="/corporate/media/past/"><i class="fa fa-angle-right" aria-hidden="true"></i>報道の記録</a></li>
							<li><a href="/corporate/company/winning/"><i class="fa fa-angle-right" aria-hidden="true"></i>受賞一覧</a></li>
							<li><a href="/corporate/recruit/cultivation/"><i class="fa fa-angle-right" aria-hidden="true"></i>リクルート</a></li>
						</ul>
					</li>
				</ul>
			</section>

			<section class="contents_section">
				<div class="contents_carementeh">
					<div class="contents_txt left">
						<div class="contents_txt_wrap">
							<h2 class="section_ttl"><span>クリーニングとの違いは？</span>ケアメンテ<sup>&reg;</sup>だからできること</h2>
							<p>ハッピーケアメンテ&reg;は、<br class="SPpart">様々なクリーニングの悩みや困りごとを解消します。<br class="SPpart">その違いをご覧ください。</p>
						</div>
					</div>
					<div class="contents_img right">
						<ul class="carementeh_slide">
							<li class="carementeh_slide_about">
								<h2>おっと、こんな時どうする？<br>ケアメンテ<sup>&reg;</sup>技術が<br class="SPpart">あなたの衣服の悩みを解決します</h2>
								<ul class="carementeh_about_slide">
									<li><a href="/carementeh_search/"><p>ケアメンテすればホントにきれいになるの？<strong>Before & After事例集</strong>ってないのですか？</p><div><i class="fa fa-angle-right" aria-hidden="true"></i>詳しく見る</div></a></li>
									<li><a href="/technology/before_after/suit/"><p>ブリオーニ、キートン、イザイア、アットリーニなどのイタリアンクラシコスーツを<strong>高級クリーニングに出したらベタっとして戻ってきた。どうしよう？</strong></p><div><i class="fa fa-angle-right" aria-hidden="true"></i>詳しく見る</div></a></li>
									<li><a href="/technology/before_after/down/"><p>グレイグース使用のモンクレールの<strong>ダウンジャンパーがクリーニングでボリュームがなくなったり、</strong>デリケートな生地やブランドの飾りも使用されているから<strong>壊れないか心配。</strong></p><div><i class="fa fa-angle-right" aria-hidden="true"></i>詳しく見る</div></a></li>
									<li><a href="/technology/before_after/macintosh/"><p>そもそもメンテナンスができないマッキントッシュのゴム引きコート。<strong>このままだと経年劣化で着られなくなってしまう。</strong></p><div><i class="fa fa-angle-right" aria-hidden="true"></i>詳しく見る</div></a></li>
									<li><a href="/carementeh_search/result.html?select=0007_0037_0601"><p>着続けたトレンチコート。撥水加工の効果がなくなって黒ずみ汚れや黄ばみで着れなくなってきた。<strong>クリーニングに出しても、汚れは取れないし撥水効果もないまま。</strong>どうしよう？</p><div><i class="fa fa-angle-right" aria-hidden="true"></i>詳しく見る</div></a></li>
									<li><a href="/use/howtoorder/similarity/"><p>クリーニングで<strong>水洗いって本当にできるの？</strong></p><div><i class="fa fa-angle-right" aria-hidden="true"></i>詳しく見る</div></a></li>
									<li><a href="/carementeh/overview/difference/"><p>ケアメンテはクリーニングやネット宅配クリーニングと<strong>何が違う</strong>の？</p><div><i class="fa fa-angle-right" aria-hidden="true"></i>詳しく見る</div></a></li>
									<li><a href="https://www.youtube.com/watch?v=urRD7z71bws" target="_blank"><p><strong>電子カルテ</strong>を作成するってどういうこと？</p><div><i class="fa fa-angle-right" aria-hidden="true"></i>詳しく見る</div></a></li>
									<li><a href="https://www.youtube.com/watch?v=462-mbvqCsc" target="_blank"><p>カウンセリングって何？</p><div><i class="fa fa-angle-right" aria-hidden="true"></i>詳しく見る</div></a></li>
									<li><a href="/use/howtoorder/package/"><p>宅配用の<strong>パッケージはなぜそんなに大きい</strong>の？</p><div><i class="fa fa-angle-right" aria-hidden="true"></i>詳しく見る</div></a></li>
									<li><a href="/carementeh_search/"><p>10年放置していたこのシミ。<strong>クリーニングに出しても全く何も変わらなかったけどホントに取れるの？</strong></p><div><i class="fa fa-angle-right" aria-hidden="true"></i>詳しく見る</div></a></li>
									<li><a href="https://www.youtube.com/watch?v=4okBMUdZc_E" target="_blank"><p><strong>ケアメンテ</strong>って一体なんなの？説明してよ</p><div><i class="fa fa-angle-right" aria-hidden="true"></i>詳しく見る</div></a></li>
								</ul>
								<div class="contents_btn"><a href="/lp/"><i class="fa fa-angle-right" aria-hidden="true"></i>ケアメンテ&reg;技術を厳しくチェックする</a></div>
							</li>
							<li class="carementeh_slide_verify">
								<h2>高級クリーニング vs <br class="SPpart">ハッピーケアメンテ<sup>&reg;</sup>の検証</h2>
								<p>ハッピーケアメンテ&reg;は、高級クリーニングで“シミ・汚れ・黄ばみ・ニオイが取れない、色が変わった（変色・色むら）、シミが浮き出てきた”など、クリーニングの悩みや困りごとを解消します。特に、高級で上質なラグジュアリーブランドの衣服、エルメスのバッグやシャネルのスーツなど、ケアメンテで奇麗（キレイ）に美しく新品のように蘇らせることができます。</p>
								<div class="contents_btn"><a href="https://www.kyoto-happy.co.jp:8443/pdf/Manga.pdf?ver1.1"><i class="fa fa-angle-right" aria-hidden="true"></i>ケアメンテ&reg;の技術を漫画で詳しく見る</a></div>
							</li>
							<li class="carementeh_slide_similarity">
								<h2>類似・模倣サービスにご注意</h2>
								<p>ハッピーの登録商標「ケアメンテ」を使用して、ハッピーのサービスと混同を招いているクリーニング店が見受けられます。<br>また、当社サービスについて、クリーニング関係者によるものと思われる根拠の無い誹謗中傷かつ悪質な書込み、広告目的の比較評価サイト等には充分ご注意ください。</p>
								<div class="contents_btn"><a href="/use/howtoorder/similarity/"><i class="fa fa-angle-right" aria-hidden="true"></i>ケアメンテ&reg;はネット宅配<br class="SPpart">クリーニングではありません</a></div>
							</li>
						</ul>
					</div>
				</div>

				<div class="contents_partner">
					<div class="contents_txt left">
						<div class="contents_txt_wrap">
							<h2 class="section_ttl">業務提携先</h2>
							<p>様々なファッションブランドや<br class="SPpart">ショップ・企業がケアメンテ&reg;と提携。<br class="SPpart">全国の取扱い店舗の地図がご覧いただけます。</p>
						</div>
					</div>
					<div class="contents_img right">
						<div class="partner_wrap">
							<ul class="partner_list">
								<div class="contents_btn"><a href="https://www.kyoto-happy.co.jp/shop_search/"><span>提携先にお持ち込みできます(全国対応)</span><br /><i class="fa fa-angle-right" aria-hidden="true"></i>現在地から提携先ショップ検索</a></div>
								<li><a href="/shop/brand/tomorrowland/"><img src="https://www.kyoto-happy.co.jp:8443/_assets/img/index2019/partner_logo_01.gif" alt="TOMORROWLAND"></a></li>
								<li><a href="/shop/brand/beams/"><img src="https://www.kyoto-happy.co.jp:8443/_assets/img/index2019/partner_logo_02.gif" alt="BEAMS"></a></li>
								<li><a href="/shop/brand/united-arrows/"><img src="https://www.kyoto-happy.co.jp:8443/_assets/img/index2019/partner_logo_03.gif" alt="UNITED ARROWS"></a></li>
								<li><a href="/shop/brand/aquascutum/"><img src="https://www.kyoto-happy.co.jp:8443/_assets/img/index2019/partner_logo_04.gif" alt="Aquascutum"></a></li>
								<li><a href="/shop/brand/durban/"><img src="https://www.kyoto-happy.co.jp:8443/_assets/img/index2019/partner_logo_05.gif" alt="DURBAN"></a></li>
								<li><a href="/shop/brand/sinjuku_takashimaya/"><img src="https://www.kyoto-happy.co.jp:8443/_assets/img/index2019/partner_logo_06.gif" alt="新宿タカシマヤ"></a></li>
								<li><a href="/shop/brand/seibu_ikebukuro/"><img src="https://www.kyoto-happy.co.jp:8443/_assets/img/index2019/partner_logo_07.gif" alt="西武池袋本店"></a></li>
								<li><a href="/shop/brand/abeno_harukas/"><img src="https://www.kyoto-happy.co.jp:8443/_assets/img/index2019/partner_logo_08.gif" alt="あべのハルカス 近鉄本店"></a></li>
								<li><a href="/shop/brand/yokohama_takashimaya/"><img src="https://www.kyoto-happy.co.jp:8443/_assets/img/index2019/partner_logo_09.gif" alt="横浜タカシマヤ"></a></li>
								<li><a href="/shop/brand/komehyo/"><img src="https://www.kyoto-happy.co.jp:8443/_assets/img/index2019/partner_logo_10.gif" alt="KOMEHYO"></a></li>
							</ul>
						</div>
					</div>
				</div>

				<div class="contents_partner-hermes PCpart">
					<div class="contents_img right">
						<div class="partner_hermes"><a href="tel:0120-88-3040"><img src="https://www.kyoto-happy.co.jp:8443/_assets/img/index2019/partner_tel.png" alt="エルメス公認 お客様ご愛用ダイヤル 0120-88-3040"></a></div>
					</div>
				</div>
				<div class="tel_section"><a href="tel:0120-88-3040"><img src="https://www.kyoto-happy.co.jp:8443/_assets/img/index2019/tel2_sp.gif" alt="エルメス公認 お客様ご愛用ダイヤル"></a></div>

				<div class="contents_wardrobe">
					<div class="contents_txt right">
						<div class="contents_txt_wrap">
							<h2 class="section_ttl"><span>保管お預かり</span>ハッピーワードローブ<sup>&reg;</sup></h2>
							<p>私たちは、服を長く着続けることを考えています。<br class="SPpart">そのために環境を整えて大切にお預かりしているのです。</p>
						</div>
					</div>
					<div class="contents_img left">
						<div class="contents_boldtxt"><img src="https://www.kyoto-happy.co.jp:8443/_assets/img/index2019/wardrobe_bg-txt.png" alt="服は息をしている"></div>
						<div class="contents_btn"><a href="/carementeh/service/wardrobe/"><i class="fa fa-angle-right" aria-hidden="true"></i>ハッピーワードローブを見る</a></div>
					</div>
				</div>

				<div class="contents_reuse">
					<div class="contents_txt left">
						<div class="contents_txt_wrap">
							<h2 class="section_ttl">自然循環型産業の創出</h2>
							<p>「ハッピーケアメンテ®」は、良い服／良いモノを長もちさせる究極の“自然循環型産業”です</p>
						</div>
					</div>
					<div class="contents_img right">
						<div class="contents_btn"><a href="/corporate/csr/reuse/"><i class="fa fa-angle-right" aria-hidden="true"></i>自然循環型産業の創出を見る</a></div>
					</div>
				</div>

			</section>

			<section class="order_section">
				<ul>
					<li class="order_general">
						<h2>ハッピーケアメンテ<sup>&reg;</sup>を利用する</h2>
						<h3>様々なご注文方法で<br>ケアメンテ<sup>&reg;</sup>をご利用いただけます。</h3>
						<p>クリーニングの悩みや困りごとを<br class="SPpart">ハッピーケアメンテが解消します。<br>お客様に合わせた豊富なご注文方法とメニューで<br>あなたの大事な衣服をお預かりします。</p>
						<div class="order_link">
							<a href="/use/"><i class="fa fa-angle-right" aria-hidden="true"></i>ご利用方法</a>
							<a href="/use/price/pricelist/"><i class="fa fa-angle-right" aria-hidden="true"></i>価格表</a>
						</div>
						<div class="contents_btn"><a href="/order/form.html"><i class="fa fa-angle-right" aria-hidden="true"></i>ご注文はこちら</a></div>
					</li>
					<li class="order_company">
						<h2>企業様からのご依頼もどうぞ</h2>
						<h3>クリーニング店・アパレル・<br class="SPpart">飲食店レストラン・百貨店・<br>ホテル・ヘアサロン・リサイクルショップ  etc...</h3>
						<p>クリーニングの駆け込み寺&reg;<br class="SPpart">「ハッピー」がお手伝いします。<br>どうしても落ちないシミ汚れ、黄ばみ、ニオイ。<br>復元が難しいシルエット etc...<br>そんなお悩み・困りごとの解決を...。</p>
						<div class="contents_btn"><a href="/order/form.html"><i class="fa fa-angle-right" aria-hidden="true"></i>企業様からのご注文・お申込みはコチラ</a></div>
					</li>
				</ul>
			</section>

			<section class="banner_section">
				<ul>
					<li><a href="/movie/"><div class="banner_bg"><picture><source srcset="https://www.kyoto-happy.co.jp:8443/_assets/img/index2019/banner_img_01_sp.jpg" media="(max-width:767px)"><img src="https://www.kyoto-happy.co.jp:8443/_assets/img/index2019/banner_img_01.jpg" alt="プロモーションビデオ"></picture></div><h3><span>ケアメンテを動画でチェック</span>プロモーションビデオ</h3></a></li>
					<li><a href="/knowledge/"><div class="banner_bg"><img src="https://www.kyoto-happy.co.jp:8443/_assets/img/index2019/banner_img_02.jpg" alt="おしゃれの雑学"></div><h3><span>おしゃれを楽しむ情報満載</span>おしゃれの雑学</h3></a></li>
					<li><a href="/detail/"><div class="banner_bg"><img src="https://www.kyoto-happy.co.jp:8443/_assets/img/index2019/banner_img_03.jpg" alt="こだわりのディテール"></div><h3><span>ハッピーが厳選した事例をご紹介</span>こだわりのディテール</h3></a></li>
					<li><a href="#userVoice" class="popup"><div class="banner_bg"><img src="https://www.kyoto-happy.co.jp:8443/_assets/img/index2019/banner_img_04.jpg" alt="ケアメンテ体験者の声"></div><h3><span>続々と寄せられる「きれい」の声</span>ケアメンテ体験者の声</h3></a></li>
					<li><a href="/corporate/media/past/"><div class="banner_bg"><img src="https://www.kyoto-happy.co.jp:8443/_assets/img/index2019/banner_img_05.jpg" alt="報道一覧"></div><h3><span>メディアで紹介された情報を掲載</span>報道一覧</h3></a></li>
				</ul>
				<!--userVoice Popup-->
				<div style="display:none;" class="news_headline-detail">
					<section id="userVoice">
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
							<p class="arrow"><span>私たちが解決します</span><br><img src="https://www.kyoto-happy.co.jp:8443/_assets/img_sp/common_page/icon_arrow_off.png"></p>
							<ul class="block">
								<li><h5>お客さまの評判</h5><div><a href="/review/"><img src="https://www.kyoto-happy.co.jp:8443/_assets/img/index/icn_sns02.png" alt="きづく">お客さまレビュー『きづく』</a><br><a href="/use/evaluate/blog/">お客さまのブログ（体験談）</a><p>あなたの質問・疑問にハッピーケアメンテ体験者のお客さまがお答えします。</p></div></li>
								<li><h5>ビフォー・アフター事例集1800点</h5><div><a href="/carementeh_search/"><img src="https://www.kyoto-happy.co.jp:8443/_assets/img/index/icn_sns01.png" alt="さがす">ケアメンテ検索エンジン『さがす』</a><br class="PCpart"><p>お手持ち衣服に近い衣服をさがして、ケアメンテの仕上り感をイメージしていただけます。</p></div></li>
							</ul>
						</div>
					</section>
				</div>
			</section>

			<section class="more_section">
				<div class="contents_reading">
					<ul>
						<li class="reading_comic">
							<div class="reading_img"><img src="https://www.kyoto-happy.co.jp:8443/_assets/img/index2019/comic_img2.jpg" alt="服はあなたの分身・魂です 「もっと服が輝く」"></div>
							<div class="reading_txt">
								<h2>マンガで分かる<br>「ケアメンテサービス」<span>ケアメンテであなたのファッションライフが変わる</span></h2>
								<p>いい服を長く楽しむ新習慣<br>新しい衣文化価値を創造します</p>
								<div class="contents_btn"><a href="https://www.kyoto-happy.co.jp:8443/pdf/Manga_01.pdf?ver1.0" target="_blank"><i class="fa fa-angle-right" aria-hidden="true"></i>マンガを読む</a></div>
							</div>
						</li>
						<li class="reading_sachi">
							<div class="reading_img"><img src="https://www.kyoto-happy.co.jp:8443/_assets/img/index2019/sachi_img_v25.jpg?191003" alt="幸sachi"><div class="reading_img_new"><img src="https://www.kyoto-happy.co.jp:8443/_assets/img/index2019/sachi_new.png" alt="最新刊"></div></div>
							<div class="reading_txt">
								<h2><img src="https://www.kyoto-happy.co.jp:8443/_assets/img/index2019/sachi_ttl.gif" alt="京の伝統工芸職人を追う WEBマガジン 幸sachi"></h2>
								<h3><span>Vol. 25　中村藤𠮷本店</span>甘味や旨味の中に「苦渋味」を感じる<br class="PCpart">お茶本来の味わいを楽しんでほしい</h3>
								<div class="contents_btn"><a href="/sachi/"><i class="fa fa-angle-right" aria-hidden="true"></i>幸sachiを読む</a></div>
							</div>
						</li>
					</ul>
				</div>
				<div class="contents_app">
					<a href="/use/howtoorder/apps/">
						<div class="app_img"><img src="https://www.kyoto-happy.co.jp:8443/_assets/img/index2019/app_img.jpg" alt="ケアメンテ"></div>
						<div class="app_txt">
							<h2><img src="https://www.kyoto-happy.co.jp:8443/_assets/img/index2019/app_icon.png" alt="ケアメンテ"></h2>
							<div class="app_store"><img src="https://www.kyoto-happy.co.jp:8443/_assets/img/index2019/app_store.gif" alt="Apple Android"></div>
							<p>ケアメンテアプリは、ケアメンテ事例集「さがす」や、ご依頼品のご注文、マイページでケアメンテご依頼品のご利用履歴の確認や電子カルテの閲覧など、お手持ち衣類の管理ツールとしてもご活用いただける便利なアプリです。</p>
						</div>
					</a>
				</div>

				<div class="contents_sns">
					<ul class="sns_list">
						<li>
							<a href="/carementeh_search/">
								<div class="sns_list_img"><img src="https://www.kyoto-happy.co.jp:8443/_assets/img/index2019/sns_img_01.jpg" alt="さがす"></div>
								<div class="sns_list_txt">
									<h3>さがす<span>Before &amp; After実例集</span></h3>
									<p>Before &amp; After実例集から検索して仕上がり感をイメージできます。</p>
								</div>
							</a>
						</li>
						<li>
							<a href="/review/">
								<div class="sns_list_img"><img src="https://www.kyoto-happy.co.jp:8443/_assets/img/index2019/sns_img_02.jpg" alt="きづく"></div>
								<div class="sns_list_txt">
									<h3>きづく<span>お客様レビュー</span></h3>
									<p>過去にケアメンテをご利用いただいたお客様の”体験談”をご紹介します。</p>
								</div>
							</a>
						</li>
						<li>
							<a href="/mypage/sns.html">
								<div class="sns_list_img"><img src="https://www.kyoto-happy.co.jp:8443/_assets/img/index2019/sns_img_03.jpg" alt="つなぐ"></div>
								<div class="sns_list_txt">
									<h3>つなぐ<span>ハッピー コミュニケーションSNS</span></h3>
									<p>会員登録のご利用のお客様間で情報共有ができます。</p>
								</div>
							</a>
						</li>
						<li>
							<a href="/mypage/">
								<div class="sns_list_img"><img src="https://www.kyoto-happy.co.jp:8443/_assets/img/index2019/sns_img_04.jpg" alt="マイページ"></div>
								<div class="sns_list_txt">
									<h3>マイページ<span>お客様専用ページ</span></h3>
									<p>ケアメンテのご利用履歴などが画像付きでいつでも確認できます。</p>
								</div>
							</a>
						</li>
					</ul>
				</div>
			</section>

			<section class="article_section">
				<div class="contents_news">
					<h2>News</h2>
					<ul class="news_list">
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

						<li><a href="<?php echo get_news_permalink()?>"><span class="title"><?php the_time('Y.m.d')?></span><span class="text"><?php the_title()?></span></a></li>
						<?php endforeach; ?>
					</ul>
					<div class="more_link"><a href="/news/"><i class="fa fa-angle-right" aria-hidden="true"></i>もっと見る</a></div>
				</div>

				<div class="contents_faq">
					<h2>FAQ</h2>
					<ul class="faq_list">
						<?php
							$args = array(
								'post_type' => 'faq',
								'posts_per_page' => 4,
								'meta_query' => array(
									'relation' => 'OR',
									array(
									   'key' => 'faq',
									   'value' => true,
									   'compare' => 'NOT EXISTS'
									),
									array(
									  'key' => 'faq',
									  'value' => '1',
									  'compare' => '!='
									),
								)
								);
								$my_posts = get_posts( $args );

								foreach ( $my_posts as $post ):
				        ?>

						<li><a href="/faq/"><span class="title">Q</span><span class="text"><?php the_title()?></span></a></li>
						<?php endforeach; ?>
					</ul>
					<div class="more_link"><a href="/faq/"><i class="fa fa-angle-right" aria-hidden="true"></i>もっと見る</a></div>
				</div>
			</section>

			<section class="link_section">
				<ul class="link_slide">
					<!--
					<li><a href="/mailmag/"><img src="https://www.kyoto-happy.co.jp:8443/_assets/img/index/link_4th_01.gif" alt="メールマガジン登録 Mail Magazine"><span>メールマガジン登録</span></a></li>
					-->
					<li><a href="/corporate/recruit/cultivation/"><img src="https://www.kyoto-happy.co.jp:8443/_assets/img/index/link_4th_02.gif" alt="リクルート Recruit"><span>リクルート</span></a></li>
					<li><a href="/corporate/media/literary/"><img src="https://www.kyoto-happy.co.jp:8443/_assets/img/index/link_4th_03.gif" alt="ハッピーの著作物一覧 Book"><span>ハッピーの著作物一覧</span></a></li>
					<li><a href="/sale/"><img src="https://www.kyoto-happy.co.jp:8443/_assets/img/index/link_4th_04.gif" alt="SALE 優待券を取得"><span>SALE</span></a></li>
					<li><a href="/carementeh/overview/etymology/"><img src="https://www.kyoto-happy.co.jp:8443/_assets/img/index/link_4th_05.gif" alt="ケアメンテの語源 Etymology"><span>ケアメンテの語源</span></a></li>
					<li><a href="http://www.hashimoto-hideo.com" target="_blank" rel="nofollow"><img src="https://www.kyoto-happy.co.jp:8443/_assets/img/index/link_4th_06.gif" alt="当社代表のオフィシャルサイト 橋本英夫 Official Site"><span>橋本英夫 Official Site</span></a></li>
				</ul>
			</section>

			<section class="award_section">
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
		</div>
		<!--/Contents-->

<?php get_footer() ?>
