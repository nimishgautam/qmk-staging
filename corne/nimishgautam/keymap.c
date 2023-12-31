// Copyright 2022 Nimish Gåtam (@nimishgautam)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

uint8_t magic_case_state = 0;

#define MAGIC_CASE_OFF 0
#define MAGIC_CASE_SNAKE 1
#define MAGIC_CASE_CAMEL 2
#define MAGIC_CASE_KEBAB 3 

enum custom_key_codes {
    SHOW_WIN_LEFT = SAFE_RANGE, // show windows on tap, move active window left on hold
    NUMERIC_WIN_RIGHT, // lock to numeric layer on press, move active window right on hold
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
    OPEN_TERMINAL_HERE, //open terminal at current location in finder
    /* macros */
    PASTE_VIM, // paste in vim from system register
    ACIRCLE, // å
    ADOT, // ä
    ODOT, // ö
    COMPOSE_MACRO, // compose key for mac or linux
    SCREENSHOT, // This is theoretically reprogrammable on Linux, but Gui(Shift(4)) or Gui(4) is reserved for '4th item on favorite menu' and doesn't remap so well
    MAGIC_CASING, // magic casing -- snake_case by default, shift = camelCase, alt = kebab-case
};

//Tap Dance Declarations
enum {
  TD_MOVE_BEGIN_LINE = 0, // tap-dance, on single press move to beginning of the line, on double, output ^(vim character for beginning of line nonwhitespace char)
  TD_MOVE_END_LINE, // tap-dance, on single press move to end of the line, on double, output $ (vim character for last nonblank char on a line)
  TD_PERIOD_COMMA, // period on single press, comma on second press
};

// Mac-specific definitions of these functions
// I've changed Linux to accept these defaults

#define FINDER          LGUI(LALT(KC_SPACE)) //open the search bar for finding apps, docs in-computer, etc
#define COMPOSE_KEY    KC_SCRL //manually set on linux, to create chars via .Xcompose ()
#define COMPOSE_MAC     KC_F13 //manually set on mac using some tricks
#define X_COMPOSE_KEY    X_SCROLL_LOCK //for use with macros
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
#define ZOOM_IN         LALT(LGUI(KC_EQL)) // mac code zoom in
#define ZOOM_OUT        LALT(LGUI(KC_MINUS)) // mac code zoom out
#define SWITCH_APP_WINDOWS LCTL(KC_GRAVE) //mac code

#define MOVE_LEFT_TERMINAL LALT(KC_LEFT) //move cursor one word left on the terminal... does not work if .inputrc is set to use vim bindings!
#define MOVE_RIGHT_TERMINAL LALT(KC_RIGHT) //move cursor one word left on the terminal... does not work if .inputrc is set to use vim bindings!
#define DEL_WORD_TERMINAL LCTL(KC_W) // delete one word back on terminal ... does not work if .inputrc is set to use vim bindings!

// I believe these only exist in linux. Send current window to one monitor left or right
// Note that they are actually LGUI, but because I've defined Linux as 'swapped' ctrl/gui,
// I have to define them 'swapped' so they become GUI when entered. This constraint doesn't exist for keycodes that 
// are directly entered via tap_16

#define SEND_WINDOW_LEFT RSFT(LCTL(KC_LEFT))
#define SEND_WINDOW_RIGHT RSFT(LCTL(KC_RIGHT))

// Window control, also only in linux
// maximize window, vertical only or horizontal only
// toggle window maximization state after maximizing it

#define MAX_VERTICAL LCTL(LGUI(RSFT(KC_F8)))
#define MAX_HORIZONTAL LCTL(LGUI(RSFT(KC_F6)))
#define TOG_WINDOW_STATE LALT(KC_F10)

enum custom_layers {
    _BASE,

    _NUMS, // triggered by left hand large thumb button
    _TEXT_NAV, // triggered by right hand large thumb button
    
