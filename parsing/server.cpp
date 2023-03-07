/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-aoun <yel-aoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 10:02:47 by yel-aoun          #+#    #+#             */
/*   Updated: 2023/03/07 11:24:46 by yel-aoun         ###   ########.fr       */
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

server::server(const std::list<std::string> &conf, int n_serv)
{
    for(std::list<std::string>::const_iterator it = conf.begin(); it != conf.end(); it++)
    {
        std::string input = *it;
        std::string tabs = trim_tabs(input);
        std::string str = trim_spaces(tabs);
        std::vector<std::string> tokens = split(str, ' ');
        for (std::vector<std::string>::iterator tt = tokens.begin(); tt != tokens.end(); ++tt) {
            std::cout << *tt << std::endl;
        }
        std::cout<<"****************"<<std::endl;
    }
}