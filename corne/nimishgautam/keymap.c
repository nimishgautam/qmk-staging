// Copyright 2022 Nimish Gåtam (@nimishgautam)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

#include "ng_key_definitions.h"
#include "ng_tapdances_corne.c"
#include "ng_layer_definitions.h"
#include "ng_combos.c"
#include "ng_layout_corne.c"
#include "ng_process_keycodes_corne.c"

#ifdef OLED_ENABLE
#include "ng_double_oled.c"
#endif

// attempt to shrink firmware size -- this is for magic replacement of keys (not mods)
uint16_t keycode_config(uint16_t keycode) {
    switch (keycode) {
        case KC_LEFT_CTRL:
            if (keymap_config.swap_lctl_lgui) {
                return KC_LEFT_GUI;
            }
        break;
        case KC_LEFT_GUI:
            if (keymap_config.swap_lctl_lgui) {
                return KC_LEFT_CTRL;
            }
        break;
        case KC_RIGHT_CTRL:
            if (keymap_config.swap_rctl_rgui) {
                return KC_RIGHT_GUI;
            }
        break;
        case KC_RIGHT_GUI:
            if (keymap_config.swap_rctl_rgui) {
                return KC_RIGHT_CTRL;
            }
        break;
    }
    return keycode;
}

//shrink further, replacing mods
uint8_t mod_config(uint8_t mod) {
    /**
     * Note: This function is for the 5-bit packed mods, NOT the full 8-bit mods.
     * More info about the mods can be seen in modifiers.h.
     */

    if (keymap_config.swap_lctl_lgui) {
        // left mods ANDed with right-hand values to check for right hand bit 
        if (((mod & MOD_RCTL) == MOD_LCTL) ^ ((mod & MOD_RGUI) == MOD_LGUI)) {
            mod ^= (MOD_LCTL | MOD_LGUI);
        }
    }
    if (keymap_config.swap_rctl_rgui) {
        if (((mod & MOD_RCTL) == MOD_RCTL) ^ ((mod & MOD_RGUI) == MOD_RGUI)) {
            //lefthand values to preserve the right hand bit
            mod ^= (MOD_LCTL | MOD_LGUI);
        }
    }
    return mod;
}



bool get_permissive_hold(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case LSFT_T(KC_D): // for modtap shift, otherwise lots of mis-firings
        case RSFT_T(KC_K):
            // Immediately select the hold action when another key is tapped.
            return true;
        default:
            // Do not select the hold action when another key is tapped.
            return false;
    }
}

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

