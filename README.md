# Happy Care Mainte Site

京都ハッピー クリーニング店コーポレートサイト

## ディレクトリ構成

```
www/
├── csr/                    # SSL証明書 (git管理外)
├── public_html/            # 公開ディレクトリ (空)
└── secure_html/
    ├── core/               # PHPカスタムフレームワーク
    │   ├── application/    # コントローラー (API, Mypage, Public)
    │   ├── conf/           # 環境別設定 (local/staging/release)
    │   ├── define/         # 定数定義
    │   ├── library/        # 共通ライブラリ
    │   ├── module/         # モジュール (DB, REST, FCM等)
    │   └── tmp/            # ログ・セッション (git管理外)
    ├── public/
    │   ├── wp/             # WordPress
    │   └── images/         # 画像ファイル
    └── view/               # HTMLテンプレート
```

## 環境設定

設定ファイルは環境ごとに分離されています:

- `local/` - ローカル開発環境
- `staging/` - ステージング環境
- `release/` - 本番環境

### WordPress設定

`www/secure_html/public/wp/wp-config.php` は機密情報を含むため git 管理外です。
`wp-config-sample.php` を参考に作成してください。

## 主要機能

- **マイページ**: 会員登録、ログイン、履歴確認
- **Webカウンセリング**: オンライン相談
- **REST API**: モバイルアプリ連携
- **FCM**: プッシュ通知 (Firebase Cloud Messaging)
- **WordPress**: ブログ・お知らせ管理

## git管理外ファイル

以下は `.gitignore` で除外されています:

| 対象 | 理由 |
|------|------|
| `core/tmp/` | ログ・セッション |
| `wp-content/uploads/` | ユーザーアップロード |
| `wp-content/cache/` | キャッシュ |
| `wp-content/updraft/` | バックアップ |
| `wp-content/ai1wm-backups/` | 移行バックアップ |
| `wp-config.php` | DB認証情報 |
| `csr/` | SSL証明書 |
