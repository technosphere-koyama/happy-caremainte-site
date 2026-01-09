/*
	PUSH通知

	・利用するページで下記を<body>内に記述する
	<script src="https://www.gstatic.com/firebasejs/8.2.1/firebase-app.js"></script>
	<script src="https://www.gstatic.com/firebasejs/8.2.1/firebase-messaging.js"></script>
	<script src="./push_notification.js"></script>
*/

var PUSH = PUSH || {};
{
	PUSH.updateUserNotification = async function(userId, deviceType = 0, registrationToken) {
		// console.log("updateUserNotification start");

		var ret = {"code": "0", "message": ""};

		await $.ajax( {
			url : "https://happy-kh01-dev.jcontents.co.jp/_api/v1/updateUserNotification",
			method: 'POST',
			data: {
				user_id: userId,
				device_type: deviceType,
				registration_token: registrationToken,
			},
			dataType: 'text',
			// cache: false,	// true: "_={timestamp}"を付与してアクセスする
			// crossDomain: false,	// domainを解析して自動で付与してくれそう
		} )
		.done( function( data, textStatus, jqXHR ) {
			console.log("updateUserNotification: completed.");
			console.log( data, textStatus, jqXHR );
			ret = JSON.parse(data);
		} )
		.fail( function( jqXHR, textStatus, errorThrown ) {
			console.log("updateUserNotification: failed.");
		} )
		.always(function( data, textStatus, jqXHR ) {
		});

		// console.log("updateUserNotification end");
		return ret;
	}

	PUSH.sendNotification = async function(title, message, userId = 0) {
		// console.log("sendNotification start");

		var ret = {"code": "0", "message": ""};

		await $.ajax( {
			url : "https://happy-kh01-dev.jcontents.co.jp/_api/v1/sendNotificationUser",
			method: 'POST',
			data: {
				user_id: userId,
				title: title,
				message: message,
			},
			dataType: 'text',
			// cache: false,	// true: "_={timestamp}"を付与してアクセスする
			// crossDomain: false,	// domainを解析して自動で付与してくれそう
		} )
		.done( function( data, textStatus, jqXHR ) {
			console.log("sendNotification: completed.");
			console.log( data, textStatus, jqXHR );
			ret = JSON.parse(data);
		} )
		.fail( function( jqXHR, textStatus, errorThrown ) {
			console.log("sendNotification: failed.");
		} )
		.always(function( data, textStatus, jqXHR ) {
		});

		// console.log("sendNotification end");
		return ret;
	}

	PUSH.sendNotificationAll = async function(title, message) {
		// console.log("sendNotificationAll start");

		var ret = {"code": "0", "message": ""};

		await $.ajax( {
			url : "https://happy-kh01-dev.jcontents.co.jp/_api/v1/sendNotificationAll",
			method: 'POST',
			data: {
				title: title,
				message: message,
			},
			dataType: 'text',
			// cache: false,	// true: "_={timestamp}"を付与してアクセスする
			// crossDomain: false,	// domainを解析して自動で付与してくれそう
		} )
		.done( function( data, textStatus, jqXHR ) {
			console.log("sendNotificationAll: completed.");
			console.log( data, textStatus, jqXHR );
			ret = JSON.parse(data);
		} )
		.fail( function( jqXHR, textStatus, errorThrown ) {
			console.log("sendNotificationAll: failed.");
		} )
		.always(function( data, textStatus, jqXHR ) {
		});

		// console.log("sendNotificationAll end");
		return ret;
	}
}
