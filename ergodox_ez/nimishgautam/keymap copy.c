#include QMK_KEYBOARD_H
#include "version.h"


// Mac-specific definitions of these functions
// No memory costs this way, but means they can't be changed on the fly
#define FULLSCREEN      LGUI(LCTL(KC_F))
#define FINDER          LGUI(LALT(KC_SPACE))
#define PASTE_NOSTYLE   LGUI(LALT(KC_V))
#define SPOTLIGHT       LGUI(KC_SPACE)
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
#define SHOW_APP_WINDOWS LCTL(KC_DOWN)
#define LOCK_SCREEN     LCTL(LGUI(KC_Q))
#define EURO            LALT(LSFT(KC_2))
#define EMOJI_KBD       LCTL(LGUI(KC_SPACE))

enum custom_keycodes {
  RGB_SLD = EZ_SAFE_RANGE,
};

enum tap_dance_codes {
  DANCE_0, // printscrn normally, lock screen on double-tap
  DANCE_1, // ^ normal, select word 1 back on double-tap
  DANCE_2, // leftbracket normally, alt+ctrl+shift+L on double-tap (window left -custom shortcut)
  DANCE_7, // $ normally, select 1 word forward on double-tap
  DANCE_8, // rightbracket, alt+ctrl+shift+R on double-tap (window right - custom)
  DANCE_14, // vol down normally, mute on double-tap
};

