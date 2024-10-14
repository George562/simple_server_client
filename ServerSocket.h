#include "Socket.h"
#include <thread>
#include <mutex>
#include <vector>
#include <fstream>

class ServerSocket : public Socket {
public:
    ServerSocket ( int port );
    virtual ~ServerSocket() {};

    void accept ( Socket& );
    void join(Socket&);
    
    std::ofstream log;
    std::vector<std::thread*> threads;
    std::mutex mtx;
};