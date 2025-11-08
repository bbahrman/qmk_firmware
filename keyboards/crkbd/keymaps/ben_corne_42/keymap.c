#include QMK_KEYBOARD_H

/*
Commands / note
compile to JSON: qmk c2json -kb crkbd -km ben_corne_42 -o keymap.json
visualize JSON https://keymap-drawer.streamlit.app/
compile to hex (maybe the shorthand works but it was going to another format): qmk compile -kb crkbd -km ben_corne_42
*/

enum user_keycodes {
	INITIAL = SAFE_RANGE, // start in safe range and then switch to custom range
	CMD_OPT_LEFT, // WebStorm navigate back
	CMD_OPT_RIGHT, // Webstorm navigate forward
	RBG_COLOR_TOGGLE,
	OPTION_SHIFT_V, // paste app
	MACRO_ARROW_FUNC,
	MACRO_PAREN_AND_BLOCK,
	NETSUITE,
	PDF,
	WARPD,
    CMD_LEFT,
    CMD_RIGHT,
    CMD_F,
    CHECKBOX
};

enum combos {
	CAPS_LOCK
};

const uint16_t PROGMEM caps_lock[] = { KC_G,   	KC_H, COMBO_END };
combo_t key_combos[] = {
	COMBO(caps_lock, KC_CAPS)
};


static uint16_t rgb_timer;
static uint8_t current_color = 0;

const HSV hsv_colors[] = {
	{HSV_RED},
	{HSV_GREEN},
	{HSV_BLUE},
	{HSV_PURPLE},
	{HSV_YELLOW},
	{HSV_CYAN},
};
#define NUM_COLORS (sizeof(hsv_colors) / sizeof(hsv_colors[0]))


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
     [0] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
     KC_ESC,             KC_Q,              KC_W,               KC_F,                   KC_P,               KC_B,                                         KC_J,                   KC_L,                 KC_U,               KC_Y,                KC_SCLN,            KC_BSPC,
  //|--------+---------------------+---------------------+---------------------+---------------------+---------------------|                    |---------------------+---------------------+---------------------+---------------------+---------------------+---------------------|
      KC_GRV,   MT(MOD_LCTL, KC_A),    MT(MOD_LALT, KC_R),   MT(MOD_LGUI, KC_S),   MT(MOD_LSFT, KC_T),           KC_G,                                     KC_M,         MT(MOD_RSFT, KC_N),    MT(MOD_RGUI, KC_E),    MT(MOD_LALT, KC_I), MT(MOD_RCTL, KC_O),        KC_QUOT,
  //|--------+---------------------+---------------------+---------------------+---------------------+---------------------|                    |---------------------+---------------------+---------------------+---------------------+---------------------+---------------------|
     MO(5),     KC_Z,                       KC_X,                    KC_C,           KC_D,                    KC_V,                                       KC_K,                KC_H,                  KC_COMM,              KC_DOT,              KC_SLSH,           TO(3),
  //|--------+---------------------+---------------------+---------------------+---------------------+---------------------|                    |---------------------+---------------------+---------------------+---------------------+---------------------+---------------------|
                                                                  OSL(1),             TG(4),             KC_TAB,                                       KC_ENT,               KC_SPC,                 OSL(2)
                                                      //`---------------------+---------------------+---------------------'                      `---------------------+---------------------+---------------------|
),

    [1] = LAYOUT_split_3x6_3( // ONE SHOT numbers, left side symbols, 
  //|--------+---------------------+---------------------+---------------------+---------------------+---------------------|                    |---------------------+---------------------+---------------------+---------------------+---------------------+---------------------|
     TO(0),     KC_1,                   KC_2,               KC_3,                   KC_4,                   KC_5,                                   KC_6,               KC_7,                   KC_8,                    KC_9,              KC_0,               _______,
  //|--------+---------------------+---------------------+---------------------+---------------------+---------------------|                    |---------------------+---------------------+---------------------+---------------------+---------------------+---------------------|
      _______,   _______,            _______,               _______,               _______,             MACRO_PAREN_AND_BLOCK,                       MACRO_ARROW_FUNC,            KC_LCBR,                KC_LBRC,                KC_LPRN,            _______,            _______, 
  //|--------+---------------------+---------------------+---------------------+---------------------+---------------------|                    |---------------------+---------------------+---------------------+---------------------+---------------------+---------------------|
     _______,  _______,               _______,              _______,             _______,                  _______,                               _______,                      _______,        _______,            _______,                _______,            _______, 
  //|--------+---------------------+---------------------+---------------------+---------------------+---------------------|                    |---------------------+---------------------+---------------------+---------------------+---------------------+---------------------|
                                                                   TO(1),         _______,              _______,                                                             _______,                    KC_SPC,            _______             
                                                      //`---------------------+---------------------+---------------------'                                      `---------------------+---------------------+---------------------|'
  ),
