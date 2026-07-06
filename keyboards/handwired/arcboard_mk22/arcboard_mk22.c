#include "arcboard_mk22.h"
#include "transactions.h"
#include <string.h>

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
    if (config->is_dragscroll_enabled) {
        pointing_device_set_cpi(DRAGSCROLL_CPI);
    } else {
        pointing_device_set_cpi(PMW33XX_CPI);
    }
}
void pointing_device_init_kb(void) {
    pointing_device_init_user(); // set auto mouse layer
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
static void debug_kb_config_to_console(kb_config_t* config) {
    #    ifdef CONSOLE_ENABLE
        dprintf("(arcboard) process_record_kb: config = {\n"
                "\traw = 0x%X,\n"
                "\t{\n"
                "\t\tis_dragscroll_enabled=%u\n"
                "\t\tis_super_alt_tab_active=%u\n"
                "\t\tis_alt_tab_active=%u\n"
                "\t}\n"
                "}\n",
                config->raw, config->is_dragscroll_enabled, config->is_super_alt_tab_active, config->is_alt_tab_active);
    #    endif // CONSOLE_ENABLE
}


static void pointing_device_task_arcboard(report_mouse_t* mouse_report) {
    if (kb_config.is_dragscroll_enabled) {
        mouse_report->h -= mouse_report->x; // -= to invert x-axis
        mouse_report->v =  mouse_report->y;
        mouse_report->x = 0;
        mouse_report->y = 0;
    }
}

report_mouse_t pointing_device_task_kb(report_mouse_t mouse_report) {
    if (!is_keyboard_left()) {
        pointing_device_task_arcboard(&mouse_report);
        mouse_report = pointing_device_task_user(mouse_report);
    } else {
        mouse_report = pointing_device_task_user(mouse_report);
    }
    return mouse_report;
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

void kb_config_sync_handler(uint8_t initiator2target_buffer_size, const void* initiator2target_buffer, uint8_t target2initiator_buffer_size, void* target2initiator_buffer) {
    if (initiator2target_buffer_size == sizeof(kb_config)) {
        memcpy(&kb_config, initiator2target_buffer, sizeof(kb_config));
    }
}

void keyboard_post_init_kb(void) {
    #ifdef POINTING_DEVICE_ENABLE
    maybe_update_pointing_device_cpi(&kb_config);
    #endif  // POINTING_DEVICE_ENABLE
    transaction_register_rpc(RPC_ID_KB_CONFIG_SYNC, kb_config_sync_handler);
    keyboard_post_init_user();
}

void housekeeping_task_kb(void) {
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
}
