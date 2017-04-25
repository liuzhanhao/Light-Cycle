#=======================================================================
#
# FILE:			Makefile
#
# DESCRIPTION:	This make file produces the RS232 surrogate program.
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
#    If you discover a bug or add an enhancement contact us on the
#    SIMPL project mailing list.
#-----------------------------------------------------------------------
# Revision history:
# $Log: Makefile,v $
# Revision 1.1  2008/04/21 17:17:01  johnfcsoft
# initial
#
#
#=======================================================================

#====================================================================
# definitions
#====================================================================

//MSG_TYPE = SUR_BIN
MSG_TYPE = SUR_CHR

CC = cc

OBJ_DIR = ./obj
BIN_DIR = ../bin
LIB_DIR = ../../../lib
INC_DIR = ../../../include
LOCAL_INC_DIR = ../include
INSTALL_BIN_DIR=../../../bin

SURROGATE_OBJ =	\
	$(OBJ_DIR)/surrogate.o	\
	$(OBJ_DIR)/surrogateInit.o \
	$(OBJ_DIR)/surrogate_R.o \
	$(OBJ_DIR)/surrogate_S.o \
	$(OBJ_DIR)/surrogate_r.o \
	$(OBJ_DIR)/surrogate_s.o \
	$(OBJ_DIR)/surrogateUtils.o

RS232_OBJ = \
	$(OBJ_DIR)/rs232_rw.o

CDFLAGS = -c -D$(MSG_TYPE) -O -Wall -I$(INC_DIR) -I$(LOCAL_INC_DIR) -o
LDFLAGS = -L$(LIB_DIR) -lsimpl -lsimplmisc

#=====================================================================
# Default targets
#=====================================================================
all: \
    title \
    $(OBJ_DIR) \
    $(BIN_DIR) \
    $(BIN_DIR)/surrogate \
	$(BIN_DIR)/rs232_rw
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

$(BIN_DIR)/rs232_rw: $(RS232_OBJ)
	$(CC) -o $@ $(RS232_OBJ) $(LDFLAGS)
	
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

$(OBJ_DIR)/rs232_rw.o: rs232_rw.c
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
    $(BIN_DIR)/surrogate \
	$(BIN_DIR)/rs232_rw
	-cp $(BIN_DIR)/surrogate $(INSTALL_BIN_DIR)/surrogateRS232
	-cp $(BIN_DIR)/rs232_rw $(INSTALL_BIN_DIR)/rs232_rw
	@echo surrogate install

#===================
#  debug
#===================
debug:
	make install DE=-g
	@echo surrogate debug
