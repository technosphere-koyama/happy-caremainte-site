<?php
/*
Template Name: マイページ

*/
?>

<?php get_header(); ?>
  
	<div id="Contents">
		<div class="mainvisual__section">
        <div>MY PAGE<br><p>マイページ</p></div>
		</div>
	
		<?php breadcrumb(); ?>
	
		<div class="content">
       		
            <?php if(have_posts()): while(have_posts()): the_post(); ?>
            <?php remove_filter('the_content', 'wpautop'); ?>
			<?php the_content(); ?>
			<?php endwhile; endif; ?>
        
		</div><!--/content--> 
    
  </div><!--/Contents--> 
  
<?php get_footer(); ?>
