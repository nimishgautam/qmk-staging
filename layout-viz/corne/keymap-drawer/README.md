# About these files

This was from keymap drawer, which exists as a web demo (https://github.com/ijprest/keyboard-layout-editor) and as github code: https://github.com/caksoylar/keymap-drawer/

It takes a YML file and outputs a SVG.

## Why

This is a better way of showing 'layers' but also combos, and it has a lot of options that let you highlight aspects of your design how you wish. 

## building
You download the package and actually execute the *folder* because the folder has a __main__ in it, do a pipx install and you're good to go.

```bash
python keymap_drawer draw ./examples/nimish_corne.yaml > nimish_corne.svg 
```

## icons

I used mostly phosphor: https://phosphoricons.com/?weight=light
It supports a few icon packs directly, and supports many more indirectly via svg importing

I also used some unicode from here:
* https://www.copyandpastesymbols.net/arrow-symbols.html
* https://www.compart.com/en/unicode/search?q=none
