#pragma once

#ifdef RGBLIGHT_ENABLE
#define RGBLIGHT_ANIMATIONS
#define RGBLIGHT_HUE_STEP 8
#define RGBLIGHT_SAT_STEP 8
#define RGBLIGHT_VAL_STEP 8
#define RGBLIGHT_LIMIT_VAL 150
#endif

#ifdef LEADER_ENABLE
#define LEADER_TIMEOUT 500
#endif

#ifdef OLED_ENABLE
#define OLED_DISPLAY_128X32
#define OLED_TIMEOUT 60000
#endif

// Lets you roll mod-tap keys
#define IGNORE_MOD_TAP_INTERRUPT

#ifdef TAP_DANCE_ENABLE
#define TAPPING_TERM 200
#endif
