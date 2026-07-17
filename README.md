# OLSK60

OrthoLinear for the Standard Keysets 60%

OLSK60 は 58〜60 キーの 60% キーボードです。アルファ部を格子（オーソリニア）配列に、
モディファイア部を標準キーセット配列にすることで、GMK / ePBT の Base Kit だけで
キーを揃えられます。GH60 互換ケースにネジレス搭載できます。

![OLSK60](https://user-images.githubusercontent.com/88352328/179516853-f877d9fe-37f1-40e3-9d84-a61ef3d8cbfe.JPG)

> **このリポジトリは OLSK60（v1）です。** 現行販売モデルは
> [OLSK60 v2](https://github.com/techmech-keeb/OLSK60_v2)（トラックポイント搭載）です。
> v1 は販売当時 **PRK Firmware + Remap** で動作する仕様でしたが、今回の見直しで
> **QMK（VIA / Vial）** に移行し、ソースを公開しました。

## 特長

- 格子配列 58〜60 キー、60% サイズ
- GMK / ePBT Base Kit のみでキー網羅
- GH60 互換ケース・ネジレス搭載対応
- **QMK ファームウェア**（VIA / Vial / Remap 対応）
- RGB アンダーグロー（WS2812 × 21）

## ハードウェア

| 項目 | 内容 |
|------|------|
| コントローラ | Adafruit KB2040（RP2040 / UF2 ブートローダ） |
| マトリクス | 10 行 × 6 列（`COL2ROW`） |
| RGB | WS2812 アンダーグロー 21 個（GP9） |
| 接続 | USB Type-C（KB2040） |
| キーマップ | 4 レイヤー、VIA / Vial で編集可能 |

## ファームウェア

現行ファームウェアは [`Firmware/qmk-config/`](Firmware/qmk-config/) にあります
（QMK 本体の外部でキーボード定義のみを管理するアウトオブツリー構成）。
旧版の PRK Firmware は参照用に [`Firmware/legacy/`](Firmware/legacy/) に保管しています
（現在は使用しません）。

### ビルド

QMK 本体（VIA は `qmk/qmk_firmware`、Vial は `vial-kb/vial-qmk`）を取得し、
`Firmware/qmk-config/techmechkeys/olsk60` を `keyboards/techmechkeys/olsk60` に
配置してビルドします。

```sh
qmk compile -kb techmechkeys/olsk60 -km via    # VIA 版（qmk_firmware ツリー）
qmk compile -kb techmechkeys/olsk60 -km vial   # Vial 版（vial-qmk ツリー）
```

GitHub Actions（[`.github/workflows/build-olsk60-firmware.yml`](.github/workflows/build-olsk60-firmware.yml)）
でも VIA / Vial の両方を自動ビルドし、`.uf2` を Artifacts として出力します。

### 書き込み（UF2）

1. キーボードを未接続の状態にする。
2. KB2040 の **RESET を素早く 2 回押す**（またはブート状態で USB 接続する）。
   QMK 書き込み後の個体は **Esc を押しながら接続**（bootmagic）でも起動できます。
3. `RPI-RP2` ドライブが表示される。
4. VIA 用または Vial 用の `.uf2` をドライブのルートにコピーする。
5. 自動的に再起動し、書き込み完了。
6. VIA 版は `olsk60_via.json` を VIA に読み込ませて使用します。Vial 版は定義内蔵です。

### リリース

`v*` タグ（例 `v1.0.0`）を push すると、
[`release-olsk60-firmware.yml`](.github/workflows/release-olsk60-firmware.yml) が
VIA / Vial をビルドして GitHub Release を作成し、`.uf2` と `olsk60_via.json` を添付します。
詳細は [リリース運用](Firmware/qmk-config/techmechkeys/olsk60/docs/release_process.md) を参照。

### ドキュメント

- [マトリクス / キーマップ対応表](Firmware/qmk-config/techmechkeys/olsk60/docs/matrix_keymap_map.md)
- [実機検証チェックリスト](Firmware/qmk-config/techmechkeys/olsk60/docs/hardware_verification_checklist.md)
- [リリース運用（タグ設計）](Firmware/qmk-config/techmechkeys/olsk60/docs/release_process.md)

## ディレクトリ構成

```text
OLSK60/
├─ Firmware/
│  ├─ qmk-config/            # 現行 QMK（VIA / Vial）ファームウェア
│  │  └─ techmechkeys/olsk60/
│  └─ legacy/                # 旧 PRK Firmware（参照用・使用しない）
│     └─ PRK_Firmware/
└─ .github/workflows/        # ビルド CI
```

## ライセンス

- 本リポジトリのハードウェアデータ・ドキュメントは [MIT License](LICENSE)。
- `Firmware/qmk-config/` 配下の QMK ファームウェアソースは、QMK の要件に従い
  **GPL-2.0-or-later**（各ファイルの SPDX ヘッダを参照）。
