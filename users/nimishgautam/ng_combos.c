#include "action_tapping.h"

enum combos {
    COMPOSE_COMBO,
    SEARCH_COMBO,
    VIM_PASTE_COMBO,
    CALCULATOR_COMBO,
    ACIRCLE_COMBO,
    ADOT_COMBO,
    ODOT_COMBO,
    PLUS_COMBO,
    EQUALS_COMBO,
    AMPERSAND_COMBO,
    UNDERSCORE_COMBO,
    UP_COMBO,
    DOWN_COMBO,
    LEFT_COMBO,
    RIGHT_COMBO,
    EMOJI_COMBO,
    SCROLLDOWN_COMBO,
    SCROLLUP_COMBO,
    SMILEY_COMBO,
    THUMBSUP_COMBO,
    POWER_BUTTON_COMBO,
    FORCE_QUIT_COMBO,
    MAGIC_SYSRQ_COMBO,
    MUTE_COMBO,
    PAUSEPLAY_COMBO,
    MOUSE_WARP_GRID_COMBO,
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
const uint16_t PROGMEM acircle_combo[] = { KC_BSPC, LCTL_T(KC_A),COMBO_END};

// combo - press combo+ l to get ä
const uint16_t PROGMEM adot_combo[] = {KC_SPACE, RALT_T(KC_L), COMBO_END};

// combo - press combo+ ; to get ö
const uint16_t PROGMEM odot_combo[] = {KC_SPACE, RCTL_T(KC_SCLN),COMBO_END};

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

// combo - smiley face 🙂
const uint16_t PROGMEM smiley_combo[] = {KC_R, KC_U ,COMBO_END};

//combo - thumbs up 👍️
const uint16_t PROGMEM thumbsup_combo[] = {KC_W, KC_O ,COMBO_END};

//combo - power button
const uint16_t PROGMEM power_button_combo[] = {LT(0, NUMERIC_WIN_RIGHT), KC_MINUS, COMBO_END};

//combo - xkill or command opt esc
const uint16_t PROGMEM force_quit_combo[] = {MAGIC_CASING, LT(0, SHOW_WIN_LEFT), COMBO_END};

//combo - magic sysrq
const uint16_t PROGMEM magic_sysrq_combo[] = {LT(0, SHOW_WIN_LEFT), LT(0, NUMERIC_WIN_RIGHT), COMBO_END};

//combo - mute
const uint16_t PROGMEM mute_combo[] = {KC_Y, KC_T, COMBO_END};

//combo - play/pause
const uint16_t PROGMEM pauseplay_combo[] = {KC_B, KC_N, COMBO_END};

//combo - mouse warp grid (from warpd or shortcat)
const uint16_t PROGMEM mouse_warp_grid_combo[] = {KC_COMM, KC_M, COMBO_END};

combo_t key_combos[] = {
    [COMPOSE_COMBO] = COMBO(compose_combo, COMPOSE_MACRO),
    [SEARCH_COMBO] = COMBO(search_combo, FINDER),
    [VIM_PASTE_COMBO] = COMBO(vim_paste_combo, PASTE_VIM),
    [CALCULATOR_COMBO] = COMBO(calculator_combo, CALCULATOR),
    [ACIRCLE_COMBO] = COMBO(acircle_combo, ACIRCLE),
    [ADOT_COMBO] = COMBO(adot_combo, ADOT),
    [ODOT_COMBO] = COMBO(odot_combo, ODOT),
    [PLUS_COMBO] = COMBO(plus_combo, KC_PLUS),
    [EQUALS_COMBO] = COMBO(equals_combo, KC_EQL),
    [AMPERSAND_COMBO] = COMBO(ampersand_combo, KC_AMPERSAND),
    [UNDERSCORE_COMBO] = COMBO(underscore_combo, KC_UNDS),
    [UP_COMBO] = COMBO(up_combo, KC_UP),
    [DOWN_COMBO] = COMBO(down_combo, KC_DOWN),
    [LEFT_COMBO] = COMBO(left_combo, KC_LEFT),
    [RIGHT_COMBO] = COMBO(right_combo, KC_RIGHT),
    [EMOJI_COMBO] = COMBO(emoji_combo, EMOJI_KBD),
    [SCROLLDOWN_COMBO] = COMBO(scrolldown_combo, MS_WHLD),
    [SCROLLUP_COMBO] = COMBO(scrollup_combo, MS_WHLU),
    [SMILEY_COMBO] = COMBO(smiley_combo, SMILEY),
    [THUMBSUP_COMBO] = COMBO(thumbsup_combo, THUMBS_UP),
    [POWER_BUTTON_COMBO] = COMBO(power_button_combo, KC_PWR),
    [FORCE_QUIT_COMBO] = COMBO(force_quit_combo, FORCE_QUIT),
    [MAGIC_SYSRQ_COMBO] = COMBO(magic_sysrq_combo, MAGIC_SYSRQ),
    [MUTE_COMBO] = COMBO(mute_combo, KC_MUTE),
    [PAUSEPLAY_COMBO] = COMBO(pauseplay_combo, KC_MPLY),
    [MOUSE_WARP_GRID_COMBO] = COMBO(mouse_warp_grid_combo, MOUSE_WARP_GRID),
};

/* // These are probably no longer needed with the flow tap feature
bool get_combo_must_hold(uint16_t index, combo_t *combo) {
    // decide by keycode, the combo index, or by the keys in the chord.

    switch (combo->keycode) {
        case SMILEY:
        case THUMBS_UP:
        case EMOJI_KBD:
            return true;
    }

    return false;
} */

bool combo_should_trigger(uint16_t combo_index, combo_t *combo, uint16_t keycode, keyrecord_t *record) {
    /* These combos should only fire when not in flow tap*/
    switch (combo_index) {
        case PLUS_COMBO:
        case EQUALS_COMBO:
        case AMPERSAND_COMBO:
        case UNDERSCORE_COMBO:
        case UP_COMBO:
        case DOWN_COMBO:
        case LEFT_COMBO:
        case RIGHT_COMBO:
        case SMILEY_COMBO:
        case THUMBSUP_COMBO:
        case EMOJI_COMBO:
            return !within_flow_tap_term(keycode, record);
    }

    return true;
}