/*======================================================================

FILE:			fcslay.c

DESCRIPTION:	This program kills a SIMPL process based on its SIMPL
				name.

AUTHOR:			FC Software Inc.
-----------------------------------------------------------------------
    Copyright (C) 2000, 2002, 2004 FCSoftware Inc. 

    This software is in the public domain.
    Permission to use, copy, modify, and distribute this software and its
    documentation for any purpose and without fee is hereby granted, 
    without any conditions or restrictions.
    This software is provided "as is" without express or implied warranty.

    If you discover a bug or add an enhancement contact us on the
    SIMPL project mailing list. 

-----------------------------------------------------------------------

Revision history:
====================================================================
$Log: fcslay.c,v $
Revision 1.2  2007/07/24 19:52:40  bobfcsoft
new contact info

Revision 1.1.1.1  2005/03/27 11:50:55  paul_c
Initial import

Revision 1.9  2004/07/29 11:39:15  root
make compatible with GCC 3.x.x versions of compiler
file->d_name + len + 1 no longer works

Revision 1.8  2004/07/29 10:24:04  root
added FIFO_PATH entry removal if kill fails

Revision 1.7  2003/04/14 13:34:20  root
added MAC_OS_X stuff

Revision 1.6  2002/11/22 16:37:38  root
2.0rc3

====================================================================
======================================================================*/

#ifdef _MAC_OS_X
	#include <db.h>
#endif

#include <dirent.h>
#include <errno.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>

int main(int argc, char **argv)
{
DIR *directory;
struct dirent *file;
int len;
char *fifoPath;
pid_t pid;
int rc;

// check command line
if (argc != 2)
	{
	printf("Incorrect command line\n");
	printf("Use: fcslay simplName\n");
	exit(-1);
	}

// get the fifo directory
fifoPath = getenv("FIFO_PATH");
if (fifoPath == NULL)
	{
	printf("Unable to obtain fifo path-%s\n", strerror(errno));
	exit(-1);
	}

// the length of the simpl name passed in
len = strlen(argv[1]);

// open the fifo directory
directory = opendir(fifoPath);
if (directory == NULL)
	{
	printf("Cannot open fifo directory-%s\n", strerror(errno));
	exit(-1);
	}

// check all fifo directory entries
while ( (file = readdir(directory)) != NULL )
	{
	// check for a match
	if (!memcmp(file->d_name, argv[1], len) && file->d_name[len] == '.')
		{
		// extract the pid from the fifo name
		pid = atoi(&file->d_name[len + 1]);

		// kill this process
		rc=kill(pid, SIGTERM);
		if(rc == -1)
			{
			char name[128];

// remove Receive fifo
			sprintf(name, "%s/%s",		
				fifoPath,
				file->d_name);
			remove(name);

// remove Reply fifo
			sprintf(name, "%s/Y%s",
				fifoPath,
				file->d_name);
			remove(name);
			}
		}
	}

closedir(directory);

return(0);
}
