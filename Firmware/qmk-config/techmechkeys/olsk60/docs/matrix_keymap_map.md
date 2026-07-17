# OLSK60 v1 マトリクス / キーマップ対応表

回路図（マトリクス）・KB2040 ピンアウト・旧 PRK ソース（`keymap.rb` /
`via_map.txt`）・`OLSK60_via.json` の4点を突き合わせて作成した、
スイッチ ↔ 電気マトリクス ↔ キーコードの対応表。実機デバッグの基準に使う。

## 座標系

- **電気マトリクス（QMK 配線）**: 10 行 × 6 列（`COL2ROW`）。
  - 行 `r0–r9` → `GP29, GP28, GP27, GP26, GP18, GP0, GP1, GP2, GP3, GP4`
  - 列 `c0–c5` → `GP10, GP19, GP20, GP5, GP7, GP8`
- 物理 1 行 = 左バンク `RowN` ＋ 右バンク `Row(N+5)`（列 `Col0–Col5` は両バンク共有）。

## スイッチ ↔ マトリクス（回路図由来）

左バンク（Row0–4）:

| | Col0 | Col1 | Col2 | Col3 | Col4 | Col5 |
|---|---|---|---|---|---|---|
|Row0| SW1 | SW6 | SW11 | SW16 | SW21 | SW26 |
|Row1| SW2 | SW7 | SW12 | SW17 | SW22 | SW27 |
|Row2| SW3 | SW8 | SW13 | SW18 | SW23 | SW28 |
|Row3| SW4 | SW9 | SW14 | SW19 | SW24 | SW29 |
|Row4| SW5 | SW10 | SW15 | SW20 | SW25 | SW30 |

右バンク（Row5–9、回路図では Col5→Col0 の順で左右反転配置）:

| | Col0 | Col1 | Col2 | Col3 | Col4 | Col5 |
|---|---|---|---|---|---|---|
|Row5| SW56 | SW51 | SW46 | SW41 | SW36 | SW31 |
|Row6| SW57 | SW52 | SW47 | SW42 | SW37 | SW32 |
|Row7| SW58 | SW53 | SW48 | SW43 | SW38 | SW33 |
|Row8| SW59 | SW54 | SW49 | SW44 | SW39 | SW34 |
|Row9| SW60 | SW55 | SW50 | SW45 | SW40 | SW35 |

## 全 60 キー対応（L0=デフォルト）

`#` は VIA/Vial の配列上の並び順（旧 PRK `via_map.txt` と同順）。

| # | SW | 電気[Row,Col] | サイズ | L0 | L1(Fn) | L2(RGB) |
|--:|:--:|:--:|:--:|:--|:--|:--|
|1|SW1|0,0|1|Esc|`` ` ``|QK_BOOT|
|2|SW6|0,1|1|1|F1|RGB_SPI|
|3|SW11|0,2|1|2|F2|RGB_SPD|
|4|SW16|0,3|1|3|F3|RGB_VAI|
|5|SW21|0,4|1|4|F4|RGB_VAD|
|6|SW26|0,5|1|5|F5|RGB_SAI|
|7|SW31|5,5|1|6|F6|RGB_SAD|
|8|SW36|5,4|1|7|F7|RGB_HUI|
|9|SW41|5,3|1|8|F8|RGB_HUD|
|10|SW46|5,2|1|9|F9|RGB_MOD|
|11|SW51|5,1|1|0|F10|RGB_RMOD|
|12|SW56|5,0|2|Bksp|Bksp|RGB_TOG|
|13|SW2|1,0|1.5|Tab|Tab|Tab|
|14|SW7|1,1|1|Q|F11|Q|
|15|SW12|1,2|1|W|F12|W|
|16|SW17|1,3|1|E|E|E|
|17|SW22|1,4|1|R|R|R|
|18|SW27|1,5|1|T|T|T|
|19|SW32|6,5|1|Y|Y|Y|
|20|SW37|6,4|1|U|U|U|
|21|SW42|6,3|1|I|Insert|I|
|22|SW47|6,2|1|O|O|O|
|23|SW52|6,1|1|P|PrtSc|P|
|24|SW57|6,0|1|[|]|[|
|25|SW60|9,0|1.5|\\ (BCSL)|Delete|\\|
|26|SW3|2,0|1.75|LCtrl|CapsLock|LCtrl|
|27|SW8|2,1|1|A|A|A|
|28|SW13|2,2|1|S|S|S|
|29|SW18|2,3|1|D|D|D|
|30|SW23|2,4|1|F|F|F|
|31|SW28|2,5|1|G|G|G|
|32|SW33|7,5|1|H|H|H|
|33|SW38|7,4|1|J|- (Minus)|J|
|34|SW43|7,3|1|K|= (Equal)|K|
|35|SW48|7,2|1|L|[|L|
|36|SW53|7,1|1|;|]|;|
|37|SW58|7,0|2.25|Enter|Enter|Enter|
|38|SW4|3,0|1.75|LShift|LShift|LShift|
|39|SW9|3,1|1|Z|Z|Z|
|40|SW14|3,2|1|X|X|X|
|41|SW19|3,3|1|C|C|C|
|42|SW24|3,4|1|V|V|V|
|43|SW29|3,5|1|B|B|B|
|44|SW34|8,5|1|N|N|N|
|45|SW39|8,4|1|M|M|M|
|46|SW44|8,3|1|,|,|,|
|47|SW49|8,2|1|.|.|.|
|48|SW54|8,1|1|/|/|/|
|49|SW59|8,0|1|Up|Up|PgUp|
|50|SW55|9,1|1.25|RShift|RShift|RShift|
|51|SW5|4,0|1.25|LCtrl|LCtrl|LCtrl|
|52|SW10|4,1|1.25|LGUI|LGUI|LGUI|
|53|SW15|4,2|1.25|LAlt|LAlt|LAlt|
|54|SW20|4,3|2.25|Space|Space|Space|
|55|SW25|4,4|1.25|Fn1 = LT(_FN, Enter)|(透過)|(透過)|
|56|SW30|4,5|2.75|Delete|Delete|Delete|
|57|SW35|9,5|1|Fn2 = LT(_RGB, Space)|(透過)|(透過)|
|58|SW40|9,4|1|Left|Left|Home|
|59|SW45|9,3|1|Down|Down|PgDn|
|60|SW50|9,2|1|Right|Right|End|

## 旧 PRK からの変更点・メモ

- **L2 の #44/#45**: 旧 `via_map.txt` では `N→NumLock` / `M→N` と 1 つずれていた
  （PRK 側の打ち間違いと判断）。本ファームでは `#44=N` / `#45=M` に修正済み。
- **レイヤー数**: 旧 PRK は 3。本ファームは 4（`_BASE` / `_FN` / `_RGB` / `_EXTRA`）。
  `_EXTRA` は予備で全透過。
- **FUNC キー**: 旧 `VIA_FUNC0`=BOOTSEL は `QK_BOOT`（L2 左上）に、
  `VIA_FUNC1`=Enter/Layer1 は `LT(_FN, KC_ENT)`、`VIA_FUNC2`=Space/Layer2 は
  `LT(_RGB, KC_SPC)` に置換。
- **6.25U スペース option（SW25-1）**: 電気的に Fn1 ノード（`4,4`）を共有。
  現状は分割スペース版の LAYOUT のみ定義。1 本バージョンのプレートを標準化する
  場合は別途 LAYOUT / キーマップ変種を検討する。
- 上記の割り当て（特に最下段・矢印まわり）は**実機デバッグで最終確認する**。
