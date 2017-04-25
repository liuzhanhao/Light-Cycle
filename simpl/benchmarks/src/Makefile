###############################################
#
# Makefile - for benchmarks 
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
#
#-----------------------------------------------------------------------
#
#$Log: Makefile,v $
#Revision 1.2  2007/07/24 20:08:45  bobfcsoft
#new comment info
#
#Revision 1.1.1.1  2005/03/27 11:50:37  paul_c
#Initial import
#
#Revision 1.11  2002/12/02 15:58:47  root
#switched to public licence
#
#Revision 1.10  2002/07/11 19:52:21  root
#SIMPL to SIMPLIPC
#
#Revision 1.9  2002/06/12 18:16:57  root
#make simplipc default case
#
#Revision 1.8  2002/05/29 15:27:31  root
#bug fixes
#
#Revision 1.7  2001/07/05 14:40:30  root
#added _SIMPLIPC case
#
#Revision 1.6  2001/01/29 15:11:06  root
#using Wall compiler option
#
#Revision 1.5  2000/10/13 13:50:20  root
#LGPL
#using SIMPL_HOME
#
#Revision 1.4  2000/04/17 14:56:26  root
#enhanced for SRR, SIPC and QNX
#
#Revision 1.3  1999/08/05 13:25:13  root
#*** empty log message ***
#
#Revision 1.2  1999/03/29 16:07:30  root
#bug fixes
#
#Revision 1.1  1999/02/04 15:41:15  root
#Initial revision
#
#
#
###############################################
CC=cc
OS=_THISIS_LINUX
VER=_SIMPLIPC

PROGRAM_NAME=
line1 = --------------------------------------------------------------------
line2 = ====================================================================

SIMPL_DIR=$(SIMPL_HOME)
OBJ_DIR=obj
BIN_DIR=../bin

LOCAL_INCL_DIR=../include
INCL_DIR=$(SIMPL_DIR)/include
DEST_BIN_DIR=$(SIMPL_DIR)/bin

BOB_OBJ=\
	$(OBJ_DIR)/bob.o

SENDER_OBJ=\
	$(OBJ_DIR)/sender.o

RECEIVER_OBJ=\
	$(OBJ_DIR)/receiver.o

CDFLAGS=-c \
	-Wall \
        -I $(LOCAL_INCL_DIR)\
        -I $(INCL_DIR)\
	-D$(OS)\
	-D$(VER)

LDFLAGS=\
	-L $(SIMPL_DIR)/lib\
	-lsimpl\
	-lsimplmisc

#========================
# Default targets
#========================
all:\
     title \
     whichOS \
     $(OBJ_DIR) \
     $(BIN_DIR) \
     $(BIN_DIR)/sender \
     $(BIN_DIR)/receiver
	@echo benchmark all

whichOS:
	@echo whichOS = $(OS)

title:
	@echo benchmark build starting

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
$(BIN_DIR)/bob:	$(BOB_OBJ)
	$(CC) -o $(BIN_DIR)/bob $(BOB_OBJ) $(LDFLAGS)
	
$(BIN_DIR)/sender:	$(SENDER_OBJ)
	$(CC) -o $(BIN_DIR)/sender $(SENDER_OBJ) $(LDFLAGS)
	
$(BIN_DIR)/receiver:	$(RECEIVER_OBJ)
	$(CC) -o $(BIN_DIR)/receiver $(RECEIVER_OBJ) $(LDFLAGS)
	
#===================
# Compiles
#===================
$(OBJ_DIR)/bob.o: bob.c
	$(CC) $(CDFLAGS) -o $(OBJ_DIR)/bob.o bob.c

$(OBJ_DIR)/receiver.o: receiver.c
	$(CC) $(CDFLAGS) -o $(OBJ_DIR)/receiver.o receiver.c

$(OBJ_DIR)/sender.o: sender.c
	$(CC) $(CDFLAGS) -o $(OBJ_DIR)/sender.o sender.c

#===================
#  clobber 
#===================
clobber:
	@-rm -f $(OBJ_DIR)/*.o
	@-rm -f $(BIN_DIR)/*.a
	@echo benchmark clobber

#===================
#  install 
#===================
install:\
     title \
     whichOS \
     $(OBJ_DIR) \
     $(BIN_DIR) \
     $(BIN_DIR)/sender \
     $(BIN_DIR)/receiver
	@echo benchmark install
