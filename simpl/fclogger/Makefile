#================================================
#
#    fclogger top level build
#
#-----------------------------------------------------------------------
#    Copyright (C) 2002 FCSoftware Inc. 
#
#    This software is in the public domain.
#    Permission to use, copy, modify, and distribute this software and its
#    documentation for any purpose and without fee is hereby granted, 
#    without any conditions or restrictions.
#    This software is provided "as is" without express or implied warranty.
#
#    If you discover a bug or add an enhancement contact us on the 
#    SIMPL mailing list. 
#
#-----------------------------------------------------------------------
#
#$Log: Makefile,v $
#Revision 1.2  2007/07/24 20:36:38  bobfcsoft
#new contact info
#
#Revision 1.1.1.1  2005/03/27 11:50:39  paul_c
#Initial import
#
#Revision 1.3  2003/04/23 20:43:35  root
#added support for dynamic library
#
#Revision 1.2  2002/11/22 16:26:24  root
#2.0rc3
#
#Revision 1.1  2002/06/12 18:17:51  root
#Initial revision
#
#

PROJECT=SIMPL
TASK=fclogger

SRC_DIR=src
TEST_DIR=test

#===================================
# entry point for simple make
#===================================
all:
	@echo "$(PROJECT) $(TASK) build <all> starting"
	@echo `date`
	@cd $(SRC_DIR); make -i
	@cd $(TEST_DIR); make -i
	@echo "$(PROJECT) $(TASK) <all> done"
	@echo `date`

#=================================
# to force a total rebuild
#=================================
clobber:
	@echo "$(PROJECT) $(TASK) <clobber> starting"
	@cd $(SRC_DIR); make -s clobber
	@cd $(TEST_DIR); make -s clobber
	@echo "$(PROJECT) $(TASK) <clobber> done"

#========================
# to move into master area
#========================
install:
	@echo "$(PROJECT) $(TASK) build <install> starting"
	@echo `date`
	@cd $(SRC_DIR); make -i install
	@cd $(TEST_DIR); make -i install
	@echo "$(PROJECT) $(TASK) <install> done"
	@echo `date`

#========================
# to move into master area
#========================
dynamic:
	@echo "$(PROJECT) $(TASK) build <dynamic> starting"
	@echo `date`
	@cd $(SRC_DIR); make -i dynamic
	@cd $(TEST_DIR); make -i install
	@echo "$(PROJECT) $(TASK) <dynamic> done"
	@echo `date`
