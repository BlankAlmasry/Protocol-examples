ifeq ($(strip $(PORT)),)
    $(error PORT is undefined. Usage: make <target> PORT=<port> MAX_CONNECTIONS=<max_connections>)
endif

CC=gcc
CFLAGS=-I.
.PHONY: udb4Server udb6Server tcp4ServerWithThreads

udb4Server:
	@$(CC) udb4Server.c  $(CFLAGS) -o udb4Server.o
	@bash -c "trap 'rm -f *.o main' EXIT; ./udb4Server.o $(PORT)"
	@./udb4Server.o $(PORT)
	@rm -f *.o

udb6Server:
	@$(CC) udb6Server.c  $(CFLAGS) -o udb6Server.o
	@bash -c "trap 'rm -f *.o main' EXIT; ./udb6Server.o $(PORT)"
	@./udb6Server.o $(PORT)
	@rm -f *.o

tcp4ServerWithThreads:
ifeq ($(strip $(MAX_CONNECTIONS)),)
	$(error MAX_CONNECTIONS is undefined. Usage: make <target> PORT=<port> MAX_CONNECTIONS=<max_connections>)
endif
	@$(CC) -pthread tcp4ServerWithThreads.c  $(CFLAGS) -o tcp4ServerWithThreads.o
	@bash -c "trap 'rm -f tcp4ServerWithThreads.o main' EXIT; ./tcp4ServerWithThreads.o $(PORT) $(MAX_CONNECTIONS)"
	@./tcpServer.o $(PORT) $(MAX_CONNECTIONS)
	@rm -f tcpServerWithThreads.o
