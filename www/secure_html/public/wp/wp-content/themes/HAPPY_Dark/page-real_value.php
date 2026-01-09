<?php get_header(); ?>
<link rel="stylesheet" href="https://www.kyoto-happy.co.jp/wp/wp-content/themes/HAPPY_Dark/css/real_value.css">
<style>
#A {margin-top:-100px;padding-top:100px;}
</style>
	<div id="Contents">
		<div class="mainvisual__section real_value__back">
		        <div>CORPORATE<br><p><?php the_title() ?></p></div>
		</div>
		<?php breadcrumb(); ?>
		<div class="content">
			<div class="real_value"><?php the_field('text-01'); ?></div>
			<p><?php the_field('text-02'); ?></p>
			<div id="A"></div>
			<p><?php the_field('text-02-01'); ?></p>
			<table class="real_value_table">
				<tr>
					<td><img src="<?php the_field('images-01'); ?>" alt="<?php the_title() ?>｜<?php the_field('text-01'); ?>" /></td>
					<td><img src="<?php the_field('images-02'); ?>" alt="<?php the_title() ?>｜<?php the_field('text-01'); ?>" /></td>
					<td><img src="<?php the_field('images-03'); ?>" alt="<?php the_title() ?>｜<?php the_field('text-01'); ?>" /></td>
				</tr>
			</table>
			<p><?php the_field('text-03'); ?></p>
			<div class="real_value_img"><img src="<?php the_field('images-04'); ?>" alt="<?php the_title() ?>｜<?php the_field('text-01'); ?>" /></div>
			<p><?php the_field('text-04'); ?></p>
			<div class="real_value_img"><img src="<?php the_field('images-05'); ?>" alt="<?php the_title() ?>｜<?php the_field('text-01'); ?>" /></div>
			<p><?php the_field('text-05'); ?></p>
			<div class="LColumn ">
				<p class="btns">
					<a class="linkBtnCommon" href="<?php the_field('link-01'); ?>"><?php the_field('link-text-01'); ?></a>
				</p>
			</div>
		</div><!--/content--> 
	</div><!--/Contents--> 
<?php get_footer(); ?>
