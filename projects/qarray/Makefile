CC = cc
CFLAGS ?= -ansi -Wall -Wextra -Wpedantic -Wconversion -Wshadow -Wdouble-promotion

TESTS=tests/init.out tests/stack_init.out tests/insert.out tests/stack_insert.out tests/pop.out

.PHONY: check clean

all: $(TESTS)

.c.out:
	$(CC) $< -o $@ $(CFLAGS)

check: $(TESTS)
	./scripts/check.sh

clean:
	$(RM) tests/*.out
