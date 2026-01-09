<?php
/*
Template Name: movie

*/
?>

<?php get_header(); ?>
  
	<div id="Contents">
		<div class="mainvisual__section">
        <div>MOVIE<br><p>プロモーションビデオ</p></div>
        <div class="youtube_icon"><img src="/_assets/img/movie/icon.png" alt="youtube"></div>
		</div>
	
		<?php breadcrumb(); ?>
	
		<div class="content">
       		<div class="movie-cont">
				<div id="player"></div>
				<ul id="thumbnail"></ul>
			</div>
		<script src="/_assets/js/jquery.movie.js"></script>
		</div><!--/content--> 
    
  </div><!--/Contents--> 
  
<?php get_footer(); ?>
