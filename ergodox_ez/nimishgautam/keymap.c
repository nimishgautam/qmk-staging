// Copyright 2022 Nimish Gåtam (@nimishgautam)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H
#include "version.h"

#include "ng_key_definitions.h"
#include "ng_layer_definitions.h"
#include "ng_combos.c"
#include "ng_tapdances_ergodox.c"

extern keymap_config_t keymap_config;


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_BASE] = LAYOUT_ergodox_pretty(
    SCREENSHOT,     KC_1,           KC_2,           KC_3,           KC_4,           KC_5,           TD(TD_SELECT_LEFT),                                    TD(TD_SELECT_RIGHT),    KC_6,           KC_7,           KC_8,           KC_9,           KC_0,           KC_BSLS,
    KC_TAB,         KC_Q,           KC_W,           KC_E,           KC_R,           KC_T,           KC_LBRC,                                    KC_RBRC,    KC_Y,           KC_U,           KC_I,           KC_O,           KC_P,           KC_MINUS,
    KC_ESCAPE,      MT(MOD_LCTL, KC_A),    MT(MOD_LALT,KC_S),    MT(MOD_LSFT,KC_D),    MT(MOD_LGUI, KC_F),           KC_G,                                                                           KC_H,    MT(MOD_RGUI,KC_J),    MT(MOD_RSFT,KC_K),    MT(MOD_RALT,KC_L), MT(MOD_LCTL,KC_SCLN),      KC_QUOTE,
    MT(MOD_LSFT, SHOW_WINDOWS),    KC_Z,           KC_X,           KC_C,           KC_V,           KC_B,           KC_LPRN,                                        KC_RPRN,        KC_N,           KC_M,           KC_COMMA,       KC_DOT,    KC_SLASH,       KC_RSFT,
    MT(MOD_LCTL, WINDOW_LEFT),    KC_GRAVE, KC_HASH,    KC_LALT,        LT(_NUMS, COMPOSE_KEY),                                                                                                    LT(_NUMS, KC_UNDS),   KC_EQUAL,       MT(MOD_RGUI, EMOJI_KBD),        KC_RCTL,       MT(MOD_RALT, WINDOW_RIGHT),
                                                                                                    FINDER,     TD(TD_LEFT_TERM),   TD(TD_RIGHT_TERM), CALCULATOR,
                                                                                                                    KC_LEFT,        KC_UP,
                                                                                    KC_BSPC,      KC_ENTER,       KC_RIGHT,       KC_DOWN,        LT(_TEXT_NAV, KC_PAST),   KC_SPACE
  ),  
  [_NUMS] = LAYOUT_ergodox_pretty(
    KC_TRANSPARENT, KC_F1,          KC_F2,          KC_F3,          KC_F4,          KC_F5,           KC_F11,                                            KC_F12,         KC_F6,          KC_F7,          KC_F8,          KC_F9,          KC_F10,         KC_TRANSPARENT,
    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,  KC_TRANSPARENT,                                    KC_TRANSPARENT, KC_7,           KC_8,           KC_9,           KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
    TO(0),          ACIRCLE,        KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,                                                                     KC_4,           KC_5,           KC_6,           ADOT,           ODOT,           KC_TRANSPARENT,
    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, PASTE_NOSTYLE,  KC_TRANSPARENT,  KC_TRANSPARENT,                                    KC_TRANSPARENT, KC_1,           KC_2,           KC_3,           KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,                                                                                                     KC_0,           KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
                                                                                                    KC_VOLU, TD(TD_VOL_DOWN_MUTE), KC_TRANSPARENT, KC_TRANSPARENT,
                                                                                                                    KC_TRANSPARENT,KC_TRANSPARENT,
                                                                                    KC_TRANSPARENT,KC_TRANSPARENT, KC_TRANSPARENT,KC_TRANSPARENT,  KC_TRANSPARENT, KC_UNDS
  ), 

  [_TEXT_NAV] = LAYOUT_ergodox_pretty(
    LOCK_SCREEN,    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_CIRC,                                        KC_DLR,         KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, QK_BOOT,
    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_PSCR,                                        KC_TRANSPARENT, KC_TRANSPARENT, KC_MS_WH_UP,    EMOJI_KBD, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
    TO(0),          KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,                                                                 KC_MS_WH_LEFT,  KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_CAPS,
    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_DELETE,                                      KC_INSERT,      KC_MS_WH_RIGHT, KC_MS_WH_DOWN,  KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,                                                                                                 KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
                                                                                                    DEL_WORD_TERMINAL, KC_TRANSPARENT, CG_TOGG, SHOW_OS,
                                                                                                                    KC_HOME,        KC_PGUP,
                                                                                    DEL_WORD,LSFT(KC_ENTER), KC_END,                KC_PGDN,      KC_TRANSPARENT, KC_TRANSPARENT
  ),
};

