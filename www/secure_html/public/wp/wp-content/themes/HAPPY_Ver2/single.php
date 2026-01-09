<?php get_header(); 

 if(have_posts()): while(have_posts()): the_post();
 $posttype = 'post';
 $POSTID = $post->ID;
 $current_cat =  '';
?>


<div id="Contents" class="care01">

	
	<div class="mainvisual__section">
            <div>NEWS<br><p>更新情報一覧／ニュース</p></div>
    </div>
    
	<?php breadcrumb(); ?>

    <div class="content">
        
        <div class="LColumn">
        <span class="news_date"><?php the_time('Y.m.d')?></span>
        <h1><?php the_title()?></h1>
            <div class="news_entry">
	    	<?php remove_filter('the_content', 'wpautop'); ?>
	    	<?php the_content(); ?>
	    	 </div>
        </div>
        
<?php 
	get_template_part('nav','pcrcolumn');
?>
        
    </div><!--/content-->


</div><!--/Contents-->


<?php 
	get_template_part('nav','spfooter');
?>


<?php endwhile; endif; 
get_footer(); ?>