#define _BASE 0
#define _DISABLE_HR_MODS 1
#define _NUMS 2
#define _SYMBOLS 3
#define _TEXT_NAV 4
#define _FN_KEYS 5

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_BASE] = LAYOUT_ergodox_pretty(
    TD(DANCE_0),    KC_1,           KC_2,           KC_3,           KC_4,           KC_5,           TD(DANCE_1),                                    TD(DANCE_7),    KC_6,           KC_7,           KC_8,           KC_9,           KC_0,           KC_BSLASH,
    KC_TAB,         KC_Q,           KC_W,           KC_E,           KC_R,           KC_T,           TD(DANCE_2),                                    TD(DANCE_8),    KC_Y,           KC_U,           KC_I,           KC_O,           KC_P,           KC_MINUS,
    KC_ESCAPE,      LCTL_T(KC_A),           LALT_T(KC_S),           RSFT_T(KC_D),           LGUI_T(KC_F),           KC_G,                                                                           KC_H,    RGUI_T(KC_J),     RSFT_T(KC_K),       RALT_T(KC_L),           RCTL_T(KC_SCOLON),      KC_QUOTE,
    MT(MOD_RSFT, LCTL(KC_UP)),    KC_Z,           KC_X,           KC_C,           KC_V,           KC_B,           KC_LPRN,                                        KC_RPRN,        KC_N,           KC_M,           KC_COMMA,       KC_DOT,    KC_SLASH,       MT(MOD_RSFT, RCTL(KC_DOWN)),
    MT(MOD_LCTL, LGUI(KC_TAB)),    LT(_NUMS,KC_GRAVE), LT(_NUMS, KC_HASH),    KC_LALT,        MT(MOD_LGUI, LGUI(KC_SPACE)),                                                                                                    LT(_NUMS, KC_UNDS),   KC_EQUAL,       KC_RGUI,        KC_RCTRL,       MT(MOD_RALT, LGUI(LSFT(KC_TAB))),
                                                                                                    KC_ASTG,        FINDER,LALT(LGUI(KC_SLASH)),EMOJI_KBD,
                                                                                                                    KC_LEFT,        KC_UP,
                                                                                    KC_BSPACE,      KC_ENTER,       KC_RIGHT,       KC_DOWN,        LT(_TEXT_NAV, KC_PAST),   KC_SPACE
  ),  
  [_NUMS] = LAYOUT_ergodox_pretty(
    KC_TRANSPARENT, KC_F1,          KC_F2,          KC_F3,          KC_F4,          KC_F5,          KC_TRANSPARENT,                                 KC_TRANSPARENT, KC_F6,          KC_F7,          KC_F8,          KC_F9,          KC_F10,         KC_TRANSPARENT,
    KC_TRANSPARENT, KC_1,           KC_2,           KC_3,           KC_4,           KC_5,           KC_F15,                                         KC_AUDIO_VOL_UP,KC_6,           KC_7,           KC_8,           KC_9,           KC_0,           KC_TRANSPARENT,
    TO(0),          KC_F11,         KC_F12,         KC_F13,         LGUI(LCTL(KC_F)),KC_PLUS,                                                                        KC_TRANSPARENT, KC_4,           KC_5,           KC_6,           KC_TRANSPARENT, KC_TRANSPARENT,
    KC_LCBR,        KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, LALT(LGUI(LSFT(KC_V))),KC_EQUAL,       KC_F14,                                         TD(DANCE_14),   KC_UNDS,        KC_1,           KC_2,           KC_3,           KC_BSLASH,      KC_RCBR,
    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, TG(_DISABLE_HR_MODS),                                                                                                 TG(_DISABLE_HR_MODS), KC_KP_0,        KC_KP_ASTERISK, KC_TRANSPARENT, KC_TRANSPARENT,
                                                                                                    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
                                                                                                                    LALT(LSFT(KC_LEFT)),LCTL(KC_UP),
                                                                                    LALT(KC_BSPACE),LSFT(KC_ENTER), LALT(LSFT(KC_RIGHT)),LCTL(KC_DOWN),  KC_TRANSPARENT, KC_TRANSPARENT
  ), 
  [_DISABLE_HR_MODS] = LAYOUT_ergodox_pretty(
    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,                                 KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,                                 KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
    TO(0),          KC_A,           KC_S,           KC_D,           KC_F,           KC_TRANSPARENT,                                                                 KC_TRANSPARENT,           KC_J,           KC_K,           KC_L,      KC_SCOLON, KC_TRANSPARENT,
    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,                                 KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,                                                                                                 KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
                                                                                                    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
                                                                                                                    KC_TRANSPARENT, KC_TRANSPARENT,
                                                                                    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT
  ),
  [_SYMBOLS] = LAYOUT_ergodox_pretty(
    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,                                 KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
    KC_TRANSPARENT, KC_EXLM,        KC_AT,          KC_HASH,        KC_DLR,         KC_PERC,        KC_TRANSPARENT,                                 KC_TRANSPARENT, KC_CIRC,        KC_AMPR,        KC_ASTR,        KC_LPRN,        KC_RPRN,        KC_TRANSPARENT,
    TO(0),          KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,                                                                 KC_LEFT,        KC_DOWN,        KC_UP,          KC_RIGHT,       KC_TRANSPARENT, KC_TRANSPARENT,
    KC_TRANSPARENT, KC_TILD,        KC_GRAVE,       KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,                                 KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
    KC_TRANSPARENT, KC_TRANSPARENT, TO(0),          KC_TRANSPARENT, KC_TRANSPARENT,                                                                                                 KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
                                                                                                    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
                                                                                                                    KC_TRANSPARENT, KC_TRANSPARENT,
                                                                                    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT
  ),
  [_TEXT_NAV] = LAYOUT_ergodox_pretty(
    LGUI(LCTL(KC_Q)),KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,                                 KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, RESET,
    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, LGUI(KC_T),                                     LGUI(KC_W),     KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
    TO(0),          LALT(LSFT(KC_LEFT)),KC_TRANSPARENT, KC_TRANSPARENT, LALT(LSFT(KC_RIGHT)),KC_CAPS,                                                                 KC_MS_WH_LEFT,  KC_MS_WH_DOWN,  KC_MS_WH_UP,    KC_MS_WH_RIGHT, KC_TRANSPARENT, KC_TRANSPARENT,
    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_INSERT,                                      KC_DELETE,      KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,                                                                                                 KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
                                                                                                    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
                                                                                                                    KC_HOME,        KC_PGUP,
                                                                                    LALT(KC_BSPACE),LSFT(KC_ENTER), KC_END,         KC_PGDOWN,      KC_TRANSPARENT, KC_TRANSPARENT
  ),
};


bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
      case MT(MOD_RSFT, LCTL(KC_UP)):      
        if (record->tap.count && record->event.pressed) {
            tap_code16(LCTL(KC_UP)); 
        return false; 
        }
        break;
    case MT(MOD_LCTL, LGUI(KC_TAB)):
        if (record->tap.count && record->event.pressed) {
            tap_code16(LGUI(KC_TAB)); 
        return false; 
        }
        break;
    case LT(_NUMS, KC_HASH):
        if (record->tap.count && record->event.pressed) {
            tap_code16(KC_HASH); 
        return false; 
        }
        break;
    case MT(MOD_LGUI, LGUI(KC_SPACE)):
        if (record->tap.count && record->event.pressed) {
            tap_code16(LGUI(KC_SPACE)); 
        return false; 
        }
        break;
    case MT(MOD_RSFT, RCTL(KC_DOWN)): 
        if (record->tap.count && record->event.pressed) {
            tap_code16(RCTL(KC_DOWN)); 
        return false; 
        }
        break;
    case LT(_NUMS, KC_UNDS):
        if (record->tap.count && record->event.pressed) {
            tap_code16(KC_UNDS); 
        return false; 
        }
        break;
    case MT(MOD_RALT, LGUI(LSFT(KC_TAB))):
        if (record->tap.count && record->event.pressed) {
            tap_code16(LGUI(LSFT(KC_TAB))); 
        return false; 
        }
        break;
  }
  return true;
}

// customize the value of autoshifted keys
void autoshift_press_user(uint16_t keycode, bool shifted, keyrecord_t *record) {
    switch(keycode) {
        case KC_DOT:
            register_code16((!shifted) ? KC_DOT : ((get_mods() & MOD_MASK_SHIFT)?KC_LT:KC_EXLM));
            break;
        case LT(_TEXT_NAV, KC_PAST):
            register_code16((!shifted) ? KC_ASTR : KC_HASH);
            break;
        default:
            if (shifted) {
                add_weak_mods(MOD_BIT(KC_LSFT));
            }
            // & 0xFF gets the Tap key for Tap Holds, required when using Retro Shift
            register_code16((IS_RETRO(keycode)) ? keycode & 0xFF : keycode);
    }
}

void autoshift_release_user(uint16_t keycode, bool shifted, keyrecord_t *record) {
    switch(keycode) {
        case KC_DOT:
            //unregister_code16((!shifted) ? KC_DOT : KC_EXLM);
            unregister_code16((!shifted) ? KC_DOT : ((get_mods() & MOD_MASK_SHIFT)?KC_LT:KC_EXLM));
            break;        
            case LT(_TEXT_NAV, KC_PAST):
            unregister_code16((!shifted) ? KC_ASTR : KC_HASH);
            break;
        default:
            // & 0xFF gets the Tap key for Tap Holds, required when using Retro Shift
            // The IS_RETRO check isn't really necessary here, always using
            // keycode & 0xFF would be fine.
            unregister_code16((IS_RETRO(keycode)) ? keycode & 0xFF : keycode);
    }
}

// end custom autoshift

// For Auto-Shift to work right on keys that are also modifier keys
// the keys keycodes need to be registered in this function
#ifdef RETRO_SHIFT
bool get_custom_auto_shifted_key(uint16_t keycode, keyrecord_t *record) {
    // retro keys to return false on
    switch(keycode){
        //case MT(MOD_RALT, KC_DOT):
        case MT(MOD_LSFT,KC_LBRACKET):
        case MT(MOD_LALT,KC_TILD):
        case MT(MOD_RGUI, KC_COMM):
            return false;

    }
    // else retro keys to return true on (ie all of them)
    if (IS_RETRO(keycode)){return true;}
    switch (keycode)
    {
        case KC_SLASH: // slash to ?
        case KC_QUOT: // ' to ""
        case KC_SCLN: // ; to :
        case KC_DOT: // . to ! (special)
            return true;
        break;
    
    default:
        break;
    }
    return false;
}
#endif

