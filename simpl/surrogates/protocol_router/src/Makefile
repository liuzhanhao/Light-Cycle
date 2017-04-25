#=======================================================================
#
# FILE:			Makefile
#
# DESCRIPTION:	This make file produces the protocolRouter program.
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
# Revision 1.1.1.1  2005/03/27 11:50:58  paul_c
# Initial import
#
# Revision 1.1  2002/11/22 16:39:09  root
# Initial revision
#
#
#=======================================================================

#====================================================================
# definitions
#====================================================================
CC = cc
DE =

OBJ_DIR = ./obj
BIN_DIR = ../bin
LIB_DIR = ../../../lib
INC_DIR = ../../../include
INSTALL_BIN_DIR=../../../bin

PROTOCOL_ROUTER_OBJ =	\
			$(OBJ_DIR)/protocolRouter.o

CDFLAGS = -c $(DE) -O -Wall -I$(INC_DIR) -o
LDFLAGS = -L$(LIB_DIR) -lsimpl

#=====================================================================
# Default targets
#=====================================================================
all: \
    title \
    $(OBJ_DIR) \
    $(BIN_DIR) \
    $(BIN_DIR)/protocolRouter 
	@echo protocolRouter all

title:
	@echo protocolRouter starting

description:
	@(\
	echo;\
	echo "$(line1)";\
	echo "Compiling $(PROGRAM_NAME) module -> $<";\
	echo )

$(OBJ_DIR):
	mkdir ./obj
	chmod a+w ./obj

$(BIN_DIR):
	mkdir ../bin
	chmod a+w ../bin

#=====================================================================
# linking
#=====================================================================
$(BIN_DIR)/protocolRouter: $(PROTOCOL_ROUTER_OBJ)
	$(CC) -o $@ $? $(LDFLAGS)
	
#=====================================================================
# compiling
#=====================================================================
$(OBJ_DIR)/protocolRouter.o : protocolRouter.c
	$(CC) $(CDFLAGS) $@ $<

#=====================================================================
#  cleanup
#=====================================================================
clobber: clean
clean:
	@-rm -f $(OBJ_DIR)/*.o
	@-rm -f $(BIN_DIR)/*
	@echo protocolRouter clean/clobber

#=====================================================================
#  install 
#=====================================================================
install: \
    title \
    $(OBJ_DIR) \
    $(BIN_DIR) \
    $(BIN_DIR)/protocolRouter 
	-cp $(BIN_DIR)/protocolRouter $(INSTALL_BIN_DIR)
	@echo protocolRouter install

#===================
#  debug
#===================
debug:
	make install DE=-g
	@echo protocolRouter debug
