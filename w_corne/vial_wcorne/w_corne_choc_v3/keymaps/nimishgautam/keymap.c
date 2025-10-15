// Copyright 2022 Nimish Gåtam (@nimishgautam)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

#include "w_corne_choc_v3.h"

#include "os_detection.h"

#include "ng_key_definitions.h"
#include "ng_tapdances_corne.c"
#include "ng_layer_definitions.h"
#include "ng_combos.c"
// Note, the right hand is reversed!!!
// Must regenerate reversed keymap after change
#include "ng_layout_corne_reversed.c"
#include "ng_process_keycodes_corne.c"

void os_detect(void) {
    os_variant_t host_os = detected_host_os();
    if (host_os) {
        switch (host_os) {
            case OS_MACOS:
            case OS_IOS:
                //check
                if( keymap_config.swap_lctl_lgui){
                    keymap_config.swap_lctl_lgui = keymap_config.swap_rctl_rgui = false;
                    eeconfig_update_keymap(&keymap_config);
                }
            break;
            default: //Linux, but also windows etc with swapped ctl/gui
                if( !keymap_config.swap_lctl_lgui){
                    keymap_config.swap_lctl_lgui = keymap_config.swap_rctl_rgui = true;
                    eeconfig_update_keymap(&keymap_config);
                }
            break;
        }

    }
}

void keyboard_post_init_user(void) {
    if (is_keyboard_master()) {
    os_detect();
    }
}

#ifdef RGB_MATRIX_ENABLE
// base rgb mode, some sensible default if undefined
uint8_t base_rgb_mode = RGB_MATRIX_SOLID_SPLASH;
HSV base_HSV = {HSV_PINK};
uint8_t prev_layer = _BASE;

void set_lighting_user(void) {

 uint8_t layer = get_highest_layer(layer_state);
    if (layer != _ADJUST){
    // check if mods are set. If so, no need to check layers
    led_t led_state = host_keyboard_led_state();
        if(get_mods() || led_state.caps_lock){
            if((get_mods() & MOD_MASK_SHIFT)  || led_state.caps_lock){
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
            if( rgb_matrix_get_mode() != RGB_MODS_MODE){
                rgb_matrix_mode_noeeprom(RGB_MODS_MODE);
            }
            return;
        }
    }

    // otherwise some layer coloring and stuff
    switch(layer){
        case _BASE:
            if(prev_layer == _ADJUST){
                base_HSV = rgb_matrix_get_hsv();
                base_rgb_mode = rgb_matrix_get_mode();
            }
            rgb_matrix_sethsv_noeeprom(base_HSV.h, base_HSV.s, base_HSV.v);
            if(rgb_matrix_get_mode() != base_rgb_mode){
                //could be we change from a different base OR from mods
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
            rgb_matrix_sethsv_noeeprom(HSV_CYAN);
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
            if(prev_layer != _ADJUST){
                rgb_matrix_sethsv_noeeprom(HSV_CYAN);
                rgb_matrix_mode_noeeprom(base_rgb_mode);
            }
            // adjust, and any adjustments will be saved to base layer
        break;
        case _FN_KEYS:
            rgb_matrix_sethsv_noeeprom(HSV_PURPLE); 
            if(rgb_matrix_get_mode() != RGB_FN_MODE){
                rgb_matrix_mode_noeeprom(RGB_FN_MODE);
            }             
        break;
        #ifdef POINTING_DEVICE_ENABLE
        case _MOUSE:
            if(rgb_matrix_get_mode() != RGB_MOUSE_MODE){
                rgb_matrix_sethsv_noeeprom(HSV_CHARTREUSE); // color not needed for swirly animations
                rgb_matrix_mode_noeeprom(RGB_MOUSE_MODE);
            }
            break;
        #endif
        default:
        break;
    }
    prev_layer = layer;
    //return state;
}
#endif

led_config_t g_led_config = { {
        {0, 1, 2, 3}
    }, {
        // The LED corresponds to the physical location, you can refer to the formula below
        // x = 224 / (NUMBER_OF_COLS - 1) * COL_POSITION
        // y = 64 / (NUMBER_OF_ROWS - 1) * ROW_POSITION
        {0, 0}, {75, 0}, {149, 0}, {224, 0}

    }, {
        // Grouping, if there's no need to create your own lighting, the functionality is actually not very significant
        1, 1, 1, 1
    }
};
