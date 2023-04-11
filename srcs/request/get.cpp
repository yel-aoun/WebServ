# include "get.hpp"
#include "../server/client.hpp"
#include "../parsing/location.hpp"
#include "../server/server.hpp"
#include <sys/stat.h>
#include <dirent.h>
#include <fcntl.h>

Get::Get(): state(0), index_exist(0)
{
}

Get::~Get()
{
}

void    Get::get_requested_resource(std::list<Client *>::iterator iter)
{
    this->state = 0;
    this->read = 0;
    std::string path = (*iter)->loc_path; 
    struct stat file_stat;
    if (stat(path.c_str(), &file_stat) == 0)
    {
        if (S_ISDIR(file_stat.st_mode))
        {
            check_the_end_of_uri(iter);
        }
        else if (S_ISREG(file_stat.st_mode))
            if_location_has_cgi(iter);
        else
        {
            this->state = 1;
            (*iter)->status_code = 404;
            (*iter)->status = "Not Found";
            std::vector<std::string> error = (*iter)->error_pages;
            std::vector<std::string>::iterator it = error.begin();
            if (it != error.end())
            {
                int num;
                std::stringstream ss(*it);
                ss >> num;
                std::cout<<"num : "<<num<<" (*it) : "<< (*it)<<std::endl;
                if (num == (*iter)->status_code)
                {
                    std::cout<<"forbiden"<<std::endl;
                    std::string path = "." + (*++it);
                    struct stat file_stat;
                    if (stat(path.c_str(), &file_stat) == 0)
                    {
                        if (S_ISREG(file_stat.st_mode))
                        {
                            (*iter)->loc_path = path;
                            this->state = 1;
                            return ;
                        }
                        else
                        {
                            (*iter)->loc_path = "./default_error_pages/404.html";
                            this->state = 1;
                            return ;
                        }
                    }
                    else
                    {
                        (*iter)->loc_path = "./default_error_pages/404.html";
                        this->state = 1;
                        return ;
                    }
                }
                else
                {
                    (*iter)->loc_path = "./default_error_pages/404.html";
                    this->state = 1;
                    return ;
                }
            }
            else
                (*iter)->loc_path = "./default_error_pages/404.html";
            return ;
        }
    }
    else
    {
        this->state = 1;
        (*iter)->status_code = 404;
        (*iter)->status = "Not Found";
        std::vector<std::string> error = (*iter)->error_pages;
        std::vector<std::string>::iterator it = error.begin();
        if (it != error.end())
        {
            int num;
            std::stringstream ss(*it);
            ss >> num;
            if (num == (*iter)->status_code)
            {
                std::string path = "." + (*++it);
                struct stat file_stat;
                if (stat(path.c_str(), &file_stat) == 0)
                {
                    if (S_ISREG(file_stat.st_mode))
                    {
                        (*iter)->loc_path = path;
                        this->state = 1;
                        return ;
                    }
                    else
                    {
                        (*iter)->loc_path = "./default_error_pages/404.html";
                        this->state = 1;
                        return ;
                    }
                }
                else
                {
                    (*iter)->loc_path = "./default_error_pages/404.html";
                    this->state = 1;
                    return ;
                }
            }
            else
            {
                (*iter)->loc_path = "./default_error_pages/404.html";
                this->state = 1;
                return ;
            }
        }
        else
            (*iter)->loc_path = "./default_error_pages/404.html";
        return ;
    }
}

void    Get::check_the_end_of_uri(std::list<Client *>::iterator iter)
{
    std::string path = (*iter)->loc_path; 
    if (path[path.length() - 1] != '/')
    {
        (*iter)->redirect_301.append("/");
        std::cout<<"error / 301 Moved Permanently"<<std::endl;
        (*iter)->status_code = 301;
        (*iter)->status = "Moved Permanently";
        this->state = 1;
        return ;
    }
    else
          is_dir_has_index_files(iter);
}

void    Get::is_dir_has_index_files(std::list<Client *>::iterator iter)
{
    location loc = (*iter)->location_match;
    std::list<std::string> index = loc.get_index();
    std::list<std::string>::iterator it;
    struct stat file_stat;
    for(it = index.begin(); it != index.end(); it++)
    {
        std::string path = (*iter)->loc_path + (*it);
        if (stat(path.c_str(), &file_stat) == 0)
        {
            if (S_ISREG(file_stat.st_mode))
            {
                this->index_exist = 1;
                // std::cout<<"is file "<<std::endl;
                break ;
            }
        }
    }
    if (this->index_exist == 1)
    {
        (*iter)->loc_path.append((*it));
        // std::cout<<"heer: "<<(*iter)->loc_path<<std::endl;
        if_location_has_cgi(iter);
    }
    else
        check_for_auto_index(iter);
}

std::string Get::getHeaderCgi(std::string header)
{
    std::string cgiHeader(header);
    for (int i = 0; i < header.length(); i++)
    {
        if (header[i] == '-')
            cgiHeader[i] = '_';
        else if (islower(header[i]))
            cgiHeader[i] = toupper(header[i]);
    }
    return ("HTTP_" + cgiHeader);
}

void Get::addCgiHeaders(std::list<Client *>::iterator iter)
{
    Client *client  = *iter;
    if (client == nullptr)
    {
        printf("equal nulll  \n");
        return ;
    }
    std::map<std::string, std::vector<std::string> >::iterator it = (*iter)->request_pack.begin();

    while (it != (*iter)->request_pack.end())
    {
        if (!it ->first.empty())
        {
            std::string cgiHeader = getHeaderCgi(it->first);
    
            std::vector<std::string> v = it ->second;
            std::string cgiValue;
            std::cout<<"size : "<<v.size()<<std::endl;
            for (int i = 0; i < (int)v.size() - 1;i++)
                cgiValue += v[i] + " ";
            if (!v.empty())
                cgiValue += v[v.size() - 1];
            std::string currEnvVal =  cgiHeader + "="+ cgiValue;
            //std::cout << "currVaal ====== " << currEnvVal << std::endl;
            (*iter)->env = ft_add_var((*iter)->env, const_cast<char *>(currEnvVal.c_str()));
        }

        it++;
    }
}

