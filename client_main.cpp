#include "ClientSocket.h"
#include "SocketException.h"
#include <string>
#include <ctime>
#include <iomanip>
#include <iostream>

int main ( int argc, char* argv[] ) {
    try {
        ClientSocket client_socket("localhost", std::stoi(argv[2]));

        try {
            while (true) {
                time_t timestamp = time(NULL);
                struct tm datetime = *localtime(&timestamp);
                std::stringstream buffer;
                buffer << std::put_time(&datetime, "[%Y-%m-%e %H:%M:%S] ") << argv[1];
                if (int status = client_socket.send(buffer.str()))
                    std::cout << status << '\n';
                else {
                    throw SocketException("Error sending data");
                }
                sleep(std::stoi(argv[3]));
            }
        } catch ( SocketException& ) {}
    } catch ( SocketException& e ) {
        std::cout << "Exception was caught:" << e.description() << "\n";
    }

    return 0;
}