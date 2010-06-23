SHELL=/bin/sh
SRCDIR=src
DOCDIR=doc
OBJDIR=obj
BINDIR=bin
SRC=main.cpp
PROG=Universum-Meum

CC=g++
CFLAGS=-lSDL -lGL -pipe

DOXY=doxygen
DCONFIG=Doxyfile

all: ${PROG}

${PROG}: debug

full: dirs clean release documentation

release: dirs clean
	${CC} -o ${BINDIR}/${PROG} ${CFLAGS} -O3 -s ${SRCDIR}/${SRC}

debug: dirs clean
	${CC} -o ${BINDIR}/${PROG}-debug ${CFLAGS} -g ${SRCDIR}/${SRC}

wall: dirs clean
	${CC} -o ${BINDIR}/${PROG}-wall ${CFLAGS} -g \
	-Wextra -pedantic -Wmain -Weffc++ -Wswitch-default -Wswitch-enum -Wmissing-include-dirs \
	-Wmissing-declarations -Wunreachable-code -Winline -Wfloat-equal -Wundef -Wcast-align \
	-Wredundant-decls -Winit-self -Wshadow \
	${SRCDIR}/${SRC}

profile: dirs clean
	${CC} -o ${BINDIR}/${PROG}-profile ${CFLAGS} -pg ${SRCDIR}/${SRC}

documentation:
	${DOXY} ${DCONFIG}

dirs:
	mkdir -p ${SRCDIR}
	mkdir -p ${DOCDIR}
	mkdir -p ${OBJDIR}
	mkdir -p ${BINDIR}

clean:
	rm -rf ${OBJDIR}/*
	rm -rf ${BINDIR}/*
	rm -rf ${DOCDIR}/*

