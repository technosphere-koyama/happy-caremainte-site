$(function() {
  // スクロールのオフセット値
  var offsetY = -10;
  // スクロールにかかる時間
  var time = 500;

  // ページ内リンクのみを取得
  $('.movieBtn a , .wardrobeInfo a').click(function() {
    // 移動先となる要素を取得
    var target = $(this.hash);
    if (!target.length) return ;
    // 移動先となる値
    var targetY = target.offset().top+offsetY;
    // スクロールアニメーション
    $('html,body').animate({scrollTop: targetY}, time, 'swing');
    // ハッシュ書き換えとく
    window.history.pushState(null, null, this.hash);
    // デフォルトの処理はキャンセル
    return false;
  });
});


$(document).ready(function(){
	
	/*
	ユーザーエージェント判別
	osVer = "iPhone";
	osVer = "Android";
	osVer = "iPod";
	osVer = "iPad";
	*/
	var osVer;
	osVer = "Android";
	if (navigator.userAgent.indexOf(osVer)>0){
		$.ajax({
			url: 'js/android.js',
			dataType: 'script',
			cache: false
		});
	}
    
    /*SPメニュー　クリックで開閉*/
	$("header .menu, header .closebtn").on('click',function(){
		$("header .menu_bg").fadeToggle();
		$("header .menu_over").fadeToggle();
		$("header .menu").fadeToggle();
	});
	 
});


$(function() {
	$(window).scroll(function(){
			var s = $(this).scrollTop();
			var m = 360;
			if(s > m) {
				$("#pagetop").fadeIn('slow');
			} else if(s < m) {
				$("#pagetop").fadeOut('slow');
			}
		});
		$("#pagetop").click(function () {
			$('html,body').animate({ scrollTop: 0 }, 'fast');
			return false;
	});
});


//アプリの場合のみローディング表示
if ( navigator.userAgent.indexOf('CareMenteh App User') != -1 ){
	$(window).load(function(){
	$(".loadingWrap").fadeOut();
});
}else {
}


//メッセージボックス
$(function(){
    $(".messageClose").click(function(){
        $('.pickupMessage').css('display', 'none');
    });
});

//さがす モーダルウインドウ
$(function(){
    $(document).on("click", ".SearchWindowClose", function() {
        $('.SearchWindow').css('display', 'none');
    });
});

