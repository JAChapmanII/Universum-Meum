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

universum-meum: dirs clean release

release:
	${DD} -D -Dq${DOCDIR} -oq${OBJDIR} -of${BINDIR}/${PROG} -I${SRCDIR}/\
		${DFLAGS} -O -release ${SRCDIR}/${SRC}

debug:
	${DD} -D -Dq${DOCDIR} -oq${OBJDIR} -of${BINDIR}\${PROG} -I${SRCDIR}/\
		${DFLAGS} -g -debug ${SRCDIR}/${SRC}

profile:
	${DD} -D -Dq${DOCDIR} -oq${OBJDIR} -of${BINDIR}/${PROG} -I${SRCDIR}/\
		${DFLAGS} -g -debug -profile ${SRCDIR}/${SRC}

dirs:
	mkdir -p ${SRCDIR}
	mkdir -p ${DOCDIR}
	mkdir -p ${OBJDIR}
	mkdir -p ${BINDIR}

clean:
	rm -f obj/*
	rm -f bin/*
	rm -f doc/*

