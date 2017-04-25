/*======================================
	sender.c

Description:
This file contains code for the benchmarking
"sender" task.

-----------------------------------------------------------------------
    Copyright (C) 1998, 2002 FCSoftware Inc. 

    This software is in the public domain.
    Permission to use, copy, modify, and distribute this software and its
    documentation for any purpose and without fee is hereby granted, 
    without any conditions or restrictions.
    This software is provided "as is" without express or implied warranty.

    If you discover a bug or add an enhancement contact us on the 
    SIMPL project mailing list. 

-----------------------------------------------------------------------
======================================*/
/*
 *$Log: sender.c,v $
 *Revision 1.5  2007/07/24 20:08:45  bobfcsoft
 *new comment info
 *
 *Revision 1.4  2005/11/24 21:48:45  bobfcsoft
 *better error handling
 *
 *Revision 1.3  2005/11/17 15:36:05  bobfcsoft
 *intercepted Send failure
 *
 *Revision 1.2  2005/05/19 13:16:31  bobfcsoft
 *sync with 2.3.4
 *
 *Revision 1.13  2005/02/17 12:45:00  root
 *expanded toName size to 80
 *added error logging on name_locate failure
 *
 *Revision 1.12  2002/11/22 16:25:14  root
 *2.0rc3
 *
 *Revision 1.11  2002/11/19 15:00:16  root
 *2.0rc1
 *
 *Revision 1.10  2002/05/29 15:28:56  root
 *enhanced with _SIMPLFCIPC compatibility
 *
 *Revision 1.9  2001/07/05 14:40:50  root
 *added _SIMPLIPC case
 *
 *Revision 1.8  2001/01/29 15:11:31  root
 *using fcipcProto.h instead of ipcProto.h
 *
 *Revision 1.7  2000/10/13 13:52:02  root
 *LGPL
 *
 *Revision 1.6  2000/04/17 14:57:29  root
 *enhanced for SRR, SIPC and QNX
 *
 *Revision 1.5  2000/02/15 18:47:36  root
 *fixed int main warning
 *
 *Revision 1.4  1999/09/09 13:56:56  root
 *added ipcProto.h
 *
 *Revision 1.3  1999/09/09 13:54:55  root
 *cleanup
 *
 *Revision 1.2  1999/03/29 16:06:53  root
 *added msec timing
 *
 *Revision 1.1  1999/02/04 15:44:31  root
 *Initial revision
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <time.h>
#include <sys/timeb.h>

#if 0
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#endif

#define _ALLOC
#include "sender.h"
#undef _ALLOC

int repeats;
int mySize;

#ifdef _FIFO
#include "fcipcProto.h"
#if 0
#include "fcqnxProto.h"
#endif
#endif

#ifdef _SIMPLFCIPC
#include "simpl.h"
#include "simplProto.h"
#endif

#ifdef _SRR
#include "srrProto.h"
#endif

#ifdef _SIPC
#include "sipc_lib.h"
#endif

#ifdef _SIMPLIPC
#include "simpl.h"
#endif

void initialize(int, char **);

/*--------------------------------------
	sender - entry point
--------------------------------------*/
int main(int argc, char **argv, char **envp)
{
static char *fn="sender";
int i;
struct timeb before;
struct timeb after;
int msec;
int x_it=0;

initialize(argc, argv);

ftime(&before);

for(i=0; i<repeats; i++)
	{
#ifdef _FIFO
	loadSend(outArea,strlen(outArea));
	sendMsgx(toPid);
#endif
#ifdef _SIMPLFCIPC
	loadSend(outArea,strlen(outArea));
	sendMsgx(toPid);
#endif
#ifdef _SIMPLIPC
	if(i%10000 == 0) 
		{
		printf("i=%d\n",i);
		fflush(stdout);
		}

	if(Send(toPid, outArea, inArea, mySize, mySize) == -1) 
		{
		x_it=1;
		break;
		}
#endif
#ifdef _SIPC
	Send(toPid, outArea, inArea, mySize, mySize);
#endif
#ifdef _QNX
	Send(toPid, outArea, inArea, mySize, mySize);
#endif
#ifdef _SRR
	SrrSend(toPid, outArea, inArea, mySize, mySize);
#endif
	}

if(x_it == 0)
	{
ftime(&after);
msec=(after.time - before.time)*1000 + (after.millitm - before.millitm);
printf("%s:%d messages took %d ms\n",fn,repeats, msec);
	}
else
	{
printf("%s:exit on Send error\n",fn);
	}

#ifdef _FIFO
detachName();
#endif

#ifdef _SIMPLFCIPC
name_detach();
#endif

#ifdef _SRR
SrrNameDetach(nameid);
#endif

#ifdef _SIPC
name_detach();
#endif

#ifdef _SIMPLIPC
name_detach();
#endif

return(1);

}// end sender

