#include QMK_KEYBOARD_H

// Tap Dance setup
// See https://docs.qmk.fm/#/feature_tap_dance

typedef enum {
    TD_NONE,
    TD_UNKNOWN,
    TD_SINGLE_TAP,
    TD_SINGLE_HOLD,
    TD_DOUBLE_TAP,
    TD_DOUBLE_HOLD,
    TD_DOUBLE_SINGLE_TAP, // Send two single taps
    TD_TRIPLE_TAP,
    TD_TRIPLE_HOLD
} td_state_t;

typedef struct {
    bool is_press_action;
    td_state_t state;
} td_tap_t;

// Tap dance enums
enum {
    X_DASH
};

td_state_t cur_dance(tap_dance_state_t *state);

// For the x tap dance. Put it here so it can be used in any keymap
void x_finished(tap_dance_state_t *state, void *user_data);
void x_reset(tap_dance_state_t *state, void *user_data);

// Layers

enum layers {
    _QWERTY,
    _LOWER,
    _RAISE,
    _ADJUST
};

// ADJUST layer accessed by pressing RAISE and LOWER
layer_state_t layer_state_set_user(layer_state_t state) {
  return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

        // --------------------------------------------------------------------------------
        // |  TAB |  Q  |  W  |  E  |  R  |  T  |   |  Y  |  U   |  I  |  O  |  P  | BKSP |
        // | CTRL |  A  |  S  |  D  |  F  |  G  |   |  H  |  J   |  K  |  L  |  ;  |  '   |
        // | SHFT |  Z  |  X  |  C  |  V  |  B  |   |  N  |  M   |  ,  |  .  |  /  | ESC  |
        //                    | GUI | LWR | SPC |   | ENT | RSE  | ALT |
  
        [0] = LAYOUT_split_3x6_3(
     	  KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,  KC_T,       KC_Y,       KC_U,   KC_I,     KC_O,    KC_P,    KC_BSPC,
	      KC_LCTL, KC_A,    KC_S,    KC_D,    KC_F,  KC_G,       KC_H,       KC_J,   KC_K,     KC_L,    KC_SCLN, KC_QUOT,
	      KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,  KC_B,       KC_N,       KC_M,   KC_COMM,  KC_DOT,  KC_SLSH, KC_ESC,
	                                 KC_LGUI, MO(1), KC_SPC,     KC_ENT,     MO(2),   KC_RALT
				 ),

	// -----------------------------------------------------------------------------------
        // |  TAB |  1  |  2  |  3  |  4  |  5  |   |  6   |  7   |  8   |  9   |  0  | DEL  |
        // | CTRL | F1  | F2  | F3  | F3  | F5  |   | LEFT | DOWN |  UP  | RIGT | F11 |      |
        // | SHFT | F6  | F7  | F8  | F9  | F10 |   | HOME | PGDN | PGUP | END  | F12 | GRESC|
        //                    | GUI |     | SPC |   | ENT  |      | ALT  |
	
        [1] = LAYOUT_split_3x6_3(
	      KC_TRNS, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,      KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_DEL,
	      KC_TRNS, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,     KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, KC_F11,  KC_TRNS,
	      KC_TRNS, KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,    KC_HOME, KC_PGDN, KC_PGUP, KC_END , KC_F12,  KC_TRNS,
	                                 KC_TRNS, KC_TRNS, KC_TRNS,   KC_TRNS, KC_TRNS, KC_TRNS
				 ),

	// -------------------------------------------------------------------------------
        // |  TAB |  !  |  @  |  #  |  $  |  %  |   |  ^  |  &  |  *  |  (  |  )  | BKSP |
        // | CTRL |  EN |     |     |     |     |   |  -  |  =  |  [  |  ]  |  \  |  `   |
        // | SHFT |  EM |     |     |     |     |   |  _  |  +  |  {  |  }  | "|" |  ~   |
        //                    | GUI |     | SPC |   | ENT |     | ALT |

	
        [2] = LAYOUT_split_3x6_3(
	      KC_TRNS, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC,   KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_TRNS,
	      KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,   TD(X_DASH), KC_EQL,  KC_LBRC, KC_RBRC, KC_BSLS, KC_GRV,
	      KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,   KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR, KC_PIPE, KC_TILD,
	                                 KC_TRNS, KC_TRNS, KC_TRNS,   KC_TRNS, KC_TRNS, KC_TRNS
				 ),

	// -------------------------------------------------------------------------------------
        // | BOOT |     |     |     |     |     |   | MUTE|     |     |     |PLAY |     |      |
        // | RBOOT|     |     | SPD+| BRI+|     |   | VLUP|BRIUP|     |     |     |     |      |
        // |      |     | RGB | SPD-| BRI-|     |   | VLDN|BRIDN|PREV |NEXT |     |     | BTCLR|
        //                    | GUI |     |C-TOG|   | ENT |     | ALT |
	
        [3] = LAYOUT_split_3x6_3(
	      QK_BOOT, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,   KC_MUTE, KC_TRNS, KC_TRNS, KC_TRNS, KC_MPLY, KC_TRNS,
	      QK_RBT,  KC_TRNS, KC_TRNS, RGB_SPI, RGB_VAI, KC_TRNS,   KC_VOLU, KC_BRIU, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
	      KC_TRNS, KC_TRNS, RGB_TOG, RGB_SPD, RGB_VAD, KC_TRNS,   KC_VOLD, KC_BRID, KC_MPRV, KC_MNXT, KC_TRNS, KC_TRNS,
	                                 KC_TRNS, KC_TRNS, CG_TOGG,   KC_TRNS, KC_TRNS, KC_TRNS
				 )
};

