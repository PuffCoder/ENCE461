/**
 * @file circ_buff.h
 * @author Jamie Thomas
 * @brief Checks for radio switches (1 and 2) to check which channel to run the radio on. 
 * @date 2023-05-09
 */

#ifndef CIRC_BUFF_H
#define CIRC_BUFF_H

// *******************************************************
// 
// circBufT.h
//
// Support for a circular buffer of uint32_t values on the 
//  Tiva processor.
// P.J. Bones UCECE
// Last modified:  7.3.2017
// 
// *******************************************************
#include "config.h"

// *******************************************************
// Buffer structure
typedef struct {
	int16_t size;		// Number of entries in buffer
	int16_t windex;	// index for writing, mod(size)
	int16_t rindex;	// index for reading, mod(size)
	int16_t *data;		// pointer to the data
} circBuf_t;

// *******************************************************
// initCircBuf: Initialise the circBuf instance. Reset both indices to
// the start of the buffer.  Dynamically allocate and clear the the 
// memory and return a pointer for the data.  Return NULL if 
// allocation fails.
int16_t *
initCircBuf (circBuf_t *buffer, int16_t size);

// *******************************************************
// writeCircBuf: insert entry at the current windex location,
// advance windex, modulo (buffer size).
void
writeCircBuf (circBuf_t *buffer, int16_t entry);

// *******************************************************
// readCircBuf: return entry at the current rindex location,
// advance rindex, modulo (buffer size). The function deos not check
// if reading has advanced ahead of writing.
int16_t
readCircBuf (circBuf_t *buffer);

// *******************************************************
// freeCircBuf: Releases the memory allocated to the buffer data,
// sets pointer to NULL and other fields to 0. The buffer can
// re initialised by another call to initCircBuf().
void
freeCircBuf (circBuf_t *buffer);


int16_t 
readAverageCircBuf(circBuf_t *buffer);


#endif /* CIRC_BUFF_H */