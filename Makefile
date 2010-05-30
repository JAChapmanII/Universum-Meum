SHELL=/bin/sh
SRCDIR=src
DOCDIR=doc
OBJDIR=obj
BINDIR=bin
SRC=main.d
PROG=Universum-Meum

DD=rebuild
DFLAGS=-no-export-dynamic -lldl

all: universum-meum

universum-meum: clean release

release:
	${DD} -D -Dq${DOCDIR} -oq${OBJDIR} -of${BINDIR}/${PROG} \
		${DFLAGS} -O -release ${SRCDIR}/${SRC}

debug:
	${DD} -D -Dq${DOCDIR} -oq${OBJDIR} -of${BINDIR}/${PROG} \
		${DFLAGS} -g -debug ${SRCDIR}/${SRC}

profile:
	${DD} -D -Dq${DOCDIR} -oq${OBJDIR} -of${BINDIR}/${PROG} \
		${DFLAGS} -g -debug -profile ${SRCDIR}/${SRC}

clean:
	rm -f obj/*
	rm -f bin/*
	rm -f doc/*

