<?xml version="1.0" encoding="UTF-8"?>

<!-- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 

バックエンドのディレクトリ構成XML
ここにあるディレクトリ内のクラスについては、autoloadで読み込んでくれる
使いたくないクラスディレクトリは、ここでコメントアウトすれば読み込まれなくなる
使わないとしても、ディレクトリ構成把握のためにコメントアウトで残しておくこと
また、各ディレクトリの説明を記載すること

今回の構成は、
最近流行りの
・クラウドサービスとのAPI連携
・スケールアップ・スケールアウト対応の仮想インスタンスクラスタサーバの癖
・オープンソースフレームワーク(今回はcakePHP)の作り
を考慮・参考にして

・APIを念頭に置いた構成(フロントエンドからもAPIのみでのバックエンドアクセスを実現。など)
・MVCモデル構成の明確化
・設定値の、開発環境・本番環境の変更対応
・サードパーティのモジュール・ライブラリを取り込む構成
を実現している

実際に運用する中で新しいことが出てくると思うので、
その都度アップデートを行っていくこと

※ライブラリなどで、特別にincludeが必要な場合は要素「class」に個別指定を行う事

- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -->

<directry>

	<!--
	フロントから直接タッチできる範囲

	APIは、外部(フロントのJSからのAJAX含む)からのアクセス用
	directAccessは、htmlファイル作成処理中から実行される処理用
	とすみ分けを行っている

	API方式(バックエンドへのアクセスをforInternalAPIのみとする)ならAPIディレクトリのみで完結し
	directAccess方式(ユーザがHTMLアクセスした際にバックエンド処理を行う)ならdirectAccessディレクトリのみで完結する
	という流れ

	両方併用しても構わない
	-->
	<application>

		<!--
		applicatoin programming interface
		外部(フロントのJSからのAJAX含む)からの
		アクセス用に用意するインターフェース
		-->
		<API>

			<!--
			外部に公開するAPI
			-->
			<forExternal>

				<!-- コントローラ -->
				<controller>

					<!-- コントローラで処理する中で利用する少単位のモジュール -->
					<component></component>

				</controller>

			</forExternal>

			<!--
			内部に公開するAPI
			※主にフロント側からのAJAXアクセス用
			-->
			<forInternal>

				<!-- コントローラ -->
				<controller>

					<!-- コントローラで処理する中で利用する少単位のモジュール -->
					<component></component>

				</controller>

			</forInternal>

		</API>

		<!--
		ユーザがHTMLアクセスした際に、
		そのまま直接バックエンド処理を行う際のインターフェース
		※この直下には、サービス(ユーザがアクセスするサイト)毎のディレクトリを作成すること
		　例：ショップの購入サイト、運営側が触る管理画面のなら2つ必要
		-->
		<directAccess>

			<!--
			入会画面
			お客様が来店して、ユーザ登録・年会費支払い(カード決済)を行うフォームページ
			-->
			<admission>

				<controller>

					<component></component>

				</controller>

			</admission>

			<!--
			体験入園申し込み画面
			体験入園に行ってみたいと思ってるお客様が申し込みを行うフォームページ
			-->
			<application>

				<controller>

					<component></component>

				</controller>

			</application>

			<!--
			共通パーツ
			複数のサービスで共通で使用するもの用
			-->
			<common>

				<controller>

					<component></component>

				</controller>

			</common>

		</directAccess>

	</application>

	<!--
	configuration
	システム自体の設定を行うところ
	-->
	<conf>

		<!--
		開発・本番環境での設定を行うところ
		-->
		<common></common>

		<!--
		開発環境での設定を行うところ
		-->
		<local></local>

		<!--
		本番環境での設定を行うところ
		-->
		<release></release>

	</conf>

	<!--
	プログラムライブラリ
	function単位の最小処理を纏めて配置するところ
	※libraryはディレクトリ一覧を随時取得してクラス検索対象とするのでコメントアウトする
	<library>
		外部が作成したライブラリを配置するところ
		<thirdParty></thirdParty>
	</library>
	-->

	<!--
	function単位よりもう少し大きいモジュール単位のものを配置するところ
	※moduleはディレクトリ一覧を随時取得してクラス検索対象とするのでコメントアウトする
	<module>
		<thirdParty></thirdParty>
	</module>
	-->

</directry>
