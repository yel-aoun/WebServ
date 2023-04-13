#include "post.hpp"
#include "../headers_cpp.hpp"
#include "../server/server.hpp"
#include "../parsing/location.hpp"
#include "../server/client.hpp"

int Post::generate_bdr_file(Server &serv, Client *client)
{
    int len;
    char *end;
    char *content_type;
    std::string mime_type;

    end = (char *) memmem(serv._request, serv._request_size, "\r\n\r\n", 4);
    len = end - serv._request + 4;
    content_type = (char *) memmem(serv._request, len, "Content-Type: ", 14);
    if(content_type)
    {
        int i = 14;
        mime_type.clear();
        while(content_type[i] != '\r')
            mime_type.push_back((content_type[i++]));
    }
    client->file_path = client->loc_path + "/" + client->location_match.get_upload_pass();
    if (access(client->file_path.c_str(), F_OK))
        mkdir(client->file_path.c_str(), 0777);
    client->generate_file_name(mime_type, serv.file_extensions);
    if(access(const_cast<char *>(client->file_path.c_str()), F_OK))
        client->file.open(client->file_path, std::ios::binary | std::ios::app);
    this->is_created = true;
    return (len);
}

void    Post::boundary_post (Server &serv, Client *client)
{
    int buff_read = 0;
    int bdr_pos = serv._request_size;
    char *bdr;
    bool close = false;

    if(!is_created)
        buff_read = this->generate_bdr_file(serv, client);
    bdr = (char *) memmem(serv._request + buff_read, serv._request_size - buff_read, client->boundary.c_str(), client->boundary.size());
    if(bdr)
    {
        bdr_pos = bdr - serv._request - 4;
        close = true;
    }
    while(buff_read < bdr_pos)
    {
        client->file.write(serv._request + buff_read, 1);
        buff_read++;
    }
    if(close)
    {
        client->file.close();
        client->Fill_response_data(201, "Created", "./default_error_pages/201.html");
    }
}