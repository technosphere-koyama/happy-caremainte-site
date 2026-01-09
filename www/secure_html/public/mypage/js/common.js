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


	/* フッターナビ*/
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


	/* SP版 ナビ  footer_nav_sp*/
  /*var btmNav = $('.footer_nav_sp');
  btmNav.hide();

  $(window).scroll(function () {
      if ($(this).scrollTop() > 700) {
          btmNav.fadeIn();
      } else {
          btmNav.fadeOut();
      }
  });*/
	
	$('#menu_sp_trigger').on('click', function() {
		$(this).toggleClass('act');
		$('.footer_Hidden').toggleClass('act');
		$('html').toggleClass('is-fixed');

	});

	/* 固定snsボタン*/
  var snsBtn = $('.footer_sns');
  snsBtn.hide();

  $(window).scroll(function () {
      if ($(this).scrollTop() > 700) {
          snsBtn.fadeIn();
      } else {
          snsBtn.fadeOut();
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

	
	/* pager_top*/
		var pageTop = $('#pager_top');    
    pageTop.hide();
	
		$(window).scroll(function () {
				if ($(this).scrollTop() > 500) {
						pageTop.fadeIn();
				} else {
						pageTop.fadeOut();
				}
		});

		pageTop.click(function () {
				$('body,html').animate({
						scrollTop: 0
				}, 500);
				return false;
		});

});
