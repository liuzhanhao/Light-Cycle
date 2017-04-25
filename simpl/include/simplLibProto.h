/*======================================================================

FILE:			simplLibProto.h

DESCRIPTION:	This file contains function prototype definitions
				used by the simpl source code.

AUTHOR:			FC Software Inc.

-----------------------------------------------------------------------
    Copyright (C) 2000, 2002, 2007 FCSoftware Inc. 

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
$Log: simplLibProto.h,v $
Revision 1.4  2007/07/24 20:18:45  bobfcsoft
new contact info

Revision 1.3  2005/11/12 12:18:55  bobfcsoft
added postMsg/readReply functions

Revision 1.2  2005/09/26 15:46:12  bobfcsoft
proxy/trigger changes

Revision 1.1.1.1  2005/03/27 11:50:37  paul_c
Initial import

Revision 1.4  2003/12/08 16:10:04  root
added detachShmem function

Revision 1.3  2002/11/22 16:22:49  root
2.0rc3

Revision 1.2  2002/11/22 15:13:58  root
2.0rc2

Revision 1.1  2002/11/19 14:01:15  root
Initial revision


====================================================================
======================================================================*/

#ifndef _SIMPL_LIB_PROTO_H
#define _SIMPL_LIB_PROTO_H

#include <simplDefs.h>

// name locate functions
int _simpl_local_name_locate(const char *);
int _simpl_get_hostname(char *);
int _simpl_net_name_locate(const char *, const char *, const char *);
int _simpl_getNames(char *, char *, char *, char *);

// message shared memory functions
int _simpl_createShmem(unsigned);
int _simpl_detachShmem(void);
int _simpl_deleteShmem(void);

// fifo functions
int _simpl_statFifoName(const char *);
int _simpl_getFifoName(const char *, char *);
int _simpl_readFifoMsg(int, char *);

// miscellaneous functions
int saveSenderId(char *);
int removeSenderId(char *);
int ReplyError(char *);
inline void _simpl_setErrorCode(int);
void _simpl_log(char *, ...);
inline int _simpl_check(void);
void _simpl_initSignalHandling(void);
void _simpl_hndlSignals(int);
void _simpl_exitFunc(void);
int _simpl_postMsg(int, void *, unsigned, unsigned);
int _simpl_readReply(void *, unsigned);

#endif
