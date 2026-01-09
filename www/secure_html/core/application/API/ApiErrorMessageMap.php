<?php

/*
 * DEFINES
 */
//400 bad request
define("API_ERR_BAD_PARAM_KEY",			4000001);
define("API_ERR_BAD_PARAM_VALUE",		4000002);
//401 unauthorized
define("API_ERR_AUTH_FAILED",			4010001);
define("API_ERR_ACCOUNT_DISABLED",		4010002);
define("API_ERR_OAUTH_FAILED",			4010003);
define("API_ERR_TOKEN_EXPIRED",			4010004);
//403 forbidden
define("API_ERR_INSUFFICIENT_PERMISSIONS",	4030001);
define("API_ERR_RESTRICT_IP",			4030002);
//404 not found
define("API_ERR_NOT_FOUND",			4040001);
//405 method not allowed 
define("API_ERR_NOT_ARROWED",			4050001);
//406 not acceptable
define("API_ERR_OVER_ACCEPT_NUM",		4060001);
define("API_ERR_RESTRICT_PROTOCOL",		4060002);
//409 conflict
define("API_ERR_ALREADY_EXISTS",		4090001);
//415 unsupported media type
//429 too many requests
define("API_ERR_LIMIT_OVER",			4290001);
//500 internal server error
define("API_ERR_INTERNAL",			5000001);
define("API_ERR_TIME_OUT",			5000002);
define("API_ERR_SEND_MAIL",			5000003);
//503 server busy
define("API_ERR_SERVER_BUSY",			5030001);
//999 other
define("API_ERR_OTHER",				9990001);
define("API_ERR_GENGO_API",			1000001);

/* * **********************************
 * NAME:ApiErrorMessageMap
 * DESC:
 *  APIでの処理にてエラーが発生した際のコード・テキストのリスト
 *  キーを指定することでコードとテキストを取得し、呼び出し元へ返すことを想定している
 *  これにより、エラー管理をAPI側で一元管理し、呼び出し元でのエラー表示作業をなくす
 *  ことが可能となる
 * NOTICE:
 *  エラーコードはきちんと体系化する
 * 
 *  array(
 *	key(DEFINES) => array(code, status, reason, message),
 *	...
 *  )
 *  ex.
 *  array(
 *	API_ERR_NOT_ARROWED => array(E405-0001, 405, 'not allowed', '許可されていません')
 *  )
 * 
 *  ------------------
 *  現状では、複数エラーはサポートしない
 *  ※複数エラーに対応すると、受け取り側も対応する必要があり、
 *  　現状複数エラーを想定していないのに作りを複雑にするのも
 *  　どうだろうというところから
 *  必要になれば作り変える
 *  ------------------
 * 
 * CREATE: 2016.07.21 hesaka
 * *********************************** */
class ApiErrorMessageMap {

	/*
	 * Constructor
	 */
	public function __construct() {
	}

