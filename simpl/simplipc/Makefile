#================================================
#
#    simplipc top level build
#
#-----------------------------------------------------------------------
#    Copyright (C) 2002 FCSoftware Inc. 
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
#$Log: Makefile,v $
#Revision 1.1.1.1  2005/03/27 11:50:50  paul_c
#Initial import
#
#Revision 1.2  2003/04/23 20:44:55  root
#added support for dynamic library
#
#Revision 1.1  2002/06/12 18:38:05  root
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
