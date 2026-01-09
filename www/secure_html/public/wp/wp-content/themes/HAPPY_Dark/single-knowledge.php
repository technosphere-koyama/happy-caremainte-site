<?php get_header();

 if(have_posts()): while(have_posts()): the_post();
 $posttype = 'knowledge';
 $POSTID = $post->ID;
 $current_cat =  '';
?>


<div id="Contents" class="care01">


	<div class="mainvisual__section">
		<div>READING<br><p>特集・読みもの</p></div>
	</div>

	<?php breadcrumb(); ?>

	<div class="content">
		<div class="pagettl"><h1><?php the_title()?></h1></div>
		<?php remove_filter('the_content', 'wpautop'); ?>
		<?php the_content(); ?>
		<div class="btn"><a href="/knowledge/" class="linkBtnCommon smallBtn">目次に戻る</a></div>

	</div><!--/content-->


</div><!--/Contents-->

<?php endwhile; endif;
get_footer(); ?>
