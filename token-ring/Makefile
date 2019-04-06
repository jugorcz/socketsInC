CC = gcc
CFLAGS = -std=c99 -g -Wall
DEPS = auxiliaryFunctions.h
OBJ = client.o clientTCP.o clientUDP.o common.o
SRC = client.c clientTCP.c clientUDP.c common.c

all: client clean

client: $(OBJ) 
	$(CC) $(CFLAGS) -o $@ $+

%.o: %.c $(DEPS)
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f *.o

tcp1:
	./client A 10123 127.0.0.1 10123 1 TCP

tcp2:
	./client B 10124 127.0.0.1 10123 0 TCP

tcp3:
	./client C 10125 127.0.0.1 10123 0 TCP