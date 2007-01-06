

DA = dreamass

EXO = exomizer

# directory for backup
export ArcDir = /home/baccy/BackUp/

# mmc64_plugin source directory
export MMC64_PLUGIN_SRC = ../..

# mylene source directory
export MYLENE_SRC = ../..

# dload source directory
export DLOAD_SRC = ../..

#--------------------------------------

.PHONY: all backup clean distrib install

all: dfiplgin.bin dfitest.d64 dfiplgin_debug.bin
#all: dfiplgin.bin

#--------------------------------------

DFI_FS_SRC_ALL =	dfi_fs_bam.src \
			dfi_fs_bank0.src \
			dfi_fs_bank1.src \
			dfi_fs_bank2.src \
			dfi_fs_bank_jsr.src \
			dfi_fs_cmd.src \
			dfi_fs_debug.src \
			dfi_fs_dir.src \
			dfi_fs_error.src \
			dfi_fs_mmc64.src \
			dfi_fs_reu.src \
			dfi_fs_rom.src \
			dfi_fs_switcher.src

DFI_FS_SRC_RELEASE =	dfi_fs.src \
			dfi_fs_switcher.src

DFI_FS_SRC_DEBUG =	dfi_fs_debug.src \
			dfi_fs_switcher_debug.src

PLGIN_SRC =		actions.src \
			browser.src \
			mylene_dfi.src \
			$(MMC64_PLUGIN_SRC)/mmc64_plugin/mmc64_plugin.src \
			$(MYLENE_SRC)/mylene/com_lib.src \
			$(MYLENE_SRC)/mylene/entry.src \
			$(MYLENE_SRC)/mylene/levels.src \
			$(MYLENE_SRC)/mylene/mylene.src \
			$(DLOAD_SRC)/dload/mmcparam.src

PLGIN_HEADERS =		$(MYLENE_SRC)/mylene/entry.h \
			$(MYLENE_SRC)/mylene/mylene.h


banks.bin banks.lab: $(DFI_FS_SRC_ALL) $(DFI_FS_SRC_RELEASE)
	$(DA) -v -d banks.html -l banks.lab -o $@ dfi_fs.src

banks_debug.bin banks_debug.lab: $(DFI_FS_SRC_ALL) $(DFI_FS_SRC_DEBUG)
	$(DA) -v -d banks_debug.html -l banks_debug.lab -o $@ dfi_fs_debug.src

banks.exo: banks.bin
	$(EXO) -r -o $@ $<

banks_debug.exo: banks_debug.bin
	$(EXO) -r -o $@ $<

dfiplgin.bin: dfiplgin.src $(PLGIN_SRC) $(PLGIN_HEADERS) banks.exo banks.lab
	$(DA) -I$(MMC64_PLUGIN_SRC) -I$(MYLENE_SRC) -I$(DLOAD_SRC) -v -d dfiplgin.html -l dfiplgin.lab -o $@ dfiplgin.src

dfiplgin_debug.bin: dfiplgin.src $(PLGIN_SRC) $(PLGIN_HEADERS) banks_debug.exo banks_debug.lab
	$(DA) -DDEBUG=1 -I$(MMC64_PLUGIN_SRC) -I$(MYLENE_SRC) -I$(DLOAD_SRC) -v -d dfiplgin_debug.html -l dfiplgin_debug.lab -o $@ dfiplgin.src

dfitest.prg: dfitest.src banks.exo banks.lab
	$(DA) -v -d dfitest.html -l dfitest.lab -o $@ $<

.PHONY: sim

dfitest.d64: dfitest.prg
	rm -f $@
	cbmconvert -nD4 $@ $^

sim: dfitest.d64
	x64 +sound -cartrr /home/baccy/RetroReplay/rr-38a-64pal.bin -reu -reusize 512 dfitest.d64

#--------------------------------------

install:
	mount /MemoryStickDos
	cp dfiplgin.bin /MemoryStickDos/system64/
	umount /MemoryStickDos

#--------------------------------------

clean:
	$(RM) dfiplgin.bin banks.bin banks.exo banks.html banks.lab
	$(RM) dfiplgin_debug.bin banks_debug.bin banks_debug.exo banks_debug.html banks_debug.lab

#--------------------------------------

DATE := $(shell date +%Y%m%d)
DATETIME := $(shell date +%Y%m%d_%H%M)

CURRENTPATH := $(subst /, ,$(shell pwd))
THISDIR := $(word $(words $(CURRENTPATH)), $(CURRENTPATH))

backup:
	cd .. && tar cfjv $(ArcDir)dfiplgin_complete_$(DATETIME).tar.bz2 $(THISDIR)


DISTRIBFILES := $(addprefix $(THISDIR)/,$(SRC) $(HEADER) $(MISCARC))

distrib:
	cd .. && tar cfjv $(ArcDir)dfiplgin_src_$(DATE).tar.bz2 $(DISTRIBFILES)
	zip -9 $(ArcDir)dfiplgin_bin_$(DATE).zip dfiplgin.bin

#---------------------------------------

