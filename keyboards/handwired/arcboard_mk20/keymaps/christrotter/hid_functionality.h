

#if defined(RAW_ENABLE)
    // raw-hid config
    typedef struct PACKED {
        uint16_t source_id;  // first two bytes == always identifier
        uint8_t type;        // 1 byte for type
        uint8_t type_id;     // 1 byte for type id
        uint8_t payload[16]; // takes up the rest of the bytes you send; 16 cuz nice number, can be up to 26
    } hid_msg_t;
    
    typedef enum {
        _APPSENSE   = 0x01,
        _LAYER      = 0x02,
        _ONESHOT    = 0x03,
        _DRAGSCROLL = 0x04,
        _WLED       = 0x05,
    } hid_types;
    
    typedef enum {
        _ONESHOT_SHIFT = 0x01,
        _ONESHOT_LGUI  = 0x02,
        _ONESHOT_LCTRL = 0x03,
        _ONESHOT_LALT  = 0x04,
    } hid_oneshot_ids;
    
    typedef enum {
        _APP_OTHER  = 0x00,
        _APP_VSCODE = 0x01,
        _APP_CHROME = 0x02,
        _APP_FUSION = 0x03,
        _APP_KICAD = 0x04,
    } hid_appsense_apps;
    
    typedef enum {
        _CYCLE_PEDAL_LAYERS = 0xBA,
    } hid_commands;
    
    // refactor this code to use the native layers...
    typedef enum {
        _TOGGLE_KB_RECT = 0xDF,
    } hid_layers;
#endif // RAW_ENABLE

void cycle_pedal_layer(void);
void send_wled_layer(layer_state_t layer);
