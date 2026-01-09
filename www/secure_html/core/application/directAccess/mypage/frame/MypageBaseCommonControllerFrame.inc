<?php

/* * **********************************
 * NAME: MypageBaseCommonControllerFrame
 * DESC:
 * NOTICE:
 * CREATE: 2016.10.13 aoyama
 * *********************************** */
class MypageBaseCommonControllerFrame extends ControllerCore {

	private $public_user_data;

	/*	 * **********************************
	 * NAME  : __construct
	 * INPUT : NONE
	 * OUTPUT: NONE
	 * DESC  :
	 *  マイページ画面の共通部分に用いる
	 *  フレームのコンストラクタ
	 *  下記内容を処理する
	 *  
	 *  ・コアの起動
	 *  ・セッションスタート
	 *  ・各種認証(verification)など
	 *  ・viewの統一化
	 * NOTICE:
	 * --------------------------------------
	 *  当該フレーム定義に必要な認証は
	 *  コントローラではなくここで行う
	 * --------------------------------------
	 * CREATE: 2016.10.13 aoyama
	 * UPDATE: 2016.12.5 aoayma
	 * 		SNS未登録と共通画面の時でも情報表示したいので
	 * 		「MypageCloseCommonControllerFrame」から移植
	 * *********************************** */
	public function __construct() {

		if (CONF::read('DEBUG_BAR.IS_ACTIVE'))
			DebugBarMaster::start_measure('controller_constructor', '【FRAME_CONSTRUCTOR】');

		/*
		 * セッション スタート
		 */
		SESSION::start();

		//子クラス名をControllerCoreに渡す
		parent::__construct(get_class($this));

		/*
		 * 強制リダイレクトチェック
		 */
		if (CONF::read('FORCE_REDIRECT.IS_ACTIVE') === true) {
			$fr = new ForceRedirect();
			if (!$fr->verification()) {
				$this->redirect(CONF::read('FORCE_REDIRECT.DESTINATION'));
			}
		}

		/*
		 * メンテナンスチェック
		 * ※PUBLIC側のみの判断となる
		 */
		if (CONF::read('DB_SERVICE_MASTER.IS_MAINTENANCE') === true) {
			/*
			 * 許可されたIP以外はメンテナンス画面へ
			 */
			$irc = new IpAddressRestrict();
			if (!$irc->verification()) {
				$this->redirect(CONF::read('MAINTENANCE.URL'));
			}
		}

		/*
		 * ドメインリダイレクトチェック
		 */
		if (CONF::read('DOMAIN_REDIRECT.IS_ACTIVE') === true) {
			$fr = new DomainRedirect();
			$url = $fr->verification();
			if ($url !== true) {
				LOGS_ENV('DOMAIN REDIRECT!!! env=' . ENV_DIR_NAME);
				$this->redirect($url);
			}
		}

		/*
		 * http,httpsリダイレクト
		 * ※どちらにリダイレクトするかはCONFIG設定による
		 */
		if (CONF::read('SSL_REDIRECT.IS_ACTIVE') === true) {
			$irc = new SslRedirect();
			$schema = $irc->verification();
			//指定外ポートの場合はリダイレクト
			if ($schema !== true) {
				$this->redirect($schema . '://' . URL_HOST . URL_REQUEST);
			}
		}

		/*
		 * ベーシック認証
		 */
		if (CONF::read('BASIC_AUTH.IS_ACTIVE')) {
			$ba = new BasicAuth();
			/*
			 * 認証を行っていない、もしくは失敗した場合は認証ダイアログを表示する
			 * ※ダイアログを表示する場合はverification()の中でexit()をする
			 * 　成功した場合はtrueが返ってくるが、何も行わないためリターン値のチェックを行う必要が無い
			 */
			$ba->verification();
		}

		/*
		 * ログイン認証
		 */
		if (CONF::read('LOGIN.IS_ACTIVE') === true) {
			$login = new Login();
			//対象となるターゲットユーザモデルを指定
			$login->set_target_model(CONF::read('LOGIN_CATEGORY.PUBLIC'));

			//ログイン中かセッションにある値で認証
			if (!$login->is_login()) {

				//ログインページへリダイレクト
				$this->redirect(CONF::read('URL_PUBLIC_ROOT') . '/login?callback=' . urlencode(URL_FULL));
			}

			/*
			 * セッションからユーザ情報を取得しガジェット用にセット
			 * UPDATE. 2016.10.24 aoyama
			 * UPDATE: 2016.12.5 aoayma
			 * 		SNS未登録と共通画面の時でも情報表示したいので
			 * 		「MypageCloseCommonControllerFrame」から移植
			 */
			$image = new Image();
			$this->public_user_data = SESSION::read(CONF::read('LOGIN_CATEGORY.PUBLIC'));

			$this->set("g_name", StaticFunction::marge_name($this->public_user_data['name1'], $this->public_user_data['name2']));
			$this->set("g_suid", $this->public_user_data['system_user_id']);
			$this->set("g_point", StaticFunction::count_num_format($this->public_user_data['point']));
			$this->set("g_depo", StaticFunction::count_num_format($this->public_user_data['depo']));

			//SNS利用登録があるかをviewに送る
			$this->set("sns_entry", $this->is_sns_entry());
			
			//SNS利用登録がある場合は情報をviewに。
			if ($this->is_sns_entry()) {
				$this->set("g_nickname", $this->public_user_data['nickname']);
				$this->set("g_avatar", $image->get_avatar_url($this->public_user_data['system_id']));
				$this->set("g_comment", nl2br($this->public_user_data['comment']));

				/*
				 * 未読メッセージ件数のセット
				 * 2016.12.22 aoyama
				 *		未読件数取得メソッドを新設
				 */
				//$message = new MypageMessageModel();

				$message = new MypageMessageModel();
				$unlead_num = (int) $message->get_message_unlead_num(SESSION::read(CONF::read('LOGIN_CATEGORY.PUBLIC') . ".user_id"));
				SESSION::write(CONF::read('LOGIN_CATEGORY.PUBLIC') . ".message_count", $unlead_num);
				$this->set("count_unread", $unlead_num);
				
				/*
				 * フレンドリストを表示
				 * ここは完全にフレンド状態「complete」を絞り込む
				 * UPDATE: 2016.10.26 aoyama
				 */
				$friend = new UserMatchModel();
				$friendList = $friend->get_friend_list($this->public_user_data['user_id'], 0, 10, 'commit');

				$friendArray = array();
				if (!StaticFunction::is_empty($friendList)) {
					foreach ($friendList AS $value) {

						$friendArray[] = array(
							"nickname" => $value['nickname'],
							"system_id" => $value['system_id'],
							"avatar" => $image->get_avatar_url($value['system_id'])
						);
					}
				}
				$this->set("friendArray", $friendArray);


				/*
				 * 参加コミュニティリストを表示
				 */
				$community = new CommunityModel();
				$communityList = $community->get_thread_from_user($this->public_user_data['user_id'], 0, 10);

				$communityArray = array();
				if (!StaticFunction::is_empty($communityList)) {
					foreach ($communityList AS $value) {

						$communityArray[] = array(
							"thread_id" => $value['thread_id'],
							"thread_link" => "/community/detail.html?tid=" . $value['thread_id'],
							"community_name" => $value['community_name'],
							"community_detail" => $value['community_detail'],
							"category_name" => $value['category_name'],
							"avatar" => $image->get_avatar_thread_url($value['thread_id'], $value['image_file'])
						);
					}
				}
				$this->set("communityArray", $communityArray);
			}
		}
	}

