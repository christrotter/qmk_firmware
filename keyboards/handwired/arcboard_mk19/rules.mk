# general config
SERIAL_DRIVER = vendor

# matrix config
CUSTOM_MATRIX = lite
QUANTUM_LIB_SRC += spi_master.c     # do we still need this?
SRC += matrix.c

# LED settings
RGB_MATRIX_LEDMAPS_ENABLED = yes 	# turn on per-key colours

# pointing
POINTING_DEVICE_ENABLE = yes
DRAGSCROLL_ENABLE = yes

# audio
AUDIO_DRIVER = pwm_hardware

RAW_ENABLE = yes