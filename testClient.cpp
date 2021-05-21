#include "Socket.hpp"

int main(int argc, char** argv)
{
    try
    {
        TCPSocket sock = TCPSocket(AF_INET, SOCK_STREAM);
        sock.Connect("127.0.0.1", 4444);
        sock.Close();
        /*sock.Send("Hello\n");
        std::cout << std::atoi(sock.RecvChar(1024));
        sock.Close();*/
    }
    catch(SockError& err)
    {
        std::cerr << err.getDescription() << "\n";
    }
    return 0;
}