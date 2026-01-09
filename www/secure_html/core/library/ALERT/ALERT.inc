<?php

/* * **********************************
 * NAME:ALERT
 * DESC:
 *  アラート用のモジュール
 *  COMPONENTでHTML出力を行っており、
 *  そこで期待しているinputの形式にしてデータを返す。
 *
 * [形式]
 * ----------------------
 * array(
 * 		0 => array(
 * 			'target' => 'hoge',
 * 			'message' => 'hoge'
 * 		),
 * 		1 => array(
 * 			'target' => 'hoge',
 * 			'message' => 'hoge'
 * 		),
 * )
 * ----------------------
 *
 * 使い方について
 * 通常のテキストをセットする際は、set_textを使用すればいい。
 * targetはフォームのカラム毎にエラーを出す要望があるかもしれないので、
 * 念のためセットしておくほうがいい。
 *
 * 複数のエラーを配列に格納する際は、set_arrayを使用すればいい。
 * コントローラ側は、以下の様な実装で、アラート用の配列を生成することが可能。
 * $tmp_array[] = set_array('hoge', 'hoge')
 *
 * NOTICE:
 * CREATE: 2016.09.21 sonoda
 * *********************************** */
class ALERT {

	/* * **********************************
	 * NAME  : set_text
	 * INPUT : text / string / アラート文字列
	 * OUTPUT: alert_list / array / フォーマットした配列
	 * DESC  :
	 * NOTICE:
	 * CREATE: 2016.09.22 sonoda
	 * *********************************** */
	public static function set_text($text, $target = '') {

		if(StaticFunction::is_empty($text)) {
			return false;
		}

		return array(0 => array('target' => $target, 'message' => $text));
	}

	/* * **********************************
	 * NAME  : set_array
	 * INPUT : text / string / アラート文字列
	 * OUTPUT: alert_list / array / フォーマットした配列
	 * DESC  :
	 * NOTICE:
	 * CREATE: 2016.09.22 sonoda
	 * *********************************** */
	public static function set_array($text, $target = '') {

		if(StaticFunction::is_empty($text)) {
			return false;
		}

		return array('target' => $target, 'message' => $text);
	}

    /**
     * アラートをセッションにセットする
     */
	public static function set_session($text,$target = '')
	{
		$array = array();
        if(!StaticFunction::is_empty(SESSION::read('error'))) {
			$array = SESSION::read('error');
		}

        $array[] = array('message' => $text,'target' => $target);
        SESSION::write('error',$array);
	}

	/**
	 * セッションアラートを配列として返し、アラートセッションを消す。
	 */
    public static function get_session()
	{
        if(!StaticFunction::is_empty(SESSION::read('error'))) {
            $array = SESSION::read('error');
        }
        SESSION::delete('error');
        return $array;
	}
}

?>
