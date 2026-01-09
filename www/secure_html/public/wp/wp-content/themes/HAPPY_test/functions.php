<?php
/*
================================================================================
	テンプレートディレクトリ　ショートコード
================================================================================
*/

function shortcode_templateurl() {
    return get_bloginfo('template_url');
}
add_shortcode('template_url', 'shortcode_templateurl');

/*
================================================================================
	サイトURL　ショートコード
================================================================================
*/
function my_home_url( $atts ) {
    return home_url();
}
add_shortcode( 'my_home_url', 'my_home_url' );

/*
================================================================================
	content内の画像一覧を取得
================================================================================
*/
function getPostImage($mypost){
  $resultArray = array();
  $cnt = 0;
  if(empty($mypost)){
     return(null);
  }
  	  
	  if(preg_match_all('/<img([ ]+)([^>]*)src\=["|\']([^"|^\']+)["|\']([^>]*)>.*([^<]+)/u',$mypost->post_content,$img_array)){
		///キャプションなし
		foreach( $img_array[0] as $img ){
			$img_array_list = '';
			if(preg_match('/<img([ ]+)([^>]*)src\=["|\']([^"|^\']+)["|\'].*a>(.*)/u',$img,$img_array_list)){
				//imgタグで検索
				$resultArray[0][$cnt] =$img_array_list[3];
				if(preg_match('/\[\/caption]/u',$img_array_list[4])){
					$resultArray[1][$cnt] = preg_replace("/\[\/caption]/u", "$1", $img_array_list[4]);
				}else{
					$resultArray[1][$cnt] ='';
				}
			}
			$cnt++;
		}
	  }
    return($resultArray);

}

/*
================================================================================
	news記事　ページネーション設定
================================================================================
*/
function custom_wp_link_pages() {
 
$defaults = array(
 'before' => '',
 'after' => '',
 'link_before' => '',
 'link_after' => '',
 'next_or_number' => 'number',
 'separator' => ' ',
 'nextpagelink' => __( '<li class="prev"><a href=""><img src="/content/images/common/pager-prev.png" width="32" height="32" alt="前へ"/></a></li>' ),
 'previouspagelink' => __( '<li class="next"><a href=""><img src="/content/images/common/pager-next.png" width="32" height="32" alt="次へ"/></a></li>' ),
 'pagelink' => '<span class="number">%</span>',
 'echo' => 1
 );
 return $defaults;
}
add_filter( 'wp_link_pages_args', 'custom_wp_link_pages');



/*
================================================================================
	管理バー非表示
================================================================================
*/

add_filter( 'show_admin_bar', '__return_false' );


/*
================================================================================
	ユーザエージェント判別
	（retuen　スマホ:1　その他：2）
================================================================================
*/
function is_custom_mobileCheck() {
	$ua = $_SERVER['HTTP_USER_AGENT'];
	if(preg_match('/iPhone/i', $ua) || preg_match('/Android/i', $ua) || preg_match('/iPod/i', $ua)) {
		return true;
	}else{
		return false;
	}
}

/*
================================================================================
	カスタムタクソノミー名をURLから削除
================================================================================
*/
function my_custom_post_type_permalinks_set($termlink, $term, $taxonomy){
    return str_replace('/'.$taxonomy.'/', '/', $termlink);
}
add_filter('term_link', 'my_custom_post_type_permalinks_set',11,3);


