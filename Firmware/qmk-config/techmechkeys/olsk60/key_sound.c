// SPDX-License-Identifier: GPL-2.0-or-later
#include "key_sound.h"
#include QMK_KEYBOARD_H
#include <stdlib.h>

#define MIN_SOUND_INTERVAL   30
#define PIANO_OCTAVE_MIN    -3
#define PIANO_OCTAVE_MAX     3
#define TYPEWRITER_SOUND SONG(E__NOTE(_C6), E__NOTE(_E6), E__NOTE(_G6))
static float typewriter_song[][2] = TYPEWRITER_SOUND;

static bool all_sound_enabled = false;
static bool key_sound_enabled_flag = false;
static bool typewriter_sound_enabled = false;
static bool typewriter_sound_playing = false;
static key_sound_mode_t sound_mode = KEY_SOUND_MODE_RANDOM;
static int8_t piano_octave_offset = 0;
static uint16_t last_sound_time = 0;

static const uint16_t piano_base_freqs_x100[12] = {
    26163, 27718, 29366, 31113, 32963, 34923,
    36999, 39200, 41530, 44000, 46616, 49388
};

static int8_t keycode_to_semitone(uint16_t keycode) {
    switch (keycode) {
        case KC_A:    return 0;
        case KC_W:    return 1;
        case KC_S:    return 2;
        case KC_E:    return 3;
        case KC_D:    return 4;
        case KC_F:    return 5;
        case KC_T:    return 6;
        case KC_G:    return 7;
        case KC_Y:    return 8;
        case KC_H:    return 9;
        case KC_U:    return 10;
        case KC_J:    return 11;
        case KC_K:    return 12;
        case KC_O:    return 13;
        case KC_L:    return 14;
        case KC_P:    return 15;
        case KC_SCLN: return 16;
        default:      return -1;
    }
}

static float piano_freq(int8_t semitone) {
    int16_t total = semitone + piano_octave_offset * 12;
    int8_t note_idx = total % 12;
    if (note_idx < 0) note_idx += 12;
    int8_t octave_shift = (total >= 0) ? (total / 12) : ((total - 11) / 12);
    uint32_t freq_x100 = piano_base_freqs_x100[note_idx];
    if (octave_shift > 0) {
        freq_x100 <<= octave_shift;
    } else if (octave_shift < 0) {
        freq_x100 >>= (-octave_shift);
    }
    return (float)freq_x100 / 100.0f;
}

void key_sound_init(void) {
    all_sound_enabled = false;
    key_sound_enabled_flag = false;
    typewriter_sound_enabled = false;
    typewriter_sound_playing = false;
    sound_mode = KEY_SOUND_MODE_RANDOM;
    piano_octave_offset = 0;
    last_sound_time = 0;
}

void key_sound_play(uint16_t keycode) {
    if (!all_sound_enabled || !key_sound_enabled_flag) return;
    uint16_t current_time = timer_read();
    if (keycode == KC_ENT) {
        if (typewriter_sound_enabled && !typewriter_sound_playing) {
            PLAY_SONG(typewriter_song);
            typewriter_sound_playing = true;
            last_sound_time = current_time;
        }
        return;
    }
    if (timer_elapsed(last_sound_time) <= MIN_SOUND_INTERVAL) return;
    if (sound_mode == KEY_SOUND_MODE_PIANO) {
        int8_t semitone = keycode_to_semitone(keycode);
        if (semitone >= 0) {
            audio_play_note(piano_freq(semitone), 50);
        } else {
            audio_play_note((float)(200 + (rand() % 800)), 50);
        }
    } else {
        audio_play_note((float)(200 + (rand() % 800)), 50);
    }
    last_sound_time = current_time;
}

void key_sound_on_key_release(uint16_t keycode) {
    if (keycode == KC_ENT) {
        typewriter_sound_playing = false;
    }
}

void key_sound_set_all_enabled(bool enabled) {
    all_sound_enabled = enabled;
    key_sound_enabled_flag = enabled;
    typewriter_sound_enabled = enabled;
}
bool key_sound_get_all_enabled(void) { return all_sound_enabled; }
bool key_sound_get_key_enabled(void) { return key_sound_enabled_flag; }
bool key_sound_get_typewriter_enabled(void) { return typewriter_sound_enabled; }

void key_sound_set_mode(key_sound_mode_t mode) {
    sound_mode = mode;
    piano_octave_offset = 0;
}
key_sound_mode_t key_sound_get_mode(void) { return sound_mode; }
int8_t key_sound_get_piano_octave(void) { return piano_octave_offset; }

bool key_sound_piano_octave_up(void) {
    if (sound_mode != KEY_SOUND_MODE_PIANO || piano_octave_offset >= PIANO_OCTAVE_MAX)
        return false;
    piano_octave_offset++;
    return true;
}
bool key_sound_piano_octave_down(void) {
    if (sound_mode != KEY_SOUND_MODE_PIANO || piano_octave_offset <= PIANO_OCTAVE_MIN)
        return false;
    piano_octave_offset--;
    return true;
}

uint8_t key_sound_pack_flags(void) {
    uint8_t flags = 0;
    if (all_sound_enabled)        flags |= KEY_SOUND_FLAG_ALL_BIT;
    if (key_sound_enabled_flag)   flags |= KEY_SOUND_FLAG_KEY_BIT;
    if (typewriter_sound_enabled) flags |= KEY_SOUND_FLAG_TYPEWRITER_BIT;
    if (sound_mode == KEY_SOUND_MODE_PIANO) flags |= KEY_SOUND_FLAG_PIANO_BIT;
    return flags;
}
void key_sound_unpack_flags(uint8_t flags) {
    all_sound_enabled        = (flags & KEY_SOUND_FLAG_ALL_BIT) != 0;
    key_sound_enabled_flag   = (flags & KEY_SOUND_FLAG_KEY_BIT) != 0;
    typewriter_sound_enabled = (flags & KEY_SOUND_FLAG_TYPEWRITER_BIT) != 0;
    sound_mode = (flags & KEY_SOUND_FLAG_PIANO_BIT) ? KEY_SOUND_MODE_PIANO : KEY_SOUND_MODE_RANDOM;
}
