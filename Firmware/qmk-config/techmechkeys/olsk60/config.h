// Copyright 2022 techmech-keeb (@techmech-keeb)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

// VIA / Vial で編集可能なレイヤー数（4レイヤー）
#define DYNAMIC_KEYMAP_LAYER_COUNT 4

// Adafruit KB2040 (RP2040) の外部発振子の起動安定化
#define PICO_XOSC_STARTUP_DELAY_MULTIPLIER 64

// アンダーグロー用キーコード名の互換
//   新しい QMK 本家では RGB_* が UG_* に改名された。vial-qmk など旧ベースは
//   まだ RGB_* を使う。両ツリーでビルドできるよう中立名 OLSK_UG_* を定義し、
//   keymap.c ではこちらを使う。分岐は vial-qmk の目印 VIAL_ENABLE で行う。
#ifdef VIAL_ENABLE
#    define OLSK_UG_TOG  RGB_TOG
#    define OLSK_UG_NEXT RGB_MOD
#    define OLSK_UG_PREV RGB_RMOD
#    define OLSK_UG_HUEU RGB_HUI
#    define OLSK_UG_HUED RGB_HUD
#    define OLSK_UG_SATU RGB_SAI
#    define OLSK_UG_SATD RGB_SAD
#    define OLSK_UG_VALU RGB_VAI
#    define OLSK_UG_VALD RGB_VAD
#    define OLSK_UG_SPDU RGB_SPI
#    define OLSK_UG_SPDD RGB_SPD
#else
#    define OLSK_UG_TOG  UG_TOGG
#    define OLSK_UG_NEXT UG_NEXT
#    define OLSK_UG_PREV UG_PREV
#    define OLSK_UG_HUEU UG_HUEU
#    define OLSK_UG_HUED UG_HUED
#    define OLSK_UG_SATU UG_SATU
#    define OLSK_UG_SATD UG_SATD
#    define OLSK_UG_VALU UG_VALU
#    define OLSK_UG_VALD UG_VALD
#    define OLSK_UG_SPDU UG_SPDU
#    define OLSK_UG_SPDD UG_SPDD
#endif

#ifdef AUDIO_ENABLE
#    define AUDIO_PIN GP6
#    define AUDIO_PWM_DRIVER PWMD3
#    define AUDIO_PWM_CHANNEL RP2040_PWM_CHANNEL_A
#    define AUDIO_INIT_DELAY
#    define STARTUP_SONG SONG(NO_SOUND)
#endif

// サウンドフラグの EEPROM 保存用（user datablock）
#define EECONFIG_USER_DATA_SIZE 4
