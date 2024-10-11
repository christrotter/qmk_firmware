
ifeq ($(strip $(RGB_MATRIX_LEDMAPS_ENABLED)), yes)
	SRC += keymaps/christrotter/rgb_ledmaps.c
	OPT_DEFS += -DRGB_MATRIX_LEDMAPS_ENABLED
endif

ifeq ($(strip $(QUANTUM_PAINTER_ENABLE)), yes)
	SRC += keymaps/christrotter/ui.c
	SRC += keymaps/christrotter/graphics/awesome.qgf.c
	SRC += keymaps/christrotter/graphics/disappointed_guy.qgf.c
	SRC += keymaps/christrotter/graphics/roger.qgf.c
	SRC += keymaps/christrotter/graphics/qmk-logo.qgf.c
endif