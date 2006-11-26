# -------------------------------------
#
#   Makefile for DreaMon
#
# -------------------------------------

all: bootlogos ../$(ODIR)dreamon.bin


OBJ = area.src\
 cmd_range.src\
 com_lib.src\
 com_lib_vdc25.src\
 com_lib_vic.src\
 dreamon.src\
 dump.src\
 fkeys.src\
 fkey_defs.src\
 fpoint.src\
 file_lib.src\
 file_lib_iec.src\
 get_num.src\
 keyb.src\
 long_lib.src\
 mapping.src\
 message_texts.src\
 messages.src\
 opcodes.src\
 out_buf.src\
 prefs.src\
 regs.src\
 sub_zero.src


HEAD = area.hx\
 cmd_range.hx\
 com_lib.hx\
 dreamon.hx\
 fkeys.hx\
 fpoint.hx\
 file_lib.hx\
 get_num.hx\
 keyb.hx\
 keys.hx\
 long_lib.hx\
 mapping.hx\
 messages.hx\
 message_macros.hx\
 opcodes.hx\
 out_buf.hx\
 sub_zero.hx\
 ../version.hx

RAW = charset8x6.src\
 fun_screen.src\
 bootlogo/bootlogo.src\
 bootlogo/resetmenu.src

#--------------------------------------

../$(ODIR)dreamon.bin: $(OBJ) $(HEAD) $(RAW)
	$(DA) $(DAOPTS) -I.. -Ibootlogo -l dreamon.lab -d dreamon.html -o ../$(ODIR)dreamon.bin dreamon.src

charset8x6.src: charset8x6.raw
	../$(DATAMAKE) -o charset8x6.src charset8x6.raw

fun_screen.src: fun_screen.bin
	../$(DATAMAKE) -o fun_screen.src fun_screen.bin

bootlogos:
	$(MAKE) -C bootlogo all

#--------------------------------------

clean:
	rm -f ../$(ODIR)dreamon.bin dreamon.lab charset8x6.src fun_screen.src
	$(MAKE) -C bootlogo clean


