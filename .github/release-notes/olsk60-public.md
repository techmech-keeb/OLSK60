# OLSK60 firmware {version}

OLSK60（v1）向けの QMK ファームウェアです。VIA / Vial に対応しています。

## ダウンロード

このリリースの Assets から、利用する設定ツールに合わせて選んでください。

- **VIA / Remap を使う場合**: `OLSK60_VIA_v{version}.uf2` ＋ `OLSK60_via_v{version}.json`
- **Vial を使う場合**: `OLSK60_Vial_v{version}.uf2`（キーボード定義は内蔵）

## 書き込み方法（UF2）

1. キーボードを PC から取り外します。
2. コントローラ（Adafruit KB2040）の **RESET を素早く 2 回押す**か、
   QMK 書き込み済みの個体は **Esc を押しながら USB 接続**します。
3. `RPI-RP2` ドライブが表示されたら、使用する `.uf2` をルートにコピーします。
4. コピー完了後、自動的に再起動して書き込み完了です。
5. VIA を使う場合は、認識されないときに `OLSK60_via_v{version}.json` を読み込ませてください。

## 注意事項

- 通常利用中に問題がなければ、更新は必須ではありません。
- 更新中は USB ケーブルを抜かないでください。
- VIA / Remap には VIA 用、Vial には Vial 用の UF2 を使用してください。
- JSON は VIA / Remap 用です。Vial では通常不要です。
