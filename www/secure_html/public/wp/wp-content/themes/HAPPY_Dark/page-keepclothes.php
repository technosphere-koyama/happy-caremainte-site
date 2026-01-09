<?php get_header(); ?>
<link rel="stylesheet" href="https://www.kyoto-happy.co.jp/wp/wp-content/themes/HAPPY_Dark/css/real_value.css">
<style>
.content a {color:#0000ff; word-break: break-all;}
</style>
	<div id="Contents">
		<div class="mainvisual__section real_value__back">
		        <div>CORPORATE<br><p><?php the_title() ?></p></div>
		</div>
		<?php breadcrumb(); ?>
		<div class="content">
			<div class="difference2-title">■ <?php the_title() ?></div>
			<p><?php the_field('text-01'); ?></p>
			<p><?php the_field('text-02'); ?></p>
			<p><?php the_content(); ?></p>
			<p><?php the_field('text-04'); ?></p>
			<p><?php the_field('text-05'); ?></p>

		</div><!--/content--> 
	</div><!--/Contents--> 
<?php get_footer(); ?>
