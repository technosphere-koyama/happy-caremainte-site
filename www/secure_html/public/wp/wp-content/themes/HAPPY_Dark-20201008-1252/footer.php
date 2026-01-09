<?php
$webroot = $_SERVER['DOCUMENT_ROOT'];
//include($webroot."/include/footer.php");
include($webroot."/include/body_retargeting_cord.php");
?>
<div class="footer_sns">
  <div class="container">
    <ul>
      <li><a href="https://www.facebook.com/pages/%e3%83%8f%e3%83%83%e3%83%94%e3%83%bc%2d%e3%82%b1%e3%82%a2%e3%83%a1%e3%83%b3%e3%83%86Happy%2dCareMenteh%2f107312759374049" target="_blank"><i class="fa fa-facebook" aria-hidden="true"></i></a></li>
      <li><a href="https://twitter.com/Happy_KYOTO" target="_blank"><i class="fa fa-twitter" aria-hidden="true"></i></a></li>
      <li><a href="https://www.instagram.com/happycarementeh/" target="_blank"><i class="fa fa-instagram" aria-hidden="true"></i></a></li>
      <li><a href="https://www.youtube.com/channel/UCZyJC69VvnDqIAgsEQ-rTeQ" target="_blank"><i class="fa fa-youtube" aria-hidden="true"></i></a></li>
    </ul>
  </div>
</div>
<!--　/.footer_sns -->
</div>
<!--　/.bg -->

<div class="footer_nav">
<div class="container">
  <ul>
    <li><a href=""><img src="<?php echo get_stylesheet_directory_uri(); ?>/img/footer01.png" alt="ご利用方法・価格表"><span>ご利用方法 価格表</span></a></li>
    <li><a href=""><img src="<?php echo get_stylesheet_directory_uri(); ?>/img/footer02.png" alt="サービス・技術"><span>サービス・技術</span></a></li>
    <li><a href=""><img src="<?php echo get_stylesheet_directory_uri(); ?>/img/footer03.png" alt="事例・レビュー"><span>事例・レビュー</span></a></li>
    <li><a href=""><img src="<?php echo get_stylesheet_directory_uri(); ?>/img/footer04.png" alt="特集・読みもの"><span>特集・読みもの</span></a></li>
    <li><a href=""><img src="<?php echo get_stylesheet_directory_uri(); ?>/img/footer05.png" alt="会社情報・リクルート"><span>会社情報・リクルート</span></a></li>
  </ul>
</div>
</div>
<!--　/.footer_nav -->

<div class="footer_nav_sp">
<div class="wrap">
  <div class="container">
    <nav id="menu_sp_trigger">
      <div>
        <span></span>
        <span></span>
        <span></span>
      </div>
      <p>MENU</p>
    </nav>
    <div class="gFooter">
      <ul>
        <li><a href=""><img src="<?php echo get_stylesheet_directory_uri(); ?>/img/header01_w.png" alt="さがす"><br><span>さがす</span></a></li>
        <li><a href=""><img src="<?php echo get_stylesheet_directory_uri(); ?>/img/header02_w.png" alt="きづく"><br><span>きづく</span></a></li>
        <li><a href=""><img src="<?php echo get_stylesheet_directory_uri(); ?>/img/header03_w.png" alt="つなぐ"><br><span>つなぐ</span></a></li>
      </ul>
    </div>
    <div class="link">
      <div class="tel">
        <a href=""><img src="<?php echo get_stylesheet_directory_uri(); ?>/img/icon_tel_w.png" alt="tel"><br><span>お電話</span></a>
      </div>
      <div class="order">
        <a href=""><img src="<?php echo get_stylesheet_directory_uri(); ?>/img/order_w.png" alt="配送"><br>
        <span>お申し込み</span></a>
      </div>
    </div>
  </div>
</div>
<ul class="footer_Hidden">
  <li><a href=""><img src="<?php echo get_stylesheet_directory_uri(); ?>/img/footer01.png" alt="ご利用方法 価格表"><span>ご利用方法 価格表</span></a></li>
  <li><a href=""><img src="<?php echo get_stylesheet_directory_uri(); ?>/img/footer02.png" alt="サービス・技術"><span>サービス・技術</span></a></li>
  <li><a href=""><img src="<?php echo get_stylesheet_directory_uri(); ?>/img/footer03.png" alt="事例・レビュー"><span>事例・レビュー</span></a></li>
  <li><a href=""><img src="<?php echo get_stylesheet_directory_uri(); ?>/img/footer04.png" alt="特集・読みもの"><span>特集・読みもの</span></a></li>
  <li><a href=""><img src="<?php echo get_stylesheet_directory_uri(); ?>/img/footer05.png" alt="会社情報・リクルート"><span>会社情報・リクルート</span></a></li>
</ul>
</div>
<!--　/.footer_nav_sp -->

