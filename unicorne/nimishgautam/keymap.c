// Copyright 2022 Nimish Gåtam (@nimishgautam)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H
#include "transactions.h"
#include "os_detection.h"

#include "ng_key_definitions.h"
#include "ng_tapdances_corne.c"
#include "ng_layer_definitions.h"
#include "ng_combos.c"
#include "ng_layout_corne.c"
#include "ng_process_keycodes_corne.c"


#ifdef OS_DETECTION_ENABLE
void os_detect(void) {
    os_variant_t host_os = detected_host_os();
    #ifdef AUDIO_ENABLE
    float cg_norm_song[][2] = CG_NORM_SONG;
    float cg_swap_song[][2] = CG_SWAP_SONG;
    #endif
    if (host_os) {
        switch (host_os) {
            case OS_MACOS:
            case OS_IOS:
                //check
                if( keymap_config.swap_lctl_lgui){
                    keymap_config.swap_lctl_lgui = keymap_config.swap_rctl_rgui = false;
                    #ifdef AUDIO_ENABLE
                    PLAY_SONG(cg_norm_song);
                    #endif
                }

            break;
            default: //Linux, but also windows etc with swapped ctl/gui
                if( !keymap_config.swap_lctl_lgui){
                    keymap_config.swap_lctl_lgui = keymap_config.swap_rctl_rgui = true;
                    #ifdef AUDIO_ENABLE
                    PLAY_SONG(cg_swap_song);
                    #endif
                }
            break;
        }

    }
}
#endif

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

#ifdef RGB_MATRIX_ENABLE
// base rgb mode, some sensible default if undefined
uint8_t base_rgb_mode = RGB_MATRIX_SPLASH;
HSV base_HSV = {HSV_CYAN};
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

#ifdef OLED_ENABLE

#ifdef OLED_STUPID_WAY_AROUND
// send a bunch of crap to the other side

uint16_t keymap_config_transport  = 0;
uint8_t magic_case_transport = 0;

uint32_t last_sync = 0;

void magic_case_sync(uint8_t initiator2target_buffer_size, const void* initiator2target_buffer,
                     uint8_t target2initiator_buffer_size, void* target2initiator_buffer) {
    if (initiator2target_buffer_size == sizeof(magic_case_transport)) {
        memcpy(&magic_case_transport, initiator2target_buffer, initiator2target_buffer_size);
    }
}

void keymap_sync(uint8_t initiator2target_buffer_size, const void* initiator2target_buffer,
                     uint8_t target2initiator_buffer_size, void* target2initiator_buffer) {
    if (initiator2target_buffer_size == sizeof(keymap_config_transport)) {
        memcpy(&keymap_config_transport, initiator2target_buffer, initiator2target_buffer_size);
    }
}

void split_send_all_if_needed(void) {
    //static uint16_t last_keymap = 0;
    //uint8_t last_magic_case = 0;
    bool needs_sync = false;

    // Send every 500ms regardless of state change
    if (timer_elapsed32(last_sync) > 2000) {
        needs_sync = true;
    }

    /* can check if the vars have changed here */

    if (needs_sync) {
        if (
            transaction_rpc_send(SYNC_MAGIC_CASE, sizeof(magic_case_transport), &magic_case_transport)
        &&   transaction_rpc_send(SYNC_KEYMAP, sizeof(keymap_config_transport), &keymap_config_transport))
            {
                last_sync = timer_read32();
            }
    }
}
#endif



oled_rotation_t oled_init_user(oled_rotation_t rotation) {
  return OLED_ROTATION_270;
}

