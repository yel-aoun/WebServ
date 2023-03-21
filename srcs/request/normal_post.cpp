#include "Post.hpp"
#include "../server/server.hpp"
#include "../parsing/location.hpp"
#include "../server/client.hpp"

void    Post::normal_post(Server &serv, Client *client)
{
        std::list<location> loc = serv.get_locations();
        for (std::list<location>::iterator it = loc.begin(); it != loc.end(); ++it)
        {
            if (it->get_locations() == client->path)
            {
                    if (access(it->get_upload_pass().c_str(), F_OK))
                        mkdir(it->get_upload_pass().c_str(), 0777);
                    if(access(std::strcat(const_cast<char *>(it->get_upload_pass().c_str()), "/mas3od"), F_OK))
                        client->file.open(it->get_upload_pass() + "/mas3od");
                    client->file.write(serv._request_buff, std::strlen(serv._request_buff));
            }
        }

}