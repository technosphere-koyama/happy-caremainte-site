<?php
/*
Template Name: マイページ

*/
?>

<?php get_header(); ?>

    <section id="mypage_nav">
      <div class="container">
        <ul>
					<li><a href="/mypage/"><img src="/mypage/img/header04.png" alt="マイページ"><span>マイページ<br>トップ</span></a></li>
					<li class="linkoff"><a><img src="/mypage/img/img/mypage01.png" alt="カウンセリング"><span>カウンセリング</span></a></li>
					<li><a href="/mypage/ordered/index.html"><img src="/mypage/img/mypage02.png" alt="ただいまのお預かり品"><span>ただいまの<br>お預かり品</span></a></li>
					<li><a href="/mypage/history/index.html"><img src="/mypage/img/mypage05.png" alt="過去のケアメンテご利用履歴"><span>過去のケアメンテ<br>ご利用履歴</span></a></li>
					<li><a href="/mypage/wardrobe/index.html"><img src="/mypage/img/mypage04.png" alt="ワードローブお預かり品"><span>ワードローブ<br>お預かり品</span></a></li>
					<li><a href="/sale/"><img src="/mypage/img/mypage03.png" alt="セール情報（会員ご優待）"><span>セール情報<br>（会員ご優待）</span></a></li>
				</ul>
			</div>
    </section>
    <!--　/#mypage_nav -->

    <section class="howto">
      <div class="container tac">
        <div class="howto_img" id="h1">
          <img src="<?php echo get_stylesheet_directory_uri(); ?>/img/howto_1_pc.png" alt="" class="pc">
          <img src="<?php echo get_stylesheet_directory_uri(); ?>/img/howto_1_sp.png" alt="" class="sp">
        </div>
        <div class="howto_img" id="h2">
          <img src="<?php echo get_stylesheet_directory_uri(); ?>/img/howto_2_pc.png" alt="" class="pc">
          <img src="<?php echo get_stylesheet_directory_uri(); ?>/img/howto_2_sp.png" alt="" class="sp">
        </div>
      </div>
    </section>

<?php get_footer(); ?>
