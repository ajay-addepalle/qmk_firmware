#include QMK_KEYBOARD_H

#ifdef PROTOCOL_LUFA
  #include "lufa.h"
  #include "split_util.h"
#endif
#ifdef SSD1306OLED
  #include "ssd1306.h"
#endif

#ifdef RGBLIGHT_ENABLE
//Following line allows macro to read current RGB settings
extern rgblight_config_t rgblight_config;
#endif

extern uint8_t is_master;

#define _QWERTY 0
#define _LOWER 1
#define _RAISE 2
#define _ADJUST 3

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  LOWER,
  RAISE,
  ADJUST,
};


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* QWERTY
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |  =   |   1  |   2  |   3  |   4  |   5  |                    |   6  |   7  |   8  |   9  |   0  |  -   |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |DEL   |   Q  |   W  |   E  |   R  |   T  |                    |   Y  |   U  |   I  |   O  |   P  |  `   |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |BackSP|   A  |   S  |   D  |   F  |   G  |-------.    ,-------|   H  |   J  |   K  |   L  |   ;  |  '   |
 * |------+------+------+------+------+------|   [   |    |    ]  |------+------+------+------+------+------|
 * |LShift|   Z  |   X  |   C  |   V  |   B  |-------|    |-------|   N  |   M  |   ,  |   .  |   /  |RShift|
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   | LAlt | LCTL |LOWER | /Space  /       \Enter \  |RAISE |RCTL  | RGUI |
 *                   |      |      |      |/       /         \      \ |      |      |      |
 *                   `----------------------------'           '------''--------------------'
 */

 [_QWERTY] = LAYOUT( \
KC_EQL,   KC_1,     KC_2,   KC_3,    KC_4,    KC_5,                      KC_6,  KC_7,  KC_8,     KC_9,    KC_0,     KC_MINS,\
KC_DEL,   KC_Q,     KC_W,   KC_E,    KC_R,    KC_T,                      KC_Y,  KC_U,  KC_I,     KC_O,    KC_P,     KC_GRV,\
KC_BSPC,  KC_A,     KC_S,   KC_D,    KC_F,    KC_G,                      KC_H,  KC_J,  KC_K,     KC_L,    KC_SCLN,  KC_QUOT,\
KC_LSFT,  KC_Z,     KC_X,   KC_C,    KC_V,    KC_B,   KC_ESC,   KC_TAB,  KC_N,  KC_M,  KC_COMM,  KC_DOT,  KC_SLSH,  KC_RSFT,\
                          KC_LALT,  KC_LCTL,  OSL(1),  KC_SPC,  KC_ENT,  OSL(2),  KC_RCTL,  KC_LGUI \
),
/* LOWER
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |      |  F1  |  F2  |  F3  |  F4  |  F5  |                    |  F6  |  F7  |  F8  | F9   | F10  | F11  |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |   &  |   *  |      |   {  |   }  |   /  |                    |   /  |   7  |   8  |   9  |   *  | F12  |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |   $  |   %  |   ^  |   (  |   )  |   |  |-------.    ,-------|   -  |   4  |   5  |   6  |   +  |      |
 * |------+------+------+------+------+------|   0   |    |   $   |------+------+------+------+------+------|
 * |   !  |   @  |   #  |   [  |   ]  |   \  |-------|    |-------|   0  |   1  |   2  |   3  |   .  |  =   |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   |      |      |      | /       /       \      \  |      |      |      |
 *                   |      |      |      |/       /         \      \ |      |      |      |
 *                   `----------------------------'           '------''--------------------'
 */
