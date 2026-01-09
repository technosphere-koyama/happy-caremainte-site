// プレーヤーのサイズを指定
var ytWidth = 1000;
var ytHeight = 563;

// 埋め込むyoutubeのIDを指定
var ytData = [
	{
		id: '4okBMUdZc_E',
		title: 'ケアメンテの仕事スタイルをご紹介',
		duration: '17:06'
	}, {
		id: 'mD-PtkxqTcY',
		title: 'ケアメンテご利用の流れ（ご注文・お申し込み方法）',
		duration: '2:33'
	}, {
		id: 'eC0pAD3-pbQ',
		title: 'オープニング',
		duration: '1:39'
	}, {
		id: 'urRD7z71bws',
		title: 'ハッピー 電子カルテシステム',
		duration: '2:12'
	}, {
		id: '462-mbvqCsc',
		title: 'カウンセリングとトレーサビリティ',
		duration: '1:42'
	}, {
		id: 'WXoQ_QsNUtw',
 		title: '水洗いとドライクリーニングの特徴',
 		duration: '2:20'
 	}, {
		id: 'XOZDiuoTP7c',
		title: '基本洗浄 アクアドライ',
		duration: '2:06'
	}, {
		id: 'lyfSWybcPlM',
		title: '再生産技術 リプロン',
		duration: '1:11'
	}, {
		id: 'tOlgzVOOqjc',
		title: '無重力バランス洗浄',
		duration: '2:55'
	}, {
		id: 'QpfCelO2X3o',
		title: 'シルエットプレス',
		duration: '1:21'
	}, {
		id: '-7DC4Z0p1dk',
		title: 'ボタン付け・検品・梱包・出荷',
		duration: '0:57'
	}, {
		id: 'bVQYSM9ubyQ',
		title: 'エンディング',
		duration: '1:28'
	}
];

ytBaseUrl = 'https://www.youtube.com/embed/';

// サムネイル画像の埋め込み準備
var thumbInsert = '';
for(var i = 0; i < ytData.length; i++) {
	thumbInsert += '<li><a href="' + ytBaseUrl + ytData[i]['id'] + '" class="ytp">';
	thumbInsert += '<img src="https://img.youtube.com/vi/' + ytData[i]['id'] + '/mqdefault.jpg" alt="" />';
	thumbInsert += '</a>';
	thumbInsert += '<div class="ytdetail">';
	thumbInsert += '<h3><a href="' + ytBaseUrl + ytData[i]['id'] + '" class="ytp">' + ytData[i]['title'] + '</a></h3>';
	thumbInsert += '<p class="time">' + ytData[i]['duration'] + '　<img src="/_assets/img/movie/icon_gray.png" class="ytlogo" style="width: 26px;" /></p>';
	thumbInsert += '</div></li>';
}

var ytPlayer;
// YouTube Player APIを読み込む
var tag = document.createElement('script');
tag.src = "https://www.youtube.com/iframe_api";
var firstScriptTag = document.getElementsByTagName('script')[0];
firstScriptTag.parentNode.insertBefore(tag, firstScriptTag);

// API読み込み後にプレーヤーを埋め込む
function onYouTubeIframeAPIReady() {
	ytPlayer = new YT.Player('player', {
		height: ytHeight,
		width: ytWidth,
		videoId: ytData[0]['id']
	});
}
// 動画の再生
function play(ytId, seekTime) {
	ytPlayer.loadVideoById(ytId, seekTime);
}

$(function() {
	// サムネイル画像の埋め込み
	$('#thumbnail').append(thumbInsert);

	$(document).on('click', '#thumbnail a', function() {
		ytId = $(this).attr('href').replace(ytBaseUrl, '');
		play(ytId, 0);
		return false;
	});
});


//ユーザーエージェント設定
var _ua = (function(u){
	return {
	Tablet:u.indexOf("ipad") != -1 || (u.indexOf("android") != -1 && u.indexOf("mobile") == -1) || (u.indexOf("firefox") != -1 && u.indexOf("tablet") != -1) || u.indexOf("kindle") != -1 || u.indexOf("silk") != -1 || u.indexOf("playbook") != -1,
	Mobile:(u.indexOf("windows") != -1 && u.indexOf("phone") != -1) || u.indexOf("iphone") != -1 || u.indexOf("ipod") != -1 || (u.indexOf("android") != -1 && u.indexOf("mobile") != -1) || (u.indexOf("firefox") != -1 && u.indexOf("mobile") != -1) || u.indexOf("blackberry") != -1,
	IE:u.indexOf('msie') != -1 || u.indexOf('trident') != -1
	}
	})(window.navigator.userAgent.toLowerCase());
	var _ap = (function(ap){
	return {
	OldIE:
	ap.indexOf("msie 6.") !=  -1 ||
	ap.indexOf("msie 7.") !=  -1 ||
	ap.indexOf("msie 8.") !=  -1 ||
	ap.indexOf("msie 9.") !=  -1
	}
	})(window.navigator.appVersion.toLowerCase());

	if(_ua.Mobile){ //Mobile
	var ua_num = 3;
	}else if(_ua.Tablet){ //Tablet
	var ua_num = 2;
	}else if(_ua.IE && _ap.OldIE){ //OLD IE
	var ua_num = 1;
	}else{
	var ua_num = 0;
}


//動画選択時にプレイヤーの高さまで移動
$(function(){
    $('.ytp').click(function () {
        if(ua_num == 3){
        $("html,body").animate({scrollTop:220},"300");
		}else{
        $("html,body").animate({scrollTop:580},"300");
		};
    });
});
