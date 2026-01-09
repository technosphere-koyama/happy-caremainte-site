// Your web app's Firebase configuration
// For Firebase JS SDK v7.20.0 and later, measurementId is optional
var firebaseConfig = {
	apiKey: "AIzaSyA5nfQsm0eQHwJ7pucYq9DjZDImmm47S8s",
	authDomain: "happycarementeh.firebaseapp.com",
	databaseURL: "https://happycarementeh.firebaseio.com",
	projectId: "happycarementeh",
	storageBucket: "happycarementeh.appspot.com",
	messagingSenderId: "303775457768",
	appId: "1:303775457768:web:6c7b7c2889377cb031c45d",
	measurementId: "G-WL549VPHTL"
};
// Initialize Firebase
firebase.initializeApp(firebaseConfig);

// 設定 > Cloud Meesaging > ウェブプッシュ証明書 > 鍵ペア
var vapidKey = "BBSrmNpJV5rzxEo59vBBecBPvx3b0hdAxdIHsvrhd3_U__fzalciYwLSr673qbrnEgfZe47XFSRSaz0gXgoeY9Q";

var registrationToken

// Retrieve Firebase Messaging object.
const messaging = firebase.messaging();

// chromeのみ有効。firefoxはユーザー操作起点でないとrequestPermissionが拒否される
messaging.requestPermission()
.then(function () {
	console.log('Have permission');
	return messaging.getToken({vapidKey: vapidKey});
})
.then(function (token) {
	console.log(token);
})
.catch(function (err) {
	console.log('Error occurred');
});
