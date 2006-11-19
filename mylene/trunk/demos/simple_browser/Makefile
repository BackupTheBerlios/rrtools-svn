
#--------------------------------------

# name and path of dreamass
export DA = dreamass

# name and path of pucrunch2
export PUC = pucrunch

CBMC = cbmconvert

# c compiler
export CC = gcc

# c++ compiler
export CPP = g++

# directory for backup
export ArcDir = /home/baccy/BackUp/

# pal cart, useful for the simulation targets
export PALCRT = -cartrr /home/baccy/RetroReplay/rr-38a-64pal.bin

# ntsc cart, useful for the simulation targets
export NTSCCRT = -cartrr /home/baccy/RetroReplay/rr-38a-64ntsc.bin

#--------------------------------------
# End of Config
# nothing needs to be changed below
#--------------------------------------

MYLENE_PRE  = ../../../mylene
MYLENE_SRC  = $(MYLENE_PRE)/com_lib.src $(MYLENE_PRE)/entry.src $(MYLENE_PRE)/levels.src $(MYLENE_PRE)/mylene.src
MYLENE_HEAD = $(MYLENE_PRE)/entry.h $(MYLENE_PRE)/mylene.h

USER_PROJECT = simple_browser.src
USER_SRC  = actions.src iec_lib.src iff_lib.src keyb.src screen.src serial.src
USER_HEAD = keyb.h 

all: mylene.d64

mylene.d64: mylene.prg
	rm -f $@
	$(CBMC) -n -D4 $@ $^

mylene.d81: mylene.prg
	rm -f $@
	$(CBMC) -n -D8 $@ $^

mylene.prg: $(USER_PROJECT) $(MYLENE_SRC) $(MYLENE_HEAD) $(USER_SRC) $(USER_HEAD)
	$(DA) -v -I../../.. -l mylene.lab -d mylene.html -o $@ $<

clean:
	rm -f mylene.prg mylene.d64

#-------------------------------------

sim41p: mylene.d64
	x64 +sound -drive8type 1541 -truedrive -8 $^ -drive9type 1541 -9 die_neue_stadt_disk1of6.d64 -pal $(PALCRT)

sim70p: mylene.d64
	x64 +sound -drive8type 1570 -truedrive -8 $^ -drive9type 1570 -9 die_neue_stadt_disk1of6.d64 -pal $(PALCRT)

sim71p: mylene.d64
	x64 +sound -drive8type 1571 -truedrive -8 $^ -drive9type 1571 -9 something.d71 -pal $(PALCRT)

sim81p: mylene.d81
	x64 +sound -drive8type 1581 -truedrive -8 $^ -drive9type 1581 -9 something.d81 -pal $(PALCRT)

sim41n: mylene.d64
	x64 +sound -drive8type 1541 -truedrive -8 $^ -drive9type 1541 -9 die_neue_stadt_disk1of6.d64 -ntsc $(NTSCCRT)

sim70n: mylene.d64
	x64 +sound -drive8type 1570 -truedrive -8 $^ -drive9type 1570 -9 die_neue_stadt_disk1of6.d64 -ntsc $(NTSCCRT)

sim71n: mylene.d64
	x64 +sound -drive8type 1571 -truedrive -8 $^ -drive9type 1571 -9 something.d71 -ntsc $(NTSCCRT)

sim81n: mylene.d81
	x64 +sound -drive8type 1581 -truedrive -8 $^ -drive9type 1581 -9 something.d81 -ntsc $(NTSCCRT)

#-------------------------------------

TARGET = mylene

DATE := $(shell date +%Y%m%d)
DATETIME := $(shell date +%Y%m%d_%H%M)

CURRENTPATH := $(subst /, ,$(shell pwd))
THISDIR := $(word $(words $(CURRENTPATH)), $(CURRENTPATH))

backup:
	cd .. && tar cfjv $(ArcDir)$(TARGET)_complete_$(DATETIME).tar.bz2 $(THISDIR)


#DISTRIBFILES := $(addprefix $(THISDIR)/,$(SRC) $(HEADER) $(MISCARC))
#
#distrib:
#	cd .. && tar cfjv $(ArcDir)$(TARGET)_src_$(DATE).tar.bz2 $(DISTRIBFILES)
#	zip -9 $(ArcDir)$(TARGET)_bin_$(DATE).zip $(TARGET).bin

#---------------------------------------
