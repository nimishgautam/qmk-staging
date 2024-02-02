
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
      KC_TRANSPARENT, KC_TRANSPARENT, TMUX_PREV_PANE, MOVE_BEGIN_LINE_TERMINAL, TMUX_NEXT_PANE, TD(TD_MOVE_BEGIN_LINE),                           KC_TRANSPARENT, KC_TRANSPARENT, OPEN_TERMINAL_HERE, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
  //|--------+--------+--------+--------+--------+--------|                                                           |--------+--------+--------+--------+--------+--------|
      TO(_BASE), SELECT_LEFT_WD, MOVE_LEFT_TERMINAL, MOVE_END_LINE_TERMINAL, MOVE_RIGHT_TERMINAL,SELECT_RIGHT_WD,                                            KC_TRANSPARENT, KC_RGUI, KC_RSFT, KC_RALT,KC_RCTL, KC_TRANSPARENT,
  //|--------+--------+--------+--------+--------+--------|                                                           |--------+--------+--------+--------+--------+--------|
      SEND_WINDOW_LEFT, KC_TRANSPARENT, TMUX_SPLIT_VERT, TMUX_CLOSE_PANE, TMUX_SPLIT_HORIZ, KC_TRANSPARENT,                                       KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,KC_TRANSPARENT, KC_TRANSPARENT,
  //|--------+--------+--------+--------+--------+--------+--------|                                              |--------+--------+--------+--------+--------+--------+--------|
                                          DEL_TO_END_TERMINAL,  DEL_WORD_TERMINAL, KC_TRANSPARENT ,                                  KC_TRANSPARENT  ,  KC_TRANSPARENT, KC_TRANSPARENT
                                      //`--------------------------'                                              `--------------------------'
  ),

#if defined(RGB_LIGHT_ENABLE) || defined(RGB_MATRIX_ENABLE)
//RGB EXISTS

      [_ADJUST] = LAYOUT_split_3x6_3( // adjust things
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
     EE_CLR, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      TO(_BASE), RGB_HUI, RGB_SAI, RGB_VAI, XXXXXXX, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LSFT, RGB_MOD, RGB_RMOD, RGB_TOG, XXXXXXX, XXXXXXX,                       XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          SHOW_OS, XXXXXXX, CG_TOGG ,     XXXXXXX, XXXXXXX, XXXXXXX
                                      //`--------------------------'  `--------------------------'
  ), // CG_TOGG toggles gui and Ctrl (switching from mac to windows/linux)
    // the RGB buttons go backwards if shift is held when they're pressed, so shift is included
    // RGB MOD changes the mode, it's the most important one
    // right side mostly no-op so I can play with the visualization

#else

// NO RGB
      [_ADJUST] = LAYOUT_split_3x6_3( // adjust things
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
     EE_CLR, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      TO(_BASE), XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LSFT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                       XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          SHOW_OS, XXXXXXX, CG_TOGG ,     XXXXXXX, XXXXXXX, XXXXXXX
                                      //`--------------------------'  `--------------------------'
  ), // CG_TOGG toggles gui and Ctrl (switching from mac to windows/linux)
 

#endif

#ifdef POINTING_DEVICE_ENABLE
   [_MOUSE] = LAYOUT_split_3x6_3( //fn keys,
   /**
    * Left hand pressing the inner key, left modifiers active, right FN keys
    * Also scroll lock and printscreen in here
    * 
   */
  //,-----------------------------------------------------.                                                                   ,-----------------------------------------------------.
     KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,                           KC_TRANSPARENT, KC_TRANSPARENT,    KC_TRANSPARENT,    KC_TRANSPARENT,    KC_TRANSPARENT, KC_TRANSPARENT,
  //|--------+--------+--------+--------+--------+--------|                                                                   |--------+--------+--------+--------+--------+--------|
     KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,                           KC_TRANSPARENT, KC_BTN4,    KC_BTN5,    KC_TRANSPARENT,    KC_TRANSPARENT, KC_TRANSPARENT,
  //|--------+--------+--------+--------+--------+--------|                                                                   |--------+--------+--------+--------+--------+--------|
      KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,                         KC_TRANSPARENT, KC_TRANSPARENT,    KC_TRANSPARENT,    KC_TRANSPARENT,    KC_TRANSPARENT, KC_TRANSPARENT,
  //|--------+--------+--------+--------+--------+--------+--------|                                                   |--------+--------+--------+--------+--------+--------+--------|
                                          KC_TRANSPARENT, KC_TRANSPARENT, KC_BTN1 ,                             KC_BTN2  ,  KC_BTN3, KC_TRANSPARENT
                                      //`--------------------------'                                                   `--------------------------'
  ),

#endif
};
