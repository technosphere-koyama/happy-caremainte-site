        <div class="RColumn PCpart">
            <div class="localNav">
            	<ul>
<?php
	global $POSTID,$current_cat,$posttype,$tax_name,$page,$parent_cat;
	$flg = 0;
	$navList ='';
	$navList = '';

	if($posttype == 'carementeh' || $posttype == 'technology'){ /*ケアメンテ、ケアメンテの技術*/
		$args = array(
			'taxonomy' => $tax_name,
			'parent' => 0,
			'pad_counts' => true,
		);
		
		$categories = get_categories( $args );
		$firstflg = '';
		foreach($categories as $cat){
			$down = '';
			if ( is_wp_error( $term_link ) ) {
				continue;
			}

			$args = array( /*親カテゴリの投稿取得*/
				'post_type' => $posttype,
				'posts_per_page' => -1,
				'taxonomy' => $tax_name,
				'term' => $cat->slug,
				'include_children' => false
			);
			$posts = get_posts($args);
			
			if( $parent_cat == $cat->term_id || $current_cat == $cat->term_id){ $down ='down';}
			else{$down ='';}/*現在のカテゴリなら表示*/
			
				if( $firstflg == 0){ /*最初の行かチェック*/
					$navList .= '<li class="firstRow '.$down.'">'."\n";
					$navList .= '<a>'.$cat->name.'</a>'."\n";
					$navList .= '<ul class="open">'."\n";
					$firstflg = 1;
				}else{
					$navList .= '<li class="'.$down.'">'."\n";
					$navList .= '<a>'.$cat->name.'</a>'."\n";
					$navList .= '<ul class="open">'."\n";			
				}

				$children = get_term_children( $cat->term_id, $tax_name ); /*子カテゴリがあれば出力*/
				
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
						
						$navList .= '<li class="down2">'."\n";		
						$navList .= '<a href="'.get_pdf_check_permalink($child_posts[0]->ID).'">'.$chobj->name.'</a>'."\n";
						$navList .= '<ul class="open2">'."\n";
						
						foreach($child_posts as $chpost){

								if( $chpost->ID == $POSTID ){
									$navList .= '<li class="stay"><a href="'.get_pdf_check_permalink($chpost->ID).'">'.get_the_title($chpost->ID).'</a></li>'."\n";
								}else{
									$navList .= '<li><a href="'.get_pdf_check_permalink($chpost->ID).'">'.get_the_title($chpost->ID).'</a></li>'."\n";
								}
						} wp_reset_postdata();
						
						$navList .= '</ul>'."\n";
						$navList .= '</li>'."\n";
					}
				}
				
				if( $posts ){
						foreach($posts as $post){
							setup_postdata( $post ); 
							$catnow = get_the_terms( $post->ID, $tax_name );
							if($catnow[0]->parent == 0){

								if( $post->ID == $POSTID ){
									$navList .= '<li class="stay"><a href="'.get_pdf_check_permalink($post->ID).'">'.get_the_title().'</a></li>'."\n";
								}else{
									$navList .= '<li><a href="'.get_pdf_check_permalink($post->ID).'">'.get_the_title().'</a></li>'."\n";
								}
							}
						} wp_reset_postdata();

						$navList .= '</ul>'."\n";
						$navList .= '</li>'."\n";
				}

		}
		echo $navList."\n";
				
	}elseif($posttype == 'use'){ /*集荷依頼*/
		$args = array(
			'taxonomy' => $tax_name,
			'parent' => 0,
			'pad_counts' => true,
		);
		
		$categories = get_categories( $args );
		foreach($categories as $cat){
			$down = '';
			$term_link = get_term_link( $cat, $tax_name );
			if ( is_wp_error( $term_link ) ) {
				continue;
			}
			$args = array(
				'post_type' => $posttype,
				'posts_per_page' => -1,
				'taxonomy' => 'use_cat',
				'term' => $cat->slug
			);
			$posts = get_posts($args);
			
			if( $posts ){
				if( $current_cat == $cat->term_id){$down = 'down';}else{$down = '';}
				if($firstflg == 0){
					$navList .= '<li class="firstRow '.$down.'">'."\n";
					$firstflg = 1;
				}else{
					$navList .= '<li class="'.$down.'">'."\n";
				}
				$navList .= '<a>'.$cat->name.'</a>'."\n";
				$navList .= '<ul class="open">'."\n";

				foreach($posts as $post){
					if( $post->ID == $POSTID ){
						$navList .= '<li class="stay"><a href="'.get_the_permalink().'">'.get_the_title().'</a></li>'."\n";
					}else{
						$navList .= '<li><a href="'.get_the_permalink().'">'.get_the_title().'</a></li>'."\n";
					}
				} wp_reset_postdata();
					$navList .= '</ul>'."\n";
					$navList .= '</li>'."\n";
			}
		}
				echo $navList."\n";
	}elseif( $posttype == 'knowledge' ){ /*おしゃれ雑学*/
			$flg = 0;
			$args = array(
				'post_type' => $posttype,
				'posts_per_page' => -1,
			);
			$posts = get_posts($args);
			
			if( $posts ){					
					
					foreach($posts as $post){
						$class = '';
						if( $flg == 0 && $post->ID == $POSTID ){ $class = 'firstRow stay'; $flg = 1; }
						elseif( $flg == 0 ){ $class = 'firstRow'; $flg = 1; }
						elseif( $post->ID == $POSTID ){ $class = 'stay'; }
						
						if($class){
							$navList .= '<li class="'.$class.'"><a href="'.get_the_permalink().'">'.get_the_title().'</a></li>'."\n";
						}else{
							$navList .= '<li><a href="'.get_the_permalink().'">'.get_the_title().'</a></li>'."\n";
						}

					} wp_reset_postdata();
					$navList .= '</ul>'."\n";
			}

			echo $navList."\n";

	}elseif( $posttype == 'post' ){ /*ニュース*/
			$firstflg = 0;
			$class = '';

			$args = array(
				'post_type' => $posttype,
				'posts_per_page' => 10,
			);
			$posts = get_posts($args);
			
			if( $posts ){					
					
					foreach($posts as $post){
						$class = '';
						if( $firstflg == 0 && $post->ID == $POSTID ){ $class = 'firstRow stay'; $firstflg = 1; }
						elseif( $firstflg == 0 ){ $class = 'firstRow'; $firstflg = 1; }
						elseif( $post->ID == $POSTID ){ $class = 'stay'; }
						
						if($class){
							$navList .= '<li class="'.$class.'"><a href="'.get_news_permalink().'">'.mb_substr($post->post_title, 0,20).'</a></li>'."\n";
						}else{
							$navList .= '<li><a href="'.get_news_permalink().'">'.mb_substr($post->post_title, 0,20).'</a></li>'."\n";
						}
						
					} wp_reset_postdata();
					$navList .= '</ul>'."\n";
			}

			echo $navList."\n";
			
	}elseif($posttype == 'shop' || $page == 'shop_search'){ /*ショップ*/
		if($page == 'shop_search'){
			echo '<li class="firstRow stay"><a href="/shop_search/">ショップ検索</a></li>'."\n";

		}else{
			echo '<li class="firstRow"><a href="/shop_search/">ショップ検索</a></li>'."\n";
		}

		
		$args = array(
			'parent' => 0,
			'hide_empty' => false
		);

		$terms = get_terms( $tax_name , $args );		
		$first_term_link = get_term_link( $terms[0]->term_id, $tax_name );

		echo '<li class="down">'."\n";
		echo '<a href="'.$first_term_link.'">ショップ情報</a>'."\n";
		echo '<ul class="open">'."\n";

		foreach($terms as $cat){
			$term_link = get_term_link( $cat->term_id, $tax_name );
			
			if( $cat->term_id == $POSTID ){
				echo '<li class="stay"><a href="'.$term_link.'">'.$cat->name.'</a></li>'."\n";
			}else{
				echo '<li><a href="'.$term_link.'">'.$cat->name.'</a></li>'."\n";
			}
			
		}
	}elseif($posttype == 'corporate'){ /*会社情報*/
		$args = array(
			'taxonomy' => $tax_name,
			'parent' => 0,
			'pad_counts' => true,
		);
		
		$categories = get_categories( $args );
		foreach($categories as $cat){
			$down = '';
			$term_link = get_term_link( $cat, $tax_name );

			if ( is_wp_error( $term_link ) ) {
				continue;
			}
			$args = array(
				'post_type' => $posttype,
				'posts_per_page' => -1,
				'taxonomy' => $tax_name,
				'term' => $cat->slug
			);
			$posts = get_posts($args);
			
			if( $posts ){
				if( $current_cat == $cat->term_id){$down = 'down';}else{$down = '';}
				if($firstflg == 0){
					$navList .= '<li class="firstRow '.$down.'">'."\n";
					$firstflg=1;
				}else{
					$navList .= '<li class="'.$down.'">'."\n";
				}
				$navList .= '<a>'.$cat->name.'</a>'."\n";
				$navList .= '<ul class="open">'."\n";

				foreach($posts as $post){
					if( $post->ID == $POSTID ){
						$navList .= '<li class="stay"><a href="'.get_pdf_check_permalink($post->ID).'">'.get_the_title().'</a></li>'."\n";
					}else{
						$navList .= '<li><a href="'.get_pdf_check_permalink($post->ID).'">'.get_the_title().'</a></li>'."\n";
					}
				} wp_reset_postdata();
				$navList .= '</ul>'."\n";
				$navList .= '</li>'."\n";
	
			}
		}
		echo $navList."\n";	
	}

?>
            	</ul>
            </div>
        </div>