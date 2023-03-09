#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <sys/socket.h>

#define SOCKET  int
#define DATA    int

typedef struct sockaddr_storage sock_storage;

class Client
{
    private:
        SOCKET          _sockfd;
        DATA            _received_data;

    public:
        socklen_t       _address_length;
        sock_storage    _address;    
        Client();
        Client(const Client& rhs);
        Client          &operator=(const Client& rhs);
        SOCKET          get_sockfd(void);
        void            set_sockfd(SOCKET sfd);
        void            set_received_data(DATA data);
        DATA            get_received_data(void);
        ~Client();
};

#endif