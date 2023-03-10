#include "server.hpp"

Server::Server(PORT port):_port(port)
{
    Socket socket(this->_port);
    this->_server_socket = socket.get_socket();
}

// this function is init sockfds for a serve and clients.
void  Server::init_sockfds()
{
    FD_ZERO(&this->_reads);
    FD_SET(this->_server_socket, &this->_reads);
    this->_max_socket = this->_server_socket;
    std::list<Client *>::iterator iter;
    for(iter = this->_clients.begin(); iter != this->_clients.end(); iter++)
    {
        FD_SET((*iter)->get_sockfd(), &this->_reads);
        if ((*iter)->get_sockfd() > this->_max_socket)
            this->_max_socket = (*iter)->get_sockfd();
    }
}

// this function tell some connection comes,
// and we know that the connection happened when select detects changes in the server socket.
// and select have 1 second to check if no connection happened we have to move one to serve clients that already connected
void    Server::wait_on_clients()
{
    struct timeval restrict;

    this->init_sockfds();
    restrict.tv_sec = 10;
    restrict.tv_usec = 0;
    //std::cout << "max socket = " << this->_max_socket  << std::endl;
    if (select(this->_max_socket + 1, &(this->_reads), NULL, NULL, &restrict) < 0)
    {
        std::cerr << "select() failed" << std::endl;
        exit(EXIT_FAILURE);
    }
    
}

const char *get_client_address(Client *ci)
{
    static char address_buffer[100];
    getnameinfo((struct sockaddr*)&ci->_address,
    ci->_address_length,
    address_buffer, sizeof(address_buffer), 0, 0,
    NI_NUMERICHOST);
    return address_buffer;
}

void    Server::accept_new_client()
{
    Client *client = new Client;

    SOCKET r = accept(this->_server_socket, \
        reinterpret_cast<struct sockaddr *>(&client->_address), \
        &(client->_address_length));
    client->set_sockfd(r);
    if (!ISVALIDSOCKET(client->get_sockfd()))
    {
        std::cerr << "accept() failed." << std::endl;
        exit(EXIT_FAILURE);
    }
    this->_clients.push_back(client);
    std::cout << "New connection from : " << get_client_address(client) << std::endl;
}

void    Server::run_serve()
{
    int i = 0;
    while(1)
    {
        this->wait_on_clients();
        if (FD_ISSET(this->_server_socket, &this->_reads))
            this->accept_new_client();
        this->serve_clients();
    }
}

void    Server::serve_clients()
{
    int                             request_size;
    std::list<Client *>::iterator   iter;

    for(iter = this->_clients.begin(); iter != this->_clients.end(); iter++)
    {
        if(FD_ISSET((*iter)->get_sockfd(), &this->_reads))
        {
            memset(this->_request_buff, 0, MAX_REQUEST_SIZE + 1);
            request_size = recv((*iter)->get_sockfd(), this->_request_buff, MAX_REQUEST_SIZE, 0);
            //std::cout << "request size: " << request_size << std::endl;
            if (request_size < 1)
            {
                printf("Unexpected disconnect from %s.\n",
                get_client_address(*iter));
                drop_client(iter);
            }
            (*iter)->set_received_data(request_size);
            (*iter)->_request.append(this->_request_buff);
            if(request_size < MAX_REQUEST_SIZE)
            {
                std::cout << (*iter)->_request << std::endl;
                this->drop_client(iter);
            }
        }
    }
}

void    Server::drop_client(std::list<Client *>::iterator client)
{
    CLOSESOCKET((*client)->get_sockfd());
    std::list<Client *>::iterator iter;

    for(iter = this->_clients.begin(); iter != this->_clients.end(); iter++)
    {
        if((*client)->get_sockfd() == (*iter)->get_sockfd())
            iter = this->_clients.erase(iter);
        return ;
    }
    std::cerr << "Drop Client not found !" << std::endl;
}

Server::~Server()
{
    // close server socket;
}