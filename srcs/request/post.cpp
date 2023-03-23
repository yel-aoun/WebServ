
#include "post.hpp"
#include "../server/server.hpp"
#include "../parsing/location.hpp"
#include "../server/client.hpp"


Post::Post(): body_or_head(0), _post_type(0)
{
    this->generate_extensions();
}

void    Post::call_post_func(Server &serv, Client *client)
{
    
    if(this->_post_type == 0)
        this->normal_post(serv, client);
}

std::string Post::check_hexa(std::string buff)
{
    std::string hex;
    int i = 0;
    int ind = buff.find("\r\n");
    
    std::cout << "INDEX ======== " << ind << std::endl;
    while (buff[ind]!= '\r' && buff[ind]!= '\n')
        hex += buff[ind++];
    
    return (hex);
}


int Post::hexToDec(const std::string& hexStr) {
    std::stringstream ss;
    ss << std::hex << hexStr;
    int decNum;
    ss >> decNum;
    return decNum;
}

// void    Post::normal_post(Server &serv, std::string &path)
// {
//     // std::list<location> loc = serv.get_locations();
//     // std::ofstream file;
//     //    for (std::list<location>::iterator it = loc.begin(); it != loc.end(); ++it)
//     //    {
//     //        if (it->get_locations() == path)
//     //        {
//     //            if (access(it->get_upload_pass().c_str(), F_OK))
//     //                int status = mkdir(it->get_upload_pass().c_str(), 0777);
//     //             if(access(std::strcat(const_cast<char *>(it->get_upload_pass().c_str()), "/testing"), F_OK))
//     //                 file(it->get_upload_pass() + "/testing");
//     //             else
//     //                 file.open(it->get_upload_pass() + "/testing");
//     //             if (file.is_open())
//     //             {
//     //                 if(!file.write(serv._request_buff, std::strlen(serv._request_buff)))
//     //                     file.close();
//     //             }
//     //        }
//     //    }
// }

int Post::skip_hex(std::string body)
{
     int i = body.find("\r\n") + 1;
    while (body[++i])
        if (body[i] == '\n')
            break;
    return (i + 1);
}

void Post::exec_head(std::string buff, Server &serv, std::string &path)
{
    // std::cout << "Hello" << std::endl;
    // if (!path.empty())
    // {
    //     std::list<location> loc = serv.get_locations();
    //     for (std::list<location>::iterator it = loc.begin(); it != loc.end(); ++it)
    //     {
    //         if (it->get_locations() == path)
    //         {
    //             if (access(it->get_upload_pass().c_str(), F_OK))
    //                 int status = mkdir(it->get_upload_pass().c_str(), 0777);
    //             std::ofstream file(it->get_upload_pass() + "/testing");
    //             if (file.is_open())
    //             {
    //                 std::string body = seperate_header(buff);
    //                 std::string hex = check_hexa(body);
    //                 int num_to_read = hexToDec(hex);
    //                  int ind = skip_hex(body);
    //                 file.write(&body[ind], num_to_read);
    //                 //if (i == body.find("\r\n0\r\n"))
    //                 //{
    //                     file.close();
    //                   //  break;
    //                 //}
    //             }
    //         }
    //     }
    // }
}


void Post::exec_body(std::string buff, Server &serv, std::string &path)
{
    if (!path.empty())
    {
        std::list<location> loc = serv.get_locations();
        for (std::list<location>::iterator it = loc.begin(); it != loc.end(); ++it)
        {
            if (it->get_locations() == path)
            {
                if (access(it->get_upload_pass().c_str(), F_OK))
                    int status = mkdir(it->get_upload_pass().c_str(), 0777);
                std::ofstream file(it->get_upload_pass() + "/testing");
                if (file.is_open())
                {
                    std::string hex = check_hexa(buff);
                    std::cout << "HEX ===== " << hex << std::endl;
                    int num_to_read = hexToDec(hex);
                     int ind = skip_hex(buff);
                    file.write(&buff[ind], num_to_read);
                    //if (i == body.find("\r\n0\r\n"))
                    //{
                        file.close();
                      //  break;
                    //}
                }
            }
        }
    }
}

std::string Post::generate_file_name(std::string mime_type)
{
    std::map <std::string, std::string>::iterator iter;
    std::string file_name;
    time_t      now;

    now = std::time(0);
    file_name = std::to_string(now);
    iter = this->_extensions.find(mime_type);
    if(iter == this->_extensions.end())
        return (file_name);
    else
        return (file_name.append((*iter).second));
}

