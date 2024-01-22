//Tap Dance Declarations
enum {
  TD_MOVE_BEGIN_LINE = 0, // tap-dance, on single press move to beginning of the line, on double, output ^(vim character for beginning of line nonwhitespace char)
  TD_MOVE_END_LINE, // tap-dance, on single press move to end of the line, on double, output $ (vim character for last nonblank char on a line)
  TD_PERIOD_COMMA, // period on single press, comma on second press
};

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