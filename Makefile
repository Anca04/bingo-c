# compiler setup
CC=gcc
CFLAGS=-Wall -g

# define targets
TARGETS = bingo 

build: $(TARGETS)

bingo: bingo.c
	$(CC) $(CFLAGS) bingo.c -lm -o bingo

clean:
	rm -f $(TARGETS)

.PHONY: pack clean
