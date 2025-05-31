
#include "raw_hid.h"
#include "hid_functionality.h"
#include "keymap.h"

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
#endif

// probably should separate this out into another file
#if defined(RAW_ENABLE)
// [2byte src identifier][1byte type][1byte type id][n bytes data]
    void raw_hid_receive(uint8_t *data, uint8_t length) {
        const hid_msg_t *msg = (hid_msg_t *)data;
        uint16_t incoming_pid = __builtin_bswap16(msg->source_id);

        if (incoming_pid == 0xF002) {
            xprintf("Raw-hid: we sent this, dropping rebroadcast packet. \n");
            return;
        } 

        switch (msg->type) {
            case _APPSENSE:
                switch (msg->type_id) {
                    case _APP_VSCODE:
                        layer_on(_VSCODE);
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
            case _DRAGSCROLL:
                kb_set_pointer_dragscroll_enabled(!kb_get_pointer_dragscroll_enabled());
                break;

            default:
                xprintf("Raw-hid: received unexpected type: %02x \n", msg->type);
                xprintf("Raw-hid: 0x%02x 0x%02x 0x%02x 0x%02x 0x%02x \n", data[0], data[1], data[2], data[3], data[4]);
                break;
        }
    }
#endif // RAW_ENABLE