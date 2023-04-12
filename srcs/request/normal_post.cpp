#include "post.hpp"
#include "../server/server.hpp"
#include "../parsing/location.hpp"
#include "../server/client.hpp"

void    Post::normal_post(Server &serv, Client *client)
{
    // i have to write byte by byte because i have to check for content_length.
    // if i change the content_length to some number not <calculated when request is sent> ?
    client->file.write(serv._request, serv._request_size);
    client->_content_len -= serv._request_size;
    if(!client->_content_len)
    {
        if (!client->exec_path.empty())
        {
            client->is_done = 1 ;
            _is_matched = 0;
        }
        else
        {
            client->status_code = 201;
            client->status = "Created";
            client->loc_path = "./default_error_pages/201.html";
            client->_is_ready = true;
        }
        client->file.close();
    }
}