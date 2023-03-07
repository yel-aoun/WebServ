/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-aoun <yel-aoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 10:02:47 by yel-aoun          #+#    #+#             */
/*   Updated: 2023/03/07 13:06:52 by yel-aoun         ###   ########.fr       */
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
int set_port(std::vector<std::string> tokens)
{
    std::vector<std::string>::iterator it = tokens.begin();
    int num;
    if (++it == tokens.end())
        return (0); // the end of 
    else
    {
        std::string str = *it;
        for(std::string::const_iterator it = str.begin(); it != str.end(); it++)
        {
            if (!isdigit(*it))
                return (0);
        }
        std::stringstream ss(str);
        ss >> num;
    }
    return (num);
}

// std::string set_server_name(std::vector<std::string> tokens)
// {
//     std::vector<std::string>::iterator it = tokens.begin();
//     if (it++ == tokens.end())
//         return (0);
// }

server::server(const std::list<std::string> &conf, int n_serv)
{
    // int i = 0;
    // while (i < n_serv)
    // {
        for(std::list<std::string>::const_iterator it = conf.begin(); it != conf.end(); it++)
        {
            std::string input = *it;
            std::string tabs = trim_tabs(input);
            std::string str = trim_spaces(tabs);
            std::vector<std::string> tokens = split(str, ' ');
            std::vector<std::string>::iterator tt = tokens.begin();
            // for (std::vector<std::string>::iterator tt = tokens.begin(); tt != tokens.end(); ++tt) {
            //     std::cout << *tt << std::endl;
            // }
            if (*tt == "port")
                this->port = set_port(tokens);
            else if (*tt == "server_name")
                std::cout<<*tt<<std::endl;
                // this->server_name = set_server_name(tokens);
            else if (*tt == "max_client_body_size")
                std::cout<<*tt<<std::endl;
            else if (*tt == "error_page")
                std::cout<<*tt<<std::endl;
            else if (*tt == "locations")
                std::cout<<*tt<<std::endl;
        }
        std::cout<<port<<std::endl;
        
    //     i++;
    // }
}