
ifeq ($(strip $(RGB_MATRIX_ENABLE)), yes)
	OPT_DEFS += -DRGB_MATRIX_ENABLE
endif
ifeq ($(strip $(DRAGSCROLL_ENABLE)), yes)
	OPT_DEFS += -DDRAGSCROLL_ENABLE
endif
ifeq ($(strip $(CUSTOM_DRAGSCROLL)), yes)
	OPT_DEFS += -DCUSTOM_DRAGSCROLL
endif

QUANTUM_PAINTER_ENABLE ?= yes
ifeq ($(strip $(QUANTUM_PAINTER_ENABLE)), yes)
	SRC += arcboard_mk13_ui.c
	QUANTUM_PAINTER_DRIVERS = st7789_spi
	BACKLIGHT_DRIVER = pwm
	BACKLIGHT_ENABLE = yes
else
	BACKLIGHT_ENABLE = no
endif
