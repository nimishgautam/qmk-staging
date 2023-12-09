// Copyright 2022 Nimish Gåtam (@nimishgautam)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H
#include "version.h"

extern keymap_config_t keymap_config;

// Mac-specific definitions of these functions
// No memory costs this way, but means they can't be changed on the fly
#define FULLSCREEN      LGUI(LCTL(KC_F))
#define FINDER          LGUI(LALT(KC_SPACE))
#define SPOTLIGHT       LGUI(KC_SPACE)
#define SHOW_WINDOWS    LCTL(KC_UP)
#define SHOW_APP_WINDOWS LCTL(KC_DOWN)
#define LOCK_SCREEN     LCTL(LGUI(KC_Q))
#define EURO            LALT(LSFT(KC_2))
#define EMOJI_KBD       LCTL(LGUI(KC_SPACE))

enum custom_keycodes {
  RGB_SLD = EZ_SAFE_RANGE,
  DEL_WORD, //delete a word
  SELECT_LEFT_WD, // select word left of cursor
  SELECT_RIGHT_WD, // select word right of cursor
  SELECT_LEFT_LINE, // select all from left of cursor to beginning of line
  SELECT_RIGHT_LINE, // select all from right of cursor to end of line
  MOVE_LEFT_WD, // move one word to the left
  MOVE_RIGHT_WD, // move one word to the right
  MOVE_LEFT_LINE, // move to beginning of line
  MOVE_RIGHT_LINE, // move to end of line
  PASTE_NOSTYLE, // paste without formatting
  MOVE_BEGIN_LINE_TERMINAL, // move to the beginning of the line in the terminal
  MOVE_END_LINE_TERMINAL, // move to the end of the line in the terminal
  /* macros */
  PASTE_VIM, // paste in vim from system register
  ACIRCLE, // å 
  ADOT, // ä
  ODOT, // ö
  COMPOSE_MACRO, // compose key for mac or linux
  SCREENSHOT, // This is theoretically reprogrammable on Linux, but Gui(Shift(4)) or Gui(4) is reserved for '4th item on favorite menu' and doesn't remap so well
  SHOW_OS,
};

enum tap_dance_codes {
  TD_SELECT_LEFT, // select 1 word back normally, select back to beginning of line on double-tap
  TD_SELECT_RIGHT, // select 1 word forward normally, select forward to end of line on double-tap
  TD_LEFT_TERM, // move 1 word back on terminal, all the way back to the beginning of the terminal on double-tap
  TD_RIGHT_TERM, // move 1 word forward on terminal, all the way to end of line on terminal on double-tap
  
  TD_VOL_DOWN_MUTE, // vol down normally, mute on double-tap
};

// Mac-specific definitions of these functions
// I've changed Linux to accept these defaults

#define FINDER          LGUI(LALT(KC_SPACE)) //open the search bar for finding apps, docs in-computer, etc
#define COMPOSE_KEY    KC_SCRL //manually set on linux, to create chars via .Xcompose ()
#define COMPOSE_MAC     KC_F13 //manually set on mac using some tricks
#define X_COMPOSE_KEY    X_SCROLLLOCK //for use with macros
#define SHOW_WINDOWS    LCTL(KC_UP) //'Expose' on Mac, overview on linux. Just all the windows
#define WINDOW_LEFT LCTL(LGUI(LSFT(KC_LEFT))) //custom shortcut for this feature -- make window take up 50% left screen (using gui and ctl to make it os agnostic)
#define WINDOW_RIGHT LCTL(LGUI(LSFT(KC_RIGHT))) //custom shortcut for this feature -- make window take up 50% right screen (using gui and ctl to make it os agnostic)/fully custom shortcut, using ctl and gui keys so will need them both irrespective of os
#define SHOW_APP_WINDOWS LCTL(KC_DOWN) 
#define LOCK_SCREEN     LCTL(LGUI(KC_Q)) //manually set this on linux to match osx default
#define EURO            LALT(LSFT(KC_2))
#define EMOJI_KBD       LCTL(LGUI(KC_SPACE)) //manually set this on linux to match osx default, with 'emote' on linux and a custom shortcut (probably better to use compose feature)
#define APP_LEFT		LGUI(KC_TAB)
#define APP_RIGHT		RSFT(LGUI(KC_TAB))
#define CALCULATOR      RSFT(LGUI(LCTL(KC_SLASH))) // arbitrary shortcut

#define MOVE_LEFT_TERMINAL LALT(KC_LEFT) //move cursor one word left on the terminal... does not work if .inputrc is set to use vim bindings!
#define MOVE_RIGHT_TERMINAL LALT(KC_RIGHT) //move cursor one word left on the terminal... does not work if .inputrc is set to use vim bindings!
#define DEL_WORD_TERMINAL LALT(KC_BSPACE) // delete one word back on terminal ... does not work if .inputrc is set to use vim bindings!

#define _BASE 0
#define _NUMS 1
#define _TEXT_NAV 2

// combo - press ,. to paste in vim
const uint16_t PROGMEM vim_paste_combo[] = {KC_COMM, KC_DOT, COMBO_END};

