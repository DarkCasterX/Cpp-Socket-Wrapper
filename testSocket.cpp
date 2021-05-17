#include "Socket.hpp"

int main(int argc, char** argv)
{
    try
    {
        TCPSocket sock = TCPSocket(AF_INET, SOCK_STREAM);
        sock.Bind("127.0.0.1", 4444);
        sock.Listen(1);
        sock.Accept();
        sock.Send("Hello\n");
        std::cout << sock.Recv(1024);
        sock.Send("1024");
        sock.Close();
    }
    catch(SockError& err)
    {
        std::cerr << "Got an error " << err.name << std::endl;
    }

    char bytes[6] = {0x22, 0x34, 0x56, 0x78, 0x79, 0x55};

    displayBytes(bytes, 6);
    displayBytes(bytes, 6);
    ReverseByteOrder(bytes, 6);
    displayBytes(bytes, 6);
    displayBytes(bytes, 6);

    TCPSocket newSock = TCPSocket(AF_INET, SOCK_STREAM);
    return 0;
}