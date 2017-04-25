#===============================================================
#
#  Makefile for surrogate/tcp tree
#
#-----------------------------------------------------------------------
#    Copyright (C) 2007 FCSoftware Inc. 
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
#    If you discover a bug or add an enhancement contact us on the
#    SIMPL project mailing list. 
#
#-----------------------------------------------------------------------
#===============================================================
#$Log: Makefile,v $
#Revision 1.2  2007/02/08 19:18:40  bobfcsoft
#new comment block
#
#Revision 1.1  2005/11/11 20:50:34  bobfcsoft
#prerelease for 3.0
#
#Revision 1.1.1.1  2005/03/27 11:50:58  paul_c
#Initial import
#
#Revision 1.2  2003/06/24 17:48:55  root
#fixed test target to test0
#
#Revision 1.1  2002/11/22 16:38:49  root
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
	@echo "$(PROJECT) surrogate/tcp build <all> starting"
	@echo `date`
	@cd $(SRC_DIR); make -i 
	@cd $(TEST_DIR); make -i  test0
	@echo "$(PROJECT) surrogate/tcp <all> done"
	@echo `date`

#===================================
# to force a total rebuild
#===================================
clobber:
	@echo "$(PROJECT) surrogate/tcp <clobber> starting"
	@cd $(SRC_DIR); make -s clobber
	@cd $(TEST_DIR); make -s clobber
	@echo "$(PROJECT) surrogate/tcp <clobber> done"

#===================================
# to move into master area
#===================================
install:
	@echo "$(PROJECT) surrogate/tcp build <install> starting"
	@echo `date`
	@cd $(SRC_DIR); make -i install
	@cd $(TEST_DIR); make -i test0
	@echo "$(PROJECT) surrogate/tcp <install> done"
	@echo `date`
