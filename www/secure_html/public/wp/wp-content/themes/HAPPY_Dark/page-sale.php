<?php
/*
Template Name: セール情報

*/
?>

<?php
$redirect_url = urlencode($_SERVER["REQUEST_URI"]);

if(class_exists ('StaticFunction')) {
	if (!StaticFunction::is_empty(SESSION::read("PUBLIC_USER.name1"))) {
		$mypage1 = '<!--';
		$mypage2 = '-->';
		$mypage_btn = '<input type="button" id="btn" class="btn" value="お申込み注文" onClick="location.href=\'/order/form.html?special=mypagesale\'">';
	}
	else {
		$first1 = '<!--';
		$first2 = '-->';
	}
}
else {
	if (!session_id()) {
		session_name("kh");
		session_save_path($_SERVER['DOCUMENT_ROOT'] . "/../core/tmp/session");
		@session_start();
	}
	if (isset($_SESSION['PUBLIC_USER']['name1'])) {
		$mypage1 = '<!--';
		$mypage2 = '-->';
		$mypage_btn = '<input type="button" id="btn" class="btn" value="お申込み注文" onClick="location.href=\'/order/form.html?special=mypagesale\'">';
	}
	else {
		$first1 = '<!--';
		$first2 = '-->';
	}
}
?>

<?php get_header(); ?>

	<div id="Contents">
		<div class="mainvisual__section">
        <div>SALE<br><p>優待券を取得</p></div>
		</div>

		<?php breadcrumb(); ?>

		<div class="content">

			<?php echo $first1 ?>
			<div class="sale">
				<div class="sale_header">
					<h2>マイページ会員のお客様だけに<br>さらにお得なご優待チケット！</h2>
					<p>いつもハッピー ケアメンテ&reg;をご利用いただきありがとうございます。
						<a href="/mypageuse/use_mypage/" target="_blank"><u>マイページ会員</u></a>のお客様にご利用いただだけるご優待チケットをご用意させていただきました。
					以下の「お申込み注文」ボタンからケアメンテ&reg;をご注文いただくと割引サービスをお受けいただけます。
					ご利用方法をお読みいただき、ご注文ください。<br />
					<br />
					<a href="/mypageuse/use_mypage/" target="_blank"><u>マイページ会員とは？</u></a>
					</p>
				</div>
				<div class="saleL">
					<?php if(get_field('sale_img')): ?><div class="saleimg SPpart"><img src="<?php the_field('sale_img'); ?>" alt="セール画像"></div><?php else : ?><?php endif; ?>
					<div class="ticket gold">
						<div class="title_sub">Happy ケアメンテサービス®</div>
						<div class="title">【会員ご優待】Thanks Ticket</div>
						<?php if(have_rows('sale_mypage')): ?>
						<?php while(have_rows('sale_mypage')): the_row(); ?>
						<div class="sale_warp">
						<div class="sale_content"><?php the_sub_field('list'); ?></div>
						<div class="sale_off"><?php the_sub_field('discount'); ?><?php the_sub_field('unit'); ?></div>
						</div>
						<?php endwhile; ?>
						<?php endif; ?>
						<div class="code">ご優待コード：【<?php the_field('sale_mypage_code'); ?>】</div>
					</div>
				</div>
				<div class="saleR">
					<?php if(get_field('sale_img')): ?><div class="saleimg PCpart"><img src="<?php the_field('sale_img'); ?>" alt="セール画像"></div><?php else : ?><?php endif; ?>
					<h2>ご優待チケットの<br class="SPpart">ご利用方法とお願い</h2>
					<ul>
					<?php
					if ( have_rows ( 'sale_caution' ) ) {
					while ( have_rows ( 'sale_caution' ) ) {
					the_row();
					echo '<li>'."\n";
					$s_repeat_table_number = get_sub_field ( 'list' );
					echo $s_repeat_table_number;
					echo '</li>'."\n";
					}
					} else {
					echo "";
					}
					?>
					</ul>
					<div class="btnarea"><input type="button" id="btn" class="btn" value="お申込み注文" onClick="location.href='/order/form.html?special=<?php the_field('sale_mypage_code'); ?>'"></div>
				</div>
			</div>
			<?php echo $first2 ?>

			<?php echo $mypage1 ?>
			<div class="sale">
				<div class="sale_header">
					<h2>会員登録していただくと<br class="PCpart">さらにお得なご優待チケットをご利用いただけます。</h2>
					<p>過去のお申し込み内容や電子カルテの閲覧、ハッピーSNSなどをご利用いただける<a href="/mypageuse/use_mypage/" target="_blank"><u>マイページ会員</u></a>に登録していただくと、さらにお得なご優待チケットをご利用いただけます。<br>
					ケアメンテ&reg;のご利用を検討いただいている方はぜひ会員登録をして、お得にご利用ください。<br />
					<br />
					<a href="/mypageuse/use_mypage/" target="_blank"><u>マイページ会員とは？</u></a>
					</p>
					<div class="memberbtnarea">
						<div class="line">
							<p class="PCpart">会員登録すればさらにお得！</p>
							<div class="btn"><a href="/entry/">新規会員登録</a></div>
							<div class="btn login"><a href="/login/?callback=/sale/">登録済みの方はこちら（ログイン）</a></div>
						</div>
					</div>
				</div>
				<div class="saleL">
					<div class="ticket">
						<div class="title_sub">Happy ケアメンテサービス®</div>
						<div class="title">【一般ご優待】Thanks Ticket</div>
						<?php if(have_rows('sale_first')): ?>
						<?php while(have_rows('sale_first')): the_row(); ?>
						<div class="sale_warp">
						<div class="sale_content"><?php the_sub_field('list'); ?></div>
						<div class="sale_off"><?php the_sub_field('discount'); ?><?php the_sub_field('unit'); ?></div>
						</div>
						<?php endwhile; ?>
						<?php endif; ?>
						<div class="code">ご優待コード：【<?php the_field('sale_first_code'); ?>】</div>
					</div>
					<div class="memberbtnarea PCpart">
						<div class="line">
							<p class="PCpart">会員登録すればさらにお得！</p>
							<div class="btn"><a href="/entry/">新規会員登録</a></div>
							<div class="btn login"><a href="/login/?callback=/sale/">登録済みの方はこちら（ログイン）</a></div>
						</div>
					</div>
				</div>
				<div class="saleR">
					<div class="btnarea"><input type="button" id="btn" class="btn" value="お申込み注文" onClick="location.href='/order/form.html?special=<?php the_field('sale_first_code'); ?>'"></div>
					<h2>ご優待チケットの<br class="SPpart">ご利用方法とお願い</h2>
					<ul>
					<?php
					if ( have_rows ( 'sale_caution' ) ) {
					while ( have_rows ( 'sale_caution' ) ) {
					the_row();
					echo '<li>'."\n";
					$s_repeat_table_number = get_sub_field ( 'list' );
					echo $s_repeat_table_number;
					echo '</li>'."\n";
					}
					} else {
					echo "";
					}
					?>
					</ul>
					<div class="btnarea"><input type="button" id="btn" class="btn" value="お申込み注文" onClick="location.href='/order/form.html?special=<?php the_field('sale_first_code'); ?>'"></div>
				</div>
			</div>
			<?php echo $mypage2 ?>

		</div><!--/content-->

  </div><!--/Contents-->

<?php get_footer(); ?>
