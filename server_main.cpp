#include "ServerSocket.h"
#include "SocketException.h"
#include <string>
#include <iostream>

ServerSocket* server;
int main ( int argc, char* argv[] ) {
    std::cout << "running....\n";

    server = new ServerSocket(std::stoi(argv[1]));
    char c;

    try {
        while (true) {
            Socket* socket = new Socket;
            server->accept(*socket);
        }
    } catch ( SocketException& e ) {
        std::cout << "Exception was caught:" << e.description() << "\nExiting.\n";
    }

    return 0;
}