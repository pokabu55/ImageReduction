# ImageReduction
画像の縮小専用

## 仕様
* NIKONのスマホアプリで、”2Mサイズでスマホに転送” と同じサイズの画像を作って保存する
* フォルダを引数とし、一括処理
* 変換後の画像は、元のフォルダ名＋”_2M” とし、ファイル名は変更しない
* デフォルトのサイズ設定は以下の通り。今の所、それ以外のサイズは受け付けない
* 6000x4000 -> 1620x1080 つまりは、0.27 倍だった
* メタ情報って引き継がれるの？できたら、残したい

## 参考リンク
* [コマンドライン引数の参考](https://www.mm2d.net/main/prog/c/getopt-02.html)

## ソフト開発の中断
* 上記仕様でソフト開発を進めていたが、重大な欠点を見つけてしまった
* 撮影情報を残せないんですよ。OpenCVでは。これは、仕様っぽい。
* で、ググってみたところ、linux定番のコマンドライン画像編集ソフトのImageMagikならばできるって。
* なので、開発を中断し、下記のコマンドで対応することにします。

# imagemagik
* 詳細はどっかでググってね

## 一括縮小コマンド
* [参考１](https://liginc.co.jp/394506)
* [参考２](http://technique.sonots.com/?UNIX%2F%E3%82%B3%E3%83%9E%E3%83%B3%E3%83%89%2F%E5%A4%89%E6%8F%9B%2Fmogrify)

## シェルスクリプト
* 以下の内容のスクリプトを作って、対象ディレクトリで実行すれば、一括で変換できます。

```
#!/bin/sh

echo "start..."
mogrify -resize 27% -quality 100 *.JPG
echo "finished!"

```