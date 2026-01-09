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

  if(!isSmartPhone()){
  $(window).scroll(function () {
    if ($(this).scrollTop() < 240) {
      $('#pankuzu-wrapp').removeClass("scl");
      $('#Contents .content').removeClass("scl");
    } else {
      $('#pankuzu-wrapp').addClass("scl");
      $('#Contents .content').addClass("scl");
    }
  });
}


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

  btmNav.fadeIn();
  /*
  $(window).scroll(function () {
    if ($(this).scrollTop() > 10) {
      btmNav.fadeIn();
    } else {
      btmNav.fadeOut();
    }
  });
  */

  $('#menu_sp_trigger').on('click', function() {
    if ( $(this).hasClass('act') ) {
      $('.footer_Hidden div.menu__second-level').hide();
    }
    $(this).toggleClass('act');
    $('.footer_Hidden').toggleClass('act');
    $('html').toggleClass('is-fixed');
    $('body').toggleClass('no-scroll');

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
  var sch_footer = $('#sch_footer');
  sch_footer.hide();
  if(!isSmartPhone()){
    pgtp.hide();
  }

  $(window).scroll(function () {
    if ($(this).scrollTop() > 10) {
      snsBtn.fadeIn();
      pgtp.fadeIn();
      sch_footer.fadeIn();
    } else {
      snsBtn.fadeOut();
      pgtp.fadeOut();
      sch_footer.fadeOut();
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
    $('#pankuzu-wrapp').toggleClass("act");
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


  /* SP版 サチコのハッピーナビ */
  $('.guideNav li.menu__first-level > a').on('click', function(){
    $(this).next('.guideNav div.menu__second-level').slideToggle();
    $(this).toggleClass('open');
  }).each(function(){
    $(this).next('.guideNav div.menu__second-level').hide();
  });
  var hSize = $(window).height();
  $('.footer_nav_sp .footer_Hidden').css({"max-height":hSize-130+"px"});

  if ( navigator.userAgent.indexOf('Android') > 0 ) {
    $("body").addClass("Android");
  };

});


  /* お支払方法/デポジット モーダル */
$(function(){
	$(".payment_depositBtn a").click(function(){
		scrollPosition = $(window).scrollTop();
		$('body').addClass('fixed').css({'top': -scrollPosition});
		
		//キーボード操作などにより、オーバーレイが多重起動するのを防止する
		$( this ).blur() ;	//ボタンからフォーカスを外す
		if( $( "#modal-overlay" )[0] ) return false ;		//新しくモーダルウィンドウを起動しない (防止策1)
		//if($("#modal-overlay")[0]) $("#modal-overlay").remove() ;		//現在のモーダルウィンドウを削除して新しく起動する (防止策2)

		//オーバーレイを出現させる
		$( "body" ).append( '<div id="modal-overlay"></div>' ) ;
		$( "#modal-overlay" ).fadeIn( "slow" ) ;

		//コンテンツをセンタリングする
		centeringModalSyncer() ;

		//コンテンツをフェードインする
		$( ".payment_deposit" ).fadeIn( "slow" ) ;

		//[#modal-overlay]、または[#modal-close]をクリックしたら…
		$( "#modal-overlay,#modal-close" ).unbind().click( function(){
			$('body').removeClass('fixed').css({'top': 0});
		window.scrollTo( 0 , scrollPosition );

			//[.payment_deposit]と[#modal-overlay]をフェードアウトした後に…
			$( ".payment_deposit,#modal-overlay" ).fadeOut( "slow" , function(){

				//[#modal-overlay]を削除する
				$('#modal-overlay').remove() ;

			} ) ;

		} ) ;

	} ) ;

	//リサイズされたら、センタリングをする関数[centeringModalSyncer()]を実行する
	$( window ).resize( centeringModalSyncer ) ;

	//センタリングを実行する関数
	function centeringModalSyncer() {

		//画面(ウィンドウ)の幅、高さを取得
		var w = $( window ).width() ;
		var h = $( window ).height() ;

		// コンテンツ(.payment_deposit)の幅、高さを取得
		// jQueryのバージョンによっては、引数[{margin:true}]を指定した時、不具合を起こします。
		var cw = $( ".payment_deposit" ).outerWidth( {margin:true} );
		var ch = $( ".payment_deposit" ).outerHeight( {margin:true} );
		var cw = $( ".payment_deposit" ).outerWidth();
		var ch = $( ".payment_deposit" ).outerHeight();

		//センタリングを実行する
		$( ".payment_deposit" ).css( {"left": ((w - cw)/2) + "px","top": ((h - ch)/2) + "px"} ) ;

	}

} ) ;


