#include "location.hpp"

location::location(std::list<std::string> config)
{
    for (std::list<std::string>::iterator it = config.begin(); it != config.end(); ++it)
    {
        if (it->find("location") != -1)
            std::cout << "Location found" << std::endl;
        else if (it->find("allow_methods") != -1)
            std::cout << "allow_methods found" << std::endl;
        else if (it->find("redirect") != -1)
            std::cout << "redirect found" << std::endl;
        else if (it->find("auto_index") != -1)
            std::cout << "auto_index found" << std::endl;
        else if (it->find("root") != -1)
            std::cout << "root found" << std::endl;
        else if (it->find("index") != -1)
            std::cout << "index found" << std::endl;
        else if (it->find("upload_pass") != -1)
            std::cout << "upload_pass found" << std::endl;
        else if (it->find("cgi_pass") != -1)
            std::cout << "cgi_pass found" << std::endl;
        else
            std::cout << "Undefined element" << std::endl;
    }
}