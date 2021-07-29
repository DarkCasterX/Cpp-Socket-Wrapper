#include "Socket.hpp"

void onAccept(TCPSocket sock)
{
    std::cout << "Handling accept event\n";
}

void onConnect(TCPSocket sock)
{
    std::cout << "Handling connect event\n";
    std::cout << sock.Recv(1024);
    sock.Send("Hello\n");
    std::cout << std::atoi(sock.RecvChar(1024));
}

int main(int argc, char** argv)
{
    try
    {
        TCPSocket sock = TCPSocket(AF_INET, SOCK_STREAM);
        sock.Connect("127.0.0.1", 4444, onConnect);
        sock.Close();
        sock.Open(SERVER, AF_INET, SOCK_STREAM);
        sock.Bind("127.0.0.1", 7777);
        sock.Listen(1);
        sock.Accept(onAccept);
    }
    catch(SockError& err)
    {
        std::cerr << err.getDescription() << "\n";
    }
    return 0;
}
