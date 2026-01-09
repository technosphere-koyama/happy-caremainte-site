
<div class="footernavi SPpart">

<?php
	global $POSTID,$current_cat,$parent_cat,$posttype,$tax_name,$page;
	$flg = 0;
	
	if( $tax_name ){

		$args = array(
			'parent' => 0,
			'hide_empty' => false
		);

		$terms = get_terms( $tax_name , $args );
		
		foreach($terms as $term){
			$term_link = get_term_link( $term, $tax_neme );
			if ( is_wp_error( $term_link ) ) {
				continue;
			}
			
			if( $tax_name == 'list'){
				if($flg == 0){
					echo '<div class="link_menu"><a href="/shop_search/">ショップ検索</a></div>'."\n";
        			echo '<div class="main_menu active on">ショップ情報</div>'."\n";
					echo '<ul class="sub_menu">'."\n";
					$flg = 1;
				}
				if($current_cat == $term->term_id ){
					echo '<li class="on"><a href="'.$term_link.'">'.$term->name.'</a></li>'."\n";
				}else{
					echo '<li><a href="'.$term_link.'">'.$term->name.'</a></li>'."\n";
				}
				
			}else{
				$args = array(
					'post_type' => $posttype,
					'posts_per_page' => -1,
					'taxonomy' => $tax_name,
					'term' => $term->slug
				);
				$posts = get_posts($args);
			
				if( $posts ){
					if( $current_cat == $term->term_id || $parent_cat == $term->term_id){
						echo '<div class="main_menu active on">'.$term->name.'</div>'."\n";
						echo '<ul class="sub_menu">'."\n";
					}else{
						echo '<div class="main_menu">'.$term->name.'</div>'."\n";
						echo '<ul class="sub_menu" style="display:none;">'."\n";
		
					}
					
					$children = get_term_children( $term->term_id, $tax_name ); /*子カテゴリ出力*/
					
					if($children){
						foreach($children as $child){
							$chobj = get_term_by( 'id', $child, $tax_name );
							$args = array(
								'post_type' => $posttype,
								'posts_per_page' => -1,
								'taxonomy' => $tax_name,
								'term' => $chobj->slug
							);
							$child_posts = get_posts($args);

							if($current_cat == $child){
								echo '<div class="main_menu active on">'.$chobj->name.'</div>'."\n";
								echo '<ul class="sub_menu2">'."\n";
							}else{
								echo '<li><a href="'.get_pdf_check_permalink($child_posts[0]->ID).'">'.$chobj->name.'</a>'."\n";
								echo '<ul class="sub_menu2" style="display:none;">'."\n";
							}
							foreach($child_posts as $chpost){
		
									if( $chpost->ID == $POSTID ){
										echo '<li class="on"><a href="'.get_pdf_check_permalink($chpost->ID).'">'.get_the_title($chpost->ID).'</a></li>'."\n";
									}else{
										echo '<li><a href="'.get_pdf_check_permalink($chpost->ID).'">'.get_the_title($chpost->ID).'</a></li>'."\n";
									}
							} wp_reset_postdata();
							
							echo '</ul>'."\n";
							echo '</li>'."\n";

						}
						
					}
						
					foreach($posts as $post){
						$catnow = '';
						$catnow = get_the_terms( $post->ID, $tax_name );

						if($catnow[0]->parent == 0){
							if( $POSTID == $post->ID ){
								echo '<li class="on"><a href="'.get_pdf_check_permalink($post->ID).'">'.get_the_title().'</a></li>'."\n";
	
							}else{
								echo '<li><a href="'.get_pdf_check_permalink($post->ID).'">'.get_the_title().'</a></li>'."\n";
							}
						}
					}
					wp_reset_postdata();
					echo '</ul>'."\n";
				}
			}
		}

		if( $tax_name == 'list'){echo '</ul>'."\n";}
		
	}else{
			$post_per_page = -1;
			if($posttype == 'post'){ $post_per_page = 10; } /*ニュースの時だけ10件だけ表示*/
			
			$args = array(
				'post_type' => $posttype,
				'posts_per_page' => $post_per_page,
			);
			$posts = get_posts($args);
			
			if( $posts ){
				echo '<ul class="sub_menu local">'."\n";
	
				foreach($posts as $post){
					if( $POSTID == $post->ID ){
						echo '<li class="on"><a href="'.get_news_permalink($post->ID).'">'.mb_substr($post->post_title, 0,44).'</a></li>'."\n";
					}else{
						echo '<li><a href="'.get_news_permalink($post->ID).'">'.mb_substr($post->post_title, 0,44).'</a></li>'."\n";
					}
				}
				wp_reset_postdata();
				echo '</ul>'."\n";
			}
		}	
	
?>

</div>