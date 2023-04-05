#include QMK_KEYBOARD_H

#include "layers.h"

#ifdef OLED_ENABLE
#include "oled.h"
#endif

#ifdef ENCODER_ENABLE
#include "encoder.h"
#endif

// Mod-Tap
#define MTM(kc) MT(MOD_LGUI | MOD_LCTL | MOD_LSFT, kc) // meh

// Layer-Tap
#define MTC(kc) MT(MOD_LCTL, kc)
#define MTS(kc) MT(MOD_LSFT, kc)
#define MTA(kc) MT(MOD_LALT, kc)
#define MTG(kc) MT(MOD_LGUI, kc)

#define SPC_SYM LT(SYM, KC_SPC)
#define ENT_SYM LT(SYM, KC_ENT)
#define BSPC_NUM LT(NUM, KC_BSPC)
#define ENT_NUM LT(NUM, KC_ENT)
#define ENT_FUN LT(FUN, KC_ENT)

// Single Keys - just for less typing
#define SPC KC_SPC
#define BSPC KC_BSPC
#define NA XXXXXXX
#define TAB KC_TAB
#define SCLN KC_SCLN

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [BASE] = LAYOUT(
      MTM(TAB), KC_Q    , KC_W    , KC_E    , KC_R    , KC_T    ,                                                         KC_Y    , KC_U    , KC_I    , KC_O    , KC_P    , MTM(KC_LBRC),
      KC_CAPS , KC_A    , KC_S    , KC_D    , KC_F    , KC_G    ,                                                         KC_H    , KC_J    , KC_K    , KC_L    , KC_QUOT , MTS(SCLN),
 MTC(KC_LBRC) , KC_Z    , KC_X    , KC_C    , KC_V    , KC_B    , XXXXXXX , XXXXXXX ,                 XXXXXXX , XXXXXXX , KC_N    , KC_M    , KC_COMM , KC_DOT  , KC_SLSH , MTC(KC_RBRC),
                                    KC_LALT , KC_LALT , MTG(SPC), MTS(SPC), SPC_SYM ,                 MO(NUM) ,MTS(BSPC), KC_LALT , KC_LALT , KC_LGUI
    ),

    [SYM] = LAYOUT(
      KC_0    , KC_CIRC , KC_PERC , KC_HASH , KC_MINUS, KC_UNDS ,                                                         KC_UNDS , KC_PLUS , KC_ASTR , KC_PERC , KC_DLR  , KC_DLR  ,
      KC_COMM , KC_PERC , XXXXXXX , KC_AT   , KC_EXLM , KC_EQL  ,                                                         KC_COLN , KC_AMPR , KC_DQUO,  KC_GRV  , KC_GRV  , KC_SCLN ,
      KC_LCBR , XXXXXXX , XXXXXXX , XXXXXXX , KC_QUES , KC_BSLS , XXXXXXX , XXXXXXX ,                 XXXXXXX , XXXXXXX , KC_SLSH , KC_PIPE , KC_QUOT,  XXXXXXX , KC_BSLS , KC_RCBR ,
                                    _______ , _______ , _______ , _______ , _______ ,                 MO(FUN) , ENT_FUN , _______ , _______ , _______
    ),

    [NUM] = LAYOUT(
      KC_TILDE, KC_1    , KC_2    , KC_3    , XXXXXXX , XXXXXXX ,                                                         MTM(NA) , MTM(NA) , MTM(NA) , MTM(NA) , MTM(NA) , _______ ,
      _______ , KC_4    , KC_5    , KC_6    , XXXXXXX , KC_DOT  ,                                                         KC_EQL  , KC_PLUS , KC_ASTR , XXXXXXX , XXXXXXX , _______ ,
      KC_LPRN , KC_7    , KC_8    , KC_9    , XXXXXXX , KC_COMM , XXXXXXX , XXXXXXX ,                 XXXXXXX , XXXXXXX , KC_EQL  , KC_MINUS, KC_SLSH , XXXXXXX , XXXXXXX , KC_RPRN ,
                                    KC_0    , _______ , _______ , ENT_FUN , MO(FUN) ,                 _______ , _______ , _______ , _______ , _______
    ),

    [FUN] = LAYOUT(
      _______ , KC_F1   , KC_F2   , KC_F3   , KC_F4   , XXXXXXX ,                                                         XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , _______ ,
      _______ , KC_F5   , KC_F6   , KC_F7   , KC_F8   , XXXXXXX ,                                                         XXXXXXX , XXXXXXX , KC_UP   , XXXXXXX , XXXXXXX , _______ ,
      KC_LABK , KC_F9   , KC_F10  , KC_F11  , KC_F12  , XXXXXXX , XXXXXXX , XXXXXXX ,                 XXXXXXX , XXXXXXX , XXXXXXX , KC_LEFT , KC_DOWN , KC_RIGHT, XXXXXXX , KC_RABK ,
                                    _______ , _______ , _______ , _______ , _______ ,                 _______ , _______ , _______ , _______ , _______
    )

};

#ifdef OLED_ENABLE
oled_rotation_t oled_init_user(oled_rotation_t rotation) { return OLED_ROTATION_270; }

bool oled_task_user(void) {
    handle_oled(); // <-- Lib load
    return false;
}
#endif

#ifdef ENCODER_ENABLE
bool encoder_update_user(uint8_t index, bool clockwise) {
    handle_encoder(index, clockwise); // <-- Lib load
    return false;
}
#endif


//    Layer template 
//
//     [LAYER] = LAYOUT(
//      _______ , _______ , _______ , _______ , _______ , _______ ,                                                         _______ , _______ , _______ , _______ , _______ , _______ ,
//      _______ , _______ , _______ , _______ , _______ , _______ ,                                                         _______ , _______ , _______ , _______ , _______ , _______ ,
//      _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ ,                 _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ ,
//                                    _______ , _______ , _______ , _______ , _______ ,                 _______ , _______ , _______ , _______ , _______
//     ),
