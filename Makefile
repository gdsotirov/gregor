# Gregorian calendar routines
# Written by Georgi D. Sotirov <gdsotirov@gmail.com

CC = gcc
AR = ar
LN = ln
RM = rm
RANLIB = ranlib
MKDIR = mkdir
INSTALL = install

DEBUG = 0
DEBUG_FLAGS = -ggdb
ifeq ($(DEBUG), 1)
CCFLAGS = -Wall $(DEBUG_FLAGS)
else
CCFLAGS = -Wall
endif
ARFLAGS = rc
LNFLAGS = -sf
RMFLAGS = -f
MKDIRFLAGS = -p
INSTALLFLAGS = -m 0755

PREFIX = /usr/local
LIBDIR = $(PREFIX)/lib

MAJOR = 0
MINOR = 3
PATCH = 1

LIBNAME = gregor
ANAME = lib$(LIBNAME).a
SONAME = lib$(LIBNAME).so.$(MAJOR).$(MINOR).$(PATCH)
SOVERSION = lib$(LIBNAME).so.$(MAJOR).$(MINOR)
EASTER = easter

OBJS    = gregor.o
OBJSDLL = $(OBJS:.o=.pic.o)

STATIC_COMPILE_CMD = $(CC) $(CCFLAGS) -o $@ -c $<
SHARED_COMPILE_CMD = $(CC) $(CCFLAGS) -fPIC -o $@ -c $<

# Build static and shared libraries and test programm
all : static shared test

# Build static library file
$(ANAME) : $(OBJS)
	$(AR) $(ARFLAGS) $@ $(OBJS) $(CIFAPI)
	$(RANLIB) $@

# Build shared library file and make links
$(SONAME) : $(OBJSDLL)
	$(CC) -shared $(OBJSDLL) $(CIFAPI) -Wl,-soname -Wl,$(SOVERSION) -o $@
	$(LN) $(LNFLAGS) $(SONAME) $(SOVERSION)
	$(LN) $(LNFLAGS) $(SONAME) lib$(LIBNAME).so

gregor.o : gregor.c gregor.h
	$(STATIC_COMPILE_CMD)

gregor.pic.o : gregor.c gregor.h
	$(SHARED_COMPILE_CMD)

$(EASTER) : easter.c gregor.h
	$(CC) $(CCFLAGS) $(OBJS) -o $@ $<

# Build static library
static : $(ANAME)

# Build shared library
shared : $(SONAME)

test : $(EASTER)

# Install static and shared libraries
install : all
	$(MKDIR) $(MKDIRFLAGS) $(LIBDIR)
	$(INSTALL) $(INSTALLFLAGS) $(ANAME) $(LIBDIR)
	$(INSTALL) $(INSTALLFLAGS) $(SONAME) $(LIBDIR)
	$(LN) $(LNFLAGS) $(LIBDIR)/$(SONAME) $(LIBDIR)/$(SOVERSION)
	$(LN) $(LNFLAGS) $(LIBDIR)/$(SONAME) $(LIBDIR)/lib$(LIBNAME).so

# Uninstall static and shared libraries
uninstall :
	$(RM) $(RMFLAGS) $(LIBDIR)/lib$(LIBNAME).so
	$(RM) $(RMFLAGS) $(LIBDIR)/$(SOVERSION)
	$(RM) $(RMFLAGS) $(LIBDIR)/$(SONAME)
	$(RM) $(RMFLAGS) $(LIBDIR)/$(ANAME)

# Clean objects and intermediate files
clean :
	$(RM) $(RMFLAGS) $(OBJS) $(OBJSDLL)

# Clean objects, intermediate files and binaries
distclean : clean
	$(RM) $(RMFLAGS) $(ANAME) $(SONAME) $(SOVERSION) lib$(LIBNAME).so
	$(RM) $(RMFLAGS) $(EASTER)

