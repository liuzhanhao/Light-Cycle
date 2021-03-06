/*************************************************************
FILE:	relayProto.h	

DESCRIPTION:	
This file contains prototypes for relay app.

AUTHOR:			R.D. Findlay

-----------------------------------------------------------------------
    Copyright (C) 2000, 2002 FCSoftware Inc. 

    This software is in the public domain.
    Permission to use, copy, modify, and distribute this software and its
    documentation for any purpose and without fee is hereby granted, 
    without any conditions or restrictions.
    This software is provided "as is" without express or implied warranty.

    If you discover a bug or add an enhancement here's how to reach us: 

	fcsoft@attcanada.ca
-----------------------------------------------------------------------
Revision history:
=======================================================
$Log: sandboxRelayProto.h,v $
Revision 1.1  2007/07/03 18:28:04  bobfcsoft
added sandboxRelay

Revision 1.2  2002/12/03 21:18:53  root
v2.0 compatible

Revision 1.1  2002/12/03 19:52:28  root
Initial revision

=======================================================

*************************************************************/

#ifndef _RELAY_PROTO_DEF
#define _RELAY_PROTO_DEF

void initialize(int, char **);
void myUsage();

int sb_name_attach(const char *myName);
void sb_name_detach();
int sb_name_locate(char *localName);
int _sb_local_name_locate(const char *processName);
int _sb_getFifoName(const char *simplName, char *fifoName);
int sbSend(int fd, void *outBuffer, void *inBuffer, unsigned outBytes, unsigned inBytes);

#endif
