<?php

/*
 * ステージングは、ドメイン直下のパスではなく、ローカルと同じく
 * ディレクトリでのPublicアクセスとなるので、ローカルと同じにしておく
 * ※ステージング用ドメインを取得する場合はreleaseと同じにする必要がある
 */
$is_public = false;
$list = explode('/', URL_REQUEST);
$path = '';
if (!empty($list)) {
	foreach ($list as $value) {
		$path .= $value . '/';
		if ($value == 'public') {
			$is_public = true;
			break;
		}
	}
}

//publicがなかったらURL_HOSTをドキュメントルートとする
if (!$is_public) {
	$path = '/';
}

$config["URL_PUBLIC_ROOT"] = URL_SCHEME . '://' . URL_HOST . $path;
$config["URL_SYSTEM_ROOT"] = $config["URL_PUBLIC_ROOT"] . DIR_NAME_ADMIN . '/';

?>
