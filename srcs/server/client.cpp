#include "client.hpp"

Client::Client(): _received_data(0) 
{
    this->_address_length = sizeof(this->_address);
}

Client::Client(const Client& rhs)
{
    this->_sockfd = rhs._sockfd;
    this->_received_data = rhs._received_data;
    this->_address = rhs._address;
    this->_address_length = rhs._address_length;
}

Client &Client::operator=(const Client& rhs)
{
    this->_sockfd = rhs._sockfd;
    this->_received_data = rhs._received_data;
    this->_address = rhs._address;
    this->_address_length = rhs._address_length;
    return (*this);
}

SOCKET  Client::get_sockfd(void)
{;
    return (this->_sockfd);
}

void    Client::set_sockfd(SOCKET sfd)
{
    this->_sockfd = sfd;
}

DATA    Client::get_received_data(void)
{
    return (this->_received_data);
}

void    Client::set_received_data(DATA data)
{
    this->_received_data += data;
}

Client::~Client() {}