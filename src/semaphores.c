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
#include <semaphore.h>
#include "semaphores.h"

int sem_create(sem_t *sem, int *shared, unsigned int *value)
{
  sem=sem;
  shared=shared;
  value=value;
  //  int *sem_fd;
  //  *sem_fd = open(SEM_KEY_FILE, O_WRONLY | O_TRUNC | O_EXCL | O_CREAT, 0644);
  //  if(*sem_fd < 0)
  //    {
      
  //    }
  return -1;
}

const char* sem_getname(void)
{
  static int semcnt=0;
  uid_t id = getuid();
  char buffer[256];
  sprintf(buffer, "/sem_%d", 1000*id+(semcnt++));
  return strdup(buffer);
}
