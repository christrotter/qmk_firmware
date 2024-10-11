
ifeq ($(strip $(RGB_MATRIX_ENABLE)), yes)
	OPT_DEFS += -DRGB_MATRIX_ENABLE
endif

# Trackball settings
POINTING_DEVICE_ENABLE ?= yes
ifeq ($(strip $(POINTING_DEVICE_ENABLE)), yes)
	CUSTOM_POINTING_DEVICE  = yes
	POINTING_DEVICE_DRIVER 	= pmw3360
endif
