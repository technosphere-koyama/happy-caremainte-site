<?php

/* * **********************************
 * NAME:Image
 * DESC:
 *  画像処理用モジュール
 * NOTICE:
 * CREATE: 2015.11.13 hesaka
 * *********************************** */
class Image {

	private $img_info;
	private $ext;
	private $image_data;
	private $function;
	private $quality;
	private $create_image_data;

	/*	 * **********************************
	 * NAME  : get_tmp_file_url
	 * INPUT : $system_id / string / ユーザーのsystem_id
	 * OUTPUT:
	 * 		string
	 * DESC  :
	 * 		tmp画像のURLパスを返す
	 * NOTICE:
	 * CREATE: 2016.11.14 aoyama
	 * *********************************** */
	public function get_tmp_file_url($date_dir, $file_name) {

		//バリデーション。もう少し詳細にしたほうが良いかも（2016.11.14 aoyama）
		if (StaticFunction::is_empty($date_dir) || StaticFunction::is_empty($file_name)) {
			return;
		}

		$file_path = "/images/tmp/" . $date_dir . "/" . $file_name;
		$system_file_path = $tmp_dir = DIR_SYSTEM_IMG_TMP . DS . $date_dir . DS . $file_name;

		if (!file_exists($system_file_path)) {
			return;
		}
		return $file_path;
	}

	/*	 * **********************************
	 * NAME  : delete
	 * INPUT : 
	 * 		$dir / string / フォルダ
	 * 		$file_name/ string / ファイル名
	 * OUTPUT:
	 * 		true / 成功時
	 * 		false / 失敗時
	 * DESC  :
	 *  ファイルを削除する
	 * NOTICE:
	 * CREATE: 2016.10.30 aoyama
	 * *********************************** */
	public function delete($dir, $file_name) {

		if ($this->image_exists($dir, $file_name)) {
			unlink($dir . $file_name);
			return true;
		}
		return false;
	}

	/*	 * **********************************
	 * NAME  : load
	 * INPUT : src / string / 対象ファイルパス(フル)
	 * OUTPUT: true / 成功時
	 *         false / 失敗時
	 * DESC  :
	 *  ファイルをロードする
	 * NOTICE:
	 *  各メンバに情報をセットする
	 *  最初にこれを実行しておく必要がある
	 * 
	 *  POSTで投げられたものの場合、srcに指定するのは以下となる
	 *  $_FILES[form-name]['tmp_name']
	 * 
	 * CREATE: 2015.11.14 hesaka
	 * *********************************** */
	public function load($src) {

		//空の場合はエラー
		if (StaticFunction::is_empty($src)) {
			LOGS_ERR('parameter is empty');
			return false;
		}

		//mimeタイプを取得
		$this->img_info = getimagesize($src);

		$this->img_path = $src;
		$this->width = $this->img_info[0];
		$this->height = $this->img_info[1];

		// mimeタイプにより処理変更
		switch ($this->img_info['mime']) {
			case "image/jpeg":
				$this->ext = "jpg";
				$this->image_data = ImageCreateFromJPEG($src);
				$this->function = "ImageJpeg";
				$this->quality = "95";
				break;
			case "image/gif":
				$this->ext = "gif";
				$this->image_data = ImageCreateFromgif($src);
				$this->function = "ImageGif";
				$this->quality = "";
				break;
			case "image/png":
				$this->ext = "png";
				$this->image_data = imagecreatefrompng($src);
				$this->function = "ImagePng";
				$this->quality = "6";
				break;
			default:
				LOGS_WARN('mime type is out of assumption [' . $this->img_info['mime'] . ']');
				return false;
		}
		return true;
	}

	/*	 * **********************************
	 * NAME  : get_image_type
	 * INPUT : NONE
	 * OUTPUT: string / 拡張子
	 *         false / 失敗時
	 * DESC  :
	 *  ロードしたファイルのmimeタイプ(拡張子)を取得する
	 * NOTICE:
	 *  「.」は含まない
	 * CREATE: 2015.11.14 hesaka
	 * *********************************** */
	public function get_image_type() {

		//空チェック
		if (StaticFunction::is_empty($this->ext)) {
			return false;
		}

		return $this->ext;
	}

