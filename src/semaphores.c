/*
 * =====================================================================================
 *
 *       Filename:  semaphroe.c
 *
 *    Description:  Handling der Semaphore
 *
 *        Version:  1.0.0
 *        Created:  04/30/2018 10:20:05 AM
 *       Revision:  none
 *       Compiler:  gcc52
 *
 *         Author:  Ovidiu - Dan Bogat [ic17b501], ic17b501@technikum-wien.at
 * =====================================================================================
 */
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <sys/stat.h>        /* mode Konstanten */
#include <fcntl.h>           /* O_* Konstanten (O_CREAT) */
#include <semaphore.h>
#include "semaphores.h"
#include "error_handling.h"

//sem_t* sem_create(sem_t *l,int shared, unsigned int value)
semaphore* sem_create(const char *name, size_t value)
{
  semaphore *s;

#ifdef DEBUG
  DBG("Creating/Opening requested semaphore with name %s and size %ld", name, value);
#endif
  
  semaphore local =
    {
      .sem_name = name,
      .sem = sem_open(
		     name,
		     O_CREAT|O_RDWR,
		     S_IRUSR|S_IWUSR,
		     (int)value
		      ),
      .max_value = value
    };

  s = malloc(sizeof(semaphore));

  if(s == NULL)
    {
      handle_error(FATAL, "malloc for semaphore");
      return NULL;
    }

  memcpy(s,&local,sizeof(semaphore));
  
  return s;
}

const char* sem_getname(void)
{
  static int semcnt=0;
  uid_t id = getuid();
  char buffer[256];
  sprintf(buffer, "/sem_%d", 1000*id+(semcnt++));
  return strdup(buffer);
}

size_t sem_val(semaphore *s)
{
  int val=0;
  if(sem_getvalue(s->sem,&val) != 0)
    handle_error(WARN,"Getting semaphore value");
 
  return (size_t)val;
}

int sem_del(semaphore *s)
{

  if(s == NULL || sem_val(s) < s->max_value)
    {
#ifdef DEBUG
    DBG("Nothing to do, someone is still using the sem buffer with sem_shm at %d", sem_val(s));
#endif
    return 0;
    }
  
  if(s != NULL && sem_val(s) < s->max_value)
    {
#ifdef DEBUG
      DBG("Got sem semaphore value %ld", sem_val(s));
      DBG("Setting sem semaphore up");
#endif
      sem_post(s->sem);
#ifdef DEBUG
      DBG("Got sem semaphore value %ld", sem_val(s));
#endif
    }

#ifdef DEBUG
  DBG("unlinking semaphore %s",s->sem_name);
#endif

  if(sem_val(s) >= s->max_value)
    sem_unlink(s->sem_name);
  return 0;
}
