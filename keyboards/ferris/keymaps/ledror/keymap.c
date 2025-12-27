#include QMK_KEYBOARD_H

enum layers {
    _QWERTY = 0,
    _NAV,
    _SYM,
    _NUM,
};

// Defaults are good for us
// #define TRI_LAYER_LOWER_LAYER _NAV
// #define TRI_LAYER_UPPER_LAYER _SYM
// #define TRI_LAYER_ADJUST_LAYER _NUM

#define MO_NAV TL_LOWR
#define MO_SYM TL_UPPR

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_QWERTY] = LAYOUT_split_3x5_2(
        KC_Q,      KC_W,      KC_E,      KC_R,      KC_T,      KC_Y,      KC_U,      KC_I,      KC_O,      KC_P,
        KC_A,      KC_S,      KC_D,      KC_F,      KC_G,      KC_H,      KC_J,      KC_K,      KC_L,      KC_SCLN,
        KC_Z,      KC_X,      KC_C,      KC_V,      KC_B,      KC_N,      KC_M,      KC_COMM,   KC_DOT,    KC_SLSH,
                                         KC_SPC,    MO_NAV,    MO_SYM,    KC_LSFT
    ),
    [_NAV] = LAYOUT_split_3x5_2(
        KC_TAB,    KC_ESC,    KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_HOME,   KC_END,    KC_DEL,    KC_BSPC,
        OS_LGUI,   OS_LALT,   OS_LCTL,   OS_LSFT,   KC_TRNS,   KC_LEFT,   KC_DOWN,   KC_UP,     KC_RGHT,   KC_ENT,
        KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_PGDN,   KC_PGUP,   KC_INS,    KC_TRNS,
                                         KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS
    ),
    [_SYM] = LAYOUT_split_3x5_2(
        KC_DQUO,   KC_LBRC,   KC_LCBR,   KC_LPRN,   KC_PERC,   KC_CIRC,   KC_RPRN,   KC_RCBR,   KC_RBRC,   KC_GRV,
        KC_EXLM,   KC_QUOT,   KC_EQL,    KC_MINS,   KC_HASH,   KC_DLR,    OS_RSFT,   OS_RCTL,   OS_RALT,   OS_RGUI,
        KC_AT,     KC_BSLS,   KC_PLUS,   KC_UNDS,   KC_AMPR,   KC_ASTR,   KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS,
                                         KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS
    ),
    [_NUM] = LAYOUT_split_3x5_2(
        KC_1,      KC_2,      KC_3,      KC_4,      KC_5,      KC_6,      KC_7,      KC_8,      KC_9,      KC_0,
        OS_LGUI,   OS_LALT,   OS_LCTL,   OS_LSFT,   KC_F11,    KC_F12,    OS_RSFT,   OS_RALT,   OS_RCTL,   OS_RGUI,
        KC_F1,     KC_F2,     KC_F3,     KC_F4,     KC_F5,     KC_F6,     KC_F7,     KC_F8,     KC_F9,     KC_F10,
                                         KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS
    )
};
// clang-format on
