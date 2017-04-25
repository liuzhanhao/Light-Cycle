#=======================================================================
#
# FILE:			Makefile
#
# DESCRIPTION:	This make file produces some test programs.
#
# AUTHOR:		FC Software Inc.
#-----------------------------------------------------------------------
#    Copyright (C) 2002 FCSoftware Inc. 
#
#    This software is in the public domain.
#    Permission to use, copy, modify, and distribute this software and its
#    documentation for any purpose and without fee is hereby granted, 
#    without any conditions or restrictions.
#    This software is provided "as is" without express or implied warranty.
#
#    If you discover a bug or add an enhancement here's how to reach us: 
#
#	fcsoft@attcanada.ca
#-----------------------------------------------------------------------
#
# Revision history:
# ======================================================================
# $Log: Makefile,v $
# Revision 1.2  2005/05/26 14:18:05  bobfcsoft
# added sender2/receive2
#
# Revision 1.1.1.1  2005/03/27 11:51:03  paul_c
# Initial import
#
# Revision 1.3  2003/04/23 20:39:40  root
# added test0 and test1 targets
#
# Revision 1.2  2003/04/14 14:01:07  root
# enabled MAC_OS_X stuff
#
# Revision 1.1  2002/11/22 16:41:13  root
# Initial revision
#
#
#=======================================================================

#====================================================================
# definitions
#====================================================================
CC = cc
DE = DE

OBJ_DIR = ./obj
BIN_DIR = ../bin
LIB_DIR = ../../../lib
INC_DIR = ../../../include

RECEIVER_OBJ =	\
			$(OBJ_DIR)/receiver.o

SENDER_OBJ =	\
			$(OBJ_DIR)/sender.o

# release flags
COMFLAGS = -O2 -pipe
#COMFLAGS = -mno-486 -O2 -pipe
# debug flags
#COMFLAGS = -g -pipe
# profile flags
#COMFLAGS = -g -pipe -a -pg

CDFLAGS = $(COMFLAGS) -c -Wall -I$(INC_DIR) -o
LDFLAGS = $(COMFLAGS) -L$(LIB_DIR) -lsimpl -lsimplmisc

#=====================================================================
# Default target: all
#=====================================================================
all: install

install:\
    title \
    $(OBJ_DIR) \
    $(BIN_DIR) \
    $(BIN_DIR)/receiver \
    $(BIN_DIR)/sender
	- cp go $(BIN_DIR)/
	- cp stop $(BIN_DIR)/
	@echo test all

title:
	@echo test starting

$(OBJ_DIR):
	mkdir ./obj
	chmod a+w ./obj

$(BIN_DIR):
	mkdir ../bin
	chmod a+w ../bin

test0:
	ln -fs receiver0.c receiver.c
	ln -fs sender0.c sender.c
	make install

test1:
	ln -fs receiver1.c receiver.c
	ln -fs sender1.c sender.c
	make install

test2:
	ln -fs receiver2.c receiver.c
	ln -fs sender2.c sender.c
	make install

#=====================================================================
# linking
#=====================================================================
$(BIN_DIR)/receiver: $(RECEIVER_OBJ)
	$(CC) -o $@ $< $(LDFLAGS)

$(BIN_DIR)/sender: $(SENDER_OBJ)
	$(CC) -o $@ $< $(LDFLAGS)
	
#=====================================================================
# compiling
#=====================================================================
$(OBJ_DIR)/receiver.o: receiver.c
	$(CC) $(CDFLAGS) $@ $<

$(OBJ_DIR)/sender.o: sender.c
	$(CC) $(CDFLAGS) $@ $<

#=====================================================================
#  cleanup
#=====================================================================
clobber: clean
clean:
	@-rm -f $(OBJ_DIR)/*.o
	@-rm -f $(BIN_DIR)/receiver
	@-rm -f $(BIN_DIR)/sender
	@echo test clean/clobber
