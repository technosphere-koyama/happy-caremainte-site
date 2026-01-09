<?php get_header(); ?>

    <div id="Contents" class="careIndex">
    <div class="mainvisual__section">
        <div>SERVICE<br><p>サービス概要・メニュー一覧</p></div>
	</div>
    
	<?php breadcrumb(); ?>

    <div class="content">
        <h2>ハッピー「ケアメンテ<sup>&reg;</sup>」で<br class="SPpart">幸服<sup>&reg;</sup>をつくろう</h2>
        <h4>“きれい”の先にある新習慣・ケアメンテ&reg;</h4>
        <h3>あなたの服とシッカリ向き合って、<br class="SPpart">新品と同じほどに<br>ケアメンテ&reg;は、最上級の美しさをお届けします。</h3>
        <div class="movieBtn"><a href="#movie"><img src="https://www.kyoto-happy.co.jp:8443/_assets/img/carementeh/btn1.jpg" alt="MOVIE"></a></div>
        
        <div class="section-imgRight">
        	<div class="Rimages">
	        	<img src="https://www.kyoto-happy.co.jp:8443/_assets/img/carementeh/img1.jpg" alt="ハッピー「ケアメンテ」で幸服をつくろう">
    	        <img src="https://www.kyoto-happy.co.jp:8443/_assets/img/carementeh/img2.jpg" alt="ハッピー「ケアメンテ」で幸服をつくろう" class="PCpart">
        	</div>
        	<p>あなたの大切な服、そこには一人ひとりのかけがえのない、あなたの“想い”があるというのが私たちハッピーの考え方です。<br>
        	つまり、ハッピーの仕事スタイルは、あなたの“きれいの想い”をカタチにすることです。<br>
        	しかしながら、今までのクリーニングでは“きれいの想い”をカタチにできませんでした。<br>
        	その原因の多くは、クリーニング技術の限界にあると考えています。<br>
        	私たちハッピーは、新品をいつまでも着つづけることを目指してたどり着いたのが、無重力バランス洗浄とシルエットプレス技術でした。<br>
        	その技術をサポートするIoT・ICTシステムによって、サービスモデルの仕組みを30有余年の歳月をかけて確立したのが「ハッピー ケアメンテ サービス&reg;」です。<br>
        	医療の現場にも似た“ハッピー電子カルテ”を作成し、あなたの“きれいの想い”をカタチにするためにカウンセリング（問診）に始まり、一品ごとに丹精込めて緻密で精緻な“ケアメンテ&reg;”の施術をおこないます。
        	</p>
            <img src="https://www.kyoto-happy.co.jp:8443/_assets/img/carementeh/img2.jpg" alt="ハッピー「ケアメンテ」で幸福をつくろう" class="SPpart">
            <br>
        	<p>新品のおろしたての服は「そのままに」着つづけられるように、捨てられる運命の服は「もう一度、命を吹き込んで」長く着つづけられるようにするのが「ハッピー ケアメンテ サービス&reg;」です。<br>
        	クリーニングの駆け込み寺の異名を持つ「ハッピー ケアメンテ サービス&reg;」が、あなたの服の新習慣を創造してまいります。
        	</p>
        </div>

    </div><!--/content-->
    
    <div id="movie">
        <div class="promo PCpart">
            <iframe width="1000" height="563" src="https://www.youtube.com/embed/4okBMUdZc_E?rel=0&loop=1" frameborder="0" allowfullscreen></iframe>
        </div>
        <div class="promo SPpart">
            <a href="https://www.youtube.com/embed/4okBMUdZc_E?rel=0"><img src="/_assets/img_sp/movie/thumb_img02.jpg" alt="MOVIE"></a>
        </div>
    </div>
    
<div class="footerguide">
	<ul>
    	<li class="fnavi1"><div class="fnaviwrap"><div class="fnaviTtl">サービス概要</div><p>ケアメンテ&reg;で衣服を新品のように再現。そんなケアメンテ&reg;のサービスについてご紹介します。</p><div class="fnaviBtn PCpart"><a href="/carementeh/overview/style/">詳しくはこちら</a></div></div></li>
        <li class="fnavi2"><div class="fnaviwrap"><div class="fnaviTtl">サービスメニュー一覧</div><p>ケアメンテ&reg;の数多くのサービスについて詳しくご紹介します。</p><div class="fnaviBtn PCpart"><a href="/carementeh/service/aquadry/">詳しくはこちら</a></div></div></li>
	</ul>
</div>

<script><!--YouTube埋め込み サムネイル画像変更-->
$(function (){
	var youtube = new Array();
	var images = new Array(
		'https://www.kyoto-happy.co.jp:8443/_assets/img/movie/thumb_img02.jpg'
	);
	
	$('iframe').each(function(index, element) {
		youtube[index] = $(this).attr('src');
		$(this).after('<img src="'+images+'" class="youtube">').remove();
	});
	
	$('.youtube').each(function(index, element) {
		$(this).click(function (){
			var number = index;
			$(this).after('<iframe src="'+youtube[number]+'?rel=0&autoplay=1" width="1000" height="563" frameborder="0"></iframe>').remove();
		});
	});
});
</script>

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