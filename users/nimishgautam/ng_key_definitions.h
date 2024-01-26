
// Mac-specific definitions of these functions
// I've changed Linux to accept these defaults

#define FINDER         LGUI(LALT(KC_SPACE)) //open the search bar for finding apps, docs in-computer, etc
#define COMPOSE_KEY    KC_SCRL //manually set on linux, to create chars via .Xcompose ()
#define COMPOSE_MAC    KC_F13 //manually set on mac using some tricks
#define X_COMPOSE_KEY  X_SCROLL_LOCK //for use with macros
#define X_COMPOSE_MAC  X_F13 // for use with macros
#define SHOW_WINDOWS   LCTL(KC_UP) //'Expose' on Mac, overview on linux. Just all the windows
#define WINDOW_LEFT    LCTL(LGUI(LSFT(KC_LEFT))) //custom shortcut for this feature -- make window take up 50% left screen (using gui and ctl to make it os agnostic)
#define WINDOW_RIGHT   LCTL(LGUI(LSFT(KC_RIGHT))) //custom shortcut for this feature -- make window take up 50% right screen (using gui and ctl to make it os agnostic)/fully custom shortcut, using ctl and gui keys so will need them both irrespective of os
#define SHOW_APP_WINDOWS LCTL(KC_DOWN)
#define LOCK_SCREEN    LCTL(LGUI(KC_Q)) //manually set this on linux to match osx default
#define EURO           LALT(LSFT(KC_2))
#define EMOJI_KBD      LCTL(LGUI(KC_SPACE)) //manually set this on linux to match osx default, with 'emote' on linux and a custom shortcut (probably better to use compose feature)
#define APP_LEFT	   LGUI(KC_TAB)
#define APP_RIGHT	   RSFT(LGUI(KC_TAB))
#define CALCULATOR     RSFT(LGUI(LCTL(KC_SLASH))) // arbitrary shortcut
#define ZOOM_IN        LALT(LGUI(KC_EQL)) // mac code zoom in
#define ZOOM_OUT       LALT(LGUI(KC_MINUS)) // mac code zoom out
#define SWITCH_APP_WINDOWS LCTL(KC_GRAVE) //mac code

// mac tools (more)
#define FULLSCREEN      LGUI(LCTL(KC_F))
#define SPOTLIGHT       LGUI(KC_SPACE)

// All of these are now using readline bindings
// Will not work if .inputrc set to vim bindings
// Also some caution around tmux/screen command keys
// Note heavy use of 'control'... if LEGACY_MAGIC_HANDLING gets taken out
// then these will no longer work right on linux

#define MOVE_LEFT_TERMINAL  LALT(KC_LEFT) //move cursor one word left on the terminal... does not work if .inputrc is set to use vim bindings!
#define MOVE_RIGHT_TERMINAL LALT(KC_RIGHT) //move cursor one word left on the terminal... does not work if .inputrc is set to use vim bindings!
#define DEL_WORD_TERMINAL   LCTL(KC_W) // delete one word back on terminal ... does not work if .inputrc is set to use vim bindings!
#define MOVE_BEGIN_LINE_TERMINAL LCTL(KC_A) // move to the beginning of the line in the terminal
#define MOVE_END_LINE_TERMINAL LCTL(KC_E) // move to the end of the line in the terminal
#define DEL_TO_END_TERMINAL LCTL(KC_U) // delete everything from cursor to beginning of line

// I believe these only exist in linux. Send current window to one monitor left or right
// Note that this requires LEGACY_MAGIC_HANDLING or it won't work 
// This constraint doesn't exist for keycodes that are directly entered via tap_16

#define SEND_WINDOW_LEFT  RSFT(LGUI(KC_LEFT))
#define SEND_WINDOW_RIGHT RSFT(LGUI(KC_RIGHT))

// Window control, also only in linux
// maximize window, vertical only or horizontal only
// toggle window maximization state after maximizing it

#define MAX_VERTICAL LCTL(LGUI(RSFT(KC_F8)))
#define MAX_HORIZONTAL LCTL(LGUI(RSFT(KC_F6)))
#define TOG_WINDOW_STATE LALT(KC_F10)

enum custom_key_codes {
    RGB_SLD = SAFE_RANGE,
    SHOW_WIN_LEFT, // show windows on tap, move active window left on hold
    NUMERIC_WIN_RIGHT, // lock to numeric layer on press, move active window right on hold
    DEL_WORD, //delete a word
    SELECT_LEFT_WD, // select word left of cursor
    SELECT_RIGHT_WD, // select word right of cursor
    SELECT_LEFT_LINE, // select all from left of cursor to beginning of line
    SELECT_RIGHT_LINE, // select all from right of cursor to end of line
    MOVE_LEFT_WD, // move one word to the left
    MOVE_RIGHT_WD, // move one word to the right
    MOVE_LEFT_LINE, // move to beginning of line
    MOVE_RIGHT_LINE, // move to end of line
    PASTE_NOSTYLE, // paste without formatting
    OPEN_TERMINAL_HERE, //open terminal at current location in finder
    /* macros */
    PASTE_VIM, // paste in vim from system register
    ACIRCLE, // å
    ADOT, // ä
    ODOT, // ö
    SHOW_OS, // type out the OS 
    COMPOSE_MACRO, // compose key for mac or linux
    SCREENSHOT, // This is theoretically reprogrammable on Linux, but Gui(Shift(4)) or Gui(4) is reserved for '4th item on favorite menu' and doesn't remap so well
    MAGIC_CASING, // magic casing -- snake_case by default, shift = camelCase, alt = kebab-case
    /* tmux */
    TMUX_CLOSE_PANE,
    TMUX_SPLIT_VERT,
    TMUX_SPLIT_HORIZ,
    TMUX_NEXT_PANE,
    TMUX_PREV_PANE,
    /* emojis (via Xcompose and not unicode) */
    SMILEY,
    THUMBS_UP,
};