	/*	 * **********************************
	 * NAME  : resize_avatar
	 * INPUT : max_w / integer / リサイズ後の横幅サイズ
	 * OUTPUT: NONE
	 * DESC  :
	 * 		カルテ用の画像を生成する
	 * NOTICE:
	 * CREATE: 2016.11.4 aoyama
	 * *********************************** */
	public function create_chart($type, $small, $large) {

		$font = dirname(__FILE__) . "/fonts/ipam.ttf";
		$image = dirname(__FILE__) . "/chart_type/screen" . $type . ".jpg";

		$new_image = ImageCreateFromJPEG($image);

		// 色の指定  
		// RGB形式で色の指定を行います  
		$TextColor = ImageColorAllocate($new_image, 0, 0, 0);

		//マーク配置
		$array = array(
			"0" => "", "1" => "〇", "2" => "△", "3" => "×", "4" => "●",
			"5" => "◎", "6" => "▲", "7" => "■", "8" => "□", "9" => "※",
			"A" => "伸", "B" => "＃", "C" => "＃", "D" => "他", "E" => "◆",
			"F" => "カ", "G" => "移", "H" => "／", "I" => "。", "J" => "＊"
		);

		//  マーク小
		$x = 15;
		$y = 15;
		// テキストの埋め込み  
		for ($i = 0; $i < 225; $i++) {
			$left_pos = $i % 15;
			$top_pos = ceil(($i + 1) / 15);
			$text = $array[substr($small, $i, 1)];
			imageTtfText($new_image, 11, 0, ($x * $left_pos), ($y * $top_pos) - 2, $TextColor, $font, $text);
		}

		// マーク中
		$x2 = 75;
		$y2 = 75;
		// テキストの埋め込み  
		for ($i = 0; $i < 10; $i++) {
			if ($i == 9) {
				// マーク大
				// テキストの埋め込み  
				$text = $array[substr($large, $i, 1)];
				imageTtfText($new_image, 150, 0, 12, 184, $TextColor, $font, $text);
			} else {
				$left_pos = $i % 3;
				$top_pos = ceil(($i + 1) / 3);
				$text = $array[substr($large, $i, 1)];
				imageTtfText($new_image, 50, 0, ($x2 * $left_pos) + 3, ($y2 * $top_pos) - 13, $TextColor, $font, $text);
			}
		}

		//Mimeヘッダーの出力
		header("Content-Type: image/png");

		//メモリ上の画像データを出力
		Imagepng($new_image);
		exit;
	}

	/*	 * **********************************
	 * NAME  : resize_avatar
	 * INPUT : max_w / integer / リサイズ後の横幅サイズ
	 * OUTPUT: NONE
	 * DESC  :
	 *  ロードしたファイルをリサイズする
	 * NOTICE:
	 * CREATE: 2015.11.14 aoyama
	 * *********************************** */
	public function resize_avatar($max_w = 500) {

		//画像幅の取得
		$src_w = imagesx($this->image_data);
		//画像高の取得
		$src_h = ImageSy($this->image_data);
		// 縦横比
		$src_rate = $src_w / $src_h;

		//横長画像
		if ($src_w > $src_h) {
			$dst_h = $max_w;
			$dst_w = floor($dst_h * $src_rate);
			$dst_y = 0;
			$dst_x = floor(($dst_w - $max_w) / 2) * -1;
		} else {
			$dst_w = $max_w;
			$dst_h = floor($dst_w / $src_rate);
			$dst_x = 0;
			$dst_y = floor(($dst_h - $max_w) / 2) * -1;
		}

		// 画像作成
		$new_image = ImageCreateTrueColor($max_w, $max_w);

		// 元画像から再サンプリング
		ImageCopyResampled($new_image, $this->image_data, $dst_x, $dst_y, 0, 0, $dst_w, $dst_h, $src_w, $src_h);

		$this->create_image_data = $new_image;
	}

