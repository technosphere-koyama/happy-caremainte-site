<?php get_header();

 if(have_posts()): while(have_posts()): the_post();
 $tax_name = 'corporate_cat';
 $posttype = 'corporate';
 $POSTID = $post->ID;
 $current =  get_the_terms( $post ->ID, 'corporate_cat' );
 $current_cat = $current[0]->term_id;
 $current_cat_slug = $current[0]->slug;
?>

<div id="Contents" class="<?php echo $current_cat_slug;?>">

	<div class="mainvisual__section">
		<div>CORPORATE<br><p>会社情報</p></div>
	</div>

	<?php breadcrumb(); ?>

    <div class="content">
    	<div class="pagettl"><h1><?php the_title()?></h1></div>

        <div class="LColumn">
					<?php remove_filter('the_content', 'wpautop'); ?>
					<?php the_content(); ?>

					<?php if( is_single('334') ) : ?>
					<div class="Donation">
						これまでの義援金
						<ul>
							<?php if(have_rows('Donation',334)): ?><?php while(have_rows('Donation',334)): the_row(); ?>
							<li><div class="left"><?php the_sub_field('disaster'); ?><br /><span><?php the_sub_field('OrganizationName'); ?></span></div><div class="right"><?php the_sub_field('date'); ?></div></li>
							<?php endwhile; ?>
							<?php endif; ?>
						</ul>
					</div>
					<?php endif; ?>
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
