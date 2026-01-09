<?php get_header();
if ( have_posts() ) :
	while ( have_posts() ) : the_post();

 $tax_name = 'list';
 $posttype = 'shop';
 $POSTID = $post->id;
 $terms = get_the_terms( $POSTID, $tax_name );
 $current_cat = $terms[0]->term_id;

?>


	<div id="Contents">
		<div class="mainvisual__section">
			<div>USE<br><p>ご利用方法・価格表</p></div>
		</div>

	<?php breadcrumb(); ?>

	<div class="content">

		<div class="LColumn">
			<div class="pagettl"><h1><?php the_title(); ?></h1></div>
			<div class="pagettl-sub"></div>
			<?php echo get_field('brand_contents',$term) ?>


			<dl class="listdetail">
				<dt><h6>住所</h6></dt>
				<dd><?php the_field('shop_zip') ?><br><?php the_field('shop_address') ?></dd>
				<dt><h6>電話番号</h6></dt>
				<dd><?php the_field('shop_tel') ?></dd>
			</dl>

		   <iframe src="https://maps.google.co.jp/maps?q=<?php the_field('shop_latitude')?>,<?php the_field('shop_longitude')?>&output=embed&t=m&z=16&hl=ja" frameborder="0" scrolling="no" marginheight="0" marginwidth="0" width="100%" height="400"></iframe>

			<p class="store-return"><a href="javascript:history.back();"><?php echo $terms[0]->name ?>の取り扱い店舗一覧に戻る</a></p>

		</div>

	</div><!--/content-->
</div><!--/Contents-->
<?php
	endwhile;
endif;
get_footer(); ?>
