#ifndef SERVER_HPP
#define SERVER_HPP

#include "client.hpp"
#include "socket.hpp"
#include <cstring>

#include <iostream>
#include <iterator>
#include <list>
#include "../parsing/parce_server.hpp"
#include "../request/request.hpp"

#define PORT                int
#define MAX_REQUEST_SIZE    1024

class Server
{
    private:
        PORT                    _port;
        std::string             _host_name;
        int                     _max_client_body_size;
        std::vector<std::string> _error_page;
        std::list<location>     _locations;
        fd_set                  _writes;
        fd_set                  _reads;
        SOCKET                  _server_socket;
        SOCKET                  _max_socket;
        std::list<Client *>     _clients;
        char                    _request_buff[MAX_REQUEST_SIZE + 1];

        void    init_sockfds();
        void    wait_on_clients();
        void    new_connection();
        void    accept_new_client();
        void    drop_client(std::list<Client *>::iterator client);
        void    serve_clients();

        void    check_path(std::string &path, std::map<std::string, std::vector<std::string> > &map);
        void    check_transfer_in_coding(std::map<std::string, std::vector<std::string> > &map_req);

    public:
        Server(parce_server &server_data);
        void    run_serve();
        std::list<location>     get_locations() const;
        // const char *get_client_address(Client *);
        // void    serve_resource(Client client, const char *path);
        ~Server();
};

#endif
