

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

TARGET = dfiplgin

#--------------------------------------

.PHONY: all backup clean distrib install

all: $(TARGET).bin dfitest.d64
#all: $(TARGET).bin

#--------------------------------------

DFI_FS_SRC =	dfi_fs.src \
		dfi_fs_bam.src \
		dfi_fs_bank0.src \
		dfi_fs_bank1.src \
		dfi_fs_bank2.src \
		dfi_fs_bank_jsr.src \
		dfi_fs_cmd.src \
		dfi_fs_dir.src \
		dfi_fs_error.src \
		dfi_fs_mmc64.src \
		dfi_fs_reu.src \
		dfi_fs_rom.src \
		dfi_fs_switcher.src

SOURCES =	actions.src \
		browser.src \
		mylene_dfi.src \
		$(MMC64_PLUGIN_SRC)/mmc64_plugin/mmc64_plugin.src \
		$(MYLENE_SRC)/mylene/com_lib.src \
		$(MYLENE_SRC)/mylene/entry.src \
		$(MYLENE_SRC)/mylene/levels.src \
		$(MYLENE_SRC)/mylene/mylene.src \
		$(DLOAD_SRC)/dload/mmcparam.src

HEADERS =	$(MYLENE_SRC)/mylene/entry.h \
		$(MYLENE_SRC)/mylene/mylene.h


banks.bin banks.lab: $(DFI_FS_SRC)
	$(DA) -v -d banks.html -l banks.lab -o banks.bin $<

banks.exo: banks.bin
	$(EXO) -r -o $@ $<

$(TARGET).bin: $(TARGET).src $(SOURCES) $(HEADERS) banks.exo banks.lab
	$(DA) -I$(MMC64_PLUGIN_SRC) -I$(MYLENE_SRC) -I$(DLOAD_SRC) -v -d $(TARGET).html -l $(TARGET).lab -o $@ $(TARGET).src

dfitest.prg: dfitest.src banks.exo banks.lab
	$(DA) -v -d dfitest.html -l dfitest.lab -o $@ $<

.PHONY: sim

dfitest.d64: dfitest.prg
	rm -f $@
	cbmconvert -nD4 $@ $^

flimbo.dfi: flimbo.d81
	rm -f flimbo.dfi
	dd if=/dev/zero of=padme.bin bs=1024 count=192
	cbmconvert -dF fq.dfi flimbo.d81
	cat fq.dfi padme.bin > flimbo.dfi
	rm -f fq.dfi

SammyLightfoot.dfi: SammyLightfoot.d64
	rm -f SammyLightfoot.dfi
	dd if=/dev/zero of=padme.bin bs=1024 count=448
	cbmconvert -dF sl.dfi SammyLightfoot.d64
	cat sl.dfi padme.bin > SammyLightfoot.dfi
	rm -f sl.dfi

HauntedHouse.dfi: HauntedHouse.d64
	rm -f HauntedHouse.dfi
	dd if=/dev/zero of=padme.bin bs=1024 count=448
	cbmconvert -dF hh.dfi HauntedHouse.d64
	cat hh.dfi padme.bin > HauntedHouse.dfi
	rm -f hh.dfi

sim: dfitest.d64 SammyLightfoot.dfi HauntedHouse.dfi flimbo.dfi
	x64 +sound -cartrr /home/baccy/RetroReplay/rr-38a-64pal.bin -reu -reusize 512 dfitest.d64

#--------------------------------------

install:
	mount /MemoryStickDos
	cp $(TARGET).bin /MemoryStickDos/system64/
	umount /MemoryStickDos

#--------------------------------------

clean:
	$(RM) $(TARGET).bin banks.bin banks.exo banks.html banks.lab

#--------------------------------------

DATE := $(shell date +%Y%m%d)
DATETIME := $(shell date +%Y%m%d_%H%M)

CURRENTPATH := $(subst /, ,$(shell pwd))
THISDIR := $(word $(words $(CURRENTPATH)), $(CURRENTPATH))

backup:
	cd .. && tar cfjv $(ArcDir)$(TARGET)_complete_$(DATETIME).tar.bz2 $(THISDIR)


DISTRIBFILES := $(addprefix $(THISDIR)/,$(SRC) $(HEADER) $(MISCARC))

distrib:
	cd .. && tar cfjv $(ArcDir)$(TARGET)_src_$(DATE).tar.bz2 $(DISTRIBFILES)
	zip -9 $(ArcDir)$(TARGET)_bin_$(DATE).zip $(TARGET).bin

#---------------------------------------

