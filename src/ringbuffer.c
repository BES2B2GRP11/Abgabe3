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
#include <semaphore.h>
#include "sharedmem.h"
#include "semaphores.h"
#include "ringbuffer.h"
#include "error_handling.h"

static char *shm = NULL; /* Die start Adresse des Buffers */

ringbuffer* rbf_init(size_t n)
{
  ringbuffer *p;
  const char *name = NULL;
  const char *sem_shm_name = NULL;
  //  const char *sem_buffer_name = NULL;
  const char *sem_buffer_readable_name = NULL;
  const char *sem_buffer_writeable_name = NULL;
  ++n;
#ifdef DEBUG
  DBG("Creating a buffer with a requested size %ld",n);
#endif

  name = shm_getname();
  sem_shm_name = sem_getname();
  //  sem_buffer_name = sem_getname();
  sem_buffer_readable_name = sem_getname();
  sem_buffer_writeable_name = sem_getname();
  ringbuffer local = {
    /* shm_reate()... wir erstellen das file nur */
    /* wir verwenden den fd dann im jeweiligen programm fuer shmat */
    /* um es in den jeweiligen adressbereich zu kopieren */
    .shmname = name,
    .buffer = shm_create(n, (char*) name),
    .head = 0,
    .tail = 0,
    .max_length = n, /* shm datei wurde bereits getrunated auf n */
    .sem_shm = sem_create(sem_shm_name, 2),
    //.sem_buffer = sem_create(sem_buffer_name, 1),
    .sem_buffer_readable = sem_create(sem_buffer_readable_name, 1),
    .sem_buffer_writeable = sem_create(sem_buffer_writeable_name, 1)
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

#ifdef DEBUG
  DBG("shm              semaphore initialized at %ld",sem_val(local.sem_shm));
  //  DBG("buffer           semaphore initialized at %ld",sem_val(local.sem_buffer));
  DBG("buffer readable  semaphore initialized at %ld",sem_val(local.sem_buffer_readable));
  DBG("buffer readable  semaphore initialized at %ld",sem_val(local.sem_buffer_writeable));
#endif
  
  memcpy(p,&local,sizeof(ringbuffer));
  
  return p;
}

ringbuffer* rbf_destroy(ringbuffer *rbf)
{
  sem_del(rbf->sem_shm);
  //  sem_del(rbf->sem_buffer);
  sem_del(rbf->sem_buffer_readable);
  sem_del(rbf->sem_buffer_writeable);
  
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

int rbf_write(ringbuffer *rbf, char data)
{
  if(rbf == NULL)
    return -1;
  //#ifdef DEBUG
  //  DBG("Inserting %c into ringbuffer @ %ld",data, rbf->head);
  //#endif

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

  if(rbf_is_full(rbf) == 1)
    {
      if(sem_val(rbf->sem_buffer_readable) != rbf->sem_buffer_readable->max_value)
	sem_post(rbf->sem_buffer_readable->sem);
      
      sem_wait(rbf->sem_buffer_writeable->sem);
    }
  
  *(shm+rbf->head) = data;

  //#ifdef DEBUG
  //  fprintf(stdout,"Wrote %c\n", *(shm+rbf->head));
  //#endif

  if(++rbf->head >= (signed int)rbf->max_length)
      rbf->head = 0;


  if(sem_val(rbf->sem_buffer_readable) != rbf->sem_buffer_readable->max_value)
    sem_post(rbf->sem_buffer_readable->sem);

  fputc(data,stdout);
  
  return 0;
}

int rbf_read(ringbuffer *rbf, char *data)
{
  if(rbf == NULL)
    return -1; /* error handling missing */
  
  /* wir mappen es nur beim ersten Aufruf */
  if(shm == NULL)
    {
      shm = (char*) mmap(NULL,rbf->max_length,PROT_READ|PROT_WRITE, MAP_SHARED, *rbf->buffer,0);
    }  
  
  if(rbf_is_empty(rbf) == 1)
    {
      if(sem_val(rbf->sem_buffer_writeable) != rbf->sem_buffer_writeable->max_value)
	sem_post(rbf->sem_buffer_writeable->sem);
      
      sem_wait(rbf->sem_buffer_readable->sem);
    }
  
  *data = *(shm+rbf->tail); // Read data and then move

  //#ifdef DEBUG
  //  fprintf(stdout,"read %c\n", *data);
  //#endif

  if(++rbf->tail >= (signed int)rbf->max_length)
      rbf->tail = 0;

  if(sem_val(rbf->sem_buffer_writeable) != rbf->sem_buffer_writeable->max_value)
    sem_post(rbf->sem_buffer_writeable->sem);

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
  if(sem_val(rbf->sem_buffer_readable) == rbf->sem_buffer_readable->max_value)
    return 1;
     
  if(rbf->head == rbf->tail)
    return 1;
  
  return 0;
}

int rbf_is_active(ringbuffer *rbf)
{
  /* define einige parameter im header fuer die 2 hier */
  if(sem_val(rbf->sem_shm) < rbf->sem_shm->max_value)
    return 1;

  return 0;
}
