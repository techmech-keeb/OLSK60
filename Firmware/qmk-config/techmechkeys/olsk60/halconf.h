// SPDX-License-Identifier: GPL-2.0-or-later
#pragma once

// Enable the RP2040 PWM peripheral used by the GP6 speaker output.
#define HAL_USE_PWM TRUE

#include_next <halconf.h>
