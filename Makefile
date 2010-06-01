SHELL=/bin/sh
SRCDIR=src
DOCDIR=doc
OBJDIR=obj
BINDIR=bin
SRC=main.d
PROG=Universum-Meum

DD=rebuild
DFLAGS=-no-export-dynamic -lldl

all: ${PROG}

${PROG}: dirs clean release

release:
	${DD} -D -Dq${DOCDIR} -oq${OBJDIR} -of${BINDIR}/${PROG} -I${SRCDIR}/\
		${DFLAGS} -O -release ${SRCDIR}/${SRC}

debug: dirs clean
	${DD} -oq${OBJDIR} -of${BINDIR}/${PROG} -I${SRCDIR}/\
		${DFLAGS} -g -debug ${SRCDIR}/${SRC}

profile:
	${DD} -oq${OBJDIR} -of${BINDIR}/${PROG} -I${SRCDIR}/\
		${DFLAGS} -g -debug -profile ${SRCDIR}/${SRC}

dirs:
	mkdir -p ${SRCDIR}
	mkdir -p ${DOCDIR}
	mkdir -p ${OBJDIR}
	mkdir -p ${BINDIR}

clean:
	rm -f ${OBJDIR}/*
	rm -f ${BINDIR}/*
	rm -f ${DOCDIR}/*

