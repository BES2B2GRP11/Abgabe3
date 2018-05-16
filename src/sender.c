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

int main(int argc, char** argv)
{
  long ringbuf_elmnts=0;
  ringbuf_elmnts=ringbuf_elmnts;
  int c=0;
  
  while((c = getopt (argc, argv, "hm:")) != -1)
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

  shm_create();

  
  return EXIT_SUCCESS;
}

void print_help(void)
{
  puts(help_message);
  fflush(stdout);
}
