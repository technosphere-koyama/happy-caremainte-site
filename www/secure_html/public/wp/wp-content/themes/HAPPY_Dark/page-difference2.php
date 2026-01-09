<?php get_header(); ?>
<link rel="stylesheet" href="https://www.kyoto-happy.co.jp/wp/wp-content/themes/HAPPY_Dark/css/real_value.css">
<style>
</style>
	<div id="Contents">
		<div class="mainvisual__section real_value__back">
		        <div>CORPORATE<br><p><?php the_title() ?></p></div>
		</div>
		<?php breadcrumb(); ?>
		<div class="content">
			<div class="difference2-title">■ <?php the_field('title-01'); ?></div>
			<p><?php the_field('text-01'); ?></p>
			<div class="difference2-title">■ <?php the_field('title-02'); ?></div>
			<table class="difference2-table">
				<tr>
					<td colspan="2"><?php the_field('text-02'); ?></td>
					<td rowspan="4" class="difference2-table-img"><img src="https://www.kyoto-happy.co.jp/wp/wp-content/uploads/2025/07/happy-logo.png" alt="クリーニングとケアメンテの違い…ここが知りたい" /></td>
				</tr>
				<tr>
					<th>Care…</th>
					<td><?php the_field('text-02-01'); ?></td>
				</tr>
				<tr>
					<th>Mente…</th>
					<td><?php the_field('text-02-02'); ?></td>
				</tr>
				<tr>
					<th>h …</th>
					<td><?php the_field('text-02-03'); ?></td>
				</tr>
			</table>
			<div class="difference2-title">■ <?php the_field('title-03'); ?></div>
			<p><?php the_field('text-03'); ?></p>
			<div class="difference2-title">■ <?php the_field('title-04'); ?></div>
			<p><?php the_field('text-04'); ?></p>
			<div class="difference2-link">
				→ もったいないの語源は、<a href="https://www.kyoto-happy.co.jp/real_value/">コチラ</a><br />
				→ 感動の「こぼれ話」は、<a href="https://www.kyoto-happy.co.jp/merchandising/">コチラ</a><br />
				→ 本物の「真・価値」創造は、<a href="https://www.kyoto-happy.co.jp/real_value/#A">コチラ</a><br />
				→ 2000点を超えるケアメンテbefore&after実例集は、<a href="https://www.kyoto-happy.co.jp/carementeh_search/result.html">コチラ</a>
			</div>
		</div><!--/content--> 
	</div><!--/Contents--> 
<?php get_footer(); ?>
