# 85's intermediate environment

85が書いた中プロ用環境です。

## 使い方

    git clone https://github.com/85yago/kyopro-docked.git

gitはなくてもいいです（zipで落として展開すれば良いし、git管理しなくてもよい）が、dockerはOSの合わせたものを導入してください。

git管理しない場合は.gitを消しておいてください。

dockerをvscodeから使うための適切な拡張機能を入れてください。`Remote Development`を落とせば良いです。

その後vscodeでファイルを開いてから、出てきたポップアップか`F1`→`Remote-Containers`からファイルをコンテナで開かせれば良いです。

M1でも動きます。winでも動きます。適当なx11を入れてください。M1だとxquartzの設定で「セキュリティ」の2項目をいい感じにさせてください。winでもいい感じにしてください。

EzGraph使用時には`launch.json`の`preLaunchTask`を`task.json`のezccを使用している方にしてあげてください。
