#include "request.hpp"

// void send_chunk(int sockfd, const char* data, int size) {
//     // Convert the size to hexadecimal format
//     stringstream ss;
//     ss << hex << size << "\r\n";
//     string size_str = ss.str();

//     // Send the chunk size and data to the server
//     send(sockfd, size_str.c_str(), size_str.length(), 0);
//     send(sockfd, data, size, 0);
//     send(sockfd, "\r\n", 2, 0);
// }

std::string check_hexa(std::string buff)
{
    std::string hex;
    int i = 0;
    int ind = buff.find("\r\n") + 2;
    while (buff[ind]!= '\r' && buff[ind]!= '\n')
        hex += buff[ind++];
    return (hex);
}


int hexToDec(const std::string& hexStr) {
    std::stringstream ss;
    ss << std::hex << hexStr;
    int decNum;
    ss >> decNum;
    return decNum;
}

std::string seperate_header(std::string buff)
{
    int x = buff.find("\r\n\r\n") + 2;
    std::string body = buff.substr(x, buff.size() - (x + 1));
    return (body);
}

int skip_hex(std::string body)
{
     int i = body.find("\r\n") + 1;
    while (body[++i])
        if (body[i] == '\n')
            break;
    return (i + 1);
}

void Request::post(std::string buff, Server serv, std::list<Client *>::iterator iter)
{
    std::map<std::string, std::vector<std::string> >::iterator map = (*iter)->request_pack.find("PATH");
    if (map != (*iter)->request_pack.end())
    {
        std::vector<std::string> vec = map->second;
        std::vector<std::string>::iterator iter = vec.begin();
        std::list<location> loc = serv.get_locations();
        for (std::list<location>::iterator it = loc.begin(); it != loc.end(); ++it)
        {
            if (it->get_locations() == *iter)
            {
                if (access(it->get_upload_pass().c_str(), F_OK))
                    int status = mkdir(it->get_upload_pass().c_str(), 0777);
                std::ofstream file(it->get_upload_pass() + "/testing");
                if (file.is_open())
                {
                    std::string body = seperate_header(buff);
                    std::string hex = check_hexa(body);
                    int num_to_read = hexToDec(hex);
                     int ind = skip_hex(body);
                    file.write(&body[ind], num_to_read);
                    //if (i == body.find("\r\n0\r\n"))
                    //{
                        file.close();
                      //  break;
                    //}
                }
            }
        }
    }
 //   std::ofstream outfile("test2.txt"); 

    // if (outfile.is_open())
    // {
        
    // }
    // ifstream file("myfile.txt");
    // if (!file.is_open()) {
    //     cerr << "Error opening file." << endl;
    //     return 1;
    // }
    // char buffer[1024];
    // while (!file.eof()) {
    //     file.read(buffer, sizeof(buffer));
    //     int size = file.gcount();
    //     send_chunk(sockfd, buffer, size);
    //}

}