RADIO_SM_HAT_DIR = $(DRIVER_DIR)/radio_sm_hat

VPATH += $(RADIO_SM_HAT_DIR)
SRC += radio_sm_hat.c

INCLUDES += -I$(RADIO_SM_HAT_DIR)
