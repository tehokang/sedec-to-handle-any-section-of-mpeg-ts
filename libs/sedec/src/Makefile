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
OBJS		= $(C_SRC:.c=.o) $(CXX_SRC:.cpp=.o)

CXXFLAGS	= $(CFLAGS) -stdlib=libstdc++
CFLAGS		= -fPIC -O -Wall -Wno-unused-function -fomit-frame-pointer -MMD -I$(SECODEC_LIBINC) $(__DBG)
CLEANLIST	= $(TARGET) $(TARGET_VER) $(OBJS) $(DEPFILES) $(OBJS_DIR)

# implicit rules
%.o: %.c
	$(CC) -c $(CFLAGS) $< -o $@

%.o: %.cpp
	$(CXX) -c $(CXXFLAGS) $< -o $@

C_SRC		:= 

CXX_SRC		:= \
			common/bit_readwriter.cpp \
			common/descriptor.cpp \
			common/descriptor_factory.cpp \
			common/section.cpp \
			descriptors/application_descriptor.cpp \
			descriptors/application_name_descriptor.cpp \
			descriptors/application_usage_descriptor.cpp \
			descriptors/application_recording_descriptor.cpp \
			descriptors/simple_application_location_descriptor.cpp \
			descriptors/simple_application_boundary_descriptor.cpp \
			descriptors/transport_protocol_descriptor.cpp \
			descriptors/parental_rating_descriptor.cpp \
			descriptors/application.cpp \
			sections/ait_section.cpp \
			sections/ait_section_transcoder.cpp \
			
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
