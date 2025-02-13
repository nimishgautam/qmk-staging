// Copyright 2022 Nimish Gåtam (@nimishgautam)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

// OS-specific stuff
//#define UNICODE_SELECTED_MODES UNICODE_MODE_MACOS

/* Select hand configuration */
#define MASTER_LEFT
//#define MASTER_RIGHT
// #define EE_HANDS

//for split
#define RGB_MATRIX_SPLIT \
        { 27, 27 }
#define SPLIT_TRANSPORT_MIRROR


#define OLED_FONT_H "users/nimishgautam/lib/no-logo-2x-symb.c"
#define OLED_FONT_SUPER_DIGG

// oled the stupid way around, ie on the non-primary side
#define OLED_STUPID_WAY_AROUND

#ifdef OLED_STUPID_WAY_AROUND
// send all this stuff over to the oled
#define SPLIT_LAYER_STATE_ENABLE
#define SPLIT_LED_STATE_ENABLE
#define SPLIT_MODS_ENABLE
#define SPLIT_WPM_ENABLE
#define SPLIT_TRANSACTION_IDS_USER SYNC_KEYMAP, SYNC_MAGIC_CASE, SYNC_AUTO_MOUSE
#endif

//for audio
#define AUDIO_ENABLE_TONE_MULTIPLEXING
#define AUDIO_TONE_MULTIPLEXING_RATE_DEFAULT 10

// combo
//#define EXTRA_SHORT_COMBOS
#define COMBO_TERM 30
#define COMBO_STRICT_TIMER
#define COMBO_MUST_HOLD_PER_COMBO
//#define COMBO_TERM_PER_COMBO


//Tapping values
//#define QUICK_TAP_TERM 0
#define TAPPING_TERM 200
#define PERMISSIVE_HOLD_PER_KEY


// Try to save some memory
//#define NO_ACTION_ONESHOT
#undef LOCKING_SUPPORT_ENABLE
#undef LOCKING_RESYNC_ENABLE
//#define LAYER_STATE_8BIT  //8 layers max

// which lighting effects to include (less saves memory)
#ifdef RGBLIGHT_ENABLE
    #define RGBLIGHT_EFFECT_BREATHING
    #define RGBLIGHT_EFFECT_RAINBOW_MOOD
    #define RGBLIGHT_EFFECT_RAINBOW_SWIRL
    #define RGBLIGHT_EFFECT_SNAKE   #define RGBLIGHT_DISABLE_KEYCODES
    #define RGBLIGHT_EFFECT_KNIGHT
    #define RGBLIGHT_EFFECT_CHRISTMAS
    #define RGBLIGHT_EFFECT_STATIC_GRADIENT
    #define RGBLIGHT_EFFECT_RGB_TEST
    #define RGBLIGHT_EFFECT_ALTERNATING
    #define RGBLIGHT_EFFECT_TWINKLE
    #define RGBLIGHT_LIMIT_VAL 120
    #define RGBLIGHT_HUE_STEP 10
    #define RGBLIGHT_SAT_STEP 17
    #define RGBLIGHT_VAL_STEP 17

#endif

// set things matrix-centric
#define RGBLIGHT_DISABLE_KEYCODES

// rgb matrix, cooler effects than lighting above
#ifdef RGB_MATRIX_ENABLE
    #define RGB_MATRIX_KEYPRESSES
    #define RGB_MATRIX_FRAMEBUFFER_EFFECTS
    #define RGB_MATRIX_MAXIMUM_BRIGHTNESS 150
    #define RGB_MATRIX_HUE_STEP 8
    #define RGB_MATRIX_SAT_STEP 8
    #define RGB_MATRIX_VAL_STEP 8
    #define RGB_MATRIX_SPD_STEP 10
    #define RGB_DISABLE_WHEN_USB_SUSPENDED // turn off effects when suspended
    #define RGB_MATRIX_LED_PROCESS_LIMIT (RGB_MATRIX_LED_COUNT + 4) / 5 // limits the number of LEDs to process in an animation per task run (increases keyboard responsiveness)
    #define RGB_MATRIX_LED_FLUSH_LIMIT 16 // limits in milliseconds how frequently an animation will update the LEDs. 16 (16ms) is equivalent to limiting to 60fps (increases keyboard responsiveness)

    // look like The Matrix (white and green) colors randomly dropping
    #define ENABLE_RGB_MATRIX_DIGITAL_RAIN 

    // solid color splashing out from a central area
    // eg if the background color is blue, blue colors 'splashing' out from center
    // this variant only supports 1*color at a time
    #define ENABLE_RGB_MATRIX_SOLID_SPLASH 

    // same as above but multiple splashes can be happening at the same time
    #define ENABLE_RGB_MATRIX_SOLID_MULTISPLASH

    // multicolor 'splash' (simpler)
    #define ENABLE_RGB_MATRIX_SPLASH 
    #define ENABLE_RGB_MATRIX_MULTISPLASH 

    #define ENABLE_RGB_MATRIX_SOLID_REACTIVE_CROSS

    // Really pretty single-color going off randomly like a river
    #define ENABLE_RGB_MATRIX_RIVERFLOW

    #define ENABLE_RGB_MATRIX_HUE_PENDULUM

    #define ENABLE_RGB_MATRIX_HUE_BREATHING

    #define ENABLE_RGB_MATRIX_BAND_SPIRAL_SAT

    // heatmap of typing
    #define ENABLE_RGB_MATRIX_TYPING_HEATMAP

    // Fractal patterns going out from the middle
    #define ENABLE_RGB_MATRIX_PIXEL_FRACTAL

    // patterns moving along the LED wire line
    #define ENABLE_RGB_MATRIX_PIXEL_FLOW

    // radiating rainbow pinwheel
    #define ENABLE_RGB_MATRIX_RAINBOW_PINWHEELS

    // randomly twinkle (vary brightness) but vary hue (actual color) as well
    #define ENABLE_RGB_MATRIX_STARLIGHT_DUAL_HUE

    // randomly twinkle (vary brightness) but vary saturation (how strong that color is) as well
    #define ENABLE_RGB_MATRIX_STARLIGHT_DUAL_SAT

    // (single) keypress goes out in saturation and value on a nexus
    #define ENABLE_RGB_MATRIX_SOLID_REACTIVE_NEXUS


