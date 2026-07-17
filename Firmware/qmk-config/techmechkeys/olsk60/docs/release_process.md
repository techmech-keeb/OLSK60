# OLSK60 リリース運用（タグ設計）

OLSK60（v1）公開ファームウェアのリリース手順とタグ運用。

## 概要

- **ビルド CI**（[`build-olsk60-firmware.yml`](../../../../.github/workflows/build-olsk60-firmware.yml)）:
  `Firmware/qmk-config/techmechkeys/olsk60/**` への push / PR で VIA・Vial を自動ビルドし、
  `.uf2` と `olsk60_via.json` を **Artifacts**（保持 14 日）として出力。日常の動作確認用。
- **リリース CI**（[`release-olsk60-firmware.yml`](../../../../.github/workflows/release-olsk60-firmware.yml)）:
  **`v*` タグの push** をトリガーに、上記ビルドを `workflow_call` で再利用してから
  **GitHub Release** を作成し、成果物を恒久 Assets として添付。

リリースはビルド CI を作り直さず**再利用**するため、Artifacts と Release の中身は同一の
ビルド経路（同じ pinned upstream ref）で生成される。

## タグ命名

```
v<MAJOR>.<MINOR>.<PATCH>      例: v1.0.0
```

- セマンティックバージョニング。ファームウェア（このリポジトリの公開版）の版番号。
- 最初の QMK 公開版は `v1.0.0` を推奨。
- タグはリリース対象コミット（検証済みの `main`）に付ける。

## Release Assets（命名）

ビルドワークフローが版ラベル（= タグ名）で命名する。

| ファイル | 用途 |
|---|---|
| `OLSK60_VIA_v<version>.uf2` | VIA / Remap 用ファームウェア |
| `OLSK60_Vial_v<version>.uf2` | Vial 用ファームウェア（定義内蔵） |
| `OLSK60_via_v<version>.json` | VIA / Remap 用キーボード定義 |

リリースノートは [`.github/release-notes/olsk60-public.md`](../../../../.github/release-notes/olsk60-public.md)
を雛形に、`{version}` を置換して本文にする。

## リリース手順

1. 対象コミットを `main` にマージし、**実機検証**（[`hardware_verification_checklist.md`](hardware_verification_checklist.md)）を通す。
2. 必要ならリリースノート雛形を更新する。
3. タグを作成して push する。

   ```sh
   git tag v1.0.0
   git push origin v1.0.0
   ```

4. `release-olsk60-firmware.yml` が起動し、ビルド → GitHub Release 作成まで自動実行。
5. 公開された Release の Assets（`.uf2` / `.json`）を確認する。

> 手動再実行が必要な場合は、ビルドのみ `workflow_dispatch`（version 指定）で確認し、
> 問題なければタグを付け直す。既存タグへ再発行する場合は、いったん Release / タグを
> 削除してから付け直すこと（同名タグの二重発行は避ける）。

## 前提・権限

- リリースジョブは `permissions: contents: write`（同一リポジトリへ Release 作成）。
  追加のシークレットは不要（`GITHUB_TOKEN` で完結。v2 のようなクロスリポジトリ発行はしない）。
- upstream ref はビルドワークフロー内に固定（QMK 本家 / vial-qmk）。更新時は
  ビルドワークフローの `ref` を変更し、CI がグリーンなことを確認してからリリースする。
