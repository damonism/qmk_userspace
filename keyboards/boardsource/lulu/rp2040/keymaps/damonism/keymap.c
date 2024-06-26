// Copyright 2022 Cole Smith <cole@boadsource.xyz>
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

// Some custom OLED screens
#include "oleds.h"

// Sets the default mode, if none has been set
#define RGB_MATRIX_STARTUP_MODE RGB_MATRIX_ALPHAS_MODS

enum custom_keycodes {
    EM_DASH = SAFE_RANGE,
    EN_DASH,
    EX_DASH,
    CX_MOD
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {

     // Get current mod and one-shot mod states.
     const uint8_t mods = get_mods();
     const uint8_t oneshot_mods = get_oneshot_mods();

    switch (keycode) {
    case EM_DASH:
        if (record->event.pressed) {
            // when keycode EM_DASH is pressed
            SEND_STRING(SS_LALT(SS_TAP(X_KP_0) SS_TAP(X_KP_1) SS_TAP(X_KP_5) SS_TAP(X_KP_1)));
        } else {
            // when keycode EM_DASH is released
        }
    break;

    case EN_DASH:
        if (record->event.pressed) {
            // when keycode EN_DASH is pressed
            SEND_STRING(SS_LALT(SS_TAP(X_KP_0) SS_TAP(X_KP_1) SS_TAP(X_KP_5) SS_TAP(X_KP_0)));
        } else {
            // when keycode EN_DASH is released
        }
    break;

    case EX_DASH:
        // Minus when pressed normally, en-dash when alt-minus and en-dash when shift-alt-minus
        if (record->event.pressed) {
            if ((mods | oneshot_mods) & MOD_MASK_SHIFT) {       // Shift
                clear_oneshot_mods();
                unregister_mods(MOD_MASK_CSAG);
                if ((mods | oneshot_mods) & MOD_MASK_ALT) {     // Shift and Alt
                    SEND_STRING(SS_LALT(SS_TAP(X_KP_0) SS_TAP(X_KP_1) SS_TAP(X_KP_5) SS_TAP(X_KP_1)));
                } else {
                    SEND_STRING("_");                           // Just shift
                }
                register_mods(mods);    // Restore mods.
            } else if ((mods | oneshot_mods) & MOD_MASK_ALT) {  // Alt
                SEND_STRING(SS_LALT(SS_TAP(X_KP_0) SS_TAP(X_KP_1) SS_TAP(X_KP_5) SS_TAP(X_KP_0)));
            } else {
                SEND_STRING("-");
            }

        } else {
            // when keycode EX_DASH is released
        }

    break;

    // This can only be used with tap.code(), not SEND_STRING()
    case CX_MOD:
        if (record->event.pressed) {
            register_code16((get_highest_layer(default_layer_state) > 0) ? KC_LCTL : KC_LGUI);
        } else {
            unregister_code16((get_highest_layer(default_layer_state) > 0) ? KC_LCTL : KC_LGUI);
        }

    break;

    }

    return true;
};

enum layers {
    _QWERTY_WIN,
    _LOWER_WIN,
    _RAISE_WIN,
    _QWERTY,
    _LOWER,
    _RAISE,
    _ADJUST
};

// CTRL-ALT-ESC key
#define KC_CAD LALT(LCTL(KC_DEL))

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* QWERTY (WIN)
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * | G/ESC|   1  |   2  |   3  |   4  |   5  |                    |   6  |   7  |   8  |   9  |   0  |BackSP|
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |Tb/MO6|   Q  |   W  |   E  |   R  |   T  |                    |   Y  |   U  |   I  |   O  |   P  |EXDASH|
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |LGUI  |   A  |   S  |   D  |   F  |   G  |-------.    ,-------|   H  |   J  |   K  |   L  |   ;  |  '   |
 * |------+------+------+------+------+------|   [   |    |    ]  |------+------+------+------+------+------|
 * |LShift|   Z  |   X  |   C  |   V  |   B  |-------|    |-------|   N  |   M  |   ,  |   .  |   /  |RShift|
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   | LCTRL| LAlt |LOWER | /Space  /       \Enter \  |RAISE | RAlt | RCTRL|
 *                   |      |      |      |/       /         \      \ |      |      |      |
 *                   `----------------------------'           '------''--------------------'
 */

[0] = LAYOUT(QK_GESC,      KC_1, KC_2,  KC_3,    KC_4,    KC_5,                    KC_6,  KC_7,    KC_8,    KC_9,   KC_0,    KC_BSPC,
             LT(6,KC_TAB), KC_Q, KC_W,  KC_E,    KC_R,    KC_T,                    KC_Y,  KC_U,    KC_I,    KC_O,   KC_P,    EX_DASH,
             KC_LGUI,      KC_A, KC_S,  KC_D,    KC_F,    KC_G,                    KC_H,  KC_J,    KC_K,    KC_L,   KC_SCLN, KC_QUOT,
             KC_LSFT,      KC_Z, KC_X,  KC_C,    KC_V,    KC_B,  KC_LBRC, KC_RBRC, KC_N,  KC_M,    KC_COMM, KC_DOT, KC_SLSH, KC_RSFT,
                                        KC_LCTL, KC_LALT, MO(1), KC_SPC,  KC_ENT,  MO(2), KC_RALT, KC_RCTL
             ),

/* LOWER (WIN)
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |  `   |  F1  |  F2  |  F3  |  F4  |  F5  |                    |  F6  |  F6  |  F6  |  F9  | F10  |  DEL |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |   1  |  2   |  3   |  4   |  5   |                    |  6   |  7   |  8   |  9   |  0   |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |  F1  |  F2  |  F3  |  F4  |  F5  |-------.    ,-------| LEFT | DOWN |  UP  | RIGHT| F11  |      |
 * |------+------+------+------+------+------|RGB_TOG|    |  PLAY |------+------+------+------+------+------|
 * |      |  F6  |  F6  |  F6  |  F9  | F10  |-------|    |-------| HOME | PGDN | PGUP | END  | F12  |      |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   | LCTRL| LAlt |LOWER | /Space  /       \Enter \  |RAISE | RAlt | RCTRL|
 *                   |      |      |      |/       /         \      \ |      |      |      |
 *                   `----------------------------'           '------''--------------------'
 */

[1] = LAYOUT(KC_GRV,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                     KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10, KC_DEL,
             KC_TRNS, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                      KC_6,    KC_7,    KC_8,    KC_9,    KC_0,   KC_TRNS,
             KC_TRNS, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                     KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, KC_F11, KC_TRNS,
             KC_TRNS, KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  RGB_TOG, KC_TRNS, KC_HOME, KC_PGDN, KC_PGUP, KC_END,  KC_F12, KC_TRNS,
                                        KC_TRNS, KC_TRNS, KC_TRNS, KC_MUTE, KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS
             ),

/* RAISE (WIN)
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |C-A-D |      |      |      |      |      |                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |  !   |  @   |  #   |  $   |  %   |                    |   ^  |  &   |  *   |  (   |  )   |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      |      |      |      |      |-------.    ,-------|   -  |  =   |  [   |  ]   |  \   |  `   |
 * |------+------+------+------+------+------|RGB_TOG|    |    ]  |------+------+------+------+------+------|
 * |      |      |      |      |      |      |-------|    |-------|   _  |  +   |  {   |  }   | "|"  |  ~   |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   | LCTRL| LAlt |LOWER | /Space  /       \Enter \  |RAISE | RAlt | RCTRL|
 *                   |      |      |      |/       /         \      \ |      |      |      |
 *                   `----------------------------'           '------''--------------------'
 */

[2] = LAYOUT(KC_CAD,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                   KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
             KC_TRNS, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC,                   KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_TRNS,
             KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                   KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC, KC_BSLS, KC_GRV,
             KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, RGB_TOG, KC_TRNS, KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR, KC_PIPE, KC_TILD,
                                        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
             ),

/* QWERTY (MAC)
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * | ESC  |   1  |   2  |   3  |   4  |   5  |                    |   6  |   7  |   8  |   9  |   0  |  =   |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |Tb/MO6|   Q  |   W  |   E  |   R  |   T  |                    |   Y  |   U  |   I  |   O  |   P  |  -   |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |LCTRL |   A  |   S  |   D  |   F  |   G  |-------.    ,-------|   H  |   J  |   K  |   L  |   ;  |  '   |
 * |------+------+------+------+------+------|   [   |    |    ]  |------+------+------+------+------+------|
 * |LShift|   Z  |   X  |   C  |   V  |   B  |-------|    |-------|   N  |   M  |   ,  |   .  |   /  |RShift|
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   | LGUI | LAlt |LOWER | /Space  /       \Enter \  |RAISE |BackSP| RGUI |
 *                   |      |      |      |/       /         \      \ |      |      |      |
 *                   `----------------------------'           '------''--------------------'
 */

