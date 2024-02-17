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
#define COMBO_TERM 30
#define COMBO_STRICT_TIMER
#define COMBO_MUST_HOLD_PER_COMBO


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
    //#define ENABLE_RGB_MATRIX_RIVERFLOW

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


#ifdef RGB_MATRIX_ENABLE
#define RGB_MOUSE_MODE RGB_MATRIX_RAINBOW_PINWHEELS
#define RGB_MODS_MODE RGB_MATRIX_PIXEL_FRACTAL
#define RGB_TXT_MODE RGB_MATRIX_HUE_PENDULUM
#define RGB_NUMS_MODE RGB_MATRIX_HUE_BREATHING
#define RGB_FN_MODE RGB_MATRIX_PIXEL_FRACTAL
#define RGB_TERM_MODE RGB_MATRIX_BAND_SPIRAL_SAT
#endif


// mouse keys go at an inertia speed
#define MK_KINETIC_SPEED

// If I have a keypress in my defines, I want it to consistently send what it says
// eg #define END_PROCESS C(KC_C) should sent ctl-c and NOT G(KC_C) even when ctl and gui are swapped
#define LEGACY_MAGIC_HANDLING
