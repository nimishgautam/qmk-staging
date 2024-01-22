// Copyright 2022 Nimish Gåtam (@nimishgautam)
// SPDX-License-Identifier: GPL-2.0-or-later

/*
  Set any config.h overrides for your specific keymap here.
  See config.h options at https://docs.qmk.fm/#/config_options?id=the-configh-file
*/

#pragma once

// OS-specific stuff
//#define UNICODE_SELECTED_MODES UC_MAC

// combo
#define COMBO_COUNT 1
#define EXTRA_SHORT_COMBOS

//Tapping values
//#define TAPPING_FORCE_HOLD
#define TAPPING_TERM 200
#define PERMISSIVE_HOLD_PER_KEY

// Try to save some memory
#define NO_ACTION_ONESHOT
#ifndef NO_DEBUG
#define NO_DEBUG
#endif // !NO_DEBUG
#if !defined(NO_PRINT) && !defined(CONSOLE_ENABLE)
#define NO_PRINT
#endif // !NO_PRINT
#undef LOCKING_SUPPORT_ENABLE
#undef LOCKING_RESYNC_ENABLE
#define LAYER_STATE_8BIT  //8 layers max

//autoshift
/*
#define NO_AUTO_SHIFT_NUMERIC
#define NO_AUTO_SHIFT_SPECIAL
#define RETRO_SHIFT 400
#define AUTO_SHIFT_TIMEOUT 175
#define AUTO_SHIFT_ENABLED
#define AUTO_SHIFT_TIMEOUT_PER_KEY
*/


// mouse keys go at a constant speed instead of accelerating
#define MK_3_SPEED
#define MK_MOMENTARY_ACCEL


#define USB_SUSPEND_WAKEUP_DELAY 11
#undef MOUSEKEY_WHEEL_MAX_SPEED
#define MOUSEKEY_WHEEL_MAX_SPEED 3

#undef MOUSEKEY_WHEEL_TIME_TO_MAX
#define MOUSEKEY_WHEEL_TIME_TO_MAX 80

// If I have a keypress in my defines, I want it to consistently send what it says
// eg #define END_PROCESS C(KC_C) should sent ctl-c and NOT G(KC_C) even when ctl and gui are swapped
#define LEGACY_MAGIC_HANDLING