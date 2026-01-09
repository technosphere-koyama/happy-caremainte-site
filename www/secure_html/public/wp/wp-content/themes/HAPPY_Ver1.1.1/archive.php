<?php get_header(); ?>
  
	<div id="Contents">
		<div class="mainvisual__section">
        <div>NEWS<br><p>更新情報一覧</p></div>
		</div>
	
		<?php breadcrumb(); ?>
	
		<div class="content">
        
            <div class="news__section">
            <ul>
<?php if(have_posts()): while(have_posts()): the_post(); ?>
				<li><a href="<?php the_permalink() ?>"><span class="date"><?php the_time('Y.m.d') ?></span><span class="text"><?php the_title() ?></span></a></li>
<?php endwhile; endif; ?>

			</ul>        
        
		</div><!--/content--> 
    
  </div><!--/Contents--> 
  
<?php get_footer(); ?>
