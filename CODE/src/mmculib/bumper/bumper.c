#include "bumper.h"

static bool pressed = false;


bool get_bumper() {
    return pressed;
}

void set_bumper(bool update) {
    pressed = update;
}

bool update_bumper() {
    return ! pio_input_get(BUMP_PIO);
}