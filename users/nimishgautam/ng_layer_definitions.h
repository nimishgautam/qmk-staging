enum custom_layers {
    _BASE,

    _NUMS, // triggered by left hand large thumb button
    _TEXT_NAV, // triggered by right hand large thumb button
    
    _FN_KEYS, // triggered by left hand inner button
    _TERMINAL, // triggered by the right hand inner button

    _ADJUST, // triggered from series of keys to avoid accidentally getting to it

    #ifdef POINTING_DEVICE_ENABLE
    _MOUSE, // mouse layer
    #endif
};