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
#include "ringbuffer.h"

ringbuffer *create_ringbuffer(int size)
{
  size=size;
  ringbuffer *r = malloc(sizeof(ringbuffer));
  if(r == NULL)
    {
      fprintf(stderr,"[Error] ringbuffer");
      return NULL;
    }
  
  return r;
}
			   
