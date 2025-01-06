// Copyright 2022 Nimish Gåtam (@nimishgautam)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H
#include "quantum.h"
#include "transactions.h"
#include "os_detection.h"
#include "math.h"


#ifdef KBD_AUTH
#include "raw_hid.h"
#include "secrets.h"

#define SECURITY_CHALLENGE_SIZE 32
#define SECURITY_RESPONSE_SIZE 32
#define CMD_AUTH_START 0x01
#define CMD_CHALLENGE  0x02
#define CMD_RESPONSE   0x03

uint8_t last_challenge[SECURITY_CHALLENGE_SIZE];
bool challenge_received = false;

void raw_hid_receive(uint8_t *data, uint8_t length) {
    if (data[0] == CMD_CHALLENGE) {
        // Store the challenge
        memcpy(last_challenge, &data[1], SECURITY_CHALLENGE_SIZE);
        challenge_received = true;
        // Don't generate response yet - wait for button press
    }
}

void send_auth_response(void) {
    if (!challenge_received) {
        // First, request a challenge
        uint8_t start[32] = {CMD_AUTH_START};
        raw_hid_send(start, sizeof(start));
        // Wait a bit for the challenge to arrive
        wait_ms(100);
    }
    
    if (challenge_received) {
        // Generate and send response
        uint8_t response[32] = {CMD_RESPONSE};
        for(int i = 0; i < (SECURITY_CHALLENGE_SIZE - 1); i++) {
            response[i + 1] = last_challenge[i] ^ AUTH_KEY[i % sizeof(AUTH_KEY)];
        }
        raw_hid_send(response, sizeof(response));
        // Reset for next auth attempt
        challenge_received = false;
    }
}

#endif



#include "ng_key_definitions.h"
#include "ng_tapdances_corne.c"
#include "ng_layer_definitions.h"
#include "ng_combos.c"
#include "ng_layout_corne.c"
#include "ng_process_keycodes_corne.c"
#ifdef POINTING_DEVICE_ENABLE
#include "ng_unicorne_mouse.c"
#endif


#ifdef OS_DETECTION_ENABLE
#define OS_DETECTION_KEYBOARD_RESET
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
                    eeconfig_update_keymap(keymap_config.raw);
                }

            break;
            default: //Linux, but also windows etc with swapped ctl/gui
                if( !keymap_config.swap_lctl_lgui){
                    keymap_config.swap_lctl_lgui = keymap_config.swap_rctl_rgui = true;
                    #ifdef AUDIO_ENABLE
                    PLAY_SONG(cg_swap_song);
                    #endif
                    eeconfig_update_keymap(keymap_config.raw);
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
HSV base_HSV = {HSV_PINK};
uint8_t prev_layer = _BASE;

void set_lighting_user(void) {

#ifdef KBD_AUTH
// if in auth mode, most important to know that
if (challenge_received) {
    rgb_matrix_mode_noeeprom(RGB_AUTH_MODE);
    return;
}
#endif

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

#ifdef OLED_ENABLE

#ifdef OLED_STUPID_WAY_AROUND
// send a bunch of crap to the other side

uint16_t keymap_config_transport  = 0;
uint8_t magic_case_transport = 0;
bool auto_mouse_state_transport = false;

uint32_t last_sync = 0;

void magic_case_sync(uint8_t initiator2target_buffer_size, const void* initiator2target_buffer,
                     uint8_t target2initiator_buffer_size, void* target2initiator_buffer) {
    if (initiator2target_buffer_size == sizeof(magic_case_transport)) {
        memcpy(&magic_case_transport, initiator2target_buffer, initiator2target_buffer_size);
    }
}

void auto_mouse_sync(uint8_t initiator2target_buffer_size, const void* initiator2target_buffer,
                     uint8_t target2initiator_buffer_size, void* target2initiator_buffer) {
    if (initiator2target_buffer_size == sizeof(auto_mouse_state_transport)) {
        memcpy(&auto_mouse_state_transport, initiator2target_buffer, initiator2target_buffer_size);
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
        &&   transaction_rpc_send(SYNC_KEYMAP, sizeof(keymap_config_transport), &keymap_config_transport)
        && transaction_rpc_send(SYNC_AUTO_MOUSE, sizeof(auto_mouse_state_transport), &auto_mouse_state_transport))
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

#if defined (OLED_STUPID_WAY_AROUND) && defined(POINTING_DEVICE_AUTO_MOUSE_ENABLE)
    if(auto_mouse_state_transport && layer < _MOUSE){
        layer = _MOUSE;
    }
#endif

    /* write OS */
    static const char PROGMEM apple_logo[] = {
        32, 149,150,10,
        32, 181,182,0
    };
    
    static const char PROGMEM tux_logo[] = {
        32, 153,154,10,
        32, 185,186,0
    };

    static const char PROGMEM lower_layer[] = {
        145,146,147,148,10,
        177,178,179,180,0
    };

    switch (layer) {
        case _BASE:
            //oled_write_ln_P(PSTR("  -  "), false);
            oled_write_ln_P(lower_layer, false);
            break;
        case _NUMS:
            oled_write_ln_P(PSTR(" Nums"), false);
            break;
        case _TERMINAL:
            oled_write_ln_P(PSTR(" Term"), false);
            break;
        case _TEXT_NAV:
            oled_write_ln_P(PSTR(" Txt "), false);
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
            oled_write_ln_P(PSTR(" Adj "), false);
            break;
        case _FN_KEYS:
            oled_write_ln_P(PSTR("  Fn "), false);
            break;
        case _MOUSE:
            oled_write_ln_P(PSTR("Mouse"), false);
            break;
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


    const char PROGMEM gui_symbol[] = { 130, 131, 0};
    const char PROGMEM ctrl_symbol[] = { 128, 129,0};
    const char PROGMEM alt_symbol[] = { 192, 193,0};
    const char PROGMEM shift_symbol[] = { 160, 161,0};
    oled_write_ln_P(PSTR(" "), false);
    // mods
    if(get_mods() & MOD_MASK_SHIFT){
        oled_write_P(shift_symbol, false);
    }
    if(get_mods() & MOD_MASK_CTRL){
        oled_write_P(ctrl_symbol, false);
    }
    oled_write_ln_P(PSTR(" "), false);
    if(get_mods() & MOD_MASK_ALT){
        oled_write_P(alt_symbol, false);
    }
    if(get_mods() & MOD_MASK_GUI){ //ln here
        oled_write_P(gui_symbol, false);
    } 
    oled_write_ln_P(PSTR(" "), false);
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
    #endif
    oled_render_boot(jump_to_bootloader);
    return jump_to_bootloader;
}
#endif


void keyboard_post_init_user(void) {
    #ifdef OLED_STUPID_WAY_AROUND
    transaction_register_rpc(SYNC_KEYMAP, keymap_sync);
    transaction_register_rpc(SYNC_MAGIC_CASE, magic_case_sync);
    transaction_register_rpc(SYNC_AUTO_MOUSE, auto_mouse_sync);
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
        auto_mouse_state_transport = is_auto_mouse_active();
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