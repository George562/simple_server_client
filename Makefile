# Makefile for the socket programming example
#

server_objects = ServerSocket.o Socket.o server_main.o
client_objects = ClientSocket.o Socket.o client_main.o


all : server client

server: $(server_objects)
	g++ -o server $(server_objects)


client: $(client_objects)
	g++ -o client $(client_objects)


Socket: Socket.cpp
ServerSocket: ServerSocket.cpp
ClientSocket: ClientSocket.cpp
server_main: server_main.cpp
client_main: client_main.cpp


clean:
	rm -f *.o server client