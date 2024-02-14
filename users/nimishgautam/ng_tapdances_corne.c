//Tap Dance Declarations
enum {
  TD_MOVE_BEGIN_LINE = 0, // tap-dance, on single press move to beginning of the line, on double, output ^(vim character for beginning of line nonwhitespace char)
  TD_MOVE_END_LINE, // tap-dance, on single press move to end of the line, on double, output $ (vim character for last nonblank char on a line)
  TD_PERIOD_COMMA, // period on single press, comma on second press
  TD_F5_CONSOLE, // When pressing F5 twice, go to the alternate linux console
  TD_F2_CONSOLE, // When pressing F2 twice, go back to xwindows
};

void dance_left_finished (tap_dance_state_t *state, void *user_data) {
  if (state->count == 1) { //1 tap, move to line left
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
    if(keymap_config.swap_lctl_lgui){ //Linux
        tap_code16(KC_END);
    } else { //osx
    tap_code16(LGUI(KC_RIGHT));
    }
  } else { //2 taps, dollar
    tap_code16(KC_DOLLAR);
  }
}

void dance_f2_finished (tap_dance_state_t *state, void *user_data) {
  if (state->count == 1) { // 1 tap, normal f2
    tap_code16(KC_F2);
  } else { //2 taps, console
    tap_code16(LALT(KC_F2));
  }
}

void dance_f5_finished (tap_dance_state_t *state, void *user_data) {
  if (state->count == 1) { // 1 tap, normal f5
    tap_code16(KC_F5);
  } else { //2 taps, console
    tap_code16(LCTL(LALT(KC_F5)));
  }
}

//Tap Dance Definitions
tap_dance_action_t tap_dance_actions[] = {
  [TD_MOVE_BEGIN_LINE]  = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_left_finished, NULL),
  [TD_MOVE_END_LINE]  = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_right_finished, NULL),
  [TD_PERIOD_COMMA] = ACTION_TAP_DANCE_DOUBLE(KC_DOT, KC_COMMA),
  [TD_F2_CONSOLE] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_f2_finished, NULL),
  [TD_F5_CONSOLE] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_f5_finished, NULL),
};