[_LOWER] = LAYOUT( \
KC_TRNS,  KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,                        KC_F6,    KC_F7,   KC_F8,  KC_F9,  KC_F10,   KC_F11,\
KC_AMPR,  KC_ASTR,  KC_NO,    KC_LCBR,  KC_RCBR,  KC_SLSH,                      KC_PSLS,  KC_7,    KC_8,   KC_9,  KC_PAST,  KC_F12,\
KC_DLR,   KC_PERC,  KC_CIRC,  KC_LPRN,  KC_RPRN,  KC_PIPE,                      KC_PMNS,  KC_4,    KC_5,   KC_6,  KC_PPLS,  KC_TRNS,\
KC_EXLM,  KC_AT,    KC_HASH,  KC_LBRC,  KC_RBRC,  KC_BSLASH,  KC_0,     KC_DLR,   KC_0,     KC_1,    KC_2,   KC_3,  KC_PDOT,  KC_PEQL,\
                              KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS, KC_TRNS \
),
/* RAISE
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |      |      |      |      |      |      |                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |   `  |   1  |   2  |   3  |   4  |   5  |                    |   6  |   7  |   8  |   9  |   0  |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |-------.    ,-------|      | Left | Down |  Up  |Right |      |
 * |------+------+------+------+------+------|   0   |    |   $   |------+------+------+------+------+------|
 * |  F7  |  F8  |  F9  | F10  | F11  | F12  |-------|    |-------|   +  |   -  |   =  |   [  |   ]  |   \  |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   | LAlt | LGUI |LOWER | /Space  /       \Enter \  |RAISE |BackSP| RGUI |
 *                   |      |      |      |/       /         \      \ |      |      |      |
 *                   `----------------------------'           '------''--------------------'
 */

[_RAISE] = LAYOUT( \
KC_ACL2,  KC_TRNS,  NK_TOGG,  KC_TRNS,  KC_BRID,  KC_BRIU,                      KC_MPLY,  KC_MRWD,  KC_MFFD,  KC_MPRV,  KC_MNXT,  KC_MSTP,\
KC_ACL1,  KC_TRNS,  KC_WH_L,  KC_MS_U,  KC_WH_R,  KC_WH_U,                      KC_INS,   KC_HOME,  KC_PGUP,  KC_TRNS,  KC_COPY,  KC_VOLU,\
KC_ACL0,  KC_TRNS,  KC_MS_L,  KC_MS_D,  KC_MS_R,  KC_WH_D,                      KC_LEFT,  KC_DOWN,  KC_UP,    KC_RGHT,  KC_TRNS,  KC_VOLD,\
KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_BTN3,  KC_BTN2,  KC_0,     KC_DLR,  KC_DEL,   KC_END,   KC_PGDN,  KC_TRNS,  KC_PSTE,  KC_MUTE,\
                              KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_BTN1,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS \
),
/* ADJUST
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |      |      |      |      |      |      |                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      |      |      |      |      |                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      |      |      |      |      |-------.    ,-------|      |      |RGB ON| HUE+ | SAT+ | VAL+ |
 * |------+------+------+------+------+------|       |    |       |------+------+------+------+------+------|
 * |      |      |      |      |      |      |-------|    |-------|      |      | MODE | HUE- | SAT- | VAL- |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   | LAlt | LGUI |LOWER | /Space  /       \Enter \  |RAISE |BackSP| RGUI |
 *                   |      |      |      |/       /         \      \ |      |      |      |
 *                   `----------------------------'           '------''--------------------'
 */
  [_ADJUST] = LAYOUT( \
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX, XXXXXXX, RGB_TOG, RGB_HUI, RGB_SAI, RGB_VAI, \
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, RGB_MOD, RGB_HUD, RGB_SAD, RGB_VAD,\
                             _______, _______, _______, _______, _______,  _______, _______, _______ \
  )
};

int RGB_current_mode;

// Setting ADJUST layer RGB back to default
void update_tri_layer_RGB(uint8_t layer1, uint8_t layer2, uint8_t layer3) {
  if (IS_LAYER_ON(layer1) && IS_LAYER_ON(layer2)) {
    layer_on(layer3);
  } else {
    layer_off(layer3);
  }
}

void matrix_init_user(void) {
    #ifdef RGBLIGHT_ENABLE
      RGB_current_mode = rgblight_config.mode;
    #endif
}

//SSD1306 OLED update loop, make sure to enable OLED_DRIVER_ENABLE=yes in rules.mk
#ifdef OLED_DRIVER_ENABLE

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
  if (is_keyboard_master())
    return OLED_ROTATION_270;  // flips the display 180 degrees if offhand
  return rotation;
}

