#pragma once

// #define	SPLIT_HAND_PIN_LOW_IS_LEFT

#define SPI_DRIVER SPID1
#define DISPLAY_SPI_DIVISOR 4
#define DISPLAY_SPI_MODE 3

#define SPI_SCK_PIN  A5
#define SPI_MISO_PIN A6
#define SPI_MOSI_PIN A7

#define ENCODER_DEFAULT_POS 3
#define ENCODER_RESOLUTIONS { 2, 2, 2 }

#define DISPLAY_POWER_PIN B10
#define DISPLAY_BL_PIN B2
#define DISPLAY_RST_PIN B1
#define DISPLAY_DC_PIN B0
#define DISPLAY_CS_PIN C5

#define WS2812_PIN A8
#define WS2812_PWM_DRIVER PWMD1
#define WS2812_PWM_CHANNEL 1
#define WS2812_PWM_PAL_MODE 1
#define WS2812_PWM_DMA_STREAM STM32_DMA2_STREAM5
#define WS2812_PWM_DMA_CHANNEL 6

#define RGB_MATRIX_DEFAULT_HUE 5
#define RGB_MATRIX_DEFAULT_SAT 5
// we have 94 leds per side
#define RGB_TOT_IND_L 64
#define RGB_TOT_IND_R 64

// left side
#define RGB_KEYS_L_START 0 // 30 leds in keys + 4 in dpad + 3 in paddle-keys
#define RGB_KEYS_L_END 36
#define RGB_RING_L_START 37 // 18 leds in the ring
#define RGB_RING_L_END 54
#define RGB_INDICATOR_L_START 55 // 8 leds in the indicator
#define RGB_INDICATOR_L_END 62
// now we split it up for multi-function display
#define RGB_INDICATOR_L1_START RGB_INDICATOR_L_START
#define RGB_INDICATOR_L1_END 59
#define RGB_INDICATOR_L2_START 60
#define RGB_INDICATOR_L2_END RGB_INDICATOR_L_END

#define RGB_INNER_INTAKE_L_START 63 // there are 10 leds in the inner intake
#define RGB_INNER_INTAKE_L_END 72
#define RGB_OUTER_INTAKE_L_START 73 // there are 24 leds in the outer intake
// there are 24 leds in the outer intake
#define RGB_OUTER_INTAKE_L_END 96
// there are 12 leds in the logo
#define RGB_LOGO_L_START 97
#define RGB_LOGO_L_END 108 // 109 per side means 218 total

// right side
#define RGB_KEYS_R_START 111
#define RGB_KEYS_R_END 147
#define RGB_RING_R_START 148
#define RGB_RING_R_END 167
#define RGB_INDICATOR_R_START 168
#define RGB_INDICATOR_R_END 175
#define RGB_INDICATOR_R1_START RGB_INDICATOR_R_START
#define RGB_INDICATOR_R1_END 171
#define RGB_INDICATOR_R2_START 172
#define RGB_INDICATOR_R2_END RGB_INDICATOR_R_END

#define RGB_INNER_INTAKE_R_START 176
#define RGB_INNER_INTAKE_R_END 183
#define RGB_OUTER_INTAKE_R_START 184
#define RGB_OUTER_INTAKE_R_END 207
#define RGB_LOGO_R_START 208
#define RGB_LOGO_R_END 219


#define QUANTUM_PAINTER_DISPLAY_TIMEOUT 0

#define USB_VBUS_PIN D2
#define SERIAL_USART_DRIVER SD1
#define SERIAL_USART_TX_PIN A9
#define SERIAL_USART_RX_PIN A10
#define SERIAL_USART_TX_PAL_MODE 7
#define SERIAL_USART_RX_PAL_MODE 7
#define SERIAL_USART_FULL_DUPLEX
// note that F405's USART1 is not pin swap capable
#ifndef SERIAL_USART_SPEED
#    define SERIAL_USART_SPEED 1200000
#endif // SERIAL_USART_SPEED

#define EXTERNAL_FLASH_SPI_SLAVE_SELECT_PIN	B11
#define EXTERNAL_FLASH_SIZE	(16 * 1024 * 1024) // this equals 128megabits
#define EXTERNAL_FLASH_SPI_CLOCK_DIVISOR 4


// config sync settings
#define SPLIT_TRANSACTION_IDS_KB RPC_ID_KB_CONFIG_SYNC

#if defined(POINTING_DEVICE_ENABLE)
    #define PMW33XX_CS_PIN C4
    #define PMW33XX_SPI_DIVISOR 16
    #define POINTING_DEVICE_TASK_THROTTLE_MS 10 // this ensures that the trackball sensor polling happens only every 10ms
    #define MOUSE_EXTENDED_REPORT
    #define SPLIT_POINTING_ENABLE               // required for telling the master side about slave trackball state, i.e. if usb left, and tb right
    #define POINTING_DEVICE_RIGHT
    #define POINTING_DEVICE_INVERT_Y
    // #define POINTING_DEVICE_INVERT_X
    #define ROTATIONAL_TRANSFORM_ANGLE 90
    #define DRAGSCROLL_BUFFER_SIZE 0
    #define PMW33XX_CPI 700       // your mouse cpi (DPI) setting (how fast the ball tracks); note when usb main is on the left half this config needs to be 900
    #define DRAGSCROLL_CPI 100    // dragscroll cpi - interestingly, can't be set below 100?
#endif
