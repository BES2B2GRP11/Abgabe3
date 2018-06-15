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
#include <errno.h>
#include <error.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "sharedmem.h"
#include "ringbuffer.h"
#include "error_handling.h"

static char *shm = NULL; /* Die start Adresse des Buffers */

ringbuffer* rbf_init(size_t n)
{
  ringbuffer *p;
  const char *name = NULL;
#ifdef DEBUG
  DBG("Creating a buffer with size %ld",++n);
#endif

  name = shm_getname();
  ringbuffer local = {
    /* shm_reate()... wir erstellen das file nur */
    /* wir verwenden den fd dann im jeweiligen programm fuer shmat */
    /* um es in den jeweiligen adressbereich zu kopieren */
    .shmname = name,
    .buffer = shm_create(n, (char*) name),
    .head = 0,
    .tail = 0,
    .max_length = n /* shm datei wurde bereits getrunated auf n */
  };

  if (local.buffer == NULL)
    {
#ifdef DEBUG
      DBG("Buffer is null...");
#endif
      return NULL;
    }
  
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
  /* wenn kein prozess mehr im geschuetzten bereich (counting semaphore) */
  /* shm_unlink rbf->buffer */
  
#ifdef DEBUG
  DBG("Deconstructing ringbuffer");
#endif
  if(shm != NULL)
    {
      munmap(shm,rbf->max_length);
      shm=NULL;
    }

#ifdef DEBUG
  DBG("Unlinking %s",rbf->shmname);
#endif
  shm_unlink(rbf->shmname);
  
  if(rbf == NULL)
    return NULL;
  
  return NULL;
}

int rbf_write(ringbuffer *rbf, uint8_t data)
{

#ifdef DEBUG
  DBG("Inserting %c into ringbuffer @ %ld",data, rbf->head);
#endif
  
  //semaphore hier her
  if(rbf_is_full(rbf))
    return -1; /* hier warten */
  
  /* wir mappen es nur beim ersten Aufruf */
  if(shm == NULL)
    {
      shm = (char*) mmap(NULL,rbf->max_length,PROT_READ|PROT_WRITE, MAP_SHARED, *rbf->buffer,0);
    }  

#ifdef DEBUG
  DBG("rbf->buffer is located at %p",rbf->buffer);
  DBG("shm is located at %p",shm);
  DBG("writing to is located at %p",shm+rbf->head);
#endif
  
  *(shm+rbf->head) = data;

#ifdef DEBUG
  fprintf(stdout,"Wrote %c\n", *(shm+rbf->head));
#endif

  if(++rbf->head >= (signed int)rbf->max_length)
      rbf->head = 0;

  return 0;
}

int rbf_is_full(ringbuffer *rbf)
{
  if(rbf->head+1 == rbf->tail)
    return 1;
  return 0;
}

int rbf_is_empty(ringbuffer *rbf)
{
  if(rbf->head == rbf->tail)
    return 1;
  return 0;
}

