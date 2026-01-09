/* loader*/
//var ladedFlag = false;

// SmartPhone判定
function isSmartPhone() {
  if (window.matchMedia && window.matchMedia('(max-device-width: 640px)').matches) {
    return true;
  } else {
    return false;
  }
}

//if(isSmartPhone()){
//} else {
  // var rdyFlag = false;
  // YouTube Player APIの読み込み
  // var tag = document.createElement('script');
  // tag.src = "https://www.youtube.com/iframe_api";
  // var firstScriptTag = document.getElementsByTagName('script')[0];
  // firstScriptTag.parentNode.insertBefore(tag, firstScriptTag);
  // プレイヤーを埋め込む場所(IDを指定)
  // var ytArea = 'video-background';
  // 埋め込むYouTube動画のID
  // var ytID = 'oaJuGpTkMos';
//}

//load初期
$(function() {

  //var h = $(window).height();
  //$('.loader_bg').height(h).css('display','block');
});

// プレイヤーの埋め込み
/*
function onYouTubeIframeAPIReady() {
  ytPlayer = new YT.Player(ytArea, {
    videoId: ytID,
    playerVars: {
      controls: 0, // プレイヤーコントロールの非表示
      autoplay:1,
      disablekb: 1,
      enablejsapi: 1,
      rel: 0,
      modestbranding: 1, // YouTubeロゴの非表示
      iv_load_policy: 3, // アノテーションの非表示
      playsinline: 1
    },
    events: {
      'onReady': onPlayerReady,
      'onStateChange': onPlayerStateChange
    }
  });
}
*/


//全ての読み込みが完了したら実行
$(window).on('load',function () {
  //if(isSmartPhone()){
   // $('.video-backgroundWrap').delay(1500).fadeOut(800);
   var widt_value = $(window).width();
   if(widt_value < 640){//追加：2021.03.05

    $('.video-backgroundWrap').vegas({ //背景画像でスライドショーしたい場所の設定
      slides: [
       { src: 'img/vega2022/001.jpg' },
       { src: 'img/vega2022/002.jpg' },
       { src: 'img/vega2022/003.jpg' },
       { src: 'img/vega2022/004.jpg' },
       { src: 'img/vega2022/005.jpg' },
       { src: 'img/vega2022/006.jpg' },
       { src: 'img/vega2022/007.jpg' },
       { src: 'img/vega2022/008.jpg' },
       { src: 'img/vega2022/009.jpg' },
       { src: 'img/vega2022/010.jpg' },
       { src: 'img/vega2022/011.jpg' },
       { src: 'img/vega2022/012.jpg' },
       { src: 'img/vega2022/013.jpg' },
       { src: 'img/vega2022/014.jpg' },
       { src: 'img/vega2022/015.jpg' }
      ],
       delay: 4000, //スライドまでの時間ををミリ秒単位で設定
       timer: false, //タイマーバーの表示/非表示を切り替え
       transition: 'fade', //スライド間のエフェクトを設定
       transitionDuration: 1500, //エフェクト時間をミリ秒単位で設定
       loop:true,
       color:'#000'
    });
}




  //} else {
    // if(localStorage.getItem('loading') === null || localStorage.getItem('loading') != "1"){
      // ladedFlag = true;
      // playerPlay();
      // localStorage.setItem('loading',"1");
  //   } else {
      // ladedFlag = true;
      // playerPlay();
    //}


//  }
});





//10秒たったら強制的にロード画面を非表示
//$(function(){
//   if(isSmartPhone()){
  //   $('.loader_bg').delay(1500).fadeOut(800);
//   } else {
//     setTimeout('stopload()',10000);
  // }
//});

//function stopload(){
  // if(!ladedFlag){
  //   ladedFlag = true;
    // playerPlay();
  // }
//}

$(function() {

  ScrollReveal().reveal('.bg .container',{});

  $('a[href^="#"]').click(function(){
    var speed = 500;
    var href= $(this).attr("href");
    var target = $(href == "#" || href == "" ? 'html' : href);
    var position = target.offset().top;
    $("html, body").animate({scrollTop:position}, speed, "swing");
    return false;
  });
});





  // 動画の準備完了後の動作
  // function onPlayerReady(e) {
    // rdyFlag = true;
    // ytPlayer.setPlaybackQuality('default');
    // playerPlay();
  // }
  // function playerPlay(){
    // if( rdyFlag && ladedFlag ) {
    //   ytPlayer.mute();
      // ytPlayer.playVideo();
    //   $('.loader_bg').delay(1500).fadeOut(800);
    // }
  // }

  // 動画再生中と再生後の動作
  // function onPlayerStateChange(e) {
  //   var ytStatus = e.target.getPlayerState();
  //   if (ytStatus == YT.PlayerState.PLAYING) { //再生中
  //   }
  //   if (ytStatus == YT.PlayerState.ENDED) { //再生後
  //     playerPlay();
  //   }
//   }

  // 上下左右に出てくる黒帯を非表示
  /*
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
    if(isSmartPhone()){
    } else {
      yt_screen_retio();
    }
  });

  $(function(){
    if(isSmartPhone()){
    } else {
      yt_screen_retio();
    }
  });
  */

// 背景動画ぼかし
$(window).scroll(function(){
  if ($(window).scrollTop() > 1100) {
    $('#video-background').addClass('act');
    $('.vegas-slide-inner').addClass('act');
  } else {
    $('#video-background').removeClass('act');
    $('.vegas-slide-inner').removeClass('act');
  }
});
