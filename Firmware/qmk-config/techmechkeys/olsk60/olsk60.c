// SPDX-License-Identifier: GPL-2.0-or-later
#include QMK_KEYBOARD_H
#include "olsk60.h"
#include "olsk60_keycodes.h"
#include "key_sound.h"
#include "eeconfig.h"

#define OLSK60_INDICATOR_LED 0
#define OLSK60_UNDERGLOW_LED_START 1
#define OLSK60_UNDERGLOW_LED_COUNT 21
#define OLSK60_BREATHE_PERIOD_MS 3000
#define OLSK60_BASE_VAL_MIN 3
#define OLSK60_BASE_VAL_MAX 45
#define OLSK60_LAYER_VAL_MIN 5
#define OLSK60_LAYER_VAL_MAX 47
#define OLSK60_BLINK_ON_MS 60
#define OLSK60_BLINK_OFF_MS 40
#define OLSK60_BLINK_VAL 128

typedef struct {
    uint8_t hue;
    uint8_t sat;
    uint8_t val;
} olsk60_indicator_hsv_t;

static const olsk60_indicator_hsv_t indicator_colors[] = {
    [_BASE]  = {0,   0,   13},
    [_FN]    = {120, 255, 26},
    [_RGB]   = {85,  255, 26},
    [_EXTRA] = {170, 255, 26},
};

typedef struct {
    uint8_t magic;
    uint8_t version;
    uint8_t sound_flags;
    uint8_t reserved;
} olsk60_user_config_t;

_Static_assert(sizeof(olsk60_user_config_t) == EECONFIG_USER_DATA_SIZE, "size");

#define OLSK60_CFG_MAGIC 0xA5
#define OLSK60_CFG_VER   0x01

static uint8_t indicator_layer = _BASE;
static uint8_t indicator_last_val = UINT8_MAX;
static uint16_t indicator_blink_timer;
static uint8_t indicator_blink_pulses;
static bool indicator_blink_on;
static hsv_t indicator_blink_color;

static void olsk60_save_sound_config(void) {
    const olsk60_user_config_t config = {
        .magic = OLSK60_CFG_MAGIC,
        .version = OLSK60_CFG_VER,
        .sound_flags = key_sound_pack_flags(),
        .reserved = 0,
    };

    eeconfig_update_user_datablock(&config, 0, sizeof(config));
}

static void olsk60_load_sound_config(void) {
    olsk60_user_config_t config;

    eeconfig_read_user_datablock(&config, 0, sizeof(config));
    if (config.magic == OLSK60_CFG_MAGIC && config.version == OLSK60_CFG_VER) {
        key_sound_unpack_flags(config.sound_flags);
    }
}

static uint8_t olsk60_indicator_value(void) {
    const olsk60_indicator_hsv_t color = indicator_colors[indicator_layer];
    const uint8_t min = indicator_layer == _BASE ? OLSK60_BASE_VAL_MIN : OLSK60_LAYER_VAL_MIN;
    const uint8_t max = indicator_layer == _BASE ? OLSK60_BASE_VAL_MAX : OLSK60_LAYER_VAL_MAX;
    const uint8_t phase = (uint32_t)timer_read32() * 256 / OLSK60_BREATHE_PERIOD_MS;

    /* QMK's 8-bit sine keeps the phase continuous while retaining integer math. */
    return min + ((uint16_t)(max - min) * sin8(phase)) / UINT8_MAX;
}

static void olsk60_set_indicator(void) {
    const olsk60_indicator_hsv_t color = indicator_colors[indicator_layer];
    const uint8_t value = olsk60_indicator_value();

    indicator_last_val = value;
    rgblight_sethsv_at(color.hue, color.sat, value, OLSK60_INDICATOR_LED);
}

static void olsk60_start_indicator_blink(hsv_t color, uint8_t pulses) {
    indicator_blink_color = color;
    indicator_blink_pulses = pulses;
    indicator_blink_on = true;
    indicator_blink_timer = timer_read();
    rgblight_sethsv_at(color.h, color.s, OLSK60_BLINK_VAL, OLSK60_INDICATOR_LED);
}

void keyboard_post_init_user(void) {
    key_sound_init();
    olsk60_load_sound_config();

    rgblight_enable();
    /*
     * Effect range preserves physical LED numbering: rgblight animations use
     * LEDs 1-21 while rgblight_sethsv_at(..., 0) writes physical LED 0.
     * Do not use clipping here; clipping remaps logical indices before output.
     */
    rgblight_set_effect_range(OLSK60_UNDERGLOW_LED_START, OLSK60_UNDERGLOW_LED_COUNT);
    olsk60_set_indicator();
}

layer_state_t layer_state_set_user(layer_state_t state) {
    indicator_layer = get_highest_layer(state);
    olsk60_set_indicator();
    return state;
}

void housekeeping_task_user(void) {
    if (indicator_blink_pulses) {
        if (timer_elapsed(indicator_blink_timer) >= (indicator_blink_on ? OLSK60_BLINK_ON_MS : OLSK60_BLINK_OFF_MS)) {
            indicator_blink_timer = timer_read();
            if (indicator_blink_on) {
                indicator_blink_on = false;
                rgblight_sethsv_at(0, 0, 0, OLSK60_INDICATOR_LED);
            } else if (--indicator_blink_pulses) {
                indicator_blink_on = true;
                rgblight_sethsv_at(indicator_blink_color.h, indicator_blink_color.s, OLSK60_BLINK_VAL, OLSK60_INDICATOR_LED);
            } else {
                olsk60_set_indicator();
            }
        }
        return;
    }

    const uint8_t value = olsk60_indicator_value();
    if (value != indicator_last_val) {
        olsk60_set_indicator();
    }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        key_sound_play(keycode);

        switch (keycode) {
            case ALL_SOUND_TOGGLE:
                key_sound_set_all_enabled(!key_sound_get_all_enabled());
                olsk60_save_sound_config();
                olsk60_start_indicator_blink((hsv_t){key_sound_get_all_enabled() ? 85 : 0, 255, OLSK60_BLINK_VAL}, 2);
                return false;
            case SOUND_MODE_TOGGLE:
                if (key_sound_get_all_enabled()) {
                    key_sound_set_mode(key_sound_get_mode() == KEY_SOUND_MODE_RANDOM ? KEY_SOUND_MODE_PIANO : KEY_SOUND_MODE_RANDOM);
                    olsk60_save_sound_config();
                    olsk60_start_indicator_blink((hsv_t){key_sound_get_mode() == KEY_SOUND_MODE_PIANO ? 170 : 43, 255, OLSK60_BLINK_VAL}, 2);
                }
                return false;
            case PIANO_OCTAVE_UP:
                key_sound_piano_octave_up();
                return false;
            case PIANO_OCTAVE_DOWN:
                key_sound_piano_octave_down();
                return false;
        }
    } else {
        key_sound_on_key_release(keycode);
    }

    return true;
}
