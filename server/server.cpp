#include "server.hpp"


Server::Server(std::string port): _host(0), _port(port) {}
Server::Server(std::string host, std::string port): _host(host), _port(port) {}


fd_set  wait_on_clients(SOCKET server);
Client  get_client(SOCKET s);
void    drop_client(Client client);
void    serve_resource(Client client, const char *path);