使い方
g++ -o jpegRead_12.exe jpegRead_12.cpp
g++ -o huffmanTest_r7.exe huffmanTest_r7.cpp
jpegRead_12.exe <読みたいjpegファイル>
huffmanTest_r7.exe
231019_JPEG復元.xlsmの起動
ワークシートにあるインストラクションに従う
注意
huffmanTest_r7.cppにバグがあります．8x8_H.jpgをhuffmanTest_r7.exeで読みに行くと，無限ループに入ります．
Ctrl+Cで強制終了して，image.txtの上部64行だけ使ってください．
8x8の白黒画像しか対応していません．
BMPなどをjpegに変換するときは，https://convertio.co/ja/ で処理することをお勧めします．
jpegファイルがコンパクトになります．
量子化テーブルは固定のようなので，大規模なファイルになるとコンパクトにならないかもしれませんが．
