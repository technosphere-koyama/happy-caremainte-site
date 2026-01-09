<?php
/*
Template Name: フリー汎用ページ

*/
?>

<?php get_header(); ?>

	<div id="Contents" class="general">
	
		<div class="general_top">
			<img src="<?php the_field('header-img_pc'); ?>" alt="" class="PCpart">
			<img src="<?php the_field('header-img_sp'); ?>" alt="" class="SPpart">
		</div>
		
		<section class="general-sec">
			<?php if(have_posts()): while(have_posts()): the_post(); ?>
	        <?php remove_filter('the_content', 'wpautop'); ?>
			<?php the_content(); ?>
			<?php endwhile; endif; ?>
		</section>
  </div><!--/Contents-->
  
<?php get_footer(); ?>
