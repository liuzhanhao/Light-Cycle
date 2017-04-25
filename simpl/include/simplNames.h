/*======================================================================

FILE:			simplNames.h

DESCRIPTION:	This file contains the simpl names for various simpl
				processes.

AUTHOR:			FC Software Inc.

-----------------------------------------------------------------------
    Copyright (C) 2000, 2005, 2007 FCSoftware Inc. 

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Lesser General Public
    License as published by the Free Software Foundation; either
    version 2.1 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public
    License along with this library; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

    If you discover a bug or add an enhancement contact us on the
    SIMPL project mailing list. 

-----------------------------------------------------------------------

Revision history:
====================================================================
$Log: simplNames.h,v $
Revision 1.5  2007/09/12 16:31:55  bobfcsoft
enabling RS232 surrogates

Revision 1.4  2007/07/24 20:18:45  bobfcsoft
new contact info

Revision 1.3  2006/01/10 15:28:45  bobfcsoft
v3.0 changes

Revision 1.1.1.1  2005/03/27 11:50:37  paul_c
Initial import

Revision 1.1  2002/11/22 16:23:31  root
Initial revision


====================================================================
======================================================================*/

#ifndef _SIMPL_NAMES_H
#define _SIMPL_NAMES_H

// defines
#define	PROTOCOL_ROUTER				"_simplProtoRouter"
#define	SURROGATE_TCP_R_PARENT		"_tcp_Surrogate_R"
#define	SURROGATE_TCP_S_PARENT		"_tcp_Surrogate_S"
#define	SURROGATE_TCP_R_CHILD		"_tcp_Surrogate_r"
#define	SURROGATE_TCP_S_CHILD		"_tcp_Surrogate_s"

#define	RS232_WRITER				"_rs232_Writer"
#define	RS232_READER				"_rs232_Reader"
#define	SURROGATE_RS232_R_PARENT	"_rs232_Surrogate_R"
#define	SURROGATE_RS232_S_PARENT	"_rs232_Surrogate_S"
#define	SURROGATE_RS232_R_CHILD		"_rs232_Surrogate_r"
#define	SURROGATE_RS232_S_CHILD		"_rs232_Surrogate_s"

#endif
