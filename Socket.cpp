#include "Socket.h"
#include "string.h"
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <iostream>

Socket::Socket() : m_sock (-1) { memset (&m_addr, 0, sizeof (m_addr) ); }

Socket::~Socket() {
    if (is_valid() )
        ::close (m_sock );
}

bool Socket::create() {
    m_sock = socket (AF_INET, SOCK_STREAM, 0 );

    if (! is_valid() )
        return false;

    int on = 1;
    return setsockopt (m_sock, SOL_SOCKET, SO_REUSEADDR, (const char*) &on, sizeof (on) ) != -1;
}

bool Socket::bind (const int port) {
    if (! is_valid()) { return false; }

    m_addr.sin_family = AF_INET;
    m_addr.sin_addr.s_addr = INADDR_ANY;
    m_addr.sin_port = htons (port );

    int bind_return = ::bind (m_sock, (struct sockaddr *) &m_addr, sizeof (m_addr) );

    return bind_return != -1;
}

bool Socket::listen() const {
    if (!is_valid()) { return false; }

    int listen_return = ::listen (m_sock, MAXCONNECTIONS );

    return listen_return != -1;
}

bool Socket::accept(Socket& new_socket) const {
    int addr_length = sizeof (m_addr );
    new_socket.m_sock = ::accept (m_sock, (sockaddr *) &m_addr, (socklen_t *) &addr_length );

    return new_socket.m_sock > 0;
}

bool Socket::send (const std::string s) const {
    int status = ::send (m_sock, s.c_str(), s.size(), MSG_NOSIGNAL );
    return status != -1;
}

int Socket::recv (std::string& s) const {
    char buf [ MAXRECV + 1 ];

    s = "";

    memset(buf, 0, MAXRECV + 1);

    int status = ::recv (m_sock, buf, MAXRECV, 0 );

    if (status == -1) {
        std::cout << "status == -1   errno == " << errno << "  in Socket::recv\n";
        return 0;
    } else if (status == 0) {
        return 0;
    } else {
        s = buf;
        return status;
    }
}

bool Socket::connect (const std::string host, const int port) {
    if (!is_valid()) return false;

    m_addr.sin_family = AF_INET;
    m_addr.sin_port = htons (port );

    int status = inet_pton (AF_INET, host.c_str(), &m_addr.sin_addr );

    if (errno == EAFNOSUPPORT) return false;


    return ::connect (m_sock, (sockaddr*) &m_addr, sizeof (m_addr) ) == 0;
}

void Socket::set_non_blocking (const bool b) {
    int opts = fcntl (m_sock, F_GETFL );

    if (opts < 0) { return; }

    opts = b ? (opts | O_NONBLOCK) : (opts & ~O_NONBLOCK );

    fcntl (m_sock, F_SETFL, opts );
}