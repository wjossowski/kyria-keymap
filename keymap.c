#include QMK_KEYBOARD_H

#include "layers.h"
#include "modifiers.h"

#define RGBLIGHT_LED_MAP                                                 \
  {                                                                      \
    0, 1, 2, 9, 8, 7, 4, 3, 5, 6, 19, 18, 17, 10, 11, 12, 15, 16, 14, 13 \
  }

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [BASE] = LAYOUT(
    MTM(TAB), KC_Q    , KC_W    , KC_E    , KC_R    , KC_T    ,                                                         KC_Y    , KC_U    , KC_I    , KC_O    , KC_P    , LBR,
    KC_CAPS , KC_A    , KC_S    , KC_D    , KC_F    , KC_G    ,                                                         KC_H    , KC_J    , KC_K    , KC_L    , KC_QUOT , MTS(SCLN),
    MTC(LBR), KC_Z    , KC_X    , KC_C    , KC_V    , KC_B    , XXXXXXX , XXXXXXX ,                 XXXXXXX , XXXXXXX , KC_N    , KC_M    , KC_COMM , KC_DOT  , KC_SLSH , RBR,
                                  XXXXXXX , XXXXXXX , KC_LGUI , MTA(SPC), MO(SYM) ,                 MO(NUM) ,MTA(BSPC), KC_LGUI , XXXXXXX , XXXXXXX
  ),

  [SYM] = LAYOUT(
    KC_GRV  , KC_CIRC , KC_PERC , KC_HASH , KC_QUES , KC_MINUS,                                                         KC_EQL  , KC_EXLM , KC_ASTR , KC_PERC , KC_DLR  , XXXXXXX ,
    KC_COMM , KC_AT   , KC_LBRC , KC_LCBR , KC_LPRN , KC_UNDS ,                                                         KC_COLN , KC_AMPR , KC_DQUO , KC_RABK , XXXXXXX , KC_SCLN ,
    XXXXXXX , XXXXXXX , KC_RBRC , KC_RCBR , KC_RPRN , KC_MINUS, XXXXXXX , XXXXXXX ,                 XXXXXXX , XXXXXXX , XXXXXXX , KC_PIPE , KC_QUOT , XXXXXXX , KC_BSLS , XXXXXXX ,
                                  _______ , _______ , _______ , _______ , _______ ,                 MO(FUN) , ENT_FUN , _______ , _______ , _______
  ),

  [NUM] = LAYOUT(
    KC_GRV  , KC_1    , KC_2    , KC_3    , XXXXXXX , XXXXXXX ,                                                         KC_EQL  , KC_PERC , MTM(NA) , MTM(NA) , MTM(NA) , KC_LPRN ,
    KC_COMM , KC_4    , KC_5    , KC_6    , XXXXXXX , KC_LPRN ,                                                         KC_DOT  , KC_PLUS , KC_ASTR , XXXXXXX , XXXXXXX , KC_LGUI ,
    KC_0    , KC_7    , KC_8    , KC_9    , KC_0    , KC_RPRN , XXXXXXX , XXXXXXX ,                 XXXXXXX , XXXXXXX , KC_DOT  , KC_MINUS, KC_SLSH , XXXXXXX , XXXXXXX , KC_RPRN ,
                                  _______ , _______ , _______ , ENT_FUN , MO(FUN) ,                 _______ , _______ , _______ , _______ , _______
  ),


  [FUN] = LAYOUT(
    JMP_APP , KC_F1   , KC_F2   , KC_F3   , XXXXXXX , XXXXXXX ,                                                         XXXXXXX , KC_F10  , KC_F11  , KC_F12  , XXXXXXX , XXXXXXX ,
    IDE_BW  , KC_F4   , KC_F5   , KC_F6   , KC_LABK , XXXXXXX ,                                                         XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , IDE_FW  ,
    IDE_BW  , KC_F8   , KC_F9   , KC_F10  , KC_RABK , XXXXXXX , XXXXXXX , XXXXXXX ,                 XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX ,
                                  _______ , _______ , _______ , _______ , _______ ,                 _______ , _______ , _______ , _______ , _______
  )
};

