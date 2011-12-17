CXX = g++ -fPIC
NETLIBS= -lnsl -lsocket

all: talk-server 

talk-server: talk-server.c
	gcc -g -o talk-server talk-server.c linked_list.o -lnsl -lsocket

clean:
	rm -f talk-server *.out core total.txt