<script type="text/javascript" src="<?php echo get_stylesheet_directory_uri(); ?>/lib/jquery-3.3.1.min.js"></script>
<?php if ( is_front_page() ) : ?>
<link rel="stylesheet" type="text/css" href="<?php echo get_stylesheet_directory_uri(); ?>/lib/slick/slick.css" media="screen" />
<link rel="stylesheet" type="text/css" href="<?php echo get_stylesheet_directory_uri(); ?>/lib/slick/slick-theme.css" media="screen" />
<script src="<?php echo get_stylesheet_directory_uri(); ?>/lib/slick/slick.min.js"></script>
<script src="<?php echo get_stylesheet_directory_uri(); ?>/js/slick_common.js"></script>
<script src="https://unpkg.com/scrollreveal"></script>
<?php endif; ?>
<script src="<?php echo get_stylesheet_directory_uri(); ?>/js/common.js"></script>
<script>
<?php if ( is_front_page() ) : ?>
$(function() {
ScrollReveal().reveal('.container',{});
/*
var anc = [
  {"id":"technology"},
  {"id":"service"},
  {"id":"case"},
  {"id":"use"},
  {"id":"member"},
  {"id":"partner"},
  {"id":"knowledge"},
  {"id":"reading"},
  {"id":"app"},
  {"id":"review"},
  {"id":"article"}
];
$(window).resize(function() {
 for ( var i = 0; i < anc.length; i++ ){
   anc[i]["ofs"] = $("#"+anc[i]["id"]).offset().top;
 }
}).resize();
var menuFlag = true;
var autoFlag = true;
$(window).scroll(function() {
  var ws = $(window).scrollTop();
  for ( var i = 0; i < anc.length; i++ ){
    var min = (i==0) ? 0 : $("#"+anc[i-1]["id"]).offset().top;
    var max = $("#"+anc[i]["id"]).offset().top;
    if(ws >= min && ws <= max) {
      if(i == 1){
        if(menuFlag){
          $('#header_nav_common').css("top","0");
        } else {
          $('#header_nav_common').css("top","-95px");
        }
      }
      if(i == 2){
        if(autoFlag){
          autoFlag = false;
          if(menuFlag){
            menuFlag = !menuFlag;
            $('#header_nav_common').css("top","-95px");
          }
        }
      }
    }
  }
})
*/
var menuFlag = true;
$('#header_nav_common .header_tab').on('click', function() {
  menuFlag = !menuFlag;
  if(menuFlag){
    $('#header_nav_common').css("top","0");
  } else {
    $('#header_nav_common').css("top","-95px");
  }
});


$('a[href^="#"]').click(function(){
  var speed = 500;
  var href= $(this).attr("href");
  var target = $(href == "#" || href == "" ? 'html' : href);
  var position = target.offset().top;
  $("html, body").animate({scrollTop:position}, speed, "swing");
  return false;
});
});
// SmartPhone判定
function isSmartPhone() {
if (window.matchMedia && window.matchMedia('(max-device-width: 640px)').matches) {
  return true;
} else {
  return false;
}
}
// YouTube Player APIの読み込み
var tag = document.createElement('script');
tag.src = "https://www.youtube.com/iframe_api";
var firstScriptTag = document.getElementsByTagName('script')[0];
firstScriptTag.parentNode.insertBefore(tag, firstScriptTag);

// プレイヤーを埋め込む場所(IDを指定)
var ytArea = 'video-background';
// 埋め込むYouTube動画のID
console.log(isSmartPhone());
var ytID = (isSmartPhone()) ? 'g2yv-HQFsVQ':'nfM7TIGyqpM';

// プレイヤーの埋め込み
function onYouTubeIframeAPIReady() {
ytPlayer = new YT.Player(ytArea, {
  videoId: ytID,
  playerVars: {
    rel: 0, // 関連動画の非表示
    controls: 0, // プレイヤーコントロールの非表示
    showinfo: 0, // タイトルなどの非表示
    modestbranding: 1, // YouTubeロゴの非表示
    iv_load_policy: 3, // アノテーションの非表示
    wmode: 'transparent'
  },
  events: {
    'onReady': onPlayerReady,
    'onStateChange': onPlayerStateChange
  }
});
}

// 動画の準備完了後の動作
function onPlayerReady(e) {
ytPlayer.playVideo();
ytPlayer.mute();
ytPlayer.setPlaybackQuality('default'); // 画質(small・medium・large・hd720・hd1080・highres・default)
}

// 動画再生中と再生後の動作
function onPlayerStateChange(e) {
var ytStatus = e.target.getPlayerState();
if (ytStatus == YT.PlayerState.PLAYING) { //再生中
}
if (ytStatus == YT.PlayerState.ENDED) { //再生後
  ytPlayer.playVideo();
  ytPlayer.mute();
}
}

// 上下左右に出てくる黒帯を非表示
var WIN = $(window);
var WIN_H
var win_W

function yt_screen_retio(){
WIN_H = WIN.height();
WIN_W = WIN.width();
var screen_switch = 0.5625;
var screen_ratio = WIN_H / WIN_W;
var ratio_H = WIN_H / screen_switch;
var ratio_W = WIN_W * screen_switch;

if(screen_ratio > screen_switch){
  $('#video-background').css({
    'height':'100%',
    'width':ratio_H,
    'margin-top':'0',
    'margin-left': -ratio_H /2,
    'left':'50%',
    'top':'0'
  });
} else {
  $('#video-background').css({
    'width':'100%',
    'height':ratio_W,
    'margin-top': -ratio_W / 2,
    'margin-left':'0',
    'top':'50%',
    'left':'0'
  });
}
}

WIN.resize(function () {
yt_screen_retio();
});

$(function(){
yt_screen_retio();
});
<?php else: ?>
  $(function() {
    $('a[href^="#"]').click(function(){
      var speed = 500;
      var href= $(this).attr("href");
      var target = $(href == "#" || href == "" ? 'html' : href);
      var position = target.offset().top;
      $("html, body").animate({scrollTop:position}, speed, "swing");
      return false;
    });
		
    var menuFlag = true;
    $('.header_nav_common .header_tab').on('click', function() {
      menuFlag = !menuFlag;
      if(menuFlag){
        $('.header_nav_common').css("top","0");
      } else {
        $('.header_nav_common').css("top","-95px");
      }
  	});
<?php endif; ?>
</script>
</body>
</html>
