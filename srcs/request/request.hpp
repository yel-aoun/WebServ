#ifndef REQUEST_HPP
#define REQUEST_HPP

#include <map>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
class Request
{
    private:
        void    fill_map_request(std::string   &token);
        std::string from_hexa_to_decimal(std::string &str);
        int get_decimal(std::string tmp);
    public:
        std::map<std::string, std::vector<std::string> > request;
        Request();
        Request(std::string &buffer);
};
#endif