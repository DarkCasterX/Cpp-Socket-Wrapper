#include <iostream>
#include <string>

class SockError
{
    protected:
    std::string name;
    std::string desc;
    SockError()
    {

    }
    void setName(std::string n)
    {
        name = n;
    }
    void setDesc(std::string n)
    {
        desc = n;
    }

    public:
    std::string getName()
    {
        return name;
    }
    std::string getDescription()
    {
        return desc;
    }
};

class SocketError: public SockError
{
    public:
    SocketError()
    {
        setName("SocketError");
        setDesc("[ERROR] Failed to create a socket\n");
    }
};

class ListenError: public SockError
{
    public:
    ListenError()
    {
        setName("ListenError");
        setDesc("[ERROR] Listen() failed; Check your internet configuration\n");
    }
};

class BindError: public SockError
{
    public:
    BindError()
    {
        setName("BindError");
        setDesc("[ERROR] Bind(): Address may already be in use\n");
    }
};

class BindConnError: public SockError
{
    public:
    BindConnError()
    {
        setName("BindConnError");
        setDesc("[ERROR] Bind(): Cannot bind socket that is already connected\n");
    }
};

class AcceptError: public SockError
{
    public:
    AcceptError()
    {
        setName("AcceptError");
        setDesc("[ERROR] Accept(): Failed to accept a connection on the socket\n");
    }
};

class ConnectionError: public SockError
{
    public:
    ConnectionError()
    {
        setName("ConnectionError");
        setDesc("[ERROR] Connect(): Failed to connect to remote endpoint\n");
    }
};

class ConnBoundError: public SockError
{
    public:
    ConnBoundError()
    {
        setName("ConnBoundError");
        setDesc("[ERROR] Connect(): Attempted connection already bound\n");
    }
};

class SendError: public SockError
{
    public:
    SendError()
    {
        setName("SendError");
        setDesc("[ERROR] Send(): Failed to send message\n");
    }
};

class RecvError: public SockError
{
    public:
    RecvError()
    {
        setName("RecvError");
        setDesc("[ERROR] Recv(): Failed to receieve message\n");
    }
};