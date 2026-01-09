<?php
/*
Template Name: MA洗浄テストによる繊維ダメージ比較

*/
?>

<?php get_header(); ?>

	<div id="Contents">
		<div class="mainvisual__section">
        <div>SERVICE<br><p>サービス・技術</p></div>
		</div>

		<div id="pankuzu-wrapp"><div class="pan-border"><p class="pankuzu"><a href="/">トップ</a></p><p class="pankuzu"><a href="/technology/">ケアメンテの技術</a></p><p class="pankuzu"><a href="/technology/data/weightlessness/ma_test/">水系洗浄「無重力バランス洗浄技法（特許）」関連</a></p><p class="pankuzu"><a href="/technology/data/weightlessness/ma_test/">MA洗浄テストによる繊維ダメージ比較</a></p><p class="pankuzu no-arrow"><?php the_title(); ?></p></div></div>

		<div class="content">

        <div class="LColumn ma_test">
        <div class="pagettl"><h1><?php the_title(); ?></h1></div>
    	<div class="pagettl-sub"><?php the_field('subtitle') ?></div>


            <div class="section-imgCenter lectureReport">
            <?php if(have_posts()): while(have_posts()): the_post(); ?>
            <?php remove_filter('the_content', 'wpautop'); ?>
			<?php the_content(); ?>
			<?php endwhile; endif; ?>
			</div>
		 </div>

		<div class="RColumn PCpart">
            <div class="localNav">
            	<ul>
					<li class="firstRow ">
					<a>ハッピーの水系洗浄を支える技術</a>
					<ul class="open">
					<li><a href="/technology/innovation/weightlessness/">ハッピー独自の技術「無重力バランス洗浄技法」</a></li>
					<li><a href="/technology/innovation/lecirian/">サイジング技法「レシリアン」</a></li>
					<li><a href="/technology/innovation/press/">仕上げ技術「シルエットプレス」</a></li>
					</ul>
					</li>
					<li class="">
					<a>Before&amp;After／ケアメンテ事例集</a>
					<ul class="open">
					<li><a href="/technology/before_after/ripron/">「リプロン」事例集</a></li>
					<li><a href="/technology/before_after/list/">Before &#038; After集</a></li>
					<li><a href="/technology/before_after/suit/">上質スーツ</a></li>
					<li><a href="/technology/before_after/down/">最高級ダウン</a></li>
					<li><a href="/technology/before_after/shirt/">上質シャツ</a></li>
					<li><a href="/technology/before_after/bag/">バッグ</a></li>
					<li><a href="/technology/before_after/leather/">皮革・毛皮</a></li>
					<li><a href="/technology/before_after/wedding/">ウェディングドレス</a></li>
					<li><a href="/technology/before_after/macintosh/">マッキントッシュ</a></li>
					<li><a href="/technology/before_after/lifecare/">インテリア・ファニチャー・羽毛布団</a></li>
					<li><a href="/technology/before_after/tenpyou/">天平の古代染めを洗う</a></li>
					</ul>
					</li>
					<li class="down">
					<a>ケアメンテ技術を支える検証データ</a>
					<ul class="open">
					<li class="down2">
					<a href="/technology/data/weightlessness/ma_test/">水系洗浄「無重力バランス洗浄技法（特許）」関連</a>
					<ul class="open2">
					<li class="stay"><a href="/technology/data/weightlessness/ma_test/">MA洗浄テストによる繊維ダメージ比較</a></li>
					<li><a href="/technology/data/weightlessness/hohenstein/">ホーエンシュタイン研究所での試験結果</a></li>
					<li><a href="/pdf/hohenstein.pdf">ホーエンシュタイン研究所掲載論文（PDF）</a></li>
					<li><a href="/technology/data/weightlessness/niederrhein/">ドイツ・ニーダーライン大学での試験結果</a></li>
					<li><a href="/pdf/mujyuuryoku.pdf">実証実験による検証と考察（PDF）</a></li>
					<li><a href="/technology/data/weightlessness/kimono/">百年昔の「きもの」を洗う</a></li>
					</ul>
					</li>
					<li class="down2">
					<a href="/technology/data/tradition/yuzen/">京の伝統技法とケアメンテ</a>
					<ul class="open2">
					<li><a href="/technology/data/tradition/yuzen/">友禅流しと無重力バランス洗浄</a></li>
					<li><a href="/technology/data/tradition/ripron-2/">京染悉皆とリプロン</a></li>
					</ul>
					</li>
					<li><a href="/technology/data/comparison/">汗汚れの洗浄比較実験</a></li>
					<li><a href="/technology/data/brand/">ブランド各社からの洗浄依頼品</a></li>
					<li><a href="/technology/data/monograph/">ケアメンテ水系洗浄の学会誌掲載論文一覧</a></li>
					</ul>
					</li>
				</ul>
            </div>
        </div>

		</div><!--/content-->

  </div><!--/Contents-->

<?php get_footer(); ?>
