<?php
if (!session_id()) {
	session_name("kh");
	session_save_path($_SERVER['DOCUMENT_ROOT']."/../core/tmp/session");
	session_start();
}
$count = (isset($_SESSION['PUBLIC_USER']['message_count']) && $_SESSION['PUBLIC_USER']['message_count'] > 0) ? '<div class="mypage_count">'. $_SESSION['PUBLIC_USER']['message_count'] . '</div>' : '';
?>

<script type="text/javascript">
if ((navigator.userAgent.indexOf('iPhone') > 0) || navigator.userAgent.indexOf('iPod') > 0 || navigator.userAgent.indexOf('Android') > 0 || navigator.userAgent.indexOf('CareMenteh App User') != -1){
	document.write('<link rel="stylesheet" type="text/css" href="/_assets/css/app.css?190518">');
}else {
	document.write('<link rel="stylesheet" type="text/css" href="/_assets/css/app_no.css?190517">');
}
</script>

<!--<div id="pageback"><a href="javascript:history.back();"><img src="/_assets/img_app/pageback.png" alt="戻る"/></a></div>-->

<!--
<div class="loadingWrap app">
	<img src="/_assets/img_sp/common_page/loading.gif" width="40" height="40">
</div>
-->

<div class="app">
	<ul class="gnavi">
		<li class="app_navi1"><a href="/"><img src="https://www.kyoto-happy.co.jp:8443/_assets/img/app/ico_home2.svg" alt="ホーム">ホーム</a></li>
		<li class="app_navi2"><a href="/mypage/"><img src="https://www.kyoto-happy.co.jp:8443/_assets/img/app/nav_mypage.svg" alt="マイページ">マイページ</a><?php echo $count ?></li>
		<li class="app_navi3"><a href="/order/form.html?special=apps"><img src="https://www.kyoto-happy.co.jp:8443/_assets/img/app/nav_order.svg" alt="ご注文">ご注文</a></li>
		<li class="app_navi4"><a href="tel:0120886868"><img src="https://www.kyoto-happy.co.jp:8443/_assets/img/app/nav_tel.svg" alt="お電話">お電話</a></li>
		<li class="app_navi5"><a href="/mypage/sns.html"><img src="https://www.kyoto-happy.co.jp:8443/_assets/img/app/nav_sns.svg" alt="つなぐ">つなぐ</a></li>
		<li class="app_navi6"><a href="/mypage/registration/"><img src="https://www.kyoto-happy.co.jp:8443/_assets/img/app/nav_setting.svg" alt="設定">設定</a></li>
	</ul>
</div>


<script type="text/javascript">
	$(window).on('load',function(){
		var path = location.pathname

		if (path == "/mypage/"){ $('.app_navi2').addClass('current');}
		if (document.URL.match(/history/) || document.URL.match(/ordered/) || document.URL.match(/wardrobe/)){ $('.app_navi2').addClass('current');}
		if (path == "/order/form.html" || path == "/order/confirm.html" || path == "/order/complete.html"){ $('.app_navi3').addClass('current');}
		if (path == "/mypage/sns.html"){ $('.app_navi5').addClass('current');}
		if (document.URL.match(/friend/) || document.URL.match(/community/) || document.URL.match(/message/) || document.URL.match(/profile/)){ $('.app_navi5').addClass('current');}
		if (document.URL.match(/registration/)){ $('.app_navi6').addClass('current');}
	});
</script>
