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
SOURCES=sender.c empfaenger.c
DEPS=sender.h empfaenger.h
OBJECTS=sender.o empfaenger.o
CFLAGS=-DDEBUG -Wall -pedantic -Werror -Wextra -Wstrict-prototypes -Wformat=2 -fno-common -ftrapv -g -O3 -std=gnu11 -static

%.o: %.c $(DEPS)
		$(CC) $(CPPFLAGS) $(CFLAGS) -c $<

all: sender empfaenger

clean:
		$(RM) *.{a,o} *~ sender empfaenger

.PHONY: clean

