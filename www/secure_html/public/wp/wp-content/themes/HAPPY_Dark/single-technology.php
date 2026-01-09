<?php get_header();

 if(have_posts()): while(have_posts()): the_post();
 $tax_name = 'technology_cat';
 $posttype = 'technology';
 $POSTID = $post->ID;
 $cat =  get_the_terms( $post ->ID, 'technology_cat' );
 $parent_cat = $cat[0]->parent;
 $current_cat = $cat[0]->term_id;
?>

<div id="Contents" class="service before_after data">
<?php if($current_cat==41 || get_the_ID()==386): ?>
    <div class="mainvisual__section before_after_ttl">
        <div>CASE<br><p>事例・レビュー</p></div>
    </div>
<?php else : ?>
  <div class="mainvisual__section service_ttl">
      <div>SERVICE<br><p>サービス・技術</p></div>
  </div>
<?php endif; ?>

<?php $current_url = get_the_permalink();
if ( strpos( $current_url, "/technology/data/weightlessness" ) !== FALSE ) {
  get_template_part('shared/lnavi-technology-data-weightlessness');
} elseif ( strpos( $current_url, "/technology/data/tradition" ) !== FALSE ) {
  get_template_part('shared/lnavi-technology-data-tradition');
} ?>
    <?php breadcrumb(); ?>

    <div class="content">

        <div class="LColumn <?php echo attribute_escape( $post->post_name ); ?>">
          <div class="pagettl"><h1><?php the_title(); ?></h1></div>
          <div class="pagettl-sub"><?php the_field('subtitle') ?></div>

          <?php remove_filter('the_content', 'wpautop'); ?>
          <?php the_content(); ?>

          <?php get_template_part( 'nav', 'technology' ); ?>
        </div>
    </div><!--/content-->


</div><!--/Contents-->

<?php endwhile; endif;
get_footer(); ?>
