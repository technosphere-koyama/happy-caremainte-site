<?php
/*
Template Name: 規約

*/
?>
<!doctype html>
<html>

<head>
    <meta charset="UTF-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge,chrome=1">
    <script type="text/javascript">
        if ((navigator.userAgent.indexOf('iPhone') > 0) || navigator.userAgent.indexOf('iPod') > 0 || navigator.userAgent.indexOf('Android') > 0 || navigator.userAgent.indexOf('CareMenteh App User') != -1) {
            document.write('<meta name="viewport" content="width=320, user-scalable=no" />');
        } else {
            document.write('<meta name="viewport" content="width=1280" />');
        }
    </script>
    <title><?php the_title(); ?>｜ハッピー ケアメンテ&reg;</title>
    <link href="/wp/wp-content/themes/HAPPY_Dark/css/common.css" rel="stylesheet">
    <link href="/wp/wp-content/themes/HAPPY_Dark/css/mypage.css" rel="stylesheet">
    <link href="/wp/wp-content/themes/HAPPY_Dark/css/frm.css" rel="stylesheet">
    <link href="/wp/wp-content/themes/HAPPY_Dark/css/transitional.css" rel="stylesheet">
    <link href="https://maxcdn.bootstrapcdn.com/font-awesome/4.7.0/css/font-awesome.min.css" rel="stylesheet" integrity="sha384-wvfXpqpZZVQGK6TAh5PVlGOfQNHSoD2xbE+QkPxCAFlNEevoEH3Sl0sibVcOQVnN" crossorigin="anonymous">
    <!--[if lt IE 9]>
  <script src="/common/js/html5shiv.min.js"></script>
<![endif]-->
    <script type='text/javascript' src='/wp/wp-content/themes/HAPPY_Dark/lib/jquery-3.3.1.min.js'></script>
    <script src="/_assets/js/jquery.validationEngine.js"></script>
    <script src="/_assets/js/jquery.validationEngine-ja.js"></script>
</head>

<body id="mypage" class="frm kiyaku">

    <?php
	/* ヘッダーインクルード */
	$webroot = $_SERVER['DOCUMENT_ROOT'];
    include($webroot . "/include/header_new.php");
	?>

<div class="bg">
            <div id="Contents">
                <div class="mainvisual__section">
                    <div>USE<br>
                        <p><?php the_field('kiyaku-title'); ?></p>
                    </div>
                </div>
                <div id="pankuzu-wrapp">
                    <div class="pan-border">
                        <p class="pankuzu"><a href="/">ハッピーケアメンテ トップ</a></p>
                        <p class="pankuzu"><a href="/use/">ご注文方法／価格表</a></p>
                        <p class="pankuzu no-arrow"><?php the_title(); ?></p>
                    </div>
                </div>
                <section id="member_beginner">
                    <div class="container">
                        <div class="member_beginnerWrap">
                            <div>
                                <h2 class="tac colorB"><?php the_field('kiyaku-gold-title'); ?></h2>
                                <ul>
                                    <li>
                                        <h3><span>1</span><?php the_field('kiyaku-01'); ?></h3>
                                        <?php the_field('kiyaku-text-01'); ?>
                                    </li>
                                    <li>
                                        <h3><span>2</span><?php the_field('kiyaku-02'); ?></h3>
                                       <?php the_field('kiyaku-text-02'); ?>
                                    </li>
                                    <li>
                                        <h3><span>3</span><?php the_field('kiyaku-03'); ?></h3>
                                        <?php the_field('kiyaku-text-03'); ?>
                                    </li>
                                    <li>
                                        <h3><span>4</span><?php the_field('kiyaku-04'); ?></h3>
                                        <?php the_field('kiyaku-text-04'); ?>
                                    </li>
                                    <li>
                                        <h3><span>5</span><?php the_field('kiyaku-05'); ?></h3>
                                        <?php the_field('kiyaku-text-05'); ?>
                                    </li>
                                    <li>
                                        <h3><span>6</span><?php the_field('kiyaku-06'); ?></h3>
                                        <?php the_field('kiyaku-text-06'); ?>
                                    </li>
                                    <li>
                                        <h3><span>7</span><?php the_field('kiyaku-07'); ?></h3>
                                        <?php the_field('kiyaku-text-07'); ?>
                                    </li>
                                    <li>
                                        <h3><span>8</span><?php the_field('kiyaku-08'); ?></h3>
                                        <?php the_field('kiyaku-text-08'); ?>
                                    </li>
                                    <li>
                                        <h3><span>9</span><?php the_field('kiyaku-09'); ?></h3>
                                       <?php the_field('kiyaku-text-09'); ?>
                                    </li>
                                    <li>
                                        <h3><span>10</span><?php the_field('kiyaku-10'); ?></h3>
                                        <?php the_field('kiyaku-text-10'); ?>
                                    </li>
                                    <li>
                                        <?php the_field('kiyaku-att'); ?>
                                    </li>
                                </ul>
                            </div>
                        </div>
                    </div>
                </section>


</div><!--/Contents-->
            <script type="text/javascript" src="/wp/wp-content/themes/HAPPY_Dark/js/common.js"></script>
            <script type='text/javascript' src='/wp/wp-content/themes/HAPPY_Dark/lib/slick/slick.min.js'></script>
            <script type='text/javascript' src='/wp/wp-content/themes/HAPPY_Dark/js/slick_common.js'></script>
            <script type='text/javascript' src='/wp/wp-content/themes/HAPPY_Dark/js/non-front-page.js'></script>
<?php get_footer(); ?>
