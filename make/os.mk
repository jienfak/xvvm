UNAME_S := $(shell uname -s)
OS = $(UNAME_S)
UNAME_M = : $(shell uname -m)
PROC = $(UNAME_M)
CFLAGS += -D $(OS) -D $PROC