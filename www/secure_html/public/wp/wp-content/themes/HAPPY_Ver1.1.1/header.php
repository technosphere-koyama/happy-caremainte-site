<!DOCTYPE html>
<html lang="ja">
<head>
<meta charset="utf-8">
<title><?php wp_title('|', true, 'right'); ?><?php bloginfo('name'); ?></title>
<meta name="description" content="通常のクリーニングでは落ちないシミや汚れを解決。ハッピーケアメンテは衣服の持ち味である繊維・色彩・縫製と風合い、デザインのシルエットを極限まで再現して永く楽しめるようにします。">
<meta name="keywords" content="クリーニング,シミ,しみ,着物,宅配,ウェットクリーニング,水洗い,高級,黄ばみ">
<meta name="format-detection" content="telephone=no">
<script type="text/javascript">
if ((navigator.userAgent.indexOf('iPhone') > 0) || navigator.userAgent.indexOf('iPod') > 0 || navigator.userAgent.indexOf('Android') > 0 || navigator.userAgent.indexOf('CareMenteh App User') != -1) {
        document.write('<meta name="viewport" content="width=320, user-scalable=no" />');
    }else{
        document.write('<meta name="viewport" content="width=1280" />');
    }
</script>

<link rel="manifest" href="/manifest.json">
<link rel="apple-touch-icon" href="/_assets/img/common/512.png" sizes="512x512"/>

<?php if ( is_home() || is_front_page() ) : ?>
<link rel="canonical" href="https://www.kyoto-happy.co.jp/">
<?php else : ?>
<?php endif; ?>

<!-- Open Graph Protocol -->
<meta property="og:locale" content="ja_JP">
<meta property="og:site_name" content="<?php bloginfo('name'); ?>">
<?php if ( is_home() || is_front_page() ) : ?>
<meta property="og:url" content="https://www.kyoto-happy.co.jp/">
<?php else : ?>
<meta property="og:url" content="<?php the_permalink(); ?>">
<?php endif; ?>
<meta property="og:title" content="<?php wp_title('|', true, 'right'); ?><?php bloginfo('name'); ?>">
<meta property="og:description" content="通常のクリーニングでは落ちないシミや汚れを解決。ケア・メンテは衣服の持ち味、つまり繊維、色彩、縫製と風合い、デザインのシルエットを極限まで再現して永く楽しめるようにします。">
<meta property="og:image" content="https://www.kyoto-happy.co.jp/_assets/img/header/logo.png">
<!-- Open Graph Protocol -->

<link rel="stylesheet" href="/_assets/css/default.css">
<link rel="stylesheet" href="/_assets/css/common.css?181114">
<link rel="stylesheet" href="/_assets/css/tooltipster.bundle.min.css">
<?php if(is_front_page()): ?>
<link rel="stylesheet" href="/_assets/css/top.css?190402">
<?php endif; ?>

<?php if(is_post_type_archive('carementeh') || is_tax('carementeh_cat') || is_singular( 'carementeh' ) ): ?>
<link rel="stylesheet" href="/_assets/css/carementeh.css">
<?php endif; ?>
<?php if(is_post_type_archive('technology') || is_tax('technology_cat') || is_singular( 'technology' ) ): ?>
<link rel="stylesheet" href="/_assets/css/technology.css">
<?php endif; ?>
<?php if(is_post_type_archive('knowledge') || is_tax('knowledge_cat') || is_singular( 'knowledge' ) ): ?>
<link rel="stylesheet" href="/_assets/css/knowledge.css">
<?php endif; ?>
<?php if(is_post_type_archive('detail') || is_tax('detail_cat') || is_singular( 'detail' ) ): ?>
<link rel="stylesheet" href="/_assets/css/detail.css?190404">
<?php endif; ?>
<?php if(is_post_type_archive('use') || is_tax('use_cat') || is_singular( 'use' ) ): ?>
<link rel="stylesheet" href="/_assets/css/use.css?181116">
<?php endif; ?>
<?php if(is_post_type_archive('shop') || is_tax('list') || is_singular( 'shop' ) || is_page('shop_search') ): ?>
<link rel="stylesheet" href="/_assets/css/shop.css">
<?php endif; ?>
<?php if(is_post_type_archive('corporate') || is_tax('corporate_cat') || is_singular( 'corporate' )): ?>
<link rel="stylesheet" href="/_assets/css/corporate.css?181130">
<?php endif; ?>
<?php if(is_post_type_archive('meeting') || is_tax('meeting_cat') || is_singular( 'meeting' )): ?>
<link rel="stylesheet" href="/_assets/css/corporate.css?181130">
<?php endif; ?>
<?php if(is_post_type_archive('faq') || is_tax('faq_cat') || is_singular( 'faq' )): ?>
<link rel="stylesheet" href="/_assets/css/faq.css">
<?php endif; ?>
<?php if(is_post_type_archive('post') || is_singular( 'post' ) || is_page('news') ): ?>
<link rel="stylesheet" href="/_assets/css/news.css">
<?php endif; ?>
<?php if(is_post_type_archive('post') || is_singular( 'post' ) || is_page('privacy') ): ?>
<link rel="stylesheet" href="/_assets/css/privacy.css">
<?php endif; ?>
<?php if(is_post_type_archive('post') || is_singular( 'post' ) || is_page('sale') ): ?>
<link rel="stylesheet" href="/_assets/css/sale.css">
<?php endif; ?>
<?php if(is_post_type_archive('post') || is_singular( 'post' ) || is_page('lp') ): ?>
<link rel="stylesheet" href="/_assets/css/lp.css">
<?php endif; ?>
<?php if(is_post_type_archive('post') || is_singular( 'post' ) || is_page('mypageuse') || is_page('use1') || is_page('use2') || is_page('use_search') || is_page('use_mypage') || is_page('use_sns') ): ?>
<link rel="stylesheet" href="/_assets/css/mypage_page.css">
<?php endif; ?>
<?php 	 if(is_post_type_archive('post') || is_singular( 'post' ) || is_page('movie') ): ?>
<link rel="stylesheet" href="/_assets/css/movie.css">
<?php endif; ?>
<?php the_field('page-css') ?>
<?php the_field('page-js') ?>

