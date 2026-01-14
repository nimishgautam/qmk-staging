// Copyright 2022 Nimish Gåtam (@nimishgautam)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

#include "ng_key_definitions.h"
#include "ng_tapdances_corne.c"
#include "ng_layer_definitions.h"
#include "ng_combos.c"
#include "ng_layout_corne.c"
#include "ng_process_keycodes_corne.c"

#if defined(RGB_LIGHT_ENABLE) || defined(RGB_MATRIX_ENABLE)
// base rgb mode, some sensible default if undefined
uint8_t base_rgb_mode = RGB_MATRIX_SPLASH;

// yeah, should be layer_state_set_user but that one doesn't update the mods
void set_lighting_user(void) {
//layer_state_t layer_state_set_user(layer_state_t state){
    uint8_t layer = get_highest_layer(layer_state);
    
    // Check if mods are set first (mods override layer colors)
    led_t led_state = host_keyboard_led_state();
    if(get_mods() || led_state.caps_lock){
        if((get_mods() & MOD_MASK_SHIFT) || led_state.caps_lock){
            rgb_matrix_sethsv_noeeprom(HSV_RED);
        }
        if(get_mods() & MOD_MASK_CTRL){
            rgb_matrix_sethsv_noeeprom(HSV_MAGENTA);
        }
        if(get_mods() & MOD_MASK_ALT){
            rgb_matrix_sethsv_noeeprom(HSV_YELLOW);
        }
        if(get_mods() & MOD_MASK_GUI){
            rgb_matrix_sethsv_noeeprom(HSV_TEAL);
        }
        if(rgb_matrix_get_mode() != RGB_MODS_MODE){
            rgb_matrix_mode_noeeprom(RGB_MODS_MODE);
        }
        return;
    }
    
    // Otherwise set layer colors and animations
    switch(layer){
        case _BASE:
            rgb_matrix_sethsv_noeeprom(HSV_WHITE);
            if(rgb_matrix_get_mode() != base_rgb_mode){
                // Restore base mode when returning from mods or other layers
                rgb_matrix_mode_noeeprom(base_rgb_mode);
            }
        break;
        case _NUMS:
            rgb_matrix_sethsv_noeeprom(HSV_GREEN);
            if(rgb_matrix_get_mode() != RGB_NUMS_MODE){
                rgb_matrix_mode_noeeprom(RGB_NUMS_MODE);
            }
        break;
        case _TERMINAL:
            rgb_matrix_sethsv_noeeprom(HSV_PINK);
            if(rgb_matrix_get_mode() != RGB_TERM_MODE){
                rgb_matrix_mode_noeeprom(RGB_TERM_MODE);
            }
        break;
        case _TEXT_NAV:
            rgb_matrix_sethsv_noeeprom(HSV_BLUE);
            if(rgb_matrix_get_mode() != RGB_TXT_MODE){
                rgb_matrix_mode_noeeprom(RGB_TXT_MODE);
            }
        break;
        case _ADJUST:
            rgb_matrix_sethsv_noeeprom(HSV_ORANGE);
        break;
        case _FN_KEYS:
            rgb_matrix_sethsv_noeeprom(HSV_PURPLE);
            if(rgb_matrix_get_mode() != RGB_FN_MODE){
                rgb_matrix_mode_noeeprom(RGB_FN_MODE);
            }
        break;
        default:
        break;
    }
    //return state;
}
#endif

#ifdef OLED_ENABLE
#include "ng_double_oled.c"
#endif

