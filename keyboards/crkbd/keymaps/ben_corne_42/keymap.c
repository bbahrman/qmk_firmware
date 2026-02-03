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
	PASTE, // paste app
	MACRO_ARROW_FUNC,
	MACRO_PAREN_AND_BLOCK,
	NETSUITE,
	PDF,
	WARPD,
    CMD_LEFT,
    CMD_RIGHT,
    CMD_F,
    CHECKBOX,
    TAX,
    RESCHEDULED,
    SCHEDULED,
    PIN,
    OBSIDIAN_UP,
    OBSIDIAN_DOWN,
    STAR,
    CROSS_OUT
};

enum combos {
	CAPS_LOCK
};

const uint16_t PROGMEM caps_lock[] = { KC_G,   	KC_M, COMBO_END };
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
      _______,       KC_Q,              KC_W,               KC_F,                   KC_P,               KC_B,                                         KC_J,                   KC_L,                 KC_U,               KC_Y,                KC_SCLN,            KC_BSPC,
  //|--------+---------------------+---------------------+---------------------+---------------------+---------------------|                    |---------------------+---------------------+---------------------+---------------------+---------------------+---------------------|
      KC_GRV,   MT(MOD_LCTL, KC_A),    MT(MOD_LALT, KC_R),   MT(MOD_LGUI, KC_S),   MT(MOD_LSFT, KC_T),           KC_G,                                     KC_M,         MT(MOD_RSFT, KC_N),    MT(MOD_RGUI, KC_E),    MT(MOD_LALT, KC_I), MT(MOD_RCTL, KC_O),        KC_QUOT,
  //|--------+---------------------+---------------------+---------------------+---------------------+---------------------|                    |---------------------+---------------------+---------------------+---------------------+---------------------+---------------------|
     MO(5),     KC_Z,                       KC_X,                    KC_C,           KC_D,                    KC_V,                                       KC_K,                KC_H,                  KC_COMM,              KC_DOT,              KC_SLSH,           TO(3),
  //|--------+---------------------+---------------------+---------------------+---------------------+---------------------|                    |---------------------+---------------------+---------------------+---------------------+---------------------+---------------------|
                                                                  OSL(1),                 KC_TAB,         TG(4),                                KC_ENT,               KC_SPC,                 OSL(2)
                                                      //`---------------------+---------------------+---------------------'                      `---------------------+---------------------+---------------------|
),

    [1] = LAYOUT_split_3x6_3( // ONE SHOT numbers, left side symbols, 
  //|--------+---------------------+---------------------+---------------------+---------------------+---------------------|                    |---------------------+---------------------+---------------------+---------------------+---------------------+---------------------|
     TO(0),     KC_1,                   KC_2,               KC_3,                   KC_4,                   KC_5,                                   KC_6,               KC_7,                   KC_8,                    KC_9,              KC_0,               _______,
  //|--------+---------------------+---------------------+---------------------+---------------------+---------------------|                    |---------------------+---------------------+---------------------+---------------------+---------------------+---------------------|
      _______,   _______,            _______,               _______,               TAX,             MACRO_PAREN_AND_BLOCK,                       MACRO_ARROW_FUNC,            KC_LCBR,                KC_LBRC,                KC_LPRN,            _______,            _______, 
  //|--------+---------------------+---------------------+---------------------+---------------------+---------------------|                    |---------------------+---------------------+---------------------+---------------------+---------------------+---------------------|
     _______,  _______,               _______,              _______,             _______,                  _______,                               _______,                      _______,        _______,            _______,                _______,            _______, 
  //|--------+---------------------+---------------------+---------------------+---------------------+---------------------|                    |---------------------+---------------------+---------------------+---------------------+---------------------+---------------------|
                                                                   TG(1),         _______,              _______,                                                             _______,                    KC_SPC,            _______             
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
                                _______,            _______,               _______,                                                             _______,    KC_UNDS,                    TG(2)                         
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
      _______,    KC_LCTL,           KC_LALT,               KC_LGUI,              KC_LSFT,                   _______,                                   KC_HOME,  	          KC_LEFT,           KC_DOWN,              KC_RIGHT,               KC_END,                 _______,
  //|--------+---------------------+---------------------+---------------------+---------------------+---------------------|                    |---------------------+---------------------+---------------------+---------------------+---------------------+---------------------|
      CMD_F,   _______,              _______,               _______,                 _______,                 _______,                                     _______,         CMD_LEFT,                 _______,              CMD_RIGHT,               _______,              _______,
  //|--------+---------------------+---------------------+---------------------+---------------------+---------------------|                    |---------------------+---------------------+---------------------+---------------------+---------------------+---------------------|
                                                            PASTE,                KC_TAB,      TG(4),                                          KC_ENT,           KC_SPC,           TG(7)
                                                        //`---------------------+---------------------+---------------------'                      `---------------------+---------------------+---------------------|'

  ),

  [5] = LAYOUT_split_3x6_3( // system, NEVER LOCK THIS, putting escape here to allow it to be return to base for all other layers
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      KC_ESC,    PDF(6),            _______,               _______,                KC_BRID,          	KC_BRIU,                                    KC_MUTE, 	    KC_VOLD,            	KC_VOLU,                  _______,                _______,                 QK_BOOT,
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

  [7] = LAYOUT_split_3x6_3( // obsidian
    //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       TO(0),    _______,            _______,               _______,                _______,                 _______,                                     CROSS_OUT,          SCHEDULED,                 OBSIDIAN_UP,       RESCHEDULED,                STAR,                 _______,
    //|--------+---------------------+---------------------+---------------------+---------------------+---------------------|                    |---------------------+---------------------+---------------------+---------------------+---------------------+---------------------|
        _______,    _______,           _______,               _______,              _______,                   _______,                                   KC_HOME,  	          KC_LEFT,           OBSIDIAN_DOWN,          KC_RIGHT,           KC_END,                 _______,
    //|--------+---------------------+---------------------+---------------------+---------------------+---------------------|                    |---------------------+---------------------+---------------------+---------------------+---------------------+---------------------|
        _______,   _______,              _______,               _______,                 _______,                 _______,                                     _______,         _______,                 PIN,              _______,               _______,              _______,
    //|--------+---------------------+---------------------+---------------------+---------------------+---------------------|                    |---------------------+---------------------+---------------------+---------------------+---------------------+---------------------|
                                                              _______,                KC_TAB,                TG(7),                                          KC_ENT,           KC_SPC,           TG(7)
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
		case PASTE:
			if (record->event.pressed) {
				tap_code16(C(A(S(KC_V))));
			}
			return false; // end execution
        case SCHEDULED:
			if (record->event.pressed) {
                tap_code16(KC_LEFT);
                tap_code16(KC_LEFT);
				tap_code16(KC_BSPC);
                tap_code16(KC_LEFT_ANGLE_BRACKET);
			}
			return false; // end execution
        case PIN:
			if (record->event.pressed) {
                tap_code16(KC_LEFT);
                tap_code16(KC_LEFT);
				tap_code16(KC_BSPC);
                tap_code(KC_N);
			}
			return false; // end execution
        case RESCHEDULED:
			if (record->event.pressed) {
                tap_code16(KC_LEFT);
                tap_code16(KC_LEFT);
                tap_code16(KC_BSPC);
                tap_code16(KC_RIGHT_ANGLE_BRACKET);
			}
			return false; // end execution
        case CROSS_OUT:
			if (record->event.pressed) {
                tap_code16(KC_LEFT);
                tap_code16(KC_LEFT);
                tap_code16(KC_BSPC);
                tap_code16(KC_MINS);
			}
			return false; // end execution
                case STAR:
			if (record->event.pressed) {
                tap_code16(KC_LEFT);
                tap_code16(KC_LEFT);
                tap_code16(KC_BSPC);
                tap_code16(KC_ASTR);
			}
			return false; // end execution
            case OBSIDIAN_UP:
			if (record->event.pressed) {
                tap_code16(KC_UP);
                tap_code16(KC_HOME);
                tap_code16(KC_HOME);
                tap_code16(KC_HOME);
                tap_code16(KC_HOME);
                tap_code16(KC_RIGHT);
                tap_code16(KC_RIGHT);
                tap_code16(KC_RIGHT);
                tap_code16(KC_RIGHT);
                tap_code16(KC_RIGHT);
                tap_code16(KC_RIGHT);
			}
			return false; // end execution
            case OBSIDIAN_DOWN:
			if (record->event.pressed) {
                tap_code16(KC_DOWN);
                tap_code16(KC_HOME);
                tap_code16(KC_HOME);
                tap_code16(KC_HOME);
                tap_code16(KC_HOME);
                tap_code16(KC_RIGHT);
                tap_code16(KC_RIGHT);
                tap_code16(KC_RIGHT);
                tap_code16(KC_RIGHT);
                tap_code16(KC_RIGHT);
                tap_code16(KC_RIGHT);
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
        case TAX:
            if (record->event.pressed) {
                tap_code16(KC_ASTR); // * 
                tap_code(KC_1); // 1
                tap_code16(KC_DOT); // .
                tap_code(KC_0); // 0
                tap_code(KC_8); // 8
                tap_code(KC_2); // 2
                tap_code(KC_5); // 5

            }
            return false;
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

#ifdef RGB_MATRIX_ENABLE
// RGB matrix indicators for caps lock and layer 4
bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    led_t led_state = host_keyboard_led_state();
    layer_state_t layers = layer_state | default_layer_state;
    
    // Helper function to set LED color at a specific matrix position
    void set_led_at_pos(uint8_t row, uint8_t col, uint8_t r, uint8_t g, uint8_t b) {
        if (row < MATRIX_ROWS && col < MATRIX_COLS) {
            uint8_t led_index = g_led_config.matrix_co[row][col];
            if (led_index != NO_LED && led_index >= led_min && led_index <= led_max) {
                rgb_matrix_set_color(led_index, r, g, b);
            }
        }
    }
    
    // When caps lock is active: Set G (R1C5) and M (R5C5) to red
    // RGB_RED is defined as 0xFF, 0x00, 0x00 (macro, not struct)
    if (led_state.caps_lock) {
        set_led_at_pos(1, 5, RGB_RED); // G key
        set_led_at_pos(5, 5, RGB_RED); // M key TODO figure out why this won't work
    }
    
    // When layer 4 is active: Set U, N, E, I to yellow
    // RGB_YELLOW is defined as 0xFF, 0xFF, 0x00 (macro, not struct)
    if (IS_LAYER_ON_STATE(layers, 4)) {
        set_led_at_pos(4, 3, RGB_YELLOW); // U key
        set_led_at_pos(5, 4, RGB_YELLOW); // N key
        set_led_at_pos(5, 3, RGB_YELLOW); // E key
        set_led_at_pos(5, 2, RGB_YELLOW); // I key
        set_led_at_pos(6, 4, RGB_PURPLE); // H key
        set_led_at_pos(6, 2, RGB_PURPLE); // . key
    }

        // When layer 4 is active: Set U, N, E, I to yellow
    // RGB_YELLOW is defined as 0xFF, 0xFF, 0x00 (macro, not struct)
    if (IS_LAYER_ON_STATE(layers, 7)) {
        set_led_at_pos(4, 3, RGB_PURPLE); // U key
        set_led_at_pos(5, 4, RGB_PURPLE); // N key
        set_led_at_pos(5, 3, RGB_PURPLE); // E key
        set_led_at_pos(5, 2, RGB_PURPLE); // I key
    }

    // Numbers
    if (IS_LAYER_ON_STATE(layers, 1)) {
        set_led_at_pos(0, 1, RGB_YELLOW);
        set_led_at_pos(0, 2, RGB_YELLOW);
        set_led_at_pos(0, 3, RGB_YELLOW);
        set_led_at_pos(0, 4, RGB_YELLOW);
        set_led_at_pos(0, 5, RGB_YELLOW);
        set_led_at_pos(4, 5, RGB_YELLOW);
        set_led_at_pos(4, 4, RGB_YELLOW);
        set_led_at_pos(4, 3, RGB_YELLOW);
        set_led_at_pos(4, 2, RGB_YELLOW);
        set_led_at_pos(4, 1, RGB_YELLOW);
    }

    // symbols
    if (IS_LAYER_ON_STATE(layers, 2)) {
        set_led_at_pos(0, 1, RGB_MAGENTA);
        set_led_at_pos(0, 2, RGB_MAGENTA);
        set_led_at_pos(0, 3, RGB_MAGENTA);
        set_led_at_pos(0, 4, RGB_MAGENTA);
        set_led_at_pos(0, 5, RGB_MAGENTA);
        set_led_at_pos(4, 5, RGB_MAGENTA);
        set_led_at_pos(4, 4, RGB_MAGENTA);
        set_led_at_pos(4, 3, RGB_MAGENTA);
        set_led_at_pos(4, 2, RGB_MAGENTA);
        set_led_at_pos(4, 1, RGB_MAGENTA);
    }

    // 10 key
    if (IS_LAYER_ON_STATE(layers, 3)) {
        set_led_at_pos(4, 5, RGB_YELLOW);
        set_led_at_pos(4, 4, RGB_YELLOW);
        set_led_at_pos(4, 3, RGB_YELLOW);
        set_led_at_pos(5, 5, RGB_YELLOW);
        set_led_at_pos(5, 4, RGB_YELLOW);
        set_led_at_pos(5, 3, RGB_YELLOW);
        set_led_at_pos(6, 5, RGB_YELLOW);
        set_led_at_pos(6, 4, RGB_YELLOW);
        set_led_at_pos(6, 3, RGB_YELLOW);
    }

    if (IS_LAYER_ON_STATE(layers, 5)) {
        set_led_at_pos(0, 0, RGB_RED); // ESC
    } else if (get_highest_layer(layer_state) > 0) {
        set_led_at_pos(0, 0, RGB_GREEN); // esc key, but return to home layer
    }
    
    return false; // We've handled the indicators
}
#endif

