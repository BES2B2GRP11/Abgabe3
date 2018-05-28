/*
 * =====================================================================================
 *
 *       Filename:  sender.c
 *
 *    Description:  sender fuer Ringbuffer Broadcast-Nachrichten via /dev/shm
 *
 *        Version:  1.0.0
 *        Created:  04/30/2018 10:20:05 AM
 *       Revision:  none
 *       Compiler:  gcc52
 *
 *         Author:  Ovidiu - Dan Bogat [ic17b501], ic17b501@technikum-wien.at
 * =====================================================================================
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "sender.h"
#include "ringbuffer.h"
#include "sharedmem.h"
#include "semaphores.h"

/*                          +----------------------------------------------------------------------------------+ */
/*                          |  [Datei mit n fixen Bloecken in /dev/shm als circular-linked-list] == ringbuffer | */
/*                          |  Ist fuer beide Programme gleich /dev/shm/shm_{1000*uid+0}                       | */
/*                          |                                                                                  | */
/*                          |       1      2      3      4      5      6                                   n   | */
/*                          |     +---+  +---+  +---+  +---+  +---+  +---+                               +---+ | */
/*                          |     |   |  |   |  |   |  |   |  |   |  |   |                               |   | | */
/*                          +---> |   +> |   +> |   +> |   +> |   +> |   +--------> . . . . . . . +----> |   +-+ */
/*                                +-+-+  +-+-+  +-+-+  +-+-+  +-+-+  +-+-+                               +-+-+ */
/*                                  ^      ^      ^      ^      ^      ^                                   ^ */
/*                                  |      |      |      |      |      |                                   | */
/*                                  |      |      |      |      |      |                                   | */
/*                                  +      +      +      +      +      +                                   + */
/*                                  p      p      p      p      p      p                                   p */

/*                                +----------------------------------------------------------+------------------+ */
/*                                |                                                          |                  | */
/*                                |  [Datei mit n fixen blöcken]+>/dev/shm/shm_{1000*uid+j}  |  /dev/shm @ RAM  | */
/*                                |                                                          |                  | */
/*                                +------------+-+-------------------------------------------+------------------+ */
/*                                             ^ ^ */
/*                                             | | */
/* +-----------------------------+             | |                                  +------------------------------+ */
/* |   Sender                    |             | |                                  |                    Empfaenger| */
/* +-----------------------------+             | |                                  +------------------------------+ */
/* |                             |             | |                                  |                              | */
/* | int fd = /dev/shm/shm_...   |             | |                                  |  int fd = /dev/shm/shm_...   | */
/* |                             +-------------+ +----------------------------------+                              | */
/* | Complex+Semaphore+up()      |                                                  |  Complex+Semaphore+up()      | */
/* |                             | Alle Arbeiten mit den gleichen Dateien.          |                              | */
/* | write to ringbuffer@dev/shm | Bei uns macht es die Reihenfolge:                |  read from ringbuffer@dev/shm| */
/* |                             |                                                  |                              | */
/* | Complex+Semaphore+down()    | /dev/shm_{1000*uid+j} -> j = 0 ==> ringbuffer    |  Complex+Semaphore+down()    | */
/* |                             |                                                  |                              | */
/* | atexit(cleanup)             | Fuer Semaphore:                                  |  atexit(cleanup)             | */
/* +-----------------------------+ /dev/sem_{1000*uid+j} -> j = 0 --> complex-sem.  +------------------------------+ */
/*                                 /dev/sem_{1000*uid+j} -> j = 1 --> ring buffer sem */

/*                                 Der Complex-Semaphore gibt an, wie viele threads */
/*                                 bzw. Prozesse sich in der geschuetzten Region befinden. */
/*                                 Diese wird ausgewertet beim Abbau und Loeschen des Buffers: */
/*                                 Empfaenger ist der letzte, der noch mit dem buffer arbeitet, */
/*                                 somit kann er nach dem letzten auslesen auch geloescht werden. */

/*                                 Der Ring buffer Semaphore wird verwendet um das Lesen und Schreiben */
/*                                 in dem Ringbuffer zu Synchronisieren. */



int main(int argc, char** argv)
{
  long ringbuf_elmnts=0;
  int c=0;

  while((c = getopt (argc, argv, "hm:l:")) != -1)
    {
      switch (c)
	{
	case 'h':
	  print_help();
	  return EXIT_SUCCESS;
	case 'm':
	  ringbuf_elmnts=strtol(optarg,NULL,10);
	  break;
	default:
	  return EXIT_FAILURE;
	}
    }

  ringbuf_elmnts=ringbuf_elmnts; // DELETE THIS LINE

  
  int *shm_fd = shm_create();
  
  shm_fd=shm_fd;

  
  return EXIT_SUCCESS;
}

void print_help(void)
{
  puts(help_message);
  fflush(stdout);
}
