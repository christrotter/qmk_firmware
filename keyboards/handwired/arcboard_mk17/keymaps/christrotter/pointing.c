// Copyright 2023 Chris Trotter (@christrotter)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "quantum.h"
#include "arcboard_mk17.h"
#include "keymap.h"

#if defined(POINTING_DEVICE_ENABLE)
    #if defined(CONSOLE_ENABLE)
        #include "print.h"
        static uint32_t last_draw = 0;
    #endif
    extern bool set_scrolling;

    void pointing_device_init_user(void) {
        set_auto_mouse_enable(true);
    }
    void pointing_device_init_kb(void) {
        pointing_device_init_user(); // set auto mouse layer
    }
    // todo: put this back to single side only
    report_mouse_t pointing_device_task_combined_user(report_mouse_t left_report, report_mouse_t right_report) {
        #if defined(CONSOLE_ENABLE)
        if (timer_elapsed32(last_draw) > 10000) { // every 10s write our cpi out to console
            last_draw = timer_read32();
            if (is_keyboard_left()) {
                uprintf("left cpi is: %d \n", pointing_device_get_cpi());
            }
            else {
                uprintf("right cpi is: %d \n", pointing_device_get_cpi());
            }
        }
        #endif
        if (set_scrolling) {
            pointing_device_set_cpi(DRAGSCROLL_CPI);
            right_report.h -= right_report.x; // -= to invert x-axis
            right_report.v = right_report.y;
            right_report.x = 0;
            right_report.y = 0;
        } else {
            pointing_device_set_cpi(PMW33XX_CPI);
        }

        return pointing_device_combine_reports(left_report, right_report);
    }
    report_mouse_t pointing_device_task_user(report_mouse_t mouse_report) {
        // ...
    #ifdef MACCEL_ENABLE
        return pointing_device_task_maccel(mouse_report);
    #endif
    }
#endif