	/* * **********************************
	 * NAME  : load
	 * INPUT : NONE
	 * OUTPUT: array / エラーマップ配列
	 * DESC  :
	 *  APIエラーマップ配列を返す
	 * NOTICE:
	 *  コードの参考
	 *  Cloud Oracle Messaging Cloud Service
	 *  https://docs.oracle.com/cd/E60665_01/messcs_common/CSMES/GUID-AAB1EE32-BE4A-4ACC-BEAC-ABA85EB41919.htm
	 *  Microsoft Azure
	 *  https://msdn.microsoft.com/ja-jp/library/azure/dd179357.aspx?f=255&MSPPError=-2147217396
	 * CREATE: 2016.10.06 hesaka 言語毎にエラーテキストを読み分ける変更により、
	 *                           処理タイミングを変更する必要が出たため
	 *                           ロードメソッドにした
	 * *********************************** */
	public function load() {
		return array(

			/*
			 * 400
			 * bad request
			 * パス情報の書式が正しくない、
			 * パラメータまたはリクエストの本文値の書式が正しくない、
			 * 必要なパラメータが足りない、
			 * または値の書式は正しいが何らかの原因で無効である
			 * (例: 
			 *	destinationパラメータが存在しない、
			 *	コンテンツが大きすぎる、
			 *	またはクライアントIDが使用中である)のいずれかです。
			 * )
			 */
			API_ERR_BAD_PARAM_KEY => array(
				'code' => 'E400-0001', 
				'status' => 400, 
				'reason' => 'bad parameter key', 
				'message' => CONF::read('LANG_TEXT.API_ERROR.E400-0001')
			),
			API_ERR_BAD_PARAM_VALUE => array(
				'code' => 'E400-0002', 
				'status' => 400, 
				'reason' => 'bad parameter value', 
				'message' => CONF::read('LANG_TEXT.API_ERROR.E400-0002')
			),

			/*
			 * 401
			 * unauthorized
			 * 認証の情報が正しくない
			 */
			API_ERR_AUTH_FAILED => array(
				'code' => 'E401-0001', 
				'status' => 401, 
				'reason' => 'id,password authentication failed', 
				'message' => CONF::read('LANG_TEXT.API_ERROR.E401-0001')
			),
			API_ERR_ACCOUNT_DISABLED => array(
				'code' => 'E401-0002', 
				'status' => 401, 
				'reason' => 'account is disabled', 
				'message' => CONF::read('LANG_TEXT.API_ERROR.E401-0002')
			),
			API_ERR_OAUTH_FAILED => array(
				'code' => 'E401-0003', 
				'status' => 401, 
				'reason' => 'o authentication failed', 
				'message' => CONF::read('LANG_TEXT.API_ERROR.E401-0003')
			),
			API_ERR_TOKEN_EXPIRED => array(
				'code' => 'E401-0004', 
				'status' => 401, 
				'reason' => 'access token expired', 
				'message' => CONF::read('LANG_TEXT.API_ERROR.E401-0004')
			),

			/*
			 * 403
			 * forbidden
			 * 起動者に操作を起動する権限がありません。
			 */
			API_ERR_INSUFFICIENT_PERMISSIONS => array(
				'code' => 'E403-0001', 
				'status' => 403, 
				'reason' => 'insufficient account permissions', 
				'message' => CONF::read('LANG_TEXT.API_ERROR.E403-0001')
			),
			API_ERR_RESTRICT_IP => array(
				'code' => 'E403-0002', 
				'status' => 403, 
				'reason' => 'ip restrict', 
				'message' => CONF::read('LANG_TEXT.API_ERROR.E403-0002')
			),

			/*
			 * 404
			 * not found
			 * パスで参照されたオブジェクトは存在しません。
			 */
			API_ERR_NOT_FOUND => array(
				'code' => 'E404-0001', 
				'status' => 404, 
				'reason' => 'not found', 
				'message' => CONF::read('LANG_TEXT.API_ERROR.E404-0001')
			),

			/*
			 * 405 method not allowed 
			 * メソッドがパスに許可されているメソッドの1つではありません。
			 */
			API_ERR_NOT_ARROWED => array(
				'code' => 'E405-0001', 
				'status' => 405, 
				'reason' => 'not allowed', 
				'message' => CONF::read('LANG_TEXT.API_ERROR.E405-0001')
			),

			/*
			 * 406
			 * not acceptable
			 * 受理できない。
			 * Acceptヘッダにサーバが送信可能なメディアタイプが指定されていなかった等。
			 * ※現在は使用しない
			 */
			API_ERR_OVER_ACCEPT_NUM => array(
				'code' => 'E406-0001', 
				'status' => 406, 
				'reason' => 'over accept num', 
				'message' => CONF::read('LANG_TEXT.API_ERROR.E406-0001')
			),
			API_ERR_RESTRICT_PROTOCOL => array(
				'code' => 'E406-0002', 
				'status' => 406, 
				'reason' => 'protocol restrict', 
				'message' => CONF::read('LANG_TEXT.API_ERROR.E406-0002')
			),

			/*
			 * 409
			 * conflict
			 * すでに存在するオブジェクトを作成しようとしました。
			 */
			API_ERR_ALREADY_EXISTS => array(
				'code' => 'E409-0001', 
				'status' => 409, 
				'reason' => 'already exists', 
				'message' => CONF::read('LANG_TEXT.API_ERROR.E409-0001')
			),

			/*
			 * 415
			 * unsupported media type
			 * 指定されたメディアタイプがサポートされていない。
			 * PUT, POST リクエストのボディのメディアタイプがXMLでない場合等。 
			 * ※現在は使用しない
			 */

			/*
			 * 429
			 * too many requests
			 * 使用制限をオーバー
			 */
			API_ERR_LIMIT_OVER => array(
				'code' => 'E429-0001', 
				'status' => 429, 
				'reason' => 'limit over', 
				'message' => CONF::read('LANG_TEXT.API_ERROR.E429-0001')
			),

			/*
			 * 500
			 * internal server error
			 * サービスの実行が何らかの原因で失敗しました。
			 */
			API_ERR_INTERNAL => array(
				'code' => 'E500-0001', 
				'status' => 500, 
				'reason' => 'internal server error', 
				'message' => CONF::read('LANG_TEXT.API_ERROR.E500-0001')
			),
			API_ERR_TIME_OUT => array(
				'code' => 'E500-0002', 
				'status' => 500, 
				'reason' => 'time out', 
				'message' => CONF::read('LANG_TEXT.API_ERROR.E500-0002')
			),
			API_ERR_SEND_MAIL => array(
				'code' => 'E500-0003', 
				'status' => 500, 
				'reason' => 'send mail error', 
				'message' => CONF::read('LANG_TEXT.API_ERROR.E500-0003')
			),

			/*
			 * 503
			 * out of service
			 * サービス利用不可
			 */
			API_ERR_SERVER_BUSY => array(
				'code' => 'E503-0001', 
				'status' => 503, 
				'reason' => 'server busy', 
				'message' => CONF::read('LANG_TEXT.API_ERROR.E503-0001')
			),

			/*
			 * 999
			 * other
			 * 上記エラーに当てはまらない場合はこれを返す
			 */
			API_ERR_OTHER => array(
				'code' => 'E999-0001', 
				'status' => 999, 
				'reason' => 'other error', 
				'message' => CONF::read('LANG_TEXT.API_ERROR.E999-0001')
			),

			/*
			 * 1000
			 * GENGO API
			 * (※)外部API実行でエラーが発生した場合は、1000番台のエラーを返す
			 * messageは通常ユーザにも表示される可能性があるので、GENGOという文言は隠す。
			 */
			API_ERR_GENGO_API => array(
				'code' => 'E1000-0001',
				'status' => 1000,
				'reason' => 'geogn error',
				'message' => CONF::read('LANG_TEXT.API_ERROR.E1000-0001')
			)
		);
	}

}

?>
