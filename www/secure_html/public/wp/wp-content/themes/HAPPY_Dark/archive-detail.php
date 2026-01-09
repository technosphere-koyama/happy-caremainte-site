<?php get_header(); ?>

	<div id="Contents">
		<div class="mainvisual__section">
			<div>READING<br><p>特集・読みもの</p></div>
		</div>

		<?php breadcrumb(); ?>

		<div class="content">
			<div class="pagettl-large">
				<h2>いい服を知る人に愛され続ける「ケアメンテ」<br />
				～ケアメンテはクリーニングではありません～</h2>
			</div>

			<p class="index_txt">　大切なビスポークメイドやインポート衣服を安易にクリーニングに出したばかりに、生地はテカテカ、風合いやシルエットも損なわれてペタンコ、シミや汚れは落ちずにベタつき、さらには独特の石油臭…。このような経験から、自分の分身ともいえる一張羅をクリーニングに出して後悔した人は多いのではないでしょうか。<br />
			　いい服を知る人は、クリーニングとは異なる、いいメンテナンスを求めています。それが、ハッピー「ケアメンテ」です。
			</p>

			<!--<p class="index_txt2">※詳細は画像をクリックしてください。</p>-->

			<ul class="section">
<?php if(have_posts()): while(have_posts()): the_post(); ?>
				<li><a href="<?php the_permalink() ?>"><img src="<?php the_field('detail_index'); ?>" alt="<?php the_title() ?>"></a>
                	<p class="midashi"><a href="<?php the_permalink() ?>"><?php the_title() ?></a></p>
				</li>
<?php endwhile; endif; ?>
				<li><a href="/mariopecora/"><img src="https://www.kyoto-happy.co.jp:8443/_assets/img/detail/MarioPecora.jpg" alt="おしゃれの裏づけ"></a>
                	<p class="midashi"><a href="/mariopecora/">おしゃれの裏づけ</a></p>
				</li>
			</ul>

			<?php get_template_part('list','case'); ?>

			<div class="footerguide footerguide-bicolor footerguide-detail pc">
				<ul>
						<li class="fnavi-banner fnavi-package"><a href="/use/howtoorder/package/"><div class="fnaviwrap"><div class="fnaviTtl">シルエットを大切にした<br>パッケージでお届けします</div><div class="fnaviBtn PCpart">詳しくはこちら</div></div></a></li>
					</ul>
			</div>

			<!--
			<p class="index_txt">　ケアメンテでは、独自開発の「<a href="/technology/innovation/weightlessness/">無重力バランス洗浄</a>」を用いて水系洗浄をベースとしたケアをおこないます。水を使わなければ、着崩れたシルエットをリセットすることができないのです。しかし、繊細な衣服に「水」を使うことは、同時に繊維にダメージを与えるという大きなリスクを伴うため、そう簡単な技術ではありません。<br />
			　ハッピーでは、水系洗浄でリセットする衣服の繊維を保護するために、「<a href="/technology/innovation/lecirian/">レシリアン</a>」という独自のサイジング加工技術を施して、繊維本来の風合いを保つと同時に、テーラーならではの芸術的シルエットを、ハッピーのクラフトマンが「<a href="/technology/innovation/press/">シルエットプレス</a>」技術によって丹念に丁寧に再現します。だから、新品に袖を通したときの、あの“さわやか気分”が蘇るのです。<br />
			　高級衣服をケアメンテすることで「ここゾッ!」という時の一張羅があなたの気品を演出して、生き筋にパワーを与えてくれる。これが、ハッピー「ケアメンテ」が、いい服を知る多くの人々に愛され続けている所以です。
			</p>

			<p class="index_txt3">「ケアメンテ」 シャワー効果</p>
			<p class="index_img">
			<img src="https://www.kyoto-happy.co.jp:8443/_assets/img/detail/detail_img.jpg">
			<h4>ケアメンテサービス → 高級衣服の保証代行サービス</h4>
			</p>
			-->


		</div><!--/content-->

  </div><!--/Contents-->

<?php get_footer(); ?>
