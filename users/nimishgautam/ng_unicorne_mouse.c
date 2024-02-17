#ifndef SCROLLING_LAYER
    #define SCROLLING_LAYER _TEXT_NAV
#endif
#ifndef TAPPING_LAYER
    #define TAPPING_LAYER _TERMINAL
#endif
#ifndef BASE_CURSOR_LAYER
    #define BASE_CURSOR_LAYER _BASE
#endif
#ifndef CURSOR_SPEED
    #define CURSOR_SPEED 30
#endif
#ifndef SCROLL_SPEED
    #define SCROLL_SPEED 35
#endif
#ifndef SCROLL_DELAY_MS
    #define SCROLL_DELAY_MS 70
#endif

#define THUMBSTICK_RIGHT_TAP KC_RIGHT
#define THUMBSTICK_LEFT_TAP KC_LEFT
#define THUMBSTICK_UP_TAP KC_UP
#define THUMBSTICK_DOWN_TAP KC_DOWN

// Thumbstick code, no customisation needed

uint16_t mouse_mode = SCROLLING_LAYER;

// tracks if thumbstick was released
bool returned_to_zero = true;

// tracks how many times mouse_report.x/y have been read zero in succession
uint16_t zero_reads = 0;

// set mode depending on layer
layer_state_t layer_state_set_user(layer_state_t state) {
    switch (get_highest_layer(state)) {
        case SCROLLING_LAYER:
            if (mouse_mode != SCROLLING_LAYER) {
                mouse_mode = SCROLLING_LAYER;
                set_auto_mouse_enable(false);
            }
            break;
        case TAPPING_LAYER:
            if (mouse_mode != TAPPING_LAYER) {
                mouse_mode = TAPPING_LAYER;
                set_auto_mouse_enable(false);
            }
            break;
        default:
            if (mouse_mode != BASE_CURSOR_LAYER){
                mouse_mode = BASE_CURSOR_LAYER;
            }
            if (!get_auto_mouse_enable()){
                set_auto_mouse_enable(true);
            }
            break;
    }
    return state;
}

// manipulate mouse report based on current mode
report_mouse_t pointing_device_task_user(report_mouse_t mouse_report) {

    if (mouse_mode == BASE_CURSOR_LAYER) {
        
        mouse_report.x = CURSOR_SPEED * mouse_report.x/100;
        mouse_report.y = CURSOR_SPEED * mouse_report.y/100;
            /* float magnitude = sqrtf( mouse_report.x * mouse_report.x + mouse_report.y * mouse_report.y );
            float adjusted_magnitude = powf(magnitude, 0.2f);
            mouse_report.x = (mouse_report.x * adjusted_magnitude);
            if(mouse_report.x > 127){mouse_report.x = 127;}
            if(mouse_report.x < -127){mouse_report.x = -127;}
            mouse_report.y = (mouse_report.y * adjusted_magnitude); 
             if(mouse_report.y > 127){mouse_report.y = 127;}
            if(mouse_report.y < -127){mouse_report.y = -127;} */  
    }
    if (mouse_mode == SCROLLING_LAYER) {
        mouse_report.h = SCROLL_SPEED * mouse_report.x/100;
        mouse_report.v = -1 * SCROLL_SPEED * mouse_report.y/100;
        mouse_report.x = 0;
        mouse_report.y = 0;
        if ((mouse_report.h != 0) | (mouse_report.v != 0)) {
            wait_ms(SCROLL_DELAY_MS);
        }

    } else if (mouse_mode == TAPPING_LAYER) {
        if ((mouse_report.x || mouse_report.y) != 0) {
            if (returned_to_zero) {
                if (mouse_report.x > 0) {
                    tap_code16(THUMBSTICK_RIGHT_TAP);
                }
                if (mouse_report.x < 0) {
                    tap_code16(THUMBSTICK_LEFT_TAP);
                }
                if (mouse_report.y > 0) {
                    tap_code16(THUMBSTICK_DOWN_TAP);
                }
                if (mouse_report.y < 0) {
                    tap_code16(THUMBSTICK_UP_TAP);
                }
                returned_to_zero = false;
            }
            zero_reads = 0;
        } else if (zero_reads < 20) {
            zero_reads++;
        }
        if (zero_reads >= 20) {
            if (returned_to_zero == false) {
                returned_to_zero = true;
            }
        }
        mouse_report.x = 0;
        mouse_report.y = 0;
    }

    return mouse_report;
}

void pointing_device_init_user(void) {
    set_auto_mouse_layer(_MOUSE); // only required if AUTO_MOUSE_DEFAULT_LAYER is not set to index of <mouse_layer>
    set_auto_mouse_enable(true);         // always required before the auto mouse feature will work
}