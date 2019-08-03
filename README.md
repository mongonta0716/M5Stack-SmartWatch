# M5Stack-SmartWatch
 M5Stack SmartWatch with pcf8523
 RTC(Realtime Time Clock)を接続したM5Stack用のスマートウォッチアプリです。

# ハードウェア(Hardware)
- Adafruit PCF8523

# 使い方(Usage)

buildフォルダ配下にあるM5SmartWatch.bin,jpgフォルダ,jsonフォルダをmicroSDカードのルート上にコピーして、
[M5Stack LovyanLauncher](https://github.com/lovyan03/M5Stack_LovyanLauncher)から起動します。

LovyanLauncherの詳しい使い方は下記のブログにて解説しています。

[M5Stack LovyanLauncherの使い方｜ラズパイ好きの日記](https://raspberrypi.mongonta.com/howto-use-m5stack-lovyanlauncher/)

## 注意事項(Notice)
まだ、日付と時間を表示するだけのテスト版のためソースのみの公開です。
これから随時機能アップしていこうと思います。

# 必要なライブラリ(Requirement)
コンパイルする場合は、以下のライブラリが必要です。
どちらもArduinoIDEのライブラリマネージャーから追加できます。
- [M5Stack-SD-Updater](https://github.com/tobozo/M5Stack-SD-Updater/)
- [RTClib](https://github.com/adafruit/RTClib)

# Licence
[MIT](https://github.com/mongonta0716/M5Stack-Smartwatch/blob/master/LICENSE)

# Author
[Takao Akaki](https://twitter.com/mongonta555)

