<?php get_header(); ?>

	<div id="Contents">
		<div class="mainvisual__section">
			<div>USE<br><p>ご利用方法・価格表</p></div>
		</div>

		<?php breadcrumb(); ?>

<div class="content">
			<div class="pagettl-large">
				<h2>ケアメンテ&reg;を推奨する<br class="sp">全国のブランドやデパートで<br>ご依頼品のお預かりを受け付けております。</h2>
			</div>
			<div class="searchBtn tac spPart">
				<a href="/shop_search/" class="linkBtnCommon">現在地から検索</a>
			</div>

			<ul class="section">
<?php
	$flg = 0;
	$args = array(
		'parent' => 0,
		'pad_counts' => true,
		'hide_empty' => 0
	);

	$terms = get_terms( 'list' , $args );
	foreach($terms as $term){
		$term_link = get_term_link( $term, 'list' );
		$photo = get_field('brand_logo',$term);
		$logo = wp_get_attachment_image_src($photo, 'full');

		if ( is_wp_error( $term_link ) ) {
			continue;
		}
		echo '<li><a href="'.$term_link.'"><img src="'.$logo[0].'" alt="'.$term->name.'"></a>'."\n";
		echo  '<p class="midashi"><a href="'.$term_link .'">'.$term->name.'</a></p>'."\n";
		echo  '</li>'."\n";

	}
?>
			</ul>

		</div><!--/content-->

  </div><!--/Contents-->

<?php get_footer(); ?>
