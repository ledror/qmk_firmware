#include QMK_KEYBOARD_H

enum keycodes {
    // Custom oneshot mod implementation with no timers.
    OS_SHFT = SAFE_RANGE,
    OS_CTRL,
    OS_ALT,
    OS_CMD,
};

enum layers {
    QWERTY = 0,
    NAV,
    SYM,
    NUM,
};

// Defaults are good for us
// #define TRI_LAYER_LOWER_LAYER _NAV
// #define TRI_LAYER_UPPER_LAYER _SYM
// #define TRI_LAYER_ADJUST_LAYER _NUM

#define LA_NAV MO(NAV)
#define LA_SYM MO(SYM)

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [QWERTY] = LAYOUT(
        KC_Q,      KC_W,      KC_E,      KC_R,      KC_T,      KC_Y,      KC_U,      KC_I,      KC_O,      KC_P,
        KC_A,      KC_S,      KC_D,      KC_F,      KC_G,      KC_H,      KC_J,      KC_K,      KC_L,      KC_SCLN,
        KC_Z,      KC_X,      KC_C,      KC_V,      KC_B,      KC_N,      KC_M,      KC_COMM,   KC_DOT,    KC_SLSH,
                                         KC_SPC,    LA_NAV,    LA_SYM,    KC_LSFT
    ),
    [NAV] = LAYOUT(
        KC_TAB,    KC_ESC,    KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_HOME,   KC_END,    KC_DEL,    KC_BSPC,
        OS_CMD,    OS_ALT,    OS_CTRL,   OS_SHFT,   KC_TRNS,   KC_LEFT,   KC_DOWN,   KC_UP,     KC_RGHT,   KC_ENT,
        KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_PGDN,   KC_PGUP,   KC_INS,    KC_TRNS,
                                         KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS
    ),
    [SYM] = LAYOUT(
        KC_DQUO,   KC_LBRC,   KC_LCBR,   KC_LPRN,   KC_PERC,   KC_CIRC,   KC_RPRN,   KC_RCBR,   KC_RBRC,   KC_GRV,
        KC_EXLM,   KC_QUOT,   KC_EQL,    KC_MINS,   KC_HASH,   KC_DLR,    OS_SHFT,   OS_CTRL,   OS_ALT,    OS_CMD,
        KC_AT,     KC_BSLS,   KC_PLUS,   KC_UNDS,   KC_AMPR,   KC_ASTR,   KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS,
                                         KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS
    ),
    [NUM] = LAYOUT(
        KC_1,      KC_2,      KC_3,      KC_4,      KC_5,      KC_6,      KC_7,      KC_8,      KC_9,      KC_0,
        OS_CMD,    OS_ALT,    OS_CTRL,   OS_SHFT,   KC_F11,    KC_F12,    OS_SHFT,   OS_ALT,    OS_CTRL,   OS_CMD,
        KC_F1,     KC_F2,     KC_F3,     KC_F4,     KC_F5,     KC_F6,     KC_F7,     KC_F8,     KC_F9,     KC_F10,
                                         KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS
    )
};
// clang-format on

bool is_oneshot_cancel_key(uint16_t keycode) {
    switch (keycode) {
        case LA_SYM:
        case LA_NAV:
            return IS_LAYER_ON(QWERTY);
        default:
            return false;
    }
}

bool is_oneshot_ignored_key(uint16_t keycode) {
    switch (keycode) {
        case LA_SYM:
        case LA_NAV:
        case KC_LSFT:
        case OS_SHFT:
        case OS_CTRL:
        case OS_ALT:
        case OS_CMD:
            return true;
        default:
            return false;
    }
}

typedef enum {
    os_up_unqueued,
    os_up_queued,
    os_down_unused,
    os_down_used,
} oneshot_state;

void update_oneshot(oneshot_state* state, uint16_t mod, uint16_t trigger, uint16_t keycode, keyrecord_t* record) {
    if (keycode == trigger) {
        if (record->event.pressed) {
            // Trigger keydown
            if (*state == os_up_unqueued) {
                register_code(mod);
            }
            *state = os_down_unused;
        } else {
            // Trigger keyup
            switch (*state) {
                case os_down_unused:
                    // If we didn't use the mod while trigger was held, queue it.
                    *state = os_up_queued;
                    break;
                case os_down_used:
                    // If we did use the mod while trigger was held, unregister it.
                    *state = os_up_unqueued;
                    unregister_code(mod);
                    break;
                default:
                    break;
            }
        }
    } else {
        if (record->event.pressed) {
            if (is_oneshot_cancel_key(keycode) && *state != os_up_unqueued) {
                // Cancel oneshot on designated cancel keydown.
                *state = os_up_unqueued;
                unregister_code(mod);
            }
        } else {
            if (!is_oneshot_ignored_key(keycode)) {
                // On non-ignored keyup, consider the oneshot used.
                switch (*state) {
                    case os_down_unused:
                        *state = os_down_used;
                        break;
                    case os_up_queued:
                        *state = os_up_unqueued;
                        unregister_code(mod);
                        break;
                    default:
                        break;
                }
            }
        }
    }
}

oneshot_state os_shft_state = os_up_unqueued;
oneshot_state os_ctrl_state = os_up_unqueued;
oneshot_state os_alt_state = os_up_unqueued;
oneshot_state os_cmd_state = os_up_unqueued;

bool process_record_user(uint16_t keycode, keyrecord_t* record) {
    update_oneshot(&os_shft_state, KC_LSFT, OS_SHFT, keycode, record);
    update_oneshot(&os_ctrl_state, KC_LCTL, OS_CTRL, keycode, record);
    update_oneshot(&os_alt_state, KC_LALT, OS_ALT, keycode, record);
    update_oneshot(&os_cmd_state, KC_LCMD, OS_CMD, keycode, record);

    return true;
}

layer_state_t layer_state_set_user(layer_state_t state) {
    return update_tri_layer_state(state, SYM, NAV, NUM);
}
