enum tap_dance_codes {
  TD_SELECT_LEFT, // select 1 word back normally, select back to beginning of line on double-tap
  TD_SELECT_RIGHT, // select 1 word forward normally, select forward to end of line on double-tap
  TD_LEFT_TERM, // move 1 word back on terminal, all the way back to the beginning of the terminal on double-tap
  TD_RIGHT_TERM, // move 1 word forward on terminal, all the way to end of line on terminal on double-tap
  TD_VOL_DOWN_MUTE, // vol down normally, mute on double-tap
};

// Tap dance actions

void dance_left_select_finished (tap_dance_state_t *state, void *user_data) {
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

void dance_right_select_finished (tap_dance_state_t *state, void *user_data) {
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

void dance_left_term_finished (tap_dance_state_t *state, void *user_data) {
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

void dance_right_term_finished (tap_dance_state_t *state, void *user_data) {
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
tap_dance_action_t tap_dance_actions[] = {
  [TD_SELECT_LEFT]  = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_left_select_finished, NULL),
  [TD_SELECT_RIGHT]  = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_right_select_finished, NULL),
  [TD_LEFT_TERM]  = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_left_term_finished, NULL),
  [TD_RIGHT_TERM]  = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_right_term_finished, NULL),
  
  [TD_VOL_DOWN_MUTE] = ACTION_TAP_DANCE_DOUBLE(KC_VOLD, KC_MUTE),
};
