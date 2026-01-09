// theme_url は functions.php を参照
$(function() {
	$('.slick_technology_list').slick({
		slidesToShow:3,
		slide:"li",
		prevArrow: '<img src="'+ theme_url.template_directory_uri + '/img/prev_arrow_w.png" class="slide-arrow prev-arrow">',
		nextArrow: '<img src="'+ theme_url.template_directory_uri + '/img/next_arrow_w.png" class="slide-arrow next-arrow">',
		dots:true,
		responsive: [{
			breakpoint: 992,settings:{
				slidesToShow: 1,
				slidesToScroll: 1,
				arrows:false,
				autoplay:true,
        autoplaySpeed:5000,
				speed:800,
			}
		}]
	});

	$('.slick_case_list').slick({
		slidesToShow:4,
		slide:"li",
		prevArrow: '<img src="'+ theme_url.template_directory_uri + '/img/prev_arrow_w.png" class="slide-arrow prev-arrow">',
		nextArrow: '<img src="'+ theme_url.template_directory_uri + '/img/next_arrow_w.png" class="slide-arrow next-arrow">',
		dots:true,
		responsive: [{
			breakpoint: 992,settings:{
				slidesToShow: 2,
				slidesToScroll: 2,
				arrows:false,
        autoplaySpeed:3000,
				speed:500,
			}
		}]
	});

	$('.slick_knowledge_list').slick({
		slidesToShow:4,
		slide:"li",
		prevArrow: '<img src="'+ theme_url.template_directory_uri + '/img/prev_arrow_w.png" class="slide-arrow prev-arrow">',
		nextArrow: '<img src="'+ theme_url.template_directory_uri + '/img/next_arrow_w.png" class="slide-arrow next-arrow">',
		dots:true,
		responsive: [{
			breakpoint: 992,settings:{
				slidesToShow: 1,
				slidesToScroll: 1,
				arrows:false,
				autoplay:true,
        autoplaySpeed:5000,
				speed:800,
			}
		}]
	});

	$('.slick_review_list').slick({
		slide:"li",
		prevArrow: '<img src="'+ theme_url.template_directory_uri + '/img/prev_arrow_w.png" class="slide-arrow prev-arrow">',
		nextArrow: '<img src="'+ theme_url.template_directory_uri + '/img/next_arrow_w.png" class="slide-arrow next-arrow">',
		dots:true,
		responsive: [{
			breakpoint: 992,settings:{
				arrows:false,
				autoplay:true,
        autoplaySpeed:5000,
				speed:1000,
			}
		}]
	});


	$('.member_sns_list').slick({
		slidesToShow:4,
		slide:"li",
		prevArrow: '<img src="'+ theme_url.template_directory_uri + '/img/prev_arrow_w.png" class="slide-arrow prev-arrow">',
		nextArrow: '<img src="'+ theme_url.template_directory_uri + '/img/next_arrow_w.png" class="slide-arrow next-arrow">',
		dots:true,
		responsive: [{
			breakpoint: 992,settings:{
				slidesToShow: 2,
				slidesToScroll: 2,
				arrows:false,
				autoplay:true,
        autoplaySpeed:5000,
				speed:800,
			}
		}]
	});

	$(window).on('resize orientationchange', function() {
    $('.member_sns_list').slick('resize');
  });


});
