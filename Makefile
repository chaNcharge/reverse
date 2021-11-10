CFLAGS=-W -Wall -g -I/usr/local/include
LDFLAGS=-L/usr/local/lib
LIBRARIES=-lADTs
PROGRAMS=reverse alreverse

all: $(PROGRAMS)

reverse: reverse.o stringlist.o
	gcc -o reverse $^

alreverse: alreverse.o
	gcc $(CFLAGS) $(LDFLAGS) -o $@ $^ $(LIBRARIES)

stringlist.o: stringlist.c stringlist.h
reverse.o: reverse.c stringlist.h
alreverse.o: alreverse.c

clean:
	rm -f $(PROGRAMS) *.o