[2] = LAYOUT_split_3x6_3( // ONE SHOT symbols from numbers, right side symbols
  //|--------+---------------------+---------------------+---------------------+---------------------+---------------------|                    |---------------------+---------------------+---------------------+---------------------+---------------------+---------------------|
     TO(0),     KC_EXLM,               KC_AT,                KC_HASH,             KC_DLR,                KC_PERC,                                    KC_CIRC,           KC_AMPR,                KC_ASTR,                S(KC_BACKSLASH),            _______,                _______,
  //|--------+---------------------+---------------------+---------------------+---------------------+---------------------|                    |---------------------+---------------------+---------------------+---------------------+---------------------+---------------------|
      _______,    KC_TILD,           KC_BACKSLASH,            KC_MINS,             KC_EQL,                 KC_PLUS,                                    CHECKBOX,            KC_RCBR,                KC_RBRC,                KC_RPRN,            _______,            _______, 
  //|--------+---------------------+---------------------+---------------------+---------------------+---------------------|                    |---------------------+---------------------+---------------------+---------------------+---------------------+---------------------|
     _______,  _______,               _______,              _______,             _______,                  _______,                               _______,                      _______,        _______,            _______,                _______,            _______, 
  //|--------+---------------------+---------------------+---------------------+---------------------+---------------------|                    |---------------------+---------------------+---------------------+---------------------+---------------------+---------------------|
                                _______,            _______,               _______,                                                             _______,    KC_UNDS,                    TO(2)                         
                        //`---------------------+---------------------+---------------------'                                      `---------------------+---------------------+---------------------|'
  ),

  [3] = LAYOUT_split_3x6_3( // ten key
  //,-----------------------------------------------------.                                                                                     ,-----------------------------------------------------.
     TO(0),      _______,            _______,               _______,                _______,                 _______,                                     KC_7,            KC_8,                   KC_9,                  KC_ASTR,              KC_SLSH,              KC_BSPC,
  //|--------+---------------------+---------------------+---------------------+---------------------+---------------------|                    |---------------------+---------------------+---------------------+---------------------+---------------------+---------------------|
      _______,    _______,           _______,               _______,            _______,                     _______,                                   KC_4,  	        KC_5,                KC_6,                 KC_MINS,               KC_LPRN,                KC_RPRN,
  //|--------+---------------------+---------------------+---------------------+---------------------+---------------------|                    |---------------------+---------------------+---------------------+---------------------+---------------------+---------------------|
      _______, _______,              _______,               _______,                 _______,                 _______,                                      KC_1,       KC_2,                 KC_3,                KC_PLUS,                KC_LEFT,             KC_RIGHT,
  //|--------+---------------------+---------------------+---------------------+---------------------+---------------------|                    |---------------------+---------------------+---------------------+---------------------+---------------------+---------------------|
                                                            _______,              _______,                _______,                                     KC_ENT,               KC_0,                KC_DOT
                                                        //`---------------------+---------------------+---------------------'                      `---------------------+---------------------+---------------------|'

  ),

  [4] = LAYOUT_split_3x6_3( // paste app
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
     TO(0),    _______,            _______,               _______,                _______,                 _______,                                     _______,          _______,                 KC_UP,                  _______,                _______,                 _______,
  //|--------+---------------------+---------------------+---------------------+---------------------+---------------------|                    |---------------------+---------------------+---------------------+---------------------+---------------------+---------------------|
      _______,    KC_LCTL,           KC_LALT,               KC_LGUI,              KC_LSFT,                   _______,                                   _______,  	          KC_LEFT,           KC_DOWN,              KC_RIGHT,               _______,                 _______,
  //|--------+---------------------+---------------------+---------------------+---------------------+---------------------|                    |---------------------+---------------------+---------------------+---------------------+---------------------+---------------------|
      CMD_F,   _______,              _______,               _______,                 _______,                 _______,                                     _______,         CMD_LEFT,                 _______,              CMD_RIGHT,               _______,              _______,
  //|--------+---------------------+---------------------+---------------------+---------------------+---------------------|                    |---------------------+---------------------+---------------------+---------------------+---------------------+---------------------|
                                                            OPTION_SHIFT_V,         TG(4),                 KC_TAB,                                              KC_ENT,           KC_SPC,           _______
                                                        //`---------------------+---------------------+---------------------'                      `---------------------+---------------------+---------------------|'

  ),

  [5] = LAYOUT_split_3x6_3( // system
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
     TO(0),    PDF(6),            _______,               _______,                KC_BRID,          	KC_BRIU,                                    KC_MUTE, 	    KC_VOLD,            	KC_VOLU,                  _______,                _______,                 QK_BOOT,
  //|--------+---------------------+---------------------+---------------------+---------------------+---------------------|                    |---------------------+---------------------+---------------------+---------------------+---------------------+---------------------|
      RBG_COLOR_TOGGLE,    _______,           _______,               _______,            _______,                     _______,                                   _______,  	        _______,            _______,            _______,               _______,                 _______,
  //|--------+---------------------+---------------------+---------------------+---------------------+---------------------|                    |---------------------+---------------------+---------------------+---------------------+---------------------+---------------------|
      _______, _______,              _______,               PDF(0),                 _______,                 _______,                                      _______,    _______,                 _______,              _______,               _______,              _______,
  //|--------+---------------------+---------------------+---------------------+---------------------+---------------------|                    |---------------------+---------------------+---------------------+---------------------+---------------------+---------------------|
                                                          _______,              _______,                RBG_COLOR_TOGGLE,                           _______,               _______,                _______
                                                        //`---------------------+---------------------+---------------------'                      `---------------------+---------------------+---------------------|'

  ),

      [6] = LAYOUT_split_3x6_3( //querty
  //,----------------------------------------------------------------------------------------------------------------------.                    ,-----------------------------------------------------.
     KC_ESC,    KC_Q,               KC_W,                   KC_E,                KC_R,                 KC_T,                                     KC_Y,                 KC_U,                 KC_I,                  KC_O,                KC_P,                 KC_BSPC,
  //|--------+---------------------+---------------------+---------------------+---------------------+---------------------|                    |---------------------+---------------------+---------------------+---------------------+---------------------+---------------------|
      MO(5),   MT(MOD_LCTL, KC_A),   MT(MOD_LALT, KC_S),  MT(MOD_LGUI, KC_D),  	MT(MOD_LSFT,KC_F),    KC_G,                                      KC_H,                 MT(MOD_RSFT,KC_J),    MT(MOD_RGUI,KC_K),   	MT(MOD_LALT,KC_L),   MT(MOD_RCTL,KC_SCLN), KC_QUOT,
  //|--------+---------------------+---------------------+---------------------+---------------------+---------------------|                    |---------------------+---------------------+---------------------+---------------------+---------------------+---------------------|
      MO(6),     KC_Z,                KC_X,                 KC_C,                 KC_V,                 KC_B,                                      KC_N,                 KC_M,                 KC_COMM,              KC_DOT,               KC_SLSH,              TO(2),
  //|--------+---------------------+---------------------+---------------------+---------------------+---------------------|                    |---------------------+---------------------+---------------------+---------------------+---------------------+---------------------|
                                                            TO(4),                           KC_SPC,     KC_TAB,                                 KC_ENT,               TG(1),                TG(3)
                                                        //`---------------------+---------------------+---------------------'                      `---------------------+---------------------+---------------------|'

  ),

};

