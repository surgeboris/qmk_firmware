/*
Copyright 2019 @foostan
Copyright 2020 Drashna Jaelre <@drashna>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include QMK_KEYBOARD_H
#include <stdio.h>

enum userspace_layers {
    L_QWERTY = 0,
    L_DVORAK,
    L_SYM,
    L_MOUSE,
    L_FN,
    L_LAYERNAV
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [L_QWERTY] = LAYOUT_split_3x6_3(
    LALT_T(KC_ESC), KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, LALT_T(KC_BSPC),
    LCTL_T(KC_TAB), KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, RCTL_T(KC_QUOT),
    LSFT_T(KC_GRV), KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, RSFT_T(KC_ENT),
    OSL(L_LAYERNAV), LT(L_SYM, KC_SPC), KC_LGUI, TG(L_MOUSE), LT(L_FN, KC_SPC), KC_RALT
  ),
  [L_DVORAK] = LAYOUT_split_3x6_3(
    KC_TRNS, KC_QUOT, KC_COMM, KC_DOT, KC_P, KC_Y, KC_F, KC_G, KC_C, KC_R, KC_L, KC_TRNS,
    KC_TRNS, KC_A, KC_O, KC_E, KC_U, KC_I, KC_D, KC_H, KC_T, KC_N, KC_S, RCTL_T(KC_SLSH),
    KC_TRNS, KC_SCLN, KC_Q, KC_J, KC_K, KC_X, KC_B, KC_M, KC_W, KC_V, KC_Z, KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
  ),
  [L_SYM] = LAYOUT_split_3x6_3(
    KC_TRNS, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, LALT_T(KC_DEL),
    KC_TRNS, KC_UNDS, KC_SLSH, KC_MINS, KC_EQL, KC_PLUS, KC_BSLS, KC_LPRN, KC_RPRN, KC_LCBR, KC_RCBR, KC_TRNS,
    KC_TRNS, KC_EXLM, KC_AT, KC_HASH, KC_DLR, KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_LBRC, KC_RBRC, KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
  ),
  [L_MOUSE] = LAYOUT_split_3x6_3(
    LALT_T(KC_MPLY), KC_RALT, KC_RCTL, OSM(MOD_HYPR), KC_BTN3, KC_APP, KC_WH_L, KC_WH_D, KC_WH_U, KC_WH_R, KC_NLCK, LALT_T(KC_MUTE),
    LCTL_T(KC_MNXT), KC_ACL2, KC_ACL1, KC_ACL0, KC_BTN1, KC_BTN2, KC_MS_L, KC_MS_D, KC_MS_U, KC_MS_R, KC_SLCK, RCTL_T(KC_INS),
    LSFT_T(KC_MPRV), KC_RSFT, KC_RGUI, OSM(MOD_MEH), KC_BTN4, KC_BTN5, KC_HOME, KC_PGDN, KC_PGUP, KC_END, KC_CAPS, RSFT_T(KC_PAUS),
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, HYPR(KC_M)
  ),
  [L_FN] = LAYOUT_split_3x6_3(
    LALT_T(KC_F1), KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, LALT_T(KC_F12),
    LCTL_T(KC_BRIU), LGUI(KC_1), LGUI(KC_2), LGUI(KC_3), LGUI(KC_4), LGUI(KC_5), KC_LEFT, KC_DOWN, KC_UP, KC_RGHT, KC_HOME, RCTL_T(KC_VOLU),
    LCTL_T(KC_BRID), LGUI(KC_6), LGUI(KC_7), LGUI(KC_8), LGUI(KC_9), LGUI(KC_0), LCTL(KC_LEFT), LCTL(KC_END), LCTL(KC_HOME), LCTL(KC_RIGHT), KC_END, RSFT_T(KC_VOLD),
    KC_TRNS, KC_TRNS, LCA(KC_DEL), KC_TRNS, KC_TRNS, LCA(KC_INS)
  ),
  [L_LAYERNAV] = LAYOUT_split_3x6_3(
    OSM(MOD_LALT), KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, OSM(MOD_LCTL|MOD_LSFT),
    OSM(MOD_LCTL), KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, OSM(MOD_LSFT|MOD_LALT),
    OSM(MOD_LSFT), KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, NK_TOGG, OSM(MOD_LCTL|MOD_LALT),
    TO(0), TO(2), TO(1), TO(3), TO(4), RESET
  )
};

#ifdef OLED_ENABLE
oled_rotation_t oled_init_user(oled_rotation_t rotation) {
  #if defined(MASTER_RIGHT)
    return OLED_ROTATION_180;  // flips the display 180 degrees if offhand
  #else
    return rotation;
  #endif
}

void oled_render_layer_state(void) {
    if (layer_state & (1 << L_FN)) {
      oled_write_P(PSTR("FN"), false);
    } else if (layer_state & (1 << L_MOUSE)) {
        oled_write_P(PSTR("MOUSE"), false);
    } else if (layer_state & (1 << L_SYM)) {
        oled_write_P(PSTR("SYM"), false);
    } else if (layer_state & (1 <<  L_DVORAK)) {
        oled_write_P(PSTR("DVORAK"), false);
    } else if (layer_state & (1 << L_LAYERNAV)) {
        oled_write_P(PSTR("LAYERNAV"), false);
    } else {
        oled_write_P(PSTR("QWERTY"), false);
    }
}


char keylog_str[24] = {};

const char code_to_name[60] = {
    ' ', ' ', ' ', ' ', 'a', 'b', 'c', 'd', 'e', 'f',
    'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p',
    'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
    '1', '2', '3', '4', '5', '6', '7', '8', '9', '0',
    'R', 'E', 'B', 'T', '_', '-', '=', '[', ']', '\\',
    '#', ';', '\'', '`', ',', '.', '/', ' ', ' ', ' '};

void set_keylog(uint16_t keycode, keyrecord_t *record) {
  char name = ' ';
    if ((keycode >= QK_MOD_TAP && keycode <= QK_MOD_TAP_MAX) ||
        (keycode >= QK_LAYER_TAP && keycode <= QK_LAYER_TAP_MAX)) { keycode = keycode & 0xFF; }
  if (keycode < 60) {
    name = code_to_name[keycode];
  }

  // update keylog
  snprintf(keylog_str, sizeof(keylog_str), "%dx%d, k%2d : %c",
           record->event.key.row, record->event.key.col,
           keycode, name);
}

void oled_render_keylog(void) {
    oled_write(keylog_str, false);
}

bool oled_task_user(void) {
    if (is_keyboard_master()) {
      oled_write_ln_P(PSTR(""), false);
      if (!keymap_config.nkro) {
        oled_write_P(PSTR("6KRO "), false);
      }
      oled_render_layer_state();
      oled_write_ln_P(PSTR(""), false);
      oled_write_ln_P(PSTR(""), false);
      oled_render_keylog();
    }
    return false;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (record->event.pressed) {
    set_keylog(keycode, record);
  }
  return true;
}
#endif // OLED_ENABLE
