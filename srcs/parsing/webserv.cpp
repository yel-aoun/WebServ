# include "webserv.hpp"
void Webserv::parce_config_file(std::string &conf_file)
{
	int count_location = 0;
	int count_serv = 0;
	int count_loc = 0;
	int i = 0;
    if (conf_file.empty())
    {
        std::cout << "Error! Empty string you must provide a config file";
		exit(1);
    }
	size_t extension = conf_file.rfind(".conf");
	if (extension == -1 || extension + 5 != conf_file.length())
	{
		std::cout << "Error! Please check the extension" << std::endl;
		exit(1);
	}
    std::ifstream filein;
	filein.open(conf_file);
	if (filein)
	{
		while (filein.good())
		{
			getline(filein, conf_file);
			if (conf_file.find("{") != -1)
				i++;
			if (conf_file.find("}") != -1)
				i--;
			if (i < 0)
			{
				std::cout << "Error! Please close every bracket" << std::endl;
				exit (1);
			}
			if (conf_file.find("server") != std::string::npos)
				count_serv++;
            config.push_back(conf_file);
		}
		filein.close();
		if (i != 0)
		{
			std::cout << "Error! Please close every bracket" << std::endl;
			exit (1);
		}
		i = 0;
		int j = 0;
		while (i < count_serv)
		{
			parce_server	serv(config, i);
	 		this->servers_data.push_back(serv);
	 		i++;
		}
	}
	else
	{
		std::cout << "Error! Please check if the file exists!" << std::endl;
		exit (1);
	}
}

Webserv::Webserv(std::string conf_file)
{
	parce_config_file(conf_file);
	run_webservs();
}

void Webserv::init_servers()
{
	std::list<parce_server>::iterator iter;
	for(iter = servers_data.begin(); iter != servers_data.end(); iter++)
	{
		Server *sv = new Server(*iter);
		this->servers.push_back(sv);
	}
	// std::cout<<this->servers.size()<<std::endl;
}

void Webserv::run_webservs()
{
	this->init_servers();
	while (1)
	{
		std::list<Server *>::iterator iter;
		// std::cout<<this->servers.size()<<std::endl;
		for(iter = this->servers.begin(); iter != this->servers.end(); iter++)
		{
			(*iter)->run_serve();
			std::cout<<"runing servers"<<std::endl;
		}
	}
}