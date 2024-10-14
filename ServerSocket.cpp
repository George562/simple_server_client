#include "ServerSocket.h"
#include "SocketException.h"

ServerSocket::ServerSocket(int port) {
    if (!Socket::create()) {
        throw SocketException("Could not create server socket.");
    }
    if (!Socket::bind(port)) {
        throw SocketException("Could not bind to port.");
    }
    if (!Socket::listen()) {
        throw SocketException("Could not listen to socket.");
    }
    log.open("log.txt");
    log.close();
}

void ServerSocket::accept(Socket& sock) {
    if (!Socket::accept(sock)) {
        throw SocketException("Could not accept socket.");
    }
    join(sock);
}

void ServerSocket::join(Socket& sock) {
    threads.push_back(new std::thread([this, &sock]() {
        std::string data;
        while (true) {
            if (!sock.recv(data)) {
                break;
            }
            mtx.lock();
            log.open("log.txt", std::ios_base::app);
            log << data << '\n';
            data.clear();
            log.close();
            mtx.unlock();
        }
    }));
}