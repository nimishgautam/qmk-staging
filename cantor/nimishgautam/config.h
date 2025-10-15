// Copyright 2022 Nimish Gåtam (@nimishgautam)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

// OS-specific stuff
//#define UNICODE_SELECTED_MODES UNICODE_MODE_MACOS

/* Select hand configuration */
#define MASTER_LEFT

//#define EE_HANDS
//#define SPLIT_LAYER_STATE_ENABLE
//#define SPLIT_MODS_ENABLE


// combo
#define EXTRA_SHORT_COMBOS
#define COMBO_TERM 30
#define COMBO_STRICT_TIMER
#define COMBO_MUST_HOLD_PER_COMBO
#define COMBO_HOLD_TERM 250

//Tapping values
//#define QUICK_TAP_TERM 0
#define TAPPING_TERM 200
#define PERMISSIVE_HOLD_PER_KEY

//flow tap
#define FLOW_TAP_TERM 150

// Try to save some memory
#undef LOCKING_SUPPORT_ENABLE
#undef LOCKING_RESYNC_ENABLE
#define LAYER_STATE_8BIT  //8 layers max


// mouse keys go at an inertial speed
#define MK_KINETIC_SPEED

// If I have a keypress in my defines, I want it to consistently send what it says
// eg #define END_PROCESS C(KC_C) should sent ctl-c and NOT G(KC_C) even when ctl and gui are swapped
#define LEGACY_MAGIC_HANDLING
