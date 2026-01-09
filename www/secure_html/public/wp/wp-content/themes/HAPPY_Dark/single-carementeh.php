<?php get_header();

 if(have_posts()): while(have_posts()): the_post();
 $tax_name = 'carementeh_cat';
 $posttype = 'carementeh';
 $POSTID = $post->ID;
 $cat =  get_the_terms( $post ->ID, 'carementeh_cat' );
 $parent_cat = $cat[0]->parent;
 $current_cat = $cat[0]->term_id;
?>
<div id="Contents" class="care01 service">

	<div class="mainvisual__section">
        <div>SERVICE<br><p>サービス・技術</p></div>
	</div>

	<?php breadcrumb(); ?>

    <div class="content">

        <div class="LColumn <?php echo attribute_escape( $post->post_name ); ?>">
        <div class="pagettl"><h1><?php the_title(); ?></h1></div>
    	<div class="pagettl-sub"><?php the_field('subtitle') ?></div>

            <?php remove_filter('the_content', 'wpautop'); ?>
            <?php the_content(); ?>

		 </div>

    </div><!--/content-->


</div><!--/Contents-->

<?php endwhile; endif; ?>
<?php get_footer(); ?>
