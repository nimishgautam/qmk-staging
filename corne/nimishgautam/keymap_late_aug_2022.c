
#include QMK_KEYBOARD_H
#include <stdio.h>

extern keymap_config_t keymap_config;

enum custom_key_codes {
    SHOW_WIN_LEFT = SAFE_RANGE, // show windows on tap, move active window left on hold
    NUMERIC_WIN_RIGHT, // lock to numeric layer on press, move active window right on hold
    DEL_WORD,
};

// Mac-specific definitions of these functions
// No memory costs this way, but means they can't be changed on the fly

#define SCREENSHOT      LGUI(LSFT(KC_4))
#define FINDER          LGUI(LALT(KC_SPACE))
#define COMPOSE_KEY    KC_SCRL
#define SHOW_WINDOWS    LCTL(KC_UP)
#define WINDOW_LEFT LCTL(LGUI(LSFT(KC_LEFT)))
#define WINDOW_RIGHT LCTL(LGUI(LSFT(KC_RIGHT)))
#define SHOW_APP_WINDOWS LCTL(KC_DOWN)
#define LOCK_SCREEN     LCTL(LGUI(KC_Q))
#define EURO            LALT(LSFT(KC_2))
#define EMOJI_KBD       LCTL(LGUI(KC_SPACE))

#define _BASE 0
#define _NUMS 1
#define _NUM_MASK 2
#define _TEXT_NAV 3
#define _ADJUST 4
#define _FN_KEYS 5