#endif

//autoshift
/*
#define NO_AUTO_SHIFT_NUMERIC
#define NO_AUTO_SHIFT_SPECIAL
#define RETRO_SHIFT 400
#define AUTO_SHIFT_TIMEOUT 175
#define AUTO_SHIFT_ENABLED
#define AUTO_SHIFT_TIMEOUT_PER_KEY
*/

// mouse keys go at an inertial speed
#define MK_KINETIC_SPEED
#define POINTING_DEVICE_AUTO_MOUSE_ENABLE
#define AUTO_MOUSE_TIME 1500

#ifdef RGB_MATRIX_ENABLE
#define RGB_MOUSE_MODE RGB_MATRIX_RAINBOW_PINWHEELS
#define RGB_MODS_MODE RGB_MATRIX_RIVERFLOW
#define RGB_TXT_MODE RGB_MATRIX_HUE_PENDULUM
#define RGB_NUMS_MODE RGB_MATRIX_HUE_BREATHING
#define RGB_FN_MODE RGB_MATRIX_PIXEL_FRACTAL
#define RGB_TERM_MODE RGB_MATRIX_BAND_SPIRAL_SAT
#define RGB_AUTH_MODE RGB_MATRIX_RAINBOW_PINWHEELS
#endif

// If I have a keypress in my defines, I want it to consistently send what it says
// eg #define END_PROCESS C(KC_C) should sent ctl-c and NOT G(KC_C) even when ctl and gui are swapped
#define LEGACY_MAGIC_HANDLING

// music

#define MARIO_CAVE_1                                                                                        \
    E__NOTE(_C5), E__NOTE(_REST), E__NOTE(_C5), E__NOTE(_REST), E__NOTE(_A4), E__NOTE(_REST), E__NOTE(_A4), \
        E__NOTE(_REST), E__NOTE(_AS4), E__NOTE(_REST), E__NOTE(_AS4), E__NOTE(_REST)

#define MARIO_THEME_U \
    Q__NOTE(_E5), \
    H__NOTE(_E5), \
    H__NOTE(_E5), \
    Q__NOTE(_C5), \
    H__NOTE(_E5), \
    W__NOTE(_G5), \
    Q__NOTE(_G4),

#define MARIO_GAMEOVER_U \
    HD_NOTE(_C5 ), \
    HD_NOTE(_G4 ), \
    H__NOTE(_E4 ), \
    H__NOTE(_A4 ), \
    H__NOTE(_B4 ), \
    H__NOTE(_A4 ), \
    H__NOTE(_AF4), \
    H__NOTE(_BF4), \
    H__NOTE(_AF4), \
    WD_NOTE(_G4 ),

#define ONE_UP_SOUND_U \
    Q__NOTE(_E6  ),  \
    Q__NOTE(_G6  ),  \
    Q__NOTE(_E7  ),  \
    Q__NOTE(_C7  ),  \
    Q__NOTE(_D7  ),  \
    Q__NOTE(_G7  ),

#define IMPERIAL_MARCH_U \
  HD_NOTE(_A4), HD_NOTE(_A4), HD_NOTE(_A4), QD_NOTE(_F4), QD_NOTE(_C5), \
  HD_NOTE(_A4), QD_NOTE(_F4),  QD_NOTE(_C5), WD_NOTE(_A4), \
  HD_NOTE(_E5), HD_NOTE(_E5), HD_NOTE(_E5), QD_NOTE(_F5), QD_NOTE(_C5), \
  HD_NOTE(_A4), QD_NOTE(_F4),  QD_NOTE(_C5), WD_NOTE(_A4)

#undef STARTUP_SONG
#define STARTUP_SONG SONG(NO_SOUND)
#define GOODBYE_SONG SONG(MARIO_GAMEOVER_U)
#define CG_SWAP_SONG SONG(ONE_UP_SOUND_U)
#define CG_NORM_SONG SONG(MARIO_CAVE_1)


#define KBD_AUTH
#define RAW_USAGE_PAGE 0xFF60
#define RAW_USAGE_ID 0x61

