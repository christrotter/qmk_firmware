# Hardware/build options
MCU 					= RP2040	# MCU name
BOOTLOADER 				= rp2040	# Bootloader selection
BOARD 					= GENERIC_RP_RP2040

# Functionality options
BOOTMAGIC_ENABLE		= yes
CONSOLE_ENABLE			= no        # Enables the use of qmk console; debug messages need this
POINTING_DEBUG_ENABLE	= no
MOUSEKEY_ENABLE 		= yes       # Mouse keys
EXTRAKEY_ENABLE 		= yes       # Audio control and System control
NKRO_ENABLE 			= yes 		# Enable N-Key Rollover
TAP_DANCE_ENABLE        = yes

# LED settings
RGB_MATRIX_ENABLE 		= yes 		# matrix enable turns on the white background lighting
RGB_MATRIX_LEDMAPS_ENABLED = yes 	# turn on per-key colours
RGB_MATRIX_DRIVER 		= WS2812
WS2812_DRIVER 			= vendor  	# RP2040 lyfe

# Trackball settings
POINTING_DEVICE_ENABLE 	= yes		# Flag, set to no to disable the trackball/PMW functionality
CUSTOM_POINTING_DEVICE  = yes		# Auto-mouse layer and such
POINTING_DEVICE_DRIVER 	= pmw3389
DRAGSCROLL_ENABLE		= yes
CUSTOM_DRAGSCROLL 		= yes

# Split settings
SPLIT_KEYBOARD 				= yes
# RP2040-specific split options
PICO_INTRINSICS_ENABLED = no # ATM Unsupported by ChibiOS.
SERIAL_DRIVER = vendor

# Enable the TFT screens
# currently disabled cuz transport woes, probably related to SPI config
QUANTUM_PAINTER_ENABLE 	= no
