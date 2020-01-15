# Includable for c1-like makefiles.

# Program name is defaulty the root directory name.
PROGNAME= $(notdir $(patsubst %/,%,$(dir $(abspath $(firstword $(MAKEFILE_LIST)) ))))

# Version.
VERSION = 6.2

# Artifacts.
TGT     = $(PROGNAME)$(EXEEXT)
SRC     = $(wildcard *.c) $(ADDSRC)
HDR     = $(wildcard *.h) $(ADDHDR)
ADDSRC  =
ADDHDR  =
OBJ     = $(SRC:$(CEXT)=$(OBJEXT))

# Tarball.
TARDIR  = $(PROGNAME)-$(VERSION)
TARARC  = $(TARDIR)$(TAREXT)
TARGZARC  = $(TARARC)$(GZEXT)

# Manual.
MANSTDSECT = 1
MANUAL  = $(TGT).$(MANSECT)

# Directories.

# Includes.
INCFLAGS = -I/usr/X11R6/include -I/usr/include/freetype2

# Dynamic/static libraries.
LIBFLAGS = -L/usr/X11R6/include -lX11 -lfontconfig -lXft

# CPPreprocessor.
CPPFLAGS = -DVERSION=\"$(VERSION)\"

# Warnings.
WRNFLAGS =

# Optimiziation flags.
OPTFLAGS = -O3

# Compilation Flags.
DBGFLAGS = -g $(INCFLAGS) -O0         -Wall       $(CPPFLAGS) -DDBG
CFLAGS   =    $(INCFLAGS) $(OPTFLAGS) $(WRNFLAGS) $(CPPFLAGS)
LDFLAGS  = $(LIBFLAGS)

# Compiler and linker.
CC = tcc 
LD = $(CC)
