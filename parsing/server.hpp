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
        std::string host_name;
        int max_client_body_size;
        std::vector<std::string> error_page;
        std::list<location> locations;
        server();
        server(const std::list<std::string> &conf, int  n_serv, int &count_loc);
        std::string trim_tabs(const std::string& str);
        std::string trim_spaces(const std::string& str);
};
#endif