$(function() {
  /* ヘッダーナビ */
  // $('#header_nav_common');
  var topBtn = $('.header_nav');
  //topBtn.hide();
  /*
  var menuFlag = true;

  $(window).scroll(function () {
    console.log($(this).scrollTop());
    if ($(this).scrollTop() > 700) {
      if(menuFlag){
        $('#header_nav_common').css("top","0");
      } else {
        $('#header_nav_common').css("top","-95px");
      }
    } else if ($(this).scrollTop() > 1200) {
      menuFlag = false;
      $('#header_nav_common').css("top","-95px");
    } else {
      $('#header_nav_common').css("top","-120px");
    }
  });

  $('#header_nav_common .header_tab').on('click', function() {
    menuFlag = !menuFlag;
    if(menuFlag){
      $('#header_nav_common').css("top","0");
    } else {
      $('#header_nav_common').css("top","-95px");
    }
  });*/


  /* フッターナビ */
  var btmBtn = $('.footer_nav');
  btmBtn.hide();
  btmBtn.fadeIn();
  /*
  $(window).scroll(function () {
      if ($(this).scrollTop() > 700) {
          btmBtn.fadeIn();
      } else {
          btmBtn.fadeOut();
      }
  });*/


  /* SP版 ナビ  footer_nav_sp */
  var btmNav = $('.footer_nav_sp');
  btmNav.hide();
  var btmNavContent = $('#footer_nav_pc').clone().attr('id', 'footer_nav_sp');
  $('li.menu__first-level > a', btmNavContent).on('click', function(){
    $(this).next('div.menu__second-level').slideToggle();
    $(this).toggleClass('open');
  }).each(function(){
    $(this).next('div.menu__second-level').hide();
  });
  $('.footer_Hidden').html(btmNavContent);

  $(window).scroll(function () {
    if ($(this).scrollTop() > 10) {
      btmNav.fadeIn();
    } else {
      btmNav.fadeOut();
    }
  });

  $('#menu_sp_trigger').on('click', function() {
    if ( $(this).hasClass('act') ) {
      $('.footer_Hidden div.menu__second-level').hide();
    }
    $(this).toggleClass('act');
    $('.footer_Hidden').toggleClass('act');
    $('html').toggleClass('is-fixed');

  });

  function isSmartPhone() {
    if (window.matchMedia && window.matchMedia('(max-device-width: 640px)').matches) {
      return true;
    } else {
      return false;
    }
  }

  /* 固定snsボタン */
  var snsBtn = $('.footer_sns');
  snsBtn.hide();
  var pgtp = $('.footer_pagetop');
  if(!isSmartPhone()){
    pgtp.hide();
  }

  $(window).scroll(function () {
    if ($(this).scrollTop() > 10) {
      snsBtn.fadeIn();
      if(!isSmartPhone()){
      pgtp.fadeIn();
    }
    } else {
      snsBtn.fadeOut();
      if(!isSmartPhone()){
      pgtp.fadeOut();
    }
    }
  });


  /* member_sns_list_sp*/
  var flag = "close";
  $(".btn_toggle").on("click", function() {
    $(this).prev().slideToggle("slow");
    $(this).toggleClass("active");

    if(flag == "close"){ //もしflagがcloseだったら
      $(this).text("閉じる");
      flag = "open"; //flagをopenにする
    }
    else{ //もしflagがopenだったら
      $(this).text("さらに見る");
      flag = "close"; //flagをcloseにする
    }
  });



  $('#menu_pc_trigger').on('click', function() {
    $(this).toggleClass('act');
    $('.header_nav_common').toggleClass('act');
    $('.footer_nav').toggleClass('act');
  });
	
	
  /*検索 アコーディオン*/
  $( document ).ready(function() {
    var flg = "close";

      $(".accordionBtn").click(function () {
        $(this).next().slideToggle();
        $(this).toggleClass("active");
        if(flg == "close"){
          $(".accordionTxt").text("閉じる");
          flg = "open";
        }else{
            $(".accordionTxt").text("開く");
            flg = "close";
        }

      });
  });

});

