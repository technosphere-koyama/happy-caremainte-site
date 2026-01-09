<?php
/*
Template Name: 幸 sachi

*/
?>

<?php get_header(); ?>

<div id="Contents" class="sachi">
		<div class="content">
       		
            <?php if(have_posts()): while(have_posts()): the_post(); ?>
            <?php remove_filter('the_content', 'wpautop'); ?>
			<?php the_content(); ?>
			<?php endwhile; endif; ?>
			
<?php get_template_part( 'parts', 'sachi' ); ?>
        
		</div><!--/content--> 
</div><!--/Contents--> 

<?php get_footer(); ?>
