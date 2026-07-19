// Copyright 2022 techmech-keeb (@techmech-keeb)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H
#include "olsk60_keycodes.h"

// レイヤー定義
enum layers {
    _BASE,  // 基本レイヤー
    _FN,    // Fn（Enter 保持で有効）
    _RGB,   // RGB / ナビ（Space 保持で有効）
    _EXTRA, // 予備（VIA/Vial 編集用）
};

// PRK 版の VIA_FUNC を QMK のレイヤータップで再現
//   FUNC1: タップ=Enter / 保持=_FN
//   FUNC2: タップ=Space / 保持=_RGB
//   FUNC0(bootloader) は _EXTRA レイヤーの左上（QK_BOOT）に配置
#define FUNC1 LT(_FN, KC_ENT)
#define FUNC2 LT(_RGB, KC_SPC)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* _BASE
     * ,-----------------------------------------------------------------.
     * | Esc| 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | 0 |  Bksp  |
     * | Tab | Q | W | E | R | T | Y | U | I | O | P | [ |  \   |
     * | Ctrl | A | S | D | F | G | H | J | K | L | ; |  Enter  |
     * | Shift | Z | X | C | V | B | N | M | , | . | / | Up | RSft|
     * | Ctrl | GUI | Alt | Space | Fn1 |  Delete  | Fn2 | < | v | > |
     * `-----------------------------------------------------------------'
     */
    [_BASE] = LAYOUT(
        KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC,
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_BSLS,
        KC_LCTL, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_ENT,
        KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_UP,   KC_RSFT,
        KC_LCTL, KC_LGUI, KC_LALT, KC_SPC,  FUNC1,   KC_DEL,  FUNC2,   KC_LEFT, KC_DOWN, KC_RGHT
    ),

    /* _FN */
    [_FN] = LAYOUT(
        KC_GRV,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_BSPC,
        KC_TAB,  KC_F11,  KC_F12,  KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_INS,  KC_O,    KC_PSCR, KC_RBRC, KC_DEL,
        KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC, KC_ENT,
        KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_UP,   KC_RSFT,
        KC_LCTL, KC_LGUI, KC_LALT, KC_SPC,  _______, KC_DEL,  _______, KC_LEFT, KC_DOWN, KC_RGHT
    ),

    /* _RGB */
    [_RGB] = LAYOUT(
        EE_CLR,  OLSK_UG_SPDU, OLSK_UG_SPDD, OLSK_UG_VALU, OLSK_UG_VALD, OLSK_UG_SATU, OLSK_UG_SATD, OLSK_UG_HUEU, OLSK_UG_HUED, OLSK_UG_NEXT, OLSK_UG_PREV, QK_RBT,
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,     KC_LBRC, OLSK_UG_TOG,
        KC_LCTL, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN,  KC_ENT,
        KC_LSFT, ALL_SOUND_TOGGLE, SOUND_MODE_TOGGLE, PIANO_OCTAVE_UP, PIANO_OCTAVE_DOWN, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_PGUP, KC_RSFT,
        KC_LCTL, KC_LGUI, KC_LALT, KC_SPC,  _______, KC_DEL,  _______, KC_HOME, KC_PGDN, KC_END
    ),

    /* _EXTRA（予備・Esc のみ BOOTSEL） */
    [_EXTRA] = LAYOUT(
        QK_BOOT, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
    ),
};
