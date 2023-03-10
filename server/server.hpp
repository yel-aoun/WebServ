#ifndef SERVER_HPP
#define SERVER_HPP

#include "client.hpp"
#include "socket.hpp"

#include <iostream>
#include <iterator>
#include <list>

#define PORT    int

class Server
{
    private:
        fd_set                  _reads;
        PORT                    _port;
        SOCKET                  _server_socket;
        SOCKET                  _max_socket;
        std::list<Client>     _clients;

    public:
        void    init_sockfds();
        void    wait_on_clients();
        void    new_connection();
        void    accept_new_client();
        void    drop_client(std::list<Client *>::iterator &client);
        Server(PORT port);
        void    run_serve();
        // const char *get_client_address(Client *);
        // void    serve_resource(Client client, const char *path);
        ~Server();
};

#endif
