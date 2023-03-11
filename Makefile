CC=gcc
CFLAGS=-I.
.PHONY: udb4Server udb6Server

udb4Server:
	@$(CC) udb4Server.c  $(CFLAGS) -o udb4Server.o
	@bash -c "trap 'rm -f *.o main' EXIT; ./udb4Server.o $(PORT)"
	@./udb4Server.o $(PORT)
	@rm -f *.o main

udb6Server:
	@$(CC) udb6Server.c  $(CFLAGS) -o udb6Server.o
	@bash -c "trap 'rm -f *.o main' EXIT; ./udb6Server.o $(PORT)"
	@./udb6Server.o $(PORT)
	@rm -f *.o main