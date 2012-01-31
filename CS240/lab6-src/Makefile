
all: talk-client

talk-client: talk-client.c
	gcc -g -o talk-client talk-client.c -lcurses -lsocket -lnsl -lpthread

clean:
	rm -f talk-client *.out outfile* total.txt infile* fifo*
