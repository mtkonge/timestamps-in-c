
OUT=timestamps

OFILES= \
	main.o \
	timespan.o \
	date.o

CC=gcc
CFLAGS=-std=c17 -Wall -Werror -pedantic -Wpedantic -pedantic-errors

LD=gcc
LFLAGS=

HEADERS=$(wildcard *.h)

$(OUT): $(OFILES)
	$(LD) -o $@ $^ $(LFLAGS)

%.o: %.c $(HEADERS)
	$(CC) -c -o $@ $< $(CFLAGS)

.PHONY: clean

clean:
	$(RM) $(OUT) $(OFILES)

