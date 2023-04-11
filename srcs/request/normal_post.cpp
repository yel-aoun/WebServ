#include "post.hpp"
#include "../server/server.hpp"
#include "../parsing/location.hpp"
#include "../server/client.hpp"

void    Post::normal_post(Server &serv, Client *client)
{
    // for (int i = 0; i < serv._request_size; i++)
    //     printf("%c",serv._request[i]);
    // i have to write byte by byte because i have to check for content_length.
    // if i change the content_length to some number not <calculated when request is sent> ?
    client->file.write(serv._request, serv._request_size);
    client->_content_len -= serv._request_size;
    // std::cout << serv._request << std::endl;
    // std::cout << "LENGTH=== " << client->_content_len << std::endl;
    if(!client->_content_len)
    {
        if (!client->exec_path.empty())
        {
            client->is_done = 1 ;
            _is_matched = 0;
        }
        client->file.close();
    }
    //  std::cout << serv._request << std::endl;
        // client->file.close();
}