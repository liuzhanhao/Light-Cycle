###############################################
#
# Makefile - for fclogger 
#
#-----------------------------------------------------------------------
#    Copyright (C) 1998, 2002 FCSoftware Inc. 
#
#    This software is in the public domain.
#    Permission to use, copy, modify, and distribute this software and its
#    documentation for any purpose and without fee is hereby granted, 
#    without any conditions or restrictions.
#    This software is provided "as is" without express or implied warranty.
#
#    If you discover a bug or add an enhancement contact us on the 
#    SIMPL project mailing list.
#-----------------------------------------------------------------------
#
#$Log: Makefile,v $
#Revision 1.2  2007/07/24 20:40:47  bobfcsoft
#new contact info
#
#Revision 1.1.1.1  2005/03/27 11:50:45  paul_c
#Initial import
#
#Revision 1.11  2003/04/16 01:49:19  root
#added dynamic target
#
#Revision 1.10  2002/11/22 16:26:01  root
#2.0rc3
#
#Revision 1.9  2002/06/12 18:19:52  root
#fcipc merge completed
#
#Revision 1.8  2001/07/05 14:24:52  root
#added debug target
#
#Revision 1.7  2001/01/29 15:16:42  root
#added stuff for simpllog library
#
#Revision 1.6  2000/10/13 14:00:18  root
#LGPL
#using SIMPL_HOME
#
#Revision 1.5  1999/05/19 16:54:15  root
#enabled full warnings
#
#Revision 1.4  1999/04/08 14:26:28  root
#added fclog stuff
#
#Revision 1.3  1999/02/04 14:40:33  root
#cleanup
#
#Revision 1.2  1999/01/31 12:53:26  root
#*** empty log message ***
#
#Revision 1.1  1998/07/09 17:30:42  root
#Initial revision
#
#
#
###############################################
CC=cc
DE=

SIMPL_DIR=../..

PROGRAM_NAME=
line1 = --------------------------------------------------------------------
line2 = ====================================================================

DEST_DIR=.

OBJ_DIR=obj
LIB_DIR=../lib
BIN_DIR=../bin

INSTALL_LIB_DIR=$(SIMPL_DIR)/lib
INSTALL_BIN_DIR=$(SIMPL_DIR)/bin
LOCAL_INCL_DIR=../include
INCL_DIR=$(SIMPL_DIR)/include

LOGGER_OBJ=\
	$(OBJ_DIR)/fclogger.o

SIMPLLOG_OBJ=\
	$(OBJ_DIR)/simplLogUtils.o

MY_LIBRARY = libsimpllog.a

CDFLAGS=-c \
	$(DE)\
	-Wall\
        -I $(LOCAL_INCL_DIR)\
        -I $(INCL_DIR)

LDFLAGS_OLD=-L $(INSTALL_LIB_DIR) -lfcipc

LDFLAGS=-L $(INSTALL_LIB_DIR) -lsimpl
LIBFLAGS=

SONAME = libsimpllog.so.1
VERSION = 1.0.0

#========================
# Default targets
#========================
all:\
     title \
     $(OBJ_DIR) \
     $(BIN_DIR) \
     $(LIB_DIR) \
     $(LIB_DIR)/$(MY_LIBRARY) \
     $(BIN_DIR)/fclogger
	@echo fclogger all

title:
	@echo fclogger build starting

description:
	@(\
	echo;\
	echo "$(line1)";\
	echo "Compiling $(PROGRAM_NAME) module -> $<";\
	echo )

$(OBJ_DIR):
	mkdir obj
	chmod a+w obj

$(BIN_DIR):
	mkdir ../bin
	chmod a+w ../bin

$(LIB_DIR):
	mkdir ../lib
	chmod a+w ../lib

#========================
# Link
#========================
$(BIN_DIR)/fclogger:	$(LOGGER_OBJ)
	$(CC) -o $(BIN_DIR)/fclogger $(LOGGER_OBJ) $(LDFLAGS)
	
#=====================================================================
# static library
#=====================================================================
$(LIB_DIR)/libsimpllog.a: $(SIMPLLOG_OBJ)
	ar vrs $(LIB_DIR)/libsimpllog.a $?	
			
#=====================================================================
# dynamic library
#=====================================================================
$(LIB_DIR)/libsimpllog.so: $(LIB_DIR)/$(SONAME)
	ln -sf $(LIB_DIR)/$(SONAME) $(LIB_DIR)/libsimpllog.so

$(LIB_DIR)/$(SONAME): $(LIB_DIR)/libsimpllog.so.$(VERSION)
	ln -sf $(LIB_DIR)/libsimpllog.so.$(VERSION) $(LIB_DIR)/$(SONAME)	

$(LIB_DIR)/libsimpllog.so.$(VERSION): $(SIMPLLOG_OBJ)
	$(CC) -shared -Wl,-soname,$(SONAME) -o $@ $? -lc


#===================
# Compiles
#===================
$(OBJ_DIR)/fclogger.o: fclogger.c
	$(CC) $(CDFLAGS) -o $(OBJ_DIR)/fclogger.o fclogger.c

$(OBJ_DIR)/simplLogUtils.o: simplLogUtils.c
	$(CC) $(LIBFLAGS) $(CDFLAGS) -o $(OBJ_DIR)/simplLogUtils.o simplLogUtils.c

#===================
# Cleanup
#===================
clobber:
	@-rm -f $(OBJ_DIR)/*.o
	@-rm -f $(BIN_DIR)/fclogger
	@-rm -f $(LIB_DIR)/libsimpllog.*
	@-rm -f $(INSTALL_LIB_DIR)/libsimpllog.*
	@echo fclogger clobber

#===================
# Install
#===================
install:\
     title \
     $(OBJ_DIR) \
     $(BIN_DIR) \
     $(LIB_DIR) \
     $(LIB_DIR)/$(MY_LIBRARY) \
     $(BIN_DIR)/fclogger
	cp $(BIN_DIR)/fclogger $(INSTALL_BIN_DIR)/fclogger
	cp $(LIB_DIR)/$(MY_LIBRARY) $(INSTALL_LIB_DIR)
	@echo logger install

#=====================================================================
#   dynamic
#=====================================================================
dynamic:
	make install MY_LIBRARY=libsimpllog.so LIBFLAGS="-D_REENTRANT -fPIC"
	@echo logger dynamic

#===================
#  debug
#===================
debug:
	make install DE=-g
	@echo logger debug
