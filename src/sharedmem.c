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

int *shm_create(size_t n, char *name)
{
  int *shm_fd;
  shm_fd = malloc(sizeof(int));
  if(shm_fd == NULL)
    {
      return NULL;
    }

  /* shm_open und wir leben POSIX anstatt shmget */
  /* Aus SysV  --> shmget gefolgt von shmat  <-- arbeitet mit keys */
  /* POSIX FTW --> shm_open gefolgt von mmap <-- arbeitet mit file-descriptors */
  *shm_fd = shm_open(
		     name,
		     O_CREAT | O_RDWR, //man shm_open
		     0666
		     );

  if (*shm_fd == -1 || shm_fd == NULL) {
    fprintf(stderr,"[Error] %s\n", strerror(errno));
    exit(1);
  }

  ftruncate(*shm_fd, n);
  
  return shm_fd;
}

/* \brief Retourniert den naechsten Namen
 * 
 * \author Ovidiu - Dan Bogat
 */
const char* shm_getname(void)
{
  static int shmcnt=0;
  uid_t id = getuid();
  char buffer[256];
  sprintf(buffer, "/shm_%d", 1000*id+(shmcnt++));
  return strdup(buffer);
}

int shm_close(int *fd)
{
  if(fd != NULL)
    {
      puts("cleaning");
      close(*fd);
      return 0;
    }
  return 0;
}
