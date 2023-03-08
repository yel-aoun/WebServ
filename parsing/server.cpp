/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouazahr <zouazahr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 10:02:47 by yel-aoun          #+#    #+#             */
/*   Updated: 2023/03/08 17:43:08 by zouazahr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "server.hpp"

std::vector<std::string> split(const std::string &str, char delimiter)
{
        std::vector<std::string> tokens;
        std::istringstream tokenStream(str);
        std::string token;
        while (std::getline(tokenStream, token, delimiter))
        {
            tokens.push_back(token);
        }
        return (tokens);
}

std::string server::trim_spaces(const std::string& str) {
    std::string::size_type first = str.find_first_not_of(' ');
    if (first == std::string::npos) {
        return "";
    }
    std::string::size_type last = str.find_last_not_of(' ');
    return str.substr(first, last - first + 1);
}

std::string server::trim_tabs(const std::string& str) {
    std::string::size_type first = str.find_first_not_of('\t');
    if (first == std::string::npos) {
        return "";
    }
    std::string::size_type last = str.find_last_not_of('\t');
    return str.substr(first, last - first + 1);
}
int set_port(std::vector<std::string> &tokens)
{
    std::vector<std::string>::iterator it = tokens.begin();
    int num;
    if (++it == tokens.end())
        return (8080); // the end of 
    else
    {
        std::string str = *it;
        for(std::string::const_iterator it = str.begin(); it != str.end(); it++)
        {
            if (!isdigit(*it))
                return (8080);
        }
        std::stringstream ss(str);
        ss >> num;
    }
    return (num);
}

std::string set_host_name(std::vector<std::string> &tokens)
{
    std::vector<std::string>::iterator it = tokens.begin();
    if (++it == tokens.end())
        return ("127.0.0.1");
    else
    {
        return (*it);
    }
}

int set_max_client_body_size(std::vector<std::string> &tokens)
{
    std::vector<std::string>::iterator it = tokens.begin();
    int num;
    if (++it == tokens.end())
        return (1);
    else
    {
        std::string str = *it;
        for(std::string::const_iterator it = str.begin(); it != str.end(); it++)
        {
            if (!isdigit(*it))
                return (8080);
        }
        std::stringstream ss(str);
        ss >> num;
    }
    return (num);
}

std::vector<std::string> set_error_page(std::vector<std::string> &tokens)
{
    std::vector<std::string>::iterator it = tokens.begin();
    std::vector<std::string> tmp;
    if (++it == tokens.end())
    {
        tmp.push_back("defualt");
        return (tmp);
    }
    else
    {
        tmp.push_back(*it);
        if (++it == tokens.end())
            return (tmp);
        else
            tmp.push_back(*it);
    }
    return (tmp);
}

server::server(const std::list<std::string> &conf, int n_serv, int &count_loc)
{
    std::list<std::string>::const_iterator it = conf.begin();
    while (it != conf.end() && n_serv != 0)
    {
        if (it->find("};"))
            n_serv--;
        it++;
    }
    // i must set the default of my variables each time i work on new server 
    //so the default will be set first and 
    //then i read from the conf file to change the default if i must to
    this->port = 8080;
    this->host_name = "172.0.0.1";
    this->max_client_body_size = 1;
    // this->error_page;
    for(; it != conf.end(); it++)
    {
        if (it->find("location") != -1 && it->rfind("{") != -1)
            count_loc++;
        if (it->rfind("};") != std::string::npos)
            break;
        std::string input = *it;
        std::string tabs = trim_tabs(input);
        std::string str = trim_spaces(tabs);
        std::vector<std::string> tokens = split(str, ' ');
        std::vector<std::string>::iterator tt = tokens.begin();
        if (*tt == "port")
            this->port = set_port(tokens);
        else if (*tt == "host_name")
            // std::cout<<*tt<<std::endl;
            this->host_name = set_host_name(tokens);
        else if (*tt == "max_client_body_size")
            this->max_client_body_size = set_max_client_body_size(tokens);
        else if (*tt == "error_page")
            this->error_page = set_error_page(tokens);
    }
}