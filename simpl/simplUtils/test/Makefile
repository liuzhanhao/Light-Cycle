###############################################
#
# Makefile - for testBinhex
#
#-----------------------------------------------------------------------
#    Copyright (C) 1999, 2002 FCSoftware Inc. 
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
#$Log: Makefile,v $
#Revision 1.1.1.1  2005/03/27 11:50:58  paul_c
#Initial import
#
#Revision 1.2  2003/04/16 00:03:29  root
#added install target
#
#Revision 1.1  2003/04/14 13:32:01  root
#Initial revision
#
#
###############################################

CC=cc
DE=

PROGRAM_NAME=
line1 = --------------------------------------------------------------------
line2 = ====================================================================

OBJ_DIR=./obj
BIN_DIR=../bin
INCL_DIR=../../include
DEST_BIN_DIR=../../bin

TEST_BIN_STR_OBJ = \
	$(OBJ_DIR)/testbinstr.o

CDFLAGS=\
	-c \
	$(DE) \
	-Wall \
	-I $(INCL_DIR)

LDFLAGS=\
	-L../../lib\
	-lsimplmisc

#========================
# Default targets
#========================
all: \
     title \
     $(OBJ_DIR) \
     $(LIB_DIR) \
     $(BIN_DIR) \
     $(BIN_DIR)/testbinstr
	@echo testbinstr all

title:
	@echo test bin hexc build starting

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
$(BIN_DIR)/testbinstr:	$(TEST_BIN_STR_OBJ)
	$(CC) -o $@ $? $(LDFLAGS)
	
#===================
# Compiles
#===================
$(OBJ_DIR)/testbinstr.o:	testbinstr.c
	$(CC) $(CDFLAGS) -o $@ $<

#===================
#  clobber 
#===================
clobber:
	@-rm -f $(OBJ_DIR)/testbinstr.o
	@-rm -f $(BIN_DIR)/testbinstr
	@echo testbinstr clobber

install: \
     title \
     $(OBJ_DIR) \
     $(LIB_DIR) \
     $(BIN_DIR) \
     $(BIN_DIR)/testbinstr
	@echo testbinstr install

#===================
#  debug
#===================
debug:
	make all DE=-g
	@echo testbinstr debug
