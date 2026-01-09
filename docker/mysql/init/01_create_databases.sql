-- データベース作成
CREATE DATABASE IF NOT EXISTS happy_sns CHARACTER SET utf8mb4 COLLATE utf8mb4_unicode_ci;
CREATE DATABASE IF NOT EXISTS happy_wp CHARACTER SET utf8mb4 COLLATE utf8mb4_unicode_ci;

-- ユーザー作成
CREATE USER IF NOT EXISTS 'happy_sns'@'%' IDENTIFIED BY 'happy_sns_pass';
CREATE USER IF NOT EXISTS 'happy_wp'@'%' IDENTIFIED BY 'happy_wp_pass';

-- 権限付与
GRANT ALL PRIVILEGES ON happy_sns.* TO 'happy_sns'@'%';
GRANT ALL PRIVILEGES ON happy_wp.* TO 'happy_wp'@'%';
FLUSH PRIVILEGES;
