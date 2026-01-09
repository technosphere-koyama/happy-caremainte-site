<?php get_header(); ?>


<div id="Contents" class="technologyIndex">


	<div class="mainvisual__section">
        <div>TECHNOLOGY<br><p>ケアメンテ&reg;の技術</p></div>
	</div>

	<?php breadcrumb(); ?>

    <div class="content">
        <div class="pagettl-large">
          <h2 class="pagettl-large-main">ハッピーの独自技術が、<br class="SPpart">世界の常識を変える</h2>
          <small>クリーニングの先を行く、ケアメンテ&reg;の技術</small>
        </div>
        <div class="pagettl-sub">
          <h3>30有余年の歳月をかけて確立したハッピーの技術が<br>従来の水洗いやドライクリーニングの欠点を解消します。</h3>
        </div>

        <div class="movieBtn tac"><a href="#movie"><img src="/_assets/img/carementeh/btn1.png" srcset="/_assets/img/carementeh/btn1.png 2x" alt="MOVIE"></a></div>

        <div class="section-imgRight">
          <img src="https://www.kyoto-happy.co.jp:8443/_assets/img/technology/img1.jpg" alt="ハッピーの独自技術が常識を変える" class="width-1-2">
        	<p>従来の水洗いは、たたく・ねじる・揉むなどの物理的機械力に頼る洗い方が一般的で、大きな外力を加えることから繊維に負担をかけたり、ウールやシルクなどの動物繊維の洗浄が不可能でした。<br>
        	一方、水洗いによる欠点を克服するものとして開発されたドライクリーニングは、シミや黄ばみの原因となる水性の汚れが除去できないためその洗浄自体に根本的な欠陥があります。<br>
        	これら水洗いとドライクリーニングの致命的な欠陥を克服する、画期的な洗浄技術「無重力バランス洗浄技法」をハッピーは発明しました。<br>
        	<br>
        	また水を使って洗浄した衣服の繊維を保護するサイジング技法「レシリアン」、お預かりした衣類1点ごとに縫製や生地に合った最適な手法で職人がプレスをするハッピーの「シルエットプレス」などのハッピーの技術力が、これまでの画一的なクリーニングの常識を根本から変えます。<br>
        	<br>
        	「ハッピー ケアメンテ サービス&reg;」は、海外の研究機関・大学でも評価されているハッピー独自の洗浄技術によって支えられています。
        	</p>
        </div>

        <div id="movie">
            <div class="promo">
                <a href="https://www.youtube.com/watch?v=tOlgzVOOqjc?rel=0" target="_blank"><img src="/_assets/img_sp/movie/thumb_img03.jpg" alt="MOVIE"></a>
            </div>
        </div>
        <?php get_template_part( 'nav', 'technology' ); ?>

    </div><!--/content-->

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

</div><!--/Contents-->

<?php get_footer(); ?>
