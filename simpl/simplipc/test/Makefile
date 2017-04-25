#=======================================================================
#
# FILE:			Makefile
#
# DESCRIPTION:	This is the local test make file.
#
# AUTHOR:		FC Software Inc.
#-----------------------------------------------------------------------
#    Copyright (C) 2000 FCSoftware Inc. 
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
#    If you discover a bug or add an enhancement here's how to reach us: 
#
#	fcsoft@attcanada.ca
#-----------------------------------------------------------------------
#
# Revision history:
# ======================================================================
# $Log: Makefile,v $
# Revision 1.1.1.1  2005/03/27 11:50:54  paul_c
# Initial import
#
# Revision 1.3  2003/04/16 00:05:57  root
# added install target
#
# Revision 1.2  2003/04/14 13:43:53  root
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

CC = cc

OBJ_DIR = ./obj
LIB_DIR = ../../lib
INC_DIR = ../../include
BIN_DIR = ../bin

SENDER_OBJ = \
	$(OBJ_DIR)/sender.o

RECEIVER_OBJ = \
	$(OBJ_DIR)/receiver.o

CDFLAGS = -c -O -Wall -I$(INC_DIR)
LDFLAGS = -L$(LIB_DIR) -lsimpl

#=====================================================================
# Default targets
#=====================================================================
all: \
	title \
	$(OBJ_DIR) \
	$(BIN_DIR) \
	$(BIN_DIR)/sender \
	$(BIN_DIR)/receiver
	@echo simplipc/test all

title:
	@echo simplipc/test build starting

$(OBJ_DIR):
	mkdir obj
	chmod a+w obj

$(BIN_DIR):
	mkdir ../bin
	chmod a+w ../bin

#========================
# Link
#========================
$(BIN_DIR)/sender: $(SENDER_OBJ)
	$(CC) -o $@ $? $(LDFLAGS)
	
$(BIN_DIR)/receiver: $(RECEIVER_OBJ)
	$(CC) -o $@ $? $(LDFLAGS)
	
#===================
# Compiles
#===================
$(OBJ_DIR)/receiver.o: receiver.c
	$(CC) $(CDFLAGS) -o $@ $<

$(OBJ_DIR)/sender.o: sender.c
	$(CC) $(CDFLAGS) -o $@ $<

#===================
#  clobber 
#===================
clobber: clean
clean:
	@-rm -f $(OBJ_DIR)/*.o
	@-rm -f $(BIN_DIR)/sender
	@-rm -f $(BIN_DIR)/receiver
	@echo simplipc/test clobber

install: \
    title \
    $(OBJ_DIR) \
    $(BIN_DIR) \
    $(BIN_DIR)/sender \
    $(BIN_DIR)/receiver
	@echo simplipc/test install

