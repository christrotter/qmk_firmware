
ifeq ($(strip $(RGB_MATRIX_ENABLE)), yes)
	OPT_DEFS += -DRGB_MATRIX_ENABLE
endif
ifeq ($(strip $(DRAGSCROLL_ENABLE)), yes)
	OPT_DEFS += -DDRAGSCROLL_ENABLE
endif
ifeq ($(strip $(CUSTOM_DRAGSCROLL)), yes)
	OPT_DEFS += -DCUSTOM_DRAGSCROLL
endif
