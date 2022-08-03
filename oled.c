#include <string.h>
#include "layers.h"
#include "oled.h"
#include "gfx/templeos_logo_0.h"
#include "gfx/layer_0.h"
#include "gfx/layer_1.h"
#include "gfx/layer_2.h"
#include "gfx/layer_3.h"

#define COVER_SIZE 1024
#define WINDOW_SIZE 256

static const char PROGMEM layer_0[] = { LAYER_0 };
static const char PROGMEM layer_1[] = { LAYER_1 };
static const char PROGMEM layer_2[] = { LAYER_2 };
static const char PROGMEM layer_3[] = { LAYER_3 };
static const char PROGMEM templeos_logo_0[] = { TEMPLEOS_LOGO_0 };

void handle_oled(void) {

    oled_set_cursor(0, 0);

    if (is_keyboard_master()) {
        switch (get_highest_layer(layer_state | default_layer_state)) {
            case BASE:
                oled_write_raw_P(layer_0, COVER_SIZE);
                break;
            case NUM:
                oled_write_raw_P(layer_1, COVER_SIZE);
                break;
            case SYM:
                oled_write_raw_P(layer_2, COVER_SIZE);
                break;
            case FUN:
                oled_write_raw_P(layer_3, COVER_SIZE);
                break;
            default:
                oled_write_raw_P(templeos_logo_0, COVER_SIZE);
        }
    } else {
        oled_write_raw_P(templeos_logo_0, COVER_SIZE);
    }
}
