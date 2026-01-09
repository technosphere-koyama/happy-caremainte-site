<?php if ( 'menu-faq' == get_post_type()) : //menu_faq カスタム投稿タイプの詳細のパンくず ?>
	<div id="breadcrumb">
		<a href="<?php echo home_url(); ?>">HOME</a> &raquo; <a href="<?php echo home_url(); ?>/faq">よくある質問</a> &raquo; <?php wp_title(''); ?>
	</div><!--/breadcrumb-->
<?php elseif(is_subpage()) : //親ページを持つ、すなわち子ページのパンくず ?>
	<div id="breadcrumb">
		<a href="<?php echo home_url(); ?>">HOME</a> &raquo; <a href="<?php echo get_permalink(is_subpage()); ?>"><?php echo get_the_title($post->post_parent); ?></a> &raquo; <?php wp_title(''); ?>
	</div><!--/breadcrumb-->
<?php elseif ( 'menu-news' == get_post_type()) : ?>
	<div id="breadcrumb">
		<a href="<?php echo home_url(); ?>">HOME</a> &raquo; <a href="<?php echo home_url(); ?>/news">お知らせ</a> &raquo; <?php wp_title(''); ?>
	</div><!--/breadcrumb-->
<?php elseif (is_tax('taxo-gallery')) : ?>
	<div id="breadcrumb">
		<a href="<?php echo home_url(); ?>">HOME</a> &raquo; <a href="<?php echo home_url(); ?>/gallery">ギャラリー</a> &raquo; <?php wp_title(''); ?>
	</div><!--/breadcrumb-->
<?php elseif (is_tax('taxo-cat')) : ?>
	<div id="breadcrumb">
		<a href="<?php echo home_url(); ?>">HOME</a> &raquo; <a href="<?php echo home_url(); ?>/menu">商品メニュー</a> &raquo; <?php wp_title(''); ?>
	</div><!--/breadcrumb-->
<?php elseif (is_tax()) : ?>
	<div id="breadcrumb">
		<a href="<?php echo home_url(); ?>">HOME</a> &raquo; <?php wp_title('')?>
	</div><!--/breadcrumb-->
<?php elseif ( 'menu-list' == get_post_type()) : //タクソノミーがなければ一覧トップに変える ?>
	<div id="breadcrumb">
		<a href="<?php echo home_url(); ?>">HOME</a> &raquo; <a href="<?php echo home_url(); ?>/menu">商品メニュー</a> &raquo; <?php echo get_the_term_list( $post->ID, 'taxo-cat' ); ?> &raquo; <?php wp_title(''); ?>
	</div><!--/breadcrumb-->
<?php elseif ( 'menu-gallery' == get_post_type()) : //タクソノミーがなければ一覧トップに変える ?>
	<div id="breadcrumb">
		<a href="<?php echo home_url(); ?>">HOME</a> &raquo; <a href="<?php echo home_url(); ?>/gallery">ギャラリー</a> &raquo; <?php echo get_the_term_list( $post->ID, 'taxo-gallery' ); ?> &raquo; <?php wp_title(''); ?>
	</div><!--/breadcrumb-->
<?php elseif(is_single())://ブログ詳細-パンくず ?>
	<div id="breadcrumb">
		<a href="<?php echo home_url(); ?>">HOME</a> &raquo; <a href="<?php echo home_url(); ?>/blog">ブログ</a> &raquo; <?php the_category(','); ?> &raquo; <?php wp_title(''); ?>
	</div><!--/breadcrumb-->
<?php elseif(is_category()||is_archive()) : //カテゴリ、アーカイブのパンくず ?>
	<div id="breadcrumb">
		<a href="<?php echo home_url(); ?>">HOME</a> &raquo; <a href="<?php echo home_url(); ?>/blog">ブログ</a> &raquo; <?php wp_title(''); ?>
	</div><!--/breadcrumb-->
<?php else : ?>
	<div id="breadcrumb">
		<a href="<?php echo home_url(); ?>">HOME</a> &raquo; <?php wp_title(''); ?>
	</div><!--/breadcrumb-->
<?php endif; //パンくずここまで ?>
