#
# Makefile for the Opera Build Environment
#
# Wrriten by Jongwon Kim.
# 2011. 03. 05
#

-include $(PWD)/config.mk

SILENT		:= @

all: examples lib$(SECODEC_LIBNAME)

.PHONY: examples
examples: lib$(SECODEC_LIBNAME)
ifeq ($(ENCODER_SAMPLE),Y)
	@echo ""
	@echo "######################"
	@echo "##  ENCODER SAMPLE  ##"	
	@echo "######################"
	$(SILENT) $(MAKE) $(SECODEC_TOPDIR)/examples/encoder
endif
ifeq ($(DECODER_SAMPLE),Y)
	@echo ""
	@echo "######################"
	@echo "##  DECODER SAMPLE  ##"	
	@echo "######################"
	$(SILENT) $(MAKE) $(SECODEC_TOPDIR)/examples/decoder
endif

.PHONY: lib$(SECODEC_LIBNAME)
lib$(SECODEC_LIBNAME): 
	@echo ""
	@echo "##########################"
	@echo "##    lib$(SECODEC_LIBNAME)   ##"	
	@echo "##########################"
	$(SILENT) $(MAKE) $(SECODEC_TOPDIR)/src/

.PHONY: clean
clean: examples-clean lib$(SECODEC_LIBNAME)-clean
	@echo ""
	@echo "#####################"
	@echo "##      clean      ##"	
	@echo "#####################"

.PHONY: examples-clean
examples-clean:
ifeq ($(ENCODER_SAMPLE),Y)
	$(SILENT) $(MAKE) $(SECODEC_TOPDIR)/examples/encoder clean	
endif
ifeq ($(DECODER_SAMPLE),Y)
	$(SILENT) $(MAKE) $(SECODEC_TOPDIR)/examples/decoder clean	
endif

.PHONY: lib$(SECODEC_LIBNAME)-clean
lib$(SECODEC_LIBNAME)-clean:
	$(SILENT) $(MAKE) $(SECODEC_TOPDIR)/src clean	


.PHONY: distclean
distclean: clean
	$(RM) -rf $(INSTALLDIR)