#ifdef AUTO_SHIFT_TIMEOUT_PER_KEY
uint16_t get_autoshift_timeout(uint16_t keycode, keyrecord_t *record) {
    switch(keycode) {
        case KC_I: // Autoshift the 'i' key really fast
            return 125;
        default:
            return get_generic_autoshift_timeout(); //generally slower autoshift for others
    }
}
#endif


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

typedef struct {
    bool is_press_action;
    uint8_t step;
} tap;

enum {
    SINGLE_TAP = 1,
    SINGLE_HOLD,
    DOUBLE_TAP,
    DOUBLE_HOLD,
    DOUBLE_SINGLE_TAP,
    MORE_TAPS
};

static tap dance_state[6];

uint8_t dance_step(qk_tap_dance_state_t *state);

uint8_t dance_step(qk_tap_dance_state_t *state) {
    if (state->count == 1) {
        if (state->interrupted || !state->pressed) return SINGLE_TAP;
        else return SINGLE_HOLD;
    } else if (state->count == 2) {
        if (state->interrupted) return DOUBLE_SINGLE_TAP;
        else if (state->pressed) return DOUBLE_HOLD;
        else return DOUBLE_TAP;
    }
    return MORE_TAPS;
}


void on_dance_0(qk_tap_dance_state_t *state, void *user_data);
void dance_0_finished(qk_tap_dance_state_t *state, void *user_data);
void dance_0_reset(qk_tap_dance_state_t *state, void *user_data);

void on_dance_0(qk_tap_dance_state_t *state, void *user_data) {
    if(state->count == 3) {
        tap_code16(LSFT(RGUI(KC_4)));
        tap_code16(LSFT(RGUI(KC_4)));
        tap_code16(LSFT(RGUI(KC_4)));
    }
    if(state->count > 3) {
        tap_code16(LSFT(RGUI(KC_4)));
    }
}

void dance_0_finished(qk_tap_dance_state_t *state, void *user_data) {
    dance_state[0].step = dance_step(state);
    switch (dance_state[0].step) {
        case SINGLE_TAP: register_code16(LSFT(RGUI(KC_4))); break;
        case DOUBLE_TAP: register_code16(LCTL(LGUI(KC_Q))); break;
        case DOUBLE_SINGLE_TAP: tap_code16(LSFT(RGUI(KC_4))); register_code16(LSFT(RGUI(KC_4)));
    }
}

void dance_0_reset(qk_tap_dance_state_t *state, void *user_data) {
    wait_ms(10);
    switch (dance_state[0].step) {
        case SINGLE_TAP: unregister_code16(LSFT(RGUI(KC_4))); break;
        case DOUBLE_TAP: unregister_code16(LCTL(LGUI(KC_Q))); break;
        case DOUBLE_SINGLE_TAP: unregister_code16(LSFT(RGUI(KC_4))); break;
    }
    dance_state[0].step = 0;
}
void on_dance_1(qk_tap_dance_state_t *state, void *user_data);
void dance_1_finished(qk_tap_dance_state_t *state, void *user_data);
void dance_1_reset(qk_tap_dance_state_t *state, void *user_data);

void on_dance_1(qk_tap_dance_state_t *state, void *user_data) {
    if(state->count == 3) {
        tap_code16(KC_CIRC);
        tap_code16(KC_CIRC);
        tap_code16(KC_CIRC);
    }
    if(state->count > 3) {
        tap_code16(KC_CIRC);
    }
}

