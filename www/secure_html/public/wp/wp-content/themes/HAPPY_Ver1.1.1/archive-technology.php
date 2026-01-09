<?php get_header(); ?>


<div id="Contents" class="careIndex">

	
	<div class="mainvisual__section">
        <div>TECHNOLOGY<br><p>ケアメンテ&reg;の技術</p></div>
	</div>
    
	<?php breadcrumb(); ?>

    <div class="content">
        <h2>ハッピーの独自技術が、<br class="SPpart">世界の常識を変える</h2>
        <h4>クリーニングの先を行く、ケアメンテ&reg;の技術</h4>
        <h3>30有余年の歳月をかけて確立したハッピーの技術が<br>従来の水洗いやドライクリーニングの欠点を解消します。</h3>
        <div class="movieBtn"><a href="#movie"><img src="https://www.kyoto-happy.co.jp:8443/_assets/img/carementeh/btn1.jpg" alt="MOVIE"></a></div>
        
        <div class="section-imgRight">
        	<div class="Rimages">
	        	<img src="https://www.kyoto-happy.co.jp:8443/_assets/img/technology/img1.jpg" alt="ハッピーの独自技術が常識を変える">
        	</div>
        	<p>従来の水洗いは、たたく・ねじる・揉むなどの物理的機械力に頼る洗い方が一般的で、大きな外力を加えることから繊維に負担をかけたり、ウールやシルクなどの動物繊維の洗浄が不可能でした。<br>
        	一方、水洗いによる欠点を克服するものとして開発されたドライクリーニングは、シミや黄ばみの原因となる水性の汚れが除去できないためその洗浄自体に根本的な欠陥があります。<br>
        	これら水洗いとドライクリーニングの致命的な欠陥を克服する、画期的な洗浄技術「無重力バランス洗浄技法」をハッピーは発明しました。<br>
        	<br>
        	また水を使って洗浄した衣服の繊維を保護するサイジング技法「レシリアン」、お預かりした衣類1点ごとに縫製や生地に合った最適な手法で職人がプレスをするハッピーの「シルエットプレス」などのハッピーの技術力が、これまでの画一的なクリーニングの常識を根本から変えます。<br>
        	<br>
        	「ハッピー ケアメンテ サービス&reg;」は、海外の研究機関・大学でも評価されているハッピー独自の洗浄技術によって支えられています。
        	</p>
        </div>

    </div><!--/content-->
    
    <div id="movie">
        <div class="promo PCpart">
            <iframe width="1000" height="563" src="https://www.youtube.com/embed/tOlgzVOOqjc?rel=0&loop=1" frameborder="0" allowfullscreen></iframe>
        </div>
        <div class="promo SPpart">
            <a href="https://www.youtube.com/embed/tOlgzVOOqjc?rel=0"><img src="/_assets/img_sp/movie/thumb_img03.jpg" alt="MOVIE"></a>
        </div>
    </div>
    
<div class="footerguide">
	<ul>
    	<li class="fnavi1"><div class="fnaviwrap"><div class="fnaviTtl">ハッピーの<br>水系洗浄を支える技術</div><p>ハッピー独自の洗浄技術についてご紹介します。</p><div class="fnaviBtn PCpart"><a href="/technology/innovation/weightlessness/">詳しくはこちら</a></div></div></li>
        <li class="fnavi2"><div class="fnaviwrap"><div class="fnaviTtl">Before &amp; After／<br>ケアメンテ事例集</div><p>ケアメンテ&reg;は身だしなみを超えたオシャレを提案しています。数々の事例をご紹介しています。</p><div class="fnaviBtn PCpart"><a href="/technology/before_after/ripron/">詳しくはこちら</a></div></div></li>
        <li class="fnavi3"><div class="fnaviwrap"><div class="fnaviTtl">ケアメンテ&reg;技術を支える<br>検証データ</div><p>海外の研究機関・大学でも評価されているハッピーの技術を、科学的根拠に基づいてご案内しています。</p><div class="fnaviBtn PCpart"><a href="/technology/data/weightlessness/ma_test/">詳しくはこちら</a></div></div></li>
	</ul>
</div>

<script><!--YouTube埋め込み サムネイル画像変更-->
$(function (){
	var youtube = new Array();
	var images = new Array(
		'https://www.kyoto-happy.co.jp:8443/_assets/img/movie/thumb_img03.jpg'
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