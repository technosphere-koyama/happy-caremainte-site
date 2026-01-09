<?php
/*
Template Name: カード情報登録

*/
?>

<?php get_header(); ?>

	<div id="Contents">
		<div class="mainvisual__section">
        <div>Card registration<br><p>カード情報登録</p></div>
		</div>

		<?php breadcrumb(); ?>

		<div class="content">
			<div class="sale">
				<div class="sale_header" style="border:none;">
					<h2>カード情報登録を完了しました。</h2>
					<?php if(have_posts()): while(have_posts()): the_post(); ?>
					<?php remove_filter('the_content', 'wpautop'); ?>
		<?php the_content(); ?>
		<?php endwhile; endif; ?>
					<br />
				</div>
			</div>

		</div><!--/content-->

  </div><!--/Contents-->

<?php get_footer(); ?>
