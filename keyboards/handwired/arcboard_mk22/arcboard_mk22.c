#include "arcboard_mk22.h"
#include <string.h>

#ifdef SPLIT_KEYBOARD
#include "transactions.h"
#endif  // SPLIT_KEYBOARD

typedef union {
    uint8_t raw;
    struct {
        bool    is_dragscroll_enabled : 1;
        bool    is_super_alt_tab_active : 1;
        bool    is_alt_tab_active     : 1;
    } __attribute__((packed));
} kb_config_t;

static kb_config_t kb_config = {0};

#ifdef POINTING_DEVICE_ENABLE
static void maybe_update_pointing_device_cpi(kb_config_t* config) {
    pointing_device_set_cpi_on_side(true, LEFT_SCROLL_CPI);
    pointing_device_set_cpi_on_side(false, config->is_dragscroll_enabled ? DRAGSCROLL_CPI : PMW33XX_CPI);
}
void pointing_device_init_kb(void) {
    pointing_device_init_user(); // set auto mouse layer
    maybe_update_pointing_device_cpi(&kb_config);
}

bool kb_get_pointer_dragscroll_enabled(void) {
    return kb_config.is_dragscroll_enabled;
}
void kb_set_pointer_dragscroll_enabled(bool enable) {
    kb_config.is_dragscroll_enabled = enable;
    maybe_update_pointing_device_cpi(&kb_config);
}
#endif  // POINTING_DEVICE_ENABLE

// super-alt-tab functionality
bool kb_get_super_alt_tab_state(void) {
    return kb_config.is_super_alt_tab_active;
}
void kb_set_super_alt_tab_active(void) {
    kb_config.is_super_alt_tab_active = true;
}
void kb_set_super_alt_tab_off(void) {
    kb_config.is_super_alt_tab_active = false;
}

// alt-tab functionality
bool kb_get_alt_tab_state(void) {
    return kb_config.is_alt_tab_active;
}
void kb_set_alt_tab_active(void) {
    kb_config.is_alt_tab_active = true;
}
void kb_set_alt_tab_off(void) {
    kb_config.is_alt_tab_active = false;
}

#ifdef POINTING_DEVICE_ENABLE
#    ifdef CONSOLE_ENABLE
static void debug_kb_config_to_console(kb_config_t* config) {
    dprintf("(arcboard) process_record_kb: config = {\n"
            "\traw = 0x%X,\n"
            "\t{\n"
            "\t\tis_dragscroll_enabled=%u\n"
            "\t\tis_super_alt_tab_active=%u\n"
            "\t\tis_alt_tab_active=%u\n"
            "\t}\n"
            "}\n",
            config->raw, config->is_dragscroll_enabled, config->is_super_alt_tab_active, config->is_alt_tab_active);
}
#    endif // CONSOLE_ENABLE

// the sensor can't go below 100 cpi, which is still far too many counts per scroll step; divide them down, keeping the remainder
#ifndef LEFT_SCROLL_DIVISOR
#    define LEFT_SCROLL_DIVISOR 8
#endif

static void convert_to_scroll(report_mouse_t* mouse_report, bool reverse) {
    if (reverse) {
        static int16_t acc_x = 0, acc_y = 0;
        acc_x += mouse_report->x;
        acc_y += mouse_report->y;
        mouse_report->h += acc_x / LEFT_SCROLL_DIVISOR;
        mouse_report->v = -(acc_y / LEFT_SCROLL_DIVISOR);
        acc_x %= LEFT_SCROLL_DIVISOR;
        acc_y %= LEFT_SCROLL_DIVISOR;
    } else {
        mouse_report->h -= mouse_report->x; // -= to invert x-axis
        mouse_report->v =  mouse_report->y;
    }
    mouse_report->x = 0;
    mouse_report->y = 0;
}

// auto mouse only sees the combined report, so remember the right-side movement for it
static report_mouse_t right_report_for_auto_mouse;

report_mouse_t pointing_device_task_combined_kb(report_mouse_t left_report, report_mouse_t right_report) {
    convert_to_scroll(&left_report, true); // left trackball is always scroll
    if (kb_config.is_dragscroll_enabled) {
        convert_to_scroll(&right_report, false);
    }
    right_report_for_auto_mouse = right_report;
    return pointing_device_combine_reports(left_report, right_report);
}

