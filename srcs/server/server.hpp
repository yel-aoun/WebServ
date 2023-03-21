#ifndef SERVER_HPP
#define SERVER_HPP

#include "../headers_cpp.hpp"

class Client;
class Socket;
#include "../request/request.hpp"
# include "../request/check_path.hpp"
class parce_server;

#define SOCKET              int
#define PORT                int
#define MAX_REQUEST_SIZE    100
class location;

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

        void    init_sockfds();
        void    wait_on_clients();
        void    new_connection();
        void    accept_new_client();
        void    drop_client(std::list<Client *>::iterator client);
        void    serve_clients();

        std::string seperate_header(std::string buff);
    public:
        Server(parce_server &server_data);
        char                    _request_buff[MAX_REQUEST_SIZE + 1];
        void    run_serve();
        std::list<location>     get_locations() const;
        int get_max_client_body_size() const {return (_max_client_body_size);}
        // const char *get_client_address(Client *);
        // void    serve_resource(Client client, const char *path);
        ~Server();
};

#endif