	/*	 * **********************************
	 * NAME  : resize
	 * INPUT : max_w / integer / リサイズ後の横幅サイズ
	 * OUTPUT: NONE
	 * DESC  :
	 *  ロードしたファイルをリサイズする
	 * NOTICE:
	 * CREATE: 2015.11.14 hesaka
	 * *********************************** */
	public function resize($max_w = 500) {

		//画像幅の取得
		$src_w = imagesx($this->image_data);
		//画像高の取得
		$src_h = ImageSy($this->image_data);
		// 縦横比
		$src_rate = $src_w / $src_h;

		if ($src_w > $max_w) {
			$new_w = $max_w;
			$new_h = floor($new_w / $src_rate);
		} else {
			$new_w = $src_w;
			$new_h = $src_h;
		}

		// 画像作成
		$new_image = ImageCreateTrueColor($new_w, $new_h);

		// 元画像から再サンプリング
		ImageCopyResampled($new_image, $this->image_data, 0, 0, 0, 0, $new_w, $new_h, $src_w, $src_h);

		$this->create_image_data = $new_image;
	}

	/*	 * **********************************
	 * NAME  : save
	 * INPUT : path / string / ファイル保存先パス
	 *         file_name / string / ファイル名
	 * OUTPUT: true / 成功時
	 *         false / 失敗時
	 * DESC  :
	 *  ロードしたファイルを指定保存先に保存する
	 * NOTICE:
	 *  POSTされたデータの元のファイル名で保存したい場合は
	 *  ファイル名の部分は以下を指定することとなる
	 *  $_FILES['photo']['name']
	 * CREATE: 2015.11.14 hesaka
	 * *********************************** */
	public function save($path, $file_name) {

		//空チェック
		if (StaticFunction::is_empty($path) || StaticFunction::is_empty($file_name)) {
			return false;
		}

		//ディレクトリがなければ作る
		if (!is_dir($path)) {
			LOGS_NOTICE('create directory!!! path=' . $path . ', file_name=' . $file_name);
			StaticFunction::create_dir($path);
		}

		if (CONF::read('IMAGE_CREATE.MODE') === "IMAGE_MAGIK") {
			// ImageMagik
			$cmd = 'convert -quality 75 -resize ' . $this->width . 'x' . $this->height . ' ' . $this->img_path . ' ' . $path . $file_name . '.' . $this->ext;
			exec($cmd);
//			unlink($tmpDir . $imgName);
		} else {


			/*
			 * mimetypeに合わせたメソッドにより画像を保存する
			 * 
			 * ImageJpeg
			 * 	引数：qualityには0から100が指定可能
			 * 	100の方がクオリティ高
			 * 	デフォルトでは75らしい
			 * ImagePng
			 * 	引数：qualityには0から9が指定可能
			 * 	品質というより、圧縮率のことらしく、0の方がクオリティ高く、9の方が低い
			 * 	デフォルトは6らしい
			 * ImageGif
			 * 	引数に、quality指定はできない
			 * 
			 * ImageGifにはquality指定できないため、quality指定がなければ、
			 * call_user_func()の第4引数を指定しないように分ける必要がある
			 */
			if (StaticFunction::is_empty($this->quality)) {
				call_user_func($this->function, $this->create_image_data, $path . $file_name);
			} else {
				call_user_func($this->function, $this->create_image_data, $path . $file_name, $this->quality);
			}
		}

		return true;
	}

	/*	 * **********************************
	 * NAME  : save_jpeg
	 * INPUT : path / string / ファイル保存先パス
	 *         file_name / string / ファイル名
	 * OUTPUT: true / 成功時
	 *         false / 失敗時
	 * DESC  :
	 *  ロードしたファイルを指定保存先にJPEGで保存する
	 * NOTICE:
	 * CREATE: 2016.10.19 aoyama
	 * *********************************** */
	public function save_jpeg($path, $file_name) {

		//空チェック
		if (StaticFunction::is_empty($path) || StaticFunction::is_empty($file_name)) {
			return false;
		}

		//ディレクトリがなければ作る
		if (!is_dir($path)) {
			//LOGS_NOTICE('create directory!!! path=' . $path . ', file_name=' . $file_name);
			StaticFunction::create_dir($path);
		}

		if (CONF::read('IMAGE_CREATE.MODE') === "IMAGE_MAGIK") {
			// ImageMagik
			$cmd = 'convert -quality 75 -resize ' . $this->width . 'x' . $this->height . ' ' . $this->img_path . ' ' . $path . $file_name . '.jpg';
			exec($cmd);
//			unlink($tmpDir . $imgName);
		} else {
			/*
			 * mimetypeに合わせたメソッドにより画像を保存する
			 * 
			 * ImageJpeg
			 * 	引数：qualityには0から100が指定可能
			 * 	100の方がクオリティ高
			 * 	デフォルトでは75らしい
			 * ImagePng
			 * 	引数：qualityには0から9が指定可能
			 * 	品質というより、圧縮率のことらしく、0の方がクオリティ高く、9の方が低い
			 * 	デフォルトは6らしい
			 * ImageGif
			 * 	引数に、quality指定はできない
			 * 
			 * ImageGifにはquality指定できないため、quality指定がなければ、
			 * call_user_func()の第4引数を指定しないように分ける必要がある
			 */
			$funstionName = "ImageJpeg";
			if (StaticFunction::is_empty($this->quality)) {
				call_user_func($funstionName, $this->create_image_data, $path . $file_name);
			} else {
				call_user_func($funstionName, $this->create_image_data, $path . $file_name, $this->quality);
			}
		}

		return true;
	}

