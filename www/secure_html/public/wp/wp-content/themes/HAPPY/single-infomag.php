<?php
/*
Template Name: メールマガジン用

*/
?>
<?php get_header();
if(have_posts()): while(have_posts()): the_post();
$posttype = 'post';
$POSTID = $post->ID;
$current_cat =  '';
?>
<link rel="stylesheet" href="https://www.kyoto-happy.co.jp/wp/wp-content/themes/HAPPY_Dark/css/infomag.css">
<div id="Contents" class="care01">
	<div class="mainvisual__section infomag__back">
		<div>Happyケアメンテ通信<br /><p><?php the_time('Y.m.d')?> 配信／メールマガジン</p></div>
	</div>

	<?php breadcrumb(); ?>

	<div class="content">

		<div class="LColumn">
			<span class="news_date"><?php the_time('Y.m.d')?></span>
			<h1 class="news_title"><?php the_title()?></h1>
			<div class="news_entry">
				<?php the_field('mail-text'); ?>
<?php the_content(); ?>
			</div>
		</div>

		<?php // get_template_part('nav','pcrcolumn'); ?>
	</div><!--/content-->

</div><!--/Contents-->

<?php endwhile; endif;
get_footer(); ?>
