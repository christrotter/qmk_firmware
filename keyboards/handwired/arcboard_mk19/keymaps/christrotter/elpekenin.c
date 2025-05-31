/*
    this is example code from Elpekenin
    his take on how the data model might be implemented
*/
// WARNING: accessing the wrong union field (eg msg->setting when msg->id==APPLICATION) will cause bugs
// WARNING: if you add new structs, they **MUST** be marked with `PACKED` so that their data layout matches expected one

typedef enum {
    SETTING,
    APPLICATION,
    ...
    N_TYPES, // always last
} type_t;

//

typedef enum {
    DRAGSCROLL,
    GUI,
    RECT,
} setting_t;

typedef struct PACKED {
    setting_t id;
    uint16_t value; // lets make it a u16 to have some wiggle room
} setting_payload_t;

//

typedef enum {
    VSCODE,
    ITERM,
    ...
} app_t;

typedef struct PACKED {
    app_t id;
} app_payload_t;

//

typedef union PACKED {
    setting_t setting;
    app_t app;
} payload_t;

/*
    Examples
    [FROM_HOST, APPLICATION, VSCODE]
    [FROM_DEVICE, SETTING, DRAGSCROLL]
*/
typedef struct PACKED {
    type_t communication_type; // first byte
    type_t handler_type; // second byte
    payload_t payload; // the rest of the packet
} hid_msg_t;

// key here is that we are switching on the payload id
void setting_handler(payload_t payload) {
    switch (payload.setting.id) {
        case DRAGSCROLL:
            set_dragscroll(payload.setting.value);
            break;

        ...
    }
}

void application_handler(payload_t payload) {
    whatever();
}

// this syntax sucks, i know
typedef void (*handler_fn_t)(payload_t);

// an array of our handlers, i.e. which function to call
// if you call handlers[APPLICATION], you are essentially calling application_handler
// then, when you call handler and pass the payload, you're sending the payload data into that function
/*
    so your logic is...
    1. raw_hid_receive gets us our data
    2. we cast it to a hid_msg_t struct
    3. we get the id from the struct, our first byte
    4. we use that id to get the right handler from the handlers array
    5. we call the handler, passing in the payload
    6. the handler does its thing

    so for id=APPLICATION, payload.setting = layer_change, payload.app = VSCODE
    we are appsensing the VSCODE app and changing the layer to suit
*/

static const handler_fn_t handlers[] = {
    [SETTING] = setting_handler,
    [APPLICATION] = application_handler,
}
_Static_assert(ARRAY_SIZE(handlers) == N_TYPES, "Missed a handler");

void raw_hid_receive(uint8_t *data, uint8_t length) {
    const hid_msg_t *msg = (hid_msg_t *)data;
    const handler_fn_t handler = handlers[msg->id];
    handler(msg->payload);
}