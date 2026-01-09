<?php get_header();

 if(have_posts()): while(have_posts()): the_post();
 $tax_name = 'corporate_cat';
 $posttype = 'corporate';
 $POSTID = $post->ID;
 $current =  get_the_terms( $post ->ID, 'corporate_cat' );
 $current_cat = $current[0]->term_id;
 $current_cat_slug = $current[0]->slug;
?>

<div id="Contents">

	<div class="mainvisual__section">
        <div>CORPORATE<br><p>会社情報・リクルート</p></div>
	</div>

	<div id="pankuzu-wrapp"><div class="pan-border"><p class="pankuzu"><a href="/">ハッピーケアメンテ トップ</a></p><p class="pankuzu"><a href="/corporate/">会社情報</a></p><p class="pankuzu"><a href="/corporate/media/media_list/">メディア情報</a></p><p class="pankuzu"><a href="/corporate/media/lecture/">講演活動の記録</a></p><p class="pankuzu no-arrow"><?php the_title(); ?></p></div></div>

    <div class="content">

        <div class="LColumn">
        	<div class="pagettl"><h1><?php the_title()?></h1></div>
        	<div class="pagettl-sub"></div>

           <?php the_field('meeting_edit') ?>

           <?php // ACF Gallery Field の表示
			  $images = get_field('meeting_photo'); // フィールド名の指定
			  if( $images ):
			?>
				<ul class="meeting_photo">
			<?php foreach( $images as $image ): // ループ処理の開始 ?>
			    <li><img src="<?php echo $image['url']; ?>" alt="<?php echo $image['alt']; ?>" /></li>
			<?php endforeach; ?>
				</ul>
			<?php endif; ?>

			<div class="lectureReport_backBtn"><a href="/meeting/">講演活動の記録 一覧へ</a></div>


        </div>

        <?php get_template_part('nav','corporate'); ?>
    </div><!--/content-->


</div><!--/Contents-->

<?php endwhile; endif;
get_footer(); ?>
