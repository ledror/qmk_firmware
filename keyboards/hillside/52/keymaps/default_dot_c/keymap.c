// Copyright 2022 Michael McCoyd (@mmccoyd)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

enum layers {
    _QWERTY = 0,
    _NAV,
    _SYM,
    _ADJUST,
};

#define xxxxxxx KC_NO

#define LY_NAV MO(_NAV)
#define LY_SYM MO(_SYM)
#define LY_ADJ MO(_ADJUST)

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_QWERTY] = LAYOUT(
     KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                                           KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC,
     KC_ESC,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                                           KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_ENT,
     KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_QUOT,                      KC_MENU, KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,
     KC_LCTL, KC_LALT, KC_LGUI,          KC_F13,  KC_SPC,  LY_NAV,  KC_LCTL,    KC_RGUI, LY_SYM,  KC_RSFT, KC_RALT,          KC_RGUI, KC_RALT, KC_RCTL
    ),
    [_NAV] = LAYOUT(
     _______, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                                           KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    _______,
     _______, KC_LGUI, KC_LALT, KC_LCTL, KC_LSFT, _______,                                        KC_LEFT, KC_DOWN, KC_UP,   KC_RIGHT,KC_DEL,  _______,
     _______, _______, _______, _______, _______, _______, _______,                      _______, KC_HOME, KC_PGDN, KC_PGUP, KC_END,  _______, _______,
     _______, _______, _______,          _______, _______, _______, _______,    _______, _______, _______, _______,          _______, _______, _______
    ),
    [_SYM] = LAYOUT(
     _______, KC_DQUO, KC_LBRC, KC_LCBR, KC_LPRN, KC_PERC,                                        KC_CIRC, KC_RPRN, KC_RCBR, KC_RBRC, KC_GRV,  _______,
     _______, KC_EXLM, KC_QUOT, KC_EQL,  KC_MINUS,KC_HASH,                                        KC_DLR,  KC_RSFT, OS_RCTL, KC_RALT, KC_RGUI, _______,
     _______, KC_AT,   KC_BSLS, KC_PLUS, KC_UNDS, KC_AMPR, _______,                      _______, KC_ASTR, _______, _______, _______, _______, _______,
     _______, _______, _______,          _______, _______, _______, _______,    _______, _______, _______, _______,          _______, _______, _______
    ),
    [_ADJUST] = LAYOUT(
     _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                                          KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  _______,
     _______, KC_LGUI, KC_LALT, KC_LCTL, KC_LSFT, KC_F11,                                         KC_F12,  KC_RSFT, OS_RCTL, KC_RALT, KC_RGUI, _______,
     _______, _______, _______, _______, _______, _______, _______,                      _______, _______, _______, _______, _______, _______, _______,
     QK_BOOT, _______, _______,          _______, _______, _______, _______,    _______, _______, _______, _______,          _______, _______, _______
    ),
};

//  Template:
//    [_INDEX] = LAYOUT(
//     _______, _______, _______, _______, _______, _______,                                        _______, _______, _______, _______, _______, _______,
//     _______, _______, _______, _______, _______, _______,                                        _______, _______, _______, _______, _______, _______,
//     _______, _______, _______, _______, _______, _______, _______,                      _______, _______, _______, _______, _______, _______, _______,
//     _______, _______, _______,          _______, _______, _______, _______,    _______, _______, _______, _______,          _______, _______, _______
//    ),

layer_state_t layer_state_set_user(layer_state_t state) {
    return update_tri_layer_state(state, _SYM, _NAV, _ADJUST);
}
