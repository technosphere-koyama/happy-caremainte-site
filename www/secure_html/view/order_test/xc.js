/*無効な日付を選択させない*/
function dateCheckXc(year, month, day) {
  eval('var y = Number(document.getElementsByName(\'' + year + '\')[0].value);');
  eval('var m = Number(document.getElementsByName(\'' + month + '\')[0].value);');
  eval('var day = document.getElementsByName(\'' + day + '\')[0];');
  var d = Number(day.value);
  if (y && m) {
    var ds = new Date(y, m, 0);
    var dsn = Number(ds.getDate());
    var html = '<option value="">日</option>';
    for (var i = 1; i <= dsn; i++) {
      if (i === d) {
        html += '<option value="' + i + '" selected>' + i + '日</option>';
      } else {
        html += '<option value="' + i + '">' + i + '日</option>';
      }
    }
    day.innerHTML = html;
  }
}
function postApi(dataArray, target, type) {
  var defer = $.Deferred();
  var err = 0;

  $.ajax({
    type: type,
    url: target,
    cache: false, // ie8対策
    //jsonpCallback: 'callback',
    //crossDomain: true,
    data: dataArray,
    timeout: 40000,
    dataType: 'json',
    /* functions */
    scriptCharset: 'utf-8',
    success: defer.resolve,
    error: function(XMLHttpRequest, textStatus, errorThrown) {
      err++;
      if (err < 2) {
        $.ajax(this);
        alert('送信に失敗しました');
      } else {
      }
    },
  });
  return defer.promise();
}

$(document).ready(function() {

  var like_url = '/_API/forExternal/likeApi.php';

  /*---すべてのいいねを巡回していいねしているか判定---*/
  $('.postingLike').each(function() {
    var res_num = $(this).find('a').attr('rel');
    if ($.inArray(res_num, like_array) != -1) {
      $(this).addClass('on');
    } else {
      $(this).removeClass('on');
    }
  });

  /*------ いいね -------*/
  $('.postingLike').find('a').click(function() {
    var click_link = $(this);
    var now_count = $(this).find('.like_count').html();
    var rel = $(this).attr('rel');
    var rel_array = rel.split(':');

    if (click_link.parent('.postingLike').hasClass('on')) {
      var likeArray = {
        'mode': 'dislike',
        'type': rel_array[0],
        'target_id': rel_array[1],
      };

      postApi(likeArray, like_url, 'GET').done(function(json) {

        var set_count = parseInt(now_count);
        set_count--;

        if (json.code == '200') {
          click_link.parent('.postingLike').removeClass('on');
          click_link.find('.like_count').html(set_count);
        }
      });
    } else {
      var target_id = $(this).attr('rel');
      var likeArray = {
        'mode': 'like',
        'type': rel_array[0],
        'target_id': rel_array[1],
      };

      postApi(likeArray, like_url, 'GET').done(function(json) {

        var set_count = parseInt(now_count);
        set_count++;

        if (json.code == '200') {
          click_link.parent('.postingLike').addClass('on');
          click_link.find('.like_count').html(set_count);
        }
      });
    }
  });
});

/*submitの前にvalidateチェックを実行する*/
function validate(form) {
  if (!$(form).validationEngine('validate')) {
    return false;
  }
  return true;
}

function xc_taking_check() {
  var y = $('[name=taking_y]').val();
  var m = $('[name=taking_m]').val();
  var day = $('[name=taking_d]').val();
  var sd = parseInt(
      String(y) + ( '00' + m ).slice(-2) + ( '00' + day ).slice(-2));

  if (sd >= 20170619) {
    $('.sw201705').hide().find('[type="checkbox"]').prop('checked', false);
    $('.sw201706').show();
  } else {
    $('.sw201705').show();
    $('.sw201706').hide().find('[type="checkbox"]').prop('checked', false);
  }
}