void Post::generate_extensions(void)
{
   this->_extensions["audio/aac"] = ".aac";
   this->_extensions["application/x-abiword"] = ".abw";
   this->_extensions["application/x-freearc"] = ".arc";
   this->_extensions["image/avif"] = ".avif";
   this->_extensions["video/x-msvideo"] = ".avi";
   this->_extensions["application/vnd.amazon.ebook"] = ".azw";
   this->_extensions["application/octet-stream"] = ".bin";
   this->_extensions["image/bmp"] = ".bmp";
   this->_extensions["application/x-bzip"] = ".bz";
   this->_extensions["application/x-bzip2"] = ".bz2";
   this->_extensions["application/x-cdf"] = ".cda";
   this->_extensions["application/x-csh"] = ".csh";
   this->_extensions["text/css"] = ".css";
   this->_extensions["text/csv"] = ".csv";
   this->_extensions["application/msword"] = ".doc";
   this->_extensions["application/vnd.openxmlformats-officedocument.wordprocessingml.document"] = ".docx";
   this->_extensions["application/vnd.ms-fontobject"] = ".eot";
   this->_extensions["application/epub+zip"] = ".epub";
   this->_extensions["application/gzip"] = ".gz";
   this->_extensions["image/gif"] = ".gif";
   this->_extensions["text/html"] = ".html";
   this->_extensions["image/vnd.microsoft.icon"] = ".ico";
   this->_extensions["text/calendar"] = ".ics";
   this->_extensions["application/java-archive"] = ".jar";
   this->_extensions["image/jpeg"] = ".jpg";
   this->_extensions["text/javascript"] = ".js";
   this->_extensions["application/json"] = ".json";
   this->_extensions["application/ld+json"] = ".jsonld";
   this->_extensions["audio/midi"] = ".midi";
   this->_extensions["text/javascript"] = ".mjs";
   this->_extensions["audio/mpeg"] = ".mp3";
   this->_extensions["video/mp4"] = ".mp4";
   this->_extensions["video/mpeg"] = ".mpeg";
   this->_extensions["application/vnd.apple.installer+xml"] = ".mpkg";
   this->_extensions["application/vnd.oasis.opendocument.presentation"] = ".odp";
   this->_extensions["application/vnd.oasis.opendocument.spreadsheet"] = ".ods";
   this->_extensions["application/vnd.oasis.opendocument.text"] = ".odt";
   this->_extensions["audio/ogg"] = ".oga";
   this->_extensions["video/ogg"] = ".ogv";
   this->_extensions["application/ogg"] = ".ogx";
   this->_extensions["audio/opus"] = ".opus";
   this->_extensions["font/otf"] = ".otf";
   this->_extensions["image/png"] = ".png";
   this->_extensions["application/pdf"] = ".pdf";
   this->_extensions["application/x-httpd-php"] = ".php";
   this->_extensions["application/vnd.ms-powerpoint"] = ".ppt";
   this->_extensions["application/vnd.openxmlformats-officedocument.presentationml.presentation"] = ".pptx";
   this->_extensions["application/vnd.rar"] = ".rar";
   this->_extensions["application/rtf"] = ".rtf";
   this->_extensions["application/x-sh"] = ".sh";
   this->_extensions["image/svg+xml"] = ".svg";
   this->_extensions["application/x-tar"] = ".tar";
   this->_extensions["image/tiff"] = ".tiff";
   this->_extensions["video/mp2t"] = ".ts";
   this->_extensions["font/ttf"] = ".ttf";
   this->_extensions["text/plain"] = ".txt";
   this->_extensions["application/vnd.visio"] = ".vsd";
   this->_extensions["audio/wav"] = ".wav";
   this->_extensions["audio/webm"] = ".weba";
   this->_extensions["video/webm"] = ".webm";
   this->_extensions["image/webp"] = ".webp";
   this->_extensions["font/woff"] = ".woff";
   this->_extensions["font/woff2"] = ".woff2";
   this->_extensions["application/xhtml+xml"] = ".xhtml";
   this->_extensions["application/vnd.ms-excel"] = ".xls";
   this->_extensions["application/vnd.openxmlformats-officedocument.spreadsheetml.sheet"] = ".xlsx	";
   this->_extensions["application/xml"] = ".xml";
   this->_extensions["application/vnd.mozilla.xul+xml"] = ".xul";
   this->_extensions["application/zip"] = ".zip";
   this->_extensions["video/3gpp"] = ".3gp";
   this->_extensions["video/3gpp2"] = ".3g2";
   this->_extensions["application/x-7z-compressed"] = ".7z";
}