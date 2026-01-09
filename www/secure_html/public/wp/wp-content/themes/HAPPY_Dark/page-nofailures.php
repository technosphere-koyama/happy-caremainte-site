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
			<?php the_content(); ?>
			<p><?php the_field('text-01'); ?></p>
			<p><?php the_field('text-02'); ?></p>
		</div><!--/content--> 
	</div><!--/Contents--> 
<?php get_footer(); ?>