    _FN_KEYS, // triggered by left hand inner button
    _TERMINAL, // triggered by the right hand inner button

    _ADJUST, // triggered from series of keys to avoid accidentally getting to it
};

// combo - press space and backspace together to get 'scroll lock', used as the compose key on my custom linux
const uint16_t PROGMEM compose_combo[] = {KC_BSPC, KC_SPACE, COMBO_END};

// combo - press the 2 larger keys on the inner part of the corne to get the search window ('finder' as I'm calling it)
const uint16_t PROGMEM search_combo[] = {LT(_NUMS, KC_ENTER),LT(_TEXT_NAV, KC_TAB), COMBO_END};

// combo - press ,. to paste in vim
const uint16_t PROGMEM vim_paste_combo[] = {KC_COMM, KC_DOT, COMBO_END};

// combo - press () to launch calculator
const uint16_t PROGMEM calculator_combo[] = {LT(_FN_KEYS,KC_LPRN),  LT(_TERMINAL,KC_RPRN), COMBO_END};

// combo - press combo+ a to get å
const uint16_t PROGMEM acircle_combo[] = { KC_BSPC, KC_SPACE, LCTL_T(KC_A),COMBO_END};

// combo - press combo+ l to get ä
const uint16_t PROGMEM adot_combo[] = {KC_BSPC, KC_SPACE, RALT_T(KC_L), COMBO_END};

// combo - press combo+ ; to get ö
const uint16_t PROGMEM odot_combo[] = {KC_BSPC, KC_SPACE, RCTL_T(KC_SCLN),COMBO_END};

// combo - press top row (index and middle) to get a +
const uint16_t PROGMEM plus_combo[] = {KC_U, KC_I,COMBO_END};

// combo - press top row (middle and ring) to get =
const uint16_t PROGMEM equals_combo[] = {KC_I, KC_O,COMBO_END};

// combo - press middle inner buttons to get a &
const uint16_t PROGMEM ampersand_combo[] = {KC_G, KC_H,COMBO_END};

// combo - press right middle + space to get underscore
const uint16_t PROGMEM underscore_combo[] = {KC_SPACE, RSFT_T(KC_K),COMBO_END};

// combo - press left top row (middle and ring) for up
const uint16_t PROGMEM up_combo[] = {KC_W, KC_E,COMBO_END};

// combo - press left bottom row (middle and ring) for down
const uint16_t PROGMEM down_combo[] = {KC_X, KC_C,COMBO_END};;

// combo - press left middle and ring for left
const uint16_t PROGMEM left_combo[] = {LALT_T(KC_S),LSFT_T(KC_D),COMBO_END};

// combo - press left index and middle for right
const uint16_t PROGMEM right_combo[] = {LSFT_T(KC_D), LGUI_T(KC_F),COMBO_END};

// combo - press both middle finger up to get emoji keyboard
const uint16_t PROGMEM emoji_combo[] = {KC_E, KC_I,COMBO_END};

// combo - press both index fingers to scroll down
const uint16_t PROGMEM scrolldown_combo[] = {LGUI_T(KC_F), RGUI_T(KC_J),COMBO_END};

// combo - press both middle fingers to scroll up
const uint16_t PROGMEM scrollup_combo[] = {LSFT_T(KC_D), RSFT_T(KC_K),COMBO_END};

