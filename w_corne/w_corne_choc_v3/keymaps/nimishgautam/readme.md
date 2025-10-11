# Compiling custom QMK firmware for the keyclicks w_corne

This is directly based off the source code at https://github.com/KeyClicks/Split-Keyboard/tree/main/source_code/vial-qmk/keyboards/keyclicks

This guide will (hopefully) let you put custom QMK firmware on it, VIAL on not.

### Thinking about this board

The two halves of the board talk to eachother via bluetooth transmission, and then to the dongle. These transmissions let the dongle know which keys had been pressed, as though it were hooked up to a keyboard itself.

In practicality, this means:

* As far as QMK is concerned, this isn't a split keyboard since QMK isn't brokering the messaging between the halves, the bluetooth firmware is
* You just need the dongle for flashing etc, the actual keyboard can be off or sitting somewhere else

#### Right hand is backwards!!

Because of the above, the right hand is actually backwards on the LAYOUT from the way you would expect it. (ie if your top row is QWERT YUIOP you have to write the firmware as though it was QWERT POIUY)

### Notes on Bootloader

I wasn't able to get this device into a hardware bootloader state where it would accept booting from stm32duino from QMK. I tried various combinations of the boot and reset buttons on the board itself but QMK wouldn't recognize it. 

#### Make sure you have a RESET in the layout!!

The above means it's most likely not possible to put this into a flash state through the board itself, meaning **you should put a RESET key into your layout!**. (I haven't tested QMK's fallback of holding down key 0,0 while plugged in to put it into bootloader state yet, I don't know if it works for vibl keyboards)

#### Using vibl as the bootloader

**vibl** is vial's bootloader, and doesn't come with QMK. The board is flashed with vial by default so it'll let you update firmware with vibl. 

Note: using vibl as the core bootloader just means that vial will be able to flash the firmware for you when you put it in a bootloader-ready state. This is **not** the same as being able to view your layout and change it on the fly with vial.

There are rules in `rules.mk` (`#VIA_ENABLE = yes` and `#VIAL_ENABLE = yes`) that will try to make the firmware actually compatible with VIAL, but there are far more settings that need to be adjusted in order to make this work. 

**making a general QMK layout fully compatible with vial is beyond the scope of this intro**

### Flashing

After running `make keyclicks/w_corne:nimishgautam` you should get a .vfw file along with a .bin and .hex file.

Next, run vial. If it opens and you see the key layout, you can go to the 'firmware' tab and just upload the .vfw and update the firmware that way. If you don't see the tab then you have to put the keyboard in a bootloader state using the RESET key (or potentially the failsafe 0,0 method). After that, vial should recognize that there's a keyboard waiting to be flashed.

## Troubleshooting

### issues with uart

If you get an error like this: `error: 'A9' undeclared` while it's building `chibios`, this is because of missing header files. You can add `#include "quantum.h"` at the top of `platforms/chibios/drivers/uart.c` and it should work.