/*
 [0] = LAYOUT_split_3x6_3( // template
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
     _______,    _______,            _______,               _______,                _______,                 _______,                                     _______,     _______,                 _______,                  _______,                _______,                 _______,
  //|--------+---------------------+---------------------+---------------------+---------------------+---------------------|                    |---------------------+---------------------+---------------------+---------------------+---------------------+---------------------|
      _______,    _______,           _______,               _______,            _______,                     _______,                                   _______,  	        _______,            _______,            _______,               _______,                 _______,
  //|--------+---------------------+---------------------+---------------------+---------------------+---------------------|                    |---------------------+---------------------+---------------------+---------------------+---------------------+---------------------|
      _______, _______,              _______,               _______,                 _______,                 _______,                                      _______,    _______,                 _______,              _______,               _______,              _______,
  //|--------+---------------------+---------------------+---------------------+---------------------+---------------------|                    |---------------------+---------------------+---------------------+---------------------+---------------------+---------------------|
                                                            _______,              _______,                _______,                                     _______,               _______,                _______
                                                        //`---------------------+---------------------+---------------------'                      `---------------------+---------------------+---------------------|'

  ),
*/
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
	switch (keycode) {
		case CMD_OPT_LEFT:
			if (record->event.pressed) {
				tap_code16(LGUI(LALT(KC_LEFT)));
			}
			return false; // end execution
		case CMD_OPT_RIGHT:
			if (record->event.pressed) {
				tap_code16(LGUI(LALT(KC_RIGHT)));
			}
			return false; // end execution
        case CMD_LEFT:
			if (record->event.pressed) {
				tap_code16(LGUI(KC_LEFT));
			}
			return false; // end execution
         case CMD_F:
			if (record->event.pressed) {
				tap_code16(LGUI(KC_F));
			}
			return false; // end execution    
		case CMD_RIGHT:
			if (record->event.pressed) {
				tap_code16(LGUI(KC_RIGHT));
			}
			return false; // end execution
		case OPTION_SHIFT_V:
			if (record->event.pressed) {
				tap_code16(A(S(KC_V)));
			}
			return false; // end execution
		case MACRO_ARROW_FUNC:
			if (record->event.pressed) {
				register_code(KC_LSFT);
				tap_code(KC_9);  // (
				tap_code(KC_0);  // )
				unregister_code(KC_LSFT);
				tap_code(KC_SPC); // space
				tap_code(KC_EQL); // =
				register_code(KC_LSFT);
				tap_code(KC_DOT); // >
				unregister_code(KC_LSFT);
				tap_code(KC_SPC);
				register_code(KC_LSFT);
				tap_code(KC_LBRC); // {
				tap_code(KC_RBRC); // }
				unregister_code(KC_LSFT);
			}
			return false; // end execution
		case WARPD:
			tap_code16(LGUI(LALT(KC_X)));	
			return false;
		case MACRO_PAREN_AND_BLOCK:
			if (record->event.pressed) {
				register_code(KC_LSFT);
				tap_code(KC_9);  // (
				tap_code(KC_0);  // )
				unregister_code(KC_LSFT);
				tap_code(KC_SPC);
				register_code(KC_LSFT);
				tap_code(KC_LBRC); // {
				tap_code(KC_RBRC); // }
				unregister_code(KC_LSFT);
			}
			return false; // end execution
		case NETSUITE:
			if (record->event.pressed) {
        register_code(KC_LSFT);
        tap_code(KC_N);
        unregister_code(KC_LSFT);
        tap_code(KC_E);
        tap_code(KC_T);
        register_code(KC_LSFT);
        tap_code(KC_S);
        unregister_code(KC_LSFT);
        tap_code(KC_U);
        tap_code(KC_I);
        tap_code(KC_T);
        tap_code(KC_E);
			}
			return false; // end execution	
		case PDF: // because home row mods are great until you write PDF 5 times in a paragraph
			if (record->event.pressed) {
        register_code(KC_LSFT);
        tap_code(KC_P);
        tap_code(KC_D);
        tap_code(KC_F);
        unregister_code(KC_LSFT);
			}
			return false; // end execution
        case CHECKBOX: // - [ ]
			if (record->event.pressed) {
        tap_code(KC_MINS);     // -
    tap_code(KC_SPC);      // space
    tap_code(KC_LBRC);     // [
    tap_code(KC_SPC);      // space
    tap_code(KC_RBRC);     // ]
    tap_code(KC_SPC);      // trailing space (nice for typing the task right away)
			}
			return false; // end execution
		case RBG_COLOR_TOGGLE: // TODO see if this long press logic can be handled more natively, AI wrote this but I feel like there's a native function
			if (record->event.pressed) {
					rgb_timer = timer_read();
			} else {
					if (timer_elapsed(rgb_timer) < 500) {
							// Short press: cycle color
							current_color = (current_color + 1) % NUM_COLORS;
							rgb_matrix_mode(1);
							rgb_matrix_sethsv_noeeprom(
								hsv_colors[current_color].h,
    						hsv_colors[current_color].s,
    						hsv_colors[current_color].v
							);
					} else {
							// Long press: toggle RGB on/off
							rgb_matrix_toggle();
					}
			}
			return false;
	}
	return true; // default to allow other keycodes to process
}

