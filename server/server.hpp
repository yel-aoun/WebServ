#ifndef SERVER_HPP
#define SERVER_HPP

#include "utils.hpp"
#include "client.hpp"
#include "socket.hpp"

#include <iostream>
#include <iterator>
#include <list>

#define SOCKET int

class Server
{
    private:
        std::string         _host;
        std::string         _port;
        SOCKET              _server;
        std::list<Client>   _clients;
    public:
        Server(std::string port);
        Server(std::string host, std::string port);
        fd_set  wait_on_clients(SOCKET server);
        Client  get_client(SOCKET s);
        void    drop_client(Client client);
        void    serve_resource(Client client, const char *path);
};

#endif
