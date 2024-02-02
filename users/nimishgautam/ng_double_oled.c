#ifdef OLED_ENABLE
oled_rotation_t oled_init_user(oled_rotation_t rotation) {
  return OLED_ROTATION_270;
}

void oled_render_general_state(void){
    set_lighting_user();

    static const char PROGMEM apple_logo[] = {
        149,150,10,
        181,182,0
    };
    
    static const char PROGMEM tux_logo[] = {
        153,154,10,
        185,186,0
    };

    keymap_config.raw = eeconfig_read_keymap();
    if(keymap_config.swap_lctl_lgui){
        //oled_write_ln_P(PSTR("Linux"), false);
        oled_write_ln_P(tux_logo, false);
    }
    else {
        //oled_write_ln_P(PSTR("OSX"), false);
        oled_write_ln_P(apple_logo, false);
    }

    oled_write_ln(get_u8_str(get_current_wpm(), '0'), false);

    if(magic_case_state){
        oled_write_ln_P(PSTR("MAGIC"), true);
    } else {
        oled_write_ln_P(PSTR(" "), false);
    }

}

void oled_render_layer_mod_state(void) {
    //Layer
    uint8_t layer = get_highest_layer(layer_state);
    switch (layer) {
        case _BASE:
            oled_write_ln_P(PSTR("  -  "), false);
            //rgblight_sethsv(HSV_OFF);
            break;
        case _NUMS:
            oled_write_ln_P(PSTR(" Nums"), false);
            break;
        case _TERMINAL:
            oled_write_ln_P(PSTR(" Term"), false);
            break;
        case _TEXT_NAV:
            oled_write_ln_P(PSTR(" Txt"), false);
            break;
        case _ADJUST:
            oled_write_ln_P(PSTR(" Adj"), false);
            break;
        case _FN_KEYS:
            oled_write_ln_P(PSTR("  Fn"), false);
            break;
        default:
            break;
    }
    oled_write_ln_P(PSTR(" "), false);
    // mods
    if(get_mods() & MOD_MASK_SHIFT){
        oled_write_ln_P(PSTR("SHIFT"), true);
    }
    if(get_mods() & MOD_MASK_CTRL){
        oled_write_ln_P(PSTR(" CTRL"), true);
    }
    if(get_mods() & MOD_MASK_ALT){
        oled_write_ln_P(PSTR(" ALT "), true);
    }
    if(get_mods() & MOD_MASK_GUI){
        oled_write_ln_P(PSTR(" GUI "), true);
    }
    if(!get_mods()){
        for (int i = 0; i < 5; i++) {
            oled_write_ln_P(PSTR("     "), false);
        }
    }

    // led state doesn't have to be handled by master, but
    // the keyboard will freeze if you type too fast
    // and have this handled on the slave side
    led_t led_state = host_keyboard_led_state();
    if(led_state.caps_lock){
        oled_write_P(PSTR("C"), false);
    } else {
        oled_write_P(PSTR(" "), false);
    }
    if(led_state.num_lock){
        oled_write_P(PSTR("N"), false);
    } else {
        oled_write_P(PSTR(" "), false);
    }
    if(led_state.scroll_lock){
        oled_write_P(PSTR("S"), false);
    } else {
        oled_write_P(PSTR(" "), false);
    }
    if(led_state.compose){ // note the ln here
        oled_write_ln_P(PSTR("c"), false);
    } else {
        oled_write_ln_P(PSTR(" "), false);
    }
}


/* https://joric.github.io/qle/  - font */


// render general state on master, a little bit of info on slave side
bool oled_task_user(void) {
    if (is_keyboard_master()) {
        oled_render_general_state();
    }
    else {
        oled_render_layer_mod_state();
    }
    return false;
}

void oled_render_boot(bool bootloader) {
    oled_clear();
    if (bootloader) {
        oled_write_P(PSTR("BOOT!"), false);
    } else {
        oled_write_P(PSTR("Rebooting "), false);
    }
    oled_render_dirty(true);
}

bool shutdown_user(bool jump_to_bootloader) {
    oled_render_boot(jump_to_bootloader);
    return jump_to_bootloader;
}

#endif