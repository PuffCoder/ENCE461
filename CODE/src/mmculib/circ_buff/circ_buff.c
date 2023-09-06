// *******************************************************
// 
// circ_buff.c
//
// Support for a circular buffer of uint32_t values on the 
//  Tiva processor.
// P.J. Bones UCECE
// Last modified:  8.3.2017
// 
// *******************************************************

#include "circ_buff.h"

#include <stdlib.h>

// *******************************************************
// initCircBuf: Initialise the circBuf instance. Reset both indices to
// the start of the buffer.  Dynamically allocate and clear the the 
// memory and return a pointer for the data.  Return NULL if 
// allocation fails.
int16_t *
initCircBuf (circBuf_t *buffer, int16_t size)
{
	buffer->windex = 0;
	buffer->rindex = 0;
	buffer->size = size;
	buffer->data = 
        (int16_t *) calloc (size, sizeof(int16_t));
	return buffer->data;
}
   // Note use of calloc() to clear contents.

// *******************************************************
// writeCircBuf: insert entry at the current windex location,
// advance windex, modulo (buffer size).
void
writeCircBuf (circBuf_t *buffer, int16_t entry)
{
	buffer->data[buffer->windex] = entry;
	buffer->windex++;
	if (buffer->windex >= buffer->size)
	   buffer->windex = 0;
}

// *******************************************************
// readCircBuf: return entry at the current rindex location,
// advance rindex, modulo (buffer size). The function deos not check
// if reading has advanced ahead of writing.
int16_t
readCircBuf (circBuf_t *buffer)
{
	int16_t entry;
	
	entry = buffer->data[buffer->rindex];
	buffer->rindex++;
	if (buffer->rindex >= buffer->size)
	   buffer->rindex = 0;
    return entry;
}

// *******************************************************
// freeCircBuf: Releases the memory allocated to the buffer data,
// sets pointer to NULL and ohter fields to 0. The buffer can
// re-initialised by another call to initCircBuf().
void
freeCircBuf (circBuf_t * buffer)
{
	buffer->windex = 0;
	buffer->rindex = 0;
	buffer->size = 0;
	free (buffer->data);
	buffer->data = NULL;
}

int16_t readAverageCircBuf(circBuf_t *buffer)
{
    // Initialize variables
    int16_t sum = 0;
    uint8_t i;

    // Sum buffer values
    for (i = 0; i < BUF_SIZE; i++) {
        sum = sum + readCircBuf(buffer);
    }
	// printf("%d\n", sum);
    // return the average of the values
    return (2 * sum + BUF_SIZE) / 2 / BUF_SIZE;
}
