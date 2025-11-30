#include "arcboard_mk20.h"
#include QMK_KEYBOARD_H
#include "raw_hid.h"
#include "hid_functionality.h"


#if defined(RAW_ENABLE)
    void cycle_pedal_layer(void) {
        uint8_t data[32];
        memset(data, 0, 32);
        data[0] = (uint8_t)(PRODUCT_ID >> 8) & 0xFF;
        data[1] = (uint8_t)(PRODUCT_ID & 0xFF);
        data[2] = _CYCLE_PEDAL_LAYERS;
        printf("Raw-hid: Send data: %u %u %u\n", data[0], data[1], data[2]);
        raw_hid_send(data, 32);
    }
    // send a wled layer change
    void send_wled_layer(layer_state_t layer) {
        // we need to convert the layer from a bitmask to an integer
        layer = get_highest_layer(layer);
        if (is_auto_mouse_active()) { 
            layer = 1;
        };

        uint8_t data[32];
        memset(data, 0, 32);
        data[0] = (uint8_t)(PRODUCT_ID >> 8) & 0xFF;
        data[1] = (uint8_t)(PRODUCT_ID & 0xFF);
        data[2] = _WLED;
        data[3] = layer;
        printf("Raw-hid: Send WLED layer data: %u %u %u %u\n", data[0], data[1], data[2], data[3]);
        raw_hid_send(data, 32);
    }
#endif

// probably should separate this out into another file
#if defined(RAW_ENABLE)
void turn_appsense_layer_off(void) {
    if (get_highest_layer(layer_state | default_layer_state) != 0) {
        layer_off(get_highest_layer(layer_state | default_layer_state));
    }
}

// [2byte src identifier][1byte type][1byte type id][n bytes data]
    void raw_hid_receive(uint8_t *data, uint8_t length) {
        const hid_msg_t *msg = (hid_msg_t *)data;
        uint16_t incoming_pid = __builtin_bswap16(msg->source_id);

        if (incoming_pid == 0xF002) {
            xprintf("Raw-hid: we sent this, dropping rebroadcast packet. \n");
            return;
        }

        // if the current layer is not the first layer, we want to layer_off that layer

        switch (msg->type) {
            case _APPSENSE:
                switch (msg->type_id) {
                    case _APP_VSCODE:
                        turn_appsense_layer_off();
                        layer_on(_VSCODE);
                        break;
                    
                    case _APP_FUSION:
                        turn_appsense_layer_off();
                        layer_on(_FUSION);
                        break;

                    case _APP_CHROME:
                        turn_appsense_layer_off();
                        layer_on(_CHROME);
                        break;
                    
                    case _APP_KICAD:
                        turn_appsense_layer_off();
                        layer_on(_KICAD);
                        break;
                                
                    case _APP_OTHER:
                        layer_move(0);
                        break;
                    
                    default:
                        xprintf("Raw-hid: unknown app command: %02x \n", data[1]);
                        xprintf("Raw-hid: 0x%02x 0x%02x 0x%02x 0x%02x 0x%02x \n", data[0], data[1], data[2], data[3], data[4]);
                        break;
                }
                break;
            case _LAYER:
                switch (msg->type_id) {
                    case _TOGGLE_KB_RECT:
                        set_oneshot_layer(4, ONESHOT_START);
                        clear_oneshot_layer_state(ONESHOT_PRESSED);
                        break;
                }
                break;
            case _ONESHOT:
                switch (msg->type_id) {
                    case _ONESHOT_LGUI:
                        set_oneshot_mods(MOD_LGUI);
                        break;
                }
                break;
            // case _DRAGSCROLL:
            //     kb_set_pointer_dragscroll_enabled(!kb_get_pointer_dragscroll_enabled());
            //     break;

            default:
                xprintf("Raw-hid: received unexpected type: %02x \n", msg->type);
                xprintf("Raw-hid: 0x%02x 0x%02x 0x%02x 0x%02x 0x%02x \n", data[0], data[1], data[2], data[3], data[4]);
                break;
        }
    }
#endif // RAW_ENABLE