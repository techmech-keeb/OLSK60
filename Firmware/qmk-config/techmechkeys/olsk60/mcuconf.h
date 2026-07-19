// SPDX-License-Identifier: GPL-2.0-or-later
#pragma once

#include_next <mcuconf.h>

// GP6 is driven by RP2040 PWM slice 3, channel A.
#undef RP_PWM_USE_PWM3
#define RP_PWM_USE_PWM3 TRUE
