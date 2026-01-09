<?php

/* * **********************************
 * NAME:MypageLoginFirstController
 * DESC:
 *  マイページ用のコントローラ(クローズエリア)
 * 
 *  コントローラの継承
 *  MypageLoginFirstController
 *  ↓
 *  MypageBaseCommonControllerFrame
 *  ↓
 *  ControllerCore
 *  となる
 * 
 * NOTICE:
 * CREATE: 2016.10.14 aoyama
 * *********************************** */
class MypageLoginFirstController extends MypageBaseCommonControllerFrame {

	private $sGroup;
	private $public_user_data;
	private $fashionMasterArray;

	/* Constructor */
	public function __construct() {

		parent::__construct();

		/*
		 * すでに初回ログインを済ませている場合はmypageにリダイレクト
		 */
		if (!StaticFunction::is_empty(SESSION::read(CONF::read('LOGIN_CATEGORY.PUBLIC') . ".user_id"))) {
			$this->redirect(CONF::read('URL_PUBLIC_ROOT') . 'mypage');
		}


		$this->sGroup = 'login_first';
		//セッションからユーザ情報を取得
		$this->public_user_data = SESSION::read(CONF::read('LOGIN_CATEGORY.PUBLIC'));

		//ファッション系統の配列を取得してvuewに渡す
		$fashionMaster = new FashionTypeMasterModel();
		$this->fashionMasterArray = $fashionMaster->get_basic_data();
		$this->set("fashionTypeArray", $this->fashionMasterArray);
	}

	/*	 * **********************************
	 * NAME  : index
	 * INPUT : 
	 * OUTPUT: 
	 * DESC  : 
	 * 		登録フォーム
	 * 		セッションにセットするのはここだけ。
	 * 		同時にバリデーションチェックも実施
	 * NOTICE:
	 * CREATE: 2016.10.14 aoyama
	 * *********************************** */
	public function index() {

		// POSTデータがある場合、セッションに登録する。
		if (!StaticFunction::is_empty(REQUEST::post_data())) {

			SESSION::write($this->sGroup . '.nickname', REQUEST::post_data('nickname'));
			SESSION::write($this->sGroup . '.fashion_id', REQUEST::post_data('fashion_id'));
			SESSION::write($this->sGroup . '.like_brand', REQUEST::post_data('like_brand'));
			SESSION::write($this->sGroup . '.comment', REQUEST::post_data('comment'));
			SESSION::write($this->sGroup . '.file',true);

			//アバター登録がある場合
			if ($_FILES['avatar']['error'] == UPLOAD_ERR_OK) {

				$thumb = new Image();

				//一時画像ファイル名を生成
				$avatar_tmp_hash = Encrypt::member_regist_token($_SERVER['REMOTE_ADDR'], time());

				//ロード
				if (!$ret = $thumb->load($_FILES['avatar']['tmp_name'])) {
					SESSION::write($this->sGroup . '.file',false);
				}
				else {
				//拡張子取得
					$thumb_ext = $thumb->get_image_type();

					//リサイズ
					$thumb->resize_avatar(CONF::read("AVATAR.WIDTH"));

					//ファイル名
					$date_dir = DbDateTime::fairing_digit_8(DbDateTime::get_cur_datetime());
					$tmp_file_name = $avatar_tmp_hash . '.jpg';

					//tmp保存先システムディレクトリ[/public/images/tmp/日付]
					$avatar_tmp_dir = DIR_SYSTEM_IMG_TMP . DS . $date_dir . DS;

					//tmpディレクトリに保存
					$ret = $thumb->save_jpeg($avatar_tmp_dir, $tmp_file_name);

					SESSION::write($this->sGroup . '.tmp_avatar', $tmp_file_name);
					SESSION::write($this->sGroup . '.tmp_avatar_date', $date_dir);
				}
			}

			$error_array = $this->checkSessionParameter();

			if (StaticFunction::is_empty($error_array)) {
				//問題なければ確認画面へ
				$this->redirect("./confirm.html");
			}
			
			$this->set('error_array', $error_array);
			$this->formReturn();
		}
		
		//正常終了時はセッションを削除
		SESSION::delete($this->sGroup);
	}

