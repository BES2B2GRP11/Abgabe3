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
#include "empfaenger.h"
#include "ringbuffer.h"

int main(int argc, char** argv)
{
  argc=argc;
  argv=argv;
  int c;
  
  while((c = getopt(argc, argv, "h")) != -1)
  {
    switch (c)
    {
      case 'h':
        print_help();
        return EXIT_SUCCESS;
      default:
        return EXIT_FAILURE;
    }
    
  }

  return EXIT_SUCCESS;
}

void print_help(void)
{
  puts(help_message);
  fflush(stdout);
}