#if defined(ENCODER_ENABLE) && defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {

};
#endif // defined(ENCODER_ENABLE) && defined(ENCODER_MAP_ENABLE)

// The OLED is only on the left-hand side

#ifdef OLED_ENABLE
oled_rotation_t oled_init_user(oled_rotation_t rotation) {
//    if (is_keyboard_master()) {
        return OLED_ROTATION_0;
//    }
//    return rotation;
}

void render_layer_qw_win(void){
    static const char PROGMEM raw_logo[] = {
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 64,192, 64, 64, 64, 64, 64, 64, 64,128,  0,192, 64, 64, 64, 64, 64, 64, 64,128,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 56, 68,130,130,130, 68, 56,  0,  0,  0,  0,  0, 56, 68,130,130,130, 68, 56,  0,  0,  0,  0,  0, 56, 68,130,130,130, 68, 56,  0,  0,  0,  0,  0, 56,124,254,254,254,124, 56,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,128,192,177,142,128,128,128,128,128, 64, 49,206,177,142,128,128,128,128,128, 64, 49, 14,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 24, 24, 24, 24,248,248, 24, 24,224,224,  0,  0,248,248, 24, 24, 24, 24, 24, 24, 24, 24,  0,  0, 24, 24,152,152,248,248, 24, 24,248,248,  0,  0, 96, 96,152,152, 24, 24, 24, 24,224,224,  0,  0,  0,  0,  0,  0,  0,  0,
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,112,140,  2,  2,  2,  2,  2,  2,114,142,114,140,  2,  2,  2,  2,  2,  2,114,142,  2,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,230,230,102,102,103,103,102,102,225,225,  0,  0,135,135, 96, 96, 96, 96, 96, 96,128,128,  0,  0,102,102, 97, 97,225,225,102,102,129,129,  0,  0,102,102,225,225,102,102,102,102, 97, 97,  0,  0,  0,  0,  0,  0,  0,  0,
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,  6,  4,  4,  4,  4,  4,  4,  5,  6,  1,  6,  4,  4,  4,  4,  4,  4,  5,  6,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  7,  7, 24, 24, 24, 24, 24, 24,  7,  7,  0,  0,  7,  7, 24, 24, 24, 24, 24, 24,  7,  7,  0,  0, 24, 24, 24, 24, 31, 31, 24, 24,  7,  7,  0,  0, 96, 96,121,121,102,102, 96, 96, 96, 96,  0,  0,  0,  0,  0,  0,  0,  0,
    };
    oled_write_raw_P(raw_logo, sizeof(raw_logo));
}

