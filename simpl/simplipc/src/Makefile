#=======================================================================
#
# FILE:			Makefile
#
# DESCRIPTION:	This make file produces the simpl library.
#
# AUTHOR:		FC Software Inc.
#-----------------------------------------------------------------------
#    Copyright (C) 2000,2007 FCSoftware Inc. 
#
#    This library is free software; you can redistribute it and/or
#    modify it under the terms of the GNU Lesser General Public
#    License as published by the Free Software Foundation; either
#    version 2.1 of the License, or (at your option) any later version.
#
#    This library is distributed in the hope that it will be useful,
#    but WITHOUT ANY WARRANTY; without even the implied warranty of
#    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
#    Lesser General Public License for more details.
#
#    You should have received a copy of the GNU Lesser General Public
#    License along with this library; if not, write to the Free Software
#    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
#
#    If you discover a bug or add an enhancement contact us on the
#    SIMPL project mailing list.
#
#-----------------------------------------------------------------------
#
# Revision history:
# ======================================================================
# $Log: Makefile,v $
# Revision 1.3  2007/09/12 16:33:20  bobfcsoft
# added fPIC flag for 64bit compile
#
# Revision 1.2  2007/07/24 19:57:22  bobfcsoft
# new contact info
#
# Revision 1.1.1.1  2005/03/27 11:50:50  paul_c
# Initial import
#
# Revision 1.11  2003/04/14 13:38:06  root
# enabled MAC_OS_X stuff
#
# Revision 1.10  2002/11/22 16:34:55  root
# 2.0rc3
#
#
#=======================================================================

#====================================================================
# definitions
#====================================================================

# default OS type
OS_TYPE = _LINUX_OS
# so far this value can also be set OS_TYPE = _MAC_OS_X

CC = cc

OBJ_DIR = ./obj
LIB_DIR = ../lib
INC_DIR = ../../include
INSTALL_LIB_DIR = ../../lib

SIMPL_OBJ =	\
			$(OBJ_DIR)/simpl.o \
			$(OBJ_DIR)/simplUtils.o

MY_LIBRARY = libsimpl.a

CDFLAGS = -c -D$(OS_TYPE) -fPIC -O -Wall -I$(INC_DIR) -o
LDFLAGS = -L$(LIB_DIR) -lsimpl
LIBFLAGS =

SONAME = libsimpl.so.1
VERSION = 1.0.0

#=====================================================================
# Default targets
#=====================================================================
all: \
    title \
	whichOS \
    $(OBJ_DIR) \
    $(LIB_DIR) \
    $(LIB_DIR)/$(MY_LIBRARY)
	@echo simpl all

title:
	@echo simpl starting

whichOS:
	@echo OS TYPE = $(OS_TYPE)

$(OBJ_DIR):
	mkdir ./obj
	chmod a+w ./obj

$(LIB_DIR):
	mkdir ../lib
	chmod a+w ../lib

#=====================================================================
# static library
#=====================================================================
$(LIB_DIR)/libsimpl.a: $(SIMPL_OBJ)
	ar vrs $(LIB_DIR)/libsimpl.a $?	

#=====================================================================
# dynamic library
#=====================================================================
$(LIB_DIR)/libsimpl.so: $(LIB_DIR)/$(SONAME)
	ln -sf $(LIB_DIR)/$(SONAME)	$(LIB_DIR)/libsimpl.so

$(LIB_DIR)/$(SONAME): $(LIB_DIR)/libsimpl.so.$(VERSION)
	ln -sf $(LIB_DIR)/libsimpl.so.$(VERSION) $(LIB_DIR)/$(SONAME)	

$(LIB_DIR)/libsimpl.so.$(VERSION): $(SIMPL_OBJ)
	$(CC) -shared -Wl,-soname,$(SONAME) -o $@ $? -lc

#=====================================================================
# compiling
#=====================================================================
$(OBJ_DIR)/simpl.o: simpl.c
	$(CC) $(LIBFLAGS) $(CDFLAGS) $@ $<

$(OBJ_DIR)/simplUtils.o: simplUtils.c
	$(CC) $(LIBFLAGS) $(CDFLAGS) $@ $<

#=====================================================================
#  cleanup
#=====================================================================
clobber: clean
clean:
	@-rm -f $(OBJ_DIR)/*.o
	@-rm -f $(LIB_DIR)/libsimpl.*
	@-rm -f $(INSTALL_LIB_DIR)/libsimpl.*
	@echo simpl clean/clobber

#=====================================================================
#  install 
#=====================================================================
install: \
     title \
     $(OBJ_DIR) \
     $(LIB_DIR) \
     $(LIB_DIR)/$(MY_LIBRARY)
	-cp $(LIB_DIR)/$(MY_LIBRARY) $(INSTALL_LIB_DIR)
	@echo simpl install

#=====================================================================
#   dynamic
#=====================================================================
dynamic:
	make install MY_LIBRARY=libsimpl.so LIBFLAGS="-D_REENTRANT -fPIC"
	@echo simpl dynamic

#===================
#  debug
#===================
debug:
	make install DE=-g
	@echo simpl debug