void    Get::if_location_has_cgi(std::list<Client *>::iterator iter)
{
    // if cgi exist
    //run it && return code depend on it
    //else
    // std::cout<<"path : "<< (*iter)->loc_path<<std::endl;
    int dot = (*iter)->loc_path.rfind('.');
    std::string extention = &(*iter)->loc_path[dot + 1];
    std::map<std::string, std::string> cgi = (*iter)->location_match.get_cgi_pass();
    std::map<std::string, std::string>::iterator it = cgi.find(extention);
    if (it != cgi.end())
    {
        std::string str = it->second;
        // std::cout<<"exucutable : "<<(*iter)->loc_path<<std::endl;
        if (access(str.c_str(), X_OK) == 0)
        {
            std::string filename = create_temp_file((*iter));
            (*iter)->fd = open(filename.c_str(), O_CREAT | O_RDWR | O_TRUNC);
            if ((*iter)->fd < 0)
            {
                (*iter)->status_code = 403;
                (*iter)->status = "Forbidden";
                (*iter)->loc_path = "./default_error_pages/403.html";
                this->state = 1;
                return ;
            }
            std::string pathInfo = "PATH_INFO=" + (*iter)->loc_path;
            (*iter)->env = ft_add_var((*iter)->env, const_cast<char *>(pathInfo.c_str()));
            std::string queryString = "QUERY_STRING=" + (*iter)->query;
            (*iter)->env = ft_add_var((*iter)->env, const_cast<char *>(queryString.c_str()));
            addCgiHeaders(iter);
            int i = 0 ;
            // while ( (*iter)->env[i])
            // {
            //     std::cout << (*iter)->env[i] << std::endl;
            //     i++;
            // }
            (*iter)->pid = fork();
            if ((*iter)->pid == 0)
            {
                dup2((*iter)->fd, STDOUT_FILENO);
                char *arg[3];
                arg[0] = strdup(str.c_str());
                arg[1] = strdup((*iter)->loc_path.c_str());
                arg[2] = NULL;
                execve(arg[0], arg, (*iter)->env);
            }
            (*iter)->header_flag = 1;
            (*iter)->loc_path = filename;
            (*iter)->status_code = 200;
            (*iter)->status = "OK";
        }
        else
        {
            (*iter)->header_flag = 0;
            (*iter)->status_code = 200;
            (*iter)->status = "OK";
        }
    }
    else
    {
        (*iter)->header_flag = 0;
        (*iter)->status_code = 200;
        (*iter)->status = "OK";
    }
    return ;
}

void    Get::check_for_auto_index(std::list<Client *>::iterator iter)
{
    location loc = (*iter)->location_match;
    if (loc.get_auto_index() == "on")
    {
        DIR *dir = opendir((*iter)->loc_path.c_str());
        if (dir == NULL)
        {
            (*iter)->status_code = 403;
            (*iter)->status = "Forbidden";
            (*iter)->loc_path = "./default_error_pages/403.html";
            this->state = 1;
            return ;
        }
        std::ofstream outfile("./default_error_pages/auto_index.html");
        if (!outfile.is_open())
        {
            (*iter)->status_code = 403;
            (*iter)->status = "Forbidden";
            (*iter)->loc_path = "./default_error_pages/403.html";
            this->state = 1;
            return ;
        }
        struct dirent *entity;
        entity = readdir(dir);
        std::cout<<(*iter)->redirect_301<<std::endl;
        outfile<<"<html><head><title>Listing directories</title></head><body><h1>listing files : </h1>";
        while (entity != NULL)
        {
            std::string uri = (*iter)->redirect_301;
            if (uri[uri.length() - 1] != '/')
                uri += "/";
            uri += entity->d_name;
            outfile<< "<li><a href='"+ uri + "'>"+ entity->d_name +"</a></li></br>";
            entity = readdir(dir);
        }
        outfile<<"</body></html>"<<std::endl;
        closedir(dir);
        this->state = 1;
        (*iter)->status_code = 200;
        (*iter)->status = "OK";
        (*iter)->loc_path = "./default_error_pages/auto_index.html";
        this->state = 1;
    }
    else
    {
        (*iter)->status_code = 403;
        (*iter)->status = "Forbidden";
        std::vector<std::string> error = (*iter)->error_pages;
        std::vector<std::string>::iterator it = error.begin();
        if (it != error.end())
        {
            int num;
            std::stringstream ss(*it);
            ss >> num;
            if (num == (*iter)->status_code)
            {
                std::string path = "." + (*++it);
                struct stat file_stat;
                if (stat(path.c_str(), &file_stat) == 0)
                {
                    if (S_ISREG(file_stat.st_mode))
                    {
                        (*iter)->loc_path = path;
                        this->state = 1;
                        return ;
                    }
                    else
                    {
                        (*iter)->loc_path = "./default_error_pages/403.html";
                        this->state = 1;
                        return ;
                    }
                }
                else
                {
                    (*iter)->loc_path = "./default_error_pages/403.html";
                    this->state = 1;
                    return ;
                }
            }
            else
            {
                (*iter)->loc_path = "./default_error_pages/403.html";
                this->state = 1;
                return ;
            }
        }
        else
            (*iter)->loc_path = "./default_error_pages/403.html";
        this->state = 1;
        return ;
    }
}