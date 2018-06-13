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


//https://stackoverflow.com/questions/47905554/segmentation-fault-appears-when-i-use-shared-memory-only-from-statically-build-p
//#ifndef  SHM_MOUNT
//#define  SHM_MOUNT "/dev/shm/"
//#endif

//const char *__shm_directory(size_t *len);
int shm_create(void);
const char* shm_getname(void);
int shm_close(int*);

#endif /* sharedmem.h */
