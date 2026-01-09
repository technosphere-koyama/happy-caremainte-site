<?php


$redirect_url = urlencode($_SERVER["REQUEST_URI"]);

if(class_exists ('StaticFunction')) {
	
	if (!StaticFunction::is_empty(SESSION::read("PUBLIC_USER.name1"))) {
		$sns_name = '<a href="/mypage/"><i class="fa fa-user" aria-hidden="true"></i>' . $_SESSION['PUBLIC_USER']['name1'] . " " . $_SESSION['PUBLIC_USER']['name2'] . 'さま</a>';
		$tsunagu_link = "/mypage/sns.html";
	}
	else {
		$sns_name = '<a href="/login/?callback='.$redirect_url.'"><i class="fa fa-user" aria-hidden="true"></i>ログイン<span class="SPpart">／新規会員登録</span></a>';
		$tsunagu_link = "/login/happy.html";
	}	
}
else {
	if (!session_id()) {
		session_name("kh");
		session_save_path($_SERVER['DOCUMENT_ROOT'] . "/../core/tmp/session");
		@session_start();
	}

	if (isset($_SESSION['PUBLIC_USER']['name1'])) {
		$sns_name = '<a href="/mypage/"><i class="fa fa-user" aria-hidden="true"></i>' . $_SESSION['PUBLIC_USER']['name1'] . " " . $_SESSION['PUBLIC_USER']['name2'] . 'さま</a>';
		$tsunagu_link = "/mypage/sns.html";
	}
	else {
		$sns_name = '<a href="/login/?callback='.$redirect_url.'"><i class="fa fa-user" aria-hidden="true"></i>ログイン<span class="SPpart">／新規会員登録</span></a>';
		$tsunagu_link = "/login/happy.html";
	}
}

?>

<header>
			<div class="title"><a href="/"><h1><img src="/wp/wp-content/themes/HAPPY_Dark/img/logo_w.png" alt="ハッピー ケアメンテ"></h1></a></div>
			<div class="submenu">
				<?php echo $sns_name ?>
				<div class="tel">
					<img src="/_assets/img/app_home/tel.png" alt="tel">
				</div>
			</div>
		</header>