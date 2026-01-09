<?php get_header(); ?>
  
	<div id="Contents">
		<div class="mainvisual__section">
			<div>BRAND/SHOP LIST<br><p>提携ブランド／全国取扱い店舗一覧</p></div>
		</div>
	
		<?php breadcrumb(); ?>
	
	<div class="content">
        
        <div class="LColumn shopSearch" id="data-list">   
    	<div class="pagettl"><h1>ショップ検索</h1></div>         
		
		<?php if(have_posts()): while(have_posts()): the_post();
			$page = $post->post_name;
			$tax_name = 'list';
			$POSTID = $post->id;
		?>
				
		<?php endwhile; endif; ?>	

        </div>
        
        <div class="RColumn PCpart">
            <div class="localNav">
            	<ul>
<li class="firstRow"><a href="/shop_search/">ショップ検索</a></li>
<li class="down">
<a href="https://www.kyoto-happy.co.jp/shop/brand/abeno_harukas/">ショップ情報</a>
<ul class="open">
<li><a href="https://www.kyoto-happy.co.jp/shop/brand/abeno_harukas/">あべのハルカス 近鉄本店</a></li>
<li><a href="https://www.kyoto-happy.co.jp/shop/brand/sinjuku_takashimaya/">新宿タカシマヤ</a></li>
<li><a href="https://www.kyoto-happy.co.jp/shop/brand/yokohama_takashimaya/">横浜タカシマヤ</a></li>
<li><a href="https://www.kyoto-happy.co.jp/shop/brand/seibu_ikebukuro/">西武池袋本店</a></li>
<li><a href="https://www.kyoto-happy.co.jp/shop/brand/tomorrowland/">TOMORROWLAND</a></li>
<li><a href="https://www.kyoto-happy.co.jp/shop/brand/beams/">BEAMS</a></li>
<li><a href="https://www.kyoto-happy.co.jp/shop/brand/united-arrows/">UNITED ARROWS</a></li>
            	</ul>
            </div>
        </div>
      	
		</div><!--/content-->
    
	</div><!--/Contents--> 
  
<script type="text/javascript" src="//maps.google.com/maps/api/js?sensor=false&region=JP"></script>
<script type="text/javascript" src="//ajax.googleapis.com/ajax/libs/jquery/1.11.2/jquery.min.js"></script>
<script type="text/javascript" src="<?php echo home_url() ?>/gps_pointer/"></script>

<?php get_footer(); ?>