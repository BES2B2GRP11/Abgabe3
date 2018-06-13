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
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "sharedmem.h"
#include "ringbuffer.h"
#include "error_handling.h"

ringbuffer* rbf_init(size_t n)
{
  ringbuffer *p;
  uint8_t lbuffer[n];

#ifdef DEBUG
  DBG("Creating a buffer with size %-2.ld",++n);
#endif
  
  ringbuffer local = {
    .buffer = lbuffer,
    .head = 0,
    .tail = 0,
    .max_length = n
  };
  
  p=malloc(sizeof(ringbuffer));
  if(p==NULL)
    {
      handle_error(FATAL,"malloc for ringbuffer");
      return NULL;
    }

  memcpy(p,&local,sizeof(ringbuffer));
  return p;
}

ringbuffer* rbf_destroy(ringbuffer *rbf)
{
#ifdef DEBUG
  DBG("Deconstructing ringbuffer");
#endif
  if(rbf == NULL)
    return NULL;
  
  return NULL;
}
