# ifndef SERVER_HPP
# define SERVER_HPP

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
# include <list>
#include <sstream>
# include "location.hpp"

class server
{
    public :
        int port;
        std::string server_name;
        std::string max_client_body_size;
        std::string error_page;
        std::list<location> locations;
        server();
        server(const std::list<std::string> &conf, int  n_serv);
};
#endif