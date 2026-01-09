<?php get_header(); ?>
  
<div id="Contents" class="coIndex">
	<div class="mainvisual__section">
        <div>CORPORATE<br><p>会社情報</p></div>
	</div>    	
		<?php breadcrumb(); ?>
	
<div class="content">
        <h2>衣服再生産技術で<br class="SPpart">世界に“幸服<sup>&reg;</sup>”を届ける</h2>
        <h4>従来のクリーニングとは一線を画した衣服再生サービス</h4>
        
        <div class="section-imgRight">
        	<div class="Rimages">
	        	<img src="https://www.kyoto-happy.co.jp:8443/_assets/img/corporate/img1.jpg" alt="衣服再生加工技術で世界に“幸服”を届ける">
        	</div>
        	<p class="mgB30">上質な無地の反物を買い、仕立て、着古すたびに徐々に濃い色に染め直して一着の着物を最後まで楽しむ、そんな京都特有の”着だおれ”精神と伝統を現在に受け継いだ、衣服のケアメンテサービスを提供するのが株式会社ハッピーです。<br>
        	難しい汚れや、特殊な生地を使った衣類を新品同様に蘇らせるという、既存のクリーニングでは対応できなかったことに私たちは挑戦しています。
        	</p>
        	<p class="mgB30">お客様からお預かりした大切なお洋服を、徹底した情報管理やカウンセリング・品質で満足していただけるサービスをこれからもご提供します。
        	</p>
        </div>

    </div><!--/content-->
    
<div class="footerguide">
	<ul>
    	<li class="fnavi1"><div class="fnaviwrap"><div class="fnaviTtl">会社概要</div><p>株式会社ハッピーの企業紹介はこちら。</p><div class="fnaviBtn PCpart"><a href="/corporate/company/profile/">詳しくはこちら</a></div></div></li>
        <li class="fnavi2"><div class="fnaviwrap"><div class="fnaviTtl">メディア情報</div><p>過去のメディア報道や講演活動などをご紹介します。</p><div class="fnaviBtn PCpart"><a href="/corporate/media/media_list/">詳しくはこちら</a></div></div></li>
        <li class="fnavi3"><div class="fnaviwrap"><div class="fnaviTtl">リクルート</div><p>募集概要はこちら。</p><div class="fnaviBtn PCpart"><a href="/corporate/recruit/cultivation/">詳しくはこちら</a></div></div></li>
        <li class="fnavi4"><div class="fnaviwrap"><div class="fnaviTtl">環境への取組み</div><p>地球環境保護の取り組みについてはこちら。</p><div class="fnaviBtn PCpart"><a href="/corporate/csr/weightlessness/">詳しくはこちら</a></div></div></li>
        <li class="fnavi5"><div class="fnaviwrap"><div class="fnaviTtl">ヨーロッパ洗浄技術交流紀行</div><p>環境・技術交流を目的に定期的にヨーロッパを訪問しています。</p><div class="fnaviBtn PCpart"><a href="/corporate/europe/2013_summer/">詳しくはこちら</a></div></div></li>
	</ul>
</div>

<script>
$(".footerguide li").each(function(){
	if ($(window).width() < 1024) {
    var rel_url = $("a", this).attr("href");  
    $(this).click(function(){  
        location.href= rel_url;  
    });
	}
});  
</script>
    
</div><!--/Contents--> 
  
<?php get_footer(); ?>
