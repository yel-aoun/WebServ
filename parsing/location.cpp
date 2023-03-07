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
void location::FillAllow_methods(std::string prompt)
{

    std::vector<std::string> substring = splitString(prompt, " ");
    if (substring.size() < 2 || substring.size() > 4)
    {
        std::cout << "sixe ====" << substring.size() << std::endl;
        for (std::vector<std::string>::iterator it = substring.begin(); it != substring.end(); ++it)
                std::cout << "------> " << *it << std::endl;
        std::cout << "Error! the allow_methods param has something wrong in it" << std::endl;
        exit (1);
    }

    for (std::vector<std::string>::iterator it = substring.begin() + 1 ; it != substring.end(); ++it)
    {
        if (*it == "POST" || *it == "GET" || *it == "DELETE")
            this->allow_methods.push_back(*it);
        else
        {
            std::cout << "----->" << *it << std::endl;
            std::cout << "Error! Please ensure that the methods specified are either POST, GET or DELETE" << std::endl;
            exit (1);
        }
    }
}

void location::FillIndex(std::string prompt)
{
    std::vector<std::string> substring = splitString(prompt, " ");
    if (substring.size() != 2)
    {
        std::cout << "Error! there's something wrong with the index parameter" << std::endl;
        exit (1);
    }
    std::vector<std::string>::iterator it = substring.begin() + 1;
    this->index = *it;
}

void location::FillRedirect(std::string prompt)
{
    std::vector<std::string> substring = splitString(prompt, " ");
    if (substring.size() != 2)
    {
        std::cout << "Error! there's something wrong with the redirect parameter" << std::endl;
        exit (1);
    }
    std::vector<std::string>::iterator it = substring.begin() + 1;
    this->redirect = *it;
}

void location::FillRoot(std::string prompt)
{
    std::vector<std::string> substring = splitString(prompt, " ");
    if (substring.size() != 2)
    {
        std::cout << "Error! there's something wrong with the root parameter" << std::endl;
        exit (1);
    }
    std::vector<std::string>::iterator it = substring.begin() + 1;
    this->root = *it;
}

void location::FillCgi_pass(std::string prompt)
{
    std::vector<std::string> substring = splitString(prompt, " ");
    if (substring.size() != 2)
    {
        std::cout << "Error! there's something wrong with the cgi_pass parameter" << std::endl;
        exit (1);
    }
    std::vector<std::string>::iterator it = substring.begin() + 1;
    this->cgi_pass = *it;
}

void location::FillUpload_pass(std::string prompt)
{
    std::vector<std::string> substring = splitString(prompt, " ");
    if (substring.size() != 2)
    {
        std::cout << "Error! there's something wrong with the upload_pass parameter" << std::endl;
        exit (1);
    }
    std::vector<std::string>::iterator it = substring.begin() + 1;
    this->upload_pass = *it;
}

void location::FillAuto_index(std::string prompt)
{
    std::vector<std::string> substring = splitString(prompt, " ");
    if (substring.size() != 2)
    {
        std::cout << "Error! there's something wrong with the auto_index parameter" << std::endl;
        exit (1);
    }
    std::vector<std::string>::iterator it = substring.begin() + 1;
    this->auto_index = *it;
}

location::location(const std::list<std::string> &config)
{
    for ( std::list<std::string>::const_iterator it = config.begin(); it != config.end(); ++it)
    {
        if (it->find("location") != -1)
        {
            //TRY TO HANDLE IF THE LOCATION ISN'T SPEIFIED
            std::cout << "Location found" << std::endl;
            this->FillLocation(*it);
            std::cout << this->locations << std::endl;
        }
        else if (it->find("allow_methods") != -1)
        {
            std::cout << "allow_methods found" << std::endl;
            this->FillAllow_methods(*it);
            for (std::list<std::string>::iterator it = allow_methods.begin(); it != allow_methods.end(); ++it)
                std::cout << "------> " << *it << std::endl;
        }
        else if (it->find("redirect") != -1)
        {
            std::cout << "redirect found" << std::endl;
            this->FillRedirect(*it);
        }
        else if (it->find("auto_index") != -1)
        {
            std::cout << "auto_index found" << std::endl;
            this->FillAuto_index(*it);
        }
        else if (it->find("root") != -1)
        {
            std::cout << "root found" << std::endl;
            this->FillRoot(*it);
        }
        else if (it->find("index") != -1)
        {
            std::cout << "index found" << std::endl;
            this->FillIndex(*it);
        }
        else if (it->find("upload_pass") != -1)
        {
            std::cout << "upload_pass found" << std::endl;
            this->FillUpload_pass(*it);
        }
        else if (it->find("cgi_pass") != -1)
        {
            std::cout << "cgi_pass found" << std::endl;
            this->FillCgi_pass(*it);
        }
        else
            std::cout << "Undefined element: " << *it << std::endl;
    }
}