// this is the style you want to emulate.
// This is the canonical layout file for the Quantum project. If you want to add another keyboard,

#include QMK_KEYBOARD_H
#include "print.h"
#include "quantum/quantum.h"

#ifdef RGBLIGHT_LAYERS
#include "rgblight.h"
#endif

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define _QW 0
#define _RS 1
#define _LW 2
#define _GAMING 3


#ifdef RGBLIGHT_LAYERS
const rgblight_segment_t PROGMEM _raise[] = RGBLIGHT_LAYER_SEGMENTS(
	{12, 8, HSV_CYAN}
);

const rgblight_segment_t PROGMEM _lower[] = RGBLIGHT_LAYER_SEGMENTS(
	{12, 8, HSV_PURPLE}
);

const rgblight_segment_t PROGMEM _gaming[] = RGBLIGHT_LAYER_SEGMENTS(
       {12, 8, HSV_BLUE}
);

const rgblight_segment_t* const PROGMEM _rgb_layers[] = RGBLIGHT_LAYERS_LIST(
	_raise,
	_lower,
        _gaming
);
#endif

void keyboard_post_init_user(void) {
	setPinOutput(F7);
#ifdef RGBLIGHT_LAYERS
	rgblight_layers = _rgb_layers;
#endif
}

#ifdef RGBLIGHT_LAYERS
layer_state_t layer_state_set_user(layer_state_t state) {
    // Both layers will light up if both kb layers are active
#if 1
    for(int i = 0; i < sizeof(_rgb_layers)/sizeof(_rgb_layers[0]); i++)
    {

    rgblight_set_layer_state(i, 0);
    }

    if (get_highest_layer(state) > 0)
    {
        rgblight_set_layer_state(get_highest_layer(state) - 1, 1);
    }
#endif
    return state;

}

bool led_update_user(led_t led_state) {
    return true;
}
#endif

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_QW] = LAYOUT( /* Qwerty */
    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                      KC_Y,    KC_U,    KC_I,    KC_O,    KC_P    ,
    KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                      KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN ,
    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                      KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH ,
    SFT_T(KC_ESC), KC_TAB, KC_LGUI,  KC_LSFT, KC_BSPC,  KC_LCTL, KC_LALT, KC_SPC,  MO(_RS), KC_MINS, KC_QUOT, KC_ENT
  ),

  /*
   *  !       @     up     {    }        ||     pgup    7     8     9    *
   *  #     left   down  right  $        ||     pgdn    4     5     6    +
   *  [       ]      (     )    &        ||       `     1     2     3    \
   * lower  insert super shift bksp ctrl || alt space   fn    .     0    =
   */
  [_RS] = LAYOUT( /* [> RAISE <] */
    KC_EXLM, KC_AT,   KC_UP,   KC_LCBR, KC_RCBR,                   KC_PGUP, KC_7,    KC_8,   KC_9, KC_ASTR ,
    KC_HASH, KC_LEFT, KC_DOWN, KC_RGHT, KC_DLR,                    KC_PGDN, KC_4,    KC_5,   KC_6, KC_PLUS ,
    KC_LBRC, KC_RBRC, KC_LPRN, KC_RPRN, KC_AMPR,                   KC_GRV,  KC_1,    KC_2,   KC_3, KC_BSLS ,
    TG(_LW), KC_INS,  KC_LGUI, KC_LSFT, KC_BSPC, KC_LCTL, KC_LALT, KC_SPC,  KC_TRNS, KC_DOT, KC_0, KC_EQL  ),
  /*
   * insert home   up  end   pgup       ||      up     F7    F8    F9   F10
   *  del   left  down right pgdn       ||     down    F4    F5    F6   F11
   *       volup             reset      ||             F1    F2    F3   F12
   *       voldn  super shift bksp ctrl || alt space   L0  prtsc scroll pause
   */
  [_LW] = LAYOUT( /* [> LOWER <] */
    KC_INS,  KC_HOME, KC_UP,   KC_END,  KC_PGUP,                   KC_UP,   KC_F7,   KC_F8,   KC_F9,   KC_F10  ,
    KC_DEL,  KC_LEFT, KC_DOWN, KC_RGHT, KC_PGDN,                   KC_DOWN, KC_F4,   KC_F5,   KC_F6,   KC_F11  ,
    RGB_MOD,   KC_VOLU, KC_NO,   KC_NO,   RESET,                     KC_NO,   KC_F1,   KC_F2,   KC_F3,   KC_F12  ,
    TG(_GAMING),   KC_VOLD, KC_LGUI, KC_LSFT, KC_BSPC, KC_LCTL, KC_LALT, KC_SPC,  TO(_QW), KC_PSCR, KC_SLCK, KC_PAUS ),

  [_GAMING] = LAYOUT( /* Gaming layout */
    KC_1,    KC_2,    KC_3,   KC_4,      KC_5,                        KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO   ,
    KC_6,    KC_Q,    KC_W,   KC_E,      KC_R,                       KC_I,    KC_NO,    KC_NO,    KC_NO,    KC_NO   ,
    KC_7,    KC_A,    KC_S,   KC_D,      KC_F,                       KC_N,    KC_M,    KC_NO,    KC_NO,    KC_NO   ,         
    KC_8,    KC_TAB,   KC_ESC,  KC_LSHIFT, KC_SPACE, KC_LCTL, KC_LALT, KC_NO,    TO(_QW),  KC_NO,    KC_NO,    KC_NO)   
};
