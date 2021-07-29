#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include "./SocketErrors.hpp"
#define SERVER 1
#define CLIENT 2

class TCPSocket
{
    int sock;
    int conn;
    int socketMode;
    struct sockaddr_in address;
    struct sockaddr_in remote;
    char* buf;
    int family;
    int sockType;
    bool bound;
    bool connected;
    bool opened;

    public:
    
    TCPSocket(int AF, int SOCK_TYPE)
    {
        if((sock = socket(AF, SOCK_TYPE, 0)) < 0)
        {
            throw SocketError();
        }
        opened = true;
        family = AF;
        sockType = SOCK_TYPE;
    }
    ~TCPSocket()
    {
        std::cout << "Destructor called.\n";
        Close();
    }

    int SockMode()
    {
        return socketMode;
    }

    void Close()
    {
        close(sock);
        close(conn);
        opened = false;
        if(bound)
        {
            bound = false;
        }
        if(connected)
        {
            connected = false;
        }
        std::cout << "Closed sockets.\n";
    }
    
	void Open(int mode, int AF, int SOCK_TYPE)
    {
        if(opened == false)
        {
            if(mode == SERVER)
            {
                this->socketMode = SERVER;
                if((sock = socket(AF, SOCK_TYPE, 0)) < 0)
                {
                        throw SocketError();
                }
            }
            else if(mode == CLIENT)
            {
                this->socketMode = CLIENT;
            }
            else
            {
                std::cerr << "Invalid mode.\n";
            }
            opened = true;
        }
        else
        {
            std::cerr << "This socket is already open. Close it to reopen it.\n";
        }
    }
    bool Closed()
    {
        if(opened)
        {
            return false;
        }
        return true;
    }

    void Bind(std::string ip_add, int port)
    {
        if(!connected)
        {
            inet_aton(ip_add.c_str(), (in_addr*)&address.sin_addr);
            address.sin_family = family;
            address.sin_port = htons(port);
            if(bind(sock, (const sockaddr*)&address, sizeof(address)) < 0)
            {
                throw BindError();
            }
            bound = true;
            std::cout << "Bound socket to [" << ip_add << ":" << port << "]\n";
        }
        else
        {
            throw BindConnError();
        }
    }
   
    void Listen(int n)
    {
        std::cout << "Listening for a connection...\n";
        if(listen(sock, n) < 0)
        {
            throw ListenError();
        }
    }
   
    void Accept(void (*f)(TCPSocket))
    {
        int remoteLen = sizeof(remote);
        if((conn = accept(sock, (struct sockaddr*)&remote, (socklen_t*)&remoteLen)) < 0)
        {
            throw AcceptError();
        }
        std::cout << "Accepted a connection from [" << inet_ntoa(remote.sin_addr) << ":" << ntohs(remote.sin_port) << "]\n";
        f(*this);
    }
   
    void Accept()
    {
        int remoteLen = sizeof(remote);
        if((conn = accept(sock, (struct sockaddr*)&remote, (socklen_t*)&remoteLen)) < 0)
        {
            throw AcceptError();
        }
        std::cout << "Accepted a connection from [" << inet_ntoa(remote.sin_addr) << ":" << ntohs(remote.sin_port) << "]\n";
    }

    void Connect(std::string ip_add, int port)
    {
        if(!bound)
        {
            conn = socket(AF_INET, SOCK_STREAM, 0);
            inet_aton(ip_add.c_str(), (in_addr*)&remote.sin_addr);
            remote.sin_family = AF_INET;
            remote.sin_port = htons(port);

            if(connect(conn, (const sockaddr*)&remote, sizeof(remote)) < 0)
            {
                throw ConnectionError();
            }
            connected = true;
            std::cout << "Connected to [" << inet_ntoa(remote.sin_addr) << ":" << ntohs(remote.sin_port) << "]\n";
        }
        else
        {
            throw ConnBoundError();
        }   
    }

    void Connect(std::string ip_add, int port, void(*f)(TCPSocket))
    {
        if(!bound)
        {
            conn = socket(AF_INET, SOCK_STREAM, 0);
            inet_aton(ip_add.c_str(), (in_addr*)&remote.sin_addr);
            remote.sin_family = AF_INET;
            remote.sin_port = htons(port);

            if(connect(conn, (const sockaddr*)&remote, sizeof(remote)) < 0)
            {
                throw ConnectionError();
            }
            connected = true;
            std::cout << "Connected to [" << inet_ntoa(remote.sin_addr) << ":" << ntohs(remote.sin_port) << "]\n";
            f(*this);
        }
        else
        {
            throw ConnBoundError();
        }   
    }

    void Send(std::string message)
    {

        if(send(conn, message.c_str(), sizeof(message.c_str()), 0) < 0)
        {
            throw SendError();
        }
    }

    std::string Recv(int bytes)
    {
        buf = new char[bytes];
        if(recv(conn, buf, sizeof(buf), 0) < 0)
        {
            throw RecvError();
        }
        delete buf;
        return std::string(buf);
    }
    char* RecvChar(int bytes)
    {
        buf = new char[bytes];
        if(recv(conn, buf, sizeof(buf), 0) < 0)
        {
            throw RecvError();
        }
        return buf;
    }
};

//Reverses byte order of a string of bytes
void ReverseByteOrder(char bytes[], int size)
{
    int end = size - 1;
    for(int i = 0; i < size / 2; i++)
    {
        char temp = bytes[i];
        bytes[i] = bytes[end];
        bytes[end] = temp;
        end--;
    }
}

//Displays the bytes of a character array in ASCII format
void displayBytes(char bytes[], int size)
{
    for(int i = 0; i < size; i++)
    {
        std::cout << bytes[i];
    }
    std::cout << std::endl;
}
