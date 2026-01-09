<?php

/*
 * ローカルは、各人の環境によってパスが変わるので
 * 「public」までのパスを取得し、ドキュメントルートとして設定する
 * ※人によってはhostsに設定してダミーホストで「public」をドキュメントルートに設定する場合がある
 * 　なので、「public」が見当たらなければ、ステージングなどと同じようにURL_HOSTをルートとする
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