	/*	 * **********************************
	 * NAME  : set_review_file
	 * INPUT : path / string / ファイル保存先パス
	 *         file_name / string / ファイル名
	 * OUTPUT: true / 成功時
	 *         false / 失敗時
	 * DESC  :
	 * 		tmpにあるレビューの添付ファイルを公開する
	 * NOTICE:
	 * CREATE: 2016.10.31 aoyama
	 * *********************************** */
	public function set_review_file($tmp_date, $tmp_file, $system_id) {

		$src_dir = DIR_SYSTEM_IMG_TMP . DS . $tmp_date . DS;
		$src_file = $tmp_file;
		$target_dir = DIR_PUBLIC_IMG . DS . "review" . DS . $system_id . DS;
		$target_file = $tmp_file;

		return self::move_file($src_dir, $src_file, $target_dir, $target_file);
	}

	/*	 * **********************************
	 * NAME  : set_timeline_public
	 * INPUT : path / string / ファイル保存先パス
	 *         file_name / string / ファイル名
	 * OUTPUT: true / 成功時
	 *         false / 失敗時
	 * DESC  :
	 * 		tmpにあるタイムラインの添付ファイルを公開用ディレクトリに移動し
	 *		公開状態にする。
	 * CREATE: 2016.10.21 aoyama
	 * UPDATE: 2017.2.13 aoyama
	 *		複数画像に対応するためDB処理も追加
	 * *********************************** */
	public function set_timeline_public($tmp_date, $tmp_file, $system_id, $timeline_id,$sort_num=0) {
		
		// フォルダの指定
		$src_dir = DIR_SYSTEM_IMG_TMP . DS . $tmp_date . DS;
		$src_file = $tmp_file;
		$target_dir = DIR_PUBLIC_IMG . DS . "user" . DS . $system_id . DS . $timeline_id . DS;
		$target_file = $tmp_file;
		
		//DBへの登録処理
		$tl = new TimelineModel();
		
		$datetime = DbDateTime::get_cur_datetime();
		
		$tl->insert_file($timeline_id,$tmp_file,$datetime,$sort_num);

		return self::move_file($src_dir, $src_file, $target_dir, $target_file);
	}

    /**
     * コミュニティレスポンスの画像ファイルを公開フォルダに移動する
     * INPUT : path / string / ファイル保存先パス
     *         file_name / string / ファイル名
     * OUTPUT: true / 成功時
     *         false / 失敗時
     * DESC  :
     * CREATE: 2017.09.20 aoyama
     *        複数画像に対応するためDB処理も追加
     */
    public function set_community_response_public($tmp_date, $tmp_file, $thread_id,$response_id,$sort_num=0) {

        $community = new CommunityModel();

        // フォルダの指定
        $src_dir = DIR_SYSTEM_IMG_TMP . DS . $tmp_date . DS;
        $src_file = $tmp_file;
        $target_dir = DIR_PUBLIC_IMG . DS . "community" . DS . $thread_id . DS;
        $target_file = $tmp_file;

        //DBへの登録処理
        $tl = new TimelineModel();

        $datetime = DbDateTime::get_cur_datetime();

        $community->add_community_response_file($response_id,$tmp_file,$datetime,$sort_num);

        return self::move_file($src_dir, $src_file, $target_dir, $target_file);
    }

