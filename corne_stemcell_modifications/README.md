# Corne with Stemcell

## Background

I have a corne that has RGB lighting and oled screens. These are quite memory-intensive with a standard ProMicro. I eventually found that the [Stemcell](https://github.com/megamind4089/STeMCell) could work.

### Stemcell v1 vs v2

Unfortunately QMK's `CONVERT_TO` feature is only for stemcell v2. If you want to use v1 then you will have to take the files included here and replace them in your QMK firmware directory in `platforms/chibios/converters/promicro_to_stemcell` directory.

The main difference is that 2 pins were switched for some reason in v2 and there's something about the UART being reversed. This can be passed in with a flag but I know this works.

### Tiny soldering

There are also a few pads on the board itself that you need to solder to set the modes right. If you don't then OLED, background lighting, and communicating to the other side of the board might not work.

I've included the wiring diagram given to me by the creator of stemcell.

### Convert

After this, you should be able to just add `CONVERT_TO = stemcell` in your `rules.mk` and it should work fine
