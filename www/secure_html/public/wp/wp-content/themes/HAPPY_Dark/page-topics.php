<?php
/*
Template Name: Topics

*/
?>
<section id="article">
	<div class="container">
		<div class="article_box">
			<div class="contents_news">
				<h2>News</h2>
				<ul class="news_list">
					<?php
						$args = array(
							'post_type' => 'post',
							'posts_per_page' => 4,
							'meta_query' => array(
								'relation' => 'OR',
								array(
									 'key' => 'news_headline',
									 'value' => true,
									 'compare' => 'NOT EXISTS'
								),
								array(
									'key' => 'news_headline',
									'value' => '1',
									'compare' => '!='
								),
							)
							);
							$my_posts = get_posts( $args );

							foreach ( $my_posts as $post ): ?>
							<li><a href="<?php echo get_news_permalink(); ?>">
								<span class="title"><?php the_time('Y.m.d'); ?></span>
								<span class="text"><?php the_title(); ?></span></a></li>
					<?php endforeach; ?>
				</ul>
				<div class="btn"><a href="/news/">もっと見る</a></div>
			</div>
			<div class="contents_faq">
				<h2>Q<span>&amp;</span>A</h2>
				<ul class="faq_list">
					<?php
						$args = array(
							'post_type' => 'faq',
							'posts_per_page' => 4,
							'meta_query' => array(
								'relation' => 'OR',
								array(
									 'key' => 'faq',
									 'value' => true,
									 'compare' => 'NOT EXISTS'
								),
								array(
									'key' => 'faq',
									'value' => '1',
									'compare' => '!='
								),
							)
							);
							$my_posts = get_posts( $args );

							foreach ( $my_posts as $post ):
							?>
								<li><a href="/faq/"><span class="title">Q</span><span class="text"><?php the_title()?></span></a></li>
						<?php endforeach; ?>
					</ul>
				<div class="btn"><a href="/faq/">もっと見る</a></div>
			</div>
		</div>
	</div>
</section>
<!--　/#article -->
