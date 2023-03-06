#include "location.hpp"

std::vector<std::string> splitString(const std::string& str, std::string delimiter) {
    std::vector<std::string> substrings;
    std::size_t pos = 0;
    std::size_t found;
    while ((found = str.find(delimiter, pos)) != -1) {
        substrings.push_back(str.substr(pos, found - pos));
        pos = found + delimiter.length();
    }
    substrings.push_back(str.substr(pos));
    return substrings;
}

void location::FillLocation(std::string prompt)
{
    std::vector<std::string> substring = splitString(prompt, " ");
    if (substring.size() != 3)
    {
        std::cout << "Error! the location block should start like this: Location 'your desired location' {" << std::endl;
        exit (1);
    }
    std::vector<std::string>::iterator it = substring.begin() + 1;
    this->locations = *it;
}

location::location(const std::list<std::string> &config)
{
    for ( std::list<std::string>::const_iterator it = config.begin(); it != config.end(); ++it)
    {
        if (it->find("location") != -1)
        {
            std::cout << "Location found" << std::endl;
            this->FillLocation(*it);
            std::cout << this->locations << std::endl;
        }
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
        {
            std::cout << "Undefined element: " << *it << std::endl;
        }
    }
}