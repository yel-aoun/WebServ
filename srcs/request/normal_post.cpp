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
     std::cout << serv._request << std::endl;
        // client->file.close();
}