	/*	 * **********************************
	 * NAME  : set_message_public
	 * INPUT : path / string / ファイル保存先パス
	 *         file_name / string / ファイル名
	 * OUTPUT: true / 成功時
	 *         false / 失敗時
	 * DESC  :
	 * 		tmpにあるタイムラインの添付ファイルを公開する
	 * NOTICE:
	 * CREATE: 2016.11.2 aoyama
	 * *********************************** */
	public function set_message_public($tmp_date, $tmp_file, $system_id) {

		$src_dir = DIR_SYSTEM_IMG_TMP . DS . $tmp_date . DS;
		$src_file = $tmp_file;
		$target_dir = DIR_PUBLIC_IMG . DS . "user" . DS . $system_id . DS;
		$target_file = $tmp_file;

		return self::move_file($src_dir, $src_file, $target_dir, $target_file);
	}

	/*	 * **********************************
	 * NAME  : set_response_public
	 * INPUT : path / string / ファイル保存先パス
	 *         file_name / string / ファイル名
	 * OUTPUT: true / 成功時
	 *         false / 失敗時
	 * DESC  :
	 * 		tmpにあるresponseの添付ファイルを公開する
	 * NOTICE:
	 * CREATE: 2016.10.21 aoyama
	 * *********************************** */
	public function set_response_public($tmp_date, $tmp_file, $thread_id) {

		$src_dir = DIR_SYSTEM_IMG_TMP . DS . $tmp_date . DS;
		$src_file = $tmp_file;
		$target_dir = DIR_PUBLIC_IMG . DS . "community" . DS . $thread_id . DS;
		$target_file = $tmp_file;

		return self::move_file($src_dir, $src_file, $target_dir, $target_file);
	}

	/*	 * **********************************
	 * NAME  : set_thread_avatar_public
	 * INPUT : path / string / ファイル保存先パス
	 *         file_name / string / ファイル名
	 * OUTPUT: true / 成功時
	 *         false / 失敗時
	 * DESC  :
	 * 		tmpにあるthreadのavatarファイルを公開する
	 * NOTICE:
	 * CREATE: 2016.10.21 aoyama
	 * *********************************** */
	public function set_thread_avatar_public($tmp_date, $tmp_file, $thread_id) {

		$src_dir = DIR_SYSTEM_IMG_TMP . DS . $tmp_date . DS;
		$src_file = $tmp_file;
		$target_dir = DIR_PUBLIC_IMG . DS . "community" . DS . $thread_id . DS;
		$target_file = $tmp_file;

		return self::move_file($src_dir, $src_file, $target_dir, $target_file);
	}

    /*	 * **********************************
     * NAME  : set_thread_bg_public
     * INPUT : path / string / ファイル保存先パス
     *         file_name / string / ファイル名
     * OUTPUT: true / 成功時
     *         false / 失敗時
     * DESC  :
     * 		tmpにあるthreadのavatarファイルを公開する
     *      既存ファイルを削除する
     * NOTICE:
     * CREATE: 2017.08.12 aoyama
     * *********************************** */
    public function set_thread_bg_public($tmp_date, $tmp_file, $thread_id) {

        $src_dir = DIR_SYSTEM_IMG_TMP . DS . $tmp_date . DS;
        $src_file = $tmp_file;
        $target_dir = DIR_PUBLIC_IMG . DS . "community" . DS . $thread_id . DS;
        $target_file = $tmp_file;

        return self::move_file($src_dir, $src_file, $target_dir, $target_file);
    }

	/*	 * **********************************
	 * NAME  : set_user_avatar_public
	 * INPUT : path / string / ファイル保存先パス
	 *         file_name / string / ファイル名
	 * OUTPUT: true / 成功時
	 *         false / 失敗時
	 * DESC  :
	 * 		tmpにあるユーザーのavatarファイルを公開する
	 * NOTICE:
	 * CREATE: 2016.10.21 aoyama
	 * *********************************** */
	public function set_user_avatar_public($tmp_date, $tmp_file, $system_user) {

		$src_dir = DIR_SYSTEM_IMG_TMP . DS . $tmp_date . DS;
		$src_file = $tmp_file;
		$target_dir = DIR_PUBLIC_IMG . DS . "user" . DS . $system_user . DS;
		$target_file = "avatar.jpg";

		return self::move_file($src_dir, $src_file, $target_dir, $target_file);
	}

