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

CFLAGS		= -fPIC -O -Wall -Wno-unused-function -fomit-frame-pointer -MMD -I$(SECODEC_LIBINC) $(__DBG)
LDFLAGS		= -L$(SECODEC_LIBSRC) -l$(SECODEC_LIBNAME) -lstdc++
CXXFLAGS	= $(CFLAGS)

OBJS_DIR	= zobj
OBJS		= $(C_SRC:.c=.o) $(CXX_SRC:.cpp=.o)
DEPFILES	= $(OBJS:.o=.d)
CLEANLIST	= $(OBJS) $(DEPFILES) $(OBJS_DIR)

# implicit rules
%.o: %.c
	$(CC) -c $(CFLAGS) $< -o $@

%.o: %.cpp
	$(CXX) -c $(CXXFLAGS) $< -o $@

C_SRC		:= 

CXX_SRC		:= \
			encoder_sample.cpp \

TARGET		:= ait_encoder

### Targets
all: $(OBJS)
	$(SILENT) $(RM) -rf $(OBJS_DIR)
	$(CC) $(OBJS) -o $(TARGET) $(LDFLAGS)
	$(SILENT) $(MKDIR) $(OBJS_DIR)
	$(SILENT) $(MV) $(CLEANLIST) 

clean:
	rm -rf $(CLEANLIST) $(TARGET)

#-include $(DEPFILES)
