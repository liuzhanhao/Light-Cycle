#===============================================================
#
#  Makefile for simpl/surrogates tree
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
#Revision 1.4  2008/04/21 17:10:27  johnfcsoft
#added rs232 make
#
#Revision 1.3  2006/01/10 15:30:40  bobfcsoft
#no more tcp_x in v3.0
#
#Revision 1.2  2005/11/12 12:23:41  bobfcsoft
#allow tcp_x
#
#Revision 1.1.1.1  2005/03/27 11:50:58  paul_c
#Initial import
#
#Revision 1.1  2002/11/22 16:38:21  root
#Initial revision
#
#===============================================================

PROJECT=SIMPL

PROTOCOL_ROUTER_DIR=protocol_router
TCP_PROTOCOL_DIR=tcp
RS232_PROTOCOL_DIR=rs232
#===================================
# entry point for simple make
#===================================
all:
	@echo "$(PROJECT) surrogate build <all> starting"
	@echo `date`
	@cd $(PROTOCOL_ROUTER_DIR); make -i
	@cd $(TCP_PROTOCOL_DIR); make -i
	@cd $(RS232_PROTOCOL_DIR); make -i
	@echo "$(PROJECT) surrogate <all> done"
	@echo `date`

#===================================
# to force a total rebuild
#===================================
clobber:
	@echo "$(PROJECT) surrogate <clobber> starting"
	@cd $(PROTOCOL_ROUTER_DIR); make -s clobber
	@cd $(TCP_PROTOCOL_DIR); make -s clobber
	@cd $(RS232_PROTOCOL_DIR); make -s clobber
	@echo "$(PROJECT) surrogate <clobber> done"

#===================================
# to move into master area
#===================================
install:
	@echo "$(PROJECT) surrogate build <install> starting"
	@echo `date`
	@cd $(PROTOCOL_ROUTER_DIR); make -i install
	@cd $(TCP_PROTOCOL_DIR); make -i install
	@cd $(RS232_PROTOCOL_DIR); make -i install
	@echo "$(PROJECT) surrogate <install> done"
	@echo `date`
