#===============================================================
#
#  Makefile for fc/fcUtils tree
#
#-----------------------------------------------------------------------
#    Copyright (C) 1999 FCSoftware Inc. 
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
#	fcsoft@netcom.ca
#-----------------------------------------------------------------------
#===============================================================
#$Log: Makefile,v $
#Revision 1.1.1.1  2005/03/27 11:50:54  paul_c
#Initial import
#
#Revision 1.4  2003/04/23 20:45:37  root
#added support for dynamic libraries
#
#Revision 1.3  2003/04/14 13:25:30  root
#added test directory
#
#Revision 1.2  2000/10/04 02:02:01  root
#LGPL'd
#
#Revision 1.1  1999/11/04 15:42:43  root
#Initial revision
#
#===============================================================

PROJECT=SIMPL

SRC_DIR=src
TEST_DIR=test

#===================================
# entry point for simple make
#===================================
all:
	@echo "$(PROJECT) fcUtils build <all> starting"
	@echo `date`
	@cd $(SRC_DIR); make -i 
	@cd $(TEST_DIR); make -i 
	@echo "$(PROJECT) fcUtils <all> done"
	@echo `date`

#===================================
# to force a total rebuild
#===================================
clobber:
	@echo "$(PROJECT) fcUtils <clobber> starting"
	@cd $(SRC_DIR); make -s clobber
	@cd $(TEST_DIR); make -s clobber
	@echo "$(PROJECT) fcUtils <clobber> done"

#===================================
# to move into master area
#===================================
install:
	@echo "$(PROJECT) simplUtils build <install> starting"
	@echo `date`
	@cd $(SRC_DIR); make -i install
	@cd $(TEST_DIR); make -i install
	@echo "$(PROJECT) simplUtils <install> done"
	@echo `date`

dynamic:
	@echo "$(PROJECT) simplUtils build <dynamic> starting"
	@echo `date`
	@cd $(SRC_DIR); make -i dynamic
	@cd $(TEST_DIR); make -i install
	@echo "$(PROJECT) simplUtils <dynamic> done"
	@echo `date`
