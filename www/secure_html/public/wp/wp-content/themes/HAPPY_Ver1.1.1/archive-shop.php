<?php get_header(); ?>
  
	<div id="Contents">
		<div class="mainvisual__section">
			<div>BRAND/SHOP LIST<br><p>提携ブランド／全国取扱い店舗一覧</p></div>
		</div>
	
		<?php breadcrumb(); ?>
	
<div class="content">
			<h4>ケアメンテ&reg;を推奨する<br class="SPpart">全国のブランドやデパートで<br>
            ご依頼品のお預かりを受け付けております。</h4>
            
            <div class="searchBtn">
            	<a href="/shop_search/">現在地から検索</a>
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
