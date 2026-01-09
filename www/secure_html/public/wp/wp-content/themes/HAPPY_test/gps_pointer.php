<?php
/*
Template Name: gps_pointer

*/
?>
	;(function($, window, undefined){

	// 緯度経度取得後に、各データ毎にlat(緯度),lng(経度)が入ります。
	var dataList = [
	
<?php
			$args = array(
				'post_type' => 'shop',
				'posts_per_page' => -1, 
				);
				$my_posts = get_posts( $args );

				foreach ( $my_posts as $post ):
?>
			{"name": "<?php the_title()?>","lat": "<?php echo get_field('shop_latitude') ?>","lng": "<?php echo get_field('shop_longitude') ?>","url": "<?php the_permalink()?>","zip": "<?php echo get_field('shop_zip') ?>","address": "<?php echo get_field('shop_address') ?>"},
<?php
			endforeach;
			wp_reset_postdata();
?>
		];

	// 現在位置の取得
	function dfdCurrentPosition(){
		var dfd = $.Deferred();

		// Geolocationが使用可能かチェック
		if( !window.navigator.geolocation ) dfd.reject();

		// 現在地の取得
		window.navigator.geolocation.getCurrentPosition(
			// Success
			function(position){
				dfd.resolve(position);
			},
			// Error
			function(error){
				dfd.reject();
			},
			// Options
			{
				enableHighAccuracy:true, //位置情報の精度を高く
				timeout: 10000, //10秒でタイムアウト
				maximumAge: 600000 //10分間有効
			}
		);

		return dfd.promise();
	}


	// DOM Content Loaded
	function dfdDocumentReady(){
		var dfd = $.Deferred();
		$(function(){
			dfd.resolve($(document));
		});
		return dfd.promise();
	}


	// データが揃った段階でソートを開始
	$.when(
		dfdCurrentPosition(),
		dfdDocumentReady()
	)
	.done(function(position){

		// 現在地
		var coords = position.coords;

		// 距離の割り出しを行ない、各データにdistance属性を設定
		$.each(dataList, function(i, data){
			data.distance = getDistance(data.lat, data.lng, coords.latitude, coords.longitude, 0) / 1000; //kmで算出
            data.distance = floatFormat( data.distance, 2 ) ;
		});

		// 現在地からの距離が小さい順にソート
		dataList.sort(function(a, b){
			return (a.distance < b.distance) ? -1 : 1;
		});

		// データを出力
		var html =  "";

		$.each(dataList, function(i, data){
        	if(i === 11){
            	return false;
           	}
			html += '<ul>';
				html += '<li><a href="'+data.url+'">';
				html += data.name;
				html += '</a></li>';
				html += '<li>'+data.zip+'<br>'+data.address+'</li>';
				html += '<li><a href="https://maps.google.co.jp/maps?q='+data.lat+','+data.lng+'&z=15&iwloc=A">';
				html += '地図を確認';
				html += '</a></li>';
			html += '</ul>';
		});
        	
		$("#data-list").append(html);

	})
	.fail(function(){
		alert("お使いの端末の位置情報サービスが無効になっているか対応していないため、エラーが発生しました");
		console.log("error", arguments);
	});



	//2点間の緯度経度から距離を取得
	//測地線航海算法を使用して距離を算出する。
	function getDistance(lat1, lng1, lat2, lng2, precision){
	  var distance = 0;
	  if( ( Math.abs(lat1 - lat2) < 0.00001 ) && ( Math.abs(lng1 - lng2) < 0.00001 ) ) {
	    distance = 0;
	  }else{
	    lat1 = lat1 * Math.PI / 180;
	    lng1 = lng1 * Math.PI / 180;
	    lat2 = lat2 * Math.PI / 180;
	    lng2 = lng2 * Math.PI / 180;
	 
	    var A = 6378140;
	    var B = 6356755;
	    var F = ( A - B ) / A;
	 
	    var P1 = Math.atan( ( B / A ) * Math.tan(lat1) );
	    var P2 = Math.atan( ( B / A ) * Math.tan(lat2) );
	 
	    var X = Math.acos( Math.sin(P1) * Math.sin(P2) + Math.cos(P1) * Math.cos(P2) * Math.cos(lng1 - lng2) );
	    var L = ( F / 8 ) * ( ( Math.sin(X) - X ) * Math.pow( (Math.sin(P1) + Math.sin(P2) ), 2) / Math.pow( Math.cos(X / 2), 2 ) - ( Math.sin(X) - X ) * Math.pow( Math.sin(P1) - Math.sin(P2), 2 ) / Math.pow( Math.sin(X), 2) );
	 
	    distance = A * ( X + L );
	    var decimal_no = Math.pow(10, precision);
	    distance = Math.round(decimal_no * distance / 1) / decimal_no;
	  }
	  return distance;
	}


    function floatFormat( number, n ) {
        var _pow = Math.pow( 10 , n ) ;
    
        return Math.round( number * _pow ) / _pow ;
    }
}(jQuery, window));