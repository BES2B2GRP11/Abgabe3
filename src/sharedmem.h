/*
 * =====================================================================================
 *
 *       Filename:  sharedmem.h
 *
 *    Description:  Header fuer /dev/shm handling
 *
 *        Version:  1.0.0
 *        Created:  04/30/2018 10:20:05 AM
 *       Revision:  none
 *       Compiler:  gcc52
 *
 *         Author:  Ovidiu - Dan Bogat [ic17b501], ic17b501@technikum-wien.at
 * =====================================================================================
 */
#ifndef __sharedmem_h
#define __sharedmem_h
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

//int shm_create(const char *, int *, mode_t *);
int shm_create(void);
const char* shm_getname(void);

#endif /* sharedmem.h */
