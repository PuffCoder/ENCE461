RADIO_HAT_DIR = $(DRIVER_DIR)/radio_hat

VPATH += $(RADIO_HAT_DIR)
SRC += radio_hat.c

INCLUDES += -I$(RADIO_HAT_DIR)