<link href="https://fonts.googleapis.com/css?family=Libre+Baskerville" rel="stylesheet">
<link href="https://maxcdn.bootstrapcdn.com/font-awesome/4.7.0/css/font-awesome.min.css" rel="stylesheet" integrity="sha384-wvfXpqpZZVQGK6TAh5PVlGOfQNHSoD2xbE+QkPxCAFlNEevoEH3Sl0sibVcOQVnN" crossorigin="anonymous">

<script src="/_assets/js/jquery.js"></script>
<script src="/_assets/js/jquery.bxslider.min.js"></script>
<script src="/_assets/js/common.js" defer></script>
<script src="/_assets/js/common_3rd.js" defer></script>
<script src="/_assets/js/ga.js"defer></script>
<script src="https://ajax.googleapis.com/ajax/libs/jquery/1.8.3/jquery.min.js"></script>
<script src="/_assets/js/tooltipster.bundle.min.js"></script>
<script src="/_assets/js/jquery.js"></script>
<?php  if(is_front_page()): ?>
<script src="/_assets/js/index.js"></script>
<?php endif; ?>

<script type="text/javascript">
window.addEventListener("load", function(event) {
    lazyload();
});
</script>

<?php 	 if(is_post_type_archive('shop') || is_tax('list') || is_singular( 'shop' ) || is_page('shop_search') ): ?>
<script src="/_assets/js/shop.js"></script>
<?php endif; ?>
<?php 	 if(is_post_type_archive('technology') || is_tax('technology_cat') || is_singular( 'technology' ) ): ?>
<script src="/_assets/js/technology.js"></script>
<?php endif; ?>

<script src="//synalio.com/api/chatbox?appid=d06e2e1166344d9fa669ede59c7ae502" type="text/javascript" defer></script>
<script src="//kitchen.juicer.cc?color=/4VMpPelySQ=" async></script>

<?php wp_head(); ?>
</head>

<body id="pTop">
<!-- FB script ▼ -->
<div id="fb-root"></div>
<script>(function(d, s, id) {
var js, fjs = d.getElementsByTagName(s)[0];
if (d.getElementById(id)) return;
js = d.createElement(s); js.id = id;
js.src = "//connect.facebook.net/ja_JP/sdk.js#xfbml=1&version=v2.3&appId=755562857883941";
fjs.parentNode.insertBefore(js, fjs);
}(document, 'script', 'facebook-jssdk'));</script>
<!-- FB script ▲ -->
<!-- Twitter script ▼ -->
<script>!function(d,s,id){var js,fjs=d.getElementsByTagName(s)[0];if(!d.getElementById(id)){js=d.createElement(s);js.id=id;js.src="//platform.twitter.com/widgets.js";fjs.parentNode.insertBefore(js,fjs);}}(document,"script","twitter-wjs");</script>
<!-- Twitter script ▲ -->

<div id="Container">

<header>
<?php
$webroot = $_SERVER['DOCUMENT_ROOT'];
include($webroot."/include/header.php");
?>
<?php wp_head(); ?>
</header>
