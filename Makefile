BIN	= free
MAN	= $(BIN).1
OBJ	= $(BIN).o

PREFIX	= /usr/local
BINDIR	= $(PREFIX)/bin
MANDIR	= $(PREFIX)/man/man1

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
	install -m0644 $(MAN) $(MANDIR)

uninstall:
	rm -f $(BINDIR)/$(BIN)
	rm -f $(MANDIR)/$(MAN)

.PHONY: all clean install uninstall
