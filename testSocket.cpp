#include "Socket.hpp"

void sayHello(TCPSocket sock)
{
    std::cout << "In sayHello function.\n";
    sock.Send("Hello\n");
    std::cout << sock.Recv(1024);
    sock.Send("1024\n");
}

int main(int argc, char** argv)
{
    try
    {
        TCPSocket sock = TCPSocket(AF_INET, SOCK_STREAM);
        sock.Bind("127.0.0.1", 4444);
        sock.Listen(1);
        sock.Accept(sayHello);
        sock.Close();
        sock.Open(CLIENT, AF_INET, SOCK_STREAM);
        sock.Connect("127.0.0.1", 7777);
    }
    catch(SockError& err)
    {
        std::cerr << "Got an error " << err.getDescription() << std::endl;
    }

    return 0;
}
