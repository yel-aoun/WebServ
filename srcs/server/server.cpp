#include "server.hpp"

static int i = 0;

Server::Server(parce_server &server_data)
{
    this->_port = server_data.port;
    this->_host_name = server_data.host_name;
    this->_max_client_body_size = server_data.max_client_body_size;
    this->_error_page = server_data.error_page;
    this->_locations = server_data.locations;
    Socket socket(this->_port);
    this->_server_socket = socket.get_socket();
}

void  Server::init_sockfds()
{
    FD_ZERO(&this->_reads);
    FD_ZERO(&this->_writes);
    FD_SET(this->_server_socket, &this->_reads);
    this->_max_socket = this->_server_socket;
    std::list<Client *>::iterator iter;
    for(iter = this->_clients.begin(); iter != this->_clients.end(); iter++)    {
        FD_SET((*iter)->get_sockfd(), &this->_writes);
        FD_SET((*iter)->get_sockfd(), &this->_reads);
        if ((*iter)->get_sockfd() > this->_max_socket)
            this->_max_socket = (*iter)->get_sockfd();
    }
}

void    Server::wait_on_clients()
{
    struct timeval restrict;

    this->init_sockfds();
    restrict.tv_sec = 1;
    restrict.tv_usec = 0;
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
}

void    Server::run_serve()
{
    this->wait_on_clients();
    if (FD_ISSET(this->_server_socket, &this->_reads))
        this->accept_new_client();
    else
        this->serve_clients();
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
            if (request_size < 1)
            {
                std::cerr << "Unexpected disconnect from << " << get_client_address(*iter) << std::endl;
                drop_client(iter);
            }
            (*iter)->set_received_data(request_size);
            (*iter)->_request.append(this->_request_buff);
            if(!std::strcmp(this->_request_buff + request_size -  4, "\r\n\r\n"))
            {
                Request req((*iter)->_request);
                (*iter)->request_pack = req.request;
                
                //*******************************************************************
                //*this block is for printing the content of the map<string, vector>*
                //*******************************************************************

                // std::vector<std::string> vec = (*iter)->request_pack.find("User-Agent")->second;
                // std::vector<std::string>::iterator iter = vec.begin();
                // for(; iter != vec.end(); iter++)
                // {
                //     std::cout<<(*iter)<<std::endl;
                // }
                // std::cout<<(*iter)->_request<<std::endl;
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