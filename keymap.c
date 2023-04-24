#include QMK_KEYBOARD_H

#include "layers.h"
#include "modifiers.h"

#define RGBLIGHT_LED_MAP {0,1,2,9,8,7,4,3,5,6,19,18,17,10,11,12,15,16,14,13}

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [BASE] = LAYOUT(
    MTM(TAB), KC_Q    , KC_W    , KC_E    , KC_R    , KC_T    ,                                                         KC_Y    , KC_U    , KC_I    , KC_O    , KC_P    , MTM(KC_BSPC),
    KC_CAPS , KC_A    , KC_S    , KC_D    , KC_F    , KC_G    ,                                                         KC_H    , KC_J    , KC_K    , KC_L    , KC_QUOT , MTS(SCLN),
    MTC(LBR), KC_Z    , KC_X    , KC_C    , KC_V    , KC_B    , XXXXXXX , XXXXXXX ,                 XXXXXXX , XXXXXXX , KC_N    , KC_M    , KC_COMM , KC_DOT  , KC_SLSH , MTC(KC_RBRC),
                                  XXXXXXX , KC_LALT , MTG(SPC), MTS(SPC), SPC_SYM ,                 BSP_NUM , MTS(BSP), KC_LALT , KC_LGUI , XXXXXXX
  ),

  [SYM] = LAYOUT(
    KC_0    , KC_CIRC , KC_PERC , KC_HASH , KC_MINUS, KC_MINUS,                                                         KC_EQL  , KC_PLUS , KC_ASTR , KC_PERC , KC_DLR  , KC_DLR  ,
    KC_COMM , KC_AT   , XXXXXXX , KC_EXLM , KC_QUES , KC_UNDS ,                                                         KC_COLN , KC_AMPR , KC_DQUO,  KC_GRV  , KC_GRV  , KC_SCLN ,
    KC_LCBR , KC_LPRN , XXXXXXX , XXXXXXX , XXXXXXX , KC_BSLS , XXXXXXX , XXXXXXX ,                 XXXXXXX , XXXXXXX , KC_SLSH , KC_PIPE , KC_QUOT,  XXXXXXX , KC_RPRN , KC_RCBR ,
                                  _______ , _______ , _______ , _______ , _______ ,                 MO(FUN) , ENT_FUN , _______ , _______ , _______
  ),

  [NUM] = LAYOUT(
    KC_TILDE, KC_COMM , KC_1    , KC_2    , KC_3    , KC_COMM ,                                                         MTM(NA) , MTM(NA) , MTM(NA) , MTM(NA) , MTM(NA) , _______ ,
    _______ , KC_DOT  , KC_4    , KC_5    , KC_6    , KC_DOT  ,                                                         KC_EQL  , KC_PLUS , KC_ASTR , XXXXXXX , XXXXXXX , _______ ,
    KC_LABK , KC_0    , KC_7    , KC_8    , KC_9    , KC_0    , XXXXXXX , XXXXXXX ,                 XXXXXXX , XXXXXXX , KC_EQL  , KC_MINUS, KC_SLSH , XXXXXXX , XXXXXXX , KC_RABK ,
                                  _______ , _______ , _______ , ENT_FUN , MO(FUN) ,                 _______ , _______ , _______ , _______ , _______
  ),

  [FUN] = LAYOUT(
    _______ , KC_F1   , KC_F2   , KC_F3   , KC_F4   , XXXXXXX ,                                                         XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , _______ ,
    _______ , KC_F5   , KC_F6   , KC_F7   , KC_F8   , XXXXXXX ,                                                         XXXXXXX , XXXXXXX , KC_UP   , XXXXXXX , XXXXXXX , _______ ,
    _______ , KC_F9   , KC_F10  , KC_F11  , KC_F12  , XXXXXXX , XXXXXXX , XXXXXXX ,                 XXXXXXX , XXXXXXX , XXXXXXX , KC_LEFT , KC_DOWN , KC_RIGHT, XXXXXXX , _______ ,
                                  _______ , _______ , _______ , _______ , _______ ,                 _______ , _______ , _______ , _______ , _______
  )
};