combo_t key_combos[] = {
    COMBO(compose_combo, COMPOSE_MACRO),
    COMBO(search_combo, FINDER),
    COMBO(calculator_combo, CALCULATOR),
    /* macros */
    COMBO(vim_paste_combo, PASTE_VIM),
    COMBO(acircle_combo, ACIRCLE),
    COMBO(adot_combo, ADOT),
    COMBO(odot_combo, ODOT), 
    /* defined keys */
    COMBO(plus_combo, KC_PLUS),
    COMBO(equals_combo, KC_EQL),
    COMBO(ampersand_combo, KC_AMPERSAND),
    COMBO(underscore_combo, KC_UNDS),
    COMBO(up_combo, KC_UP),
    COMBO(down_combo, KC_DOWN),
    COMBO(left_combo, KC_LEFT),
    COMBO(right_combo, KC_RIGHT),
    COMBO(emoji_combo, EMOJI_KBD),
    COMBO(scrolldown_combo, KC_MS_WH_DOWN),
    COMBO(scrollup_combo, KC_MS_WH_UP),
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_BASE] = LAYOUT_split_3x6_3(  //basic
  //,-------------------------------------------------------------------------.                    ,-------------------------------------------------------------------------.
      MAGIC_CASING,    KC_Q,         KC_W,         KC_E,         KC_R,         KC_T,                      KC_Y, KC_U,         KC_I,         KC_O,         KC_P,             KC_MINUS,
  //|-----------+-------------+-------------+------------+-------------+------|                    |-----+------------+-------------+-------------+-----------------+--------|
      KC_ESCAPE, LCTL_T(KC_A), LALT_T(KC_S), LSFT_T(KC_D), LGUI_T(KC_F), KC_G,                      KC_H, RGUI_T(KC_J), RSFT_T(KC_K), RALT_T(KC_L), RCTL_T(KC_SCLN), KC_QUOT,
  //|-----------+-------------+-------------+------------+-------------+------|                    |-----+------------+-------------+-------------+-----------------+--------|
      LT(0, SHOW_WIN_LEFT),  KC_Z, KC_X,     KC_C,        KC_V,          KC_B,                      KC_N, KC_M,         KC_COMM, KC_DOT,  KC_SLASH,  LT(0, NUMERIC_WIN_RIGHT),
  //|-----------------------+-----+---------+------------+-------------+------|                    |-----+------------+--------+--------+----------+-------------------------|
                                LT(_FN_KEYS,KC_LPRN),     KC_BSPC,       LT(_NUMS, KC_ENTER),       LT(_TEXT_NAV, KC_TAB),     KC_SPACE, LT(_TERMINAL,KC_RPRN)
                               //`--------------------------------------------------------------'   `----------------------------------------------------------'

  ),

  [_NUMS] = LAYOUT_split_3x6_3( //numbers on the right, left mostly free
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
     QK_BOOT, KC_TRANSPARENT,KC_LBRC, KC_RBRC, KC_TRANSPARENT,KC_TRANSPARENT,                                 KC_CIRCUMFLEX, KC_7,  KC_8,  KC_9,  KC_TRANSPARENT, KC_PIPE,
  //|--------+--------+--------+--------+--------+--------|                                                   |--------+--------+--------+--------+--------+--------|
      TO(_BASE), KC_LCTL, KC_LALT, KC_LSFT, KC_LGUI, KC_TRANSPARENT,                                           KC_ENTER,      KC_4,  KC_5,  KC_6,  KC_BSLS,    KC_CAPS,
  //|--------+--------+--------+--------+--------+--------|                                                    |--------+--------+--------+--------+--------+--------|
      LOCK_SCREEN, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,          TD(TD_PERIOD_COMMA), KC_1,  KC_2,  KC_3, KC_SLASH, KC_TRANSPARENT,
  //|--------+--------+--------+--------+--------+--------+--------|                                    |--------+--------+--------+--------+-C```-------+--------+--------|
                                          KC_TRANSPARENT, KC_TRANSPARENT, KC_ENTER                 , KC_HASH  ,  KC_ASTR, KC_0
                                      //`--------------------------'                                      `--------------------------'
  ),

  [_TEXT_NAV] = LAYOUT_split_3x6_3( //nav on the left, right mostly free
  /**
   * Right hand is pressing the thumb key, so all modifiers on the right. Left hand mostly free.
   * Screenshot here, feels right
   * Curly braces on same hand
  */
  //,------------------------------------------------------------.                                                           ,-----------------------------------------------------.
      SCREENSHOT, KC_EXCLAIM, KC_AT, KC_UP, KC_DOLLAR, KC_PERCENT,                                                     KC_TRANSPARENT, KC_TRANSPARENT, KC_LCBR, KC_RCBR, KC_TRANSPARENT, QK_BOOT,
  //|--------+--------+--------+--------+--------+--------|                                                           |--------+--------+--------+--------+--------+--------|
      TO(_BASE), SELECT_LEFT_LINE, KC_LEFT, KC_DOWN, KC_RIGHT,KC_END,                                            KC_TRANSPARENT, KC_RGUI, KC_RSFT, KC_RALT,KC_RCTL, KC_NUM,
  //|--------+--------+--------+--------+--------+--------|                                                           |--------+--------+--------+--------+--------+--------|
      KC_INSERT, KC_DELETE, KC_TILD, KC_GRAVE, PASTE_NOSTYLE, KC_HOME,                                 KC_TRANSPARENT, KC_MS_WH_LEFT, KC_MS_WH_RIGHT, KC_TRANSPARENT,KC_TRANSPARENT, TO(_ADJUST),
  //|--------+--------+--------+--------+--------+--------+--------|                                              |--------+--------+--------+--------+--------+--------+--------|
                                          KC_PAGE_UP,  DEL_WORD, KC_PAGE_DOWN ,                                  KC_TRANSPARENT  ,  KC_TRANSPARENT, KC_TRANSPARENT
                                      //`--------------------------'                                              `--------------------------'
  ),

   [_FN_KEYS] = LAYOUT_split_3x6_3( //fn keys,
   /**
    * Left hand pressing the inner key, left modifiers active, right FN keys
    * Also scroll lock and printscreen in here
    * 
   */
  //,-----------------------------------------------------.                                                                   ,-----------------------------------------------------.
     KC_TRANSPARENT, KC_TRANSPARENT,KC_TRANSPARENT, TOG_WINDOW_STATE, KC_TRANSPARENT, KC_TRANSPARENT,                           TD(TD_MOVE_END_LINE), KC_F7,    KC_F8,    KC_F9,    KC_F11, KC_PSCR,
  //|--------+--------+--------+--------+--------+--------|                                                                   |--------+--------+--------+--------+--------+--------|
      TO(_BASE), KC_LCTL, KC_LALT, KC_LSFT, KC_LGUI, KC_TRANSPARENT,                                                          MAX_VERTICAL, KC_F4,    KC_F5,  KC_F6,  KC_F12, KC_SCRL,
  //|--------+--------+--------+--------+--------+--------|                                                                   |--------+--------+--------+--------+--------+--------|
      KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,                         MAX_HORIZONTAL, KC_F1,    KC_F2,  KC_F3, KC_TRANSPARENT, SEND_WINDOW_RIGHT,
  //|--------+--------+--------+--------+--------+--------+--------|                                                   |--------+--------+--------+--------+--------+--------+--------|
                                          KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT ,                             ZOOM_IN  ,  ZOOM_OUT, KC_F10
                                      //`--------------------------'                                                   `--------------------------'
  ),

    [_TERMINAL] = LAYOUT_split_3x6_3( //terminal movement on the left, right mostly free
  /**
   * Right hand is pressing the thumb key, so all modifiers on the right. Left hand mostly free.
   * Screenshot here, feels right
   * Curly braces on same hand
  */
  //,-----------------------------------------------------.                                                           ,-----------------------------------------------------.
      KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, MOVE_BEGIN_LINE_TERMINAL, KC_TRANSPARENT, TD(TD_MOVE_BEGIN_LINE),                           KC_TRANSPARENT, KC_TRANSPARENT, OPEN_TERMINAL_HERE, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
  //|--------+--------+--------+--------+--------+--------|                                                           |--------+--------+--------+--------+--------+--------|
      TO(_BASE), SELECT_LEFT_WD, MOVE_LEFT_TERMINAL, MOVE_END_LINE_TERMINAL, MOVE_RIGHT_TERMINAL,SELECT_RIGHT_WD,                                            KC_TRANSPARENT, KC_RGUI, KC_RSFT, KC_RALT,KC_RCTL, KC_TRANSPARENT,
  //|--------+--------+--------+--------+--------+--------|                                                           |--------+--------+--------+--------+--------+--------|
      SEND_WINDOW_LEFT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,                                       KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,KC_TRANSPARENT, KC_TRANSPARENT,
  //|--------+--------+--------+--------+--------+--------+--------|                                              |--------+--------+--------+--------+--------+--------+--------|
                                          KC_TRANSPARENT,  DEL_WORD_TERMINAL, KC_TRANSPARENT ,                                  KC_TRANSPARENT  ,  KC_TRANSPARENT, KC_TRANSPARENT
                                      //`--------------------------'                                              `--------------------------'
  ),

      [_ADJUST] = LAYOUT_split_3x6_3( // adjust things
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
     XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      TO(_BASE), RGB_TOG, RGB_HUI, RGB_SAI, RGB_VAI, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LSFT, RGB_MOD, RGB_HUD, RGB_SAD, RGB_VAD, XXXXXXX,                       XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          XXXXXXX, XXXXXXX, CG_TOGG ,     XXXXXXX, XXXXXXX, XXXXXXX
                                      //`--------------------------'  `--------------------------'
  ) // CG_TOGG toggles gui and Ctrl (switching from mac to windows/linux)
    // the RGB buttons go backwards if shift is held when they're pressed, so shift is included
    // RGB MOD changes the mode, it's the most important one
    // right side mostly no-op so I can play with the visualization
};

