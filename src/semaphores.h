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

//int sem_create(sem_t*,int, unsigned int);
sem_t* sem_create(void);
const char* sem_getname(void);

#endif /* semaphores.h */
