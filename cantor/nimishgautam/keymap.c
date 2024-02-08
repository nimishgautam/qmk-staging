// Copyright 2022 Nimish Gåtam (@nimishgautam)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H
#include "os_detection.h"

#include "ng_key_definitions.h"
#include "ng_tapdances_corne.c"
#include "ng_layer_definitions.h"
#include "ng_combos.c"
#include "ng_layout_corne.c"
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
                    eeconfig_update_keymap(keymap_config.raw);
                }
            break;
            default: //Linux, but also windows etc with swapped ctl/gui
                if( !keymap_config.swap_lctl_lgui){
                    keymap_config.swap_lctl_lgui = keymap_config.swap_rctl_rgui = true;
                    eeconfig_update_keymap(keymap_config.raw);
                }
            break;
        }

    }
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

void keyboard_post_init_user(void) {
    if (is_keyboard_master()) {
        os_detect();
    }
}