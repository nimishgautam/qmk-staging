uint8_t magic_case_state = 0;

#define MAGIC_CASE_OFF 0
#define MAGIC_CASE_SNAKE 1
#define MAGIC_CASE_CAMEL 2
#define MAGIC_CASE_KEBAB 3 

bool process_record_user(uint16_t keycode, keyrecord_t *record) {

  switch (keycode) {
    /* MAGIC CASING */
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
    //break;


    /* LAYER TAPS */

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

    /* SPECIAL MOVEMENT FUNCTIONS */
    case LT(0,SHOW_WIN_LEFT):
            if (record->tap.count && record->event.pressed) {
                tap_code16(SHOW_WINDOWS); // Intercept tap function
            } else if (record->event.pressed) {
                tap_code16(WINDOW_LEFT); // Intercept hold function
            }
        return false;
    //break;

    case LT(0, NUMERIC_WIN_RIGHT):
            if (record->tap.count && record->event.pressed) {
                layer_on(_NUMS);// Intercept tap function
            } else if (record->event.pressed) {
                tap_code16(WINDOW_RIGHT); // Intercept hold function
            }
        return false;
    //break;

    /* MISC */
    case PASTE_VIM:
        if (record->event.pressed){
            SEND_STRING(SS_TAP(X_ESCAPE)"\"+pi");
        }
        return false;
    //break;

 /* TMUX */

    case TMUX_CLOSE_PANE:
    case TMUX_SPLIT_VERT:
    case TMUX_SPLIT_HORIZ:
    case TMUX_NEXT_PANE:
    case TMUX_PREV_PANE:
        if(record->event.pressed){
            tap_code16(C(KC_B)); //tmux escape key
            switch(keycode){
                    case TMUX_CLOSE_PANE:
                        tap_code16(KC_X);
                        break;
                    case TMUX_SPLIT_VERT:
                        // create a vertical line, split "horizontal"
                        tap_code16(KC_PERCENT);
                        break;
                    case TMUX_SPLIT_HORIZ:
                        // create a horizontal line, split "vertical"
                        tap_code16(KC_DQUO);
                        break;                
                    case TMUX_NEXT_PANE:
                        tap_code16(KC_O);
                        break;
                    case TMUX_PREV_PANE:
                        tap_code16(KC_SCLN);
                        break;
            }
        }
        return false;
    //break;


    /* OS-DEPENDENT FUNCTIONS */

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
    case ACIRCLE:
    case ADOT:
    case ODOT:
    case COMPOSE_MACRO:
    case SCREENSHOT:
    case OPEN_TERMINAL_HERE:
    case SHOW_OS:
    case SMILEY:
    case THUMBS_UP:

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
                case SHOW_OS:
                    if(keymap_config.swap_lctl_lgui){ //Linux
                        SEND_STRING("Lx");
                    } else { //osx
                        SEND_STRING("Mac");
                    }
                break;
                case SMILEY:
                    if(keymap_config.swap_lctl_lgui){ //Linux
                        SEND_STRING(SS_TAP(X_COMPOSE_KEY)":)");
                    } else { //osx
                        SEND_STRING(SS_TAP(X_COMPOSE_MAC)":)");
                    }
                break;
                case THUMBS_UP:
                    if(keymap_config.swap_lctl_lgui){ //Linux
                        SEND_STRING(SS_TAP(X_COMPOSE_KEY)":+");
                    } else { //osx
                        SEND_STRING(SS_TAP(X_COMPOSE_MAC)":+");
                    }
                break;

            }
        }

    return false;
    //break;
  }
  return true;
}