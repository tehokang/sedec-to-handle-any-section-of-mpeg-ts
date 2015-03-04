#
#
#	Makefile for HDK
#
#	Written by Jongwon Kim
#		2013. 11. 14.
#

-include ./config.mk
HDKLIBS		= $(shell find $(HDKKIT) -name *.so*)
HDKLIBS		+= $(shell find $(SECODEC_TOPDIR) -name *.so*)
KITHEADERS	= $(shell find $(HDKKIT)/include/ -name *.h)
SEDECHEADER	= $(shell find $(SECODEC_TOPDIR)/include/ -name *.h)

all: libs kit install

.PHONY: premake
premake:
	@if [ ! -d $(INSTALL_PKG) ]; then   \
		$(MKDIR) $(INSTALL_PKG);	\
		$(MKDIR) $(EXAMPLEDIR);	\
		$(MKDIR) $(INSTALL_PKG)/include;	\
		$(MKDIR) $(INSTALL_PKG)/libs;	\
		$(MKDIR) $(INSTALL_PKG)/runtime;	\
		$(MKDIR) $(INSTALL_PKG)/include/sedec;	\
	fi

.PHONY: libs
libs:
	$(MAKE) $(SUBLIBS)

.PHONY: libs-clean
libs-clean:
	$(MAKE) $(SUBLIBS) clean

.PHONY: libs-release
libs-release: premake libs
	@for header in $(SEDECHEADER); do	\
		$(CP) $$header $(INSTALL_PKG)/include/sedec;	\
	done

.PHONY: libs-examples
libs-examples: premake libs
	$(SILENT) $(CP) $(SECODEC_TOPDIR)/examples/encoder/ait_encoder $(EXAMPLEDIR);
	$(SILENT) $(CP) $(SECODEC_TOPDIR)/examples/decoder/ait_decoder $(EXAMPLEDIR);
	
.PHONY: kit
kit:
	$(MAKE) $(HDKKIT)

.PHONY: kit-clean
kit-clean:
	$(MAKE) $(HDKKIT) clean

.PHONY: kit-release
kit-release: premake kit
	@for lib in $(HDKLIBS); do	\
		$(CP) $$lib $(INSTALL_PKG)/libs/;	\
	done
	@for header in $(KITHEADERS); do	\
		$(CP) $$header $(INSTALL_PKG)/include/;	\
	done

.PHONY: install
install: libs-release kit-release
	$(SILENT) $(ECHO) "copy completed"

.PHONY: clean
clean: libs-clean kit-clean
	
.PHONY: distclean
distclean: clean
	$(RM) $(INSTALL_PKG)
