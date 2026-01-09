<?php get_header(); ?>
<link rel="stylesheet" href="https://www.kyoto-happy.co.jp/wp/wp-content/themes/HAPPY_Dark/css/infomag.css">
	<div id="Contents">
		<div class="mainvisual__section infomag__back">
        <div>Happyケアメンテ技術通信<br><p>バックナンバー</p></div>
		</div>
	
		<?php breadcrumb(); ?>
	
		<div class="content">
        
            <div class="news__section">
            <ul class="infomag">
<?php 
			$args = array(
				'post_type' => array('infomag'),
				'posts_per_page' => -1,
			);
			$posts = get_posts($args);
			foreach($posts as $post): the_post();
?>
				<li><a href="<?php echo get_news_permalink()?>"><span class="date"><?php the_time('Y.m.d') ?></span>配信<br /><span class="text"><?php the_title() ?></span></a></li>
<?php endforeach; wp_reset_postdata(); ?>

			</ul>         
		</div><!--/content--> 
    
  </div><!--/Contents--> 
  
<?php get_footer(); ?>
