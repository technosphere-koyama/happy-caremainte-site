/* Key visual */
/*$(window).on("load", function(){
	var target = "#kv_slide";
	var speed = 500;
	var pause = [6,6,.15,.15,1.6,8]; //sec

	var current = 0, style = { position:"absolute", top:0, left:0 };
	var slider = $(target).css("position", "relative");
	var elms = slider.children().css(style);

	var loop = function(){
		setTimeout(function(){
			elms.eq(current++).fadeOut(speed);
			current %= elms.length;
			elms.eq(current).fadeIn(speed, loop);
		} , pause[current] * 1000);
	};

	slider.height(elms.height());
	elms.hide().eq(current).show();
	loop();
});*/
$(document).ready(function(){
	$("#kv_slide").slick({
		fade: true,
		autoplay: true,
		autoplaySpeed: 5000,
		infinite: true,
		arrows: true
	})
	.on("afterChange", function(event, slick, currentSlide, nextSlide) {
		switch (currentSlide){
			case 0:
				$(this).slick("slickSetOption", "autoplaySpeed", 8000);
				break;
			case 1:
				$(this).slick("slickSetOption", "autoplaySpeed", 8000);
				break;
			case 2:
				$(this).slick("slickSetOption", "autoplaySpeed", 8000);
				break;
			case 3:
				$(this).slick("slickSetOption", "autoplaySpeed", 8000);
				break;
		}
	});
});


var windowWidth = $(window).width();
var windowSm = 767;
$(function(){
	/* Slider */
	if (windowWidth <= windowSm) {
		var windowWidthSlide = jQuery(window).width();
		var width = windowWidthSlide / 2;
		$('.topics_pickup').bxSlider({
			mode: 'horizontal',
			auto: true,
			minSlides: 2,
			maxSlides: 2,
			moveSlides: 2,
			slideWidth: width,
			slideMargin: 10,
			infiniteLoop: true,
			pager: true,
			controls: false
		});
	}
	$('.carementeh_slide').bxSlider({
		mode: 'horizontal',
		auto: true,
		infiniteLoop: true,
		pager: true,
		controls: true,
		adaptiveHeight: false
	});
	$('.carementeh_about_slide').bxSlider({
		mode: 'fade',
		auto: true,
		infiniteLoop: true,
		pager: false,
		controls: false
	});
	if (windowWidth >= windowSm) {
		$('.link_slide').bxSlider({
			auto: true,
			minSlides: 3,
			maxSlides: 3,
			moveSlides: 1,
			slideWidth: 360,
			slideMargin: 28,
			pager: false,
			responsive: false
		});
	}

	/* Topics */
	$('.topics_more').click(function(){
		$('.topics_detail').toggleClass('open');
	});
});

/* Technology accordion */
(function($){
	$(function(){
		if (windowWidth <= windowSm) {
			$('.technology_list li').find('.technology_list_accordion').hide();

			var no=0;
			$('.technology_list li').find('.technology_list_img').eq(no).addClass("active").next('.technology_list_accordion').show();

			$('.technology_list li').find('.technology_list_img').click(function() {
				$('.technology_list li').find('.technology_list_accordion:visible').slideUp();
				$('.technology_list li').find('.technology_list_img').removeClass('active');
				$(this).next('.technology_list_accordion').slideToggle();
				$(this).toggleClass('active');
			});
		}
	});
})(jQuery);