[3] = LAYOUT(KC_ESC,       KC_1,  KC_2,  KC_3,    KC_4,    KC_5,                    KC_6,  KC_7,    KC_8,    KC_9,   KC_0,    KC_EQL,
             LT(6,KC_TAB), KC_Q,  KC_W,  KC_E,    KC_R,    KC_T,                    KC_Y,  KC_U,    KC_I,    KC_O,   KC_P,    KC_MINS,
             KC_LCTL,      KC_A,  KC_S,  KC_D,    KC_F,    KC_G,                    KC_H,  KC_J,    KC_K,    KC_L,   KC_SCLN, KC_QUOT,
             KC_LSFT,      KC_Z,  KC_X,  KC_C,    KC_V,    KC_B,  KC_LBRC, KC_RBRC, KC_N,  KC_M,    KC_COMM, KC_DOT, KC_SLSH, KC_RSFT,
                                         KC_LGUI, KC_LALT, MO(4), KC_SPC,  KC_ENT,  MO(5), KC_BSPC, KC_RGUI
             ),

/* LOWER (MAC)
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |  `   |  F1  |  F2  |  F3  |  F4  |  F5  |                    |  F6  |  F6  |  F6  |  F9  | F10  | F11  |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      |  UP  |      |      |      |                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      | LEFT | DOWN | RIGHT|      |      |-------.    ,-------|      |      |      |      |      |      |
 * |------+------+------+------+------+------|RGB_TOG|    |  PLAY |------+------+------+------+------+------|
 * |      |      |      |      |      | LEAD |-------|    |-------|      |      |      |      |  \|  |      |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   | LGUI | LAlt |LOWER | / MUTE  /       \Enter \  |RAISE |  DEL | RGUI |
 *                   |      |      |      |/       /         \      \ |      |      |      |
 *                   `----------------------------'           '------''--------------------'
 */

