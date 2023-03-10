#include "location.hpp"
//DON'T FORGET TO SET THE DEFAULT VALUES OF SOME PARAMETERS
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

std::string trim_spaces(const std::string& str) {
    std::string::size_type first = str.find_first_not_of(' ');
    if (first == std::string::npos) {
        return "";
    }
    std::string::size_type last = str.find_last_not_of(' ');
    return str.substr(first, last - first + 1);
}

std::string trim_tabs(const std::string& str) {
    std::string::size_type first = str.find_first_not_of('\t');
    if (first == std::string::npos) {
        return "";
    }
    std::string::size_type last = str.find_last_not_of('\t');
    return str.substr(first, last - first + 1);
}

int count_slash(std::string location)
{
    int i = 0;
    int x = 0;
    for (; i != location.size() ; i++)
    {
        if (location[i] == '/')
            x++;
    }
    return (x);
}
std::string location::trim_directory(int slash)
{
    int x = this->locations.rfind("/");
    std::cout << "THE LOCATION OF / IS " << x << std::endl;
    std::string sub = locations.substr(0, x);
    std::cout << "THE SUBSTRING IS " << sub << std::endl;
    return (sub);
}

void location::FillLocation(std::string prompt)
{
    std::vector<std::string> substring = splitString(prompt, " ");
    if (substring.size() != 3)
    {
        for (std::vector<std::string>::iterator it = substring.begin(); it != substring.end(); ++it)
            std::cout << "********" << *it << std::endl;
        std::cout << "Error! the location block should start like this: Location 'your desired location' {" << std::endl;
        exit (1);
    }
    std::vector<std::string>::iterator it = substring.begin() + 1;
    this->locations = *it;
    int slash = count_slash(this->locations);
    std::string tmp;
    while (slash)
    {
        if (access(tmp.c_str(), F_OK) == 0)
            break;
        else
        {
            this->locations = trim_directory(slash);
            tmp = this->locations + "/";
            std::cout << "LOCATIONS  " << this->locations << std::endl;
        }
        slash--;
    }
    this->locations = tmp;
}

void location::FillAllow_methods(std::string prompt)
{

    std::vector<std::string> substring = splitString(prompt, " ");
    if (substring.size() < 2 || substring.size() > 4)
        return;
    allow_methods.clear();
    for (std::vector<std::string>::iterator it = substring.begin() + 1 ; it != substring.end(); ++it)
    {
        if (*it == "POST" || *it == "GET" || *it == "DELETE")
            this->allow_methods.push_back(*it);
        else
        {
            std::cout << "Error! Please ensure that the methods specified are either POST, GET or DELETE" << std::endl;
            exit (1);
        }
    }
}

void location::FillIndex(std::string prompt)
{
    std::vector<std::string> substring = splitString(prompt, " ");
    // if (substring.size() < 2)
    // {
        // std::cout << "Error! there's something wrong with the index parameter" << std::endl;
        // exit (1);
    // }
    if (substring.size() > 1)
    {
        index.clear();
        for(std::vector<std::string>::iterator it = substring.begin() + 1; it != substring.end(); ++it)
            index.push_back(*it);
    }
}

void location::FillRedirect(std::string prompt)
{
    std::vector<std::string> substring = splitString(prompt, " ");
    if (substring.size() != 2)
    {
        // std::cout << "Error! there's something wrong with the redirect parameter" << std::endl;
        // exit (1);
        return;
    }
    std::vector<std::string>::iterator it = substring.begin() + 1;
    this->redirect = *it;
}

void location::FillRoot(std::string prompt)
{
    std::vector<std::string> substring = splitString(prompt, " ");
    if (substring.size() != 2)
    {
        // std::cout << "Error! there's something wrong with the root parameter" << std::endl;
        // exit (1);
        return;
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
        //return ;
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
        return;
    std::vector<std::string>::iterator it = substring.begin() + 1;
    this->auto_index = *it;
}

location::location(const std::list<std::string> &config, int j)
{
    std::string nextvalue;
    std::list<std::string>::const_iterator it = config.begin();
    while (it != config.end() && j != 0)
    {
        if (it->find("}") != -1)
            j--;
        it++;
    }
    allow_methods.push_back("GET");
    allow_methods.push_back("POST");
    allow_methods.push_back("DELETE");
    redirect.clear();
    auto_index = "404";
    root = "/var/www/html/";
    index.push_back("index.html");
    index.push_back("index.htm");
    index.push_back("index.php");
    redirect = "404";
    cgi_pass = "404";
    //DON'T REDIRECT WHEN IT'S EMPTY
    for (; it != config.end() && std::next(it) != config.end(); ++it)
    {
        std::string tab = trim_tabs(*it);
        std::string prompt = trim_spaces(tab);
        nextvalue = *std::next(it);
        if (prompt.find("}") != -1)
            break;
        if (prompt.find("location") != -1)
        {
            //TRY TO HANDLE IF THE LOCATION ISN'T SPECIFIED
            this->FillLocation(prompt);
            std::cout << this->locations << std::endl;
        }
        else if (prompt.find("allow_methods") != -1)
        {
            this->FillAllow_methods(prompt);
            for (std::list<std::string>::iterator it = allow_methods.begin(); it != allow_methods.end(); ++it)
                std::cout << "------> " << *it << std::endl;
        }
        else if (prompt.find("redirect") != -1)
        {
            this->FillRedirect(prompt);
            std::cout << "-------->" << redirect << std::endl;
        }
        else if (prompt.find("auto_index") != -1)
        {
            this->FillAuto_index(*it);
            std::cout << "-------->" << auto_index << std::endl;
        }
        else if (prompt.find("root") != -1)
        {
            this->FillRoot(prompt);
            std::cout << "-------->" << root << std::endl;
        }
        else if (prompt.find("index") != -1)
        {
            this->FillIndex(prompt);
            //std::cout << "-------->" << index << std::endl;
        }
        else if (prompt.find("upload_pass") != -1)
        {
            this->FillUpload_pass(prompt);
            std::cout << "-------->" << upload_pass << std::endl;
        }
        else if (prompt.find("cgi_pass") != -1)
        {
            this->FillCgi_pass(prompt);
            std::cout << "-------->" << cgi_pass << std::endl;
        }
        else if (prompt == "}" && (nextvalue != "};" || (nextvalue.find("location") == -1 && nextvalue.find("{") == -1)))
        {
            std::cout << "Please only have another location block after starting with one" << std::endl;
            exit (1);
        }
        std::cout << "=========-------> " << prompt << "------- " << nextvalue << std::endl;
        //else
       //     std::cout << "Undefined element" << std::endl;
    }
}