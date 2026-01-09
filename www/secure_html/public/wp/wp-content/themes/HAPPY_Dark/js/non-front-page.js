$(function() {
  $('a[href^="#"]').click(function(){
    var speed = 500;
    var href= $(this).attr("href");
    var target = $(href == "#" || href == "" ? 'html' : href);
    var position = target.offset().top;
    $("html, body").animate({scrollTop:position}, speed, "swing");
    return false;
  });

  var menuFlag = true;
  $('.header_nav_common .header_tab').on('click', function() {
    menuFlag = !menuFlag;
    if(menuFlag){
      $('.header_nav_common').css("top","0");
    } else {
      $('.header_nav_common').css("top","-95px");
    }
  });
});
