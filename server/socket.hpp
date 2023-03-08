#ifndef SOCKET_HPP
#define SOCKET_HPP

#include <sys/socket.h>
#include <iostream>
#include <netdb.h>
#include <string.h>

#define ISVALIDSOCKET(s) ((s) >= 0)
#define CLOSESOCKET(s) close(s)
#define SOCKET int
#define GETSOCKETERRNO() (errno)
#define EXIT_FAILURE    1
#define EXIT_SUCCESS    0
#define STD_ERROR       2

class Socket
{
    private:
        SOCKET      _sockfd;
        char*       _port;
    public:
        Socket(char* port);
        Socket(const Socket &rhs);
        Socket  &operator = (const Socket& rhs);
        void    init_socket();
        void    bind_socket();
        void    listen_socket();
        Socket  creat_socket();
        Socket  get_socket() const;
        ~Socket();
};

#endif