// combo - press space and backspace together to get 'scroll lock', used as the compose key on my custom linux
const uint16_t PROGMEM compose_combo[] = {KC_BSPACE, KC_SPACE, COMBO_END};
const uint16_t PROGMEM search_combo[] = {LT(_FN_KEYS, KC_ENTER),LT(_TEXT_NAV, KC_PAST), COMBO_END};
combo_t key_combos[COMBO_COUNT] = {
    COMBO(compose_combo, COMPOSE_KEY),
    COMBO(search_combo, FINDER),
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_BASE] = LAYOUT_split_3x6_3(  //basic
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_TAB,     KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                    KC_Y,    KC_U,    KC_I,    KC_O,   KC_P,     KC_MINUS,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_ESCAPE, MT(MOD_LCTL, KC_A),    MT(MOD_LALT,KC_S),    MT(MOD_RSFT,KC_D),    MT(MOD_LGUI, KC_F),    KC_G,                    KC_H,    MT(MOD_RGUI,KC_J),    MT(MOD_RSFT,KC_K),    MT(MOD_RALT,KC_L), MT(MOD_LCTL,KC_SCLN), KC_QUOT,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      LT(0, SHOW_WIN_LEFT), KC_Z, KC_X,  KC_C, KC_V,  KC_B,   KC_N,                  KC_M,  KC_COMM, KC_DOT,  KC_SLASH,  LT(0, NUMERIC_WIN_RIGHT),
  //|--------+--------+--------+--------+--------+--------+--------|                 |--------+--------+--------+--------+--------+--------+--------|
                                         LT(_NUMS,KC_LPRN),   KC_BSPACE,  LT(_FN_KEYS, KC_ENTER),     LT(_TEXT_NAV, KC_PAST),   KC_SPACE, LT(_NUMS,KC_RPRN)
                                      //`--------------------------'                    `--------------------------'

  ),

  [_NUMS] = LAYOUT_split_3x6_3( //numbers
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
     SCREENSHOT,   KC_EXCLAIM,KC_AT, KC_HASH, KC_DOLLAR,KC_PERCENT,            KC_CIRCUMFLEX,    KC_7,    KC_8,    KC_9,    KC_TRANSPARENT, KC_PIPE, 
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      TO(_BASE), KC_LCTL, KC_LALT, KC_RSFT, KC_LGUI,KC_PLUS,         KC_EQL, KC_4,  KC_5,  KC_6,  KC_BSLASH, KC_TRANSPARENT,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LCBR, KC_LBRACKET, KC_TILD, KC_GRAVE, KC_TRANSPARENT, KC_AMPERSAND,        KC_TRANSPARENT, KC_1,  KC_2,  KC_3, KC_RBRACKET, KC_RCBR,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+-C```-------+--------+--------|
                                          KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT , KC_TRANSPARENT  ,  KC_UNDS, KC_0
                                      //`--------------------------'  `--------------------------'
  ),

     [_NUM_MASK] = LAYOUT_split_3x6_3( //NUM MASK
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
     KC_TRANSPARENT, KC_TRANSPARENT,KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,KC_TRANSPARENT,      KC_TRANSPARENT, KC_7,    KC_8,    KC_9, KC_TRANSPARENT, KC_TRANSPARENT, 
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      TO(_BASE), KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,KC_TRANSPARENT,         KC_TRANSPARENT, KC_4,  KC_5,  KC_6, KC_TRANSPARENT, KC_TRANSPARENT,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
     KC_TRANSPARENT, KC_TRANSPARENT,KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,      KC_TRANSPARENT, KC_1,  KC_2,  KC_3,KC_TRANSPARENT, KC_TRANSPARENT,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT , KC_TRANSPARENT  ,  KC_TRANSPARENT, KC_0
                                      //`--------------------------'  `--------------------------'
  ),

  [_TEXT_NAV] = LAYOUT_split_3x6_3( //text nav
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      LOCK_SCREEN, KC_END, KC_HOME, KC_UP, KC_PAGE_UP, KC_CIRC,                    KC_DLR, KC_MS_WH_UP, EMOJI_KBD, FINDER, KC_TRANSPARENT, RESET,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      TO(_BASE), KC_TRANSPARENT, KC_LEFT, KC_DOWN, KC_RIGHT,KC_CAPS,              KC_MS_WH_LEFT, KC_RGUI, KC_RSFT, KC_RALT,KC_RCTRL, KC_TRANSPARENT,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_INSERT, KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_PSCR, KC_TRANSPARENT,                    KC_MS_WH_RIGHT, KC_MS_WH_DOWN, KC_TRANSPARENT, KC_TRANSPARENT,KC_TRANSPARENT, TO(_ADJUST),
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_DELETE,  DEL_WORD, KC_PAGE_DOWN , KC_TRANSPARENT  ,  KC_TRANSPARENT, KC_TRANSPARENT
                                      //`--------------------------'  `--------------------------'
  ),

    [_ADJUST] = LAYOUT_split_3x6_3( // adjust things
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
     XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      TO(_BASE), RGB_TOG, RGB_HUI, RGB_SAI, RGB_VAI, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LSFT, RGB_MOD, RGB_HUD, RGB_SAD, RGB_VAD, XXXXXXX,                       XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          CG_TOGG, XXXXXXX, XXXXXXX ,     TO(_BASE), XXXXXXX, XXXXXXX
                                      //`--------------------------'  `--------------------------'
  ), // CG_TOGG toggles gui and Ctrl (switching from mac to windows/linux)
    // the RGB buttons go backwards if shift is held when they're pressed, so shift is included

   [_FN_KEYS] = LAYOUT_split_3x6_3( //fn keys
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
     KC_TRANSPARENT, KC_TRANSPARENT,KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,      KC_F11, KC_F7,    KC_F8,    KC_F9,    KC_F14, KC_TRANSPARENT, 
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      TO(_BASE), KC_LCTL, KC_LALT, KC_RSFT, KC_LGUI, KC_TRANSPARENT,         KC_F12, KC_F4,  KC_F5,  KC_F6,  KC_F15, KC_TRANSPARENT,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,                           KC_F13, KC_F1,  KC_F2,  KC_F3, KC_F16, KC_TRANSPARENT,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT , KC_TRANSPARENT  ,  KC_TRANSPARENT, KC_F10
                                      //`--------------------------'  `--------------------------'
  )
  
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {


  switch (keycode) {

    // as of this writing, you can't do a layer tap (LT)
    // and also send a shifted code, like left parens
    // If you call such a function, it'll do the layer shift but 
    // it'll ignore the key code on tap... this is the workaround
 
    case LT(_NUMS,KC_LPRN): // Shift to _NUMS layer on hold, but send left paren on press
        if (record->tap.count && record->event.pressed) {
            tap_code16(KC_LPRN); 
            return false; 
        }
    break;
    case LT(_NUMS,KC_RPRN): // Shift to _NUMS on hold, send right parens on press
        if (record->tap.count && record->event.pressed) {
            tap_code16(KC_RPRN); 
            return false; 
        }
    break;
    case LT(_TEXT_NAV, KC_ASTR): // Shift to _TEXT_NAV on hold, send * on press
        if (record->tap.count && record->event.pressed) {
            tap_code16(KC_ASTR); 
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
                layer_on(_NUM_MASK);// Intercept tap function
            } else if (record->event.pressed) {
                tap_code16(WINDOW_RIGHT); // Intercept hold function 
            }
        return false;
        break;

    case LT(_TEXT_NAV, KC_COMM):
        if(record->event.pressed){
            if(!record->tap.count){
                register_mods(MOD_LSFT);}
        }
        else{
            unregister_mods(MOD_LSFT);
        }
        return true; // keep processing key!
        break;
    
    case DEL_WORD: //fallbacks for other things like this...

        if(record->event.pressed) {
            keymap_config.raw = eeconfig_read_keymap();
            switch (keycode){
                case DEL_WORD:
                    if(keymap_config.swap_lctl_lgui){ //Linux
                        tap_code16(LCTL(KC_BSPACE));
                    } else { //osx
                        tap_code16(LALT(KC_BSPACE));
                    }
                break;
            }
        }

    return false;
    break;

  }
  return true;
}

