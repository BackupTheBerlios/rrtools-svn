# Makefile for the unix tools for IEC-ATA
# Asbjørn Djupdal 2002

CC = gcc

CFLAGS = -Wall -O -DUNIX
LDFLAGS = -Wall

OBJECTS = unix.o

iecata : $(OBJECTS) Makefile
	$(CC) $(LDFLAGS) -o $@ $(OBJECTS)

unix.o : unix.c ../dos-init.c ../dos-dir.c ../dos-file.c ../iecata.h Makefile
	$(CC) $(CFLAGS) -c $<

.PHONY : clean
clean :
	rm -rf *.hex *.out *.o *.map iecata
