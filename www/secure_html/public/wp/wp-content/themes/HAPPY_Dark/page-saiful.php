<?php get_header(); ?>
<link rel="stylesheet" href="https://www.kyoto-happy.co.jp/wp/wp-content/themes/HAPPY_Dark/css/real_value.css">
<style>
.content a {color:#0000ff; word-break: break-all;}
.saiful-title {font-weight:bold;margin-bottom:10px}
</style>
	<div id="Contents">
		<div class="mainvisual__section real_value__back">
		        <div>CORPORATE<br><p><?php the_title() ?></p></div>
		</div>
		<?php breadcrumb(); ?>
		<div class="content">
			<div class="saiful-title">■ <?php the_title() ?></div>
			<p><?php the_field('text-01'); ?><a href="<?php the_field('text-01'); ?>" target="_blank"><?php the_field('link-text-01'); ?></a></p>
			<div class="saiful-title"><?php the_field('title-02'); ?></div>
			<?php the_content(); ?>
			<p><?php the_field('text-02-2'); ?></p>
			<div class="saiful-title"><?php the_field('title-03'); ?></div>
			<p><?php the_field('text-03'); ?></p>
			<div class="saiful-title"><?php the_field('title-04'); ?></div>
			<p><?php the_field('text-04'); ?></p>
			<div class="saiful-title"><?php the_field('title-05'); ?></div>
			<p><?php the_field('text-05'); ?></p>
			<div class="saiful-title"><?php the_field('title-06'); ?></div>
			<p><?php the_field('text-06'); ?><br />詳しくは、<a href="<?php the_field('link-06-01'); ?>" target="_blank"><?php the_field('link-text-06-01'); ?></a>、<a href="<?php the_field('link-06-02'); ?>" target="_blank"><?php the_field('link-text-06-02'); ?></a></p>

		</div><!--/content--> 
	</div><!--/Contents--> 
<?php get_footer(); ?>
