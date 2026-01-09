/*
	PUSH通知

	・利用するページで下記を<body>内に記述する
	<script src="https://www.gstatic.com/firebasejs/8.2.1/firebase-app.js"></script>
	<script src="https://www.gstatic.com/firebasejs/8.2.1/firebase-messaging.js"></script>
	<script src="./push_notification.js"></script>
*/

var PUSH = PUSH || {};
{
	let firebaseConfig = {
		apiKey: "AIzaSyA5nfQsm0eQHwJ7pucYq9DjZDImmm47S8s",
		authDomain: "happycarementeh.firebaseapp.com",
		databaseURL: "https://happycarementeh.firebaseio.com",
		projectId: "happycarementeh",
		storageBucket: "happycarementeh.appspot.com",
		messagingSenderId: "303775457768",
		appId: "1:303775457768:web:6c7b7c2889377cb031c45d",
		measurementId: "G-WL549VPHTL"
	};

	// 設定 > Cloud Meesaging > ウェブプッシュ証明書 > 鍵ペア
	let vapidKey = "BBSrmNpJV5rzxEo59vBBecBPvx3b0hdAxdIHsvrhd3_U__fzalciYwLSr673qbrnEgfZe47XFSRSaz0gXgoeY9Q";

	let _isSupported;
	let messaging;
	let registrationToken = "";

	PUSH = {
		initializeApp: function() {
			if (this.isSupported()) {
				firebase.initializeApp(firebaseConfig);
				messaging = firebase.messaging();
			}
		},

		isSupported: function() {
			if( _isSupported !== undefined ) { return _isSupported; }
			_isSupported = firebase.messaging.isSupported();
			return _isSupported;
		},

		getToken: async function() {
			if (registrationToken != "") { return registrationToken; }

			// console.log("getTokenFromUA");
			registrationToken = this.getTokenFromUA();
			if (registrationToken != "") { return registrationToken; }

			// console.log("getTokenFromFCM");
			registrationToken = await this.getTokenFromFCM();
			return registrationToken;
		},

		getTokenFromUA: function() {
			var ua = navigator.userAgent;
			var vals = ua.split(" ");
			const result = vals.filter(val => val.indexOf("registrationToken/") == 0 );

			console.log(result);

			if (result.length > 0) {
				console.log(result[0].substring("registrationToken/".length, result[0].length));
				return result[0].substring("registrationToken/".length, result[0].length);
			} else {
				console.log('registrationToken not exists.');
				return "";
			}
		},

		getTokenFromFCM: async function() {
			var ret = "";
			if (!this.isSupported()) { return ret; }

			await messaging.requestPermission()
			.then(async function () {
				console.log('Have permission');
				ret = await messaging.getToken({vapidKey: vapidKey});
			})
			.catch(function (err) {
				console.log('Error occurred');
			});

			return ret;
		},
	};
}

(async function() {
	PUSH.initializeApp();

	// chromeのみページ読み込み時に有効。
	// firefoxはユーザー操作起点でないとrequestPermission等による通知の許可設定が拒否される
	await PUSH.getToken()
	.then( (ret) => { console.log(ret); } );
}());
