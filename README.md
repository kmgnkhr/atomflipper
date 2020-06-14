# Pageflipper for M5Atom lite

## 概要

M5StickCで作ったページめくりデバイスをM5Atomで作り直したもの。  
https://github.com/kmgnkhr/pageflipper

## 操作

Bluetoothのデバイス一覧に"AtomFlipper"という名前で出てくるので接続。

* Btn単押しで CURSOR LEFT  
* Btnダブルクリックで CURSOR RIGHT

電子書籍のマンガ（右綴じ）を読みたいのでFORWARDがLEFTとなります。

## 使用ライブラリ

ESP32-BLE-Keyboard  https://github.com/T-vK/ESP32-BLE-Keyboard

## 感想

ワイヤレスにできるからM5StickCを使ってたけど、すぐにバッテリ切れするので難儀してた。
M5AtomLiteで十分だったんだなあ。（しみじみ）
