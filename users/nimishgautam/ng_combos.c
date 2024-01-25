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
    COMBO(smiley_combo, SMILEY),
    COMBO(thumbsup_combo, THUMBS_UP)
};