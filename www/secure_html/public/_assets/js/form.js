/*必須項目リアルタイムチェック*/
$(function(){
    jQuery("#form_1").validationEngine();
});

/*郵便番号から住所自動入力*/
//$(function () {
//	$('#zip').jpostal({
//		click : '#zipbtn',
//		postcode : [
//			'#zip'
//		],
//		address : {
//			'#pref'  : '%3',
//			'#address'  : '%4',
//			'#address2'  : '%5'
//		}
//	});
//});
//$(function () {
//	$('#zip_b').jpostal({
//		click : '#zipbtn_b',
//		postcode : [
//			'#zip_b'
//		],
//		address : {
//			'#pref_b'  : '%3',
//			'#address_b'  : '%4',
//			'#address2_b'  : '%5'
//		}
//	});
//});

/*無効な日付を選択させない*/
function dateCheck(year, month, day) {
  var y = Number(document.getElementsByName(year)[0].value);
  var m = Number(document.getElementsByName(month)[0].value);
  var day = document.getElementsByName(day)[0];
  var d = Number(day.value);
  if (y && m) {
    var ds = new Date(y, m, 0);
    var dsn = Number(ds.getDate());
    var html = '<option value="">日</option>';
    for(var i = 1; i <= dsn; i++) {
      if (i === d) {
        html += '<option value="' + i + '" selected>' + i + '日</option>';
      }
      else {
        html += '<option value="' + i + '">' + i + '日</option>';
      }
    }
    day.innerHTML = html;
  }
}
function dateCheck(year_b, month_b, day_b) {
  var y = Number(document.getElementsByName(year_b)[0].value);
  var m = Number(document.getElementsByName(month_b)[0].value);
  var day = document.getElementsByName(day_b)[0];
  var d = Number(day_b.value);
  if (y && m) {
    var ds = new Date(y, m, 0);
    var dsn = Number(ds.getDate());
    var html = '<option value="">日</option>';
    for(var i = 1; i <= dsn; i++) {
      if (i === d) {
        html += '<option value="' + i + '" selected>' + i + '日</option>';
      }
      else {
        html += '<option value="' + i + '">' + i + '日</option>';
      }
    }
    day.innerHTML = html;
  }
}
function dateCheck(year_c, month_c, day_c) {
  var y = Number(document.getElementsByName(year_c)[0].value);
  var m = Number(document.getElementsByName(month_c)[0].value);
  var day = document.getElementsByName(day_c)[0];
  var d = Number(day_c.value);
  if (y && m) {
    var ds = new Date(y, m, 0);
    var dsn = Number(ds.getDate());
    var html = '<option value="">日</option>';
    for(var i = 1; i <= dsn; i++) {
      if (i === d) {
        html += '<option value="' + i + '" selected>' + i + '日</option>';
      }
      else {
        html += '<option value="' + i + '">' + i + '日</option>';
      }
    }
    day.innerHTML = html;
  }
}

/*お申し込み・ご注文 アコーディオン*/
$( document ).ready(function() {
		$(".accordionTxt").click(function () {
			$(this).next().slideToggle();
			$(this).toggleClass("active");
		});
});


/*メルマガSP アコーディオン*/
$( document ).ready(function() {
	if ($(window).width() < 1024) {
		$(".contactTxt").click(function () {
			$(this).next().slideToggle();
			$(this).toggleClass("active");
		});
	}
});