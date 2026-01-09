<?php
/*
Template Name: アプリホーム

*/
?>

<!DOCTYPE html>
<html lang="ja">
<head>
<meta charset="utf-8">
<title>Happy Carementeh</title>
<meta name="viewport" content="width=360">

<link rel="stylesheet" href="/_assets/css/default.css">
<link rel="stylesheet" href="/_assets/css/jquery.bxslider.css">
<link rel="stylesheet" href="/_assets/css/top.css">
<link rel="stylesheet" href="/_assets/css/app.css">
<link rel="stylesheet" href="/_assets/css/app-home.css">

<link href="https://fonts.googleapis.com/css?family=Libre+Baskerville" rel="stylesheet">

<script src="/_assets/js/jquery.js"></script>
<script src="/_assets/js/index.js"></script>
<script src="/_assets/js/ga.js"></script>
<script type="text/javascript" src="http://ajax.googleapis.com/ajax/libs/jquery/1.9.1/jquery.min.js"></script>

</head>

<body id="pTop">
<div id="Container">

<header>
	<div class="title"><a href="/"><img src="https://www.kyoto-happy.co.jp:8443/_assets/img_app/index/logo.png" alt="Happy Carementeh"></a></div>   
</header>


<div id="Contents">
	
    <div id="container">
		<div id="theTargetSP">
			<div style="background-image: url(https://www.kyoto-happy.co.jp:8443/_assets/img/index/pct_newkv01_sp.jpg)"><a href="/carementeh/">ハッピー「ケアメンテ」で幸福をつくろう</a></div>
			<div style="background-image: url(https://www.kyoto-happy.co.jp:8443/_assets/img/index/pct_newkv02_sp.jpg)"><a href="/movie/">ケアメンテ プロモーションビデオ</a></div>
			<div style="background-image: url(https://www.kyoto-happy.co.jp:8443/_assets/img/index/pct_newkv03_sp.jpg)"><a href="/community/">提携ブランド・取扱い店舗一覧</a></div>
			<div style="background-image: url(https://www.kyoto-happy.co.jp:8443/_assets/img/index/pct_newkv04_sp.jpg)"><a href="/shop/">提携ブランド・取扱い店舗一覧</a></div>
		</div>
	</div>
    
    <div class="navi">
    	<ul>
        	<li><figure><a href="/order/"><img src="https://www.kyoto-happy.co.jp:8443/_assets/img_app/index/icon_01.png" alt="ご注文"></a><figcaption><a href="/order/">ご注文</a></figcaption></figure></li>
            <li><figure><a href="/carementeh/"><img src="https://www.kyoto-happy.co.jp:8443/_assets/img_app/index/icon_02.png" alt="ケアメンテとは？"></a><figcaption><a href="/carementeh/">ケアメンテとは？</a></figcaption></figure></li>
            <li><figure><a href="/mypage/"><img src="https://www.kyoto-happy.co.jp:8443/_assets/img_app/index/icon_03.png" alt="マイページ"></a><figcaption><a href="/mypage/">マイページ</a></figcaption></figure></li>
        </ul>
        <ul>
        	<li><figure><a href="/carementeh_search/"><img src="https://www.kyoto-happy.co.jp:8443/_assets/img_app/index/icon_04.png" alt="さがす"></a><figcaption><a href="/carementeh_search/">さがす</a></figcaption></figure></li>
            <li><figure><a href="/review/"><img src="https://www.kyoto-happy.co.jp:8443/_assets/img_app/index/icon_05.png" alt="きづく"></a><figcaption><a href="/review/">きづく</a></figcaption></figure></li>
            <!--<li><figure><a href="/faq/"><img src="https://www.kyoto-happy.co.jp:8443/_assets/img_app/index/icon_06.png" alt="よくあるご質問"></a><figcaption><a href="/faq/">よくあるご質問</a></figcaption></figure></li>-->
            <li><figure><a href="/mypage/sns.html"><img src="https://www.kyoto-happy.co.jp:8443/_assets/img_app/index/icon_07.png" alt="つなぐ"></a><figcaption><a href="/mypage/sns.html">つなぐ</a></figcaption></figure></li>
        </ul>
    </div>

</div><!--/Contents-->

<?php
if (!session_id()) {
	session_name("kh");
	session_save_path($_SERVER['DOCUMENT_ROOT']."/core/tmp/session");
	session_start();
}
$count = (isset($_SESSION['PUBLIC_USER']['message_count']) && $_SESSION['PUBLIC_USER']['message_count'] > 0) ? '<div class="mypage_count">'. $_SESSION['PUBLIC_USER']['message_count'] . '</div>' : '';
?>
<link rel="stylesheet" href="/_assets/css/app.css">
<div class="app">
	<div class="menu"><a href="/app_home/"><img src="https://www.kyoto-happy.co.jp:8443/_assets/img_app/icon1.png" alt="ホーム"></a></div>
	<div class="menu"><a href="/shop/"><img src="https://www.kyoto-happy.co.jp:8443/_assets/img_app/icon2.png" alt="ショップ検索"></a></div>
	<div class="menu"><a href="/order/"><img src="https://www.kyoto-happy.co.jp:8443/_assets/img_app/icon3.png" alt="ご注文"></a></div>
	<div class="menu"><a href="tel:0120886868"><img src="https://www.kyoto-happy.co.jp:8443/_assets/img_app/icon4.png" alt="お電話"></a></div>
	<div class="menu"><a href="/mypage/"><img src="https://www.kyoto-happy.co.jp:8443/_assets/img_app/icon5.png" alt="マイページ"></a><?php echo $count ?></div>
</div>

</div>
<!--/Container-->
</body>
        <link rel="stylesheet" href="/_assets/css/skippr_170920.css">
		<script src="/_assets/js/skippr.min_170920.js"></script>
		<script>
		$("#theTarget").skippr({
			transition: 'fade',
			speed: 1000,
			navType: 'bubble',
			autoPlay: true,
			autoPlayDuration: 6000,
			keyboardOnAlways: false
		});
		$("#theTargetSP").skippr({
			transition: 'fade',
			speed: 1000,
			navType: 'bubble',
			autoPlay: true,
			autoPlayDuration: 6000,
			keyboardOnAlways: false
		});
		</script>
</html>

