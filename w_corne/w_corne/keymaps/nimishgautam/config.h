// Copyright 2022 Nimish Gåtam (@nimishgautam)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#define VIAL_KEYBOARD_UID {0xFB, 0x76, 0xAE, 0x06, 0x25, 0x41, 0x12, 0xC9}

//   use timer2 ch1 pwm output, dma1_ch5, PA15
//or use timer2 ch2 pwm output, dma1_ch7, PB3
#define WS2812_PWM_DRIVER PWMD2
#define WS2812_PWM_CHANNEL 2
#define WS2812_PWM_PAL_MODE 2
#define WS2812_DMA_STREAM STM32_DMA1_STREAM7
#define WS2812_DMA_CHANNEL 7
// OS-specific stuff
//#define UNICODE_SELECTED_MODES UNICODE_MODE_MACOS

// combo
#define EXTRA_SHORT_COMBOS
#define COMBO_TERM 30
#define COMBO_STRICT_TIMER


//Tapping values
//#define QUICK_TAP_TERM 0
#define TAPPING_TERM 200
#define PERMISSIVE_HOLD_PER_KEY

// Try to save some memory
//#define NO_ACTION_ONESHOT
#undef LOCKING_SUPPORT_ENABLE
#undef LOCKING_RESYNC_ENABLE
#define LAYER_STATE_8BIT  //8 layers max


// which lighting effects to include (less saves memory)
#ifdef RGBLIGHT_ENABLE
    //#define RGBLIGHT_EFFECT_BREATHING
    //#define RGBLIGHT_EFFECT_RAINBOW_MOOD
    //#define RGBLIGHT_EFFECT_RAINBOW_SWIRL
    //#define RGBLIGHT_EFFECT_SNAKE
    //#define RGBLIGHT_EFFECT_KNIGHT
    //#define RGBLIGHT_EFFECT_CHRISTMAS
    //#define RGBLIGHT_EFFECT_STATIC_GRADIENT
    //#define RGBLIGHT_EFFECT_RGB_TEST
    //#define RGBLIGHT_EFFECT_ALTERNATING
    //#define RGBLIGHT_EFFECT_TWINKLE
    #define RGBLIGHT_LIMIT_VAL 120
    #define RGBLIGHT_HUE_STEP 10
    #define RGBLIGHT_SAT_STEP 17
    #define RGBLIGHT_VAL_STEP 17

#endif

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

    #define ENABLE_RGB_MATRIX_SOLID_SPLASH

    // NOTE: the below effects are super cool but they go absolutely nuts if you manually set hsv colors (eg with layers)

    //#define ENABLE_RGB_MATRIX_TYPING_HEATMAP
    //#define ENABLE_RGB_MATRIX_SOLID_MULTISPLASH
    //#define ENABLE_RGB_MATRIX_SOLID_REACTIVE
#endif


// mouse keys go at an inertia speed
#define MK_KINETIC_SPEED
