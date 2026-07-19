// SPDX-License-Identifier: GPL-2.0-or-later
#include QMK_KEYBOARD_H
#include "olsk60.h"
#include "olsk60_keycodes.h"
#include "key_sound.h"
#include "eeconfig.h"

#define OLSK60_INDICATOR_LED 0
#define OLSK60_UNDERGLOW_LED_START 1
#define OLSK60_UNDERGLOW_LED_COUNT 21
#define OLSK60_BREATHE_INTERVAL_MS 125

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

/* One 4-second, 32-step sine cycle scaled to a +/-6 value modulation. */
static const int8_t indicator_breathe_offsets[] = {
    0, 1, 2, 3, 4, 5, 6, 6, 6, 6, 6, 5, 4, 3, 2, 1,
    0, -1, -2, -3, -4, -5, -6, -6, -6, -6, -6, -5, -4, -3, -2, -1,
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
static uint16_t indicator_breathe_timer;
static uint8_t indicator_breathe_step;

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

static void olsk60_set_indicator(void) {
    const olsk60_indicator_hsv_t color = indicator_colors[indicator_layer];
    int16_t value = color.val + indicator_breathe_offsets[indicator_breathe_step];

    rgblight_sethsv_at(color.hue, color.sat, (uint8_t)value, OLSK60_INDICATOR_LED);
}

void keyboard_post_init_user(void) {
    key_sound_init();
    olsk60_load_sound_config();

    rgblight_enable();
    rgblight_mode(RGBLIGHT_MODE_BREATHING);
    rgblight_set_clipping_range(OLSK60_UNDERGLOW_LED_START, OLSK60_UNDERGLOW_LED_COUNT);
    olsk60_set_indicator();
}

layer_state_t layer_state_set_user(layer_state_t state) {
    indicator_layer = get_highest_layer(state);
    olsk60_set_indicator();
    return state;
}

void housekeeping_task_user(void) {
    if (timer_elapsed(indicator_breathe_timer) >= OLSK60_BREATHE_INTERVAL_MS) {
        indicator_breathe_timer = timer_read();
        indicator_breathe_step = (indicator_breathe_step + 1) % ARRAY_SIZE(indicator_breathe_offsets);
    }

    /* Clipping confines rgblight effects to LEDs 1-21; write LED 0 explicitly. */
    olsk60_set_indicator();
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        key_sound_play(keycode);

        switch (keycode) {
            case ALL_SOUND_TOGGLE:
                key_sound_set_all_enabled(!key_sound_get_all_enabled());
                olsk60_save_sound_config();
                return false;
            case SOUND_MODE_TOGGLE:
                if (key_sound_get_all_enabled()) {
                    key_sound_set_mode(key_sound_get_mode() == KEY_SOUND_MODE_RANDOM ? KEY_SOUND_MODE_PIANO : KEY_SOUND_MODE_RANDOM);
                    olsk60_save_sound_config();
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