bool oled_task_user(void){

    // sneaky way to pass in bootloader info :)
    if(magic_case_state == 99){
        oled_clear();
        oled_write_P(PSTR("BOOT!"), false);
        oled_render_dirty(true);
        return false;
    }

    //Layer
    uint8_t layer = get_highest_layer(layer_state);

    /* write OS */
    static const char PROGMEM apple_logo[] = {
        32, 149,150,10,
        32, 181,182,0
    };
    
    static const char PROGMEM tux_logo[] = {
        32, 153,154,10,
        32, 185,186,0
    };


    switch (layer) {
        case _BASE:
            oled_write_ln_P(PSTR("  -  "), false);
            break;
        case _NUMS:
            oled_write_ln_P(PSTR(" Nums"), false);
            break;
        case _TERMINAL:
            oled_write_ln_P(PSTR(" Term"), false);
            break;
        case _TEXT_NAV:
            oled_write_ln_P(PSTR(" Txt"), false);
            break;
        case _ADJUST:
            if(keymap_config.swap_lctl_lgui){
                //oled_write_ln_P(PSTR("Linux"), false);
                oled_write_ln_P(tux_logo, false);
            }
            else {
                //oled_write_ln_P(PSTR("OSX"), false);
                oled_write_ln_P(apple_logo, false);
            }
            oled_write_ln_P(PSTR(" Adj"), false);
            break;
        case _FN_KEYS:
            oled_write_ln_P(PSTR("  Fn"), false);
            break;
        #ifdef POINTING_DEVICE_ENABLE
        case _MOUSE:
            oled_write_ln_P(PSTR("Mouse"), false);
            break;
        #endif
        default:
            break;
    }
    oled_write_ln_P(PSTR(" "), false);

    /* write wpm */
    oled_write_P(PSTR(" "), false);
    oled_write_ln(get_u8_str(get_current_wpm(), '0'), false);

    /* write magic */
    if(magic_case_state){
        oled_write_ln_P(PSTR("MAGIC"), true);
    } else {
        oled_write_ln_P(PSTR(" "), false);
    }


    const char PROGMEM up_arrow[] = { 24,};
    const char PROGMEM circle_symbol[] = { 15,};
    oled_write_ln_P(PSTR(" "), false);
    // mods
    if(get_mods() & MOD_MASK_SHIFT){
        oled_write_P(up_arrow, false);
    }
    if(get_mods() & MOD_MASK_CTRL){
        oled_write_P(PSTR("^"), false);
    }
    if(get_mods() & MOD_MASK_ALT){
        oled_write_P(PSTR("/"), false);
    }
    if(get_mods() & MOD_MASK_GUI){ //ln here
        oled_write_ln_P(circle_symbol, false);
    } else {
        oled_write_ln_P(PSTR(" "), false);
    }
    
    //led state
    led_t led_state = host_keyboard_led_state();
    if(led_state.caps_lock){
        oled_write_P(PSTR("C"), false);
    } else {
        oled_write_P(PSTR(" "), false);
    }
    if(led_state.num_lock){
        oled_write_P(PSTR("N"), false);
    } else {
        oled_write_P(PSTR(" "), false);
    }
    if(led_state.scroll_lock){
        oled_write_P(PSTR("S"), false);
    } else {
        oled_write_P(PSTR(" "), false);
    }
    if(led_state.compose){ // note the ln here
        oled_write_ln_P(PSTR("*"), false);
    } else {
        oled_write_ln_P(PSTR(" "), false);
    }

    return false;

}

void oled_render_boot(bool bootloader) {
    oled_clear();
    if (bootloader) {
        oled_write_P(PSTR("BOOT!"), false);
    } else {
        oled_write_P(PSTR("Rebooting "), false);
    }
    oled_render_dirty(true);
}

bool shutdown_user(bool jump_to_bootloader) {
    #ifdef OLED_STUPID_WAY_AROUND
    magic_case_state = 99;
    magic_case_transport = 99;
    transaction_rpc_send(SYNC_MAGIC_CASE, sizeof(magic_case_transport), &magic_case_transport);
    #else
    oled_render_boot(jump_to_bootloader);
    #endif

    return jump_to_bootloader;
}
#endif



#ifndef SCROLLING_LAYER
    #define SCROLLING_LAYER _TEXT_NAV
#endif
#ifndef TAPPING_LAYER
    #define TAPPING_LAYER _TERMINAL
#endif
#ifndef CURSOR_SPEED
    #define CURSOR_SPEED 70
#endif
#ifndef SCROLL_SPEED
    #define SCROLL_SPEED 45
#endif
#ifndef SCROLL_DELAY_MS
    #define SCROLL_DELAY_MS 70
#endif

#define THUMBSTICK_RIGHT_TAP KC_RIGHT
#define THUMBSTICK_LEFT_TAP KC_LEFT
#define THUMBSTICK_UP_TAP KC_UP
#define THUMBSTICK_DOWN_TAP KC_DOWN

// Thumbstick code, no customisation needed

bool cursor_mode = false;
bool scrolling_mode = false;
bool tapping_mode = false;

