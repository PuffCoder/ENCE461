/** @file   bumper.h
    @author Heng Yin, John Elliott
    @date   16 May 2023
    @brief  bumper info
*/

#ifndef BUMPER_H
#define BUMPER_H

#include "config.h"
#include "pio.h"

#ifdef __cplusplus
extern "C" {
#endif


bool get_bumper(void);

void set_bumper(bool);

bool update_bumper(void);


#ifdef __cplusplus
}
#endif
#endif
