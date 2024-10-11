// Copyright 2023 Chris Trotter (@christrotter)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "quantum.h"
#include "arcboard_mk19.h"
#include "keymap.h"

extern bool set_scrolling;

void pointing_device_init_user(void) {
    set_auto_mouse_enable(true);
}

void pointing_device_init_kb(void) {
    pointing_device_init_user(); // set auto mouse layer
}

report_mouse_t pointing_device_task_user(report_mouse_t mouse_report) {
    if (set_scrolling) {
        pointing_device_set_cpi(DRAGSCROLL_CPI);
        mouse_report.h -= mouse_report.x; // -= to invert x-axis
        mouse_report.v =  mouse_report.y;
        mouse_report.x = 0;
        mouse_report.y = 0;
    } else {
        pointing_device_set_cpi(PMW33XX_CPI);
    }
    
    return mouse_report;
}
