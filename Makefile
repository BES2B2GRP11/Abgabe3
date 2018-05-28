#
# =====================================================================================
#
#       Filename:  Makefile
#
#    Description:  Top-Level Makefile
#
#        Version:  1.0.0
#        Created:  04/10/2018 09:40:05 AM
#       Revision:  none
#
#         Author:  Ovidiu - Dan Bogat [ic17b501], ic17b501@technikum-wien.at
# =====================================================================================
#
# DOXYGEN
##
## @file Makefile
## Betriebssysteme Broadcast-Nachrichten via /dev/shm
## Abgabe 3
##
## @author Ovidiu - Dan Bogat [ic17b501]
## @date 2018/04/30
##
## @version $Revision: 1.0.0$
##
## @todo Nothing much
##
## Last Modified: $Author: Ovidiu $
##
##

CC=gcc
SUBDIRS=src
RM=-rm -rf
CFLAGS=-Wall -pedantic -Werror -Wextra -Wstrict-prototypes -Wformat=2 -fno-common -ftrapv -g -O3 -std=gnu89
SRC_DIR=src
EXAMPLE_DIR=examples
DOC_DIR=doc
TEST_DIR=test
DIST_DIR=bes2_grp11
DISTNAME="$(DIST_DIR).zip"
TARBALL=$(DIST_DIR).tar.bz2
TAR=tar -cvjf
ZIP=zip -r

all: clean $(SUBDIRS)
	$(MAKE) -C src

clean:
	$(MAKE) $@ -C src
	$(RM) $(DOC_DIR)

test: clean all

dist-check:
	mkdir check-$(DIST_DIR)
	cp -r $(SRC_DIR)/mypopen.{c,h} Makefile check-$(DIST_DIR)
	m4 templates/Makefile.m4 > check-$(DIST_DIR)/Makefile
	m4 templates/doxygen.m4 > check-$(DIST_DIR)/doxygen.dcf
	cd check-$(DIST_DIR) && make test && make doc && make clean
	rm -rf check-$(DIST_DIR)

dist: distclean dist-check
	mkdir $(DIST_DIR)
	cp -r $(SRC_DIR)/mypopen.{c,h} doxygen.dcf Makefile $(DIST_DIR)
	m4 templates/Makefile.m4 > $(DIST_DIR)/Makefile
	m4 templates/doxygen.m4 > $(DIST_DIR)/doxygen.dcf
	$(ZIP) $(DISTNAME) $(DIST_DIR) 1> /dev/null &&\
		$(RM) -rf $(DIST_DIR) || echo "Could not create the tarball $(DISTNAME)"
	@echo "Dist is ready to ship @ $(DISTNAME)"

distclean: clean
	$(RM) -rf $(DOC_DIR) $(DIST_DIR) $(DISTNAME) check-$(DIST_DIR) $(TARBALL)

doxy dox doc: $(SUBDIRS)
	doxygen doxygen.dcf 1> /dev/null

.PHONY: all clean distclean dist
