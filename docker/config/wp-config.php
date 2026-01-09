<?php
/**
 * WordPress の基本設定 (Docker環境用)
 */

// ** MySQL 設定 ** //
define('DB_NAME', 'happy_wp');
define('DB_USER', 'happy_wp');
define('DB_PASSWORD', 'happy_wp_pass');
define('DB_HOST', 'db');
define('DB_CHARSET', 'utf8');
define('DB_COLLATE', '');

/**
 * 認証用ユニークキー (開発用)
 * 本番環境では別のキーを使用すること
 */
define('AUTH_KEY',         'docker-dev-key-1');
define('SECURE_AUTH_KEY',  'docker-dev-key-2');
define('LOGGED_IN_KEY',    'docker-dev-key-3');
define('NONCE_KEY',        'docker-dev-key-4');
define('AUTH_SALT',        'docker-dev-salt-1');
define('SECURE_AUTH_SALT', 'docker-dev-salt-2');
define('LOGGED_IN_SALT',   'docker-dev-salt-3');
define('NONCE_SALT',       'docker-dev-salt-4');

$table_prefix = 'wp_';

define('WP_DEBUG', true);
define('WP_DEBUG_LOG', true);
define('WP_DEBUG_DISPLAY', true);

if (isset($_SERVER['HTTP_X_FORWARDED_PROTO']) && $_SERVER['HTTP_X_FORWARDED_PROTO'] == 'https')
    $_SERVER['HTTPS'] = 'on';

if (!defined('ABSPATH'))
    define('ABSPATH', dirname(__FILE__) . '/');

require_once(ABSPATH . 'wp-settings.php');