bool get_permissive_hold(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case MT(MOD_RSFT,KC_D): // for modtap shift
        case MT(MOD_RSFT,KC_K):
            // Immediately select the hold action when another key is tapped.
            return true;
        default:
            // Do not select the hold action when another key is tapped.
            return false;
    }
}


#ifdef OLED_ENABLE
oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    /*
  if (is_keyboard_master()) {
    return OLED_ROTATION_270;  // flips the display 270 degrees if main
  }
  else{
    return OLED_ROTATION_180;
  }
  return rotation;
  */
  return OLED_ROTATION_270;
}


void oled_render_layer_state(void) {
    uint8_t layer = get_highest_layer(layer_state);
    switch (layer) {
        case _BASE:
            oled_write_ln_P(PSTR("Base"), false);
            //rgblight_sethsv(HSV_OFF);
            rgblight_sethsv(HSV_WHITE);
            break;
        case _NUMS:
            oled_write_ln_P(PSTR("Nums"), false);
            rgblight_sethsv(HSV_GREEN);
            break;
        case _NUM_MASK:
            oled_write_ln_P(PSTR("NumX"), false);
            rgblight_sethsv(HSV_PINK);
            break;
        case _TEXT_NAV:
            oled_write_ln_P(PSTR("Text"), false);
            rgblight_sethsv(HSV_BLUE);
            break;
        case _ADJUST:
            oled_write_ln_P(PSTR("Adj"), false);
            rgblight_sethsv(HSV_ORANGE);
            break;
        case _FN_KEYS:
            oled_write_ln_P(PSTR("Fn"), false);
            rgblight_sethsv(HSV_PURPLE);
            break;   
        default:
            break;
    }

   keymap_config.raw = eeconfig_read_keymap();
    if(keymap_config.swap_lctl_lgui){
        oled_write_ln_P(PSTR("Linux"), false);
    }
    else {
        oled_write_ln_P(PSTR("OSX"), false);
    }

    led_t led_state = host_keyboard_led_state();
    if(led_state.caps_lock){
        oled_write_ln_P(PSTR("CAPS"), false);
        rgblight_sethsv(HSV_RED);
    } else {
        oled_write_ln_P(PSTR(" "), false);
    }
    if(get_mods() & MOD_MASK_SHIFT){
        oled_write_ln_P(PSTR("SHIFT"), false);
        if(layer == _BASE){rgblight_sethsv(HSV_RED);}
        if(layer == _NUMS){rgblight_sethsv(HSV_GREEN);}
    }
    if(get_mods() & MOD_MASK_CTRL){
        oled_write_ln_P(PSTR("ctrl"), false);
        rgblight_sethsv(HSV_MAGENTA);
    }
    if(get_mods() & MOD_MASK_ALT){
        oled_write_ln_P(PSTR("alt"), false);
        rgblight_sethsv(HSV_YELLOW);
    }
    if(get_mods() & MOD_MASK_GUI){
        oled_write_ln_P(PSTR("GUI"), false);
        rgblight_sethsv(HSV_TEAL);
    }
    if(!get_mods()){
        oled_write_ln_P(PSTR(" "), false);
        oled_write_ln_P(PSTR(" "), false);
        oled_write_ln_P(PSTR(" "), false);
    }
 
}



/* https://joric.github.io/qle/ */


// just write the layer state on both oleds
bool oled_task_user(void) {
    if (is_keyboard_master()) {
        oled_render_layer_state();
    } else {
            led_t led_state = host_keyboard_led_state();
            if(led_state.caps_lock){
            oled_write_ln_P(PSTR("CAPS"), false);
    } else {
        oled_write_ln_P(PSTR(" "), false);
    }
        /*oled_write("                     ", true);
        oled_write("  Nimish's Keyboard  ", true);
        oled_write("                     ", true);*/
    }
    return false;
}



#endif