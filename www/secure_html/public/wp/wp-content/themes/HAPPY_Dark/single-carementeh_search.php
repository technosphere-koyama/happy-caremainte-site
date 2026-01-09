<?php get_header(); ?>
<section id="case_detail">
	<div class="container">
		<div class="backBtn"><a href="">BACK</a></div>
		<div class="case_detailWrap">
			<div class="lBox">
				<h2 class="tac">Before<span></span>After</h2>
				<ul class="case_detail_list">
					<?php for( $i = 1; $i <= 7; $i++ ) : #XXX: 実際にはカスタム投稿タイプの仕様に合わせてください ?>
						<li>
							<div class="itemBox">
								<div><h3><?php echo $i; ?></h3></div>
								<div class="case_list_img">
									<img src="/_assets/wp/dummy/before<?php printf("%02d", $i); ?>.jpg" alt="before<?php printf("%02d", $i); ?>">
								</div>
								<div class="case_list_img">
									<img src="/_assets/wp/dummy/after<?php printf("%02d", $i); ?>.jpg" alt="after<?php printf("%02d", $i); ?>">
								</div>
							</div>
						</li>
					<?php endfor; ?>
				</ul>
				<p>※ビフォーアフターの画像と現物に差異がある場合がございます。ご了承ください。</p>
			</div>
			<div class="rBox">
				<ul>
					<li class="info01">
						<h3># 000000</h3>
						<ul>
							<li>
								<div class="label_box">
									<span class="label">ア</span>
									<span class="label">イ</span>
									<span class="label">テ</span>
									<span class="label">ム</span>
									<span class="label">：</span>
								</div>婦人ジャケット</li>
							<li>
								<div class="label_box">
									<span class="label">色</span>
									<span class="label">・</span>
									<span class="label">柄</span>
									<span class="label">：</span>
								</div>緑系チェック</li>
							<li>
								<div class="label_box">
									<span class="label">ブ</span>
									<span class="label">ラ</span>
									<span class="label">ン</span>
									<span class="label">ド</span>
									<span class="label">：</span>
								</div>MOGA</li>
							<li>
								<div class="label_box">
									<span class="label">素</span>
									<span class="label">&nbsp;&nbsp;</span>
									<span class="label">材</span>
									<span class="label">：</span>
								</div>表地／ﾚｰﾖﾝ82% ｼﾙｸ10% ﾎﾟﾘｴｽﾃﾙ4% ｷｭﾌﾟﾗ4%
								<br class="pc">裏地／ｷｭﾌﾟﾗ100%</li>
						</ul>
					</li>
					<li class="info02">
						<h3>ケアラベル</h3>
						<img src="/_assets/wp/dummy/carelabel01.jpg" alt="carelabel01">
						<img src="/_assets/wp/dummy/carelabel02.jpg" alt="carelabel02">
					</li>
					<li class="info03">
						<div class="status_box">
							<div class="status_img">
								<h3>FRONT</h3>
								<div class="status_img_figure front"><img src="<?php echo get_stylesheet_directory_uri(); ?>/img/front01.png" alt="FRONT">
									<div class="status01">4</div>
									<div class="status02">5</div>
									<div class="status03">6</div>
								</div>
							</div>
							<div class="status_img">
								<h3>BACK</h3>
								<div class="status_img_figure back"><img src="<?php echo get_stylesheet_directory_uri(); ?>/img/back01.png" alt="BACK">
								</div>
							</div>
						</div>
					</li>
					<li class="info04">
						<h3>コメント</h3>
						<p>レーヨン・シルク混紡で鮮やかなグリーン系色が特徴の婦人ジャケットです。汗をかかれており襟や脇・袖口に黄ばみと汚れが重なった状態でしたが、ハッピーの無重力バランス洗浄による水洗いとリプロン技術で、元色が蘇り新品のように復活しました。</p>
					</li>
					<li class="info05">
						<h3>お預り時点状態</h3>
						<div class="status_box">
							<div class="status_box_inner">
								<h4>◎ 汚れ</h4>
								<div class="status_img">
									<div>
										<h5>FRONT</h5>
										<div class="status_img_figure front"><img src="<?php echo get_stylesheet_directory_uri(); ?>/img/front.png" alt="FRONT">
											<div class="status01">
												<img src="<?php echo get_stylesheet_directory_uri(); ?>/img/status01.svg" alt="シミ"><img src="<?php echo get_stylesheet_directory_uri(); ?>/img/status01.svg" alt="シミ"><img src="<?php echo get_stylesheet_directory_uri(); ?>/img/status01.svg" alt="シミ"><img src="<?php echo get_stylesheet_directory_uri(); ?>/img/status01.svg" alt="シミ"><img src="<?php echo get_stylesheet_directory_uri(); ?>/img/status01.svg" alt="シミ">
											</div>
											<div class="status02_01">
												<img src="<?php echo get_stylesheet_directory_uri(); ?>/img/status02.svg" alt="キバミ">
											</div>
											<div class="status02_02">
												<img src="<?php echo get_stylesheet_directory_uri(); ?>/img/status02.svg" alt="キバミ">
											</div>
											<div class="status02_03">
												<img src="<?php echo get_stylesheet_directory_uri(); ?>/img/status02.svg" alt="キバミ">
											</div>
										</div>
									</div>
									<div>
										<h5>BACK</h5>
										<div class="status_img_figure back"><img src="<?php echo get_stylesheet_directory_uri(); ?>/img/back.png" alt="BACK">
											<div class="status01">
												<img src="<?php echo get_stylesheet_directory_uri(); ?>/img/status01.svg" alt="シミ"><img src="<?php echo get_stylesheet_directory_uri(); ?>/img/status01.svg" alt="シミ"><img src="<?php echo get_stylesheet_directory_uri(); ?>/img/status01.svg" alt="シミ"><img src="<?php echo get_stylesheet_directory_uri(); ?>/img/status01.svg" alt="シミ"><img src="<?php echo get_stylesheet_directory_uri(); ?>/img/status01.svg" alt="シミ">
											</div>
											<div class="status02_01">
												<img src="<?php echo get_stylesheet_directory_uri(); ?>/img/status02.svg" alt="キバミ">
											</div>
											<div class="status02_02">
												<img src="<?php echo get_stylesheet_directory_uri(); ?>/img/status02.svg" alt="キバミ">
											</div>
											<div class="status02_03">
												<img src="<?php echo get_stylesheet_directory_uri(); ?>/img/status02.svg" alt="キバミ">
											</div>
										</div>
									</div>
								</div>
							</div>
							<div class="status_box_inner">
								<h4>◎ 損傷</h4>
								<div class="status_img">
									<div>
										<h5>FRONT</h5>
										<div class="status_img_figure"><img src="<?php echo get_stylesheet_directory_uri(); ?>/img/front.png" alt="FRONT"></div>
									</div>
									<div>
										<h5>BACK</h5>
										<div class="status_img_figure"><img src="<?php echo get_stylesheet_directory_uri(); ?>/img/back.png" alt="BACK"></div>
									</div>
								</div>
							</div>
						</div>
						<ul class="status_guide">
							<li><img src="<?php echo get_stylesheet_directory_uri(); ?>/img/status01.svg" alt="シミ">：シミ</li>
							<li><img src="<?php echo get_stylesheet_directory_uri(); ?>/img/status02.svg" alt="キバミ">：キバミ</li>
							<li><img src="<?php echo get_stylesheet_directory_uri(); ?>/img/status03.svg" alt="変色">：変色</li>
							<li><img src="<?php echo get_stylesheet_directory_uri(); ?>/img/status04.svg" alt="脱色">：脱色</li>
							<li><img src="<?php echo get_stylesheet_directory_uri(); ?>/img/status05.svg" alt="てかり">：てかり</li>								
							<li><img src="<?php echo get_stylesheet_directory_uri(); ?>/img/status06.svg" alt="すり切れ">：すり切れ</li>								
							<li><img src="<?php echo get_stylesheet_directory_uri(); ?>/img/status07.svg" alt="破れ">：破れ</li>								
							<li><img src="<?php echo get_stylesheet_directory_uri(); ?>/img/status08.svg" alt="穴">：穴</li>
							<li><img src="<?php echo get_stylesheet_directory_uri(); ?>/img/status09.svg" alt="キズ">：キズ</li>
							<li><img src="<?php echo get_stylesheet_directory_uri(); ?>/img/status10.svg" alt="ほつれ">：ほつれ</li>
							<li><img src="<?php echo get_stylesheet_directory_uri(); ?>/img/status11.svg" alt="カビ">：カビ</li>
							<li><img src="<?php echo get_stylesheet_directory_uri(); ?>/img/status12.svg" alt="移染">：移染</li>
							<li><img src="<?php echo get_stylesheet_directory_uri(); ?>/img/status13.svg" alt="糸引き（長）">：糸引き（長）</li>
							<li><img src="<?php echo get_stylesheet_directory_uri(); ?>/img/status14.svg" alt="糸引き（短）">：糸引き（短）</li>
							<li><img src="<?php echo get_stylesheet_directory_uri(); ?>/img/status15.svg" alt="毛足が無くなっている">：毛足が無くなっている</li>
							<li><img src="<?php echo get_stylesheet_directory_uri(); ?>/img/status16.svg" alt="袖口、裾などの伸び">：袖口、裾などの伸び</li>
							<li><img src="<?php echo get_stylesheet_directory_uri(); ?>/img/status17.svg" alt="その他">：その他</li>
						</ul>
					</li>
					<li class="info06">
						<h3>価格</h3>
						<div class="menuBox bordr_btm">
							<div class="name">アクアドライ上着</div>
							<div class="price"><span>3,500</span>円</div>
						</div>
						<div class="menuBox bordr_btm">
							<div class="name">リプロン シミ汚れ落とし（1）</div>
							<div class="price"><span>2,600</span>円</div>
						</div>
						<div class="menuBox">
							<div class="name">リプロン 黄ばみ取り</div>
							<div class="price"><span>2,500</span>円</div>
						</div>
						<div class="total">
							<div class="name">合計（税抜）</div>
							<div class="price"><span>8,600</span>円</div>
						</div>
						<p>※表示価格は、カウンセリング終了当時の参考価格（目安）です。<br>大半が旧価格での金額表示となりますのでご注意ください。</p>
					</li>
				</ul>
			</div>
		</div>
		<div class="postingForm">
			<form>
				<textarea name="comment" placeholder="コメント投稿"></textarea>
				<div class="btn">
					<button type="submit">投 稿</button>
				</div>
			</form>
		</div>
	</div>
</section>
<!--　/#case_detail -->

<?php get_footer(); ?>
