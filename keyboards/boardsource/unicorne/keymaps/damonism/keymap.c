#include QMK_KEYBOARD_H

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
     	      KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,  KC_T,       KC_Y,    KC_U,   KC_I,     KC_O,    KC_P,    KC_BSPC,
	      KC_LCTL, KC_A,    KC_S,    KC_D,    KC_F,  KC_G,       KC_H,    KC_J,   KC_K,     KC_L,    KC_SCLN, KC_QUOT,
	      KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,  KC_B,       KC_N,    KC_M,   KC_COMM,  KC_DOT,  KC_SLSH, KC_ESC,
	                                 KC_LGUI, MO(1), KC_SPC,     KC_ENT,  MO(2),   KC_RALT
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
	      KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,   KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC, KC_BSLS, KC_GRV,
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