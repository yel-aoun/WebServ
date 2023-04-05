#include "post.hpp"
#include "../headers_cpp.hpp"
#include "../server/server.hpp"
#include "../parsing/location.hpp"
#include "../server/client.hpp"

void    Post::generate_tmp_file(Client *client)
{
    time_t      now;

    this->tmp_file_path.append(client->loc_path);
    this->tmp_file_path.append(client->location_match.get_upload_pass());
    if (access(tmp_file_path.c_str(), F_OK))
        mkdir(tmp_file_path.c_str(), 0777);
    now = std::time(0);
    this->tmp_file_path.append("/tmp_");
    this->tmp_file_path.append(std::to_string(now));
    this->tmp_file_path.push_back('_');
    this->tmp_file_path.append(std::to_string(id++));
    std::cout << this->tmp_file_path << std::endl;
    this->tmp_file.open(this->tmp_file_path, std::ios::binary | std::ios::app);
    this->is_created = true;
}

void    Post::boundary_post (Server &serv, Client *client)
{
    if(!is_created)
        this->generate_tmp_file(client);
    if(!is_tmp_finished)
    {
        if(serv._request_size)
            this->tmp_file.write(serv._request, serv._request_size);
        if(memmem(serv._request, serv._request_size, this->_end_boundary.c_str(), this->_end_boundary.size()))
        {
            this->tmp_file.close();
            this->tmp_file_read.open(this->tmp_file_path, std::ios::binary | std::ios::app);
            is_tmp_finished = true;
        }
    }
    if(is_tmp_finished)
    {
        std::string line;

        std::cout << this->tmp_file_path << std::endl;
        std::cout << std::getline(this->tmp_file_read, line) << std::endl;
        std::cout << std::getline(this->tmp_file_read, line) << std::endl;
        std::cout << "line = " << line << std::endl;
        std::cout << "size = " << line.size() << std::endl;
    }
}