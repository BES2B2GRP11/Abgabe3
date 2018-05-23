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
#include <sys/mman.h>
#include <sys/stat.h>        /* mode Konstanten */
#include <fcntl.h>           /* O_* Konstanten (O_CREAT) */
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <error.h>
#include <errno.h>
#include "sharedmem.h"

/* static const char  shm_mount[] = SHM_MOUNT; */

/* const char *__shm_directory(size_t *len) */
/* { */
/*   if (len) */
/*     *len = strlen(shm_mount); */
/*   return shm_mount; */
/* } */

int* shm_create(void)
{
  int *shm_fd;

  shm_fd = malloc(sizeof(int));
  if(!shm_fd)
    {
      return NULL;
    }
  
  *shm_fd = shm_open(shm_getname(), O_CREAT | O_EXCL | O_RDWR, 0666);

  if (*shm_fd == -1 || shm_fd == NULL) {
    printf("prod: Shared memory failed: %s\n", strerror(errno));
    exit(1);
  }
  
  return shm_fd;
}

const char* shm_getname(void)
{
  static int shmcnt=0;
  uid_t id = getuid();
  char buffer[256];
  sprintf(buffer, "/shm_%d", 1000*id+(shmcnt++));
  return strdup(buffer);
}