void dance_1_finished(qk_tap_dance_state_t *state, void *user_data) {
    dance_state[1].step = dance_step(state);
    switch (dance_state[1].step) {
        case SINGLE_TAP: register_code16(KC_CIRC); break;
        case DOUBLE_TAP: register_code16(LGUI(LSFT(KC_LEFT))); break;
        case DOUBLE_SINGLE_TAP: tap_code16(KC_CIRC); register_code16(KC_CIRC);
    }
}

void dance_1_reset(qk_tap_dance_state_t *state, void *user_data) {
    wait_ms(10);
    switch (dance_state[1].step) {
        case SINGLE_TAP: unregister_code16(KC_CIRC); break;
        case DOUBLE_TAP: unregister_code16(LGUI(LSFT(KC_LEFT))); break;
        case DOUBLE_SINGLE_TAP: unregister_code16(KC_CIRC); break;
    }
    dance_state[1].step = 0;
}
void on_dance_2(qk_tap_dance_state_t *state, void *user_data);
void dance_2_finished(qk_tap_dance_state_t *state, void *user_data);
void dance_2_reset(qk_tap_dance_state_t *state, void *user_data);

void on_dance_2(qk_tap_dance_state_t *state, void *user_data) {
    if(state->count == 3) {
        tap_code16(KC_LBRACKET);
        tap_code16(KC_LBRACKET);
        tap_code16(KC_LBRACKET);
    }
    if(state->count > 3) {
        tap_code16(KC_LBRACKET);
    }
}

void dance_2_finished(qk_tap_dance_state_t *state, void *user_data) {
    dance_state[2].step = dance_step(state);
    switch (dance_state[2].step) {
        case SINGLE_TAP: register_code16(KC_LBRACKET); break;
        case SINGLE_HOLD: register_code16(LALT(LCTL(LSFT(KC_L)))); break;
        case DOUBLE_TAP: register_code16(KC_LBRACKET); register_code16(KC_LBRACKET); break;
        case DOUBLE_SINGLE_TAP: tap_code16(KC_LBRACKET); register_code16(KC_LBRACKET);
    }
}

void dance_2_reset(qk_tap_dance_state_t *state, void *user_data) {
    wait_ms(10);
    switch (dance_state[2].step) {
        case SINGLE_TAP: unregister_code16(KC_LBRACKET); break;
        case SINGLE_HOLD: unregister_code16(LALT(LCTL(LSFT(KC_L)))); break;
        case DOUBLE_TAP: unregister_code16(KC_LBRACKET); break;
        case DOUBLE_SINGLE_TAP: unregister_code16(KC_LBRACKET); break;
    }
    dance_state[2].step = 0;
}

void on_dance_7(qk_tap_dance_state_t *state, void *user_data);
void dance_7_finished(qk_tap_dance_state_t *state, void *user_data);
void dance_7_reset(qk_tap_dance_state_t *state, void *user_data);

void on_dance_7(qk_tap_dance_state_t *state, void *user_data) {
    if(state->count == 3) {
        tap_code16(KC_DLR);
        tap_code16(KC_DLR);
        tap_code16(KC_DLR);
    }
    if(state->count > 3) {
        tap_code16(KC_DLR);
    }
}

void dance_7_finished(qk_tap_dance_state_t *state, void *user_data) {
    dance_state[7].step = dance_step(state);
    switch (dance_state[7].step) {
        case SINGLE_TAP: register_code16(KC_DLR); break;
        case DOUBLE_TAP: register_code16(RGUI(RSFT(KC_RIGHT))); break;
        case DOUBLE_SINGLE_TAP: tap_code16(KC_DLR); register_code16(KC_DLR);
    }
}

void dance_7_reset(qk_tap_dance_state_t *state, void *user_data) {
    wait_ms(10);
    switch (dance_state[7].step) {
        case SINGLE_TAP: unregister_code16(KC_DLR); break;
        case DOUBLE_TAP: unregister_code16(RGUI(RSFT(KC_RIGHT))); break;
        case DOUBLE_SINGLE_TAP: unregister_code16(KC_DLR); break;
    }
    dance_state[7].step = 0;
}
void on_dance_8(qk_tap_dance_state_t *state, void *user_data);
void dance_8_finished(qk_tap_dance_state_t *state, void *user_data);
void dance_8_reset(qk_tap_dance_state_t *state, void *user_data);