	/*	 * **********************************
	 * NAME  : move_file
	 * INPUT : path / string / ファイル保存先パス
	 *         file_name / string / ファイル名
	 * OUTPUT: true / 成功時
	 *         false / 失敗時
	 * DESC  :
	 *  画像を移動するメソッド
	 * move_tmp_publicからリプレイス
	 * NOTICE:
	 * CREATE: 2016.10.21 aoyama
	 * *********************************** */
	public function move_file($tmp_dir, $tmp_file, $public_dir, $public_file) {

		StaticFunction::create_dir($public_dir);
		$ret = rename($tmp_dir . $tmp_file, $public_dir . $public_file);
		chmod($public_dir . $public_file, 0666);

		if (!$ret) {
			LOGS_ERR($tmp_dir . $tmp_file);
			LOGS_ERR($public_dir . $public_file);
		}
//		unlink($tmp_dir.$tmp_file);
		return true;
	}

	/*	 * **********************************
	 * NAME  : move_tmp_public
	 * INPUT : path / string / ファイル保存先パス
	 *         file_name / string / ファイル名
	 * OUTPUT: true / 成功時
	 *         false / 失敗時
	 * DESC  :
	 *  ロードしたファイルを指定保存先にJPEGで保存する
	 * いずれ廃止する。（2016.10.21）
	 * NOTICE:
	 * CREATE: 2016.10.19 aoyama
	 * *********************************** */
	public function move_tmp_public($tmp_dir, $tmp_file, $public_dir, $public_file) {

		StaticFunction::create_dir($public_dir);
		$ret = rename($tmp_dir . $tmp_file, $public_dir . $public_file);
		if (!$ret) {
			LOGS_ERR($tmp_dir . $tmp_file);
			LOGS_ERR($public_dir . $public_file);
		}
//		unlink($tmp_dir.$tmp_file);
		return true;
	}

	/*	 * **********************************
	 * NAME  : get_review_url
	 * INPUT : $review_id / string / レビューID
	 * OUTPUT:
	 * 		string
	 * DESC  :
	 * 		レスポンスの添付ファイルのURLを返す
	 * NOTICE:
	 * CREATE: 2016.10.31 aoyama
	 * *********************************** */
	public function get_review_url($review_id, $file_name) {
		return (StaticFunction::is_empty($file_name)) ? null : CONF::read('URL_PUBLIC_ROOT') . "images/review/" . $review_id . "/" . $file_name;
	}

	/*	 * **********************************
	 * NAME  : get_message_url
	 * INPUT : $system_id / string / ユーザーのsystem_id
	 * OUTPUT:
	 * 		string
	 * DESC  :
	 * 		メッセージの添付ファイルのURLを返す
	 * NOTICE:
	 * CREATE: 2016.11.2 aoyama
	 * *********************************** */
	public function get_message_url($system_id, $file_name) {
		return (StaticFunction::is_empty($file_name)) ? null : CONF::read('URL_PUBLIC_ROOT') . "images/user/" . $system_id . "/" . $file_name;
	}

	/*	 * **********************************
	 * NAME  : get_timeline_url
	 * INPUT : $system_id / string / ユーザーのsystem_id
	 * OUTPUT:
	 * 		string
	 * DESC  :
	 * 		レスポンスの添付ファイルのURLを返す
	 * NOTICE:
	 * CREATE: 2016.10.21 aoyama
	 * UPDATE: 2017.2.13 aoyama
	 * 		画像ディレクトリからファイル名を配列にして返す方式に変更
	 *		その後、DB格納方式にしたので下記メソッドは廃止
	 * *********************************** */
	public function get_timeline_url($system_id, $timeline_id) {
		
		/*
		$file_url = array();

		$thread_dir = DIR_PUBLIC_IMG . DS . "user" . DS . $system_id . DS . $timeline_id;
		if (file_exists($thread_dir)) {
			if (is_dir($thread_dir) && $handle = opendir($thread_dir)) {
				//ファイルリストを取得
				while (($file = readdir($handle)) !== false) {
					if (filetype($path = $thread_dir . DS . $file) == "file") {
						$file_url[] = CONF::read('URL_PUBLIC_ROOT') . "images/user/" . $system_id . "/" . $timeline_id . "/" . $file;
					}
				}
			}
		}
		
		return $file_url;
		 * 
		 */
	}

