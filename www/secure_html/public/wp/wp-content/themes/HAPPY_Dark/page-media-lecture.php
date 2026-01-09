<?php
/*
Template Name: 講演活動の記録

*/
?>

<?php get_header(); ?>

	<div id="Contents">
		<div class="mainvisual__section">
        <div>CORPORATE<br><p>会社情報・リクルート</p></div>
		</div>

		<div id="pankuzu-wrapp"><div class="pan-border"><p class="pankuzu"><a href="/">トップ</a></p><p class="pankuzu"><a href="/corporate/">会社情報</a></p><p class="pankuzu"><a href="/corporate/media/media_list/">メディア情報</a></p><p class="pankuzu"><a href="/corporate/media/lecture/">講演活動の記録</a></p><p class="pankuzu no-arrow"><?php the_title(); ?></p></div></div>

		<div class="content">

        <div class="LColumn">
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
					<a>会社概要</a>
					<ul class="open">
					<li><a href="/corporate/company/profile/">企業情報</a></li>
					<li><a href="/corporate/company/winning/">認定・受賞一覧</a></li>
					<li><a href="/corporate/company/ip/">知的財産（特許・商標）</a></li>
					<li><a href="/pdf/fukusyoku.pdf">服飾関連の皆様へ（PDF）</a></li>
					<li><a href="/pdf/kanren_brand.pdf">アパレル業の皆様へ（PDF）</a></li>
					<li><a href="/pdf/kanren_ryutu.pdf">流通業の皆様へ（PDF）</a></li>
					<li><a href="/pdf/kanren_kaden.pdf">洗濯機メーカーの皆様へ（PDF）</a></li>
					</ul>
					</li>
					<li class="down">
					<a>メディア情報</a>
					<ul class="open">
					<li><a href="/corporate/media/media_list/">メディア報道特集</a></li>
					<li><a href="/corporate/media/past/">過去の報道記録</a></li>
					<li class="stay"><a href="/corporate/media/lecture/">講演活動の記録</a></li>
					<li><a href="/corporate/media/literary/">著作物一覧</a></li>
					</ul>
					</li>
					<li class="">
					<a>リクルート</a>
					<ul class="open">
					<li><a href="/corporate/recruit/cultivation/">人財育成について</a></li>
					<li><a href="/corporate/recruit/staff/">ケアメンテスタッフの募集</a></li>
					<li><a href="/corporate/recruit/executive/">経営幹部候補の募集</a></li>
					</ul>
					</li>
					<li class="">
					<a>環境への取組み</a>
					<ul class="open">
					<li><a href="/corporate/csr/weightlessness/">無重力バランス洗浄による環境保護</a></li>
					<li><a href="/corporate/csr/world2007/">環境と洗浄の世界大会 2007 秋</a></li>
					<li><a href="/corporate/csr/moribito/">森びとプロジェクト委員会</a></li>
					<li><a href="/corporate/csr/unicef/">世界の子供達を応援しよう</a></li>
					</ul>
					</li>
					<li class="">
					<a>ヨーロッパ洗浄技術交流紀行</a>
					<ul class="open">
					<li><a href="/corporate/europe/2013_summer/">ヨーロッパ交流紀行 2013 初夏</a></li>
					<li><a href="/corporate/europe/2012_autumn/">ヨーロッパ交流紀行 2012 初秋</a></li>
					<li><a href="/corporate/europe/2006_summer/">ヨーロッパ交流紀行 2006 夏</a></li>
					<li><a href="/corporate/europe/2006_spring/">ヨーロッパ交流紀行 2006 春</a></li>
					<li><a href="/corporate/europe/2005_autumn/">ヨーロッパ交流紀行 2005 秋</a></li>
					</ul>
					</li>
				</ul>
            </div>
        </div>

		</div><!--/content-->

  </div><!--/Contents-->

<?php get_footer(); ?>
