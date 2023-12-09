
#include QMK_KEYBOARD_H
#include <stdio.h>


enum custom_key_codes {
    LSFT_LAYER_WINDOWS = SAFE_RANGE, // layer shift to NUMS with shift held down, on tap show windows
    RSFT_LAYER_WINDOWS, // same as above, but on tap show app windows
    LSFT_LAYER_COMMA, // layer shift to TEXT with shift held down, on tap ; (shift to get :, or hold down with autoshift on)
};

// Mac-specific definitions of these functions
// No memory costs this way, but means they can't be changed on the fly
#define FULLSCREEN      LGUI(LCTL(KC_F))
#define FINDER          LGUI(LALT(KC_SPACE))
#define PASTE_NOSTYLE   LGUI(LALT(KC_V))
#define UNDO            LGUI(KC_Z)
#define CUT             LGUI(KC_X)
#define COPY            LGUI(KC_C)
#define PASTE           LGUI(KC_V)
#define BOLD            LGUI(KC_B)
#define SELECT_ALL      LGUI(KC_A)
#define SAVE            LGUI(KC_S)
#define SCREENSHOT      LGUI(LSFT(KC_4))
#define DEL_WORD        LALT(KC_BSPACE)
#define SHOW_WINDOWS    LCTL(KC_UP)
#define SHOW_WINDOWS_CUSTOM LGUI(KC_UP)
#define WINDOW_LEFT LCTL(LGUI(LSFT(KC_LEFT)))
#define WINDOW_RIGHT LCTL(LGUI(LSFT(KC_RIGHT)))
#define SHOW_APP_WINDOWS LCTL(KC_DOWN)
#define LOCK_SCREEN     LCTL(LGUI(KC_Q))
#define EURO            LALT(LSFT(KC_2))
#define EMOJI_KBD       LCTL(LGUI(KC_SPACE))

#define _BASE 0
#define _NUMS 1
#define _SYMBOLS 2
#define _TEXT_NAV 3
#define _ADJUST 4
#define _FN_KEYS 5


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_BASE] = LAYOUT_split_3x6_3(  //basic
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_TAB,     KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                    KC_Y,    KC_U,    KC_I,    KC_O,   KC_P,     KC_MINUS,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_ESCAPE, MT(MOD_LCTL, KC_A),    MT(MOD_LALT,KC_S),    MT(MOD_RSFT,KC_D),    MT(MOD_LGUI, KC_F),    KC_G,                    KC_H,    MT(MOD_RGUI,KC_J),    MT(MOD_RSFT,KC_K),    MT(MOD_RALT,KC_L), MT(MOD_LCTL,KC_SCLN), KC_QUOT,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_SCRL, KC_Z, KC_X,  KC_C, KC_V,  KC_B,   KC_N,                  KC_M,  KC_COMM, KC_DOT,  KC_SLASH,  TO(_NUMS),
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

     [_SYMBOLS] = LAYOUT_split_3x6_3( //SYMBOLS
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
     KC_TRANSPARENT, KC_EXCLAIM,KC_AT, KC_HASH, KC_DOLLAR,KC_PERCENT,      KC_CIRCUMFLEX, KC_AMPERSAND,KC_ASTERISK, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, 
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      TO(_BASE), KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,KC_TRANSPARENT,         KC_TRANSPARENT, KC_TRANSPARENT,KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
     KC_TRANSPARENT, KC_TRANSPARENT,KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,      KC_TRANSPARENT, KC_TRANSPARENT,KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT , KC_TRANSPARENT  ,  KC_TRANSPARENT, KC_TRANSPARENT
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
    // KC_ASTG toggles autoshift
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
    case LT(_SYMBOLS, SHOW_WINDOWS): // Shift to SYMBOLS on hold, send special on press
        if (record->tap.count && record->event.pressed) {
            tap_code16(SHOW_WINDOWS); 
            return false; 
        }
    break;
    case LT(_SYMBOLS, KC_UNDS): // Shift to SYMBOLS on hold, send special on press
        if (record->tap.count && record->event.pressed) {
            tap_code16(KC_UNDS); 
            return false; 
        }
    break;


    case MT(MOD_LALT,KC_TILD):
        if (record->tap.count && record->event.pressed) {
            tap_code16(KC_TILD); 
            return false; 
        }
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

  }
  return true;
}


#ifdef OLED_ENABLE
oled_rotation_t oled_init_user(oled_rotation_t rotation) {
  if (is_keyboard_master()) {
    return OLED_ROTATION_270;  // flips the display 270 degrees if main
  }
  else{
    return OLED_ROTATION_180;
  }
  return rotation;
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
            rgblight_sethsv(HSV_PINK);
            break;
        case _SYMBOLS:
            oled_write_ln_P(PSTR("Symb"), false);
            rgblight_sethsv(HSV_GREEN);
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
        oled_write("                     ", true);
        oled_write("  Nimish's Keyboard  ", true);
        oled_write("                     ", true);
    }
    return false;
}


#endif