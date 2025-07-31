ifeq ($(strip $(RAW_ENABLE)), yes)
	SRC += keymaps/christrotter/hid_functionality.c
endif

LVGL_ENABLE_LARGE_FONTS = yes