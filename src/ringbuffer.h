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
#include <semaphore.h>
#include "semaphores.h"

typedef struct _ringbuffer
{
  const char *shmname;
  int* const buffer; /* File pointer zu shm */
  int head;          /* Administrative ringbuffer sachen */
  int tail;
  const size_t max_length;
  semaphore *sem_shm;
  //  semaphore *sem_buffer;
  semaphore *sem_buffer_readable;
  semaphore *sem_buffer_writeable;
} ringbuffer;

ringbuffer* rbf_init(size_t);
ringbuffer* rbf_destroy(ringbuffer*);
int rbf_write(ringbuffer*,uint8_t);
int rbf_read(ringbuffer*,uint8_t*);
int rbf_is_full(ringbuffer*);
int rbf_is_empty(ringbuffer*);
int rbf_is_active(ringbuffer *);
#endif /* ringbuffer.h */
