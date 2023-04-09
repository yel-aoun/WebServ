#include "post.hpp"
#include "../server/server.hpp"
#include "../parsing/location.hpp"
#include "../server/client.hpp"
#include "../parsing/webserv.hpp"


Post::Post(): body_or_head(0), _post_type(0), _chunk_len(0), _hex_len(0), is_created(false), _buff_read(0) , _is_matched(0)
{
    this->is_tmp_finished = 0;
    memset(this->_hex, 0, 20);
}

Post::~Post(){}

void Post::check_post(Client *clt)
{
    if (!clt->location_match.get_upload_pass().empty())
        _is_matched = 1;
}

void    Post::call_post_func(Server &serv, Client *client)
{
    if (_is_matched == 1)
    {
        if(!is_created && this->_post_type != 1)
            this->create_file(serv, client);
        switch(this->_post_type)
        {
            case 0:
                this->normal_post(serv, client);
                break;
            case 1:
                this->boundary_post(serv, client);
                break;
            case 2:
                this->chunked_post(serv, client);
                break;
        }
    }
    else
        Treat_Post(client, serv);
}

char	**ft_add_var(char **env, char *cmd)
{
	int		i;
	char	**newenv;

	i = 0;
	newenv = new char* [sizeof(char *) * (ft_strlenc(env) + 2)];
	if (newenv == 0)
	{
		free(newenv);
		return (NULL);
	}
	while (env[i] != 0)
	{
		newenv[i] = strdup(env[i]);
		i++;
	}
	newenv[i++] = strdup(cmd);
	newenv[i] = 0;
    i = 0;
	free_str_array(env, ft_strlenc(env));
	return (newenv);
}

std::string create_temp_file(Client *ctl)
{
    std::string filename;
    time_t now;
    std::ifstream file;
    now = std::time(0);
    filename = "/tmp/file" + std::to_string(now) + "XXXXXX";
    int fd = mkstemp(&filename[0]);
    if (fd == -1) {
        std::perror("mkstemp");
        std::exit(EXIT_FAILURE);
    }
    return (filename);
}

void Post::Add_Necessary_Env(Client *ctl)
{
    // ctl->file.flush(); 
    // ctl->file.seekp(0, std::ios::end);
    // unsigned int l = static_cast<unsigned int>(ctl->file.tellp());
    // ctl->file.seekp(0, std::ios::beg);
    // std::string ct = "CONTENT_LENGTH=" + std::to_string(l);
    // ctl->env = ft_add_var(ctl->env, const_cast<char *>(ct.data()));
    // std::cout << "*****************" << std::endl;
    // std::map<std::string, std::vector<std::string> >::iterator iter;
    // iter = ctl->request_pack.find("Content-Type");
    // std::cout << "==== " << iter.first() << std::endl;
    std::cout << "INFO ===== " << ctl->loc_path << std::endl;
    std::string test = "PATH_INFO=" + ctl->loc_path + "index.php" ; 
    ctl->env = ft_add_var(ctl->env, const_cast<char *>(test.data()));
    std::string test2 = "QUERY_STRING=" + ctl->query;
    ctl->env = ft_add_var(ctl->env, const_cast<char *>(test2.data()));
    std::string test3 = "CONTENT_LENGTH=98350";
    ctl->env = ft_add_var(ctl->env, const_cast<char *>(test3.data()));
    std::string test4 = "CONTENT_TYPE=image/png";
    ctl->env = ft_add_var(ctl->env, const_cast<char *>(test4.data()));
    std::string test5 = "SCRIPT_FILENAME=/Users/zouazahr/Desktop/Mainweb/test/index.php";
    ctl->env = ft_add_var(ctl->env, const_cast<char *>(test5.data()));
    ctl->env[ft_strlenc(ctl->env)] = NULL;
}

