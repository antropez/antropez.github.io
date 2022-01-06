PREFIX ?= /usr/bin

.PHONY: install uninstall

install: $(PREFIX)/m4make

uninstall:
	rm $(PREFIX)/m4make

$(PREFIX)/m4make: src/m4make.sh
	cp src/m4make.sh $(PREFIX)/m4make
	chmod +x $(PREFIX)/m4make
