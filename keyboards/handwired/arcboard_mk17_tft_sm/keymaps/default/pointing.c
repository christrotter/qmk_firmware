/*
 * Copyright 2023 Chris Trotter <ctrotter@gmail.com> (@christrotter)
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Publicw License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "quantum.h"
#include "arcboard_mk17_tft_sm.h"
#include "keymap.h"

#if defined(POINTING_DEVICE_ENABLE)
    void pointing_device_init_user(void) {
        set_auto_mouse_enable(true);
    }
    // TODO do we need this?
    void pointing_device_init_kb(void) {
        pointing_device_init_user(); // set auto mouse layer
    }
    // haha this requires split...
    report_mouse_t pointing_device_task_combined_user(report_mouse_t left_report, report_mouse_t right_report) {
        left_report.h = left_report.x;
        left_report.v = left_report.y;
        left_report.x = 0;
        left_report.y = 0;
        return pointing_device_combine_reports(left_report, right_report);
    }
#endif
