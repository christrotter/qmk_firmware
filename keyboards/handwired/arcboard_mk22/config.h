#pragma once

#define SPI_DRIVER SPID1
#define DISPLAY_SPI_DIVISOR 4
#define DISPLAY_SPI_MODE 3
#define SPI_SCK_PIN  B3
#define SPI_MISO_PIN B4
#define SPI_MOSI_PIN B5

#define ENCODER_DEFAULT_POS 3
#define ENCODER_RESOLUTIONS { 2, 2, 2 }

#define DISPLAY_POWER_PIN B14
#define DISPLAY_BL_PIN B1
#define DISPLAY_RST_PIN E9
#define DISPLAY_DC_PIN A7
#define DISPLAY_CS_PIN C4

#define QUANTUM_PAINTER_DISPLAY_TIMEOUT 0
#define LCD_HEIGHT 280
#define LCD_WIDTH 240

#define RGB_POWER_ENABLE_PIN D1

#define WS2812_PIN C9
#define WS2812_PWM_DRIVER PWMD3
#define WS2812_PWM_CHANNEL 4
#define WS2812_PWM_PAL_MODE 2
#define WS2812_PWM_DMA_STREAM STM32_DMA1_STREAM2
#define WS2812_PWM_DMA_CHANNEL 5

#define RGB_MATRIX_DEFAULT_HUE 5
#define RGB_MATRIX_DEFAULT_SAT 5

#define USB_VBUS_PIN B15

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
    #define PMW33XX_CS_PIN E8

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

// ws2812 chain, per half; the right half's leds follow the left's, so add RGB_LEDS_PER_HALF on the right
#define RGB_KEYS_START      0
#define RGB_KEYS_COUNT      24 // 4 rows x 6 cols
#define RGB_THUMBS_START    (RGB_KEYS_START + RGB_KEYS_COUNT)
#define RGB_THUMBS_COUNT    5
#define RGB_RING_START      (RGB_THUMBS_START + RGB_THUMBS_COUNT)
#define RGB_RING_COUNT      16
#define RGB_ENC1_START      (RGB_RING_START + RGB_RING_COUNT)
#define RGB_ENC1_COUNT      4
#define RGB_DPAD_START      (RGB_ENC1_START + RGB_ENC1_COUNT)
#define RGB_DPAD_COUNT      4
#define RGB_ENC2_START      (RGB_DPAD_START + RGB_DPAD_COUNT)
#define RGB_ENC2_COUNT      4
#define RGB_INDICATOR_START (RGB_ENC2_START + RGB_ENC2_COUNT)
#define RGB_INDICATOR_COUNT 16 // 4 rows of 4
#define RGB_PANEL_START     (RGB_INDICATOR_START + RGB_INDICATOR_COUNT)
#define RGB_PANEL_COUNT     60 // wing insert, logo included
#define RGB_LEDS_PER_HALF   (RGB_PANEL_START + RGB_PANEL_COUNT) // 133, must match split_count in keyboard.json

// logo leds within the panel (0-based offsets from RGB_PANEL_START): two runs of 10
#define RGB_PANEL_LOGO_A_START   17
#define RGB_PANEL_LOGO_B_START   33
#define RGB_PANEL_LOGO_RUN_COUNT 10

// ledmaps[] covers keys + thumbs: the left half's entries, then the right half's
#define RGB_LEDMAP_PER_HALF (RGB_KEYS_COUNT + RGB_THUMBS_COUNT)
