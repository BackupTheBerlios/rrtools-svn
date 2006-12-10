

DA = dreamass

# directory for backup
export ArcDir = /home/baccy/BackUp/

# mmc64_plugin source directory
export MMC64_PLUGIN_SRC = ../..

TARGET = funplgin

#--------------------------------------

.PHONY: all backup clean distrib install

all: $(TARGET).bin

#--------------------------------------

$(TARGET).bin: $(TARGET).src $(MMC64_PLUGIN_SRC)/mmc64_plugin/mmc64_plugin.src
	$(DA) -v -I$(MMC64_PLUGIN_SRC) -d $(TARGET).html -l $(TARGET).lab -o $@ $(TARGET).src

#--------------------------------------

install:
	mount /MemoryStick
	cp $(TARGET).bin /MemoryStick/system64/
	umount /MemoryStick

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

