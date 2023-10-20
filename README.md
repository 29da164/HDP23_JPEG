# JPEGアナライザ
## コンパイル
### Windows
```
g++ -o jpegRead.exe jpegRead.cpp
```
### Linux
```
g++ -o jpegRead jpegRead.cpp
```
## 実行
### Windows
```
jpegRead.exe <読みたいjpegファイル>
```
### Linux
```
jpegRead <読みたいjpegファイル>
```

# JPEGデコーダ
## コンパイル
### Windows
```
g++ -o huffmanDecoder.exe huffmanDecoder.cpp
```
### Linux
```
g++ -o huffmanDecoder huffmanDecoder.cpp
```
## 実行
### Windows
```
huffmanDecoder.exe
```
### Windows
```
huffmanDecoder
```

# JPEG可視化
231019_JPEG復元.xlsmを起動し，ワークシートにあるインストラクションに従う．

# 注意

huffmanTest_r7.cppにバグがあります．8x8_H.jpgをhuffmanTest_r7.exeで読みに行くと，無限ループに入ります．
Ctrl+Cで強制終了して，image.txtの上部64行だけ使ってください．
8x8の白黒画像しか対応していません．
BMPなどをjpegに変換するときは，https://convertio.co/ja/ で処理することをお勧めします．
jpegファイルがコンパクトになります．
量子化テーブルは固定のようなので，大規模なファイルになるとコンパクトにならないかもしれませんが．
> サンプル jpeg ファイル
```
8x8_A.jpg, 8x8_F.jpeg, 8x8_G.jpg, 8x8_H.jpg
```
