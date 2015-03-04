################################################################################
# User configuration
# the user configuration should be set by own development environment.
################################################################################
# you should choose one of arm, mipsel, x86 CHIP_CORE to assigned
CHIP_CORE	= x86
CROSS_VER	=

################################################################
TOOLCHAIN_PATH	= /opt/toolchains/$(CROSS_VER)/
CROSS_COMPILE   = /opt/toolchains/$(CROSS_VER)/bin/$(CHIP_CORE)-linux-

ifeq ($(CHIP_CORE),x86)
CROSS_COMPILE	:=
endif

################################################################
SILENT  := @
MKDIR	:= mkdir -p
CP	:= cp -a
RM	:= rm -rf
ECHO	:= echo
LN	:= ln -s
MV	:= mv
MAKE  	:= make -C
CC    	:= $(CROSS_COMPILE)gcc
CXX   	:= $(CROSS_COMPILE)g++
LD    	:= $(CROSS_COMPILE)ld
STRIP 	:= $(CROSS_COMPILE)strip --strip-debug --strip-unneeded
################################################################################
# Common BUILD configuration
# The following configurations are managed by the opera part engineers.
################################################################################

TOPDIR			:= $(PWD)/../
SUBLIBS			:= $(TOPDIR)/libs
HDKKIT			:= $(TOPDIR)/kit
EXAMPLEDIR		:= $(TOPDIR)/examples

INSTALL_ROOT		:= ./out
ifeq ($(CHIP_CORE),x86)
INSTALL_PKG		:= $(INSTALL_ROOT)/$(CHIP_CORE)/
else
INSTALL_PKG		:= $(INSTALL_ROOT)/$(CHIP_CORE)/$(CROSS_VER)/
endif
################################################################################
# SectionCodec BUILD configuration
# The following configurations are managed by the opera part engineers.
################################################################################
SECODEC_LIBNAME		:= sedec
SECODEC_TOPDIR 		:= $(SUBLIBS)/$(SECODEC_LIBNAME)
SECODEC_LIBVER		:= 0.0.1
SECODEC_LIBINC		:= $(SUBLIBS)/$(SECODEC_LIBNAME)/include
SECODEC_LIBSRC		:= $(SUBLIBS)/$(SECODEC_LIBNAME)/src

ENCODER_SAMPLE		:= Y
DECODER_SAMPLE		:= Y



