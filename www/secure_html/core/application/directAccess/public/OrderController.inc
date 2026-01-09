<?php

/* * **********************************
 * NAME:OrderController
 * DESC:
 * 		注文ページのコントローラー
 * NOTICE:
 * CREATE: 2016.10.18 aoyama
 * UPDATE: 2016.11.17 aoyama
 *		POST方式を変更
 * *********************************** */

class OrderController extends PublicOpenControllerFrame
{

    private $sGroup;

    /* Constructor */
    public function __construct()
    {
        parent::__construct();
        $this->sGroup = 'order';
        $this->sSpecial = 'special';
        $this->sComm = 'comm';

        $this->set("page_group", "order");

        //セッションからユーザ情報を取得
		$this->public_user_data = SESSION::read(CONF::read('LOGIN_CATEGORY.PUBLIC'));
    }

    /*	 * **********************************
     * NAME  : index
     * INPUT :
     * OUTPUT:
     * DESC  :
     * 		利用規約を表示するだけなので何もしない
     * NOTICE:
     * CREATE: 2016.10.18 aoyama
     * UPDATE: 2016.11.14 aoyama
     *		友達紹介のパターンを追加
     * UPDATE: 2016.12.13 aoyama
     *		sale経由のパターンを追加
     * *********************************** */
    public function index()
    {
        /* 友達紹介 */
        if (REQUEST::get_data('special') == CONF::read('REFER_FRIEND.PARAM')) {
            SESSION::write($this->sSpecial . '.mode', CONF::read('REFER_FRIEND.PARAM'));
        } /* sale経由 */
        else {
            if (REQUEST::get_data('special') == CONF::read('REFER_SALE.PARAM')) {
                SESSION::write($this->sSpecial . '.mode', CONF::read('REFER_SALE.PARAM'));
            } /* それ以外ならセッションをクリア */
            else {
                SESSION::delete($this->sSpecial);
            }

            if (REQUEST::get_data('special')) {
                SESSION::write($this->sComm . '.comm', REQUEST::get_data('special'));
            }
        }
    }

