CIRC_BUFF_DIR = $(DRIVER_DIR)/circ_buff

VPATH += $(CIRC_BUFF_DIR)
SRC += circ_buff.c

INCLUDES += -I$(CIRC_BUFF_DIR)
