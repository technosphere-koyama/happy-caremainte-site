<?php
/*
Template Name: こだわりのディテール

*/
?>

<?php get_header(); ?>

<div id="Contents">

	<div class="mainvisual__section">
		<div>READING<br><p>特集・読みもの</p></div>
	</div>

	<div id="pankuzu-wrapp"><div class="pan-border"><p class="pankuzu"><a href="/">ハッピーケアメンテ トップ</a></p><p class="pankuzu"><a href="/detail/">こだわりのディテール</a></p><p class="pankuzu no-arrow"><?php wp_title(); ?></p></div></div>

	<div class="content">

		<?php if(have_posts()): while(have_posts()): the_post(); ?>
			<?php remove_filter('the_content', 'wpautop'); ?>
			<?php the_content(); ?>
		<?php endwhile; endif; ?>

		<div class="btn"><a href="/detail/" class="linkBtnCommon">インデックスに戻る</a></div>

	</div><!--/content-->

</div><!--/Contents-->

<?php get_footer(); ?>
