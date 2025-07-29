// Copyright 2023 christrotter (@christrotter)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#define DEBOUNCE 10

// GPIO configuration
#define SPI_SCK_PIN  GP10
#define SPI_MOSI_PIN GP11
#define SPI_MISO_PIN GP12
#define DISPLAY_DC_PIN GP5
#define DISPLAY_RST_PIN GP4
#define DISPLAY_BL_PIN GP7
#define DISPLAY_CS_PIN GP9

#define SPI_DRIVER SPID1


#define DISPLAY_SPI_DIVISOR 0
#define DISPLAY_SPI_MODE 3

// #define QUANTUM_PAINTER_TASK_THROTTLE 50 // trying to reduce the scan rate impact
// #define QUANTUM_PAINTER_DISPLAY_TIMEOUT 0 // this is super important - you get a white screen after 30s otherwise
// #define QUANTUM_PAINTER_SUPPORTS_NATIVE_COLORS true

#define QUANTUM_PAINTER_DEBUG // massively degrades performance!!!