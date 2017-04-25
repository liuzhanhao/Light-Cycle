###############################################
#
# Makefile - for fclogger test code 
#
#-----------------------------------------------------------------------
#    Copyright (C) 1998, 2002, 2007 FCSoftware Inc. 
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
#$Log: Makefile,v $
#Revision 1.2  2007/07/24 20:38:31  bobfcsoft
#new contact info
#
#Revision 1.1.1.1  2005/03/27 11:50:39  paul_c
#Initial import
#
#Revision 1.6  2002/12/02 15:59:28  root
#no longer prompts logit to upper level directories on
#make install
#
#Revision 1.5  2002/11/22 16:26:47  root
#2.0rc3
#
#Revision 1.4  2002/06/12 18:18:19  root
#fcipc merge completed
#
#Revision 1.3  2001/04/20 19:28:52  root
#added logit2 stuff
#
#Revision 1.2  2000/10/13 13:59:25  root
#LGPL
#using SIMPL_HOME
#
#Revision 1.1  1999/04/08 14:25:23  root
#Initial revision
#
#Revision 1.2  1999/01/31 12:53:43  root
#*** empty log message ***
#
#Revision 1.1  1998/07/31 21:36:39  root
#Initial revision
#
#
#
###############################################
CC=cc
DE=NODEBUG

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

LOGIT_OBJ=\
	$(OBJ_DIR)/logit.o

CDFLAGS=-c \
        -I $(LOCAL_INCL_DIR)\
        -I $(INCL_DIR)

LDFLAGS=-L $(INSTALL_LIB_DIR) -lsimpllog -lsimpl

#========================
# Default targets
#========================
all:\
     title \
     $(OBJ_DIR) \
     $(BIN_DIR) \
     $(BIN_DIR)/logit
	@echo fclogger test all

title:
	@echo fclogger test build starting

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

#========================
# Link
#========================
$(BIN_DIR)/logit:	$(LOGIT_OBJ) 
	$(CC) -o $(BIN_DIR)/logit $(LOGIT_OBJ) $(LDFLAGS)
	
#===================
# Compiles
#===================
$(OBJ_DIR)/logit.o: logit.c
	$(CC) $(CDFLAGS) -o $(OBJ_DIR)/logit.o logit.c

#===================
# start over
#===================
clobber:
	@-rm -f $(OBJ_DIR)/*.o
	@-rm -f $(BIN_DIR)/*.a
	@echo fclogger test clobber

install:\
     title \
     $(OBJ_DIR) \
     $(BIN_DIR) \
     $(BIN_DIR)/logit
	@echo fclogger test install
