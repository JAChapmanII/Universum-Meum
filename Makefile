SRCDIR=src
DOCDIR=doc
BINDIR=bin
SOURCES=$(wildcard $(SRCDIR)/*.cpp)
HEADERS=$(wildcard $(SRCDIR)/*.hpp)
OBJS=$(SOURCES:.cpp=.o)
EXEC=Universum-Meum

CC=g++
CFLAGS=

LD=ld
LFLAGS=
LFLAGS+=-lsfml-graphics -lsfml-window -lsfml-system -lGL

ifdef profile
CFLAGS+=-pg
endif

ifndef nowall
CFLAGS+=-Wextra -pedantic -Wmain -Weffc++ -Wswitch-default -Wswitch-enum
CFLAGS+=-Wmissing-include-dirs -Wmissing-declarations -Wunreachable-code
CFLAGS+=-Winline -Wfloat-equal -Wundef -Wcast-align -Wredundant-decls
CFLAGS+=-Winit-self -Wshadow
endif

ifdef release
CFLAGS+=-O3 -s
else
CFLAGS+=-g
endif

DOXY=doxygen
DCONFIG=Doxyfile

all: $(EXEC)

full: $(EXEC) documentation

$(EXEC): $(OBJS)
	mkdir -p $(BINDIR)
# TODO If you're feeling brave, figure out what the hell happens here
	$(CC) -o $(BINDIR)/$(EXEC) $(LFLAGS) $?

%.o: %.cpp $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

documentation:
	mkdir -p $(DOCDIR)
	$(DOXY) $(DCONFIG)

clean:
	rm -f $(BINDIR)/$(EXEC)
	rm -f $(SRCDIR)/*.o
	rm -rf $(DOCDIR)/*

