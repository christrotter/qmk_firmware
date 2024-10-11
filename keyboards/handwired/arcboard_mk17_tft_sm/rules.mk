# TFT options
QUANTUM_PAINTER_ENABLE 	= yes

RGB_MATRIX_ENABLE 		= yes 		# matrix enable turns on the white background lighting
RGB_MATRIX_LEDMAPS_ENABLED = yes 	# turn on per-key colours

# Trackball settings
POINTING_DEVICE_ENABLE 	= yes		# Flag, set to no to disable the trackball/PMW functionality

# Split settings
# RP2040-specific split options
PICO_INTRINSICS_ENABLED = no # ATM Unsupported by ChibiOS.
SERIAL_DRIVER = vendor

# Encoder
ENCODER_MAP_ENABLE = yes
