// SPDX-License-Identifier: GPL-2.0-or-later
#pragma once
#include <stdint.h>
#include <stdbool.h>
typedef enum {
    KEY_SOUND_MODE_RANDOM = 0,
    KEY_SOUND_MODE_PIANO  = 1,
} key_sound_mode_t;
void              key_sound_init(void);
void              key_sound_play(uint16_t keycode);
void              key_sound_on_key_release(uint16_t keycode);
void              key_sound_set_all_enabled(bool enabled);
bool              key_sound_get_all_enabled(void);
bool              key_sound_get_key_enabled(void);
bool              key_sound_get_typewriter_enabled(void);
void              key_sound_set_mode(key_sound_mode_t mode);
key_sound_mode_t  key_sound_get_mode(void);
int8_t            key_sound_get_piano_octave(void);
bool              key_sound_piano_octave_up(void);
bool              key_sound_piano_octave_down(void);
#define KEY_SOUND_FLAG_ALL_BIT          (1u << 0)
#define KEY_SOUND_FLAG_KEY_BIT          (1u << 1)
#define KEY_SOUND_FLAG_TYPEWRITER_BIT   (1u << 2)
#define KEY_SOUND_FLAG_PIANO_BIT        (1u << 6)
uint8_t           key_sound_pack_flags(void);
void              key_sound_unpack_flags(uint8_t flags);
