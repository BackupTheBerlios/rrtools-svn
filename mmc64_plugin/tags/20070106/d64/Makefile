

DA = dreamass

# directory for backup
export ArcDir = /home/baccy/BackUp/

# mmc64_plugin source directory
export MMC64_PLUGIN_SRC = ../..

# mylene source directory
export MYLENE_SRC = ../..

# dload source directory
export DLOAD_SRC = ../..

TARGET = d64plgin

#--------------------------------------

.PHONY: all backup clean distrib install

all: $(TARGET).bin

#--------------------------------------

SOURCES =	actions.src \
		browser.src \
		mylene_dfi.src \
		$(MMC64_PLUGIN_SRC)/mmc64_plugin/mmc64_plugin.src \
		$(MYLENE_SRC)/mylene/com_lib.src \
		$(MYLENE_SRC)/mylene/entry.src \
		$(MYLENE_SRC)/mylene/levels.src \
		$(MYLENE_SRC)/mylene/mylene.src

$(TARGET).bin: $(TARGET).src $(SOURCES)
	$(DA) -I$(MMC64_PLUGIN_SRC) -I$(MYLENE_SRC) -I$(DLOAD_SRC) -v -d $(TARGET).html -l $(TARGET).lab -o $@ $(TARGET).src

#--------------------------------------

install:
	mount /MemoryStickDos
	cp $(TARGET).bin /MemoryStickDos/system64/
	umount /MemoryStickDos

#--------------------------------------

clean:
	$(RM) $(TARGET).bin

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

