#include QMK_KEYBOARD_H

#include "layers.h"

#ifdef OLED_ENABLE
#    include "oled.h"
#endif

#ifdef ENCODER_ENABLE
#    include "encoder.h"
#endif

// Mod-Tap
#define MTM(kc) MT(MOD_LGUI | MOD_LCTL | MOD_LSFT, kc) // meh
#define MTH(kc) MT(MOD_LGUI | MOD_LALT | MOD_LCTL | MOD_LSFT, kc) // hyper

#define MTC(kc) MT(MOD_LCTL, kc)
#define MTS(kc) MT(MOD_LSFT, kc)
#define MTA(kc) MT(MOD_LALT, kc)
#define MTG(kc) MT(MOD_LGUI, kc)

// Layer-Tap
#define SPC_LSYM LT(SYM, KC_SPC)
#define ENT_LNUM LT(NUM, KC_ENT)
#define ENT_LFUN LT(FUN, KC_ENT)

// Single Keys - just for less typing
#define SPC KC_SPC
#define BSPC KC_BSPC
#define NA  XXXXXXX
#define TAB KC_TAB

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [BASE] = LAYOUT(
      MTM(TAB), KC_Q    , KC_W    , KC_E    , KC_R    , KC_T    ,                                                         KC_Y    , KC_U    , KC_I    , KC_O    , KC_P    , MTC(TAB),
      KC_CAPS , KC_A    , KC_S    , KC_D    , KC_F    , KC_G    ,                                                         KC_H    , KC_J    , KC_K    , KC_L    , KC_QUOT ,MTS(BSPC),
      KC_LSFT , KC_Z    , KC_X    , KC_C    , KC_V    , KC_B    , XXXXXXX , XXXXXXX ,                 XXXXXXX , XXXXXXX , KC_N    , KC_M    , KC_COMM , KC_DOT  , KC_SLSH , MTC(TAB),
                                    XXXXXXX , MTC(SPC), MTA(SPC), MTG(SPC), SPC_LSYM,                 ENT_LNUM,MTA(BSPC),MTA(BSPC),MTG(BSPC), XXXXXXX
    ),

    [SYM] = LAYOUT(
      KC_0    , KC_CIRC , KC_PERC , KC_HASH , KC_PLUS , KC_UNDS ,                                                         KC_MINUS, KC_EQL  , KC_ASTR , KC_PERC , KC_DLR  , KC_DLR  ,
      _______ , KC_PERC , KC_LABK , KC_LBRC , KC_LCBR , KC_LPRN ,                                                         KC_COLN , KC_PIPE , KC_DQUO , KC_QUES , KC_GRV  , _______ ,
      _______ , XXXXXXX , KC_RABK , KC_RBRC , KC_RCBR , KC_RPRN , XXXXXXX , XXXXXXX ,                 XXXXXXX , XXXXXXX , KC_SCLN , KC_BSLS , KC_QUOTE, KC_EXLM	, KC_BSLS , _______ ,
                                    XXXXXXX , _______ , _______ , _______ , _______ ,                 ENT_LFUN, _______ , _______ , _______ , XXXXXXX
    ),

    [NUM] = LAYOUT(
      KC_TILDE, KC_LPRN , KC_1    , KC_2    , KC_3    , KC_COMM ,                                                         MTM(NA) , MTM(NA) , MTM(NA) , MTM(NA) , MTM(NA) , _______ ,
      _______ , KC_RPRN , KC_4    , KC_5    , KC_6    , KC_DOT  ,                                                         KC_EQL  , KC_PLUS , KC_ASTR , XXXXXXX , XXXXXXX , _______ ,
      _______ , KC_0    , KC_7    , KC_8    , KC_9    , KC_0    , XXXXXXX , XXXXXXX ,                 XXXXXXX , XXXXXXX , KC_EQL  , KC_MINUS, KC_SLSH , XXXXXXX , XXXXXXX , _______ ,
                                    XXXXXXX , _______ , _______ , _______ , ENT_LFUN,                 _______ , _______ , _______ , _______ , XXXXXXX
    ),

    [FUN] = LAYOUT(
      _______ , KC_VOLU , KC_F1   , KC_F2   , KC_F3   , KC_F4   ,                                                         XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , KC_MNXT , _______ ,
      _______ , KC_MPLY , KC_F5   , KC_F6   , KC_F7   , KC_F8   ,                                                         KC_LGUI , KC_LALT , KC_LSFT , KC_LCTL , KC_MPLY , _______ ,
      _______ , KC_VOLD , KC_F9   , KC_F10  , KC_F11  , KC_F12  , XXXXXXX , XXXXXXX ,                 XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , KC_MPRV , _______ ,
                                    XXXXXXX , _______ , _______ , _______ , _______ ,                 _______ , _______ , _______ , _______ , XXXXXXX
    )

};

uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case MTA(BSPC):
        case MTG(BSPC):
            return TAPPING_TERM - 100;
        case ENT_LNUM:
        case ENT_LFUN:
            return TAPPING_TERM - 50;
        default:
            return TAPPING_TERM;
    }
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