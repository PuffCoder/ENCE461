MPUU_DIR = $(DRIVER_DIR)/adxl_data

VPATH += $(MPUU_DIR)
SRC += adxl_data.c

INCLUDES += -I$(MPUU_DIR)

