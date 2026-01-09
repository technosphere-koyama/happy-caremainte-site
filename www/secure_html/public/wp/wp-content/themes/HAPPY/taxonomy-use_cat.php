<?php get_header(); 

$term = $wp_query->queried_object;

 $tax_name = 'use_cat';
 $posttype = 'use';
 $POSTID = $term->term_id;
 $current_cat = $term->term_id;
 
 ?>


<div id="Contents">


	<div class="mainvisual__section">
        <div>USE<br><p>ご注文方法／価格表</p></div>
	</div>
    
	<?php breadcrumb(); ?>

    <div class="content">
        
        <div class="LColumn <?php echo attribute_escape( $post->post_name ); ?>">
    	<div class="pagettl"><h1><?php single_tag_title(); ?></h1></div>
        
		<?php echo get_field('use_cat_content',$term) ?>
		
		
		 </div> 
        
<?php 
	get_template_part('nav','pcrcolumn');
?>
        
    </div><!--/content-->


</div><!--/Contents-->


<?php 
	get_template_part('nav','spfooter');
?>


<?php 
get_footer(); ?>
