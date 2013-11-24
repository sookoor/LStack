#############################################################################
#
#  Makefile for AS-test
#
#############################################################################
#
#  If you move this makefile, update the variable below
#  or else depend won't work.
#############################################################################

MAKEFILE	= Makefile
CC		= g++

CFILES		= LS-test.cpp \
		  LStack.cpp \

#############################################################################
# Flags for Installation
#############################################################################
BINDIR		= .
#############################################################################

DFLAGS		= -g 
IFLAGS          = # -DUSE_TEMPLATES
OPTFLAGS	=  # Enable this flag if compiler supports templates...
LDFLAGS		=  
CFLAGS		= $(IFLAGS) $(OPTFLAGS) $(DFLAGS)

#############################################################################
# G++ directives
#############################################################################
.SUFFIXES: .cpp
.cpp.o:
	$(CC) $(CFLAGS) -c $<
#############################################################################

all: LS-test

LS-test: LS-test.o LStack.o
	$(CC) $(LDFLAGS) LS-test.o LStack.o -o $@

clean:
	rm -f *.o *.out *~ core

realclean: clean
	rm -rf LS-test

depend:
	o-g++dep -f $(MAKEFILE) $(CFILES)

# DO NOT DELETE THIS LINE -- g++dep uses it.
# DO NOT PUT ANYTHING AFTER THIS LINE, IT WILL GO AWAY.

LS-test.o: LS-test.cpp LStack.h Stack_Exceptions.h LStack.cpp LStack.inl
LStack.o: LStack.cpp LStack.h Stack_Exceptions.h LStack.cpp LStack.inl

# IF YOU PUT ANYTHING HERE IT WILL GO AWAY
