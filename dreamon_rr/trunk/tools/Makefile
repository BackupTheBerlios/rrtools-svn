#--------------------------------------
#
# Makefile for DataMake
#
#--------------------------------------

# c compiler
export CC = gcc

# Options for c compiler
export CFLAGS = -Wall -O3

#--------------------------------------
# End of Config
# nothing needs to be changed below
#--------------------------------------

.PHONY: all clean backup

all: datamake

#--------------------------------------

datamake: datamake.c
	$(CC) $(CFLAGS) -o $@ $<

#--------------------------------------

clean:
	rm -f datamake

#--------------------------------------

DAT := $(shell date +%Y%m%d)

backup:
	tar cfvj $(ArcDir)datamake$(DAT).tar.bz2 *

#--------------------------------------

