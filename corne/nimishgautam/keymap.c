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
// yeah, should be layer_state_set_user but that one doesn't update the mods
void set_lighting_user(void) {
//layer_state_t layer_state_set_user(layer_state_t state){
    uint8_t layer = get_highest_layer(layer_state);
    switch(layer){
        case _BASE:
            rgb_matrix_sethsv_noeeprom(HSV_WHITE);
            led_t led_state = host_keyboard_led_state();
            if(led_state.caps_lock){
                rgb_matrix_sethsv_noeeprom(HSV_RED);
            }
            //rgblight_sethsv(HSV_OFF);
        break;
        case _NUMS:
            rgb_matrix_sethsv_noeeprom(HSV_GREEN);
        break;
        case _TERMINAL:
            rgb_matrix_sethsv_noeeprom(HSV_PINK);
        break;
        case _TEXT_NAV:
            rgb_matrix_sethsv_noeeprom(HSV_BLUE);
        break;
        case _ADJUST:
            rgb_matrix_sethsv_noeeprom(HSV_ORANGE);
        break;
        case _FN_KEYS:
            rgb_matrix_sethsv_noeeprom(HSV_PURPLE);
        break;
        default:
        break;
    }
    // override color with mods

    if(get_mods() & MOD_MASK_SHIFT){
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
    //return state;
}
#endif

#ifdef OLED_ENABLE
#include "ng_double_oled.c"
#endif