	/*	 * **********************************
	 * NAME  : confirm
	 * INPUT : 
	 * OUTPUT: 
	 * DESC  : 
	 *  入力確認画面用
	 *  セッションがあればとりあえず表示する
	 *  ここではバリデーション無し
	 * NOTICE:
	 * CREATE: 2016.10.14 aoyama
	 * *********************************** */
	public function confirm() {
		// POSTデータがないので「戻るボタン」の可能性。setしそのまま表示
		$this->formReturn();
	}

	/*	 * **********************************
	 * NAME  : complete
	 * INPUT : 
	 * OUTPUT: 
	 * DESC  : 
	 *  入力完了画面用
	 *  APIで情報を送信
	 * NOTICE:
	 *  API送信処理あり（セッションバリデーション含む）
	 * CREATE: 2016.10.14 aoyama
	 * *********************************** */
	public function complete() {

		if (StaticFunction::is_empty(SESSION::read($this->sGroup))) {
			$this->redirect("./");
		}

		$error_array = $this->checkSessionParameter();
		if (!StaticFunction::is_empty($error_array)) {
			$this->redirect("./");
		}

		//system_idハッシュ生成
		$datetime = DbDateTime::get_cur_datetime();
		$token = Encrypt::member_regist_token(SESSION::read(CONF::read('LOGIN_CATEGORY.PUBLIC') . '.system_user_id'), $datetime);

		// 配列にPOSTデータを格納
		$param_array = array(
			"system_id" => DbCast::string($token),
			"system_user_id" => DbCast::string(SESSION::read(CONF::read('LOGIN_CATEGORY.PUBLIC') . '.system_user_id')),
			"nickname" => DbCast::string(SESSION::read($this->sGroup . '.nickname')),
			'fashion_id' => DbCast::integer(SESSION::read($this->sGroup . '.fashion_id')),
			"like_brand" => DbCast::string(SESSION::read($this->sGroup . '.like_brand')),
			"comment" => DbCast::string(SESSION::read($this->sGroup . '.comment')),
			'update_time' => DbCast::datetime($datetime),
			'create_time' => DbCast::datetime($datetime),
			"active" => DbCast::float(DB_ACTIVE_ON)
		);

		$usermember = new UserPublicModel();
		/* API通信エラー */
		if (!$user_id = $usermember->regist($param_array)) {
			$error_array[] = array("message" => "初回ログイン登録に失敗しました。お手数をおかけしますが時間をおいて再度登録してください。");
			$this->set('error_array', $error_array);
			return;
		}

		//成功したのでセッションにも同様の情報を登録する
		SESSION::write(CONF::read('LOGIN_CATEGORY.PUBLIC') . '.user_id', $user_id);
		SESSION::write(CONF::read('LOGIN_CATEGORY.PUBLIC') . '.system_id', $token);
		SESSION::write(CONF::read('LOGIN_CATEGORY.PUBLIC') . '.nickname', SESSION::read($this->sGroup . '.nickname'));
		SESSION::write(CONF::read('LOGIN_CATEGORY.PUBLIC') . '.fashion_id', SESSION::read($this->sGroup . '.fashion_id'));
		SESSION::write(CONF::read('LOGIN_CATEGORY.PUBLIC') . '.like_brand', SESSION::read($this->sGroup . '.like_brand'));
		SESSION::write(CONF::read('LOGIN_CATEGORY.PUBLIC') . '.comment', SESSION::read($this->sGroup . '.comment'));

		//アバター画像がある場合は画像をユーザーディレクトリに移動
		if (!StaticFunction::is_empty(SESSION::read($this->sGroup . '.tmp_avatar'))) {

			$img = new Image();
			$ret = $img->set_user_avatar_public(SESSION::read($this->sGroup . '.tmp_avatar_date'), SESSION::read($this->sGroup . '.tmp_avatar'), $token);

			if (!$ret) {
				LOGS_ERR("SNS登録時の画像登録エラー：");
			}
		}

		/*
		 * ハッピーさんアカウント「CONF::read("MASTER_USER.USER_ID")」は必須なのでここで登録（相互フォロー）
		 * フォローステータスはDBのCONFを読み込む「ShopConfig.inc」
		 */
		$match = new UserMatchModel();
		$match->set($user_id, CONF::read("MASTER_USER.USER_ID"), DB_FOLLOW_STATUS_ON);
		$match->set_friend_count($user_id);
		$match->set_friend_count(CONF::read("MASTER_USER.USER_ID"));

		//正常終了時はセッションを削除
		SESSION::delete($this->sGroup);

		//マイページへリダイレクト
		$this->redirect(CONF::read('URL_PUBLIC_ROOT') . 'mypage');
	}

