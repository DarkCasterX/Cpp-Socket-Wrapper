#include "Socket.hpp"

int main(int argc, char** argv)
{
    try
    {
        TCPSocket sock = TCPSocket(AF_INET, SOCK_STREAM);
        sock.Bind("127.0.0.1", 4444);
        sock.Listen(1);
        sock.Accept();
        /*sock.Send("Hello\n");
        std::cout << sock.Recv(1024);
        sock.Send("1024");*/
    }
    catch(SockError& err)
    {
        std::cerr << "Got an error " << err.getDescription() << std::endl;
    }

    TCPSocket newSock = TCPSocket(AF_INET, SOCK_STREAM);
    return 0;
}