/*============================================
	initialize - entry point
============================================*/
void initialize(int argc, char **argv)
{
static char *fn="initialize";
int i;                          /* loop variable */
char myName[20];
char toName[80];

repeats = 1000;
mySize = 1024;

/*===============================================
  process command args
===============================================*/
for(i=1; i<=argc; ++i)
        {
        char *p = argv[i];

        if(p == NULL) continue;

        if(*p == '-')
                {
                switch(*++p)
                        {
                        case 'n':
                                for(;*p != 0; p++);
				sprintf(myName,"%s",++p);
#ifdef _FIFO
				attachName(myName, 8192, NULL);
#endif

#ifdef _SIMPLFCIPC
				name_attach(myName,8192,NULL);
#endif

#ifdef _QNX
				qnx_name_attach(0, myName);
#endif

#ifdef _SRR
				nameid=SrrNameAttach(myName);
#endif

#ifdef _SIPC
				name_attach(myName,8192);
#endif

#ifdef _SIMPLIPC
				name_attach(myName,NULL);
#endif
                                break;

			case 'r':
                                for(;*p != 0; p++);
				sprintf(toName,"%s",++p);
#ifdef _FIFO
				toPid=nameLocatex(toName);
				if(toPid.slot == -1)
					{
					printf("unable to locate <%s>\n",toName);
#endif

#ifdef _SIMPLFCIPC
				toPid = name_locate(toName);
				if(toPid.slot == -1)
					{
					printf("unable to locate <%s>\n",toName);
#endif

#ifdef _QNX
				toPid = qnx_name_locate(0,toName,1024,NULL);
				if(toPid == -1)
					{
					printf("unable to locate <%s>\n",toName);
#endif
#ifdef _SRR
				toPid = SrrNameLocate(toName);
				if(toPid == -1)
					{
					printf("unable to locate <%s>\n",toName);
#endif
#ifdef _SIPC
				toPid = name_locate(NULL,toName);
				if(toPid == -1)
					{
					printf("unable to locate <%s>\n",toName);
#endif
#ifdef _SIMPLIPC
				toPid = name_locate(toName);
				if(toPid == -1)
					{
					printf("unable to locate <%s>-%s\n",toName,whatsMyError());
#endif
#ifdef _FIFO
					detachName();
#endif

#ifdef _SIMPLFCIPC
					name_detach();
#endif

#ifdef _SRR
					SrrNameDetach(nameid);
#endif
					exit(0);
					}
				break;

			case 't':
                                for(;*p != 0; p++);
				repeats = atoi(++p);
				break;

			case 's':
                                for(;*p != 0; p++);
				mySize = atoi(++p);
				break;

                        default:
				printf("%s:unknown arg %s\n",fn, p);
                                break;
                        }/*end switch*/
                } /* end if *p */
        }/*end for i*/

#ifdef _FIFO
printf("FIFO version\n");
#endif
#ifdef _SIMPLFCIPC
printf("SIMPLFCIPC version\n");
#endif
#ifdef _SRR
printf("SRR version\n");
#endif
#ifdef _SIPC
printf("SIPC version\n");
#endif
#ifdef _SIMPLIPC
printf("SIMPLipc version\n");
#endif

printf("Sender <%s> sending %d messages of %d bytes to receiver <%s>\n",
	myName, repeats, mySize, toName);

} /* end initialize */