// attempt to shrink firmware size -- this is for magic replacement of keys (not mods)
uint16_t keycode_config(uint16_t keycode) {
    return keycode;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {


  switch (keycode) {

    case MAGIC_CASING:
        if(record->event.pressed){
            if(magic_case_state ){
                // was on, turned it off
                magic_case_state = MAGIC_CASE_OFF;
            }
            else {
                //pressed, set case
                if(get_mods() == 0){
                    magic_case_state = MAGIC_CASE_SNAKE;
                }
                if(get_mods() & MOD_MASK_SHIFT){
                    magic_case_state = MAGIC_CASE_CAMEL;
                } 
                if (get_mods() & MOD_MASK_ALT){
                    magic_case_state = MAGIC_CASE_KEBAB;
                }
            }
        }
        return false;
    break;
    case KC_SPACE:
        if(magic_case_state){
            if(record->event.pressed){
                if (magic_case_state == MAGIC_CASE_SNAKE){
                    tap_code16(KC_UNDS);
                }
                if (magic_case_state == MAGIC_CASE_KEBAB){
                    tap_code16(KC_MINUS);
                }
                if (magic_case_state == MAGIC_CASE_CAMEL){
                    add_oneshot_mods(MOD_LSFT);
                }
            }
            return false; // do not process space any more
        }
    return true; // just return out otherwise
    break;

    // as of this writing, you can't do a layer tap (LT)
    // and also send a shifted code, like left parens
    // If you call such a function, it'll do the layer shift but
    // it'll ignore the key code on tap... this is the workaround

    case LT(_FN_KEYS,KC_LPRN): // Shift to _NUMS layer on hold, but send left paren on press
        if (record->tap.count && record->event.pressed) {
            tap_code16(KC_LPRN);
            return false;
        }
    break;
    case LT(_TERMINAL,KC_RPRN): // Shift to _NUMS on hold, send right parens on press
        if (record->tap.count && record->event.pressed) {
            tap_code16(KC_RPRN);
            return false;
        }
    break;

    case LT(0,SHOW_WIN_LEFT):
            if (record->tap.count && record->event.pressed) {
                tap_code16(SHOW_WINDOWS); // Intercept tap function
            } else if (record->event.pressed) {
                tap_code16(WINDOW_LEFT); // Intercept hold function
            }
        return false;
        break;

    case LT(0, NUMERIC_WIN_RIGHT):
            if (record->tap.count && record->event.pressed) {
                layer_on(_NUMS);// Intercept tap function
            } else if (record->event.pressed) {
                tap_code16(WINDOW_RIGHT); // Intercept hold function
            }
        return false;
        break;

    case PASTE_VIM:
        if (record->event.pressed){
            SEND_STRING(SS_TAP(X_ESCAPE)"\"+pi");
        }
        return false;
        break;

    //only read the keymap config if it's one of the below cases (instead of every time)
    case DEL_WORD:
    case SELECT_LEFT_WD:
    case SELECT_RIGHT_WD:
    case SELECT_LEFT_LINE:
    case SELECT_RIGHT_LINE:
    case MOVE_LEFT_WD:
    case MOVE_RIGHT_WD:
    case MOVE_LEFT_LINE:
    case MOVE_RIGHT_LINE:
    case PASTE_NOSTYLE:
    case MOVE_BEGIN_LINE_TERMINAL:
    case MOVE_END_LINE_TERMINAL:
    case ACIRCLE:
    case ADOT:
    case ODOT:
    case COMPOSE_MACRO:
    case SCREENSHOT:
    case OPEN_TERMINAL_HERE:


        if(record->event.pressed) {
            keymap_config.raw = eeconfig_read_keymap();
            switch (keycode){
                case DEL_WORD:
                    if(keymap_config.swap_lctl_lgui){ //Linux
                        tap_code16(LCTL(KC_BSPC));
                    } else { //osx
                        tap_code16(LALT(KC_BSPC));
                    }
                break;
                case SELECT_LEFT_WD:
                    if(keymap_config.swap_lctl_lgui){ //Linux
                        tap_code16(RSFT(LCTL(KC_LEFT)));
                    } else { //osx
                        tap_code16(RSFT(LALT(KC_LEFT)));
                    }
                break;
                case SELECT_RIGHT_WD:
                    if(keymap_config.swap_lctl_lgui){ //Linux
                        tap_code16(RSFT(LCTL(KC_RIGHT)));
                    } else { //osx
                        tap_code16(RSFT(LALT(KC_RIGHT)));
                    }
                break;
                case SELECT_LEFT_LINE:
                    if(keymap_config.swap_lctl_lgui){ //Linux
                        tap_code16(RSFT(KC_HOME));
                    } else { //osx
                        tap_code16(RSFT(LCTL(KC_LEFT)));
                    }
                break;
                case SELECT_RIGHT_LINE:
                    if(keymap_config.swap_lctl_lgui){ //Linux
                        tap_code16(RSFT(KC_END));
                    } else { //osx
                        tap_code16(RSFT(LCTL(KC_RIGHT)));
                    }
                break;
                case MOVE_LEFT_WD:
                    if(keymap_config.swap_lctl_lgui){ //Linux
                        tap_code16(LCTL(KC_LEFT));
                    } else { //osx
                        tap_code16(LALT(KC_LEFT));
                    }
                break;
                case MOVE_RIGHT_WD:
                    if(keymap_config.swap_lctl_lgui){ //Linux
                        tap_code16(LCTL(KC_RIGHT));
                    } else { //osx
                        tap_code16(LALT(KC_RIGHT));
                    }
                break;
                case MOVE_LEFT_LINE:
                    if(keymap_config.swap_lctl_lgui){ //Linux
                        tap_code16(KC_HOME);
                    } else { //osx
                        tap_code16(LGUI(KC_LEFT)); //GUI for move, shift-ctl for highlight... thanks mac!
                    }
                break;
                case MOVE_RIGHT_LINE:
                    if(keymap_config.swap_lctl_lgui){ //Linux
                        tap_code16(KC_END);
                    } else { //osx
                        tap_code16(LGUI(KC_RIGHT)); //GUI for move, shift-ctl for highlight... thanks mac!
                    }
                break;
                case PASTE_NOSTYLE:
                    if(keymap_config.swap_lctl_lgui){ //Linux
                        tap_code16(LCTL(RSFT(KC_V)));
                    } else { //osx
                        tap_code16(LGUI(LALT(LSFT(KC_V))));
                    }
                break;
                case MOVE_BEGIN_LINE_TERMINAL:
                    if(keymap_config.swap_lctl_lgui){ //Linux
                        tap_code16(KC_HOME);
                    } else { //osx
                        tap_code16(LSFT(KC_HOME));
                    }
                break;
                case MOVE_END_LINE_TERMINAL:
                    if(keymap_config.swap_lctl_lgui){ //Linux
                        tap_code16(KC_END);
                    } else { //osx
                        tap_code16(LSFT(KC_END));
                    }
                break;
                case ACIRCLE: // å
                    if(keymap_config.swap_lctl_lgui){ //Linux
                        SEND_STRING(SS_TAP(X_COMPOSE_KEY)"aa");
                    } else { //osx
                        tap_code16(LALT(KC_A));
                    }
                break;
                case ADOT: // ä
                    if(keymap_config.swap_lctl_lgui){ //Linux
                        SEND_STRING(SS_TAP(X_COMPOSE_KEY)"a\"");
                    } else { //osx
                        SEND_STRING(SS_LALT("u")"a");
                    }
                break;
                case ODOT: // ö
                    if(keymap_config.swap_lctl_lgui){ //Linux
                        SEND_STRING(SS_TAP(X_COMPOSE_KEY)"o\"");
                    } else { //osx
                        SEND_STRING(SS_LALT("u")"o");
                    }
                break;
                case COMPOSE_MACRO:
                    if(keymap_config.swap_lctl_lgui){ //Linux
                        tap_code16(COMPOSE_KEY);
                    } else { //osx
                        tap_code16(COMPOSE_MAC);
                    }
                break;
                case SCREENSHOT:
                    if(keymap_config.swap_lctl_lgui){ //Linux
                        tap_code16(KC_PSCR);
                    } else { //osx
                        tap_code16(LGUI(LSFT(KC_4)));
                    }
                break;
                case OPEN_TERMINAL_HERE:
                    if(keymap_config.swap_lctl_lgui){ //Linux
                        tap_code16(LSFT(KC_F10));
                        tap_code16(KC_E);
                    } else { //osx
                        tap_code16(LCTL(KC_F10));
                    }
                break;
            }
        }

    return false;
    break;

  }
  return true;
}

void dance_left_finished (tap_dance_state_t *state, void *user_data) {
  if (state->count == 1) { //1 tap, move to line left
    keymap_config.raw = eeconfig_read_keymap();
    if(keymap_config.swap_lctl_lgui){ //Linux
        tap_code16(KC_HOME);
    } else { //osx
    tap_code16(LGUI(KC_LEFT));
    }
  } else { //2 taps, make a circumflex
    tap_code16(KC_CIRC);
  }
}

void dance_right_finished (tap_dance_state_t *state, void *user_data) {
  if (state->count == 1) { // 1 tap, move line right
       keymap_config.raw = eeconfig_read_keymap();
    if(keymap_config.swap_lctl_lgui){ //Linux
        tap_code16(KC_END);
    } else { //osx
    tap_code16(LGUI(KC_RIGHT));
    }
  } else { //2 taps, dollar
    tap_code16(KC_DOLLAR);
  }
}

//Tap Dance Definitions
tap_dance_action_t tap_dance_actions[] = {
  [TD_MOVE_BEGIN_LINE]  = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_left_finished, NULL),
  [TD_MOVE_END_LINE]  = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_right_finished, NULL),
  [TD_PERIOD_COMMA] = ACTION_TAP_DANCE_DOUBLE(KC_DOT, KC_COMMA),
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
