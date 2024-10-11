
SRC += keymaps/christrotter/callbacks.c
ifeq ($(strip $(RGB_MATRIX_LEDMAPS_ENABLED)), yes)
	SRC += rgb_ledmaps.c
	OPT_DEFS += -DRGB_MATRIX_LEDMAPS_ENABLED
endif
