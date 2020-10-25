BIN	= free
OBJ	= $(BIN).o

PREFIX	= /usr/local
BINDIR	= $(PREFIX)/bin
MANDIR	= $(PREFIX)/man

CC	= cc
CFLAGS	= -std=c99 -pedantic -Wall -Wextra -Werror -O2

all: $(BIN)

.c.o:
	$(CC) -c $(CFLAGS) -o $@ $<

$(BIN): $(OBJ)
	$(CC) -o $@ $(OBJ)

clean:
	rm -f $(BIN) $(OBJ)

install: $(BIN)
	install -m0755 $(BIN) $(BINDIR)
	install -m0644 $(BIN).1 $(MANDIR)/man1

uninstall:
	rm -f $(BINDIR)/$(BIN)
	rm -f $(MANDIR)/man1/$(BIN).1

.PHONY: all clean install uninstall
