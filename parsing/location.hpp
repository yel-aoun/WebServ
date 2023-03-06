# ifndef LOCATION_HPP
# define LOCATION_HPP

#include <iostream>
#include <fstream>
#include <string>
#include <list>

class location
{
    private:
    std::string allow_methods;
    std::string redirect;
    std::string root;
    std::string index;
    std::string cgi_pass;
    std::string upload_pass;
    public:
    location(){}
    ~location(){}
    location(std::list<std::string> config);
};
# endif