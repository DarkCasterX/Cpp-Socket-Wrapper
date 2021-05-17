#include "Socket.hpp"

int main(int argc, char** argv)
{
    try
    {
        TCPSocket sock = TCPSocket(AF_INET, SOCK_STREAM);
        sock.Connect("www.google.com", 80);
        sock.Send("GET / HTTP/1.1\n\n");
        std::cout << std::atoi(sock.RecvChar(1024));
        sock.Close();
    }
    catch(SockError& err)
    {
        std::cerr << "Got an error " << err.name << "\n";
    }
    return 0;
}