[4] = LAYOUT(KC_GRV,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                     KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,
             KC_TRNS, KC_TRNS, KC_UP,   KC_TRNS, KC_TRNS, KC_TRNS,                   KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
             KC_TRNS, KC_LEFT, KC_DOWN, KC_RGHT, KC_TRNS, KC_TRNS,                   KC_TRNS, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, KC_TRNS,
             KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, QK_LEAD, RGB_TOG, KC_MPLY, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_BSLS, KC_TRNS,
                                        KC_TRNS, KC_TRNS, KC_TRNS, KC_MUTE, KC_TRNS, KC_TRNS, KC_DEL,  KC_TRNS
             ),

/* RAISE (MAC)
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |      |      |      |      |      |      |                    |      |      |      |      |      | F12  |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      | PGUP |      |      |      |                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      | HOME | PGDN |  END |      |      |-------.    ,-------| LEFT | DOWN |  UP  | RIGHT|      |      |
 * |------+------+------+------+------+------|RGB_TOG|    |    ]  |------+------+------+------+------+------|
 * |      |      |      |      |      |      |-------|    |-------|      |      |      |      |      |      |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   | LGUI | LAlt |LOWER | /Space  /       \Enter \  |RAISE |BackSP| RGUI |
 *                   |      |      |      |/       /         \      \ |      |      |      |
 *                   `----------------------------'           '------''--------------------'
 */

[5] = LAYOUT(KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                   KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_F12,
             KC_TRNS, KC_TRNS, KC_PGUP, KC_TRNS, KC_TRNS, KC_TRNS,                   KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
             KC_TRNS, KC_HOME, KC_PGDN, KC_END,  KC_TRNS, KC_TRNS,                   KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, KC_TRNS, KC_TRNS,
             KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, RGB_TOG, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                                        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
             ),