// tracks if thumbstick was released
bool returned_to_zero = true;

// tracks how many times mouse_report.x/y have been read zero in succession
uint16_t zero_reads = 0;

// set mode depending on layer
layer_state_t layer_state_set_user(layer_state_t state) {
    
    switch (get_highest_layer(state)) {
        case SCROLLING_LAYER:
            if (scrolling_mode == false) {
            scrolling_mode = true;
            set_auto_mouse_enable(false);
            }
            if (tapping_mode) {
                tapping_mode = false;
            }
            if (cursor_mode) {
                cursor_mode = false;
            }
            break;
        case TAPPING_LAYER:
            if (tapping_mode == false) {
                tapping_mode = true;
                set_auto_mouse_enable(false);
            }
            if (cursor_mode) {
                cursor_mode = false;
            }
            if (scrolling_mode) {
                scrolling_mode = false;
            }
            break;
        default:
            if (scrolling_mode) {
                scrolling_mode = false;
            }
            if (tapping_mode) {
                tapping_mode = false;
            }
            if (cursor_mode == false) {
                cursor_mode = true;
            }
            if (!get_auto_mouse_enable()){
                set_auto_mouse_enable(true);
            }
            break;
    }
    return state;
}

// manipulate mouse report based on current mode
report_mouse_t pointing_device_task_user(report_mouse_t mouse_report) {

    if (cursor_mode) {
        mouse_report.x = CURSOR_SPEED * mouse_report.x/100;
        mouse_report.y = CURSOR_SPEED * mouse_report.y/100;      
    }
    if (scrolling_mode) {
        mouse_report.h = SCROLL_SPEED * mouse_report.x/100;
        mouse_report.v = -1 * SCROLL_SPEED * mouse_report.y/100;
        mouse_report.x = 0;
        mouse_report.y = 0;
        if ((mouse_report.h != 0) | (mouse_report.v != 0)) {
            wait_ms(SCROLL_DELAY_MS);
        }

    } else if (tapping_mode) {
        if ((mouse_report.x || mouse_report.y) != 0) {
            if (returned_to_zero) {
                if (mouse_report.x > 0) {
                    tap_code16(THUMBSTICK_RIGHT_TAP);
                }
                if (mouse_report.x < 0) {
                    tap_code16(THUMBSTICK_LEFT_TAP);
                }
                if (mouse_report.y > 0) {
                    tap_code16(THUMBSTICK_DOWN_TAP);
                }
                if (mouse_report.y < 0) {
                    tap_code16(THUMBSTICK_UP_TAP);
                }
                returned_to_zero = false;
            }
            zero_reads = 0;
        } else if (zero_reads < 20) {
            zero_reads++;
        }
        if (zero_reads >= 20) {
            if (returned_to_zero == false) {
                returned_to_zero = true;
            }
        }
        mouse_report.x = 0;
        mouse_report.y = 0;
    }

    return mouse_report;
}

void pointing_device_init_user(void) {
    set_auto_mouse_layer(_MOUSE); // only required if AUTO_MOUSE_DEFAULT_LAYER is not set to index of <mouse_layer>
    set_auto_mouse_enable(true);         // always required before the auto mouse feature will work
}


void keyboard_post_init_user(void) {
    #ifdef OLED_STUPID_WAY_AROUND
    transaction_register_rpc(SYNC_KEYMAP, keymap_sync);
    transaction_register_rpc(SYNC_MAGIC_CASE, magic_case_sync);
    #endif
    #ifdef OS_DETECTION_ENABLE
    if (is_keyboard_master()) {
        os_detect();
    }
#endif
}

void housekeeping_task_user(void) {

    if (is_keyboard_master()) {
        #ifdef RGB_MATRIX_ENABLE
            set_lighting_user();
        #endif
        #ifdef OLED_STUPID_WAY_AROUND
        // update transport variables with current master values
        keymap_config_transport = keymap_config.raw;
        magic_case_transport = magic_case_state;

        // send over if needed
        split_send_all_if_needed();
    } else { //else we're on the secondary side, set our vars to whatever is around

        // this one is a eeprom / persistent one so no writing if not needed
        if(keymap_config_transport != keymap_config.raw){
            keymap_config.raw = keymap_config_transport;
        }
        magic_case_state = magic_case_transport;
        #endif
    }

}

