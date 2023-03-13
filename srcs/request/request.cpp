# include "request.hpp"

Request::Request(std::string &buffer)
{
    std::stringstream ss(buffer);
    std::string token;
    // std::cout<<"+++++______+++++++ " <<std::endl;
    // std::cout<<"-=+-=+"<<token<<std::endl;
    int i = 0;
    while (std::getline(ss, token))
    {
        std::cout<<"=====>"<<i<<std::endl;
        // if (token[0] == '\r')
        // {
        //     std::cout<<"found"<<std::endl;
        //     break ;
        // }
        fill_map_request(token);
        i++;
    }
    std::cout<<"++++"<<this->request.find("PATH")->second<<"++++"<<std::endl;
}

void    Request::fill_map_request(std::string   &buff_line)
{
    std::stringstream ss(buff_line);
    std::string token;
    ss >> token;
    if (token == "GET" || token == "POST" || token == "DELETE")
    {
        this->request.insert(std::make_pair("METHOD",token));
        ss >> token;
        this->request.insert(std::make_pair("PATH",token));
    }
//    else
//    {
//        if (token == "Host:")
//            this->request.insert(std::make_pair("HOST",token));
//        else if(token == "User-Agent:")
//            this->request.insert(std::make_pair("USER_AGENT",token));
//        // else if(token == "Accept:")
//        // {
//        //     ss >> token;
//        //     std::string str = token;
//        //     while (ss >> token)
//        //     {
//        //         str = str + " " + token;
//        //     }
//        //     this->request.insert(std::make_pair("ACCEPT",token));
//        // }
//    }
}