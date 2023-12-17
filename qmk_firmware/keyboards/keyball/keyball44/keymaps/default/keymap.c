/*
Copyright 2022 @Yowkees
Copyright 2022 MURAOKA Taro (aka KoRoN, @kaoriya)

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

#include "quantum.h"

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  // keymap for default
  [0] = LAYOUT_universal(
    KC_TAB   , KC_Q     , KC_W     , KC_E     , KC_R     , KC_T     ,                                        KC_Y     , KC_U     , KC_I     , KC_O     , KC_P     , KC_MINS  ,
    KC_LCTL  , KC_A     , KC_S     , KC_D     , LT(1, KC_F) , KC_G  ,                                        KC_H     , KC_J     , KC_K     , KC_L     , KC_SCLN  , LT(1, KC_QUOT),
    KC_LSFT  , KC_Z     , KC_X     , KC_C     , KC_V     , KC_B     ,                                        KC_N     , KC_M     , KC_COMM  , KC_DOT   , KC_SLSH  , RSFT_T(KC_LBRC)  ,
              KC_LALT, KC_LGUI,  LT(2, KC_SPC), KC_GRV, LT(1, KC_BSLS),                             RSFT_T(KC_BSPC), LT(2, KC_ENT), _______,     _______  , LT(3, KC_RBRC)
  ),

  [1] = LAYOUT_universal(
    _______  , KC_F1  , KC_F2  , KC_F3  , KC_F4  , KC_F5  ,                                        _______ , _______ , _______ , KC_F14 , KC_F15 , _______ ,
    _______  , KC_KB_VOLUME_DOWN, KC_KB_VOLUME_UP, KC_KB_MUTE, KC_F11, KC_F12,                     KC_LEFT , KC_DOWN , KC_UP , KC_RIGHT , KC_BTN2 , _______  ,
    _______  , KC_F6    , KC_F7    , KC_F8    , KC_F9     , KC_F10 ,                                        _______  , _______  , KC_BTN1    , KC_BTN4  , KC_BTN5  , _______  ,
    _______    , _______  , _______  ,        _______  , _______  ,                   _______  , _______  , _______       , _______  , _______
  ),

  [2] = LAYOUT_universal(
    KC_GRV   , S(KC_1)  , S(KC_2)  , S(KC_3) , S(KC_4)  , S(KC_5)  ,                                         S(KC_6)  , S(KC_7)  , S(KC_8)  , S(KC_9)  , S(KC_0)  , KC_EQUAL  ,
    S(KC_GRV), KC_1     , KC_2     , KC_3    , KC_4     , KC_5     ,                                         KC_6     , KC_7     , KC_8     , KC_9     , KC_0     , KC_BSLS  ,
    _______  , _______  , KC_MINS, S(KC_MINS), KC_EQUAL , S(KC_EQUAL),                                       KC_LBRC  , KC_RBRC  ,S(KC_LBRC),S(KC_RBRC), S(KC_EQUAL), _______ ,
                  _______ , _______, _______  ,         _______  , _______  ,                   KC_DEL   , _______  , _______       , _______  , _______
  ),

  [3] = LAYOUT_universal(
    _______ , _______  , KC_7      , KC_8    , KC_9     , _______ ,                                         _______  , _______  , _______  , _______ , _______, _______  ,
    _______ , _______  , KC_4      , KC_5    , KC_6     , _______ ,                                         SCRL_DVD  , SCRL_DVI , _______  , _______ , _______  , KBC_RST  ,
    _______ , _______  , KC_1      , KC_2    , KC_3     , _______ ,                                         CPI_D1K  , CPI_D100 , CPI_I100 , CPI_I1K  , KBC_SAVE , _______ ,
                  QK_RBT  , KBC_RST  , KC_0      , _______  , _______  ,                         _______  , _______  , _______       , _______  , _______
  ),

  [4] = LAYOUT_universal(
    _______  ,  _______   , _______    , _______   , _______    , _______    ,                             _______    , _______    , _______    , _______    , _______   , _______   ,
    _______  ,  _______ , _______  , _______   , _______   , _______   ,                                     _______  , _______  , _______    , _______  , KC_BTN2  , _______  ,
    _______  ,  _______ , _______  , _______ , _______  , _______  ,                                         _______  , _______  , KC_BTN1    , KC_BTN4  , KC_BTN5  , _______  ,
                  _______  , _______ , _______  ,   _______  , _______  ,                   _______  , _______  , _______       , _______  , _______
  ),
};
// clang-format on

layer_state_t layer_state_set_user(layer_state_t state) {
    switch(get_highest_layer(remove_auto_mouse_layer(state, true))) {
        case 3:
            // Auto enable scroll mode when the highest layer is 3
            state = remove_auto_mouse_layer(state, false);
            set_auto_mouse_enable(false);
            keyball_set_scroll_mode(true);
            break;
        default:
            set_auto_mouse_enable(true);
            keyball_set_scroll_mode(false);
            break;
    }

    return state;
}

#ifdef OLED_ENABLE

#    include "lib/oledkit/oledkit.h"

void oledkit_render_info_user(void) {
    keyball_oled_render_keyinfo();
    keyball_oled_render_ballinfo();
    keyball_oled_render_layerinfo();
}
#endif
