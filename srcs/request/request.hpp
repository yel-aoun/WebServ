#ifndef REQUEST_HPP
#define REQUEST_HPP

#include <map>
#include <iostream>
#include <string>
#include <sstream>
class Request
{
    private:
        void    fill_map_request(std::string   &token);
    public:
        std::map<std::string, std::string> request;
        Request();
        Request(std::string &buffer);
};
#endif