combo_t key_combos[COMBO_COUNT] = {
    /* macros */
    COMBO(vim_paste_combo, PASTE_VIM),
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_BASE] = LAYOUT_ergodox_pretty(
    SCREENSHOT,     KC_1,           KC_2,           KC_3,           KC_4,           KC_5,           TD(TD_SELECT_LEFT),                                    TD(TD_SELECT_RIGHT),    KC_6,           KC_7,           KC_8,           KC_9,           KC_0,           KC_BSLASH,
    KC_TAB,         KC_Q,           KC_W,           KC_E,           KC_R,           KC_T,           KC_LBRACKET,                                    KC_RBRACKET,    KC_Y,           KC_U,           KC_I,           KC_O,           KC_P,           KC_MINUS,
    KC_ESCAPE,      MT(MOD_LCTL, KC_A),    MT(MOD_LALT,KC_S),    MT(MOD_LSFT,KC_D),    MT(MOD_LGUI, KC_F),           KC_G,                                                                           KC_H,    MT(MOD_RGUI,KC_J),    MT(MOD_RSFT,KC_K),    MT(MOD_RALT,KC_L), MT(MOD_LCTL,KC_SCLN),      KC_QUOTE,
    MT(MOD_LSFT, SHOW_WINDOWS),    KC_Z,           KC_X,           KC_C,           KC_V,           KC_B,           KC_LPRN,                                        KC_RPRN,        KC_N,           KC_M,           KC_COMMA,       KC_DOT,    KC_SLASH,       KC_RSFT,
    MT(MOD_LCTL, WINDOW_LEFT),    KC_GRAVE, KC_HASH,    KC_LALT,        LT(_NUMS, COMPOSE_KEY),                                                                                                    LT(_NUMS, KC_UNDS),   KC_EQUAL,       MT(MOD_RGUI, EMOJI_KBD),        KC_RCTRL,       MT(MOD_RALT, WINDOW_RIGHT),
                                                                                                    FINDER,     TD(TD_LEFT_TERM),   TD(TD_RIGHT_TERM), CALCULATOR,
                                                                                                                    KC_LEFT,        KC_UP,
                                                                                    KC_BSPACE,      KC_ENTER,       KC_RIGHT,       KC_DOWN,        LT(_TEXT_NAV, KC_PAST),   KC_SPACE
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
    LOCK_SCREEN,    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_CIRC,                                        KC_DLR,         KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, RESET,
    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_PSCR,                                        KC_TRANSPARENT, KC_TRANSPARENT, KC_MS_WH_UP,    EMOJI_KBD, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
    TO(0),          KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,                                                                 KC_MS_WH_LEFT,  KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_CAPS,
    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_DELETE,                                      KC_INSERT,      KC_MS_WH_RIGHT, KC_MS_WH_DOWN,  KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,                                                                                                 KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
                                                                                                    DEL_WORD_TERMINAL, KC_TRANSPARENT, CG_TOGG, SHOW_OS,
                                                                                                                    KC_HOME,        KC_PGUP,
                                                                                    DEL_WORD,LSFT(KC_ENTER), KC_END,                KC_PGDOWN,      KC_TRANSPARENT, KC_TRANSPARENT
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
              tap_code16(LCTL(KC_BSPACE));
              } else { //osx
              tap_code16(LALT(KC_BSPACE));
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

// Tap dance actions

void dance_left_select_finished (qk_tap_dance_state_t *state, void *user_data) {
  keymap_config.raw = eeconfig_read_keymap();
  if (state->count == 1) { //1 tap, select word to left
    if(keymap_config.swap_lctl_lgui){ //Linux
        tap_code16(RSFT(LCTL(KC_LEFT)));
      } else { //osx
        tap_code16(RSFT(LALT(KC_LEFT)));           
    }
  } else { //2 taps, select to beginning of line
      if(keymap_config.swap_lctl_lgui){ //Linux
        tap_code16(RSFT(KC_HOME));
      } else { //osx
        tap_code16(RSFT(LCTL(KC_LEFT)));           
    }
  }
}

void dance_right_select_finished (qk_tap_dance_state_t *state, void *user_data) {
  keymap_config.raw = eeconfig_read_keymap();
  if (state->count == 1) { //1 tap, select word to right
    if(keymap_config.swap_lctl_lgui){ //Linux
        tap_code16(RSFT(LCTL(KC_RIGHT)));
      } else { //osx
        tap_code16(RSFT(LALT(KC_RIGHT)));           
    }
  } else { //2 taps, select to end of line
      if(keymap_config.swap_lctl_lgui){ //Linux
        tap_code16(RSFT(KC_END));
      } else { //osx
        tap_code16(RSFT(LCTL(KC_RIGHT)));           
    }
  }
}

void dance_left_term_finished (qk_tap_dance_state_t *state, void *user_data) {
  if (state->count == 1) { //1 tap, move 1 word left
    tap_code16(MOVE_LEFT_TERMINAL);
  } else { //2 taps, all the way left in terminal
    keymap_config.raw = eeconfig_read_keymap();
    if(keymap_config.swap_lctl_lgui){ //Linux
        tap_code16(KC_HOME);
      } else { //osx
        tap_code16(RSFT(KC_HOME));           
    }  
  }
}

void dance_right_term_finished (qk_tap_dance_state_t *state, void *user_data) {
  if (state->count == 1) { //1 tap, move 1 word right
    tap_code16(MOVE_RIGHT_TERMINAL);
  } else { //2 taps, all the way right in terminal
    keymap_config.raw = eeconfig_read_keymap();
    if(keymap_config.swap_lctl_lgui){ //Linux
        tap_code16(KC_END);
      } else { //osx
        tap_code16(RSFT(KC_END));           
    }  
  }
}

//Tap Dance Definitions
qk_tap_dance_action_t tap_dance_actions[] = {
  [TD_SELECT_LEFT]  = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_left_select_finished, NULL),
  [TD_SELECT_RIGHT]  = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_right_select_finished, NULL),
  [TD_LEFT_TERM]  = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_left_term_finished, NULL),
  [TD_RIGHT_TERM]  = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_right_term_finished, NULL),
  
  [TD_VOL_DOWN_MUTE] = ACTION_TAP_DANCE_DOUBLE(KC_VOLD, KC_MUTE),
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