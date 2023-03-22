#include "post.hpp"
#include "../server/server.hpp"
#include "../parsing/location.hpp"
#include "../server/client.hpp"

void    Post::normal_post(Server &serv, Client *client)
{
        std::list<location> loc = serv.get_locations();
        std::string file_path;
        for (std::list<location>::iterator it = loc.begin(); it != loc.end(); ++it)
        {
            if (it->get_locations() == client->path)
            {
                if(client->file_name.empty())
                {
                    std::cout << "Hello" << std::endl;
                    std::map<std::string, std::vector<std::string> >::iterator iter;
                    iter = client->request_pack.find("Content-Type");
                    client->generate_file_name(*((*iter).second.begin()), serv.file_extensions);
                }
                file_path = it->get_upload_pass() + client->file_name;
                if (access(it->get_upload_pass().c_str(), F_OK))
                    mkdir(it->get_upload_pass().c_str(), 0777);
                if(access(const_cast<char *>(file_path.c_str()), F_OK))
                    client->file.open(const_cast<char *>(file_path.c_str()) , std::ios::binary | std::ios::app);
                client->file.write(const_cast<char *>(file_path.c_str()), serv._request_size);
            }
        }

}