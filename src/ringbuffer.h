/*
 * =====================================================================================
 *
 *       Filename:  ringbuffer.h
 *
 *    Description:  Header fuer 
 *
 *        Version:  1.0.0
 *        Created:  04/30/2018 10:20:05 AM
 *       Revision:  none
 *       Compiler:  gcc52
 *
 *         Author:  Ovidiu - Dan Bogat [ic17b501], ic17b501@technikum-wien.at
 * =====================================================================================
 */
#ifndef __ringbuffer_h
#define __ringbuffer_h

#include <stdint.h>

typedef struct _ringbuffer
{
  uint8_t * const buffer;
  int head;
  int tail;
  const int max_length;
} ringbuffer;

#endif /* ringbuffer.h */
