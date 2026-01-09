#!/bin/bash

# Docker環境セットアップスクリプト

echo "=== Docker環境セットアップ ==="

# ローカル用設定ファイルをコピー
echo "1. 設定ファイルをコピー中..."

# データベース設定
cp docker/config/DatabaseConfig.inc www/secure_html/core/module/database/preLoadConf/local/DatabaseConfig.inc
echo "   - DatabaseConfig.inc をコピーしました"

# WordPress設定
cp docker/config/wp-config.php www/secure_html/public/wp/wp-config.php
echo "   - wp-config.php をコピーしました"

# tmp ディレクトリ作成
echo "2. 必要なディレクトリを作成中..."
mkdir -p www/secure_html/core/tmp/log
mkdir -p www/secure_html/core/tmp/session
mkdir -p www/secure_html/public/images/tmp
chmod -R 777 www/secure_html/core/tmp
chmod -R 777 www/secure_html/public/images/tmp
echo "   - tmp ディレクトリを作成しました"

echo ""
echo "=== セットアップ完了 ==="
echo ""
echo "次のコマンドでDockerを起動してください:"
echo "  docker-compose up -d"
echo ""
echo "アクセスURL:"
echo "  サイト:      http://localhost:8080/"
echo "  WordPress:   http://localhost:8080/wp/"
echo "  phpMyAdmin:  http://localhost:8081/"
echo ""