/* ADJUST
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * | BOOT | SWAP | NORM |      |      |      |                    | MOD  | MODR |      |      |  H+  |  H-  |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      |DF(3) |      |      |GUITOG|                    |      |      |      |      |  S+  |  S-  |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      |      |      |      |      |-------.    ,-------|      |      |      |      |  V+  |  V-  |
 * |------+------+------+------+------+------|RGB_TOG|    |       |------+------+------+------+------+------|
 * |      |      |      |      |      |      |-------|    |-------|      |      |DF(0) |      |  SP+ |  SP- |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   |GUICTL| LAlt |LOWER | /Space  /       \Enter \  |RAISE |BackSP|GUICTL|
 *                   |      |      |      |/       /         \      \ |      |      |      |
 *                   `----------------------------'           '------''--------------------'
 */

[6] = LAYOUT(QK_BOOT, CG_SWAP, CG_NORM, KC_NO,   KC_NO,   KC_NO,                     RGB_MOD, RGB_RMOD, KC_NO, KC_NO, RGB_HUI, RGB_HUD,
             KC_NO,   KC_NO,   DF(0),   KC_NO,   KC_NO,   CG_TOGG,                   KC_NO,   KC_NO,    KC_NO, KC_NO, RGB_SAI, RGB_SAD,
             KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,                     KC_NO,   KC_NO,    KC_NO, KC_NO, RGB_VAI, RGB_VAD,
             KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   RGB_TOG, KC_NO,   KC_NO,   DF(3),    KC_NO, KC_NO, RGB_SPI, RGB_SPD,
                                        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS
             )
};

#ifdef ENCODER_MAP_ENABLE
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][2] = {
    // Left encoder: Volume; Right encoder: Media next/previous
    [_QWERTY] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU),  ENCODER_CCW_CW(KC_MPRV, KC_MNXT) },
    // Left encoder: Screen brightness; Right encoder: RGB brightness
    [_LOWER]  = { ENCODER_CCW_CW(KC_BRID, KC_BRIU), ENCODER_CCW_CW(RGB_VAD, RGB_VAI) },
    [_RAISE]  = { ENCODER_CCW_CW(RGB_RMOD, RGB_MOD),  ENCODER_CCW_CW(RGB_SPD, RGB_SPI) },
    // Left encoder: Volume; Right encoder: Media next/previous
    [_QWERTY_WIN] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU),  ENCODER_CCW_CW(KC_MPRV, KC_MNXT) },
    // Left encoder: Screen brightness; Right encoder: RGB brightness
    [_LOWER_WIN]  = { ENCODER_CCW_CW(KC_BRID, KC_BRIU), ENCODER_CCW_CW(RGB_VAD, RGB_VAI) },
    [_RAISE_WIN]  = { ENCODER_CCW_CW(RGB_RMOD, RGB_MOD),  ENCODER_CCW_CW(RGB_SPD, RGB_SPI) },
    // Left encoder: RGB mode; Right encoder: RGB brightness
    [_ADJUST] = { ENCODER_CCW_CW(RGB_RMOD, RGB_MOD),  ENCODER_CCW_CW(RGB_VAI, RGB_VAD) }
};
#endif

// Modify the OLED display to account for the new layers

#ifdef OLED_ENABLE
oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    if (!is_keyboard_master()) {
        return OLED_ROTATION_180;
    }
    return rotation;
}

// Solved the default layer detection problem thanks to:
// https://www.reddit.com/r/olkb/comments/o5924u/comment/h2pq9rd/
void process_layer_state_user(void) {
    switch (get_highest_layer(layer_state|default_layer_state)) {
        case 0:
            render_layer_qw_win();
            break;
        case 1:
            render_layer_ra_win();
            break;
        case 2:
            render_layer_lo_win();
            break;
        case 3:
            render_layer_qw_mac();
            break;
        case 4:
            render_layer_ra_mac();
            break;
        case 5:
            render_layer_lo_mac();
            break;
        case 6:
            render_layer_ad();
            break;
    }
}

bool oled_task_user(void) {
    if (is_keyboard_master()) {
        process_layer_state_user();
    } else {
        render_logo_lulu();
    }
    return false;
}
#endif
