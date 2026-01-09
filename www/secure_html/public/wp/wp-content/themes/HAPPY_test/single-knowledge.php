<?php get_header(); 

 if(have_posts()): while(have_posts()): the_post();
 $posttype = 'knowledge';
 $POSTID = $post->ID;
 $current_cat =  '';
?>


<div id="Contents" class="care01">

	
	<div class="mainvisual__section">
		<div>KNOWLEDGE<br><p>おしゃれの雑学</p></div>
	</div>
    
	<?php breadcrumb(); ?>

    <div class="content">
    	<div class="pagettl"><h1><?php the_title()?></h1></div>
        <?php remove_filter('the_content', 'wpautop'); ?>
		<?php the_content(); ?>
        
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