void render_layer_ra_win(void){
    static const char PROGMEM raw_logo[] = {
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 64,192, 64, 64, 64, 64, 64, 64, 64,128,  0,192, 64, 64, 64, 64, 64, 64, 64,128,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 56, 68,130,130,130, 68, 56,  0,  0,  0,  0,  0, 56, 68,130,130,130, 68, 56,  0,  0,  0,  0,  0, 56,124,254,254,254,124, 56,  0,  0,  0,  0,  0, 56, 68,130,130,130, 68, 56,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,128,192,177,142,128,128,128,128,128, 64, 49,206,177,142,128,128,128,128,128, 64, 49, 14,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 24, 24, 24, 24,248,248, 24, 24,224,224,  0,  0,248,248, 24, 24, 24, 24, 24, 24, 24, 24,  0,  0, 24, 24,152,152,248,248, 24, 24,248,248,  0,  0, 96, 96,152,152, 24, 24, 24, 24,224,224,  0,  0,  0,  0,  0,  0,  0,  0,
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,112,140,  2,  2,  2,  2,  2,  2,114,142,114,140,  2,  2,  2,  2,  2,  2,114,142,  2,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,230,230,102,102,103,103,102,102,225,225,  0,  0,135,135, 96, 96, 96, 96, 96, 96,128,128,  0,  0,102,102, 97, 97,225,225,102,102,129,129,  0,  0,102,102,225,225,102,102,102,102, 97, 97,  0,  0,  0,  0,  0,  0,  0,  0,
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,  6,  4,  4,  4,  4,  4,  4,  5,  6,  1,  6,  4,  4,  4,  4,  4,  4,  5,  6,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  7,  7, 24, 24, 24, 24, 24, 24,  7,  7,  0,  0,  7,  7, 24, 24, 24, 24, 24, 24,  7,  7,  0,  0, 24, 24, 24, 24, 31, 31, 24, 24,  7,  7,  0,  0, 96, 96,121,121,102,102, 96, 96, 96, 96,  0,  0,  0,  0,  0,  0,  0,  0,
    };
    oled_write_raw_P(raw_logo, sizeof(raw_logo));
}

void render_layer_lo_win(void){
    static const char PROGMEM raw_logo[] = {
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 64,192, 64, 64, 64, 64, 64, 64, 64,128,  0,192, 64, 64, 64, 64, 64, 64, 64,128,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 56, 68,130,130,130, 68, 56,  0,  0,  0,  0,  0, 56,124,254,254,254,124, 56,  0,  0,  0,  0,  0, 56, 68,130,130,130, 68, 56,  0,  0,  0,  0,  0, 56, 68,130,130,130, 68, 56,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,128,192,177,142,128,128,128,128,128, 64, 49,206,177,142,128,128,128,128,128, 64, 49, 14,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 24, 24, 24, 24,248,248, 24, 24,224,224,  0,  0,248,248, 24, 24, 24, 24, 24, 24, 24, 24,  0,  0, 24, 24,152,152,248,248, 24, 24,248,248,  0,  0, 96, 96,152,152, 24, 24, 24, 24,224,224,  0,  0,  0,  0,  0,  0,  0,  0,
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,112,140,  2,  2,  2,  2,  2,  2,114,142,114,140,  2,  2,  2,  2,  2,  2,114,142,  2,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,230,230,102,102,103,103,102,102,225,225,  0,  0,135,135, 96, 96, 96, 96, 96, 96,128,128,  0,  0,102,102, 97, 97,225,225,102,102,129,129,  0,  0,102,102,225,225,102,102,102,102, 97, 97,  0,  0,  0,  0,  0,  0,  0,  0,
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,  6,  4,  4,  4,  4,  4,  4,  5,  6,  1,  6,  4,  4,  4,  4,  4,  4,  5,  6,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  7,  7, 24, 24, 24, 24, 24, 24,  7,  7,  0,  0,  7,  7, 24, 24, 24, 24, 24, 24,  7,  7,  0,  0, 24, 24, 24, 24, 31, 31, 24, 24,  7,  7,  0,  0, 96, 96,121,121,102,102, 96, 96, 96, 96,  0,  0,  0,  0,  0,  0,  0,  0,
    };
    oled_write_raw_P(raw_logo, sizeof(raw_logo));
}

