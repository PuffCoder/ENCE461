BUZZER_DIR = $(DRIVER_DIR)/buzzer

VPATH += $(BUZZER_DIR)
SRC += buzzer.c

PERIPHERALS += pwm

INCLUDES += -I$(BUZZER_DIR)
