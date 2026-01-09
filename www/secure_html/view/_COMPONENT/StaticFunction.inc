<?php

/* * **********************************
 * NAME:
 * DESC:
 *		view専用の生function
 * NOTICE:
 * CREATE: 2016.10.21 aoyama
 * *********************************** */

	function h($text, $double = true, $charset = null) {
//		if (is_string($text)) {
//			//optimize for strings
//		} elseif (is_array($text)) {
//			$texts = array();
//			foreach ($text as $k => $t) {
//				$texts[$k] = h($t, $double, $charset);
//			}
//			return $texts;
//		} elseif (is_object($text)) {
//			if (method_exists($text, '__toString')) {
//				$text = (string)$text;
//			} else {
//				$text = '(object)' . get_class($text);
//			}
//		} elseif (is_bool($text)) {
//			return $text;
//		}
//
//		static $defaultCharset = false;
//		if ($defaultCharset === false) {
//			$defaultCharset = Configure::read('App.encoding');
//			if ($defaultCharset === null) {
//				$defaultCharset = 'UTF-8';
//			}
//		}
//		if (is_string($double)) {
//			$charset = $double;
//		}
//		return htmlspecialchars($text, ENT_QUOTES, ($charset) ? $charset : $defaultCharset, $double);
		return htmlspecialchars($text, ENT_QUOTES, "UTF-8");
	}



?>
