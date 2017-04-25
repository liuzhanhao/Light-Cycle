#=======================================================================
#
# FILE:			Makefile
#
# DESCRIPTION:	This make file produces the tcp surrogate program.
#
# AUTHOR:		FC Software Inc.
#-----------------------------------------------------------------------
#    Copyright (C) 2005 FCSoftware Inc. 
#
#    This software is in the public domain.
#    Permission to use, copy, modify, and distribute this software and its
#    documentation for any purpose and without fee is hereby granted, 
#    without any conditions or restrictions.
#    This software is provided "as is" without express or implied warranty.
#
#    If you discover a bug or add an enhancement here's how to reach us: 
#
#	fcsoft@allstream.net
#-----------------------------------------------------------------------
#
# Revision history:
# ======================================================================
# $Log: Makefile,v $
# Revision 1.3  2008/04/21 13:42:28  johnfcsoft
# SUR_CHR set as default
#
# Revision 1.2  2007/01/09 15:17:39  bobfcsoft
# restoring from tcp_x
#
# Revision 1.5  2006/01/10 15:32:22  bobfcsoft
# v3.0 changes
#
# Revision 1.4  2005/12/20 15:26:18  bobfcsoft
# more 3.0 prerelease code
#
# Revision 1.3  2005/11/24 21:46:58  bobfcsoft
# 2nd 3.0 prerelease
#
# Revision 1.1.1.1  2005/03/27 11:50:58  paul_c
# Initial import
#
# Revision 1.2  2003/04/14 14:07:17  root
# enabled MAC_OS_X stuff
#
#
#=======================================================================

#====================================================================
# definitions
#====================================================================

#MSG_TYPE = SUR_BIN
MSG_TYPE = SUR_CHR

MSG_BUFFERING = NOT_BUFFERED
#MSG_BUFFERING = BUFFERED

CC = cc

OBJ_DIR = ./obj
BIN_DIR = ../bin
LIB_DIR = ../../../lib
INC_DIR = ../../../include
LOCAL_INC_DIR = ../include
INSTALL_BIN_DIR=../../../bin

SURROGATE_OBJ =	\
	$(OBJ_DIR)/surrogate.o \
	$(OBJ_DIR)/surrogateInit.o \
	$(OBJ_DIR)/surrogate_R.o \
	$(OBJ_DIR)/surrogate_r.o \
	$(OBJ_DIR)/surrogate_S.o \
	$(OBJ_DIR)/surrogate_s.o \
	$(OBJ_DIR)/surrogateUtils.o

CDFLAGS = -c -D$(MSG_BUFFERING) -D$(MSG_TYPE) -O -Wall -I$(INC_DIR) -I$(LOCAL_INC_DIR) -o
LDFLAGS = -L$(LIB_DIR) -lsimpl -lsimplmisc

#=====================================================================
# Default targets
#=====================================================================
all: \
    title \
    $(OBJ_DIR) \
    $(BIN_DIR) \
    $(BIN_DIR)/surrogate
	@echo surrogate all

title:
	@echo surrogate starting

$(OBJ_DIR):
	mkdir ./obj
	chmod a+w ./obj

$(BIN_DIR):
	mkdir ../bin
	chmod a+w ../bin

#=====================================================================
# linking
#=====================================================================
$(BIN_DIR)/surrogate: $(SURROGATE_OBJ)
	$(CC) -o $@ $(SURROGATE_OBJ) $(LDFLAGS)
	
#=====================================================================
# compiling
#=====================================================================
$(OBJ_DIR)/surrogate.o: surrogate.c
	$(CC) $(CDFLAGS) $@ $<

$(OBJ_DIR)/surrogateInit.o: surrogateInit.c
	$(CC) $(CDFLAGS) $@ $<

$(OBJ_DIR)/surrogate_R.o: surrogate_R.c
	$(CC) $(CDFLAGS) $@ $<

$(OBJ_DIR)/surrogate_r.o: surrogate_r.c
	$(CC) $(CDFLAGS) $@ $<

$(OBJ_DIR)/surrogate_S.o: surrogate_S.c
	$(CC) $(CDFLAGS) $@ $<

$(OBJ_DIR)/surrogate_s.o: surrogate_s.c
	$(CC) $(CDFLAGS) $@ $<

$(OBJ_DIR)/surrogateUtils.o: surrogateUtils.c
	$(CC) $(CDFLAGS) $@ $<

#=====================================================================
#  cleanup
#=====================================================================
clobber: clean
clean:
	@-rm -f $(OBJ_DIR)/*.o
	@-rm -f $(BIN_DIR)/*
	@echo surrogate clean/clobber

#=====================================================================
#  install 
#=====================================================================
install: \
    title \
    $(OBJ_DIR) \
    $(BIN_DIR) \
    $(BIN_DIR)/surrogate
	-cp $(BIN_DIR)/surrogate $(INSTALL_BIN_DIR)/surrogateTcp
	@echo surrogate install

#===================
#  debug
#===================
debug:
	make install DE=-g
	@echo surrogate debug