	/*	 * **********************************
	 * NAME  : is_sns_entry
	 * INPUT : directory / string / viewのアクセス先ディレクトリ名
	 * OUTPUT: NONE
	 * DESC  :
	 * NOTICE:
	 * CREATE: 2016.11.5 aoyama
	 * *********************************** */
	public function is_sns_entry() {
		if (StaticFunction::is_empty(SESSION::read(CONF::read('LOGIN_CATEGORY.PUBLIC') . ".user_id"))) {
			return false;
		} else {
			return true;
		}
	}

	/*	 * **********************************
	 * NAME  : view
	 * INPUT : directory / string / viewのアクセス先ディレクトリ名
	 * OUTPUT: NONE
	 * DESC  :
	 * NOTICE:
	 * UPDATE: 2016.10.13 aoyama
	 * *********************************** */
	public function view($directory = 'index') {

		/*
		 * 画面共通セット
		 */
		//フッタの言語切り替えリストセット
//		$this->set('lang_list', CONF::read('MULTI_LANGUAGE'));

		if (CONF::read('DEBUG_BAR.IS_ACTIVE'))
			DebugBarMaster::start_measure('view', '【VIEW】');

		/*
		 * デバイスにより実行するViewを読み分ける
		 */
		switch (DEVICE_TYPE) {
			//PC ro タブレット or SP
			//今回はレスポンシブなのでデバイスによりディレクトリを分ける必要はない
			case DEVICE_TYPE_SP:
			case DEVICE_TYPE_PC:
			case DEVICE_TYPE_TABLET:
			default:
				LOGS_DBG_LV1('--- GO TO VIEW (PUBLIC' . ':' . $directory . ') ---');

//				echo (DIR_VIEW . DS . $directory . DS . FILENAME);
//				exit;
				include_once DIR_VIEW . DS . $directory . DS . FILENAME;
//				include_once DIR_VIEW . DS . DIR_NAME_MYPAGE . DS . $directory . DS . FILENAME;
				break;
		}

		//stop_measure()は、html周りを出力する際にレンダリングしているので、使用するとエラーとなるので実行しない
	}

}

?>
