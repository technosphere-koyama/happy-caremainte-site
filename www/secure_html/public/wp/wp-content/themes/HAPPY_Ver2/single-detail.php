<?php get_header(); 

 if(have_posts()): while(have_posts()): the_post();
 $posttype = 'detail';
 $POSTID = $post->ID;
 $current_cat =  '';
?>


<div id="Contents" class="care01">

	
	<div class="mainvisual__section">
		<div>DETAIL<br><p>こだわりのディティール</p></div>
	</div>
    
	<?php breadcrumb(); ?>

    <div class="content">
    	<div class="pagettl"><h1><?php the_title()?>　<span><?php the_field('detail_yomi'); ?></span></h1>　</div>
    	
    	<div class="detailimg">
    	<img src="<?php the_field('detail_main'); ?>" alt="<?php the_title() ?>">
    	</div>
    	
    	<div class="detailtxt">
        <?php remove_filter('the_content', 'wpautop'); ?>
		<?php the_content(); ?>
    	</div>
    	
    	<div class="btn"><a href="/detail/" class="linkBtnCommon">こだわりのディティール インデックス</a></div>
        
    </div><!--/content-->


</div><!--/Contents-->


<?php 
	get_template_part('nav','spfooter');
?>


<?php endwhile; endif; 
get_footer(); ?>
