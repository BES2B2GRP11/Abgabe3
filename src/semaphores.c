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

//sem_t* sem_create(sem_t *l,int shared, unsigned int value)
sem_t* sem_create(void)
{
  return sem_open(sem_getname(), O_CREAT|O_RDWR,S_IRUSR|S_IWUSR, 2);

  return NULL;
}

const char* sem_getname(void)
{
  static int semcnt=0;
  uid_t id = getuid();
  char buffer[256];
  sprintf(buffer, "/sem_%d", 1000*id+(semcnt++));
  return strdup(buffer);
}
