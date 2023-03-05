# ifndef WEBSERV_HPP
# define WEBSERV_HPP

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <list>
# include "server.hpp"


class webserv
{
    public:
        std::list<std::string> config;
        std::list<server> servers;
        webserv(std::string conf_file);
};
# endif