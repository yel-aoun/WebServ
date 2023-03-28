#include "post.hpp"
#include "../headers_cpp.hpp"
#include "../server/server.hpp"
#include "../parsing/location.hpp"
#include "../server/client.hpp"

bool Post::check_hex()
{
    char    *str;
    char    hex_copy[10];
    int     hex_len;

    if(!memmem(this->_hex, 2, "\r\n", 2))
        return (false);
    str = (char *) memmem(this->_hex + 2, 8, "\r\n", 2);
    if(!str)
        return(false);
    hex_len = str - (this->_hex + 2);
    memcpy(hex_copy, this->_hex + 2, hex_len);
    memset(this->_hex, 0, 10);
    memcpy(this->_hex, hex_copy, hex_len);
    this->_hex_ready = true;
    return (true);
}

void    Post::chunked_post(Server &serv, Client *client)
{
    int buff_read = 0;
    char *str;

    this->_hex_ready = false;
    if(access("video.mp4", F_OK))
        client->file.open("video.mp4", std::ios::binary | std::ios::app);
    while(buff_read < client->_request_size)
    {
        if(!this->_chunk_len)
        {

            while((this->_hex_len < 10) && (buff_read < MAX_REQUEST_SIZE))
            {
                this->_hex[this->_hex_len++] = client->_request[buff_read++];
                if(check_hex())
                    break ;
            }
            if(!this->_hex_ready)
                break;
            this->_chunk_len = std::stoi(this->_hex, nullptr, 16);
            this->_hex_len = 0;
            memset(this->_hex, 0, 20);
            if(!this->_chunk_len)
            {
                client->file.close();
                exit(0);
                break;
            }
        };
        while((buff_read < client->_request_size) && this->_chunk_len)
        {
            client->file.write(client->_request.c_str() + buff_read, 1);
            this->_chunk_len--;
            buff_read++;
        }
    }
}