SRC="src/main.d"
OBJ="$(foreach obj, $(SRC:.d=.o), $(notdir $(obj)))"

all: universum-meum

universum-meum: release

release:
	rebuild -dc=gdc-posix-tango -D -Dqdoc -oqobj -ofbin/Universum-Meum \
		-no-export-dynamic -lldl -Isrc -O -release src/main.d

debug:
	rebuild -dc=gdc-posix-tango -D -Dqdoc -oqobj -ofbin/Universum-Meum \
		-no-export-dynamic -lldl -Isrc -g -debug src/main.d

profile:
	rebuild -dc=gdc-posix-tango -D -Dqdoc -oqobj -ofbin/Universum-Meum \
		-no-export-dynamic -lldl -Isrc -g -debug -profile src/main.d

clean:
	rm -f obj/*
	rm -f bin/*
	rm -f doc/*

