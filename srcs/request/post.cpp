#include "post.hpp"
#include "../server/server.hpp"
#include "../parsing/location.hpp"
#include "../server/client.hpp"
#include "../parsing/webserv.hpp"


Post::Post(): body_or_head(0), _post_type(0), _chunk_len(0), _hex_len(0), is_created(false), _buff_read(0)
{
    this->is_tmp_finished = 0;
    memset(this->_hex, 0, 20);
}

Post::~Post(){}

void    Post::call_post_func(Server &serv, Client *client)
{
    if(!is_created && this->_post_type != 1)
        this->create_file(serv, client);
    switch(this->_post_type)
    {
        case 0:
            this->normal_post(serv, client);
            break;
        case 1:
            this->boundary_post(serv, client);
            break;
        case 2:
            this->chunked_post(serv, client);
            break;
    }
}

void    Post::create_file(Server &serv, Client *client)
{
    std::string merge_path;
    if(client->file_path.empty())
    {
        std::map<std::string, std::vector<std::string> >::iterator iter;
        iter = client->request_pack.find("Content-Type");
        merge_path = client->loc_path + "/" + client->location_match.get_upload_pass();
        client->file_path = merge_path;
        client->generate_file_name(*((*iter).second.begin()), serv.file_extensions);
    }
    if (access(merge_path.c_str(), F_OK))
        mkdir(merge_path.c_str(), 0777);
    if(access(const_cast<char *>(client->file_path.c_str()), F_OK))
        client->file.open(client->file_path, std::ios::binary | std::ios::app);
    this->is_created = true;
}