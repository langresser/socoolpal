ifeq (WINS,$(findstring WINS, $(PLATFORM)))
ZDIR=$(EPOCROOT)\epoc32\release\$(PLATFORM)\$(CFG)\Z
else
ZDIR=$(EPOCROOT)\epoc32\data\z
endif
# -------------------------------------------------------------------
# TODO: Configure these
# -------------------------------------------------------------------
TARGETDIR=$(ZDIR)\RESOURCE\apps
#ICONTARGETFILENAME=$(TARGETDIR)\sdlpal_aif.mif
ICONTARGETFILENAME=$(TARGETDIR)\sdlpal_aif.mbm

do_nothing :
	@rem do_nothing

MAKMAKE : do_nothing

BLD : do_nothing

CLEAN : do_nothing

LIB : do_nothing

CLEANLIB : do_nothing


RESOURCE :
	mifconv $(ICONTARGETFILENAME) \
		 /c24,8 sdlpal.bmp
#RESOURCE :
#	mifconv $(ICONTARGETFILENAME) \
#		/c8,8 sdlpal.svg
		
FREEZE : do_nothing

SAVESPACE : do_nothing

RELEASABLES :
	
	@echo $(ICONTARGETFILENAME)

FINAL : do_nothing
