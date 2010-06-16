SHELL=/bin/sh
SRCDIR=src
DOCDIR=doc
OBJDIR=obj
BINDIR=bin
SRC=main.cpp
PROG=Universum-Meum

CC=g++
CFLAGS=-lSDL -lGL -pipe

all: ${PROG}

${PROG}: debug

full: dirs clean release documentation

release:
	${CC} -o ${BINDIR}/${PROG} ${CFLAGS} -O ${SRCDIR}/${SRC}

debug: dirs clean
	${CC} -o ${BINDIR}/${PROG}-debug ${CFLAGS} -g ${SRCDIR}/${SRC}

profile:
	${CC} -o ${BINDIR}/${PROG}-profile ${CFLAGS} -g ${SRCDIR}/${SRC}

documentation:
	${CC} -p -D -Dq${DOCDIR} -I${SRCDIR} ${SRCDIR}/${SRC}

dirs:
	mkdir -p ${SRCDIR}
	mkdir -p ${DOCDIR}
	mkdir -p ${OBJDIR}
	mkdir -p ${BINDIR}

clean:
	rm -f ${OBJDIR}/*
	rm -f ${BINDIR}/*
	rm -f ${DOCDIR}/*

