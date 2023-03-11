# ifndef LOCATION_HPP
# define LOCATION_HPP

#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <vector>
#include <unistd.h>
#include <sstream>

class location
{
    private:
    std::string locations;
    std::list<std::string> allow_methods;
    std::string redirect;
    std::list<std::string> index;
    std::string cgi_pass;
    std::string upload_pass;
    std::string auto_index;
    public:
    std::string root;
    location(){}
    ~location(){}
    location(const std::list<std::string> &config, int j);
    void FillLocation(std::string prompt);
    void FillAllow_methods(std::string prompt);
    void FillIndex(std::string prompt);
    void FillRedirect(std::string prompt);
    void FillRoot(std::string prompt);
    void FillCgi_pass(std::string prompt);
    void FillUpload_pass(std::string prompt);
    void FillAuto_index(std::string prompt);
    std::string trim_directory(int slash);
    void initialize();
};
# endif