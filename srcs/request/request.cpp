# include "request.hpp"

Request::Request(std::string &buffer)
{
    std::stringstream ss(buffer);
    std::string token;
    int i = 0;
    while (std::getline(ss, token))
    {
        fill_map_request(token);
        i++;
    }
}

void    Request::fill_map_request(std::string   &buff_line)
{
    std::stringstream ss(buff_line);
    std::string token;
    ss >> token;
    if (token == "GET" || token == "POST" || token == "DELETE")
    {
        std::vector<std::string> meth;
        meth.push_back(token);
        this->request.insert(std::make_pair("METHOD",meth));
        ss >> token;
        std::vector<std::string> path;
        path.push_back(token);
        this->request.insert(std::make_pair("PATH",path));
        ss >> token;
        std::vector<std::string> http;
        http.push_back(token);
        this->request.insert(std::make_pair("HTTP",http));
    }
   else
   {
        std::vector<std::string> value;
        int len = token.length();
        std::string key = token.substr(0, len - 1);
        while (ss >> token)
            value.push_back(token);
        this->request.insert(std::make_pair(key,value));
   }
}