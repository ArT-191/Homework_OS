CC=g++
CFLAGS=-c -Wall
LDFLAGS=

all: initializer main_client deinitializer

initializer: bank.o client.o initializer.o
	$(CC) $(LDFLAGS) bank.o client.o initializer.o -o initializer

main_client: bank.o client.o main_client.o
	$(CC) $(LDFLAGS) bank.o client.o main_client.o -o main_client

deinitializer: bank.o deinitializer.o
	$(CC) $(LDFLAGS) bank.o deinitializer.o -o deinitializer

bank.o: bank.c bank.h
	$(CC) $(CFLAGS) bank.c -o bank.o

client.o: client.cpp bank.h
	$(CC) $(CFLAGS) client.cpp -o client.o

initializer.o: initializer.cpp bank.h
	$(CC) $(CFLAGS) initializer.cpp -o initializer.o

main_client.o: main_client.cpp bank.h
	$(CC) $(CFLAGS) main_client.cpp -o main_client.o

deinitializer.o: deinitializer.cpp bank.h
	$(CC) $(CFLAGS) deinitializer.cpp -o deinitializer.o

clean:
	rm -f *.o initializer main_client deinitializer

