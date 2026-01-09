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
        
	<?php 
		get_template_part('nav','pcrcolumn');
	?>
      	
		</div><!--/content-->
    
	</div><!--/Contents--> 
  
<script type="text/javascript" src="//maps.google.com/maps/api/js?sensor=false&region=JP"></script>
<script type="text/javascript" src="//ajax.googleapis.com/ajax/libs/jquery/1.11.2/jquery.min.js"></script>
<script type="text/javascript" src="<?php echo home_url() ?>/gps_pointer/"></script>

<?php get_footer(); ?>