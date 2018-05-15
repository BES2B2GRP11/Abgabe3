/*
 * =====================================================================================
 *
 *       Filename:  sharedmem.c
 *
 *    Description:  Handlig fuer /dev/shm 
 *
 *        Version:  1.0.0
 *        Created:  04/30/2018 10:20:05 AM
 *       Revision:  none
 *       Compiler:  gcc52
 *
 *         Author:  Ovidiu - Dan Bogat [ic17b501], ic17b501@technikum-wien.at
 * =====================================================================================
 */
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include "sharedmem.h"

int create_shm(void)
{
  
  return -1;
}

const char* shm_getname(void)
{
  static int shmcnt=0;
  uid_t id = getuid();
  char buffer[256];
  sprintf(buffer, "shm_%d", 1000*id+(shmcnt++));
  return strdup(buffer);
}
