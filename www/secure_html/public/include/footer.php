
		<div id="pageback"><a href="javascript:history.back();"><img src="https://www.kyoto-happy.co.jp:8443/_assets/img/footer/pageback.png" alt="戻る"/></a></div>
		<div id="pagetop"><img src="https://www.kyoto-happy.co.jp:8443/_assets/img/footer/pagetop.png" alt="ページトップ"/></div>

        <footer>

			<section class="fnavi">
				<div class="fnavi_main">
					<ul>
						<li class="fnavi01">
							<ul>
								<li class="headline"><a href="/use/">ご注文方法／価格表</a></li>
								<li><a href="/use/cat/howtoorder/">ご注文方法</a></li>
								<li><a href="/use/price/list/">価格表／カタログ請求</a></li>
								<li><a href="/use/evaluate/blog/">評価</a></li>
							</ul>
						</li>
						<li class="fnavi02">
							<ul>
								<li class="headline"><a href="/carementeh/">サービス概要・メニュー一覧</a></li>
								<li><a href="/carementeh/overview/style/">サービス概要</a></li>
								<li><a href="/carementeh/service/aquadry/">サービスメニュー一覧</a></li>
							</ul>
						</li>
						<li class="fnavi03">
							<ul>
								<li class="headline"><a href="/technology/">ケアメンテの技術</a></li>
								<li><a href="/technology/washing/weightlessness/">ハッピーの水系洗浄を支える技術</a></li>
								<li><a href="/technology/before_after/ripron/">Before &amp; After</a></li>
								<li><a href="/technology/data/weightlessness/ma_test/">技術を支える検証データ</a></li>
							</ul>
						</li>
						<li class="fnavi04">
							<ul>
								<li class="headline"><a href="/shop/">取扱い店舗一覧</a></li>
								<li><a href="/shop_search/">現在地から検索</a></li>
								<li><a href="/shop/brand/abeno_harukas/">ショップ情報</a></li>
							</ul>
						</li>
						<li class="fnavi05">
							<ul>
								<li class="headline"><a href="/corporate/">会社情報</a></li>
								<li><a href="/corporate/company/profile/">会社概要</a></li>
								<li><a href="/corporate/media/literary/">メディア情報</a></li>
								<li><a href="/corporate/recruit/cultivation/">リクルート</a></li>
								<li><a href="/corporate/csr/weightlessness/">環境への取組み</a></li>
								<li><a href="/corporate/europe/2013_summer/">ヨーロッパ洗浄技術交流紀行</a></li>
							</ul>
						</li>
					</ul>
				</div>
				<div class="fnavi_sub">
					<ul>
						<li><a href="/mypage/">マイページ</a></li>
						<li><a href="/knowledge/">おしゃれの雑学</a></li>
						<!--
						<li><a href="/mailmag/">メールマガジン</a></li>
						-->
						<li><a href="/movie/">ケアメンテ&reg;を動画で紹介</a></li>
						<li><a href="/faq/">よくあるご質問</a></li>
						<li><a href="/carementeh_search/">ケアメンテ実例集『さがす』</a></li>
						<li><a href="/review/">お客さまレビュー『きづく』</a></li>
						<li><a href="/mypage/sns.html">ハッピーSNS『つなぐ』</a></li>
					</ul>
				</div>
			</section>

			<section class="footer_sns">
				<ul class="wrap">
					<li><a href="https://www.facebook.com/pages/%e3%83%8f%e3%83%83%e3%83%94%e3%83%bc%2d%e3%82%b1%e3%82%a2%e3%83%a1%e3%83%b3%e3%83%86Happy%2dCareMenteh%2f107312759374049" target="_blank"><i class="fa fa-facebook" aria-hidden="true"></i></a></li>
					<li><a href="https://twitter.com/Happy_KYOTO" target="_blank"><i class="fa fa-twitter" aria-hidden="true"></i></a></li>
					<li><a href="https://www.instagram.com/happycarementeh/" target="_blank"><i class="fa fa-instagram" aria-hidden="true"></i></a></li>
					<li><a href="https://www.youtube.com/channel/UCZyJC69VvnDqIAgsEQ-rTeQ" target="_blank"><i class="fa fa-youtube" aria-hidden="true"></i></a></li>
				</ul>
			</section>

			<section class="footer_info">
				<div class="wrap">
					<div class="footer_submenu">
						<ul>
							<li><a href="/privacy/">特定商取引法に基づく表記</a></li>
							<li><a href="/contact/">お問い合わせ</a></li>
							<li><a href="/corporate/recruit/cultivation/">リクルート</a></li>
						</ul>
					</div>
					<div class="copyright">&copy; <?php echo date("Y"); ?> Happy Co., Ltd.  All Rights Reserved.</div>
				</div>
			</section>
		</footer>

		<?php require_once( dirname(__FILE__).'/../wp/wp-load.php' );
    		$args = array(
    			'post_type' => 'site_message',
    			'posts_per_page' => 1,
    		);
    		$my_posts = get_posts( $args );

    		foreach ( $my_posts as $post ): setup_postdata($post);
        ?>

        <div class="pickupMessage">
            <div class="messageClose"><img src="https://www.kyoto-happy.co.jp:8443/_assets/img/footer/close.png" alt="close"></div>
            <a href="<?php the_field('message_Link') ?>">
                <div class="messageBox">
                    <?php the_content() ?>
                </div>
            </a>
        </div>
        <?php endforeach; ?>


<?php
$webroot = $_SERVER['DOCUMENT_ROOT'];
include($webroot."/app.php");
?>