// When you add source files to SRC in rules.mk, you can use functions.
const char *read_layer_state(void);
const char *read_logo(void);
void set_keylog(uint16_t keycode, keyrecord_t *record);
const char *read_keylog(void);
const char *read_keylogs(void);

// const char *read_mode_icon(bool swap);
// const char *read_host_led_state(void);
// void set_timelog(void);
// const char *read_timelog(void);


void render_space(void) {
    oled_write_ln_P(PSTR("    "), false);
}

void render_mod_status_gui_alt(uint8_t modifiers) {
    if(modifiers & MOD_MASK_GUI) {
        oled_write_ln_P(PSTR("GUI"), true);
    } else {
        oled_write_ln_P(PSTR("GUI"), false);
    }
    render_space();
    if(modifiers & MOD_MASK_ALT) {
        oled_write_ln_P(PSTR("ALT"), true);
    } else {
        oled_write_ln_P(PSTR("ALT"), false);
    }

}

void render_mod_status_ctrl_shift(uint8_t modifiers) {
    // fillers between the modifier icons bleed into the icon frames
    if(modifiers & MOD_MASK_CTRL) {
        oled_write_ln_P(PSTR("CTRL"), true);
    } else {
        oled_write_ln_P(PSTR("CTRL"), false);
    }
    render_space();
    if(modifiers & MOD_MASK_SHIFT) {
        oled_write_ln_P(PSTR("SHIFT"), true);
    } else {
        oled_write_ln_P(PSTR("SHIFT"), false);
    }
}


void render_layer_state(void) {
    oled_write_ln_P(PSTR("Layer"), true);
    if(layer_state_is(_ADJUST)) {
        oled_write_ln_P(PSTR("AJD"), false);
    } else if(layer_state_is(_LOWER)) {
        oled_write_ln_P(PSTR("LWR"), false);
    } else if(layer_state_is(_RAISE)) {
        oled_write_ln_P(PSTR("RSE"), false);
    } else {
        oled_write_ln_P(PSTR("DFLT"), false);
    }
    oled_write_ln_P(PSTR("-----"), false);
}


void render_logo(void) {
    static const char PROGMEM corne_logo[] = {
        0x80, 0x81, 0x82, 0x83, 0x84,
        0xa0, 0xa1, 0xa2, 0xa3, 0xa4,
        0xc0, 0xc1, 0xc2, 0xc3, 0xc4, 0};
    oled_write_P(corne_logo, false);
    oled_write_P(PSTR("corne"), false);
}


void render_status_main(void) {
    //render_logo();
    render_space();
    render_layer_state();
    render_space();
    render_mod_status_gui_alt(get_mods()|get_oneshot_mods());
    render_space();
    render_mod_status_ctrl_shift(get_mods()|get_oneshot_mods());
}


void oled_task_user(void) {
  if (is_keyboard_master()) {
    // If you want to change the display of OLED, you need to change here
    //oled_write_ln(read_layer_state(), false);
    //oled_write_ln(read_keylog(), false);
    //oled_write_ln(read_keylogs(), false);
    //oled_write_ln(read_mode_icon(keymap_config.swap_lalt_lgui), false);
    //oled_write_ln(read_host_led_state(), false);
    //oled_write_ln(read_timelog(), false);
    render_status_main();
  } else {
    oled_write(read_logo(), false);
    //oled_scroll_right();
  }
}
#endif // OLED_DRIVER_ENABLE

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (record->event.pressed) {
#ifdef OLED_DRIVER_ENABLE
    set_keylog(keycode, record);
#endif
    // set_timelog();
  }

  switch (keycode) {
    case QWERTY:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_QWERTY);
      }
      return false;
      break;
    case LOWER:
      if (record->event.pressed) {
        layer_on(_LOWER);
        update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_LOWER);
        update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
      }
      return false;
      break;
    case RAISE:
      if (record->event.pressed) {
        layer_on(_RAISE);
        update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_RAISE);
        update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
      }
      return false;
      break;
    case ADJUST:
        if (record->event.pressed) {
          layer_on(_ADJUST);
        } else {
          layer_off(_ADJUST);
        }
        return false;
        break;
  }
  return true;
}
