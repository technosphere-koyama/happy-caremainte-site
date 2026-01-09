<?php
$webroot = $_SERVER['DOCUMENT_ROOT'];
include($webroot."/include/footer.php");
?>


</div>
<!--/Container-->
</body>
<script>
<?php 	 if( !(is_tax('list') || is_singular( 'shop' ) || is_page('shop_search') || is_tax('knowledge_cat') || is_singular( 'knowledge' ) || is_singular( 'post' ))  ): ?>
//PCレフトナビ
$(".localNav .open").hide();
$(".localNav .down .open").show();

$(".localNav > ul > li").click(
  function () {
		$(".localNav > ul > li").not(this).removeClass('down');
		$('.open').slideUp('slow');
		$(this).children('.open:not(:animated)').slideToggle('slow');
		if( $(this).hasClass('down') ){
			$(this).removeClass('down');
		}else{
			$(this).addClass('down');
		}
  }
);
<?php endif; ?>

<?php 	 if( is_tax('list') || is_singular( 'shop' ) || is_page('shop_search') || is_tax('knowledge_cat') || is_singular( 'knowledge' ) || is_singular( 'post' )  ): ?>
$('.sub_menu:not(:first)').hide();
<?php else: ?>
$('.sub_menu:not(:nth-child(2n))').hide();
<?php endif; ?>
$('.main_menu').click(function () {
   $(this).next('.sub_menu').slideToggle('slow').siblings('.sub_menu').slideUp('slow');
   $(this).siblings('.main_menu').removeClass('active');
   $(this).toggleClass('active');
});
</script>
<?php 	 if(is_post_type_archive('use') || is_tax('use_cat') || is_singular( 'use' ) ): ?>
<script>
$(".more_content").css("display","none");
$('.readmore').on('click', function() {
    $(this).css('display','none');//押したボタンを非表示
    $('.more_content').slideDown('fast');
  });
</script>
<script>
$(".more_content2").css("display","none");
$('.readmore2').on('click', function() {
    $(this).css('display','none');//押したボタンを非表示
    $('.more_content2').slideDown('fast');
  });
</script>
<?php endif; ?>
</html>