#ifdef ENCODER_MAP_ENABLE
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
  [0] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(KC_MPRV, KC_MNXT), ENCODER_CCW_CW(RM_VALD, RM_VALU), ENCODER_CCW_CW(KC_RGHT, KC_LEFT), },
  [1] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(KC_MPRV, KC_MNXT), ENCODER_CCW_CW(RM_VALD, RM_VALU), ENCODER_CCW_CW(KC_RGHT, KC_LEFT), },
  [2] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(KC_MPRV, KC_MNXT), ENCODER_CCW_CW(RM_VALD, RM_VALU), ENCODER_CCW_CW(KC_RGHT, KC_LEFT), },
  [3] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(KC_MPRV, KC_MNXT), ENCODER_CCW_CW(RM_VALD, RM_VALU), ENCODER_CCW_CW(KC_RGHT, KC_LEFT), },
};
#endif
#if defined(OLED_ENABLE) || defined(OLED_DRIVER_ENABLE)
#    include "oled_driver.h"
#    include "quantum.h"
#    include <stdio.h>

// Rotate for vertical mount (swap 90/270 if your halves are flipped)
oled_rotation_t oled_init_user(oled_rotation_t rotation) {
#ifdef SPLIT_KEYBOARD
    return OLED_ROTATION_270;
#endif
}

