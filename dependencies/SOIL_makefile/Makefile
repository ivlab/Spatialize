# SOIL makefile for linux (based on the AngelScript makefile)
# Type 'make' then 'make install' to complete the installation of the library

# For 'make install' to work, set LOCAL according to your system configuration
LOCAL = ../../build/install/SOIL

LIB = libSOIL.a
INC = SOIL.h

SRCDIR = ../SOIL/src/SOIL/src
LIBDIR = ../SOIL/src/SOIL/lib
INCDIR = ../SOIL/src/SOIL/src
OBJDIR = ../SOIL/obj

CXX = gcc
CXXFLAGS = -O2 -s -Wall
DELETER = rm -f
COPIER = cp

SRCNAMES = \
  image_helper.c \
  stb_image_aug.c  \
  image_DXT.c \
  SOIL.c \

OBJ = $(addprefix $(OBJDIR)/, $(notdir $(SRCNAMES:.c=.o)))
BIN = $(LIBDIR)/$(LIB)

all: $(BIN)

$(BIN): $(OBJ)
	ar r $(BIN) $(OBJ)
	ranlib $(BIN)
	@echo -------------------------------------------------------------------
	@echo Done. As root, type 'make install' to install the library.

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CXX) $(CXXFLAGS) -o $@ -c $<


clean:
	$(DELETER) $(OBJ) $(BIN)

install: $(BIN)
	@echo Installing to: $(LOCAL)/lib/dasdfds and $(LOCAL)/include...
	@echo -------------------------------------------------------------------
	mkdir -p $(LOCAL)/lib
	mkdir -p $(LOCAL)/include
	$(COPIER) $(BIN) $(LOCAL)/lib/libSOIL.a
	$(COPIER) $(INCDIR)/$(INC) $(LOCAL)/include/SOIL.h
	@echo -------------------------------------------------------------------
	@echo SOIL library installed. Enjoy!

uninstall:
	$(DELETER) $(LOCAL)/include/$(INC) $(LOCAL)/lib/$(LIB)
	@echo -------------------------------------------------------------------
	@echo SOIL library uninstalled.

.PHONY: all clean install uninstall
