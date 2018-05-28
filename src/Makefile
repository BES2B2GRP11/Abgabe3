#
# =====================================================================================
#
#       Filename:  Makefile
#
#    Description:  Actual makefile for the sources
#
#        Version:  1.0.0
#        Created:  04/30/2018 10:20:05 AM
#       Revision:  none
#       Compiler:  gcc52
#
#         Author:  Ovidiu - Dan Bogat [ic17b501], ic17b501@technikum-wien.at
# =====================================================================================
#
# DOXYGEN
#
##
## @file Makefile
## Eigentliches Makefile fuer die sources
## Beispiel 3
##
## @author Ovidiu - Dan Bogat [ic17b501]
## @date 2018/04/30
##
## @version $Revision: 1.0.0$
##
## @todo
##
## Last Modified: $Author: Ovidiu $
##
##
CC=gcc52
SOURCES=sender.c empfaenger.c ringbuffer.c
DEPS=sender.h empfaenger.h 
OBJECTS=sender.o empfaenger.o 
CFLAGS=-DDEBUG -Wall -pedantic -Werror -Wextra -Wstrict-prototypes -Wformat=2 -fno-common -ftrapv -g -O3 -std=gnu11 -static -fbuiltin
LIBS=-lringbuffer -lsharedmem -lsemaphores -lerrorhandling -Wl,--whole-archive -lrt -lpthread -Wl,--no-whole-archive
LDFLAGS=-L. $(LIBS)


all: sender empfaenger

s: sender

e: empfaenger

sender: sender.c sender.h libringbuffer.a libsharedmem.a libsemaphores.a liberrorhandling.a
	$(CC) $(CFLAGS) -o $@ $< $(LDFLAGS)

empfaenger: empfaenger.c empfaenger.h libringbuffer.a libsharedmem.a libsemaphores.a liberrorhandling.a
	$(CC) $(CFLAGS) -o $@ $< $(LDFLAGS)

%.a: %.o
	ar rcs $@ $^

libringbuffer.o: ringbuffer.c ringbuffer.h 
	$(CC) $(CFLAGS) -c -o $@ $<

libsharedmem.o: sharedmem.c sharedmem.h 
	$(CC) $(CFLAGS) -c -o $@ $< -lrt -lpthread

libsemaphores.o: semaphores.c semaphores.h
	$(CC) $(CFLAGS) -c -o $@ $<

liberrorhandling.o: error_handling.c error_handling.h
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	$(RM) *.a *.o *~ sender empfaenger

.PHONY: clean 

