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
        std::vector<std::string> path_query;
        std::stringstream str(token);
        std::string splt;
        while (getline(str, splt, '?'))
        {
            path_query.push_back(splt);
        }
        std::vector<std::string>::iterator iter = path_query.begin();
        std::vector<std::string> path;
        std::string find = from_hexa_to_decimal(*iter);
        path.push_back(find);
        this->request.insert(std::make_pair("PATH",path));
        if (++iter  != path_query.end())
        {
            std::vector<std::string> query;
            query.push_back(*iter);
            this->request.insert(std::make_pair("query",query));
        }
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

std::string Request::from_hexa_to_decimal(std::string &str)
{
    std::string path;
    if (str.rfind('%') == std::string::npos)
        return (str);
    else
    {
        std::string::iterator it = str.begin();
        for(; it != str.end(); it++)
        {
            if (*it == '%' && (it + 1) != str.end() && (it + 2) != str.end() && *(it + 1) != '%' && *(it + 2) != '%')
            {
                it++;
                std::string tmp;
                tmp += *it;
                tmp += + *(it + 1);
                path += get_decimal(tmp);
                it++;
            }
            else
                path += *it;
        }
    }
    return (path);
}

int Request::get_decimal(std::string tmp)
{
    std::istringstream iss(tmp);
    int hexa_val;
    iss>>std::hex>>hexa_val;
    return (hexa_val);
}