	/*	 * **********************************
	 * NAME  : get_response_url
	 * INPUT : $system_id / string / ユーザーのsystem_id
	 * OUTPUT:
	 * 		string
	 * DESC  :
	 * 		レスポンスの添付ファイルのURLを返す
	 * NOTICE:
	 * CREATE: 2016.10.21 aoyama
	 * *********************************** */
	public function get_response_url($thread_id, $file_name) {
		return (StaticFunction::is_empty($file_name)) ? null : CONF::read('URL_PUBLIC_ROOT') . "images/community/" . $thread_id . "/" . $file_name;
	}

	/*	 * **********************************
	 * NAME  : get_avatar_url
	 * INPUT : $system_id / string / ユーザーのsystem_id
	 * OUTPUT:
	 * 		string
	 * DESC  :
	 * 		ユーザーアバターファイルのURLを返す
	 * NOTICE:
	 * CREATE: 2016.10.19 aoyama
	 * UPDATE: 2016.11.1  aoyama
	 * 		アバターの存在が事前に判明する場合は
	 * 		image_existsを経由しないように。
	 * *********************************** */
	public function get_avatar_url($system_id, $status = false) {

		if ($status) {
			return CONF::read('URL_PUBLIC_ROOT') . "images/user/" . $system_id . "/avatar.jpg";
		}

		if (!$this->image_exists(DIR_PUBLIC_IMG . DS . "user" . DS . $system_id . DS, "avatar.jpg") || !InputVali::is_system_id($system_id)) {
			$avatar = CONF::read('AVATAR.DUMMY_FILE');
		} else {
			$avatar = CONF::read('URL_PUBLIC_ROOT') . "images/user/" . $system_id . "/avatar.jpg";
		}
		return $avatar;
	}

	/*	 * **********************************
	 * NAME  : get_avatar_thread_url
	 * INPUT : $system_id / string / ユーザーのsystem_id
	 * OUTPUT:
	 * 		string
	 * DESC  :
	 * 		コミュニティアバターファイルのURLを返す
	 * NOTICE:
	 * CREATE: 2016.10.19 aoyama
	 * *********************************** */
	public function get_avatar_thread_url($thread_id, $file_name) {
		if (StaticFunction::is_empty($file_name)) {
			$avatar = CONF::read("AVATAR.DUMMY_THREAD");
		} else {
			$avatar = CONF::read('URL_PUBLIC_ROOT') . "/images/community/" . $thread_id . "/" . $file_name;
		}
		return $avatar;
	}

	/*	 * **********************************
	 * NAME  : file_exists
	 * INPUT : path / string / ファイル保存先パス
	 *         file_name / string / ファイル名
	 * OUTPUT: true / 成功時
	 *         false / 失敗時
	 * DESC  :
	 *  ファイルの存在確認
	 * NOTICE:
	 * CREATE: 2016.10.19 aoyama
	 * *********************************** */
	public function image_exists($public_dir, $public_file) {

		if (@file_exists($public_dir . $public_file)) {
			return true;
		} else {
			return false;
		}
	}

	/*	 * **********************************
	 * NAME  : clear
	 * INPUT : NONE
	 * OUTPUT: NONE
	 * DESC  :
	 *  セットされたメンバをクリアする
	 * NOTICE:
	 * CREATE: 2015.11.14 hesaka
	 * *********************************** */
	public function clear() {
		$this->img_info = NULL;
		$this->ext = NULL;
		$this->image_data = NULL;
		$this->function = NULL;
		$this->create_image_data = NULL;
	}

	/*	 * **********************************
	 * NAME  : get_external_image
	 * INPUT : NONE
	 * OUTPUT: NONE
	 * DESC  :
	 *  外部ファイルを取得し変換
	 * NOTICE:
	 * CREATE: 2016.11.6 aoyama
	 * UPDATE: 2016.11.29 aoyama
	 * 		フレームワークから分離したので削除
	 * *********************************** */
	public function get_external_image($url, $header = true) {
		
	}

}
