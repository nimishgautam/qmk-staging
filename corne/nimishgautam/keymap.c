// Copyright 2022 Nimish Gåtam (@nimishgautam)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

#include "ng_key_definitions.h"
#include "ng_tapdances_corne.c"
#include "ng_layer_definitions.h"
#include "ng_combos.c"
#include "ng_layout_corne.c"
#include "ng_process_keycodes_corne.c"



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

// yeah, should be layer_state_set_user but that one doesn't update the mods
void set_lighting_user(void) {
    uint8_t layer = get_highest_layer(layer_state);
    switch(layer){
        case _BASE:
            rgblight_sethsv_noeeprom(HSV_WHITE);
            led_t led_state = host_keyboard_led_state();
            if(led_state.caps_lock){
                rgblight_sethsv_noeeprom(HSV_RED);
            }
            //rgblight_sethsv(HSV_OFF);
        break;
        case _NUMS:
            rgblight_sethsv_noeeprom(HSV_GREEN);
        break;
        case _TERMINAL:
            rgblight_sethsv_noeeprom(HSV_PINK);
        break;
        case _TEXT_NAV:
            rgblight_sethsv_noeeprom(HSV_BLUE);
        break;
        case _ADJUST:
            rgblight_sethsv_noeeprom(HSV_ORANGE);
        break;
        case _FN_KEYS:
            rgblight_sethsv_noeeprom(HSV_PURPLE);
        break;
        default:
        break;
    }
    // override color with mods

    if(get_mods() & MOD_MASK_SHIFT){
        rgblight_sethsv_noeeprom(HSV_RED);
    }
    if(get_mods() & MOD_MASK_CTRL){
        rgblight_sethsv_noeeprom(HSV_MAGENTA);
    }
    if(get_mods() & MOD_MASK_ALT){
        rgblight_sethsv_noeeprom(HSV_YELLOW);
    }
    if(get_mods() & MOD_MASK_GUI){
        rgblight_sethsv_noeeprom(HSV_TEAL);
    }
    // return state;
}

#ifdef OLED_ENABLE
oled_rotation_t oled_init_user(oled_rotation_t rotation) {
  return OLED_ROTATION_270;
}

void oled_render_general_state(void){
    set_lighting_user();

    keymap_config.raw = eeconfig_read_keymap();
    if(keymap_config.swap_lctl_lgui){
        oled_write_ln_P(PSTR("Linux"), false);
    }
    else {
        oled_write_ln_P(PSTR("OSX"), false);
    }

    //oled_write_ln(get_u8_str(get_current_wpm(), '0'), false);
    /*
    led_t led_state = host_keyboard_led_state();
    if(led_state.caps_lock){
        rgblight_sethsv(HSV_RED);
    }*/
    //Layer color has to be handled by master


    // led state doesn't have to be handled by master, but
    // the keyboard will freeze if you type too fast
    // and have this handled on the slave side

    /*
    led_t led_state = host_keyboard_led_state();
    if(led_state.caps_lock){
        oled_write_ln_P(PSTR("CAPS"), false);
    } else {
        oled_write_ln_P(PSTR(" "), false);
    }
    if(led_state.num_lock){
        oled_write_ln_P(PSTR("NumLk"), false);
    } else {
        oled_write_ln_P(PSTR(" "), false);
    }
    if(led_state.scroll_lock){
        oled_write_ln_P(PSTR("Scrol"), false);
    } else {
        oled_write_ln_P(PSTR(" "), false);
    }
    if(led_state.compose){
        oled_write_ln_P(PSTR("comp"), false);
    } else {
        oled_write_ln_P(PSTR(" "), false);
    }*/
}

void oled_render_layer_mod_state(void) {
    //Layer
    uint8_t layer = get_highest_layer(layer_state);
    switch (layer) {
        case _BASE:
            oled_write_ln_P(PSTR("Base"), false);
            //rgblight_sethsv(HSV_OFF);
            break;
        case _NUMS:
            oled_write_ln_P(PSTR("Nums"), false);
            break;
        case _TERMINAL:
            oled_write_ln_P(PSTR("Term"), false);
            break;
        case _TEXT_NAV:
            oled_write_ln_P(PSTR("Text"), false);
            break;
        case _ADJUST:
            oled_write_ln_P(PSTR("Adj"), false);
            break;
        case _FN_KEYS:
            oled_write_ln_P(PSTR("Fn"), false);
            break;
        default:
            break;
    }
    oled_write_ln_P(PSTR(" "), false);
    // mods
    if(magic_case_state){
        oled_write_ln_P(PSTR("magic"), false);
    } 
    if(get_mods() & MOD_MASK_SHIFT){
        oled_write_ln_P(PSTR("SHIFT"), false);
    }
    if(get_mods() & MOD_MASK_CTRL){
        oled_write_ln_P(PSTR("ctrl"), false);
    }
    if(get_mods() & MOD_MASK_ALT){
        oled_write_ln_P(PSTR("alt"), false);
    }
    if(get_mods() & MOD_MASK_GUI){
        oled_write_ln_P(PSTR("GUI"), false);
    }
    if(!get_mods()){
        oled_write_ln_P(PSTR(" "), false);
        oled_write_ln_P(PSTR(" "), false);
        oled_write_ln_P(PSTR(" "), false);
        oled_write_ln_P(PSTR(" "), false);
    }
}


/* https://joric.github.io/qle/  - font */


// render general state on master, a little bit of info on slave side
bool oled_task_user(void) {
    if (is_keyboard_master()) {
        oled_render_general_state();
    }
    else {
        oled_render_layer_mod_state();
    }
    return false;
}

#endif
