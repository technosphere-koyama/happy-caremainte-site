/*お申し込み・ご注文 アコーディオン*/
$( document ).ready(function() {
	if ($(window).width() < 1024) {
		$(".accordionTxt").click(function () {
			$(this).next().slideToggle();
			$(this).toggleClass("active");
		});
	}
});