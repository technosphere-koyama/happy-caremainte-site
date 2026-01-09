<?php get_header(); 

 if(have_posts()): while(have_posts()): the_post();
 $tax_name = 'use_cat';
 $posttype = 'use';
 $POSTID = $post->ID;
 $current_cat =  get_the_terms( $post ->ID, 'use_cat' );
 $current_cat = $current_cat[0]->term_id;
?>


<div id="Contents">


	<div class="mainvisual__section">
        <div>USE<br><p>ご注文方法／価格表</p></div>
	</div>
    
	<?php breadcrumb(); ?>

    <div class="content">

        <div class="LColumn <?php echo attribute_escape( $post->post_name ); ?>">
        <div class="pagettl"><h1><?php the_title(); ?></h1></div>
    	<div class="pagettl-sub"><?php the_field('subtitle') ?></div>
    	
            <?php remove_filter('the_content', 'wpautop'); ?>
            <?php the_content(); ?>
		
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
