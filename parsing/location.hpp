# ifndef LOCATION_HPP
# define LOCATION_HPP

#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <vector>

class location
{
    private:
    std::string locations;
    std::string allow_methods;
    std::string redirect;
    std::string root;
    std::string index;
    std::string cgi_pass;
    std::string upload_pass;
    public:
    location(){}
    ~location(){}
    location(const std::list<std::string> &config);
    void FillLocation(std::string prompt);
};
# endif