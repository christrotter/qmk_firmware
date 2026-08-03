#pragma once

// #define SPI_DRIVER SPID1
// #define DISPLAY_SPI_DIVISOR 4
// #define DISPLAY_SPI_MODE 3
// 
// #define SPI_SCK_PIN  A5
// #define SPI_MISO_PIN A6
// #define SPI_MOSI_PIN A7
// 
#define ENCODER_DEFAULT_POS 3
#define ENCODER_RESOLUTIONS { 2, 2, 2 }

// #define DISPLAY_POWER_PIN B10
// #define DISPLAY_BL_PIN B2
// #define DISPLAY_RST_PIN B1
// #define DISPLAY_DC_PIN B0
// #define DISPLAY_CS_PIN C5

// #define QUANTUM_PAINTER_DISPLAY_TIMEOUT 0
// #define LCD_HEIGHT 284
// #define LCD_WIDTH 76

#define RGB_POWER_ENABLE_PIN D1

#define WS2812_PIN C9
#define WS2812_PWM_DRIVER PWMD3
#define WS2812_PWM_CHANNEL 4
#define WS2812_PWM_PAL_MODE 2
#define WS2812_PWM_DMA_STREAM STM32_DMA1_STREAM2
#define WS2812_PWM_DMA_CHANNEL 5

#define RGB_MATRIX_DEFAULT_HUE 5
#define RGB_MATRIX_DEFAULT_SAT 5

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

// #define EXTERNAL_FLASH_SPI_SLAVE_SELECT_PIN	B11
// #define EXTERNAL_FLASH_SIZE	(16 * 1024 * 1024) // this equals 128megabits
// #define EXTERNAL_FLASH_SPI_CLOCK_DIVISOR 4


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
    #define ROTATIONAL_TRANSFORM_ANGLE 90
    #define DRAGSCROLL_BUFFER_SIZE 0
    #define PMW33XX_CPI 600       // your mouse cpi (DPI) setting (how fast the ball tracks); note when usb main is on the left half this config needs to be 900
    #define DRAGSCROLL_CPI 100    // dragscroll cpi - interestingly, can't be set below 100?
#endif

#if defined(RGB_MATRIX_LEDMAPS_ENABLED)
    #define INDICATOR_BRIGHTNESS 150
    #define INDICATOR_BRIGHTNESS_IDLE 70
    #define INTAKE_BRIGHTNESS 50
    #define LOGO_BRIGHTNESS 90
    #define INDICATOR_BRIGHTNESS_RING 200
    #define KEYS_BRIGHTNESS 90

    // 103-37 = 66
    // this is just really ugly.  required by the rgb_range code to handle the split numbering.
    #define RGB_TOT_IND_L 66
    #define RGB_TOT_IND_R 66

    // 30 in keys + 4 in dpad + 3 in paddle-keys
    // 37 + 19 + 8 + 10 + 16 + 12 = 102
    // 102 - 37 = 65
    #define RGB_LEDS_IN_KEYS 37
    #define RGB_LEDS_IN_RING 20
    #define RGB_LEDS_IN_INDICATOR 8
    #define RGB_LEDS_IN_INDICATOR_SPLIT 4
    #define RGB_LEDS_IN_INNER_INTAKE 10
    #define RGB_LEDS_IN_OUTER_INTAKE 12
    #define RGB_LEDS_IN_LOGO 12

    // left side led counts
    // keys
    #define RGB_KEYS_L_START 0
    #define RGB_KEYS_L_END RGB_KEYS_L_START + RGB_LEDS_IN_KEYS

    // ring encoder
    #define RGB_RING_L_START RGB_KEYS_L_END
    #define RGB_RING_L_END RGB_RING_L_START + RGB_LEDS_IN_RING

    // indicator bar // 8 leds in the indicator
    #define RGB_INDICATOR_L_START RGB_RING_L_END
    #define RGB_INDICATOR_L_END RGB_INDICATOR_L_START + RGB_LEDS_IN_INDICATOR - 1 // uncertain why we need the -1, buuut we do!

    // now we split it up for multi-function display
    #define RGB_INDICATOR_L1_START RGB_INDICATOR_L_START
    #define RGB_INDICATOR_L1_END RGB_INDICATOR_L_START + RGB_LEDS_IN_INDICATOR_SPLIT
    #define RGB_INDICATOR_L2_START RGB_INDICATOR_L1_END
    #define RGB_INDICATOR_L2_END RGB_INDICATOR_L_END

    // intakes
    #define RGB_INNER_INTAKE_L_START RGB_INDICATOR_L_END // there are 10 leds in the inner intake
    #define RGB_INNER_INTAKE_L_END RGB_INNER_INTAKE_L_START + RGB_LEDS_IN_INNER_INTAKE
    #define RGB_OUTER_INTAKE_L_START RGB_INNER_INTAKE_L_END  // there are 24 leds in the outer intake
    // there are 24 leds in the outer intake
    #define RGB_OUTER_INTAKE_L_END RGB_OUTER_INTAKE_L_START + RGB_LEDS_IN_OUTER_INTAKE
    // there are 12 leds in the logo
    #define RGB_LOGO_L_START RGB_OUTER_INTAKE_L_END
    #define RGB_LOGO_L_END RGB_LOGO_L_START + RGB_LEDS_IN_LOGO

    // right side
    // keys
    #define RGB_KEYS_R_START RGB_LOGO_L_END
    #define RGB_KEYS_R_END RGB_KEYS_R_START + RGB_LEDS_IN_KEYS

    // ring encoder
    #define RGB_RING_R_START RGB_KEYS_R_END + 4
    #define RGB_RING_R_END RGB_RING_R_START + RGB_LEDS_IN_RING

    // indicator bar // 8 leds in the indicator
    #define RGB_INDICATOR_R_START RGB_RING_R_END
    #define RGB_INDICATOR_R_END RGB_INDICATOR_R_START + RGB_LEDS_IN_INDICATOR

    // now we split it up for multi-function display
    #define RGB_INDICATOR_R1_START RGB_INDICATOR_R_START
    #define RGB_INDICATOR_R1_END RGB_INDICATOR_R_START + RGB_LEDS_IN_INDICATOR_SPLIT
    #define RGB_INDICATOR_R2_START RGB_INDICATOR_R1_END
    #define RGB_INDICATOR_R2_END RGB_INDICATOR_R_END

    // intakes
    #define RGB_INNER_INTAKE_R_START RGB_INDICATOR_R_END // there are 10 leds in the inner intake
    #define RGB_INNER_INTAKE_R_END RGB_INNER_INTAKE_R_START + RGB_LEDS_IN_INNER_INTAKE
    #define RGB_OUTER_INTAKE_R_START RGB_INNER_INTAKE_R_END  // there are 24 leds in the outer intake
    // there are 24 leds in the outer intake
    #define RGB_OUTER_INTAKE_R_END RGB_OUTER_INTAKE_R_START + RGB_LEDS_IN_OUTER_INTAKE
    // there are 12 leds in the logo
    #define RGB_LOGO_R_START RGB_OUTER_INTAKE_R_END
    #define RGB_LOGO_R_END RGB_LOGO_R_START + RGB_LEDS_IN_LOGO
#endif
