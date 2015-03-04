#
#	Makefile for BPL
#
#	Written by Jongwon Kim
#		2011. 8. 19.
#

TOPDIR		:= ../
VERSION		:= 0.0.1

-include $(TOPDIR)/build/config.mk

CC          := $(CROSS_COMPILE)gcc
CXX         := $(CROSS_COMPILE)g++
LD          := $(CROSS_COMPILE)ld
MAKE        := $(CROSS_COMPILE)make
STRIP       := $(CROSS_COMPILE)strip --strip-debug --strip-unneeded

ifdef DEBUG
__DBG		:= -DDEBUG=$(DEBUG) -D_DEBUG=$(DEBUG) -O0 -g
else
__DBG		:= -O2
endif

HPATH		= ./include
INC		= -I$(HPATH)
INC		+= -I$(TOPDIR)/3rd/usr/include/

###### include AIT Section Parser ######
INC		+= -I$(TOPDIR)/libs/ait/include/

###### include DSMCC Library ######
INC		+= -I$(TOPDIR)/libs/dsmcc/include/

LIBS		=
CFLAGS		= -fPIC -O -Wall -Wno-unused-function -fomit-frame-pointer -MMD -Wall $(INC) $(__DBG)
CXXFLAGS	= $(CFLAGS)

OBJS		= $(C_SRC:.c=.o) $(CXX_SRC:.cpp=.o)
DEPFILES	= $(OBJS:.o=.d)
CLEANLIST	= $(TARGET) $(TARGET_VER) $(OBJS) $(DEPFILES)

# implicit rules
%.o: %.c
	$(CC) -c $(CFLAGS) $< -o $@

%.o: %.cpp
	$(CXX) -c $(CXXFLAGS) $< -o $@

C_SRC		:=
CXX_SRC		:= main/hdk.cpp	\
				main/hdksystem.cpp	\
				main/hdkappcontainer.cpp	\
				main/hdkappmgr.cpp	\
				main/hdkaitmgr.cpp	\
				main/hdkaitcontainer.cpp	\
				main/hdkdsmccmgr.cpp	\

TARGET		:= libhdk.so
TARGET_VER	:= libhdk.so.$(VERSION)

### Targets
$(TARGET): $(OBJS)
	$(CXX) -shared $(OBJS) -o $(TARGET_VER)
	$(STRIP) $(TARGET_VER)
	@if [ ! -f $(TARGET) ] ; then \
		$(LN) $(TARGET_VER) $(TARGET);	\
	fi

# dummy to prevent clean being executed, when no target defined previously.
__dummy:
	@echo "No target defined."

clean:
	rm -rf $(CLEANLIST)

-include $(DEPFILES)
