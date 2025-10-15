/* at some point with the old microcontrollers, I squeezed ram to the point that I had to custom-implement magic swap ctl+gui */
/* I don't need this anymore but I wanted to preserve my own knowledge of how to do that */

// attempt to shrink firmware size -- this is for magic replacement of keys (not mods)
uint16_t keycode_config(uint16_t keycode) {
    switch (keycode) {
        case KC_LEFT_CTRL:
            if (keymap_config.swap_lctl_lgui) {
                return KC_LEFT_GUI;
            }
        break;
        case KC_LEFT_GUI:
            if (keymap_config.swap_lctl_lgui) {
                return KC_LEFT_CTRL;
            }
        break;
        case KC_RIGHT_CTRL:
            if (keymap_config.swap_rctl_rgui) {
                return KC_RIGHT_GUI;
            }
        break;
        case KC_RIGHT_GUI:
            if (keymap_config.swap_rctl_rgui) {
                return KC_RIGHT_CTRL;
            }
        break;
    }
    return keycode;
}

//shrink further, replacing mods
uint8_t mod_config(uint8_t mod) {
    /**
     * Note: This function is for the 5-bit packed mods, NOT the full 8-bit mods.
     * More info about the mods can be seen in modifiers.h.
     */

    if (keymap_config.swap_lctl_lgui) {
        // left mods ANDed with right-hand values to check for right hand bit 
        if (((mod & MOD_RCTL) == MOD_LCTL) ^ ((mod & MOD_RGUI) == MOD_LGUI)) {
            mod ^= (MOD_LCTL | MOD_LGUI);
        }
    }
    if (keymap_config.swap_rctl_rgui) {
        if (((mod & MOD_RCTL) == MOD_RCTL) ^ ((mod & MOD_RGUI) == MOD_RGUI)) {
            //lefthand values to preserve the right hand bit
            mod ^= (MOD_LCTL | MOD_LGUI);
        }
    }
    return mod;
}
