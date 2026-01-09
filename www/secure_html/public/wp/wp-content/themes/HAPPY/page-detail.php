<?php
/*
Template Name: こだわりのディティール

*/
?>

<?php get_header(); ?>
  
	<div id="Contents">
		<div class="mainvisual__section">
        <div>DETAIL<br><p>こだわりのディティール</p></div>
		</div>
	
		<div id="pankuzu-wrapp"><div class="pan-border"><p class="pankuzu"><a href="/">ハッピーケアメンテ トップ</a></p><p class="pankuzu"><a href="/detail/">こだわりのディティール</a></p><p class="pankuzu no-arrow"><?php wp_title(); ?></p></div></div>
	
		<div class="content">
       		
            <?php if(have_posts()): while(have_posts()): the_post(); ?>
            <?php remove_filter('the_content', 'wpautop'); ?>
			<?php the_content(); ?>
			<?php endwhile; endif; ?>
        
		</div><!--/content--> 
    
  </div><!--/Contents--> 
  
<?php get_footer(); ?>
