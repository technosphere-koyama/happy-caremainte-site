<?php get_header(); ?>
  
	<div id="Contents">
		<div class="mainvisual__section">
			<div>KNOWLEDGE<br><p>おしゃれの雑学</p></div>
		</div>
	
		<?php breadcrumb(); ?>
	
		<div class="content">
			<h4>「シミ・黄ばみの正体」や「素材・繊維の特徴」など、<br class="PCpart">
            オシャレをもっと楽しむための知って得する情報が満載です。随時更新しています。</h4>
		
			<ul class="section">
<?php if(have_posts()): while(have_posts()): the_post(); ?>
				<li><a href="<?php the_permalink() ?>"><img src="<?php the_field('index_img'); ?>" alt="<?php the_title() ?>"></a>
                	<p class="midashi"><a href="<?php the_permalink() ?>"><?php the_title() ?></a></p><p class="line"></p>
                	<p class="text"><?php echo mb_substr(strip_tags($post-> post_content),0,100); ?></p>
				</li>
<?php endwhile; endif; ?>

			</ul>        
        
		</div><!--/content--> 
    
  </div><!--/Contents--> 
  
<?php get_footer(); ?>
