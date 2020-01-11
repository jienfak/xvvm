# Configuration for GNU/Linux systems.

# Standard programs.
RM      = rm -rf
INSTALL = install
TAR     = tar -cf
GZIP    = gzip -f
MKDIR   = mkdir -p
CP      = cp -R
STRIP   = strip
ECHO    = echo
SED     = sed
DATE    = date
MAKE    = make

# Flags.
OUTFLAG = -o
OBJFLAG = -c

# Extensions.
OBJEXT  = .o
CEXT    = .c
HEXT = .h
GZEXT   = .gz
TAREXT  = .tar
EXEEXT  = 

# Directories and prefixes.
ROOTDIR       = 
DIRPREFIX     = usr/local
BINPREFIX     = bin
DESTDIR       = $(ROOTDIR)/$(DIRPREFIX)

# For programs with manual configuration.
MANPREFIX     = share/man
MANSTDSECT    = 1
MANSECTPREFIX = man$(MANSTDSECT)
MANUAL        = $(PROGNAME).$(MANSTDSECT)
PATH2MAN      = $(DESTDIR)/$(MANPREFIX)/$(MANSECTPREFIX)/$(MANUAL)
