CC=gcc

CFLAGS=-c	-Wall

all:makeDeneme

makeDeneme:	main.o	FileOperations.o
	$(CC)	main.o	FileOperations.o	-o	main

main.o:	main.c
	$(CC)	$(CFLAGS)	main.c
FileOperations.o:	FileOperations.c	FileOperations.h
	$(CC)	$(CFLAGS)	FileOperations.c

clean:
	del	*.o	main.exe
