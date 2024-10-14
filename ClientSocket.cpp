#include "ClientSocket.h"
#include "SocketException.h"

ClientSocket::ClientSocket ( std::string host, int port ) {
    if (!Socket::create()) {
        throw SocketException ( "Could not create client socket." );
    }

    if (!Socket::connect(host, port)) {
        throw SocketException ( "Could not bind to port." );
    }
}