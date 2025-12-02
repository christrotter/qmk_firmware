ifeq ($(strip $(RAW_ENABLE)), yes)
	SRC += keymaps/christrotter/hid_functionality.c
endif

ifeq ($(strip $(RGB_MATRIX_LEDMAPS_ENABLED)), yes)
	SRC += keymaps/christrotter/rgb_ledmaps.c
	OPT_DEFS += -DRGB_MATRIX_LEDMAPS_ENABLED
endif

ENCODER_MAP_ENABLE = yes
# LVGL_ENABLE_LARGE_FONTS = yes
SRC += graphics/vscode-icon.qgf.c
SRC += graphics/fusion-icon.qgf.c
SRC += graphics/chrome-icon.qgf.c
SRC += graphics/qmk-icon.qgf.c
SRC += graphics/kicad-icon.qgf.c
SRC += graphics/default-app.qgf.c

CAPS_WORD_ENABLE = yes
