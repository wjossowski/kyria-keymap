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
    MTM(TAB), KC_Q    , KC_W    , KC_E    , KC_R    , KC_T    ,                                                         KC_Y    , KC_U    , KC_I    , KC_O    , KC_P    , MTM(LBR),
    KC_CAPS , KC_A    , KC_S    , KC_D    , KC_F    , KC_G    ,                                                         KC_H    , KC_J    , KC_K    , KC_L    , KC_QUOT , MTS(SCLN),
    MTC(LBR), KC_Z    , KC_X    , KC_C    , KC_V    , KC_B    , XXXXXXX , XXXXXXX ,                 XXXXXXX , XXXXXXX , KC_N    , KC_M    , KC_COMM , KC_DOT  , KC_SLSH , MTS(RBR),
                                  XXXXXXX , KC_LALT , KC_LGUI , MTS(SPC), MO(SYM) ,                 MO(NUM) ,MTS(BSPC), KC_LALT , KC_LGUI , XXXXXXX
  ),

  [SYM] = LAYOUT(
    KC_TILDE, XXXXXXX , XXXXXXX , KC_HASH , KC_PERC , KC_MINUS,                                                         KC_EQL  , KC_PERC , KC_ASTR , XXXXXXX , XXXXXXX , KC_LPRN ,
    KC_CIRC , KC_COMM , KC_AT   , KC_LPRN , KC_QUES , KC_LCBR ,                                                         KC_COLN , KC_AMPR , KC_QUOT , KC_RABK , KC_SCLN , KC_DLR  ,
    XXXXXXX , KC_GRV  , XXXXXXX , KC_RPRN , KC_EXLM , KC_RCBR , XXXXXXX , XXXXXXX ,                 XXXXXXX , XXXXXXX , KC_MINUS, KC_PIPE , KC_DQUO , XXXXXXX , KC_BSLS , KC_RPRN ,
                                  _______ , _______ , _______ , _______ , _______ ,                 MO(FUN) , ENT_FUN , _______ , _______ , _______
  ),

  [NUM] = LAYOUT(
    KC_TILDE, KC_1    , KC_2    , KC_3    , XXXXXXX , XXXXXXX ,                                                         KC_EQL  , KC_PERC , XXXXXXX , XXXXXXX , XXXXXXX , KC_LPRN ,
    KC_COMM , KC_4    , KC_5    , KC_6    , XXXXXXX , KC_LPRN ,                                                         KC_DOT  , KC_PLUS , KC_ASTR , XXXXXXX , XXXXXXX , KC_LGUI ,
    KC_0    , KC_7    , KC_8    , KC_9    , KC_0    , KC_RPRN , XXXXXXX , XXXXXXX ,                 XXXXXXX , XXXXXXX , KC_MINUS, KC_MINUS, KC_SLSH , XXXXXXX , XXXXXXX , KC_RPRN ,
                                  _______ , _______ , _______ , ENT_FUN , MO(FUN) ,                 _______ , _______ , _______ , _______ , _______
  ),


  [FUN] = LAYOUT(
    JMP_APP , KC_F1   , KC_F2   , KC_F3   , KC_F10  , XXXXXXX ,                                                         XXXXXXX , KC_MUTE , KC_MPLY , XXXXXXX , XXXXXXX , KC_LABK ,
    IDE_BW  , KC_F4   , KC_F5   , KC_F6   , KC_F11  , KC_LABK ,                                                         KC_BRIU , KC_VOLU , KC_MNXT , XXXXXXX , XXXXXXX , IDE_FW  ,
    IDE_BW  , KC_F7   , KC_F8   , KC_F9   , KC_F12  , KC_RABK , XXXXXXX , XXXXXXX ,                 XXXXXXX , XXXXXXX , KC_BRID , KC_VOLD , KC_MPRV , XXXXXXX , XXXXXXX , KC_RABK ,
                                  _______ , _______ , _______ , _______ , _______ ,                 _______ , _______ , _______ , _______ , _______
  )
};

