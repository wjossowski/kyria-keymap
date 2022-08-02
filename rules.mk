# Flags 
LEADER_ENABLE = yes

OLED_ENABLE = yes
OLED_DRIVER = SSD1306

ENCODER_ENABLE = no
RGBLIGHT_ENABLE = no
TAP_DANCE_ENABLE = no

# Source
ifeq ($(strip $(ENCODER_ENABLE)), yes)
	SRC += encoder.c
endif

ifeq ($(strip $(OLED_ENABLE)), yes)
	SRC += oled.c
endif