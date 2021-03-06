/*
 * =====================================================================================
 *
 *       Filename:  empfaenger.c
 *
 *    Description:  empfaenger fuer Ringbuffer Broadcast-Nachrichten via /dev/shm
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
#include <error.h>
#include <errno.h>
#include <string.h>
#include "sender.h"
#include "ringbuffer.h"
#include "error_handling.h"

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

static ringbuffer *rbf;

int main(int argc, char** argv)
{
  atexit(cleanup);
  rbf = NULL;
  size_t ringbuf_elmnts=0; //size_t mit strtol hat ein ende 
  int c=0;
  char i;
  
  while((c = getopt (argc, argv, "hm:")) != -1)
    {
      switch (c)
	{
	case 'h':
	  print_help();
	  return EXIT_SUCCESS;
	case 'm':
	  /* echt .... ....... .... ... ...... */
	  if(!strncmp(optarg,"-",1))
	    {
	      print_help();
	      errno=EINVAL;
	      handle_error(FATAL,"Unknown option %s",argv);
	      exit(errno);
	    }
	  ringbuf_elmnts=strtol(optarg,NULL,10);
	  break;
	default:
	  print_help();
	  errno=EINVAL;
	  handle_error(FATAL,"Unknown option %s",argv);
	}
    }

  if(ringbuf_elmnts <= 0 || ringbuf_elmnts >=  ((size_t)-1))
    {
      print_help();
      exit(EINVAL);
    }

  rbf=rbf_init(ringbuf_elmnts);
#ifdef DEBUG
  DBG("Got a ringbuffer with max_length %ld",rbf->max_length);
#endif
  
  do
    {
      rbf_read(rbf,&i);
      fputc(i,stdout);
    } while (i != EOF);

#ifdef DEBUG
  DBG("Got EOF... cleaning up");
#endif
  
  return EXIT_SUCCESS;
}

void print_help(void)
{
  fputs(help_message,stderr);
  fflush(stdout);
}

void cleanup()
{
  /* cleanup fuer den ringbuffer */
  if(rbf != NULL && rbf_is_empty(rbf) == 1)
    rbf_destroy(rbf);  
}