void Post::Handle_exec(Client *ctl)
{
    std::map<std::string, std::string> cgi = ctl->location_match.get_cgi_pass();
    std::map<std::string, std::string>::iterator it = cgi.find("php");
    std::string str;
    if (it != cgi.end())
        str = it->second;
    else
    {
        std::cout << "YA done goofed" << std::endl;
        exit(0);
    }
    std::string filename = create_temp_file(ctl);
    std::cout << "filename ====== " << filename << std::endl;
    int fd = open(filename.c_str(), 1);
    if (fd < 0)
    {
        std::cout << "Hey i'm here " << std::endl;
        ctl->status_code = 403;
        ctl->status = "Forbidden";
        ctl->loc_path = "./default_error_pages/403.html";
        return ;
    }
    if (fork() == 0)
    {
        dup2(fd, STDOUT_FILENO);
        close(fd);
        int ok = open(path.c_str(), O_RDWR);
        dup2(ok, 0);
        close(ok);
        char *arg[3];
        int i = 0;
            while (i < ft_strlenc(ctl->env))
        {
            std::cerr << "=====> " << ctl->env[i] << std::endl;
            i++;
        }
        arg[0] = strdup("/Users/zouazahr/Desktop/webserv/cgi-bin/php-cgi");
        std::cerr << "0-0-0-0-0-0> " << str << std::endl;
        arg[1] = strdup((ctl->loc_path + "index.php").c_str());
        arg[2] = NULL;
        std::cerr<<arg[1]<<std::endl;
        execve(arg[0], arg, ctl->env);
    }
    wait(NULL);
    close(fd);
     ctl->loc_path = "./default_error_pages/200.html";
     ctl->status_code = 200;
     ctl->status = "OK";
}

void Post::Treat_Cgi(Client *ctl, Server &serv)
{
    std::string filename = create_temp_file(ctl);
    ctl->file.open(filename.c_str(), std::ios::out | std::ios::binary);
    std::cout << "OG path : " << filename << std::endl;
    path = filename;
    if (!ctl->file.is_open())
    {
        std::cout << "Temporary file error"<< std::endl;
        exit(1);
    }
    else
    {
        std::cout << "HERE" << std::endl;
        is_created = true;
        _is_matched = 1;
        call_post_func(serv, ctl);
        Add_Necessary_Env(ctl);
        Handle_exec(ctl);
    }
}

void Post::Treat_directory(Client *ctl, Server &serv)
{
    if (ctl->location_match.get_index().empty())
    {
        ctl->status_code = 403;
        ctl->status = "Forbidden";
        ctl->loc_path = "./default_error_pages/403.html";
        return ;
    }
    else
    {
        if (ctl->location_match.get_cgi_pass().empty())
        {
            ctl->status_code = 403;
            ctl->status = "Forbidden";
            ctl->loc_path = "./default_error_pages/403.html";
            return ;
        }
        else
            Treat_Cgi(ctl, serv);
    }
}

void Post::Treat_file(Client *ctl, Server &serv)
{
    if (ctl->location_match.get_cgi_pass().empty())
    {   
        ctl->status_code = 403;
        ctl->status = "Forbidden";
        ctl->loc_path = "./default_error_pages/403.html";
        return ;
    }
    else
        Treat_Cgi(ctl, serv);
}

void Post::Treat_Post(Client *ctl, Server &serv)
{      
    DIR* dir = opendir(ctl->loc_path.c_str());
    if (dir != NULL)
    {
        std::cout << "The client requested a directory" << std::endl;
        if (ctl->loc_path[ctl->loc_path.size() - 1] == '/')
            Treat_directory(ctl, serv);
        else
        {
            ctl->loc_path += "/";
            this->Treat_directory(ctl, serv);
        }
    }
    else if (fopen(ctl->loc_path.c_str(), "r") != NULL)
    {
        std::cout << "The client requested a file" << std::endl;
        this->Treat_file(ctl, serv);
    }
    else
    {
        ctl->status_code = 404;
        ctl->status = "Not Found";
        ctl->loc_path = "./default_error_pages/404.html";
        return ;
    }
}

void    Post::create_file(Server &serv, Client *client)
{
    std::string merge_path;
    if(client->file_path.empty())
    {
        std::map<std::string, std::vector<std::string> >::iterator iter;
        iter = client->request_pack.find("Content-Type");
        merge_path = client->loc_path + "/" + client->location_match.get_upload_pass();
        client->file_path = merge_path;
        client->generate_file_name(*((*iter).second.begin()), serv.file_extensions);
    }
    if (access(merge_path.c_str(), F_OK))
        mkdir(merge_path.c_str(), 0777);
    if(access(const_cast<char *>(client->file_path.c_str()), F_OK))
        client->file.open(client->file_path, std::ios::binary | std::ios::app);
    this->is_created = true;
}