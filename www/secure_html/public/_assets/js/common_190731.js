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
});

if(navigator.userAgent.indexOf('Android') > 0){
	$("html").addClass("android");
}

/* SP menu */
$("header .menu").on('click',function(){
	$("#header").toggleClass('SPGnaviOpen');
	$("header .menu_bg").slideToggle();
	$("header .menu_over").slideToggle();
});
$('#SPGnavi ul').hide();
$('.SPGnavi_menu').click(function(){
	$(this).next('ul').slideToggle();
	$(this).toggleClass('open');
});

/* Popup */
$(function() {
	$(".popup").colorbox({
		inline:true,
		maxWidth:"90%",
		maxHeight:"90%",
		opacity: 0.7
	});
});

/* Pagetop */
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

/* App loading */
if ( navigator.userAgent.indexOf('CareMenteh App User') != -1 ){
	$(window).load(function(){
		$(".loadingWrap").fadeOut();
	});
}

/* MessageBox */
$(function(){
	$(".messageClose").click(function(){
		$('.pickupMessage').css('display', 'none');
	});
});