void render_layer_ad(void){
    static const char PROGMEM raw_logo[] = {
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 56,124,254,254,254,124, 56,  0,  0,  0,  0,  0, 56, 68,130,130,130, 68, 56,  0,  0,  0,  0,  0, 56, 68,130,130,130, 68, 56,  0,  0,  0,  0,  0, 56, 68,130,130,130, 68, 56,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 24, 24, 24, 24,248,248, 24, 24,224,224,  0,  0,248,248, 24, 24, 24, 24, 24, 24, 24, 24,  0,  0, 24, 24,152,152,248,248, 24, 24,248,248,  0,  0, 96, 96,152,152, 24, 24, 24, 24,224,224,  0,  0,  0,  0,  0,  0,  0,  0,
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,230,230,102,102,103,103,102,102,225,225,  0,  0,135,135, 96, 96, 96, 96, 96, 96,128,128,  0,  0,102,102, 97, 97,225,225,102,102,129,129,  0,  0,102,102,225,225,102,102,102,102, 97, 97,  0,  0,  0,  0,  0,  0,  0,  0,
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  7,  7, 24, 24, 24, 24, 24, 24,  7,  7,  0,  0,  7,  7, 24, 24, 24, 24, 24, 24,  7,  7,  0,  0, 24, 24, 24, 24, 31, 31, 24, 24,  7,  7,  0,  0, 96, 96,121,121,102,102, 96, 96, 96, 96,  0,  0,  0,  0,  0,  0,  0,  0,
    };
    oled_write_raw_P(raw_logo, sizeof(raw_logo));
}

bool oled_task_user(void) {
      switch (get_highest_layer(layer_state)) {
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
              render_layer_ad();
              break;
       }
  return false;
}

#endif

// Tap Dance
td_state_t cur_dance(tap_dance_state_t *state) {
    if (state->count == 1) {
        if (state->interrupted || !state->pressed) return TD_SINGLE_TAP;
        // Key has not been interrupted, but the key is still held. Means you want to send a 'HOLD'.
        else return TD_SINGLE_HOLD;
    } else if (state->count == 2) {
        // TD_DOUBLE_SINGLE_TAP is to distinguish between typing "pepper", and actually wanting a double tap
        // action when hitting 'pp'. Suggested use case for this return value is when you want to send two
        // keystrokes of the key, and not the 'double tap' action/macro.
        if (state->interrupted) return TD_DOUBLE_SINGLE_TAP;
        else if (state->pressed) return TD_DOUBLE_HOLD;
        else return TD_DOUBLE_TAP;
    }

    // Assumes no one is trying to type the same letter three times (at least not quickly).
    // If your tap dance key is 'KC_W', and you want to type "www." quickly - then you will need to add
    // an exception here to return a 'TD_TRIPLE_SINGLE_TAP', and define that enum just like 'TD_DOUBLE_SINGLE_TAP'
    if (state->count == 3) {
        if (state->interrupted || !state->pressed) return TD_TRIPLE_TAP;
        else return TD_TRIPLE_HOLD;
    } else return TD_UNKNOWN;
}

// Create an instance of 'td_tap_t' for the 'x' tap dance.
static td_tap_t xtap_state = {
    .is_press_action = true,
    .state = TD_NONE
};

void x_finished(tap_dance_state_t *state, void *user_data) {
    xtap_state.state = cur_dance(state);
    switch (xtap_state.state) {
        case TD_SINGLE_TAP: register_code(KC_MINS); break;
	// en-dash
        case TD_SINGLE_HOLD: SEND_STRING(SS_LALT(SS_TAP(X_KP_0) SS_TAP(X_KP_1) SS_TAP(X_KP_5) SS_TAP(X_KP_0))); break;
        case TD_DOUBLE_TAP: SEND_STRING(SS_LALT(SS_TAP(X_KP_0) SS_TAP(X_KP_1) SS_TAP(X_KP_5) SS_TAP(X_KP_0))); break;
        // Last case is for fast typing. Assuming your key is `f`:
        // For example, when typing the word `buffer`, and you want to make sure that you send `ff` and not `Esc`.
        // In order to type `ff` when typing fast, the next character will have to be hit within the `TAPPING_TERM`, which by default is 200ms.
        case TD_DOUBLE_SINGLE_TAP: tap_code(KC_MINS); register_code(KC_MINS); break;
	// em-dash 
        case TD_TRIPLE_TAP: SEND_STRING(SS_LALT(SS_TAP(X_KP_0) SS_TAP(X_KP_1) SS_TAP(X_KP_5) SS_TAP(X_KP_1))); break;
        default: break;
    }
}

void x_reset(tap_dance_state_t *state, void *user_data) {
    switch (xtap_state.state) {
        case TD_SINGLE_TAP: unregister_code(KC_MINS); break;
        case TD_SINGLE_HOLD: break;
        case TD_DOUBLE_TAP: break;
        case TD_DOUBLE_SINGLE_TAP: unregister_code(KC_MINS); break;
        case TD_TRIPLE_TAP: break;
        default: break;
    }
    xtap_state.state = TD_NONE;
}

tap_dance_action_t tap_dance_actions[] = {
    [X_DASH] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, x_finished, x_reset)
};

