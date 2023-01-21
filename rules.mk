# Flags 

OLED_ENABLE = no
# OLED_DRIVER = SSD1306

ENCODER_ENABLE = no
RGBLIGHT_ENABLE = yes
TAP_DANCE_ENABLE = no

LEADER_ENABLE = no
AUTO_SHIFT_ENABLE = no

# Source
ifeq ($(strip $(ENCODER_ENABLE)), yes)
	SRC += encoder.c
endif

ifeq ($(strip $(OLED_ENABLE)), yes)
	SRC += oled.c
endif
