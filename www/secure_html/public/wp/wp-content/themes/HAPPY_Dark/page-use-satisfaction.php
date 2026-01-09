<?php
/*
Template Name: ハッピー顧客満足度指数

*/
?>

<?php get_header(); ?>

	<div id="Contents">
		<div class="mainvisual__section">
        <div>USE<br><p>ご注文方法／価格表</p></div>
		</div>

		<div id="pankuzu-wrapp"><div class="pan-border"><p class="pankuzu"><a href="/">トップ</a></p><p class="pankuzu"><a href="/use/">ご注文方法／価格表</a></p><p class="pankuzu"><a href="/use/cat/evaluate/">ケアメンテの評価</a></p><p class="pankuzu"><a href="/use/evaluate/satisfaction/">ハッピー顧客満足度指数</a></p><p class="pankuzu no-arrow"><?php the_title(); ?></p></div></div>

		<div class="content">

        <div class="LColumn satisfaction">
        <div class="pagettl"><h1><?php the_title(); ?></h1></div>
    	<div class="pagettl-sub"><?php the_field('subtitle') ?></div>

            <?php if(have_posts()): while(have_posts()): the_post(); ?>
            <?php remove_filter('the_content', 'wpautop'); ?>
			<?php the_content(); ?>
			<?php endwhile; endif; ?>

		 </div>

		<!--div class="RColumn PCpart">
            <div class="localNav">
            	<ul>
					<li class="firstRow ">
						<a>ご注文方法</a>
						<ul class="open">
						<li><a href="/use/howtoorder/tel/">電話・FAXから</a></li>
						<li><a href="/use/howtoorder/web/">ホームページから</a></li>
						<li><a href="/use/howtoorder/apps/">スマホアプリから</a></li>
						<li><a href="/use/howtoorder/shop/">提携SHOPから</a></li>
						<li><a href="/use/howtoorder/mail/">郵便局・コンビニから</a></li>
						<li><a href="/use/howtoorder/payment/">お支払方法</a></li>
						<li><a href="/use/howtoorder/point/">ハッピーポイントについて</a></li>
						<li><a href="/use/howtoorder/reparation/">事故賠償制度</a></li>
						<li><a href="/use/howtoorder/package/">美しいシルエットのままお届けするために</a></li>
						<li><a href="/use/howtoorder/reasonable/">ケアメンテをリーズナブルにご利用いただく方法</a></li>
						<li><a href="/use/howtoorder/similarity/">類似サービスにご注意ください</a></li>
						</ul>
						</li>
						<li class="">
						<a>価格表／カタログ請求</a>
						<ul class="open">
						<li><a href="/use/price/pricelist/">価格表</a></li>
						<li><a href="/use/price/catalog/">カタログ請求／PDF閲覧</a></li>
						</ul>
						</li>
						<li class="down">
						<a>ケアメンテの評価</a>
						<ul class="open">
						<li><a href="/use/evaluate/blog/">ブログでの第三者評価</a></li>
						<li><a href="/use/evaluate/value/">ケアメンテとクリーニングの評価</a></li>
						<li class="stay"><a href="/use/evaluate/satisfaction/">ハッピー顧客満足度指数</a></li>
				</ul>
            </div>
        </div-->

		</div><!--/content-->

  </div><!--/Contents-->

<?php get_footer(); ?>