    /*	 * **********************************
     * NAME  : form
     * INPUT :
     * OUTPUT:
     * DESC  :
     * 		登録フォーム
     * 		セッションにセットするのはここだけ。
     * 		同時にバリデーションチェックも実施
     * NOTICE:
     * CREATE: 2016.10.18 aoyama
     * UPDATE: 2017.4.3 aoyama
     *      直接フォームページにアクセスさせるためindex()に置いていた
     *      sale格納処理をform()へ移動させる。
     * IPDATE: 2017.05.24 aoyama
     * 		23時以降の申し込みの場合は集荷日を翌々日以降にする
     * 		siteConfig.phpも調整　Conf::read("MASTER_SHOP.PICKUP_TOO_LATE")
     * *********************************** */
    public function form()
    {

        /* 友達紹介 */
        if (REQUEST::get_data('special') == CONF::read('REFER_FRIEND.PARAM')) {
            SESSION::write($this->sSpecial . '.mode', CONF::read('REFER_FRIEND.PARAM'));
        } /* sale経由 */
        else {
            if (REQUEST::get_data('special') == CONF::read('REFER_SALE.PARAM')) {
                SESSION::write($this->sSpecial . '.mode', CONF::read('REFER_SALE.PARAM'));
            } /* それ以外ならセッションをクリア */
            else {
                SESSION::delete($this->sSpecial);
            }

            if (REQUEST::get_data('special')) {
                SESSION::write($this->sComm . '.comm', REQUEST::get_data('special'));
            }
        }

        //* ログイン中でログイン情報を配置
        $login = new Login();
        if ($login->is_login()) {

            $this->set("is_login", true);

            //もしもAPIからのTELが連結されていた場合は分割（aoyama）
            $telArray = StaticFunction::phone_to_array(SESSION::read(CONF::read('LOGIN_CATEGORY.PUBLIC') . '.tel'));

            $this->set("name1", SESSION::read(CONF::read('LOGIN_CATEGORY.PUBLIC') . '.name1'));
            $this->set("name2", SESSION::read(CONF::read('LOGIN_CATEGORY.PUBLIC') . '.name2'));
            $this->set("kana1", SESSION::read(CONF::read('LOGIN_CATEGORY.PUBLIC') . '.kana1'));
            $this->set("kana2", SESSION::read(CONF::read('LOGIN_CATEGORY.PUBLIC') . '.kana2'));
            $this->set("sex", SESSION::read(CONF::read('LOGIN_CATEGORY.PUBLIC') . '.sex'));
            $this->set("birth_y", SESSION::read(CONF::read('LOGIN_CATEGORY.PUBLIC') . '.birth_y'));
            $this->set("birth_m", SESSION::read(CONF::read('LOGIN_CATEGORY.PUBLIC') . '.birth_m'));
            $this->set("birth_d", SESSION::read(CONF::read('LOGIN_CATEGORY.PUBLIC') . '.birth_d'));
            $this->set("zip", SESSION::read(CONF::read('LOGIN_CATEGORY.PUBLIC') . '.zip'));
            $this->set("state", SESSION::read(CONF::read('LOGIN_CATEGORY.PUBLIC') . '.state'));
            $this->set("addr1", SESSION::read(CONF::read('LOGIN_CATEGORY.PUBLIC') . '.addr1'));
            $this->set("addr2", SESSION::read(CONF::read('LOGIN_CATEGORY.PUBLIC') . '.addr2'));
            $this->set("addr3", SESSION::read(CONF::read('LOGIN_CATEGORY.PUBLIC') . '.addr3'));
            $this->set("telephone", StaticFunction::convert_zen_to_han_num($telArray[0]));
            $this->set("telephone2", StaticFunction::convert_zen_to_han_num($telArray[1]));
            $this->set("telephone3", StaticFunction::convert_zen_to_han_num($telArray[2]));
            $this->set("email", SESSION::read(CONF::read('LOGIN_CATEGORY.PUBLIC') . '.email'));
            $this->set("email2", SESSION::read(CONF::read('LOGIN_CATEGORY.PUBLIC') . '.email2'));
            $this->set("wkbn", SESSION::read(CONF::read('LOGIN_CATEGORY.PUBLIC') . '.wkbn'));
        }
        $this->set("kutisu", 1);

        if (!StaticFunction::is_empty(SESSION::read($this->sGroup . '.error_array'))) {
            $this->set("error_array", SESSION::read($this->sGroup . '.error_array'));
            SESSION::delete($this->sGroup . '.error_array');
        }

        //初期状態をセット
        $this->set("cat1_selected", 'checked');
        $this->set("mag1_selected", 'checked');
        $this->set("kep1_selected", 'checked');
        $this->set("time", array());

        //配送業を選択
        $carrier_array = CONF::read('SHIPPING_TRADER');
        $this->set("carrier", "2");

        //集荷希望日は明日以降をセット 21時以降の申し込みは翌々日
        $delay = ((int)date("Hi") >= Conf::read("MASTER_SHOP.PICKUP_TOO_LATE_TIME")) ? Conf::read("MASTER_SHOP.PICKUP_TOO_LATE") : Conf::read("MASTER_SHOP.PICKUP_LATE");
        $date_src = DbDateTime::get_date_type_slash(DbDateTime::get_datetime_change(DbDateTime::get_cur_datetime(),
            $delay));
        $date = explode("/", $date_src);

        $this->set("taking_y", $date[0]);
        $this->set("taking_m", $date[1]);
        $this->set("taking_d", $date[2]);

        $min_date = date("Y/m/d", strtotime($delay));
        $this->set("min_taking_date", $min_date);

        $max_date = date("Y/m/d", strtotime("+1 month"));
        $this->set("max_taking_date", $max_date);

        $this->set("delay", $delay);

        $this->formReturn();
        //リターンしたのでセッションは消す。
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
    public function confirm()
    {  
        // POSTデータがある場合、セッションに登録する。
        if (!StaticFunction::is_empty(REQUEST::post_data())) {
            SESSION::write($this->sGroup . '.name1', REQUEST::post_data('name1'));
            SESSION::write($this->sGroup . '.name2', REQUEST::post_data('name2'));
            SESSION::write($this->sGroup . '.kana1', REQUEST::post_data('kana1'));
            SESSION::write($this->sGroup . '.kana2', REQUEST::post_data('kana2'));
            SESSION::write($this->sGroup . '.sex', REQUEST::post_data('sex'));
            SESSION::write($this->sGroup . '.birth_y', REQUEST::post_data('birth_y'));
            SESSION::write($this->sGroup . '.birth_m', REQUEST::post_data('birth_m'));
            SESSION::write($this->sGroup . '.birth_d', REQUEST::post_data('birth_d'));
            SESSION::write($this->sGroup . '.zip', REQUEST::post_data('zip'));
            SESSION::write($this->sGroup . '.state', REQUEST::post_data('state'));
            SESSION::write($this->sGroup . '.addr1', REQUEST::post_data('addr1'));
            SESSION::write($this->sGroup . '.addr2', REQUEST::post_data('addr2'));
            SESSION::write($this->sGroup . '.addr3', REQUEST::post_data('addr3'));
            SESSION::write($this->sGroup . '.telephone',
                StaticFunction::convert_zen_to_han_num(REQUEST::post_data('telephone')));
            SESSION::write($this->sGroup . '.telephone2',
                StaticFunction::convert_zen_to_han_num(REQUEST::post_data('telephone2')));
            SESSION::write($this->sGroup . '.telephone3',
                StaticFunction::convert_zen_to_han_num(REQUEST::post_data('telephone3')));
            SESSION::write($this->sGroup . '.faxnum',
                StaticFunction::convert_zen_to_han_num(REQUEST::post_data('faxnum')));
            SESSION::write($this->sGroup . '.faxnum2',
                StaticFunction::convert_zen_to_han_num(REQUEST::post_data('faxnum2')));
            SESSION::write($this->sGroup . '.faxnum3',
                StaticFunction::convert_zen_to_han_num(REQUEST::post_data('faxnum3')));
            SESSION::write($this->sGroup . '.email', REQUEST::post_data('email'));
            SESSION::write($this->sGroup . '.email2', REQUEST::post_data('email2'));
            SESSION::write($this->sGroup . '.wkbn', REQUEST::post_data('wkbn'));

            SESSION::write($this->sGroup . '.s_name1', REQUEST::post_data('s_name1'));
            SESSION::write($this->sGroup . '.s_name2', REQUEST::post_data('s_name2'));
            SESSION::write($this->sGroup . '.s_kana1', REQUEST::post_data('s_kana1'));
            SESSION::write($this->sGroup . '.s_kana2', REQUEST::post_data('s_kana2'));
            SESSION::write($this->sGroup . '.s_zip',
                StaticFunction::convert_zen_to_han_num(REQUEST::post_data('s_zip')));
            SESSION::write($this->sGroup . '.s_state', REQUEST::post_data('s_state'));
            SESSION::write($this->sGroup . '.s_addr1', REQUEST::post_data('s_addr1'));
            SESSION::write($this->sGroup . '.s_addr2', REQUEST::post_data('s_addr2'));
            SESSION::write($this->sGroup . '.s_addr3', REQUEST::post_data('s_addr3'));
            SESSION::write($this->sGroup . '.s_telephone',
                StaticFunction::convert_zen_to_han_num(REQUEST::post_data('s_telephone')));
            SESSION::write($this->sGroup . '.s_telephone2',
                StaticFunction::convert_zen_to_han_num(REQUEST::post_data('s_telephone2')));
            SESSION::write($this->sGroup . '.s_telephone3',
                StaticFunction::convert_zen_to_han_num(REQUEST::post_data('s_telephone3')));

            $taking_date = REQUEST::post_data('taking_date');
            $taking_array = explode("/", $taking_date);
            SESSION::write($this->sGroup . '.taking_y', $taking_array[0]);
            SESSION::write($this->sGroup . '.taking_m', $taking_array[1]);
            SESSION::write($this->sGroup . '.taking_d', $taking_array[2]);
            /*
            SESSION::write($this->sGroup . '.taking_y', REQUEST::post_data('taking_y'));
            SESSION::write($this->sGroup . '.taking_m', REQUEST::post_data('taking_m'));
            SESSION::write($this->sGroup . '.taking_d', REQUEST::post_data('taking_d'));
            */

            SESSION::write($this->sGroup . '.carrier', REQUEST::post_data('carrier'));
            SESSION::write($this->sGroup . '.time', REQUEST::post_data('time'));
            SESSION::write($this->sGroup . '.kutisu', REQUEST::post_data('kutisu'));
            SESSION::write($this->sGroup . '.cat', REQUEST::post_data('cat'));
            SESSION::write($this->sGroup . '.mag', REQUEST::post_data('mag'));
            SESSION::write($this->sGroup . '.kep', REQUEST::post_data('kep'));

            /*
            SESSION::write($this->sGroup . '.cause', REQUEST::post_data('cause'));
            SESSION::write($this->sGroup . '.cause_t3', REQUEST::post_data('cause_t3'));
            SESSION::write($this->sGroup . '.cause_t1', REQUEST::post_data('cause_t1'));
            SESSION::write($this->sGroup . '.cause_t2', REQUEST::post_data('cause_t2'));
            */
            
            SESSION::write($this->sGroup . '.comm', REQUEST::post_data('comm'));

            /*
            *   Added by: Manjunathgouda
            *   Desc: Storing all cause session data 
            *   Date: 2022-02-10
            * ----------------------------  START --------------------------------------------------
            */
            SESSION::write($this->sGroup . '.netsearchcheck', REQUEST::post_data('netsearchcheck'));
            SESSION::write($this->sGroup . '.netsearchcomment', REQUEST::post_data('netsearchcomment'));
            SESSION::write($this->sGroup . '.webadvertisingcheck', REQUEST::post_data('webadvertisingcheck'));
            SESSION::write($this->sGroup . '.facebookcheck', REQUEST::post_data('facebookcheck'));
            SESSION::write($this->sGroup . '.instagramcheck', REQUEST::post_data('instagramcheck'));
            SESSION::write($this->sGroup . '.twittercheck', REQUEST::post_data('twittercheck'));
            SESSION::write($this->sGroup . '.youtubecheck', REQUEST::post_data('youtubecheck'));
            SESSION::write($this->sGroup . '.shopcheck', REQUEST::post_data('shopcheck'));
            SESSION::write($this->sGroup . '.acquaintanceintroductioncheck', REQUEST::post_data('acquaintanceintroductioncheck'));
            SESSION::write($this->sGroup . '.tvcheck', REQUEST::post_data('tvcheck'));
            SESSION::write($this->sGroup . '.tvcomment', REQUEST::post_data('tvcomment'));
            SESSION::write($this->sGroup . '.changeclothescheck', REQUEST::post_data('changeclothescheck'));
            SESSION::write($this->sGroup . '.salecheck', REQUEST::post_data('salecheck'));
            SESSION::write($this->sGroup . '.otherscheck', REQUEST::post_data('otherscheck'));
            SESSION::write($this->sGroup . '.otherscomment', REQUEST::post_data('otherscomment'));

            // --------------------------- END -----------------------------------------------------

            SESSION::write($this->sGroup . '.idpass', REQUEST::post_data('idpass'));

            // バリデーション
            $error_array = $this->checkSessionParameter();
             
        
            if (!StaticFunction::is_empty($error_array)) {
                SESSION::write($this->sGroup . '.error_array', $error_array);
                $this->redirect("/order/form.html");
            }

            $this->formReturn();
            return;

        }

        //POSTのないアクセスなのでindexへリダイレクト
        $this->redirect("/order/form.html");
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
    public function complete()
    {

        //セッションがないのでTOPへリダイレクト
        if (StaticFunction::is_empty(SESSION::read($this->sGroup))) {
            $this->redirect("/order/");
        }

        // バリデーション
        $error_array = $this->checkSessionParameter();
        if (!StaticFunction::is_empty($error_array)) {
            SESSION::write($this->sGroup . '.error_array', $error_array);
            $this->redirect("/order/form.html");
        }

        $user_id = "";
        if(isset($this->public_user_data['system_user_id'])){
			$user_id = $this->public_user_data['system_user_id'];
		}

        // オーダー内容をDBに保存
        // 登録情報の配列格納

        $carrier = SESSION::read($this->sGroup . '.carrier');
		if ($carrier == 0) { $carrier = 2; }

        $time_mail_text = "";
		foreach (SESSION::read($this->sGroup . '.time') AS $value) {
			$time_mail_text .= CONF::read('SHIPPING_TIMEZONE_ARRAY2.' . $carrier . '.' . (string) $value);
		}

		//友達紹介またはSALEページ経由ならメールのタイトルをセット
		$refer_friend_text = "";
		if (SESSION::read($this->sSpecial . '.mode') == CONF::read('REFER_FRIEND.PARAM')) {
			$refer_friend_text = "紹介キャンペーン ";
		}
		//友達紹介状態ならメールのタイトルをセット
		if (SESSION::read($this->sSpecial . '.mode') == CONF::read('REFER_SALE.PARAM')) {
			$refer_friend_text = "SALE ";
		}

        $user_array = array(
            "carrier" => CONF::read('SHIPPING_TRADER.' . $carrier),
            "taking_date" => SESSION::read($this->sGroup . '.taking_y') . "-" . SESSION::read($this->sGroup . '.taking_m') . "-" . SESSION::read($this->sGroup . '.taking_d'),
            "taking_time" => $time_mail_text,
            "name" => StaticFunction::marge_name(SESSION::read($this->sGroup . '.name1'),
                SESSION::read($this->sGroup . '.name2')),
            "kana" => StaticFunction::marge_name(SESSION::read($this->sGroup . '.kana1'),
                SESSION::read($this->sGroup . '.kana2')),
            "tel" => StaticFunction::marge_phone(SESSION::read($this->sGroup . '.telephone'),
                SESSION::read($this->sGroup . '.telephone2'), SESSION::read($this->sGroup . '.telephone3')),
            "fax" => StaticFunction::marge_phone(SESSION::read($this->sGroup . '.faxnum'), 
                SESSION::read($this->sGroup . '.faxnum2'), SESSION::read($this->sGroup . '.faxnum3')),
            "email" => SESSION::read($this->sGroup . '.email'),
            "email2" => SESSION::read($this->sGroup . '.email2'),
            "zip" => SESSION::read($this->sGroup . '.zip'),
            "state" => SESSION::read($this->sGroup . '.state'),
            "addr1" => SESSION::read($this->sGroup . '.addr1'),
            "addr2" => SESSION::read($this->sGroup . '.addr2'),
            "addr3" => SESSION::read($this->sGroup . '.addr3'),
            "pass" => SESSION::read($this->sGroup . '.idpass'),
            "birth" => StaticFunction::marge_birth(SESSION::read($this->sGroup . '.birth_y'),
                SESSION::read($this->sGroup . '.birth_m'), SESSION::read($this->sGroup . '.birth_d')),
            "sex" => SESSION::read($this->sGroup . '.sex'),
            "wkbn" => SESSION::read($this->sGroup . '.wkbn'),
            "netsearchcheck" => SESSION::read($this->sGroup . '.netsearchcheck'),
            "netsearchcomment" => SESSION::read($this->sGroup . '.netsearchcomment'),
            "webadvertisingcheck" => SESSION::read($this->sGroup . '.webadvertisingcheck'),
            "facebookcheck" => SESSION::read($this->sGroup . '.facebookcheck'),
            "instagramcheck" => SESSION::read($this->sGroup . '.instagramcheck'),
            "twittercheck" => SESSION::read($this->sGroup . '.twittercheck'),
            "youtubecheck" => SESSION::read($this->sGroup . '.youtubecheck'),
            "shopcheck" => SESSION::read($this->sGroup . '.shopcheck'),
            "acquaintanceintroductioncheck" => SESSION::read($this->sGroup . '.acquaintanceintroductioncheck'),
            "tvcheck" => SESSION::read($this->sGroup . '.tvcheck'),
            "tvcomment" => SESSION::read($this->sGroup . '.tvcomment'),
            "changeclothescheck" => SESSION::read($this->sGroup . '.changeclothescheck'),
            "salecheck" => SESSION::read($this->sGroup . '.salecheck'),
            "otherscheck" => SESSION::read($this->sGroup . '.otherscheck'),
            "otherscomment" => SESSION::read($this->sGroup . '.otherscomment'),
            "cause" => SESSION::read($this->sGroup . '.cause'),
            "cause_text" => SESSION::read($this->sGroup . '.cause_t1') . SESSION::read($this->sGroup . '.cause_t2') . SESSION::read($this->sGroup . '.cause_t3'),
            "user_id" => $user_id,
			"friend_text" => $refer_friend_text,
            "comment" => SESSION::read($this->sGroup . '.comm'),
            "kutisu" => SESSION::read($this->sGroup . '.kutisu'),
        );
        
        // メール内容をDBに保存
        $url = Conf::read('REST_API.BASE_URL') . "/preRegistOrder";
        $this->curl_api_post($url, $user_array);
        
        /*
            "cause"・・・利用のきっかけ
        　  "cause_text"・・・利用のきっかけテキスト
        　  "user_id"・・・お客様ID
        　  "sex"・・・性別
        　  "wkbn"・・・職種
        */

        //オーダー完了したのでメール送信（オーダー専用のメール）
        $mail = new Mail();

        if (!$mail->send_order_care($this->sGroup, $this->sSpecial)) {
            LOGS_ERR('*** PASSWORD RESET ACCEPT MAIL SEND FAILED. ***');
            $this->set('alert', '申し込みのメール送信エラー発生しました。');
            return;
        }

        /*
         * 同時会員登録
         * パスワードの入力があった場合は同時登録。
         * ※ここでの会員登録は基幹システムへの登録のみなので
         * 　初回ログインを経由する必要がある。
         * 　理由：
         * 　ニックネームなどのフォームがないため。
         * 　ただ、ここでそれらの情報を入力させるのはUX的にはよくないともうので
         * 　このままでもよいのではないかと。
         */
        if (!StaticFunction::is_empty(SESSION::read($this->sGroup . '.idpass'))) {

            // 登録情報の配列格納
            $user_array = array(
                "name" => StaticFunction::marge_name(SESSION::read($this->sGroup . '.name1'),
                    SESSION::read($this->sGroup . '.name2')),
                "kana" => StaticFunction::marge_name(SESSION::read($this->sGroup . '.kana1'),
                    SESSION::read($this->sGroup . '.kana2')),
                "tel" => StaticFunction::marge_phone(SESSION::read($this->sGroup . '.telephone'),
                    SESSION::read($this->sGroup . '.telephone2'), SESSION::read($this->sGroup . '.telephone3')),
                "email" => SESSION::read($this->sGroup . '.email'),
                "email2" => SESSION::read($this->sGroup . '.email2'),
                "zip" => SESSION::read($this->sGroup . '.zip'),
                "state" => SESSION::read($this->sGroup . '.state'),
                "addr1" => SESSION::read($this->sGroup . '.addr1'),
                "addr2" => SESSION::read($this->sGroup . '.addr2'),
                "addr3" => SESSION::read($this->sGroup . '.addr3'),
                "pass" => SESSION::read($this->sGroup . '.idpass'),
                "birth" => StaticFunction::marge_birth(SESSION::read($this->sGroup . '.birth_y'),
                    SESSION::read($this->sGroup . '.birth_m'), SESSION::read($this->sGroup . '.birth_d')),
                "sex" => SESSION::read($this->sGroup . '.sex'),
                "wkbn" => SESSION::read($this->sGroup . '.wkbn')
            );

            if (!$mail->send_core_system_regist($user_array)) {
                LOGS_ERR('*** USER REGIST ON ORDER MAIL SEND FAILED. ***');
                $this->set('alert', 'エラーが発生しました。お手数ですが、再度お試し下さい。');
                return;
            }

            // メール内容をDBに保存
            $url = Conf::read('REST_API.BASE_URL') . "/preRegistVisitor";
            $this->curl_api_post($url, $user_array);
        }

        //正常終了時はセッションを削除
        SESSION::delete($this->sGroup);
    }

    /*	 * **********************************
     * NAME:checkSessionParameter
     * DESC:
     *  メルマガ登録専用のセッション情報バリデーション
     * NOTICE:
     * CREATE: 2016.10.14 aoyama
     * UPDATE: 2017.05.24 aoyama
     * 		23時以降の申し込みについては翌々日以降の集荷とする
     * *********************************** */
    private function checkSessionParameter()
    {

        $usermember = new UserPublicModel();
        $error_array = array();

        if (!InputVali::is_user_name(SESSION::read($this->sGroup . '.name1'))) {
            $error_array[] = array('target' => 'name1', 'message' => 'お名前(姓)を全角7文字以内で入力してください');
        }
        if (!InputVali::is_user_name(SESSION::read($this->sGroup . '.name2'))) {
            $error_array[] = array('target' => 'name2', 'message' => 'お名前(名)を全角7文字以内で入力してください');
        }

        if (!InputVali::is_name_kana(SESSION::read($this->sGroup . '.kana1'))) {
            $error_array[] = array('target' => 'kana1', 'message' => 'ふりがな(姓)を7文字以内のカタカナで入力してください');
        }
        if (!InputVali::is_name_kana(SESSION::read($this->sGroup . '.kana2'))) {
            $error_array[] = array('target' => 'kana2', 'message' => 'ふりがな(名)を7文字以内のカタカナで入力してください');
        }

        if (!InputVali::is_sex_val(SESSION::read($this->sGroup . '.sex'))) {
            $error_array[] = array('target' => 'sex', 'message' => '性別を選択してください');
        }
        if (!InputVali::is_birth_y(SESSION::read($this->sGroup . '.birth_y'))) {
            $error_array[] = array('target' => 'birth_y', 'message' => '生年を選択してください。');
        }
        if (!InputVali::is_month(SESSION::read($this->sGroup . '.birth_m'))) {
            $error_array[] = array('target' => 'birth_m', 'message' => '生月を選択してください。');
        }
        if (!InputVali::is_date(SESSION::read($this->sGroup . '.birth_d'))) {
            $error_array[] = array('target' => 'birth_d', 'message' => '生日を選択してください。');
        }

        if (!InputVali::is_zip(SESSION::read($this->sGroup . '.zip'))) {
            $error_array[] = array('target' => 'zip', 'message' => '郵便番号は半角数字で入力してください。');
        }
        if (!InputVali::is_prefecture(SESSION::read($this->sGroup . '.state'))) {
            $error_array[] = array('target' => 'state', 'message' => '都道府県を選択してください。');
        }

        if (!InputVali::is_municipality(SESSION::read($this->sGroup . '.addr1'))) {
            $error_array[] = array('target' => 'addr1', 'message' => '市区郡を半角22文字以内(全角11文字)以内で入力してください。');
        }
        if (!InputVali::is_house_number(SESSION::read($this->sGroup . '.addr2'))) {
            $error_array[] = array('target' => 'addr2', 'message' => '町村・番地を半角32文字以内(全角16文字)以内で入力してください。');
        }
        if (!StaticFunction::is_empty(SESSION::read($this->sGroup . '.addr3'))) {
            if (!InputVali::is_building(SESSION::read($this->sGroup . '.addr3'))) {
                $error_array[] = array('target' => 'addr3', 'message' => 'ビル・マンション名は半角32文字以内(全角16文字)以内で入力してください。');
            }
        }
        if (!InputVali::is_phone(SESSION::read($this->sGroup . '.telephone') . "-" . SESSION::read($this->sGroup . '.telephone2') . "-" . SESSION::read($this->sGroup . '.telephone3'))) {
            $error_array[] = array('target' => 'tel', 'message' => '電話番号はハイフン無しの半角文字で入力して下さい。');
        }
        if (
            !StaticFunction::is_empty(SESSION::read($this->sGroup . '.faxnum')) ||
            !StaticFunction::is_empty(SESSION::read($this->sGroup . '.faxnum2')) ||
            !StaticFunction::is_empty(SESSION::read($this->sGroup . '.faxnum3'))
        ) {
            if (!InputVali::is_phone(SESSION::read($this->sGroup . '.faxnum') . "-" . SESSION::read($this->sGroup . '.faxnum2') . "-" . SESSION::read($this->sGroup . '.faxnum3'))) {
                $error_array[] = array('target' => 'tel', 'message' => 'FAX番号はハイフン無しの半角文字で入力して下さい。');
            }
        }

        if (!InputVali::is_mailaddress(SESSION::read($this->sGroup . '.email'))) {
            $error_array[] = array('target' => 'email', 'message' => 'メールアドレスを入力してください');
        }
        if (!StaticFunction::is_empty(SESSION::read($this->sGroup . '.email2'))) {
            if (!InputVali::is_mailaddress(SESSION::read($this->sGroup . '.email2'))) {
                $error_array[] = array('target' => 'email2', 'message' => 'サブメールアドレスを正しいメールアドレスで入力してください');
            }
        }

        if (!InputVali::is_job(SESSION::read($this->sGroup . '.wkbn'))) {
            $error_array[] = array('target' => 'wkbn', 'message' => '職業を選択してください');
        }

        /*
         * お届け先
         *
         * とりあえず苗字と郵便番号、addr1に入力がある場合はその他をすべて必須にする。
         */

        if (!StaticFunction::is_empty(SESSION::read($this->sGroup . '.s_name1')) ||
            !StaticFunction::is_empty(SESSION::read($this->sGroup . '.s_zip')) ||
            !StaticFunction::is_empty(SESSION::read($this->sGroup . '.s_addr1'))
        ) {
            $this->set("toggle_open", true);

            if (!InputVali::is_user_name(SESSION::read($this->sGroup . '.s_name1'))) {
                $error_array[] = array('target' => 's_name1', 'message' => 'お届け先のお名前(姓)を全角7文字以内で入力してください');
            }
            if (!InputVali::is_user_name(SESSION::read($this->sGroup . '.s_name2'))) {
                $error_array[] = array('target' => 's_name2', 'message' => 'お届け先のお名前(名)を全角7文字以内で入力してください');
            }
            if (!InputVali::is_name_kana(SESSION::read($this->sGroup . '.s_kana1'))) {
                $error_array[] = array('target' => 's_kana1', 'message' => 'お届け先のふりがな(姓)を7文字以内のカタカナ入力してください');
            }
            if (!InputVali::is_name_kana(SESSION::read($this->sGroup . '.s_kana2'))) {
                $error_array[] = array('target' => 's_kana2', 'message' => 'お届け先のふりがな(名)を7文字以内のカタカナ入力してください');
            }
            if (!InputVali::is_zip(SESSION::read($this->sGroup . '.s_zip'))) {
                $error_array[] = array('target' => 's_zip', 'message' => 'お届け先の郵便番号は半角数字で入力してください。');
            }

            if (!InputVali::is_prefecture(SESSION::read($this->sGroup . '.s_state'))) {
                $error_array[] = array('target' => 's_state', 'message' => 'お届け先の都道府県を選択してください。');
            }
            if (!InputVali::is_municipality(SESSION::read($this->sGroup . '.s_addr1'))) {
                $error_array[] = array('target' => 's_addr1', 'message' => 'お届け先の市区郡は半角22文字以内(全角11文字)以内で入力してください。');
            }
            if (!InputVali::is_house_number(SESSION::read($this->sGroup . '.s_addr2'))) {
                $error_array[] = array('target' => 's_addr2', 'message' => 'お届け先の町村・番地は半角32文字以内(全角16文字)以内で入力してください。');
            }
            if (!StaticFunction::is_empty(SESSION::read($this->sGroup . '.s_addr3'))) {
                if (!InputVali::is_building(SESSION::read($this->sGroup . '.s_addr3'))) {
                    $error_array[] = array(
                        'target' => 's_addr3',
                        'message' => 'お届け先のビル・マンション名は半角32文字以内(全角16文字)以内で入力してください。'
                    );
                }
            }
            if (!InputVali::is_phone(SESSION::read($this->sGroup . '.s_telephone') . "-" . SESSION::read($this->sGroup . '.s_telephone2') . "-" . SESSION::read($this->sGroup . '.s_telephone3'))) {
                $error_array[] = array('target' => 'tel', 'message' => 'お届け先の電話番号はハイフン無しの半角文字で入力して下さい。');
            }
        }

        /* 引取情報 */
        //入力時刻が23時以降の場合は翌々日の日付しか選択できないように。
        if (!InputVali::is_order_pickup_date(SESSION::read($this->sGroup . '.taking_y'),
            SESSION::read($this->sGroup . '.taking_m'), SESSION::read($this->sGroup . '.taking_d'))
        ) {
            $error_array[] = array(
                'target' => 'tel',
                'message' => '引取日は明日以降の日時を指定してください。また、23時以降のお申込みでの引取日は翌々日以降の日時を指定してください。'
            );
        }

        if (StaticFunction::is_empty(SESSION::read($this->sGroup . '.time'))) {
            $error_array[] = array('target' => 'time', 'message' => '取引時間を選択してください。');
        } else {
            foreach (SESSION::read($this->sGroup . '.time') AS $value) {
                if (!InputVali::is_array_key($value, CONF::read('SHIPPING_TIMEZONE_ARRAY.'.SESSION::read($this->sGroup . '.carrier')))) {
                    $error_array[] = array('target' => 'kutisu', 'message' => '取引時間は選択肢から選択してください。');
                }

                /* 6/18以降の時間指定バリデーション */
                /*
                $switch_date = 20170619;
                $oder_date = DbDateTime::fairing_digit_8(DbDateTime::get_datetime_by_part(SESSION::read($this->sGroup . '.taking_y'),
                    SESSION::read($this->sGroup . '.taking_m'), SESSION::read($this->sGroup . '.taking_d') ));

                if ($oder_date >= $switch_date && ($value === "7")) {
                    $error_array[] = array('target' => 'kutisu', 'message' => '6/18以降の取引時間は選択肢から選択してください。');
                }
                if ($oder_date < $switch_date &&  $value === "8") {
                    $error_array[] = array('target' => 'kutisu', 'message' => '6/18以前の取引時間は選択肢から選択してください。');
                }
                */
            }
        }

        if (!InputVali::is_num(SESSION::read($this->sGroup . '.kutisu'), true, 1, 20)) {
            $error_array[] = array('target' => 'kutisu', 'message' => '荷物個口数を1～20の半角数字で入力してください。');
        }
        if (!InputVali::is_array_key(SESSION::read($this->sGroup . '.cat'), CONF::read('CATALOG_ORDER'))) {
            $error_array[] = array('target' => 'cat', 'message' => 'カタログ送付を選択してください。');
        }
        if (!InputVali::is_array_key(SESSION::read($this->sGroup . '.mag'), CONF::read('MAILMAG'))) {
            $error_array[] = array('target' => 'mag', 'message' => 'メールマガジンを選択してください。');
        }
        if (!InputVali::is_array_key(SESSION::read($this->sGroup . '.kep'), CONF::read('WARDROBE_ORDER'))) {
            $error_array[] = array('target' => 'kep', 'message' => '保管お預かりを選択してください。');
        }

        if (!StaticFunction::is_empty(SESSION::read($this->sGroup . '.cause'))) {
            if (!InputVali::is_num(SESSION::read($this->sGroup . '.cause'), true, 1, 6)) {
                $error_array[] = array('target' => 'cause', 'message' => '今回利用されたきっかけは選択肢から選択してください。');
            }
        }
        if (!StaticFunction::is_empty(SESSION::read($this->sGroup . '.cause_t3'))) {
            if (!InputVali::is_comment_contact(SESSION::read($this->sGroup . '.cause_t3'))) {
                $error_array[] = array('target' => 'cause_t3', 'message' => '検索エンジン/キーワード欄は200文字以内で入力してください');
            }
        }
        if (!StaticFunction::is_empty(SESSION::read($this->sGroup . '.cause_t1'))) {
            if (!InputVali::is_comment_contact(SESSION::read($this->sGroup . '.cause_t1'))) {
                $error_array[] = array('target' => 'cause_t1', 'message' => 'TV番組名/雑誌名欄は200文字以内で入力してください');
            }
        }
        if (!StaticFunction::is_empty(SESSION::read($this->sGroup . '.cause_t2'))) {
            if (!InputVali::is_comment_contact(SESSION::read($this->sGroup . '.cause_t2'))) {
                $error_array[] = array('target' => 'cause_t2', 'message' => 'その他欄は200文字以内で入力してください');
            }
        }
        if (!StaticFunction::is_empty(SESSION::read($this->sGroup . '.comm'))) {
            if (!InputVali::is_comment_contact(SESSION::read($this->sGroup . '.comm'))) {
                $error_array[] = array('target' => 'comm', 'message' => '通信欄は200文字以内で入力してください');
            }
        }

        if (!StaticFunction::is_empty(SESSION::read($this->sGroup . '.idpass'))) {
            if (!InputVali::is_password(SESSION::read($this->sGroup . '.idpass'))) {
                $error_array[] = array('target' => 'idpass', 'message' => 'パスワードは半角英数の5～8文字で入力してください');
            }
        }
        return $error_array;
    }

    /*	 * **********************************
     * NAME:formReturn
     * DESC:
     *  セッション情報をフォームに渡すためにセットする機能
     * NOTICE:
     * CREATE: 2015.11.27 aoyama
     * UPDATE: 2016.10.13 aoyama
     * *********************************** */
    private function formReturn()
    {

        // セッションの情報をセットしてviewに渡す
        if (!StaticFunction::is_empty(SESSION::read($this->sGroup))) {
            $this->set("name1", SESSION::read($this->sGroup . '.name1'));
            $this->set("name2", SESSION::read($this->sGroup . '.name2'));
            $this->set("name_view", StaticFunction::marge_name(SESSION::read($this->sGroup . '.name1'),
                SESSION::read($this->sGroup . '.name2'), SESSION::read($this->sGroup . '.name3')));
            $this->set("kana1", SESSION::read($this->sGroup . '.kana1'));
            $this->set("kana2", SESSION::read($this->sGroup . '.kana2'));
            $this->set("kana_view", StaticFunction::marge_name(SESSION::read($this->sGroup . '.kana1'),
                SESSION::read($this->sGroup . '.kana2'), SESSION::read($this->sGroup . '.kana3')));
            $this->set("sex", SESSION::read($this->sGroup . '.sex'));
            $this->set("birth_y", SESSION::read($this->sGroup . '.birth_y'));
            $this->set("birth_m", SESSION::read($this->sGroup . '.birth_m'));
            $this->set("birth_d", SESSION::read($this->sGroup . '.birth_d'));
            $this->set("birth_view", StaticFunction::marge_birth_for_view(SESSION::read($this->sGroup . '.birth_y'),
                SESSION::read($this->sGroup . '.birth_m'), SESSION::read($this->sGroup . '.birth_d')));

            $this->set("zip", SESSION::read($this->sGroup . '.zip'));
            $this->set("state", SESSION::read($this->sGroup . '.state'));
            $this->set("addr1", SESSION::read($this->sGroup . '.addr1'));
            $this->set("addr2", SESSION::read($this->sGroup . '.addr2'));
            $this->set("addr3", SESSION::read($this->sGroup . '.addr3'));
            $this->set("address_view", StaticFunction::marge_address_for_view(SESSION::read($this->sGroup . '.zip'),
                SESSION::read($this->sGroup . '.state'), SESSION::read($this->sGroup . '.addr1'),
                SESSION::read($this->sGroup . '.addr2'), SESSION::read($this->sGroup . '.addr3')));

            $this->set("telephone", SESSION::read($this->sGroup . '.telephone'));
            $this->set("telephone2", SESSION::read($this->sGroup . '.telephone2'));
            $this->set("telephone3", SESSION::read($this->sGroup . '.telephone3'));
            $this->set("telephone_view", StaticFunction::marge_phone(SESSION::read($this->sGroup . '.telephone'),
                SESSION::read($this->sGroup . '.telephone2'), SESSION::read($this->sGroup . '.telephone3')));
            $this->set("faxnum", SESSION::read($this->sGroup . '.faxnum'));
            $this->set("faxnum2", SESSION::read($this->sGroup . '.faxnum2'));
            $this->set("faxnum3", SESSION::read($this->sGroup . '.faxnum3'));
            $this->set("faxnum_view", StaticFunction::marge_phone(SESSION::read($this->sGroup . '.faxnum'),
                SESSION::read($this->sGroup . '.faxnum2'), SESSION::read($this->sGroup . '.faxnum3')));
            $this->set("email", SESSION::read($this->sGroup . '.email'));
            $this->set("email2", SESSION::read($this->sGroup . '.email2'));
            $this->set("wkbn", SESSION::read($this->sGroup . '.wkbn'));

            $this->set("s_name1", SESSION::read($this->sGroup . '.s_name1'));
            $this->set("s_name2", SESSION::read($this->sGroup . '.s_name2'));
            $this->set("s_name_view", StaticFunction::marge_name(SESSION::read($this->sGroup . '.s_name1'),
                SESSION::read($this->sGroup . '.s_name2')));
            $this->set("s_kana1", SESSION::read($this->sGroup . '.s_kana1'));
            $this->set("s_kana2", SESSION::read($this->sGroup . '.s_kana2'));
            $this->set("s_kana_view", StaticFunction::marge_name(SESSION::read($this->sGroup . '.s_kana1'),
                SESSION::read($this->sGroup . '.s_kana2')));
            $this->set("s_zip", SESSION::read($this->sGroup . '.s_zip'));
            $this->set("s_state", SESSION::read($this->sGroup . '.s_state'));
            $this->set("s_addr1", SESSION::read($this->sGroup . '.s_addr1'));
            $this->set("s_addr2", SESSION::read($this->sGroup . '.s_addr2'));
            $this->set("s_addr3", SESSION::read($this->sGroup . '.s_addr3'));
            $this->set("s_address_view", StaticFunction::marge_address_for_view(SESSION::read($this->sGroup . '.s_zip'),
                SESSION::read($this->sGroup . '.s_state'), SESSION::read($this->sGroup . '.s_addr1'),
                SESSION::read($this->sGroup . '.s_addr2'), SESSION::read($this->sGroup . '.s_addr3')));
            $this->set("s_telephone", SESSION::read($this->sGroup . '.s_telephone'));
            $this->set("s_telephone2", SESSION::read($this->sGroup . '.s_telephone2'));
            $this->set("s_telephone3", SESSION::read($this->sGroup . '.s_telephone3'));
            $this->set("s_telephone_view", StaticFunction::marge_phone(SESSION::read($this->sGroup . '.s_telephone'),
                SESSION::read($this->sGroup . '.s_telephone2'), SESSION::read($this->sGroup . '.s_telephone3')));
            $taking_y = SESSION::read($this->sGroup . '.taking_y');
            $taking_m = SESSION::read($this->sGroup . '.taking_m');
            $taking_d = SESSION::read($this->sGroup . '.taking_d');
            /*
            $this->set("taking_y", SESSION::read($this->sGroup . '.taking_y'));
            $this->set("taking_m", SESSION::read($this->sGroup . '.taking_m'));
            $this->set("taking_d", SESSION::read($this->sGroup . '.taking_d'));
            */
            $this->set("taking_date", $taking_y . "-" . $taking_m . "-" . $taking_d);
            $this->set("taking_view", StaticFunction::marge_birth_for_view(SESSION::read($this->sGroup . '.taking_y'),
                SESSION::read($this->sGroup . '.taking_m'), SESSION::read($this->sGroup . '.taking_d')));

            if (StaticFunction::is_empty(SESSION::read($this->sGroup . '.time'))) {
                $this->set("time", array());
            } else {
                $this->set("time", SESSION::read($this->sGroup . '.time'));
            }


            if (StaticFunction::is_empty(SESSION::read($this->sGroup . '.kutisu'))) {
                $this->set("kutisu", 1);
            } else {
                $this->set("kutisu", SESSION::read($this->sGroup . '.kutisu'));
            }

            $carrier_view = "";
            $carrier = SESSION::read($this->sGroup . '.carrier');
            $carrier_view = CONF::read('SHIPPING_TRADER.' . (string)$carrier);
            $this->set("carrier", $carrier);
            $this->set("carrier_view", $carrier_view);

            $time_view = "";
            if (!StaticFunction::is_empty(SESSION::read($this->sGroup . '.time'))) {
                foreach (SESSION::read($this->sGroup . '.time') AS $value) {
                    if (InputVali::is_num($value, true, 1, 8)) {
                        $time_view .= CONF::read('SHIPPING_TIMEZONE_ARRAY.' . (string)$carrier . '.' . (string)$value) . "<br>";
                    }
                }
            }
            $this->set("time_view", $time_view);

            $this->set("cat", SESSION::read($this->sGroup . '.cat'));
            $this->set("cat_view", CONF::read('CATALOG_ORDER.' . SESSION::read($this->sGroup . '.cat')));
            $this->set("mag", SESSION::read($this->sGroup . '.mag'));
            $this->set("mag_view", CONF::read('MAILMAG.' . SESSION::read($this->sGroup . '.mag')));
            $this->set("kep", SESSION::read($this->sGroup . '.kep'));
            $this->set("kep_view", CONF::read('WARDROBE_ORDER.' . SESSION::read($this->sGroup . '.kep')));

            //ラジオボタンのセレクト状態をviewに渡す
            $this->set("cat1_selected", (SESSION::read($this->sGroup . '.cat') == 1) ? 'checked' : '');
            $this->set("cat2_selected", (SESSION::read($this->sGroup . '.cat') == 2) ? 'checked' : '');
            $this->set("mag1_selected", (SESSION::read($this->sGroup . '.mag') == 1) ? 'checked' : '');
            $this->set("mag2_selected", (SESSION::read($this->sGroup . '.mag') == 2) ? 'checked' : '');
            $this->set("kep1_selected", (SESSION::read($this->sGroup . '.kep') == 1) ? 'checked' : '');
            $this->set("kep2_selected", (SESSION::read($this->sGroup . '.kep') == 2) ? 'checked' : '');

            //アンケート情報を渡す
            /*
            // Commenttted by UKS Manjunathgouda
            // on 2022-02-11
            $this->set("cause", SESSION::read($this->sGroup . '.cause'));
            $this->set("cause_view", CONF::read('ORDER_ENQUETE.' . SESSION::read($this->sGroup . '.cause')));
            $this->set("cause1_selected", (SESSION::read($this->sGroup . '.cause') == 1) ? 'checked' : '');
            $this->set("cause2_selected", (SESSION::read($this->sGroup . '.cause') == 2) ? 'checked' : '');
            $this->set("cause3_selected", (SESSION::read($this->sGroup . '.cause') == 3) ? 'checked' : '');
            $this->set("cause4_selected", (SESSION::read($this->sGroup . '.cause') == 4) ? 'checked' : '');
            $this->set("cause5_selected", (SESSION::read($this->sGroup . '.cause') == 5) ? 'checked' : '');
            $this->set("cause6_selected", (SESSION::read($this->sGroup . '.cause') == 6) ? 'checked' : '');
            $this->set("cause_t3", SESSION::read($this->sGroup . '.cause_t3'));
            $this->set("cause_t1", SESSION::read($this->sGroup . '.cause_t1'));
            $this->set("cause_t2", SESSION::read($this->sGroup . '.cause_t2')); 
            */
            /*
            *   Added by: Manjunathgouda
            *   Desc: Reading all cause session data 
            *   Date: 2022-02-11
            * ----------------------------  START --------------------------------------------------
            */
            $this->set("cause1_selected", (SESSION::read($this->sGroup . '.netsearchcheck') == 1) ? 'checked' : '');
            $this->set("cause2_selected", (SESSION::read($this->sGroup . '.webadvertisingcheck') == 1) ? 'checked' : '');
            $this->set("cause3_selected", (SESSION::read($this->sGroup . '.facebookcheck') == 1) ? 'checked' : '');
            $this->set("cause4_selected", (SESSION::read($this->sGroup . '.instagramcheck') == 1) ? 'checked' : '');
            $this->set("cause5_selected", (SESSION::read($this->sGroup . '.twittercheck') == 1) ? 'checked' : '');
            $this->set("cause6_selected", (SESSION::read($this->sGroup . '.youtubecheck') == 1) ? 'checked' : '');
            $this->set("cause7_selected", (SESSION::read($this->sGroup . '.shopcheck') == 1) ? 'checked' : '');
            $this->set("cause8_selected", (SESSION::read($this->sGroup . '.acquaintanceintroductioncheck') == 1) ? 'checked' : '');
            $this->set("cause9_selected", (SESSION::read($this->sGroup . '.tvcheck') == 1) ? 'checked' : '');
            $this->set("cause10_selected", (SESSION::read($this->sGroup . '.changeclothescheck') == 1) ? 'checked' : '');
            $this->set("cause11_selected", (SESSION::read($this->sGroup . '.salecheck') == 1) ? 'checked' : '');
            $this->set("cause12_selected", (SESSION::read($this->sGroup . '.otherscheck') == 1) ? 'checked' : '');

            $this->set("cause_t3", SESSION::read($this->sGroup . '.netsearchcomment'));
            $this->set("cause_t1", SESSION::read($this->sGroup . '.tvcomment'));
            $this->set("cause_t2", SESSION::read($this->sGroup . '.otherscomment'));

            // ----------------------------  START --------------------------------------------------

            $this->set("comm", SESSION::read($this->sGroup . '.comm'));
            $this->set("idpass", SESSION::read($this->sGroup . '.idpass'));
            $this->set("pass_mask", StaticFunction::changePasswordText(SESSION::read($this->sGroup . '.idpass')));
        } else {
            $this->set("comm", SESSION::read($this->sComm . '.comm'));
        }
    }

    /**
	 * CURLでAPIと通信する（POST)
	 *
	 * @param string $url
	 * @param array $post_data
	 * @return void
	 */
	private function curl_api_post($url, $post_data) {
		// cURLセッションを初期化
		$ch = curl_init();

		// オプションを設定
		curl_setopt($ch, CURLOPT_URL, $url); // 取得するURLを指定
		curl_setopt($ch, CURLOPT_POST, TRUE);
        curl_setopt($ch, CURLOPT_POSTFIELDS, http_build_query($post_data));
        curl_setopt($ch, CURLOPT_SSL_VERIFYPEER, FALSE);  // オレオレ証明書対策
        curl_setopt($ch, CURLOPT_SSL_VERIFYHOST, FALSE);  // 
        curl_setopt($ch, CURLOPT_RETURNTRANSFER, TRUE);
        curl_setopt($ch, CURLOPT_COOKIEJAR, 'cookie');
        curl_setopt($ch, CURLOPT_COOKIEFILE, 'tmp');
        curl_setopt($ch, CURLOPT_FOLLOWLOCATION, TRUE); // Locationヘッダを追跡

		// URLの情報を取得
		$response =  curl_exec($ch);

		$res = json_decode($response, true);

		return $res;
	}

}

?>