/*
================================================================================
	パンくずリスト
================================================================================
*/
function breadcrumb(){
	global $post;
	$str ='';
	if(!is_home()&&!is_admin()){
		$str.= '<div id="pankuzu-wrapp">';
		$str.= '<div class="pan-border">';
		$str.= '<p class="pankuzu"><a href="'.home_url('/').'">ハッピーケアメンテ トップ</a></p>';
		
		/* 投稿のページ */
		if(is_single()){
			if( is_singular( 'carementeh' ) ){
				$categories = get_the_terms($post->ID,'carementeh_cat');
				$cat = $categories[0];
				$str.='<p class="pankuzu"><a href="'.home_url('/').'carementeh/">サービス概要・メニュー一覧</a></p>';
	
				$args = array(
					'post_type' => $posttype,
					'posts_per_page' => 1,
					'taxonomy' => 'carementeh_cat',
					'term' => $cat->slug,
					'orderby' => 'menu_order',
					'order' => 'ASC'
				);
				$posts = get_posts($args);

				$str.='<p class="pankuzu"><a href="'.get_the_permalink($posts[0]->ID). '">'. $cat-> name . '</a></p>';
			
			}elseif( is_singular( 'technology' ) ){
				$categories = get_the_terms($post->ID,'technology_cat');
				$cat = $categories[0];
				$str.='<p class="pankuzu"><a href="'.home_url('/').'technology/">ケアメンテ&reg;の技術</a></p>';
	
				$args = array(
					'post_type' => $posttype,
					'posts_per_page' => 1,
					'taxonomy' => 'technology_cat',
					'term' => $cat->slug,
					'orderby' => 'menu_order',
					'order' => 'ASC'
				);
				$posts = get_posts($args);

				$str.='<p class="pankuzu"><a href="'.get_the_permalink($posts[0]->ID). '">'. $cat-> name . '</a></p>';
				
			}elseif( is_singular( 'shop' ) ){ /*ショップ情報　シングルページ*/
				$categories = get_the_terms($post->ID,'list');
				$cat = $categories[0];
				$str.='<p class="pankuzu"><a href="'.home_url('/').'shop/">提携ブランド／全国取扱い店舗一覧</a></p>';
				$str.='<p class="pankuzu"><a href="'.get_term_link( $cat, 'list' ).'">'.$cat->name.'</a></p>';

			}elseif( is_singular( 'use' ) ){ /*ご注文（集荷依頼）ご利用方法　シングルページ*/
				$categories = get_the_terms($post->ID,'use_cat');
				$cat = $categories[0];
				$str.='<p class="pankuzu"><a href="'.home_url('/').'use/">ご注文方法／価格表</a></p>';
				$str.='<p class="pankuzu"><a href="'.get_term_link( $cat, 'use_cat' ).'">'.$cat->name.'</a></p>';
	
			}elseif( is_singular( 'knowledge' ) ){ /*おしゃれ雑学　シングルページ*/
				$str.='<p class="pankuzu"><a href="'.home_url('/').'knowledge/">おしゃれの雑学</a></p>';
				
			}elseif( is_singular( 'detail' ) ){ /*こだわりのディティール　シングルページ*/
				$str.='<p class="pankuzu"><a href="'.home_url('/').'detail/">こだわりのディティール</a></p>';
				
			}elseif( is_singular( 'corporate' ) ){ /*会社情報　シングルページ*/
				$categories = get_the_terms($post->ID,'corporate_cat');
				$cat = $categories[0];
				$str.='<p class="pankuzu"><a href="'.home_url('/').'corporate/">会社情報</a></p>';
				
				$args = array(
					'post_type' => $posttype,
					'posts_per_page' => 1,
					'taxonomy' => 'corporate_cat',
					'term' => $cat->slug,
					'orderby' => 'menu_order',
					'order' => 'ASC'
				);
				$posts = get_posts($args);
				
				$str.='<p class="pankuzu"><a href="'.get_the_permalink($posts[0]->ID). '">'. $cat-> name . '</a></p>';
				
			}elseif( is_singular( 'post' ) ){				
				$str.='<p class="pankuzu"><a href="'.home_url('/').'news/">更新情報一覧／ニュース</a></p>';
			}else{
				$categories = get_the_category($post->ID);
				$cat = $categories[0];
				if($cat -> parent != 0){
					$ancestors = array_reverse(get_ancestors( $cat -> cat_ID, 'category' ));
					foreach($ancestors as $ancestor){
						$str.='<p class="pankuzu"><a href="'. get_category_link($ancestor).'">'. get_cat_name($ancestor). '</a></p>';
										}
				}
			}

			$str.= '<p class="pankuzu no-arrow">'. $post -> post_title .'</p>';
		} 
		
		/* 固定ページ */
		elseif(is_page()){
			if($post -> post_parent != 0 ){
				$ancestors = array_reverse(get_post_ancestors( $post->ID ));
				foreach($ancestors as $ancestor){
					$str.='<p class="pankuzu"><a href="'. get_permalink($ancestor).'">'. get_the_title($ancestor) .'</a></p>';
									}
			}
			if(is_page('shop_search')){
					$str.='<p class="pankuzu"><a href="'.home_url('/').'shop/">提携ブランド／全国取扱い店舗一覧</a></p>';
			}
			$str.= '<p class="pankuzu no-arrow">'. $post -> post_title .'</p>';
			

		}
		
		/* カテゴリページ */	
		elseif(is_category()) {
			$cat = get_queried_object();
			if($cat -> parent != 0){
				$ancestors = array_reverse(get_ancestors( $cat -> cat_ID, 'category' ));
				foreach($ancestors as $ancestor){
					$str.='<p class="pankuzu"><a href="'. get_category_link($ancestor) .'">'. get_cat_name($ancestor) .'</a></p>';
				}
			}
			$str.='<p class="pankuzu no-arrow">'. $cat -> name . '</span></li>';
		}
		
		/* タグページ */
		elseif(is_tag()){
			$str.='<p class="pankuzu no-arrow">'. single_tag_title( '' , false ). '</span></li>';
		} 

		/* ショップ　カテゴリートップ */
		elseif(is_tax('list')){
			$str.='<p class="pankuzu"><a href="'.home_url('/').'shop/">提携ブランド／全国取扱い店舗一覧</a></p>';
			$str.='<p class="pankuzu no-arrow">'. single_tag_title( '' , false ). '</span></li>';
		} 

		/* 集荷依頼　カテゴリートップ */
		elseif(is_tax('use_cat')){
			$str.='<p class="pankuzu"><a href="'.home_url('/').'use/">ご注文方法／価格表</a></p>';
			$str.='<p class="pankuzu no-arrow">'. single_tag_title( '' , false ). '</span></li>';
		} 
		
		/* 時系列アーカイブページ */
		elseif(is_date()){
			if(get_query_var('day') != 0){
				$str.='<p class="pankuzu"><a href="'. get_year_link(get_query_var('year')). '">' . get_query_var('year'). '年</a></p>';
				$str.='<p class="pankuzu"><a href="'. get_month_link(get_query_var('year'), get_query_var('monthnum')). '">'. get_query_var('monthnum') .'月</a></p>';
				$str.='<p class="pankuzu">'. get_query_var('day'). '</span>日</li>';
			} elseif(get_query_var('monthnum') != 0){
				$str.='<p class="pankuzu"><a href="'. get_year_link(get_query_var('year')) .'">'. get_query_var('year') .'年</span.</a></li>';
				$str.='<p class="pankuzu">'. get_query_var('monthnum'). '</span>月</li>';
			} else {
				$str.='<p class="pankuzu no-arrow">'. get_query_var('year') .'年</span></li>';
			}
		}	

		/* 投稿者ページ */
		elseif(is_author()){
			$str .='<p class="pankuzu no-arrow">投稿者 : '. get_the_author_meta('display_name', get_query_var('author')).'</span></li>';
		}	
		
		/* 添付ファイルページ */
		elseif(is_attachment()){
			if($post -> post_parent != 0 ){
				$str.= '<p class="pankuzu"><a href="'. get_permalink($post -> post_parent).'">'. get_the_title($post -> post_parent) .'</a></p>';
			}
			$str.= '<p class="pankuzu no-arrow">'. $post -> post_title .'</p>';
		}

		/* 検索結果ページ */
		elseif(is_search()){
			$str.='<p class="pankuzu">「'. get_search_query() .'」で検索した結果</span></li>';
		} 
		
		/* 404 Not Found ページ */
		elseif(is_404()){
			$str.='<p class="pankuzu no-arrow">お探しの記事は見つかりませんでした。</span></li>';
		} 
				
		/* その他のページ */
		else{
			$str.= '<p class="pankuzu no-arrow">'. wp_title('', false) .'</p>';
		}
		
		
		
		
		$str.='</div>';
		$str.='</div>';
	}
	echo $str;
}

/*
================================================================================
	ニュースパーマリンク設定
================================================================================
*/
function get_news_permalink(){
	global $post;
	if(!get_field('news_detailpage')){
		return get_the_permalink();
	}else{
		if(get_field('news_otherURL')){
			return get_field('news_otherURL');
		}
	}
	
}

/*
================================================================================
	パーマリンク設定 (PDFファイルかチェック）
================================================================================
*/
function get_pdf_check_permalink($post_id){
	if(!get_field('pdf_file_URL',$post_id)){
		return get_the_permalink($post_id);
	}else{
		return get_field('pdf_file_URL',$post_id);
	}
	
}

?>