// only the right trackball (and buttons) may activate the auto mouse layer; left scrolling is ignored
bool auto_mouse_activation(report_mouse_t mouse_report) {
    static int16_t total_x, total_y, total_h, total_v;
    total_x += right_report_for_auto_mouse.x;
    total_y += right_report_for_auto_mouse.y;
    total_h += right_report_for_auto_mouse.h;
    total_v += right_report_for_auto_mouse.v;
    bool activated = abs(total_x) > AUTO_MOUSE_THRESHOLD || abs(total_y) > AUTO_MOUSE_THRESHOLD || abs(total_h) > AUTO_MOUSE_THRESHOLD || abs(total_v) > AUTO_MOUSE_THRESHOLD || mouse_report.buttons;
    if (activated) {
        total_x = total_y = total_h = total_v = 0;
    }
    return activated;
}

report_mouse_t pointing_device_task_kb(report_mouse_t mouse_report) {
    return pointing_device_task_user(mouse_report);
}

bool is_mouse_record_kb(uint16_t keycode, keyrecord_t* record) {
    switch(keycode) {
        case QK_LAYER_LOCK:
            return true;
        case DRAGSCROLL_MODE_TOGGLE:
            return true;
        default:
            return false;
    }
    return  is_mouse_record_user(keycode, record);
}
#endif  // POINTING_DEVICE_ENABLE

bool process_record_kb(uint16_t keycode, keyrecord_t* record) {
#ifdef POINTING_DEVICE_ENABLE
    switch (keycode) {
        case DRAGSCROLL_MODE_TOGGLE:
            if (record->event.pressed) {
                kb_set_pointer_dragscroll_enabled(!kb_get_pointer_dragscroll_enabled());
                #ifdef CONSOLE_ENABLE
                    xprintf("process_record_kb: DRAGSCROLL_MODE_TOGGLE");
                    debug_kb_config_to_console(&kb_config);
                #endif // CONSOLE_ENABLE
            }
            break;
    }
#endif  // POINTING_DEVICE_ENABLE
    return process_record_user(keycode, record);
}

#ifdef SPLIT_KEYBOARD
void kb_config_sync_handler(uint8_t initiator2target_buffer_size, const void* initiator2target_buffer, uint8_t target2initiator_buffer_size, void* target2initiator_buffer) {
    if (initiator2target_buffer_size == sizeof(kb_config)) {
        memcpy(&kb_config, initiator2target_buffer, sizeof(kb_config));
    }
}
#endif  // SPLIT_KEYBOARD

void keyboard_post_init_kb(void) {
    // Turn on the RGB
    gpio_set_pin_output(RGB_POWER_ENABLE_PIN);
    gpio_write_pin_high(RGB_POWER_ENABLE_PIN);
    gpio_set_pin_output(DISPLAY_POWER_PIN);
    gpio_write_pin_high(DISPLAY_POWER_PIN);
    
    #ifdef POINTING_DEVICE_ENABLE
    maybe_update_pointing_device_cpi(&kb_config);
    #endif  // POINTING_DEVICE_ENABLE

    #ifdef SPLIT_KEYBOARD
    transaction_register_rpc(RPC_ID_KB_CONFIG_SYNC, kb_config_sync_handler);
    #endif  // SPLIT_KEYBOARD

    keyboard_post_init_user();
}

void housekeeping_task_kb(void) {
    #ifdef SPLIT_KEYBOARD
    if (is_keyboard_master()) {
        // Keep track of the last state, so that we can tell if we need to propagate to slave.
        static kb_config_t last_kb_config = {0};
        static uint32_t           last_sync             = 0;
        bool                      needs_sync            = false;

        // Check if the state values are different.
        if (memcmp(&kb_config, &last_kb_config, sizeof(kb_config))) {
            needs_sync = true;
            memcpy(&last_kb_config, &kb_config, sizeof(kb_config));
        }
        // Send to slave every 500ms regardless of state change.
        if (timer_elapsed32(last_sync) > 500) {
            needs_sync = true;
        }

        if (needs_sync) {
            // this is one of those one-way data transfers mentioned in the docs; does not need SPLIT_TRANSPORT=custom
            if (transaction_rpc_send(RPC_ID_KB_CONFIG_SYNC, sizeof(kb_config), &kb_config)) {
                last_sync = timer_read32();
            }
        }
    }
    #endif  // SPLIT_KEYBOARD
}
