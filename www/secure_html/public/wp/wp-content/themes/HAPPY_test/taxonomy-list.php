<?php get_header(); 


 $tax_name = 'list';
 $posttype = 'shop';
 $term = get_term_by('slug', $term, 'list');
 $POSTID = $term->term_id;
 $current_cat = $term->term_id;

?>


 <div id="Contents">
        <div class="mainvisual__section">
            <div>BRAND/SHOP LIST<br><p>提携ブランド／全国取扱い店舗一覧</p></div>
        </div>
    
    <?php breadcrumb(); ?>
    
	<div class="content">

		 <div class="LColumn">
    	<div class="pagettl"><h1><?php single_tag_title(); ?></h1></div>
		<?php echo get_field('brand_contents',$term) ?>

		<?php if ( have_posts() ): ?>
		<h3>取扱い店舗</h3>
            <div class="section-imgCenter">
                <p class="mgB20">以下の<?php echo $term->name ?> 店舗で、ハッピーケアメンテサービスを受付けております。</p>
            </div>
        <?php
		$args = array(
			'taxonomy' => 'area',
			'parent' => 0,
			'pad_counts' => true,
		);
		
		$areas = get_categories( $args );
		
		foreach($areas as $area){
			$args = array(
				'post_type' => $posttype,
				'posts_per_page' => -1,
				'tax_query' => array(
					'relation' => 'AND',
					array(
						'taxonomy' => 'area',
						'field' => 'slug',
						'terms' => $area->slug
					),
					array(
						'taxonomy' => 'list',
						'field' => 'slug',
						'terms' => $term->slug,
					)
				)
			);
			$posts = get_posts($args);
			
			if( $posts ){
				echo '<div class="shopSearch area">'."\n";
				echo '<h5 class="accordionTxt">'.$area->name.'</h5>'."\n";
				echo '<div class="accordionWrap">'."\n";
				
				foreach($posts as $post){
            		echo '<ul>'."\n";
                    echo '<li><a href="'.get_the_permalink().'">'.get_the_title().'</a></li>'."\n";
                    echo '<li>'.get_field('shop_zip').'<br>'.get_field('shop_address').'</li>'."\n";
                    echo '<li>'.get_field('shop_tel').'</li>'."\n";
                    echo '</ul>'."\n";
				}
				echo '</div>'."\n";
				echo '</div>'."\n";
			}

		}
		
		endif; ?>

        </div>            
<?php 
	get_template_part('nav','pcrcolumn');
?>



    </div><!--/content-->



</div><!--/Contents-->


<?php 
	get_template_part('nav','spfooter');
?>


<?php get_footer(); ?>