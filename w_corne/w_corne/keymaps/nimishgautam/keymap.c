// Copyright 2022 Nimish Gåtam (@nimishgautam)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

#include "w_corne.h"
#include "os_detection.h"

#include "ng_key_definitions.h"
#include "ng_tapdances_corne.c"
#include "ng_layer_definitions.h"
#include "ng_combos.c"

// layout not included because layout is backwards here and uses a different structure

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

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_BASE] = LAYOUT(  //basic -- RIGHT HAND BACKWARDS!!!
    //,-------------------------------------------------------------------------.                    ,-------------------------------------------------------------------------.
      MAGIC_CASING,    KC_Q,         KC_W,         KC_E,         KC_R,         KC_T,                      KC_MINUS, KC_P,         KC_O,         KC_I,         KC_U,             KC_Y,
  //|-----------+-------------+-------------+------------+-------------+------|                    |-----+------------+-------------+-------------+-----------------+--------|
      KC_ESCAPE, LCTL_T(KC_A), LALT_T(KC_S), LSFT_T(KC_D), LGUI_T(KC_F), KC_G,                      KC_QUOT, RCTL_T(KC_SCLN), RALT_T(KC_L), RSFT_T(KC_K), RGUI_T(KC_J), KC_H,
  //|-----------+-------------+-------------+------------+-------------+------|                    |-----+------------+-------------+-------------+-----------------+--------|
      LT(0, SHOW_WIN_LEFT),  KC_Z, KC_X,     KC_C,        KC_V,          KC_B,                      LT(0, NUMERIC_WIN_RIGHT), KC_SLASH,     KC_DOT, KC_COMM,     KC_M,  KC_N,
  //|-----------------------+-----+---------+------------+-------------+------|                    |-----+------------+--------+--------+----------+-------------------------|
                                LT(_FN_KEYS,KC_LPRN),     KC_BSPC,       LT(_NUMS, KC_ENTER),       LT(_TERMINAL,KC_RPRN) , KC_SPACE, LT(_TEXT_NAV, KC_TAB)
                               //`--------------------------------------------------------------'   `----------------------------------------------------------'

  ),

  [_NUMS] = LAYOUT( //numbers on the right, left mostly free -- RIGHT HAND BACKWARDS!!!
  /**
   * The left outer key is probably pressed here (enter) so it's probably being used as a numpad. All the numpad stuff is on the right
   * However, this is also the place for the | and \ symbols (and ^ since that's where I'd naturally reach for it)
   * slash falls to slash in the lower layer but I wanted to make it explicit here.
   * Also the numlock is here.
   * 
   * On the left, QKBOOT so you can reset one-handed if needed. Also [] for ease, all the left-hand mods
   * 
   * The right thumb should be enter, but I use the key for hash already since I make markup/bullet lists quite a bit to use that symbol
   * 
   * Lock screen here since it's hard to accidentally trigger also
  */
  //,-----------------------------------------------------.                                                   ,-----------------------------------------------------.
     QK_BOOT, KC_TRANSPARENT,KC_LBRC, KC_RBRC, KC_TRANSPARENT,KC_TRANSPARENT,                                 KC_PIPE, KC_TRANSPARENT,  KC_9,  KC_8,  KC_7, KC_CIRCUMFLEX,
  //|--------+--------+--------+--------+--------+--------|                                                   |--------+--------+--------+--------+--------+--------|
      TO(_BASE), KC_LCTL, KC_LALT, KC_LSFT, KC_LGUI, KC_TRANSPARENT,                                           KC_CAPS,      KC_BSLS,  KC_6,  KC_5,  KC_4,    KC_ENTER,
  //|--------+--------+--------+--------+--------+--------|                                                    |--------+--------+--------+--------+--------+--------|
      LOCK_SCREEN, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,           KC_TRANSPARENT, KC_SLASH,  KC_3,  KC_2, KC_1, TD(TD_PERIOD_COMMA),
  //|--------+--------+--------+--------+--------+--------+--------|                                    |--------+--------+--------+--------+-C```-------+--------+--------|
                                          KC_BRID, KC_BRIU, KC_ENTER                 , KC_0  ,  KC_ASTR, KC_HASH
                                      //`--------------------------'                                      `--------------------------'
  ),

  [_TEXT_NAV] = LAYOUT( //nav on the left, right mostly free -- RIGHT HAND BACKWARDS!!!
  /**
   * Right hand is pressing the thumb key, so all modifiers on the right. Left hand mostly free.
   * Screenshot here, feels right
   * Curly braces on same hand
  */
  //,-----------------------------------------------------.                                                           ,-----------------------------------------------------.
      SCREENSHOT, KC_EXCLAIM, KC_AT, KC_UP, KC_DOLLAR, KC_PERCENT,                                                     QK_BOOT, KC_TRANSPARENT, KC_RCBR, KC_LCBR, KC_TRANSPARENT, KC_TRANSPARENT,
  //|--------+--------+--------+--------+--------+--------|                                                           |--------+--------+--------+--------+--------+--------|
      TO(_BASE), SELECT_LEFT_LINE, KC_LEFT, KC_DOWN, KC_RIGHT,KC_END,                                            KC_NUM, KC_RCTL, KC_RALT, KC_RSFT,KC_RGUI, KC_TRANSPARENT,
  //|--------+--------+--------+--------+--------+--------|                                                           |--------+--------+--------+--------+--------+--------|
      KC_INSERT, KC_DELETE, KC_TILD, KC_GRAVE, PASTE_NOSTYLE, KC_HOME,                                 TO(_ADJUST), KC_TRANSPARENT, KC_TRANSPARENT, KC_MS_WH_RIGHT, KC_MS_WH_LEFT, KC_TRANSPARENT,
  //|--------+--------+--------+--------+--------+--------+--------|                                              |--------+--------+--------+--------+--------+--------+--------|
                                          KC_PAGE_UP,  DEL_WORD, KC_PAGE_DOWN ,                                  KC_VOLU  ,  KC_VOLD, KC_TRANSPARENT
                                      //`--------------------------'                                              `--------------------------'
  ),

   [_FN_KEYS] = LAYOUT( //fn keys -- RIGHT HAND BACKWARDS!!!
   /**
    * Left hand pressing the inner key, left modifiers active, right FN keys
    * Also scroll lock and printscreen in here
    * 
   */
  //,-----------------------------------------------------.                                                                   ,-----------------------------------------------------.
     KC_TRANSPARENT, KC_TRANSPARENT,KC_TRANSPARENT, TOG_WINDOW_STATE, KC_TRANSPARENT, KC_TRANSPARENT,                           KC_PSCR, KC_F11,    KC_F9,    KC_F8,    KC_F7, TD(TD_MOVE_END_LINE),
  //|--------+--------+--------+--------+--------+--------|                                                                   |--------+--------+--------+--------+--------+--------|
      TO(_BASE), KC_LCTL, KC_LALT, KC_LSFT, KC_LGUI, KC_TRANSPARENT,                                                          KC_SCRL, KC_F12,    KC_F6,  TD(TD_F5_CONSOLE),  KC_F4, MAX_VERTICAL,
  //|--------+--------+--------+--------+--------+--------|                                                                   |--------+--------+--------+--------+--------+--------|
      KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,                         SEND_WINDOW_RIGHT, KC_TRANSPARENT,    KC_F3,  TD(TD_F2_CONSOLE), KC_F1, MAX_HORIZONTAL,
  //|--------+--------+--------+--------+--------+--------+--------|                                                   |--------+--------+--------+--------+--------+--------+--------|
                                          KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT ,                             KC_F10  ,  ZOOM_OUT, ZOOM_IN
                                      //`--------------------------'                                                   `--------------------------'
  ),

    [_TERMINAL] = LAYOUT( //terminal movement on the left, right mostly free -- RIGHT HAND BACKWARDS!!!
  /**
   * Right hand is pressing the thumb key, so all modifiers on the right. Left hand mostly free.
   * Screenshot here, feels right
   * Curly braces on same hand
  */
  //,-----------------------------------------------------.                                                           ,-----------------------------------------------------.
      KC_TRANSPARENT, KC_TRANSPARENT, TMUX_PREV_PANE, MOVE_BEGIN_LINE_TERMINAL, TMUX_NEXT_PANE, TD(TD_MOVE_BEGIN_LINE),                           KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, OPEN_TERMINAL_HERE,  KC_TRANSPARENT, KC_TRANSPARENT,
  //|--------+--------+--------+--------+--------+--------|                                                           |--------+--------+--------+--------+--------+--------|
      TO(_BASE), SELECT_LEFT_WD, MOVE_LEFT_TERMINAL, MOVE_END_LINE_TERMINAL, MOVE_RIGHT_TERMINAL,SELECT_RIGHT_WD,                                            KC_TRANSPARENT, KC_RCTL, KC_RALT, KC_RSFT,KC_RGUI, KC_TRANSPARENT,
  //|--------+--------+--------+--------+--------+--------|                                                           |--------+--------+--------+--------+--------+--------|
      SEND_WINDOW_LEFT, KC_TRANSPARENT, TMUX_SPLIT_VERT, TMUX_CLOSE_PANE, TMUX_SPLIT_HORIZ, KC_BRK,                                       KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,KC_TRANSPARENT, KC_TRANSPARENT,
  //|--------+--------+--------+--------+--------+--------+--------|                                              |--------+--------+--------+--------+--------+--------+--------|
                                          DEL_TO_END_TERMINAL,  DEL_WORD_TERMINAL, KC_TRANSPARENT ,                                  KC_TRANSPARENT  ,  KC_TRANSPARENT, KC_TRANSPARENT
                                      //`--------------------------'                                              `--------------------------'
  ),

      [_ADJUST] = LAYOUT( // adjust things
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
     EE_CLR, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      TO(_BASE), RGB_TOG, RGB_HUI, RGB_SAI, RGB_VAI, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LSFT, RGB_MOD, RGB_HUD, RGB_SAD, RGB_VAD, XXXXXXX,                       XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          SHOW_OS, XXXXXXX, CG_TOGG ,     XXXXXXX, XXXXXXX, XXXXXXX
                                      //`--------------------------'  `--------------------------'
  ) // CG_TOGG toggles gui and Ctrl (switching from mac to windows/linux)
    // the RGB buttons go backwards if shift is held when they're pressed, so shift is included
    // RGB MOD changes the mode, it's the most important one
    // right side mostly no-op so I can play with the visualization
};


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

void keyboard_post_init_user(void) {
    if (is_keyboard_master()) {
        os_detect();
    }
}