void on_dance_8(qk_tap_dance_state_t *state, void *user_data) {
    if(state->count == 3) {
        tap_code16(KC_RBRACKET);
        tap_code16(KC_RBRACKET);
        tap_code16(KC_RBRACKET);
    }
    if(state->count > 3) {
        tap_code16(KC_RBRACKET);
    }
}

void dance_8_finished(qk_tap_dance_state_t *state, void *user_data) {
    dance_state[8].step = dance_step(state);
    switch (dance_state[8].step) {
        case SINGLE_TAP: register_code16(KC_RBRACKET); break;
        case SINGLE_HOLD: register_code16(RALT(RCTL(RSFT(KC_R)))); break;
        case DOUBLE_TAP: register_code16(KC_RBRACKET); register_code16(KC_RBRACKET); break;
        case DOUBLE_SINGLE_TAP: tap_code16(KC_RBRACKET); register_code16(KC_RBRACKET);
    }
}

void dance_8_reset(qk_tap_dance_state_t *state, void *user_data) {
    wait_ms(10);
    switch (dance_state[8].step) {
        case SINGLE_TAP: unregister_code16(KC_RBRACKET); break;
        case SINGLE_HOLD: unregister_code16(RALT(RCTL(RSFT(KC_R)))); break;
        case DOUBLE_TAP: unregister_code16(KC_RBRACKET); break;
        case DOUBLE_SINGLE_TAP: unregister_code16(KC_RBRACKET); break;
    }
    dance_state[8].step = 0;
}


void on_dance_14(qk_tap_dance_state_t *state, void *user_data);
void dance_14_finished(qk_tap_dance_state_t *state, void *user_data);
void dance_14_reset(qk_tap_dance_state_t *state, void *user_data);

void on_dance_14(qk_tap_dance_state_t *state, void *user_data) {
    if(state->count == 3) {
        tap_code16(KC_AUDIO_VOL_DOWN);
        tap_code16(KC_AUDIO_VOL_DOWN);
        tap_code16(KC_AUDIO_VOL_DOWN);
    }
    if(state->count > 3) {
        tap_code16(KC_AUDIO_VOL_DOWN);
    }
}

void dance_14_finished(qk_tap_dance_state_t *state, void *user_data) {
    dance_state[14].step = dance_step(state);
    switch (dance_state[14].step) {
        case SINGLE_TAP: register_code16(KC_AUDIO_VOL_DOWN); break;
        case DOUBLE_TAP: register_code16(KC_AUDIO_MUTE); break;
        case DOUBLE_SINGLE_TAP: tap_code16(KC_AUDIO_VOL_DOWN); register_code16(KC_AUDIO_VOL_DOWN);
    }
}

void dance_14_reset(qk_tap_dance_state_t *state, void *user_data) {
    wait_ms(10);
    switch (dance_state[14].step) {
        case SINGLE_TAP: unregister_code16(KC_AUDIO_VOL_DOWN); break;
        case DOUBLE_TAP: unregister_code16(KC_AUDIO_MUTE); break;
        case DOUBLE_SINGLE_TAP: unregister_code16(KC_AUDIO_VOL_DOWN); break;
    }
    dance_state[14].step = 0;
}

qk_tap_dance_action_t tap_dance_actions[] = {
        [DANCE_0] = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_0, dance_0_finished, dance_0_reset),
        [DANCE_1] = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_1, dance_1_finished, dance_1_reset),
        [DANCE_2] = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_2, dance_2_finished, dance_2_reset),
        [DANCE_7] = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_7, dance_7_finished, dance_7_reset),
        [DANCE_8] = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_8, dance_8_finished, dance_8_reset),      
        [DANCE_14] = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_14, dance_14_finished, dance_14_reset),
};

