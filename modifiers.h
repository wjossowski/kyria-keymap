#pragma once

#include QMK_KEYBOARD_H

// Mod-Tap
#define MTM(kc) MT(MOD_LGUI | MOD_LCTL | MOD_LSFT, kc) // meh

// Layer-Tap
#define MTC(kc) MT(MOD_LCTL, kc)
#define MTS(kc) MT(MOD_LSFT, kc)
#define MTA(kc) MT(MOD_LALT, kc)
#define MTG(kc) MT(MOD_LGUI, kc)

#define SPC_SYM LT(SYM, KC_SPC)
#define BSP_NUM LT(NUM, KC_BSPC)
#define ENT_NUM LT(NUM, KC_ENT)
#define ENT_FUN LT(FUN, KC_ENT)

// Single Keys - just for less typing
#define SPC KC_SPC
#define BSPC KC_BSPC
#define NA XXXXXXX
#define TAB KC_TAB
#define SCLN KC_SCLN
#define LBR KC_LBRC
