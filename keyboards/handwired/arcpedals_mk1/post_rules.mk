
ifeq ($(strip $(RGB_MATRIX_ENABLE)), yes)
	OPT_DEFS += -DRGB_MATRIX_ENABLE
endif
