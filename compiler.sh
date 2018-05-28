#!/bin/bash

if [[ "$(hostname)" =~ ^annuminas.technikum-wien.at$ ]];
then
	sed -i -e 's/^CC\=gcc$/CC\=gcc52/g' Makefile src/Makefile
else
	sed -i -e 's/^CC\=gcc52$/CC\=gcc/g' Makefile src/Makefile
fi

printf "CC set accordingly\n"
