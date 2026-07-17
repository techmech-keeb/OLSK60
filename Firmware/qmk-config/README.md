# qmk-config (現行ファームウェア)

OLSK60 の現行ファームウェア（VIA / Vial 対応の QMK 構成）を格納します。
ソース管理方式は `qmk-config` リポジトリの構成を踏襲し、QMK 本体の外部で
キーボード定義のみを管理します（アウトオブツリー・ビルド）。

## 構成

```text
qmk-config/
└─ techmechkeys/olsk60/          # QMK ネイティブパス: keyboards/techmechkeys/olsk60
   ├─ keyboard.json              # ハードウェア定義（KB2040 / RP2040・マトリクス・RGB・LAYOUT）
   ├─ config.h                   # レイヤー数・RP2040 起動安定化
   ├─ olsk60_via.json            # VIA 用キーボード定義（配布用）
   ├─ keymaps/
   │  ├─ default/                # ビルド確認用のデフォルトキーマップ
   │  ├─ via/                    # VIA 対応（Remap 互換）
   │  └─ vial/                   # Vial 対応（定義内蔵）
   └─ docs/
      └─ matrix_keymap_map.md    # スイッチ↔マトリクス↔キーコード対応表
```

## ハードウェア要点

| 項目 | 値 |
|------|-----|
| コントローラ | Adafruit KB2040（RP2040, UF2 ブートローダ） |
| USB VID / PID | `0x84E9` / `0x7960` |
| マトリクス | 10 行 × 6 列（`COL2ROW`） |
| 行ピン | GP29, GP28, GP27, GP26, GP18, GP0, GP1, GP2, GP3, GP4 |
| 列ピン | GP10, GP19, GP20, GP5, GP7, GP8 |
| RGB | WS2812 アンダーグロー GP9 / 21 個 |
| レイヤー | 4（VIA / Vial で編集可能） |

## ビルド

QMK 本体（VIA は `qmk/qmk_firmware`、Vial は `vial-kb/vial-qmk`）を取得し、
`techmechkeys/olsk60` を `keyboards/techmechkeys/olsk60` に配置してビルドします。

```sh
# 例（VIA 版）
qmk compile -kb techmechkeys/olsk60 -km via
# 例（Vial 版・vial-qmk ツリーで）
qmk compile -kb techmechkeys/olsk60 -km vial
```

CI（GitHub Actions）でも VIA / Vial の両方を自動ビルドします
（[`.github/workflows/build-olsk60-firmware.yml`](../../.github/workflows/build-olsk60-firmware.yml)）。

> 旧版（PRK Firmware）は [`../legacy/`](../legacy/) を参照。
