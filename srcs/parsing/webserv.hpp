# ifndef WEBSERV_HPP
# define WEBSERV_HPP

# include "../headers_cpp.hpp"
# include "parce_server.hpp"
class Server;

class Webserv
{
        std::list<std::string> config;
        std::list<parce_server> servers_data;
        std::list<Server *> servers;

        void parce_config_file(std::string &conf_file);
        std::string trim_spaces(std::string& str);
    public:
        Webserv(std::string conf_file);
        void init_servers();
        void run_webservs();
};
# endif