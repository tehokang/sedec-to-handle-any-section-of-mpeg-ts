#
#	Makefile for Library
#
#	Written by Jongwon Kim
#		2011. 8. 19.
#

-include $(PWD)/config.mk

DEBUG		:= y

ifdef DEBUG
__DBG		:= -DDEBUG=$(DEBUG) -D_DEBUG=$(DEBUG) -O0 -g
else
__DBG		:= -O2
endif

TARGET		:= lib$(SECODEC_LIBNAME).so
TARGET_VER	:= $(TARGET).$(SECODEC_LIBVER)

OBJS_DIR	= zobj
DEPFILES	= $(OBJS:.o=.d)
OBJS		= $(C_SRC:.c=.o) $(CXX_SRC:.cc=.o)

CXXFLAGS	= $(CFLAGS) -stdlib=libstdc++
CFLAGS		= -fPIC -O -Wall -Wno-unused-function -fomit-frame-pointer -MMD -I$(SECODEC_LIBINC) $(__DBG)
CLEANLIST	= $(TARGET) $(TARGET_VER) $(OBJS) $(DEPFILES) $(OBJS_DIR)

# implicit rules
%.o: %.c
	$(CC) -c $(CFLAGS) $< -o $@

%.o: %.cc
	$(CXX) -c $(CXXFLAGS) $< -o $@

C_SRC		:= 

CXX_SRC		:= \
			common/bit_readwriter.cc \
			common/descriptor.cc \
			common/descriptor_factory.cc \
			common/section.cc \
			descriptors/application_descriptor.cc \
			descriptors/application_name_descriptor.cc \
			descriptors/application_usage_descriptor.cc \
			descriptors/application_recording_descriptor.cc \
			descriptors/simple_application_location_descriptor.cc \
			descriptors/simple_application_boundary_descriptor.cc \
			descriptors/transport_protocol_descriptor.cc \
			descriptors/parental_rating_descriptor.cc \
			descriptors/application.cc \
			sections/ait_section.cc \
			sections/ait_section_transcoder.cc \
			
### Targets
all: $(OBJS)
	$(CC) -shared $(OBJS) -o $(TARGET_VER)
	@echo $(STRIP) $(TARGET_VER)
	@if [ ! -f $(TARGET) ] ; then \
		$(LN) $(TARGET_VER) $(TARGET);	\
	fi
	$(MKDIR) $(OBJS_DIR)
	@echo $(SILENT) $(MV) $(OBJS) $(DEPFILES) $(OBJS_DIR)

clean:
	rm -rf $(CLEANLIST)
	
#-include $(DEPFILES)
