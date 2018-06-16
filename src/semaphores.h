/*
 * =====================================================================================
 *
 *       Filename:  semaphores.h
 *
 *    Description:  Header fuer semaphroe handling
 *
 *        Version:  1.0.0
 *        Created:  04/30/2018 10:20:05 AM
 *       Revision:  none
 *       Compiler:  gcc52
 *
 *         Author:  Ovidiu - Dan Bogat [ic17b501], ic17b501@technikum-wien.at
 * =====================================================================================
 */
#ifndef __semaphores_h
#define __semaphores_h
#include <stdlib.h>
#include <semaphore.h>

typedef struct _semaphore
{
  const char *sem_name;
  sem_t *sem;
  const size_t max_value;
} semaphore;

semaphore* sem_create(const char*, size_t);
const char* sem_getname(void);
size_t sem_val(semaphore *);
int sem_del(semaphore *);

#endif /* semaphores.h */
