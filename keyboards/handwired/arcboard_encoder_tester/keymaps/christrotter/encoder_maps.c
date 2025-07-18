// Copyright 2023 Chris Trotter (@christrotter)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "quantum.h"

// Copyright 2023 Chris Trotter (@christrotter)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "quantum.h"

#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [0] = { ENCODER_CCW_CW(MS_WHLU, MS_WHLD),  ENCODER_CCW_CW(KC_VOLD, KC_VOLU)  },
};
#endif
