<?php get_header(); ?>

<div id="Contents" class="media">
	<div class="mainvisual__section">
        <div>CORPORATE<br><p>会社情報・リクルート</p></div>
	</div>
		<div id="pankuzu-wrapp"><div class="pan-border"><p class="pankuzu"><a href="/">ハッピーケアメンテ トップ</a></p><p class="pankuzu"><a href="/corporate/">会社情報</a></p><p class="pankuzu"><a href="/corporate/media/media_list/">メディア情報</a></p><p class="pankuzu no-arrow">講演活動の記録</p></div></div>

<div class="content">
        <div class="LColumn">
        	<div class="pagettl"><h1>講演活動の記録</h1></div>
        	<div class="pagettl-sub"></div>
        	<p>
        	当社、代表 橋本英夫が、経営から社員教育にいたるまでさまざまな切り口でお話いたします。<br />
            講演会依頼については、電話またはメールでお問合せ下さい。<br />
            e-mail：y-imada@kyoto-happy.co.jp　　TEL：0774-28-1288
            </p>

            <br /><br />
<div class="bg_w">
            <h2>これまでのレポート</h2>
            <?php if(have_posts()): while(have_posts()): the_post(); ?>

            <table class="mediaTable lecture">
                <tbody>
                <tr>
                <th colspan="2"><?php the_time('Y.m.d') ?></th>
                </tr>
                <tr>
                <td>タイトル</td>
                <td><?php if(get_field('meeting_page')): ?><a href="<?php the_permalink() ?>"><?php endif; ?><?php the_title()?><?php if(get_field('meeting_page')): ?></a><?php endif; ?></td>
                </tr>
                <tr>
                <td>会　場</td>
                <td><?php the_field('meeting_Venue') ?></td>
                </tr>
                <tr>
                <td>主　催</td>
                <td><?php the_field('meeting_Sponsor') ?></td>
                </tr>
                <tr>
                <td>参加人数</td>
                <td><?php the_field('meeting_Number') ?></td>
                </tr>
                </tbody>
            </table>

            <?php endwhile; endif; ?>
</div>

        </div>
        <?php get_template_part('nav','corporate'); ?>
    </div><!--/content-->

</div><!--/Contents-->

<?php get_footer(); ?>