// Empty template
/*  [_LAYER_X] = LAYOUT_ergodox_pretty(
    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,                                 KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,                                 KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
    TO(0),          KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,                                                                 KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,                                 KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,                                                                                                 KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
                                                                                                    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
                                                                                                                    KC_TRANSPARENT, KC_TRANSPARENT,
                                                                                    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT
  ),*/

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
      case MT(MOD_LSFT, SHOW_WINDOWS):      
        if (record->tap.count && record->event.pressed) {
            tap_code16(SHOW_WINDOWS); 
        return false; 
        }
        break;
    case MT(MOD_LCTL, WINDOW_LEFT):
        if (record->tap.count && record->event.pressed) {
            tap_code16(WINDOW_LEFT); 
        return false; 
        }
        break;
    case MT(MOD_RALT, WINDOW_RIGHT):
        if (record->tap.count && record->event.pressed) {
            tap_code16(WINDOW_RIGHT); 
        return false; 
        }
        break;
    case LT(_NUMS, KC_UNDS):
        if (record->tap.count && record->event.pressed) {
            tap_code16(KC_UNDS); 
        return false; 
        }
        break;
        
    case LT(_TEXT_NAV, KC_PAST):
        if (record->tap.count && record->event.pressed) {
            tap_code16(KC_PAST); 
        return false; 
        }
        break;
    case MT(MOD_RGUI, EMOJI_KBD):      
        if (record->tap.count && record->event.pressed) {
            tap_code16(EMOJI_KBD); 
        return false; 
        }
        break;
    case PASTE_VIM:
        if (record->event.pressed){
            SEND_STRING(SS_TAP(X_ESCAPE)"\"+pi");
        }
        return false;
        break;
  

    // this one is OS-specific but doesn't fit the same
    // pattern as the others
    // If pressed and held, needs to return TRUE for layer-tap code
    // to activate (via the return statement at the end of process fn)
    // whereas the other os-specific ones return false
   case LT(_NUMS, COMPOSE_KEY): 
    if (record->tap.count && record->event.pressed){
      keymap_config.raw = eeconfig_read_keymap();
      if(keymap_config.swap_lctl_lgui){ //Linux
          tap_code16(COMPOSE_KEY);
        } else { //osx
            tap_code16(COMPOSE_MAC);
        }
      return false;
      }
    break;


    // read keymap config for os-specific keys
   case SCREENSHOT:
   case PASTE_NOSTYLE:
   case DEL_WORD:
   case ACIRCLE:
   case ADOT:
   case ODOT:
   case SHOW_OS:

   if(record->event.pressed) {
      keymap_config.raw = eeconfig_read_keymap();
        
        switch (keycode){

          case SCREENSHOT:
            if(keymap_config.swap_lctl_lgui){ //Linux
              tap_code16(KC_PSCR);
            } else { //osx
              tap_code16(LGUI(LSFT(KC_4)));
            }
          break;
          case PASTE_NOSTYLE:
            if(keymap_config.swap_lctl_lgui){ //Linux
                tap_code16(LCTL(RSFT(KC_V)));
            } else { //osx
                tap_code16(LGUI(LALT(LSFT(KC_V)))); 
            }
            break;
          case DEL_WORD:
            if(keymap_config.swap_lctl_lgui){ //Linux
              tap_code16(LCTL(KC_BSPC));
              } else { //osx
              tap_code16(LALT(KC_BSPC));
              }
            break;

          case ACIRCLE: // å
            if(keymap_config.swap_lctl_lgui){ //Linux
              if (get_mods() & MOD_MASK_SHIFT){
                SEND_STRING(SS_TAP(X_COMPOSE_KEY)"AA"); 
              } else {
                SEND_STRING(SS_TAP(X_COMPOSE_KEY)"aa");
              }
            } else { //osx
              if (get_mods() & MOD_MASK_SHIFT){
                tap_code16(LSFT(LALT(KC_A))); 
              } else {
                tap_code16(LALT(KC_A)); 
              }
            }
          break;

          case ADOT: // ä
            if(keymap_config.swap_lctl_lgui){ //Linux
              if (get_mods() & MOD_MASK_SHIFT){
                SEND_STRING(SS_TAP(X_COMPOSE_KEY)"A\""); 
              } else {
                SEND_STRING(SS_TAP(X_COMPOSE_KEY)"a\"");
              }
            } else { //osx
              if (get_mods() & MOD_MASK_SHIFT){
                SEND_STRING(SS_LALT("u")"A");
              } else {
                SEND_STRING(SS_LALT("u")"a");
              }
            }
          break;

          case ODOT: // ö
            if(keymap_config.swap_lctl_lgui){ //Linux
              if (get_mods() & MOD_MASK_SHIFT){
                SEND_STRING(SS_TAP(X_COMPOSE_KEY)"O\""); 
              } else {
                SEND_STRING(SS_TAP(X_COMPOSE_KEY)"o\"");
              }
            } else { //osx
              if (get_mods() & MOD_MASK_SHIFT){
                SEND_STRING(SS_LALT("u")"o");
              } else {
                SEND_STRING(SS_LALT("u")"O");
              }
            }
          break;

          case SHOW_OS:
            if(keymap_config.swap_lctl_lgui){ //Linux
                SEND_STRING("Lx");
            } else { //osx
                SEND_STRING("Mac");
            }
            break;
        }//switch
   }//if


   return false; // return false for all OS-specific keys
   break;
  
  }
  return true; // default
}





layer_state_t layer_state_set_user(layer_state_t state) {
  uint8_t layer = biton32(state);
  ergodox_board_led_off();
  ergodox_right_led_1_off();
  ergodox_right_led_2_off();
  ergodox_right_led_3_off();
  switch (layer) {
    case 1:
      ergodox_right_led_1_on();
      break;
    case 2:
      ergodox_right_led_2_on();
      break;
    case 3:
      ergodox_right_led_3_on();
      break;
    case 4:
      ergodox_right_led_1_on();
      ergodox_right_led_2_on();
      break;
    case 5:
      ergodox_right_led_1_on();
      ergodox_right_led_3_on();
      break;
    case 6:
      ergodox_right_led_2_on();
      ergodox_right_led_3_on();
      break;
    case 7:
      ergodox_right_led_1_on();
      ergodox_right_led_2_on();
      ergodox_right_led_3_on();
      break;
    default:
      break;
  }
  return state;
};


bool get_permissive_hold(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case MT(MOD_LSFT,KC_D): 
        case MT(MOD_RSFT,KC_K):
        case LT(_TEXT_NAV, KC_PAST):
            // Immediately select the hold action when another key is tapped.
            return true;
        default:
            // Do not select the hold action when another key is tapped.
            return false;
    }
}