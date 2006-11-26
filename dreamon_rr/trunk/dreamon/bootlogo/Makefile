# -------------------------------------
#
#   Makefile for the bootlogo
#
# -------------------------------------

all: bootlogo.src resetmenu.src

CFLAGS = -Wall

#--------------------------------------

compress_logo: compress_logo.c
	$(CC) $(CFLAGS) -o compress_logo compress_logo.c

compress_menu: compress_menu.c
	$(CC) $(CFLAGS) -o compress_menu compress_menu.c


bootlogo.src: compress_logo bootlogo_scr.bin bootlogo_col.bin
	./compress_logo bootlogo_scr.bin bootlogo_col.bin bootlogo.src

resetmenu.src: compress_menu resetmenu.bin
	./compress_menu resetmenu.bin 6 8 33 20 resetmenu.src

#--------------------------------------

clean:
	rm -f compress_logo compress_menu
	rm -f bootlogo.src resetmenu.src

#--------------------------------------