// How many text rows your display has
#if defined(OLED_DISPLAY_128X64)
#    define OLED_ROWS 8
#else
#    define OLED_ROWS 4
#endif

// Label known layers (edit names to match your layout)
static const char *label_for_layer(uint8_t l) {
    switch (l) {
        case 0: return "COLE";
        case 1: return "NUM";
        case 2: return "SYM";
        case 3: return "TEN";
        case 4: return "NAV/P";
        case 5: return "SYS";
        case 8: return "QUER";
        default: return NULL; // we'll fall back to "L<n>"
    }
}

// Collect active layers into out[], from highest -> lowest.
// Returns count (capped at out_len).
static uint8_t collect_active_layers(uint8_t *out, uint8_t out_len) {
    layer_state_t s = layer_state | default_layer_state;  // include base layers
    uint8_t count = 0;
    // Scan from top (31) down so we get precedence order
    for (int8_t l = 31; l >= 0 && count < out_len; l--) {
        if (s & ((layer_state_t)1u << l)) {
            out[count++] = (uint8_t)l;
        }
    }
    return count;
}

bool oled_task_user(void) {
    oled_clear();

    uint8_t active[OLED_ROWS];
    uint8_t n = collect_active_layers(active, OLED_ROWS);

    for (uint8_t row = 0; row < OLED_ROWS; row++) {
        oled_set_cursor(0, row);
        if (row < n) {
            const char *name = label_for_layer(active[row]);
            if (name) {
                oled_write_ln(name, false);
            } else {
                char buf[6];
                snprintf(buf, sizeof buf, "L%u", active[row]);
                oled_write_ln(buf, false);
            }
        } else {
            oled_write_ln_P(PSTR("     "), false);  // blank line for unused rows
        }
    }
    return false;
}
#endif