	/*	 * **********************************
	 * NAME:checkSessionParameter
	 * DESC:
	 *  メルマガ登録専用のセッション情報バリデーション
	 * NOTICE:
	 * CREATE: 2016.10.14 aoyama
	 * *********************************** */
	private function checkSessionParameter() {

		$error_array = array();

		if (!SESSION::read($this->sGroup . '.file')) {
			$error_array[] = array('target' => 'file', 'message' => '添付できるファイルは画像のみです。');
		}

		if (!InputVali::is_nickname(SESSION::read($this->sGroup . '.nickname'))) {
			$error_array[] = array('target' => 'nickname', 'message' => 'ニックネームを入力してください');
		}
		if (SESSION::read($this->sGroup . '.nickname') == CONF::read("MASTER_USER.NICKNAME")) {
			$error_array[] = array('target' => 'nickname', 'message' => 'ニックネームに「' . CONF::read("MASTER_USER.NICKNAME") . '」を設定することはできません');
		}

		if (!StaticFunction::is_empty(SESSION::read($this->sGroup . '.fashion_id'))) {
			if (!array_key_exists(SESSION::read($this->sGroup . '.fashion_id'), $this->fashionMasterArray)) {
				$error_array[] = array('target' => 'zip', 'message' => 'ファッション系統は選択肢から選んでください。');
			}
		}

		if (!StaticFunction::is_empty(SESSION::read($this->sGroup . '.like_brand'))) {
			if (!InputVali::is_brand_name(SESSION::read($this->sGroup . '.like_brand'))) {
				$error_array[] = array('target' => 'like_brand', 'message' => '好きなブランド名は20文字以内で入力してください。');
			}
		}

		if (!StaticFunction::is_empty(SESSION::read($this->sGroup . '.comment'))) {
			if (!InputVali::is_prof_comment(SESSION::read($this->sGroup . '.comment'))) {
				$error_array[] = array('target' => 'comment', 'message' => '自己紹介はは200文字以内で入力してください。');
			}
		}
		return $error_array;
	}

	/*	 * **********************************
	 * NAME:formReturn
	 * DESC:
	 *  セッション情報をフォームに渡すためにセットする機能
	 * NOTICE:
	 * CREATE: 2016.10.14 aoyama
	 * *********************************** */
	private function formReturn() {

		// セッションの情報をセットしてviewに渡す
		if (!StaticFunction::is_empty(SESSION::read($this->sGroup))) {
			$this->set("nickname", SESSION::read($this->sGroup . '.nickname'));
			$this->set("fashion_id", SESSION::read($this->sGroup . '.fashion_id'));
			if (!StaticFunction::is_empty(SESSION::read($this->sGroup . '.fashion_id'))) {
				$this->set("fashion_id_view", $this->fashionMasterArray[SESSION::read($this->sGroup . '.fashion_id')]);
			}
			$this->set("like_brand", SESSION::read($this->sGroup . '.like_brand'));
			$this->set("comment", SESSION::read($this->sGroup . '.comment'));
			$this->set("tmp_avatar", SESSION::read($this->sGroup . '.tmp_avatar'));
			$this->set("tmp_avatar_date", SESSION::read($this->sGroup . '.tmp_avatar_date'));
		}
	}

}
