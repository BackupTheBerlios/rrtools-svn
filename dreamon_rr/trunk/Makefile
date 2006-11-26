#--------------------------------------
#
# Makefile for DreaMon
#
#--------------------------------------

# name and path of DreamAss
export DA = dreamass

# c compiler
export CC = gcc

# c++ compiler
export CPP = g++

export DATAMAKE = tools/datamake

#--------------------------------------
# End of Config
# nothing needs to be changed below
#--------------------------------------

#all: AllTools AllDreaMon AllDocs
#all: AllTools AllDreaMon
all: AllDreaMon

#--------------------------------------

export DAOPTS = -v

export DDIR = dreamon/
export ODIR = obj/
export TDIR = tools/
export DocDir = doc/
export ArcDir = /home/baccy/BackUp/

#--------------------------------------

AllTools:
	$(MAKE) -C $(TDIR) all

AllDreaMon: AllTools
	$(MAKE) -C $(DDIR) all

AllDocs:
	$(MAKE) -C $(DocDir) all

#--------------------------------------

clean:
	$(MAKE) -C $(DDIR) clean
	$(MAKE) -C $(TDIR) clean
#	$(MAKE) -C $(IDIR) clean
#	$(MAKE) -C $(DocDir) clean

#--------------------------------------

DAT := $(shell date +%Y%m%d)

backup:
	tar cfvj $(ArcDir)DreaMonAll$(DAT).tar.bz2 *
	rm -f $(ArcDir)DreaMonObj$(DAT).zip
	zip -j9 $(ArcDir)DreaMonObj$(DAT).zip obj/DreaMon.bin

#--------------------------------------
