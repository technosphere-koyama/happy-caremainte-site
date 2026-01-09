$(function(){
  $(window).scroll(function (){
    $('#left_banner').each(function(){
      var TargetPos = 800;
      var spPos = 1000;
      var elemPos = $(this).offset().top;
      var scroll = $(window).scrollTop();
      var windowHeight = $(window).height();
      var widt_value = $(window).width();

      if (scroll > TargetPos){
        $(this).addClass('scrollin');
      }else {
        $(this).removeClass('scrollin');
            }
    });
  });
});





$(function () {
    const ua = navigator.userAgent;
    if (ua.indexOf('iPhone') > -1 || (ua.indexOf('Android') > -1 && ua.indexOf('Mobile') > -1)) {
			$(function(){
				$('#left_banner').hide();
			});
    } else if (ua.indexOf('iPad') > -1 || ua.indexOf('Android') > -1) {
			$(function(){
				$('#left_banner').show();
					$('#left_banner_off').click(function(){
						$('#left_banner_inner').hide();
					});
					$('#left_banner_off2').click(function(){
						$('#left_banner_inner2').hide();
					});
					$('#left_banner_off3').click(function(){
						$('#left_banner_inner3').hide();
					});
			});
    } else {
			$(function(){
				$('#left_banner').show();
					$('#left_banner_off').click(function(){
						$('#left_banner_inner').hide();
					});
					$('#left_banner_off2').click(function(){
						$('#left_banner_inner2').hide();
					});
					$('#left_banner_off3').click(function(){
						$('#left_banner_inner3').hide();
					});
			});
    }
})
