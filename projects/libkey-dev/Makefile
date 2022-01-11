CC ?= cc
PREFIX ?= /usr/local
CFLAGS ?= -ansi -pedantic -Wall -Wextra -Wconversion -Wdouble-promotion -Wshadow -fpic -Wno-unused
LDLIBS ?= -lncurses
DEBUGGER ?=

OBJS=src/libkey.o src/sequence-validation.o src/scan.o
TESTS=tests/init.out tests/add_mode.out tests/mode_compare.out tests/mode_exists.out tests/add_sequence.out \
	  tests/sequence_compare.out
HEADERS=src/libkey.h

.PHONY: all install clean check conform

.c.o:
	cat $< | m4 -Isrc/ | gcc -x c - $(CFLAGS) $(LDLIBS) -Isrc/

.c.out:
	$(CC) $< $(OBJS) -o $@ $(CFLAGS)

all: $(OBJS)

$(PREFIX)/lib/libkey.so: $(OBJS)
	$(CC) -shared $(OBJS) $(CFLAGS) -o $(PREFIX)/lib/libkey.so

install: $(PREFIX)/lib/libkey.so
	mkdir --parents $(PREFIX)/libkey
	cp $(HEADERS) $(PREFIX)/libkey

clean:
	$(RM) $(OBJS)
	$(RM) $(PREFIX)/lib/libkey.so
	$(RM) $(PREFIX)/include/libkey -r
	$(RM) ../libkey-user/ -r
	$(RM) tests/*.out

check: $(OBJS) $(TESTS)
	./scripts/check.sh $(DEBUGGER)

conform:
	mkdir --parents ../libkey-user

	# Grab all system header inclusions
	cat src/*.h src/*.c | grep '#include <' | awk '{ print length " " $$0 }' | sort -n | cut -d ' ' -f 2- | uniq > ../libkey-user/libkey.c

	echo '#include "libkey.h"' >> ../libkey-user/libkey.c

	# Dump defines from each header into the source file.
	for file in src/*.h; do sed -n '3,$$p' $$file | tac | sed -n '2,$$p' | tac; done | grep '^#define' >> ../libkey-user/libkey.c

	# Preprocess all source files with all defines, and m4 files with the C preprocessor and m4.
	grep '#define' src/*.h | grep -v '_H$$' | cat - src/*.m4 src/*.c | grep -v '^#include' | $(CPP) - -ftrack-macro-expansion=0 | m4 | grep -v '^#' >> ../libkey-user/libkey.c

	# Dump header file information
	echo '#ifndef LIB_KEY_H' > ../libkey-user/libkey.h
	echo '#define LIB_KEY_H' >> ../libkey-user/libkey.h
	cat src/*.h src/*.c | grep '#include <' | awk '{ print length " " $$0 }' | sort -n | cut -d ' ' -f 2- | uniq >> ../libkey-user/libkey.h
	for file in src/*.h; do sed -n '3,$$p' $$file | tac | sed -n '2,$$p' | tac | grep -v '^#include'; done >> ../libkey-user/libkey.h
	echo '#endif' >> ../libkey-user/libkey.h
	
	# Compile the user source file to make sure there are no errors.
	$(CC) -c ../libkey-user/libkey.c
	rm libkey.o
