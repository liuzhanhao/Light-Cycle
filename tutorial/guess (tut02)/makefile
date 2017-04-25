CC=gcc
OS=_THISIS_LINUX
VER=_SIMPLIPC
SIMPL_DIR=${SIMPL_HOME}
INCL_DIR=${SIMPL_DIR}/include
CDFLAGS=-c -Wall -I ${INCL_DIR} -D${OS} -D${VER}
LDFLAGS=-L ${SIMPL_DIR}/lib -lsimpl 
LIBS=
SOURCES=admin worker

all: ${SOURCES}

admin.o: message.h admin.c
	${CC} ${CDFLAGS} admin.c -o admin.o

admin: admin.o
	${CC} admin.o -o admin ${LDFLAGS}

worker.o: message.h worker.c
	${CC} ${CDFLAGS} worker.c -o worker.o

worker: worker.o
	${CC} worker.o -o worker ${LDFLAGS}

# CLEAN UP

clean:
	@rm -f *.o *~ ${SOURCES}
