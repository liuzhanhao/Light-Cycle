#===============================================================
#
#  Makefile for surrogate/rs232 tree
#
#-----------------------------------------------------------------------
#    Copyright (C) 2005 FCSoftware Inc. 
#
#    This software is in the public domain.
#    Permission to use, copy, modify, and distribute this software and its
#    documentation for any purpose and without fee is hereby granted, 
#    without any conditions or restrictions.
#    This software is provided "as is" without express or implied warranty.#
#
#    If you discover a bug or add an enhancement contact us on the
#    SIMPL project mailing list.
#-----------------------------------------------------------------------
#===============================================================
#$Log: Makefile,v $
#Revision 1.2  2008/05/13 00:33:43  bobfcsoft
#no test dir
#
#Revision 1.1  2008/04/21 17:12:48  johnfcsoft
#inital
#

#===============================================================

PROJECT=SIMPL

SRC_DIR=src
TEST_DIR=test

#===================================
# entry point for simple make
#===================================
all:
	@echo "$(PROJECT) surrogate/rs232 build <all> starting"
	@echo `date`
	@cd $(SRC_DIR); make -i
	@echo "$(PROJECT) surrogate/rs232 <all> done"
	@echo `date`

#===================================
# to force a total rebuild
#===================================
clobber:
	@echo "$(PROJECT) surrogate/rs232 <clobber> starting"
	@cd $(SRC_DIR); make -s clobber
	@echo "$(PROJECT) surrogate/rs232 <clobber> done"

#===================================
# to move into master area
#===================================
install:
	@echo "$(PROJECT) surrogate/rs232 build <install> starting"
	@echo `date`
	@cd $(SRC_DIR); make -i install
	@echo "$(PROJECT) surrogate/rs232 <install> done"
	@echo `date`
