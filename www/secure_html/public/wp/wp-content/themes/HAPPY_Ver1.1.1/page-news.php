<?php get_header(); ?>
  
	<div id="Contents">
		<div class="mainvisual__section">
        <div>NEWS<br><p>更新情報一覧</p></div>
		</div>
	
		<?php breadcrumb(); ?>
	
		<div class="content">
        
            <div class="news__section">
            <ul>
<?php 
			$args = array(
				'post_type' => 'post',
				'posts_per_page' => 20,
			);
			$posts = get_posts($args);
			foreach($posts as $post): the_post();
?>
				<li><a href="<?php echo get_news_permalink()?>"><span class="date"><?php the_time('Y.m.d') ?></span><span class="text"><?php the_title() ?></span></a></li>
<?php endforeach; wp_reset_postdata(); ?>

			</ul>        
        
		</div><!--/content--> 
    
  </div><!--/Contents--> 
  
<?php get_footer(); ?>
