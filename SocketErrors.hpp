#include <iostream>
#include <string>

class SockError
{
    public:
    std::string name;
    SockError()
    {

    }
    void setName(std::string n)
    {
        name = n;
    }
};

class SocketError: public SockError
{
    public:
    SocketError()
    {
        setName("SocketError");
        std::cout << "[ERROR] Failed to create a socket\n";
    }
};

class ListenError: public SockError
{
    public:
    ListenError()
    {
        setName("ListenError");
        std::cout << "[ERROR] Listen() failed; Check your internet configuration\n";
    }
};

class BindError: public SockError
{
    public:
    BindError()
    {
        setName("BindError");
        std::cout << "[ERROR] Bind() error: Address my already be in use\n";
    }
};

class BindConnError: public SockError
{
    public:
    BindConnError()
    {
        setName("BindConnError");
        std::cout << "[ERROR] Attempted bind already connected\n";
    }
};

class AcceptError: public SockError
{
    public:
    AcceptError()
    {
        setName("AcceptError");
        std::cout << "[ERROR] Failed to accept a connection on the socket\n";
    }
};

class ConnectionError: public SockError
{
    public:
    ConnectionError()
    {
        setName("ConnectionError");
        std::cout << "[ERROR] Failed to connect to remote endpoint\n";
    }
};

class ConnBoundError: public SockError
{
    public:
    ConnBoundError()
    {
        setName("ConnBoundError");
        std::cout << "[ERROR] Attempted connection already bound\n";
    }
};

class SendError: public SockError
{
    public:
    SendError()
    {
        setName("SendError");
        std::cout << "[ERROR] Failed to send message\n";
    }
};

class RecvError: public SockError
{
    public:
    RecvError()
    {
        setName("RecvError");
        std::cout << "[ERROR] Failed to receieve message\n";
    }
};