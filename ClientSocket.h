#include "Socket.h"

class ClientSocket : public Socket {
public:
    ClientSocket ( std::string host, int port );
    virtual ~ClientSocket(){};
};